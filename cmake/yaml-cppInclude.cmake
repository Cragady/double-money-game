if (NOT TARGET yaml-cpp)

  include(FetchContent)

  FetchContent_Declare(
    yaml-cpp
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/vendor/yaml-cpp
  )

  FetchContent_MakeAvailable(yaml-cpp)
endif()
