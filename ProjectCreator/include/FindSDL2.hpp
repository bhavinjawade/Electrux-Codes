//
// Created by Electrux Redsworth on 9/19/17.
//

#ifndef PROJECTCREATOR_FINDSDL2_HPP
#define PROJECTCREATOR_FINDSDL2_HPP

#include <string>

const std::string FINDSDL2FILESTR = "# Locate SDL2 library\n"
	"# This module defines\n"
	"# SDL2_LIBRARY, the name of the library to link against\n"
	"# SDL2_FOUND, if false, do not try to link to SDL2\n"
	"# SDL2_INCLUDE_DIR, where to find SDL.h\n"
	"#\n"
	"# This module responds to the the flag:\n"
	"# SDL2_BUILDING_LIBRARY\n"
	"# If this is defined, then no SDL2main will be linked in because\n"
	"# only applications need main().\n"
	"# Otherwise, it is assumed you are building an application and this\n"
	"# module will attempt to locate and set the the proper link flags\n"
	"# as part of the returned SDL2_LIBRARY variable.\n"
	"#\n"
	"# Don't forget to include SDLmain.h and SDLmain.m your project for the\n"
	"# OS X framework based version. (Other versions link to -lSDL2main which\n"
	"# this module will try to find on your behalf.) Also for OS X, this\n"
	"# module will automatically add the -framework Cocoa on your behalf.\n"
	"#\n"
	"#\n"
	"# Additional Note: If you see an empty SDL2_LIBRARY_TEMP in your configuration\n"
	"# and no SDL2_LIBRARY, it means CMake did not find your SDL2 library\n"
	"# (SDL2.dll, libsdl2.so, SDL2.framework, etc).\n"
	"# Set SDL2_LIBRARY_TEMP to point to your SDL2 library, and configure again.\n"
	"# Similarly, if you see an empty SDL2MAIN_LIBRARY, you should set this value\n"
	"# as appropriate. These values are used to generate the final SDL2_LIBRARY\n"
	"# variable, but when these values are unset, SDL2_LIBRARY does not get created.\n"
	"#\n"
	"#\n"
	"# $SDL2DIR is an environment variable that would\n"
	"# correspond to the ./configure --prefix=$SDL2DIR\n"
	"# used in building SDL2.\n"
	"# l.e.galup  9-20-02\n"
	"#\n"
	"# Modified by Eric Wing.\n"
	"# Added code to assist with automated building by using environmental variables\n"
	"# and providing a more controlled/consistent search behavior.\n"
	"# Added new modifications to recognize OS X frameworks and\n"
	"# additional Unix paths (FreeBSD, etc).\n"
	"# Also corrected the header search path to follow \"proper\" SDL guidelines.\n"
	"# Added a search for SDL2main which is needed by some platforms.\n"
	"# Added a search for threads which is needed by some platforms.\n"
	"# Added needed compile switches for MinGW.\n"
	"#\n"
	"# On OSX, this will prefer the Framework version (if found) over others.\n"
	"# People will have to manually change the cache values of\n"
	"# SDL2_LIBRARY to override this selection or set the CMake environment\n"
	"# CMAKE_INCLUDE_PATH to modify the search paths.\n"
	"#\n"
	"# Note that the header path has changed from SDL2/SDL.h to just SDL.h\n"
	"# This needed to change because \"proper\" SDL convention\n"
	"# is #include \"SDL.h\", not <SDL2/SDL.h>. This is done for portability\n"
	"# reasons because not all systems place things in SDL2/ (see FreeBSD).\n"
	"\n"
	"#=============================================================================\n"
	"# Copyright 2003-2009 Kitware, Inc.\n"
	"#\n"
	"# Distributed under the OSI-approved BSD License (the \"License\");\n"
	"# see accompanying file Copyright.txt for details.\n"
	"#\n"
	"# This software is distributed WITHOUT ANY WARRANTY; without even the\n"
	"# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n"
	"# See the License for more information.\n"
	"#=============================================================================\n"
	"# (To distribute this file outside of CMake, substitute the full\n"
	"#  License text for the above reference.)\n"
	"\n"
	"SET(SDL2_SEARCH_PATHS\n"
	"\t~/Library/Frameworks\n"
	"\t/Library/Frameworks\n"
	"\t/usr/local\n"
	"\t/usr\n"
	"\t/sw # Fink\n"
	"\t/opt/local # DarwinPorts\n"
	"\t/opt/csw # Blastwave\n"
	"\t/opt\n"
	")\n"
	"\n"
	"FIND_PATH(SDL2_INCLUDE_DIR SDL.h\n"
	"\tHINTS\n"
	"\t$ENV{SDL2DIR}\n"
	"\tPATH_SUFFIXES include/SDL2 include\n"
	"\tPATHS ${SDL2_SEARCH_PATHS}\n"
	")\n"
	"\n"
	"FIND_LIBRARY(SDL2_LIBRARY_TEMP\n"
	"\tNAMES SDL2\n"
	"\tHINTS\n"
	"\t$ENV{SDL2DIR}\n"
	"\tPATH_SUFFIXES lib64 lib\n"
	"\tPATHS ${SDL2_SEARCH_PATHS}\n"
	")\n"
	"\n"
	"IF(NOT SDL2_BUILDING_LIBRARY)\n"
	"\tIF(NOT ${SDL2_INCLUDE_DIR} MATCHES \".framework\")\n"
	"\t\t# Non-OS X framework versions expect you to also dynamically link to\n"
	"\t\t# SDL2main. This is mainly for Windows and OS X. Other (Unix) platforms\n"
	"\t\t# seem to provide SDL2main for compatibility even though they don't\n"
	"\t\t# necessarily need it.\n"
	"\t\tFIND_LIBRARY(SDL2MAIN_LIBRARY\n"
	"\t\t\tNAMES SDL2main\n"
	"\t\t\tHINTS\n"
	"\t\t\t$ENV{SDL2DIR}\n"
	"\t\t\tPATH_SUFFIXES lib64 lib\n"
	"\t\t\tPATHS ${SDL2_SEARCH_PATHS}\n"
	"\t\t)\n"
	"\tENDIF(NOT ${SDL2_INCLUDE_DIR} MATCHES \".framework\")\n"
	"ENDIF(NOT SDL2_BUILDING_LIBRARY)\n"
	"\n"
	"# SDL2 may require threads on your system.\n"
	"# The Apple build may not need an explicit flag because one of the\n"
	"# frameworks may already provide it.\n"
	"# But for non-OSX systems, I will use the CMake Threads package.\n"
	"IF(NOT APPLE)\n"
	"\tFIND_PACKAGE(Threads)\n"
	"ENDIF(NOT APPLE)\n"
	"\n"
	"# MinGW needs an additional library, mwindows\n"
	"# It's total link flags should look like -lmingw32 -lSDL2main -lSDL2 -lmwindows\n"
	"# (Actually on second look, I think it only needs one of the m* libraries.)\n"
	"IF(MINGW)\n"
	"\tSET(MINGW32_LIBRARY mingw32 CACHE STRING \"mwindows for MinGW\")\n"
	"ENDIF(MINGW)\n"
	"\n"
	"IF(SDL2_LIBRARY_TEMP)\n"
	"\t# For SDL2main\n"
	"\tIF(NOT SDL2_BUILDING_LIBRARY)\n"
	"\t\tIF(SDL2MAIN_LIBRARY)\n"
	"\t\t\tSET(SDL2_LIBRARY_TEMP ${SDL2MAIN_LIBRARY} ${SDL2_LIBRARY_TEMP})\n"
	"\t\tENDIF(SDL2MAIN_LIBRARY)\n"
	"\tENDIF(NOT SDL2_BUILDING_LIBRARY)\n"
	"\n"
	"\t# For OS X, SDL2 uses Cocoa as a backend so it must link to Cocoa.\n"
	"\t# CMake doesn't display the -framework Cocoa string in the UI even\n"
	"\t# though it actually is there if I modify a pre-used variable.\n"
	"\t# I think it has something to do with the CACHE STRING.\n"
	"\t# So I use a temporary variable until the end so I can set the\n"
	"\t# \"real\" variable in one-shot.\n"
	"\tIF(APPLE)\n"
	"\t\tSET(SDL2_LIBRARY_TEMP ${SDL2_LIBRARY_TEMP} \"-framework Cocoa\")\n"
	"\tENDIF(APPLE)\n"
	"\n"
	"\t# For threads, as mentioned Apple doesn't need this.\n"
	"\t# In fact, there seems to be a problem if I used the Threads package\n"
	"\t# and try using this line, so I'm just skipping it entirely for OS X.\n"
	"\tIF(NOT APPLE)\n"
	"\t\tSET(SDL2_LIBRARY_TEMP ${SDL2_LIBRARY_TEMP} ${CMAKE_THREAD_LIBS_INIT})\n"
	"\tENDIF(NOT APPLE)\n"
	"\n"
	"\t# For MinGW library\n"
	"\tIF(MINGW)\n"
	"\t\tSET(SDL2_LIBRARY_TEMP ${MINGW32_LIBRARY} ${SDL2_LIBRARY_TEMP})\n"
	"\tENDIF(MINGW)\n"
	"\n"
	"\t# Set the final string here so the GUI reflects the final state.\n"
	"\tSET(SDL2_LIBRARY ${SDL2_LIBRARY_TEMP} CACHE STRING \"Where the SDL2 Library can be found\")\n"
	"\t# Set the temp variable to INTERNAL so it is not seen in the CMake GUI\n"
	"\tSET(SDL2_LIBRARY_TEMP \"${SDL2_LIBRARY_TEMP}\" CACHE INTERNAL \"\")\n"
	"ENDIF(SDL2_LIBRARY_TEMP)\n"
	"\n"
	"INCLUDE(FindPackageHandleStandardArgs)\n"
	"\n"
	"FIND_PACKAGE_HANDLE_STANDARD_ARGS(SDL2 REQUIRED_VARS SDL2_LIBRARY SDL2_INCLUDE_DIR)";

#endif //PROJECTCREATOR_FINDSDL2_HPP
