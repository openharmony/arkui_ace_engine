# TimePickerDialog Context

> 文档版本：v1.0
> 更新时间：2026-07-24
> 来源：`docs/context_registry.json` 主题 `TimePickerDialog`

## 定位

TimePickerDialog 是 ArkUI 时间选择弹窗，承载选中时间、时间范围、小时制、文本样式、按钮和弹窗事件等配置。它复用 TimePicker 的列、格式化、本地化和触觉反馈能力，通过 TimePickerDialogView 构建弹窗内容。

TimePickerDialog 已完成组件化改造，动态模块名为 `TimePickerDialog`，由 `libarkui_timepicker.z.so` 承载。具体参数、事件和版本差异以 SDK、源码、测试与 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| 主目录 | `frameworks/core/components_ng/pattern/time_picker/` | TimePicker 与 TimePickerDialog 实现集中目录 |
| Dialog View | `frameworks/core/components_ng/pattern/time_picker/timepicker_dialog_view.cpp`、`frameworks/core/components_ng/pattern/time_picker/timepicker_dialog_view.h` | 时间弹窗节点树、列、按钮和事件创建入口 |
| Dialog Model | `frameworks/core/components_ng/pattern/time_picker/timepicker_model_ng.cpp` | TimePickerDialogModelNG 与弹窗显示入口 |
| Dynamic Dialog Bridge | `frameworks/core/components_ng/pattern/time_picker/bridge/arkts_native_timepickerdialog_bridge.cpp` | Dynamic ArkTS options、样式和事件解析入口 |
| Static Dialog Extender | `frameworks/core/components_ng/pattern/time_picker/bridge/time_picker_dialog_extender.cpp` | Static ArkTS options 转换和显示入口 |
| Static Modifier | `frameworks/core/components_ng/pattern/time_picker/bridge/timepickerdialog_static_modifier.cpp` | Static Dialog modifier 入口 |
| Dynamic Module | `frameworks/core/components_ng/pattern/time_picker/bridge/timepickerdialog_dynamic_module.cpp` | TimePickerDialog 组件化模块入口 |
| JSView 兼容加载 | `frameworks/bridge/declarative_frontend/jsview/js_datepicker.cpp` | TimePickerDialogModel 的动态模块加载和旧 Pipeline 兼容入口 |
| Static UIContext 接入 | `frameworks/core/interfaces/native/implementation/dialog_extender_accessor.cpp` | Static UIContext DialogExtender 路由；不是公开 NDK API |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/time_picker.d.ts` | TimePickerDialog 与 TimePickerDialogOptions 声明 |
| Static API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/timePicker.static.d.ets` | Static ArkTS TimePickerDialogOptions 声明 |
| Dynamic UIContext | `<OH_ROOT>/interface/sdk-js/api/@ohos.arkui.UIContext.d.ts` | `showTimePickerDialog` 声明 |
| Static UIContext | `<OH_ROOT>/interface/sdk-js/api/@ohos.arkui.UIContext.static.d.ets` | Static `showTimePickerDialog` 声明 |
| Static UIContext 实现 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/base/UIContextImpl.ets` | Static ArkTS UIContext 到 DialogExtender 的入口 |

API 检索建议：在 SDK 中搜索 `TimePickerDialog`、`TimePickerDialogOptions`、`showTimePickerDialog`、`useMilitaryTime` 和具体回调名。

### API 解析实现路径

TimePickerDialog 已组件化，`adapter/ohos/osal/dynamic_module_helper.cpp` 将其映射到 timepicker 模块。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| Dynamic 全局 API | `frameworks/core/components_ng/pattern/time_picker/bridge/arkts_native_timepickerdialog_bridge.cpp` | TimePickerDialog.show 参数、样式和事件解析 |
| Dynamic UIContext | `frameworks/bridge/declarative_frontend/engine/jsUIContext.js` | `showTimePickerDialog` 转发到动态 Dialog API |
| JSView Model 加载 | `frameworks/bridge/declarative_frontend/jsview/js_datepicker.cpp` | 通过 DynamicModuleHelper 获取 TimePickerDialogModelNG |
| Static UIContext | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/base/UIContextImpl.ets` | Static UIContext 调用 DialogExtender |
| Static accessor | `frameworks/core/interfaces/native/implementation/dialog_extender_accessor.cpp` | 加载 TimePickerDialog Static Modifier；不是公开 NDK API |
| Static 参数转换 | `frameworks/core/components_ng/pattern/time_picker/bridge/time_picker_dialog_extender.cpp` | 将 Static options 转为时间选择弹窗数据 |
| Dynamic Module | `frameworks/core/components_ng/pattern/time_picker/bridge/timepickerdialog_dynamic_module.cpp` | 导出 TimePickerDialog 动态模块和 Model |
| 弹窗构建 | `frameworks/core/components_ng/pattern/time_picker/timepicker_dialog_view.cpp` | 创建并展示 TimePickerDialog |


### 外部依赖入口

外部仓路径以 OpenHarmony 根目录为基准。

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件 / 目标路径 | 说明 |
|----------|----------|------------|--------------------------------|------|
| 触觉反馈 | `frameworks/core/components_ng/pattern/time_picker/timepicker_column_pattern.cpp` | `foundation/multimedia/player_framework` | `audio_haptic` | 选择列滚动的音频触觉控制入口 |
| 振动适配 | `adapter/ohos/entrance/picker/`、`adapter/ohos/entrance/vibrator/` | `base/sensors/miscdevice` | `vibrator_interface_native` | OHOS 平台振动适配入口 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| Dialog 单元测试 | `test/unittest/core/pattern/time_picker/` | TimePickerDialog View、显示、时间数据和事件回归 |
| Static accessor 测试 | `test/unittest/capi/accessors/time_picker_dialog_accessor_test.cpp` | Static ArkTS Dialog accessor 回归 |
| 组件测试样例 | `test/component_test/test_cases/components/popup_window/entry/src/main/ets/pages/time_picker_dialog/` | TimePickerDialog 组件级执行入口 |

### 相关 Spec

| Spec | 路径 |
|------|------|
| 设计文档 | `specs/05-ui-components/06-popup-components/07-time-picker-dialog/design.md` |
| TimePickerDialog 规格 | `specs/05-ui-components/06-popup-components/07-time-picker-dialog/Feat-01-time-picker-dialog-spec.md` |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| Dialog 未显示 | Dynamic/Static API 入口、DynamicModuleHelper、TimePickerDialogModelNG、Dialog View |
| 选中时间、范围或小时制异常 | TimePickerDialogOptions 解析、Dialog Extender、TimePicker 模型和 Spec |
| 文本、按钮或弹窗样式异常 | Bridge/Extender 样式转换、TimePickerDialogView、主题 |
| 回调不触发或结果格式异常 | Dynamic Bridge、Dialog Extender 事件转换和 Dialog 测试 |
| UIContext 与全局 API 行为不一致 | `jsUIContext.js`、`UIContextImpl.ets`、DialogExtenderAccessor |

## 调试入口

- Dynamic 全局 API 从 TimePickerDialog Bridge 跟到 Model 和 Dialog View。
- Dynamic UIContext 先检查 `jsUIContext.js` 的转发，再进入同一 Dialog 路径。
- Static UIContext 从 `UIContextImpl.ets` 跟到 DialogExtenderAccessor、Static Modifier 和 TimePickerDialogExtender。
- 时间列、本地化和触觉反馈问题转到 TimePicker Context；弹窗容器和事件问题留在 Dialog View。
- 回归验证优先运行 time_picker 目录 Dialog 用例和 accessor 测试。

## 相关主题

- [TimePicker](time-picker.md)
- [DatePickerDialog](date-picker-dialog.md)
- [TextPickerDialog](text-picker-dialog.md)