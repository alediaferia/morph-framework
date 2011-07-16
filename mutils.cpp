#include "mutils.h"
#include <string>
#include <iostream>
#include <cmath>
#include "mmutex.h"

MMutex mutils_print_mutex;

const char* mArrayToHex(const char* input, int length)
{
    const int outputLength = length * 2 + 1;
    unsigned char *string = new unsigned char[outputLength];

    int j = 0;
    for (int i = 0; i < length; i++) {

        const unsigned int mostSignificant = input[i] >> 4;
        const unsigned int leastSignificant = input[i] & 0x0000FFFF;

        if (mostSignificant < 10) {
            string[j] = mostSignificant + 0x00000030;
        } else {
            string[j] = mostSignificant + 0x00000057;
        }

        if (leastSignificant < 10) {
            string[j + 1] = leastSignificant + 0x00000030;
        } else {
            string[j + 1] = leastSignificant + 0x00000057;
        }

        j += 2;
    }

    string[outputLength - 1] = '\0';
    return (const char*)string;
}

/*
    F(X,Y,Z) = XY v not(X) Z
    G(X,Y,Z) = XZ v Y not(Z)
    H(X,Y,Z) = X xor Y xor Z
    I(X,Y,Z) = Y xor (X v not(Z))
*/

uint32_t F(uint32_t X, uint32_t Y, uint32_t Z)
{
    return (X & Y) | ((!X) & Z);
}

uint32_t G(uint32_t X, uint32_t Y, uint32_t Z)
{
    return (X & Z) | (Y & (!Z));
}

uint32_t H(uint32_t X, uint32_t Y, uint32_t Z)
{
    return X ^ Y ^ Z;
}

uint32_t I(uint32_t X, uint32_t Y, uint32_t Z)
{
    return Y ^ (X | (!Z));
}

uint32_t leftrotate (uint32_t x, uint32_t c) {
    return (x << c) or (x >> (32-c));
}

bool mLittleEndian()
{
    union {
        uint32_t i;
        char c[4];
    }mint = {0x01000004};

    return mint.c[0] == 4;
}

int mHash(const char *message)
{
    // rfc requires little endian
    // bits order
    // if we are on a big-endian architecture
    // we need to reverse the message bits

    if (!mLittleEndian()) {
        // reversing code...
    }

    const uint32_t length = strlen(message);

    // padding
    // message must be 64 bits fewer than 512 bits multiple
    uint32_t remain = 0;
    if (length < 56) {
        remain = 56 - length;
    } else {
        remain = length % 56; // 448 bits
    }

    const int newLength = length + remain + 8;

    unsigned char *result = new unsigned char[newLength]; // length -> 512bits modulo

    strcpy((char*)result, message);
    result[length] = (unsigned int)128;
    for (uint32_t i = 1; i < remain; i++) {
        result[length + i] = (unsigned int)0;
    }

    uint64_t length64 = length;
    // original length must be stored
    // at the end as a 64 bit integer
    // with little-endian representation
    result[length + remain] = (uint32_t) length64 >> 56;
    result[length + remain + 1] = (uint32_t) length64 >> 48;
    result[length + remain + 2] = (uint32_t) length64 >> 40;
    result[length + remain + 3] = (uint32_t) length64 >> 32;
    result[length + remain + 4] = (uint32_t) length64 >> 24;
    result[length + remain + 5] = (uint32_t) length64 >> 16;
    result[length + remain + 6] = (uint32_t) length64 >> 8;
    result[length + remain + 7] = (uint32_t) length64;

    /*
        word A: 01 23 45 67
        word B: 89 ab cd ef
        word C: fe dc ba 98
        word D: 76 54 32 10
    */

    // low order defined words
    uint32_t A = 0x67452301;
    uint32_t B = 0xEFCDAB89;
    uint32_t C = 0x98BADCFE;
    uint32_t D = 0x10325476;

    // per-round pre-defined shifts
    static const uint32_t roundShifts[64] = {
        7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
        5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,
        4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
        6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
    };

    // binary integer part of the sines of integers (Radians) as constants
    float k[64];
    for (int i = 0; i < 64; i++) {
        const float fsin = (float)sin((float)i + 1);
        const float abs_sin = fabs(fsin);
        k[i] = floor(abs_sin * (2^32));
    }

    // one round for each of the 512bits block
    for (uint32_t i = 0; i < newLength; i += 64) {
        uint32_t a = A;
        uint32_t b = B;
        uint32_t c = C;
        uint32_t d = D;

        uint32_t words[16];
        for (int j = 0; j < 16; j++) {
            words[j] = (uint32_t)result[i] >> 24 |
                                   (uint32_t)result[i + 1] >> 16 |
                                   (uint32_t)result[i + 2] >> 8 |
                                   (uint32_t)result[i + 3];
        }

        uint32_t f;
        uint32_t g;
        for (uint32_t j = 0; j < 64; j++) {
            if (j < 16) {
                f = F(b, c, d);
                g = j;
            } else if (j < 32) {
                f = F(d, b, c);
                g = (5 * j + 1) % 16;
            } else if (j < 48) {
                f = H(b, c, d);
                g = (3 * j + 5) % 16;
            } else if (j < 64) {
                f = I(b, c, d);
                g = (7 * j) % 16;
            }

            uint32_t temp = d;
            d = c;
            c = b;
            b = b + leftrotate((a + f + k[j] + words[g]), roundShifts[i]);
            a = temp;

            A = A + a;
            B = B + b;
            C = C + c;
            D = D + d;
        }
    }

    unsigned char output[16];
    output[0] = (uint32_t) A >> 24;
    output[1] = (uint32_t) A & 0x00FF0000 >> 16;
    output[2] = (uint32_t) A & 0x0000FF00 >> 8 ;
    output[3] = (uint32_t) A & 0x000000FF;

    output[4] = (uint32_t) B >> 24;
    output[5] = (uint32_t) B & 0x00FF0000 >> 16;
    output[6] = (uint32_t) B & 0x0000FF00 >> 8 ;
    output[7] = (uint32_t) B & 0x000000FF;

    output[8] = (uint32_t) C >> 24;
    output[9] = (uint32_t) C & 0x00FF0000 >> 16;
    output[10] = (uint32_t) C & 0x0000FF00 >> 8 ;
    output[11] = (uint32_t) C & 0x000000FF;

    output[12] = (uint32_t) D >> 24;
    output[13] = (uint32_t) D & 0x00FF0000 >> 16;
    output[14] = (uint32_t) D & 0x0000FF00 >> 8 ;
    output[15] = (uint32_t) D & 0x000000FF;

    //std::cout << "digest: " << mArrayToHex(output, 16) << std::endl;


    return 0;
}

void mPrint(const char *message)
{

    mutils_print_mutex.lock();

    std::cout << message << std::endl;

     mutils_print_mutex.unlock();
}

