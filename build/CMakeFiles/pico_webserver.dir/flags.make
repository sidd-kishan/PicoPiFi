# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# compile ASM with /usr/bin/arm-none-eabi-gcc
# compile C with /usr/bin/arm-none-eabi-gcc
# compile CXX with /usr/bin/arm-none-eabi-g++
ASM_DEFINES = -DCFG_TUSB_MCU=OPT_MCU_RP2040 -DCFG_TUSB_OS=OPT_OS_PICO -DCYW43_LWIP=0 -DLIB_PICO_ASYNC_CONTEXT_THREADSAFE_BACKGROUND=1 -DLIB_PICO_BIT_OPS=1 -DLIB_PICO_BIT_OPS_PICO=1 -DLIB_PICO_CYW43_ARCH=1 -DLIB_PICO_DIVIDER=1 -DLIB_PICO_DIVIDER_HARDWARE=1 -DLIB_PICO_DOUBLE=1 -DLIB_PICO_DOUBLE_PICO=1 -DLIB_PICO_FIX_RP2040_USB_DEVICE_ENUMERATION=1 -DLIB_PICO_FLOAT=1 -DLIB_PICO_FLOAT_PICO=1 -DLIB_PICO_INT64_OPS=1 -DLIB_PICO_INT64_OPS_PICO=1 -DLIB_PICO_MALLOC=1 -DLIB_PICO_MEM_OPS=1 -DLIB_PICO_MEM_OPS_PICO=1 -DLIB_PICO_MULTICORE=1 -DLIB_PICO_PLATFORM=1 -DLIB_PICO_PRINTF=1 -DLIB_PICO_PRINTF_PICO=1 -DLIB_PICO_RUNTIME=1 -DLIB_PICO_STANDARD_LINK=1 -DLIB_PICO_STDIO=1 -DLIB_PICO_STDLIB=1 -DLIB_PICO_SYNC=1 -DLIB_PICO_SYNC_CRITICAL_SECTION=1 -DLIB_PICO_SYNC_MUTEX=1 -DLIB_PICO_SYNC_SEM=1 -DLIB_PICO_TIME=1 -DLIB_PICO_UNIQUE_ID=1 -DLIB_PICO_UTIL=1 -DLIB_TINYUSB_DEVICE=1 -DPICO_BOARD=\"pico_w\" -DPICO_BUILD=1 -DPICO_CMAKE_BUILD_TYPE=\"Release\" -DPICO_COPY_TO_RAM=0 -DPICO_CXX_ENABLE_EXCEPTIONS=0 -DPICO_CYW43_ARCH_THREADSAFE_BACKGROUND=1 -DPICO_ENTER_USB_BOOT_ON_EXIT=1 -DPICO_NO_FLASH=0 -DPICO_NO_HARDWARE=0 -DPICO_ON_DEVICE=1 -DPICO_RP2040_USB_DEVICE_UFRAME_FIX=1 -DPICO_TARGET_NAME=\"pico_webserver\" -DPICO_USE_BLOCKED_RAM=0

ASM_INCLUDES = -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/lib/lwip/src/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/lib/tinyusb/src -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/lib/tinyusb/lib/networking -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/common/pico_stdlib/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/hardware_gpio/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/common/pico_base/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/build/generated/pico_base -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/boards/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/pico_platform/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2040/hardware_regs/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/hardware_base/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2040/hardware_structs/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/hardware_claim/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/hardware_sync/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/hardware_irq/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/common/pico_sync/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/common/pico_time/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/hardware_timer/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/common/pico_util/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/hardware_uart/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/hardware_resets/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/hardware_clocks/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/hardware_pll/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/hardware_vreg/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/hardware_watchdog/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/hardware_xosc/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/hardware_divider/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/pico_runtime/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/pico_printf/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/common/pico_bit_ops/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/common/pico_divider/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/pico_double/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/pico_float/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/pico_malloc/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/pico_bootrom/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/common/pico_binary_info/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/pico_stdio/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/pico_int64_ops/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/pico_mem_ops/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/boot_stage2/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/pico_unique_id/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/hardware_flash/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/lib/tinyusb/src/common -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/lib/tinyusb/hw -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/pico_fix/rp2040_usb_device_enumeration/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/pico_cyw43_arch/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/lib/cyw43-driver/src -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/lib/cyw43-driver/firmware -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/pico_cyw43_driver/cybt_shared_bus -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/hardware_pio/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/hardware_dma/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/hardware_exception/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/pico_cyw43_driver/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/pico_async_context/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/build/pico-sdk/src/rp2_common/pico_cyw43_driver -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/pico_multicore/include

ASM_FLAGS = -mcpu=cortex-m0plus -mthumb -O3 -DNDEBUG -ffunction-sections -fdata-sections

C_DEFINES = -DCFG_TUSB_MCU=OPT_MCU_RP2040 -DCFG_TUSB_OS=OPT_OS_PICO -DCYW43_LWIP=0 -DLIB_PICO_ASYNC_CONTEXT_THREADSAFE_BACKGROUND=1 -DLIB_PICO_BIT_OPS=1 -DLIB_PICO_BIT_OPS_PICO=1 -DLIB_PICO_CYW43_ARCH=1 -DLIB_PICO_DIVIDER=1 -DLIB_PICO_DIVIDER_HARDWARE=1 -DLIB_PICO_DOUBLE=1 -DLIB_PICO_DOUBLE_PICO=1 -DLIB_PICO_FIX_RP2040_USB_DEVICE_ENUMERATION=1 -DLIB_PICO_FLOAT=1 -DLIB_PICO_FLOAT_PICO=1 -DLIB_PICO_INT64_OPS=1 -DLIB_PICO_INT64_OPS_PICO=1 -DLIB_PICO_MALLOC=1 -DLIB_PICO_MEM_OPS=1 -DLIB_PICO_MEM_OPS_PICO=1 -DLIB_PICO_MULTICORE=1 -DLIB_PICO_PLATFORM=1 -DLIB_PICO_PRINTF=1 -DLIB_PICO_PRINTF_PICO=1 -DLIB_PICO_RUNTIME=1 -DLIB_PICO_STANDARD_LINK=1 -DLIB_PICO_STDIO=1 -DLIB_PICO_STDLIB=1 -DLIB_PICO_SYNC=1 -DLIB_PICO_SYNC_CRITICAL_SECTION=1 -DLIB_PICO_SYNC_MUTEX=1 -DLIB_PICO_SYNC_SEM=1 -DLIB_PICO_TIME=1 -DLIB_PICO_UNIQUE_ID=1 -DLIB_PICO_UTIL=1 -DLIB_TINYUSB_DEVICE=1 -DPICO_BOARD=\"pico_w\" -DPICO_BUILD=1 -DPICO_CMAKE_BUILD_TYPE=\"Release\" -DPICO_COPY_TO_RAM=0 -DPICO_CXX_ENABLE_EXCEPTIONS=0 -DPICO_CYW43_ARCH_THREADSAFE_BACKGROUND=1 -DPICO_ENTER_USB_BOOT_ON_EXIT=1 -DPICO_NO_FLASH=0 -DPICO_NO_HARDWARE=0 -DPICO_ON_DEVICE=1 -DPICO_RP2040_USB_DEVICE_UFRAME_FIX=1 -DPICO_TARGET_NAME=\"pico_webserver\" -DPICO_USE_BLOCKED_RAM=0

C_INCLUDES = -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/lib/lwip/src/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/lib/tinyusb/src -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/lib/tinyusb/lib/networking -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/common/pico_stdlib/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/hardware_gpio/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/common/pico_base/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/build/generated/pico_base -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/boards/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/pico_platform/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2040/hardware_regs/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/hardware_base/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2040/hardware_structs/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/hardware_claim/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/hardware_sync/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/hardware_irq/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/common/pico_sync/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/common/pico_time/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/hardware_timer/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/common/pico_util/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/hardware_uart/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/hardware_resets/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/hardware_clocks/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/hardware_pll/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/hardware_vreg/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/hardware_watchdog/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/hardware_xosc/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/hardware_divider/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/pico_runtime/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/pico_printf/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/common/pico_bit_ops/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/common/pico_divider/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/pico_double/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/pico_float/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/pico_malloc/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/pico_bootrom/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/common/pico_binary_info/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/pico_stdio/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/pico_int64_ops/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/pico_mem_ops/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/boot_stage2/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/pico_unique_id/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/hardware_flash/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/lib/tinyusb/src/common -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/lib/tinyusb/hw -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/pico_fix/rp2040_usb_device_enumeration/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/pico_cyw43_arch/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/lib/cyw43-driver/src -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/lib/cyw43-driver/firmware -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/pico_cyw43_driver/cybt_shared_bus -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/hardware_pio/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/hardware_dma/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/hardware_exception/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/pico_cyw43_driver/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/pico_async_context/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/build/pico-sdk/src/rp2_common/pico_cyw43_driver -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/pico_multicore/include

C_FLAGS = -mcpu=cortex-m0plus -mthumb -O3 -DNDEBUG -ffunction-sections -fdata-sections

CXX_DEFINES = -DCFG_TUSB_MCU=OPT_MCU_RP2040 -DCFG_TUSB_OS=OPT_OS_PICO -DCYW43_LWIP=0 -DLIB_PICO_ASYNC_CONTEXT_THREADSAFE_BACKGROUND=1 -DLIB_PICO_BIT_OPS=1 -DLIB_PICO_BIT_OPS_PICO=1 -DLIB_PICO_CYW43_ARCH=1 -DLIB_PICO_DIVIDER=1 -DLIB_PICO_DIVIDER_HARDWARE=1 -DLIB_PICO_DOUBLE=1 -DLIB_PICO_DOUBLE_PICO=1 -DLIB_PICO_FIX_RP2040_USB_DEVICE_ENUMERATION=1 -DLIB_PICO_FLOAT=1 -DLIB_PICO_FLOAT_PICO=1 -DLIB_PICO_INT64_OPS=1 -DLIB_PICO_INT64_OPS_PICO=1 -DLIB_PICO_MALLOC=1 -DLIB_PICO_MEM_OPS=1 -DLIB_PICO_MEM_OPS_PICO=1 -DLIB_PICO_MULTICORE=1 -DLIB_PICO_PLATFORM=1 -DLIB_PICO_PRINTF=1 -DLIB_PICO_PRINTF_PICO=1 -DLIB_PICO_RUNTIME=1 -DLIB_PICO_STANDARD_LINK=1 -DLIB_PICO_STDIO=1 -DLIB_PICO_STDLIB=1 -DLIB_PICO_SYNC=1 -DLIB_PICO_SYNC_CRITICAL_SECTION=1 -DLIB_PICO_SYNC_MUTEX=1 -DLIB_PICO_SYNC_SEM=1 -DLIB_PICO_TIME=1 -DLIB_PICO_UNIQUE_ID=1 -DLIB_PICO_UTIL=1 -DLIB_TINYUSB_DEVICE=1 -DPICO_BOARD=\"pico_w\" -DPICO_BUILD=1 -DPICO_CMAKE_BUILD_TYPE=\"Release\" -DPICO_COPY_TO_RAM=0 -DPICO_CXX_ENABLE_EXCEPTIONS=0 -DPICO_CYW43_ARCH_THREADSAFE_BACKGROUND=1 -DPICO_ENTER_USB_BOOT_ON_EXIT=1 -DPICO_NO_FLASH=0 -DPICO_NO_HARDWARE=0 -DPICO_ON_DEVICE=1 -DPICO_RP2040_USB_DEVICE_UFRAME_FIX=1 -DPICO_TARGET_NAME=\"pico_webserver\" -DPICO_USE_BLOCKED_RAM=0

CXX_INCLUDES = -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/lib/lwip/src/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/lib/tinyusb/src -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/lib/tinyusb/lib/networking -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/common/pico_stdlib/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/hardware_gpio/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/common/pico_base/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/build/generated/pico_base -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/boards/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/pico_platform/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2040/hardware_regs/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/hardware_base/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2040/hardware_structs/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/hardware_claim/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/hardware_sync/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/hardware_irq/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/common/pico_sync/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/common/pico_time/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/hardware_timer/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/common/pico_util/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/hardware_uart/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/hardware_resets/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/hardware_clocks/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/hardware_pll/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/hardware_vreg/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/hardware_watchdog/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/hardware_xosc/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/hardware_divider/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/pico_runtime/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/pico_printf/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/common/pico_bit_ops/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/common/pico_divider/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/pico_double/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/pico_float/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/pico_malloc/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/pico_bootrom/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/common/pico_binary_info/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/pico_stdio/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/pico_int64_ops/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/pico_mem_ops/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/boot_stage2/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/pico_unique_id/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/hardware_flash/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/lib/tinyusb/src/common -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/lib/tinyusb/hw -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/pico_fix/rp2040_usb_device_enumeration/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/pico_cyw43_arch/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/lib/cyw43-driver/src -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/lib/cyw43-driver/firmware -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/pico_cyw43_driver/cybt_shared_bus -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/hardware_pio/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/hardware_dma/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/hardware_exception/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/pico_cyw43_driver/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/pico_async_context/include -I/mnt/c/Users/Aayush/Desktop/pico-webserver/build/pico-sdk/src/rp2_common/pico_cyw43_driver -I/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/src/rp2_common/pico_multicore/include

CXX_FLAGS = -mcpu=cortex-m0plus -mthumb -O3 -DNDEBUG -ffunction-sections -fdata-sections -fno-exceptions -fno-unwind-tables -fno-rtti -fno-use-cxa-atexit

