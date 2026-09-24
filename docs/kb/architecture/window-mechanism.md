# Window Mechanism Context

> 文档版本：v1.1
> 更新时间：2026-07-23
> 来源：`docs/context_registry.json` 主题 `WindowMechanism`

## 定位

Window Mechanism 是 ArkUI 引擎与 OHOS 窗口系统（Rosen WindowManager）之间的连接和适配架构，覆盖窗口创建/销毁、生命周期事件传递、安全区/避让区、键盘避让、子窗口（对话框/菜单/Toast/Sheet）、拖拽预览浮窗、窗口焦点/激活状态、视口配置和折叠屏适配等全部交互。它不是独立的应用侧组件或公共 API，而是引擎内部从 OS 窗口到渲染管线的桥接层。

本文档只提供稳定的源码、SDK、测试和 Spec 路由。具体事件传递细节、默认值和边界条件应回到当前源码、测试与相关 Spec 核实。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| UIContent 公共接口 | `interfaces/inner_api/ace/ui_content.h` | 每个 UIAbility/ExtensionAbility 创建 `UIContent` 实例的入口；定义 `Initialize`、`Foreground`、`Background`、`Destroy`、`UpdateViewportConfig`、`GetRemoteObj` 等全部生命周期方法 |
| UIContent OHOS 实现 | `adapter/ohos/entrance/ui_content_impl.h`、`adapter/ohos/entrance/ui_content_impl.cpp` | 持有 `Rosen::Window*` 和全部 Rosen listener；`CommonInitialize` 创建 AceContainer 并注册窗口事件监听 |
| UIContent 预览实现 | `adapter/preview/entrance/ui_content_impl.h`、`adapter/preview/entrance/ui_content_impl.cpp` | IDE/预览器变体；用模拟 surface 替代 Rosen Window |
| 视口配置 | `interfaces/inner_api/ace/viewport_config.h` | `ViewportConfig` 数据结构：宽高、密度、方向、displayId 等 |
| OHOS 视口适配 | `adapter/ohos/entrance/ace_viewport_config.h` | 扩展 `ViewportConfig` 添加 `WindowSizeChangeReason` 和 `RSTransaction` |
| AceContainer OHOS | `adapter/ohos/entrance/ace_container.h`、`adapter/ohos/entrance/ace_container.cpp` | 每个实例的容器；持有 `sptr<Rosen::Window> uiWindow_`；静态生命周期方法 `OnShow/OnHide/OnActive/OnInactive` |
| Container 抽象 | `frameworks/core/common/container.h` | 虚接口：`GetWindowId`、`IsMainWindow/IsSubWindow/IsDialogWindow/IsSystemWindow`、窗口类型查询 |
| AceView 抽象 | `frameworks/core/common/ace_view.h` | 平台视图抽象；注册 ViewChange、DensityChange、SystemBarHeightChange 等回调 |
| 引擎内部 Window | `frameworks/core/common/window.h`、`frameworks/core/common/window.cpp` | 内部窗口抽象；`OnShow/OnHide`、vsync 调度、subwindow ID 管理 |
| PlatformWindow 抽象 | `frameworks/core/common/platform_window.h` | 最小平台抽象：`RequestFrame`、`RegisterVsyncCallback`、`SetRootRenderNode` |
| AceAbility (FA 模型) | `adapter/ohos/entrance/ace_ability.h`、`adapter/ohos/entrance/ace_ability.cpp` | 旧 FA 模型入口；`AceWindowListener` 实现多个 Rosen listener 接口 |
| 无窗口容器 | `frameworks/core/common/window_free_container.h` | 不依赖 Rosen Window 的容器工厂；用于 headless/测试场景 |
| 窗口工具 | `adapter/ohos/osal/window_utils.h`、`adapter/ohos/osal/window_utils.cpp` | Rosen orientation → Ace `DeviceOrientation` 转换 |

### 子窗口系统

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| Subwindow 抽象 | `frameworks/base/subwindow/subwindow.h` | 子窗口接口；`SubwindowType` enum（Toast/Menu/Popup/Dialog/Sheet/SelectMenu/Tips）；`ShowMenuNG/ShowPopupNG/ShowDialogNG/ShowToast/ShowBindSheetNG` |
| Subwindow OHOS 实现 | `adapter/ohos/entrance/subwindow/subwindow_ohos.h`、`adapter/ohos/entrance/subwindow/subwindow_ohos.cpp` | 持有 `sptr<Rosen::Window>` 和子容器；创建 Rosen 子窗口 |
| Subwindow 静态变体 | `adapter/ohos/entrance/subwindow/subwindow_ohos_static.cpp` | ArkTS 1.2（static）子窗口操作变体 |
| SubwindowManager | `frameworks/base/subwindow/subwindow_manager.h`、`frameworks/base/subwindow/subwindow_manager.cpp` | 单例注册表；按 instanceId/displayId/foldStatus/windowType/nodeId 映射 Subwindow 实例 |

### 拖拽浮窗

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| DragWindow 抽象 | `frameworks/base/window/drag_window.h` | 拖拽预览浮窗接口；`CreateDragWindow`、`MoveTo`、`DrawPixelMap/DrawFrameNode/DrawImage/DrawTextNG` |
| DragWindow OHOS | `adapter/ohos/entrance/window/drag_window_ohos.h`、`adapter/ohos/entrance/window/drag_window_ohos.cpp` | 创建 Rosen 浮动子窗口；持有 `RSUIDirector` 渲染拖拽内容 |

### 折叠屏适配

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| FoldableWindow 抽象 | `frameworks/base/window/foldable_window.h` | 折叠屏查询接口；`IsFoldExpand` |
| FoldableWindow OHOS | `adapter/ohos/entrance/window/foldable_window_ohos.h`、`adapter/ohos/entrance/window/foldable_window_ohos.cpp` | 检查 `Rosen::DisplayManager::GetFoldStatus` |

### WindowExtension

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| NG 适配器 | `frameworks/core/common/window_ng/window_extension_connection_adapter_ng.h` | NG WindowExtension 连接抽象基类 |
| NG OHOS 实现 | `adapter/ohos/capability/window_connection_ng/window_extension_connection_ohos_ng.h`、`adapter/ohos/capability/window_connection_ng/window_extension_connection_ohos_ng.cpp` | NG 实现；`ConnectExtension`、`UpdateRect`、`Show/Hide/RemoveExtension` |
| Legacy 适配器 | `frameworks/core/common/window/window_extension_connection_adapter.h` | 旧版 WindowExtension 连接抽象基类 |
| Legacy OHOS 实现 | `adapter/ohos/capability/window_connection/window_extension_connection_ohos.h`、`adapter/ohos/capability/window_connection/window_extension_connection_ohos.cpp` | 旧版实现 |

### Pipeline 窗口集成

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| PipelineContext 窗口方法 | `frameworks/core/pipeline_ng/pipeline_context.h`、`frameworks/core/pipeline_ng/pipeline_context.cpp` | `OnShow/OnHide`、`WindowFocus/WindowActivate`、`OnWindowSizeChanged`、`OnSurfaceDensityChanged`、`UpdateSystemSafeArea/UpdateCutoutSafeArea/UpdateNavSafeArea`、`OnKeyboardAvoidOverlay`、`CheckAndUpdateKeyboardInset`；注册 `WindowStateChangedCallback`、`WindowFocusChangedCallback`、`WindowActivateChangedCallback`、`WindowSizeChangeCallback` |
| PipelineBase 窗口虚接口 | `frameworks/core/pipeline/pipeline_base.h` | 虚方法声明：`OnShow/OnHide`、`WindowFocus/WindowActivate`、`OnSurfaceDensityChanged`、安全区更新等 |

### 安全区与键盘避让

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| SafeAreaManager | `frameworks/core/components_ng/manager/safe_area/safe_area_manager.h`、`frameworks/core/components_ng/manager/safe_area/safe_area_manager.cpp` | 管理所有避让区 inset：`systemSafeArea_`、`cutoutSafeArea_`、`navSafeArea_`、`keyboardInset_`；`KeyBoardAvoidMode`（NONE/OFFSET/RESIZE） |
| SafeAreaInsets | `frameworks/core/components_ng/property/safe_area_insets.h`、`frameworks/core/components_ng/property/safe_area_insets.cpp` | 每边 inset 数据结构 |
| AvoidInfoManager | `frameworks/core/components_ng/manager/avoid_info/avoid_info_manager.h`、`frameworks/core/components_ng/manager/avoid_info/avoid_info_manager.cpp` | ContainerModal 避让信息管理；`IAvoidInfoListener` |
| DisplayInfo | `frameworks/core/common/display_info.h` | 显示元数据：宽高、旋转、foldable、`WindowStatus` enum |
| DisplayInfoUtils | `frameworks/core/common/display_info_utils.h` | 平台抽象：查询默认 display、fold status 等 |
| WindowSizeBreakpoint | `frameworks/core/common/window_size_breakpoint.h` | 响应式断点：`WidthBreakpoint`（XS/SM/MD/LG/XL/XXL）、`HeightBreakpoint`（SM/MD/LG） |

### 外部依赖入口

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件 / 目标路径 | 说明 |
|----------|----------|------------|--------------------------------|------|
| WindowManager (Rosen) | `adapter/ohos/entrance/ui_content_impl.cpp` | `foundation/window/window_manager` | `wm/include/window.h`、`wm/include/window_option.h` | Rosen Window 创建、listener 注册、GetUIContentRemoteObj |
| WindowManager (Rosen) | `adapter/ohos/entrance/subwindow/subwindow_ohos.cpp` | `foundation/window/window_manager` | `wm/include/window.h` | 子窗口创建（app sub-window、system float、toast 类型） |
| WindowManager (Rosen) | `adapter/ohos/entrance/window/drag_window_ohos.cpp` | `foundation/window/window_manager` | `wm/include/window.h` | 拖拽浮窗创建 |
| RenderService (Rosen) | `adapter/ohos/entrance/ace_container.cpp` | `foundation/graphic/graphic_2d` | `rosen/modules/render_service_client/core/` | AceView → RSRootNode、vsync |
| RenderService (Rosen) | `adapter/ohos/entrance/window/drag_window_ohos.cpp` | `foundation/graphic/graphic_2d` | `rosen/modules/render_service_client/core/` | DragWindow RSUIDirector |
| DisplayManager (Rosen) | `adapter/ohos/osal/display_info_utils.cpp` | `foundation/graphic/graphic_2d` | `rosen/modules/display_manager/` | 默认 display 查询、fold status |
| DisplayManager (Rosen) | `adapter/ohos/entrance/window/foldable_window_ohos.cpp` | `foundation/graphic/graphic_2d` | `rosen/modules/display_manager/` | Fold expand 查询 |

### API 入口

Window Mechanism 是引擎内部架构，没有独立 SDK API。应用侧通过 Ability 框架间接使用 UIContent 的生命周期方法；安全区和键盘避让的公共 API 从下列 SDK 声明进入：

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic 公共属性 | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/common.d.ts` | `expandSafeArea`、`ignoreLayoutSafeArea` 等安全区属性 |
| Static 公共属性 | `<OH_ROOT>/interface/sdk-js/api/arkui/component/common.static.d.ets` | 静态 ArkTS 安全区属性声明 |
| Dynamic Common Modifier | `<OH_ROOT>/interface/sdk-js/api/arkui/CommonModifier.d.ts` | 动态 Modifier 安全区属性 |
| Static Common Modifier | `<OH_ROOT>/interface/sdk-js/api/arkui/CommonModifier.static.d.ets` | 静态 Modifier 安全区属性 |
| C API | `interfaces/native/native_node.h` | C API window-scene 和通用安全区枚举 |

公共安全区属性从前端到 `SafeAreaManager` 的解析路径属于"安全区域机制"主题（`docs/kb/capabilities/safe-area.md`）。

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| UIContent 单元测试 | `test/unittest/interfaces/ui_content_test.cpp` | UIContent 创建、GetUIContent、GetUIContentWindowID |
| UIContent TDD | `test/unittest/interfaces/ui_content_tdd_test.cpp` | Host TDD：UIContent 静态方法 |
| SubwindowManager 单元测试 | `test/unittest/base/subwindow_manager_test.cpp` | SubwindowManager：ShowPreviewNG/HidePreviewNG/CloseDialog 等 |
| AceContainer 适配测试 | `test/unittest/adapter/ohos/entrance/container_test.cpp` | OHOS AceContainer 初始化、auto-fill、窗口类型查询 |
| ContainerScope 测试 | `test/unittest/frameworks/core/common/container_scope_test.cpp` | ContainerScope scope push/pop、instance ID 切换 |
| SafeAreaManager 单元测试 | `test/unittest/core/manager/safe_area_manager_test_ng.cpp`、`test/unittest/core/manager/safe_area_manager_test_ng_part_two.cpp` | 安全区 inset、keyboard safe area、expand/ignore safe area |
| 安全区布局测试 | `test/unittest/core/layout/safe_area/` | expand_safe_area、ignore_layout_safe_area 属性回归 |
| WindowScene pattern 测试 | `test/unittest/core/pattern/window_scene/` | WindowScene pattern、SceneSession 生命周期 |
| ContainerModal 测试 | `test/unittest/core/pattern/container_modal/` | ContainerModal pattern：标题栏、toolbar、close button |
| 焦点窗口测试 | `test/unittest/core/event/focus_core/focus_window_test.cpp` | WindowFocusCase、焦点遍历、ContainerModal 焦点交互 |
| Rosen/PlatformWindow 测试 | `test/unittest/core/common/rosen/rosen_test.cpp` | RosenWindow 生命周期、vsync callback |
| DragWindow 测试 | `test/unittest/core/manager/drag_drop_manager_test_ng*.cpp` | CreateDragWindow、DestroyDragWindow、DrawPixelMap/DrawFrameNode |
| Sheet 子窗口测试 | `test/unittest/core/pattern/overlay/sheet_showInSubwindow_test_ng.cpp`、`test/unittest/core/pattern/overlay/sheet_showInSubwindow_test_one_ng.cpp` | Sheet 在子窗口中的生命周期 |
| WindowScene C API 测试 | `test/unittest/capi/modifiers/windowscene_modifier_test.cpp` | C API WindowScene modifier：setAttractionEffect、setWindowSceneOptions |
| UI 输入事件窗口坐标 | `test/unittest/interfaces/ace_ui_input_event/oh_arkui_uiinputevent_getwindowx_test.cpp`、`test/unittest/interfaces/ace_ui_input_event/oh_arkui_uiinputevent_getwindowy_test.cpp` | C API 窗口坐标获取 |

### 相关 Spec

窗口机制功能域：`specs/03-engine-framework/05-window-mechanism/01-window-mechanism/`（功能 ID `03-05-01`）。

Spec 仓库不在本仓工作区；需要单独克隆到 `./specs` 后验证目录是否存在。当前 `spec_status` 为 `pending`。

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 窗口生命周期事件不触发 | UIContentImpl listener 注册、AceContainer `InitWindowCallback`、PipelineContext `OnShow/OnHide` |
| 安全区/避让区 inset 异常 | `UIContentImpl::UpdateViewportConfig` → PipelineContext `UpdateSystemSafeArea/CutoutSafeArea/NavSafeArea` → SafeAreaManager |
| 键盘避让行为异常 | PipelineContext `CheckAndUpdateKeyboardInset` → `OnKeyboardAvoidOverlay` → SafeAreaManager `KeyBoardAvoidMode` |
| 子窗口（Dialog/Menu/Toast）不显示 | SubwindowManager `GetOrCreateSubWindow` → SubwindowOhos `InitContainer` → Rosen 子窗口创建 |
| 拖拽预览浮窗不创建 | DragWindowOhos `CreateDragWindow` → Rosen 浮动子窗口 → RSUIDirector |
| 窗口焦点不生效 | PipelineContext `WindowFocus` → FocusManager `WindowFocus` → FrameNode `OnWindowFocused/OnWindowUnfocused` |
| 视口尺寸/密度不更新 | UIContentImpl `UpdateViewportConfig` → AceViewportConfig → PipelineContext `OnWindowSizeChanged/OnSurfaceDensityChanged` |
| 折叠屏适配异常 | FoldableWindowOhos `IsFoldExpand` → Rosen DisplayManager `GetFoldStatus` → PipelineContext fold status callback |
| ContainerModal 避让信息异常 | AvoidInfoManager → `IAvoidInfoListener` → UIExtension 避让回调 |
| WindowExtension 嵌入异常 | WindowExtensionConnectionAdapterOhosNG `ConnectExtension` → Rosen WindowExtensionConnection |

## 调试入口

- 窗口生命周期断点：`UIContentImpl::CommonInitialize`（listener 注册）、`UIContentImpl::Foreground/Background`（生命周期转发）、`AceContainer::OnShow/OnHide/OnActive/OnInactive`（静态方法分发）
- 安全区断点：`UIContentImpl` avoidArea listener、`PipelineContext::UpdateSystemSafeArea/CutoutSafeArea/NavSafeArea`、`SafeAreaManager::UpdateKeyboardSafeArea`
- 视口更新断点：`UIContentImpl::UpdateViewportConfig`、`PipelineContext::OnWindowSizeChanged`
- 子窗口断点：`SubwindowOhos::InitContainer`、`SubwindowManager::GetOrCreateSubWindow`
- 拖拽浮窗断点：`DragWindowOhos::CreateDragWindow`、`DragWindowOhos::MoveTo`
- 焦点断点：`PipelineContext::WindowFocus`、`FocusManager::WindowFocus`
- Pipeline dump：`PipelineContext` dump 参数 `-contentChange` 查看 `ContentChangeManager::DumpInfo`
- 窗口类型查询：`Container::IsMainWindow/IsSubWindow/IsDialogWindow/IsSystemWindow`

## 相关主题

- [安全区域机制](../capabilities/safe-area.md)
- [布局框架](layout-framework.md)
- [预览器平台适配](preview-platform-adaptation.md)
- [基础布局属性](../capabilities/layout-attributes.md)
- [UISession（UI 会话通道）](uisession-service.md)
- Pipeline：见 [布局框架](layout-framework.md) 与 [基础渲染管线](basic-render-pipeline.md)