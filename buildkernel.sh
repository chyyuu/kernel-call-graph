cd linux
make mrproper
make CC=clang HOSTCC=clang AS=llvm-as defconfig O=../buildl5
make CC=clang HOSTCC=clang AS=llvm-as  O=../buildl5 -j2

