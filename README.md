# JTracer
A path tracer that renders to file. 

<img src="/outputs/final/original/world5-16spp.png" height="300"/>

## Description
JTracer is a simple path tracer written for educational purposes. It includes basic primitive objects (sphere, box), and easily extendable classes to add further primatives. Due to the structure of the codebase, it is easy to edit the scene programmatically, adding, moving, or rotating objects, etc.

Within the `scripts` foler, there helper scripts for analysing path traced images. Each script is explained below. 

For the time being, the path tracer lacks significant optimization. 

## To Build
1. Clone this repo:
```
git clone https://github.com/jjc914/jtracer.git
```
2. Make a build folder within the project folder and change directory:
```
mkdir build
cd build
```
3. Build the project and run:
```
cmake ..
cmake --build .
src/jtracer
```

## Usage
* `denoise.sh` uses Intel Open Image Denoise to denoise the image. Follow Intel's install guide for usage. 
* `compare.py` outputs an image of the absolute difference of each pixel for two images. It is used to compare two scenes rendered with different settings, such as a denoised image compared to a high sample image. Such examples can be found in `outputs/final`.
* `invert.py` inverts an image. It may be useful for finding areas with absolute difference when it is difficult to spot originally.

To render, the following code can be used:
```cpp
camera cam(vec3<double>(0.0, 1.0, 0.0), 16.0 / 9.0, 70);
screen scrn(&cam, 256, 144, color(0.0, 0.0, 0.0));

std::vector<primative*> world1;

lambertian* red = new lambertian(color(1.0, 0.0, 0.0));
sphere* myObject = new sphere("red", red, vec3<double>(0.0, 2.95, -13.0), 2.0);
world1.push_back(myObject);

scrn.render(&world5, 16, 3, 64, "world5-16spp.ppm");
```

For further examples, read `main.cpp`. 

## To Do
- [ ] Implement importance sampling
- [ ] Implement multi-importance sampling
- [ ] Add ray-triangle intersection
- [ ] OBJ reader
