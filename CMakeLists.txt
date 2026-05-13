cmake_minimum_required (VERSION 3.27)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project (Bounce VERSION 1.0.0)

# Libraries
include(FetchContent)

FetchContent_Declare(
  TeaTimeEngine
  GIT_REPOSITORY https://github.com/SammyTeaTime/TeaTimeEngine
  GIT_TAG        1.0.0
  GIT_SHALLOW    true
)
FetchContent_MakeAvailable(TeaTimeEngine)

# Setup project files
include_directories("Include")

set(SOURCES "Source/Main.cpp")
add_executable(Bounce ${SOURCES})
add_subdirectory("Source/GameEntities")

target_compile_features(Bounce PRIVATE cxx_std_20)
target_link_libraries(Bounce PRIVATE TeaTimeEngine::TeaTimeEngine)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT 
    Bounce)

add_custom_target(CopyAssets ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/Assets"
        "${CMAKE_CURRENT_BINARY_DIR}/Assets"
    COMMENT "Ensuring Assets are copied every build"
)
add_dependencies(Bounce CopyAssets)

add_custom_target(CopyConfig ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/Config"
        "${CMAKE_CURRENT_BINARY_DIR}/Config"
    COMMENT "Ensuring Config files are copied every build"
)
add_dependencies(Bounce CopyConfig)