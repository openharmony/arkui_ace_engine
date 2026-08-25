# AlertDialog Context

> 文档版本：v1.0
> 更新时间：2026-07-28
> 来源：`docs/context_registry.json` 主题 `AlertDialog`

## 定位

ArkUI AlertDialog 提供警告弹窗交互，基于 DialogPattern 实现。支持 title/message/buttons 配置，通过 AlertDialogModelNG 创建。可通过声明式 `AlertDialog.show()` 或 `@ohos.promptAction.showDialog()` 调用。C API 暴露在 dialog_model.cpp。

本文档用于快速定位 AlertDialog 相关源码、SDK 声明、测试和规格文档。具体行为、默认值、边界条件和兼容性说明以对应 SDK 声明、源码实现、测试用例和 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| alert_dialog_model | `frameworks/core/components_ng/pattern/dialog/alert_dialog/alert_dialog_model.h` | |
| alert_dialog_model_ng | `frameworks/core/components_ng/pattern/dialog/alert_dialog/alert_dialog_model_ng.cpp` | |
| base_dialog_pattern | `frameworks/core/components_ng/pattern/dialog/dialog_pattern.cpp` | |
| dialog_layout_algorithm | `frameworks/core/components_ng/pattern/dialog/dialog_layout_algorithm.cpp` | |
| dialog_layout_property | `frameworks/core/components_ng/pattern/dialog/dialog_layout_property.h` | |
| dialog_view | `frameworks/core/components_ng/pattern/dialog/dialog_view.cpp` | |
| overlay_dialog_manager | `frameworks/core/components_ng/pattern/overlay/dialog_manager.cpp` | |
| overlay_manager | `frameworks/core/components_ng/pattern/overlay/overlay_manager.cpp` | |
| js_alert_dialog | `frameworks/bridge/declarative_frontend/jsview/dialog/js_alert_dialog.cpp` | |
| napi_prompt_action | `interfaces/napi/kits/promptaction/js_prompt_action.cpp` | |
| node_dialog_model | `interfaces/native/node/dialog_model.cpp` | |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| alert_dialog | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/alert_dialog.d.ts` | |
| prompt_action | `<OH_ROOT>/interface/sdk-js/api/@ohos.promptAction.d.ts` | |
| common | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/common.d.ts` | |

### 测试入口

| 稳定路径 | 用途 |
|----------|------|
| test/unittest/core/pattern/dialog/ | |
| test/unittest/core/pattern/overlay/dialog_manager_test_ng.cpp | |
| test/unittest/capi/accessors/alert_dialog_accessor_test.cpp | |
| test/unittest/interfaces/dialog_model_test.cpp | |

### 相关 Spec

| Spec | 路径 | 说明 |
|------|------|------|
| 功能域 | `specs/05-ui-components/06-popup-components/02-alert-dialog/` | AlertDialog 警告弹窗，基于 DialogPattern，支持标题/内容/按钮配置。通过 promptAction 或声明式 API 调用。 |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 弹窗不显示 | 确认 OverlayManager 的 Dialog 创建链路和 DialogPattern 初始化 |
| 按钮点击无响应 | 检查 AlertDialogModelNG 的按钮事件回调注册 |
| 弹窗布局异常 | 查看 DialogLayoutAlgorithm 的布局计算 |

## 调试入口

- 创建链路：AlertDialogModelNG → DialogPattern → OverlayManager
- 布局链路：DialogLayoutAlgorithm → DialogLayoutProperty
- C API 链路：dialog_model.cpp → DialogCommon

## 相关主题

- ActionSheet 列表选择弹窗
- Dialog 弹窗组件
- 弹窗类属性
