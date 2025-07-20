#!/bin/bash

# Build script for Arduino Snake game using Arduino CLI

echo "Building Arduino Snake game with Arduino CLI..."

# Set up PATH to include local Arduino CLI installation
export PATH="$(pwd)/bin:$PATH"

# Check if Arduino CLI is installed
if ! command -v arduino-cli &> /dev/null; then
    echo "Error: Arduino CLI is not installed."
    echo "Run: curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | sh"
    exit 1
fi

# Check if cores and libraries are installed
echo "Checking Arduino AVR core..."
if ! arduino-cli core list | grep -q "arduino:avr"; then
    echo "Installing Arduino AVR core..."
    arduino-cli core install arduino:avr
fi

echo "Checking for Arduboy2 library..."
if ! arduino-cli lib list | grep -q "Arduboy2"; then
    echo "Installing Arduboy2 library..."
    arduino-cli lib install Arduboy2
fi

# Compile the sketch for Arduboy (uses Leonardo board)
echo "Compiling sketch for Arduboy..."
arduino-cli compile --fqbn arduino:avr:leonardo src/

if [ $? -eq 0 ]; then
    echo "Build successful!"
    echo "Firmware located at: src/build/arduino.avr.leonardo/src.ino.hex"
    echo "Ready to upload to Arduboy!"
else
    echo "Build failed!"
    exit 1
fi