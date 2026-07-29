# NavDestination Context

> 文档版本：v1.0
> 更新时间：2026-07-08
> 来源：`docs/context_registry.json` 主题 `NavDestination`

## 定位

NavDestination 是 Navigation 导航体系中的目标页组件，负责承载具体页面内容、页面生命周期回调、转场动画配置和沉浸式样式。当前推荐通过 Navigation(NavPathStack) push/pop 管理导航跳转与返回。NavRouter 自 API version 13 起已标记 `@deprecated`，不应再作为跳转入口使用。行为事实来源于 SDK 声明、源码和测试。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| Pattern 主实现 | `frameworks/core/components_ng/pattern/navrouter/navdestination_pattern.cpp` | 页面生命周期、转场、布局协调 |
| Pattern 头文件 | `frameworks/core/components_ng/pattern/navrouter/navdestination_pattern.h` | |
| Model（动态） | `frameworks/core/components_ng/pattern/navrouter/navdestination_model_ng.cpp` | 属性设置入口 |
| Model（静态） | `frameworks/core/components_ng/pattern/navrouter/navdestination_model_static.cpp` | 静态编译属性入口 |
| Layout Property | `frameworks/core/components_ng/pattern/navrouter/navdestination_layout_property.h` | 属性声明 |
| Layout Algorithm | `frameworks/core/components_ng/pattern/navrouter/navdestination_layout_algorithm.cpp` | |
| Event Hub | `frameworks/core/components_ng/pattern/navrouter/navdestination_event_hub.h` | 生命周期事件 |
| Context | `frameworks/core/components_ng/pattern/navrouter/navdestination_context.cpp` | 页面上下文 |
| Scrollable Processor | `frameworks/core/components_ng/pattern/navrouter/navdestination_scrollable_processor.h` | 滚动嵌套处理 |
| Group Node | `frameworks/core/components_ng/pattern/navrouter/navdestination_group_node.cpp` | |
| Pattern 基类（Navigation 共用） | `frameworks/core/components_ng/pattern/navigation/navdestination_pattern_base.cpp` | 基类抽象 |
| Node 基类（Navigation 共用） | `frameworks/core/components_ng/pattern/navigation/navdestination_node_base.cpp` | |
| Content Pattern | `frameworks/core/components_ng/pattern/navigation/navdestination_content_pattern.h` | |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/nav_destination.d.ts` | 声明式 API |
| Static | `<OH_ROOT>/interface/sdk-js/api/arkui/component/nav_destination.static.d.ets` | 静态编译 API |
| Modifier Dynamic | `<OH_ROOT>/interface/sdk-js/api/arkui/NavDestinationModifier.d.ts` | 动态属性 Modifier |
| Modifier Static | `<OH_ROOT>/interface/sdk-js/api/arkui/NavDestinationModifier.static.d.ets` | 静态属性 Modifier |

### API 解析实现路径

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| JSView（声明式组件） | `frameworks/bridge/declarative_frontend/jsview/js_navdestination.cpp` | `JSNavDestination::Create()` → `NavDestinationModelNG::GetInstance()->Create()` |
| ArkTS Bridge（动态属性） | `frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_nav_destination_bridge.cpp` | Bridge → ModelNG |
| 前端 Modifier（ArkTS 侧） | `frameworks/bridge/declarative_frontend/ark_modifier/src/nav_destination_modifier.ts` | ArkTS Modifier 类 |
| NavDestination Context JSView | `frameworks/bridge/declarative_frontend/jsview/js_navdestination_context.cpp` | 页面上下文桥接 |
| NavDestination Scrollable Processor JSView | `frameworks/bridge/declarative_frontend/jsview/js_navdestination_scrollable_processor.cpp` | 滚动处理桥接 |

NavDestination 未组件化（无 `bridge/` 子目录、无独立 so）。组件化改造参考：通用组件化重构方案。改造后 JSView 和 Bridge 双路径将统一到 `pattern/navrouter/bridge/`，并输出独立 so。

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| NavDestination Pattern UT | `test/unittest/core/pattern/navrouter/navdestination_pattern_test_ng.cpp` | Pattern 逻辑测试 |
| NavDestination Model UT | `test/unittest/core/pattern/navrouter/navdestination_model_test_ng.cpp` | Model 属性设置测试 |
| NavDestination Model Static UT | `test/unittest/core/pattern/navrouter/navdestination_model_static_test_ng.cpp` | 静态 Model 测试 |
| NavDestination Group Node UT | `test/unittest/core/pattern/navrouter/navdestination_group_node_test_ng.cpp` | Group Node 测试 |
| NavDestination Base UT（Navigation 目录） | `test/unittest/core/pattern/navigation/navdestination_base_test_ng.cpp` | 基类测试 |
| NavDestination Pattern Base UT | `test/unittest/core/pattern/navigation/navdestination_pattern_base_test_ng.cpp` | Pattern 基类测试 |
| NavDestination Result UT | `test/unittest/core/pattern/navigation/navdestination_result_test.cpp` | 返回值结果测试 |
| NavDestination 全量 UT | `test/unittest/core/pattern/navigation/navdestination_test_ng.cpp` | 综合测试 |

### 相关 Spec

Spec 功能域：`specs/05-ui-components/02-navigation-components/02-nav-router/`

当前状态：`pending`（spec 目录尚未创建，design 为 null）。NavDestination 的 Spec 内容目前嵌合在 Navigation 的 Feat 体系中（`05-02-01`），独立 spec 待后续拆分。

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 页面生命周期回调未触发 | `navdestination_pattern.cpp` — `OnAttachToFrameNode` / `OnDetachFromFrameNode` / lifecycle 方法 |
| 转场动画异常 | `navdestination_pattern.cpp` — `GetTransitionAnimation` / animated config |
| 沉浸式样式不生效 | `navdestination_layout_property.h` — `systemBarStyle` / `hideSystemBar` 属性 |
| 页面返回值传递失败 | `navdestination_context.cpp` — `NavDestinationContext` 返回值机制 |
| 滚动嵌套/手势冲突 | `navdestination_scrollable_processor.h` — nested scroll processing |
| NavPathStack 跳转后 NavDestination 不渲染 | `navigation_pattern.cpp` — NavPathStack push 流程与 NavDestination 创建链路 |

## 调试入口

- Pattern 日志关键字：`NavDestination`、`NavDestPattern`
- 生命周期日志：搜索 `OnAppear` / `OnDisappear` / `onShown` / `onHidden` 回调触发
- 堆栈管理调试：`NavPathStack` push/pop 日志，观察 NavDestination 入栈出栈时机
- 滚动调试：`NavDestinationScrollableProcessor` nested scroll trace

## 相关主题

- Navigation 容器组件 — `docs/kb/components/container/navigation.md`
- NavPathStack — `frameworks/core/components_ng/pattern/navigation/navigation_stack.cpp`（推荐路由管理方式）
- NavRouter（已废弃） — `frameworks/core/components_ng/pattern/navrouter/navrouter_pattern.*`（API 13 deprecated，推荐 NavPathStack 替代）
- Navigator 组件 — `frameworks/core/components_ng/pattern/navigator/`
- 页面生命周期 — NavPathStack 与 NavDestination 生命周期联动
- 转场动画 — Navigation 路由转场与 NavDestination 自定义动画
