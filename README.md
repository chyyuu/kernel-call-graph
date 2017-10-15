# kernel-call-graph

## try to find buggy path

### ideas
 1. 第一步，我需要找到调用了might_sleep(用M表示)的所有call graph路径.  A-->...-->{...M...}-->Z
 1. 第二步，然后分析这些路径中位于M之前的函数集合是否有属于atomic_context的，且没有改变，把此属性一直传递到M，就出错了。

### problems
 1. 广度：如何得到尽量完整的call graph? 如何解决函数指针问题？
 1. 精度：如何加入path-sensitive信息？提高 call graph的精度？
 1. atomic_context的识别？何时enable? 何时disable? 需要体现在 node中

### example
buggy.c 是一个程序，其生成的call graph为g.txt

```
o 
e 
f e 
d might_sleep f 
c d 
b c 
intr_atomic b o 
a b f 
sys_read a o 
foo printf 
main foo a 
```

这是用pass.cpp生成出来的。
下面的路径是non-atomic path A，这是从syscall的起始出发，最终由于等待等原因，调用了might_sleep

```
sys_read-->a-->b-->c-->d-->might_sleep 
```

下面的路径是atomic path B，这是一个中断处理路径

```
intr_atomic--> b -->c -->d --> might_sleep

```

由于调度或中断原因在执行path A过程中，会出现中断，导致path B也会执行，就会出现rt bug。



