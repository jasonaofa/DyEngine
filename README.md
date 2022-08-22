# DyEngine
# 1. 项目描述
- 这是基于C++和opengl的小引擎，学习Cherno的引擎课程的记录。
- 目前实现了:
- DLL和SANDBOX的衔接，引擎入口点的设置，分开了引擎端和客户端
- 日志系统
- 事件系统
- 层
- Imgui
- Polling input
- 还处在一个比较初级的状态。但是底层的架构已经搭完了。
![image](https://user-images.githubusercontent.com/31367799/185868136-fd3ae58d-bed2-4427-be68-0787ab321f87.png)

# 2. 如何运行
- 目前只支持WINDOWS系统。
- 基于Premake编译，在根目录下写好了一个批处理：![image](https://user-images.githubusercontent.com/31367799/185866568-dec06497-fcdf-482c-8da6-7c01410ab2fd.png)
- 默认是VS2019，可以自己修改
# 3. Submodule
- 都在\DyEngine\vendor里，记得拉一下。
- 目前只有：
- glfw
- glad
- imgui
- spdlog
4. 项目备注
