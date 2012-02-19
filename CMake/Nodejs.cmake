# Following macros are exported
#
# - prepare_nodejs()
# This macro prepare nodejs env vars.
#
# Following functions are exported
#
# - add_node_extension(target ...)
# This function add node extension by srcs follow by target.

macro(prepare_nodejs)
  set(NODE_ROOT "" CACHE PATH "Path to nodejs root dir")
  if(NOT NODE_ROOT)
	if($ENV{NODE_ROOT})
	  set(NODE_ROOT $ENV{NODE_ROOT} FORCE)
	else()
	  if(UNIX)
		find_program(node_exe_path node)
		if(node_exe_path)
		  set(NODE_ROOT ${node_exe_path}/.. FORCE)
		endif()
	  endif()
	endif()
  endif()

  if(WIN32)
	link_directories(${NODE_ROOT}/Release/lib ${NODE_ROOT}/Release)
	include_directories(${NODE_ROOT}/deps/v8/include ${NODE_ROOT}/deps/uv/include ${NODE_ROOT}/src)
  else()
	link_directories(${NODE_ROOT}/lib)
	include_directories(${NODE_ROOT}/include)
  endif()

  if(Linux)
	add_definitions(-D_GNU_SOURCE)
  endif()

  add_definitions(-D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64)
endmacro()

function(add_node_extension target)
  add_library(${target} SHARED ${ARGN})
  target_link_libraries(${target} node)
  set_target_properties(${target} PROPERTIES SUFFIX ".node")
endfunction()
