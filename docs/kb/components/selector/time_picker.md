# TimePicker Context

> 文档版本：v1.0
> 更新时间：2026-07-11
> 来源：`docs/context_registry.json` 主题 `TimePicker`

## 定位

TimePicker 是 ArkUI 的时间选择器组件，用于时分秒选择、12/24 小时制、时间文本格式、级联和选择事件等场景。本文档只作为 TimePicker 相关源码、SDK 声明、C API、测试和 Spec 的快速路由；具体行为、默认值、边界处理和兼容性以 SDK 声明、源码实现、测试用例和 Spec 为准。

TimePicker 已完成组件化改造，动态模块名为 `TimePicker` / `TimePickerDialog`，组件模块通过 `arkui.components.arktimepicker` 加载，构建产物对应 `libarkui_timepicker.z.so`。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| Pattern 主目录 | `frameworks/core/components_ng/pattern/time_picker/` | TimePicker、TimePickerDialog、列、布局、格式化和桥接实现集中目录 |
| Row Pattern | `frameworks/core/components_ng/pattern/time_picker/timepicker_row_pattern.cpp` | 时分秒列构建、12/24 小时制、级联和事件协调入口 |
| Column Pattern | `frameworks/core/components_ng/pattern/time_picker/timepicker_column_pattern.cpp` | 单列滚动、无障碍和触觉反馈入口 |
| ArkTS Dynamic Model | `frameworks/core/components_ng/pattern/time_picker/timepicker_model_ng.cpp` | 动态前端和 node_modifier 写入 Model 的入口 |
| ArkTS Static Model | `frameworks/core/components_ng/pattern/time_picker/timepicker_model_static.cpp` | 静态前端属性写入入口 |
| 列布局算法 | `frameworks/core/components_ng/pattern/time_picker/timepicker_column_layout_algorithm.cpp` | 时间列布局测量入口 |
| 布局辅助 | `frameworks/core/components_ng/pattern/time_picker/timepicker_layout_utils.cpp` | TimePicker 布局和尺寸辅助 |
| 事件定义 | `frameworks/core/components_ng/pattern/time_picker/timepicker_event_hub.h` | TimePicker 事件挂接 |
| 组件化 Bridge 目录 | `frameworks/core/components_ng/pattern/time_picker/bridge/` | 统一 Bridge、Dynamic/Static Modifier、DynamicModule 和 Dialog Bridge |
| JSView 兼容加载 | `frameworks/bridge/declarative_frontend/jsview/js_datepicker.cpp` | TimePicker / TimePickerDialog 动态模块加载兼容入口 |
| node_modifier | `frameworks/core/interfaces/native/node/node_timepicker_modifier.cpp` | C++ 属性 Set/Reset/Get 委托层 |
| C API 枚举 | `interfaces/native/native_node.h` | `ARKUI_NODE_TIME_PICKER`、`NODE_TIME_PICKER_*`、`NODE_TIME_PICKER_EVENT_*` |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/time_picker.d.ts` | `TimePickerInterface`、`TimePickerAttribute`、`TimePickerOptions`、Dialog 声明 |
| Static API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/timePicker.static.d.ets` | 静态 ArkTS TimePicker 组件、Options、Attribute 和 Dialog 声明 |
| Modifier API (Dynamic) | `<OH_ROOT>/interface/sdk-js/api/arkui/TimePickerModifier.d.ts` | 动态 Modifier 声明 |
| Modifier API (Static) | `<OH_ROOT>/interface/sdk-js/api/arkui/TimePickerModifier.static.d.ets` | 静态 Modifier 声明 |
| CAPI / NDK | `interfaces/native/native_node.h` | TimePicker 节点、属性和事件枚举 |
| Picker 通用结构 | `interfaces/native/node_attributes/picker.h` | Picker 通用 indicator/option 结构 |

API 检索建议：

- 构造参数：搜索 `TimePickerInterface`、`TimePickerOptions`、`TimePicker(`。
- 属性声明：搜索 `TimePickerAttribute` 和具体属性名。
- Dialog：搜索 `TimePickerDialog`、`TimePickerDialogOptions`。
- C API：搜索 `ARKUI_NODE_TIME_PICKER`、`NODE_TIME_PICKER_`。

### API 解析实现路径

TimePicker 已完成组件化改造，Bridge 和动态属性路径统一到 `pattern/time_picker/bridge/`；`js_datepicker.cpp` 仍保留为 DatePicker / TimePicker 动态模块加载兼容入口。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| 前端 Modifier 定义 | `frameworks/bridge/declarative_frontend/ark_modifier/src/time_picker_modifier.ts` | TimePicker Modifier 类和 `arkui.components.arktimepicker` 模块加载入口 |
| 动态组件加载 | `frameworks/bridge/declarative_frontend/engine/arkDynamicComponent.js` | 前端动态组件侧加载 TimePicker / TimePickerDialog 模块 |
| 统一 Bridge（声明式 + 动态属性） | `frameworks/core/components_ng/pattern/time_picker/bridge/arkts_native_timepicker_bridge.cpp` | 参数解析、事件绑定和 node_modifier 调用入口 |
| Dialog Bridge | `frameworks/core/components_ng/pattern/time_picker/bridge/arkts_native_timepickerdialog_bridge.cpp` | TimePickerDialog 参数解析和显示入口 |
| Dynamic Modifier | `frameworks/core/components_ng/pattern/time_picker/bridge/timepicker_dynamic_modifier.cpp` | 动态属性路径，供 Bridge 和动态模块使用 |
| Static Modifier | `frameworks/core/components_ng/pattern/time_picker/bridge/timepicker_static_modifier.cpp` | 静态编译路径 |
| Dynamic Module | `frameworks/core/components_ng/pattern/time_picker/bridge/timepicker_dynamic_module.cpp` | `TimePickerDynamicModule`，动态模块入口 |
| JSView 兼容入口 | `frameworks/bridge/declarative_frontend/jsview/js_datepicker.cpp` | 通过 `DynamicModuleHelper` 获取 TimePicker / TimePickerDialog Model |
| node_modifier 委托层 | `frameworks/core/interfaces/native/node/node_timepicker_modifier.cpp` | C API 与 Bridge 共用的 C++ 属性委托层 |

组件化改造参考：`./组件化重构通用方案.md`。

### 外部依赖入口

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件 / 目标路径 | 说明 |
|----------|----------|------------|--------------------------------|------|
| 触觉反馈 | `frameworks/core/components_ng/pattern/time_picker/timepicker_column_pattern.cpp` | `foundation/multimedia/player_framework` | `audio_haptic` | 通过 `PickerAudioHapticFactory` 获取音频触觉控制器 |
| 触觉适配 | `adapter/ohos/entrance/picker/`、`adapter/ohos/entrance/vibrator/` | `base/sensors/miscdevice` | `vibrator_interface_native` | 平台侧触觉和 vibrator 适配 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| Pattern 单元测试 | `test/unittest/core/pattern/time_picker/` | TimePicker 模型、列、布局、12/24 小时制、弹窗、资源和 ToJson 等回归 |
| C API modifier 测试 | `test/unittest/capi/modifiers/time_picker_modifier_test.cpp` | TimePicker node_modifier/C API 属性回归 |
| Dialog accessor 测试 | `test/unittest/capi/accessors/time_picker_dialog_accessor_test.cpp` | TimePickerDialog C API accessor 回归 |

### 相关 Spec

| Spec | 路径 | 说明 |
|------|------|------|
| TimePicker 设计文档 | `specs/05-ui-components/05-picker-components/04-time-picker/design.md` | Spec 仓库存在时的设计入口 |
| TimePicker 特性规格 | `specs/05-ui-components/05-picker-components/04-time-picker/Feat-01-time-picker-full-spec.md` | TimePicker 功能规格定义 |
| 本仓规格目录 | `specs/05-ui-components/05-picker-components/04-time-picker/` | 当前工作区规格目录 |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 选中时间、起止时间或 12/24 小时制异常 | SDK `TimePickerOptions` / `TimePickerAttribute`，以及 `timepicker_model_ng.cpp`、`timepicker_row_pattern.cpp` |
| 时分秒列联动异常 | `timepicker_row_pattern.cpp`、`timepicker_column_pattern.cpp` |
| 时间格式、AM/PM 或前导零异常 | `timepicker_row_pattern.cpp`、`timepicker_layout_utils.cpp`、`base/i18n` 相关入口 |
| Dialog 参数不生效 | `arkts_native_timepickerdialog_bridge.cpp`、`time_picker_dialog_extender.cpp`、`timepicker_dialog_view.cpp` |
| 事件不触发 | SDK 事件声明、Bridge 事件绑定、`timepicker_event_hub.h`、`NODE_TIME_PICKER_EVENT_*` |
| C API 行为不一致 | `node_timepicker_modifier.cpp`、`interfaces/native/native_node.h`、C API 测试 |

## 调试入口

- 创建链路：从 `TimePickerDynamicModule`、`TimePickerModelNG` 或 `js_datepicker.cpp` 确认 Model 获取和 FrameNode 创建。
- 属性链路：从 SDK 属性名定位 Bridge → `timepicker_dynamic_modifier.cpp` / `timepicker_static_modifier.cpp` → `TimePickerModelNG` / `TimePickerModelStatic`。
- 时间格式链路：从 `timepicker_row_pattern.cpp` 的 12/24 小时制和 AM/PM 处理入口追到 `base/i18n`。
- Dialog 链路：从 `arkts_native_timepickerdialog_bridge.cpp` 和 `time_picker_dialog_extender.cpp` 跟到 `timepicker_dialog_view.cpp`。
- 回归验证：优先运行 `test/unittest/core/pattern/time_picker/` 和 `test/unittest/capi/modifiers/time_picker_modifier_test.cpp`。

## 相关主题

- DatePicker Context
- TextPicker Context
- UIPickerComponent Context
- 组件化改造通用方案
