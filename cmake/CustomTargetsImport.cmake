add_custom_target(
  test
  COMMAND tests
)

add_custom_target(
  verbose-test
  COMMAND tests -s
)

add_custom_target(
  run
  COMMAND DMG
)

add_custom_target(
  val
  COMMAND valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=${CMAKE_SOURCE_DIR}/log/valgrind.log ${CMAKE_SOURCE_DIR}/build/DMG
)

add_custom_target(
  og
  COMMAND gcc ${CMAKE_SOURCE_DIR}/ref/double-money-game.c -Iinclude -Wall -Wpedantic -Werror -o ${CMAKE_SOURCE_DIR}/build/og.out
)

add_custom_target(
  print-test
  COMMAND gcc ${CMAKE_SOURCE_DIR}/ref/terminal-print-test.c -Iinclude -Wall -Wpedantic -Werror -o ${CMAKE_SOURCE_DIR}/build/print-test.out
)

add_custom_target(
  alt-all
  COMMAND make og
  COMMAND make print-test
)

add_custom_target(
  run-og
  COMMAND ${CMAKE_SOURCE_DIR}/build/og.out
)

add_custom_target(
  run-print-test
  COMMAND ${CMAKE_SOURCE_DIR}/build/print-test.out
)

add_custom_target(
  ultra-clean
  COMMAND rm -rf ${CMAKE_SOURCE_DIR}/build/*
)

add_custom_target(
  git-clean-see
  COMMAND git clean -ndfX --exclude="\!.idea/" --exclude="\!.idea/*" --exclude="\!.playground/" --exclude="\!.playground/*" --exclude="\!log/*" --exclude="\!imgui.ini"

  # COMMAND echo "run \\\"make git-clean\\\" or \\\'git clean -dfX --exclude=\\\"\\\\!.idea/\\\" --exclude=\\\"\\\\!.idea/*\\\" --exclude=\\\"\\\\!.playground/\\\" --exclude=\\\"\\\\!.playground/*\\\" --exclude=\\\"\\\\!log/*\\\" --exclude=\\\"\\\\!imgui.ini\\\"\\\' if you are OK with deleting the listed files"
  COMMAND echo "run \\\"make git-clean\\\" if you are OK with deleting the listed files"
)

add_custom_target(
  git-clean
  COMMAND git clean -dfX --exclude="\!.idea/" --exclude="\!.idea/*" --exclude="\!.playground/" --exclude="\!.playground/*" --exclude="\!log/*" --exclude="\!imgui.ini"
)
