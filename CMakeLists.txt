cmake_minimum_required(VERSION 3.16)
project(sfml-test LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

# Fetch SFML from Git
include(FetchContent)
FetchContent_Declare(SFML GIT_REPOSITORY https://github.com/SFML/SFML.git GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(sfml-test src/main.cpp
        src/core/entity.h src/core/entity.cpp
        src/core/flags.h
        src/core/game.h src/core/game.cpp
        src/core/input_manager.h src/core/input_manager.cpp
        src/core/level.h src/core/level.cpp
        src/core/utilities.h

        src/entities/player.h src/entities/player.cpp
        src/entities/tile.h src/entities/tile.cpp

        src/exceptions/load_file_exception.h

        src/graphics/animation.h
        src/graphics/animation_controller.h src/graphics/animation_controller.cpp
        src/graphics/texture_sheet.h src/graphics/texture_sheet.cpp)
target_link_libraries(sfml-test PRIVATE sfml-graphics)
target_compile_features(sfml-test PRIVATE cxx_std_17)

add_executable(level-editor src/level-editor/main.cpp
        src/level-editor/editor.h src/level-editor/editor.cpp
        src/level-editor/storable_tile.h src/level-editor/storable_tile.cpp

        src/core/entity.h src/core/entity.cpp
        src/core/input_manager.h src/core/input_manager.cpp
        src/core/utilities.h

        src/entities/tile.h src/entities/tile.cpp

        src/exceptions/load_file_exception.h

        src/graphics/texture_sheet.h src/graphics/texture_sheet.cpp)
target_link_libraries(level-editor PRIVATE sfml-graphics)
target_compile_features(level-editor PRIVATE cxx_std_17)

if (WIN32)
    add_custom_command(
            TARGET sfml-test
            COMMENT "Copy OpenAL DLL"
            PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:sfml-test>
            VERBATIM)

    add_custom_command(
            TARGET level-editor
            COMMENT "Copy OpenAL DLL"
            PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:level-editor>
            VERBATIM)
endif ()

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

install(TARGETS sfml-test)
