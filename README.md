# FLIR Boson SDK modified by the RRC for USMA
- This SDK is based on the FLIR "Boson SDK" located at: https://www.flir.com/support/products/boson/#Downloads
- Modifications were made to enable the compiled shared libraries to work when compiled against CPP projects.
- Other changes involved modifying the compiling and linking commands.

# Only the ClientFiles_C were used and tested, everything else is provided for completeness.

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




