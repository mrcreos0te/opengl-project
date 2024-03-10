set(SRC_LIST
    src/line.cpp
)

set(HEADERS_LIST
    include/line.h
)

add_library(mcrgraphics ${SRC_LIST})

target_include_directories(mcrgraphics PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(mcrgraphics
    PUBLIC OpenGL::GL
    PUBLIC GLEW::GLEW
    PUBLIC glfw
    PUBLIC glm)