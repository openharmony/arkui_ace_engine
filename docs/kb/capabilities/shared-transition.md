# Shared Transition Context

> 文档版本：v1.0
> 更新时间：2026-07-25
> 来源：`docs/context_registry.json` 主题 `SharedTransition`

## 定位

Shared Transition 是共享元素动画能力，通过 `sharedTransition(id, options)` 属性在页面间实现共享元素的过渡动画。支持 EXCHANGE（交换）和 STATIC（静态）两种效果类型，由 `SharedTransitionController` 管理元素配对和动画执行。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| SharedTransition | `frameworks/core/animation/shared_transition.h` | `SharedTransition`/`SharedTransitionElement`/`SharedTransitionEffectType` |
| Controller | `frameworks/core/animation/shared_transition_controller.h` / `.cpp` | `SharedTransitionController` |
| Effect | `frameworks/core/animation/shared_transition_effect.h` / `.cpp` | `SharedTransitionEffect`/`SharedTransitionExchange`/`SharedTransitionStatic` |
| NG Manager | `frameworks/core/components_ng/manager/shared_overlay/shared_overlay_manager.h` / `.cpp` | `SharedOverlayManager` |
| NG Effect | `frameworks/core/components_ng/manager/shared_overlay/shared_transition_effect.h` / `.cpp` | NG 版 `SharedTransitionEffect` |
| Option | `frameworks/core/components/common/properties/shared_transition_option.h` | `SharedTransitionOptions` |
| JSView 桥接 | `frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h` | `JsSharedTransition` |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/common.d.ts` | `sharedTransition` 属性声明 |
| C API | `interfaces/native/native_node.h` | `NODE_SHARED_TRANSITION` 属性 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 单元测试 | `test/unittest/core/animation/animation_test_core.cpp` | 共享元素动画回归 |

### 相关 Spec

| Spec | 路径 | 说明 |
|------|------|------|
| 共享元素动画功能域 | `specs/03-engine-framework/02-animation-capability/06-shared-transition/` | 规格目录 |
| Feat-01 | `specs/03-engine-framework/02-animation-capability/06-shared-transition/Feat-01-shared-transition-spec.md` | 共享元素动画全量规格 |
| 架构设计 | `specs/03-engine-framework/02-animation-capability/06-shared-transition/design.md` | 架构设计文档 |


## 调试入口

- 核心断点：在 `shared_transition` 的关键方法设置断点，观察状态变化
- 触发链路：从 `SharedTransition` 入口追踪调用链到核心实现
- 回归验证：运行 `test/unittest/core/animation/animation_test_core.cpp` 下定向用例

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 共享元素不配对 | `SharedTransitionController` 的 `CheckIn`/`TakeOff` 机制 |
| 交换动画异常 | `SharedTransitionExchange` 实现 |

## 相关主题

- [Transition Animation（转场动画）](transition-animation.md)
- [Geometry Transition（组件共享元素动画）](geometry-transition.md)