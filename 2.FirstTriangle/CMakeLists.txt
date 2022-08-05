# CMakeList.txt : CMake project for Setup, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
find_package(glfw3 CONFIG REQUIRED)
find_package(glew CONFIG REQUIRED)
find_package(OpenGL REQUIRED)


include_directories(${GLEW_INCLUDE_DIRS})
include_directories(${GLFW_INCLUDE_DIRS})
include_directories(${OPENGL_INCLUDE_DIRS})



# Add source to this project's executable.
add_executable (FirstTriangle "main.cpp" )
target_link_libraries(FirstTriangle PRIVATE glfw ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES})



if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Setup PROPERTY CXX_STANDARD 20)
endif()

