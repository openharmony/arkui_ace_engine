# NdkBindInputEvent 示例

### 介绍

本示例通过使用[ArkUI开发文档](https://gitcode.com/openharmony/docs/tree/master/zh-cn/application-dev/ui)中各场景的开发示例，展示在工程中，帮助开发者更好地理解ArkUI提供的组件及组件属性并合理使用。

### 效果预览

| 主页                        |
|---------------------------|
| ![](pictures/image01.gif) |

### 使用说明

1. 在主界面，点击ShowNativeUI按钮，通过列表项分别测试各项事件，查看详细的事件信息。

### 工程目录

```
entry/src/main/cpp/
|---types
|   |---Index.d.ts                            // TypeScript 类型定义
|---ArkUIBaseNode.h                           // 节点基类，封装生命周期和树操作
|---ArkUIListItemNode.h                       // 列表项节点封装类
|---ArkUIListNode.h                           // 列表节点封装类
|---ArkUINode.h                               // 节点封装类，提供通用属性设置
|---ArkUITextNode.h                           // 文本节点封装类
|---CMakeLists.txt                            // CMake 配置文件
|---napi_init.cpp                             // NAPI 初始化，桥接 Native 和 ArkTS
|---NativeEntry.cpp                           // Native 入口实现
|---NativeEntry.h                             // Native 入口定义
|---NativeModule.h                            // Native 模块管理
|---NormalTextListExample.h                   // 输入事件列表示例（核心实现）

entry/src/main/ets/
|---entryability
|---entrybackupability
|---pages
|   |---Index.ets                             // 应用启动页，加载承载 Native 的容器

entry/src/ohosTest/
|---ets
|   |---Index.test.ets                       // 对应页面测试代码
```

### 具体实现

#### 一、ArkTS 侧占位组件配置与 Native 交互触发

1. **初始化占位组件**：创建 NodeContent 对象（rootSlot），作为 Native 组件挂载的桥梁
2. **状态控制显示逻辑**：用 @State @Watch('changeNativeFlag') 修饰 showNative 变量，变量变化时触发回调
3. **绑定占位组件**：通过 ContentSlot(rootSlot) 在 UI 中声明占位区域，与 NodeContent 绑定
4. **交互触发 Native 操作**：changeNativeFlag 回调中，根据 showNative 值调用 Native 接口（createNativeRoot/destroyNativeRoot），传递 NodeContent 用于挂载/卸载 Native 组件

#### 二、Native 侧 UI 组件封装（基类 + 列表/文本组件）

1. **基类封装通用能力**：
   - ArkUIBaseNode：封装节点生命周期（析构时移除子节点、释放资源）和树操作（AddChild/RemoveChild）
   - ArkUINode：继承基类，封装通用属性设置（SetWidth/SetBackgroundColor 等）

2. **具体组件封装**：
   - ArkUIListNode：创建 ARKUI_NODE_LIST 类型节点，封装滚动条状态设置
   - ArkUITextNode：创建 ARKUI_NODE_TEXT 类型节点，封装字体大小、颜色、文本内容等属性设置
   - ArkUIListItemNode：创建 ARKUI_NODE_LIST_ITEM 类型节点，作为列表的子项

#### 三、输入事件监听和处理

1. **自定义列表项类 (InputEventListItem)**：
   - 继承 ArkUIListItemNode
   - 构造函数接收事件名称、背景色和事件类型
   - 根据事件类型自动注册相应的事件
   - 重写 OnNodeEvent 方法处理事件

2. **事件注册**：
   ```cpp
   case CLICK_EVENT:
       nativeModule_->registerNodeEvent(handle_, NODE_ON_CLICK_EVENT, 0, nullptr);
       break;
   ```

3. **事件信息获取**：
   - 点击事件：OH_ArkUI_PointerEvent_GetX/Y、OH_ArkUI_PointerEvent_GetPointerCount 等
   - 触摸事件：OH_ArkUI_PointerEvent_GetPointerId、OH_ArkUI_PointerEvent_GetXByIndex 等
   - 鼠标事件：OH_ArkUI_PointerEvent_GetMouseButton 等
   - 按键事件：OH_ArkUI_KeyEvent_GetCode、OH_ArkUI_KeyEvent_GetAction 等

4. **日志输出**：
   所有事件信息通过 OH_LOG_Print 输出到 Hilog，便于调试和分析

### 相关权限

不涉及。

### 依赖

不涉及。

### 约束与限制

1. 本示例仅支持标准系统上运行, 支持设备：华为手机。

2. HarmonyOS系统：HarmonyOS 5.0.5 Release及以上。

3. 本示例需要使用DevEco Studio 6.0.0 Release (Build Version: 6.0.0.868, built on October 22, 2025)及以上版本才可编译运行。

### 下载

如需单独下载本工程，执行如下命令：

```
git init
git config core.sparsecheckout true
echo ArkUISample/NdkBindInputEvent > .git/info/sparse-checkout
git remote add origin https://gitcode.com/harmonyos_samples/guide-snippets.git
git pull origin master
```
