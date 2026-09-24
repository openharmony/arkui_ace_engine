# Explicit Animation Context

> 文档版本：v1.0
> 更新时间：2026-07-25
> 来源：`docs/context_registry.json` 主题 `ExplicitAnimation`

## 定位

Explicit Animation 是显式动画能力，通过 `animateTo(options, callback)` API 在闭包中修改属性状态，框架自动将状态变更包装为属性动画。`AnimationOption` 作为载体保存 duration、curve、delay、iterations、playMode 等参数，由 PipelineContext 保存和清除。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| AnimationOption | `interfaces/inner_api/ace_kit/include/ui/animation/animation_option.h` | `AnimationOption`，显式动画参数载体 |
| Pipeline 保存/清除 | `frameworks/core/pipeline/pipeline_context.h` | `SaveExplicitAnimationOption`/`ClearExplicitAnimationOption` |
| RenderNode | `frameworks/core/pipeline/base/render_node.h` | RenderNode 级别的显式动画选项访问 |
| JSView 桥接 | `frameworks/bridge/declarative_frontend/jsview/js_view_context.h` / `.cpp` | `JSAnimateTo`/`JSAnimateToImmediately`/`AnimateToInner` |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/common.d.ts` | `animateTo` 声明 |
| C API | `interfaces/native/native_animate.h` | `ArkUI_NativeAnimateAPI_1::animateTo` + `OH_ArkUI_AnimateOption_*` |
| C API 实现 | `interfaces/native/node/animate_impl.cpp` | `AnimateTo()` 实现 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 单元测试 | `test/unittest/core/animation/animation_test_core.cpp` | 显式动画选项处理 |
| C API 测试 | `test/unittest/capi/` | animate 相关用例 |

### 相关 Spec

| Spec | 路径 | 说明 |
|------|------|------|
| 显式动画功能域 | `specs/03-engine-framework/02-animation-capability/03-explicit-animation/` | 规格目录 |
| Feat-01 | `specs/03-engine-framework/02-animation-capability/03-explicit-animation/Feat-01-explicit-animation-spec.md` | 显式动画全量规格 |
| 架构设计 | `specs/03-engine-framework/02-animation-capability/03-explicit-animation/design.md` | 架构设计文档 |


## 调试入口

- 核心断点：在 `animation_option` 的关键方法设置断点，观察状态变化
- 触发链路：从 `AnimationOption` 入口追踪调用链到核心实现
- 回归验证：运行 `test/unittest/core/animation/animation_test_core.cpp` 下定向用例

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| animateTo 不生效 | `PipelineContext::SaveExplicitAnimationOption` 调用链 |
| 动画参数丢失 | `AnimationOption` 解析；`JSAnimateTo` 参数传递 |

## 相关主题

- [Property Animation（属性动画）](property-animation.md)
- [Keyframe Animation（关键帧动画）](keyframe-animation.md)
- [Animation Interface（动画接口）](animation-interface.md)