set(SFML_VERSION 2.6.x)
set(IMGUI_VERSION v1.90)

include(FetchContent)

# Declare Git dependencies
FetchContent_Declare(SFML GIT_REPOSITORY https://github.com/SFML/SFML.git GIT_TAG ${SFML_VERSION})
FetchContent_Declare(ImGUI GIT_REPOSITORY https://github.com/ocornut/imgui GIT_TAG ${IMGUI_VERSION})
FetchContent_Declare(ImGUI-SFML GIT_REPOSITORY https://github.com/SFML/imgui-sfml.git GIT_TAG ${SFML_VERSION})

# Disable SFML networking
option(SFML_BUILD_NETWORK "Build network" OFF)

FetchContent_MakeAvailable(SFML)

FetchContent_MakeAvailable(ImGUI)

# Configure ImGUI-SFML
set(IMGUI_DIR ${imgui_SOURCE_DIR})
option(IMGUI_SFML_FIND_SFML "Use find_package to find SFML" OFF)
option(IMGUI_SFML_IMGUI_DEMO "Build imgui_demo.cpp" ON)

FetchContent_MakeAvailable(ImGUI-SFML)
