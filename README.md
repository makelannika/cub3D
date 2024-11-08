# Cub3D: First-Person Maze Raycasting Game

Cub3D is a maze exploration game built with raycasting techniques, inspired by the classic Wolfenstein 3D. This project leverages the MLX42 graphics library to create a 3D first-person view within a maze environment, incorporating wall textures, floor and ceiling colors, and smooth player movements.

![Screenshot from 2024-10-25 14-17-40](https://github.com/user-attachments/assets/f88b9716-9933-40d7-8f53-fc974632db74)

## Features

- **First-Person Perspective**: Experience the maze as if you are moving through it in real time, with walls and textures displayed based on the direction faced.
- **Textured Walls**: Each wall face has a distinct texture (North, South, East, West), adding realism and depth to the game.
- **Smooth Window Management**: The window allows for switching, minimizing, and closing without any issues.
- **Player Control**: Navigate through the maze with:
  - Arrow keys to look around
  - W, A, S, D keys to move in different directions
- **Map Parsing**: Load different .cub maps, each defining the player's starting position, walls, and walkable areas.
- **Scene Configuration**: Customize the maze's appearance with a .cub file specifying wall textures, floor/ceiling colors, and the maze structure.
- **Error Handling**: If the configuration is incorrect, the program exits gracefully, displaying an error message.

## How to Run

### Prerequisites

- **MLX42 Library**: The project uses MLX42 for graphics, so make sure it's installed.
- **libft Library**: Build your custom libft library if required by your setup.

### Compilation

```bash
make
```

### Run the Game

Provide a .cub configuration file to define the scene:
```bash
./cub3D maps/forest.cub
```
There are other premade map files ready to run with different textures in the maps folder. 

## Controls

| Key | Action |
|-----|--------|
| W | Move Forward |
| S | Move Backward |
| A | Strafe Left |
| D | Strafe Right |
| ←, → | Rotate View Left/Right |
| ESC | Exit the Game |

## Map File Format

The .cub configuration file is crucial for defining the scene's layout and appearance. Here's an example structure:

```
NO ./path_to_north_texture
SO ./path_to_south_texture
WE ./path_to_west_texture
EA ./path_to_east_texture

F 220,100,0     # Floor color (RGB)
C 225,30,0      # Ceiling color (RGB)

111111111111
100000000001
101111111101
1000000000N1
111111111111
```

- **Texture Paths** (NO, SO, WE, EA): Specify the path to the wall texture files.
- **Floor and Ceiling Colors** (F, C): Define colors in RGB format.
- **Map Structure**: A grid of 0 (empty), 1 (wall), and N, S, E, W (player spawn with orientation).

## Error Handling

The program validates the map file. If any misconfiguration is detected, the program exits with an error message.
