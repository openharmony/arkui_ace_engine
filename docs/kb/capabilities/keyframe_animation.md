# Keyframe Animation Context

> 文档版本：v1.0
> 更新时间：2026-07-25
> 来源：`docs/context_registry.json` 主题 `KeyframeAnimation`

## 定位

Keyframe Animation 是关键帧动画能力，通过 `keyframeAnimateTo` API 设置多个关键帧（Keyframe），每个关键帧可指定时间和曲线，框架在关键帧之间分段插值。与 `animateTo` 不同，关键帧动画支持更精细的时间点和曲线控制。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| KeyframeAnimation | `frameworks/core/animation/keyframe_animation.h` | `KeyframeAnimation<T> : Animation<T>`，`AddKeyframe`/`ReplaceKeyframe`/`Calculate` |
| Keyframe | `frameworks/core/animation/keyframe.h` | `Keyframe<T>`，时间/值/曲线 |
| JSView 桥接 | `frameworks/bridge/declarative_frontend/jsview/js_view_context.h` / `.cpp` | `JSKeyframeAnimateTo` |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/common.d.ts` | `keyframeAnimateTo` 声明 |
| C API | `interfaces/native/native_animate.h` | `ArkUI_NativeAnimateAPI_1::keyframeAnimateTo` + `OH_ArkUI_KeyframeAnimateOption_*` |
| C API 实现 | `interfaces/native/node/animate_impl.cpp` | `KeyframeAnimateTo()` 实现 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 单元测试 | `test/unittest/core/animation/animation_test_core.cpp` | 关键帧动画回归 |

### 相关 Spec

| Spec | 路径 | 说明 |
|------|------|------|
| 关键帧动画功能域 | `specs/03-engine-framework/02-animation-capability/04-keyframe-animation/` | 规格目录 |
| Feat-01 | `specs/03-engine-framework/02-animation-capability/04-keyframe-animation/Feat-01-keyframe-animation-spec.md` | 关键帧动画全量规格 |
| 架构设计 | `specs/03-engine-framework/02-animation-capability/04-keyframe-animation/design.md` | 架构设计文档 |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 关键帧不生效 | `KeyframeAnimation::AddKeyframe` 调用链 |
| 关键帧时间不对 | `Keyframe` 时间参数解析 |

## 相关主题

- Explicit Animation（显式动画）
- Property Animation（属性动画）
- Animation Interface（动画接口）
