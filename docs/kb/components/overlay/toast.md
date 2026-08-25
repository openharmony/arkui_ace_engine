# Toast Context

> 文档版本：v1.1
> 更新时间：2026-07-23
> 来源：`docs/context_registry.json` 主题 `Toast`

## 定位

Toast 是 ArkUI 提示类组件，通过 `promptAction.showToast()` 命令式 API 显示简短消息提示。Toast 不是声明式组件，没有 JSView/Bridge 层，也没有独立 C API 接口。Toast 的底层渲染基于 `ToastPattern`，由 `OverlayManager::ShowToast()` 统一创建和管理。Toast 未进行组件化改造（无 `bridge/` 子目录、无动态模块注册），属于 overlay 基础设施的一部分。

本文档用于快速定位 Toast 相关源码、SDK 声明、测试和规格文档。具体行为、默认值、边界条件和兼容性说明以对应 SDK 声明、源码实现、测试用例和 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| Toast Pattern | `frameworks/core/components_ng/pattern/toast/toast_pattern.cpp` | `ToastPattern`，Toast 显示/隐藏逻辑 |
| Toast 多线程 | `frameworks/core/components_ng/pattern/toast/toast_pattern_multithread.cpp` | 多线程支持 |
| Toast 布局算法 | `frameworks/core/components_ng/pattern/toast/toast_layout_algorithm.cpp` | `ToastLayoutAlgorithm` |
| Toast 布局属性 | `frameworks/core/components_ng/pattern/toast/toast_layout_property.h` | `ToastLayoutProperty`、`ToastInfo` 数据结构 |
| Toast 视图 | `frameworks/core/components_ng/pattern/toast/toast_view.cpp` | `ToastView`，Toast 节点创建工厂 |
| Toast 无障碍 | `frameworks/core/components_ng/pattern/toast/toast_accessibility_property.cpp` | `ToastAccessibilityProperty` |
| Overlay 管理器（Toast 核心） | `frameworks/core/components_ng/pattern/overlay/overlay_manager.cpp` | `OverlayManager::ShowToast()` / `CloseToast()` / `OpenToastAnimation()` / `PopToast()`，`toastMap_` 管理 |
| 静态管理器 | `frameworks/core/components_ng/pattern/overlay/dialog_manager_static.cpp` | `DialogManagerStatic::ShowToastStatic()` / `CloseToastStatic()`，静态入口分发 |
| Dialog 管理器 | `frameworks/core/components_ng/pattern/overlay/dialog_manager.cpp` | `DialogManager`，overlay 层弹窗管理 |
| NAPI 实现 | `interfaces/napi/kits/promptaction/prompt_action.cpp` | `JSPromptShowToast()` / `ShowToast()`，NAPI 入口 |
| NAPI 注册 | `interfaces/napi/kits/promptaction/js_prompt_action.cpp` | NAPI 模块注册，`"showToast"` → `JSPromptShowToast` |
| NAPI JS 封装 | `interfaces/napi/kits/promptaction/promptaction.js` | JS 层 `showToast(options)` 封装 |
| Prompt Controller | `interfaces/napi/kits/promptaction/prompt_controller.cpp` | `PromptController` |
| 旧版 NAPI 入口 | `interfaces/napi/kits/prompt/js_prompt.cpp` | 旧版 prompt NAPI |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic API | `<OH_ROOT>/interface/sdk-js/api/@ohos.promptAction.d.ts` | `showToast()` API 声明 |
| Dynamic API (UIContext) | `<OH_ROOT>/interface/sdk-js/api/@ohos.arkui.UIContext.d.ts` | `getPromptAction().showToast()` 实例化 API |
| NAPI JS | `interfaces/napi/kits/promptaction/promptaction.js` | JS 层 showToast 封装 |
| CAPI / NDK | 无 | Toast 无独立 C API 接口 |

API 检索建议：

- API 声明：在 SDK 文件中搜索 `showToast`、`ShowToastOptions`。
- NAPI 入口：在 `prompt_action.cpp` 中搜索 `JSPromptShowToast`。
- 调用链路：`promptaction.js` → `js_prompt_action.cpp` → `prompt_action.cpp::ShowToast()` → `OverlayManager::ShowToast()`。

### API 解析实现路径

Toast **尚未组件化**——不是声明式组件，没有 JSView/Bridge/Modifier 路径，编译产物在主 `libace_compatible.z.so` 中。Toast 通过 NAPI 命令式 API 触发，经 `OverlayManager` 创建和管理节点。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| NAPI 模块 | `interfaces/napi/kits/promptaction/js_prompt_action.cpp` | NAPI 模块注册，`"promptAction"` 模块，`"showToast"` 方法 |
| NAPI 实现 | `interfaces/napi/kits/promptaction/prompt_action.cpp` | `JSPromptShowToast()` 解析参数 → `ShowToast()` 分发 |
| Overlay 入口 | `frameworks/core/components_ng/pattern/overlay/dialog_manager_static.cpp` | `DialogManagerStatic::ShowToastStatic()` 静态入口 |
| Overlay 核心 | `frameworks/core/components_ng/pattern/overlay/overlay_manager.cpp` | `OverlayManager::ShowToast()` 创建 Toast 节点并管理 |
| Toast 节点 | `frameworks/core/components_ng/pattern/toast/toast_view.cpp` | `ToastView::CreateToastNode()` 创建 Toast FrameNode |

注：Toast 无组件化改造，无独立 SO，不属于动态模块列表。

### 外部依赖入口

外部仓路径以 OpenHarmony 根目录为基准；相对路径列仅记录外部仓内的头文件、目录或 GN 目标。

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件 / 目标路径 | 说明 |
|----------|----------|------------|--------------------------------|------|
| 窗口子系统 | `frameworks/core/components_ng/pattern/overlay/overlay_manager.cpp` | `window_manager` | `interfaces/innerkits/wm/window_manager.h` | Toast 子窗口创建与管理（跨窗口场景） |
| 图形渲染 | `frameworks/core/components_ng/pattern/toast/toast_pattern.cpp` | `foundation/graphic/graphic_2d` | `rosen/modules/render_service_base/include/` | RSNode / RSCanvas 绘制 Toast 背景、圆角 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 单元测试 | `test/unittest/core/pattern/overlay/overlay_manager_toast_test_ng.cpp` | Toast 显示/隐藏、动画、overlay 管理回归 |
| Context registry | `docs/context_registry.json` | Toast 的 KB、源码、API、测试统一路由 |

### 相关 Spec

| Spec | 路径 | 说明 |
|------|------|------|
| promptAction 接口功能域 | `specs/05-ui-components/06-popup-components/10-prompt-action/` | promptAction 规格目录 |
| Feat-01 | `specs/05-ui-components/06-popup-components/10-prompt-action/Feat-01-prompt-action-full-spec.md` | Toast/promptAction 全量规格 |
| 架构设计 | `specs/05-ui-components/06-popup-components/10-prompt-action/design.md` | promptAction 架构设计文档 |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| Toast 不显示 | `OverlayManager::ShowToast()` 的节点创建和挂载；`prompt_action.cpp::ShowToast()` 的参数解析 |
| Toast 位置错误 | `ToastLayoutAlgorithm` 的布局计算 |
| Toast 不消失 | `OverlayManager::CloseToast()` / `PopToast()` 的定时器管理 |
| Toast 动画异常 | `OverlayManager::OpenToastAnimation()` 的动画配置 |
| Toast 多实例冲突 | `OverlayManager` 的 `toastMap_` 管理 |
| 子窗口 Toast 不生效 | `prompt_action.cpp::ShowToast()` 中 `delegate->ShowToast()` vs `SubwindowManager` 的分发逻辑 |

## 调试入口

- 调用链路：从 `promptaction.js::showToast()` → `js_prompt_action.cpp::JSPromptShowToast` → `prompt_action.cpp::ShowToast()` → `OverlayManager::ShowToast()`。
- 节点创建：从 `ToastView::CreateToastNode()` 确认 Toast FrameNode 创建。
- 动画链路：从 `OverlayManager::OpenToastAnimation()` 跟踪显示动画。
- 回归验证：运行 `test/unittest/core/pattern/overlay/overlay_manager_toast_test_ng.cpp`。

## 相关主题

- [Dialog 组件（对话框组件，同属弹窗类组件）](dialog.md)
- [bindPopup 组件（气泡弹窗，同属弹窗类组件）](bind-popup.md)
- Overlay 管理器（Toast / Dialog / Popup 共享的 overlay 基础设施）