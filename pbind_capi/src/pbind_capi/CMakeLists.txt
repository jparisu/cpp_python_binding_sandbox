
# Some system may inject Python headers via Toolchain file
if(NOT PythonLibs_FOUND)
    find_package(PythonLibs REQUIRED)
endif()

find_package(PythonInterp)
find_package(Python)

set(SOURCE_FILE
    "easy_bytes.cpp")
set(MODULE_NAME ${PROJECT_NAME})

add_library(${MODULE_NAME} ${SOURCE_FILE})

target_include_directories(${MODULE_NAME} PUBLIC ${PYTHON_INCLUDE_DIRS})

target_link_libraries(${MODULE_NAME} ${PYTHON_LIBRARIES} pbind_cpp)

set_target_properties(
    ${PROJECT_NAME}
        PROPERTIES
        PREFIX ""
        OUTPUT_NAME ${PROJECT_NAME}
        LINKER_LANGUAGE CXX
    )

# install(TARGETS ${MODULE_NAME}
#     EXPORT ${MODULE_NAME}-targets
#     RUNTIME DESTINATION ${BIN_INSTALL_DIR}
#     LIBRARY DESTINATION ${LIB_INSTALL_DIR}
#     ARCHIVE DESTINATION ${LIB_INSTALL_DIR}
#     COMPONENT libraries
#     )

# install(EXPORT ${MODULE_NAME}-targets
#     DESTINATION ${LIB_INSTALL_DIR}/cmake/${MODULE_NAME}
#     COMPONENT cmake
#     )

install(
    TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION ${BIN_INSTALL_DIR}
    LIBRARY DESTINATION ${LIB_INSTALL_DIR}
    ARCHIVE DESTINATION ${LIB_INSTALL_DIR}
)
