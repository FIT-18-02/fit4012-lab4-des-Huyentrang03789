#!/usr/bin/env bash
set -euo pipefail
source .github/grading/common.sh

PLAINTEXT="0001001000110100010101100111100010011010101111001101111011110001"
K1="0001001100110100010101110111100110011011101111001101111111110001"
K2="1111000011001100101010101111010101010110011001111000111100001111"
K3="0000111100001111000011110000111100001111000011110000111100001111"
EXPECTED_CIPHER="0000100111010100110001011011100101000001100001100000010111111010"

if [[ ! -x ./des ]]; then
  g++ -std=c++17 -Wall -Wextra -pedantic des.cpp -o des
fi

ENC_OUTPUT=$(timeout 10s bash -lc 'printf "3\n%s\n%s\n%s\n%s\n" "$0" "$1" "$2" "$3" | ./des' "$PLAINTEXT" "$K1" "$K2" "$K3" 2>&1 || true)
ENC_ACTUAL=$(extract_last_binary "$ENC_OUTPUT")

if [[ -z "$ENC_ACTUAL" ]]; then
  fail "Không đọc được output cho TripleDES encrypt. Q4 cần hỗ trợ mode=3 và in ra ciphertext cuối cùng."
fi

if [[ "$ENC_ACTUAL" != "$EXPECTED_CIPHER" ]]; then
  echo "--- Output TripleDES encrypt ---"
  printf '%s\n' "$ENC_OUTPUT"
  echo "--------------------------------"
  fail "Q4 chưa đạt ở TripleDES encrypt (EDE)."
fi

DEC_OUTPUT=$(timeout 10s bash -lc 'printf "4\n%s\n%s\n%s\n%s\n" "$0" "$1" "$2" "$3" | ./des' "$EXPECTED_CIPHER" "$K1" "$K2" "$K3" 2>&1 || true)
DEC_ACTUAL=$(extract_last_binary "$DEC_OUTPUT")

if [[ -z "$DEC_ACTUAL" ]]; then
  fail "Không đọc được output cho TripleDES decrypt. Q4 cần hỗ trợ mode=4 và in ra plaintext cuối cùng."
fi

if [[ "$DEC_ACTUAL" != "$PLAINTEXT" ]]; then
  echo "--- Output TripleDES decrypt ---"
  printf '%s\n' "$DEC_OUTPUT"
  echo "--------------------------------"
  fail "Q4 chưa đạt ở TripleDES decrypt."
fi

pass "Q4 đạt: TripleDES encrypt/decrypt đúng theo vector kiểm thử."
