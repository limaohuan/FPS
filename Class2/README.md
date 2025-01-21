#记录一些遇到的问题  
##添加到视口的用于显示游戏剩余时间的控件并不随着时间的减少而减少，而是一直维持在初始值10s  
2025.1.18  
怀疑是将Create WBP Time Widget和Add to Viewport两个事件在GameMode蓝图中接在了事件Begin Play之后，导致函数只在游戏开始时调用了有且只有一次。  
是根据B站siki学院的飞机大战的教程做的，因为之前做过这个项目所以想借鉴一下。原视频是接在主角蓝图的Begin Play之后，但是本项目用的ue的fps模版，character类并没有Begin Play事件  
2025.1.21  
后来向gpt求助，gpt采用另外的方案，就是在c++文件中实例化ui widget，然后在已有的UpdateTimer函数中获取最新的时间并更新至ui  
将代码写好之后生成失败，报错信息如下：  
FPS_ProjectGameMode.gen.cpp.obj : error LNK2019: 无法解析的外部符号 "__declspec(dllimport) class UClass * __cdecl Z_Construct_UClass_UUserWidget_NoRegister(void)" (__imp_?Z_Construct_UClass_UUserWidget_NoRegister@@YAPEAVUClass@@XZ)，函数 "void __cdecl dynamic initializer for 'public: static struct UECodeGen_Private::FObjectPropertyParams const Z_Construct_UClass_AFPS_ProjectGameMode_Statics::NewProp_TimerWidget''(void)" (??__E?NewProp_TimerWidget@Z_Construct_UClass_AFPS_ProjectGameMode_Statics@@2UFObjectPropertyParams@UECodeGen_Private@@B@@YAXXZ) 中引用了该符号  
遂手动在.uproject 文件中添加了 UMG 模块，在 YourProject.Build.cs 文件中将 UMG 模块添加到项目的构建依赖  
编译通过了，但是运行游戏之后ui widget并没有在游戏界面显示TT
