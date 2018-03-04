
# Kary-Tabesh Curve; Proof of Concept

__Kary-Tabesh Curve__ is a technique to investigate if an arbitrary point in space R(n) where n is more than 1 is inside of a closed shape.

This demo uses the Kary-Tabesh Curve to validate each pixel on the screen to see if they are inside a demo triangle and then paints the pixels within the triangle red.

<br>

<img width="1002" alt="screen shot 1396-12-14 at 1 50 19 am" src="https://user-images.githubusercontent.com/2157285/36951331-b30fee28-2017-11e8-9fe1-6071f4a6c063.png">

<br>

## How to run this software?
You must be inside a UNIX environment with GCC, OpenGL and GLUT installed. Your installation of GCC must support C++11. Then you can simply run:

```
make build
```

And then run

```
./kary-tabesh-curve
```

Within the root of this project's directory.