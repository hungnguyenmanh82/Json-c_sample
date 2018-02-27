#Licensed under the MIT license. See LICENSE file in the project root for full license information.

cmake_minimum_required(VERSION 2.8.7)
cmake_policy(SET CMP0048 NEW)
project(testJson VERSION 0.13.99)


include(CheckSymbolExists)

check_symbol_exists(strtoll "stdlib.h" HAVE_STRTOLL)

set(cmake_strtoll "strtoll")
if (NOT HAVE_STRTOLL)
  # Use _strtoi64 if strtoll is not available.
  check_symbol_exists(_strtoi64 stdlib.h have_strtoi64)
  if (have_strtoi64)
    set(HAVE_STRTOLL 1)
    set(cmake_strtoll "_strtoi64")
    # could do the same for strtoull, if needed
  endif ()
endif ()



if(MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4100 /wd4996 /wd4244 /wd4706 /wd4702 /wd4127 /wd4701")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /wd4100 /wd4996 /wd4244 /wd4706 /wd4702 /wd4127 /wd4701")
  set(cmake_create_config 1)
elseif(MINGW)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -D_GNU_SOURCE=1")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror -D_GNU_SOURCE=1")
  if (MSYS OR CMAKE_GENERATOR STREQUAL "Unix Makefiles")
    execute_process(COMMAND echo ${CMAKE_CURRENT_SOURCE_DIR} WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
    execute_process(COMMAND sh autogen.sh WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
    execute_process(COMMAND sh ./configure WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
    file(COPY ./config.h DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/include/)
    file(COPY ./json_config.h DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/include/)
  else()
    set(cmake_create_config 1)
  endif()
elseif(UNIX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror -D_GNU_SOURCE")
  execute_process(COMMAND echo ${CMAKE_CURRENT_SOURCE_DIR} WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
  execute_process(COMMAND sh autogen.sh WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
  execute_process(COMMAND ./configure WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
  file(COPY ./config.h DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/include/)
  file(COPY ./json_config.h DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/include/)
endif()

if (cmake_create_config)
  file(REMOVE ./config.h)  # make sure any stale one is gone
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.win32 ${CMAKE_CURRENT_BINARY_DIR}/include/config.h)
  file(COPY ./json_config.h.win32 DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/include/)
  file(RENAME ${CMAKE_CURRENT_BINARY_DIR}/include/json_config.h.win32 ${CMAKE_CURRENT_BINARY_DIR}/include/json_config.h)
endif ()

include_directories(${CMAKE_CURRENT_BINARY_DIR}/include ../json-c .)

#get all header *.h file
file(GLOB_RECURSE HEADER_JSON_FILES ../json-c/*.h)

#get all source *.c file 
file(GLOB_RECURSE SRC_JSON_FILES ../json-c/*.c)
#folder json
set(SRC_JSON_FOLDER ../json-c)

set(JSON_C_HEADERS
    ${CMAKE_CURRENT_BINARY_DIR}/include/config.h 
    ${CMAKE_CURRENT_BINARY_DIR}/include/json_config.h 
	${HEADER_JSON_FILES}
)

add_executable(testJsonInt ./test_int_add.c     
		${SRC_JSON_FILES})

add_executable(testParse ./test_parse.c     
		${SRC_JSON_FILES})


set_property(TARGET json-c PROPERTY C_STANDARD 99)
set_property(TARGET json-c-static PROPERTY C_STANDARD 99)
set_target_properties(json-c-static PROPERTIES OUTPUT_NAME json-c)



if (UNIX)
	set(prefix ${CMAKE_INSTALL_PREFIX})
	set(exec_prefix ${CMAKE_INSTALL_PREFIX}/bin)
	set(libdir ${CMAKE_INSTALL_PREFIX}/lib)
	set(includedir ${CMAKE_INSTALL_PREFIX}/include)
	set(VERSION ${PROJECT_VERSION})
	configure_file(json-c.pc.in json-c.pc @ONLY)
	set(INSTALL_PKGCONFIG_DIR "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" CACHE PATH "Installation directory for pkgconfig (.pc) files")
	install(FILES ${CMAKE_BINARY_DIR}/json-c.pc DESTINATION "${INSTALL_PKGCONFIG_DIR}")
endif ()
