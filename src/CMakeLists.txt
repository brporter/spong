cmake_minimum_required(VERSION 3.7)

project(spong)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set( SPOT_NAME "spot.bmp" )
set( SPOT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/resources/${SPOT_NAME}" )

if (APPLE)
    execute_process(COMMAND xcrun -find cc OUTPUT_VARIABLE CMAKE_C_COMPILER)
    execute_process(COMMAND xcrun -find c++ OUTPUT_VARIABLE CMAKE_CXX_COMPILER)
    string(STRIP ${CMAKE_C_COMPILER} CMAKE_C_COMPILER)
    string(STRIP ${CMAKE_CXX_COMPILER} CMAKE_CXX_COMPILER)
endif (APPLE)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

set_source_files_properties( ${SPOT_PATH} PROPERTIES MACOSX_PACKAGE_LOCATION Resources )

add_executable(
    spong 
    MACOSX_BUNDLE 
    input.cpp 
    resources.cpp 
    main.cpp 
    player.cpp 
    ${SPOT_PATH}
)

set_property(TARGET spong PROPERTY CXX_STANDARD 20)
target_link_libraries(spong ${SDL2_LIBRARIES})

if (APPLE)
    target_link_libraries(spong "-framework CoreFoundation")

    # Create an application bundle on macOS
    set_target_properties(spong PROPERTIES
        MACOSX_BUNDLE TRUE
        MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/Info.plist
    )
endif (APPLE)

#ADD_CUSTOM_COMMAND(TARGET spong POST_BUILD
#    COMMAND cp "${CMAKE_BINARY_DIR}/compile_commands.json" "${CMAKE_CURRENT_SOURCE_DIR}/../"
#    COMMENT "copying compile_commands.json..."
#)
