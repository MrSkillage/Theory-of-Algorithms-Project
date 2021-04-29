#!/bin/bash

# Test 1 for sha512sum expected result of the SHA-512 hash value of input.txt for PASS
echo "Checking [SHA-512] Hash Value of [input.txt] with [sha512sum] expected result to [PASS]."
expec="$(sha512sum input.txt | cut -d " " -f 1)"
myout="$(./main -f input.txt | sed "1 d")"
echo "Expected: " $expec
echo "Output:   " $myout
if [[ $myout == $expec ]]; then
    echo "[-----PASS-----]"
    echo ""
else
    echo "[-----FAIL-----]"
    echo ""
fi

# Test 2 for sha512sum expected result of the SHA-512 hash value of input.txt for FAIL
echo "Checking [SHA-512] Hash Value of [input.txt] with [sha512sum] expected result to [FAIL]."
expec="FAILED-HASH-VALUE"
myout="$(./main -f input.txt | sed "1 d")"
echo "Expected: " $expec
echo "Output:   " $myout
if [[ $myout == $expec ]]; then
    echo "[-----PASS-----]"
    echo ""
else
    echo "[-----FAIL-----]"
    echo ""
fi

# Test 3 for sha256sum expected result of the SHA-256 hash value of input.txt for PASS
echo "Checking [SHA-256] Hash Value of [input.txt] with [sha256sum] expected result to [PASS]."
expec="$(sha256sum input.txt | cut -d " " -f 1)"
myout="$(./main -a 256 -f input.txt | sed "1 d")"
echo "Expected: " $expec
echo "Output:   " $myout
if [[ $myout == $expec ]]; then
    echo "[-----PASS-----]"
    echo ""
else
    echo "[-----FAIL-----]"
    echo ""
fi

# Test 4 for sha256sum expected result of the SHA-512 hash value of input.txt for FAIL
echo "Checking [SHA-256] Hash Value of [input.txt] with [sha256sum] expected result to [FAIL]."
expec="FAILED-HASH-VALUE"
myout="$(./main -a 256 -f input.txt | sed "1 d")"
echo "Expected: " $expec
echo "Output:   " $myout
if [[ $myout == $expec ]]; then
    echo "[-----PASS-----]"
    echo ""
else
    echo "[-----FAIL-----]"
    echo ""
fi