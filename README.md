# DyEngine
————————————————————————————————————————————
# 1. 项目描述

这是基于C++和opengl的小引擎，学习Cherno的引擎课程的记录。

目前已实现:
- DLL和SANDBOX的衔接，引擎入口点的设置，分成了引擎端和客户端
- 日志系统
- 事件系统
- 层
- Imgui
- Input Polling 
![image](https://user-images.githubusercontent.com/31367799/186081856-01701abe-82cc-489e-b6e0-e3d5715427d3.png)

<还处在一个非常初级的阶段>

# 2. 如何运行
目前只支持WINDOWS系统。
基于Premake编译，在根目录下写好了一个批处理：![image](https://user-images.githubusercontent.com/31367799/185866568-dec06497-fcdf-482c-8da6-7c01410ab2fd.png)
默认是VS2019，可以自己修改

#3. 设计
- 入口是EntryPoint 启动的时候首先执行
- 界面和应用都写在Applicaiton
- 不同系统的事件都写在不同的window，e.g.:WindowsWindow
- 记得啦submodule都在\DyEngine\vendor里。
