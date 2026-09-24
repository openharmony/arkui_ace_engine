# Motion Path Context

> 文档版本：v1.0
> 更新时间：2026-07-25
> 来源：`docs/context_registry.json` 主题 `MotionPath`

## 定位

Motion Path 是路径动画能力，通过 `motionPath` 属性指定 SVG 路径，让组件在动画过程中沿路径进行位移和旋转。`MotionPathOption` 保存路径、起点、终点、是否旋转等参数，`MotionPathEvaluator` 负责路径采样和位置计算。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| MotionPathOption | `frameworks/core/components/common/properties/motion_path_option.h` | 路径动画参数 |
| MotionPathEvaluator | `frameworks/core/components/common/properties/motion_path_evaluator.h` / `.cpp` | 路径采样和位置计算 |
| NativeCurveHelper | `frameworks/core/animation/native_curve_helper.h` / `.cpp` | 桥接 RS `RSMotionPathOption` |
| JSView 桥接 | `frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h` | `JsMotionPath` |
| Bridge | `frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_common_bridge.h` | `SetMotionPath`/`ResetMotionPath` |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/common.d.ts` | `motionPath` 属性声明 |
| C API | `interfaces/native/native_type.h` | `ArkUI_MotionPathOptions` + `OH_ArkUI_MotionPathOptions_*` |
| C API 属性 | `interfaces/native/native_node.h` | `NODE_MOTION_PATH` 属性 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 单元测试 | `test/unittest/core/animation/animation_test_core.cpp` | 路径动画回归 |

### 相关 Spec

| Spec | 路径 | 说明 |
|------|------|------|
| 路径动画功能域 | `specs/03-engine-framework/02-animation-capability/08-motion-path/` | 规格目录 |
| Feat-01 | `specs/03-engine-framework/02-animation-capability/08-motion-path/Feat-01-motion-path-spec.md` | 路径动画全量规格 |
| 架构设计 | `specs/03-engine-framework/02-animation-capability/08-motion-path/design.md` | 架构设计文档 |


## 调试入口

- 核心断点：在 `motion_path_option` 的关键方法设置断点，观察状态变化
- 触发链路：从 `MotionPathOption` 入口追踪调用链到核心实现
- 回归验证：运行 `test/unittest/core/animation/animation_test_core.cpp` 下定向用例

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 路径不生效 | `MotionPathOption` 路径解析；`MotionPathEvaluator` 采样 |
| 旋转不跟随 | `MotionPathOption` 的 `rotatable` 参数 |

## 相关主题

- [Property Animation（属性动画）](property-animation.md)
- [Animation Framework（动效框架）](animation-framework.md)