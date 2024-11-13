cmsenv
cd include
make
cd ..
make
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PWD/include
