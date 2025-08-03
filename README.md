<div align = center>
<img width="1920" height="1080" alt="2025-07-27T02:14:30,825112127+02:00" src="https://github.com/user-attachments/assets/a0b4e573-403d-465f-b088-3934bd188807" />
<sub>v0.01</sub>

</div>

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
