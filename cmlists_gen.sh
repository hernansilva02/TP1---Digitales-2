#!/bin/bash
if [ $# -lt 1 ]; then
    echo "Bad usage: cmlists_gen.sh <project_name>"
    exit
fi

project_name="$1"

if [ ! -d "/home/${USER}/SDK_25_06_00_LPC845BREAKOUT" ]; then 
    echo "No SDK installed. Run install.sh to be able to compile"
fi

c_files="$(find . -name "*.c" -type f -printf '%f\n')"
h_files="$(find . -name "*.h" -type f -printf '%f\n')"

if [ -z "$c_files" ] && [ -z "$h_files" ]; then
    echo "No .c or .h files in current directory. No executables added to the file"
fi

cat > CMakeLists.txt << EOF 
# CROSS COMPILER SETTING
set(CMAKE_SYSTEM_NAME Generic)
cmake_minimum_required(VERSION 3.10.0)

# THE VERSION NUMBER
SET (MCUXPRESSO_CMAKE_FORMAT_MAJOR_VERSION 2)
SET (MCUXPRESSO_CMAKE_FORMAT_MINOR_VERSION 0)

include(ide_overrides.cmake OPTIONAL)

if(CMAKE_SCRIPT_MODE_FILE)
  message("\${MCUXPRESSO_CMAKE_FORMAT_MAJOR_VERSION}")
  return()
endif()


set(CMAKE_EXECUTABLE_LIBRARY_PREFIX)
set(CMAKE_EXECUTABLE_LIBRARY_SUFFIX)

# CURRENT DIRECTORY
set(ProjDirPath \${CMAKE_CURRENT_SOURCE_DIR})

set(EXECUTABLE_OUTPUT_PATH \${ProjDirPath}/\${CMAKE_BUILD_TYPE})
set(LIBRARY_OUTPUT_PATH \${ProjDirPath}/\${CMAKE_BUILD_TYPE})


project(${project_name})

enable_language(ASM)

set(MCUX_BUILD_TYPES debug release)

set(MCUX_SDK_PROJECT_NAME ${project_name}.elf)

if (NOT DEFINED SdkRootDirPath)
    SET(SdkRootDirPath /home/${USER}/SDK_25_06_00_LPC845BREAKOUT)
endif()

add_executable(\${MCUX_SDK_PROJECT_NAME} 
${c_files}
${h_files}
)

target_include_directories(\${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${ProjDirPath}/..
)

include(\${SdkRootDirPath}/boards/lpc845breakout/demo_apps/new_project/armgcc/flags.cmake)
include(\${SdkRootDirPath}/boards/lpc845breakout/demo_apps/new_project/armgcc/config.cmake) 
include(\${SdkRootDirPath}/devices/LPC845/all_lib_device.cmake)

IF(NOT DEFINED TARGET_LINK_SYSTEM_LIBRARIES)  
    SET(TARGET_LINK_SYSTEM_LIBRARIES "-lm -lc -lgcc -lnosys")  
ENDIF()  

TARGET_LINK_LIBRARIES(\${MCUX_SDK_PROJECT_NAME} PRIVATE -Wl,--start-group)

target_link_libraries(\${MCUX_SDK_PROJECT_NAME} PRIVATE \${TARGET_LINK_SYSTEM_LIBRARIES})

TARGET_LINK_LIBRARIES(\${MCUX_SDK_PROJECT_NAME} PRIVATE -Wl,--end-group)

ADD_CUSTOM_COMMAND(TARGET \${MCUX_SDK_PROJECT_NAME} POST_BUILD COMMAND \${CMAKE_OBJCOPY}
-Obinary \${EXECUTABLE_OUTPUT_PATH}/\${MCUX_SDK_PROJECT_NAME} \${EXECUTABLE_OUTPUT_PATH}/${project_name}.bin)

set_target_properties(\${MCUX_SDK_PROJECT_NAME} PROPERTIES ADDITIONAL_CLEAN_FILES "output.map;\${EXECUTABLE_OUTPUT_PATH}/${project_name}.bin")

# wrap all libraries with -Wl,--start-group -Wl,--end-group to prevent link order issue
group_link_libraries()
EOF
echo "CMakeLists.txt generated"
