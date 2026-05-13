#!/usr/bin/env bash
set -euo pipefail

echo "===================================="
echo " AES Tamper Negative Test "
echo "===================================="

# Build project
echo "[INFO] Building project..."
make all >/dev/null

# Create AES key
echo "[INFO] Writing AES key..."
cat > keyfile <<'KEY'
01 04 02 03 01 03 04 0A 09 0B 07 0F 0F 06 03 00
KEY

# Plaintext
PLAINTEXT="tamper negative test"

echo "[INFO] Encrypting plaintext..."
printf "%s\n" "$PLAINTEXT" | ./encrypt >/tmp/aes_encrypt_tamper.log

# Ensure ciphertext exists
if [[ ! -f message.aes ]]; then
    echo "[FAIL] message.aes was not created."
    exit 1
fi

echo "[INFO] Tampering ciphertext (flip 1 byte)..."

python3 - <<'PY'
from pathlib import Path

p = Path('message.aes')
data = bytearray(p.read_bytes())

if not data:
    raise SystemExit('message.aes is empty')

# Flip first byte
data[0] ^= 0x01

p.write_bytes(data)
PY

echo "[INFO] Attempting decrypt after tampering..."

OUTPUT=$(./decrypt 2>&1 | tr -d '\000' || true)

# Original plaintext should NOT appear
if grep -q "$PLAINTEXT" <<< "$OUTPUT"; then
    echo "----------- decrypt output -----------"
    echo "$OUTPUT"
    echo "--------------------------------------"
    echo "[FAIL] Tampered ciphertext should not recover original plaintext."
    exit 1
fi

echo "[PASS] Tamper / flip 1 byte negative test changes decrypted output successfully."
exit 0
