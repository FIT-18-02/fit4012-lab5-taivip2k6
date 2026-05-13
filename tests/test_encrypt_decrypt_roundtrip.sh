#!/usr/bin/env bash
set -euo pipefail

echo "===================================="
echo " AES Roundtrip Encrypt/Decrypt Test "
echo "===================================="

# Build project
echo "[INFO] Building project..."
make all >/dev/null

# Create AES key
echo "[INFO] Writing AES key to keyfile..."
cat > keyfile <<'KEY'
01 04 02 03 01 03 04 0A 09 0B 07 0F 0F 06 03 00
KEY

# Plaintext test message
PLAINTEXT="hello FIT4012 AES"

echo "[INFO] Encrypting plaintext..."
printf "%s\n" "$PLAINTEXT" | ./encrypt >/tmp/aes_encrypt_roundtrip.log

# Ensure ciphertext file exists
if [[ ! -f message.aes ]]; then
    echo "[FAIL] message.aes was not created."
    exit 1
fi

echo "[INFO] Decrypting ciphertext..."
OUTPUT=$(./decrypt 2>&1 | tr -d '\000')

# Verify plaintext recovered
if ! grep -q "$PLAINTEXT" <<< "$OUTPUT"; then
    echo "----------- decrypt output -----------"
    echo "$OUTPUT"
    echo "--------------------------------------"
    echo "[FAIL] Round-trip encrypt/decrypt did not recover plaintext."
    exit 1
fi

echo "[PASS] Round-trip encrypt/decrypt recovers plaintext successfully."
exit 0
