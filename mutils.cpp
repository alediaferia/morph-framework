#include "mutils.h"
#include <string>
#include <iostream>
#include <cmath>
#include "mmutex.h"

MMutex mutils_print_mutex;

/*
    F(X,Y,Z) = XY v not(X) Z
    G(X,Y,Z) = XZ v Y not(Z)
    H(X,Y,Z) = X xor Y xor Z
    I(X,Y,Z) = Y xor (X v not(Z))
*/
/*
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
    return (x << c) | (x >> (32-c));
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
    uint32_t totalBitLength = length*8 + 1; // added one 1 bit
    while ((totalBitLength + 64) % 512) {
        totalBitLength += 1;
    }

    const int outputMessageByteLength = (totalBitLength + 64) / 8;
    uint8_t *outputMessage = new uint8_t[outputMessageByteLength];
    strcpy((char*)outputMessage, message);
    outputMessage[length + 1] = 0x80;
    for (int i = length + 2; i < outputMessageByteLength - 7; i++) {
        outputMessage[i] = 0x00;
    }

    outputMessage[outputMessageByteLength - 8] = 0x00;
    outputMessage[outputMessageByteLength - 7] = 0x00;
    outputMessage[outputMessageByteLength - 6] = 0x00;
    outputMessage[outputMessageByteLength - 5] = 0x00;

    outputMessage[outputMessageByteLength - 4] = length >> 24;
    outputMessage[outputMessageByteLength - 3] = length >> 16;
    outputMessage[outputMessageByteLength - 2] = length >> 8;
    outputMessage[outputMessageByteLength - 1] = length;
    // --- padding ended ---

    //
    //    word A: 01 23 45 67
    //    word B: 89 ab cd ef
    //    word C: fe dc ba 98
    //    word D: 76 54 32 10

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
    for (uint32_t i = 0; i < outputMessageByteLength; i += 64) {
        uint32_t a = A;
        uint32_t b = B;
        uint32_t c = C;
        uint32_t d = D;

        uint32_t words[16];
        int offset = 0;
        for (int j = 0; j < 16; j++) {
            words[j] = (uint32_t)(outputMessage[i + offset]) << 24 |
                                   (uint32_t)(outputMessage[i + offset + 1]) << 16 |
                                   (uint32_t)(outputMessage[i + offset + 2]) << 8 |
                                   (uint32_t)(outputMessage[i + offset + 3]);
            offset += 4;
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
            } else {
                f = I(b, c, d);
                g = (7 * j) % 16;
            }

            uint32_t temp = d;
            d = c;
            c = b;
            b = b + leftrotate((a + f + k[j] + words[g]), roundShifts[j]);
            a = temp;

            A = A + a;
            B = B + b;
            C = C + c;
            D = D + d;
        }
    }

    printf("A: %x, B: %x, C: %x, D: %x\n", A, B, C, D);

    uint8_t output[16];
    output[0] =  A >> 24;
    output[1] =  A >> 16;
    output[2] =  A >> 8 ;
    output[3] =  A;

    output[4] = B >> 24;
    output[5] = B >> 16;
    output[6] = B >> 8 ;
    output[7] = B;

    output[8] = C >> 24;
    output[9] = C >> 16;
    output[10] = C >> 8 ;
    output[11] = C;

    output[12] =  D >> 24;
    output[13] = D >> 16;
    output[14] = D >> 8 ;
    output[15] = D;

    //std::cout << "digest: " << mArrayToHex(output, 16) << std::endl;
    for (int i = 0; i < 16; i++) {
        printf("%02x", output[i]);
    }
    printf("\n");

    return 0;
}
*/

void mPrint(const char *message)
{
    mutils_print_mutex.lock();
    std::cout << message << std::endl;
    mutils_print_mutex.unlock();
}

