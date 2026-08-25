# Component Shortcuts Context

> 文档版本：v1.0
> 更新时间：2026-07-30
> 来源：`docs/context_registry.json` 主题 `ComponentShortcuts`

## 定位

Component Shortcuts 是 ArkUI 组件通过 `keyboardShortcut` 注册并响应组合快捷键的独立公共能力。它连接 Common API、Dynamic/Static 前端参数解析、ViewAbstract/EventHub 注册和 KeyEventManager 的快捷键匹配处理。

该能力具有独立功能 ID `04-04-04`，不并入普通按键事件。本文档只维护注册、桥接、管理和测试路由；按键基础数据、普通按键回调及 Pre-IME 由按键事件 KB 承载。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| Dynamic JSView 解析 | `frameworks/bridge/declarative_frontend/jsview/js_view_abstract.cpp` | `keyboardShortcut` 参数解析和公共属性入口 |
| Dynamic Common Bridge | `frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_common_bridge.cpp` | AttributeModifier/FrameNode 场景快捷键桥接入口 |
| NG 公共属性写入 | `frameworks/core/components_ng/base/view_abstract.cpp` | 组件快捷键注册到节点/EventHub 的入口 |
| 组件事件存储 | `frameworks/core/components_ng/event/event_hub.cpp` | 快捷键值、修饰键和回调保存入口 |
| 快捷键管理与触发 | `frameworks/core/common/key_event_manager.cpp` | 快捷键节点管理、匹配和触发入口 |
| Common node modifier | `frameworks/core/interfaces/native/node/node_common_modifier.cpp` | Dynamic native modifier 快捷键入口 |
| Static Common modifier | `frameworks/core/interfaces/native/implementation/common_method_modifier.cpp` | Static ArkTS 快捷键转换与写入入口 |

建议按 `keyboardShortcut`、`KeyboardShortcut`、`SetKeyboardShortcut`、`AddKeyboardShortcutNode` 和 `KeyEventManager` 检索。

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic Common API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/common.d.ts` | `keyboardShortcut` 和修饰键类型声明 |
| Static Common API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/common.static.d.ets` | Static ArkTS 组件快捷键声明 |
| Dynamic Common Modifier | `<OH_ROOT>/interface/sdk-js/api/arkui/CommonModifier.d.ts` | Dynamic Modifier 快捷键声明入口 |
| Static Common Modifier | `<OH_ROOT>/interface/sdk-js/api/arkui/CommonModifier.static.d.ets` | Static Modifier 快捷键声明入口 |
| Native Node API | `interfaces/native/native_node.h` | 按公开节点事件/属性确认 Native 场景支持范围，不从 ArkTS API 直接推断 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 组件测试样例 | `test/component_test/test_cases/components/common/` | 按 `KeyboardShortcutSample.ets`、`KeyboardShortcutTest.ets` 定位端到端用例 |
| KeyEventManager 测试 | `test/unittest/core/common/key_event_manager/` | 快捷键注册、匹配、冲突和触发回归 |
| Context registry | `docs/context_registry.json` | `ComponentShortcuts` 的统一路由入口 |

### 相关 Spec

组件组合键功能域：`specs/04-common-capability/04-common-events/04-component-shortcuts/`（功能 ID `04-04-04`）。

| Feat | 主题 | 文件 |
|------|------|------|
| Feat-01 | 组件快捷键注册与触发 | `Feat-01-component-shortcut-registration-trigger-spec.md` |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 快捷键未注册 | SDK 参数约束、JSView/Common Bridge、ViewAbstract 和 EventHub 存储 |
| 按键到达但快捷键不触发 | `KeyEventManager` 匹配、组件可见/有效状态、修饰键集合和 Feat-01 |
| 多组件快捷键冲突 | 快捷键节点管理、注册顺序/有效性及对应 KeyEventManager 测试 |
| Dynamic 与 Static 不一致 | 分别核对 Dynamic Bridge/node modifier 与 Static modifier，不共用解析结论 |
| 普通 onKeyEvent 行为异常 | 转到按键事件 KB，检查焦点分发和普通回调链 |

## 调试入口

- 先确认 SDK 参数是否被前端接受，再检查快捷键值、修饰键集合和回调是否写入 EventHub。
- 在 KeyEventManager 中对比实际 KeyEvent 的按键码/修饰键与注册项。
- 冲突问题记录所有候选节点的注册状态、可用状态和匹配结果。
- 回归优先运行 KeyEventManager 定向用例及 Common 组件快捷键测试。

## 相关主题

- 按键事件：`docs/kb/capabilities/key-events.md`
- 事件基础框架：`docs/kb/architecture/event-base-framework.md`
- 组件组合键 Spec：`specs/04-common-capability/04-common-events/04-component-shortcuts/`
