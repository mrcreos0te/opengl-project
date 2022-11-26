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
