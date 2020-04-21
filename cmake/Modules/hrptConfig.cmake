INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_HRPT hrpt)

FIND_PATH(
    HRPT_INCLUDE_DIRS
    NAMES hrpt/api.h
    HINTS $ENV{HRPT_DIR}/include
        ${PC_HRPT_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    HRPT_LIBRARIES
    NAMES gnuradio-hrpt
    HINTS $ENV{HRPT_DIR}/lib
        ${PC_HRPT_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
          )

include("${CMAKE_CURRENT_LIST_DIR}/hrptTarget.cmake")

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(HRPT DEFAULT_MSG HRPT_LIBRARIES HRPT_INCLUDE_DIRS)
MARK_AS_ADVANCED(HRPT_LIBRARIES HRPT_INCLUDE_DIRS)
