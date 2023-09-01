# CMakeList.txt : CMake project for Kaizen.

cmake_minimum_required(VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if(POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project("kaizen")

################################### Delete kaizen.h if it exists

add_custom_target(delete_kaizen_header
    COMMAND ${CMAKE_COMMAND} -E remove -f ${CMAKE_CURRENT_BINARY_DIR}/kaizen.h
    COMMENT "DELETING kaizen.h"
)

################################### Single header generation

add_custom_command(
    OUTPUT  kaizen.h
    COMMAND python3 ${CMAKE_SOURCE_DIR}/make_kaizen.py
    DEPENDS datas/list.h datas/vector.h datas/array.h
    COMMENT "GENERATING kaizen.h"
)

add_custom_target(generate_kaizen_header ALL DEPENDS kaizen.h)
add_dependencies(generate_kaizen_header delete_kaizen_header)

################################### Add source to this project's executable.
add_executable(kaizen "test_kaizen.cpp"
    "datas/type_traits.h" "datas/string.h"
    "datas/vector.h" "datas/list.h" "datas/array.h" "datas/deque.h"
    "functions/utils.h"
    "test_kaizen.h" "tests/test_vector.h" "tests/test_list.h" "tests/test_deque.h" "tests/test_utils.h"
    "tests/test_string.h"
   )

# Set a dependency on the custom target to ensure it runs before the kaizen executable is built
add_dependencies(kaizen generate_kaizen_header)

if(CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET kaizen PROPERTY CXX_STANDARD 20)
endif()

# Copy the automated build-and-run scripts
if(UNIX)
  configure_file(${CMAKE_SOURCE_DIR}/runbuild_linx.sh ${CMAKE_BINARY_DIR}/runbuild_linx.sh COPYONLY)
  file(READ ${CMAKE_BINARY_DIR}/runbuild_linx.sh CONTENTS)
  string(REPLACE "\r\n" "\n" FIXED_CONTENTS "${CONTENTS}")       # Replace CRLF with LF
  string(REPLACE "\r"   "\n" FIXED_CONTENTS "${FIXED_CONTENTS}") # Replace CR   with LF (in case the file uses old Mac line endings)
  file(WRITE ${CMAKE_BINARY_DIR}/runbuild_linx.sh "${FIXED_CONTENTS}")
endif()

if(WIN32)
    configure_file(${CMAKE_SOURCE_DIR}/runbuild_win.bat ${CMAKE_BINARY_DIR}/runbuild_win.bat COPYONLY)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

# TODO: Add tests and install targets if needed.
