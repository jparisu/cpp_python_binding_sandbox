# Copyright 2022 Proyectos y Sistemas de Mantenimiento SL (eProsima).
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

###############################################################################
# Compile python wrapper with SWIG
###############################################################################

cmake_minimum_required(VERSION 3.15)

# SWIG: use standard target name.
if(POLICY CMP0078)
  cmake_policy(SET CMP0078 NEW)
endif()

# SWIG: use SWIG_MODULE_NAME property.
if(POLICY CMP0086)
  cmake_policy(SET CMP0086 NEW)
endif()

# Done this to set machine architecture and be able to call cmake_utils
enable_language(CXX)

###############################################################################
# Find package cmake_utils
###############################################################################
# Package cmake_utils is required to get every cmake macro needed
find_package(cmake_utils REQUIRED)

###############################################################################
# Project
###############################################################################
# Configure project by info set in project_settings.cmake
# - Load project_settings variables
# - Read version
# - Set installation paths
configure_project()

# Call explictly project
project(
    ${MODULE_NAME}
    VERSION
        ${MODULE_VERSION}
    DESCRIPTION
        ${MODULE_DESCRIPTION}
)

###############################################################################
# C++ Project
###############################################################################
# Configure CPP project for dependencies and required flags:
# - Set CMake Build Type
# - Set C++ version
# - Set shared libraries by default
# - Find external packages and thirdparties
# - Activate Code coverage if flag CODE_COVERAGE
# - Configure log depending on LOG_INFO flag and CMake type
configure_project_cpp()

find_package(SWIG REQUIRED)
include(${SWIG_USE_FILE})
set(CMAKE_SWIG_FLAGS "")
find_package (Python3 COMPONENTS Interpreter Development REQUIRED)

set(${PROJECT_NAME}_MODULE
        ${PROJECT_NAME}
    )

set(${PROJECT_NAME}_FILES
        ${${PROJECT_NAME}_MODULE}.i
    )

SET_SOURCE_FILES_PROPERTIES(
        ${${PROJECT_NAME}_FILES}
        PROPERTIES CPLUSPLUS ON
        USE_TARGET_INCLUDE_DIRECTORIES TRUE
    )

SWIG_ADD_LIBRARY(${PROJECT_NAME}
        TYPE SHARED
        LANGUAGE python
        SOURCES ${${PROJECT_NAME}_FILES}
    )

if(UNIX AND CMAKE_SIZEOF_VOID_P EQUAL 8)
    set_property(TARGET ${PROJECT_NAME} PROPERTY SWIG_COMPILE_DEFINITIONS SWIGWORDSIZE64)
endif()

SWIG_LINK_LIBRARIES(${PROJECT_NAME}
        Python3::Module
        pbind_cpp
    )

# Find the installation path
execute_process(COMMAND ${Python3_EXECUTABLE} -c "from distutils import sysconfig; print(sysconfig.get_python_lib(plat_specific=True, prefix='${CMAKE_INSTALL_PREFIX}' ) )"
        OUTPUT_VARIABLE _ABS_PYTHON_MODULE_PATH
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
get_filename_component (_ABS_PYTHON_MODULE_PATH ${_ABS_PYTHON_MODULE_PATH} ABSOLUTE)
file (RELATIVE_PATH _REL_PYTHON_MODULE_PATH ${CMAKE_INSTALL_PREFIX} ${_ABS_PYTHON_MODULE_PATH})
SET (PYTHON_MODULE_PATH
        ${_REL_PYTHON_MODULE_PATH}
    )

# Install
install(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}-targets
        DESTINATION ${PYTHON_MODULE_PATH}
    )
get_property(support_files TARGET ${PROJECT_NAME} PROPERTY SWIG_SUPPORT_FILES)
install(FILES ${support_files} DESTINATION ${PYTHON_MODULE_PATH})

export(TARGETS ${PROJECT_NAME} FILE ${PROJECT_BINARY_DIR}/cmake/config/${PROJECT_NAME}-targets.cmake)

install(EXPORT ${PROJECT_NAME}-targets
        DESTINATION ${LIB_INSTALL_DIR}/cmake/${PROJECT_NAME}/
    )

# Create CMake config file.
include(CMakePackageConfigHelpers)

configure_package_config_file(
        ${cmake_utils_CONFIG_TEMPLATES_PATH}/library-Config.cmake.in
        ${PROJECT_BINARY_DIR}/cmake/config/${PROJECT_NAME}-config.cmake
        INSTALL_DESTINATION ${LIB_INSTALL_DIR}/cmake/${PROJECT_NAME}
        PATH_VARS LIB_INSTALL_DIR
    )
write_basic_package_version_file(${PROJECT_BINARY_DIR}/cmake/config/${PROJECT_NAME}-config-version.cmake
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY SameMajorVersion
    )
install(FILES ${PROJECT_BINARY_DIR}/cmake/config/${PROJECT_NAME}-config.cmake
        ${PROJECT_BINARY_DIR}/cmake/config/${PROJECT_NAME}-config-version.cmake
        DESTINATION ${LIB_INSTALL_DIR}/cmake/${PROJECT_NAME}
    )

eprosima_packaging()
