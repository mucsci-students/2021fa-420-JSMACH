cmake_minimum_required (VERSION 3.19.0)
project(UML_CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED Off)

include(conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

#ensure files are avalible we can remove after testing
macro(add_dependency)
foreach(contentName IN ITEMS ${ARGV})
  string(TOLOWER ${contentName} contentNameLower)
  FetchContent_GetProperties(${contentName})
  if(NOT ${contentNameLower}_POPULATED)
      message(STATUS "\tSetting up ${BoldBlue}${contentName}${ColorReset}")
    FetchContent_Populate(${contentName})

    if(${ADD_DEP_USE_CMAKELIST})
      message("\t\t ${Grey}Using CMakeLists.txt${ColorReset}")
      set(MESSAGE_QUIET ON)
      add_subdirectory(${${contentNameLower}_SOURCE_DIR}
                       ${${contentNameLower}_BINARY_DIR})
      unset(MESSAGE_QUIET)
    else()
      message("\t\t ${Grey}Using as header only library${ColorReset}")
    endif()
  endif()
endforeach()
endmacro()

#get needed files
include(FetchContent)
FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG master
)
FetchContent_MakeAvailable(imgui)


FetchContent_Declare(
  SDL2
  GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
  GIT_TAG 35d045584df29c2399e624d15d7723851b16dc39
)
FetchContent_MakeAvailable(SDL2)

FetchContent_Declare(
    gl3w
    GIT_REPOSITORY https://github.com/skaslev/gl3w.git
    GIT_TAG master
)
FetchContent_MakeAvailable(gl3w)

FetchContent_GetProperties(gl3w)
FetchContent_GetProperties(SDL2)
FetchContent_GetProperties(imgui)

#THIS IS USED TO RUN GLEW PYTHON FILE NEEDED FOR IMGUI 
execute_process(COMMAND python gl3w_gen.py --root ${PROJECT_BINARY_DIR}/libs/gl3w WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/libs/gl3w)

#remove after testing 
add_dependency(imgui SDL2  )

#setting up opengl and SDL2 
set(SOURCE_DIR ${CMAKE_CURRENT_BINARY_DIR}/src)
set(HEADER_DIR ${CMAKE_CURRENT_BINARY_DIR}/include)
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)
set(SDL2_INCLUDE_DIR C:/SDL/SDL2-2.0.3/include/SDL2)
set(SDL2_LIB_DIR C:/SDL/SDL2-2.0.3/lib/x64)
include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})
include_directories(${SDL2_INCLUDE_DIRS})


#this is where I am stuck I'm trying to get all header files
file(GLOB SOURCES_)
file(GLOB SOURCES_IMGUI CONFIGURE_DEPENDS "${imgui_SOURCE_DIR}/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/imgui/*.cpp")
file(GLOB HEADERS_IMGUI CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/imgui/*.hpp")
file(GLOB SOURCES_IMGUI CONFIGURE_DEPENDS "${imgui_SOURCE_DIR}/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/imgui/*.cpp")
file(GLOB HEADERS_IMGUI CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/backends/*.hpp")
source_group("ImGui" FILES ${HEADERS_IMGUI} ${SOURCES_IMGUI})

#get those files!!!
set(IMGUI_DIR ${imgui_SOURCE_DIR})
set(IMGUI_SOURCES
${IMGUI_INCLUDE_DIR}/examples/example_glfw_opengl3
${IMGUI_INCLUDE_DIR}/imgui_draw.cpp
${IMGUI_INCLUDE_DIR}/imgui_tables.cpp
${IMGUI_INCLUDE_DIR}/imgui_widgets.cpp
${IMGUI_INCLUDE_DIR}/misc/cpp/imgui_stdlib.cpp)

#more trying to get the files
set(IMGUI_PUBLIC_HEADERS
${IMGUI_INCLUDE_DIR}/imconfig.h
${IMGUI_INCLUDE_DIR}/imgui.h
${IMGUI_INCLUDE_DIR}/imgui_internal.h # not actually public...
${IMGUI_INCLUDE_DIR}/imstb_rectpack.h
${IMGUI_INCLUDE_DIR}/imstb_textedit.h
${IMGUI_INCLUDE_DIR}/imstb_truetype.h
${IMGUI_INCLUDE_DIR}/misc/cpp/imgui_stdlib.h)


set(HEADERS_CXX_FILES 
${SOURCE_DIR}/imgui.h
${SOURCE_DIR}/imconfig.h
${SOURCE_DIR}/imgui_internal.h
${SOURCE_DIR}/imstb_rectpack.h
${SOURCE_DIR}/imstb_textedit.h
${SOURCE_DIR}/imstb_truetype.h
)

set(SOURCES_CXX_FILES 
${SOURCE_DIR}/imgui.cpp
${SOURCE_DIR}/imgui_draw.cpp
${SOURCE_DIR}/imgui_widgets.cpp
${SOURCE_DIR}/imgui_demo.cpp
)

file(GLOB FONTS_FILES ${FONTS_DIR}/*.ttf)

set(HEADERS_CXX_IMPL_FILES)
set(SOURCES_CXX_IMPL_FILES)
if (IMGUI_WITH_IMPL)
Init_Impl_Files(HEADERS_CXX_IMPL_FILES SOURCES_CXX_IMPL_FILES)
endif()

#the updates on 9/29 where failing removed for the moment 

#add_library(uml ${HEADERS_IMGUI} ${SOURCES_IMGUI})

#target_sources(uml PRIVATE "UMLController.cpp" "UMLAttribute.cpp" "UMLClass.cpp" "UMLRelationship.cpp" "UMLModel.cpp" "JSONFileSys.cpp")
#target_link_libraries(uml CONAN_PKG::nlohmann_json) 
#target_include_directories(uml PUBLIC ${imgui_SOURCE_DIR})

add_executable(jsmach_gui )
#target_include_directories(jsmach_gui PUBLIC ${imgui_SOURCE_DIR})
target_sources(jsmach_gui PUBLIC main.cpp)
 target_link_libraries(jsmach_gui SDL2main SDL2  )
 #target_sources(jsmach_gui PRIVATE "UMLController.cpp" "UMLAttribute.cpp" "UMLClass.cpp" "UMLRelationship.cpp" "UMLModel.cpp" "JSONFileSys.cpp")
target_link_libraries(jsmach_gui CONAN_PKG::nlohmann_json)
target_include_directories(jsmach_gui PUBLIC ${SDL2_INCLUDE_DIRS})
target_include_directories(jsmach_gui PUBLIC ${OPENGL_INCLUDE_DIR})
target_link_libraries(jsmach_gui ${SDL2_LIBRARIES})
target_link_libraries(jsmach_gui ${OPENGL_LIBRARIES})



#add_executable(jsmach_uml)
#target_sources(jsmach_uml PUBLIC main.cpp)
#target_link_libraries(jsmach_uml uml)

#add_executable(jsmach_tests)
#target_sources(jsmach_tests PUBLIC tests/UnitTests.cpp tests/UMLModel_Test.cpp)
#target_link_libraries(jsmach_tests uml CONAN_PKG::catch2)


enable_testing()
add_test (NAME unit_tests COMMAND jsmach_tests)

#This is the easiest way to check what's been installed remove after testing
get_target_property(OUT jsmach_gui LINK_LIBRARIES)
message(STATUS ${OUT})
