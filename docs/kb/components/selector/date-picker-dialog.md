# DatePickerDialog Context

> 文档版本：v1.0
> 更新时间：2026-07-24
> 来源：`docs/context_registry.json` 主题 `DatePickerDialog`

## 定位

DatePickerDialog 是 ArkUI 日期选择弹窗，承载日期范围、选中日期、农历与时间组合、文本样式、按钮和弹窗事件等配置。它复用 DatePicker 的列、日期模型和本地化能力，通过 Dialog View 创建弹窗内容。

DatePickerDialog 已完成组件化改造，动态模块名为 `DatePickerDialog`，由 `libarkui_datepicker.z.so` 承载。具体参数、事件和版本差异以 SDK、源码、测试与 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| 主目录 | `frameworks/core/components_ng/pattern/date_picker/` | DatePicker 与 DatePickerDialog 实现集中目录 |
| Dialog View | `frameworks/core/components_ng/pattern/date_picker/datepicker_dialog_view.cpp`、`frameworks/core/components_ng/pattern/date_picker/datepicker_dialog_view.h` | 日期弹窗节点树、列、按钮和事件创建入口 |
| Dialog Model | `frameworks/core/components_ng/pattern/date_picker/datepicker_model_ng.cpp` | DatePickerDialogModelNG 与弹窗显示入口 |
| Dynamic Dialog Bridge | `frameworks/core/components_ng/pattern/date_picker/bridge/arkts_native_datepickerdialog_bridge.cpp` | Dynamic ArkTS options、样式和事件解析入口 |
| Static Dialog Extender | `frameworks/core/components_ng/pattern/date_picker/bridge/date_picker_dialog_extender.cpp` | Static ArkTS options 转换和显示入口 |
| Static Modifier | `frameworks/core/components_ng/pattern/date_picker/bridge/datepickerdialog_static_modifier.cpp` | Static Dialog modifier 入口 |
| Dynamic Module | `frameworks/core/components_ng/pattern/date_picker/bridge/datepickerdialog_dynamic_module.cpp` | DatePickerDialog 组件化模块入口 |
| JSView 兼容加载 | `frameworks/bridge/declarative_frontend/jsview/js_datepicker.cpp` | DatePickerDialogModel 的动态模块加载和旧 Pipeline 兼容入口 |
| Static UIContext 接入 | `frameworks/core/interfaces/native/implementation/dialog_extender_accessor.cpp` | Static UIContext DialogExtender 路由；不是公开 NDK API |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/date_picker.d.ts` | DatePickerDialog 与 DatePickerDialogOptions 声明 |
| Static API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/datePicker.static.d.ets` | Static ArkTS DatePickerDialogOptions 声明 |
| Dynamic UIContext | `<OH_ROOT>/interface/sdk-js/api/@ohos.arkui.UIContext.d.ts` | `showDatePickerDialog` 声明 |
| Static UIContext | `<OH_ROOT>/interface/sdk-js/api/@ohos.arkui.UIContext.static.d.ets` | Static `showDatePickerDialog` 声明 |
| Static UIContext 实现 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/base/UIContextImpl.ets` | Static ArkTS UIContext 到 DialogExtender 的入口 |

API 检索建议：在 SDK 中搜索 `DatePickerDialog`、`DatePickerDialogOptions`、`showDatePickerDialog`、`onDateAccept`、`onDateChange`。

### API 解析实现路径

DatePickerDialog 已组件化，`adapter/ohos/osal/dynamic_module_helper.cpp` 将其映射到 datepicker 模块。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| Dynamic 全局 API | `frameworks/core/components_ng/pattern/date_picker/bridge/arkts_native_datepickerdialog_bridge.cpp` | DatePickerDialog.show 参数、样式和事件解析 |
| Dynamic UIContext | `frameworks/bridge/declarative_frontend/engine/jsUIContext.js` | `showDatePickerDialog` 转发到动态 Dialog API |
| JSView Model 加载 | `frameworks/bridge/declarative_frontend/jsview/js_datepicker.cpp` | 通过 DynamicModuleHelper 获取 DatePickerDialogModelNG |
| Static UIContext | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/base/UIContextImpl.ets` | Static UIContext 调用 DialogExtender |
| Static accessor | `frameworks/core/interfaces/native/implementation/dialog_extender_accessor.cpp` | 加载 DatePickerDialog Static Modifier；不是公开 NDK API |
| Static 参数转换 | `frameworks/core/components_ng/pattern/date_picker/bridge/date_picker_dialog_extender.cpp` | 将 Static options 转为 PickerDialogInfo 和 DatePickerSettingData |
| Dynamic Module | `frameworks/core/components_ng/pattern/date_picker/bridge/datepickerdialog_dynamic_module.cpp` | 导出 DatePickerDialog 动态模块和 Model |
| 弹窗构建 | `frameworks/core/components_ng/pattern/date_picker/datepicker_dialog_view.cpp` | 创建并展示 DatePickerDialog |


### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| Picker 单元测试 | `test/unittest/core/pattern/picker/` | DatePickerDialog View、日期范围、列和事件回归 |
| Static accessor 测试 | `test/unittest/capi/accessors/date_picker_dialog_accessor_test.cpp` | Static ArkTS Dialog accessor 回归 |
| 组件测试样例 | `test/component_test/test_cases/components/popup_window/entry/src/main/ets/pages/date_picker_dialog/` | DatePickerDialog 组件级执行入口 |

### 相关 Spec

| Spec | 路径 |
|------|------|
| 设计文档 | `specs/05-ui-components/06-popup-components/06-date-picker-dialog/design.md` |
| DatePickerDialog 规格 | `specs/05-ui-components/06-popup-components/06-date-picker-dialog/Feat-01-date-picker-dialog-spec.md` |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| Dialog 未显示 | Dynamic/Static API 入口、DynamicModuleHelper、DatePickerDialogModelNG、Dialog View |
| 日期范围、农历或时间组合异常 | DatePickerDialogOptions 解析、Dialog Extender、DatePicker 模型和 Spec |
| 文本、按钮或弹窗样式异常 | Bridge/Extender 样式转换、DatePickerDialogView、主题 |
| 回调不触发或数据格式异常 | Dynamic Bridge、Dialog Extender 事件转换和 picker 测试 |
| UIContext 与全局 API 行为不一致 | `jsUIContext.js`、`UIContextImpl.ets`、DialogExtenderAccessor |

## 调试入口

- Dynamic 全局 API 从 DatePickerDialog Bridge 跟到 Model 和 Dialog View。
- Dynamic UIContext 先检查 `jsUIContext.js` 的转发，再进入同一 Dialog 路径。
- Static UIContext 从 `UIContextImpl.ets` 跟到 DialogExtenderAccessor、Static Modifier 和 DatePickerDialogExtender。
- 日期列和本地化问题转到 DatePicker Context；弹窗容器和事件问题留在 Dialog View。
- 回归验证优先运行 picker 目录的 DatePickerDialog 用例和 accessor 测试。

## 相关主题

- [DatePicker](date-picker.md)
- [TimePickerDialog](time-picker-dialog.md)
- [CalendarPickerDialog](calendar-picker-dialog.md)