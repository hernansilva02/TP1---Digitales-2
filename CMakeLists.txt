# CROSS COMPILER SETTING
set(CMAKE_SYSTEM_NAME Generic)
cmake_minimum_required(VERSION 3.10.0)

# THE VERSION NUMBER
SET (MCUXPRESSO_CMAKE_FORMAT_MAJOR_VERSION 2)
SET (MCUXPRESSO_CMAKE_FORMAT_MINOR_VERSION 0)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # compile options for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # compile options for clangd



include(ide_overrides.cmake OPTIONAL)

if(CMAKE_SCRIPT_MODE_FILE)
  message("${MCUXPRESSO_CMAKE_FORMAT_MAJOR_VERSION}")
  return()
endif()


set(CMAKE_EXECUTABLE_LIBRARY_PREFIX)
set(CMAKE_EXECUTABLE_LIBRARY_SUFFIX)

# CURRENT DIRECTORY
set(ProjDirPath ${CMAKE_CURRENT_SOURCE_DIR})

set(EXECUTABLE_OUTPUT_PATH ${ProjDirPath}/${CMAKE_BUILD_TYPE})
set(LIBRARY_OUTPUT_PATH ${ProjDirPath}/${CMAKE_BUILD_TYPE})


project(tp1)

enable_language(ASM)

set(MCUX_BUILD_TYPES debug release)

set(MCUX_SDK_PROJECT_NAME tp1.elf)

if (NOT DEFINED SdkRootDirPath)
    SET(SdkRootDirPath /home/hernan/SDK_25_06_00_LPC845BREAKOUT)
endif()

add_executable(${MCUX_SDK_PROJECT_NAME} 
board.c
clock_config.c
#CMakeCCompilerId.c
peripherals.c
pin_mux.c
"${CMAKE_CURRENT_SOURCE_DIR}/src/adc.c"
"${CMAKE_CURRENT_SOURCE_DIR}/src/button.c"
"${CMAKE_CURRENT_SOURCE_DIR}/src/led.c"
"${CMAKE_CURRENT_SOURCE_DIR}/src/timer.c"
"${CMAKE_CURRENT_SOURCE_DIR}/src/usart.c"
main.c
board.h
clock_config.h
mcux_config.h
peripherals.h
pin_mux.h
"${CMAKE_CURRENT_SOURCE_DIR}/src/adc.h"
"${CMAKE_CURRENT_SOURCE_DIR}/src/adc.h"
"${CMAKE_CURRENT_SOURCE_DIR}/src/button.h"
"${CMAKE_CURRENT_SOURCE_DIR}/src/led.h"
"${CMAKE_CURRENT_SOURCE_DIR}/src/timer.h"
"${CMAKE_CURRENT_SOURCE_DIR}/src/usart.h"
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    /..
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

include(${SdkRootDirPath}/boards/lpc845breakout/demo_apps/new_project/armgcc/flags.cmake)
include(${SdkRootDirPath}/boards/lpc845breakout/demo_apps/new_project/armgcc/config.cmake) 
include(${SdkRootDirPath}/devices/LPC845/all_lib_device.cmake)

IF(NOT DEFINED TARGET_LINK_SYSTEM_LIBRARIES)  
    SET(TARGET_LINK_SYSTEM_LIBRARIES "-lm -lc -lgcc -lnosys")  
ENDIF()  

TARGET_LINK_LIBRARIES(${MCUX_SDK_PROJECT_NAME} PRIVATE -Wl,--start-group)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE ${TARGET_LINK_SYSTEM_LIBRARIES})

TARGET_LINK_LIBRARIES(${MCUX_SDK_PROJECT_NAME} PRIVATE -Wl,--end-group)

ADD_CUSTOM_COMMAND(TARGET ${MCUX_SDK_PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_OBJCOPY}
-Obinary ${EXECUTABLE_OUTPUT_PATH}/${MCUX_SDK_PROJECT_NAME} ${EXECUTABLE_OUTPUT_PATH}/tp1.bin)

set_target_properties(${MCUX_SDK_PROJECT_NAME} PROPERTIES ADDITIONAL_CLEAN_FILES "output.map;${EXECUTABLE_OUTPUT_PATH}/tp1.bin")

# wrap all libraries with -Wl,--start-group -Wl,--end-group to prevent link order issue
group_link_libraries()
