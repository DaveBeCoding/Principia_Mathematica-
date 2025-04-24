#!/bin/bash

# Create base directory
mkdir -p c-memory-modeling-suite/{src,tests,docs}

# Create files in src/
touch c-memory-modeling-suite/src/memory_ops.c
touch c-memory-modeling-suite/src/triple_integral.c
touch c-memory-modeling-suite/src/utils.h

# Create files in tests/
touch c-memory-modeling-suite/tests/memory_ops_test.c
touch c-memory-modeling-suite/tests/triple_integral_test.c

# Create docs/
touch c-memory-modeling-suite/docs/memory_theory.md

# Create README and Makefile
touch c-memory-modeling-suite/README.md
touch c-memory-modeling-suite/Makefile

echo "✅ Project structure created at ./c-memory-modeling-suite"
