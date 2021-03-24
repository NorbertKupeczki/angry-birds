cmake_minimum_required(VERSION 3.14)
project(AngryBirdsSFML)

set(CMAKE_CXX_STANDARD 14)

if(WIN32)
    set(SFML_STATIC_LIBRARIES TRUE)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
endif()


find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)
set(SOURCE_FILES src/main.cpp src/Game.cpp src/Game.h src/Vector2.h src/Vector2.cpp src/Pig.cpp src/Pig.h src/GameObject.cpp src/GameObject.h src/Slingshot.cpp src/Slingshot.h src/Buttons.cpp src/Buttons.h src/Birds.cpp src/Birds.h src/Options.cpp src/Options.h)
add_executable(AngryBirdsSFML ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")

target_link_libraries (AngryBirdsSFML sfml-graphics sfml-window sfml-system sfml-network sfml-audio)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Data/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Data/)