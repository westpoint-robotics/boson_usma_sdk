#!/usr/bin/env bash


cd ClientFiles_C
bash do_build.sh
sudo cp libboson.so /usr/local/lib/
#sudo mkdir /usr/local/include/boson || :
sudo cp *.h /usr/local/include/boson/
cd ../FSLP_Files
make
cd ..
sudo cp FSLP_Files/FSLP_64.so /usr/local/lib/libFSLP.so
sudo chmod 777 /usr/local/lib/libFSLP.so
sudo ldconfig
