#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <cstring>
#include "structures.h"

using namespace std;

void AES_encrypt(unsigned char state[16], unsigned char* expandedKey) {
    AddRoundKey(state, expandedKey);
    for (int round = 1; round <= 9; round++) {
        SubBytes(state);
        ShiftRows(state);
        MixColumns(state);
        AddRoundKey(state, expandedKey + (round * 16));
    }
    SubBytes(state);
    ShiftRows(state);
    AddRoundKey(state, expandedKey + 160);
}

int main() {
    unsigned char key[16] = {0};
    unsigned char expandedKey[176] = {0};
    char message[17] = {0};

    cout << "=============================" << endl;
    cout << "AES-128 Encryption Tool" << endl;
    cout << "=============================" << endl;

    // Đọc key từ file
    ifstream kf("keyfile");
    if (kf) {
        int val;
        for (int i = 0; i < 16 && (kf >> hex >> val); i++) {
            key[i] = (unsigned char)val;
        }
        kf.close();
    }

    KeyExpansion(key, expandedKey);

    cout << "Enter 16-char message: ";
    cin.getline(message, 17);

    unsigned char state[16] = {0};
    memcpy(state, message, strlen(message));

    AES_encrypt(state, expandedKey);

    // Xuất file message.aes
    ofstream out("message.aes", ios::binary);
    out.write((char*)state, 16);
    out.close();

    cout << "Encrypted hex: ";
    for(int i = 0; i < 16; i++) 
        cout << hex << setw(2) << setfill('0') << (int)state[i];
    cout << endl << "Saved to message.aes" << endl;

    return 0;
}
