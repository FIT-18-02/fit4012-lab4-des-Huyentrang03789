#!/usr/bin/env bash
set -euo pipefail
source .github/grading/common.sh

LONG_PLAINTEXT="00010010001101000101011001111000100110101011110011011110111100011010101010101010"
KEY="0001001100110100010101110111100110011011101111001101111111110001"
EXPECTED="01111110101111110100010010010011001000111111101011111010111110000100000010010001101001000010011111010110110001100000111000110100"

if [[ ! -x ./des ]]; then
  g++ -std=c++17 -Wall -Wextra -pedantic des.cpp -o des
fi

OUTPUT=$(timeout 10s bash -lc 'printf "1\n%s\n%s\n" "$0" "$1" | ./des' "$LONG_PLAINTEXT" "$KEY" 2>&1 || true)
ACTUAL=$(extract_last_binary "$OUTPUT")

if [[ -z "$ACTUAL" ]]; then
  fail "Không đọc được kết quả nhị phân từ output. Q2 cần hỗ trợ nhập từ bàn phím theo contract mode=1, rồi in ra ciphertext cuối cùng."
fi

if [[ "$ACTUAL" != "$EXPECTED" ]]; then
  echo "--- Output chương trình ---"
  printf '%s\n' "$OUTPUT"
  echo "---------------------------"
  fail "Q2 chưa đạt. Auto-check yêu cầu mode 1 nhận plaintext >64 bit + key từ stdin và mã hóa multi-block với zero padding đúng."
fi

pass "Q2 đạt: có nhập từ bàn phím và xử lý multi-block + zero padding đúng theo vector kiểm thử."
