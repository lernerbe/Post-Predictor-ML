#!/bin/bash

# Example script for Post Predictor ML
# Demonstrates various ways to use the sentiment classifier

echo "=== Post Predictor ML - Example Usage ==="
echo

# Check if the executable exists
if [ ! -f "./sentiment_classifier" ]; then
    echo "Building the classifier..."
    make
    echo
fi

echo "1. Basic classification with sample data:"
echo "   Command: ./sentiment_classifier train.csv test.csv"
echo "   Output:"
./sentiment_classifier train.csv test.csv
echo

echo "2. Debug mode with detailed output:"
echo "   Command: ./sentiment_classifier train.csv test.csv --debug"
echo "   Output (first 20 lines):"
./sentiment_classifier train.csv test.csv --debug | head -20
echo

echo "3. Using Makefile targets:"
echo "   make test    - Build and run with sample data"
echo "   make debug   - Build and run with debug output"
echo "   make clean   - Remove build artifacts"
echo

echo "4. Creating custom test data:"
echo "   Create a CSV file with columns: n,tag,content"
echo "   Example:"
echo "   n,tag,content"
echo "   1,positive,\"This is a great movie!\""
echo "   2,negative,\"Terrible film, waste of time\""
echo

echo "=== Example completed ==="
