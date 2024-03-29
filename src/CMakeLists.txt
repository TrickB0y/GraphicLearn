link_directories("${MyProject_SOURCE_DIR}/glad/src"
				"${MyProject_SOURCE_DIR}/glfw/src")

add_executable(GraphicLearn main.cpp)

target_link_libraries(GraphicLearn glfw glad ${GLFW_LIBRARIES})
