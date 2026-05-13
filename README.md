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
