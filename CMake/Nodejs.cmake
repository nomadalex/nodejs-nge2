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
  foreach(arg ${ARGN})
	if(${arg} STREQUAL "BIN_VERSION")
	  set(BIN_VERSION true)
	endif()
  endforeach()

  set(NODE_ROOT "" CACHE PATH "Path to nodejs root dir")
  if(NOT NODE_ROOT)
	if($ENV{NODE_ROOT})
	  set(NODE_ROOT $ENV{NODE_ROOT} CACHE PATH "Path to nodejs root dir" FORCE)
	else()
	  find_program(node_exe_path node)
	  mark_as_advanced(node_exe_path)
	  get_filename_component(node_dir ${node_exe_path} PATH)
	  if(node_exe_path)
		if(NOT WIN32)
		  get_filename_component(node_dir ${node_dir}/.. ABSOLUTE)
		endif()
		set(NODE_ROOT ${node_dir} CACHE PATH "Path to nodejs root dir" FORCE)
	  else()
		message(FATAL_ERROR "Can not find nodejs!")
	  endif()
	endif()
  endif()

  message(STATUS "Find node root : ${NODE_ROOT}")

  if(WIN32)
	if(BIN_VERSION)
	  link_directories(${NODE_ROOT}/lib)
	  include_directories(${NODE_ROOT}/include/v8 ${NODE_ROOT}/include/uv ${NODE_ROOT}/include)
	else()
	  link_directories(${NODE_ROOT}/Release/lib ${NODE_ROOT}/Release)
	  include_directories(${NODE_ROOT}/deps/v8/include ${NODE_ROOT}/deps/uv/include ${NODE_ROOT}/src)
	endif()
  else()
	link_directories(${NODE_ROOT}/lib)
	include_directories(${NODE_ROOT}/include/node)
  endif()

  if(Linux)
	add_definitions(-D_GNU_SOURCE)
  endif()

  add_definitions(-D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64)
endmacro()

function(add_node_extension target)
  add_library(${target} SHARED ${ARGN})
  if(WIN32)
	set_target_properties(${target} PROPERTIES SUFFIX ".node")
	target_link_libraries(${target} node)
  endif()
  if(NOT WIN32)
	# simulate node-waf behaviour, copy target to per-configure directory e.g. Debug and Release
	get_target_property(LIB_LOCATION ${target} LOCATION)
	add_custom_command(
  	  TARGET ${target}
  	  POST_BUILD
  	  COMMAND "${CMAKE_COMMAND}" -E copy
  	  "${LIB_LOCATION}"
  	  "${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/${target}.node"
  	  )
  endif()
endfunction()
