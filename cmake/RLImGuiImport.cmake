if (NOT RLImGui_Loaded)

  project(rlimgui)

  include(ImGuiImport)

  add_library(rlimgui STATIC
    "${CMAKE_SOURCE_DIR}/vendor/rlImGui/rlImGui.cpp"
  )
  target_include_directories(rlimgui PUBLIC ${CMAKE_SOURCE_DIR}/vendor/rlImGui)
  target_link_libraries(rlimgui PUBLIC imgui)
  set(RLImGui_Loaded true)
endif ()
