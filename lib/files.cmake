set(zfLibDir ${ProjDirPath}/lib/)
target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${zfLibDir}/zf_common
  ${zfLibDir}/zf_device
  ${zfLibDir}/zf_driver
)
file(GLOB_RECURSE ZF_SRCS ${zfLibDir}/*.c)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${ZF_SRCS}
)
