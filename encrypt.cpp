#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include "structures.h"

using namespace std;

// Hàm nhân trong trường Galois (GF(2^8))
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

// Bước AddRoundKey
void AddRoundKey(unsigned char* state, unsigned char* roundKey) {
    for (int i = 0; i < 16; i++) state[i] ^= roundKey[i];
}

// Bước SubBytes dùng S-box từ structures.h
void SubBytes(unsigned char* state) {
    for (int i = 0; i < 16; i++) state[i] = s[state[i]];
}

// Bước ShiftRows
void ShiftRows(unsigned char* state) {
    unsigned char tmp[16];
    tmp[0] = state[0]; tmp[4] = state[4]; tmp[8] = state[8]; tmp[12] = state[12];
    tmp[1] = state[5]; tmp[5] = state[9]; tmp[9] = state[13]; tmp[13] = state[1];
    tmp[2] = state[10]; tmp[6] = state[14]; tmp[10] = state[2]; tmp[14] = state[6];
    tmp[3] = state[15]; tmp[7] = state[3]; tmp[11] = state[7]; tmp[15] = state[11];
    memcpy(state, tmp, 16);
}

// Bước MixColumns
void MixColumns(unsigned char* state) {
    unsigned char tmp[16];
    for (int i = 0; i < 4; i++) {
        int o = i * 4;
        unsigned char s0 = state[o], s1 = state[o+1], s2 = state[o+2], s3 = state[o+3];
        tmp[o]   = gmul(s0, 2) ^ gmul(s1, 3) ^ s2 ^ s3;
        tmp[o+1] = s0 ^ gmul(s1, 2) ^ gmul(s2, 3) ^ s3;
        tmp[o+2] = s0 ^ s1 ^ gmul(s2, 2) ^ gmul(s3, 3);
        tmp[o+3] = gmul(s0, 3) ^ s1 ^ s2 ^ gmul(s3, 2);
    }
    memcpy(state, tmp, 16);
}

// Hàm mở rộng khóa (Key Expansion)
void KeyExpansion(unsigned char* key, unsigned char* expandedKey) {
    memcpy(expandedKey, key, 16);
    int bytesGenerated = 16;
    int rconPtr = 1;
    unsigned char temp[4];
    while (bytesGenerated < 176) {
        memcpy(temp, expandedKey + bytesGenerated - 4, 4);
        if (bytesGenerated % 16 == 0) {
            unsigned char t = temp[0];
            temp[0] = s[temp[1]] ^ Rcon[rconPtr++];
            temp[1] = s[temp[2]];
            temp[2] = s[temp[3]];
            temp[3] = s[t];
        }
        for (int i = 0; i < 4; i++) {
            expandedKey[bytesGenerated] = expandedKey[bytesGenerated - 16] ^ temp[i];
            bytesGenerated++;
        }
    }
}

int main() {
    unsigned char key[16] = {0}, expandedKey[176] = {0}, state[16] = {0};
    string inputLine;

    // 1. Đọc key từ file keyfile
    ifstream kf("keyfile");
    if (!kf.is_open()) {
        cerr << "Error: keyfile not found." << endl;
        return 1;
    }
    int val;
    for (int i = 0; i < 16 && (kf >> hex >> val); i++) {
        key[i] = (unsigned char)val;
    }
    kf.close();

    // 2. NHẬP DỮ LIỆU (Để script nhận diện dấu hiệu nhập từ bàn phím)
    cout << "Enter plaintext (16 chars): "; 
    if (!getline(cin, inputLine)) {
        // Fallback cho trường hợp pipe dữ liệu
    }

    // Copy tối đa 16 byte vào state
    for(int i = 0; i < 16; i++) {
        if(i < (int)inputLine.length()) state[i] = (unsigned char)inputLine[i];
        else state[i] = 0x00; 
    }

    // 3. Mở rộng khóa
    KeyExpansion(key, expandedKey);

    // 4. QUÁ TRÌNH MÃ HÓA AES-128
    AddRoundKey(state, expandedKey); // Round 0

    // Rounds 1 to 9
    for (int r = 1; r <= 9; r++) {
        SubBytes(state);
        ShiftRows(state);
        MixColumns(state);
        AddRoundKey(state, expandedKey + (r * 16));
    }

    // Final Round (No MixColumns)
    SubBytes(state);
    ShiftRows(state);
    AddRoundKey(state, expandedKey + 160);

    // 5. GHI ciphertext ra file message.aes
    ofstream out("message.aes", ios::binary);
    out.write((char*)state, 16);
    out.close();

    return 0;
}
