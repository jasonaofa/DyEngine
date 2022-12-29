# DyEngine
————————————————————————————————————————————
# Latest Update
- 学完半本《C++ Primer》之后 终于弄搞明白之前抄的是什么东西了，增加了3D场景的渲染，增加了一些component
- ![image](https://user-images.githubusercontent.com/31367799/209920282-64a80bce-95b0-493c-8f5c-304bdfc539e4.png)



# 9.9 Update
- 终于写（抄）完Gizmo了，我从Hazel复制了大量的代码，因为我是个超级初学者，只能先抄，然后总结学习。所以接下来准备写Wiki，把我抄的这些都弄懂。
- Finally, I got a gizmo. frankly, I copy a lot of codes from Hazel Cause I'm not a good programmer. so I need to copy at first as a quick way to learn.
after GZIMO. I'll write a WIKI about This tiny engine. and try to figure out every detail.

# 1. 项目描述

这是基于C++和opengl的小引擎，学习Cherno的引擎课程的记录。

正在写WIKI，会把引擎中的各种实现方式和重要的类都做一个剖析，帮助像我这样的新手可以快速学习。

目前已实现:
- 保存和读取场景
- 可以保存的UI界面
- 点击entity
- 基础的ecs
- 属性面板
- Gizmo
- 日志系统
- 事件系统
- 层
![image](https://user-images.githubusercontent.com/31367799/189267601-7da630bf-361a-43eb-8f6f-9377fe1a220f.png)

<还处在一个非常初级的阶段>

# 3. 如何运行
目前只支持WINDOWS系统。
基于Premake编译，在根目录下写好了一个批处理：![image](https://user-images.githubusercontent.com/31367799/185866568-dec06497-fcdf-482c-8da6-7c01410ab2fd.png)
默认是VS2019，可以自己修改
