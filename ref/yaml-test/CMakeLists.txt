set(YamlTest_SOURCES_DIR ${CMAKE_SOURCE_DIR}/ref/yaml-test/YamlTest)

set (YamlTest_SOURCES
  ${YamlTest_SOURCES_DIR}/YamlTest.cpp
)

set (YamlTest_HEADERS
  ${YamlTest_SOURCES_DIR}/YamlTest.hpp
)

set(YamlTest_INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/include")
# foreach(_headerFile ${YamlTest_HEADERS})
#   get_filename_component(_dir ${_headerFile} PATH)
#   list(APPEND YamlTest_INCLUDE_DIRS ${_dir})
# endforeach()
list(REMOVE_DUPLICATES YamlTest_INCLUDE_DIRS)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(YamlTestlib ${YamlTest_HEADERS} ${YamlTest_SOURCES})
target_include_directories(YamlTestlib
  PUBLIC
  $<BUILD_INTERFACE:${YamlTest_SOURCES_DIR}/..>
  $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
)
target_link_libraries(YamlTestlib yaml-cpp::yaml-cpp)

add_executable(YamlTest main.cpp)
target_link_libraries(YamlTest YamlTestlib)
target_include_directories(YamlTest PUBLIC ${YamlTest_INCLUDE_DIRS})
set_target_properties(YamlTest PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BUILD_OUTPUT})

