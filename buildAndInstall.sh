#!/usr/bin/env bash


cd ClientFiles_C
bash do_build.sh
sudo cp libboson.so /usr/local/lib/
#sudo mkdir /usr/local/include/boson
if [[ ! -e /usr/local/include/boson ]]; then
    mkdir /usr/local/include/boson
elif [[ ! -d /usr/local/include/boson ]]; then
    echo "/usr/local/include/boson already exists but is not a directory" 1>&2
    exit
fi
sudo cp *.h /usr/local/include/boson/
cd ../FSLP_Files
make
cd ..
sudo cp FSLP_Files/FSLP_64.so /usr/local/lib/libFSLP.so
sudo chmod 777 /usr/local/lib/libFSLP.so
sudo ldconfig
cd TestFolder/
gcc boson_synch.cpp -o bosonsynch -lstdc++ -lboson -lFSLP
gcc bosontest.cpp -o bosontest -lstdc++ -lboson -lFSLP
cd ..
echo ""
echo "If this worked then you should be able to run the command 'TestFolder/bosonsynch s' to put the camera into slave mode."
echo "If the last line of output from this command is 'Failed to initialize, exiting.' then it failed."
echo "If the second to last line of output from this command is 'Boson Synch mode set to 2' then it succedded."
echo "If it does not work make sure you setup the UDEV rules as per the README.md"

