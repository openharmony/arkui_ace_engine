# bindPopup Context

> 文档版本：v1.1
> 更新时间：2026-07-23
> 来源：`docs/context_registry.json` 主题 `bindPopup`

## 定位

bindPopup 是 ArkUI 弹窗类属性，通过 `bindPopup(show, popup)` 通用属性方法为任意组件绑定气泡弹窗。bindPopup 的底层渲染基于 `BubblePattern`（气泡模式）和 `PopupBasePattern`（命令式 openPopup 模式）。Bubble Pattern 已完成组件化改造，输出独立 SO `libarkui_bubble.z.so`。bindPopup 不暴露为 `ArkUI_NodeType` 节点类型，C API 通过 `bubble_modifier` 委托层提供属性设置。

本文档用于快速定位 bindPopup 相关源码、SDK 声明、测试和规格文档。具体行为、默认值、边界条件和兼容性说明以对应 SDK 声明、源码实现、测试用例和 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| Bubble Pattern（气泡核心） | `frameworks/core/components_ng/pattern/bubble/bubble_pattern.cpp` | `BubblePattern`，气泡显示/隐藏、位置计算、动画 |
| Bubble 多线程 | `frameworks/core/components_ng/pattern/bubble/bubble_pattern_multi_thread.cpp` | 多线程支持 |
| Bubble 布局算法 | `frameworks/core/components_ng/pattern/bubble/bubble_layout_algorithm.cpp` | `BubbleLayoutAlgorithm`，气泡位置、箭头、避让 |
| Bubble 布局属性 | `frameworks/core/components_ng/pattern/bubble/bubble_layout_property.h` | `BubbleLayoutProperty` |
| Bubble 渲染属性 | `frameworks/core/components_ng/pattern/bubble/bubble_render_property.h` | `BubbleRenderProperty` |
| Bubble 绘制方法 | `frameworks/core/components_ng/pattern/bubble/bubble_paint_method.cpp` | `BubblePaintMethod`，气泡背景、圆角、阴影绘制 |
| Bubble 视图 | `frameworks/core/components_ng/pattern/bubble/bubble_view.cpp` | `BubbleView`，气泡节点创建工厂 |
| Bubble 事件 | `frameworks/core/components_ng/pattern/bubble/bubble_event_hub.h` | `BubbleEventHub` |
| Bubble 无障碍 | `frameworks/core/components_ng/pattern/bubble/bubble_accessibility_property.cpp` | `BubbleAccessibilityProperty` |
| Bubble 主题 | `frameworks/core/components_ng/pattern/bubble/popup_theme_wrapper.h` | Popup Token 适配 |
| Popup Base Pattern（命令式） | `frameworks/core/components_ng/pattern/overlay/popup_base_pattern.cpp` | `PopupBasePattern`，命令式 `openPopup` / `updatePopup` / `closePopup` 基类 |
| Overlay 管理器 | `frameworks/core/components_ng/pattern/overlay/overlay_manager.cpp` | `OverlayManager`，弹窗挂载和 overlay 基础设施 |
| JSView 桥接 | `frameworks/bridge/declarative_frontend/jsview/js_popups.cpp` | `JSViewAbstract::JsBindPopup()`，bindPopup 属性解析入口 |
| View Abstract Model | `frameworks/bridge/declarative_frontend/jsview/models/view_abstract_model_impl.cpp` | `ViewAbstractModelImpl::BindPopup()`，Model 层实现 |
| 组件化 Bridge 目录 | `frameworks/core/components_ng/pattern/bubble/bridge/` | 组件化后的 Bubble 动态模块 Bridge |
| node_modifier 委托层 | `frameworks/core/interfaces/native/node/bubble_modifier.cpp` | Bubble C++ 属性委托层 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic API (属性) | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/common.d.ts` | `bindPopup(show, popup)` 属性声明；`PopupOptions` / `CustomPopupOptions` 类型 |
| Dynamic API (命令式) | `<OH_ROOT>/interface/sdk-js/api/@ohos.arkui.UIContext.d.ts` | `openPopup()` / `updatePopup()` / `closePopup()` 命令式 API |
| CAPI / NDK | 无独立 NODE 枚举 | Bubble 使用 modifier-based C API |

API 检索建议：

- 属性声明：在 `common.d.ts` 中搜索 `bindPopup`、`PopupOptions`、`CustomPopupOptions`、`PopupMaskType`。
- 命令式 API：在 `@ohos.arkui.UIContext.d.ts` 中搜索 `openPopup`、`updatePopup`、`closePopup`。
- C API：在 `frameworks/core/interfaces/native/node/bubble_modifier.cpp` 中搜索属性名。

### API 解析实现路径

Bubble Pattern 已完成组件化改造，`bridge/` 目录存在动态模块入口。bindPopup 属性仍通过通用属性桥接（`js_popups.cpp` → `ViewAbstractModel`）触发。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| JSView（声明式属性） | `frameworks/bridge/declarative_frontend/jsview/js_popups.cpp` | `JsBindPopup()` 解析参数 → `ViewAbstractModel::BindPopup()` |
| Model 实现 | `frameworks/bridge/declarative_frontend/jsview/models/view_abstract_model_impl.cpp` | `ViewAbstractModelImpl::BindPopup()` 事件注册 |
| 统一 Bridge（动态模块） | `frameworks/core/components_ng/pattern/bubble/bridge/bubble_dynamic_module.cpp` | `BubbleDynamicModule` 派生类，`libarkui_bubble.z.so` 入口 |
| Inner Modifier | `frameworks/core/components_ng/pattern/bubble/bridge/inner_modifier/bubble_inner_modifier.cpp` | 内部 modifier 委托 |
| node_modifier 委托层 | `frameworks/core/interfaces/native/node/bubble_modifier.cpp` | 通过 `DynamicModuleHelper` 转发到动态模块 |

独立 SO：`libarkui_bubble.z.so`。

### 外部依赖入口

外部仓路径以 OpenHarmony 根目录为基准；相对路径列仅记录外部仓内的头文件、目录或 GN 目标。

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件 / 目标路径 | 说明 |
|----------|----------|------------|--------------------------------|------|
| 窗口子系统 | `frameworks/core/components_ng/pattern/bubble/bubble_pattern.cpp` | `window_manager` | `interfaces/innerkits/wm/window_manager.h` | 气泡子窗口创建与管理 |
| 图形渲染 | `frameworks/core/components_ng/pattern/bubble/bubble_paint_method.cpp` | `foundation/graphic/graphic_2d` | `rosen/modules/render_service_base/include/` | RSNode / RSCanvas 绘制气泡背景、圆角、阴影、箭头 |
| 无障碍框架 | `frameworks/core/components_ng/pattern/bubble/bubble_accessibility_property.*` | `base/accessibility` | `accessibility:accessibility_common` | 气泡无障碍属性上报和操作响应 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 单元测试 | `test/unittest/core/pattern/bubble/` | Bubble Pattern、布局、绘制、交互等回归测试 |
| Overlay 测试 | `test/unittest/core/pattern/overlay/overlay_manager_popup_test_ng.cpp` | Popup overlay 管理回归 |
| Context registry | `docs/context_registry.json` | bindPopup 的 KB、源码、API、测试统一路由 |

### 相关 Spec

| Spec | 路径 | 说明 |
|------|------|------|
| popup 弹窗功能域 | `specs/05-ui-components/06-popup-components/11-popup/` | bindPopup 规格目录 |
| Feat-01 | `specs/05-ui-components/06-popup-components/11-popup/Feat-01-bind-popup-bubble-layout-spec.md` | bindPopup 属性绑定与气泡布局 |
| Feat-02 | `specs/05-ui-components/06-popup-components/11-popup/Feat-02-imperative-popup-api-spec.md` | 命令式 Popup API (openPopup / updatePopup / closePopup) |
| 架构设计 | `specs/05-ui-components/06-popup-components/11-popup/design.md` | Popup 弹窗架构设计文档 |
| 弹窗类属性功能域 | `specs/04-common-capability/03-common-attributes/05-popup-attributes/` | 通用弹窗属性规格目录（待创建） |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 气泡不显示 | `JsBindPopup()` 参数解析；`ViewAbstractModelImpl::BindPopup()` 事件注册；`OverlayManager` 挂载 |
| 气泡位置/箭头错误 | `BubbleLayoutAlgorithm` 的位置计算和箭头布局 |
| 气泡动画异常 | `BubblePattern` 的显示/隐藏动画 |
| openPopup 不触发 | `PopupBasePattern` 的命令式 API 链路 |
| 无障碍操作无效 | `BubbleAccessibilityProperty` |

## 调试入口

- 属性链路：从 `js_popups.cpp::JsBindPopup()` → `ViewAbstractModelImpl::BindPopup()` → `BubbleView` 节点创建。
- 布局链路：从 `BubbleLayoutAlgorithm::Measure()` / `Layout()` 跟踪气泡位置、箭头、避让。
- 命令式链路：从 `OverlayManager::OpenPopup()` / `ClosePopup()` 跟踪命令式 popup。
- 组件化链路：从 `BubbleDynamicModule` 跟踪动态模块加载。
- 回归验证：优先运行 `test/unittest/core/pattern/bubble/` 下的定向用例。

## 相关主题

- Popup 高级组件（ArkUI 高级气泡组件）
- Menu 组件（菜单组件，同属弹窗类组件）
- Overlay 管理器（Popup / Toast / Dialog 共享的 overlay 基础设施）
- 组件化改造通用方案
