# Physics Animation Context

> 文档版本：v1.0
> 更新时间：2026-07-25
> 来源：`docs/context_registry.json` 主题 `PhysicsAnimation`

## 定位

Physics Animation 是物理动画能力，基于弹簧（Spring）、摩擦（Friction）、滚动（Scroll）等物理模型驱动动画，无需固定时长。`Motion` 基类定义接口，`SpringMotion`/`FrictionMotion`/`ScrollMotion` 等子类实现具体物理模拟。弹簧模型支持临界阻尼、过阻尼、欠阻尼三种模式。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| Motion 基类 | `frameworks/core/animation/motion.h` | `Motion : TimeEvent, ValueListenable<double>` |
| SpringMotion | `frameworks/core/animation/spring_motion.h` / `.cpp` | 弹簧运动 |
| FrictionMotion | `frameworks/core/animation/friction_motion.h` / `.cpp` | 摩擦运动 |
| ScrollMotion | `frameworks/core/animation/scroll_motion.h` / `.cpp` | 滚动运动 |
| VelocityMotion | `frameworks/core/animation/velocity_motion.h` | 速度运动 |
| SpringModel | `frameworks/core/animation/spring_model.h` / `.cpp` | `SpringModel` + 临界/过/欠阻尼 |
| SpringAnimation | `frameworks/core/animation/spring_animation.h` / `.cpp` | `SpringAnimation : Animation<float>` |
| SpringCurve | `frameworks/core/animation/spring_curve.h` / `.cpp` | `SpringCurve`（response/dampingRatio/velocity） |
| SpringChain | `frameworks/core/animation/simple_spring_chain.h` / `.cpp` | `SimpleSpringChain` 链式弹簧 |
| ChainAnimation | `frameworks/core/animation/chain_animation.h` / `.cpp` | `ChainAnimation` 链式动画基类 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| C API | `interfaces/native/native_animate.h` | `OH_ArkUI_Curve_CreateSpringMotion`/`CreateResponsiveSpringMotion`/`CreateSpringCurve`/`CreateInterpolatingSpring` |
| C API 实现 | `interfaces/native/node/animate_impl.cpp` | `SpringMotion`/`ResponsiveSpringMotion` 实现 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 单元测试 | `test/unittest/core/animation/animation_test_core.cpp` | 弹簧/物理动画回归 |
| 弹簧链测试 | `frameworks/core/animation/test/unittest/spring_chain/` | 链式弹簧专用测试 |

### 相关 Spec

| Spec | 路径 | 说明 |
|------|------|------|
| 物理动画功能域 | `specs/03-engine-framework/02-animation-capability/09-physics-animation/` | 规格目录 |
| Feat-01 | `specs/03-engine-framework/02-animation-capability/09-physics-animation/Feat-01-physics-animation-spec.md` | 物理动画全量规格 |
| 架构设计 | `specs/03-engine-framework/02-animation-capability/09-physics-animation/design.md` | 架构设计文档 |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 弹簧动画不收敛 | `SpringModel` 刚度/阻尼参数；`CriticalDampedSpring`/`OverdampedSpring`/`UnderdampedSpring` |
| 链式弹簧不同步 | `SimpleSpringChain`/`ChainAnimation` 编排逻辑 |

## 相关主题

- Animation Framework（动效框架）
- Animation Interface（动画接口）
