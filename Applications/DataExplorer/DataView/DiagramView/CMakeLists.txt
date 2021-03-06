# Source files
SET( SOURCES
	DetailWindow.cpp
	DiagramList.cpp
	DiagramPrefsDialog.cpp
	DiagramScene.cpp
	DiagramView.cpp
	QArrow.cpp
	QGraphicsGrid.cpp
)

# Moc Header files
SET( MOC_HEADERS
	DetailWindow.h
	DiagramPrefsDialog.h
	DiagramView.h
)

# Header files
SET( HEADERS
	DiagramList.h
	QArrow.h
	QGraphicsGrid.h
	DiagramScene.h
)

# UI files
SET( UIS
	DetailWindow.ui
	DiagramPrefs.ui
)

# Run Qts user interface compiler uic on .ui files
QT4_WRAP_UI( UI_HEADERS ${UIS} )

# Run Qts meta object compiler moc on header files
QT4_WRAP_CPP( MOC_SOURCES ${MOC_HEADERS} )

# Include the headers which are generated by uic and moc
# and include additional header
SET(SOURCE_DIR_REL ${CMAKE_CURRENT_SOURCE_DIR}/../../../..)
SET(GUI_SOURCE_DIR_REL ${CMAKE_CURRENT_SOURCE_DIR}/../..)
INCLUDE_DIRECTORIES(
	${SOURCE_DIR_REL}/BaseLib
	${SOURCE_DIR_REL}/GeoLib
	${SOURCE_DIR_REL}/MathLib
	${CMAKE_CURRENT_SOURCE_DIR}
	${GUI_SOURCE_DIR_REL}/Base
	${GUI_SOURCE_DIR_REL}/DataView
	${CMAKE_CURRENT_BINARY_DIR}/../../DataView
	${CMAKE_CURRENT_BINARY_DIR}
)

# Put moc files in a project folder
SOURCE_GROUP("Moc Files" REGULAR_EXPRESSION moc_*)

# Create the library
ADD_LIBRARY( QtDiagramView STATIC
	${SOURCES}
	${HEADERS}
	${MOC_HEADERS}
	${MOC_SOURCES}
	${UI_HEADERS}
)

# Link Qt library
TARGET_LINK_LIBRARIES( QtDiagramView
	${QT_LIBRARIES}
	GeoLib
)

SET_PROPERTY(TARGET QtDiagramView PROPERTY FOLDER "DataExplorer")
