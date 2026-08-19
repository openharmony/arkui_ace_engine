# Touch Events Context

> 文档版本：v1.0
> 更新时间：2026-07-30
> 来源：`docs/context_registry.json` 主题 `TouchEvents`

## 定位

Touch Events 是 ArkUI 面向触摸输入的数据建模、组件回调和多点/历史采样信息能力。该主题连接平台触摸数据转换、引擎通用事件模型、NG 组件事件注册、前端回调对象以及 Native 输入事件访问接口。

本文档只提供稳定的源码、API、测试和 Spec 路由。触摸回调传播、消费语义、坐标定义、版本差异和历史采样规则应以当前源码、SDK、测试及 Spec 为准；命中测试、事件分发与手势识别的通用机制分别路由到对应主题。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| 通用触摸数据模型 | `frameworks/core/event/touch_event.h` | 触摸点、触摸事件、历史点和事件目标等基础类型入口 |
| NG 触摸事件封装 | `frameworks/core/components_ng/event/touch_event.h` | 组件侧触摸回调、TouchEventImpl 和触摸目标相关入口 |
| 前端回调对象转换 | `frameworks/bridge/declarative_frontend/engine/functions/js_touch_function.cpp` | Dynamic 前端触摸事件对象及触摸点数据转换入口 |
| 平台输入接入 | `adapter/ohos/entrance/ace_view_ohos.cpp` | OHOS 输入事件进入 AceView 和管线的入口之一 |
| 平台触摸转换 | `adapter/ohos/entrance/touch_event_convertor.cpp` | 平台 PointerEvent 到引擎触摸数据的转换入口 |
| Native 输入事件声明 | `interfaces/native/ui_input_event.h` | ArkUI_UIInputEvent 及触摸访问接口声明 |
| Native 输入事件实现 | `interfaces/native/event/ui_input_event.cpp` | Native 输入事件类型判断和触摸字段访问实现 |

按问题建议检索 `TouchEvent`、`TouchLocationInfo`、`TouchEventInfo`、`TouchEventImpl`、`ConvertTouchEvent` 和具体 SDK 回调名。

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic Common API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/common.d.ts` | 通用组件触摸回调及触摸事件类型声明 |
| Static Common API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/common.static.d.ets` | Static ArkTS 通用触摸事件声明 |
| Dynamic Common Modifier | `<OH_ROOT>/interface/sdk-js/api/arkui/CommonModifier.d.ts` | Modifier 范式公共事件入口 |
| Static Common Modifier | `<OH_ROOT>/interface/sdk-js/api/arkui/CommonModifier.static.d.ets` | Static Modifier 公共事件入口 |
| Native 输入事件 | `interfaces/native/ui_input_event.h` | Native 侧触摸事件类型、坐标、触摸点和历史数据访问入口 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 触摸事件单元测试 | `test/unittest/core/event/touch_event_test_ng.cpp` | 触摸数据模型和 NG 事件处理回归 |
| Native 输入事件测试 | `test/unittest/interfaces/ace_ui_input_event/` | ArkUI_UIInputEvent 触摸访问接口回归 |
| C API accessor 测试 | `test/unittest/capi/accessors/touch_event_accessor_test.cpp` | C API 触摸字段访问回归 |
| Context registry | `docs/context_registry.json` | `TouchEvents` 的统一路由入口 |

### 相关 Spec

触摸事件功能域：`specs/04-common-capability/04-common-events/01-touch-events/`（功能 ID `04-04-01`）。

| Feat | 主题 | 文件 |
|------|------|------|
| Feat-01 | 触摸回调与传播 | `Feat-01-touch-callback-propagation-spec.md` |
| Feat-02 | 多点触摸数据模型 | `Feat-02-touch-event-multipoint-data-model-spec.md` |
| Feat-03 | 历史采样与高级触摸信息 | `Feat-03-history-sampling-advanced-touch-info-spec.md` |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 回调未触发或传播结果异常 | Common API、NG `touch_event.h`、事件分发与拦截 KB、Feat-01 |
| 多指数量、标识或坐标异常 | 平台转换、通用 `touch_event.h`、前端对象转换、Feat-02 |
| 历史点或高级字段为空 | SDK 版本声明、平台转换、Native 输入事件实现、Feat-03 |
| ArkTS 与 Native 字段不一致 | 分别核对 SDK 类型、`js_touch_function.cpp`、`ui_input_event.h/.cpp` |
| 触摸触发了非预期手势 | GestureEventHub、识别器与手势裁决路由，不只检查触摸回调 |

## 调试入口

- 从平台 PointerEvent 转换入口确认触摸点、action、时间戳和坐标是否进入引擎。
- 从组件注册点确认触摸回调是否进入 EventHub/GestureEventHub，再检查命中测试和分发链。
- 数据字段问题同时比较通用事件模型、前端转换对象和 Native accessor，避免跨范式推断。
- 回归优先运行触摸事件单测和对应 Native/C API accessor 用例。

## 相关主题

- [事件基础框架：`docs/kb/architecture/event-base-framework.md`](../architecture/event-base-framework.md)
- [事件分发和拦截：`docs/kb/capabilities/event-dispatch-intercept.md`](event-dispatch-intercept.md)
- [手势能力：`docs/kb/capabilities/gesture-capability.md`](gesture-capability.md)