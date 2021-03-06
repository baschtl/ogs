INCLUDE(CodeCoverage)

SET(COVERAGE_EXCLUDES
	'/gpfs0/*'
	'/usr/*'
	'${CMAKE_BINARY_DIR}/*'
	'${CMAKE_SOURCE_DIR}/Tests/*'
	'${CMAKE_SOURCE_DIR}/ThirdParty/*'
)

IF(LCOV_PATH AND GENHTML_PATH)
	SETUP_TARGET_FOR_COVERAGE(testrunner_coverage testrunner "testrunner_coverage_results" "-j;${PROCESSOR_COUNT}")
	IF(OGS_BUILD_GUI)
		SETUP_TARGET_FOR_COVERAGE(DataExplorer_coverage DataExplorer "DataExplorer_coverage_results")
	ENDIF()
ELSE()
	MESSAGE(STATUS "No lcov coverage report generated because lcov or genhtml was not found.")
ENDIF()

IF(PYTHON_EXECUTABLE)
	SETUP_TARGET_FOR_COVERAGE_COBERTURA(testrunner_coverage_cobertura testrunner "testrunner_coverage_cobertura_results" "-j;${PROCESSOR_COUNT}")
ELSE()
	MESSAGE(STATUS "No cobertura coverage report generated because Python executable was not found.")
ENDIF()
