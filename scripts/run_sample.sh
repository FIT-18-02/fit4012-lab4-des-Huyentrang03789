#!/usr/bin/env bash
set -euo pipefail

g++ -std=c++17 -Wall -Wextra -pedantic des.cpp -o des
./des
