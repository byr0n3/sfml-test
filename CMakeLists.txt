cmake_minimum_required(VERSION 3.16)
project(sfml-test LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

# Fetch SFML from Git
include(FetchContent)
FetchContent_Declare(SFML GIT_REPOSITORY https://github.com/SFML/SFML.git GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(sfml-test src/main.cpp)
target_link_libraries(sfml-test PRIVATE sfml-graphics)
target_compile_features(sfml-test PRIVATE cxx_std_17)

if (WIN32)
    add_custom_command(
            TARGET sfml-test
            COMMENT "Copy OpenAL DLL"
            PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:CMakeSFMLProject>
            VERBATIM)
endif ()

install(TARGETS sfml-test)
