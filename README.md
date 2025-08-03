`VoxelGL` - Voxel Engine, writen with OpenGL

# 1. How to build?
## 1.1. On Linux:
Clone the repo:
```
git clone https://github.com/MrKrot792/VoxelGL
```

Then, build with CMake:
```
mkdir build && cd build
cmake ..
make
```

To run:
```
cd .. # Going to VoxelGL root
build/VoxelGL
```

## 1.2. On windows:
I'm not quite sure how CMake works on Windows.
But no worries! Just download the latest release for Windows and enjoy!
If you're brave enough, you can compile it yourself - all the libraries are in the `external` directory.
Just run cmake with `-DCMAKE_TOOLCHAIN_FILE=../toolchain-mingw64.cmake`.
