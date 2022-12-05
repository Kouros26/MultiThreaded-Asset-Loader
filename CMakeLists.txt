cmake_minimum_required(VERSION 3.20)
include("FetchContent")

get_filename_component(CURRENT_FOLDER_NAME ${CMAKE_CURRENT_LIST_DIR} NAME)
set(PROJECT_NAME ${CURRENT_FOLDER_NAME})

project(${PROJECT_NAME} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

#set (SOURCE_DIR ${PROJECT_SOURCE_DIR}/Source source)
#set (VENDOR_DIR ${PROJECT_SOURCE_DIR}/Dependencies vendor)
#set (GLAD_DIR ${PROJECT_SOURCE_DIR}/Dependencies/GLAD)

file(GLOB_RECURSE SOURCE_CORE "${PROJECT_SOURCE_DIR}/Core/src/*.cpp")
file(GLOB_RECURSE INCLUDE_CORE "${PROJECT_SOURCE_DIR}/Core/include/*.h")
file(GLOB_RECURSE SOURCE_FILEGL "${PROJECT_SOURCE_DIR}/LibGL/src/*.cpp")
file(GLOB_RECURSE INCLUDE_FILEGL "${PROJECT_SOURCE_DIR}/LibGL/include/*.h")

add_executable(${PROJECT_NAME}
			${SOURCE_CORE}
			${INCLUDE_CORE}
			${SOURCE_FILEGL}
			${INCLUDE_FILEGL})

source_group("Source Files\\OpenGL" FILES ${SOURCE_FILEGL})
source_group("Header Files\\OpenGL" FILES ${INCLUDE_FILEGL})
source_group("Source Files\\MultiThreading" FILES ${SOURCE_CORE})
source_group("Header Files\\MultiThreading" FILES ${INCLUDE_CORE})
set_property(TARGET ${PROJECT_NAME} PROPERTY

VS_DEBUGGER_WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}")

#add GLAD
target_include_directories(${PROJECT_NAME} PUBLIC
	"external/GLAD/include")
target_sources(${PROJECT_NAME} PUBLIC "external/GLAD/src/glad.cpp")

#add GLFW
FetchContent_Declare(
	glfw
	GIT_REPOSITORY https://github.com/glfw/glfw.git
	GIT_TAG 3.3.8)

#add ASSIMP
include("FetchContent")

FetchContent_Declare(
	assimp
	GIT_REPOSITORY https://github.com/assimp/assimp.git
	GIT_TAG v5.2.5)

#add RapidJASON
target_include_directories(${PROJECT_NAME} PUBLIC "external/RapidJASON")

#add STB
target_include_directories(${PROJECT_NAME} PUBLIC "external/STB")

#add IrrKlang
target_include_directories(${PROJECT_NAME} PUBLIC "external/IrrKlang/include")
#target_link_libraries(${PROJECT_NAME} "../external/IrrKlang/lib/irrKlang")

#add Maths Library
FetchContent_Declare(
	MathLib
	GIT_REPOSITORY https://github.com/Kouros26/MathLib.git)

#add ImGUI
# file(GLOB_RECURSE IMGUI_SOURCES "external/ImGUI/*.cpp" "external/ImGUI/*.h")
# add_library(ImGui STATIC EXCLUDE_FROM_ALL "${IMGUI_SOURCES}")
# target_include_directories(ImGui PUBLIC "external/ImGUI")
# target_include_directories(ImGui PUBLIC ${GLFW3_INCLUDE_DIR})
# target_include_directories(ImGui PUBLIC "external/GLAD/include")
# target_include_directories(ImGui PUBLIC ${MATHS_DIR})
# target_include_directories(ImGui PUBLIC ${ASSIMP_INCLUDE_DIR})
# target_include_directories(ImGui PUBLIC ${BULLET_INCLUDE_DIR})
# target_link_libraries(${PROJECT_NAME} PUBLIC ImGui)

FetchContent_MakeAvailable(glfw assimp MathLib)

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_INCLUDE_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${assimp_SOURCE_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${glfw_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${MathLib})

target_link_libraries(${PROJECT_NAME} assimp)
target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} MathLib)

if(MSVC)
  target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX)
endif()