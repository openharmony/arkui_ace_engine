# Navigation Context

> 文档版本：v1.0
> 更新时间：2026-07-08
> 来源：`docs/context_registry.json` 主题 `Navigation`

## 定位

Navigation 是 ArkUI 的导航容器组件，面向应用侧提供页面路由栈管理、NavDestination 推入/退出、转场动画、标题栏/工具栏配置、安全区避让、分栏/强制分屏等能力。Navigation 与 NavDestination、NavRouter 构成 ArkUI 导航体系的核心组件族。

本文档用于快速定位 Navigation 相关源码、SDK 声明、测试和规格文档。具体行为、默认值、边界条件和兼容性说明以对应 SDK 声明、源码实现、测试用例和 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| Pattern 生命周期、路由栈、转场、分栏 | `frameworks/core/components_ng/pattern/navigation/navigation_pattern.cpp` | Navigation 核心行为实现入口 |
| Pattern 类型和扩展接口 | `frameworks/core/components_ng/pattern/navigation/navigation_pattern.h` | `NavigationPattern` 类型声明 |
| ArkTS Dynamic Model | `frameworks/core/components_ng/pattern/navigation/navigation_model_ng.cpp` | 动态前端 Navigation 创建和属性写入 |
| ArkTS Static Model | `frameworks/core/components_ng/pattern/navigation/navigation_model_static.cpp` | 静态前端 Navigation 属性写入 |
| 布局属性 | `frameworks/core/components_ng/pattern/navigation/navigation_layout_property.h` | Navigation 布局属性声明 |
| 布局算法 | `frameworks/core/components_ng/pattern/navigation/navigation_layout_algorithm.cpp` | Navigation 布局计算逻辑 |
| 事件存储 | `frameworks/core/components_ng/pattern/navigation/navigation_event_hub.h` | Navigation 事件回调 |
| 路由栈 | `frameworks/core/components_ng/pattern/navigation/navigation_stack.cpp` | NavigationStack 实现 |
| 路由信息 | `frameworks/core/components_ng/pattern/navigation/navigation_route.h` | 路由信息声明 |
| NavDestination Pattern | `frameworks/core/components_ng/pattern/navrouter/navdestination_pattern.cpp` | NavDestination 核心行为 |
| NavRouter Pattern | `frameworks/core/components_ng/pattern/navrouter/navrouter_pattern.cpp` | NavRouter 核心行为 |
| Navigator Pattern | `frameworks/core/components_ng/pattern/navigator/navigator_pattern.cpp` | Navigator 核心行为 |
| NavBar Pattern | `frameworks/core/components_ng/pattern/navigation/nav_bar_pattern.cpp` | NavBar 核心行为 |
| TitleBar Pattern | `frameworks/core/components_ng/pattern/navigation/title_bar_pattern.cpp` | TitleBar 核心行为 |
| Toolbar Pattern | `frameworks/core/components_ng/pattern/navigation/tool_bar_pattern.cpp` | Toolbar 核心行为 |
| Navigation 声明 | `frameworks/core/components_ng/pattern/navigation/navigation_declaration.h` | Navigation 属性和配置声明 |
| Navigation 选项 | `frameworks/core/components_ng/pattern/navigation/navigation_options.h` | Navigation 选项配置 |
| 多线程 Pattern 扩展 | `frameworks/core/components_ng/pattern/navigation/navigation_pattern_multi_thread.cpp` | 多线程场景 Pattern 实现 |
| 主题 | `frameworks/core/components_ng/pattern/navigation/navigation_bar_theme_wrapper.h` | Navigation 主题包装 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/navigation.d.ts` | 动态 ArkTS Navigation 接口声明 |
| Static API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/navigation.static.d.ets` | 静态 ArkTS Navigation 组件声明 |
| Modifier API (Dynamic) | `<OH_ROOT>/interface/sdk-js/api/arkui/NavigationModifier.d.ts` | 动态 Modifier 声明 |
| Modifier API (Static) | `<OH_ROOT>/interface/sdk-js/api/arkui/NavigationModifier.static.d.ets` | 静态 Modifier 声明 |
| CAPI / NDK | 无 | Navigation 当前无独立 C API 节点类型 |

API 检索建议：

- 属性声明：在 SDK 文件中搜索 `NavigationAttribute` 和具体属性名。
- 构造参数：在 SDK 文件中搜索 `NavigationInterface` 或 `Navigation(`。
- Modifier：在 `NavigationModifier*.d.ts` 中确认继承或实现关系。

### API 解析实现路径

Navigation 当前未完成组件化改造（无 `bridge/` 子目录、JSView 文件仍存在）。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| JSView（声明式组件） | `frameworks/bridge/declarative_frontend/jsview/js_navigation.cpp` | `JSNavigation::SetXxx()` → `NavigationModel::GetInstance()->SetXxx()` |
| JSView（NavDestination） | `frameworks/bridge/declarative_frontend/jsview/js_navdestination.cpp` | `JSNavDestination::SetXxx()` → `NavDestinationModel::GetInstance()->SetXxx()` |
| JSView（NavigationStack） | `frameworks/bridge/declarative_frontend/jsview/js_navigation_stack.cpp` | NavigationStack JS 侧桥接 |
| JSView（NavigationUtils） | `frameworks/bridge/declarative_frontend/jsview/js_navigation_utils.cpp` | NavigationUtils JS 侧桥接 |
| ArkTS Bridge（动态属性） | `frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_navigation_bridge.cpp` | Bridge → ModelNG |
| ArkTS Bridge（NavRouter） | `frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_nav_router_bridge.cpp` | NavRouter Bridge → ModelNG |
| ArkTS Bridge（NavigationUtils） | `frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_navigation_utils.cpp` | NavigationUtils Bridge |
| 前端 Modifier（ArkTS 侧） | `frameworks/bridge/declarative_frontend/ark_modifier/src/navigation_modifier.ts` | ArkTS Navigation Modifier 类 |

组件化改造参考：改造后 JSView 和 Bridge 双路径将统一到 `pattern/navigation/bridge/`，并输出独立 so。

### 外部依赖入口

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件 / 目标路径 | 说明 |
|----------|----------|-----------|-------------------------------|------|
| UI 会话管理 | `interfaces/inner_api/ui_session/ui_session_manager.h` | — | — | UI 会话信息上报 |
| 输入法管理 | `core/common/ime/input_method_manager.h` | — | — | 输入法显示/隐藏联动 |
| 窗口场景 | `core/components_ng/pattern/window_scene/helper/window_scene_helper.h` | — | — | 窗口场景辅助 |
| UIContent 配置 | `interfaces/inner_api/ace/ui_content_config.h` | — | — | UIContent 配置接口 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| Navigation Pattern 单元测试 | `test/unittest/core/pattern/navigation/` | Navigation、NavBar、TitleBar、Toolbar、BarItem、NavDestination 等 Pattern 测试 |
| NavRouter 单元测试 | `test/unittest/core/pattern/navrouter/` | NavRouter、NavDestination Pattern 测试 |
| Navigator 单元测试 | `test/unittest/core/pattern/navigator/` | Navigator Pattern 测试 |

### 相关 Spec

| ID | 主题 | Spec 路径 | 状态 |
|----|------|-----------|------|
| 05-02-01 | Navigation | `specs/05-ui-components/02-navigation-components/01-navigation/` | active |

Design 文档：`specs/05-ui-components/02-navigation-components/01-navigation/design.md`

| Feat-ID | 标题 | 覆盖范围 | 状态 |
|---------|------|----------|------|
| Feat-01 | 创建与布局模式 | NavigationInterface, mode, navBarWidth, navBarPosition, navBarWidthRange, minContentWidth, hideNavBar, ignoreLayoutSafeArea, enableModeChangeAnimation, configuration | Baselined |
| Feat-02 | 标题栏配置 | title, subTitle, titleMode, hideTitleBar, hideBackButton, backButtonIcon, menus, NavigationTitleOptions | Baselined |
| Feat-03 | 工具栏配置 | toolbarConfiguration, hideToolBar, enableToolBarAdaptation, ToolbarItem | Baselined |
| Feat-04 | 路由栈管理 | NavPathStack 全量方法, NavPathInfo, LaunchMode, NavigationOptions | Baselined |
| Feat-05 | 转场动画与自定义过渡 | customNavContentTransition, NavigationAnimatedTransition, NavigationTransitionProxy | Baselined |
| Feat-06 | 系统栏/安全区/分栏/恢复 | systemBarStyle, BarStyle, divider, enableDragBar, splitPlaceholder, recoverable | Baselined |
| Feat-07 | 事件回调与Modifier | onTitleModeChange, onNavBarStateChange, onNavigationModeChange, NavigationModifier | Baselined |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 路由栈 push/pop 行为异常 | `navigation_pattern.cpp` 中的 `OnPush`/`OnPop` 流程，`navigation_stack.cpp` |
| 转场动画不生效或闪屏 | `navigation_pattern.cpp` 中转场动画创建逻辑，`navigation_transition_proxy.h` |
| NavDestination 生命周期回调缺失 | `navdestination_pattern.cpp` 中 `OnAttachToFrameNode`/`OnDetachFromFrameNode` |
| 标题栏/工具栏布局异常 | `title_bar_layout_algorithm.cpp`、`tool_bar_layout_algorithm.cpp` |
| NavBar 显示/隐藏异常 | `nav_bar_pattern.cpp` 中 NavBar 状态管理 |
| 安全区避让异常 | `navigation_pattern.cpp` 中避让信息处理，`avoid_info_manager.h` |
| 分栏/强制分屏行为异常 | `force_split_manager.h`、`force_split_utils.h` |
| 导航返回键行为 | `navigation_pattern.cpp` 中返回拦截逻辑 |

## 调试入口

- Navigation 属性搜索：在源码中 grep `NavigationPattern`、`NavigationModel`、`NavigationLayoutProperty`
- NavDestination 属性搜索：grep `NavDestinationPattern`、`NavDestinationModel`
- 路由栈关键字：grep `NavigationStack`、`NavPathInfo`、`NavRouteInfo`
- 事件关键字：grep `NavigationEventHub`、`NavBarEventHub`、`BarItemEventHub`
- 布局关键字：grep `NavigationLayoutAlgorithm`、`NavBarLayoutAlgorithm`、`TitleBarLayoutAlgorithm`

## 相关主题

- NavDestination：`frameworks/core/components_ng/pattern/navrouter/`（NavDestination/NavRouter 共目录）
- Navigator：`frameworks/core/components_ng/pattern/navigator/`（已组件化，有 `bridge/` 子目录）
- NavigationStack：`frameworks/core/components_ng/pattern/navigation/navigation_stack.cpp`
- NavBar / TitleBar / Toolbar：`frameworks/core/components_ng/pattern/navigation/` 内同名 Pattern 文件
- Stage/Page：`frameworks/core/components_ng/pattern/stage/`（Navigation 与 Stage 联动）
