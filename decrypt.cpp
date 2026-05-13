#include <iostream>
#include <fstream>
#include <iomanip>
#include "structures.h"

using namespace std;

int main() {
    unsigned char key[16];
    unsigned char ciphertext[16];
    unsigned char state[4][4];

    // 1. Đọc khóa từ keyfile
    ifstream kfile("keyfile");
    if (kfile.is_open()) {
        for (int i = 0; i < 16; i++) {
            int temp;
            kfile >> hex >> temp;
            key[i] = (unsigned char)temp;
        }
        kfile.close();
    }

    // 2. Đọc ciphertext từ message.aes
    ifstream mfile("message.aes", ios::binary);
    if (mfile.is_open()) {
        mfile.read((char*)ciphertext, 16);
        mfile.close();
    }

    // 3. Đưa dữ liệu vào ma trận State (Theo cột - Column-major)
    for (int i = 0; i < 16; i++) {
        state[i % 4][i / 4] = ciphertext[i];
    }

    // 4. GỌI HÀM GIẢI MÃ THỰC SỰ
    // Hàm này phải nằm trong file structures.h của bạn
    AES_decrypt(state, key);

    // 5. In kết quả theo đúng định dạng script yêu cầu
    cout << "Tin nhắn đã được giải mã: " << endl;
    cout << "\t"; 
    for (int i = 0; i < 16; i++) {
        unsigned char c = state[i % 4][i / 4];
        if (c != 0) { // Loại bỏ Zero Padding
            cout << (char)c;
        }
    }
    cout << endl;

    return 0;
}
