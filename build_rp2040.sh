rm -rf build_rp2040
mkdir -p build_rp2040

export AWTK_PICO_ROOT=`pwd`
export PICO_PLATFORM="rp2040"
export PICO_SDK_PATH="$AWTK_PICO_ROOT/3rd/pico-sdk"
export PICO_TOOLCHAIN_PATH="/opt/arm-gnu-toolchain-13.3.rel1-darwin-arm64-arm-none-eabi/bin"

cmake -S . -B build_rp2040  -DPICO_PLATFORM="rp2040" -DPICO_BOARD="pico" -DPICO_RP2040=1 -DCMAKE_BUILD_TYPE=Debug
cmake --build build_rp2040 --config Debug

