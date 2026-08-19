# Key Events Context

> 文档版本：v1.0
> 更新时间：2026-07-30
> 来源：`docs/context_registry.json` 主题 `KeyEvents`

## 定位

Key Events 是 ArkUI 的按键数据模型、组件按键回调、自定义分发和 Pre-IME 处理能力。该主题覆盖平台按键进入引擎后的事件表示、焦点节点分发、前端事件对象转换及 Native KeyEvent 接口。

本文档只维护稳定路由。按键码、修饰键、消费结果、焦点规则、Pre-IME 与自定义分发语义应回到当前 SDK、源码、测试和 Spec 核实。组件组合快捷键有独立功能 ID 和知识库，不在本页混写。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| 通用按键数据模型 | `frameworks/core/event/key_event.h` | KeyEvent、按键动作、按键码和修饰键辅助逻辑入口 |
| 按键分发管理 | `frameworks/core/common/key_event_manager.h`、`frameworks/core/common/key_event_manager.cpp` | 焦点分发、快捷键处理和按键事件管理入口 |
| 前端回调对象转换 | `frameworks/bridge/declarative_frontend/engine/functions/js_key_function.cpp` | Dynamic 前端 KeyEvent 对象转换与回调入口 |
| 平台输入接入 | `adapter/ohos/entrance/ace_view_ohos.cpp` | OHOS 按键输入进入 AceView 和管线的入口之一 |
| Native KeyEvent 声明 | `interfaces/native/native_key_event.h` | Native 按键事件公开接口 |
| Native KeyEvent 实现 | `interfaces/native/event/key_event_impl.cpp` | Native KeyEvent 对象访问实现 |

建议按 `KeyEvent`、`KeyEventManager`、`OnKeyEvent`、`OnPreIme`、`DispatchKeyEvent` 和具体 SDK 回调名检索。

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic Common API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/common.d.ts` | 通用组件按键、Pre-IME 和自定义分发相关声明 |
| Static Common API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/common.static.d.ets` | Static ArkTS 按键事件声明 |
| Dynamic Common Modifier | `<OH_ROOT>/interface/sdk-js/api/arkui/CommonModifier.d.ts` | Modifier 范式公共按键事件入口 |
| Static Common Modifier | `<OH_ROOT>/interface/sdk-js/api/arkui/CommonModifier.static.d.ets` | Static Modifier 公共按键事件入口 |
| Native KeyEvent | `interfaces/native/native_key_event.h` | Native 按键事件对象及字段访问入口 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 按键事件单元测试 | `test/unittest/core/event/key_event_test_ng.cpp` | KeyEvent 数据与基础处理回归 |
| 按键管理器测试 | `test/unittest/core/common/key_event_manager/` | 焦点分发、快捷键和管理逻辑回归 |
| Native KeyEvent 测试 | `test/unittest/interfaces/ace_key_event/` | Native KeyEvent 接口回归 |
| C API accessor 测试 | `test/unittest/capi/accessors/key_event_accessor_test.cpp` | 按键字段访问回归 |
| Context registry | `docs/context_registry.json` | `KeyEvents` 的统一路由入口 |

### 相关 Spec

按键事件功能域：`specs/04-common-capability/04-common-events/02-key-events/`（功能 ID `04-04-02`）。

| Feat | 主题 | 文件 |
|------|------|------|
| Feat-01 | 按键事件模型与基础回调 | `Feat-01-key-event-model-basic-callback-spec.md` |
| Feat-02 | Pre-IME 与自定义分发 | `Feat-02-pre-ime-custom-dispatch-spec.md` |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 组件收不到按键 | 焦点状态、Common API 注册、`KeyEventManager` 分发和 Feat-01 |
| keyCode、action 或修饰键异常 | 平台输入、`key_event.h`、前端转换和 Native KeyEvent accessor |
| Pre-IME 回调未生效 | SDK 版本声明、对应前端注册、`KeyEventManager` 和 Feat-02 |
| 自定义分发消费结果异常 | 自定义分发入口、焦点链、返回值处理和 Feat-02 |
| 组合快捷键不触发 | 转到组件组合键 KB，检查注册、冲突与 `KeyEventManager` 快捷键路由 |

## 调试入口

- 先确认目标组件是否可获焦且当前处于预期焦点链，再追踪按键分发。
- 从平台事件进入点记录 keyCode、action、时间戳和 pressedKeys，再对比前端/Native 暴露字段。
- Pre-IME、自定义分发和普通按键回调应分别核对对应注册入口与调用阶段。
- 回归优先运行按键事件、KeyEventManager 和 Native KeyEvent 定向用例。

## 相关主题

- [组件组合键：`docs/kb/capabilities/component-shortcuts.md`](component-shortcuts.md)
- [事件分发和拦截：`docs/kb/capabilities/event-dispatch-intercept.md`](event-dispatch-intercept.md)
- [事件基础框架：`docs/kb/architecture/event-base-framework.md`](../architecture/event-base-framework.md)