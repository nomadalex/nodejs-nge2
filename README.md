nodejs-nge2
============

libnge2的nodejs绑定。

**正在重度编写中**

目前已经完成：

* 基本图元的绘制，
* （键盘、鼠标）输入部分，
* 图片的载入与绘制，
* 声音的载入与播放控制，
* 字体的载入与绘制。

基本绘画

![例子1](https://github.com/ifreedom/nodejs-nge2/raw/master/img/run.js.png)

显示图片

![例子2](https://github.com/ifreedom/nodejs-nge2/raw/master/img/test_img.png)

显示字体(点阵式和truetype皆可)

![例子3](https://github.com/ifreedom/nodejs-nge2/raw/master/img/test_font.png)

具体计划请查看 [TODO](https://github.com/ifreedom/nodejs-nge2/blob/master/TODO.md)。

编译
-----

使用cmake作为编译系统，如不会使用cmake，请先自行学习其使用方法。

nodejs
------

因编译扩展需要nodejs，所以为了方便大家使用，特地编译了一份带有头文件和库文件的nodejs版本，在windows上可以直接使用此版本，[nodejs.7z](https://open.ge.tt/1/files/1AwzUME/0/blob)。

目前nodejs的社区对于windows上的扩展构建并不是十分重视，我个人因习惯使用cmake作为构建系统，自己写了一份用于构建nodejs扩展的cmake文件，[nodejs.cmake](https://github.com/ifreedom/nodejs-nge2/blob/master/CMake/Nodejs.cmake)，且同时支持我提供的nodejs二进制版本和官方的源码版本。

由NODE\_ROOT变量指示node所在的根目录，此变量可在环境变量中指定或直接手动指定，同时提供一定程度的自动探测。

当使用由我所提供的二进制版本时，在CmakeLists.txt里使用prepare\_nodejs(BIN_VERSION)即可，并且可以根据node的可执行文件直接推断NODE\_ROOT变量。

官方的源码版本只支持由Release配置编译出来的库文件位置，使用prepare\_nodejs()即可。

在linux下也可正常使用此cmake脚本。

依赖
----

你可以直接下载打包好的依赖包：

* [Win32Depends.7z](https://open.ge.tt/1/files/8rT8cKE/0/blob)

解压到项目根目录或自行准备以下依赖：

* libnge2
  https://github.com/ifreedom/libnge2

* nodejs
  http://nodejs.org

