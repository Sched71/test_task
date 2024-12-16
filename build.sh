if [[ ! -d "googletest" ]] ; then
    git clone https://github.com/google/googletest/ 
fi

mkdir -p build
cd build
rm CMakeCache.txt
cmake ..
make