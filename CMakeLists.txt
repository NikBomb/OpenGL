# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("OpenGL")

# Include sub-projects.
add_subdirectory ("1.Setup")
add_subdirectory("2.FirstTriangle")
add_subdirectory("3.Transformations")
add_subdirectory("4.Interpolation")
add_subdirectory("5.SpinningPyramid")
add_subdirectory("6.TwoSpinsCleanup")

