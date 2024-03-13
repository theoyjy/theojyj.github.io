---
finished: false
---

_[homepage](../index.md)_

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

- b 10 在第十行增加breakpoint
- b func
- b file : func
- b file : line
- d 断点编号
- dis/disable 断电编号
- ena/enable 断点编号
- b 10 if i==5 设置条件断点
- i b 显示所有断点
- r 运行程序
- c/continue
- n next 逐行调试
- p/print var 打印变量
- ptype var  打印变量类型
- s/step 向下单步调试
- finish 跳出函数体
- dispaly var 自动打印变量值
- i/info diplay
- undisplay 编号
- until 跳出循环


