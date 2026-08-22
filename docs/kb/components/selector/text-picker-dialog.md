# TextPickerDialog Context

> 文档版本：v1.0
> 更新时间：2026-07-24
> 来源：`docs/context_registry.json` 主题 `TextPickerDialog`

## 定位

TextPickerDialog 是 ArkUI 文本选择弹窗，承载单列、多列、级联数据、选中项、循环、文本样式、按钮和弹窗事件等配置。它复用 TextPicker 的列、数据模型和触觉反馈能力，通过 TextPickerDialogView 构建弹窗内容。

TextPickerDialog 已完成组件化改造，动态模块名为 `TextPickerDialog`，由 `libarkui_textpicker.z.so` 承载。具体参数、事件和版本差异以 SDK、源码、测试与 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| 主目录 | `frameworks/core/components_ng/pattern/text_picker/` | TextPicker 与 TextPickerDialog 实现集中目录 |
| Dialog View | `frameworks/core/components_ng/pattern/text_picker/textpicker_dialog_view.cpp`、`frameworks/core/components_ng/pattern/text_picker/textpicker_dialog_view.h` | 文本选择弹窗节点树、列、按钮和事件创建入口 |
| Dialog Model | `frameworks/core/components_ng/pattern/text_picker/textpicker_model_ng.cpp` | TextPickerDialogModelNG 与弹窗显示入口 |
| Dynamic Dialog Bridge | `frameworks/core/components_ng/pattern/text_picker/bridge/arkts_native_textpickerdialog_bridge.cpp` | Dynamic ArkTS options、样式和事件解析入口 |
| Static Dialog Extender | `frameworks/core/components_ng/pattern/text_picker/bridge/text_picker_dialog_extender.cpp` | Static ArkTS options 转换和显示入口 |
| Static Modifier | `frameworks/core/components_ng/pattern/text_picker/bridge/textpickerdialog_static_modifier.cpp` | Static Dialog modifier 入口 |
| Dynamic Module | `frameworks/core/components_ng/pattern/text_picker/bridge/textpickerdialog_dynamic_module.cpp` | TextPickerDialog 组件化模块入口 |
| Static UIContext 接入 | `frameworks/core/interfaces/native/implementation/dialog_extender_accessor.cpp` | Static UIContext DialogExtender 路由；不是公开 NDK API |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/text_picker.d.ts` | TextPickerDialog、Options 和扩展 Options 声明 |
| Static API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/textPicker.static.d.ets` | Static ArkTS TextPickerDialogOptions 声明 |
| Dynamic UIContext | `<OH_ROOT>/interface/sdk-js/api/@ohos.arkui.UIContext.d.ts` | `showTextPickerDialog` 声明 |
| Static UIContext | `<OH_ROOT>/interface/sdk-js/api/@ohos.arkui.UIContext.static.d.ets` | Static `showTextPickerDialog` 声明 |
| Static UIContext 实现 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/base/UIContextImpl.ets` | Static ArkTS UIContext 到 DialogExtender 的入口 |

API 检索建议：在 SDK 中搜索 `TextPickerDialog`、`TextPickerDialogOptions`、`TextPickerDialogOptionsExt`、`showTextPickerDialog` 和具体回调名。

### API 解析实现路径

TextPickerDialog 已组件化，`adapter/ohos/osal/dynamic_module_helper.cpp` 将其映射到 textpicker 模块。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| Dynamic API 注册 | `frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_api_impl_bridge.cpp` | 注册 TextPickerDialog 动态模块名 |
| Dynamic 全局 API | `frameworks/core/components_ng/pattern/text_picker/bridge/arkts_native_textpickerdialog_bridge.cpp` | TextPickerDialog.show 参数、数据、样式和事件解析 |
| Dynamic UIContext | `frameworks/bridge/declarative_frontend/engine/jsUIContext.js` | `showTextPickerDialog` 转发到动态 Dialog API |
| Static UIContext | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/base/UIContextImpl.ets` | Static UIContext 调用 DialogExtender |
| Static accessor | `frameworks/core/interfaces/native/implementation/dialog_extender_accessor.cpp` | 加载 TextPickerDialog Static Modifier；不是公开 NDK API |
| Static 参数转换 | `frameworks/core/components_ng/pattern/text_picker/bridge/text_picker_dialog_extender.cpp` | 转换单列、多列、级联和扩展 options |
| Dynamic Module | `frameworks/core/components_ng/pattern/text_picker/bridge/textpickerdialog_dynamic_module.cpp` | 导出 TextPickerDialog 动态模块和 Model |
| 弹窗构建 | `frameworks/core/components_ng/pattern/text_picker/textpicker_dialog_view.cpp` | 创建并展示 TextPickerDialog |


### 外部依赖入口

外部仓路径以 OpenHarmony 根目录为基准。

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件 / 目标路径 | 说明 |
|----------|----------|------------|--------------------------------|------|
| 触觉反馈 | `frameworks/core/components_ng/pattern/text_picker/textpicker_column_pattern.cpp` | `foundation/multimedia/player_framework` | `audio_haptic` | 选择列滚动的音频触觉控制入口 |
| 振动适配 | `adapter/ohos/entrance/picker/`、`adapter/ohos/entrance/vibrator/` | `base/sensors/miscdevice` | `vibrator_interface_native` | OHOS 平台振动适配入口 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| TextPicker 单元测试 | `test/unittest/core/pattern/text_picker/` | TextPickerDialog 数据、列、显示和事件回归 |
| Static accessor 测试 | `test/unittest/capi/accessors/text_picker_dialog_accessor_test.cpp` | Static ArkTS Dialog accessor 回归 |
| 组件测试样例 | `test/component_test/test_cases/components/popup_window/entry/src/main/ets/pages/text_picker_dialog/` | TextPickerDialog 组件级执行入口 |

### 相关 Spec

| Spec | 路径 |
|------|------|
| 设计文档 | `specs/05-ui-components/06-popup-components/08-text-picker-dialog/design.md` |
| TextPickerDialog 规格 | `specs/05-ui-components/06-popup-components/08-text-picker-dialog/Feat-01-text-picker-dialog-spec.md` |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| Dialog 未显示 | Dynamic/Static API 入口、DynamicModuleHelper、TextPickerDialogModelNG、Dialog View |
| 单列、多列或级联数据异常 | Options 解析、TextPickerDialogExtender、TextPicker 数据模型和 Spec |
| selected、value 或循环状态异常 | Dynamic Bridge/Extender、TextPicker Pattern 和 Dialog 测试 |
| 文本、按钮或弹窗样式异常 | Bridge/Extender 样式转换、TextPickerDialogView、主题 |
| UIContext 与全局 API 行为不一致 | `jsUIContext.js`、`UIContextImpl.ets`、DialogExtenderAccessor |

## 调试入口

- Dynamic 全局 API 从 TextPickerDialog Bridge 跟到 Model 和 Dialog View。
- Dynamic UIContext 先检查 `jsUIContext.js` 的转发，再进入同一 Dialog 路径。
- Static UIContext 从 `UIContextImpl.ets` 跟到 DialogExtenderAccessor、Static Modifier 和 TextPickerDialogExtender。
- 数据列、级联和触觉反馈问题转到 TextPicker Context；弹窗容器和事件问题留在 Dialog View。
- 回归验证优先运行 text_picker 目录相关用例和 accessor 测试。

## 相关主题

- `TextPicker`：[docs/kb/components/selector/text-picker.md](text-picker.md)
- `TimePickerDialog`：[docs/kb/components/selector/time-picker-dialog.md](time-picker-dialog.md)
- `DatePickerDialog`：[docs/kb/components/selector/date-picker-dialog.md](date-picker-dialog.md)