#!/bin/bash

set -e

echo "🚀 Compiling and testing C Memory Modeling Suite..."

if ! command -v gcc &> /dev/null; then
  echo "❌ gcc is not installed. Please install GCC before running this script."
  exit 1
fi

make test

echo "✅ All tests completed successfully."
