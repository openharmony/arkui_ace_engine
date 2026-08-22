# Mouse Events Context

> 文档版本：v1.0
> 更新时间：2026-07-30
> 来源：`docs/context_registry.json` 主题 `MouseEvents`

## 定位

Mouse Events 是 ArkUI 鼠标输入的数据建模、组件鼠标/悬停回调、命中分发以及鼠标指针样式与自定义光标能力。根据当前功能域划分，鼠标指针请求继续由鼠标事件 Spec 和本 KB 承载；样式多态等通用样式属性不在此处扩展。

本文档只维护稳定路由。鼠标按键、action、坐标、hover 状态、传播消费和光标版本差异应以当前 SDK、源码、测试及 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| 通用鼠标数据模型 | `frameworks/core/event/mouse_event.h` | MouseEvent、按键、action、坐标和目标数据入口 |
| NG 鼠标/悬停注册 | `frameworks/core/components_ng/event/input_event_hub.cpp` | 组件鼠标、hover 事件和输入目标管理入口 |
| 前端回调对象转换 | `frameworks/bridge/declarative_frontend/engine/functions/js_mouse_function.cpp` | Dynamic 前端 MouseEvent 对象转换入口 |
| 平台输入接入 | `adapter/ohos/entrance/ace_view_ohos.cpp` | OHOS 鼠标事件进入 AceView 和管线的入口之一 |
| Native 输入事件 | `interfaces/native/ui_input_event.h`、`interfaces/native/event/ui_input_event.cpp` | Native 鼠标事件声明与字段访问实现 |
| 光标抽象与管理 | `frameworks/base/mousestyle/` | MouseStyle 接口、光标样式管理和相关基础定义 |
| OHOS 光标适配 | `adapter/ohos/osal/mouse_style_ohos.cpp` | 引擎光标请求到平台鼠标样式能力的适配入口 |

建议按 `MouseEvent`、`InputEventHub`、`MouseStyle`、`SetMouseStyle`、`onMouse`、`onHover` 和具体光标 API 名检索。

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic Common API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/common.d.ts` | 鼠标、hover、光标样式和自定义光标相关声明入口 |
| Static Common API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/common.static.d.ets` | Static ArkTS 鼠标与光标相关声明入口 |
| Dynamic Common Modifier | `<OH_ROOT>/interface/sdk-js/api/arkui/CommonModifier.d.ts` | Dynamic Modifier 鼠标/光标入口 |
| Static Common Modifier | `<OH_ROOT>/interface/sdk-js/api/arkui/CommonModifier.static.d.ets` | Static Modifier 鼠标/光标入口 |
| Native 输入事件 | `interfaces/native/ui_input_event.h` | Native 鼠标事件类型及字段访问入口 |

### 平台依赖入口

| 依赖方向 | 本仓入口 | 说明 |
|----------|----------|------|
| OHOS 输入系统 | `adapter/ohos/entrance/ace_view_ohos.cpp` | 接收平台 PointerEvent 并转入 ArkUI 事件管线 |
| OHOS 鼠标样式 | `adapter/ohos/osal/mouse_style_ohos.cpp` | 向平台请求系统光标样式或自定义光标；平台能力边界需结合对应系统接口核实 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| InputEventHub 测试 | `test/unittest/core/event/input_event_hub_test_ng.cpp` | 鼠标/hover 注册和输入目标回归 |
| 鼠标分发测试 | `test/unittest/core/event/event_manager_dispatch_mouse_hover_event_ng.cpp` | 鼠标与 hover 分发回归 |
| 光标管理测试 | `test/unittest/core/event/mouse_style_manager_test_ng.cpp` | 鼠标样式管理回归 |
| C API accessor 测试 | `test/unittest/capi/accessors/mouse_event_accessor_test.cpp` | Native 鼠标字段访问回归 |
| Context registry | `docs/context_registry.json` | `MouseEvents` 的统一路由入口 |

### 相关 Spec

鼠标事件功能域：`specs/04-common-capability/04-common-events/05-mouse-events/`（功能 ID `04-04-05`）。

| Feat | 主题 | 文件 |
|------|------|------|
| Feat-01 | 鼠标事件注册、命中与分发 | `Feat-01-mouse-event-registration-hit-test-dispatch-spec.md` |
| Feat-02 | 鼠标事件数据模型与版本演进 | `Feat-02-mouse-event-data-model-version-evolution-spec.md` |
| Feat-04 | 鼠标指针样式与自定义光标 | `Feat-04-mouse-cursor-style-custom-cursor-spec.md` |

当前目录未见 Feat-03 实体规格文件；以目录中的实际文件为准，不推测其主题或状态。

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| onMouse/onHover 未触发 | Common API、InputEventHub、EventManager 鼠标分发和 Feat-01 |
| 按键、action 或坐标字段异常 | 平台输入、`mouse_event.h`、前端转换、Native accessor 和 Feat-02 |
| hover 进入/退出状态异常 | 命中测试、hover 节点缓存、鼠标分发测试和 Feat-01 |
| cursor 设置未生效 | SDK 声明、MouseStyle 管理、OHOS 适配和 Feat-04 |
| 自定义光标显示异常 | 资源/像素数据入口、尺寸热点参数、平台适配能力和 Feat-04 |
| 样式属性的多态解析问题 | 转到对应通用样式属性主题；本 KB 仅承载鼠标指针请求链路 |

## 调试入口

- 从平台 PointerEvent 确认 source、action、button、坐标和时间戳进入引擎。
- 回调问题检查 InputEventHub 注册、命中节点和 EventManager 分发结果。
- hover 问题按移动轨迹观察上一次/当前 hover 节点集合变化。
- 光标问题同时记录组件请求、MouseStyleManager 状态和平台适配返回结果。

## 相关主题

- [事件分发和拦截：[docs/kb/capabilities/event-dispatch-intercept.md](event-dispatch-intercept.md)](event-dispatch-intercept.md)
- [事件基础框架：[docs/kb/architecture/event-base-framework.md](../architecture/event-base-framework.md)](../architecture/event-base-framework.md)
- [触摸事件：[docs/kb/capabilities/touch-events.md](touch-events.md)](touch-events.md)