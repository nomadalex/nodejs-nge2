# - Try to find libnge2
# Once done, this will define
#
#  NGE2_FOUND - system has libnge2
#  NGE2_INCLUDE_DIRS - the libnge2 include directories
#  NGE2_LIBRARIES - link these to use libnge2

if(NOT NGE2_FOUND)
  include(PkgUtils)
  findpkg_begin(NGE2)

  define_find_pkg(NGE2
	LIBRARY_HINTS nge2 libnge2
	HEADER_HINTS libnge2.h)

  findpkg_finish(NGE2)
endif()
