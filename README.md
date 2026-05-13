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
Kết quả của chương trình bao gồm:

message.aes: Tệp tin lưu trữ bản mã (ciphertext) sau khi mã hóa.

Console Log: Hiển thị quá trình chia khối (blocking), quá trình thêm đệm (padding) và kết quả mã hóa/giải mã cuối cùng.

Test Results: Trạng thái PASS hoặc FAIL khi chạy các kịch bản kiểm thử tự động trong thư mục tests/.

5. Ethics & Safe use / An toàn sử dụng
Mục đích giáo dục: Mã nguồn này được thiết kế thuần túy cho mục đích học tập và tìm hiểu nguyên lý hoạt động của thuật toán AES-128.

Không dùng cho dữ liệu nhạy cảm: Tuyệt đối không sử dụng code này để bảo vệ dữ liệu thực tế hoặc triển khai trên các hệ thống sản xuất (production) vì đây chỉ là bản mô phỏng, chưa tối ưu chống lại các cuộc tấn công kênh kề (side-channel attacks).

Tuân thủ pháp luật: Việc sử dụng các công cụ mật mã phải tuân thủ quy định của pháp luật địa phương về an toàn thông tin.
