# Interaction Normalization Context

> 文档版本：v1.0
> 更新时间：2026-07-31
> 来源：`docs/context_registry.json` 主题 `InteractionNormalization`

## 定位

交互归一化是 ArkUI 将触控、鼠标、触控板、滚轮和按键等底层输入转换为统一点击、滑动、平移、缩放与旋转交互语义的公共能力。它覆盖平台输入接入、事件模型转换、手势识别器汇聚以及 ArkTS/Native 输入事件出口；具体组件如何消费交互结果，仍由对应组件实现和 Spec 约束。

本文档只提供源码、SDK/API、测试和 Spec 路由。输入源支持范围、事件字段、识别阈值、冲突仲裁与版本差异，应继续查阅当前 SDK 声明、实现、测试及 `04-04-11` Spec。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| OHOS 输入接入 | `adapter/ohos/entrance/ace_view_ohos.cpp` | 接收平台侧触摸、鼠标、轴和按键输入，并分派到引擎事件通路 |
| MMI 事件转换 | `adapter/ohos/entrance/mmi_event_convertor.cpp` | 将 MMI 输入转换为 ArkUI 内部事件模型 |
| 触摸事件模型 | `frameworks/core/event/touch_event.h` | 触点、工具类型、来源设备及触摸事件字段 |
| 轴事件模型 | `frameworks/core/event/axis_event.h` | 鼠标滚轮、触控板等轴输入的统一事件表达 |
| 手势事件模型 | `frameworks/core/gestures/gesture_event.h` | 点击、平移、缩放、旋转等识别结果的公共载体 |
| 点击事件入口 | `frameworks/core/components_ng/event/click_event.cpp` | 点击事件对象与回调触发入口 |
| 组件事件汇聚 | `frameworks/core/components_ng/event/gesture_event_hub.cpp` | 组件手势注册、点击汇聚和识别器组织 |
| 按键点击适配 | `frameworks/core/components_ng/event/focus_event_handler.cpp` | 焦点组件按键意图到点击交互的适配入口 |
| 识别器公共基类 | `frameworks/core/components_ng/gestures/recognizers/gesture_recognizer.cpp` | 手势识别、仲裁和输入事件处理的公共基础 |
| 点击识别器 | `frameworks/core/components_ng/gestures/recognizers/click_recognizer.cpp` | 触控、鼠标等输入形成点击语义的识别入口 |
| 平移与滑动识别器 | `frameworks/core/components_ng/gestures/recognizers/pan_recognizer.cpp`、`frameworks/core/components_ng/gestures/recognizers/swipe_recognizer.cpp` | 位移、速度和方向等滑动/平移语义的识别入口 |
| 缩放与旋转识别器 | `frameworks/core/components_ng/gestures/recognizers/pinch_recognizer.cpp`、`frameworks/core/components_ng/gestures/recognizers/rotation_recognizer.cpp` | 多点或轴输入形成缩放、旋转语义的识别入口 |
| Native 手势实现 | `interfaces/native/node/gesture_impl.cpp` | Native 手势对象创建、配置与节点绑定 |
| Native 输入事件实现 | `interfaces/native/event/ui_input_event.cpp` | 统一 Native 输入事件查询与类型分派 |
| Native 节点事件出口 | `frameworks/core/interfaces/native/node/node_common_modifier.cpp` | 节点公共事件注册及事件数据转换入口 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic 公共事件 API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/common.d.ts` | 公共点击和组件事件声明 |
| Dynamic 手势 API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/gesture.d.ts` | 点击、平移、滑动、捏合和旋转手势声明 |
| Static 公共事件 API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/common.static.d.ets` | Static ArkTS 公共点击和组件事件契约 |
| Static 手势 API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/gesture.static.d.ets` | Static ArkTS 手势契约 |
| Native Node API | `interfaces/native/native_node.h` | 节点公共事件与输入事件类型入口 |
| Native Gesture API | `interfaces/native/native_gesture.h` | Native 手势创建、配置和回调接口 |
| Native Input Event API | `interfaces/native/ui_input_event.h` | Native 输入事件分类及字段查询接口 |

### 外部依赖入口

| 依赖方向 | 本仓入口 | 外部仓路径 | 外部目标 | 说明 |
|----------|----------|-----------|----------|------|
| 多模输入 | `adapter/ohos/entrance/ace_view_ohos.cpp`、`adapter/ohos/entrance/mmi_event_convertor.cpp` | `<OH_ROOT>/foundation/multimodalinput/input/` | `input:libmmi-client` | 提供触摸、鼠标、触控板、滚轮和按键等平台输入事件 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 点击识别 | `test/unittest/core/gestures/click_recognizer_test_ng.cpp` | 多类输入形成点击语义及识别状态验证 |
| 平移识别 | `test/unittest/core/gestures/pan_recognizer_test_ng.cpp` | 触控等输入的平移识别验证 |
| 轴输入平移 | `test/unittest/core/gestures/pan_recognizer_axis_base_test_ng.cpp` | 轴输入参与平移手势的路径验证 |
| 滑动识别 | `test/unittest/core/gestures/swipe_recognizer_test_ng.cpp` | 滑动速度、方向及识别状态验证 |
| 缩放识别 | `test/unittest/core/gestures/pinch_recognizer_test_ng.cpp` | 捏合和轴输入缩放路径验证 |
| 旋转识别 | `test/unittest/core/gestures/rotation_recognizer_test_ng.cpp` | 旋转手势识别验证 |
| 识别器基础设施 | `test/unittest/core/gestures/gesture_recognizer_test_ng.cpp` | 公共识别、仲裁和事件处理验证 |
| 组件事件汇聚 | `test/unittest/core/event/gesture_event_hub_test_ng.cpp` | 手势注册、点击汇聚和组件事件分派验证 |
| 按键点击适配 | `test/unittest/core/event/focus_event_handler_test_ng.cpp` | 按键意图转换为点击交互的验证 |
| Native Gesture | `test/unittest/interfaces/ace_gesture/` | Native 手势接口和实现验证 |
| Native Input Event | `test/unittest/interfaces/ace_ui_input_event/` | Native 输入事件类型及字段读取验证 |

### 相关 Spec

功能域：`specs/04-common-capability/04-common-events/11-interaction-normalization/`（功能 ID `04-04-11`）。

| 文档 | 稳定路径 | 覆盖范围 |
|------|----------|----------|
| 设计文档 | `specs/04-common-capability/04-common-events/11-interaction-normalization/design.md` | 输入归一化架构、模块边界和多范式出口 |
| Feat-01 | `specs/04-common-capability/04-common-events/11-interaction-normalization/Feat-01-key-intention-normalization-spec.md` | 同功能域既有的按键意图归一化主题 |
| Feat-02 | `specs/04-common-capability/04-common-events/11-interaction-normalization/Feat-02-multi-source-click-interaction-normalization-spec.md` | 多源点击交互归一化 |
| Feat-03 | `specs/04-common-capability/04-common-events/11-interaction-normalization/Feat-03-multi-source-slide-pan-normalization-spec.md` | 多源滑动与平移归一化 |
| Feat-04 | `specs/04-common-capability/04-common-events/11-interaction-normalization/Feat-04-multi-source-scale-rotation-normalization-spec.md` | 多源缩放与旋转归一化 |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 相同点击 API 在触控、鼠标或按键下结果不一致 | `ace_view_ohos.cpp`、`mmi_event_convertor.cpp`、`click_recognizer.cpp`、`focus_event_handler.cpp` 和 Feat-01/02 |
| 鼠标滚轮、触控板或触控无法形成预期滑动/平移 | `axis_event.h`、`pan_recognizer.cpp`、`swipe_recognizer.cpp` 和 Feat-03 |
| 触控板或多点触控无法形成预期缩放/旋转 | `axis_event.h`、`pinch_recognizer.cpp`、`rotation_recognizer.cpp` 和 Feat-04 |
| 手势冲突或识别状态异常 | `gesture_recognizer.cpp`、`gesture_event_hub.cpp` 及对应识别器测试 |
| ArkTS 与 Native 接口观察到的事件字段不一致 | SDK 声明、`gesture_event.h`、`ui_input_event.cpp`、`node_common_modifier.cpp` |
| Previewer 与 OHOS 真机输入路径不一致 | `docs/kb/architecture/preview-platform-adaptation.md` 和对应平台输入适配实现 |

## 调试入口

- 平台输入检索：`AceViewOhos`、`MMI::PointerEvent`、`SourceType`、`SourceTool`。
- 点击链路检索：`ClickEvent`、`ClickRecognizer`、`GestureEventHub`、`FocusEventHandler`。
- 滑动链路检索：`AxisEvent`、`PanRecognizer`、`SwipeRecognizer`、`GestureEvent`。
- 缩放旋转检索：`PinchRecognizer`、`RotationRecognizer`、`scale`、`angle`。
- Native 出口检索：`ArkUI_UIInputEvent`、`ArkUI_GestureRecognizer` 和节点公共事件枚举。

## 相关主题

- 滚动公共能力：`docs/kb/capabilities/scroll-common-capability.md`。滚动容器的摩擦、惯性、回弹和嵌套滚动不属于本主题。
- 预览器平台适配：`docs/kb/architecture/preview-platform-adaptation.md`。用于定位 Previewer 与 OHOS 输入接入差异。
- 历史手势知识库：`docs/common/interaction/Gesture_Knowledge_Base_CN.md`。仅作为旧入口线索，行为事实仍以当前实现和 Spec 为准。
