cmsenv
cd include
make clean
cd ..
make clean
cd include
make
cd ..
make
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PWD/include
