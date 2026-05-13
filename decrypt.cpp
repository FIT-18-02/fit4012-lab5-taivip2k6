#include <iostream>
#include <fstream>
#include "structures.h"

using namespace std;

int main() {
    // Khai báo các mảng cần thiết
    unsigned char key[16];
    unsigned char ciphertext[16];
    unsigned char decrypted_output[16]; // KHAI BÁO BIẾN Ở ĐÂY

    // Đọc khóa từ tệp 'keyfile'
    ifstream kfile("keyfile");
    if (kfile.is_open()) {
        for (int i = 0; i < 16; i++) {
            int temp;
            kfile >> hex >> temp;
            key[i] = (unsigned char)temp;
        }
        kfile.close();
    }

    // Đọc dữ liệu đã mã hóa từ 'message.aes'
    ifstream mfile("message.aes", ios::binary);
    if (mfile.is_open()) {
        mfile.read((char*)ciphertext, 16);
        mfile.close();
    }

    // TODO: Gọi hàm giải mã của bạn tại đây
    // Ví dụ: AES_decrypt(ciphertext, key, decrypted_output);
    
    // Tạm thời gán để tránh lỗi logic khi test nếu bạn chưa xong hàm giải mã
    for(int i = 0; i < 16; i++) decrypted_output[i] = ciphertext[i];

    // Phần in kết quả đã sửa lỗi
    cout << "Tin nhắn đã được giải mã: " << endl;
    for(int i = 0; i < 16; i++) {
        if(decrypted_output[i] != 0) { 
            cout << (char)decrypted_output[i];
        }
    }
    cout << endl;

    return 0;
}
