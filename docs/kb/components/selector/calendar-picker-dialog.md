# CalendarPickerDialog Context

> 文档版本：v1.0
> 更新时间：2026-07-24
> 来源：`docs/context_registry.json` 主题 `CalendarPickerDialog`

## 定位

CalendarPickerDialog 是 ArkUI 日历选择弹窗，通过 CalendarPickerDialog API 展示日历面板并处理日期选择、确认、取消和弹窗生命周期事件。它复用 CalendarPicker 的日期模型与主题能力，但弹窗创建、布局和事件组织集中在 calendar_picker 目录的 dialog 实现中。

CalendarPickerDialog 已完成组件化改造，动态模块名为 `CalendarPickerDialog`，由 `libarkui_calendarpicker.z.so` 承载。具体参数、事件、样式和兼容性以 SDK、源码、测试与 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| 主目录 | `frameworks/core/components_ng/pattern/calendar_picker/` | CalendarPicker 与 CalendarPickerDialog 的 Pattern、布局、View 和 Bridge 集中目录 |
| Dialog View | `frameworks/core/components_ng/pattern/calendar_picker/calendar_dialog_view.cpp`、`frameworks/core/components_ng/pattern/calendar_picker/calendar_dialog_view.h` | 弹窗节点树、按钮和内容创建入口 |
| Dialog Pattern | `frameworks/core/components_ng/pattern/calendar_picker/calendar_dialog_pattern.cpp`、`frameworks/core/components_ng/pattern/calendar_picker/calendar_dialog_pattern.h` | 弹窗交互、焦点和生命周期协调入口 |
| Dialog 布局 | `frameworks/core/components_ng/pattern/calendar_picker/calendar_dialog_layout_algorithm.cpp` | CalendarPickerDialog 布局测量入口 |
| Dialog Bridge | `frameworks/core/components_ng/pattern/calendar_picker/bridge/arkts_native_calendar_picker_dialog_bridge.cpp` | Dynamic ArkTS 参数与回调解析入口 |
| Dynamic Modifier | `frameworks/core/components_ng/pattern/calendar_picker/bridge/calendar_picker_dialog_dynamic_modifier.cpp` | Dynamic Dialog 调用入口 |
| Static Modifier | `frameworks/core/components_ng/pattern/calendar_picker/bridge/calendar_picker_dialog_static_modifier.cpp` | Static ArkTS Dialog 参数转换和显示入口 |
| Dynamic Module | `frameworks/core/components_ng/pattern/calendar_picker/bridge/calendar_picker_dialog_dynamic_module.cpp` | 组件化动态模块注册入口 |
| Static 内部 accessor | `frameworks/core/interfaces/native/implementation/calendar_picker_dialog_accessor.cpp` | Static ArkTS 运行时 accessor；不是公开 NDK API |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/calendar_picker.d.ts` | CalendarPickerDialog、CalendarDialogOptions 和回调声明 |
| Static API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/calendarPicker.static.d.ets` | Static ArkTS CalendarPickerDialog 声明 |
| 内部 Static 接口 | `frameworks/core/interfaces/native/generated/interface/arkoala_api_generated.h` | 生成的运行时接口声明；不是公开 NDK API |

API 检索建议：在 SDK 文件中搜索 `CalendarPickerDialog`、`CalendarDialogOptions`、`CalendarPickerDialog.show` 和具体回调名。

### API 解析实现路径

CalendarPickerDialog 已组件化，`adapter/ohos/osal/dynamic_module_helper.cpp` 将其映射到 calendarpicker 模块。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| Dynamic API 注册 | `frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_api_impl_bridge.cpp` | 注册 CalendarPickerDialog 动态模块名 |
| 统一 Dynamic Bridge | `frameworks/core/components_ng/pattern/calendar_picker/bridge/arkts_native_calendar_picker_dialog_bridge.cpp` | 解析 Dialog options、样式和事件，并调用 Dynamic Modifier |
| Dynamic Modifier | `frameworks/core/components_ng/pattern/calendar_picker/bridge/calendar_picker_dialog_dynamic_modifier.cpp` | Dynamic 调用转 CalendarDialogView |
| Static Modifier | `frameworks/core/components_ng/pattern/calendar_picker/bridge/calendar_picker_dialog_static_modifier.cpp` | Static ArkTS 参数转换和显示路径 |
| Static 内部 accessor | `frameworks/core/interfaces/native/implementation/calendar_picker_dialog_accessor.cpp` | Static ArkTS 运行时 accessor 路径，不属于公开 NDK API |
| Dynamic Module | `frameworks/core/components_ng/pattern/calendar_picker/bridge/calendar_picker_dialog_dynamic_module.cpp` | 导出 `CalendarPickerDialog` 模块并提供 Dynamic/Static 入口 |
| 弹窗构建 | `frameworks/core/components_ng/pattern/calendar_picker/calendar_dialog_view.cpp` | 创建并展示 CalendarPickerDialog 节点树 |


### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| Dialog Pattern 测试 | `test/unittest/core/pattern/calendar_picker/calendar_dialog_pattern_test_ng.cpp` | 弹窗 Pattern、交互和状态回归 |
| Dialog View 测试 | `test/unittest/core/pattern/calendar_picker/calendar_dialog_view_test_ng.cpp` | 弹窗构建、属性和事件回归 |
| Static accessor 测试 | `test/unittest/capi/accessors/calendar_picker_dialog_accessor_test.cpp` | Static ArkTS 内部 accessor 回归 |
| 组件测试样例 | `test/component_test/test_cases/components/popup_window/entry/src/main/ets/pages/calendar_picker_dialog/` | CalendarPickerDialog 组件级执行入口 |

### 相关 Spec

| Spec | 路径 |
|------|------|
| 设计文档 | `specs/05-ui-components/06-popup-components/05-calendar-picker-dialog/design.md` |
| CalendarPickerDialog 规格 | `specs/05-ui-components/06-popup-components/05-calendar-picker-dialog/Feat-01-calendar-picker-dialog-spec.md` |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| Dialog 未显示 | SDK 参数、Dynamic/Static 入口、CalendarDialogView、当前 PipelineContext |
| 日期范围或选中日期异常 | CalendarDialogOptions 解析、CalendarPicker 日期模型、CalendarDialogView |
| 确认、取消或变化事件不触发 | Bridge/Static Modifier 回调转换、CalendarDialogPattern、对应测试 |
| 弹窗样式或布局异常 | CalendarDialogLayoutAlgorithm、CalendarDialogView、主题和 Spec |
| Static ArkTS 行为异常 | calendar picker dialog accessor、Static Modifier 和 accessor 测试 |

## 调试入口

- Dynamic ArkTS 从动态模块注册进入 Dialog Bridge，再跟到 Dynamic Modifier 和 CalendarDialogView。
- Static ArkTS 从内部 accessor 或 Static Modifier 进入；这些路径不是公开 NDK API。
- 日期内容和选择状态问题结合 CalendarPicker 源码定位，弹窗容器问题优先看 CalendarDialogPattern。
- 回归验证优先运行 calendar dialog Pattern/View 测试和 accessor 测试。

## 相关主题

- CalendarPicker：`docs/pattern/calendar_picker/Calendar_Picker_Knowledge_Base.md`
- [DatePickerDialog](date-picker-dialog.md)
- [DatePicker](date-picker.md)