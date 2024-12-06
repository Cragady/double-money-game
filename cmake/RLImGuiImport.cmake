if (NOT RLImGui_Loaded)

  project(rlimgui)

  include(ImGuiImport)

  set(RLIMGUI_VENDOR_DIR "${CMAKE_SOURCE_DIR}/vendor/rlImGui")

  add_library(rlimgui STATIC
    "${RLIMGUI_VENDOR_DIR}/rlImGui.cpp"
  )
  target_include_directories(rlimgui PUBLIC ${CMAKE_SOURCE_DIR}/vendor/rlImGui)
  target_link_libraries(rlimgui PUBLIC imgui)

  file(COPY "${RLIMGUI_VENDOR_DIR}/resources" DESTINATION "${CMAKE_SOURCE_DIR}/assets/vendor/rlImGui")

  set(RLImGui_Loaded true)
endif ()
