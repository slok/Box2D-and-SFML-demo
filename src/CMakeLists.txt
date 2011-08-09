
file(GLOB source_files "*.cpp")

find_package(SFML REQUIRED COMPONENTS System Window Graphics)
find_package(BOX2D REQUIRED)

#set headers stuff
set(include_dirs
    ${PROJECT_SOURCE_DIR}/src
    ${SFML_INCLUDE_DIR}
    ${BOX2D_INCLUDE_DIR}
)

#set lib stuff
set(depend_libs
    ${SFML_LIBRARY}
    ${BOX2D_LIBRARY}
)

include_directories(${include_dirs})
add_executable(box2dsfml ${source_files})
target_link_libraries(box2dsfml ${depend_libs})

