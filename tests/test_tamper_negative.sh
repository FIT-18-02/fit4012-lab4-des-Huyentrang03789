#!/usr/bin/env bash
# Test: sửa 1 byte hoặc một số bit của ciphertext rồi quan sát kết quả giải mã / kiểm thử.
set -euo pipefail

g++ -std=c++17 des.cpp -o des

PLAINTEXT="1010101010101010101010101010101010101010101010101010101010101010"
KEY="1111000011110000111100001111000011110000111100001111000011110000"
CIPHER=$(printf "1\n$PLAINTEXT\n$KEY\n" | ./des | tail -n 1)
# flip 1 bit
TAMPERED="${CIPHER/0/1}"
RECOVER=$(printf "2\n$TAMPERED\n$KEY\n" | ./des | tail -n 1)
[[ "$RECOVER" != "$PLAINTEXT" ]] && echo "[PASS]" || (echo "[FAIL]"; exit 1)
