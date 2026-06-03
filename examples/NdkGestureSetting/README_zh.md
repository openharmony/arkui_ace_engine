# NdkGestureSetting

### 介绍

本示例基于[native_gesture.h](https://gitcode.com/openharmony/docs/blob/master/zh-cn/application-dev/reference/apis-arkui/capi-native-gesture-h.md)中的各接口进行构建，以帮助开发者更好地理解手势框架C-API的用法。

### 效果预览

| 首页                                 |
|------------------------------------|
|<img src="screenshots/device/image1.jpeg" width="360;">|

### 使用说明

1. 在首页可以查看多种手势C-API的使用示例，包括手势绑定、手势移除以及自定义手势判定。

2. 通过自动测试框架可进行测试及维护。

### 工程目录
```
entry/src/main/ets/
|---cpp
|     |---types
|     |---CMakeLists.txt
|     |---container.cpp
|     |---container.h
|     |---init.cpp
|     |---manager.cpp                       // 手势拦截示例代码
|     |---manager.h                         // manager头文件
|     |---napi_init.cpp
|---ets
|   |---pages
|   |   |---Index.ets                       // 应用主页面
entry/src/ohosTest/
|---ets
|   |---index.test.ets                       // 示例代码测试代码
```

### 相关权限

不涉及。

### 依赖

不涉及。

### 约束与限制

1.本示例仅支持标准系统上运行, 支持设备：华为手机。

2. HarmonyOS系统：HarmonyOS 5.0.5 Release及以上。

3.本示例需要使用DevEco Studio 6.0.0 Release及以上版本才可编译运行。

### 下载

如需单独下载本工程，执行如下命令：

````
git init
git config core.sparsecheckout true
echo ArkUISample/NdkGestureSetting > .git/info/sparse-checkout
git remote add origin https://gitcode.com/harmonyos_samples/guide-snippets.git
git pull origin master
````