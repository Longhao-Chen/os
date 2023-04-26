# 一个简单的操作系统
这个项目最初来自我们C++课程的一次作业，作业的要求是使用`MFC`写一个俄罗斯方块。
但`MFC`无法在`Linux`等上使用，`Qt`以及其他框架已经有其他同学在做，所以走投无路之下就写了这一个操作系统。

# 目前已实现的功能
* 引导
* GDT
* 320\*200 8位彩色显示
* IDT
* 计时器
* 键盘
* 残废的俄罗斯方块

# 编译和运行
## 所需的软件包
```
bochs bochs-x nasm
```

## 生成虚拟机镜像
```
bximage -hd=10M -imgmode=flat -sectsize=512 build/hd.img
```

## 编译运行
```
make
```