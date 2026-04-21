#!/bin/bash

# Compile
g++ -o ej1 ejercicio1.cpp -std=c++11

if [ $? -ne 0 ]; then
    echo "Compilation failed"
    exit 1
fi

# Test directory
TEST_DIR="tests/ejercicio1"

# Counters
PASSED=0
FAILED=0

# Run all tests
for input in $TEST_DIR/*.in.txt; do
    # Get test name (e.g., "10" from "10.in.txt")
    name=$(basename "$input" .in.txt)
    expected="$TEST_DIR/$name.out.txt"
    
    # Run test
    ./ej1 < "$input" > temp.out.txt
    
    # Compare
    if diff -q temp.out.txt "$expected" > /dev/null; then
        echo "✓ $name PASSED"
        ((PASSED++))
    else
        echo "✗ $name FAILED"
        ((FAILED++))
    fi
done

# Cleanup
rm -f temp.out.txt ej1

# Summary
echo ""
echo "=========================================="
echo "Passed: $PASSED"
echo "Failed: $FAILED"
echo "=========================================="