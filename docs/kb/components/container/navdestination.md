# NavDestination Context

> 文档版本：v1.0
> 更新时间：2026-07-28
> 来源：`docs/context_registry.json` 主题 `NavDestination`

## 定位

ArkUI NavDestination 是导航目标页组件，管理页面生命周期（onShown/onHidden）、转场动画、沉浸式状态栏等。基于 NavDestinationPattern 实现，与 Navigation 配合使用。C API 暴露为 nav_destination_modifier。

本文档用于快速定位 NavDestination 相关源码、SDK 声明、测试和规格文档。具体行为、默认值、边界条件和兼容性说明以对应 SDK 声明、源码实现、测试用例和 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| pattern | `frameworks/core/components_ng/pattern/navrouter/navdestination_pattern.cpp` | |
| pattern_header | `frameworks/core/components_ng/pattern/navrouter/navdestination_pattern.h` | |
| model | `frameworks/core/components_ng/pattern/navrouter/navdestination_model_ng.cpp` | |
| static_model | `frameworks/core/components_ng/pattern/navrouter/navdestination_model_static.cpp` | |
| layout | `frameworks/core/components_ng/pattern/navrouter/navdestination_layout_algorithm.cpp` | |
| property | `frameworks/core/components_ng/pattern/navrouter/navdestination_layout_property.h` | |
| event_hub | `frameworks/core/components_ng/pattern/navrouter/navdestination_event_hub.cpp` | |
| context | `frameworks/core/components_ng/pattern/navrouter/navdestination_context.cpp` | |
| group_node | `frameworks/core/components_ng/pattern/navrouter/navdestination_group_node.cpp` | |
| scrollable_processor | `frameworks/core/components_ng/pattern/navrouter/navdestination_scrollable_processor.h` | |
| pattern_base | `frameworks/core/components_ng/pattern/navigation/navdestination_pattern_base.cpp` | |
| node_base | `frameworks/core/components_ng/pattern/navigation/navdestination_node_base.cpp` | |
| jsview | `frameworks/bridge/declarative_frontend/jsview/js_navdestination.cpp` | |
| bridge | `frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_nav_destination_bridge.cpp` | |
| capi_modifier | `interfaces/native/node/nav_destination_modifier.cpp` | |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| dynamic | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/nav_destination.d.ts` | |
| static | `<OH_ROOT>/interface/sdk-js/api/arkui/component/nav_destination.static.d.ets` | |
| modifier | `<OH_ROOT>/interface/sdk-js/api/arkui/NavDestinationModifier.d.ts` | |
| modifier_static | `<OH_ROOT>/interface/sdk-js/api/arkui/NavDestinationModifier.static.d.ets` | |

### 测试入口

| 稳定路径 | 用途 |
|----------|------|
| test/unittest/core/pattern/navrouter/ | |
| test/unittest/core/pattern/navigation/ | |
| test/unittest/capi/modifiers/nav_destination_modifier_test.cpp | |

### 相关 Spec

| Spec | 路径 | 说明 |
|------|------|------|
| 功能域 | `specs/05-ui-components/02-navigation-components/03-nav-destination/` | NavDestination 导航目标页组件，管理页面生命周期、转场动画和沉浸式状态。func_id 更正为 05-02-03。 |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 页面生命周期不触发 | 检查 NavDestinationPattern 的生命周期状态机和 NavDestinationContext |
| 转场动画异常 | 查看 NavDestinationLayoutAlgorithm 的转场参数和动画配置 |
| 沉浸式状态栏不生效 | 确认 NavDestinationPattern 的 systemBarStyle 设置 |

## 调试入口

- 创建链路：NavDestinationModelNG::Create() → NavDestinationPattern
- 生命周期：NavDestinationPattern 状态机 → onShown/onHidden
- C API 链路：nav_destination_modifier.cpp

## 相关主题

- Navigation 导航容器
- 命名路由
- NavRouter
