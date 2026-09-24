# Atomic Service AppBar Context

> 文档版本：v1.0
> 更新时间：2026-07-28
> 来源：`docs/context_registry.json` 主题 `AtomicServiceAppBar`

## 定位

元服务 AppBar 是 ArkUI 为免安装元服务（atomic service / installation-free）注入的顶部菜单栏 chrome，结构为 `AtomicService(Column) > JsView > Stage + MenuBarRow > MenuBar(menuButton/divider/closeButton)`。核心是 `AppBarView`（构建工厂）+ `AtomicServicePattern`（LinearLayoutPattern 派生）+ `AtomicServiceLayoutAlgorithm`，由 `pipeline->GetInstallationFree()` 触发自动构建；对外经 NAPI 模块 `atomicservicebar`、C-API `OH_ArkUI_NativeModule_AtomicServiceMenuBarSetVisible`、`UIContext.getAtomicServiceBar()` 暴露 setVisible/backgroundColor/title/icon/rect 等能力。

本文档只提供稳定的源码、SDK、测试和 Spec 路由。具体菜单/关闭语义、避让与安全区行为以源码、SDK 声明和测试为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| AppBarView 构建 | `frameworks/core/components_ng/pattern/app_bar/app_bar_view.cpp` | `BuildAppbar`、`RegistAppBarNodeBuilder`、`OnMenuClick`、`OnCloseClick`、`GetAppBarRect`、`SetMenuBarVisible` |
| AppBarView 声明 | `frameworks/core/components_ng/pattern/app_bar/app_bar_view.h` | `AppBarView : public Referenced`（树结构注释 32-43） |
| AtomicServicePattern | `frameworks/core/components_ng/pattern/app_bar/atomic_service_pattern.cpp` | 颜色/布局更新、rect-change 监听、安全区回调、`SetIsAtomicService(true)`、返回按压 |
| AtomicServicePattern 声明 | `frameworks/core/components_ng/pattern/app_bar/atomic_service_pattern.h` | `AtomicServicePattern : LinearLayoutPattern` |
| 布局算法 | `frameworks/core/components_ng/pattern/app_bar/atomic_service_layout_algorithm.cpp` | `AtomicServiceLayoutAlgorithm`：避让/overlay 布局 |
| 布局算法声明 | `frameworks/core/components_ng/pattern/app_bar/atomic_service_layout_algorithm.h` | — |
| AppBar 主题 | `frameworks/core/components_ng/pattern/app_bar/app_bar_theme.h` | `AppBarTheme` |
| AppBar 工具 | `frameworks/core/components_ng/pattern/app_bar/app_bar_utils.cpp` | AppBar 辅助 |
| 自定义 AppBar 节点 | `frameworks/core/components_ng/pattern/custom/custom_app_bar_node.h` | `CustomAppBarNode : CustomNode`（`ARKUI_APP_BAR_*`/`ARKUI_MENU_BAR_VISIBLE`/`ARKUI_ABILITY_CLOSE_EVENT` 回调） |
| 自定义 AppBar ets | `frameworks/core/components_ng/pattern/app_bar/source/custom_app_bar.ets` | 自定义 app-bar ArkTS 源 |
| AppBarHelper | `frameworks/core/common/app_bar_helper.h` | `QueryAppGalleryBundleName()`（平台查询） |
| NAPI 模块（atomicservicebar） | `interfaces/napi/kits/atomic_service_bar/js_atomic_service_bar.cpp` | `setVisible`/`setBackgroundColor`/`setTitleContent`/`setTitleFontStyle`/`setIconColor`/`getBarRect`/`onBarRectChange` |
| C-API modifier | `frameworks/core/interfaces/native/node/atomic_service_modifier.h` | `GetAtomicServiceModifier`；`.setMenuBarVisible`，`pipeline->GetInstallationFree()` 守卫 |
| C-API 实现 | `interfaces/native/node/node_utils.cpp` | `OH_ArkUI_NativeModule_AtomicServiceMenuBarSetVisible` |
| C-API accessor | `frameworks/core/interfaces/native/implementation/ui_context_atomic_service_bar_accessor.cpp` | `UIContextAtomicServiceBarAccessor`（`getBarRect` 等） |
| 声明式 JS 绑定 | `frameworks/bridge/declarative_frontend/jsview/js_app_bar_view.cpp` | `JSAppBar`（"ContainerAppBar"）事件：OnMenuClick/OnCloseClick/OnBackPressed/OnDidBuild 等 |
| 平台 helper 实现 | `adapter/ohos/osal/app_bar_helper_impl.cpp` | `AppBarHelper::QueryAppGalleryBundleName` OHOS 实现 |
| Container plumbing | `frameworks/core/common/container.h` | `Container::GetAppBar()`/`SetAppBar(...)` |
| 触发构建 | `frameworks/bridge/declarative_frontend/frontend_delegate_declarative.cpp` | `NG::AppBarView::BuildAppbar(...)` |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic SDK d.ts | `<OH_ROOT>/interface/sdk-js/api/@ohos.arkui.UIContext.d.ts` | `UIContext.getAtomicServiceBar()` 返回 `AtomicServiceBar`（路径以 SDK 仓实际为准） |
| NAPI 模块 | `interfaces/napi/kits/atomic_service_bar/js_atomic_service_bar.cpp` | 模块名 `atomicservicebar` |
| C API / NDK | `interfaces/native/native_node.h` | `OH_ArkUI_NativeModule_AtomicServiceMenuBarSetVisible` |
| NDK 符号 | `interfaces/native/libace.ndk.json` | 注册符号 |
| ANI ArkTS 接口 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/@ohos.arkui.UIContext.ts` | `interface AtomicServiceBar`、`getAtomicServiceBar()` |
| ANI 静态实现 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/base/UIContextImpl.ets` | `AtomicServiceBarInternal implements AtomicServiceBar` |
| IDL | `frameworks/bridge/arkts_frontend/arkoala_generator/arkui_extra_idl/arkui-custom.idl` | `interface UIContextAtomicServiceBar` |
| Dynamic JS shim | `frameworks/bridge/declarative_frontend/engine/jsUIContext.js` | `getAtomicServiceBar()` 动态 shim、`AtomicServiceBar` 类 |

### 外部依赖入口

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件/目标路径 | 说明 |
|----------|----------|------------|----------------------------|------|
| 元服务包信息查询 | `adapter/ohos/osal/app_bar_helper_impl.cpp`（`AppBarHelper::QueryAppGalleryBundleName`） | `<OH_ROOT>/foundation/arkui/appexecfwk_standard` | `interfaces/inner_api/appexecfwk_core/bundlemgr/bundle_mgr_interface.h` | 经 `SystemAbilityManager` 取 `BUNDLE_MGR_SERVICE_SYS_ABILITY_ID`，`iface_cast<IBundleMgr>` 后调用 `QueryAppGalleryBundleName` 查询 AppGallery 包名（IPC） |
| 系统服务寻址 | `adapter/ohos/osal/app_bar_helper_impl.cpp` | `<OH_ROOT>/foundation/systemabilitymgr/samgr` | `iservice_registry.h`、`system_ability_definition.h` | `SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager()` 获取系统能力管理器 |

> 外部仓路径以 OpenHarmony 实际仓名为准；ace_engine 仓内仅持有调用点，头文件通过 `bundle_mgr_interface.h` 等 include 引入。

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| AppBar 单测 | `test/unittest/core/pattern/app_bar/app_bar_test_ng.cpp` | `BuildAppbar`、`AppBarTestNg` |
| 布局算法单测 | `test/unittest/core/pattern/app_bar/app_bar_layout_algorithm_test.cpp` | `AtomicServiceLayoutAlgorithm001-003`、overlay、`GetAtomicServicePattern` |
| Pattern 更新单测 | `test/unittest/core/pattern/app_bar/atomic_service_pattern_update_test.cpp` | `AppBarView::BuildAppbar`、颜色回调 |
| C-API accessor 测试 | `test/unittest/capi/accessors/ui_context_atomic_service_bar_accessor_test.cpp` | `UIContextAtomicServiceBarAccessor`（`getBarRect`） |
| Mock | `test/mock/frameworks/core/components_ng/pattern/mock_app_bar_view.cpp` | `AppBarView` 桩 |

### 相关 Spec

元服务 AppBar 功能域：`specs/04-common-capability/08-root-view/02-atomic-service-appbar/`（功能 ID `04-08-02`，当前 spec_status `pending`：已在 registry 注册，但目录与 Feat 规格尚未创建）。

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| AppBar 不出现 | `pipeline->GetInstallationFree()` 守卫（`atomic_service_modifier.cpp`）、`AppBarView::BuildAppbar` 触发条件 |
| 菜单按钮 setVisible 无效 | `OH_ArkUI_NativeModule_AtomicServiceMenuBarSetVisible`、`atomic_service_modifier` 的 setMenuBarVisible、InstallationFree 判定 |
| 安全区/避让异常 | `AtomicServiceLayoutAlgorithm` overlay 布局、`AtomicServicePattern` 安全区回调、`SetIsAtomicService(true)` |
| 颜色/标题不更新 | `AtomicServicePattern::AppBgColorCallBack`、`atomicservicebar` setBackgroundColor/setTitleContent |
| rect 回调不触发 | `AppBarView` rect-change listener、`onBarRectChange`、`getBarRect` accessor |
| 自定义 AppBar 内容不显示 | `CustomAppBarNode::CreateCustomNode`、`ARKUI_APP_BAR_*` 回调名、`RegistAppBarNodeBuilder` |
| 元服务关闭流程 | `OnCloseClick`/`RequestAtomicServiceTerminate`/`FireAbilityCloseEvent`、`ARKUI_ABILITY_CLOSE_EVENT` |

## 调试入口

- 构建链路断点：`AppBarView::BuildAppbar`（app_bar_view.cpp）→ MenuBar 组装
- Pattern 链路断点：`AtomicServicePattern::BeforeCreateLayoutWrapper`、安全区/颜色回调
- 布局链路断点：`AtomicServiceLayoutAlgorithm` 避让/overlay
- C-API 链路断点：`OH_ArkUI_NativeModule_AtomicServiceMenuBarSetVisible`（node_utils.cpp）→ `GetAtomicServiceModifier`
- accessor 链路断点：`UIContextAtomicServiceBarAccessor`（getBarRect）

## 相关主题

- [窗口工具栏（同属 08-root-view）](window-toolbar.md)
- [窗口机制（ContainerModal/窗口框架）](../architecture/window-mechanism.md)
- [UI 上下文](ui-context.md)（`UIContext.getAtomicServiceBar()` 入口）