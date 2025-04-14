# cub3D - A raycasting project (Work in progress)

A raycasting 3D game engine built using MLX42 and C. Inspired by **Wolfenstein 3D**, showcasing 2.5D graphics, interactive doors, sprites, textures, and a dynamic HUD

## Features

- **Raycasting Engine:** Uses a DDA algorithm to render texture-mapped walls.
- **Dynamic Doors:** Doors have multiple states (closed, opening, open, closing) and animate based on player proximity.
- **Sprite Rendering:** Depth-sorted sprite drawing with occlusion handling.
- **Minimap:** Real-time minimap including player position, rays, and map layout.
- **HUD Animation:** Hands HUD that animates when the player moves.
- **Input Handling:** Supports both keyboard and mouse controls for movement and view rotation.
- **Responsive Resolution:** Automatically adapts to different screen sizes and maintains a minimum window resolution.

## Screenshots

![Rotation demo](assets/optimized.gif)

---

## Dependencies

- [MLX42](https://github.com/codam-coding-college/MLX42) (will be cloned if missing)
- `cmake`, `glfw`, and `libglfw` (ensure glfw is installed, e.g., via Homebrew on macOS)
- A working C compiler (`cc`)

Install via Homebrew (for macOS, including M1/M2 chips):

```bash
brew install cmake glfw
```

## Build
Clone the repository and run

```bash
make
```

This will:
Build libft and MLX42
Compile all project source files
Link everything into the cub3d executable

## Usage
```bash
./cub3d path/to/map.cub
```

### Controls

| Action           | Key(s)                          |
|------------------|---------------------------------|
| Move forward     | **W**                           |
| Move backward    | **S**                           |
| Strafe left      | **A**                           |
| Strafe right     | **D**                           |
| Rotate left/right| **← / →** or **Mouse movement** |
| Toggle Cursor    | **TAB**                         |
| Quit             | **ESC**                         |

### Map file format

---

## General Info

### Code Structure

### Memory management

