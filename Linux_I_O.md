## Liunx I/O
<img width="1230" alt="image" src="https://user-images.githubusercontent.com/41602569/156598820-2420e45d-912c-4e93-a4df-7268ba5422da.png">
<img width="1230" alt="image" src="https://user-images.githubusercontent.com/41602569/156598894-b4b43ed6-648b-4b2d-9907-3e1c0a05f1d0.png">


## 虚拟地址空间

<img width="1230" alt="image" src="https://user-images.githubusercontent.com/41602569/156595438-140b2347-4504-4246-ac84-7087ad30c923.png">

- 内存分为内核去与用户区，CPU中的MMU（内存管理单元 Memory Management Unit），将磁盘空间映射到内存空间
- 受保护地址：NULL, nullpty
- 通过系统调用，进入内核区

<img width="1230" alt="image" src="https://user-images.githubusercontent.com/41602569/156596784-7705d0a6-4dd6-44df-b164-b4af2413d69e.png">

- 文件描述符表(数组[] fd1,fd2...)在内核区，被进程控制块管理(PCB)
- 一个进程可以同时打开多个文件
- 文件描述符表默认是1024，即一个进程最多打开1024个文件
-  Linux中一切皆文件，标准输入/输出/错误，是对应当前到终端的(同一个终端，即对应同一个文件)===> **多个文件描述可以对应同一个文件(图中的0，1，2)**
