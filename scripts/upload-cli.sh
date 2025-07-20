#!/bin/bash

# Upload script for Arduino Snake game using Arduino CLI

echo "Uploading Arduino Snake game to Arduboy..."

# Set up PATH to include local Arduino CLI installation
export PATH="$(pwd)/bin:$PATH"

# Check if Arduino CLI is installed
if ! command -v arduino-cli &> /dev/null; then
    echo "Error: Arduino CLI is not installed."
    echo "Run: curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | sh"
    exit 1
fi

# List available boards to help user identify their Arduboy
echo "Scanning for connected boards..."
arduino-cli board list

echo ""
echo "Make sure your Arduboy is connected via USB and in bootloader mode."
echo "Press and hold the UP button while powering on to enter bootloader mode."
echo ""

# Upload to the first detected Leonardo-compatible device
# Arduboy appears as Leonardo (ATmega32U4)
arduino-cli upload -p $(arduino-cli board list | grep "Leonardo" | head -1 | awk '{print $1}') --fqbn arduino:avr:leonardo src/

if [ $? -eq 0 ]; then
    echo "Upload successful!"
    echo "Your Arduboy should now be running the Snake game!"
else
    echo "Upload failed!"
    echo "Make sure:"
    echo "1. Arduboy is connected via USB"
    echo "2. Arduboy is in bootloader mode (hold UP while powering on)"
    echo "3. You have proper USB permissions"
    exit 1
fi