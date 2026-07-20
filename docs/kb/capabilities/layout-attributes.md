# Layout Attributes Context

> 文档版本：v1.0
> 更新时间：2026-07-18
> 来源：`docs/context_registry.json` 主题 `LayoutAttributes`

## 定位

Layout Attributes 是 ArkUI 组件共享的基础布局属性能力，覆盖尺寸与约束、边距与内边距、位置与偏移、对齐和布局方向，以及 Flex 子项属性。它连接应用侧 Common API、前端参数解析、ViewAbstract 属性写入和 NG `LayoutProperty` 约束消费，不等同于 Flex、Row、Column 等具体布局组件。

本文档用于快速定位属性声明、解析、存储、测试与 Spec。属性语义、API 版本、边界条件和兼容性应以当前 SDK、源码、测试及 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| NG 公共属性写入 | `frameworks/core/components_ng/base/view_abstract.cpp`、`frameworks/core/components_ng/base/view_abstract_model_ng.cpp` | 动态前端及 FrameNode 场景的尺寸、位置和 Flex 子项属性写入入口 |
| Static 公共属性写入 | `frameworks/core/components_ng/base/view_abstract_model_static.cpp` | 静态 ArkTS 公共布局属性写入入口 |
| 布局属性与约束 | `frameworks/core/components_ng/layout/layout_property.h`、`frameworks/core/components_ng/layout/layout_property.cpp` | 通用布局属性存储、父子约束生成和更新标记入口 |
| 测量属性数据结构 | `frameworks/core/components_ng/property/measure_property.h`、`frameworks/core/components_ng/property/measure_property.cpp` | 尺寸、边距、约束等测量数据结构与辅助逻辑 |
| Dynamic JSView 解析 | `frameworks/bridge/declarative_frontend/jsview/js_view_abstract.cpp` | Common 属性的声明式 JS/ArkTS 动态参数解析入口 |
| ArkTS Common Bridge | `frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_common_bridge.cpp` | AttributeModifier 和 FrameNode 动态属性解析入口 |
| Common node modifier | `frameworks/core/interfaces/native/node/node_common_modifier.cpp` | Common Bridge 到 ViewAbstract/ModelNG 的 native 属性入口 |
| Static Common modifier | `frameworks/core/interfaces/native/implementation/common_method_modifier.cpp` | Static ArkTS Common 属性的类型转换及 ViewAbstract/Static Model 写入入口 |
| Native 属性分发 | `interfaces/native/node/style_modifier.cpp`、`interfaces/native/native_node.h` | Node C API 通用属性枚举与分发入口；按具体属性枚举确认公开范围 |

按属性族检索：

| 属性族 | 建议检索词 |
|--------|------------|
| 尺寸与约束 | `Width`、`Height`、`Size`、`ConstraintSize`、`Padding`、`Margin` |
| 位置与方向 | `Position`、`Offset`、`MarkAnchor`、`Align`、`LayoutDirection` |
| Flex 子项 | `FlexGrow`、`FlexShrink`、`FlexBasis`、`AlignSelf`、`LayoutWeight`、`DisplayPriority` |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic Common API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/common.d.ts` | CommonAttribute 中的尺寸、位置和 Flex 子项属性声明 |
| Static Common API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/common.static.d.ets` | 静态 ArkTS Common 属性声明 |
| Dynamic Common Modifier | `<OH_ROOT>/interface/sdk-js/api/arkui/CommonModifier.d.ts` | Dynamic Modifier 类型入口；具体布局属性声明仍需回到 CommonAttribute 核实 |
| Static Common Modifier | `<OH_ROOT>/interface/sdk-js/api/arkui/CommonModifier.static.d.ets` | Static Modifier 类型入口；具体属性声明仍需回到静态 Common API 核实 |
| Node C API | `interfaces/native/native_node.h`、`interfaces/native/node/style_modifier.cpp` | 公开通用属性枚举及设置、重置、查询分发；逐属性确认是否公开 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 布局属性测试 | `test/unittest/core/layout/` | `LayoutProperty`、LayoutWrapper、约束、边距和通用布局行为回归 |
| 布局约束测试 | `test/unittest/core/property/layout_constraint_test_ng.cpp` | LayoutConstraint 数据和边界回归 |
| ViewAbstract 测试 | `test/unittest/core/base/` | 按 `ViewAbstract` 和具体属性名检索公共属性写入测试 |
| Common C modifier 测试 | `test/unittest/capi/modifiers/` | 按 `common_method_modifier` 和具体属性名检索 native modifier 回归 |
| Context registry | `docs/context_registry.json` | `LayoutAttributes` 的 KB、Spec、源码、API 和测试统一路由 |

### 相关 Spec

布局属性功能域：`specs/04-common-capability/03-common-attributes/01-layout-attributes/`（功能 ID `04-03-01`）。

| Feat | 主题 | 文件 |
|------|------|------|
| Feat-01 | 尺寸属性 | `Feat-01-size-properties-spec.md` |
| Feat-02 | 位置属性 | `Feat-02-position-properties-spec.md` |
| Feat-03 | Flex 子项属性 | `Feat-03-flex-properties-spec.md` |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| width、height 或 constraintSize 未生效 | SDK 声明、JSView/Common Bridge、ViewAbstract 写入、`LayoutProperty` 约束更新和 Feat-01 |
| padding、margin 影响范围异常 | `measure_property`、`LayoutProperty`、父组件布局算法和 Feat-01 |
| position、offset 或 markAnchor 位置异常 | SDK 位置属性、ViewAbstract、Geometry/RenderContext 路由和 Feat-02 |
| align 或 direction 表现异常 | Common API 声明、LayoutProperty、父容器算法和 Feat-02 |
| flexGrow、layoutWeight 等不生效 | Feat-03、父级 Flex/Row/Column KB、子节点 `LayoutProperty` 更新入口 |
| Dynamic 与 Static 行为不一致 | 分别核对 Dynamic JSView/Common Bridge、Static Common modifier/Static Model 和对应 SDK 声明，不从另一范式推断 |
| C API 找不到对应属性 | 在 `native_node.h` 按具体枚举检索；ArkTS Common 属性不保证均有公开 Node C API |

## 调试入口

- 从具体 SDK 属性名定位 Dynamic/Static 声明，再进入对应前端解析入口。
- 在 ViewAbstract/Model 写入点确认值是否进入节点，并检查 `LayoutProperty` 的 property change flag。
- 测量问题同时观察父约束、当前节点 layout constraint、content constraint 与 child constraint。
- Flex 子项问题需要同时核对父布局组件算法，避免只检查子节点属性是否写入。
- 回归优先运行 `test/unittest/core/layout/` 和具体属性相关的 CAPI modifier 用例。

## 相关主题

- 布局框架：`docs/kb/architecture/layout-framework.md`
- Safe Area：`docs/kb/capabilities/safe-area.md`
- Flex：`docs/kb/components/container/flex.md`
- Column：`docs/kb/components/container/column.md`
- Row：`docs/kb/components/container/row.md`
