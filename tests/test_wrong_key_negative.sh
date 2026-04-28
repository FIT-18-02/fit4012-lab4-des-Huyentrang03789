#!/usr/bin/env bash
# TODO_STUDENT: Hoàn thiện negative test cho wrong key / incorrect key / sai key.
# Gợi ý: giải mã với khóa sai và chứng minh không khôi phục đúng plaintext.
set -euo pipefail
g++ -std=c++17 des.cpp -o des

PLAINTEXT="1010101010101010101010101010101010101010101010101010101010101010"
KEY1="1111000011110000111100001111000011110000111100001111000011110000"
KEY2="0000111100001111000011110000111100001111000011110000111100001111"

CIPHER=$(printf "1\n$PLAINTEXT\n$KEY1\n" | ./des | tail -n 1)
RECOVER=$(printf "2\n$CIPHER\n$KEY2\n" | ./des | tail -n 1)

[[ "$RECOVER" != "$PLAINTEXT" ]] && echo "[PASS]" || (echo "[FAIL]";  exit 1)
