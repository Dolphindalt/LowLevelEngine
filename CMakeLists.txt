cmake_minimum_required (VERSION 3.0)

enable_language(CXX)
set(CMAKE_CXX_FLAGS "-g")

project (Engine)

include_directories(.)

set (Engine_VERSION_MAJOR 0)
set (Engine_VERSION_MINOR 1)

file(GLOB_RECURSE Engine_SOURCES "src/*.cpp")
file(GLOB_RECURSE Engine_TESTS "test/*.cpp")
file(GLOB_RECURSE Engine_HEADERS "src/*.h")

set(Engine_INCLUDE_DIRS "")
foreach(_headerFile ${Engine_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list(APPEND Engine_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES Engine_INCLUDE_DIRS)

add_library(AppLib SHARED ${Engine_SOURCES})
target_include_directories(AppLib PRIVATE ${Engine_INCLUDE_DIRS})
install(TARGETS AppLib
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

set(MAIN "src/game/main.cpp")

add_executable(Game ${MAIN})
set_target_properties(Game PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(Game PRIVATE ${Engine_INCLUDE_DIRS})
target_link_libraries(Game AppLib GL GLEW SDL2)

add_executable(Test ${Engine_TESTS})
target_compile_definitions(Test PRIVATE TEST_BUILD)
set_target_properties(Test PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(Test PRIVATE ${Engine_INCLUDE_DIRS})
target_link_libraries(Test AppLib GL GLEW SDL2)