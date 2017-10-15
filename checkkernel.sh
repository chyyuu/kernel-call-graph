cd linux
make mrproper
make CC=clang HOSTCC=clang AS=llvm-as defconfig O=../buildl5
#make CC=clang HOSTCC=clang AS=llvm-as O=../buildl5 C=1 CHECK="/home/osresearch/chenyu/kernel-call-graph/linux-bc-gen" CHECKFLAGS ="" -j2 -k
make CC=clang HOSTCC=clang AS=llvm-as O=../buildl5 C=1 CHECK="/home/osresearch/chenyu/kernel-call-graph/clang-bc-gen"  -j2


