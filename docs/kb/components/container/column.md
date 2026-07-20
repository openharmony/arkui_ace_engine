# Column Context

> 文档版本：v1.0
> 更新时间：2026-07-18
> 来源：`docs/context_registry.json` 主题 `Column`

## 定位

Column 是 ArkUI 的纵向线性布局容器，应用侧可配置子项间距、主轴分布、交叉轴对齐和反向排列。NG 实现与 Row 共享 `linear_layout/` 下的 Pattern、Property 和工具，并通过 `LinearLayoutAlgorithm` 复用 Flex 布局算法。

本文档用于快速定位 Column 的源码、SDK、API 解析、测试和 Spec。具体属性语义、版本约束、默认值和边界条件应回到当前 SDK 声明、源码、测试与 Spec 核实。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| Dynamic Model | `frameworks/core/components_ng/pattern/linear_layout/column_model_ng.cpp`、`frameworks/core/components_ng/pattern/linear_layout/column_model_ng.h` | Column 节点创建及 Dynamic 属性写入入口 |
| Static Model | `frameworks/core/components_ng/pattern/linear_layout/column_model_ng_static.cpp`、`frameworks/core/components_ng/pattern/linear_layout/column_model_ng_static.h` | Static Column 间距和对齐属性写入入口；其他属性继续核对 generated modifier 对 ModelNG 的委托 |
| Model 抽象 | `frameworks/core/components_ng/pattern/linear_layout/column_model.h` | Column 前端与 NG Model 的抽象接口 |
| 共享 Pattern | `frameworks/core/components_ng/pattern/linear_layout/linear_layout_pattern.h` | 纵向/横向线性容器共用的 Pattern；Column 以纵向模式创建 |
| 共享布局属性 | `frameworks/core/components_ng/pattern/linear_layout/linear_layout_property.h` | 基于 `FlexLayoutProperty` 保存线性布局方向、间距、对齐和反向属性 |
| 共享布局算法 | `frameworks/core/components_ng/pattern/linear_layout/linear_layout_algorithm.h` | `LinearLayoutAlgorithm` 在 Flex 布局算法上启用线性布局路径 |
| Flex 算法实现 | `frameworks/core/components_ng/pattern/flex/flex_layout_algorithm.cpp`、`frameworks/core/components_ng/pattern/flex/flex_layout_algorithm.h` | Column/Row 实际复用的 Measure/Layout 算法实现 |
| 线性布局工具 | `frameworks/core/components_ng/pattern/linear_layout/linear_layout_utils.cpp`、`frameworks/core/components_ng/pattern/linear_layout/linear_layout_utils.h` | 线性布局属性、约束和轴向处理的共享工具入口 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/column.d.ts` | `ColumnInterface`、构造 options 与 `ColumnAttribute` |
| Static API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/column.static.d.ets` | Static Column 构造、属性和 builder 声明 |
| Modifier API（Dynamic） | `<OH_ROOT>/interface/sdk-js/api/arkui/ColumnModifier.d.ts` | Dynamic `ColumnModifier` 声明 |
| Modifier API（Static） | `<OH_ROOT>/interface/sdk-js/api/arkui/ColumnModifier.static.d.ets` | Static `ColumnModifier` 声明 |
| Native Node C API | `interfaces/native/native_node.h` | `ARKUI_NODE_COLUMN`、`NODE_COLUMN_*` 与共享 `NODE_LINEAR_LAYOUT_*` 声明 |

API 检索建议：

- 构造与间距：搜索 `ColumnInterface`、`ColumnOptions`、`ColumnOptionsV2`、`space`。
- 对齐和反向：搜索 `alignItems`、`justifyContent`、`reverse`。
- Native Node：搜索 `ARKUI_NODE_COLUMN`、`NODE_COLUMN_`、`NODE_LINEAR_LAYOUT_SPACE`、`NODE_LINEAR_LAYOUT_REVERSE`。

### API 解析实现路径

Column **尚未完成组件化改造**：`pattern/linear_layout/` 下没有 `bridge/` 子目录，`DynamicModuleHelper` 没有 Column 动态模块映射，JSView 和旧 ArkTS Bridge 路径仍在使用；当前没有独立的 `libarkui_column.z.so`。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| JSView（声明式组件） | `frameworks/bridge/declarative_frontend/jsview/js_column.cpp` | 解析构造参数、对齐与反向属性，经 `ColumnModel::GetInstance()` 写入 Model |
| Dynamic 前端组件 | `frameworks/bridge/declarative_frontend/ark_component/src/ArkColumn.ts` | Dynamic AttributeModifier 的前端组件类和属性下发入口 |
| ArkTS Bridge（动态属性） | `frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_column_bridge.cpp` | 解析 Column 属性并调用 Column node modifier |
| 前端 Modifier（ArkTS 侧） | `frameworks/bridge/declarative_frontend/ark_modifier/src/column_modifier.ts` | Dynamic `ColumnModifier` 引擎实现入口 |
| node_modifier 层 | `frameworks/core/interfaces/native/node/column_modifier.cpp` | 间距、对齐和反向属性的 Set/Reset/Get，连接 Bridge、ModelNG 与 Native Node 框架 |
| Static 前端节点 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/typedNode/ArkColumnNode.ets` | Static Column 构造参数和属性进入 peer 的入口 |
| Static generated modifier | `frameworks/core/interfaces/native/implementation/column_modifier.cpp` | Static 类型转换、节点构造和属性委托，落到 `ColumnModelNG` / `ColumnModelNGStatic` |
| C API（通用 Native Node） | `interfaces/native/node/style_modifier.cpp`、`interfaces/native/native_node.h` | Column 没有专属 `column_native_impl.cpp`；公共属性由通用 style modifier 分发到 Column node modifier |

组件化改造参考：`./组件化重构通用方案.md`。改造后 JSView 和 Bridge 双路径将统一到 `pattern/linear_layout/bridge/`，并输出独立 so。

### 外部依赖入口

Column 的核心 Model、Pattern 和布局算法未发现组件特有的跨仓依赖，因此不建立组件专属外部依赖表。公共布局调度和渲染同步应转到 Layout Framework；`pointLight` 走 `JSViewAbstract` / `ViewAbstractModelStatic` 的公共渲染属性路径，不属于 Column 线性布局算法本身。

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 线性布局单元测试 | `test/unittest/core/pattern/linear_layout/` | Column/Row 共享 Pattern、属性、算法、约束和反向布局回归 |
| Static generated modifier 测试 | `test/unittest/capi/modifiers/column_modifier_test.cpp` | Static Column 构造参数、属性转换及 modifier 委托回归 |
| Native Node 通用测试 | `test/unittest/interfaces/native_node_test.cpp` | `NODE_COLUMN_*` 和共享 `NODE_LINEAR_LAYOUT_*` 属性回归 |
| 组件测试样例 | `test/component_test/test_cases/components/common_container/entry/src/main/ets/pages/column/` | Column 对齐、主轴分布和基本创建的组件级样例 |
| Context registry | `docs/context_registry.json` | Column 的 KB、Spec、源码、API 和测试统一路由 |

### 相关 Spec

Column 功能域：`specs/05-ui-components/01-layout-components/03-column/`（功能 ID `05-01-03`）。

| Feat | 主题 | 文件 |
|------|------|------|
| Feat-01 | Column 创建、尺寸与子项间距 | `Feat-01-column-creation-size-space-spec.md` |
| Feat-02 | Column 对齐与反向排列 | `Feat-02-column-alignment-reverse-spec.md` |
| Feat-03 | Column 多范式接口与版本兼容 | `Feat-03-column-multi-paradigm-version-spec.md` |
| Feat-04 | Column PointLight 系统光效 | `Feat-04-column-point-light-spec.md` |

架构决策和模块边界见同目录 `design.md`。行为结论以对应 Feat、当前 SDK、源码和测试的交叉证据为准。

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| Column 创建或间距未生效 | 对应范式 SDK、JSView 或 Static typed node、Column modifier、`ColumnModelNG`、Feat-01 |
| 主轴分布异常 | SDK `justifyContent`、`LinearLayoutProperty`、`FlexLayoutAlgorithm`、Feat-02 |
| 交叉轴对齐异常 | SDK `alignItems`、Column Bridge / modifier、`LinearLayoutProperty`、Feat-02 |
| 反向排列异常 | SDK `reverse`、Column modifier、ModelNG、Feat-02 |
| Dynamic 与 Static 表现不一致 | 分别核对 ArkTS Bridge/node modifier 与 typed node/generated modifier，再看 Feat-03 |
| Native Node 属性未生效 | `native_node.h` 的 Column/Linear Layout 属性、`style_modifier.cpp`、`column_modifier.cpp` |
| PointLight 表现异常 | Dynamic 公共属性入口或 Static generated modifier、ViewAbstract 公共渲染属性、Feat-04 |

## 调试入口

- 节点创建：从 `ColumnModelNG` 确认节点以纵向 `LinearLayoutPattern` 创建，并检查布局属性是否写入。
- 属性链路：Dynamic 从 `ArkColumn.ts` / JSView 或 ArkTS Bridge 向 node modifier 追踪；Static 从 `ArkColumnNode.ets` 向 generated modifier 和 Static Model 追踪。
- 布局链路：从 `LinearLayoutPattern`、`LinearLayoutProperty` 进入 `LinearLayoutAlgorithm`，再到共享 `FlexLayoutAlgorithm`。
- Native Node：按 `NODE_COLUMN_` 或 `NODE_LINEAR_LAYOUT_` 属性名从 `style_modifier.cpp` 追踪到 `column_modifier.cpp`。
- 回归验证：优先运行 `test/unittest/core/pattern/linear_layout/`，再补充 Column modifier、Native Node 或组件测试样例。

## 相关主题

- Row 横向线性布局：`docs/kb/components/container/row.md`
- Flex 弹性布局与 Wrap：`docs/kb/components/container/flex.md`
- 基础布局属性：`docs/kb/capabilities/layout-attributes.md`
- 布局框架：`docs/kb/architecture/layout-framework.md`
- 安全区机制：`docs/kb/capabilities/safe-area.md`
