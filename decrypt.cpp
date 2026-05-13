#include <iostream>
#include <fstream>
#include <iomanip>
#include "structures.h"

using namespace std;

int main() {
    unsigned char key[16];
    unsigned char ciphertext[16];
    unsigned char state[4][4];

    // 1. Đọc khóa 128-bit từ file keyfile
    ifstream kfile("keyfile");
    if (kfile.is_open()) {
        for (int i = 0; i < 16; i++) {
            int temp;
            kfile >> hex >> temp;
            key[i] = (unsigned char)temp;
        }
        kfile.close();
    }

    // 2. Đọc ciphertext từ file message.aes
    ifstream mfile("message.aes", ios::binary);
    if (mfile.is_open()) {
        mfile.read((char*)ciphertext, 16);
        mfile.close();
    }

    // 3. Đưa dữ liệu vào ma trận State (Column-major order)
    for (int i = 0; i < 16; i++) {
        state[i % 4][i / 4] = ciphertext[i];
    }

    // 4. Thực hiện giải mã 
    // Đảm bảo trong structures.h bạn đã định nghĩa hàm này
    AES_decrypt(state, key);

    // 5. Xuất kết quả theo định dạng chuẩn của Lab 5
    cout << "=============================" << endl;
    cout << "Công cụ giải mã AES 128-bit " << endl;
    cout << "=============================" << endl;
    cout << "Đọc tin nhắn được mã hóa từ message.aes" << endl;
    cout << "Đọc khóa 128 bit từ tệp khóa." << endl;
    
    // Lưu ý: Cần in thông tin hex nếu script test yêu cầu (tùy chọn)
    
    cout << "Tin nhắn đã được giải mã: " << endl;
    cout << "\t"; // Tab này rất quan trọng để khớp với script diff
    for (int i = 0; i < 16; i++) {
        unsigned char c = state[i % 4][i / 4];
        if (c != 0) { // Loại bỏ Zero Padding
            cout << (char)c;
        }
    }
    cout << endl;

    return 0;
}
