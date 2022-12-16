cmake_minimum_required(VERSION 3.20)

set(PROJECT_NAME AssetLoader)
include("FetchContent")

project(${PROJECT_NAME} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

#set (SOURCE_DIR ${PROJECT_SOURCE_DIR}/Source source)
#set (VENDOR_DIR ${PROJECT_SOURCE_DIR}/Dependencies vendor)
#set (GLAD_DIR ${PROJECT_SOURCE_DIR}/Dependencies/GLAD)

file(GLOB_RECURSE SOURCE_CORE "${PROJECT_SOURCE_DIR}/Core/src/*.cpp")
file(GLOB_RECURSE INCLUDE_CORE "${PROJECT_SOURCE_DIR}/Core/include/*.h")
file(GLOB_RECURSE SOURCE_FILEGL "${PROJECT_SOURCE_DIR}/libGL/src/*.cpp")
file(GLOB_RECURSE INCLUDE_FILEGL "${PROJECT_SOURCE_DIR}/libGL/include/*.h")

add_executable(${PROJECT_NAME}
			${SOURCE_FILEGL}
			${INCLUDE_FILEGL})

set_property(TARGET ${PROJECT_NAME} PROPERTY

VS_DEBUGGER_WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}")

#add GLAD
target_include_directories(${PROJECT_NAME} PUBLIC
	"external/GLAD/include")
target_sources(${PROJECT_NAME} PUBLIC "external/GLAD/src/glad.cpp")

#add GLFW
FetchContent_Declare(
	GLFW
	GIT_REPOSITORY https://github.com/glfw/glfw.git
	GIT_TAG 3.3.8)

#add ASSIMP
FetchContent_Declare(
	assimp
	GIT_REPOSITORY https://github.com/assimp/assimp.git
	GIT_TAG v5.2.5)

#add RapidJASON
# target_include_directories(${PROJECT_NAME} PUBLIC "external/RapidJASON")

#add STB
target_include_directories(${PROJECT_NAME} PUBLIC "external/STB")

#add IrrKlang
target_include_directories(${PROJECT_NAME} PUBLIC "external/IrrKlang/include")
target_link_libraries(${PROJECT_NAME} PUBLIC "../external/IrrKlang/lib/irrKlang")

#add Maths Library
set(MATHS_DIR "LibMaths")
file(GLOB_RECURSE MATH_SOURCES "${MATHS_DIR}/*.cpp" "${MATHS_DIR}/*.h")
add_library(libMaths STATIC EXCLUDE_FROM_ALL "${MATH_SOURCES}")
target_include_directories(libMaths PRIVATE ${MATHS_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC ${MATHS_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC ${MATHS_LIB})

# #add ImGUI
# file(GLOB_RECURSE IMGUI_SOURCES "external/ImGUI/*.cpp" "external/ImGUI/*.h")
# add_library(ImGui STATIC EXCLUDE_FROM_ALL "${IMGUI_SOURCES}")
# target_include_directories(ImGui PUBLIC "external/ImGUI")
# target_include_directories(ImGui PUBLIC ${GLFW3_INCLUDE_DIR})
# target_include_directories(ImGui PUBLIC "external/GLAD/include")
# target_include_directories(ImGui PUBLIC ${MATHS_DIR})
# target_include_directories(ImGui PUBLIC ${ASSIMP_INCLUDE_DIR})
# target_link_libraries(${PROJECT_NAME} PUBLIC ImGui)

#add Core
set(CORE_DIR "Core")
add_library(Core STATIC EXCLUDE_FROM_ALL ${SOURCE_CORE} ${INCLUDE_CORE})
target_include_directories(Core PRIVATE ${CORE_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC "${CORE_DIR}/include")
target_include_directories(Core PUBLIC "${CORE_DIR}/include")
target_link_libraries(${PROJECT_NAME} PUBLIC ${CORE_LIB})


#add OpenGL Include
set(OPENGL_INCLUDES "LibGL/include")
target_include_directories(${PROJECT_NAME} PRIVATE ${OPENGL_INCLUDES})



FetchContent_MakeAvailable(GLFW assimp)

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_INCLUDE_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${assimp_SOURCE_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${glfw_SOURCE_DIR}/include)


target_link_libraries(${PROJECT_NAME} PUBLIC assimp)
target_link_libraries(${PROJECT_NAME} PUBLIC glfw)

if(MSVC)
  target_compile_options(${PROJECT_NAME} PRIVATE /W4 )
endif()