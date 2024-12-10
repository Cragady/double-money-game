# Additional targets to perform clang-format/clang-tidy
# Get all project files
file(GLOB_RECURSE
     ALL_CXX_SOURCE_FILES
     src/*.[chi]pp src/*.[chi]xx src/*.cc src/*.hh src/*.ii src/*.[CHI]
     test/*.[chi]pp test/*.[chi]xx test/*.cc test/*.hh test/*.ii test/*.[CHI]
     )

# Adding clang-format target if executable is found
find_program(CLANG_FORMAT "clang-format")
if(CLANG_FORMAT)
  add_custom_target(
    clang-format
    COMMAND /usr/bin/clang-format
    -i
    -style=file
    ${ALL_CXX_SOURCE_FILES}
    )
endif()

# Adding clang-tidy target if executable is found
find_program(CLANG_TIDY "clang-tidy")
if(CLANG_TIDY)
  add_custom_target(
    clang-tidy
    COMMAND /usr/bin/clang-tidy
    -p ${CMAKE_SOURCE_DIR}
    ${ALL_CXX_SOURCE_FILES}
    -config=''
    )
# find_program(CLANG_TIDY "clang-tidy")
# if(CLANG_TIDY)
#   add_custom_target(
#     clang-tidy
#     COMMAND /usr/bin/clang-tidy
#     ${ALL_CXX_SOURCE_FILES}
#     -config=''
#     --
#     -std=c++20
#     ${INCLUDE_DIRECTORIES}
#     )
endif()
