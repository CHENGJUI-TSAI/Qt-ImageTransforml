# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles\\ImageTransforml_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\ImageTransforml_autogen.dir\\ParseCache.txt"
  "ImageTransforml_autogen"
  )
endif()
