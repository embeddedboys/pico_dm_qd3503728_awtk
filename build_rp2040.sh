rm -rf build
mkdir -p build

export AWTK_PICO_ROOT=`pwd`
export PICO_PLATFORM="rp2040"
export PICO_TOOLCHAIN_PATH="/opt/arm-gnu-toolchain-14.2.rel1-x86_64-arm-none-eabi"

cmake -S . -B build  -DPICO_PLATFORM="rp2040" -DPICO_BOARD="pico" -DPICO_RP2040=1 -DCMAKE_BUILD_TYPE=Release -G Ninja
cmake --build build --config Release -j$(nproc)

ln -sf build/compile_commands.json .
