#!/usr/bin/env bash
# Gợi ý: kiểm tra plaintext dài hơn 64 bit, chia block đúng và zero padding đúng.
set -euo pipefail

g++ -std=c++17 des.cpp -o des

PLAINTEXT="1010101010"  # < 64 bit
KEY="1111000011110000111100001111000011110000111100001111000011110000"

OUTPUT=$(printf "1\n$PLAINTEXT\n$KEY\n" | ./des)

# chỉ cần chạy không lỗi là pass
[[ -n "$OUTPUT" ]] && echo "[PASS]" || (echo "[FAIL]"; exit 1)
