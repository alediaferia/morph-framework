#ifndef MUTILS_H
#define MUTILS_H

bool mLittleEndian();

const char* mArrayToHex(const unsigned char* input, int length);
int mHash(const char* message);

void mPrint(const char *message);

#endif // MUtils
