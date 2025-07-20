# Arduino Snake Game

A classic Snake game implementation for the Arduboy handheld gaming device.

## Description

This is a simple yet engaging Snake game designed specifically for the Arduboy. The player controls a snake that moves around the screen, eating food to grow longer while avoiding collisions with walls and itself.

## Features

- Classic Snake gameplay mechanics
- Score tracking
- Game over screen with restart functionality
- Optimized for Arduboy's 128x64 OLED display
- 8x8 grid system for smooth gameplay

## Controls

- **D-pad**: Move snake (Up/Down/Left/Right)
- **A Button**: Restart game (when game over)

## Hardware Requirements

- Arduboy or Arduboy FX device
- USB cable for programming

## Building and Installation

### Using Arduino IDE

1. Install the Arduino IDE
2. Install the Arduboy2 library:
   - Go to Sketch → Include Library → Manage Libraries
   - Search for "Arduboy2" and install it
3. Open `src/ardusnake.ino` in Arduino IDE
4. Select your Arduboy device from Tools → Board
5. Connect your Arduboy via USB
6. Click Upload

### Using PlatformIO

1. Install PlatformIO
2. Run the build script:
   ```bash
   ./scripts/build.sh
   ```
3. Upload to device:
   ```bash
   ./scripts/upload.sh
   ```

### Using Arduino CLI (Recommended for Arduboy)

1. The Arduino CLI is automatically installed in the project directory
2. Build the game:
   ```bash
   ./scripts/build-cli.sh
   ```
3. Upload to your Arduboy:
   ```bash
   ./scripts/upload-cli.sh
   ```

**Note**: Make sure your Arduboy is in bootloader mode (hold UP button while powering on) before uploading.

## Project Structure

```
snake-two/
├── README.md
├── src/
│   └── ardusnake.ino      # Main game source code
├── scripts/
│   ├── build.sh           # PlatformIO build script
│   ├── upload.sh          # PlatformIO upload script
│   ├── build-cli.sh       # Arduino CLI build script
│   └── upload-cli.sh      # Arduino CLI upload script
├── bin/
│   └── arduino-cli        # Local Arduino CLI installation
└── platformio.ini         # PlatformIO configuration
```

## Game Rules

1. Use the D-pad to control the snake's direction
2. Eat the food (white squares) to grow and increase your score
3. Avoid hitting the walls or the snake's own body
4. The game ends when you collide with a wall or yourself
5. Press A to restart after game over

## Technical Details

- Grid Size: 8x8 pixels per cell
- Maximum Snake Length: 64 segments
- Frame Rate: 8 FPS
- Display: 128x64 pixels

## License

This project is open source. Feel free to modify and distribute.