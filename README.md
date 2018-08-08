# AVGMakerStarter
![](https://img.shields.io/badge/Language-C%2B%2B-brightgreen.svg)
简易版橙光游戏（AVGMAKER）免审核PC端发布软件

## 协议说明
本软件基于GPL-3.0协议，简单来讲，您对本软件进行的修改（比如加个GUI界面）等操作必须也要开源（因为本来免审核就是基于种种原因，如果你也卖钱就没意思了）

**但是如果您是使用本软件进行免审核发布，换言之，您只是使用本软件的功能（生成“启动器”以发布），您和您的作品将不会受到协议的约束，您对您的作品有完全的权利（当然加上对本软件或我的致谢是最好的啦~），“启动器”将成为您游戏的一部分，本人对其不承担任何责任。本条例外高于GPL协议约束，特此声明。**

## 起源
橙光游戏官网<http://www.66rpg.com/>，虽然游戏不错但是必须要审核后才能发布，但是有些自己做的玩质量肯定不高，无法过审，想搞一个PC端免审核的方法，才有了这个软件，造福其他人。

随手写成，适用于Electron框架的新版橙光游戏制作工具2017（AVGMAKER)，测试版本为2.4.7.0716

当前只支持PC端运行，跨平台没时间搞期待大家继续努力，反正本地端也是套了一个浏览器，引擎啥的都有，需要研究如何部署，理论上是可行的。

## 使用教程
注：程序没考虑太多错误处理，请自行校对输入是否正确。
准备：
1. 新建一个文件夹，把你的游戏工程目录**复制**进去并且**改名**为`Game`，如果你不想别人修改的话就删掉里面的`Backup`、`UI备份`、`.avgmakerONew后缀名的工程文件`
2. 找到你制作工具的安装目录，定位到`版本号\interpreter`这个目录，例如`D:\橙光制作工具2017\2.4.7.0716\interpreter`，这个目录应该只有一个`H5`的文件夹，把它**复制**到你刚才新建的文件夹里
3. 接下来你有两种选择
### 傻瓜一键端
优点：傻瓜式无需配置环境
缺点：标题最大长度为50字符（超过的游戏应该不多了），不能添加高级选项（99%的用不到）
1. 下载[一键端程序](https://github.com/MXWXZ/AVGMakerStarter/releases)，解压到你新建的文件夹中
2. 双击运行`Creater.exe`，输入你的“启动器”名，这个将会是别人双击运行游戏的程序名，不需要加后缀，例如`StartGame`，这样最后会生成`StartGame.exe`文件，打开即可运行游戏。
3. 输入窗口标题，这个最后就是游戏上方窗口的标题
4. 输入你游戏的工程分辨率（新建游戏时候选的那个，可以在制作工具的工程设置中看到），如果不一样会出现黑边或拉伸图片
5. 确认一下输入是否正确，然后按任意键，显示一切正常就OK了
6. 打开看看能不能运行，没问题就可以把`Creater.exe`删掉了
6. 去网上找一个给EXE换图标的软件把你生成的程序换个图标就行了（懒得加换图标的代码了），如果不嫌丑就不用换了。

### 编译Starter程序（小白慎选）
优点：没有限制，可以自定义高级选项（自己看main函数配置）
缺点：需要Visual Studio环境，需要一定的编程知识
1. 打开`AVGMakerStarter.sln`工程，打开`AVGMakerStarter`项目，找到`AVGMakerStarter.cpp`
2. 修改前三行的变量值，分别为窗口标题和工程分辨率
3. 【高级】如果需要高级选项（如果你不知道这是什么就看下一步吧），就自行修改`argument`变量里面的值。
4. 自行换一个图标，覆盖`AVGMakerStarter.ico`即可
4. 调到release版本，点击编译就行了

## 常见问题
1. 【Q】标题栏为什么会有`-v2.xxx`的字样？\
【A】这个是程序自带的版本，如果要改每个版本都需要单独下载很麻烦就不改了。你可以把它改成你的版本号，方法是打开`H5\bin`目录，修改`clientpack.txt`里面的值就可以了。
2. 【Q】为什么关掉游戏程序并没有退出（任务管理器可以看到它在后台运行）？\
【A】这个是一个偶发性BUG，我暂时没有找到复现的方法，如果您找到怎么复现，可以告诉我/提issue，我会尽快修复。
2. 【Q】为什么游戏无法运行？\
【A】请确认您的操作步骤是否正确，您最后的目录应该类似这样：
![img](https://raw.githubusercontent.com/MXWXZ/AVGMakerStarter/master/assets/1.jpg)
