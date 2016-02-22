
define ANDROID_NDK environment variable as the root path of NDK.

             
###gles3 armeabi

    mkdir build_android_shared_gles3_armeabi && cd build_android_shared_gles3_armeabi

    cmake .. -DCMAKE_TOOLCHAIN_FILE=../PlatformSpecifics/Android/android.toolchain.cmake  \
             -DOPENGL_PROFILE="GLES3" \
             -DDYNAMIC_OPENTHREADS=OFF \
             -DDYNAMIC_OPENSCENEGRAPH=OFF \
             -DANDROID_NATIVE_API_LEVEL=android-18 \
             -DANDROID_ABI=armeabi \
             -DCMAKE_INSTALL_PREFIX=./install-path \
             -DANDROID_TOOLCHAIN_NAME=arm-linux-androideabi-clang3.5 \
             -DANDROID_STL=gnustl_shared \
             -DLIBRARY_OUTPUT_PATH=./output
       
###gles3 armeabiv7a
       
    mkdir build_android_shared_gles3_armeabiv7a && cd build_android_shared_gles3_armeabiv7a

    cmake .. -DCMAKE_TOOLCHAIN_FILE=../PlatformSpecifics/Android/android.toolchain.cmake  \
             -DOPENGL_PROFILE="GLES3" \
             -DDYNAMIC_OPENTHREADS=OFF \
             -DDYNAMIC_OPENSCENEGRAPH=OFF \
             -DANDROID_NATIVE_API_LEVEL=android-18 \
             -DANDROID_ABI=armeabi-v7a \
             -DCMAKE_INSTALL_PREFIX=./install-path \
             -DANDROID_TOOLCHAIN_NAME=arm-linux-androideabi-clang3.5 \
             -DANDROID_STL=gnustl_shared \
             -DLIBRARY_OUTPUT_PATH=./output
             
