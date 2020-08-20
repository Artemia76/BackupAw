###############################################################################
# General settings
###############################################################################
cmake_minimum_required(VERSION 2.8.0 FATAL_ERROR)

# Déclaration1 du projet

project(BackupAw)

set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})

#inclusion de wxWidgets

include(FindwxWidgets)

find_package(wxWidgets COMPONENTS core base REQUIRED)
	
# If we build for windows systems, we also include the resource file
# containing the manifest, icon and other resources
if(WIN32)
  set(SRCS ${SRCS} Ressources.rc)
endif(WIN32)

#Déclaration de l'executable

add_executable(
	backupaw
	include/AboutBox.h
	include/AwObject.h
	include/CBackupCtrl.h
	include/CBot.h
	include/CBuild.h
	include/CCoord.h
	include/CDelete.h
	include/CFilter.h
	include/CGeometry.h
	include/CModify.h
	include/COutils.h
	include/Cpasspriv.h
	include/Ctrlaw.h
	include/CtrlCell.h
	include/Global.h
	include/MainApp.h
	include/MainFrame.h
	include/MapCanvas.h
	include/OptionBox.h
	include/ToolBook.h

	src/AboutBox.cpp
	src/AwObject.h
	src/CBackupCtrl.cpp
	src/CBot.cpp
	src/CBuild.cpp
	src/CCoord.cpp
	src/CDelete.cpp
	src/CFilter.cpp
	src/CGeometry.cpp
	src/CModify.cpp
	src/COutils.cpp
	src/Cpasspriv.cpp
	src/Ctrlaw.cpp
	src/CtrlCell.cpp
	src/Global.cpp
	src/MainApp.cpp
	src/MainFrame.cpp
	src/MapCanvas.cpp
	src/OptionBox.cpp
	src/ToolBook.cpp
	