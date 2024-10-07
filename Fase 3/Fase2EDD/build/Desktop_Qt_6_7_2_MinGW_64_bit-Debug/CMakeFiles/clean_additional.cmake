# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Fase2EDD_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Fase2EDD_autogen.dir\\ParseCache.txt"
  "Fase2EDD_autogen"
  )
endif()
