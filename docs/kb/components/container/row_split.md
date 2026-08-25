# RowSplit Context

> 文档版本：v1.0
> 更新时间：2026-07-24
> 来源：`docs/context_registry.json` 主题 `RowSplit`

## 定位

RowSplit 是 ArkUI 的横向分割布局容器，按水平方向排列子组件，并在相邻子组件之间提供纵向分隔区域；公开组件属性包含分隔区域是否可拖动。RowSplit 与 ColumnSplit 共享 `linear_split/` 下的 Pattern、布局算法、绘制实现和组件化产物。

本文档只提供 RowSplit 源码、SDK、API 解析、测试和 Spec 的稳定路由。具体布局约束、拖动边界、版本差异和公共属性语义应回到当前 SDK、源码、测试与 Spec 核实。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| Pattern 与交互 | `frameworks/core/components_ng/pattern/linear_split/linear_split_pattern.cpp`、`frameworks/core/components_ng/pattern/linear_split/linear_split_pattern.h` | RowSplit/ColumnSplit 共享的生命周期、拖动手势、鼠标与悬停处理入口；通过 `SplitType` 区分组件 |
| 布局算法 | `frameworks/core/components_ng/pattern/linear_split/linear_split_layout_algorithm.cpp`、`frameworks/core/components_ng/pattern/linear_split/linear_split_layout_algorithm.h` | 子组件测量、RowSplit 布局和拖动约束计算入口 |
| 布局属性 | `frameworks/core/components_ng/pattern/linear_split/linear_split_layout_property.h` | 可拖动状态与共享分割布局属性入口 |
| 分隔线绘制 | `frameworks/core/components_ng/pattern/linear_split/linear_split_paint_method.cpp`、`frameworks/core/components_ng/pattern/linear_split/linear_split_paint_method.h` | RowSplit 纵向分隔线绘制入口 |
| Dynamic Model | `frameworks/core/components_ng/pattern/linear_split/linear_split_model_ng.cpp`、`frameworks/core/components_ng/pattern/linear_split/linear_split_model_ng.h` | NG 节点创建与可拖动属性写入入口 |
| Static Model | `frameworks/core/components_ng/pattern/linear_split/linear_split_model_ng_static.cpp`、`frameworks/core/components_ng/pattern/linear_split/linear_split_model_ng_static.h` | Static FrameNode 创建入口 |
| 兼容管线 Model | `frameworks/core/components_ng/pattern/linear_split/linear_split_model_impl.cpp`、`frameworks/core/components/split_container/` | Dynamic modifier 为旧管线保留的兼容实现入口 |
| 组件化 Bridge | `frameworks/core/components_ng/pattern/linear_split/bridge/` | RowSplit/ColumnSplit 的统一 Bridge、Dynamic/Static modifier 和 Dynamic Module |
| node modifier 委托 | `frameworks/core/interfaces/native/node/row_split_modifier.cpp`、`frameworks/core/interfaces/native/node/row_split_modifier.h` | 通过 `DynamicModuleHelper` 获取 RowSplit 动态模块的内部委托层 |
| 组件构建与加载映射 | `frameworks/core/components_ng/pattern/linear_split/BUILD.gn`、`adapter/ohos/build/BUILD.gn`、`adapter/ohos/osal/dynamic_module_helper.cpp` | 共享 linear_split 模块构建、SO 聚合和 RowSplit 映射入口 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/row_split.d.ts` | `RowSplitInterface`、`RowSplitAttribute` 与 `resizeable` 声明 |
| Static API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/rowSplit.static.d.ets` | Static RowSplit 组件与属性声明 |
| Modifier API（Dynamic） | `<OH_ROOT>/interface/sdk-js/api/arkui/RowSplitModifier.d.ts` | Dynamic `RowSplitModifier` 声明 |
| Modifier API（Static） | `<OH_ROOT>/interface/sdk-js/api/arkui/RowSplitModifier.static.d.ets` | Static `RowSplitModifier` 声明 |
| Public Native Node API | `interfaces/native/native_node.h` | 当前未提供 `ARKUI_NODE_ROW_SPLIT` 或 `NODE_ROW_SPLIT_*` 专属公共入口；内部 RowSplit modifier 不是专属公开 C API |

API 检索建议：

- 组件创建和布局说明：搜索 `RowSplitInterface`、`RowSplit`。
- 分隔区域拖动：搜索 SDK 中实际采用的属性名 `resizeable`；不要改用其他拼写推断接口。
- Modifier：分别在 `RowSplitModifier.d.ts` 与 `RowSplitModifier.static.d.ets` 中核对范式声明。
- Native API：先在 `interfaces/native/native_node.h` 核对公开节点和属性枚举，不要从内部函数表推断公开 C API。

### API 解析实现路径

RowSplit **已完成组件化改造**：统一 Bridge、Dynamic/Static modifier 和 Dynamic Module 均位于 `pattern/linear_split/bridge/`，`DynamicModuleHelper` 将 RowSplit 映射到共享 linear_split 模块；当前没有旧 JSView 或旧 nativeModule RowSplit 解析文件。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| Dynamic 前端组件 | `frameworks/bridge/declarative_frontend/ark_component/components/arkrowsplit.js`、`frameworks/bridge/declarative_frontend/ark_component/src/ArkRowSplit.ts` | Dynamic 组件类和 AttributeModifier 下发入口 |
| 前端 Modifier | `frameworks/bridge/declarative_frontend/ark_modifier/src/row_split_modifier.ts` | RowSplit Modifier 模块加载与属性合并入口 |
| 统一 Bridge | `frameworks/core/components_ng/pattern/linear_split/bridge/arkts_native_row_split_bridge.cpp` | 创建、`resizeable` 和组件专用 clip 参数解析入口 |
| Dynamic Modifier | `frameworks/core/components_ng/pattern/linear_split/bridge/row_split_dynamic_modifier.cpp` | NG 与兼容管线的动态创建、属性和公共裁剪委托入口 |
| Static Modifier | `frameworks/core/components_ng/pattern/linear_split/bridge/row_split_static_modifier.cpp` | Static 节点构造和属性转换入口 |
| Dynamic Module | `frameworks/core/components_ng/pattern/linear_split/bridge/row_split_dynamic_module.cpp`、`frameworks/core/components_ng/pattern/linear_split/bridge/row_split_dynamic_module.h` | `RowSplitDynamicModule` 注册 Bridge 并导出 Dynamic、Static 和 CJ modifier |
| node modifier 委托层 | `frameworks/core/interfaces/native/node/row_split_modifier.cpp` | 通过 `DynamicModuleHelper` 加载共享组件模块并缓存内部 modifier |
| Static 接口聚合 | `frameworks/core/interfaces/native/implementation/row_split_modifier.cpp` | Static 生成接口到组件模块中 Static modifier 的委托入口 |
| Static ArkTS 组件 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/generated/component/rowSplit.ets` | Static peer、组件创建和属性下发入口；该文件由生成流程维护 |

组件化产物：`libarkui_linearsplit.z.so`。该共享库同时承载 RowSplit 与 ColumnSplit，不能据组件名推断为独立 `libarkui_rowsplit.z.so`。

### 外部依赖入口

外部仓路径以 OpenHarmony 根目录为基准；只列出由当前绘制源码和组件构建模板确认的入口。

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件 / 目标路径 | 说明 |
|----------|----------|------------|--------------------------------|------|
| 图形绘制与 RenderService | `frameworks/core/components_ng/pattern/linear_split/linear_split_paint_method.cpp`、`frameworks/core/components_ng/render/drawing.h`、`frameworks/core/components_ng/components.gni` | `<OH_ROOT>/foundation/graphic/graphic_2d` | `rosen/modules/2d_graphics/include/draw/`、`graphic_2d:2d_graphics`、`graphic_2d:librender_service_client` | 分隔线通过 Rosen Drawing 的 Canvas/Pen 接口绘制，组件构建模板提供图形依赖 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 共享 Pattern / Layout 单元测试 | `test/unittest/core/pattern/linear_split/` | RowSplit/ColumnSplit 节点、测量布局、拖动交互、分隔线和版本路径回归 |
| Static modifier 测试 | `test/unittest/capi/modifiers/row_split_modifier_test.cpp` | Static 生成式 RowSplit modifier 构造与属性回归，不代表专属公开 C API |
| 组件样例测试 | `test/component_test/test_cases/components/common_container/entry/src/main/ets/pages/row_split/` | RowSplit 创建和 `resizeable` 的组件级样例入口 |
| 测试构建入口 | `test/unittest/core/pattern/linear_split/BUILD.gn` | linear_split 定向单元测试目标与源码清单 |

### 相关 Spec

RowSplit 已在功能 registry 登记为功能 ID `05-01-10`，目标功能域为 `specs/05-ui-components/01-layout-components/10-row-split/`。

当前 functions/features registry 已有预登记，但目标目录中尚无实际 Feat 或设计文档，functions registry 中 `design` 也为空，因此本主题 `spec_status` 仍为 `pending`。后续补齐实际文档后，应同步更新 context registry 和本节。

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| RowSplit 创建失败 | Dynamic/Static SDK、统一 Bridge、对应 modifier、`LinearSplitModelNG` 与动态模块映射 |
| `resizeable` 未生效 | SDK 声明、前端 Modifier、RowSplit Bridge、Dynamic/Static modifier 和 `LinearSplitLayoutProperty` |
| 分隔区域无法拖动或拖动范围异常 | `LinearSplitPattern`、`LinearSplitLayoutAlgorithm` 和 linear_split 单元测试 |
| 子组件横向测量或布局异常 | `LinearSplitLayoutAlgorithm` 中 RowSplit 分支及当前父子布局约束 |
| 分隔线未绘制或位置异常 | `LinearSplitPaintMethod`、布局算法产出的分隔位置和图形绘制依赖 |
| Dynamic 与 Static 结果不一致 | 分别核对 RowSplit Dynamic/Static modifier、Static Model 和 modifier 测试 |
| 动态模块加载失败 | `dynamic_module_helper.cpp` 的 RowSplit 映射、RowSplit Dynamic Module、node modifier 与 linear_split BUILD |
| 查找 RowSplit 专属 Native Node C API | 当前公开 `native_node.h` 未提供该入口；内部 modifier 和 generated 接口不能当作公开 NDK API |

## 调试入口

- 创建与属性：Dynamic 从 ArkRowSplit 前端定义进入统一 Bridge 和 Dynamic modifier；Static 从生成组件进入 Static modifier 与 Static Model。
- 布局与拖动：以 `SplitType::ROW_SPLIT` 为检索词，在共享 Pattern、LayoutProperty 和 LayoutAlgorithm 中定位横向分割分支。
- 绘制：从 `LinearSplitPaintMethod` 检查分隔位置、绘制长度和 Rosen Canvas/Pen 调用入口。
- 组件化：确认 RowSplit 映射为 `linearsplit`，并检查 `libarkui_linearsplit.z.so` 是否随目标产物安装。
- 回归验证：优先运行 `test/unittest/core/pattern/linear_split/`，再补充 RowSplit modifier 与组件样例测试。

## 相关主题

- ColumnSplit：`docs/kb/components/container/column_split.md`
- Row：`docs/kb/components/container/row.md`
- Divider：`docs/kb/components/basic/divider.md`
- Layout Framework：`docs/kb/architecture/layout-framework.md`
- Layout Attributes：`docs/kb/capabilities/layout-attributes.md`
