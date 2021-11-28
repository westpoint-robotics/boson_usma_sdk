# FLIR Boson SDK modified by the RRC for USMA
- This SDK is based on the FLIR "Boson SDK" located at: https://www.flir.com/support/products/boson/#Downloads
- Modifications were made to enable the compiled shared libraries to work when compiled against CPP projects.
- Other changes involved modifying the compiling and linking commands.

# Only the ClientFiles_C were used and tested, everything else is provided for completeness.

## Udev Setup
- The boson camera when plugged in to the computer should map to two devices.  
    - One is in the `tty` subsystem (/dev/ttyACM#) and is used for sending control commands to the camera. 
    - Second one is in the `video4linux` subsystem (/dev/video#) and provides access to streaming video. 
- To avoid conflict with other devices using the same subsystems you can use the below UDEV rules.
    - `echo 'SUBSYSTEM=="tty", ATTRS{idVendor}=="09cb", ATTRS{idProduct}=="4007", GROUP="dialout", SYMLINK="boson_serial"' | sudo tee -a /etc/udev/rules.d/90-boson.rules > /dev/null`
    - `echo 'SUBSYSTEM=="video4linux", ATTRS{name}=="Boson*", GROUP="dialout", SYMLINK="boson_video"' | sudo tee -a /etc/udev/rules.d/90-boson.rules > /dev/null`
- Then reload the udev rules
    - `sudo udevadm control --reload-rules`
- The example code uses a "port_num" to identify the device name to connect to, "port_num" is an enum found in serialPortAdapter.c file. I changed the last enum value to be `/dev/boson_serial`. So now when port_num == 47, the code attempts to connect to `/dev/boson_serial`


## Build and install the SDK code
- `cd ClientFiles_C`
- `bash do_build.sh`
- `sudo cp libboson.so /usr/local/lib/`
- `sudo mkdir /usr/local/include/boson`
- `sudo cp *.h /usr/local/include/boson/`
- `sudo cp ../FSLP_Files/FSLP_64.so /usr/local/lib/libFSLP.so`
- `sudo chmod 777 /usr/local/lib/libFSLP.so`
- `sudo ldconfig`

## Test install and camera code
- `cd ../TestFolder`
- Note: it takes about 1 minute for the camera to compete its boot process after being plugged in.  
`gcc bosontest.cpp -o bosontest -lstdc++ -lboson -lFSLP`
- Run the test code to get camera info  
`./bosontest`




