# PA9: Lighting

# Building and Running

## Dependencies
Uses ImageMagick to load texture images.

## Controls

w - move cube forward

s - move cube backward

a - move cube left

d - move cube right

u - Increase ambient brightness

j - Decrease ambient brightness

h - Increase specularity of objects

k - decrease specularity of objects

q - Switch to Gouraud lighting

z - switch to phong lighting

Up Arrow - Increase spotlight size

Down Arrow - Decrease spotlight size

Left Arrow - Increase spotlight brightness

Right Arrow - Decrease spotlight brightness

## CMake Instructions
Navigate to the PA9 directory. Running the executable correctly involves specifying
the type of lighting you want to load by default, choosing between "Gouraud" or
"Phong" as command-line parameters. 

```bash
mkdir build
cd build
cmake ..
make
./Tutorial Gouraud 
OR
./Tutorial Phong 
```


## Ubuntu.cse.unr.edu
```bash
/usr/NX/scripts/vgl/vglrun ./Tutorial Gouraud 
```
