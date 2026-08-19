# Property Animation Context

> 文档版本：v1.0
> 更新时间：2026-07-25
> 来源：`docs/context_registry.json` 主题 `PropertyAnimation`

## 定位

Property Animation 是属性动画能力，通过 `Animatable` 接口和 `PropertyAnimation` 插值器实现可动画属性（位移、缩放、旋转、透明度、颜色等 40+ 属性）的自动插值。属性动画通常由 `animateTo`/`animation` 修饰器触发，框架在属性变更时自动创建插值器并在每帧计算中间值。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| PropertyAnimation | `frameworks/core/animation/property_animation.h` / `.cpp` | `PropertyAnimation : Interpolator`，属性插值核心 |
| Animatable 接口 | `frameworks/core/animation/animatable.h` | `Animatable` + `AnimatableType` 枚举（40+ 可动画属性） |
| AnimatableData | `frameworks/core/animation/animatable_data.h` / `.cpp` | `AnimatableData`，动画数据容器 |
| AnimatableProperties | `frameworks/core/animation/animatable_properties.h` / `.cpp` | `AnimatableProperties`，属性集合 |
| PropertyAnimatable | `frameworks/core/animation/property_animatable.h` | `PropertyAnimatable` 混入 |
| Evaluator | `frameworks/core/animation/evaluator.h` | `Evaluator<T>`、`LinearEvaluator`、`ColorEvaluator`、`TransformOperationEvaluator` |
| AnimationUtil | `frameworks/core/animation/animation_util.h` / `.cpp` | 动画工具函数 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/common.d.ts` | `animation` 修饰器、`animateTo` 声明 |
| C API | `interfaces/native/native_animate.h` | `animateTo` 通过 `ArkUI_NativeAnimateAPI_1` |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 单元测试 | `test/unittest/core/animation/animation_test_core.cpp` | 属性动画/插值器回归 |

### 相关 Spec

| Spec | 路径 | 说明 |
|------|------|------|
| 属性动画功能域 | `specs/03-engine-framework/02-animation-capability/02-property-animation/` | 规格目录 |
| Feat-01 | `specs/03-engine-framework/02-animation-capability/02-property-animation/Feat-01-property-animation-spec.md` | 属性动画全量规格 |
| 架构设计 | `specs/03-engine-framework/02-animation-capability/02-property-animation/design.md` | 架构设计文档 |

## 调试入口

- 插值断点：`PropertyAnimation::Calculate()` 观察每帧插值结果
- 触发链路：从 `animateTo`/`animation` 修饰器入口追踪属性变更到插值器创建
- 回归验证：运行 `test/unittest/core/animation/animation_test_core.cpp` 下定向用例

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 属性不插值 | `Animatable` 接口实现；`PropertyAnimation::Calculate()` |
| 颜色插值异常 | `ColorEvaluator` 实现 |
| Transform 插值异常 | `TransformOperationEvaluator` 实现 |

## 相关主题

- [Animation Framework（动效框架）](animation-framework.md)
- [Explicit Animation（显式动画）](explicit-animation.md)
- [Keyframe Animation（关键帧动画）](keyframe-animation.md)