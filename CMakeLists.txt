cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

# Set project name and version
project(shoot-the-aliens VERSION 0.1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

if(MSVC)
  # Link statically when building on windows to help distribution of the software
  set(SFML_STATIC_LIBRARIES TRUE)
  # Hide the console window in visual studio projects
  set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
endif()

# Find SFML shared libraries
find_package(SFML 2.5.1 COMPONENTS system window graphics audio REQUIRED)

# Compile executable
add_executable(shoot-the-aliens alien.cpp explosion.cpp fond.cpp gameengine.cpp jeu.cpp joueur.cpp main.cpp soundmanager.cpp tir.cpp vaisseau.cpp)

# Set include directory search paths
target_include_directories(shoot-the-aliens PRIVATE "${PROJECT_BINARY_DIR}")

# Link executable to required SFML libraries
target_link_libraries(shoot-the-aliens sfml-audio sfml-graphics sfml-window sfml-system)

# Install target
install(TARGETS shoot-the-aliens DESTINATION bin)
