# Additional targets to perform clang-format/clang-tidy
# Get all project files
file(GLOB_RECURSE
     ALL_CXX_SOURCE_FILES
     *.[chi]pp *.[chi]xx *.cc *.hh *.ii *.[CHI]
 )

 set (DMG_EXCLUDE_DIR "/vendor/")
 foreach(TMP_PATH ${ALL_CXX_SOURCE_FILES})
   string(FIND ${TMP_PATH} ${DMG_EXCLUDE_DIR} DMG_EXCLUDE_DIR_FOUND)
   if(DMG_EXCLUDE_DIR_FOUND GREATER -1)
     list(REMOVE_ITEM ALL_CXX_SOURCE_FILES ${TMP_PATH})
   endif()
 endforeach()
 unset(DMG_EXCLUDE_DIR)

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
