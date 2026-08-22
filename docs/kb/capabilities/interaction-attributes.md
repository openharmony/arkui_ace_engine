# Interaction Attributes Context

> 文档版本：v1.0
> 更新时间：2026-07-31
> 来源：`docs/context_registry.json` 主题 `InteractionAttributes`

## 定位

交互属性是 ArkUI 通用属性层中面向组件输入与反馈的能力集合。本主题按通用能力拆分为：鼠标光标与悬浮效果、触摸热区/触摸控制/事件独占，以及禁用控制与点击反馈。

命中测试、手势仲裁、键盘与外设输入、拖拽以及弹窗/模态分别由相邻主题维护。行为事实应以 SDK 声明、当前源码和测试为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| 通用属性分派 | `frameworks/core/components_ng/base/view_abstract.*` | 输入回调、enabled、点击反馈及声音反馈进入 NG 通用 View 的入口。 |
| 手势与指针事件 | `frameworks/core/components_ng/event/gesture_event_hub.*` | 悬浮、响应热区、触摸控制和事件独占等通用配置的保存和分发入口。 |
| 事件可用性 | `frameworks/core/components_ng/event/event_hub.*` | 组件事件可用状态入口。 |
| 禁用与焦点状态 | `frameworks/core/components_ng/event/focus_hub.*`、`frameworks/core/components_ng/event/event_hub.*` | `enabled` 对焦点和事件可用性的同步入口；键盘事件由相邻输入事件主题承接。 |
| 动态 ArkTS NativeModule | `frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_common_bridge.cpp` | CommonMethod 动态属性和事件桥接。 |
| 兼容 JS 入口 | `frameworks/bridge/declarative_frontend/jsview/js_interactable_view.cpp` | 兼容 JS 交互回调解析入口。 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| 动态 ArkTS CommonMethod | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/common.d.ts` | 检索 `cursorControl`、`onHover`、`hoverEffect`、`responseRegion`、`responseRegionList`、`touchable`、`monopolizeEvents`、`enabled`、`clickEffect` 等。 |
| 静态 ArkTS CommonMethod | `<OH_ROOT>/interface/sdk-js/api/arkui/component/common.static.d.ets` | 静态前端对应声明；需单独核对签名、可空性和 API 版本。 |
| Dynamic Modifier | `<OH_ROOT>/interface/sdk-js/api/arkui/CommonModifier.d.ts` | 通用属性 Modifier 声明入口。 |
| Static Modifier | `<OH_ROOT>/interface/sdk-js/api/arkui/CommonModifier.static.d.ets` | 静态 Modifier 声明入口。 |
| C API | `interfaces/native/native_node.h` | 通用节点属性和事件的 NDK 入口。 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 通用 View 单测 | `test/unittest/core/base/view_abstract*_test*.cpp` | 定位通用属性、事件注册与可用性行为。 |
| 手势事件单测 | `test/unittest/core/event/gesture_event_hub*_test*.cpp` | 定位触摸、悬停和手势事件 Hub 行为。 |
| 事件 Hub 单测 | `test/unittest/core/event/event_hub_test_ng.cpp` | 定位 enabled 等 EventHub 行为。 |
| 焦点单测 | `test/unittest/core/event/focus_core/` | 定位键盘与焦点输入分发。 |
| C API 测试 | `test/unittest/capi/` | 检索通用节点和 Modifier 场景。 |

### 相关 Spec

| 功能域 | Spec 路径 | 说明 |
|--------|-----------|------|
| 交互属性 | `specs/04-common-capability/03-common-attributes/04-interaction-attributes/` | 鼠标光标/悬浮效果、触摸热区/触摸控制/事件独占、禁用控制/点击反馈规格。 |
| 手势能力 | `specs/04-common-capability/04-common-events/06-gesture-capability/` | 命中测试、手势绑定与仲裁边界。 |
| 拖拽能力 | `specs/04-common-capability/04-common-events/07-drag-capability/` | draggable、DragEvent、预览和 Controller 路由。 |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 动态与静态 ArkTS 的回调签名不一致 | 分别检查 `common.d.ts` 与 `common.static.d.ets`，不要用一侧声明替代另一侧。 |
| 鼠标光标或悬浮回调未生效 | 检查 `UIContext.cursorControl`、`ViewAbstract`、`GestureEventHub`，再检查命中测试和手势能力主题。 |
| 触摸热区或事件独占未生效 | 检查 `responseRegion`、`responseRegionList`、`touchable`、`monopolizeEvents` 的 SDK 声明和 `GestureEventHub` 配置路径。 |
| 禁用后仍有异常输入 | 检查 EventHub 与 FocusHub 两个路径，而不是只检查视觉状态。 |
| clickEffect 或声音反馈异常 | 检查 CommonMethod 声明、NativeModule 解析和 FrameNode/ViewAbstract 路由。 |

## 调试入口

- 使用 `rg -n "cursorControl|onHover|hoverEffect|responseRegion|responseRegionList|touchable|monopolizeEvents|enabled|clickEffect" <OH_ROOT>/interface/sdk-js/api` 对照公开契约。
- 使用 `rg -n "SetOnHover|SetMouseResponseRegion|SetTouchable|SetMonopolizeEvents|SetEnabled|SetClickEffect" frameworks/core/components_ng` 回溯 NG 入口。
- 使用 `rg -n "SetOn.*|ResetOn.*" frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_common_bridge.cpp` 定位动态桥接。

## 相关主题

- [docs/kb/capabilities/drag-capability.md](drag-capability.md)
- [docs/kb/capabilities/ui-context.md](ui-context.md)
- [docs/kb/architecture/drag-framework.md](../architecture/drag-framework.md)