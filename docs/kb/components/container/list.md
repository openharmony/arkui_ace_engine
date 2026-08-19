# List Context

> 文档版本：v1.0
> 更新时间：2026-07-29
> 来源：`docs/context_registry.json` 主题 `List`

## 定位

List 是 ArkUI 的列表容器组件，继承 `SelectableContainerPattern`，支持纵向/横向布局、多 lanes、分隔线、childrenMainSize 精确预测量、懒加载缓存（cachedCount/syncLoad）、链动画、嵌套滚动、分组（ListItemGroup）、选择/编辑模式、拖拽排序、ListItem 滑动操作。List/ListItem/ListItemGroup 三者经 `ListLayoutAlgorithm` 协同渲染。

本文档用于快速定位 List 相关源码、SDK 声明、测试和规格文档。具体行为、默认值、边界条件和兼容性说明以对应 SDK 声明、源码实现、测试用例和 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| List Pattern（索引/手势/链动画/事件） | `frameworks/core/components_ng/pattern/list/list_pattern.cpp` | `ListPattern : SelectableContainerPattern`，默认 edgeEffect=Spring |
| ListItem Pattern（滑动状态机/选择） | `frameworks/core/components_ng/pattern/list/list_item_pattern.cpp` | `SWIPER_START/END/ACTION` 状态机 |
| ListItemGroup Pattern（分组 header/footer） | `frameworks/core/components_ng/pattern/list/list_item_group_pattern.cpp` | ShallowBuilder 延迟构建头尾 |
| List 布局算法（单列/多 lanes） | `frameworks/core/components_ng/pattern/list/list_layout_algorithm.cpp` | `ListLanesLayoutAlgorithm` 多列 |
| ListItem 布局算法 | `frameworks/core/components_ng/pattern/list/list_item_layout_algorithm.h` | `BoxLayoutAlgorithm` 子类 |
| ListItemGroup 布局算法 | `frameworks/core/components_ng/pattern/list/list_item_group_layout_algorithm.cpp` | 分组布局 |
| List 布局属性 | `frameworks/core/components_ng/pattern/list/list_layout_property.h` | direction/lanes/divider 等 |
| List 属性集合 | `frameworks/core/components_ng/pattern/list/list_properties.h` | sticky 等共享属性 |
| 分隔线计算 | `frameworks/core/components_ng/pattern/list/list_divider_arithmetic.h` | divider |
| childrenMainSize | `frameworks/core/components_ng/pattern/list/list_children_main_size.h` | 精确预测量 |
| 事件存储 | `frameworks/core/components_ng/pattern/list/list_event_hub.h` | 滚动/拖拽回调 |
| ListItem 事件 | `frameworks/core/components_ng/pattern/list/list_item_event_hub.h` | 删除区域回调 |
| 控制器 | `frameworks/core/components_ng/pattern/list/list_position_controller.cpp` | `ListPositionController : ScrollableController` |
| 索引位置映射 | `frameworks/core/components_ng/pattern/list/list_position_map.h` | getItemRectInGroup 等 |
| 拖拽管理 | `frameworks/core/components_ng/pattern/list/list_item_drag_manager.cpp` | 拖拽实现 |
| 绘制/内容 modifier | `frameworks/core/components_ng/pattern/list/list_paint_method.cpp` / `list_content_modifier.cpp` | 绘制 |
| Model（List/Item/Group） | `frameworks/core/components_ng/pattern/list/list_model_ng.cpp` + `list_item_model_ng.cpp` + `list_item_group_model_ng.cpp` | Create/Set*/静态访问器 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/list.d.ts` + `list_item.d.ts` + `list_item_group.d.ts` | 三组件动态声明 |
| Static API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/list.static.d.ets` | 静态声明 |
| Modifier API (Dynamic) | `<OH_ROOT>/interface/sdk-js/api/arkui/ListModifier.d.ts` | 动态 Modifier |
| Modifier API (Static) | `<OH_ROOT>/interface/sdk-js/api/arkui/ListModifier.static.d.ets` | 静态 Modifier |
| CAPI / NDK | `interfaces/native/native_node.h` | `ARKUI_NODE_LIST/ARKUI_NODE_LIST_ITEM/ARKUI_NODE_LIST_ITEM_GROUP` |

API 检索建议：属性搜 `ListAttribute`/`ListItemAttribute`/`ListItemGroupAttribute`；控制器搜 `ListScroller`；C API 搜 `NODE_LIST_`、`ARKUI_NODE_LIST`。

### API 解析实现路径

List 当前未完成组件化改造（无 `bridge/` 子目录、JSView 文件仍存在）。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| JSView（声明式组件） | `frameworks/bridge/declarative_frontend/jsview/js_list.cpp` + `js_list_item.cpp` + `js_list_item_group.cpp` | `JSList/JSListItem/JSListItemGroup` → ModelNG |
| 控制器桥接 | `frameworks/bridge/declarative_frontend/jsview/js_list.cpp`（`JSListScroller`） | ListScroller 控制器方法 |
| node_modifier 层 | `frameworks/core/interfaces/native/node/node_list_modifier.cpp` + `node_list_item_modifier.cpp` + `node_list_item_group_modifier.cpp` | C++ Set/Reset/Get + 事件 |
| 生成 Modifier/Accessor | `frameworks/core/interfaces/native/implementation/list_modifier.cpp` 等 + `ui_list_event_accessor.cpp`/`list_scroller_accessor.cpp`/`list_item_swipe_action_manager_accessor.cpp`/`list_item_ops_accessor.cpp` | GeneratedModifier + 事件/控制器访问器 |
| C API（NDK） | `interfaces/native/native_node.h` | `ARKUI_NODE_LIST/ITEM/ITEM_GROUP` + 事件/属性枚举 |
| 前端 Modifier（ArkTS 侧） | `frameworks/bridge/declarative_frontend/ark_modifier/src/list_modifier.ts` + `list_item_modifier.ts` | ArkTS Modifier 类 |


### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| List 单元测试 | `test/unittest/core/pattern/list/` | ListPattern/Model/Layout/Accessibility/选择/滑动测试 |

### 相关 Spec

| ID | 主题 | Spec 路径 | 状态 |
|----|------|-----------|------|
| 05-03-05 | List/ListItem/ListItemGroup | `specs/05-ui-components/03-scroll-container-components/05-list-list-item-list-item-group/` | active |

Design 文档：`specs/05-ui-components/03-scroll-container-components/05-list-list-item-list-item-group/design.md`

| Feat-ID | 标题 | 覆盖范围 | 状态 |
|---------|------|----------|------|
| Feat-01 | 创建与核心布局（含懒加载/缓存） | 三组件创建, listDirection/lanes/alignListItem/divider/childrenMainSize/syncLoad/cachedCount/supportEmptyBranchInLazyLoading, contentStartOffset/EndOffset/stackFromEnd/maintainVisibleContentPosition | Baselined |
| Feat-02 | 滚动运动学与边缘效果 | scrollBar/edgeEffect/enableScrollInteraction/friction/nestedScroll/scrollSnapAlign/scrollSnapAnimationSpeed/chainAnimation(+Options systemapi)/focusWrapMode/backPressBehavior | Baselined |
| Feat-03 | 滚动可观测性与控制器 | ListScroller(getItemRectInGroup/scrollToItemInGroup/closeAllSwipeActions/getVisibleListContentInfo), onScroll(弃用)/onScrollIndex/onScrollVisibleContentChange/onReachStart/End/onScrollStart/Stop/onScrollFrameBegin, UIListEvent | Baselined |
| Feat-04 | 分组/粘性头尾/Header/Footer | ListItemGroup header/footer/headerComponent/footerComponent/headerStyle/footerStyle, ListAttribute.sticky(StickyStyle) | Baselined |
| Feat-05 | 选择与编辑模式 | ListItem selectable/selected/onSelect, List multiSelectable/editModeOptions/enableEditMode/onEditModeChange, 弃用 editMode/editable/Sticky/EditMode | Baselined |
| Feat-06 | 拖拽 | onItemDragStart/Enter/Move/Leave/Drop/onItemMove, 弃用 onItemDelete | Baselined |
| Feat-07 | ListItem 滑动操作 | swipeAction, SwipeActionOptions/SwipeActionItem, SwipeEdgeEffect/SwipeActionState/ListItemSwipeActionDirection, ListItemSwipeActionManager(expand/collapse), CloseSwipeActionOptions | Baselined |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 多列/lanes 布局异常 | `list_layout_algorithm.cpp`、`ListLanesLayoutAlgorithm` |
| 分隔线异常 | `list_divider_arithmetic.h`、`ListDividerOptions` |
| 长列表跳变/卡顿 | `list_children_main_size.h`、`cachedCount`/`syncLoad`/`supportEmptyBranchInLazyLoading` |
| 滚动/嵌套异常 | `list_pattern.cpp` + 继承的 `ScrollablePattern`/`NestableScrollContainer` |
| 控制器查询/定位异常 | `list_position_controller.cpp`、`list_position_map.h` |
| 分组头尾/吸附异常 | `list_item_group_pattern.cpp`、`ListAttribute.sticky`（ListItem.sticky 已弃用 9） |
| 选择/编辑异常 | `selectable_container_pattern.h`、`multiSelectable`/`enableEditMode` |
| 拖拽排序异常 | `list_item_drag_manager.cpp` |
| 滑动操作/收起异常 | `list_item_pattern.cpp` 滑动状态机、`ListItemSwipeActionManager`、`ListScroller.closeAllSwipeActions` |
| C API 属性无效 | `node_list_modifier.cpp` 等 |

## 调试入口

- 关键字：grep `ListPattern`、`ListItemPattern`、`ListItemGroupPattern`、`ListLayoutAlgorithm`
- 控制器：grep `ListScroller`、`ListPositionController`、`ListPositionMap`
- 滑动：grep `SwipeAction`、`ListItemSwipeActionManager`、`SWIPER_START`
- 拖拽：grep `ListItemDragManager`、`onItemMove`
- 选择：grep `SelectableContainerPattern`、`multiSelectable`、`enableEditMode`
- C API：grep `NODE_LIST_`、`ARKUI_NODE_LIST`
- 弃用迁移：grep `editMode`(弃用 9)、`onScroll`(弃用 12)、`onItemDelete`(弃用 9)

## 相关主题

- [Scroll：List 继承 `SelectableContainerPattern`（含滚动基础设施），复用 `ScrollablePattern`，详见 Scroll KB](scroll.md)
- [ScrollBar：列表内建滚动条经 `ScrollBarProxy`，详见 ScrollBar KB](scroll-bar.md)
- [LazyForEach/Repeat：列表常配懒加载渲染控制，详见前端 KB](../../syntax/lazy-for-each.md)