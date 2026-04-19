# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)
set(BOARD fk743m5_xih6)
set(BOARD_FLASH_RUNNER jlink)
set(BOARD_DEBUG_RUNNER jlink)
# Keep board-provided --device and append J-Link external flash loader details.
# Cache-provided BOARD_RUNNER_ARGS_jlink has highest precedence in Zephyr.
set(BOARD_RUNNER_ARGS_jlink
    "--loader=BankAddr=0x90000000&Loader=CLK@PF10_nCS@PG6_D0@PF8_D1@PF9_D2@PF7_D3@PF6"
    CACHE STRING "Extra J-Link runner args" FORCE)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(98-cpp LANGUAGES CXX)

FILE(GLOB app_sources src/*.c src/*.cpp)
target_sources(app PRIVATE ${app_sources})

# Relocate app code/rodata to external flash (XIP, no copy).
# External flash memory-mapped setup is handled by Zephyr when CONFIG_STM32_MEMMAP=y.
zephyr_code_relocate(FILES $<TARGET_PROPERTY:app,SOURCES> LOCATION SDRAM1_DATA_BSS)
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

# copy compile_commands.json for vscode
add_custom_command(
    TARGET app
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_BINARY_DIR}/compile_commands.json
        ${ZEPHYR_BASE}/../.vscode/compile_commands.json
    COMMENT "Copy compile_commands.json for vscode"
)
