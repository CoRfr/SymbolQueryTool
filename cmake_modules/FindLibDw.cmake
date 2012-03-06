# - Try to find libdw (elfutils)
# Once done this will define
#
#  LIBDW_FOUND - system has libdwarf
#  LIBDW_INCLUDE_DIRS - the libdwarf include directory
#  LIBDW_LIBRARIES - Link these to use libdwarf
#  LIBDW_DEFINITIONS - Compiler switches required for using libdwarf
#

# Locate libelf library at first
if (NOT LIBELF_FOUND)
   find_package (LibElf REQUIRED)
endif (NOT LIBELF_FOUND)

if (LIBDW_LIBRARIES AND LIBDW_INCLUDE_DIRS)
  set (LibDwarf_FIND_QUIETLY TRUE)
endif (LIBDW_LIBRARIES AND LIBDW_INCLUDE_DIRS)

find_path (LIBDW_INCLUDE_DIRS
    NAMES
      libdw.h
    PATHS
      /usr/include
      /usr/include/elfutils
      /usr/local/include
      /usr/local/include/elfutils
      /opt/local/include
      /opt/local/include/elfutils
      /sw/include
      /sw/include/elfutils
      ENV CPATH)

find_library (LIBDW_LIBRARIES
    NAMES
      dw
    PATHS
      /usr/lib
      /usr/local/lib
      /opt/local/lib
      /sw/lib
      ENV LIBRARY_PATH
      ENV LD_LIBRARY_PATH)

include (FindPackageHandleStandardArgs)


# handle the QUIETLY and REQUIRED arguments and set LIBDW_FOUND to TRUE
# if all listed variables are TRUE
FIND_PACKAGE_HANDLE_STANDARD_ARGS(LibDwarf DEFAULT_MSG
    LIBDW_LIBRARIES
    LIBDW_INCLUDE_DIRS)


mark_as_advanced(LIBDW_INCLUDE_DIRS LIBDW_LIBRARIES)
