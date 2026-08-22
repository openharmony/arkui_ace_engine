# Event Base Framework Context

> 文档版本：v1.0
> 更新时间：2026-07-30
> 来源：`docs/context_registry.json` 主题 `EventBaseFramework`

## 定位

Event Base Framework 是 ArkUI 输入事件从平台接入、通用数据建模、命中测试和事件目标链，到组件 EventHub、输入分发、手势裁决、监控与诊断的内部基础框架。它为触摸、鼠标、轴、按键、组件组合键和手势能力提供共享机制，但不替代各事件类型的公共能力规格。

本文档用于架构路由。具体 API 行为、传播/消费规则、手势状态机和兼容性应进入对应能力 KB、源码、测试及 Spec 核实。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| 通用事件管理 | `frameworks/core/common/event_manager.h`、`frameworks/core/common/event_manager.cpp` | 输入事件命中结果管理和分发总入口 |
| 按键事件管理 | `frameworks/core/common/key_event_manager.h`、`frameworks/core/common/key_event_manager.cpp` | 焦点按键分发和组件快捷键管理入口 |
| 输入事件监控 | `frameworks/core/common/input_event_monitor_manager.h`、`frameworks/core/common/input_event_monitor_manager.cpp` | 输入监控、消费信息和回调管理入口 |
| 事件诊断 | `frameworks/core/common/event_dump.h`、`frameworks/core/common/event_dump.cpp` | 事件树、目标链或事件现场的诊断输出入口 |
| 组件事件基座 | `frameworks/core/components_ng/event/event_hub.h`、`frameworks/core/components_ng/event/event_hub.cpp` | FrameNode 组件事件注册、状态与基础 EventHub 能力 |
| 输入事件 Hub | `frameworks/core/components_ng/event/input_event_hub.h`、`frameworks/core/components_ng/event/input_event_hub.cpp` | 鼠标、hover、轴和输入目标管理入口 |
| 手势事件 Hub | `frameworks/core/components_ng/event/gesture_event_hub.h`、`frameworks/core/components_ng/event/gesture_event_hub.cpp` | 触摸目标、手势、命中测试、响应链和拦截入口 |
| 手势裁决框架 | `frameworks/core/components_ng/gestures/gesture_referee.h`、`frameworks/core/components_ng/gestures/gesture_referee.cpp` | 手势竞争作用域和裁决入口 |
| 输入数据模型 | `frameworks/core/event/touch_event.h`、`frameworks/core/event/mouse_event.h`、`frameworks/core/event/axis_event.h`、`frameworks/core/event/key_event.h` | 各类输入事件的通用基础类型 |
| 平台输入接入 | `adapter/ohos/entrance/ace_view_ohos.cpp` | OHOS 输入事件进入 ArkUI Pipeline 的主要适配入口之一 |

按框架阶段建议检索：

| 阶段 | 优先检索词 |
|------|------------|
| 平台接入与转换 | `AceViewOhos`、`ProcessTouchEvent`、`ProcessMouseEvent`、`ProcessKeyEvent` |
| 命中测试与目标链 | `TouchTest`、`HitTestMode`、`TouchTestResult`、`EventTarget` |
| 事件分发 | `EventManager`、`DispatchTouchEvent`、`DispatchMouseEvent`、`DispatchAxisEvent` |
| 组件事件注册 | `EventHub`、`InputEventHub`、`GestureEventHub` |
| 手势裁决 | `GestureReferee`、`GestureScope`、`Recognizer` |
| 监控与诊断 | `InputEventMonitorManager`、`EventDump`、`event tree` |

### API 入口

Event Base Framework 是内部机制，没有单一独立 SDK API。公共事件从下列声明进入，再由前端桥接和组件 EventHub 注册；具体字段与版本应转到对应事件能力核实。

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic Common API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/common.d.ts` | 触摸、按键、鼠标、hover、快捷键和手势绑定等公共入口 |
| Static Common API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/common.static.d.ets` | Static ArkTS 公共事件入口 |
| Dynamic Gesture API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/gesture.d.ts` | Dynamic 手势类型与组合入口 |
| Static Gesture API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/gesture.static.d.ets` | Static 手势类型与组合入口 |
| Native 输入事件 | `interfaces/native/ui_input_event.h`、`interfaces/native/native_key_event.h` | Native 输入和按键事件入口 |
| Native 手势与节点 | `interfaces/native/native_gesture.h`、`interfaces/native/native_node.h` | Native 手势及节点事件注册入口 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 通用事件测试 | `test/unittest/core/event/` | EventManager、EventHub、触摸、鼠标、轴事件、监控与诊断回归 |
| 手势框架测试 | `test/unittest/core/gestures/` | 识别器、组合、裁决和手势基础设施回归 |
| 按键管理测试 | `test/unittest/core/common/key_event_manager/` | 按键分发和组件快捷键管理回归 |
| Native 输入测试 | `test/unittest/interfaces/ace_ui_input_event/`、`test/unittest/interfaces/ace_key_event/`、`test/unittest/interfaces/ace_gesture/` | Native 事件和手势接口回归 |
| Context registry | `docs/context_registry.json` | `EventBaseFramework` 的统一路由入口 |

### 相关 Spec

事件基础框架功能域：`specs/03-engine-framework/04-event-framework/01-event-base-framework/`（功能 ID `03-04-01`）。

| Feat | 主题 | 文件 |
|------|------|------|
| Feat-01 | 事件模型与 EventHub | `Feat-01-event-model-and-event-hub-spec.md` |
| Feat-02 | 命中测试与事件目标链 | `Feat-02-hit-test-and-event-target-chain-spec.md` |
| Feat-03 | 输入分发与采样管线 | `Feat-03-input-dispatch-and-sampling-pipeline-spec.md` |
| Feat-04 | 手势裁决与响应控制 | `Feat-04-gesture-referee-and-response-control-spec.md` |
| Feat-05 | 事件诊断与检查 | `Feat-05-event-diagnostics-and-inspection-spec.md` |

架构设计入口：`specs/03-engine-framework/04-event-framework/01-event-base-framework/design.md`。

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 平台事件没有进入组件树 | AceView OHOS 入口、事件转换、PipelineContext/EventManager 和 Feat-03 |
| 命中节点或目标链异常 | FrameNode/GestureEventHub TouchTest、响应区域、HitTestMode 和 Feat-02 |
| EventHub 已注册但回调未执行 | 对应 Hub、目标链、EventManager 分发及具体事件能力 KB |
| 采样或历史事件异常 | 输入数据模型、平台转换、EventManager 采样路径和 Feat-03 |
| 手势竞争或响应控制异常 | GestureEventHub、GestureReferee、ResponseCtrl 和 Feat-04 |
| 事件现场难以定位 | EventDump、事件树/目标链诊断、输入监控和 Feat-05 |
| API 字段或回调语义不明确 | 转到触摸、按键、鼠标、手势或组件组合键 KB，并核对 SDK/Spec |

## 调试入口

- 按“平台输入 → 通用事件模型 → 命中测试 → 目标链 → EventManager → EventHub/Recognizer → 应用回调”分段确认事件位置。
- 记录 event id、pointer id、时间戳、source/type、containerId 和目标节点，保持同一事件链上下文一致。
- 命中与传播问题优先使用事件树/目标链诊断，手势问题再观察 recognizer 状态和裁决结果。
- 多模态问题分别进入对应 EventHub 和数据模型，不用触摸路径推断鼠标、轴或按键行为。
- 回归测试从故障阶段对应的最小单测开始，再扩展到具体输入类型测试。

## 相关主题

- [触摸事件：[docs/kb/capabilities/touch-events.md](../capabilities/touch-events.md)](../capabilities/touch-events.md)
- [按键事件：[docs/kb/capabilities/key-events.md](../capabilities/key-events.md)](../capabilities/key-events.md)
- [事件分发和拦截：[docs/kb/capabilities/event-dispatch-intercept.md](../capabilities/event-dispatch-intercept.md)](../capabilities/event-dispatch-intercept.md)
- [组件组合键：[docs/kb/capabilities/component-shortcuts.md](../capabilities/component-shortcuts.md)](../capabilities/component-shortcuts.md)
- [鼠标事件：[docs/kb/capabilities/mouse-events.md](../capabilities/mouse-events.md)](../capabilities/mouse-events.md)
- [手势能力：[docs/kb/capabilities/gesture-capability.md](../capabilities/gesture-capability.md)](../capabilities/gesture-capability.md)