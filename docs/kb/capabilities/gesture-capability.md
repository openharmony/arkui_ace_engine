# Gesture Capability Context

> 文档版本：v1.0
> 更新时间：2026-07-30
> 来源：`docs/context_registry.json` 主题 `GestureCapability`

## 定位

Gesture Capability 是 ArkUI 将触摸序列识别为点击、长按、拖动、缩放、旋转、滑动等手势，并支持手势组合、裁决、拦截和识别器恢复的公共能力。它连接应用侧 Gesture API、前端手势声明、NG GestureEventHub、各类识别器和 GestureReferee。

本文档只维护稳定路由，不复制具体手势的参数矩阵和状态机。每类手势、组合模式、裁决规则、拦截回调和恢复条件应以当前 SDK、源码、测试及 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| 手势模型与基础设施 | `frameworks/core/components_ng/gestures/` | Gesture、GestureInfo、事件数据、组装和裁决基础入口 |
| 手势识别器 | `frameworks/core/components_ng/gestures/recognizers/` | 点击、长按、拖动、缩放、旋转、滑动及组合识别器入口 |
| 组件手势管理 | `frameworks/core/components_ng/event/gesture_event_hub.cpp` | 手势注册、触摸测试、响应链、拦截和识别器组织入口 |
| 手势裁决 | `frameworks/core/components_ng/gestures/gesture_referee.cpp` | 竞争作用域、裁决和状态处理入口 |
| 响应控制 | `frameworks/core/components_ng/event/response_ctrl.cpp` | 响应控制和优先级相关入口 |
| Dynamic 手势前端 | `frameworks/bridge/declarative_frontend/jsview/js_gesture.h`、`frameworks/bridge/declarative_frontend/jsview/js_gesture.cpp` | Dynamic ArkTS/JS 手势声明解析入口 |
| Native Gesture API | `interfaces/native/native_gesture.h` | Native 手势创建、组合、回调和识别器接口声明 |
| Native gesture modifier | `frameworks/core/interfaces/native/node/node_gesture_modifier.cpp` | Node C API 到 NG 手势对象的桥接入口 |

建议按具体识别器名、`GestureEventHub`、`GestureReferee`、`GestureGroup`、`OnGestureJudgeBegin`、`ShouldBuiltInRecognizerParallelWith` 和 `Recognizer` 检索。

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic Gesture API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/gesture.d.ts` | 手势类型、组合、事件和回调声明 |
| Static Gesture API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/gesture.static.d.ets` | Static ArkTS 手势声明 |
| Dynamic Common API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/common.d.ts` | 组件绑定手势、手势判断和拦截相关入口 |
| Static Common API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/common.static.d.ets` | Static 组件手势绑定入口 |
| Native Gesture API | `interfaces/native/native_gesture.h`、`interfaces/native/native_node.h` | Native 手势对象、回调与节点绑定入口 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 手势与识别器测试 | `test/unittest/core/gestures/` | 各类识别器、组合、裁决和状态回归 |
| GestureEventHub 测试 | `test/unittest/core/event/gesture_event_hub_test_*.cpp` | 组件绑定、命中、拦截和响应链回归 |
| Native Gesture 测试 | `test/unittest/interfaces/ace_gesture/` | Native 手势接口回归 |
| Context registry | `docs/context_registry.json` | `GestureCapability` 的统一路由入口 |

### 相关 Spec

手势能力功能域：`specs/04-common-capability/04-common-events/06-gesture-capability/`（功能 ID `04-04-06`）。

| Feat | 主题 | 文件 |
|------|------|------|
| Feat-01 | 基础手势 | `Feat-01-basic-gestures-spec.md` |
| Feat-02 | 手势组合 | `Feat-02-gesture-group-spec.md` |
| Feat-03 | 手势裁决 | `Feat-03-gesture-referee-spec.md` |
| Feat-04 | 手势拦截 | `Feat-04-gesture-intercept-spec.md` |
| Feat-05 | 手势识别器恢复 | `Feat-05-gesture-recognizer-recovery-spec.md` |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 基础手势不触发或参数异常 | Gesture API、对应 recognizer、GestureEventHub 和 Feat-01 |
| 手势组合结果异常 | 组合识别器、GestureGroup 模式、成员状态和 Feat-02 |
| 父子/兄弟手势竞争异常 | GestureReferee、响应控制、竞争作用域和 Feat-03 |
| 拦截或并行判断未生效 | Common API 注册、GestureEventHub 回调入口和 Feat-04 |
| 节点更新后识别器状态丢失 | 识别器重建/恢复路径、节点手势更新和 Feat-05 |
| Native 与 ArkTS 行为不一致 | 分别核对 `native_gesture.h`/modifier 与 Dynamic/Static SDK 声明 |

## 调试入口

- 先确认触摸序列是否命中目标节点并生成对应 recognizer，再观察 recognizer 状态迁移。
- 竞争问题记录同一 GestureScope 内全部识别器、优先级、组合关系和裁决结果。
- 拦截问题区分命中测试阶段、裁决阶段和回调阶段，按对应 Feat 路由。
- 恢复问题比较节点更新前后的手势配置、识别器类型和恢复匹配信息。
- 回归优先运行具体 recognizer、GestureReferee、GestureEventHub 或 Native Gesture 定向用例。

## 相关主题

- [触摸事件](touch-events.md)
- [事件分发和拦截](event-dispatch-intercept.md)
- [事件基础框架](../architecture/event-base-framework.md)