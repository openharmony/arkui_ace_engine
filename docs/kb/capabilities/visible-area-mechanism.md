# Visible Area Mechanism Context

> 文档版本：v1.0
> 更新时间：2026-07-31
> 来源：`docs/context_registry.json` 主题 `VisibleAreaMechanism`

## 定位

可见区域机制负责根据组件与祖先裁剪关系计算可见比例，并向 ArkTS 或 Native Node 监听器提供精确阈值变化与近似节流变化通知。它连接 Common API、ViewAbstract、EventHub、FrameNode 几何计算和 Pipeline 帧调度。

本文档只提供路由入口。比例算法、阈值判定、生命周期归零、节流及版本差异，应以当前 SDK、源码、测试及 `04-04-10` Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| Dynamic JS 入口 | `frameworks/bridge/declarative_frontend/jsview/js_view_abstract.cpp` | 精确与近似可见区域监听参数解析 |
| ArkTS Modifier | `frameworks/bridge/declarative_frontend/ark_component/src/ArkComponent.ts` | Common 监听器 set/reset 入口 |
| Dynamic Common Bridge | `frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_common_bridge.cpp` | Modifier 参数转换并路由到节点 |
| View 抽象层 | `frameworks/core/components_ng/base/view_abstract.cpp` | 精确/近似监听注册、归一化与 Pipeline 节点管理 |
| 配置与回调存储 | `frameworks/core/components_ng/event/event_hub.cpp` | ratios、callback 和监听配置存储 |
| 可见矩形与阈值 | `frameworks/core/components_ng/base/frame_node.cpp` | 可见矩形、比例、阈值穿越和近似任务入口 |
| Pipeline 调度 | `frameworks/core/pipeline_ng/pipeline_context.cpp` | 帧阶段可见区域检查及节点集合维护 |
| Static Common 入口 | `frameworks/core/interfaces/native/implementation/common_method_modifier.cpp` | Static ArkTS CommonMethod 设置/清理 |
| Static UICommonEvent | `frameworks/core/interfaces/native/implementation/ui_common_event_accessor.cpp` | Static UICommonEvent 监听入口 |
| Native Modifier | `frameworks/core/interfaces/native/node/node_common_modifier.cpp` | Native payload、ViewAbstract 调用和 reset |
| Native 注册核心 | `frameworks/core/interfaces/native/node/node_api.cpp` | generic 事件注册与注销入口 |
| Native Style 路由 | `interfaces/native/node/style_modifier.cpp`、`interfaces/native/node/node_model.cpp` | ratio/options 校验及节点事件映射 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic Common API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/common.d.ts` | onVisibleAreaChange 与 onVisibleAreaApproximateChange 声明 |
| Static Common API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/common.static.d.ets` | Static ArkTS 可见区域监听契约 |
| Native Node API | `interfaces/native/native_node.h` | ratio/options、generic 事件与 CommonEvent 注册接口 |
| Native 类型 | `interfaces/native/native_type.h` | 可见区域事件数据和 options 类型 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| FrameNode | `test/unittest/core/base/frame_node_test_ng.cpp` | 可见比例、阈值和生命周期验证 |
| ViewAbstract | `test/unittest/core/base/view_abstract_test_ng.cpp` | 精确/近似监听注册和清理验证 |
| EventHub | `test/unittest/core/event/event_hub_test_ng.cpp` | ratios 与 callback 配置验证 |
| Pipeline | `test/unittest/core/pipeline/` | 帧阶段调度和近似任务验证 |
| Native Common Event | `test/unittest/capi/accessors/ui_common_event_accessor_test.cpp`、`test/unittest/interfaces/native_node_test.cpp` | Native options、事件和接口验证 |

### 相关 Spec

功能域：`specs/04-common-capability/04-common-events/10-visible-area-mechanism/`（功能 ID `04-04-10`）。

| Feat | 稳定路径 | 覆盖范围 |
|------|----------|----------|
| Feat-01 | `Feat-01-exact-visible-area-change-listening-spec.md` | 精确可见区域变化监听 |
| Feat-02 | `Feat-02-approximate-visible-area-change-listening-spec.md` | 近似可见区域变化监听 |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 可见比例与预期不一致 | `frame_node.cpp` 的可见矩形计算、祖先裁剪和相关测试 |
| 阈值穿越未触发或重复触发 | `event_hub.cpp`、`frame_node.cpp` 和 Feat-01 |
| 近似监听回调频率异常 | `view_abstract.cpp`、`frame_node.cpp`、Pipeline 调度和 Feat-02 |
| 离树、隐藏或后台后未归零 | `frame_node.cpp`、`pipeline_context.cpp` 和生命周期测试 |
| ArkTS 与 Native 结果不同 | SDK 声明、Bridge、`node_common_modifier.cpp`、`node_model.cpp` |

## 调试入口

- API 检索：`onVisibleAreaChange`、`onVisibleAreaApproximateChange`、`VisibleAreaEventOptions`。
- 核心检索：`VisibleArea`、`VisibleRatio`、`ProcessAllVisibleCallback`、`expectedUpdateInterval`。
- Native 检索：`VISIBLE_AREA`、`VISIBLE_AREA_APPROXIMATE`、`NODE_VISIBLE_AREA_APPROXIMATE_CHANGE_EVENT`、`ON_VISIBLE_AREA_APPROXIMATE_CHANGE`。

## 相关主题

- [组件相关事件：`docs/kb/capabilities/component-related-events.md`。](component-related-events.md)
- [布局框架：`docs/kb/architecture/layout-framework.md`。](../architecture/layout-framework.md)