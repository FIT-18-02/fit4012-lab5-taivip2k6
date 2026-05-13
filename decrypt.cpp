// Đảm bảo plaintext được thu hồi đúng cách
unsigned char decrypted_output[16]; 
// ... gọi hàm giải mã ...

cout << "Tin nhắn đã được giải mã: " << endl;
for(int i = 0; i < 16; i++) {
    if(decrypted_output[i] != 0) { // Loại bỏ zero padding khi in
        cout << (char)decrypted_output[i];
    }
}
cout << endl;
