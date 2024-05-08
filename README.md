# littlecraftGL

Voxel engine made in OpenGL and C++, using GLFW and GLAD.
It has recently become my pet project.
Runs on both Linux and Windows (64-bit only).

## Screenshots

![](res/old_screenshot.png)
![](res/screenshot.png)

## How to play

- Use `W,A,S,D` to fly inside the world. Use `I,J,K,L` to rotate the camera.
- You can also use your mouse to rotate the camera for precise movements, although it's a bit wonky since GLUT doesn't provide an easy way to properly handle mouse movement (es. mouse capture).
- You can press `x` for a wireframe view of the currently generated world.
- Press `q` to remove blocks, and `e` to place a wooden plank.

## How to compile

### Linux

To compile and run in Linux, simply use the following commands:

```
mkdir build
cd build
cmake .. && make
```

and that's pretty much it.

### Windows

On Windows, using CMake, the compilation setup is a bit more tedius. Provided that you're using `MinGW` as your compiler, follow these steps:

1. Install the libraries `glfw3` and `glm` manually, by downloading them from their official page (remember to download the proper archive for your CPU architecture!).
2. Unzip them and place them into your User folder (i.e. `C:\[your_user_name]\`). Rename to `glfw` and `glm` respectively.

3. After that, go to your extracted `glfw` folder and copy the contents of `lib-mingw-w64` inside your `MinGW/lib` folder (you'll need to find the path of the `MinGW` compiler yourself).

4. Open a Windows terminal and use the commands:

```
mkdir build
cd build
cmake .. -G "MinGW Makefiles"; make -j8
```

## Dependencies

This project uses the following libraries:

- GLFW
- glad
- glm - the openGL math library
- [FastNoiseLite](https://github.com/Auburn/FastNoiseLite) - A single header lib to generate the Perlin noise map

Both GLFW and glm can be easily downloaded with `pacman` or `apt-get` on Linux. On Windows, you'll have to install them manually (see 'How to compile').

The project also uses two additional libraries: `json.hpp` and `gltext.h`, which are both included in the project.

## Known Issues

- It is missing some key features, that will be added sooner or later.
- The code is very rough, and could use some refactoring. This is due to some GLUT quirks and the fact that some workarounds have been applied to solve some problems encountered during development. Also, I was extremely strict on time.
- Blocks removal is not persistent, so if you delete a cube and roam around the map, you won't be able to see the effect.

## Benchmarking

On Linux, I suggest using MangoHud to analyze the game's framerate:

```
export MANGOHUD_DLSYM=1
mangohud ./littlecraftGL
```

## Origin of the project

Originally, this was essentially my second project for the Computer Graphics course at the University Of Bologna. The goal was to make an interactable 3D scene in OpenGL. At the time, I decided to make a clone of the popular game "Minecraft", in order to challenge my knowledge and capabilities.

You can take a look at the original version of this project, made using GLUT, [in this fork](https://github.com/AngeloGalav/littlecraftGL/tree/glut-consegna).

As of now, this project functions as a way to improve my C++ skills and knowledge, as well as a way to explore the fascinating world of Voxel engines.
