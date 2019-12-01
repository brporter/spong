cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(spong)

# Resource Paths
set( SPOT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/resources/spot.bmp" )
set( BALL_PATH "${CMAKE_CURRENT_SOURCE_DIR}/resources/ball.bmp" )

if (APPLE)
    execute_process(COMMAND xcrun -find cc OUTPUT_VARIABLE CMAKE_C_COMPILER)
    execute_process(COMMAND xcrun -find c++ OUTPUT_VARIABLE CMAKE_CXX_COMPILER)
    string(STRIP ${CMAKE_C_COMPILER} CMAKE_C_COMPILER)
    string(STRIP ${CMAKE_CXX_COMPILER} CMAKE_CXX_COMPILER)
endif (APPLE)

find_package(SDL2 REQUIRED)
find_package(SDL2_TTF REQUIRED)

include_directories(
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_TTF_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}/src
)

set(ALL_SOURCES
    safesdl.h
    board.cpp 
    input.cpp 
    resources.cpp 
    main.cpp 
    player.cpp 
    ${SPOT_PATH}
    ${BALL_PATH}
)

set_source_files_properties( ${SPOT_PATH} PROPERTIES MACOSX_PACKAGE_LOCATION Resources )
set_source_files_properties( ${BALL_PATH} PROPERTIES MACOSX_PACKAGE_LOCATION Resources )

add_executable(
    spong 
    MACOSX_BUNDLE
    ${ALL_SOURCES}
)

target_link_libraries(spong
    ${SDL2_LIBRARIES}
    ${SDL2_TTF_LIBRARIES}
)

if (APPLE)
    target_link_libraries(spong "-framework CoreFoundation")

    # Create an application bundle on macOS
    set_target_properties(spong PROPERTIES
        MACOSX_BUNDLE TRUE
        MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/Info.plist
    )

    ADD_CUSTOM_COMMAND(TARGET spong POST_BUILD
        COMMAND cp "${CMAKE_BINARY_DIR}/compile_commands.json" "${CMAKE_CURRENT_SOURCE_DIR}/../"
        COMMENT "copying compile_commands.json..."
    )
endif (APPLE)
