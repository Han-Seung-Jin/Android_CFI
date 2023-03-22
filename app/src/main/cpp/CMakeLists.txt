# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.22.1)
# add compile options
set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -Wl,--no-randomize-executable")
add_compile_options(-Wl,-z,norelro -D_FORTIFY_SOURCE=0 -Wno-implicit-int-conversion -fno-sanitize=address -fsanitize=cfi -fsanitize-cfi-cross-dso -fvisibility=hidden -flto -fno-stack-protector -g)
# Declares and names the project.


project("myapplication3")

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library.
        libhello-test

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        libhello-test.h
        libhello-test.cpp
        )
add_library( # Sets the name of the library.
        libhello-jnicallback

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        libhello-jnicallback.cpp
        )

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.
target_link_libraries( # Specifies the target library.
        libhello-test
        -Wl,-z,norelro
        )
target_link_libraries( # Specifies the target library.
        libhello-jnicallback
        -Wl,-z,norelro
        libhello-test
        )
