# Grid Context

> 文档版本：v1.0
> 更新时间：2026-07-29
> 来源：`docs/context_registry.json` 主题 `Grid`

## 定位

Grid 是 ArkUI 滚动型网格布局容器组件，按行列形式排列子组件。Grid 支持 6 种布局算法（自适应、静态、单模板滚动、带选项滚动、不规则、自定义），由 `CreateLayoutAlgorithm()` 根据模板/选项参数级联分发。Grid 继承 ScrollablePattern，所有滚动基础设施来自基类。

Grid 不等同于 GridRow/GridCol 栅格布局。本文档只提供 Grid 源码、SDK、解析链路、测试和 Spec 的稳定入口。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| Pattern | `frameworks/core/components_ng/pattern/grid/grid_pattern.h` | GridPattern 继承 SelectableContainerPattern；布局算法分发、滚动控制、事件注册入口 |
| Model | `frameworks/core/components_ng/pattern/grid/grid_model_ng.cpp`、`frameworks/core/components_ng/pattern/grid/grid_model_static.cpp` | Dynamic/Static 节点创建与属性写入入口 |
| 布局属性 | `frameworks/core/components_ng/pattern/grid/grid_layout_property.cpp` | 模板/间距/方向/缓存/irregular_/userDefined_ 标志属性入口 |
| 布局信息 | `frameworks/core/components_ng/pattern/grid/grid_layout_info.cpp` | 核心数据结构 GridLayoutInfo（gridMatrix_、lineHeightMap_、startIndex_ 等） |
| 布局选项 | `frameworks/core/components_ng/pattern/grid/grid_layout_options.h` | GridLayoutOptions、GridItemSize、GridItemRect、GridStartLineInfo |
| 事件 | `frameworks/core/components_ng/pattern/grid/grid_event_hub.h` | GridEventHub 拖拽/选择事件入口 |
| 焦点 | `frameworks/core/components_ng/pattern/grid/grid_focus.h` | 焦点导航与遍历 |
| 拖拽管理 | `frameworks/core/components_ng/pattern/grid/grid_item_drag_manager.h` | GridItemDragManager 状态机（IDLE→LONG_PRESS→DRAGGING） |
| 自适应算法 | `frameworks/core/components_ng/pattern/grid/grid_adaptive/` | GridAdaptiveLayoutAlgorithm（无模板，cellLength/maxCount/minCount） |
| 静态算法 | `frameworks/core/components_ng/pattern/grid/grid_layout/` | GridLayoutAlgorithm（双模板，非滚动） |
| 滚动算法 | `frameworks/core/components_ng/pattern/grid/grid_scroll/` | GridScrollLayoutAlgorithm + GridScrollWithOptionsLayoutAlgorithm |
| 不规则算法 | `frameworks/core/components_ng/pattern/grid/irregular/` | GridIrregularLayoutAlgorithm + GridIrregularFiller + GridLayoutRangeSolver |
| 自定义算法 | `frameworks/core/components_ng/pattern/grid/grid_custom/` | GridCustomLayoutAlgorithm（onGetRectByIndex + 双 systemapi 回调） |
| 基类算法 | `frameworks/core/components_ng/pattern/grid/grid_layout_base_algorithm.h` | 布局算法基类 |
| 模板解析 | `frameworks/core/components_ng/property/templates_parser.cpp` | fr/px/%/repeat 语法解析 |
| 组件化 Bridge | `frameworks/core/components_ng/pattern/grid/bridge/` | 统一 Bridge、Dynamic/Static Modifier 和 Dynamic Module |
| node modifier 委托 | `frameworks/core/interfaces/native/node/grid_modifier.cpp` | 通过 DynamicModuleHelper 转发到 Grid 动态模块 |
| implementation modifier | `frameworks/core/interfaces/native/implementation/grid_modifier.cpp` | 静态 C-API 属性设置入口 |
| C-API GridLayoutOptions | `interfaces/native/node/grid_layout_option.h` | OH_ArkUI_GridLayoutOptions_* 函数族 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/grid.d.ts` | GridInterface、GridAttribute、GridLayoutOptions 声明 |
| Static API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/grid.static.d.ets` | 静态 ArkTS Grid 组件和属性声明 |
| Modifier API (Dynamic) | `<OH_ROOT>/interface/sdk-js/api/arkui/GridModifier.d.ts` | 动态 Modifier 声明 |
| Modifier API (Static) | `<OH_ROOT>/interface/sdk-js/api/arkui/GridModifier.static.d.ets` | 静态 Modifier 声明 |
| C API 属性枚举 | `interfaces/native/native_node.h` | NODE_GRID_COLUMN_TEMPLATE / ROW_TEMPLATE / CACHED_COUNT / ALIGN_ITEMS / LAYOUT_OPTIONS / ITEMFILLPOLICY 等 |
| C API GridItem 属性枚举 | `interfaces/native/native_node.h` | NODE_GRID_ITEM_ROW_START / ROW_END / COLUMN_START / COLUMN_END / SELECTABLE / SELECTED |

API 检索建议：

- 构造参数与属性：搜索 `Grid(scroller?, layoutOptions?)`、`columnsTemplate`、`rowsTemplate`、`GridLayoutOptions`。
- 布局算法选择：搜索 `CreateLayoutAlgorithm()`、`irregular_`、`userDefined_`。
- C API：搜索 `NODE_GRID_`、`ArkUI_GridLayoutOptions`、`ArkUI_GridItemSize`、`ArkUI_GridItemRect`。

### API 解析实现路径

Grid **已完成组件化改造**，前端组件定义和属性解析统一路由到 `pattern/grid/bridge/`，输出 `libarkui_grid.z.so`。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| 前端 JS/TS 定义 | `frameworks/bridge/declarative_frontend/ark_direct_component/src/arkgrid.ts` | Grid 前端容器类；ArkTS Modifier 类见 `frameworks/bridge/declarative_frontend/ark_modifier/src/grid_modifier.ts` |
| 统一 Bridge（Grid） | `frameworks/core/components_ng/pattern/grid/bridge/grid/arkts_native_grid_bridge.cpp` | 通过 `IsJsView()` 区分模式，统一参数解析 |
| Dynamic Modifier（Grid） | `frameworks/core/components_ng/pattern/grid/bridge/grid/grid_dynamic_modifier.cpp` | 动态属性到 GridModelNG 的写入入口 |
| Static Modifier（Grid） | `frameworks/core/components_ng/pattern/grid/bridge/grid/grid_static_modifier.cpp` | 静态编译接口到 Static Model/ModelNG 的转换与写入入口 |
| Dynamic Module（Grid） | `frameworks/core/components_ng/pattern/grid/bridge/grid/grid_dynamic_module.cpp` | GridDynamicModule 注册属性并提供动态、静态和 CJ modifier |
| 统一 Bridge（GridItem） | `frameworks/core/components_ng/pattern/grid/bridge/griditem/arkts_native_grid_item_bridge.cpp` | GridItem 创建参数及 span/selectable/selected 解析入口 |
| Dynamic Modifier（GridItem） | `frameworks/core/components_ng/pattern/grid/bridge/griditem/grid_item_dynamic_modifier.cpp` | GridItem 动态属性写入入口 |
| Static Modifier（GridItem） | `frameworks/core/components_ng/pattern/grid/bridge/griditem/grid_item_static_modifier.cpp` | GridItem 静态编译接口写入入口 |
| Dynamic Module（GridItem） | `frameworks/core/components_ng/pattern/grid/bridge/griditem/grid_item_dynamic_module.cpp` | GridItemDynamicModule 注册属性 |
| node modifier 委托层 | `frameworks/core/interfaces/native/node/grid_modifier.cpp`、`frameworks/core/interfaces/native/node/grid_item_modifier.cpp` | 通过 DynamicModuleHelper 转发到 Grid 动态模块 |

组件化产物：`libarkui_grid.z.so`。Grid 和 GridItem 共享此动态库。

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| Pattern 单元测试 | `test/unittest/core/pattern/grid/` | 属性、布局、滚动、事件、焦点、编辑模式、拖拽等回归 |
| 不规则布局测试 | `test/unittest/core/pattern/grid/irregular/` | GridIrregularFiller、GridIrregularLayoutAlgorithm 回归 |
| 自定义布局测试 | `test/unittest/core/pattern/grid/custom/` | GridCustomLayoutAlgorithm 回归 |
| 内部 modifier 单元测试 | `test/unittest/capi/modifiers/grid_modifier_test.cpp`、`grid_item_modifier_test.cpp` | 内部函数表契约验证 |

### 相关 Spec

Grid 功能域：`specs/05-ui-components/03-scroll-container-components/04-grid-grid-item/`（功能 ID `05-03-04`）。

| Feat | 稳定路径 | 主题 |
|------|----------|------|
| Feat-01 | `specs/05-ui-components/03-scroll-container-components/04-grid-grid-item/Feat-01-grid-fixed-scroll-layout-spec.md` | 固定行列与单轴滚动布局 |
| Feat-02 | `specs/05-ui-components/03-scroll-container-components/04-grid-grid-item/Feat-02-grid-irregular-adaptive-custom-layout-spec.md` | 不规则、自适应与自定义布局 |
| Feat-03 | `specs/05-ui-components/03-scroll-container-components/04-grid-grid-item/Feat-03-grid-scroll-scrollbar-events-spec.md` | 滚动控制、滚动条与事件 |
| Feat-04 | `specs/05-ui-components/03-scroll-container-components/04-grid-grid-item/Feat-04-grid-edit-mode-drag-spec.md` | 编辑模式与拖拽 |
| Feat-05 | `specs/05-ui-components/03-scroll-container-components/04-grid-grid-item/Feat-05-grid-item-layout-selection-spec.md` | GridItem 布局与选择 |
| Feat-06 | `specs/05-ui-components/03-scroll-container-components/04-grid-grid-item/Feat-06-grid-capi-multi-paradigm-spec.md` | C API 与多范式接口 |
| 设计文档 | `specs/05-ui-components/03-scroll-container-components/04-grid-grid-item/design.md` | 架构设计（6 种算法分发、15 个 ADR） |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 布局算法选择不正确 | `grid_pattern.h` 的 `CreateLayoutAlgorithm()`、`grid_layout_property.cpp` 的 `UpdateIrregularFlag()` |
| 不规则项未触发 irregular_ | 纵向模式下仅 rowSpan>1 触发 irregular_；横向模式下 columns>1 也会触发；columnSpan>1 在纵向模式下走 GridScrollWithOptionsLayoutAlgorithm |
| 自适应网格不可滚动 | GridAdaptiveLayoutAlgorithm 的 IsConfiguredScrollable()=false；使用单模板代替 |
| 双模板模式无滚动条 | IsConfiguredScrollable()=false，scrollBar 自动设 OFF |
| scrollToIndex 默认对齐 | Grid 默认 align=AUTO（不同于 List 的 START） |
| columnsTemplate 与 ItemFillPolicy 互斥 | 设置一个自动 reset 另一个 |
| layoutDirection 在滚动模式无效 | 仅自适应模式生效，滚动模式由模板决定轴向 |
| C-API regularSize 设置无效 | C-API 硬编码 [1,1]，开发者设置被忽略 |
| C-API 缺少 onGetStartIndexByOffset/OnGetStartIndexByIndex | @systemapi 回调未暴露在 C-API |
| 拖拽时鼠标滚动不响应 | onItemDragStart 注册后 GetIsAllowMouse()=false |
| GridItemStyle 无动画 | NONE 模式无 borderRadius/hover/press；使用 PLAIN 获得动画 |
| 将 Grid 与 GridRow/GridCol 混淆 | 滚动型 Grid 进入 `pattern/grid/`；栅格布局进入 `pattern/grid_row/`/`pattern/grid_col/` |

## 调试入口

- 布局算法链路：从前端 Grid 定义进入统一 Bridge，再核对 Dynamic/Static Modifier 与 Model；从 `CreateLayoutAlgorithm()` 确认算法分发路径。
- 滚动链路：Grid 继承 ScrollablePattern，所有滚动控制/事件/Scroller 方法由基类提供；Grid 在 OnModifyDone 中初始化。
- 拖拽链路：旧系统 GridEventHub::GetEditable() + 新系统 GridItemDragManager 状态机；editMode 控制旧系统守卫。
- 组件化链路：确认 Grid 映射到 `libarkui_grid.z.so`，且动态模块已安装。
- 回归验证：优先运行 `test/unittest/core/pattern/grid/` 下的 Pattern 测试，按需补充 irregular/ 和 custom/ 子目录用例。

## 相关主题

- GridItem：`docs/kb/components/container/grid_item.md`
- GridRow：`docs/kb/components/container/grid_row.md`
- GridCol：`docs/kb/components/container/grid_col.md`
- LazyGrid：`docs/pattern/lazy_layout/LazyGrid_Knowledge_Base.md`
- ScrollablePattern：`frameworks/core/components_ng/pattern/scrollable/`
- 布局属性：`docs/kb/capabilities/layout-attributes.md`
