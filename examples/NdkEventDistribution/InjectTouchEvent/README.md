# ArkTS 注册和取消过滤回调函数（KeyEventFilter）

### 介绍

WindowManager提供应用窗口的管理能力，可以用于管理多模输入事件。

使用WindowManager模块提供的能力为指定窗口注入触摸事件，仅支持同进程窗口。此操作不会触发窗口焦点、层级变化或拖拽，事件会直接发送给ArkUI。

从API version 20开始支持

### 效果预览
1、Demo提供发起注入touchEvent事件的按钮，将事件注入到指定按钮的位置，触发指定按钮onClick事件

2、点击测试InjectEvent按钮后，发起事件注入，上方按钮被注入事件，执行了按钮的onClick，显示了当前时间

![inject1.jpg](screenshots/inject1.jpg) 

### 使用说明

点击测试InjectEvent按钮后：注入touchEvent事件，上方发生变化。

### 工程目录

```
entry/src/
 ├── main
 │   ├── cpp
 │   │   ├── types
 │   │       ├── libentry
 │   │           ├── Index.d.ts         // 导出的napi函数定义
 │   │           ├── oh-package.json5   // 导出napi函数配置
 │   │   ├── CMakeLists.txt             // CMake配置
 │   │   ├── napi_init.cpp              // napi函数实现
 │   ├── ets
 │   │   ├── entryability
 │   │   ├── entrybackupability
 │   │   ├── pages
 │   │       ├── Index.ets               // 主页面
 │   ├── module.json5
 │   └── resources                       // 静态资源
 ├── ohosTest
 │   ├── ets
 │   │   ├── test
 │   │       ├── Index.test.ets          // 自动化测试代码
```

### 相关权限

权限获取与签名可以参考官方文档：
https://developer.huawei.com/consumer/cn/doc/harmonyos-guides/ide-signing#section26216104250

### 依赖

不涉及

### 约束与限制

1.本示例仅支持标准系统上运行, 支持设备：华为手机、平板、PC、TV、车机、穿戴设备。

2.本示例为Stage模型，支持API20版本SDK，版本号：6.0.0.38，镜像版本号：OpenHarmony-6.0.0.38。

3.本示例需要使用DevEco Studio 6.0.0 Release及以上版本才可编译运行。

### 下载

如需单独下载本工程，执行如下命令：

```
git init
git config core.sparsecheckout true
echo ArkUISample/FloatingBall > .git/info/sparse-checkout
git remote add origin https://gitcode.com/harmonyos_samples/guide-snippets.git
git pull origin master
```
