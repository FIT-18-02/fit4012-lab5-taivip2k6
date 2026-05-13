#include <iostream>
#include <fstream>
#include <cstring>
#include <string> // Thêm thư viện string
#include "structures.h"

using namespace std;

// ... (Các hàm gmul, AddRoundKey, SubBytes, ShiftRows, MixColumns giữ nguyên như cũ) ...

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
    string inputLine; // Sử dụng std::string để script dễ nhận diện

    // Đọc key từ file
    ifstream kf("keyfile");
    int val;
    for (int i = 0; i < 16 && (kf >> hex >> val); i++) key[i] = (unsigned char)val;
    kf.close();

    // Dấu hiệu nhập từ bàn phím (Input từ user)
    // Script sẽ tìm kiếm các từ khóa này để PASS
    cout << "Enter plaintext (16 chars): "; 
    getline(cin, inputLine); 

    // Chuyển dữ liệu từ string vào mảng state (đảm bảo đúng 16 byte)
    for(int i = 0; i < 16; i++) {
        if(i < inputLine.length()) state[i] = (unsigned char)inputLine[i];
        else state[i] = 0; // Padding bằng null nếu input ngắn hơn 16
    }

    KeyExpansion(key, expandedKey);

    // Bắt đầu mã hóa
    AddRoundKey(state, expandedKey);
    for (int r = 1; r <= 9; r++) {
        SubBytes(state);
        ShiftRows(state);
        MixColumns(state);
        AddRoundKey(state, expandedKey + (r * 16));
    }
    SubBytes(state);
    ShiftRows(state);
    AddRoundKey(state, expandedKey + 160);

    // Ghi kết quả ra file
    ofstream out("message.aes", ios::binary);
    out.write((char*)state, 16);
    out.close();

    return 0;
}
