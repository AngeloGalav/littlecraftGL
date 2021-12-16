# littlecraftGL

> :warning: **This project is still very much under completition!**, wait until it will be finished...


This is the code for the second project for the Computer Graphics course at the University Of Bologna. The goal was to make an interactable 3D scene in OpenGL.
I decided to make a clone of the popular game "Minecraft", in order to challenge my knoledge and capabilities.

Some of the features of the original are missing due to time and complexity constraints.


## How to compile

This branch represents the <b>Linux version</b> of the code (which is essentially the same aside from some minor tweaks and the compilation method). You can check the Windows version of the code [here](https://github.com/AngeloGalav/doodleJumpGL/tree/windows).

To compile and run in Linux, simply use the following commands:

```
cd doodleJumpGL
make && ./DoodleJumpGL
```

and that's pretty much it.

## Dependencies

This project uses the following libraries:
<ul>
<li>freeGLUT - an implementation of GLUT</li>
<li>GLEW</li>
<li>glm - the openGL math library</li>
</ul>

Both can be easily downloaded with `pacman` or `apt-get`.

The project also uses two additional libraries: `json.hpp` and `gltext.h`, which are both included in the project. 