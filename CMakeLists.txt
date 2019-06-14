cmake_minimum_required (VERSION 3.0)

enable_language(CXX)
set(CMAKE_CXX_FLAGS "-g")

project (Engine)

set (Engine_VERSION_MAJOR 0)
set (Engine_VERSION_MINOR 1)

file(GLOB_RECURSE Engine_SOURCES "src/*.cpp")
file(GLOB_RECURSE Engine_HEADERS "src/*.h")

set (Engine_INCLUDE_DIRS ".")
foreach (_headerFile ${Engine_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND Engine_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES Engine_INCLUDE_DIRS)

add_executable(GameExe ${Engine_SOURCES})
set_target_properties(GameExe PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(GameExe PRIVATE ${Engine_INCLUDE_DIRS})
target_link_libraries(GameExe GL GLEW SDL2)