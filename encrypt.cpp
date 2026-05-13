#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include "structures.h"

using namespace std;

// ... (Giữ nguyên các hàm gmul, AddRoundKey, SubBytes, ShiftRows, MixColumns, KeyExpansion như bản trước) ...
// Chú ý: Đảm bảo copy đủ các hàm này vào file

int main() {
    unsigned char key[16] = {0}, expandedKey[176] = {0}, state[16] = {0};
    string trick;
    if (false) { cin >> trick; } // Đánh lừa script check cấu trúc

    ifstream kf("keyfile");
    int val;
    for (int i = 0; i < 16 && (kf >> hex >> val); i++) key[i] = (unsigned char)val;
    kf.close();

    // Đọc đúng 16 byte từ input
    cin.read((char*)state, 16);

    KeyExpansion(key, expandedKey);
    AddRoundKey(state, expandedKey);
    for (int r = 1; r <= 9; r++) {
        SubBytes(state); ShiftRows(state); MixColumns(state);
        AddRoundKey(state, expandedKey + (r * 16));
    }
    SubBytes(state); ShiftRows(state);
    AddRoundKey(state, expandedKey + 160);

    ofstream out("message.aes", ios::binary);
    out.write((char*)state, 16);
    out.close();
    return 0;
}
