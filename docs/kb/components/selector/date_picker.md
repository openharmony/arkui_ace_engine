# DatePicker Context

> 文档版本：v1.0
> 更新时间：2026-07-11
> 来源：`docs/context_registry.json` 主题 `DatePicker`

## 定位

DatePicker 是 ArkUI 的日期选择器组件，用于日期范围、选中日期、农历开关、文本样式和选择事件等场景。本文档只作为 DatePicker 相关源码、SDK 声明、C API、测试和 Spec 的快速路由；具体行为、默认值、边界处理和兼容性以 SDK 声明、源码实现、测试用例和 Spec 为准。

DatePicker 已完成组件化改造，动态模块名为 `DatePicker` / `DatePickerDialog`，组件模块通过 `arkui.components.arkdatepicker` 加载，构建产物对应 `libarkui_datepicker.z.so`。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| Pattern 主目录 | `frameworks/core/components_ng/pattern/date_picker/` | DatePicker、DatePickerDialog、列、布局、格式化和桥接实现集中目录 |
| DatePickerPattern | `frameworks/core/components_ng/pattern/date_picker/datepicker_pattern.cpp` | 日期列构建、联动、农历/公历状态和事件协调入口 |
| DatePickerColumnPattern | `frameworks/core/components_ng/pattern/date_picker/datepicker_column_pattern.cpp` | 单列滚动、无障碍和触觉反馈入口 |
| ArkTS Dynamic Model | `frameworks/core/components_ng/pattern/date_picker/datepicker_model_ng.cpp` | 动态前端和 node_modifier 写入 Model 的入口 |
| ArkTS Static Model | `frameworks/core/components_ng/pattern/date_picker/datepicker_model_static.cpp` | 静态前端属性写入入口 |
| 列布局算法 | `frameworks/core/components_ng/pattern/date_picker/datepicker_column_layout_algorithm.cpp` | 日期列布局测量入口 |
| 日期/时间数据类型 | `frameworks/core/components_ng/pattern/date_picker/picker_date.h`、`frameworks/core/components_ng/pattern/date_picker/picker_date_time.h` | DatePicker 数据结构和日期时间封装 |
| 字符串和本地化辅助 | `frameworks/core/components_ng/pattern/date_picker/picker_string_formatter.h`、`frameworks/core/components_ng/pattern/date_picker/picker_data.cpp` | 日期、农历和本地化字符串处理 |
| 事件定义 | `frameworks/core/components_ng/pattern/date_picker/datepicker_event_hub.h` | DatePicker 事件挂接 |
| 组件化 Bridge 目录 | `frameworks/core/components_ng/pattern/date_picker/bridge/` | 统一 Bridge、Dynamic/Static Modifier、DynamicModule 和 Dialog Bridge |
| JSView 兼容加载 | `frameworks/bridge/declarative_frontend/jsview/js_datepicker.cpp` | DatePicker / DatePickerDialog 动态模块加载兼容入口 |
| node_modifier | `frameworks/core/interfaces/native/node/node_date_picker_modifier.cpp` | C++ 属性 Set/Reset/Get 委托层 |
| C API 枚举 | `interfaces/native/native_node.h` | `ARKUI_NODE_DATE_PICKER`、`NODE_DATE_PICKER_*`、`NODE_DATE_PICKER_EVENT_*` |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/date_picker.d.ts` | `DatePickerInterface`、`DatePickerAttribute`、`DatePickerOptions`、Dialog 声明 |
| Static API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/datePicker.static.d.ets` | 静态 ArkTS DatePicker 组件、Options、Attribute 和 Dialog 声明 |
| Modifier API (Dynamic) | `<OH_ROOT>/interface/sdk-js/api/arkui/DatePickerModifier.d.ts` | 动态 Modifier 声明 |
| Modifier API (Static) | `<OH_ROOT>/interface/sdk-js/api/arkui/DatePickerModifier.static.d.ets` | 静态 Modifier 声明 |
| CAPI / NDK | `interfaces/native/native_node.h` | DatePicker 节点、属性和事件枚举 |
| Picker 通用结构 | `interfaces/native/node_attributes/picker.h` | Picker 通用 indicator/option 结构 |

API 检索建议：

- 构造参数：搜索 `DatePickerInterface`、`DatePickerOptions`、`DatePicker(`。
- 属性声明：搜索 `DatePickerAttribute` 和具体属性名。
- Dialog：搜索 `DatePickerDialog`、`DatePickerDialogOptions`。
- C API：搜索 `ARKUI_NODE_DATE_PICKER`、`NODE_DATE_PICKER_`。

### API 解析实现路径

DatePicker 已完成组件化改造，Bridge 和动态属性路径统一到 `pattern/date_picker/bridge/`；`js_datepicker.cpp` 仍保留为 DatePicker / TimePicker 动态模块加载兼容入口。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| 前端 JS/TS 定义 | `frameworks/bridge/declarative_frontend/ark_direct_component/src/arkdatepicker.ts` | 前端组件类和 JS 侧属性转发；Modifier 类见 `frameworks/bridge/declarative_frontend/ark_modifier/src/date_picker_modifier.ts` |
| 统一 Bridge（声明式 + 动态属性） | `frameworks/core/components_ng/pattern/date_picker/bridge/arkts_native_date_picker_bridge.cpp` | 参数解析、事件绑定和 node_modifier 调用入口 |
| Dialog Bridge | `frameworks/core/components_ng/pattern/date_picker/bridge/arkts_native_datepickerdialog_bridge.cpp` | DatePickerDialog 参数解析和显示入口 |
| Dynamic Modifier | `frameworks/core/components_ng/pattern/date_picker/bridge/datepicker_dynamic_modifier.cpp` | 动态属性路径，供 Bridge 和动态模块使用 |
| Static Modifier | `frameworks/core/components_ng/pattern/date_picker/bridge/datepicker_static_modifier.cpp` | 静态编译路径 |
| Dynamic Module | `frameworks/core/components_ng/pattern/date_picker/bridge/datepicker_dynamic_module.cpp` | `DatePickerDynamicModule`，动态模块入口 |
| JSView 兼容入口 | `frameworks/bridge/declarative_frontend/jsview/js_datepicker.cpp` | 通过 `DynamicModuleHelper` 获取 DatePicker / DatePickerDialog Model |
| node_modifier 委托层 | `frameworks/core/interfaces/native/node/node_date_picker_modifier.cpp` | C API 与 Bridge 共用的 C++ 属性委托层 |

组件化改造参考：`./组件化重构通用方案.md`。

### 外部依赖入口

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件 / 目标路径 | 说明 |
|----------|----------|------------|--------------------------------|------|
| 触觉反馈 | `frameworks/core/components_ng/pattern/date_picker/datepicker_column_pattern.cpp` | `foundation/multimedia/player_framework` | `audio_haptic` | 通过 `PickerAudioHapticFactory` 获取音频触觉控制器 |
| 触觉适配 | `adapter/ohos/entrance/picker/`、`adapter/ohos/entrance/vibrator/` | `base/sensors/miscdevice` | `vibrator_interface_native` | 平台侧触觉和 vibrator 适配 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| Pattern 单元测试 | `test/unittest/core/pattern/picker/` | DatePicker 模型、列、布局、顺序、资源、弹窗和 ToJson 等回归 |
| C API modifier 测试 | `test/unittest/capi/modifiers/date_picker_modifier_test.cpp` | DatePicker node_modifier/C API 属性回归 |
| Dialog accessor 测试 | `test/unittest/capi/accessors/date_picker_dialog_accessor_test.cpp` | DatePickerDialog C API accessor 回归 |

### 相关 Spec

| Spec | 路径 | 说明 |
|------|------|------|
| DatePicker 设计文档 | `specs/05-ui-components/05-picker-components/02-date-picker/design.md` | Spec 仓库存在时的设计入口 |
| DatePicker 特性规格 | `specs/05-ui-components/05-picker-components/02-date-picker/Feat-01-date-picker-full-spec.md` | DatePicker 功能规格定义 |
| 本仓规格目录 | `specs/05-ui-components/05-picker-components/02-date-picker/` | 当前工作区规格目录 |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 日期范围、选中日期或农历状态异常 | SDK `DatePickerOptions` / `DatePickerAttribute`，以及 `datepicker_model_ng.cpp`、`datepicker_pattern.cpp` |
| 年月日列联动异常 | `datepicker_pattern.cpp`、`datepicker_column_pattern.cpp` |
| Dialog 参数不生效 | `arkts_native_datepickerdialog_bridge.cpp`、`date_picker_dialog_extender.cpp`、`datepicker_dialog_view.cpp` |
| 本地化、日期顺序或农历字符串异常 | `picker_string_formatter.h`、`picker_data.cpp`、`base/i18n` 相关入口 |
| 事件不触发 | SDK 事件声明、Bridge 事件绑定、`datepicker_event_hub.h`、`NODE_DATE_PICKER_EVENT_*` |
| C API 行为不一致 | `node_date_picker_modifier.cpp`、`interfaces/native/native_node.h`、C API 测试 |

## 调试入口

- 创建链路：从 `DatePickerDynamicModule`、`DatePickerModelNG` 或 `js_datepicker.cpp` 确认 Model 获取和 FrameNode 创建。
- 属性链路：从 SDK 属性名定位 Bridge → `datepicker_dynamic_modifier.cpp` / `datepicker_static_modifier.cpp` → `DatePickerModelNG` / `DatePickerModelStatic`。
- 联动链路：优先看 `datepicker_pattern.cpp` 的列构建、日期调整和农历/公历切换。
- Dialog 链路：从 `arkts_native_datepickerdialog_bridge.cpp` 和 `date_picker_dialog_extender.cpp` 跟到 `datepicker_dialog_view.cpp`。
- 回归验证：优先运行 `test/unittest/core/pattern/picker/` 和 `test/unittest/capi/modifiers/date_picker_modifier_test.cpp`。

## 相关主题

- TextPicker Context
- TimePicker Context
- UIPickerComponent Context
- CalendarPicker Context
- 组件化改造通用方案
