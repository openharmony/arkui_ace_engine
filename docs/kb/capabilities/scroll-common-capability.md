# Scroll Common Capability Context

> 文档版本：v1.0
> 更新时间：2026-07-30
> 来源：`docs/context_registry.json` 主题 `ScrollCommonCapability`

## 定位

滚动公共能力是 List、Grid、Scroll、WaterFlow 等滚动容器共享的基础设施，覆盖滚动条与内容视效、手势和惯性物理、嵌套滚动、内容边界以及滚动事件生命周期。组件特有的布局、索引和控制器行为仍由各组件 Pattern 与对应 Spec 承接。

本文档只提供源码、SDK、测试和 Spec 路由。具体默认值、版本差异、事件顺序和异常恢复语义应继续查阅当前 SDK 声明、实现、测试与 `05-03-01` Spec。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| 公共 Pattern | `frameworks/core/components_ng/pattern/scrollable/scrollable_pattern.cpp` | 滚动容器共享生命周期、边缘效果、滚动条、控制和事件入口 |
| 手势与物理动画 | `frameworks/core/components_ng/pattern/scrollable/scrollable.cpp` | Pan、惯性、回弹、速度处理和输入设备协同 |
| 嵌套滚动 | `frameworks/core/components_ng/pattern/scrollable/nestable_scroll_container.cpp` | 父子滚动容器发现、模式分派和速度/位移协同 |
| Dynamic Model | `frameworks/core/components_ng/pattern/scrollable/scrollable_model_ng.cpp` | 动态前端公共滚动属性写入 |
| Static Model | `frameworks/core/components_ng/pattern/scrollable/scrollable_model_static.cpp` | 静态前端公共滚动属性写入 |
| 布局属性 | `frameworks/core/components_ng/pattern/scrollable/scrollable_layout_property.h` | 内容边界等公共布局状态 |
| 绘制属性 | `frameworks/core/components_ng/pattern/scrollable/scrollable_paint_property.h` | 滚动条、渐隐和内容裁剪等绘制状态 |
| 事件存储 | `frameworks/core/components_ng/pattern/scrollable/scrollable_event_hub.h` | 公共滚动事件回调入口 |
| 公共 PaintMethod | `frameworks/core/components_ng/pattern/scrollable/scrollable_paint_method.cpp` | 公共裁剪和绘制路由 |
| 滚动条实现 | `frameworks/core/components_ng/pattern/scroll/inner/` | 单轴/二维滚动条、Overlay Modifier 和交互处理 |
| Native Modifier | `frameworks/core/interfaces/native/node/scrollable_modifier.cpp` | Bridge 和 NativeNode 共用的公共属性访问层 |
| Public C style 分派 | `interfaces/native/node/style_modifier.cpp` | 按节点类型分派公共滚动属性和事件 |
| 组件差异入口 | `frameworks/core/components_ng/pattern/{list,grid,scroll,waterflow}/` | 各容器的默认值、布局、虚拟化和事件覆盖 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/common.d.ts` | 搜索 `ScrollableCommonMethod` 与具体属性/事件名 |
| Static API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/common.static.d.ets` | 静态 ArkTS 公共滚动契约 |
| Dynamic Modifier | `<OH_ROOT>/interface/sdk-js/api/arkui/CommonModifier.d.ts` | 公共 Modifier 声明 |
| Static Modifier | `<OH_ROOT>/interface/sdk-js/api/arkui/CommonModifier.static.d.ets` | 静态公共 Modifier 声明 |
| Public C API | `interfaces/native/native_node.h` | 搜索 `NODE_SCROLL_`、公共滚动属性及事件枚举 |

公共 API 解析路由：

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| JSView 公共解析 | `frameworks/bridge/declarative_frontend/jsview/js_scrollable_base.cpp` | 声明式滚动公共属性和事件解析 |
| ArkTS Bridge | `frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_scrollable_bridge.cpp` | Dynamic ArkTS 参数解析并转入 Modifier |
| Native Modifier | `frameworks/core/interfaces/native/node/scrollable_modifier.cpp` | Set/Reset/Get 到 `ScrollableModelNG` |
| Public C API | `interfaces/native/node/style_modifier.cpp` | `ArkUI_AttributeItem` 校验和具体滚动组件分派 |
| Model/Property | `frameworks/core/components_ng/pattern/scrollable/` | 公共属性状态和运行时消费入口 |

### 外部依赖入口

| 依赖方向 | 本仓入口 | 外部仓路径 | 外部目标 | 说明 |
|----------|----------|-----------|----------|------|
| 资源调度 | `adapter/ohos/osal/ressched_report.cpp` | `<OH_ROOT>/foundation/resourceschedule/resource_schedule_service/` | `resource_schedule_service:ressched_client` | 滚动场景性能调度上报 |
| 振动反馈 | `adapter/ohos/entrance/vibrator/vibrator_utils.cpp` | `<OH_ROOT>/base/sensors/miscdevice/` | `miscdevice:vibrator_interface_native` | 滚动条和数字表冠等交互反馈 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| Scrollable 公共单元测试 | `test/unittest/core/pattern/scrollable/` | 物理、嵌套、事件、属性、边界和生成接口测试 |
| Scroll 组件回归 | `test/unittest/core/pattern/scroll/` | 公共能力在 Scroll 容器中的集成验证 |
| 公共 Modifier C API | `test/unittest/capi/modifiers/scrollable_common_method_modifier_test.cpp` | Public C 属性设置、读取和重置 |
| 公共 Modifier C API 扩展 | `test/unittest/capi/modifiers/scrollable_common_method_modifier_test_2.cpp` | 新增公共滚动属性覆盖 |
| Generated Modifier | `test/unittest/capi/modifiers/generated/scrollable_common_method_modifier_test.cpp` | generated Modifier 路径验证 |
| 事件基础设施 | `test/unittest/core/event/scrollable_event_test_ng.cpp` | ScrollableEvent 行为验证 |

### 相关 Spec

功能域：`specs/05-ui-components/03-scroll-container-components/01-scroll-common-capability/`（功能 ID `05-03-01`）。

| 文档 | 稳定路径 | 覆盖范围 |
|------|----------|----------|
| 设计文档 | `specs/05-ui-components/03-scroll-container-components/01-scroll-common-capability/design.md` | 公共层次、组件差异和多范式入口 |
| Feat-01 | `specs/05-ui-components/03-scroll-container-components/01-scroll-common-capability/Feat-01-scrollbar-content-visual-spec.md` | 滚动条与内容视效 |
| Feat-02 | `specs/05-ui-components/03-scroll-container-components/01-scroll-common-capability/Feat-02-scroll-interaction-physics-spec.md` | 滚动交互与物理效果 |
| Feat-03 | `specs/05-ui-components/03-scroll-container-components/01-scroll-common-capability/Feat-03-nested-scroll-content-boundary-spec.md` | 嵌套滚动与内容边界 |
| Feat-04 | `specs/05-ui-components/03-scroll-container-components/01-scroll-common-capability/Feat-04-scroll-event-lifecycle-spec.md` | 滚动事件生命周期 |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 手势、惯性或回弹异常 | `scrollable.cpp`、`scrollable_pattern.cpp` 和 Feat-02 |
| 父子滚动分配异常 | `nestable_scroll_container.cpp`、具体组件 Pattern 和 Feat-03 |
| 滚动条样式或位置异常 | `scroll/inner/`、`scrollable_paint_property.h` 和 Feat-01 |
| 内容裁剪或边界偏移异常 | `scrollable_layout_property.h`、具体组件布局算法和 Feat-01/03 |
| 事件顺序或参数异常 | `scrollable_event_hub.h`、具体组件布局后事件入口和 Feat-04 |
| ArkTS 与 NativeNode 结果不一致 | `common*.d.ts`、Scrollable Bridge、`scrollable_modifier.cpp`、`style_modifier.cpp` |

## 调试入口

- 公共类型检索：`ScrollablePattern`、`Scrollable`、`ScrollableModelNG`、`ScrollableEventHub`。
- 物理与输入检索：`HandleDrag`、`Friction`、`Fling`、`EdgeEffect`、`CrownSensitivity`。
- 嵌套滚动检索：`NestedScrollMode`、`NestableScrollContainer`、`HandleScrollVelocity`。
- 事件检索：`OnWillScroll`、`OnDidScroll`、`OnScrollStart`、`OnScrollStop`、`ReachStart`、`ReachEnd`。
- NativeNode 检索：`NODE_SCROLL_` 和 `ARKUI_NODE_SCROLL`。

## 相关主题

- [WaterFlow/FlowItem](../components/container/waterflow.md)。
- Scroll 组件实现：见对应 KB
- List 组件实现：见对应 KB
- Grid 组件实现：见对应 KB