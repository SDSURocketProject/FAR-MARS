cmake_minimum_required(VERSION 3.1.0)

project(controlsoftware)


find_package(Qt5 COMPONENTS Core Gui Widgets Charts)

set(SOURCES
	com.cpp
	csv.cpp
	liveplot.cpp
	logger.cpp
	main.cpp
	mainwindow.cpp
	qcgaugewidget.cpp
	serial.cpp
	liveplot.ui
	mainwindow.ui
)

set(HEADER_FILES
	include/com.h
	include/csv.h
	include/liveplot.h
	include/logger.h
	include/mainwindow.h
	include/qcgaugewidget.h
	include/serial.h
)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

add_executable(controlsoftware main.cpp mainwindow.cpp ${SOURCES} ${HEADER_FILES})

target_include_directories(controlsoftware PUBLIC include/)

target_link_libraries(controlsoftware
	PUBLIC
	Qt5::Core
	Qt5::Gui
	Qt5::Widgets
	Qt5::Charts
)


