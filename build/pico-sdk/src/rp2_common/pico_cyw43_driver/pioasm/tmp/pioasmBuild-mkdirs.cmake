# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "/mnt/c/Users/Pentest1/Downloads/PicoPiFi/pico-sdk/tools/pioasm")
  file(MAKE_DIRECTORY "/mnt/c/Users/Pentest1/Downloads/PicoPiFi/pico-sdk/tools/pioasm")
endif()
file(MAKE_DIRECTORY
  "/mnt/c/Users/Pentest1/Downloads/PicoPiFi/build/pioasm"
  "/mnt/c/Users/Pentest1/Downloads/PicoPiFi/build/pioasm-install"
  "/mnt/c/Users/Pentest1/Downloads/PicoPiFi/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/tmp"
  "/mnt/c/Users/Pentest1/Downloads/PicoPiFi/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src/pioasmBuild-stamp"
  "/mnt/c/Users/Pentest1/Downloads/PicoPiFi/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src"
  "/mnt/c/Users/Pentest1/Downloads/PicoPiFi/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src/pioasmBuild-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/mnt/c/Users/Pentest1/Downloads/PicoPiFi/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src/pioasmBuild-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/mnt/c/Users/Pentest1/Downloads/PicoPiFi/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src/pioasmBuild-stamp${cfgdir}") # cfgdir has leading slash
endif()
