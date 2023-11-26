# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\EventX_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\EventX_autogen.dir\\ParseCache.txt"
  "EventX_autogen"
  )
endif()
