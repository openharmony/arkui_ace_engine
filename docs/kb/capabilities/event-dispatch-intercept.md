# Event Dispatch and Intercept Context

> 文档版本：v1.0
> 更新时间：2026-07-30
> 来源：`docs/context_registry.json` 主题 `EventDispatchIntercept`

## 定位

Event Dispatch and Intercept 是 ArkUI 通用输入事件从命中测试、事件目标链构建到序列分发、拦截、跨容器转发和自定义事件投递的能力域。它横跨 EventManager、FrameNode 命中测试、GestureEventHub 响应链、输入监控和 PostEvent 管理。

本文档只提供机制入口，不复制各输入类型的行为规格。触摸、按键、鼠标和手势的数据模型及专属 API 应进入各自 KB；具体传播顺序、拦截结果和跨容器边界以源码、测试及本功能域 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| 通用事件分发管理 | `frameworks/core/common/event_manager.h`、`frameworks/core/common/event_manager.cpp` | 触摸、鼠标、轴事件和命中结果分发的管理入口 |
| 输入事件监控 | `frameworks/core/common/input_event_monitor_manager.h`、`frameworks/core/common/input_event_monitor_manager.cpp` | 输入事件监控注册、分发和消费信息入口 |
| 节点命中测试 | `frameworks/core/components_ng/base/frame_node.cpp` | FrameNode 触摸测试、响应区域和目标收集入口 |
| 响应链与拦截 | `frameworks/core/components_ng/event/gesture_event_hub.cpp` | 触摸测试、手势目标收集、拦截和响应链入口 |
| 自定义事件投递 | `frameworks/core/components_ng/manager/post_event/post_event_manager.cpp` | PostEvent 命中、目标缓存与投递入口 |
| 事件常量 | `frameworks/core/components_ng/event/event_constants.h` | 命中测试模式、事件树和相关枚举入口 |
| Native 输入事件 | `interfaces/native/ui_input_event.h` | 自定义输入事件构造、分发及访问接口的公开声明入口 |

建议按 `TouchTest`、`HitTestMode`、`DispatchTouchEvent`、`DispatchMouseEvent`、`OnTouchIntercept`、`PostEventManager` 和 `InputEventMonitorManager` 检索。

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic Common API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/common.d.ts` | 组件输入回调、命中测试/拦截相关公共声明入口 |
| Static Common API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/common.static.d.ets` | Static ArkTS 对应公共声明入口 |
| Dynamic Common Modifier | `<OH_ROOT>/interface/sdk-js/api/arkui/CommonModifier.d.ts` | Modifier 范式公共事件入口 |
| Static Common Modifier | `<OH_ROOT>/interface/sdk-js/api/arkui/CommonModifier.static.d.ets` | Static Modifier 公共事件入口 |
| Native 输入事件 | `interfaces/native/ui_input_event.h`、`interfaces/native/native_node.h` | Native 输入事件及节点事件注册/分发入口；按具体 API 核实公开范围 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| EventManager 测试 | `test/unittest/core/event/event_manager_test_ng.cpp` | 通用事件分发和命中结果回归 |
| 输入监控测试 | `test/unittest/core/event/input_event_monitor_manager_test_ng.cpp` | 输入监控与消费信息回归 |
| PostEvent 测试 | `test/unittest/core/manager/post_event_manager_test_ng.cpp` | 自定义投递、目标缓存和分发回归 |
| Native 输入事件测试 | `test/unittest/interfaces/ace_ui_input_event/` | 自定义输入事件与 accessor 回归 |
| Context registry | `docs/context_registry.json` | `EventDispatchIntercept` 的统一路由入口 |

### 相关 Spec

事件分发和拦截功能域：`specs/04-common-capability/04-common-events/03-event-dispatch-intercept/`（功能 ID `04-04-03`）。

| Feat | 主题 | 文件 |
|------|------|------|
| Feat-01 | 命中测试、拦截与响应链 | `Feat-01-hit-test-intercept-response-chain-spec.md` |
| Feat-02 | 触摸序列分发与传播 | `Feat-02-touch-sequence-dispatch-propagation-spec.md` |
| Feat-03 | 跨容器事件分发 | `Feat-03-cross-container-event-dispatch-spec.md` |
| Feat-04 | 自定义输入事件构造与分发 | `Feat-04-custom-input-event-construction-dispatch-spec.md` |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 节点未进入目标链 | FrameNode 响应区域、HitTestMode、GestureEventHub TouchTest 和 Feat-01 |
| 拦截结果与预期不符 | 拦截回调注册、响应链构建、命中结果枚举和 Feat-01 |
| 同一触摸序列传播异常 | EventManager 序列管理、目标缓存、消费结果和 Feat-02 |
| 子窗口或跨容器事件丢失 | 容器映射、平台入口、跨容器转发和 Feat-03 |
| 自定义事件投递不到目标 | PostEventManager 的命中、目标缓存、事件构造及 Feat-04 |
| 监控回调没有收到事件 | InputEventMonitorManager 的注册、事件类型过滤和消费信息更新 |

## 调试入口

- 从平台输入入口确认事件进入目标 PipelineContext，再观察 EventManager 的分发类型。
- 命中问题同时记录节点树、响应区域、HitTestMode、触摸测试结果和最终目标链。
- 序列问题按 pointer/touch id 追踪 DOWN、MOVE、UP/CANCEL，避免只观察单个事件。
- 跨容器和自定义投递问题应记录 containerId、目标节点与坐标转换上下文。
- 回归按问题选择 EventManager、InputEventMonitorManager、PostEventManager 或 Native 输入事件测试。

## 相关主题

- [事件基础框架](../architecture/event-base-framework.md)
- [触摸事件](touch-events.md)
- [鼠标事件](mouse-events.md)
- [手势能力](gesture-capability.md)