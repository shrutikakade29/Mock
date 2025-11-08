#!/bin/bash
# This script calculates simple interest.

# Usage: ./simple-interest.sh <principal> <rate> <time>

p=$1
r=$2
t=$3

s=$(echo "scale=2; $p * $r * $t / 100" | bc)

echo "The simple interest is: $s"
