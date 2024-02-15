# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/mnt/c/Users/Aayush/Desktop/pico-webserver/pico-sdk/tools/pioasm"
  "/mnt/c/Users/Aayush/Desktop/pico-webserver/build/pioasm"
  "/mnt/c/Users/Aayush/Desktop/pico-webserver/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm"
  "/mnt/c/Users/Aayush/Desktop/pico-webserver/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/tmp"
  "/mnt/c/Users/Aayush/Desktop/pico-webserver/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src/PioasmBuild-stamp"
  "/mnt/c/Users/Aayush/Desktop/pico-webserver/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src"
  "/mnt/c/Users/Aayush/Desktop/pico-webserver/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src/PioasmBuild-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/mnt/c/Users/Aayush/Desktop/pico-webserver/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src/PioasmBuild-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/mnt/c/Users/Aayush/Desktop/pico-webserver/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src/PioasmBuild-stamp${cfgdir}") # cfgdir has leading slash
endif()
