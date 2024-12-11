if(NOT DEFINED PLATFORM)
  set(PLATFORM "Desktop")
endif()

add_custom_target(
  desktop
  COMMAND ${CMAKE_COMMAND} -DPLATFORM=Desktop .
)

add_custom_target(
  web
  COMMAND ${CMAKE_COMMAND} -DPLATFORM=Web .
)

if(${PLATFORM} STREQUAL "Desktop")
  add_compile_definitions(PLATFORM_DESKTOP)
endif()
