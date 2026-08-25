# ActionSheet Context

> 文档版本：v1.0
> 更新时间：2026-07-28
> 来源：`docs/context_registry.json` 主题 `ActionSheet`

## 定位

ArkUI ActionSheet 提供列表选择弹窗交互，基于 DialogPattern 实现。支持 title/message/confirm/cancel/selects 配置。可通过声明式 `ActionSheet.show()` 或 `@ohos.promptAction.showActionMenu()` 调用。

本文档用于快速定位 ActionSheet 相关源码、SDK 声明、测试和规格文档。具体行为、默认值、边界条件和兼容性说明以对应 SDK 声明、源码实现、测试用例和 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| action_sheet_model | `frameworks/core/components_ng/pattern/dialog/action_sheet/action_sheet_model.h` | |
| action_sheet_model_ng | `frameworks/core/components_ng/pattern/dialog/action_sheet/action_sheet_model_ng.cpp` | |
| base_dialog_pattern | `frameworks/core/components_ng/pattern/dialog/dialog_pattern.cpp` | |
| dialog_layout_algorithm | `frameworks/core/components_ng/pattern/dialog/dialog_layout_algorithm.cpp` | |
| overlay_dialog_manager | `frameworks/core/components_ng/pattern/overlay/dialog_manager.cpp` | |
| overlay_manager | `frameworks/core/components_ng/pattern/overlay/overlay_manager.cpp` | |
| js_action_sheet | `frameworks/bridge/declarative_frontend/jsview/dialog/js_action_sheet.cpp` | |
| napi_prompt_action | `interfaces/napi/kits/promptaction/js_prompt_action.cpp` | |
| node_dialog_model | `interfaces/native/node/dialog_model.cpp` | |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| action_sheet | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/action_sheet.d.ts` | |
| prompt_action | `<OH_ROOT>/interface/sdk-js/api/@ohos.promptAction.d.ts` | |
| common | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/common.d.ts` | |

### 测试入口

| 稳定路径 | 用途 |
|----------|------|
| test/unittest/core/pattern/dialog/ | |
| test/unittest/core/pattern/overlay/dialog_manager_test_ng.cpp | |
| test/unittest/capi/accessors/action_sheet_accessor_test.cpp | |

### API 解析实现路径

ActionSheet 基于 DialogPattern 实现，通过 ActionSheetModelNG 创建。不涉及独立 JSView/Bridge 路径。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| 声明式前端 | `frameworks/bridge/declarative_frontend/jsview/dialog/js_action_sheet.cpp` | JS ActionSheet 组件 |
| Model | `frameworks/core/components_ng/pattern/dialog/action_sheet/action_sheet_model_ng.cpp` | ActionSheetModelNG |
| C API | `interfaces/native/node/dialog_model.cpp` | Dialog C API 模型 |

### 相关 Spec

| Spec | 路径 | 说明 |
|------|------|------|
| 功能域 | `specs/05-ui-components/06-popup-components/03-list-selection-dialog/` | ActionSheet 列表选择弹窗，基于 DialogPattern，支持标题/内容/选择项/按钮配置。 |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 选择项点击无响应 | 检查 ActionSheetModelNG 的 select 事件回调 |
| 弹窗不显示 | 确认 OverlayManager 的 Dialog 创建链路 |

## 调试入口

- 创建链路：ActionSheetModelNG → DialogPattern → OverlayManager
- C API 链路：dialog_model.cpp → DialogCommon

## 相关主题

- AlertDialog 警告弹窗
- Dialog 弹窗组件
- ContextMenu 接口
