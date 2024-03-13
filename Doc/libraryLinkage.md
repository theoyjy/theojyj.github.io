---
finished: false
---

_[homepage](../index.md)_

# 静态链接：
```
g++ -c file.cpp //生成目标文件
at rcs libtest.a file.o//生产静态链接库
g++ main.c -l test -L ./lib -I ./Include//-l 后加库名 -L 后为静态库的地址 -I后为.h文件地址
```

# 动态链接
```
gcc -c -fpic file.cpp //生产与位置无关的目标文件
gcc -shared file.o -o libfile.so//生成动态库
gcc main.c -o main -l file -I /Include//生产可执行文件
```
1. ldd 命令可检查动态库依赖关系
2. 动态库需要源文件的绝对路径：
  - 在vim .bashrc (~根目录下)中设置环境变量 或在vim /etc/profile 中
    - LD_LIBRARY_PATH=$LD_LIBRARY_PATH : 绝对路径
    - source .bashrc 为bash load 变化
  - 在vim /etc/ld.so.conf 中
    - 直接添加绝对路径
    - sudo ldconfig 
# 对比：
- **静态库加载更快，但不适合大型应用，要全部装入内存，不适合更新，每次更新，所有使用到该静态库的应用要全部重新编译**
- **动态库适合体量大、更新多的、版本多的，发布简单。可以控制何时加载动态库。有利于进程间资源的共享，被一个进程加载入内存，别的进程也可以使用。但速度慢，发布时需要提供依赖的动态库**
