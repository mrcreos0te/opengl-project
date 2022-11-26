# opengl-project

Setting up GLEW on linux:

install required dependencies for ubuntu:

```
sudo apt-get install libglfw3-dev libgl1-mesa-dev libglu1-mesa-dev
```

after instalation, glu.h header should appear in /usr/include/GL - this dependency is needed by glew.h

Download .tgz package and build GLEW: https://glew.sourceforge.net/index.html - follow instructions in README

if you get "error while loading shared libraries: libGLEW.so.2.1: cannot open shared object file: No such file or directory" error, create symbolic link between /lib64 and /lib libraries

```
sudo ln -s /usr/lib64/libGLEW.so.2.1 /usr/lib/libGLEW.so.2.1
```

or add 

```
#define GLEW_STATIC
```

to your code before referencing glew.h

Download GLFW sources: https://www.glfw.org/download.html

install additional packages required for compiling GLFW on Linux systems - check first if your system is using X11 or Wayland and install proper package:

```
sudo apt install xorg-dev
```

```
sudo apt install libwayland-dev libxkbcommon-dev wayland-protocols extra-cmake-modules
```

compile GLFW source: https://www.glfw.org/docs/latest/compile.html

