# Dialog Context

> 文档版本：v1.1
> 更新时间：2026-07-23
> 来源：`docs/context_registry.json` 主题 `Dialog`

## 定位

Dialog 是 ArkUI 弹窗类组件，提供自定义弹窗（CustomDialog）、警告弹窗（AlertDialog）、列表选择弹窗（ActionSheet）三种对话框形式。三者共享 `DialogPattern` 基础容器 Pattern，通过各自的 Model 和 Controller 管理生命周期。Dialog 基础 Pattern 已完成组件化改造，输出独立 SO `libarkui_dialog.z.so`；各变体（AlertDialog、ActionSheet、CustomDialogController）仍保留 JSView 桥接入口。Dialog 不暴露为 `ArkUI_NodeType` 节点类型，而是通过独立的 `ArkUI_NativeDialogAPI` C 接口族提供服务。

本文档用于快速定位 Dialog 相关源码、SDK 声明、测试和规格文档。具体行为、默认值、边界条件和兼容性说明以对应 SDK 声明、源码实现、测试用例和 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| Dialog 基础 Pattern | `frameworks/core/components_ng/pattern/dialog/dialog_pattern.cpp` | `DialogPattern`，弹窗容器生命周期、显示/隐藏 |
| Dialog 布局算法 | `frameworks/core/components_ng/pattern/dialog/dialog_layout_algorithm.cpp` | `DialogLayoutAlgorithm`，弹窗尺寸、位置、避让 |
| Dialog 布局属性 | `frameworks/core/components_ng/pattern/dialog/dialog_layout_property.h` | `DialogLayoutProperty` |
| Dialog 事件 | `frameworks/core/components_ng/pattern/dialog/dialog_event_hub.cpp` | `DialogEventHub` |
| Dialog 无障碍 | `frameworks/core/components_ng/pattern/dialog/dialog_accessibility_property.cpp` | `DialogAccessibilityProperty` |
| Dialog 视图 | `frameworks/core/components_ng/pattern/dialog/dialog_view.cpp` | `DialogView`，弹窗节点创建工厂 |
| Dialog 内部管理器 | `frameworks/core/components_ng/pattern/dialog/dialog_inner_manager.cpp` | `DialogInnerManager` |
| Dialog 主题 | `frameworks/core/components_ng/pattern/dialog/dialog_theme_wrapper.h` | Dialog Token 适配 |
| Dialog 多线程 | `frameworks/core/components_ng/pattern/dialog/dialog_pattern_multi_thread.cpp` | 多线程支持 |
| AlertDialog Model | `frameworks/core/components_ng/pattern/dialog/alert_dialog/alert_dialog_model_ng.cpp` | `AlertDialogModelNG` |
| ActionSheet Model | `frameworks/core/components_ng/pattern/dialog/action_sheet/action_sheet_model_ng.cpp` | `ActionSheetModelNG` |
| CustomDialog Model | `frameworks/core/components_ng/pattern/dialog/custom_dialog/custom_dialog_model.cpp` | `CustomDialogModel` |
| CustomDialogController Model | `frameworks/core/components_ng/pattern/dialog/custom_dialog/custom_dialog_controller_model_ng.cpp` | `CustomDialogControllerModelNG`，控制器生命周期管理 |
| CustomDialogController 静态 Model | `frameworks/core/components_ng/pattern/dialog/custom_dialog/custom_dialog_controller_model_static.cpp` | 静态前端属性写入 |
| Dialog 管理器（overlay 层） | `frameworks/core/components_ng/pattern/overlay/dialog_manager.cpp` | `DialogManager`，弹窗全局管理 |
| Dialog 静态管理器 | `frameworks/core/components_ng/pattern/overlay/dialog_manager_static.cpp` | `DialogManagerStatic`，静态弹窗管理入口 |
| Overlay 管理器 | `frameworks/core/components_ng/pattern/overlay/overlay_manager.cpp` | `OverlayManager`，弹窗挂载和 overlay 基础设施 |
| 旧版 CustomDialog 组件 | `frameworks/core/components/custom_dialog/custom_dialog_component.cpp` | `CustomDialogController` 旧版组件层（兼容） |
| 组件化 Bridge 目录 | `frameworks/core/components_ng/pattern/dialog/bridge/` | 组件化后的 Dialog 动态模块 Bridge |
| node_modifier 委托层 | `frameworks/core/interfaces/native/node/dialog_modifier.cpp` | Dialog C++ 属性委托层 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic API (CustomDialog) | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/custom_dialog.d.ts` | 动态 ArkTS `CustomDialogController` 声明 |
| Dynamic API (AlertDialog) | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/alert_dialog.d.ts` | `AlertDialog.show()` API 声明 |
| Dynamic API (ActionSheet) | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/action_sheet.d.ts` | `ActionSheet.show()` API 声明 |
| Dynamic API (promptAction) | `<OH_ROOT>/interface/sdk-js/api/@ohos.promptAction.d.ts` | `showActionMenu` / `openCustomDialog` / `openCustomDialogWithController` / `presentCustomDialog` 命令式 API 声明 |
| Dynamic API (arkui.dialog) | `<OH_ROOT>/interface/sdk-js/api/@ohos.arkui.dialog.d.ts` | `presentDialog` / `presentCustomDialog` / `updateCustomDialog` / `dismissDialog` 命令式 API 声明 |
| NAPI (promptAction) | `interfaces/napi/kits/promptaction/js_prompt_action.cpp` | NAPI 模块注册，`"promptAction"` 模块，`showActionMenu` / `openCustomDialog` / `openCustomDialogWithController` / `presentCustomDialog` 方法 |
| NAPI (arkui.dialog) | `interfaces/napi/kits/dialog/js_dialog.cpp` | NAPI 模块注册，`"arkui.dialog"` 模块，`presentDialog` / `presentCustomDialog` / `updateCustomDialog` / `dismissDialog` 方法 |
| CAPI / NDK | `interfaces/native/native_dialog.h` | `ArkUI_NativeDialogAPI_1/2/3` 独立 C 接口族 |
| CAPI / NDK Model | `interfaces/native/node/dialog_model.cpp` | Dialog 模型 C 接口 |
| CAPI / NDK Option | `interfaces/native/node/dialog_option.cpp` | `OH_ArkUI_CustomDialog_*` 选项接口 |

API 检索建议：

- CustomDialog：在 SDK 文件中搜索 `CustomDialogController`、`@CustomDialog`。
- AlertDialog：搜索 `AlertDialog`、`AlertDialogParamWithConfirm`。
- ActionSheet：搜索 `ActionSheet`、`ActionSheetParam`。
- promptAction 命令式 API：在 `@ohos.promptAction.d.ts` 中搜索 `showActionMenu`、`openCustomDialog`、`openCustomDialogWithController`、`presentCustomDialog`。
- arkui.dialog 命令式 API：在 `@ohos.arkui.dialog.d.ts` 中搜索 `presentDialog`、`presentCustomDialog`、`updateCustomDialog`、`dismissDialog`。
- C API：在 `native_dialog.h` 中搜索 `ArkUI_NativeDialogAPI`、`OH_ArkUI_CustomDialog`。

### NAPI 命令式 API 调用链

#### promptAction NAPI 模块（`interfaces/napi/kits/promptaction/`）

NAPI 模块注册于 `js_prompt_action.cpp`，模块名 `"promptAction"`，通过 `prompt_action.cpp` 实现各方法。

| NAPI 方法 | 实现函数 | 调用链 | 说明 |
|-----------|----------|--------|------|
| `showActionMenu` | `JSPromptShowActionMenu` | `js_prompt_action.cpp` 注册 → `prompt_action.cpp::JSPromptShowActionMenu()` → 解析 `ActionMenuOptions` → `delegate->ShowActionMenu()` | 列表选择弹窗，Promise 返回 index |
| `openCustomDialog` | `JSPromptOpenCustomDialog` | `js_prompt_action.cpp` 注册 → `prompt_action.cpp::JSPromptOpenCustomDialog()` → `JSPromptParseParam()` → `OpenCustomDialog()` → `delegate->OpenCustomDialog()` 或 `SubwindowManager::OpenCustomDialog()` | 命令式自定义弹窗，接受 builder 函数或 ComponentContent |
| `openCustomDialogWithController` | `JSPromptOpenCustomDialogWithController` | `js_prompt_action.cpp` 注册 → `prompt_action.cpp::JSPromptOpenCustomDialogWithController()` → 解析 `nodePtr_` + `PromptDialogController` → `OpenCustomDialog()` → `delegate->OpenCustomDialog()` | 基于节点的自定义弹窗，接受 FrameNode + Controller |
| `presentCustomDialog` | `JSPromptPresentCustomDialog` | `js_prompt_action.cpp` 注册 → `prompt_action.cpp::JSPromptPresentCustomDialog()` → 解析 builder + Controller + `DialogOptions` → `OpenCustomDialog()` → `delegate->OpenCustomDialog()` | 带样式选项的自定义弹窗 |

`OpenCustomDialog()` 是上述三个方法的公共分发函数（`prompt_action.cpp`），根据运行时环境选择 `delegate->OpenCustomDialog()` 或 `SubwindowManager::GetInstance()->OpenCustomDialog()` 路径。

#### arkui.dialog NAPI 模块（`interfaces/napi/kits/dialog/`）

NAPI 模块注册于 `js_dialog.cpp`，模块名 `"arkui.dialog"`，直接调用 `OverlayManager` / `DialogManager` / `SubwindowManager`。

| NAPI 方法 | 实现函数 | 调用链 | 说明 |
|-----------|----------|--------|------|
| `presentDialog` | `JSPresentDialog` | `js_dialog.cpp` → 解析 `DialogParams` → `overlayManager->ShowDialogWithErrorCallback()` 或 `SubwindowManager::ShowDialogNG()` 或 `DialogManager::ShowInEmbeddedOverlay()` | 命令式弹窗显示，支持属性弹窗和遮罩弹窗 |
| `presentCustomDialog` | `JSPresentCustomDialog` | `js_dialog.cpp` → 解析 builder + `DialogOptions` → `SubwindowManager::OpenCustomDialogNG()` 或 `overlayManager->OpenCustomDialogWithErrorCallback()` 或 `DialogManager::ShowInEmbeddedOverlay()` | 命令式自定义弹窗显示 |
| `updateCustomDialog` | `JSUpdateCustomDialog` | `js_dialog.cpp` → `overlayManager->UpdateCustomDialog()` | 命令式弹窗属性更新 |
| `dismissDialog` | `JSDismissDialog` | `js_dialog.cpp` → 解析 `DialogId` / `FrameNode` → `delegate->CloseCustomDialog()` | 命令式弹窗关闭 |

`js_dialog.cpp` 中的方法直接操作 `OverlayManager` 和 `DialogManager`，不经过 delegate 中转（与 `prompt_action.cpp` 不同）。

### API 解析实现路径

Dialog 基础 Pattern 已完成组件化改造，`bridge/` 目录存在动态模块入口。但各变体（AlertDialog、ActionSheet、CustomDialogController）仍保留 JSView 桥接文件。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| JSView（声明式） | `frameworks/bridge/declarative_frontend/jsview/dialog/js_alert_dialog.cpp`、`js_action_sheet.cpp`、`js_custom_dialog_controller.cpp` | AlertDialog / ActionSheet / CustomDialogController 的 JSView 桥接 |
| Model 实现 | `frameworks/bridge/declarative_frontend/jsview/models/alert_dialog_model_impl.cpp`、`custom_dialog_controller_model_impl.cpp` | Model 层实现 |
| 统一 Bridge（动态模块） | `frameworks/core/components_ng/pattern/dialog/bridge/dialog_dynamic_module.cpp` | `DialogDynamicModule` 派生类，`libarkui_dialog.z.so` 入口 |
| Dynamic Modifier | `frameworks/core/components_ng/pattern/dialog/bridge/dialog_dynamic_modifier.cpp` | 动态属性路径 |
| Inner Modifier | `frameworks/core/components_ng/pattern/dialog/bridge/inner_modifier/dialog_inner_modifier.cpp` | 内部 modifier 委托 |
| 静态访问器（AlertDialog） | `frameworks/core/components_ng/pattern/dialog/alert_dialog/bridge/alert_dialog_static_accessor.cpp` | 静态前端 AlertDialog 访问器 |
| 静态访问器（ActionSheet） | `frameworks/core/components_ng/pattern/dialog/action_sheet/bridge/action_sheet_static_accessor.cpp` | 静态前端 ActionSheet 访问器 |
| 静态 Peer（CustomDialogController） | `frameworks/core/components_ng/pattern/dialog/custom_dialog/bridge/custom_dialog_controller_static_peer_impl.cpp` | 静态前端 CustomDialogController Peer |
| 静态 Extender（CustomDialogController） | `frameworks/core/components_ng/pattern/dialog/custom_dialog/bridge/custom_dialog_controller_static_extender_accessor.cpp` | 静态前端 Extender 访问器 |
| 静态 ArkTS 前端 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/component/customDialogController.ets` | 静态 ArkTS CustomDialogController |
| State Management | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/common/custom_dialog_controller.ts` | CustomDialogController 状态管理 |
| node_modifier 委托层 | `frameworks/core/interfaces/native/node/dialog_modifier.cpp` | C++ 属性委托，`GetCustomDialogControllerModel()` |
| C API Extender | `frameworks/core/interfaces/native/implementation/custom_dialog_controller_extender_accessor.cpp` | C API Extender 访问器 |

独立 SO：`libarkui_dialog.z.so`。

SO 包含范围（依据 `frameworks/core/components_ng/pattern/dialog/BUILD.gn`）：SO 包含 Dialog 基础 Pattern（`dialog_pattern.cpp`、`dialog_layout_algorithm.cpp`、`dialog_view.cpp`、`dialog_event_hub.cpp`、`dialog_inner_manager.cpp`、`dialog_accessibility_property.cpp`）、AlertDialog Model（`alert_dialog_model_ng.cpp`）、ActionSheet Model（`action_sheet_model_ng.cpp`）、CustomDialog Model（`custom_dialog_model.cpp`、`custom_dialog_controller_model_ng.cpp`、`custom_dialog_controller_model_static.cpp`）以及动态模块 Bridge（`dialog_dynamic_module.cpp`、`dialog_dynamic_modifier.cpp`、`dialog_inner_modifier.cpp`）。该 SO 对应组件化后的 Dialog Pattern 层及其变体 Model 层，不包含 NAPI 接口（`js_prompt_action.cpp`、`js_dialog.cpp` 在独立 NAPI 模块中编译）和 JSView 桥接（`js_alert_dialog.cpp` 等在 declarative_frontend 中编译）。

### 外部依赖入口

外部仓路径以 OpenHarmony 根目录为基准；相对路径列仅记录外部仓内的头文件、目录或 GN 目标。

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件 / 目标路径 | 说明 |
|----------|----------|------------|--------------------------------|------|
| 窗口子系统 | `frameworks/core/components_ng/pattern/overlay/overlay_manager.cpp` | `window_manager` | `interfaces/innerkits/wm/window_manager.h` | 弹窗子窗口创建与管理 |
| 图形渲染 | `frameworks/core/components_ng/pattern/dialog/dialog_layout_algorithm.cpp` | `foundation/graphic/graphic_2d` | `rosen/modules/render_service_base/include/` | RSNode / RSCanvas 绘制弹窗背景、圆角、阴影 |
| 无障碍框架 | `frameworks/core/components_ng/pattern/dialog/dialog_accessibility_property.*` | `base/accessibility` | `accessibility:accessibility_common` | 弹窗无障碍属性上报和操作响应 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 单元测试 | `test/unittest/core/pattern/dialog/` | Dialog Pattern、布局、Model 回归测试 |
| C API 测试 | `test/unittest/capi/accessors/dialog_extender_accessor_test.cpp` | Dialog Extender C API 回归 |
| C API 测试 | `test/unittest/capi/accessors/custom_dialog_controller_accessor_test.cpp` | CustomDialogController C API 回归 |
| C API 测试 | `test/unittest/capi/accessors/alert_dialog_accessor_test.cpp` | AlertDialog C API 回归 |
| Context registry | `docs/context_registry.json` | Dialog 的 KB、源码、API、测试统一路由 |

### 相关 Spec

| Spec | 路径 | 说明 |
|------|------|------|
| 自定义弹窗功能域 | `specs/05-ui-components/06-popup-components/04-custom-dialog/` | CustomDialog 规格目录 |
| Feat-01 | `specs/05-ui-components/06-popup-components/04-custom-dialog/Feat-01-custom-dialog-lifecycle-layout-spec.md` | CustomDialogController 生命周期与布局属性及命令式弹窗 API |
| Feat-02 | `specs/05-ui-components/06-popup-components/04-custom-dialog/Feat-02-alert-action-sheet-spec.md` | AlertDialog/ActionSheet 命令式 API |
| Feat-03 | `specs/05-ui-components/06-popup-components/04-custom-dialog/Feat-03-dialog-capi-spec.md` | Dialog C API（ArkUI_NativeDialogAPI_1/2/3、OH_ArkUI_CustomDialog 函数族） |
| 架构设计 | `specs/05-ui-components/06-popup-components/04-custom-dialog/design.md` | CustomDialog 架构设计文档 |
| 警告弹窗功能域 | `specs/05-ui-components/06-popup-components/02-alert-dialog/` | AlertDialog 规格目录（待创建） |
| 列表选择弹窗功能域 | `specs/05-ui-components/06-popup-components/03-list-selection-dialog/` | ActionSheet 规格目录（待创建） |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 弹窗不显示 | `DialogManager` / `OverlayManager` 的弹窗挂载逻辑；`CustomDialogControllerModelNG` 的 open/close |
| 弹窗位置/尺寸错误 | `DialogLayoutAlgorithm` 的布局计算；`DialogLayoutProperty` 的约束 |
| CustomDialogController 生命周期异常 | `custom_dialog_controller_model_ng.cpp` 的 open/close/destroy；`DialogInnerManager` |
| AlertDialog 按钮不响应 | `AlertDialogModelNG` 的回调注册；JSView `js_alert_dialog.cpp` 的参数解析 |
| 弹窗动画异常 | `DialogPattern` 的显示/隐藏动画；`OverlayManager` 的转场效果 |
| 无障碍操作无效 | `DialogAccessibilityProperty` |

## 调试入口

- 创建链路：从 `DialogView::Create()` 确认弹窗节点创建和 Pattern 设置；CustomDialog 从 `CustomDialogControllerModelNG::open()` 跟踪。
- 属性链路：从 SDK 属性名定位 JSView → Model → `DialogLayoutProperty` 的属性写入。
- 管理链路：从 `DialogManager` / `OverlayManager::ShowDialog()` 跟踪弹窗挂载和窗口管理。
- 组件化链路：从 `DialogDynamicModule` 跟踪动态模块加载。
- 回归验证：优先运行 `test/unittest/core/pattern/dialog/` 下的定向用例。

## 相关主题

- Menu 组件（菜单组件，同属弹窗类组件）
- Toast 组件（提示组件，同属弹窗类组件，通过 promptAction API 触发）
- bindSheet 组件（半模态弹窗，同属弹窗类组件）
- 组件化改造通用方案
