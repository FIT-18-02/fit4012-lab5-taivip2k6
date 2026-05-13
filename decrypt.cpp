#include <iostream>
#include <fstream>
#include <cstring>
#include "structures.h"

using namespace std;

// ... (Giữ nguyên các hàm gmul, AddRoundKey, InvSubBytes, InvShiftRows, InvMixColumns, KeyExpansion) ...
// Chú ý: Đảm bảo hàm InvMixColumns dùng đúng các hệ số 0x0e, 0x0b, 0x0d, 0x09

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

    // CHỈ IN ĐÚNG 16 BYTE, KHÔNG DÙNG cout << state
    cout.write((char*)state, 16); 
    return 0;
}
