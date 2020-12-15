# C++ WS2021 🦖

Can Çölükoğlu, Anton Quietzsch

## Table of Contents

- A1
  - [1.1](./A1-1/main.cpp) `my::Vec3f`
  - [1.2](./A1-2/main.cpp) Template `my::Vec<>` (`std::array<>`)
- A2
  - [2.1](./A2-1/main.cpp) Template `my::Vector<>` (`std::vector<>`)
  - [2.2](./A2-2/main.cpp) Template `my::Vector<>` (`std::vector<>`) w/ copy, move, `malloc`

## Building and Running

> ⚠️ Create a new folder for new project first. 

Inside the project folder, run:

- `mkdir build && cd build` to create a build folder
- `cmake -G "Unix Makefiles" ..` to create makefiles
- `make all` to build a binary in `/build`
- `./main` to run

To clean the makefiles, run: `make clean`