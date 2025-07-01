# particle_sim
A particle engine using C++ and SFML.  Observe how particles affect the electric field.  Simulate the real-time motion of electrically charged particles subject to Coloumbs Law and classical physics.

## Requirements
- CMake
- C++17 or newer
- SFML 3.0.1 or newer

## Installation and Compilation
Install `CMake` and `SFML` with Brew:
```
$ brew install cmake
$ brew install sfml
```

Download the source code with:
```
$ git clone git@github.com:caoalbe/particle_sim.git
$ cd particle_sum
```

Compile the program with CMake:
```
$ mkdir build
$ cd build
$ cmake ..
$ make
```

## Examples
Here are some example simulations you can run
```
$ ./main circular
$ ./main circular-moving
$ ./main four
$ ./main random
```

If the electric field is distracting you can add the flag `--ignore-field`
```
$ ./main random --ignore-field
```