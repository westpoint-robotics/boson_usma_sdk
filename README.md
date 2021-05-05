# FLIR Boson SDK modified by the RRC for USMA
- This SDK is based on the FLIR "Boson SDK" located at: https://www.flir.com/support/products/boson/#Downloads
- Modifications were made to enable the compiled shared libraries to work when compiled against CPP projects.
- Other changes involved modifying the compiling and linking commands.

# Only the ClientFiles_C were used and tested, everything else is provided for completeness.

## To make this work
- Copy the libboson.so file and the FSLP_64.so file to a shared library location and link to them in the make file
- Copy the header files from ClientFiles_C to a shared include location and point the compiler to them

## A working example project that returns some camera info can be found in the TestFolder directory.

# Example code in the Test folder built with this command:
- `cc -I/usr/local/include/boson bosontest.cpp /usr/local/lib/libboson.so /usr/local/lib/libboson.so /home/user1/Projects/ConvergenceCamera/convergence_camera/BosonSDK/FSLP_Files/FSLP_64.so -o bosontest -lstdc++`

# Other commands used
- `sudo cp ~/Projects/ConvergenceCamera/convergence_camera/BosonSDK/ClientFiles_C/libboson.so /usr/local/lib/`
- `sudo cp ~/Projects/ConvergenceCamera/convergence_camera/BosonSDK/ClientFiles_C/*.h /usr/local/include/boson/`


# To help identify the functions in the .so file:
- nm -A /usr/local/lib/libboson.so | grep Init
- readelf --dyn-syms /usr/local/lib/libboson.so | grep Init



