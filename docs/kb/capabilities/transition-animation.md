# Transition Animation Context

> 文档版本：v1.0
> 更新时间：2026-07-25
> 来源：`docs/context_registry.json` 主题 `TransitionAnimation`

## 定位

Transition Animation 是转场动画能力，包含组件进出场转场（`TransitionEffect`）和页面/卡片转场。组件转场通过 `ChainedTransitionEffect` 链式组合 OPACITY/TRANSLATE/SCALE/ROTATE/MOVE 等效果；页面转场通过 `PageTransitionOption` 配置。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| 转场属性 | `frameworks/core/components_ng/property/transition_property.h` | `ChainedTransitionEffect` 及各子类 |
| 转场 Modifier | `frameworks/core/components_ng/render/adapter/transition_modifier.h` | 渲染侧修饰器 |
| 页面转场 | `frameworks/core/animation/page_transition_common.h` | `PageTransitionType`/`RouteType`/`PageTransitionOption` |
| 卡片转场 | `frameworks/core/animation/card_transition_controller.h` / `.cpp` | `CardTransitionController` |
| JSView 桥接 | `frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h` | `ParseJsTransitionEffect`/`ParseChainedTransition` |
| 页面转场 DSL | `frameworks/bridge/declarative_frontend/jsview/js_page_transition.h` / `.cpp` | 页面转场声明式 DSL |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/common.d.ts` | `transition` 修饰器声明 |
| C API | `interfaces/native/native_animate.h` | `OH_ArkUI_CreateOpacityTransitionEffect` 等 |
| C API Node | `interfaces/native/node/node_transition.h` | `ArkUI_TransitionEffectType`/`ArkUI_TransitionEffect` |
| C API 属性 | `interfaces/native/native_node.h` | `NODE_TRANSITION_EFFECT` 属性 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| C API 测试 | `test/unittest/capi/accessors/transition_effect_accessor_test.cpp` | 转场效果 C API 回归 |
| 单元测试 | `test/unittest/interfaces/node_transition_test.cpp` | Node 转场测试 |

### 相关 Spec

| Spec | 路径 | 说明 |
|------|------|------|
| 转场动画功能域 | `specs/03-engine-framework/02-animation-capability/05-transition-animation/` | 规格目录 |
| Feat-01 | `specs/03-engine-framework/02-animation-capability/05-transition-animation/Feat-01-transition-animation-spec.md` | 转场动画全量规格 |
| 架构设计 | `specs/03-engine-framework/02-animation-capability/05-transition-animation/design.md` | 架构设计文档 |


## 调试入口

- 核心断点：在 `transition_property` 的关键方法设置断点，观察状态变化
- 触发链路：从 `转场属性` 入口追踪调用链到核心实现
- 回归验证：运行 `test/unittest/capi/accessors/transition_effect_accessor_test.cpp` 下定向用例

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 组件转场不生效 | `ChainedTransitionEffect` 解析；`TransitionModifier` 渲染 |
| 页面转场异常 | `PageTransitionOption` 配置；`js_page_transition.cpp` |

## 相关主题

- [Shared Transition（共享元素动画）](shared-transition.md)
- [Geometry Transition（组件共享元素动画）](geometry-transition.md)
- [Animation Framework（动效框架）](animation-framework.md)