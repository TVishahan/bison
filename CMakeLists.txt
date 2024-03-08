cmake_minimum_required(VERSION 3.20.2)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>" CACHE INTERNAL "")

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
    "${DIR_SRC}/*.h" 
    "${DIR_SRC}/*.hpp"
)

include_directories(${DIR_IMGUI} ${DIR_IMGUI}/backends ${DIR_SRC} ${GTKMM_INCLUDE_DIRS})
add_executable(${PROJECT_EXEC} ${ALL_SRC})

add_subdirectory(${DIR_LIB}/json)
target_include_directories(${PROJECT_EXEC} PRIVATE "${DIR_LIB}/json/include/")

add_subdirectory(${DIR_LIB}/FTXUI)
target_include_directories(${PROJECT_EXEC} PRIVATE "${DIR_LIB}/FTXUI/include/")

target_link_libraries(${PROJECT_EXEC} PRIVATE 
    ftxui::screen ftxui::dom ftxui::component 
    nlohmann_json::nlohmann_json)