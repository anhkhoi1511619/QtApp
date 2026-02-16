# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\VPTSimulator_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\VPTSimulator_autogen.dir\\ParseCache.txt"
  "VPTSimulator_autogen"
  )
endif()
