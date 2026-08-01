# targetfinder.pri

#This file is specifically made to automatically check out operating system and compiler and the
#ultimate need to do this is to make a destination path where our compiled products are stored so as to make
#our project structure elaborated

win32 {
    # This block is executed only if the build is happening on a Windows platform.

    CONFIG += PLATFORM_WIN
    # Adds 'PLATFORM_WIN' to the CONFIG variable, indicating the platform is Windows.

    message(PLATFORM_WIN)
    # Outputs 'PLATFORM_WIN' to the console to indicate this configuration path is taken.

    win32-g++ {
        # This nested block is executed only if the compiler is MinGW (GCC for Windows).

        CONFIG += COMPILER_GCC
        # Adds 'COMPILER_GCC' to the CONFIG variable, indicating the compiler is GCC.

        message(COMPILER_GCC)
        # Outputs 'COMPILER_GCC' to the console to indicate this configuration path is taken.

        # Check if 64-bit is enabled in the QMAKE_HOST.arch
        contains(QMAKE_HOST.arch, x86_64): QMAKE_TARGET.arch = x86_64
        # If the host architecture is 64-bit (x86_64), sets the target architecture to 64-bit.
    }

    win32-msvc2017 {
        # This nested block is executed only if the compiler is MSVC 2017.

        CONFIG += COMPILER_MSVC2017
        # Adds 'COMPILER_MSVC2017' to the CONFIG variable, indicating the compiler is MSVC 2017.

        message(COMPILER_MSVC2017)
        # Outputs 'COMPILER_MSVC2017' to the console to indicate this configuration path is taken.

        # Manually set architecture for MSVC 2017
        QMAKE_TARGET.arch = x86_64
        # Sets the target architecture to 64-bit manually for MSVC 2017.
    }
}

linux {
    CONFIG += PLATFORM_LINUX
    message(PLATFORM_LINUX)
    # Make QMAKE_TARGET arch available for Linux
    !contains(QT_ARCH, x86_64) {
        QMAKE_TARGET.arch = x86
    } else {
        QMAKE_TARGET.arch = x86_64
    }
    linux-g++ {
        CONFIG += COMPILER_GCC
        message(COMPILER_GCC)
    }
}

macx {
    CONFIG += PLATFORM_OSX
    message(PLATFORM_OSX)
    macx-clang {
        CONFIG += COMPILER_CLANG
        message(COMPILER_CLANG)
        QMAKE_TARGET.arch = x86_64
    }
    macx-clang-32 {
        CONFIG += COMPILER_CLANG
        message(COMPILER_CLANG)
        QMAKE_TARGET.arch = x86
    }
}

contains(QMAKE_TARGET.arch, x86_64) { #This condition checks if the target architecture contains the
                                       #substring x86_64, indicating a 64-bit architecture.
    CONFIG += PROCESSOR_x64
#If the target architecture is 64-bit, this line adds PROCESSOR_x64 to the CONFIG variable.
#This can be used elsewhere in the project file to conditionally include 64-bit specific settings.
    message(PROCESSOR_x64)
} else {
    CONFIG += PROCESSOR_x86
    message(PROCESSOR_x86)
}

CONFIG(debug, release|debug) {
#This condition checks if the build configuration includes debug. The syntax release|debug means
#that it checks if the current build configuration is debug within the context of release and debug configurations.
    CONFIG += BUILD_DEBUG
#If the build configuration is debug, this line adds BUILD_DEBUG to the CONFIG variable. This can be used to include
#debug-specific settings, such as enabling debug symbols or other debug-related options.
    message(BUILD_DEBUG)
} else {
    CONFIG += BUILD_RELEASE
    message(BUILD_RELEASE)
}
