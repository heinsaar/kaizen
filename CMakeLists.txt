# CMakeList.txt : CMake project for Kaizen.

cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("kaizen")

################################### Add source to this project's executable.
add_executable ( kaizen
    "test_kaizen.cpp" "test_kaizen.h" "containers/vector.h" "tests/test_vector.h" "utils.h"
    "containers/list.h" "tests/test_list.h"
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET kaizen PROPERTY CXX_STANDARD 20)
endif()

################################### Single header generation

add_custom_command(
    OUTPUT  kaizen.h
    COMMAND python3 ${CMAKE_SOURCE_DIR}/make_kaizen.py
    DEPENDS containers/list.h containers/vector.h
    COMMENT "GENERATING kaizen.h"
)

add_custom_target(generate_kaizen_main_header ALL DEPENDS kaizen.h)

# TODO: Add tests and install targets if needed.
