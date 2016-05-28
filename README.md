# Qt_BaseWidget

##程序说明
窗口基类：<br/>
鼠标放在顶部可以拖动<br/>
鼠标放在界面右、下边缘或者右下角可以伸缩<br/>
支持最大化、最小化

#使用方法
将你自己的界面类从继承QWidget改为继承BaseWidget<br/>
将主界面设置为m_pMainWgt，并调整大小<br/>
例如：
```c++
ui.setupUi(m_pMainWgt);
resize(m_pMainWgt->width(), m_pMainWgt->height() + TOP_HEIGHT);
```

#界面截图
![](https://github.com/ikongziming/Qt_BaseWidget/blob/master/images/demo.png?raw=true)<br/>
应该能看出来，样式是参考网易云音乐的。
