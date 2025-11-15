cmake_minimum_required(VERSION 3.13...3.27)

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(/usr/share/pico-sdk/external/pico_sdk_import.cmake)

project(xbox_controller CXX C ASM)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# rest of your project
add_executable(main
    main.c axes.c led.c
)

#enable serial via usb and uart
pico_enable_stdio_usb(main 1)
pico_enable_stdio_uart(main 1)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(main pico_stdlib hardware_adc hardware_pwm)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(main)
