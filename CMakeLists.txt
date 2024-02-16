cmake_minimum_required(VERSION 3.20.2)
project("biso")
set(PROJECT_GITNAME   "BISO.Helper")
set(PROJECT_LONGNAME  "Batch Install Script Organizer")
set(PROJECT_EXEC      "bison")
set(PROJECT_VERSION   "dev_00001")
set(ALLOW_DUPLICATE_CUSTOM_TARGETS TRUE)

set(DIR_LIB ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(DIR_RES ${CMAKE_CURRENT_SOURCE_DIR}/res)
set(DIR_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(DIR_IMGUI ${DIR_LIB}/imgui)

file(GLOB_RECURSE ALL_SRC CONFIGURE_DEPENDS 
    "${DIR_SRC}/*.cpp" 
    "${DIR_LIB}/imgui/imgui.cpp"
    "${DIR_LIB}/imgui/imgui_draw.cpp"
    "${DIR_LIB}/imgui/imgui_tables.cpp"
    "${DIR_LIB}/imgui/imgui_widgets.cpp"
    "${DIR_LIB}/imgui/backends/imgui_impl_glfw.cpp"
    "${DIR_LIB}/imgui/backends/imgui_impl_opengl3.cpp"
)

include_directories(${DIR_IMGUI} ${DIR_IMGUI}/backends ${DIR_SRC} )
add_executable(${PROJECT_EXEC} ${ALL_SRC})

add_subdirectory(${DIR_LIB}/glfw)
target_include_directories(${PROJECT_EXEC} PRIVATE "${DIR_LIB}/glfw/include/")

add_subdirectory(${DIR_LIB}/json)
target_include_directories(${PROJECT_EXEC} PUBLIC "${DIR_LIB}/json/include/")

find_package(OpenGL REQUIRED)

target_link_libraries(${PROJECT_EXEC} PRIVATE glfw OpenGL::GL nlohmann_json::nlohmann_json)