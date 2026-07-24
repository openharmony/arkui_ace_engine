# DFX Layout Boundary Display Context

> 文档版本：v1.0
> 更新时间：2026-07-23
> 来源：`docs/context_registry.json` 主题 `DFXLayoutBoundaryDisplay`

## 定位

DFX Layout Boundary Display 是 ArkUI 引擎的布局边界调试显示能力，在组件边界绘制调试线框以可视化和定位布局问题。它不是对外公共 API，而是引擎内部调试能力，通过 SystemProperties::gestureDebugBoundaryEnabled_ 开关，仅在 Debug 模式下可用。

本文档只提供稳定的源码、SDK、测试和 Spec 路由。具体调试边界绘制、开关、绘制逻辑、渲染路径应回到当前源码、测试和 Spec 核实。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| GestureDebugBoundaryManager | `frameworks/core/components_ng/manager/gesture_debug/gesture_debug_boundary_manager.h` | 手势调试边界管理器、状态跟踪、边界重置、绘制触发 |
| DebugBoundaryPainter | `frameworks/core/components_ng/render/debug_boundary_painter.h` | 布局调试边界绘制器、PaintDebugBoundary |
| RenderContext 绘制入口 | `frameworks/core/components_ng/render/render_context.h` | RenderContext::PaintDebugBoundary，渲染上下文中的调试边界绘制入口 |
| RosenRenderContext 适配 | `frameworks/core/components_ng/render/adapter/rosen_render_context.h` | OHOS PaintGestureDebugBoundary 手势边界绘制、GestureDebugBoundaryModifier |
| SystemProperties 开关 | `frameworks/base/utils/system_properties.h` | gestureDebugBoundaryEnabled_ Debug 边界显示开关 |

### API 入口

DFX Layout Boundary Display 是引擎内部调试能力，没有独立 SDK API，仅在 Debug 版本中通过系统属性开关启用。

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| GestureDebugBoundaryManager | `test/unittest/core/manager/gesture_debug_boundary_manager_test_ng.cpp` | GestureDebugBoundaryManager 状态跟踪、边界重置 |
| GestureRecognizer 集成 | `test/unittest/core/gestures/gesture_recognizer_test_ng.cpp` | GestureDebugBoundaryManager 与 EventManager 集成 |
| RosenRenderContext 绘制 | `test/unittest/core/rosen/rosen_render_context_test.cpp` | PaintGestureDebugBoundary、GestureDebugBoundaryModifier |
| DebugBoundaryPainter | `test/unittest/core/render/render_context_test_ng.cpp` | DebugBoundaryPainter、PaintDebugBoundary |
| PaintDebugBoundaryTreeAll | `test/unittest/core/base/ui_node_test_ng_two.cpp` | UINode 递归调试边界树绘制 |
| RepeatVirtual2 | `test/unittest/core/syntax/repeat_virtual_2_syntax_test_ng_advanced.cpp` | RepeatVirtual2 调试边界绘制 |

### 相关 Spec

布局边界显示功能域：`specs/03-engine-framework/08-dfx-foundation/06-layout-boundary-display/`（功能 ID `03-08-06`）。

| 文档 | 稳定路径 | 覆盖范围 |
|------|----------|----------|
| 布局边界显示调试能力 | `specs/03-engine-framework/08-dfx-foundation/06-layout-boundary-display/Feat-01-layout-boundary-display-spec.md` | 调试边界绘制、开关、渲染路径 |
| 设计文档 | `specs/03-engine-framework/08-dfx-foundation/06-layout-boundary-display/design.md` | 整体架构 |

**注意**：布局边界显示的 Spec 状态为 Draft，尚未 Baselined。

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 调试边界不显示 | SystemProperties::gestureDebugBoundaryEnabled_ 开关，仅 Debug 版本生效 |
| 手势边界不绘制 | GestureDebugBoundaryManager 状态跟踪、HandleGestureAccept 边界触发 |
| 边界绘制渲染不输出 | RosenRenderContext PaintGestureDebugBoundary、GestureDebugBoundaryModifier 渲染管线 |
| 递归绘制不覆盖子节点 | PaintDebugBoundaryTreeAll 递归遍历、节点 enabled/disabled 传播 |

## 调试入口

- 开关确认：SystemProperties::gestureDebugBoundaryEnabled_ 仅 Debug 版本
- 状态跟踪断点：GestureDebugBoundaryManager::HandleGestureAccept/ResetAllGesturesOnNewRound/ClearNode
- 渲染断点：RosenRenderContext::PaintGestureDebugBoundary、GestureDebugBoundaryModifier mask/stroke/color
- 递归断点：UINode::PaintDebugBoundaryTreeAll 递归调用链、enabled 传播

## 相关主题

- Dump 机制：`docs/kb/architecture/dfx/dump-mechanism.md`
- 渲染管线：`docs/kb/architecture/layout-framework.md`
