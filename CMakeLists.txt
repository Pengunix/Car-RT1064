# CROSS COMPILER SETTING
set(CMAKE_SYSTEM_NAME Generic)
cmake_minimum_required(VERSION 3.10)

# THE VERSION NUMBER
set(MCUXPRESSO_CMAKE_FORMAT_MAJOR_VERSION 2)
set(MCUXPRESSO_CMAKE_FORMAT_MINOR_VERSION 0)

include(ide_overrides.cmake OPTIONAL)

if(CMAKE_SCRIPT_MODE_FILE)
    message("${MCUXPRESSO_CMAKE_FORMAT_MAJOR_VERSION}")
    return()
endif()

project(iled_blinky)

# ENABLE ASM
enable_language(ASM)

set(CMAKE_STATIC_LIBRARY_PREFIX)
set(CMAKE_STATIC_LIBRARY_SUFFIX)

set(CMAKE_EXECUTABLE_LIBRARY_PREFIX)
set(CMAKE_EXECUTABLE_LIBRARY_SUFFIX)
set(CMAKE_EXPORT_COMPILE_COMMANDS on)

# CURRENT DIRECTORY
set(ProjDirPath ${CMAKE_CURRENT_SOURCE_DIR})

set(EXECUTABLE_OUTPUT_PATH ${ProjDirPath}/${CMAKE_BUILD_TYPE})
set(LIBRARY_OUTPUT_PATH ${ProjDirPath}/${CMAKE_BUILD_TYPE})

set(MCUX_BUILD_TYPES debug release sdram_debug sdram_release flexspi_nor_debug flexspi_nor_release)

set(MCUX_SDK_PROJECT_NAME iled_blinky.elf)

if(NOT DEFINED SdkRootDirPath)
    set(SdkRootDirPath ${ProjDirPath}/../sdk)
endif()

include(${ProjDirPath}/flags.cmake)

include(${ProjDirPath}/config.cmake)

add_executable(${MCUX_SDK_PROJECT_NAME}
    "${ProjDirPath}/src/led_blinky.c"
    "${ProjDirPath}/src/pin_mux.c"
    "${ProjDirPath}/src/board.c"
    "${ProjDirPath}/src/clock_config.c"
    "${ProjDirPath}/src/dcd.c"
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${ProjDirPath}/include
    $ENV{ARMGCC_DIR}/arm-none-eabi/include
)


include(${SdkRootDirPath}/devices/MIMXRT1064/all_lib_device.cmake)

if(NOT DEFINED TARGET_LINK_SYSTEM_LIBRARIES)
    set(TARGET_LINK_SYSTEM_LIBRARIES "-lm -lc -lgcc -lnosys")
endif()

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE -Wl,--start-group)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE ${TARGET_LINK_SYSTEM_LIBRARIES})

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE -Wl,--end-group)

set_target_properties(${MCUX_SDK_PROJECT_NAME} PROPERTIES ADDITIONAL_CLEAN_FILES "output.map")

