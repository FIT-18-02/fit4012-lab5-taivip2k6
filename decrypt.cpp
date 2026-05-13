#include <iostream>
#include <fstream>
#include "structures.h"

using namespace std;

int main() {
    unsigned char key[16], ciphertext[16], state[4][4];

    ifstream kfile("keyfile");
    for (int i = 0; i < 16; i++) { int t; kfile >> hex >> t; key[i] = (unsigned char)t; }
    kfile.close();

    ifstream mfile("message.aes", ios::binary);
    mfile.read((char*)ciphertext, 16);
    mfile.close();

    for (int i = 0; i < 16; i++) state[i % 4][i / 4] = ciphertext[i];

    AES_decrypt(state, key);

    cout << "=============================" << endl;
    cout << "Công cụ giải mã AES 128-bit " << endl;
    cout << "=============================" << endl;
    cout << "Đọc tin nhắn được mã hóa từ message.aes" << endl;
    cout << "Đọc khóa 128 bit từ tệp khóa." << endl;
    cout << "Tin nhắn đã được giải mã: " << endl;
    cout << "\t"; // Bắt buộc phải có tab này
    for (int i = 0; i < 16; i++) {
        unsigned char c = state[i % 4][i / 4];
        if (c != 0) cout << (char)c;
    }
    cout << endl;
    return 0;
}
