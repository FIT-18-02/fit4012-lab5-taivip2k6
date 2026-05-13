#include <iostream>
#include <fstream>
#include <iomanip>
#include "structures.h"

using namespace std;

int main() {
    unsigned char key[16];
    unsigned char ciphertext[16];
    unsigned char state[4][4];

    // Đọc khóa
    ifstream kfile("keyfile");
    if (kfile.is_open()) {
        for (int i = 0; i < 16; i++) {
            int temp;
            kfile >> hex >> temp;
            key[i] = (unsigned char)temp;
        }
        kfile.close();
    }

    // Đọc bản mã
    ifstream mfile("message.aes", ios::binary);
    if (mfile.is_open()) {
        mfile.read((char*)ciphertext, 16);
        mfile.close();
    }

    // Chuyển vào state
    for (int i = 0; i < 16; i++) {
        state[i % 4][i / 4] = ciphertext[i];
    }

    // Gọi hàm giải mã (Hàm này đã được thêm vào structures.h ở Bước 1)
    AES_decrypt(state, key);

    // In kết quả theo đúng format bài Lab yêu cầu
    cout << "=============================" << endl;
    cout << "Công cụ giải mã AES 128-bit " << endl;
    cout << "=============================" << endl;
    cout << "Đọc tin nhắn được mã hóa từ message.aes" << endl;
    cout << "Đọc khóa 128 bit từ tệp khóa." << endl;
    cout << "Tin nhắn đã được giải mã: " << endl;
    cout << "\t"; 
    for (int i = 0; i < 16; i++) {
        unsigned char c = state[i % 4][i / 4];
        if (c != 0) cout << (char)c;
    }
    cout << endl;

    return 0;
}
