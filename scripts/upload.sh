#!/bin/bash

# Upload script for Arduino Snake game using PlatformIO

echo "Uploading Arduino Snake game to device..."

# Check if PlatformIO is installed
if ! command -v pio &> /dev/null; then
    echo "Error: PlatformIO is not installed."
    echo "Please install PlatformIO: https://platformio.org/install"
    exit 1
fi

# Upload to device
pio run --target upload

if [ $? -eq 0 ]; then
    echo "Upload successful!"
else
    echo "Upload failed! Make sure your Arduboy is connected."
    exit 1
fi