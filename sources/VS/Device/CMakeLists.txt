# (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by

project (Device)

set(CMAKE_UNITY_BUILD OFF)

include_directories(.
                    Device
                    ../../Device/src
                    ../../Device/src/Hardware/CDC
                    ../../Device/src/Hardware/HAL
                    ../../VS/ThirdParty/wxWidgets/include 
                    ../../generated/ThirdParty/lib/vc_dll/mswud
                    ../../common/_VS_KEIL/CMSIS
                    ../../common/_VS_LIBS/STM32F1
                    ../../common/STM32Cube_F1/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc
                    ../../common/STM32Cube_F1/Middlewares/ST/STM32_USB_Device_Library/Core/Inc
                    ../../common/STM32Cube_F1/Drivers/CMSIS/Device/ST/STM32F1xx/Include
                    ../../common/STM32Cube_F1/Drivers/STM32F1xx_HAL_Driver/Inc)

link_directories(../../generated/ThirdParty/lib/vc_dll)

add_definitions(-DSTM32F103xB -DWXUSINGDLL -DGUI -DDEVICE)

if(WIN32)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -MP -Wall")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")

    add_compile_options(/wd4005)
    add_compile_options(/wd4100)
    add_compile_options(/wd4255)
    add_compile_options(/wd4365)
    add_compile_options(/wd4464)
    add_compile_options(/wd4548)
    add_compile_options(/wd4514)
    add_compile_options(/wd4623)
    add_compile_options(/wd4625)
    add_compile_options(/wd4626)
    add_compile_options(/wd4774)
    add_compile_options(/wd4820)
    add_compile_options(/wd4996)
    add_compile_options(/wd5026)
    add_compile_options(/wd5027)
    add_compile_options(/wd5039)    # 'xxx': pointer or reference to potentially throwing function passed to extern C
                                    # function under -EHc.
    add_compile_options(/wd5045)
    add_compile_options(/wd5220)
    add_compile_options(/wd26812)
endif()

file(GLOB LIBS_STM32F1          ../../common/_VS_LIBS/STM32f1/*.*)
file(GLOB LIBS_USBD             ../../common/_VS_LIBS/USBD/*.*)
file(GLOB SRC                   *.h *.cpp
                                ../../Device/src/defines.h
                                ../../Device/src/Device.*)
file(GLOB DISPLAY               ../../Device/src/Display/*.*)
file(GLOB DISPLAY_FONT          ../../Device/src/Display/Font/*.*)
file(GLOB HARDWARE              ../../Device/src/Hardware/*.*)
file(GLOB HARDWARE_CDC          ../../Device/src/Hardware/CDC/*.*
                                                 Hardware/CDC/*.*)
file(GLOB HARDWARE_HAL          ../../Device/src/Hardware/HAL/*.*
                                                 Hardware/HAL/*.*)
file(GLOB HARDWARE_I2C          ../../Device/src/Hardware/I2C/*.*)
file(GLOB HARDWARE_LAN                           Hardware/LAN/*.*)
file(GLOB HARDWARE_LAN_LIBNET                    Hardware/LAN/libnet/*.*)
file(GLOB UTILS                 ../../Device/src/Utils/*.*)
file(GLOB UTILS_TEXT            ../../Device/src/Utils/Text/*.*)

source_group(libs/STM32F1        FILES ${LIBS_STM32F1})
source_group(libs/USBD           FILES ${LIBS_USBD})
source_group(src                 FILES ${SRC})
source_group(Display             FILES ${DISPLAY})
source_group(Display/Font        FILES ${DISPLAY_FONT})
source_group(Hardware            FILES ${HARDWARE})
source_group(Hardware/CDC        FILES ${HARDWARE_CDC})
source_group(Hardware/HAL        FILES ${HARDWARE_HAL})
source_group(Hardware/I2C        FILES ${HARDWARE_I2C})
source_group(Hardware/LAN        FILES ${HARDWARE_LAN})
source_group(Hardware/LAN/libnet FILES ${HARDWARE_LAN_LIBNET})
source_group(Utils               FILES ${UTILS})
source_group(Utils/Text          FILES ${UTILS_TEXT})


set_source_files_properties(../../Device/src/Hardware/CDC/usbd_conf.c
                            PROPERTIES HEADER_FILE_ONLY TRUE)

add_executable( ${PROJECT_NAME}
                ${LIBS_STM32F1}
                ${LIBS_USBD}
                ${SRC}
                ${DISPLAY}
                ${DISPLAY_FONT}
                ${HARDWARE}
                ${HARDWARE_CDC}
                ${HARDWARE_HAL}
                ${HARDWARE_I2C}
                ${HARDWARE_LAN}
                ${HARDWARE_LAN_LIBNET}
                ${UTILS}
                ${UTILS_TEXT}
)

target_link_libraries(${PROJECT_NAME} wxbase31ud wxmsw31ud_core Ws2_32)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND copy ..\\..\\ThirdParty\\lib\\vc_dll\\wxbase316ud_vc_custom.dll $(OutputPath) /Y)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND copy ..\\..\\ThirdParty\\lib\\vc_dll\\wxmsw316ud_core_vc_custom.dll $(OutputPath) /Y)
