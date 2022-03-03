_[homepage](../index.md)_

# Makefile
**自动编译，自动检测文件更新
依赖文件的修改时间若晚于目标文件，make时会重新编译，否则不会**
```
Makefile:
  目标:依赖文件
    规则
```

**通过make去执行makefile**

- 定义变量:       src= main.c add.c div.c mul.c
- 获取变量:       $(src)
- 获取对应文件:   $(wildcard /*.c)：
- 重新定义变量:   src=$(wildcard ./*.c)
- 替代字符：      objs = $(patsubst %.c, %.o, $(src)) //将所有与%.c匹配的，替换成.o

生成目标文件：
```
main.o:main.c
gcc -c main.c -o main.o

add.o:add.c
gcc -c add.c -o add.o
……
```
==>
**为每一个.c汇编成.o，`$<`表示此依赖队列里的第一个文件，生成相应的目标文件**
```
%.o:%.c
  $(CC) -c $<  -o $@
```

  - $(AR) 为ar归档，制作静态库
  - $(CC) 为gcc
  - $(CXX) 为g++
  - $<为第一个依赖
  - $^为所有依赖
  - $@为目标
  - % 通配符，匹配字符串

# 最终的Makefile:
```
src=$(wildcard ./*.c)
objs = $(patsubst %.c,%.o,$(src))
target=app
$(target):$(objs)
  $(CC) $(objs) -o $(target)
%.o:%.c
  $(CC) -c $<  -o $@

.PHONY:clean
clean:
  rm $(objs) -f
```
#  make clean 会执行删除多余中间文件
但若存在一个命为clean的文件，由于clean没有依赖，认为是最新版本，不执行相关操作，因此要声明目标clean为假文件，与文件clean不做对比

