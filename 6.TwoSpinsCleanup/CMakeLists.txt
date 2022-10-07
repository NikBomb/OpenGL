# CMakeList.txt : CMake project for Setup, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
find_package(glfw3 CONFIG REQUIRED)
find_package(glew CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm CONFIG REQUIRED)


include_directories(${GLEW_INCLUDE_DIRS})
include_directories(${GLFW_INCLUDE_DIRS})
include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(${GLM_INCLUDE_DIRS})



# Add source to this project's executable.
set(SOURCES main.cpp 
            Mesh.cpp
            Mesh.h
            Window.cpp
            Window.h 
            Shaders.h 
            Shaders.cpp)
            
add_executable (TwoSpins ${SOURCES} )
target_link_libraries(TwoSpins PRIVATE glfw ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES})
set_property(TARGET TwoSpins PROPERTY CXX_STANDARD 20)

