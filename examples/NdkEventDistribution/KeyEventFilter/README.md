# ArkTS 注册和取消过滤回调函数（KeyEventFilter）

### 介绍

WindowManager提供应用窗口的管理能力，可以用于管理多模输入事件，当前支持使用WindowManager进行多模输入事件的过滤。

从API version 12开始，支持使用WindowManager模块提供的能力去拦截按键事件，让按键事件不往应用内部组件分发

### 效果预览
1、Demo提供为指定的窗口注册过滤回调函数keyEventFilter的按钮和取消注册按钮，提供输入框验证注册后，事件是否被过滤（键盘0-9，非小键盘）

2、注册过滤回调函数后，上方显示注册success，输入框无法输入0-9，取消后，上方显示取消success，输入框可以输入0-9

![filter1.jpg](screenshots/filter1.jpg) ![filter2.jpg](screenshots/filter2.jpg) ![filter3.jpg](screenshots/filter3.jpg) ![filter4.jpg](screenshots/filter4.jpg)

### 使用说明

单击注册过滤回调函数按钮：注册过滤回调函数成功。

输入框输入0-9：使用键盘输入，无法输入。

单击取消过滤回调函数：取消过滤回调函数成功。

输入框输入0-9：使用键盘输入，可以输入。

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

2.本示例为Stage模型，支持API12版本SDK，版本号：5.0.0.21，镜像版本号：OpenHarmony-5.0.0.21。

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
