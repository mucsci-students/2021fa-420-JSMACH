# 2021fa-420-JSMACH

### Dependencies:

- CMake (version 3.17.0 minimum)
- Conan package manager

### Instructions:

[![C/C++ CI](https://github.com/mucsci-students/2021fa-420-JSMACH/actions/workflows/realmain.yml/badge.svg)](https://github.com/mucsci-students/2021fa-420-JSMACH/actions/workflows/realmain.yml)

1. Clone repo to desired local folder
2. Run this command: 

    `pip3 install cmake`

3. Navigate to the project root (Should have a CMakeLists.txt file in it)
4. `cmake . .`
5. If cmake compiled with Visual Studio, then you should have a .sln file that you can compile using either Visual Studio or using the Visual Studio Developer Command Prompt with 

    ```cl /EHsc main.cpp```

8. If cmake compiled with GCC (probably on Mac or Linux) you should have a Makefile that can be used to compile with 

    ```make```

