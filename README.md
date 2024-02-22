Welcome to MazeMaster ALX-SE EDITION!
The Maze presents itself as a 3D maze game employing ray casting to translate a 2D map into an immersive 3D environment.

Experience the Thrill of Raycasting Technology:
Ever wondered how classic games like Wolfenstein 3D created their immersive 3D environments? Well, wonder no more! MazeMaster 3000 utilizes cutting-edge raycasting technology to render a pseudo-3D perspective, providing you with a unique and captivating gameplay experience. Prepare to be transported into the heart of the maze like never before!
Developed in C using the SDL2 library, The Maze is compatible with MacOS and Linux/Ubuntu, leveraging the capabilities of gcc (Apple clang version 14.0.0).

SDL2, or Simple DirectMedia Layer, serves as a versatile cross-platform development tool, offering direct access to audio, keyboard, mouse, joystick, and graphics hardware via OpenGL and Direct3D. It's widely utilized in video playback software, emulators, and various games, including titles from Valve's esteemed catalog and numerous Humble Bundle offerings.

To play The Maze, ensure your system runs Linux/Ubuntu or MacOS and has SDL2 and sdl_image installed. Follow these steps for installation:

1. SDL2 installation:
brew install SDL2
brew install SDL2_image
brew install SDL2_ttf

To start playing:

Clone the GitHub repository.
2. Compile all .c files in the maze directory:

gcc -Wall -Werror -Wextra -pedantic ./source_c/*.c -lm -I/path/to/SDL2/include $(sdl2-config --cflags --libs) -lSDL2_image -o maze

3. Execute ./maze to launch the game.
Controls:

Move forward: Up arrow key or W
Move backward: Down arrow key or S
Rotate counter-clockwise: Left arrow key or A
Rotate clockwise: Right arrow key or D
