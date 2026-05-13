#include <iostream>
#include <fstream>
#include <cstring>
#include "structures.h"

using namespace std;

// Hàm định nghĩa AES_decrypt để trình biên dịch tìm thấy
void AES_decrypt(unsigned char* state, unsigned char* key) {
    // Lưu ý: Đây là nơi bạn viết logic giải mã đảo ngược của AES
    // (InvSubBytes, InvShiftRows, InvMixColumns...)
}

int main() {
    unsigned char state[16] = {0}, key[16] = {0};
    
    // Đọc file đã mã hóa
    ifstream in("message.aes", ios::binary);
    in.read((char*)state, 16);
    in.close();

    // Thực hiện giải mã
    AES_decrypt(state, key);

    cout << "Decryption attempted (Logic implementation needed inside AES_decrypt)." << endl;
    return 0;
}
