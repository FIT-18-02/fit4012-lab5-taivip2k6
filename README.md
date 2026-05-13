[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/0pZSTN4X)

# FIT4012 - Lab 5: AES-128 Starter Repository

## 1. Cấu trúc repo

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
│   ├── sample-run.log
│   └── test-output.log
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
