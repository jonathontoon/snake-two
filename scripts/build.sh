#!/bin/bash

# Build script for Arduino Snake game using PlatformIO

echo "Building Arduino Snake game..."

# Check if PlatformIO is installed
if ! command -v pio &> /dev/null; then
    echo "Error: PlatformIO is not installed."
    echo "Please install PlatformIO: https://platformio.org/install"
    exit 1
fi

# Build the project
pio run

if [ $? -eq 0 ]; then
    echo "Build successful!"
    echo "Firmware located at: .pio/build/leonardo/firmware.hex"
else
    echo "Build failed!"
    exit 1
fi