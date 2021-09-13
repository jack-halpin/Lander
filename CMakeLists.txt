cmake_minimum_required (VERSION 2.6)
project (lander)
# set the version number
set (lander_VERSION_MAJOR 1)
set (lander_VERSION_MINOR 0)

set (CMAKE_CXX_STANDARD 17)
if(WIN32)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
endif(WIN32)

if(APPLE)
    set(CMAKE_OSX_DEPLOYMENT_TARGET "11.1")
endif(APPLE)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if (UNIX)
    include_directories(../third_party/glfw/include)
    include_directories(../third_party/assimp-5.0.1/include)
    link_directories(/usr/local/lib)

    find_package(glfw3)
    set(LIBS glfw assimp)
endif(UNIX)
if (WIN32)
    include_directories(../third_party/Include)
    link_directories(${CMAKE_BINARY_DIR}/../../third_party/Libs/GLFW)
    set(LIBS glfw3)
endif (WIN32)

include_directories(include)

file(GLOB SOURCE
    "src//*.cpp"
    "src/shaders/*.vs"
    "src/shaders/*.fs"
    "src/glad.cpp"
)

    # Setup source groups
    file (GLOB SHADERS
        "src/shaders/*.vs"
        "src/shaders/*.fs"
    )
    file (GLOB_RECURSE HEADERS
        "include/*.h"
    )
    source_group("Shaders" FILES ${SHADERS})
    source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${HEADERS})


    set(NAME Lander)
    add_executable(${NAME} ${SOURCE} ${HEADERS})
    target_link_libraries(${NAME} ${LIBS})

    if (WIN32)
        set_property(TARGET ${NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/$<CONFIG>")
    endif (WIN32)

