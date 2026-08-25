# Animation Framework Context

> 文档版本：v1.0
> 更新时间：2026-07-25
> 来源：`docs/context_registry.json` 主题 `AnimationFramework`

## 定位

Animation Framework 是 ArkUI 引擎框架层的动效核心，提供动画控制器（Animator）、插值器（Interpolator）、VSync 调度器（Scheduler）、动画组（AnimatorGroup）和链式动画（ChainAnimation）等基础能力。所有动画类型（属性动画、显式动画、关键帧动画等）均基于此框架运行。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| Animator 控制器 | `frameworks/core/animation/animator.h` / `.cpp` | `Animator`，动画生命周期管理（play/pause/cancel/reverse） |
| Animation 模板基类 | `frameworks/core/animation/animation.h` | `Animation<T>`，插值计算模板 |
| Interpolator 接口 | `frameworks/core/animation/interpolator.h` | `Interpolator`，插值器接口 |
| Scheduler 调度器 | `frameworks/core/animation/scheduler.h` / `.cpp` | VSync 驱动的动画调度 |
| AnimatorGroup | `frameworks/core/animation/animator_group.h` / `.cpp` | 动画组编排 |
| ChainAnimation | `frameworks/core/animation/chain_animation.h` / `.cpp` | 链式动画 |
| AnimationPub | `frameworks/core/animation/animation_pub.h` / `.cpp` | 公共工具函数 |
| AnimatorInfo | `frameworks/core/animation/animator_info.h` | 动画配置包装 |
| NG Model | `frameworks/core/components_ng/pattern/animator/animator_model_ng.h` / `.cpp` | NG Animator Model |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| NAPI (@ohos.animator) | `interfaces/napi/kits/animator/js_animator.cpp` | `Animator` NAPI 模块 |
| C API | `interfaces/native/native_animate.h` | `ArkUI_NativeAnimateAPI_1`：`createAnimator`/`disposeAnimator`/`OH_ArkUI_Animator_Play/Finish/Pause/Cancel/Reverse` |
| C API 实现 | `interfaces/native/node/animate_impl.cpp` | `CreateAnimator` 等实现 |
| Dynamic API | `<OH_ROOT>/interface/sdk-js/api/@ohos.animator.d.ts` | `@ohos.animator` 声明 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 单元测试 | `test/unittest/core/animation/` | 动画核心回归 |
| Animator 测试 | `test/unittest/core/pattern/animator/` | Animator Pattern 回归 |

### 相关 Spec

| Spec | 路径 | 说明 |
|------|------|------|
| 动效框架功能域 | `specs/03-engine-framework/02-animation-capability/01-animation-framework/` | 规格目录 |
| Feat-01 | `specs/03-engine-framework/02-animation-capability/01-animation-framework/Feat-01-animation-framework-spec.md` | 动效框架全量规格 |
| 架构设计 | `specs/03-engine-framework/02-animation-capability/01-animation-framework/design.md` | 架构设计文档 |

## 调试入口

- 动画生命周期断点：`Animator::Play()`/`Pause()`/`Cancel()` 观察状态机流转
- VSync 调度断点：`Scheduler` 帧回调，观察动画 Tick 与插值时机
- 回归验证：运行 `test/unittest/core/animation/` 与 `test/unittest/core/pattern/animator/` 下定向用例

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 动画不播放 | `Animator::Play()` 调用链；`Scheduler` VSync 注册 |
| 动画卡顿 | `Scheduler` 帧调度；`AnimationOption` duration 设置 |
| 动画组不同步 | `AnimatorGroup` 编排逻辑 |

## 相关主题

- [Property Animation（属性动画）](property-animation.md)
- [Explicit Animation（显式动画）](explicit-animation.md)
- [Physics Animation（物理动画）](physics-animation.md)
- [Animation Interface（动画接口）](animation-interface.md)