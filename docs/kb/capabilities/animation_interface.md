# Animation Interface Context

> 文档版本：v1.0
> 更新时间：2026-07-25
> 来源：`docs/context_registry.json` 主题 `AnimationInterface`

## 定位

Animation Interface 是动画接口统一层，通过 `AnimationInterface` 枚举统一标识所有动画入口（ANIMATION/ANIMATE_TO/KEYFRAME_ANIMATE_TO/TRANSITION/SHARED_TRANSITION/PAGE_TRANSITION），`AnimationOption` 作为参数载体。同时包含曲线（Curve）体系：预设曲线（Curves）、三次贝塞尔（CubicCurve）、弹簧曲线（SpringCurve）、预期曲线（AnticipateCurve）等。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| AnimationInterface 枚举 | `interfaces/inner_api/ace_kit/include/ui/animation/animation_constants.h` | `AnimationInterface` 枚举定义 |
| AnimationOption | `interfaces/inner_api/ace_kit/include/ui/animation/animation_option.h` | `AnimationOption` 参数载体 |
| AnimationUtils | `interfaces/inner_api/ace_kit/include/ui/animation/animation_utils.h` | 接口工具 |
| Curve 体系 | `interfaces/inner_api/ace_kit/include/ui/animation/curve.h` / `curves.h` / `cubic_curve.h` | Curve 接口和预设 |
| AnimationPub | `frameworks/core/animation/animation_pub.h` / `.cpp` | `GetAnimationInterfaceName`/`GetAnimationFinishCount` |
| 预设曲线 | `frameworks/core/animation/curves.h` / `curves.cpp` | `Curves::LINEAR`/`EASE`/`EASE_IN`/`EASE_OUT`/`FRICTION` 等 |
| CubicCurve | `frameworks/core/animation/cubic_curve.h` / `cubic_curve.cpp` | 三次贝塞尔曲线 |
| SpringCurve | `frameworks/core/animation/spring_curve.h` / `spring_curve.cpp` | 弹簧曲线 |
| AnticipateCurve | `frameworks/core/animation/anticipate_curve.h` / `anticipate_curve.cpp` | 预期曲线 |
| NativeCurveHelper | `frameworks/core/animation/native_curve_helper.h` / `native_curve_helper.cpp` | 桥接 RS 曲线 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| C API | `interfaces/native/native_animate.h` | `ArkUI_NativeAnimateAPI_1` 统一入口（`animateTo`/`keyframeAnimateTo`/`createAnimator`/`disposeAnimator`） |
| C API 曲线 | `interfaces/native/native_animate.h` | `OH_ArkUI_Curve_*` 系列曲线创建函数 |
| NAPI | `interfaces/napi/kits/animator/js_animator.cpp` | `@ohos.animator` NAPI 模块 |
| Dynamic API | `<OH_ROOT>/interface/sdk-js/api/@ohos.animator.d.ts` | `@ohos.animator` 声明 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 单元测试 | `test/unittest/core/animation/animation_pub_test.cpp` | 接口名称映射/直方图 |
| 单元测试 | `test/unittest/core/animation/animation_test_core.cpp` | 动画核心回归 |
| Animator 测试 | `test/unittest/core/pattern/animator/animator_test_ng.cpp` | Animator 选项转换 |

### 相关 Spec

| Spec | 路径 | 说明 |
|------|------|------|
| 动画接口功能域 | `specs/03-engine-framework/02-animation-capability/10-animation-interface/` | 规格目录 |
| Feat-01 | `specs/03-engine-framework/02-animation-capability/10-animation-interface/Feat-01-animation-interface-spec.md` | 动画接口全量规格 |
| 架构设计 | `specs/03-engine-framework/02-animation-capability/10-animation-interface/design.md` | 架构设计文档 |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 动画类型识别错误 | `AnimationInterface` 枚举；`GetAnimationInterfaceName` |
| 曲线效果不对 | `Curves` 预设；`CubicCurve` 控制点；`SpringCurve` 参数 |
| 无限动画性能 | `HistogramInfiniteAnimationEvent` 性能监控 |

## 相关主题

- Animation Framework（动效框架）
- Property Animation（属性动画）
- Explicit Animation（显式动画）
- Physics Animation（物理动画）
