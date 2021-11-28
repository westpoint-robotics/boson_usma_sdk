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
    - `echo 'SUBSYSTEM=="tty", ATTRS{idVendor}=="09cb", ATTRS{idProduct}=="4007", GROUP="dialout", SYMLINK="boson_ser"' | sudo tee -a /etc/udev/rules.d/90-boson.rules > /dev/null`
    - `echo 'SUBSYSTEM=="video4linux", ATTRS{name}=="Boson*", GROUP="dialout", SYMLINK="boson_video", ATTR{index}=="0"' | sudo tee -a /etc/udev/rules.d/90-boson.rules > /dev/null`
- Then reload the udev rules
    - `sudo udevadm control --reload-rules`
- The example code uses a "port_num" to identify the device name to connect to, "port_num" is an enum found in serialPortAdapter.c file. I changed the last enum value to be `/dev/boson_ser`. So now when port_num == 47, the code attempts to connect to `/dev/boson_ser`
- The source code limits the length of device strings to 16 characters. This limit is hardcode at more than one place. Instead of chasing them all down, I opted to shorten `/dev/boson_serial` to `/dev/boson_ser`

## Build and install the SDK code
- This process is all done in a script and can be run with:  
`bash buildAndInstall.sh`
- You can test this with the command:  
`TestFolder/bosonsynch s`

## Test install and camera code
- `cd ../TestFolder`
- Note: it takes time for the camera to compete its boot process after being plugged in. Documentation says 3 seconds, but it seems to take longer sometimes.  
`gcc bosontest.cpp -o bosontest -lstdc++ -lboson -lFSLP`
- Run the test code to get camera info  
`./bosontest`
