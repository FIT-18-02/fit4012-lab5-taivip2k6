# FIT4012 - Lab 5: AES-128 Starter Repository

## 1. Giới thiệu

Bài lab này mô phỏng thuật toán AES-128 bằng ngôn ngữ C++.

Project hỗ trợ:

- mã hóa plaintext
- giải mã ciphertext
- đọc khóa AES-128 từ file
- xử lý block 128-bit
- zero padding
- test tự động bằng shell script

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
## 3. Input / Đầu vào

Chương trình nhận plaintext từ bàn phím bằng `cin.getline(...)`.

File `encrypt.cpp` nhận dữ liệu người dùng nhập và thực hiện mã hóa AES-128.

File `decrypt.cpp` đọc ciphertext từ file `message.aes` để giải mã.

Cả hai chương trình sử dụng khóa AES-128 đọc từ file `keyfile`.

Ví dụ nội dung `keyfile`:

```text
01 04 02 03 01 03 04 0A 09 0B 07 0F 0F 06 03 00
