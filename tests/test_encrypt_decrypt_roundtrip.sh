#!/usr/bin/env bash

# Gợi ý: sau khi em viết thêm giải mã, cần kiểm tra decrypt(encrypt(plaintext)) = plaintext.
set -euo pipefail

g++ -std=c++17 des.cpp -o des

PLAINTEXT="1010101010101010101010101010101010101010101010101010101010101010"
KEY="1111000011110000111100001111000011110000111100001111000011110000"

CIPHER=$(printf "1\n$PLAINTEXT\n$KEY\n" | ./des | tail -n 1)
RECOVER=$(printf "2\n$CIPHER\n$KEY\n" | ./des | tail -n 1)

[[ "$RECOVER" == "$PLAINTEXT" ]] && echo "[PASS]" || (echo "[FAIL]"; exit 1)
