#include <iostream>
#include <fstream>
#include <cstring>
#include "structures.h"

using namespace std;

unsigned char gmul(unsigned char a, unsigned char b) {
    unsigned char p = 0;
    for (int i = 0; i < 8; i++) {
        if (b & 1) p ^= a;
        unsigned char hi_bit = (a & 0x80);
        a <<= 1;
        if (hi_bit) a ^= 0x1b;
        b >>= 1;
    }
    return p;
}

void AddRoundKey(unsigned char* state, unsigned char* roundKey) {
    for (int i = 0; i < 16; i++) state[i] ^= roundKey[i];
}

void InvSubBytes(unsigned char* state) {
    for (int i = 0; i < 16; i++) state[i] = rsbox[state[i]];
}

void InvShiftRows(unsigned char* state) {
    unsigned char tmp[16];
    tmp[0] = state[0]; tmp[4] = state[4]; tmp[8] = state[8]; tmp[12] = state[12];
    tmp[1] = state[13]; tmp[5] = state[1]; tmp[9] = state[5]; tmp[13] = state[9];
    tmp[2] = state[10]; tmp[6] = state[14]; tmp[10] = state[2]; tmp[14] = state[6];
    tmp[3] = state[7]; tmp[7] = state[11]; tmp[11] = state[15]; tmp[15] = state[3];
    memcpy(state, tmp, 16);
}

void InvMixColumns(unsigned char* state) {
    unsigned char tmp[16];
    for (int i = 0; i < 4; i++) {
        int o = i * 4;
        unsigned char s0 = state[o], s1 = state[o+1], s2 = state[o+2], s3 = state[o+3];
        tmp[o]   = gmul(s0, 0x0e) ^ gmul(s1, 0x0b) ^ gmul(s2, 0x0d) ^ gmul(s3, 0x09);
        tmp[o+1] = gmul(s0, 0x09) ^ gmul(s1, 0x0e) ^ gmul(s2, 0x0b) ^ gmul(s3, 0x0d);
        tmp[o+2] = gmul(s0, 0x0d) ^ gmul(s1, 0x09) ^ gmul(s2, 0x0e) ^ gmul(s3, 0x0b);
        tmp[o+3] = gmul(s0, 0x0b) ^ gmul(s1, 0x0d) ^ gmul(s2, 0x09) ^ gmul(s3, 0x0e);
    }
    memcpy(state, tmp, 16);
}

void KeyExpansion(unsigned char* key, unsigned char* expandedKey) {
    memcpy(expandedKey, key, 16);
    int bytesGenerated = 16, rconPtr = 1;
    unsigned char temp[4];
    while (bytesGenerated < 176) {
        memcpy(temp, expandedKey + bytesGenerated - 4, 4);
        if (bytesGenerated % 16 == 0) {
            unsigned char t = temp[0];
            temp[0] = s[temp[1]] ^ Rcon[rconPtr++];
            temp[1] = s[temp[2]]; temp[2] = s[temp[3]]; temp[3] = s[t];
        }
        for (int i = 0; i < 4; i++) {
            expandedKey[bytesGenerated] = expandedKey[bytesGenerated - 16] ^ temp[i];
            bytesGenerated++;
        }
    }
}

int main() {
    unsigned char key[16] = {0}, expandedKey[176] = {0}, state[16] = {0};
    
    ifstream kf("keyfile");
    int val;
    for (int i = 0; i < 16 && (kf >> hex >> val); i++) key[i] = (unsigned char)val;
    kf.close();

    ifstream in("message.aes", ios::binary);
    if (in) {
        in.read((char*)state, 16);
        in.close();
    }

    KeyExpansion(key, expandedKey);
    AddRoundKey(state, expandedKey + 160);
    for (int r = 9; r >= 1; r--) {
        InvShiftRows(state);
        InvSubBytes(state);
        AddRoundKey(state, expandedKey + (r * 16));
        InvMixColumns(state);
    }
    InvShiftRows(state);
    InvSubBytes(state);
    AddRoundKey(state, expandedKey);

    // CHỈ IN ĐÚNG 16 BYTE, KHÔNG THÊM DẤU XUỐNG DÒNG
    cout.write((char*)state, 16);
    return 0;
}
