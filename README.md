# littlecraftGL

> :warning: **This project is still very much under development!**, wait until it will be finished...


This is the code for the second project for the Computer Graphics course at the University Of Bologna. The goal was to make an interactable 3D scene in OpenGL.
I decided to make a clone of the popular game "Minecraft", in order to challenge my knowledge and capabilities.

Some of the features of the original are missing due to time and complexity constraints.


## How to compile

This branch represents the <b>Linux version</b> of the code (which is essentially the same aside from some minor tweaks and the compilation method). You can check the Windows version of the code [here](https://github.com/AngeloGalav/littlecraftGL/tree/windows).

To compile and run in Linux, simply use the following commands:

```
cd littlecraftGL
make && ./glCraft
```

and that's pretty much it.


## Dependencies

This project uses the following libraries:

- freeGLUT - an implementation of GLUT</li>
- GLEW</li>
- glm - the openGL math library</li>
- [FastNoiseLite](https://github.com/Auburn/FastNoiseLite) - A single header lib to generate the perlin noise map

Both can be easily downloaded with `pacman` or `apt-get`.

The project also uses two additional libraries: `json.hpp` and `gltext.h`, which are both included in the project. 

## Milestones

You don't need to read any of this, I'm just using this to keep track of what I have to do.

- [x] Set up compilation enviroment on Linux
- [x] Refactor base code
- [x] Fix awful z-buffer bug (which plagued me for months)
- [x] Added Keyboard-controlled Camera
- [x] Added Quad 
- [x] Added Cube
- [x] Added Textures support
- [x] Added Cube transformations
- [x] Textured Cube
- [ ] Block management
- [ ] Plain-cube floor
- [ ] Noise for procedural generation
- [ ] Deleting and placing cubes
- [ ] Multiple chunk management
- [ ] Water
- [ ] Fog
- [ ] Cube-map
- [ ] Water reflection
- [ ] Trees?
- [ ] Gold block, silver-block 
- [ ] Shading on gold and silver blocks