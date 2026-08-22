# Component Related Events Context

> 文档版本：v1.0
> 更新时间：2026-07-31
> 来源：`docs/context_registry.json` 主题 `ComponentRelatedEvents`

## 定位

组件相关事件覆盖组件挂载、卸载、显隐生命周期以及区域和尺寸变化通知。能力由 Dynamic/Static ArkTS 与 Native Node 入口汇聚到 ViewAbstract、EventHub、UINode/FrameNode 和 Pipeline 调度层。

本文档只提供路由入口。事件时序、触发条件、节流、回调数据和版本差异，应以当前 SDK、源码、测试及 `04-04-09` Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| Dynamic 生命周期入口 | `frameworks/bridge/declarative_frontend/jsview/js_interactable_view.cpp` | onAppear/onDisAppear/onAttach/onDetach 参数解析 |
| Dynamic Common Bridge | `frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_common_bridge.cpp` | Common Modifier 生命周期和区域事件桥接 |
| ArkTS Modifier | `frameworks/bridge/declarative_frontend/ark_component/src/ArkComponent.ts` | Common 事件 set/reset 路由 |
| Static Common 入口 | `frameworks/core/interfaces/native/implementation/common_method_modifier.cpp` | Static ArkTS Common 事件转换与设置 |
| View 抽象层 | `frameworks/core/components_ng/base/view_abstract.cpp` | 前端与 Native 事件注册到 FrameNode/EventHub 的公共入口 |
| 生命周期存储 | `frameworks/core/components_ng/event/event_hub.cpp` | 生命周期、Area 和 Size 回调槽及触发入口 |
| UI 树生命周期 | `frameworks/core/components_ng/base/ui_node.cpp` | 主树挂载、卸载和状态迁移入口 |
| FrameNode 生命周期与几何 | `frameworks/core/components_ng/base/frame_node.cpp` | 生命周期派发、Area/Size 快照和变化检测 |
| 布局几何同步 | `frameworks/core/components_ng/layout/layout_wrapper.cpp` | 布局结果同步后的尺寸和区域事件触发入口 |
| Pipeline Area 调度 | `frameworks/core/pipeline_ng/pipeline_context.cpp` | Area 节点集合和帧阶段检查入口 |
| Native Modifier | `frameworks/core/interfaces/native/node/node_common_modifier.cpp` | Native 生命周期、Area 和 Size 事件包装与 reset |
| Native 映射 | `interfaces/native/node/event_converter.cpp`、`interfaces/native/node/node_utils.cpp` | Native 事件注册、payload 转换和 CommonEvent 路由 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic Common API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/common.d.ts` | onAppear/onDisAppear/onAttach/onDetach/onAreaChange/onSizeChange 声明 |
| Static Common API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/common.static.d.ets` | Static ArkTS 生命周期和几何事件契约 |
| Native Node API | `interfaces/native/native_node.h` | 泛型节点事件与 CommonEvent 注册接口 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| EventHub | `test/unittest/core/event/event_hub_test_ng.cpp` | 生命周期及区域回调存储和触发验证 |
| FrameNode | `test/unittest/core/base/frame_node_test_ng.cpp` | 主树生命周期、Area 和 Size 变化验证 |
| UINode | `test/unittest/core/base/ui_node_test_ng.cpp` | 挂载、卸载和树状态迁移验证 |
| ViewAbstract | `test/unittest/core/base/view_abstract_test_ng.cpp` | ArkTS/Common 事件注册与清理验证 |
| Native Common Event | `test/unittest/capi/accessors/ui_common_event_accessor_test.cpp`、`test/unittest/capi/modifiers/` | Native 事件注册、读取和 reset 验证 |

### 相关 Spec

功能域：`specs/04-common-capability/04-common-events/09-component-related-events/`（功能 ID `04-04-09`）。

| Feat | 稳定路径 | 覆盖范围 |
|------|----------|----------|
| Feat-01 | `Feat-01-component-mount-visibility-lifecycle-events-spec.md` | 组件挂载与显隐生命周期事件 |
| Feat-02 | `Feat-02-component-area-size-change-events-spec.md` | 组件区域与尺寸变化事件 |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 挂载、卸载或显隐回调未触发 | `ui_node.cpp`、`frame_node.cpp`、`event_hub.cpp` |
| Dynamic、Static 与 Native 清理结果不同 | SDK 声明、对应 Bridge、`common_method_modifier.cpp`、`node_common_modifier.cpp` |
| Area 回调丢失、延迟或重复 | `pipeline_context.cpp`、`frame_node.cpp`、`event_hub.cpp` |
| Size 回调与布局结果不一致 | `layout_wrapper.cpp`、`frame_node.cpp` 和 ViewAbstract 测试 |

## 调试入口

- 生命周期检索：`OnAppear`、`OnDisappear`、`OnAttach`、`OnDetach`、`OnMainTree`。
- 区域尺寸检索：`OnAreaChange`、`OnSizeChange`、`AreaChangeOptions`、`TriggerOnAreaChangeCallback`。
- Native 入口检索：`NODE_EVENT_ON_AREA_CHANGE`、`NODE_ON_SIZE_CHANGE`、`RegisterCommonEvent`。

## 相关主题

- [可见区域机制：[docs/kb/capabilities/visible-area-mechanism.md](visible-area-mechanism.md)。](visible-area-mechanism.md)
- [布局框架：[docs/kb/architecture/layout-framework.md](../architecture/layout-framework.md)。](../architecture/layout-framework.md)