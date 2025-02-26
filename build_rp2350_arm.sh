rm -rf build-pico2
mkdir -p build-pico2

export AWTK_PICO_ROOT=`pwd`
export PICO_BOARD="pico2"
export PICO_PLATFORM="rp2350"
export PICO_TOOLCHAIN_PATH="/opt/arm-gnu-toolchain-14.2.rel1-x86_64-arm-none-eabi"

cmake -S . -B build-pico2  -DPICO_PLATFORM="rp2350" -DPICO_BOARD="pico2" -DPICO_RP2350=1 -DCMAKE_BUILD_TYPE=Release -G Ninja
cmake --build build-pico2 --config Release -j24

