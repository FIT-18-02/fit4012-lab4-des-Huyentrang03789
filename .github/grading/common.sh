#!/usr/bin/env bash
set -euo pipefail

extract_last_binary() {
  local text="$1"
  printf '%s\n' "$text" | grep -oE '[01]{64,}' | tail -n 1
}

fail() {
  echo "[FAIL] $1" >&2
  exit 1
}

pass() {
  echo "[PASS] $1"
}
