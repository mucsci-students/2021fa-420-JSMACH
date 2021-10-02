cmake_minimum_required (VERSION 3.17.0)
project(UML_CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED Off)

include(conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

add_library(uml)
target_sources(uml PRIVATE "UMLController.cpp" "UMLAttribute.cpp" "UMLClass.cpp" "UMLRelationship.cpp" "UMLModel.cpp" "JSONFileSys.cpp" "UMLException.hpp" "ClassMethod.cpp" "ClassField.cpp" "MethodParameter.cpp")
target_link_libraries(uml CONAN_PKG::nlohmann_json)

add_executable(jsmach_uml)
target_sources(jsmach_uml PUBLIC main.cpp)
target_link_libraries(jsmach_uml uml)

add_executable(jsmach_tests)
target_sources(jsmach_tests PUBLIC tests/UnitTests.cpp tests/UMLModel_Test.cpp)
target_link_libraries(jsmach_tests uml CONAN_PKG::catch2)


enable_testing()
add_test (NAME unit_tests COMMAND jsmach_tests)