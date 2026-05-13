# Report 1 Page - Lab 5 AES-128

## Mục tiêu

Bài thực hành giúp sinh viên hiểu cơ chế hoạt động cơ bản của AES-128, bao gồm mã hóa và giải mã dữ liệu theo block 128-bit, mở rộng khóa (Key Expansion), các vòng xử lý AES và cơ chế padding dữ liệu.

## Cách làm / Method

Chương trình được xây dựng bằng ngôn ngữ C++ với 3 file chính:

- `encrypt.cpp`: thực hiện mã hóa plaintext thành ciphertext.
- `decrypt.cpp`: thực hiện giải mã ciphertext.
- `structures.h`: chứa S-box, inverse S-box, bảng MixColumns, InverseMixColumns và hàm KeyExpansion.

Chương trình đọc khóa AES-128 từ file `keyfile` dưới dạng hex 16 byte. Plaintext được nhập từ bàn phím, sau đó mã hóa và lưu vào file `message.aes`.

Repo được tổ chức theo cấu trúc chuẩn của FIT4012 gồm:

- `tests/` để kiểm thử
- `logs/` để lưu minh chứng
- `scripts/` để chạy mẫu
- `Makefile` và `CMakeLists.txt` để build chương trình
- GitHub Actions CI để kiểm tra tự động

## Kết quả / Result

Chương trình có thể:

- Biên dịch thành công bằng `make` hoặc `cmake`
- Mã hóa plaintext thành ciphertext
- Ghi ciphertext vào `message.aes`
- Giải mã và khôi phục plaintext ban đầu

Ví dụ plaintext:

```text
hello FIT4012 AES
