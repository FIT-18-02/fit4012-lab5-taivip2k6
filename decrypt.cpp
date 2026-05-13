#include <iostream>
#include "structures.h"
using namespace std;

int main() {
    // ... các đoạn code đọc file keyfile và message.aes đã có sẵn ...

    // GIẢ SỬ: decrypted_output là mảng chứa kết quả sau khi gọi hàm giải mã
    // Bạn cần thay tên biến cho đúng với code hiện tại của bạn
    
    cout << "Tin nhắn đã được giải mã: " << endl;
    for(int i = 0; i < 16; i++) {
        // Chỉ in các ký tự không phải là null (xử lý zero padding)
        if(decrypted_output[i] != 0) { 
            cout << (char)decrypted_output[i];
        }
    }
    cout << endl;

    return 0;
}
