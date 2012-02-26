# - Try to find SDL
# Once done, this will define
#
# SDL_FOUND, if false, do not try to link to SDL
# SDL_INCLUDE_DIRS, where to find SDL.h
#

if(NOT SDL_FOUND)
  include(PkgUtils)
  findpkg_begin(SDL)

  define_find_pkg(SDL HEADER_ONLY
	PKG_CONFIG_NAME sdl
	HEADER_HINTS SDL.h
	HEADER_SUFFIXES SDL)

  findpkg_finish(SDL)
endif()
