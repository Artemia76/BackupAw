###############################################################################
# General settings
###############################################################################

# Minimum CMake Version compatibility
cmake_minimum_required(VERSION 3.18)

# Set the project name
project(BackupAw)

if (POLICY CMP0127)
  cmake_policy(SET CMP0127 NEW) # cmake_dependent_option changes
endif ()

# Set Standard used for this project
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})

set(UNIVERSE_VERSION VP CACHE STRING "Choose version of targetted Universe")

set_property(CACHE UNIVERSE_VERSION PROPERTY STRINGS VP AW)

if(UNIVERSE_VERSION EQUAL "VP")
	add_definitions(-DVP_BUILD)
endif()

#inclusion de wxWidgets

include(FindwxWidgets)
find_package(wxWidgets COMPONENTS core base REQUIRED)
include(${wxWidgets_USE_FILE})
	
# If we build for windows systems, we also include the resource file
# containing the manifest, icon and other resources
if(WIN32)
  set(SRCS ${SRCS} Ressources.rc)
endif(WIN32)

# Create a source variable
set(SOURCES
	src/AboutBox.cpp
	src/AwObject.cpp
	src/CBackupCtrl.cpp
	src/CBot.cpp
	src/CBuild.cpp
	src/CDelete.cpp
	src/CFilter.cpp
	src/CGeometry.cpp
	src/CModify.cpp
	src/COutils.cpp
	src/Cpasspriv.cpp
	src/Ctrlaw.cpp
	src/CtrlCell.cpp
	src/MainApp.cpp
	src/MainFrame.cpp
	src/MapCanvas.cpp
	src/OptionBox.cpp
	src/ToolBook.cpp
)

# Add executable with the above sources
add_executable(${PROJECT_NAME}
        ${SOURCES}
)

if(UNIVERSE EQUAL "AW")
set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
endif()

#includes directoriesf not exist
target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/icones
)

if(UNIVERSE EQUAL "VP")
target_link_libraries(${PROJECT_NAME}
    LINK_PUBLIC
        libvpsdk.so
)
else()
target_link_libraries(${PROJECT_NAME}
    LINK_PUBLIC
        aw_sdk.a
)
endif()

if (UNIX)
    install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
endif (UNIX)