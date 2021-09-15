cmake_minimum_required (VERSION 3.17.0)
project(UML_CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED Off)

include(conanbuildinfo.cmake)
conan_basic_setup()

add_executable(jsmach_uml)
target_sources(jsmach_uml PUBLIC main.cpp "UMLController.cpp" "UMLAttribute.cpp" "UMLClass.cpp" "UMLRelationship.cpp" "UMLModel.cpp" "JSONFileSys.cpp")

target_link_libraries(jsmach_uml ${CONAN_LIBS})

# eventually when you have libraries/dependences
#   find_package(<LibraryName> REQUIRED)
#   target_link_libraries(uml PUBLIC <whatever library you need>)