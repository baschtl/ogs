STRING(REPLACE " " ";" WRAPPER_COMMAND ${WRAPPER_COMMAND})
EXECUTE_PROCESS(
	COMMAND ${WRAPPER_COMMAND} ${EXECUTABLE} ${EXECUTABLE_ARGS}
	WORKING_DIRECTORY ${case_path}
	RESULT_VARIABLE EXIT_CODE
)

IF(NOT EXIT_CODE STREQUAL "0")
	MESSAGE(FATAL_ERROR "Test wrapper exited with code: ${EXIT_CODE}")
ENDIF()
