# Source files
GET_SOURCE_FILES(SOURCES_MESHLIB)

# It should be removed too for other MPI based DDC approach in future.
IF(NOT OGS_USE_PETSC)
	list(REMOVE_ITEM SOURCES_MESHLIB NodePartitionedMesh.h)
ENDIF(NOT OGS_USE_PETSC)

GET_SOURCE_FILES(SOURCES_ELEMENTS Elements)
GET_SOURCE_FILES(SOURCES_EDITING MeshEditing)
GET_SOURCE_FILES(SOURCES_GENERATORS MeshGenerators)
GET_SOURCE_FILES(SOURCES_QUALITY MeshQuality)
SET ( SOURCES ${SOURCES_MESHLIB} ${SOURCES_ELEMENTS} ${SOURCES_EDITING} ${SOURCES_GENERATORS} ${SOURCES_QUALITY})

# Create the library
ADD_LIBRARY(MeshLib STATIC ${SOURCES})

target_link_libraries (MeshLib
	BaseLib
	GeoLib
	MathLib
	logog
)

INCLUDE(AddCatalystDependency)
ADD_CATALYST_DEPENDENCY(MeshLib)
