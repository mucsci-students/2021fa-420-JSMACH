cmake_minimum_required (VERSION 3.17.0)
project(UML_CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED Off)

include(conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

add_executable(jsmach_uml)
target_sources(jsmach_uml PUBLIC main.cpp "UMLController.cpp" "UMLAttribute.cpp" "UMLClass.cpp" "UMLRelationship.cpp" "UMLModel.cpp" "JSONFileSys.cpp")

target_link_libraries(jsmach_uml CONAN_PKG::nlohmann_json)

FILE(GLOB TEST_FILES tests/*.cpp)

add_executable(jsmach_tests tests/UnitTests.cpp ${TEST_FILES})
target_sources(jsmach_tests PUBLIC "UMLController.cpp" "UMLAttribute.cpp" "UMLClass.cpp" "UMLRelationship.cpp" "UMLModel.cpp" "JSONFileSys.cpp")
target_link_libraries(jsmach_tests CONAN_PKG::catch2 CONAN_PKG::nlohmann_json)


enable_testing()
add_test (NAME unit_tests COMMAND jsmach_tests)