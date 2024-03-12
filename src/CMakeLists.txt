include_directories("${GraphicLearn_SOURCE_DIR}/glfw/include/"
					"${GraphicLearn_SOURCE_DIR}/glad/include/")
					
link_directories("${MyProject_SOURCE_DIR}/glad/src"
				"${MyProject_SOURCE_DIR}/glfw/src")

add_executable(GraphicLearn main.cpp)

target_link_libraries(GraphicLearn glfw glad ${GLFW_LIBRARIES})