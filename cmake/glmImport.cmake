if (NOT TARGET glm)
  include(FetchContent)

  FetchContent_Declare(
    glm
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/vendor/glm
  )

  FetchContent_MakeAvailable(glm)
endif()
