# FIT4012 - Lab 5: AES-128 Starter Repository

## 1. Giới thiệu

Bài lab này mô phỏng thuật toán AES-128 bằng ngôn ngữ C++.

Project hỗ trợ:
- Mã hóa plaintext
- Giải mã ciphertext
- Đọc khóa AES-128 từ file
- Xử lý block 128-bit
- Zero padding
- Test tự động bằng shell script

Repo được tổ chức theo chuẩn starter repository của FIT4012.

---

## 2. Cấu trúc repo
```text
.
├── .github/
│   ├── scripts/
│   │   └── check_submission.sh
│   └── workflows/
│       └── ci.yml
├── docs/
│   └── aes-code-notes.md
├── logs/
│   ├── .gitkeep
│   ├── README.md
│   └── sample-run.log
├── scripts/
│   └── run_sample.sh
├── tests/
│   ├── test_aes_compile.sh
│   ├── test_encrypt_decrypt_roundtrip.sh
│   ├── test_multiblock_padding.sh
│   ├── test_tamper_negative.sh
│   └── test_wrong_key_negative.sh
├── .gitignore
├── CMakeLists.txt
├── Makefile
├── README.md
├── decrypt.cpp
├── encrypt.cpp
├── keyfile
├── report-1page.md
└── structures.h
3. Input / Đầu vào
Chương trình nhận plaintext từ bàn phím bằng cin.getline(...).

File encrypt.cpp nhận dữ liệu người dùng nhập và thực hiện mã hóa AES-128.
File decrypt.cpp đọc ciphertext từ file message.aes để giải mã.
Cả hai chương trình sử dụng khóa AES-128 đọc từ file keyfile.

Ví dụ nội dung keyfile:
01 04 02 03 01 03 04 0A 09 0B 07 0F 0F 06 03 00

4. Output / Đầu ra
Kết quả của chương trình bao gồm các thành phần sau:

4.1. Tệp tin đầu ra
message.aes: Tệp tin nhị phân chứa nội dung đã được mã hóa (ciphertext). Tệp này được tạo ra sau khi thực hiện lệnh mã hóa.

logs/sample-run.log: Lưu trữ nhật ký quá trình chạy chương trình, bao gồm các bước chuyển đổi trạng thái của ma trận AES.

4.2. Hiển thị trên màn hình (Console)
Tiến trình mã hóa: Hiển thị chuỗi plaintext đầu vào, các khối dữ liệu sau khi thực hiện Zero Padding, và cuối cùng là chuỗi Ciphertext dưới dạng Hexadecimal.

Tiến trình giải mã: Hiển thị nội dung đọc được từ file mã hóa và kết quả Plaintext sau khi giải mã thành công.

4.3. Kết quả kiểm thử (Automated Tests)
Khi thực hiện lệnh make test hoặc chạy các script trong thư mục tests/, chương trình sẽ xuất ra kết quả:

PASS: Nếu các bước mã hóa/giải mã khớp nhau và xử lý đúng các trường hợp biên.

FAIL: Nếu có lỗi logic hoặc cấu trúc file không đúng yêu cầu.
