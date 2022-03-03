---
layout: page
permalink: /Doc/
title: GDB Instruction
---

# GDB

**关闭-o优化，打开-g调试，打开-Wall提示所有warning**

**-g是在可执行文件中嵌入源代码，但不是整个放入，而是可以知道源代码的第几行对应机器指令的第几行。因此gdb需要可以找到源代码**

- 生成可执行的debug文件test：
`gcc test.c test -g -Wall`
- 进入gdb：
`gdb test`
- 退出：`quit`
- 设置参数：
`set args var1 var2`
- 获取参数：
`show args`
- 查看当前文件代码：
    - `list/l` 从默认位置开始
    - `l 20` 看20行附近
    - `l func` 看函数附近
- 查看**非当前文件**代码：
    - `l 文件名：行数`
    - `l 文件名：函数名`
显示代码时显示行数： `set nu`
设置一次显示多少行： `set listsize 20`
