# Gesture Modifier Context

> 文档版本：v1.0
> 更新时间：2026-07-31
> 来源：`docs/context_registry.json` 主题 `GestureModifier`

## 定位

Gesture Modifier 是 ArkUI 在组件不变的情况下动态构建、替换和管理手势集合的通用扩展能力。它以 `gestureModifier`、`GestureModifier`、`UIGestureEvent` 和 GestureHandler 家族为应用入口，连接 Dynamic/Static ArkTS 前端、Native modifier 桥接、GestureEventHub 和手势识别层。

本页只维护稳定路由和已验证的能力边界。具体 API 参数、版本差异、更新时序、tag 删除语义及实现风险以当前 SDK、源码、测试和 `Func-04-05-07` Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| Dynamic 公共入口 | `frameworks/bridge/declarative_frontend/jsview/js_view_abstract.cpp` | `gestureModifier` 从组件公共属性进入 Dynamic 前端的入口 |
| Dynamic 前端对象 | `frameworks/bridge/declarative_frontend/ark_component/src/ArkComponent.ts` | UIGestureEvent、Handler 分发、应用、删除和清理的前端实现 |
| Dynamic Native Bridge | `frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_common_bridge.cpp` | 将 Handler 参数转换为 Node Modifier 调用 |
| Static hook | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/hooks/index.ets` | Static 普通组件的 gestureModifier 应用与清理入口；排查 peer hook 风险的首选位置 |
| Static UIGestureEvent | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/component/common.ets` | Static 添加、并行添加、按 tag 删除和清理入口 |
| Static Handler | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/component/gesture.ets` | Static GestureHandler 和 GestureGroupHandler 到 Gesture 对象的转换 |
| Static Accessor | `frameworks/core/interfaces/native/implementation/gesture_ops_accessor.cpp` | Static GestureOps 到内部 Gesture Modifier 的访问层 |
| Node Modifier | `frameworks/core/interfaces/native/node/node_gesture_modifier.cpp` | Gesture 创建、参数设置、节点挂载、按 tag 删除和清理的核心桥接 |
| 节点手势存储 | `frameworks/core/components_ng/event/gesture_event_hub.cpp` | Modifier Gesture、备份和 recognizer hierarchy 的权威存储与更新 |
| 组合手势 | `frameworks/core/components_ng/gestures/gesture_group.cpp` | GestureGroup 子项管理和递归 tag 操作 |
| 输入来源过滤 | `frameworks/core/components_ng/gestures/gesture_info.h`、`frameworks/core/components_ng/gestures/recognizers/gesture_recognizer.cpp` | SourceTool 配置及 TouchEvent/AxisEvent 过滤入口 |
| Public Native API | `interfaces/native/native_gesture.h` | 核对公开 recognizer 创建、节点挂载和移除能力 |
| Internal Modifier API | `frameworks/core/interfaces/arkoala/arkoala_api.h` | 前端桥接使用的内部 ArkUIGestureModifier；不得当作 Public C API 契约 |

建议检索：`JsGestureModifier`、`__gestureModifier__`、`UIGestureEvent`、`hookGestureModifier`、`AttachGesture`、`ClearModifierGesture`、`RemoveGesturesByTag`、`RemoveChildrenByTag`、`modifierGestureHierarchy_`。

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic Common API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/common.d.ts` | `gestureModifier`、`GestureModifier`、`UIGestureEvent` 及生命周期契约 |
| Dynamic Gesture API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/gesture.d.ts` | GestureHandler 家族、Group Handler、优先级、Mask、方向和事件类型 |
| Static Common API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/common.static.d.ets` | Static gestureModifier、GestureModifier 和 UIGestureEvent |
| Static Gesture API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/gesture.static.d.ets` | Static Handler、Group Handler 和相关枚举 |
| Common Modifier API | `<OH_ROOT>/interface/sdk-js/api/arkui/CommonModifier.d.ts`、`<OH_ROOT>/interface/sdk-js/api/arkui/CommonModifier.static.d.ets` | 通用 Modifier 基类；确认 gestureModifier 是否由独立 Modifier 文件声明 |
| Public Native Gesture API | `interfaces/native/native_gesture.h` | 对外 Native recognizer 接口及能力边界 |

Dynamic 能力从 API 12 开始，后续 Handler 能力按 SDK `@since` 演进；Static 对应能力从 API 23 开始。排查版本问题时应分别读取 Dynamic 和 Static 声明，不能用一套声明推导另一套前端。

### 前端解析实现路径

| 路径 | 入口 | 追踪方向 |
|------|------|----------|
| Dynamic 组件属性 | `JSViewAbstract::JsGestureModifier` | 全局 modifier 函数 → ArkComponent → UINativeModule CommonBridge → Node Gesture Modifier |
| Dynamic Handler | `UIGestureEvent` in `ArkComponent.ts` | Handler 类型分发 → create/add gesture bridge → GestureEventHub |
| Static 普通组件 | `hookGestureModifier(ArkCommonMethodComponent, ...)` | UIGestureEvent → GestureOps → Static Accessor → Node Gesture Modifier |
| Static AttributeModifier | 生成的 `CommonMethodModifier.ets` | peer hook → handwritten hooks；用于定位当前实现偏差 |
| Native Public | `ArkUI_NativeGestureAPI_1` | recognizer create → add/remove gesture to node；与 ArkTS Modifier 管理面分开核对 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| GestureEventHub Modifier | `test/unittest/core/event/gesture_event_hub_test_ng_property_config.cpp` | Attach、Remove、Clear、嵌套 Group tag 删除 |
| tag 边界 | `test/unittest/core/event/gesture_event_hub_test_two_ng.cpp`、`gesture_event_hub_test_ng_two_property_config.cpp` | 不存在 tag 和顶层 tag 删除 |
| SourceTool 过滤 | `test/unittest/core/gestures/gesture_recognizer_test_ng.cpp` | allowedTypes、TouchEvent、AxisEvent 和 Cancel 路径 |
| Native Gesture | `test/unittest/interfaces/ace_gesture/` | Public Native Gesture 创建、挂载和识别器接口 |
| Static Accessor | `test/unittest/capi/accessors/gesture_event_accessor_test.cpp` | Static 生成访问器与 GestureEvent 数据通道 |

当前 Static AttributeModifier peer hook、Static 嵌套 GestureGroupHandler 和活动手势期间更新的专项覆盖，应从上述 Static hook、生成代码和 EventHub 测试入口继续核验。

### 相关 Spec

功能域：`specs/04-common-capability/05-custom-extension/07-gesture-modifier/`（FuncID `04-05-07`）。

| 文档 | 路径 | 用途 |
|------|------|------|
| Shared Design | `specs/04-common-capability/05-custom-extension/07-gesture-modifier/design.md` | 架构、ADR、多前端差异、Native 边界和风险 |
| Feat-01 | `specs/04-common-capability/05-custom-extension/07-gesture-modifier/Feat-01-gesture-modifier-dynamic-configuration-spec.md` | AC、规则、API 12～23 演进和验证映射 |

## 兼容性与风险定位

| 主题 | 优先核对 |
|------|----------|
| Dynamic 与 Static 参数或版本不一致 | Dynamic/Static Common 和 Gesture SDK 声明；Feat-01 兼容性章节 |
| 活动手势更新何时生效 | Dynamic SDK 的 GestureModifier 契约、ArkComponent、GestureEventHub touch-test/hierarchy 路径 |
| Static gestureModifier 未生效或抛错 | handwritten hooks、生成的 CommonMethodModifier、Static UIGestureEvent |
| Native 缺少 ArkTS 等价管理能力 | `interfaces/native/native_gesture.h` 与内部 `arkoala_api.h` 对照 |
| 嵌套 Group 或 tag 删除异常 | GestureEventHub、GestureGroup 和对应 EventHub 测试 |
| allowedTypes 跨触摸/轴输入异常 | GestureInfo、GestureRecognizer 和 recognizer 测试 |

不要根据内部 `ArkUIGestureModifier` 函数表推断 Public Native API 已开放相同能力；Public 契约必须以 `interfaces/native/native_gesture.h` 为准。

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| `applyGesture` 未执行 | Dynamic `JsGestureModifier`/`__gestureModifier__` 或 Static `hookGestureModifier` |
| 条件变化后仍触发旧手势 | SDK 生命周期说明、GestureEventHub 当前 touch result 和 hierarchy 更新 |
| 传入空值后手势未清除 | 分别核对 Dynamic 与 Static `gestureModifier` 签名和入口处理 |
| `addParallelGesture` 竞争关系异常 | UIGestureEvent 添加入口、Node Modifier priority、GestureEventHub hierarchy |
| `removeGestureByTag` 未删除组内手势 | GestureEventHub 顶层遍历、GestureGroup 递归删除及 tag 测试 |
| 空 `allowedTypes` 或设备来源过滤异常 | SourceTool 位图生成、Recognizer Touch/Axis 过滤路径 |
| Static AttributeModifier 抛出未实现异常 | 生成的 CommonMethodModifier 与 peer overload hook |
| Native 无法按 tag 删除或清空 | Public Native Gesture 头文件；确认是否仅存在内部桥接接口 |

## 调试入口

- 先确认目标 FrameNode 是否进入正确的 Dynamic 或 Static `gestureModifier` 入口。
- 在前端侧确认 `UIGestureEvent` 是否绑定到正确节点/PeerNode，以及 `applyGesture` 是否被同步调用。
- 对比 GestureEventHub 中普通手势集合与 Modifier 手势集合，避免把 `gesture()` 路径与 `gestureModifier()` 路径混淆。
- tag 问题同时检查顶层 Gesture 和嵌套 GestureGroup；重复 tag 不是唯一标识。
- 更新时序问题记录当前触摸序列已经收集的 recognizer 与更新后的 modifier hierarchy，确认问题发生在当前轮还是下一轮。
- 输入设备问题记录 SourceTool、TouchEvent/AxisEvent 类型和 Handler 的 allowedTypes 配置。
- Static 问题区分普通组件 hook 和 AttributeModifier peer hook；两条路径不能相互替代验证。
- Native 问题先确认调用的是 Public `native_gesture.h`，还是框架内部 ArkUIGestureModifier。

## 相关主题

- [手势识别、组合、裁决和拦截](gesture-capability.md)
- [事件分发和命中测试](event-dispatch-intercept.md)
- [事件框架](../architecture/event-base-framework.md)
- ArkUI SDK/API 范式：`docs/api/ArkUI_API_Paradigm_Knowledge_Base_CN.md`
- Common Modifier SDK：`<OH_ROOT>/interface/sdk-js/api/arkui/CommonModifier.d.ts`