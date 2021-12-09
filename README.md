# 计算机视觉

本项目基于C++实现计算机视觉中的算法。包括传统的计算机视觉算法以及基于深度学习的算法。主要开发工具是visual studio 2019，后续会学习相关的CMake操作。

## 环境配置

### OpenCV

关于OpenCV的配置在网上有很多，在这里只做简单的介绍，详情请具体搜索相关的博客或者官网资料。

1. 从官网下载对应的opencv版本
2. 双击opencv，提取文件到预设定的文件夹。然后配置相关的环境变量，在控制台上输入```opencv_version```，提示opencv版本说明配置成功。
![image](https://user-images.githubusercontent.com/27406337/145359576-1e9b1107-a4f9-497d-9f2e-626ece48d468.png)
![image](https://user-images.githubusercontent.com/27406337/145359808-aa0529e9-89db-46a8-b899-616661b07fb0.png)
3. 在配置的opencv环境之后，需要配置工程的opencv环境。对你的Debug x64编译器配置opencv的头文件include和lib即可。
4. 注意一点：假设运行之后提示没有相关的dll，只需要把安装文件下的```opencv_world*.dll```等dll文件放到系统的可执行文件上即可。
5. 配置完成后即可继续遨游C++的知识海洋了


### Tensorflow


## CMake编译C++



## 计算机视觉传统算法

### SIFT算法

### HOG算法
