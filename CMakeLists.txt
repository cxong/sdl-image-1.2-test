cmake_minimum_required(VERSION 2.8)
project(sdl_image_test)

find_package(SDL REQUIRED)
find_package(SDL_image REQUIRED)

execute_process(
	COMMAND "sh" "sdl-config" "--libs"
	OUTPUT_VARIABLE SDL_LDFLAGS
	OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(
	COMMAND "sh" "sdl-config" "--cflags"
	OUTPUT_VARIABLE SDL_CFLAGS
	OUTPUT_STRIP_TRAILING_WHITESPACE)

include_directories(${SDL_INCLUDE_DIR} ${SDLIMAGE_INCLUDE_DIR})

if(APPLE)
  set_source_files_properties(SDLMain.m
    PROPERTIES LANGUAGE C)
  set(SOURCES_EXTRA SDLMain.m SDLMain.h)
endif()
add_executable(sdl_image_test main.c ${SOURCES_EXTRA})
target_link_libraries(sdl_image_test
  ${SDL_LIBRARY} ${SDL_IMAGE_LIBRARY})
