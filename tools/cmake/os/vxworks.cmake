# VxWorks compilation support for EtcPal
set(VXWORKS_SOURCE_DIR "" CACHE STRING "Location of the VxWorks libraries, e.g. \"C:\\WindRiver\"")
if(NOT VXWORKS_SOURCE_DIR)
  message(FATAL_ERROR "You must provide the option VXWORKS_SOURCE_DIR to indicate the location of your VxWorks libraries.")
endif()

# Include the debug versions of the VxWorks libs if a Debug configuration is specified.
# I think there's probably a better way of doing this and I'm missing something here.
if(CMAKE_BUILD_TYPE STREQUAL Debug)
  set(VXWORKS_BOARD_INT_DIR debug)
else()
  set(VXWORKS_BOARD_INT_DIR release)
endif()

