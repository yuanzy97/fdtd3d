file(GLOB_RECURSE GRID_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE CUDA_GRID_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cu")

if ("${CUDA_ENABLED}")
  list(FILTER GRID_SOURCES EXCLUDE REGEX ".*/Grid.cpp$")
  add_library (Grid ${GRID_SOURCES} ${CUDA_GRID_SOURCES})
  set_target_properties (Grid PROPERTIES CUDA_SEPARABLE_COMPILATION ON)
else ()
  add_library (Grid ${GRID_SOURCES})
endif ()

target_link_libraries (Grid Kernels Settings ${MPI_CXX_LIBRARIES})
