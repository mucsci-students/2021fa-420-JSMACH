[![C/C++ CI](https://github.com/mucsci-students/2021fa-420-JSMACH/actions/workflows/realmain.yml/badge.svg)](https://github.com/mucsci-students/2021fa-420-JSMACH/actions/workflows/realmain.yml)
# 2021fa-420-JSMACH

### Dependencies:

- Python3
- CMake (version 3.17.0 minimum)
- Conan package manager

### Instructions:

1. Clone repo to desired local folder
2. Run these commands: 

    `sudo pip3 install cmake`
    `sudo pip3 install conan`

3. Navigate to the project root (Should have a CMakeLists.txt file in it)
4. `conan install .` - installs library dependencies
5. `mkdir build`
6. `cd build`
5. `cmake ..` - creates Makefile, SLN file, etc depending on your compiler
6. If cmake compiled with Visual Studio, then you should have a .sln file that you can compile using either Visual Studio or using the Visual Studio Developer Command Prompt with 

    ```cl /EHsc main.cpp```

8. If cmake compiled with GCC (probably on Mac or Linux) you should have a Makefile that can be used to compile with 

    ```make```

9. An executable should be available.
    
    ```./jsmach_uml```
