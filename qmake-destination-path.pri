# destinationfinder.pri

platform_path = unknown-platform
compiler_path = unknown-compiler
processor_path = unknown-processor
build_path = unknown-build

#The above lines initializes our self-made new variables

PLATFORM_WIN {
#This checks if the "PLATFORM_WIN" is defined elsewhere including "CONFIG" variable
    platform_path = windows
#Changes our variable "platform_path" value to windows
}
PLATFORM_OSX {
    platform_path = osx
}
PLATFORM_LINUX {
    platform_path = linux
}

COMPILER_GCC {
    compiler_path = gcc
}
COMPILER_MSVC2017 {
    compiler_path = msvc2017
}
COMPILER_CLANG {
    compiler_path = clang
}

PROCESSOR_x64 {
    processor_path = x64
}
PROCESSOR_x86 {
    processor_path = x86
}

BUILD_DEBUG {
    build_path = debug
} else {
    build_path = release
}

DESTINATION_PATH = $$platform_path/$$compiler_path/$$processor_path/$$build_path

#The above variable "DESTINATION_PATH" make a path using our self-made variables. This path will be used
#in many ways to store our compiled products in our specific places making our project structure modularized

message(Dest path: $${DESTINATION_PATH})
