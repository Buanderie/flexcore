INCLUDE( ${CMAKE_CURRENT_LIST_DIR}/flexcore-targets.cmake )

GET_PROPERTY( FLEXCORE_INCLUDE_DIRS TARGET flexcore PROPERTY INTERFACE_INCLUDE_DIRECTORIES )
SET( FLEXCORE_LIBRARIES flexcore )
GET_PROPERTY( FLEXCORE_COMPILE_OPTIONS TARGET flexcore PROPERTY INTERFACE_COMPILE_OPTIONS )

