# ArkUI Native API 知识库

> **文档说明**: 本文档位于 ace_engine 仓库，分析 OpenHarmony ArkUI Native API（原生 C/C++ 接口）的完整结构和实现。Native API 定义位于 `OpenHarmony/foundation/arkui/ace_engine/interfaces/native/`，实现层位于 `interfaces/native/node/` 和 `interfaces/native/event/`。

**API 版本**: API 8 - API 24
**Native API 路径**: `OpenHarmony/foundation/arkui/ace_engine/interfaces/native/`
**构建输出**: `libace_native.z.so`

---

## Claude 参考指南

### 文档用途
本文档是 Claude 的内部参考知识库，用于：
1. **理解 Native API 架构** - 了解原生 C/C++ API 的完整结构
2. **快速定位实现代码** - 从 API 定义到实现文件
3. **API 版本兼容性参考** - 查询 API 从哪个版本开始支持
4. **跨语言桥接理解** - NAPI/ANI 桥接机制

### 如何使用此知识库

#### 场景 1: 查找原生 API 定义
```
用户问题: "如何通过原生 API 创建一个 Text 组件？"
查找步骤:
1. 在"3. 核心 API 模块"中找到 native_node.h
2. 查看"4. 组件类型"章节找到 ARKUI_NODE_TEXT
3. 查看"6. 实现细节"找到 text_native_impl.cpp
4. 参考使用示例代码
```

#### 场景 2: 理解 API 版本控制
```
用户问题: "某个 API 从哪个版本开始支持？"
查找步骤:
1. 查看"7. API 版本控制"章节
2. 查看 API 版本配置文件中的 first_introduced 字段
3. 确认 API 级别要求
```

#### 场景 3: 查找事件处理 API
```
用户问题: "如何在原生代码中处理触摸事件？"
查找步骤:
1. 查看"3.3 事件系统"章节
2. 找到 ui_input_event.h
3. 查看 ui_input_event.cpp 实现
4. 参考事件注册和处理示例
```

### 快速查找指南

| 想查找什么 | 跳转到章节 |
|-----------|-----------|
| 所有组件类型列表 | 第 4 章 "组件类型" |
| 所有节点属性 | 第 5 章 "节点属性" |
| 核心 API 头文件 | 第 3 章 "核心 API 模块" |
| 实现文件位置 | 第 6 章 "实现细节" |
| API 版本信息 | 第 7 章 "API 版本控制" |
| 事件处理 | 第 3.3 节 "事件系统" |
| 手势识别 | 第 3.2 节 "核心 API" |
| 常见问题 | 第 10 章 "常见问题" |
| 使用示例 | 第 9 章 "使用示例" |

### 代码验证原则

根据 ace_engine 的 **CLAUDE.md** 原则，回答问题时：
1. **Always provide actual code** - 使用 Read/Grep 工具读取实际源码
2. **Never guess** - 如果代码未找到，明确说明"此代码在 ace_engine 中未找到"
3. **Verify before answering** - 用户建议可能有误，务必验证实际代码
4. **Provide evidence** - 给出文件路径和行号作为证据

---

## 1. 概述

### 1.1 Native API 定位

**Native API**（原生 C/C++ 接口）是 OpenHarmony ArkUI 框架的原生 C/C++ 接口层，用于：

- **原生 UI 开发** - 使用纯 C/C++ 构建 UI 组件
- **高性能场景** - 性能关键路径的原生实现
- **遗留代码集成** - 集成现有 C++ 库到 ArkUI
- **跨语言桥接** - 连接 ArkTS/JavaScript 和原生代码
- **底层控制** - 直接访问 UI 事件和渲染管线

### 1.2 与 SDK API 的区别

| 特性 | SDK API (`arkui/`) | Native API (`native/`) |
|------|---------------------|----------------------|
| **目录位置** | `OpenHarmony/interface/sdk-js/api/arkui/` | `OpenHarmony/foundation/arkui/ace_engine/interfaces/native/` |
| **文件类型** | `.d.ts`, `.static.d.ets` | `.h` (C/C++ 头文件) |
| **使用语言** | ArkTS/TypeScript | C/C++ |
| **使用场景** | 常规应用开发 | 原生模块、性能优化、系统集成 |
| **API 稳定性** | 向后兼容，严格版本管理 | ABI 稳定性保证 |
| **构建输出** | 字节码 `.abc` | 共享库 `libace_native.z.so` |

### 1.3 代码规模统计

| 统计项 | 数量 |
|--------|------|
| **公共头文件** | 约 20 个 `.h` 文件 |
| **实现文件** | 约 100+ 个 `.cpp` 文件 |
| **组件类型** | 40+ 个 (ARKUI_NODE_*) |
| **节点属性** | 91+ 个 (NODE_*) |
| **API 级别支持** | API 8 - API 24 |
| **核心模块** | 5 个 (Node, Dialog, Gesture, Animate, Render) |

---

## 2. 高层架构

### 2.1 架构层次

```
┌─────────────────────────────────────────────────────────┐
│  原生应用 (C/C++)                                        │
│  - 原生 UI 组件                                          │
│  - 性能关键代码                                          │
│  - 遗留 C++ 库集成                                       │
└─────────────────────────────────────────────────────────┘
                    ↓
┌─────────────────────────────────────────────────────────┐
│  interfaces/native (Native 接口层)                      │
│  - 公共 C/C++ API 头文件                                │
│  - 版本化 API 结构                                       │
│  - Native-ArkTS 桥接 (NAPI/ANI)                        │
└─────────────────────────────────────────────────────────┘
                    ↓
┌─────────────────────────────────────────────────────────┐
│  frameworks/core/ (实现层)                              │
│  - Components NG (FrameNode, Pattern)                   │
│  - 布局算法                                              │
│  - 渲染管线                                              │
└─────────────────────────────────────────────────────────┘
```

### 2.2 设计模式

所有 Native API 遵循一致的设计模式：

1. **C API with C++ 支持**：使用 `extern "C"` 接口保证 ABI 稳定性
2. **基于句柄**：使用不透明指针（`ArkUI_NodeHandle`、`ArkUI_ContextHandle`）
3. **版本化 API**：基于结构的版本控制（`ArkUI_NativeNodeAPI_1`）
4. **错误码返回**：一致的错误报告（`ARKUI_ERROR_CODE_*`）
5. **基于回调的事件**：通过函数指针进行异步事件处理
6. **字符串缓冲区模式**：调用方分配的缓冲区用于字符串返回

---

## 3. 核心 API 模块

### 3.1 统一入口 API

#### native_interface.h

**文件**: `native_interface.h`

**核心函数**:
```cpp
void* OH_ArkUI_QueryModuleInterfaceByName(
    ArkUI_NativeAPIVariantKind type,
    const char* structName
);
```

**宏辅助**:
```cpp
#define OH_ArkUI_GetModuleInterface(Type, StructName) \
    ((StructName*)OH_ArkUI_QueryModuleInterfaceByName(Type, #StructName))
```

**API 类型**:
| 枚举值 | 用途 |
|--------|------|
| `ARKUI_NATIVE_NODE` | 节点操作 API |
| `ARKUI_NATIVE_DIALOG` | 对话框管理 API |
| `ARKUI_NATIVE_GESTURE` | 手势识别 API |
| `ARKUI_NATIVE_ANIMATE` | 动画 API |
| `ARKUI_MULTI_THREAD_NATIVE_NODE` | 多线程节点 API |

**版本化结构**:
- `ArkUI_NativeNodeAPI_1`
- `ArkUI_NativeGestureAPI_1`
- `ArkUI_NativeAnimateAPI_1`
- `ArkUI_NativeDialogAPI_1`

### 3.2 核心 API 文件清单

| 头文件 | 行数 | 用途 | 主要特性 |
|--------|------|------|----------|
| **native_node.h** | 12,585 | UI 组件操作 | 40+ 组件类型，91+ 属性，树操作，事件注册 |
| **native_type.h** | 9,611 | 类型定义 | 句柄、枚举、值类型、属性结构 |
| **native_gesture.h** | 1,227 | 手势识别 | 优先级模式、手势组、触摸/拖拽处理 |
| **native_animate.h** | 357 | 动画 | 帧率控制、曲线、动画器管理 |
| **native_dialog.h** | 1,198 | 对话框管理 | 模态/非模态对话框、生命周期状态 |

### 3.3 事件系统

| 头文件 | 行数 | 用途 |
|--------|------|------|
| **ui_input_event.h** | 1,602 | 统一输入事件系统（TOUCH、AXIS、MOUSE、KEY） |
| **drag_and_drop.h** | 1,081 | 拖放功能 |
| **native_key_event.h** | 608 | 键盘事件和焦点管理 |

### 3.4 高级特性

| 头文件 | 行数 | 用途 |
|--------|------|------|
| **native_render.h** | 2,004 | RenderNode API（API 20+），底层渲染控制 |
| **native_styled_string.h** | 195 | 富文本格式化与排版 |

### 3.5 语言桥接

| 头文件 | 行数 | 用途 |
|--------|------|------|
| **native_node_napi.h** | 402 | N-API 桥接（Node.js API），用于 ArkTS FrameNode 转换 |
| **native_node_ani.h** | 107 | ArkNI（Ark Native Interface）桥接，用于 ArkTS 运行时 |
| **native_interface_xcomponent.h** | 1,316 | XComponent 原生集成，支持 surface/OpenGL ES |

---

## 4. 组件类型

### 4.1 基础组件 (0-99)

| 组件类型 | 枚举值 | 功能说明 | 对应 SDK 组件 |
|---------|--------|----------|-------------|
| **Text** | `ARKUI_NODE_TEXT` | 文本显示 | `Text` |
| **Span** | `ARKUI_NODE_SPAN` | 文本片段 | `Span` |
| **Image** | `ARKUI_NODE_IMAGE` | 图片显示 | `Image` |
| **Button** | `ARKUI_NODE_BUTTON` | 按钮 | `Button` |
| **Toggle** | `ARKUI_NODE_TOGGLE` | 开关 | `Toggle` |
| **Slider** | `ARKUI_NODE_SLIDER` | 滑块 | `Slider` |
| **TextInput** | `ARKUI_NODE_TEXT_INPUT` | 文本输入 | `TextInput` |
| **TextArea** | `ARKUI_NODE_TEXT_AREA` | 多行文本输入 | `TextArea` |
| **RichEditor** | `ARKUI_NODE_RICH_EDITOR` | 富文本编辑器 | `RichEditor` |
| **Progress** | `ARKUI_NODE_PROGRESS` | 进度条 | `Progress` |
| **LoadingProgress** | `ARKUI_NODE_LOADING_PROGRESS` | 加载进度 | `LoadingProgress` |

### 4.2 容器组件 (MAX_NODE_SCOPE_NUM+)

| 组件类型 | 枚举值 | 功能说明 | 对应 SDK 组件 |
|---------|--------|----------|-------------|
| **Stack** | `ARKUI_NODE_STACK` | 堆叠布局 | `Stack` |
| **Column** | `ARKUI_NODE_COLUMN` | 纵向布局 | `Column` |
| **Row** | `ARKUI_NODE_ROW` | 横向布局 | `Row` |
| **Flex** | `ARKUI_NODE_FLEX` | 弹性布局 | `Flex` |
| **List** | `ARKUI_NODE_LIST` | 列表 | `List` |
| **ListItem** | `ARKUI_NODE_LIST_ITEM` | 列表项 | `ListItem` |
| **ListItemGroup** | `ARKUI_NODE_LIST_ITEM_GROUP` | 列表分组 | `ListItemGroup` |
| **Grid** | `ARKUI_NODE_GRID` | 网格布局 | `Grid` |
| **GridItem** | `ARKUI_NODE_GRID_ITEM` | 网格子项 | `GridItem` |
| **Scroll** | `ARKUI_NODE_SCROLL` | 滚动容器 | `Scroll` |
| **Swiper** | `ARKUI_NODE_SWIPER` | 轮播容器 | `Swiper` |
| **Refresh** | `ARKUI_NODE_REFRESH` | 下拉刷新 | `Refresh` |
| **WaterFlow** | `ARKUI_NODE_WATER_FLOW` | 瀑布流 | `WaterFlow` |
| **FlowItem** | `ARKUI_NODE_FLOW_ITEM` | 瀑布流子项 | `FlowItem` |
| **RelativeContainer** | `ARKUI_NODE_RELATIVE_CONTAINER` | 相对布局容器 | `RelativeContainer` |

### 4.3 选择器组件

| 组件类型 | 枚举值 | 功能说明 | 对应 SDK 组件 |
|---------|--------|----------|-------------|
| **DatePicker** | `ARKUI_NODE_DATE_PICKER` | 日期选择器 | `DatePicker` |
| **TimePicker** | `ARKUI_NODE_TIME_PICKER` | 时间选择器 | `TimePicker` |
| **TextPicker** | `ARKUI_NODE_TEXT_PICKER` | 文本选择器 | `TextPicker` |
| **CalendarPicker** | `ARKUI_NODE_CALENDAR_PICKER` | 日历选择器 | `CalendarPicker` |
| **Picker** | `ARKUI_NODE_PICKER` | 通用选择器 | `Picker` |

### 4.4 特殊组件

| 组件类型 | 枚举值 | 功能说明 | 对应 SDK 组件 |
|---------|--------|----------|-------------|
| **Custom** | `ARKUI_NODE_CUSTOM` | 自定义组件 | `CustomComponent` |
| **XComponent** | `ARKUI_NODE_XCOMPONENT` | 原生组件容器 | `XComponent` |
| **XComponentTexture** | `ARKUI_NODE_XCOMPONENT_TEXTURE` | XComponent 纹理 | `XComponent` |
| **ImageAnimator** | `ARKUI_NODE_IMAGE_ANIMATOR` | 帧动画 | `ImageAnimator` |
| **EmbeddedComponent** | `ARKUI_NODE_EMBEDDED_COMPONENT` | 嵌入式组件 | `EmbeddedComponent` |

---

## 5. 节点属性

### 5.1 布局属性

| 属性枚举 | 说明 | 值类型 |
|---------|------|--------|
| `NODE_WIDTH` | 宽度 | ArkUI_NumberValue |
| `NODE_HEIGHT` | 高度 | ArkUI_NumberValue |
| `NODE_PADDING` | 内边距 | ArkUI_Padding |
| `NODE_MARGIN` | 外边距 | ArkUI_Margin |
| `NODE_WEIGHT` | 权重 | float |
| `NODE_CONSTRAINTS` | 约束 | ArkUI_SizeConstraint |

### 5.2 位置属性

| 属性枚举 | 说明 | 值类型 |
|---------|------|--------|
| `NODE_POSITION` | 位置 | ArkUI_Position |
| `NODE_OFFSET` | 偏移 | ArkUI_Offset |
| `NODE_ALIGN_CONTENT` | 内容对齐 | int |
| `NODE_ALIGN_ITEMS` | 项对齐 | int |

### 5.3 背景属性

| 属性枚举 | 说明 | 值类型 |
|---------|------|--------|
| `NODE_BACKGROUND_COLOR` | 背景颜色 | uint32_t |
| `NODE_BACKGROUND_IMAGE` | 背景图片 | char* |

### 5.4 边框属性

| 属性枚举 | 说明 | 值类型 |
|---------|------|--------|
| `NODE_BORDER` | 边框 | ArkUI_Border |
| `NODE_BORDER_RADIUS` | 圆角 | ArkUI_BorderRadius |
| `NODE_BORDER_WIDTH` | 边框宽度 | ArkUI_BorderWidth |

### 5.5 文本属性

| 属性枚举 | 说明 | 值类型 |
|---------|------|--------|
| `NODE_FONT_SIZE` | 字体大小 | ArkUI_NumberValue |
| `NODE_FONT_COLOR` | 字体颜色 | uint32_t |
| `NODE_FONT_WEIGHT` | 字体粗细 | int |
| `NODE_TEXT_ALIGN` | 文本对齐 | int |

### 5.6 显示属性

| 属性枚举 | 说明 | 值类型 |
|---------|------|--------|
| `NODE_OPACITY` | 不透明度 | float [0.0-1.0] |
| `NODE_VISIBILITY` | 可见性 | int |
| `NODE_DISPLAY_PRIORITY` | 显示优先级 | int |

### 5.7 交互属性

| 属性枚举 | 说明 | 值类型 |
|---------|------|--------|
| `NODE_ENABLED` | 启用状态 | bool |
| `NODE_TOUCH_EVENT` | 触摸事件 | ArkUI_EventCallback |
| `NODE_MOUSE_EVENT` | 鼠标事件 | ArkUI_EventCallback |

---

## 6. 实现细节

### 6.1 目录结构

```
interfaces/native/
├── *.h                          # 公共 API 头文件（约 20 个文件）
├── node/                        # 实现层（约 45 个文件）
│   ├── native_impl.cpp          # 核心原生 API 实现
│   ├── node_model.cpp           # 节点操作和数据模型
│   ├── event_converter.cpp      # 事件类型转换
│   ├── style_modifier.cpp       # 样式修饰符系统
│   ├── text_native_impl.cpp     # Text 组件原生函数
│   └── [component_*_impl.cpp]  # 组件特定实现
├── event/                       # 事件系统实现
│   ├── ui_input_event.cpp       # 核心输入事件处理
│   ├── drag_and_drop_impl.cpp   # 拖放功能
│   └── key_event_impl.cpp       # 键盘事件
├── BUILD.gn                     # 构建配置
└── API版本配置文件               # API 版本跟踪
```

### 6.2 关键实现文件

| 文件 | 行数 | 用途 |
|------|------|------|
| `style_modifier.cpp` | 888,257 | 样式修饰符系统（超大） |
| `event_converter.cpp` | 54,607 | 事件类型转换 |
| `ui_input_event.cpp` | 194,536 | 输入事件实现 |
| `node_model.cpp` | - | 核心节点操作 |
| `native_impl.cpp` | - | 原生 API 实现 |
| `render_node.cpp` | - | 渲染节点操作 |

### 6.3 构建配置

**BUILD.gn** 详情：
- **目标**：生成原生接口库
- **Native 头文件**：通过头文件生成规则
- **Native 库**：通过库配置规则
- **源文件**：来自 `node/` 和 `event/` 的 100+ 实现文件
- **外部依赖**：Rosen、NAPI、UDMF、pixelmap、hilog 等
- **版本脚本**：从 API 版本配置文件生成

---

## 7. API 版本控制

### 7.1 版本跟踪机制

API 版本配置文件跟踪 API 引入版本：
- **格式**：JSON 数组，包含 `{"name": "FunctionName", "first_introduced": "N"}`
- **API 级别**：从 API 8 到 API 24+
- **用途**：ROM 打包和向后兼容
- **版本脚本**：自动生成 .ver 版本脚本

### 7.2 版本示例

```json
{
  "first_introduced": "8",
  "name": "OH_NativeXComponent_GetXComponentId"
}
```

### 7.3 API 级别演进

| API 级别 | 主要特性 |
|----------|----------|
| **API 8** | 初始 Native API 支持，基础组件 |
| **API 9-10** | 扩展组件，手势增强 |
| **API 11-12** | 多线程节点，性能优化 |
| **API 13-15** | 新增动画，对话框增强 |
| **API 16-19** | RenderNode API，无障碍支持 |
| **API 20-24** | 现代化 API，性能改进 |

---

## 8. 常见用例

### 8.1 原生 UI 开发

使用纯 C/C++ 构建 UI 组件

**适用场景**：
- 需要高性能的 UI 场景
- 现有 C++ UI 库移植
- 跨平台 UI 框架集成

### 8.2 性能优化

原生层的关键路径代码

**适用场景**：
- 复杂布局计算
- 自定义渲染逻辑
- 大数据量处理

### 8.3 遗留代码集成

集成现有 C++ 库到 ArkUI

**适用场景**：
- 复用现有 C++ 组件库
- 集成第三方 C++ SDK
- 渐进式迁移旧项目

### 8.4 自定义组件

创建 ArkTS 中不可用的组件

**适用场景**：
- 特殊硬件交互
- 定制化渲染需求
- 系统级功能扩展

### 8.5 跨语言桥接

无缝混合 ArkTS 和原生代码

**适用场景**：
- ArkTS 调用原生能力
- 原生回调到 ArkTS
- 共享数据状态

### 8.6 系统集成

直接访问底层 UI 事件

**适用场景**：
- 全局手势拦截
- 自定义输入处理
- 无障碍功能扩展

---

## 9. 使用示例

### 9.1 基础组件创建

```cpp
// 1. 获取 Node API
auto* nodeApi = (ArkUI_NativeNodeAPI_1*)OH_ArkUI_GetModuleInterface(
    ARKUI_NATIVE_NODE, ArkUI_NativeNodeAPI_1);

// 2. 创建 Text 节点
ArkUI_NodeHandle textNode = nodeApi->createNode(ARKUI_NODE_TEXT);

// 3. 设置属性
nodeApi->setString(textNode, NODE_TEXT_CONTENT, "Hello Native!");
nodeApi->setNumber(textNode, NODE_FONT_SIZE, 20.0);
nodeApi->setColor(textNode, NODE_FONT_COLOR, 0xFFFF0000);

// 4. 添加到父节点
nodeApi->addChild(parentNode, textNode);
```

### 9.2 事件处理

```cpp
// 触摸事件回调
void OnTouchEvent(ArkUI_UIEventEvent* event) {
    auto* touchEvent = (ArkUI_UITouchEvent*)event;
    // 处理触摸事件
}

// 注册事件
nodeApi->addEventReceiver(textNode, NODE_TOUCH_EVENT, OnTouchEvent);
```

### 9.3 手势识别

```cpp
// 1. 获取手势 API
auto* gestureApi = (ArkUI_NativeGestureAPI_1*)OH_ArkUI_GetModuleInterface(
    ARKUI_NATIVE_GESTURE, ArkUI_NativeGestureAPI_1);

// 2. 创建点击手势
ArkUI_GestureHandle clickGesture = gestureApi->createClickGesture(
    1,    // fingers
      1    // count
);

// 3. 设置回调
gestureApi->setGestureCallback(clickGesture, [](void* extra) {
    // 处理点击
});

// 4. 绑定到节点
gestureApi->attachGestureToNode(textNode, clickGesture);
```

### 9.4 对话框管理

```cpp
// 1. 获取对话框 API
auto* dialogApi = (ArkUI_NativeDialogAPI_1*)OH_ArkUI_GetModuleInterface(
    ARKUI_NATIVE_DIALOG, ArkUI_NativeDialogAPI_1);

// 2. 创建警告对话框
ArkUI_DialogHandle dialog = dialogApi->createAlertDialog(
    "Alert",
    "This is a native dialog",
    "OK",
    nullptr
);

// 3. 显示对话框
dialogApi->showDialog(dialog);

// 4. 设置生命周期回调
dialogApi->setDialogCallback(dialog, [](ArkUI_DialogEvent event) {
    if (event == DIALOG_EVENT_DISMISSED) {
        // 对话框关闭
    }
});
```

### 9.5 动画控制

```cpp
// 1. 获取动画 API
auto* animateApi = (ArkUI_NativeAnimateAPI_1*)OH_ArkUI_GetModuleInterface(
    ARKUI_NATIVE_ANIMATE, ArkUI_NativeAnimateAPI_1);

// 2. 创建动画器
ArkUI_AnimatorHandle animator = animateApi->createAnimator();

// 3. 设置动画参数
animateApi->setDuration(animator, 1000);  // 1秒
animateApi->setCurve(animator, ANIMATION_CURVE_EASE_IN_OUT);

// 4. 添加动画属性
animateApi->addFloatProperty(animator, textNode, NODE_OPACITY,
    0.0f,  // from
    1.0f   // to
);

// 5. 启动动画
animateApi->start(animator);
```

### 9.6 XComponent 集成

```cpp
// 1. 获取 XComponent 实例
// OH_NativeXComponent* component = ...;

// 2. 获取 XComponent ID
char id[OH_XCOMPONENT_ID_LEN_MAX + 1];
uint64_t size = OH_XCOMPONENT_ID_LEN_MAX + 1;
OH_NativeXComponent_GetXComponentId(component, id, &size);

// 3. 注册 surface 回调和事件处理
// OH_NativeXComponent_RegisterSurfaceShowCallback(...);
// OH_NativeXComponent_RegisterSurfaceHideCallback(...);

// 4. 使用 surface 进行渲染
// 例如：通过回调获取 NativeWindow 后进行 OpenGL ES 绘制
```

---

## 10. 常见问题

### 10.1 Native API 和 SDK API 的关系

**Q**: Native API 和 SDK API 是什么关系？

**A**:
- **SDK API** (ArkTS/TypeScript) 是开发者常用的高级接口
- **Native API** (C/C++) 是底层原生接口，直接访问 UI 框架
- **Native API** 通常比 SDK API 性能更高，但开发复杂度也更高
- **两者可以混用**，通过 NAPI/ANI 桥接

### 10.2 如何选择 Native API 还是 SDK

**Q**: 什么时候应该使用 Native API 而不是 SDK？

**A**: 优先使用 Native API 的场景：
- 需要高性能（如游戏引擎、复杂动画）
- 集成现有 C++ 库
- 需要 SDK 未提供的底层能力
- 跨平台 C++ 代码复用

**优先使用 SDK 的场景**：
- 常规应用开发
- 快速原型开发
- 团队更熟悉 ArkTS

### 10.3 版本兼容性

**Q**: Native API 的版本兼容性如何保证？

**A**:
1. **ABI 稳定性**：所有公共 API 使用 `extern "C"` 保证 ABI 稳定
2. **版本化结构**：通过 `ArkUI_NativeNodeAPI_1` 等版本化结构演进
3. **API 版本配置**：跟踪每个 API 的引入版本
4. **向后兼容**：新版本保持旧 API 可用

### 10.4 常见错误

**Q**: 使用 Native API 时常见错误有哪些？

**A**:

| 错误 | 原因 | 解决方案 |
|------|------|----------|
| `ARKUI_ERROR_NULL_PTR` | 句柄为空 | 检查节点是否正确创建 |
| `ARKUI_ERROR_INVALID_PARAM` | 参数无效 | 验证参数类型和范围 |
| `ARKUI_ERROR_NO_ACTIVE_PAGE` | 无活动页面 | 确保在有效 UI 上下文中调用 |
| `ARKUI_ERROR_API_NOT_AVAILABLE` | API 不可用 | 检查 API 版本支持 |

### 10.5 性能优化建议

**Q**: 如何优化原生 UI 性能？

**A**:
1. **批量操作**：尽量批量设置属性，减少刷新次数
2. **避免频繁创建节点**：复用节点，使用 `setVisible` 控制显示
3. **合理使用多线程**：使用 `ARKUI_MULTI_THREAD_NATIVE_NODE` API
4. **事件节流**：高频事件（如滚动）使用节流处理
5. **资源管理**：及时释放不再使用的节点和资源

---

## 11. 调试指南

### 11.1 日志输出

```cpp
// 使用 hilog 输出日志
#include <hilog/log.h>

OH_LOG_Print(LOG_APP, LOG_INFO, "Native API: node=%{public}p", node);
```

### 11.2 错误处理

```cpp
// 检查 API 返回值
int32_t ret = nodeApi->addChild(parent, child);
if (ret != ARKUI_ERROR_CODE_NO_ERROR) {
    OH_LOG_Print(LOG_APP, LOG_ERROR, "Add child failed: %{public}d", ret);
}
```

### 11.3 内存泄漏检测

```bash
# 使用 AddressSanitizer 编译
./build.sh --product-name rk3568 --build-target ace_engine \
    --sanitize-address

# 运行时检测泄漏
hdc shell hilog | grep "ASAN"
```

---

## 12. 总结

### 12.1 关键特点

| 特点 | 说明 |
|------|------|
| **ABI 稳定** | 使用 `extern "C"` 保证跨版本兼容 |
| **版本化 API** | 基于结构的版本控制机制 |
| **完整覆盖** | 支持 40+ 组件类型和 91+ 属性 |
| **高性能** | 直接访问 UI 框架，无桥接开销 |
| **跨语言** | 支持 ArkTS、JavaScript、Cangjie 调用 |

### 12.2 统计数据

| 类别 | 数量 |
|------|------|
| **公共头文件** | 约 20 个 |
| **实现文件** | 约 100+ 个 |
| **组件类型** | 40+ 个 |
| **节点属性** | 91+ 个 |
| **API 级别** | API 8 - API 24 |

---

**文档维护**: 本文档应随着 Native API 的演进定期更新。当添加新 API 或组件时，请及时更新相关章节。

**相关资源**:
- [ArkUI SDK API 知识库](../sdk/ArkUI_SDK_API_Knowledge_Base.md) - SDK API 完整分析
- [knowledge_base_INDEX.json](../knowledge_base_INDEX.json) - 知识库元数据索引
- [OpenHarmony/foundation/arkui/ace_engine/interfaces/native/](OpenHarmony/foundation/arkui/ace_engine/interfaces/native/) - Native API 目录
