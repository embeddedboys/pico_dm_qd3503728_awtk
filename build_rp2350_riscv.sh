rm -rf build-pico2-riscv
mkdir -p build-pico2-riscv

export AWTK_PICO_ROOT=`pwd`
export PICO_BOARD="pico2"
export PICO_PLATFORM="rp2350"
export PICO_TOOLCHAIN_PATH="/opt/riscv/corev-openhw-gcc-ubuntu2204-20240530/"

cmake -S . -B build-pico2-riscv  -DPICO_PLATFORM="rp2350-riscv" -DPICO_BOARD="pico2" -DPICO_RP2350=1 -DCMAKE_BUILD_TYPE=Release -G Ninja
cmake --build build-pico2-riscv --config Release -j$(nproc)

ln -sf build-pico2-riscv/compile_commands.json .
