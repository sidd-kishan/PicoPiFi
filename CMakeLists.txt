cmake_minimum_required(VERSION 3.16)

# We prefer to have all linked submodules at toplevel
#set(PICO_TINYUSB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/tinyusb)
set(PICO_BOARD pico_w)
include(pico-sdk/pico_sdk_init.cmake)
project(pico_webserver)
pico_sdk_init()

set(MAKE_FS_DATA_SCRIPT ${CMAKE_CURRENT_LIST_DIR}/makefsdata)
message("Running makefsdata script")
execute_process(COMMAND
        perl ${MAKE_FS_DATA_SCRIPT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
        ECHO_OUTPUT_VARIABLE
        ECHO_ERROR_VARIABLE
        )


# Extra stuff from TinyUSB, that is not part of tinyusb_device library
set(TINYUSB_LIBNETWORKING_SOURCES
	${PICO_TINYUSB_PATH}/lib/networking
)

add_executable(${PROJECT_NAME} webserver.c tusb_lwip_glue.c usb_descriptors.c ${TINYUSB_LIBNETWORKING_SOURCES}/rndis_reports.c wifi_code.c)

pico_enable_stdio_usb(${PROJECT_NAME} 0)
pico_enable_stdio_uart(${PROJECT_NAME} 0)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${TINYUSB_LIBNETWORKING_SOURCES})
target_link_libraries(${PROJECT_NAME} pico_stdlib tinyusb_device pico_cyw43_arch_none pico_lwip pico_multicore)
pico_add_extra_outputs(${PROJECT_NAME})
target_compile_definitions(${PROJECT_NAME} PRIVATE PICO_ENTER_USB_BOOT_ON_EXIT=1)
