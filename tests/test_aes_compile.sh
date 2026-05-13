#!/usr/bin/env bash
set -euo pipefail

echo "===================================="
echo " AES Compile Test "
echo "===================================="

# Remove old executables if exist
rm -f encrypt decrypt

echo "[INFO] Compiling encrypt.cpp ..."
g++ -std=c++17 -Wall -Wextra -pedantic encrypt.cpp -o encrypt

echo "[INFO] Compiling decrypt.cpp ..."
g++ -std=c++17 -Wall -Wextra -pedantic decrypt.cpp -o decrypt

# Check executables
[[ -x ./encrypt ]] || {
    echo "[FAIL] Missing encrypt executable"
    exit 1
}

[[ -x ./decrypt ]] || {
    echo "[FAIL] Missing decrypt executable"
    exit 1
}

echo "[PASS] AES encrypt/decrypt programs compile successfully."
exit 0
