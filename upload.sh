PROGRAM=$1

if [ "$#" -eq 0 ]; then
  echo "$0 program"
  echo "ex: $0 ./build_rp2040/src/demos/app.elf"
else  
  sudo openocd -f interface/cmsis-dap.cfg -f target/rp2040.cfg -c "adapter speed 5000" -c "program $PROGRAM verify reset exit"
fi

