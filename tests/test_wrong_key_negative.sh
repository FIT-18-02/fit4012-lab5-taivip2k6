#!/usr/bin/env bash
set -euo pipefail

echo "========================================"
echo " AES-128 Wrong Key Negative Test"
echo "========================================"

# Build project
make all >/dev/null

# Correct AES key
cat > keyfile <<'KEY'
01 04 02 03 01 03 04 0A 09 0B 07 0F 0F 06 03 00
KEY

PLAINTEXT="wrong key negative test"

echo "[INFO] Encrypting plaintext..."
printf "%s\n" "$PLAINTEXT" | ./encrypt >/tmp/aes_encrypt_wrong_key.log

# Backup original key
cp keyfile keyfile.original

echo "[INFO] Replacing with wrong AES key..."

# Wrong key
cat > keyfile <<'KEY'
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
KEY

echo "[INFO] Attempting decryption using wrong key..."

OUTPUT=$(./decrypt 2>&1 | tr -d '\000' || true)

# Restore original key
mv keyfile.original keyfile

# Check if plaintext is incorrectly recovered
if grep -q "$PLAINTEXT" <<< "$OUTPUT"; then
    echo "----------------------------------------"
    echo "$OUTPUT"
    echo "----------------------------------------"
    echo "[FAIL] Wrong key should NOT recover original plaintext."
    exit 1
fi

echo "[PASS] Wrong key negative test changes decrypted output successfully."
echo "[INFO] AES decryption failed as expected when using incorrect key."
echo "========================================"
