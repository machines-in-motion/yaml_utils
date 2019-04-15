######################
# set up the project #
######################
cmake_minimum_required(VERSION 3.5.1)

project(yaml_cpp_catkin)

# required to use std::shared_ptr in code
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wl,--no-as-needed")

# ensuring path to libraries are set during install
set(CMAKE_SKIP_BUILD_RPATH  FALSE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
set(CMAKE_INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/lib)

###########################
# Define the dependencies #
###########################

set(CATKIN_PKGS ${CATKIN_PKGS}
    # MPI-IS dependencies
    mpi_cmake_modules
)
find_package(catkin REQUIRED COMPONENTS ${CATKIN_PKGS})

add_required_dependency("yaml-cpp >= 0.5")
build_prefix_for_pkg("yaml-cpp" yaml_cpp_name)
set(catkin_INCLUDE_DIRS
  ${${yaml_cpp_name}_INCLUDE_DIRS}
  ${catkin_INCLUDE_DIRS}
)
link_directories(
  ${${yaml_cpp_name}_LIBRARY_DIRS}
)
set(catkin_LIBRARIES
  ${${yaml_cpp_name}_LIBRARIES}
  ${catkin_LIBRARIES}
)

##########################################
# export the package as a catkin package #
##########################################

catkin_package(
  INCLUDE_DIRS include
)
