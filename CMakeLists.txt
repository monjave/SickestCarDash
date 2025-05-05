cmake_minimum_required(VERSION 3.16)

project(SICKEST_CAR_DASH LANGUAGES CXX)

# Set global C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable testing across all subdirectories if desired
option(BUILD_TESTING "Enable unit tests" ON)
option(BUILD_GUI "Build the Qt GUI" ON)

# Add subdirectory for actual application
add_subdirectory(QtApp)
