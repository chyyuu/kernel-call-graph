find . -name "*.bc" -exec opt -load /home/osresearch/chenyu/kernel-call-graph/pass.so -disable-output -play  {} \; 2>allfuns.txt
