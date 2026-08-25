# bindSheet Context

> 文档版本：v1.0
> 更新时间：2026-07-14
> 来源：`docs/context_registry.json` 主题 `Sheet`

## 定位

bindSheet 是 ArkUI 半模态弹窗属性，通过 `bindSheet(isShow, builder, options)` 通用属性方法为任意组件绑定半模态面板。Sheet 组件族包含 SheetPresentation（半模态内容）、SheetWrapper（包装器）、SheetDragBar（拖拽条）、SheetMask（遮罩）、SheetObject（状态对象）等。Sheet 已完成组件化改造，输出独立 SO `libarkui_sheet.z.so`，保留 JSView 薄封装入口。bindSheet 不暴露为 `ArkUI_NodeType` 节点类型，C API 通过 `sheet_modifier` 委托层提供属性设置。

本文档用于快速定位 bindSheet 相关源码、SDK 声明、测试和规格文档。具体行为、默认值、边界条件和兼容性说明以对应 SDK 声明、源码实现、测试用例和 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| Sheet Presentation Pattern（核心） | `frameworks/core/components_ng/pattern/sheet/sheet_presentation_pattern.cpp` | `SheetPresentationPattern`，半模态显示/隐藏、拖拽、生命周期管理 |
| Sheet Presentation 布局算法 | `frameworks/core/components_ng/pattern/sheet/sheet_presentation_layout_algorithm.cpp` | `SheetPresentationLayoutAlgorithm` |
| Sheet Presentation 属性 | `frameworks/core/components_ng/pattern/sheet/sheet_presentation_property.h` | `SheetPresentationProperty` |
| Sheet Wrapper Pattern | `frameworks/core/components_ng/pattern/sheet/sheet_wrapper_pattern.cpp` | `SheetWrapperPattern`，半模态包装器 |
| Sheet Wrapper 布局算法 | `frameworks/core/components_ng/pattern/sheet/sheet_wrapper_layout_algorithm.cpp` | `SheetWrapperLayoutAlgorithm` |
| Sheet Wrapper 绘制方法 | `frameworks/core/components_ng/pattern/sheet/sheet_wrapper_paint_method.cpp` | `SheetWrapperPaintMethod` |
| Sheet Wrapper 无障碍 | `frameworks/core/components_ng/pattern/sheet/sheet_wrapper_accessibility_property.cpp` | `SheetWrapperAccessibilityProperty` |
| Sheet 管理器 | `frameworks/core/components_ng/pattern/sheet/sheet_manager.cpp` | `SheetManager`，半模态全局管理 |
| Sheet 状态对象 | `frameworks/core/components_ng/pattern/sheet/sheet_object.cpp` | `SheetObject`，半模态状态管理 |
| Sheet 视图 | `frameworks/core/components_ng/pattern/sheet/sheet_view.cpp` | `SheetView`，节点创建工厂 |
| Sheet 样式 | `frameworks/core/components_ng/pattern/sheet/sheet_style.h` | `SheetStyle` 样式定义 |
| Sheet 主题 | `frameworks/core/components_ng/pattern/sheet/sheet_theme_wrapper.h` | Sheet Token 适配 |
| Sheet 拖拽条 Pattern | `frameworks/core/components_ng/pattern/sheet/sheet_drag_bar_pattern.cpp` | `SheetDragBarPattern` |
| Sheet 拖拽条绘制 | `frameworks/core/components_ng/pattern/sheet/sheet_drag_bar_paint_method.cpp` | `SheetDragBarPaintMethod` |
| Sheet 遮罩 Pattern | `frameworks/core/components_ng/pattern/sheet/sheet_mask_pattern.h` | `SheetMaskPattern` |
| Sheet 遮罩无障碍 | `frameworks/core/components_ng/pattern/sheet/sheet_mask_accessibility_property.cpp` | `SheetMaskAccessibilityProperty` |
| Sheet 边缘光效 | `frameworks/core/components_ng/pattern/sheet/sheet_edge_light.cpp` | `SheetEdgeLight` |
| Sheet Content Cover | `frameworks/core/components_ng/pattern/sheet/content_cover/sheet_content_cover_object.cpp` | `SheetContentCoverObject`，全屏覆盖模式 |
| Sheet Content Cover 布局 | `frameworks/core/components_ng/pattern/sheet/content_cover/sheet_content_cover_layout_algorithm.cpp` | Content Cover 布局 |
| Sheet Minimize Object | `frameworks/core/components_ng/pattern/sheet/minimize/sheet_minimize_object.cpp` | `SheetMinimizeObject`，最小化模式 |
| Sheet Minimize 布局 | `frameworks/core/components_ng/pattern/sheet/minimize/sheet_presentation_minimize_layout_algorithm.cpp` | Minimize 布局 |
| Sheet Side Object | `frameworks/core/components_ng/pattern/sheet/side/sheet_side_object.cpp` | `SheetSideObject`，侧边模式 |
| Sheet Side 布局 | `frameworks/core/components_ng/pattern/sheet/side/sheet_presentation_side_layout_algorithm.cpp` | Side 布局 |
| 组件化 Bridge 目录 | `frameworks/core/components_ng/pattern/sheet/bridge/` | 组件化后的 Sheet 动态模块 Bridge |
| node_modifier 委托层 | `frameworks/core/interfaces/native/node/sheet_modifier.cpp` | Sheet C++ 属性委托层 |
| Overlay 管理器 | `frameworks/core/components_ng/pattern/overlay/overlay_manager.cpp` | `OverlayManager`，半模态挂载和 overlay 基础设施 |
| Overlay 模态 Pattern | `frameworks/core/components_ng/pattern/overlay/modal_presentation_pattern.cpp` | `ModalPresentationPattern`，模态基础 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic API (属性) | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/common.d.ts` | `bindSheet(isShow, builder, options)` 属性声明；`SheetOptions`、`SheetType`、`SheetMode` 等类型 |
| Dynamic API (UIContext) | `<OH_ROOT>/interface/sdk-js/api/@ohos.arkui.UIContext.d.ts` | `showSheet()` 命令式 API |
| CAPI / NDK | 无独立 NODE 枚举 | Sheet 使用 modifier-based C API |

API 检索建议：

- 属性声明：在 `common.d.ts` 中搜索 `bindSheet`、`SheetOptions`、`SheetType`、`SheetMode`、`SheetSize`、`SheetDismiss`、`DismissSheetAction`。
- 命令式 API：在 `@ohos.arkui.UIContext.d.ts` 中搜索 `showSheet`。
- C API：在 `frameworks/core/interfaces/native/node/sheet_modifier.cpp` 中搜索属性名。

### API 解析实现路径

Sheet 已完成组件化改造，`bridge/` 目录存在动态模块入口。JSView 文件保留为薄封装。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| JSView（声明式属性） | `frameworks/bridge/declarative_frontend/jsview/js_sheet.cpp` | bindSheet 属性解析入口（薄封装） |
| 统一 Bridge（动态模块） | `frameworks/core/components_ng/pattern/sheet/bridge/sheet_dynamic_module.cpp` | `SheetDynamicModule` 派生类，`libarkui_sheet.z.so` 入口 |
| Sheet Manager Inner Modifier | `frameworks/core/components_ng/pattern/sheet/bridge/sheet_manager_inner_modifier.cpp` | SheetManager 内部 modifier 委托 |
| Sheet Pattern Inner Modifier | `frameworks/core/components_ng/pattern/sheet/bridge/sheet_pattern_inner_modifier.cpp` | SheetPattern 内部 modifier 委托 |
| Sheet View Inner Modifier | `frameworks/core/components_ng/pattern/sheet/bridge/sheet_view_inner_modifier.cpp` | SheetView 内部 modifier 委托 |
| Sheet Wrapper Inner Modifier | `frameworks/core/components_ng/pattern/sheet/bridge/sheet_wrapper_inner_modifier.cpp` | SheetWrapper 内部 modifier 委托 |
| node_modifier 委托层 | `frameworks/core/interfaces/native/node/sheet_modifier.cpp` | 通过 `DynamicModuleHelper` 转发到动态模块 |
| C API 工具 | `frameworks/core/interfaces/native/implementation/bind_sheet_utils.h` | `BindSheetUtil` 工具类、`SheetCallbacks` 结构 |
| C API Peer | `frameworks/core/interfaces/native/implementation/dismiss_sheet_action_peer.h` | `DismissSheetAction` Peer 实现 |

独立 SO：`libarkui_sheet.z.so`。

### 外部依赖入口

外部仓路径以 OpenHarmony 根目录为基准；相对路径列仅记录外部仓内的头文件、目录或 GN 目标。

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件 / 目标路径 | 说明 |
|----------|----------|------------|--------------------------------|------|
| 窗口子系统 | `frameworks/core/components_ng/pattern/sheet/sheet_presentation_pattern.cpp` | `window_manager` | `interfaces/innerkits/wm/window_manager.h` | 半模态子窗口创建与管理、最小化窗口 |
| 图形渲染 | `frameworks/core/components_ng/pattern/sheet/sheet_wrapper_paint_method.cpp` | `foundation/graphic/graphic_2d` | `rosen/modules/render_service_base/include/` | RSNode / RSCanvas 绘制半模态背景、圆角、阴影 |
| 无障碍框架 | `frameworks/core/components_ng/pattern/sheet/sheet_wrapper_accessibility_property.*` | `base/accessibility` | `accessibility:accessibility_common` | 半模态无障碍属性上报和操作响应 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 单元测试 | `test/unittest/core/pattern/overlay/sheet_presentation_test_ng.cpp` | SheetPresentation Pattern 回归（含 8 个分文件） |
| 单元测试 | `test/unittest/core/pattern/overlay/sheet_wrapper_layout_test_ng.cpp` | SheetWrapper 布局回归 |
| 单元测试 | `test/unittest/core/pattern/overlay/sheet_wrapper_paint_test_ng.cpp` | SheetWrapper 绘制回归 |
| 单元测试 | `test/unittest/core/pattern/overlay/sheet_drag_bar_test_ng.cpp` | SheetDragBar 回归 |
| 单元测试 | `test/unittest/core/pattern/overlay/sheet_content_cover_test_ng.cpp` | Content Cover 回归 |
| 单元测试 | `test/unittest/core/pattern/overlay/sheet_minimize_test_ng.cpp` | Minimize 回归 |
| 单元测试 | `test/unittest/core/pattern/overlay/sheet_side_object_test_ng.cpp` | Side Object 回归 |
| 单元测试 | `test/unittest/core/pattern/overlay/sheet_showInSubwindow_test_ng.cpp` | 子窗口模式回归 |
| 单元测试 | `test/unittest/core/pattern/overlay/sheet_others_test_ng.cpp` | 其他场景回归 |
| Context registry | `docs/context_registry.json` | Sheet 的 KB、源码、API、测试统一路由 |

### 相关 Spec

| Spec | 路径 | 说明 |
|------|------|------|
| 半模态弹窗功能域 | `specs/05-ui-components/07-modal-components/01-sheet-modal/` | bindSheet 规格目录（待创建） |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 半模态不显示 | `SheetPresentationPattern` 的显示逻辑；`OverlayManager` 挂载；`SheetManager` 生命周期 |
| 拖拽异常 | `SheetPresentationPattern` 的拖拽处理；`SheetDragBarPattern` 的交互 |
| 半模态位置/尺寸错误 | `SheetPresentationLayoutAlgorithm` 的布局计算；`SheetStyle` 的尺寸配置 |
| 最小化不生效 | `SheetMinimizeObject` 的最小化管理；`sheet_presentation_minimize_layout_algorithm.cpp` |
| 侧边模式异常 | `SheetSideObject` 的侧边管理；`sheet_presentation_side_layout_algorithm.cpp` |
| Content Cover 不显示 | `SheetContentCoverObject` 的全屏覆盖管理 |
| 关闭回调不触发 | `SheetObject` 的 dismiss 逻辑；`DismissSheetAction` 的回调链 |
| 无障碍操作无效 | `SheetWrapperAccessibilityProperty`、`SheetMaskAccessibilityProperty` |

## 调试入口

- 创建链路：从 `SheetView::Create()` 确认半模态节点创建和 Pattern 设置。
- 属性链路：从 SDK 属性名定位 JSView → Model → `SheetPresentationProperty` / `SheetStyle` 的属性写入。
- 拖拽链路：从 `SheetPresentationPattern` 的拖拽事件跟踪手势处理和高度变化。
- 管理链路：从 `SheetManager` / `OverlayManager` 跟踪半模态挂载和窗口管理。
- 组件化链路：从 `SheetDynamicModule` 跟踪动态模块加载和属性注册。
- 回归验证：优先运行 `test/unittest/core/pattern/overlay/` 下 sheet 相关的定向用例。

## 相关主题

- Dialog 组件（自定义弹窗，同属弹窗类组件）
- Menu 组件（菜单组件，同属弹窗类组件）
- Overlay 管理器（Sheet / Toast / Dialog / Popup 共享的 overlay 基础设施）
- 组件化改造通用方案
