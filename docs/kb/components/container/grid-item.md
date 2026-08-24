# GridItem Context

> 文档版本：v1.0
> 更新时间：2026-07-29
> 来源：`docs/context_registry.json` 主题 `GridItem`

## 定位

GridItem 是 Grid 滚动型网格容器的子组件，定义单个网格项的布局位置（rowStart/rowEnd/columnStart/columnEnd 跨行列属性）、选择状态（selectable/selected/onSelect）和样式（GridItemStyle NONE/PLAIN）。GridItemPattern 继承 SelectableItemPattern，选择能力来自基类。

GridItem 不等同于 GridCol。本文档只提供 GridItem 源码、SDK、解析链路、测试和 Spec 的稳定入口。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| Pattern | `frameworks/core/components_ng/pattern/grid/grid_item_pattern.h` | GridItemPattern 继承 SelectableItemPattern；MarkIsSelected/FireSelectChangeEvent 入口 |
| Model | `frameworks/core/components_ng/pattern/grid/grid_item_model_ng.cpp`、`frameworks/core/components_ng/pattern/grid/grid_item_model_static.cpp` | Dynamic/Static 节点创建与属性写入入口 |
| 布局属性 | `frameworks/core/components_ng/pattern/grid/grid_item_layout_property.cpp` | rowStart/rowEnd/columnStart/columnEnd；setter 调用 ResetGridLayoutInfoAndMeasure |
| 布局算法 | `frameworks/core/components_ng/pattern/grid/grid_item_layout_algorithm.h` | GridItem 测量与布局入口 |
| 事件 | `frameworks/core/components_ng/pattern/grid/grid_item_event_hub.h` | GridItem 事件入口 |
| 组件化 Bridge | `frameworks/core/components_ng/pattern/grid/bridge/griditem/` | 统一 Bridge、Dynamic/Static Modifier 和 Dynamic Module |
| node modifier 委托 | `frameworks/core/interfaces/native/node/grid_item_modifier.cpp` | 通过 DynamicModuleHelper 转发到 Grid 动态模块 |
| implementation modifier | `frameworks/core/interfaces/native/implementation/grid_item_modifier.cpp` | 静态 C-API 属性设置入口 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/grid_item.d.ts` | GridItemInterface、GridItemOptions、GridItemStyle 声明 |
| Static API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/gridItem.static.d.ets` | 静态 ArkTS GridItem 组件和属性声明 |
| Modifier API (Dynamic) | `<OH_ROOT>/interface/sdk-js/api/arkui/GridItemModifier.d.ts` | 动态 Modifier 声明 |
| Modifier API (Static) | `<OH_ROOT>/interface/sdk-js/api/arkui/GridItemModifier.static.d.ets` | 静态 Modifier 声明 |
| C API 属性枚举 | `interfaces/native/native_node.h` | NODE_GRID_ITEM_ROW_START / ROW_END / COLUMN_START / COLUMN_END / SELECTABLE / SELECTED |

API 检索建议：

- 构造参数与属性：搜索 `GridItem(value?: GridItemOptions)`、`GridItemStyle`、`rowStart`、`rowEnd`、`columnStart`、`columnEnd`、`selectable`、`selected`。
- 样式：搜索 `GridItemStyle.NONE`、`GridItemStyle.PLAIN`、`UpdateGridItemStyle`。
- C API：搜索 `NODE_GRID_ITEM_`。

### API 解析实现路径

GridItem **已完成组件化改造**，与 Grid 共享 `libarkui_grid.z.so`，属性解析统一路由到 `pattern/grid/bridge/griditem/`。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| 前端 JS/TS 定义 | `frameworks/bridge/declarative_frontend/ark_direct_component/src/arkgriditem.ts` | GridItem 前端容器类 |
| 统一 Bridge | `frameworks/core/components_ng/pattern/grid/bridge/griditem/arkts_native_grid_item_bridge.cpp` | 创建参数及 span/selectable/selected 的动态解析入口 |
| Dynamic Modifier | `frameworks/core/components_ng/pattern/grid/bridge/griditem/grid_item_dynamic_modifier.cpp` | 动态属性到 GridItemModelNG 的写入入口 |
| Static Modifier | `frameworks/core/components_ng/pattern/grid/bridge/griditem/grid_item_static_modifier.cpp` | 静态编译接口写入入口 |
| Dynamic Module | `frameworks/core/components_ng/pattern/grid/bridge/griditem/grid_item_dynamic_module.cpp` | GridItemDynamicModule 注册属性 |
| node modifier 委托层 | `frameworks/core/interfaces/native/node/grid_item_modifier.cpp` | 通过 DynamicModuleHelper 转发到 Grid 动态模块 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| Pattern 单元测试 | `test/unittest/core/pattern/grid/` | GridItem 属性、选择、编辑模式等回归（GridItem 测试与 Grid 共享目录） |
| 内部 modifier 单元测试 | `test/unittest/capi/modifiers/grid_item_modifier_test.cpp` | 内部函数表契约验证 |

### 相关 Spec

GridItem 与 Grid 共享同一功能域：`specs/05-ui-components/03-scroll-container-components/04-grid-grid-item/`（功能 ID `05-03-04`）。

| Feat | 稳定路径 | 主题 |
|------|----------|------|
| Feat-05 | `specs/05-ui-components/03-scroll-container-components/04-grid-grid-item/Feat-05-grid-item-layout-selection-spec.md` | GridItem 布局与选择 |
| Feat-06 | `specs/05-ui-components/03-scroll-container-components/04-grid-grid-item/Feat-06-grid-capi-multi-paradigm-spec.md` | C API 与多范式接口（含 GridItem C-API） |
| 设计文档 | `specs/05-ui-components/03-scroll-container-components/04-grid-grid-item/design.md` | 架构设计 |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| span 属性不生效 | `grid_item_layout_property.cpp`；仅在设置了模板的 Grid 中生效；无模板时 span 属性无效 |
| span 变更后布局未更新 | setter 调用 ResetGridLayoutInfoAndMeasure 触发父级 Grid 重布局 |
| selected 双向绑定不生效 | @since 10 支持 $$；@since 8-9 仅单向 |
| GridItemStyle 无动画 | NONE 模式无 borderRadius/hover/press；使用 PLAIN 获得主题圆角和动画 |
| selectable=false 后仍选中 | SetSelectable(false) 会调用 MarkIsSelected(false) 取消选中并触发事件 |
| 将 GridItem 与 GridCol 混淆 | GridItem 是 Grid 的子组件；GridCol 是 GridRow 的子组件 |

## 调试入口

- 属性链路：从前端 GridItem 定义进入统一 Bridge，再核对 Dynamic/Static Modifier 与 Model。
- 选择链路：GridItemPattern 继承 SelectableItemPattern；MarkIsSelected + FireSelectChangeEvent 触发 selectChangeEvent_ 和 onSelect_ 双事件。
- 样式链路：GridItemStyle.NONE/PLAIN 在 UpdateGridItemStyle() 中切换；PLAIN 注册 hover blend 和 press blend 动画。
- 组件化链路：确认 GridItem 映射到 `libarkui_grid.z.so`，与 Grid 共享动态库。

## 相关主题

- [Grid](grid.md)
- [GridRow](grid-row.md)
- [GridCol](grid-col.md)
- [SelectableItemPattern](grid-item.md)