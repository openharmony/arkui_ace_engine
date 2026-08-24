# Window Toolbar Context

> 文档版本：v1.0
> 更新时间：2026-07-28
> 来源：`docs/context_registry.json` 主题 `WindowToolbar`

## 定位

窗口工具栏是 ArkUI 系统窗口容器（ContainerModal）顶部的标题栏 + 工具栏项（ToolBarItem）能力，由窗口框架注入而非应用声明。核心是 `ContainerModalPattern`（NG）/`ContainerModalStaticPattern`（静态）+ `ContainerModalToolBar` 排版管理器 + `ToolBarItemPattern`，经 `@ohos.window.titlebar.component` 静态组件（TitleBar/ButtonBar）对外暴露，并在 `adapter/ohos` 的 `UIContentImpl` 提供标题可见性/高度/按钮区域、自定义手势等平台接口。

本文档只提供稳定的源码、SDK、测试和 Spec 路由。具体标题栏样式、按钮布局、手势语义以源码、SDK 声明和测试为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| 工具栏排版管理器 | `frameworks/core/components_ng/pattern/container_modal/container_modal_toolbar.cpp` | `ContainerModalToolBar`：`InitToolBarManager`，把 ToolBarItem 按 placement 放入 SideBar/NavBar/NavDest 行 |
| 工具栏排版声明 | `frameworks/core/components_ng/pattern/container_modal/container_modal_toolbar.h` | `ContainerModalToolBar : public AceType` |
| 容器 Pattern（NG） | `frameworks/core/components_ng/pattern/container_modal/container_modal_pattern.cpp` | `ContainerModalPattern`：标题高度/可见、按钮 |
| 容器 Pattern 声明 | `frameworks/core/components_ng/pattern/container_modal/container_modal_pattern.h` | — |
| 容器视图 | `frameworks/core/components_ng/pattern/container_modal/container_modal_view.h` | 标题栏/按钮构建 |
| 增强变体（手势/按钮样式） | `frameworks/core/components_ng/pattern/container_modal/enhance/container_modal_view_enhance.h` | `GetContainerModalTitleVisible`、`SetContainerButtonStyle`、`OnContainerModalEvent` |
| 增强变体实现 | `frameworks/core/components_ng/pattern/container_modal/enhance/container_modal_pattern_enhance.cpp` | 自定义手势、按钮样式 |
| 静态变体（ArkTS 1.2） | `frameworks/core/components_ng/pattern/container_modal/static/container_modal_static_pattern.cpp` | `ContainerModalStaticPattern` |
| 静态变体视图/桥 | `frameworks/core/components_ng/pattern/container_modal/static/container_modal_static_view.cpp` | 静态容器视图 |
| 容器无障碍 | `frameworks/core/components_ng/pattern/container_modal/container_modal_accessibility_property.h` | 容器无障碍属性 |
| 容器工具 | `frameworks/core/components_ng/pattern/container_modal/container_modal_utils.h` | 容器辅助 |
| ToolBarItem Pattern | `frameworks/core/components_ng/pattern/toolbaritem/toolbaritem_pattern.h` | `TOOLBARITEM_ETS_TAG="ToolBarItem"`；placement `TOP_BAR_LEADING/TRAILING` |
| ToolBarItem Model | `frameworks/core/components_ng/pattern/toolbaritem/toolbaritem_model_ng.h` | 动态创建入口 |
| ToolbarManager | `frameworks/core/components_ng/manager/toolbar/toolbar_manager.h` | 被 ContainerModal 与 Navigation 共用的 toolbar 管理器 |
| 静态组件源 | `frameworks/core/components_ng/pattern/container_modal/static/source/@ohos.window.titlebar.component.defalut.ets` | `@ohos.window.titlebar.component` 默认 ets（TitleBar/ButtonBar 入口） |
| 静态组件构建 | `frameworks/core/components_ng/pattern/container_modal/static/source/BUILD.gn` | `generate_static_abc("window_titlebar_component_abc")` |
| DynamicModule 映射 | `adapter/ohos/osal/dynamic_module_helper.cpp` | `{ "ToolBarItem", "toolbaritem" }` 动态加载映射 |
| 平台入口 | `adapter/ohos/entrance/ui_content_impl.cpp` | `SetContainerModalTitleVisible/Height`、`GetContainerModalButtonsRect`、`EnableContainerModalGesture`/`CustomGesture`、`OnContainerModalEvent` |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Static ArkTS 组件 | `<OH_ROOT>/interface/sdk-js/api/@ohos.window.titlebar.component.d.ts` | `@ohos.window.titlebar.component`（TitleBar/ButtonBar），路径以 SDK 仓实际为准 |
| 静态组件仓内源 | `frameworks/core/components_ng/pattern/container_modal/static/source/@ohos.window.titlebar.component.defalut.ets` | 仓内默认 ets 源（含 custombutton/customtitle） |
| 反射类名（Arkoala） | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/XBarProxy.ts` | `@ohos.window.titlebar.component.System__Reserved_$$$__UI__TitleBar__Component` / `...ButtonBar__Component` |
| Inner API / UIContent | `adapter/ohos/entrance/ui_content_impl.h` | `SetContainerModalTitleVisible/Height`、`SubscribeContainerModalButtonsRectChange` 等 |
| C API / NDK | 无 | 不作为应用级 Node 组件暴露；为窗口框架注入的系统 chrome |

### 外部依赖入口

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件/目标路径 | 说明 |
|----------|----------|------------|----------------------------|------|
| 窗口管理器 | `adapter/ohos/entrance/ui_content_impl.cpp`（`SetContainerModalTitleVisible`、`OnContainerModalEvent`）、`adapter/ohos/osal/app_bar_helper_impl.cpp` | `<OH_ROOT>/foundation/window/window_manager` | `interfaces/innerkits/wm/`、`window_manager:libwm` | `ContainerModal` 标题栏可见性回调与事件派发 |
| 基础工具库 | `container_modal_toolbar.cpp`、`toolbaritem_pattern.cpp` | `<OH_ROOT>/foundation/systemabilitymgr/samgr` | `c_utils:utils` | 工具函数 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 工具栏单测 | `test/unittest/core/pattern/container_modal/container_modal_toolbar_test_ng.cpp` | `ContainerModalToolBar` 排版 |
| 工具栏基础/项/placement/行/节点/高度/样式/布局/焦点/添加/管理器 | `test/unittest/core/pattern/container_modal/` | 该目录下 `container_modal_toolbar_*_test_ng.cpp` 系列覆盖各维度 |
| 容器 Pattern 测试 | `test/unittest/core/pattern/container_modal/container_modal_test_ng.cpp` | `ContainerModalPattern` 行为 |
| 增强变体测试 | `test/unittest/core/pattern/container_modal/container_modal_pattern_enhance_test_ng.cpp` | 自定义手势、按钮样式 |
| 静态变体测试 | `test/unittest/core/pattern/container_modal/container_modal_static_pattern_test.cpp` | `ContainerModalStaticPattern` |

### 相关 Spec

窗口工具栏功能域：`specs/04-common-capability/08-root-view/01-window-toolbar/`（功能 ID `04-08-01`，当前 spec_status `pending`：已在 registry 注册，但目录与 Feat 规格尚未创建）。

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 工具栏项不显示/位置错 | `ContainerModalToolBar::InitToolBarManager`、ToolBarItem placement（`TOP_BAR_LEADING/TRAILING`）、ToolbarManager 分发 |
| 标题栏可见性/高度不生效 | `UIContentImpl::SetContainerModalTitleVisible/Height`、`ContainerModalPattern` 标题字段 |
| 自定义手势不响应 | `EnableContainerModalCustomGesture`、`container_modal_pattern_enhance.cpp` 手势分支 |
| 按钮区域回调缺失 | `SubscribeContainerModalButtonsRectChange`、`GetContainerModalButtonsRect` |
| ToolBarItem 动态加载失败 | `dynamic_module_helper.cpp` 的 `{ "ToolBarItem", "toolbaritem" }` 映射、组件 so |
| 静态组件不构建 | `generate_static_abc("window_titlebar_component_abc")` 产物、`@ohos.window.titlebar.component.defalut.ets` |
| 容器事件不派发 | `OnContainerModalEvent`（ui_content_impl.cpp）、`ContainerModalViewEnhance::OnContainerModalEvent` |

## 调试入口

- 排版链路断点：`ContainerModalToolBar::InitToolBarManager` → ToolBarItem placement 装填
- 平台链路断点：`UIContentImpl::SetContainerModalTitleVisible/Height`、`OnContainerModalEvent`
- 静态组件链路断点：`@ohos.window.titlebar.component.defalut.ets` TitleBar/ButtonBar 构建 + `window_titlebar_component_abc`
- 手势链路断点：`container_modal_pattern_enhance.cpp` 自定义手势处理

## 相关主题

- [窗口机制（ContainerModal pattern 与窗口框架）](../architecture/window-mechanism.md)
- [元服务 AppBar（同属 08-root-view）](atomic-service-appbar.md)
- [UI 上下文（容器相关访问器）](ui-context.md)