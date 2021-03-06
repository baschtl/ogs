#####################
### OGS-6 Project ###
#####################

# Specify minimum CMake version
CMAKE_MINIMUM_REQUIRED(VERSION 2.8.8)

# Set CMake policies
CMAKE_POLICY(SET CMP0011 OLD)
IF(CMAKE_VERSION VERSION_GREATER 3.0.2)
	CMAKE_POLICY(SET CMP0054 NEW)
ENDIF()

# Project name
PROJECT( OGS-6 )

###########################
### Preliminary Options ###
###########################
OPTION(OGS_NO_BOOST_DOWNLOAD "Always use the system installed Boost?" OFF)
SET(CMAKE_LIBRARY_SEARCH_PATH "" CACHE PATH
	"Additional library installation path, e.g. /opt/local or C:/libs")

### CMake includes ###
INCLUDE(scripts/cmake/CheckTypeSizes.cmake)
INCLUDE(scripts/cmake/Functions.cmake)
INCLUDE(scripts/cmake/CMakeSetup.cmake)
INCLUDE(scripts/cmake/CompilerSetup.cmake)
INCLUDE(scripts/cmake/Find.cmake)
INCLUDE(scripts/cmake/SubmoduleSetup.cmake)
INCLUDE(scripts/cmake/ProjectSetup.cmake)
INCLUDE(scripts/cmake/DocumentationSetup.cmake)
IF(CMAKE_VERSION VERSION_GREATER 2.8.10)
	INCLUDE(scripts/cmake/test/Test.cmake)
ENDIF()
IF(OGS_COVERAGE AND NOT IS_SUBPROJECT)
	INCLUDE(scripts/cmake/Coverage.cmake)
ENDIF()

####################
### More Options ###
####################

# Profiling
IF((CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_GNUCC) AND GPROF_PATH)
	OPTION(OGS_PROFILE "Enables compiling with flags set for profiling with gprof." OFF)
ENDIF() # GCC AND GPROF_PATH

# Enable / Disable parts
OPTION(OGS_DONT_USE_QT "Disables all Qt specific code." OFF)

OPTION(OGS_BUILD_CLI "Should the OGS simulator be built?" ON)
OPTION(OGS_BUILD_TESTS "Should the test executables be built?" ON)
OPTION(OGS_BUILD_GUI "Should the Data Explorer be built?" OFF)
OPTION(OGS_BUILD_UTILS "Should the utilities programms be built?" OFF)

OPTION(OGS_NO_EXTERNAL_LIBS "Builds OGS without any external dependencies." OFF)

# Linear solvers
OPTION(OGS_USE_LIS "Use Lis" OFF)

# Parallel computing: vector and matrix algebraic caculation, solvers
OPTION(OGS_USE_PETSC "Use PETSc routines" OFF)

# Paralleization
OPTION(OGS_USE_MPI "Use MPI" OFF)

# Eigen
OPTION(OGS_USE_EIGEN "Use EIGEN for local matrix and vector" ON)
OPTION(EIGEN_NO_DEBUG "Disables Eigen's assertions" ON)

# Logging
OPTION(OGS_DISABLE_LOGGING "Disables all logog messages." OFF)

# Compiler flags
SET(OGS_CXX_FLAGS "" CACHE STRING "Additional C++ compiler flags.")

# Print CMake variable values
IF (OGS_CMAKE_DEBUG)
	INCLUDE(ListAllCMakeVariableValues)
	list_all_cmake_variable_values()
ENDIF (OGS_CMAKE_DEBUG)

# Code coverage
OPTION(OGS_COVERAGE "Enables code coverage measurements with gcov/lcov." OFF)

# Packaging
OPTION(OGS_DOWNLOAD_ADDITIONAL_CONTENT "Should addional content such as manuals be downloaded and packaged?" OFF)
INCLUDE(scripts/cmake/packaging/Pack.cmake)

######################
### Subdirectories ###
######################

# External projects
OPTION(Boost_USE_STATIC_LIBS "This option has to be set from the command line (before boost gets found)!" OFF)
INCLUDE(scripts/cmake/ExternalProjectBoost.cmake)
OPTION(OGS_SYSTEM_VTK_ONLY "If On VTK / ParaView will be searched if installed and will not be build locally." OFF)
INCLUDE(scripts/cmake/ExternalProjectCatalyst.cmake)

INCLUDE_DIRECTORIES( SYSTEM ${Boost_INCLUDE_DIRS} )
IF(OGS_USE_EIGEN)
	INCLUDE(scripts/cmake/ExternalProjectEigen.cmake)
ENDIF()

# Add subdirectories with the projects
ADD_SUBDIRECTORY( ThirdParty )
INCLUDE_DIRECTORIES( SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty )
INCLUDE_DIRECTORIES( SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/gtest/include )
INCLUDE_DIRECTORIES( SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/quickcheck )
INCLUDE_DIRECTORIES( SYSTEM ${CMAKE_CURRENT_BINARY_DIR}/ThirdParty/zlib )

IF(OGS_USE_LIS)
    ADD_DEFINITIONS(-DUSE_LIS)
    INCLUDE_DIRECTORIES(SYSTEM ${LIS_INCLUDE_DIR})
ENDIF()

# Use PETSc package for global assembly and linear sover for parallel computing
IF(OGS_USE_PETSC)
    ADD_DEFINITIONS(-DUSE_PETSC)
    SET(OGS_USE_MPI ON)
ENDIF()

# Use MPI
IF(OGS_USE_MPI)
    ADD_DEFINITIONS(-DUSE_MPI)
ENDIF()

IF(OGS_USE_EIGEN)
#	ADD_DEFINITIONS(-DEIGEN_DEFAULT_DENSE_INDEX_TYPE=std::size_t)
	ADD_DEFINITIONS(-DEIGEN_INITIALIZE_MATRICES_BY_ZERO)
	ADD_DEFINITIONS(-DOGS_USE_EIGEN)
	IF (EIGEN_NO_DEBUG)
		ADD_DEFINITIONS(-DEIGEN_NO_DEBUG)
	ENDIF()
	INCLUDE_DIRECTORIES (SYSTEM ${EIGEN3_INCLUDE_DIR})
ENDIF()

ADD_SUBDIRECTORY( Applications )
ADD_SUBDIRECTORY( AssemblerLib )
ADD_SUBDIRECTORY( BaseLib )
# TODO This is a hack but we have to make sure that Boost is built first
IF(TARGET Boost)
	ADD_DEPENDENCIES(BaseLib Boost)
ENDIF()
ADD_SUBDIRECTORY( FileIO )
ADD_SUBDIRECTORY( GeoLib )
ADD_SUBDIRECTORY( InSituLib )
ADD_SUBDIRECTORY( MathLib )
ADD_SUBDIRECTORY( MeshLib )
ADD_SUBDIRECTORY( MeshGeoToolsLib )
ADD_SUBDIRECTORY( NumLib )
ADD_SUBDIRECTORY( ProcessLib )
IF( OGS_BUILD_TESTS AND NOT IS_SUBPROJECT )
	IF(CMAKE_VERSION VERSION_LESS 2.8.11)
		MESSAGE(FATAL_ERROR "CMAKE 2.8.11 or higher is required to build the tests!")
	ENDIF()
	ADD_SUBDIRECTORY( Tests )

	IF(OGS_USE_MPI)
		ADD_SUBDIRECTORY( SimpleTests/MeshTests/MPI )
	ELSE()
		ADD_SUBDIRECTORY( SimpleTests/MatrixTests EXCLUDE_FROM_ALL )
		ADD_SUBDIRECTORY( SimpleTests/MeshTests EXCLUDE_FROM_ALL )
		IF(NOT MSVC AND BLAS_FOUND AND LAPACK_FOUND)
			ADD_SUBDIRECTORY( SimpleTests/SolverTests EXCLUDE_FROM_ALL )
		ENDIF()
	ENDIF()

	# Create a target 'data', which downloads all referenced data sets into the build tree
	# This has to be defined after all tests are defined
	ExternalData_Add_Target(data)
	SET_TARGET_PROPERTIES(data PROPERTIES EXCLUDE_FROM_ALL 1)
	ADD_DEPENDENCIES(ctest data)
ENDIF() # OGS_BUILD_TESTS

# The configuration must be called from the source dir and not BaseLib/.
CONFIGURE_FILE("${CMAKE_CURRENT_SOURCE_DIR}/BaseLib/BuildInfo.cpp.in"
	"${CMAKE_CURRENT_BINARY_DIR}/BaseLib/BuildInfo.cpp" @ONLY)
