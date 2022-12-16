# Locate the IRRKLANG library
#
# This module defines the following variables:
#
# IRRKLANG_LIBRARY the name of the library;
# IRRKLANG_INCLUDE_DIR where to find IRRKLANG include files.
# IRRKLANG_FOUND true if both the IRRKLANG_LIBRARY and IRRKLANG_INCLUDE_DIR have been found.
#
# To help locate the library and include file, you can define a
# variable called IRRKLANG_ROOT which points to the root of the IRRKLANG library
# installation.
#
# default search dirs
# 

set( _IRRKLANG_HEADER_SEARCH_DIRS
"/usr/include"
"/usr/local/include"
"${CMAKE_SOURCE_DIR}/include"
"C:/Program Files (x86)/IRRKLANG/include" )
set( _IRRKLANG_LIB_SEARCH_DIRS
"/usr/lib"
"/usr/local/lib"
"${CMAKE_SOURCE_DIR}/lib"
"C:/Program Files (x86)/IRRKLANG/lib-msvc110" )

# Check environment for root search directory
set( _IRRKLANG_ENV_ROOT $ENV{IRRKLANG_ROOT} )
if( NOT IRRKLANG_ROOT AND _IRRKLANG_ENV_ROOT )
	set(IRRKLANG_ROOT ${_IRRKLANG_ENV_ROOT} )
endif()

# Put user specified location at beginning of search
if( IRRKLANG_ROOT )
	list( INSERT _IRRKLANG_HEADER_SEARCH_DIRS 0 "${IRRKLANG_ROOT}" )
	list( INSERT _IRRKLANG_LIB_SEARCH_DIRS 0 "${IRRKLANG_ROOT}/lib")
endif()

# Search for the header
FIND_PATH(IRRKLANG_INCLUDE_DIR "irrKlang.h" PATHS ${_IRRKLANG_HEADER_SEARCH_DIRS} )

FIND_LIBRARY(IRRKLANG_LIBRARY NAMES irrklang
PATHS ${_IRRKLANG_LIB_SEARCH_DIRS} )
FIND_PACKAGE_HANDLE_STANDARD_ARGS(Irrklang DEFAULT_MSG
IRRKLANG_LIBRARY IRRKLANG_INCLUDE_DIR)
