#!/bin/bash

SRC_DIR="$1"
OUTPUT_FILE="$2"

echo "Packing from: $SRC_DIR"
echo "Target output: $OUTPUT_FILE"

7z a -tzip "$OUTPUT_FILE" "$SRC_DIR/." -y

if [ $? -eq 0 ]; then
    echo "Success: $OUTPUT_FILE created."
else
    echo "Error: 7-Zip failed."
    exit 1
fi
