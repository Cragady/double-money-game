if (NOT ImGui_Loaded)
  # add_subdirectory("${CMAKE_SOURCE_DIR}/vendor/imgui")
  add_library(imgui
    "${CMAKE_SOURCE_DIR}/vendor/imgui/imgui.cpp"
    "${CMAKE_SOURCE_DIR}/vendor/imgui/imgui_demo.cpp"
    "${CMAKE_SOURCE_DIR}/vendor/imgui/imgui_draw.cpp"
    "${CMAKE_SOURCE_DIR}/vendor/imgui/imgui_tables.cpp"
    "${CMAKE_SOURCE_DIR}/vendor/imgui/imgui_widgets.cpp"
  )
  target_include_directories(imgui PUBLIC ${CMAKE_SOURCE_DIR}/vendor/imgui)
  set(ImGui_Loaded true)
endif ()
