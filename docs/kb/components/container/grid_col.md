# GridCol Context

> 文档版本：v1.0
> 更新时间：2026-07-18
> 来源：`docs/context_registry.json` 主题 `GridCol`

## 定位

GridCol 是 ArkUI 响应式栅格布局中的子容器，与 GridRow 配合使用；公开接口覆盖占列数、列偏移和排列顺序，并支持按断点配置。GridCol 与 GridRow 一同完成组件化改造，由 gridlayout 聚合模块承载。

GridCol 不等同于滚动型 Grid 的列模板或 GridItem。本文档只提供 GridCol 源码、SDK、解析链路、测试和 Spec 的稳定入口。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| Pattern | `frameworks/core/components_ng/pattern/grid_col/grid_col_layout_pattern.h` | GridCol Pattern、线性子布局和焦点属性入口 |
| Model | `frameworks/core/components_ng/pattern/grid_col/grid_col_model_ng.cpp`、`frameworks/core/components_ng/pattern/grid_col/grid_col_model_ng_static.cpp` | Dynamic/Static 节点创建与属性写入入口 |
| 布局算法 | `frameworks/core/components_ng/pattern/grid_col/grid_col_layout_algorithm.cpp`、`frameworks/core/components_ng/pattern/grid_col/grid_col_layout_algorithm.h` | GridCol 测量和子节点布局入口 |
| 布局属性 | `frameworks/core/components_ng/pattern/grid_col/grid_col_layout_property.cpp`、`frameworks/core/components_ng/pattern/grid_col/grid_col_layout_property.h` | span、offset、order 及栅格计算结果的属性入口 |
| 栅格公共工具 | `frameworks/core/components_ng/pattern/gridlayout/grid_container_utils.cpp`、`frameworks/core/components_ng/pattern/gridlayout/grid_container_utils.h` | GridRow/GridCol 共享的断点、列数、间距和列宽计算入口 |
| 组件化 Bridge | `frameworks/core/components_ng/pattern/grid_col/bridge/` | 统一 Bridge、Dynamic/Static Modifier 和 Dynamic Module |
| gridlayout 聚合模块 | `frameworks/core/components_ng/pattern/gridlayout/BUILD.gn`、`adapter/ohos/build/BUILD.gn` | GridCol、GridRow 和公共栅格工具的聚合及共享 SO 构建入口 |
| node modifier 委托 | `frameworks/core/interfaces/native/node/grid_col_modifier.cpp`、`frameworks/core/interfaces/native/node/grid_col_modifier.h` | 通过 `DynamicModuleHelper` 获取 GridCol 动态模块的内部委托层 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/grid_col.d.ts` | `GridColInterface`、`GridColOptions`、`GridColColumnOption` 和属性声明 |
| Static API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/gridCol.static.d.ets` | 静态 ArkTS GridCol 组件、options 和属性声明 |
| Modifier API (Dynamic) | `<OH_ROOT>/interface/sdk-js/api/arkui/GridColModifier.d.ts` | 动态 Modifier 声明 |
| Modifier API (Static) | `<OH_ROOT>/interface/sdk-js/api/arkui/GridColModifier.static.d.ets` | 静态 Modifier 声明 |
| Public Native Node API | `interfaces/native/native_node.h` | 当前未提供 `ARKUI_NODE_GRID_COL` 或 `NODE_GRID_COL_*` 专属公共入口；`NODE_GRID_COLUMN_TEMPLATE` 属于滚动型 Grid，不是 GridCol API |

API 检索建议：

- 构造参数与属性：搜索 `GridColOptions`、`GridColColumnOption`、`span`、`gridColOffset` 和 `order`。
- Modifier：在 `GridColModifier*.d.ts` / `GridColModifier*.d.ets` 中核对声明。
- Native API：不要把内部 `ArkUIGridColModifier` 或 Grid 的 `NODE_GRID_COLUMN_TEMPLATE` 解释为 GridCol 专属公共 C API。

### API 解析实现路径

GridCol **已完成组件化改造**，前端组件定义和属性解析统一路由到 `pattern/grid_col/bridge/`，并与 GridRow 共享 `libarkui_gridlayout.z.so`。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| 前端 JS/TS 定义 | `frameworks/bridge/declarative_frontend/ark_direct_component/src/arkgridcol.ts` | GridCol 前端容器类；ArkTS Modifier 类见 `frameworks/bridge/declarative_frontend/ark_modifier/src/grid_col_modifier.ts` |
| 统一 Bridge | `frameworks/core/components_ng/pattern/grid_col/bridge/arkts_native_grid_col_bridge.cpp` | 创建参数及 span、offset、order 的动态解析入口 |
| Dynamic Modifier | `frameworks/core/components_ng/pattern/grid_col/bridge/grid_col_dynamic_modifier.cpp` | 动态属性到 `GridColModelNG` 的写入入口，并保留兼容管线路由 |
| Static Modifier | `frameworks/core/components_ng/pattern/grid_col/bridge/grid_col_static_modifier.cpp` | 静态编译接口到 Static Model/ModelNG 的转换与写入入口 |
| Dynamic Module | `frameworks/core/components_ng/pattern/grid_col/bridge/grid_col_dynamic_module.cpp` | `GridColDynamicModule` 注册属性并提供动态、静态和 CJ modifier |
| node modifier 委托层 | `frameworks/core/interfaces/native/node/grid_col_modifier.cpp` | 通过 `DynamicModuleHelper` 转发到 gridlayout 模块中的 GridCol 实现 |

组件化产物：`libarkui_gridlayout.z.so`。该共享库同时承载 GridCol、GridRow 和栅格公共工具，不能据组件名推断为 `libarkui_gridcol.z.so`。

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| Pattern 单元测试 | `test/unittest/core/pattern/grid_col/` | 节点创建、属性、测量与栅格协同布局回归 |
| 内部 modifier 单元测试 | `test/unittest/capi/modifiers/grid_col_modifier_test.cpp` | `ArkUIGridColModifier` 内部函数表契约验证，不代表专属公共 C API |
| 组件样例测试 | `test/component_test/test_cases/components/common_container/entry/src/main/ets/pages/grid_col/` | span、offset 和 order 的组件级样例入口 |
| 栅格公共工具测试 | `test/unittest/core/pattern/grid_row/feature/grid_container_utils_test_ng.cpp` | GridRow/GridCol 共享栅格计算工具回归 |

### 相关 Spec

GridCol 功能域：`specs/05-ui-components/01-layout-components/06-grid-col/`（功能 ID `05-01-06`）。

| Feat | 稳定路径 | 主题 |
|------|----------|------|
| Feat-01 | `specs/05-ui-components/01-layout-components/06-grid-col/Feat-01-grid-col-creation-responsive-span-spec.md` | 创建与响应式占列 |
| Feat-02 | `specs/05-ui-components/01-layout-components/06-grid-col/Feat-02-grid-col-offset-order-layout-spec.md` | 偏移、排序和协同布局 |
| Feat-03 | `specs/05-ui-components/01-layout-components/06-grid-col/Feat-03-grid-col-multi-paradigm-version-spec.md` | 多范式接口与版本兼容 |
| 设计文档 | `specs/05-ui-components/01-layout-components/06-grid-col/design.md` | 模块边界与实现设计 |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| GridCol 占列结果异常 | SDK `span` 声明、统一 Bridge、`grid_col_layout_property.*` 和 Feat-01 |
| offset 或 order 未生效 | SDK 对应属性、Dynamic/Static Modifier、GridRow 布局算法和 Feat-02 |
| 不同断点下配置选择异常 | `GridColColumnOption` 声明、`grid_container_utils.*`、GridRow 当前断点计算 |
| GridCol 子内容布局异常 | `grid_col_layout_algorithm.*`、`grid_col_layout_pattern.h` 及父 GridRow 约束 |
| 将 GridCol 与 Grid/GridItem 混淆 | GridCol 进入 `pattern/grid_col/`；滚动 Grid 与 GridItem 进入 `pattern/grid/` |
| 动态模块加载失败 | `grid_col_dynamic_module.cpp`、`grid_col_modifier.cpp`、`dynamic_module_helper.cpp` 与 gridlayout 构建入口 |

## 调试入口

- 创建链路：从前端 GridCol 定义进入统一 Bridge，再核对 Dynamic/Static Modifier 与 Model。
- 属性链路：按 span、offset、order 定位 Bridge 解析、Model 写入和 `GridColLayoutProperty`。
- 协同布局：同时记录父 GridRow 的当前断点、列数、gutter 与 GridCol 的属性选择结果。
- 组件化链路：确认 GridCol 映射到 gridlayout 模块，且 `libarkui_gridlayout.z.so` 已随目标产物安装。
- 回归验证：优先运行 GridCol Pattern 测试，并补充 GridRow 栅格协同与公共工具用例。

## 相关主题

- GridRow：`docs/kb/components/container/grid_row.md`
- Layout Framework：`docs/kb/architecture/layout-framework.md`
- 基础布局属性：`docs/kb/capabilities/layout-attributes.md`
- 滚动型 Grid：`frameworks/core/components_ng/pattern/grid/`
