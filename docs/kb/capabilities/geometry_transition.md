# Geometry Transition Context

> 文档版本：v1.0
> 更新时间：2026-07-25
> 来源：`docs/context_registry.json` 主题 `GeometryTransition`

## 定位

Geometry Transition 是组件共享元素动画能力，通过 `geometryTransition(id)` 属性在 FrameNode 级别实现基于几何变换的共享元素过渡。与页面级 `sharedTransition` 不同，`geometryTransition` 作用于组件级别，支持更细粒度的共享元素动画。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| GeometryTransition | `frameworks/core/components_ng/animation/geometry_transition.h` / `.cpp` | `GeometryTransition : AceType`，核心实现 |
| AnimatableArithmetic | `frameworks/core/components_ng/animation/animatable_arithmetic.h` | 可动画算术类型 |
| JSView 桥接 | `frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h` | `JsGeometryTransition` |
| Bridge | `frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_common_bridge.h` | `SetGeometryTransition`/`ResetGeometryTransition` |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/common.d.ts` | `geometryTransition` 属性声明 |
| C API | `interfaces/native/native_node.h` | `NODE_GEOMETRY_TRANSITION` 属性 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 单元测试 | `test/unittest/core/animation/geometry_transition_test_ng.cpp` | GeometryTransition NG 回归 |

### 相关 Spec

| Spec | 路径 | 说明 |
|------|------|------|
| 组件共享元素动画功能域 | `specs/03-engine-framework/02-animation-capability/07-geometry-transition/` | 规格目录 |
| Feat-01 | `specs/03-engine-framework/02-animation-capability/07-geometry-transition/Feat-01-geometry-transition-spec.md` | 组件共享元素动画全量规格 |
| 架构设计 | `specs/03-engine-framework/02-animation-capability/07-geometry-transition/design.md` | 架构设计文档 |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| geometryTransition 不生效 | `GeometryTransition` 节点注册和配对逻辑 |
| 几何变换异常 | `AnimatableArithmetic` 插值计算 |

## 相关主题

- Shared Transition（共享元素动画）
- Transition Animation（转场动画）
