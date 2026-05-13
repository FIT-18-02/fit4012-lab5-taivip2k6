#!/usr/bin/env bash
set -euo pipefail

echo "===================================="
echo " AES Multi-block Padding Test "
echo "===================================="

# Build project
echo "[INFO] Building project..."
make all >/dev/null

# Create AES key
echo "[INFO] Writing AES key..."
cat > keyfile <<'KEY'
01 04 02 03 01 03 04 0A 09 0B 07 0F 0F 06 03 00
KEY

# Plaintext longer than 16 bytes (multi-block)
PLAINTEXT="AES message longer than one block"

echo "[INFO] Encrypting multi-block plaintext..."
printf "%s\n" "$PLAINTEXT" | ./encrypt >/tmp/aes_encrypt_multiblock.log

# Verify ciphertext file exists
if [[ ! -f message.aes ]]; then
    echo "[FAIL] message.aes was not created."
    exit 1
fi

echo "[INFO] Decrypting ciphertext..."
OUTPUT=$(./decrypt 2>&1 | tr -d '\000')

# Check recovered plaintext
if ! grep -q "$PLAINTEXT" <<< "$OUTPUT"; then
    echo "----------- decrypt output -----------"
    echo "$OUTPUT"
    echo "--------------------------------------"
    echo "[FAIL] Multi-block plaintext was not recovered."
    exit 1
fi

echo "[PASS] Multi-block plaintext with zero padding is recovered successfully."
exit 0
