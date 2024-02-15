cmake_minimum_required(VERSION 3.16)

set(PICO_BOARD pico_w)
include(pico-sdk/pico_sdk_init.cmake)

#include(pico_extras_import_optional.cmake)

project(pico_examples C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.3.0")
    message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.3.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

set(PICO_EXAMPLES_PATH ${CMAKE_CURRENT_SOURCE_DIR})

set(PICO_LWIP_CORE_CODE ${PICO_EXAMPLES_PATH}/pico-sdk/lib/lwip/src/core/)
# Initialize the SDK
pico_sdk_init()

include(example_auto_set_url.cmake)

set(LWIP_DIR ${CMAKE_CURRENT_SOURCE_DIR}/pico-sdk/lib/lwip)
set (LWIP_INCLUDE_DIRS
    "${LWIP_DIR}/src/include"
    "${CMAKE_CURRENT_SOURCE_DIR}"
)


add_compile_options(-Wall
        -Wno-format          # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
        -Wno-unused-function # we have some for the docs that aren't called
        -Wno-maybe-uninitialized
        )

set(cherry_dir ${CMAKE_CURRENT_LIST_DIR}/CherryUSB/)

include_directories(${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/CherryUSB/class/cdc
    ${CMAKE_CURRENT_LIST_DIR}/CherryUSB/class/msc
    ${CMAKE_CURRENT_LIST_DIR}/CherryUSB/class/wireless

    ${CMAKE_CURRENT_LIST_DIR}/CherryUSB/common
    ${CMAKE_CURRENT_LIST_DIR}/CherryUSB/core
    ${CMAKE_CURRENT_LIST_DIR}/CherryUSB/demo
    ${CMAKE_CURRENT_LIST_DIR}/CherryUSB/port/rp2040
	#lwip directory:-
	${LWIP_INCLUDE_DIRS}
	#lwipopts.h ke liye
	${CMAKE_CURRENT_LIST_DIR}/src
	#arch/cc.h ke liye:-
	${CMAKE_CURRENT_LIST_DIR}/common
)


add_library(cherryusblib STATIC)
target_sources(cherryusblib PRIVATE ${CMAKE_CURRENT_LIST_DIR}/CherryUSB/port/rp2040/usb_dc_rp2040.c)
target_sources(cherryusblib PRIVATE ${CMAKE_CURRENT_LIST_DIR}/CherryUSB/class/cdc/usbd_cdc.c)
target_sources(cherryusblib PRIVATE ${CMAKE_CURRENT_LIST_DIR}/CherryUSB/class/msc/usbd_msc.c)
target_sources(cherryusblib PRIVATE ${CMAKE_CURRENT_LIST_DIR}/CherryUSB/class/wireless/usbd_rndis.c)
target_sources(cherryusblib PRIVATE ${CMAKE_CURRENT_LIST_DIR}/CherryUSB/core/usbd_core.c)

set(CONFIG_CHERRYUSB 1)
set(CONFIG_USB_DEVICE 1)
set(CONFIG_USB_DEVICE_RNDIS 1)
set(CONFIG_LWIP 1)
set(CONFIG_LWIP_HTTPSRV 1)

if("${CMAKE_BUILD_TYPE}" STREQUAL "")
    SET(CMAKE_BUILD_TYPE flash_xip)
endif()

project(PicoPiFi)

include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src ${PICO_EXAMPLES_PATH}/pico-sdk/lib/lwip/src/include ${PICO_EXAMPLES_PATH}/pico-sdk/lib/tinyusb/hw/bsp/rp2040)
add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/src/main.c ${CMAKE_CURRENT_SOURCE_DIR}/src/lwip.c ${CMAKE_CURRENT_SOURCE_DIR}/src/wifi_tx.c ${CMAKE_CURRENT_SOURCE_DIR}/src/cdc_rndis_device.c)


target_link_libraries(${PROJECT_NAME} PRIVATE pico_stdlib cherryusblib hardware_resets hardware_irq pico_lwip pico_multicore pico_cyw43_arch_none hardware_flash hardware_sync)
pico_add_extra_outputs(${PROJECT_NAME})
target_compile_definitions(${PROJECT_NAME} PRIVATE CYW43_SLEEP_CHECK_MS=3)