# AccessibilityCAPI示例

### 介绍

本示例[通过XComponent接入无障碍](https://developer.huawei.com/consumer/cn/doc/harmonyos-guides/ndk-accessibility-xcomponent)中各场景的开发示例，展示在工程中，帮助开发者更好地理解Accessibility CAPI接口并合理使用。该工程中展示的接口详细描述可查如下链接：

[native_interface_accessibility.h](https://gitcode.com/openharmony/docs/blob/master/zh-cn/application-dev/reference/apis-arkui/capi-native-interface-accessibility-h.md)。

### 使用说明

1. 通过开启屏幕朗读后使用单指滑动点击双击等操作，可以验证无障碍C-API接口的基本功能。

### 工程目录
```
├──entry/src/main
│  ├──cpp                               // C++代码区
│  │  ├──CMakeLists.txt                 // CMake配置文件
│  │  ├──ani_init.cpp                   // ANI模块注册
|  |  ├──fakenode                       // 假节点模块
|  |  |  ├──fake_node.cpp
|  |  |  └──fake_node.h
│  │  ├──manager            
|  |  |  ├──AccessibilityManager.cpp    // Accessibility CAPI接口示例
|  |  |  └──AccessibilityManager.h
│  ├──ets                           // ets代码区
│  │  ├──entryability
│  │  │  └──EntryAbility.ets         // 程序入口类
│  │  └──pages                      // 页面文件
│  │     └──Index.ets               // 主界面
|  ├──resources         			// 资源文件目录
├──entry/src/ohosTest/
├──ets
|   |---index.test.ets                       // 示例代码测试代码
```

### 相关权限

不涉及。

### 依赖

不涉及。

### 约束与限制

1.本示例仅支持标准系统上运行，支持设备：default、tablet。

2.本示例为Stage模型静态编译模式，支持API26版本SDK，版本号：6.0.0.0，镜像版本号：OpenHarmony_6.0.0.0。

3.本示例需要使用DevEco Studio 6.0.0 Release及以上版本才可编译运行。

### 下载

如需单独下载本工程，执行如下命令：

````
git init
git config core.sparsecheckout true
echo examples/Accessibility_sta/AccessibilityCapi > .git/info/sparse-checkout
git remote add origin https://gitcode.com/openharmony/ace_engine.git
git pull origin master
````