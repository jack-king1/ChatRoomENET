## hide console unless debug build ##
if (NOT CMAKE_BUILD_TYPE STREQUAL  "Debug" AND WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows")
endif()

## compile language settings
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

## include files
target_include_directories(
        ${PROJECT_NAME}
        PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/Headers"
        "${CMAKE_CURRENT_SOURCE_DIR}/Include"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source"
        "${CMAKE_SOURCE_DIR}/Shared/Include"
        "${CMAKE_SOURCE_DIR}/Shared/Source")

## fix issue with arch enabling gcc pie by default
## https://stackoverflow.com/questions/43367427/32-bit-absolute-addresses-no-longer-allowed-in-x86-64-linux
if(CMAKE_COMPILER_IS_GNUCC)
    target_link_libraries(${PROJECT_NAME} -no-pie pthread)
endif()

## enable static linking against gcc build
if (WIN32 AND NOT BUILD_SHARED_LIBS AND NOT MSVC)
    target_link_libraries(${PROJECT_NAME} -static)
endif()

## both server and client need the net library
add_dependencies(${PROJECT_NAME} enetpp)
target_link_libraries(${PROJECT_NAME} enetpp)
