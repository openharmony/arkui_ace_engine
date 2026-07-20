# GridRow Context

> 文档版本：v1.0
> 更新时间：2026-07-18
> 来源：`docs/context_registry.json` 主题 `GridRow`

## 定位

GridRow 是 ArkUI 的响应式栅格容器，与 GridCol 配合使用；公开接口覆盖列系统、水平/垂直间距、断点、排列方向、子项对齐和断点变化事件。GridRow 与 GridCol 一同完成组件化改造，由 gridlayout 聚合模块承载。

GridRow 不等同于滚动型 Grid 的行模板。本文档只提供 GridRow 源码、SDK、解析链路、外部依赖、测试和 Spec 的稳定入口。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| Pattern 与生命周期 | `frameworks/core/components_ng/pattern/grid_row/grid_row_layout_pattern.cpp`、`frameworks/core/components_ng/pattern/grid_row/grid_row_layout_pattern.h` | GridRow Pattern、布局算法、事件和多线程布局入口 |
| Model | `frameworks/core/components_ng/pattern/grid_row/grid_row_model_ng.cpp`、`frameworks/core/components_ng/pattern/grid_row/grid_row_model_ng_static.cpp` | Dynamic/Static 节点创建、属性和事件写入入口 |
| 布局算法 | `frameworks/core/components_ng/pattern/grid_row/grid_row_layout_algorithm.cpp`、`frameworks/core/components_ng/pattern/grid_row/grid_row_layout_algorithm.h` | 当前断点、列数、gutter、换行和子节点放置入口 |
| 布局属性 | `frameworks/core/components_ng/pattern/grid_row/grid_row_layout_property.cpp`、`frameworks/core/components_ng/pattern/grid_row/grid_row_layout_property.h` | columns、gutter、breakpoints、direction、alignItems 等属性入口 |
| 断点事件 | `frameworks/core/components_ng/pattern/grid_row/grid_row_event_hub.h` | 断点变化事件存储与触发入口 |
| 多线程布局 | `frameworks/core/components_ng/pattern/grid_row/grid_row_layout_pattern_multi_thread.cpp` | GridRow 多线程布局数据准备入口 |
| 栅格公共工具 | `frameworks/core/components_ng/pattern/gridlayout/grid_container_utils.cpp`、`frameworks/core/components_ng/pattern/gridlayout/grid_container_utils.h` | GridRow/GridCol 共享的断点、列数、间距和列宽计算入口 |
| 组件化 Bridge | `frameworks/core/components_ng/pattern/grid_row/bridge/` | 统一 Bridge、Dynamic/Static Modifier 和 Dynamic Module |
| gridlayout 聚合模块 | `frameworks/core/components_ng/pattern/gridlayout/BUILD.gn`、`adapter/ohos/build/BUILD.gn` | GridRow、GridCol 和公共栅格工具的聚合及共享 SO 构建入口 |
| node modifier 委托 | `frameworks/core/interfaces/native/node/grid_row_modifier.cpp`、`frameworks/core/interfaces/native/node/grid_row_modifier.h` | 通过 `DynamicModuleHelper` 获取 GridRow 动态模块的内部委托层 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/grid_row.d.ts` | `GridRowInterface`、options、断点类型、方向枚举、属性和事件声明 |
| Static API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/gridRow.static.d.ets` | 静态 ArkTS GridRow 组件、options、属性和事件声明 |
| Modifier API (Dynamic) | `<OH_ROOT>/interface/sdk-js/api/arkui/GridRowModifier.d.ts` | 动态 Modifier 声明 |
| Modifier API (Static) | `<OH_ROOT>/interface/sdk-js/api/arkui/GridRowModifier.static.d.ets` | 静态 Modifier 声明 |
| Public Native Node API | `interfaces/native/native_node.h` | 当前未提供 `ARKUI_NODE_GRID_ROW` 或 `NODE_GRID_ROW_*` 专属公共入口；`NODE_GRID_ROW_TEMPLATE` 属于滚动型 Grid，不是 GridRow API |

API 检索建议：

- 构造参数：搜索 `GridRowOptions`、`GridRowColumnOption`、`GutterOption`、`BreakPoints` 和 `GridRowDirection`。
- 属性与事件：搜索 `alignItems` 和 `onBreakpointChange`。
- Native API：不要把内部 `ArkUIGridRowModifier` 或 Grid 的 `NODE_GRID_ROW_TEMPLATE` 解释为 GridRow 专属公共 C API。

### API 解析实现路径

GridRow **已完成组件化改造**，前端组件定义和属性解析统一路由到 `pattern/grid_row/bridge/`，并与 GridCol 共享 `libarkui_gridlayout.z.so`。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| 前端 JS/TS 定义 | `frameworks/bridge/declarative_frontend/ark_direct_component/src/arkgridrow.ts` | GridRow 前端容器类；ArkTS Modifier 类见 `frameworks/bridge/declarative_frontend/ark_modifier/src/grid_row_modifier.ts` |
| 统一 Bridge | `frameworks/core/components_ng/pattern/grid_row/bridge/arkts_native_grid_row_bridge.cpp` | 创建参数、属性和断点变化事件的动态解析入口 |
| Dynamic Modifier | `frameworks/core/components_ng/pattern/grid_row/bridge/grid_row_dynamic_modifier.cpp` | 动态属性与事件到 `GridRowModelNG` 的写入入口，并保留兼容管线路由 |
| Static Modifier | `frameworks/core/components_ng/pattern/grid_row/bridge/grid_row_static_modifier.cpp` | 静态编译接口到 Static Model/ModelNG 的转换、回调和写入入口 |
| Dynamic Module | `frameworks/core/components_ng/pattern/grid_row/bridge/grid_row_dynamic_module.cpp` | `GridRowDynamicModule` 注册属性并提供动态、静态和 CJ modifier |
| node modifier 委托层 | `frameworks/core/interfaces/native/node/grid_row_modifier.cpp` | 通过 `DynamicModuleHelper` 转发到 gridlayout 模块中的 GridRow 实现 |

组件化产物：`libarkui_gridlayout.z.so`。该共享库同时承载 GridRow、GridCol 和栅格公共工具，不能据组件名推断为 `libarkui_gridrow.z.so`。

### 外部依赖入口

外部仓路径以 OpenHarmony 根目录为基准。

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件 / 目标路径 | 说明 |
|----------|----------|------------|--------------------------------|------|
| 窗口模式 | `frameworks/core/components_ng/pattern/grid_row/grid_row_layout_algorithm.cpp`、`frameworks/core/pipeline/container_window_manager.h`、`adapter/ohos/entrance/ace_container.cpp` | `foundation/window/window_manager` | `window_manager:libwm` | GridRow 通过 Pipeline 的 WindowManager 抽象取得窗口模式，参与响应式断点计算 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| Pattern 单元测试 | `test/unittest/core/pattern/grid_row/` | 列系统、gutter、断点、事件、排列、测量、布局策略和多线程回归 |
| 内部 modifier 单元测试 | `test/unittest/capi/modifiers/grid_row_modifier_test.cpp` | `ArkUIGridRowModifier` 内部函数表契约验证，不代表专属公共 C API |
| Static 生成接口测试 | `test/unittest/capi/modifiers/generated/grid_row_modifier_test.cpp` | 静态生成 modifier 的构造、属性和事件入口回归 |
| 组件样例测试 | `test/component_test/test_cases/components/common_container/entry/src/main/ets/pages/grid_row/` | GridRow 对齐等公开能力的组件级样例入口 |

### 相关 Spec

GridRow 功能域：`specs/05-ui-components/01-layout-components/07-grid-row/`（功能 ID `05-01-07`）。

| Feat | 稳定路径 | 主题 |
|------|----------|------|
| Feat-01 | `specs/05-ui-components/01-layout-components/07-grid-row/Feat-01-grid-row-columns-gutter-spec.md` | 列系统与间距 |
| Feat-02 | `specs/05-ui-components/01-layout-components/07-grid-row/Feat-02-grid-row-breakpoints-event-spec.md` | 响应式断点与变更事件 |
| Feat-03 | `specs/05-ui-components/01-layout-components/07-grid-row/Feat-03-grid-row-arrangement-alignment-rtl-spec.md` | 排列、换行、对齐和 RTL |
| Feat-04 | `specs/05-ui-components/01-layout-components/07-grid-row/Feat-04-grid-row-multi-paradigm-version-spec.md` | 多范式接口与版本兼容 |
| 设计文档 | `specs/05-ui-components/01-layout-components/07-grid-row/design.md` | 模块边界与实现设计 |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 列数或 gutter 计算异常 | SDK `GridRowOptions`、`grid_row_layout_property.*`、`grid_container_utils.*` 和 Feat-01 |
| 断点选择或变化事件异常 | SDK `BreakPoints` / `onBreakpointChange`、布局算法、EventHub 和 Feat-02 |
| GridCol 换行、顺序或位置异常 | `grid_row_layout_algorithm.*`、对应 GridCol LayoutProperty 和 Feat-03 |
| direction、alignItems 或 RTL 表现异常 | SDK 属性声明、Dynamic/Static Modifier、布局算法和 Feat-03 |
| 动态与静态范式结果不一致 | `grid_row_dynamic_modifier.cpp`、`grid_row_static_modifier.cpp` 和 Feat-04 |
| 将 GridRow 与 Grid 行模板混淆 | GridRow 进入 `pattern/grid_row/`；`NODE_GRID_ROW_TEMPLATE` 和滚动布局进入 `pattern/grid/` |
| 动态模块加载失败 | `grid_row_dynamic_module.cpp`、`grid_row_modifier.cpp`、`dynamic_module_helper.cpp` 与 gridlayout 构建入口 |

## 调试入口

- 创建链路：从前端 GridRow 定义进入统一 Bridge，再核对 Dynamic/Static Modifier 与 Model。
- 响应式链路：同时记录布局可用尺寸、窗口模式、breakpoints 配置和最终 GridSizeType。
- 栅格链路：核对 columns、gutter、当前断点以及各 GridCol 的 span、offset、order。
- 事件链路：从 Bridge/Static callback 进入 Model 和 `GridRowEventHub`，再确认布局后事件任务。
- 组件化链路：确认 GridRow 映射到 gridlayout 模块，且 `libarkui_gridlayout.z.so` 已随目标产物安装。
- 回归验证：优先运行 GridRow feature、layout 和 measure 子目录中的定向用例。

## 相关主题

- GridCol：`docs/kb/components/container/grid_col.md`
- Layout Framework：`docs/kb/architecture/layout-framework.md`
- 基础布局属性：`docs/kb/capabilities/layout-attributes.md`
- 滚动型 Grid：`frameworks/core/components_ng/pattern/grid/`
