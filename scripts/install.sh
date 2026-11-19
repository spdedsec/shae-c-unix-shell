#!/usr/bin/env bash
set -euo pipefail
echo "Installing shae-c-unix-shell (C language tool)"
echo "Build: gcc -O2 -std=c11 -o shae-shell src/shell.c -lreadline"
echo "Run: ./shae-shell"
