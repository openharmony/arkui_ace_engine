# TextPicker Context

> 文档版本：v1.0
> 更新时间：2026-07-11
> 来源：`docs/context_registry.json` 主题 `TextPicker`

## 定位

TextPicker 是 ArkUI 的文本选择器组件，用于单列、多列和级联文本项选择。本文档只作为 TextPicker 相关源码、SDK 声明、C API、测试和 Spec 的快速路由；具体行为、默认值、边界处理和兼容性以 SDK 声明、源码实现、测试用例和 Spec 为准。

TextPicker 已完成组件化改造，动态模块名为 `TextPicker` / `TextPickerDialog`，组件模块通过 `arkui.components.arktextpicker` 加载，构建产物对应 `libarkui_textpicker.z.so`。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| Pattern 主目录 | `frameworks/core/components_ng/pattern/text_picker/` | TextPicker 行、列、布局、样式、对话框和桥接实现集中目录 |
| 行 Pattern | `frameworks/core/components_ng/pattern/text_picker/textpicker_pattern.cpp` | 多列、级联、事件和状态协调入口 |
| 列 Pattern | `frameworks/core/components_ng/pattern/text_picker/textpicker_column_pattern.cpp` | 单列滚动、吸附、无障碍文本更新和触觉反馈入口 |
| ArkTS Dynamic Model | `frameworks/core/components_ng/pattern/text_picker/textpicker_model_ng.cpp` | 动态前端和 node_modifier 写入 Model 的入口 |
| ArkTS Static Model | `frameworks/core/components_ng/pattern/text_picker/textpicker_model_static.cpp` | 静态前端属性写入入口 |
| 布局算法 | `frameworks/core/components_ng/pattern/text_picker/textpicker_layout_algorithm.cpp` | TextPicker 行布局与列宽处理 |
| 事件定义 | `frameworks/core/components_ng/pattern/text_picker/textpicker_event_hub.h` | onChange/onScrollStop 等事件挂接 |
| 组件化 Bridge 目录 | `frameworks/core/components_ng/pattern/text_picker/bridge/` | 统一 Bridge、Dynamic/Static Modifier、DynamicModule 和 Dialog Bridge |
| node_modifier | `frameworks/core/interfaces/native/node/node_textpicker_modifier.cpp` | C++ 属性 Set/Reset/Get 委托层 |
| C API option 辅助 | `interfaces/native/node/textpicker_option.cpp` | TextPicker option/range 相关原生结构处理 |
| C API 枚举 | `interfaces/native/native_node.h` | `ARKUI_NODE_TEXT_PICKER`、`NODE_TEXT_PICKER_*`、`NODE_TEXT_PICKER_EVENT_*` |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/text_picker.d.ts` | `TextPickerInterface`、`TextPickerAttribute`、`TextPickerOptions`、Dialog 声明 |
| Static API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/textPicker.static.d.ets` | 静态 ArkTS TextPicker 组件、Options、Attribute 和 Dialog 声明 |
| Modifier API (Dynamic) | `<OH_ROOT>/interface/sdk-js/api/arkui/TextPickerModifier.d.ts` | 动态 Modifier 声明 |
| Modifier API (Static) | `<OH_ROOT>/interface/sdk-js/api/arkui/TextPickerModifier.static.d.ets` | 静态 Modifier 声明 |
| CAPI / NDK | `interfaces/native/native_node.h` | TextPicker 节点、属性和事件枚举 |
| CAPI option | `interfaces/native/node_attributes/picker.h` | Picker 通用 indicator/option 结构 |

API 检索建议：

- 构造参数：搜索 `TextPickerInterface`、`TextPickerOptions`、`TextPicker(`。
- 属性声明：搜索 `TextPickerAttribute` 和具体属性名。
- Dialog：搜索 `TextPickerDialog`、`TextPickerDialogOptions`。
- C API：搜索 `ARKUI_NODE_TEXT_PICKER`、`NODE_TEXT_PICKER_`。

### API 解析实现路径

TextPicker 已完成组件化改造，声明式组件和动态属性统一进入 `pattern/text_picker/bridge/`；当前源码未发现旧 TextPicker JSView 文件。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| 前端 JS/TS 定义 | `frameworks/bridge/declarative_frontend/ark_direct_component/src/arktextpicker.ts` | 前端组件类和 JS 侧属性转发；Modifier 类见 `frameworks/bridge/declarative_frontend/ark_modifier/src/text_picker_modifier.ts` |
| 统一 Bridge（声明式 + 动态属性） | `frameworks/core/components_ng/pattern/text_picker/bridge/arkts_native_textpicker_bridge.cpp` | 参数解析、事件绑定和 node_modifier 调用入口 |
| Dialog Bridge | `frameworks/core/components_ng/pattern/text_picker/bridge/arkts_native_textpickerdialog_bridge.cpp` | TextPickerDialog 参数解析和显示入口 |
| Dynamic Modifier | `frameworks/core/components_ng/pattern/text_picker/bridge/textpicker_dynamic_modifier.cpp` | 动态属性路径，供 Bridge 和动态模块使用 |
| Static Modifier | `frameworks/core/components_ng/pattern/text_picker/bridge/textpicker_static_modifier.cpp` | 静态编译路径 |
| Dynamic Module | `frameworks/core/components_ng/pattern/text_picker/bridge/textpicker_dynamic_module.cpp` | `TextPickerDynamicModule`，动态模块入口 |
| node_modifier 委托层 | `frameworks/core/interfaces/native/node/node_textpicker_modifier.cpp` | C API 与 Bridge 共用的 C++ 属性委托层 |

组件化改造参考：`./组件化重构通用方案.md`。

### 外部依赖入口

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件 / 目标路径 | 说明 |
|----------|----------|------------|--------------------------------|------|
| 触觉反馈 | `frameworks/core/components_ng/pattern/text_picker/textpicker_column_pattern.cpp` | `foundation/multimedia/player_framework` | `audio_haptic` | 通过 `PickerAudioHapticFactory` 获取音频触觉控制器 |
| 触觉适配 | `adapter/ohos/entrance/picker/`、`adapter/ohos/entrance/vibrator/` | `base/sensors/miscdevice` | `vibrator_interface_native` | 平台侧触觉和 vibrator 适配 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| Pattern 单元测试 | `test/unittest/core/pattern/text_picker/` | TextPicker 模型、列、布局、事件、资源和 ToJson 等回归 |
| C API modifier 测试 | `test/unittest/capi/modifiers/text_picker_modifier_test.cpp` | TextPicker node_modifier/C API 属性回归 |
| C API option 测试 | `test/unittest/interfaces/capi_textpicker_option_test.cpp` | TextPicker option 结构回归 |

### 相关 Spec

| Spec | 路径 | 说明 |
|------|------|------|
| TextPicker 设计文档 | `specs/05-ui-components/05-picker-components/03-text-picker/design.md` | Spec 仓库存在时的设计入口 |
| TextPicker 特性规格 | `specs/05-ui-components/05-picker-components/03-text-picker/Feat-01-text-picker-full-spec.md` | TextPicker 功能规格定义 |
| 本仓规格目录 | `specs/05-ui-components/05-picker-components/03-text-picker/` | 当前工作区规格目录 |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 创建或数据范围异常 | SDK `TextPickerOptions` / `TextPickerRangeContent`，以及 `textpicker_model_ng.cpp` |
| 级联列更新异常 | `textpicker_pattern.cpp` 和 `textpicker_column_pattern.cpp` |
| 列宽、分割线、选中背景或渐变异常 | `textpicker_layout_algorithm.cpp`、`textpicker_layout_property.h`、Bridge 中对应属性解析 |
| 事件不触发 | SDK 事件声明、`textpicker_event_hub.h`、Bridge 事件绑定、`NODE_TEXT_PICKER_EVENT_*` |
| 触觉反馈异常 | `textpicker_column_pattern.cpp`、`adapter/ohos/entrance/picker/` |
| C API 行为不一致 | `node_textpicker_modifier.cpp`、`interfaces/native/native_node.h`、C API 测试 |

## 调试入口

- 创建链路：从 `TextPickerDynamicModule` 或 `TextPickerModelNG` 确认 FrameNode 和 Pattern 创建。
- 属性链路：从 SDK 属性名定位 Bridge → `textpicker_dynamic_modifier.cpp` / `textpicker_static_modifier.cpp` → `TextPickerModelNG` / `TextPickerModelStatic`。
- 事件链路：从 SDK onChange/onScrollStop 到 Bridge 事件绑定，再到 `TextPickerEventHub` 和 C API 事件枚举。
- 级联链路：优先看 `textpicker_pattern.cpp` 的列构建和级联更新，再看 `textpicker_column_pattern.cpp` 的列内滚动。
- 回归验证：优先运行 `test/unittest/core/pattern/text_picker/` 和 `test/unittest/capi/modifiers/text_picker_modifier_test.cpp`。

## 相关主题

- DatePicker Context
- TimePicker Context
- UIPickerComponent Context
- 组件化改造通用方案
