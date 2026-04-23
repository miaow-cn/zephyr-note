# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)
set(BOARD fk743m5_xih6)
set(BOARD_FLASH_RUNNER jlink)
set(BOARD_DEBUG_RUNNER jlink)
set(BOARD_RUNNER_ARGS_jlink
    "--loader=BankAddr=0x90000000&Loader=CLK@PF10_nCS@PG6_D0@PF8_D1@PF9_D2@PF7_D3@PF6"
    CACHE STRING "Extra J-Link runner args" FORCE)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
find_package(Python3 REQUIRED COMPONENTS Interpreter)

project(cpp LANGUAGES CXX)

FILE(GLOB app_sources src/*.c src/*.cpp)
target_sources(app PRIVATE ${app_sources})

# Relocate app code/rodata to external flash (XIP, no copy).
# External flash memory-mapped setup is handled by Zephyr when CONFIG_STM32_MEMMAP=y.
# zephyr_code_relocate(FILES $<TARGET_PROPERTY:app,SOURCES> LOCATION SDRAM1_BSS_NOINIT_DATA)
zephyr_code_relocate(FILES $<TARGET_PROPERTY:app,SOURCES> LOCATION EXTFLASH_TEXT_RODATA NOCOPY)

target_include_directories(app PRIVATE ${CMAKE_SOURCE_DIR}/include)

# The code below locates the git index file for this repository and adds it as a dependency for
# the application VERSION file so that if the repo has a new commit added, even if no files in
# the build have changed, the application version file will be regenerated with the new git commit
find_package(Git QUIET)
if(GIT_FOUND)
  execute_process(
    COMMAND ${GIT_EXECUTABLE} rev-parse --absolute-git-dir
    WORKING_DIRECTORY .
    OUTPUT_VARIABLE application_git_dir
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_STRIP_TRAILING_WHITESPACE
    ERROR_VARIABLE stderr
    RESULT_VARIABLE return_code
  )
  # If there is an error e.g. it is not a git repo, we just silently ignore it and continue
  # without a dependency, this will be the case with freestanding applications.
  if(NOT return_code)
    if(NOT "${stderr}" STREQUAL "")
      message(WARNING "Application build version git rev-parse warned: ${stderr}")
    endif()

    set_property(TARGET app_version_h PROPERTY APP_VERSION_DEPENDS ${application_git_dir}/index)
  endif()
endif()

# Update VS Code debug settings via workspace setup script.
# Run this after final zephyr.elf is linked (not after app library build).
set(VSCODE_SETUP_SCRIPT ${ZEPHYR_BASE}/../.vscode/setup.py)
if(EXISTS ${VSCODE_SETUP_SCRIPT})
  get_filename_component(VSCODE_ARM_TOOLCHAIN_PATH ${CMAKE_GDB} DIRECTORY)

  set(VSCODE_JLINK_DEVICE "")
  set(VSCODE_JLINK_LOADER "")
  get_property(VSCODE_JLINK_ARGS GLOBAL PROPERTY BOARD_RUNNER_ARGS_jlink)

  foreach(arg IN LISTS VSCODE_JLINK_ARGS)
    if(arg MATCHES "^--device=(.*)$")
      set(VSCODE_JLINK_DEVICE ${CMAKE_MATCH_1})
    elseif(arg MATCHES "^--loader=(.*)$")
      set(VSCODE_JLINK_LOADER ${CMAKE_MATCH_1})
    endif()
  endforeach()

  if(VSCODE_JLINK_LOADER)
    set(VSCODE_JLINK_DEVICE_FULL "${VSCODE_JLINK_DEVICE}?${VSCODE_JLINK_LOADER}")
  else()
    set(VSCODE_JLINK_DEVICE_FULL ${VSCODE_JLINK_DEVICE})
  endif()

  set(VSCODE_SETUP_STAMP ${CMAKE_BINARY_DIR}/.vscode_setup.stamp)
  add_custom_command(
    OUTPUT ${VSCODE_SETUP_STAMP}
    COMMAND ${Python3_EXECUTABLE} ${VSCODE_SETUP_SCRIPT}
      --app-path ${CMAKE_CURRENT_SOURCE_DIR}
      --build-path ${CMAKE_BINARY_DIR}
      --toolchain-path ${VSCODE_ARM_TOOLCHAIN_PATH}
      --gdb-path ${CMAKE_GDB}
      --device ${VSCODE_JLINK_DEVICE_FULL}
      --launch-json ${ZEPHYR_BASE}/../.vscode/launch.json
    COMMAND ${CMAKE_COMMAND} -E touch ${VSCODE_SETUP_STAMP}
    DEPENDS ${CMAKE_BINARY_DIR}/zephyr/zephyr.elf ${VSCODE_SETUP_SCRIPT}
    COMMENT "Run .vscode/setup.py to update launch.json and build symlink"
    VERBATIM
  )
  add_custom_target(vscode_setup_symlink ALL DEPENDS ${VSCODE_SETUP_STAMP})
endif()
