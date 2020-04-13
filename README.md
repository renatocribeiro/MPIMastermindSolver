# MPIMastermindSolver
Implementation of a parallel Mastermind solver using OpenMPI.

Inspired from Donald Knuth's article [The Computer as Master Mind](https://www.cs.uni.edu/~wallingf/teaching/cs3530/resources/knuth-mastermind.pdf).

## Dependencies
* CMake 3.15.3-GCCcore-8.3.0
* OpenMPI 3.1.4-GCC-8.3.0

## Usage
```
cmake .
make
mpirun -n 4 mastermind c 9 s 6
```
### Flags
* `-n` number of nodes to be used (OpenMPI flag)
* `c` number of colors
* `s` size of the secret
* `h` uses a hardcoded/fixed secret given by the user instead of a random one (*optional*)
* `r` redestributes the challengers ranges at the end of each round (*optional*)
