#
# Copyright (c) 2019, New York University and Max Planck Gesellschaft.
#
# License BSD-3 clause
#

#
# set up the project
#
cmake_minimum_required(VERSION 3.10.2)

project(yaml_utils)

# specify the C++ 17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#
# Dependencies
#

# depend on ament macros
find_package(yaml-cpp CONFIG REQUIRED)
find_package(Eigen3 REQUIRED)


# Headers only library. we only need to install
add_library(${PROJECT_NAME} INTERFACE)
# Add the include dependencies
target_include_directories(
  ${PROJECT_NAME}
  INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:include>)

target_link_libraries(${PROJECT_NAME} INTERFACE ${YAML_CPP_LIBRARIES})
target_link_libraries(${PROJECT_NAME} INTERFACE Eigen3::Eigen)

# command to install the library
install(
  TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}Targets
  )
#
# Install the includes (nothing else needs to be installed)
#
install(DIRECTORY include/ DESTINATION include)

#
# add unit tests #
#
include(CTest)
if(BUILD_TESTING)
  find_package(GTest CONFIG REQUIRED)
  include(GoogleTest)

  add_executable(test_${PROJECT_NAME} 
                      tests/gtest_main.cpp
                      tests/test_yaml_tools.cpp)
  target_link_libraries(test_${PROJECT_NAME} Eigen3::Eigen)
  target_link_libraries(test_${PROJECT_NAME} ${YAML_CPP_LIBRARIES})
  target_link_libraries(test_${PROJECT_NAME} GTest::gtest)
  target_include_directories(
    test_${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  )
  gtest_add_tests(TARGET test_${PROJECT_NAME})
endif()

#
# create the cmake package
#
# we need this to create a nice exportable package
include(CMakePackageConfigHelpers)

# generate the necessary cmake file
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
  INSTALL_DESTINATION share/${PROJECT_NAME}/cmake
)
write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
  VERSION 1.0.0
  COMPATIBILITY SameMajorVersion )

# we copy the cmake files we would need to configure the project
install(FILES
          "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
          "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
        DESTINATION share/${PROJECT_NAME}/cmake
)


# we install the cmake package
install(EXPORT ${PROJECT_NAME}Targets
        FILE ${PROJECT_NAME}Targets.cmake
        NAMESPACE ${PROJECT_NAME}::
        DESTINATION share/${PROJECT_NAME}/cmake
)

#
# Building documentation.
#
# add_documentation()