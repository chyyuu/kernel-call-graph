all: pass.so buggy.bc

CPPFLAGS += -fPIC
CPPFLAGS += -I /opt/llvm/4.0.1/include
CPPFLAGS += -std=c++11 -I`llvm-config --includedir` --no-rtti

LDFLAGS += -shared
# LDFLAGS += -shared -L`llvm-config --libdir` `llvm-config --libs`
# LDFLAGS += -L /opt/llvm/4.0.1/lib -lLLVMCore -lLLVMSupport -lLLVMAnalysis

pass.o : pass.cpp
	gcc -c -o $@ $< $(CPPFLAGS)

pass.so: pass.o
	gcc -o $@ $< $(LDFLAGS)

buggy.bc: buggy.c
	clang -emit-llvm -c $<

run: pass.so buggy.bc
	opt -load ./pass.so -disable-output -play buggy.bc 2>cg.txt
clean:
	rm buggy.bc pass.o pass.so cg.txt
