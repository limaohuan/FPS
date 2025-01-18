#记录一些遇到的问题
##添加到视口的用于显示游戏剩余时间的控件并不随着时间的减少而减少，而是一直维持在初始值10s  
2025.1.18
怀疑是将Create WBP Time Widget和Add to Viewport两个事件在GameMode蓝图中接在了事件Begin Play之后，导致函数只在游戏开始时调用了有且只有一次。  
是根据B站siki学院的飞机大战的教程做的，因为之前做过这个项目所以想借鉴一下。原视频是接在主角蓝图的Begin Play之后，但是本项目用的ue的fps模版，character类并没有Begin Play事件
