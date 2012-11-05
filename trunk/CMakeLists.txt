cmake_minimum_required(VERSION 2.8)

project(luwak)
find_package(Qt4 REQUIRED)
find_package(OpenCV REQUIRED)

set(EXECUTABLE_OUTPUT_PATH bin)
set(Qt_HEADERS src/mainwindow.h src/fullimg.h src/iqgraphicsscene.h src/wqgraphicsscene.h)
set(Qt_FORMS src/mainwindow.ui src/fullimg.ui)


QT4_WRAP_CPP(Qt_HEADERS_MOC ${Qt_HEADERS})
QT4_WRAP_UI(Qt_FORMS_HEADERS ${Qt_FORMS})

include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})

add_definitions(-Wall -g -DPATH_DATA=\"data/\")

include_directories(src)
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

link_directories(
	${OpenCV_LINK_DIRECTORIES}
)

file(
	GLOB_RECURSE
	luwak_sources
	./src/*.cpp
	
)

add_executable(luwak ${luwak_sources} ${Qt_HEADERS_MOC} ${Qt_FORMS_HEADERS})

TARGET_LINK_LIBRARIES(
	luwak 
	${QT_LIBRARIES}
	${OpenCV_LIBS}
)
