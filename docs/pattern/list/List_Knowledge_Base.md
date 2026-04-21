# ArkUI List 组件完整知识库

> **文档版本**: v1.0
> **更新时间**: 2026-01-31
> **源码版本**: OpenHarmony ace_engine (master 分支)
> **作者**: 基于 CLAUDE.md 规范生成

---

## 目录

1. [概述](#概述)
2. [完整调用链](#完整调用链)
3. [目录结构](#目录结构)
4. [核心类继承关系](#核心类继承关系)
5. [Pattern层详解](#pattern层详解)
6. [Model层详解](#model层详解)
7. [LayoutAlgorithm层详解](#layoutalgorithm层详解)
8. [属性系统](#属性系统)
9. [事件处理](#事件处理)
10. [滚动控制](#滚动控制)
11. [特殊功能](#特殊功能)
12. [缓存机制](#缓存机制)
13. [执行流程](#执行流程)
14. [完整API清单](#完整api清单)
15. [关键实现细节](#关键实现细节)
16. [ListItem和ListItemGroup](#listitem和listitemgroup)
17. [使用示例](#使用示例)
18. [调试指南](#调试指南)
19. [常见问题](#常见问题)
20. [附录](#附录)

---

## 概述

### 组件定位

**List 组件**是 OpenHarmony ArkUI 框架中的**高性能虚拟化列表容器组件**，支持显示大量数据的列表滚动，通过懒加载和复用机制实现高性能渲染。

**技术栈**:
- **前端**: ArkTS/TypeScript
- **桥接层**: ListModelNG
- **核心层**: NG Pattern 架构 (ListPattern)
- **布局算法**: ListLayoutAlgorithm / ListLanesLayoutAlgorithm
- **渲染层**: Rosen + Skia

**代码规模**:
- 总文件数: 约 60 个文件
- 核心代码: 约 30,000+ 行 C++ 代码
- 涉及 4 个架构层次

### 功能特性

List 组件支持:
- **虚拟化滚动**: 懒加载机制，仅创建可见区域和预加载区域的子组件
- **多列布局**: lanes 属性支持多列网格布局
- **分组列表**: ListItemGroup 支持带 header/footer 的分组
- **丰富交互**:
  - ListItem 滑动操作 (swipeAction)
  - 拖拽排序
  - 链式动画 (chainAnimation)
  - 滚动对齐 (scrollSnap)
  - 分组吸顶 (sticky)
- **无障碍支持**: 完整的 Accessibility 支持

### 设计模式

List 组件采用 **NG Pattern 架构**:

```
前端 (ArkTS)
    ↓ (Model Layer)
ListModelNG (list_model_ng.cpp)
    ↓ (NG Pattern Layer)
ListPattern (list_pattern.cpp)
    ├─ ScrollablePattern (基类 - 手势处理、边缘效果、滚动条)
    ├─ SelectableContainerPattern (选择和编辑模式)
    └─ ListPattern (List 特定布局和行为)
        ├─ ListItemPattern (单个列表项)
        └─ ListItemGroupPattern (列表分组)
    ↓ (NG LayoutAlgorithm Layer)
ListLayoutAlgorithm (list_layout_algorithm.cpp)
    ├─ ListLanesLayoutAlgorithm (多列布局)
    └─ ListItemGroupLayoutAlgorithm (分组布局)
    ↓
渲染显示
```

### 核心概念

**List 的独特之处** (与 Scroll 的区别):

| 特性 | List | Scroll |
|-----|------|--------|
| **虚拟化** | ✅ 支持 (LazyForEach) | ❌ 不支持 |
| **适用场景** | 大数据量列表 | 少量内容滚动 |
| **子组件** | ListItem / ListItemGroup | 任意组件 |
| **布局方式** | 垂直/水平 + 多列 | 单轴滚动 |
| **位置管理** | 双层 (itemPosition_ + posMap_) | 单层 (currentOffset_) |
| **性能优化** | 复用池 + 预加载 | 无复用机制 |

---

## 完整调用链

### 1. 从 ArkTS 到 Pattern 的调用链

#### 调用链图

```
┌─────────────────────────────────────────────────────────┐
│ 前端 ArkTS                                                │
│                                                          │
│ List() {                                                │
│   LazyForEach(this.dataSource, (item: string, index: number) => { │
│     ListItem() {                                        │
│       Text(item)                                        │
│     }                                                   │
│   })                                                    │
│   .width('100%')                                        │
│   .height('100%')                                       │
│   .lanes(2)                                             │
│   .space({ space: 10 })                                 │
│   .cachedCount(5)                                       │
│   .onScrollIndex((start, end, center) => {             │
│     console.info(`visible: ${start}-${end}-${center}`)  │
│   })                                                    │
│ }                                                       │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│ Model Layer (NG)                                         │
│                                                          │
│ class ListModelNG                                        │
│   源码: frameworks/core/components_ng/pattern/list/     │
│         list_model_ng.cpp                                │
│                                                          │
│ 关键方法:                                                │
│ - Create() - 创建 List 节点                             │
│ - SetSpace() - 设置列表项间距                           │
│ - SetLanes() - 设置列数                                 │
│ - SetCachedCount() - 设置预加载数量                     │
│ - SetOnScrollIndex() - 注册可见索引事件                 │
│                                                          │
│ 执行流程:                                                 │
│ 1. 创建 FrameNode (V2::LIST_ETS_TAG)                   │
│ 2. 创建 ListPattern                                     │
│ 3. 应用布局属性 (ListLayoutProperty)                    │
│ 4. 注册事件 (ListEventHub)                              │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│ Pattern Layer (业务逻辑)                                  │
│                                                          │
│ class ListPattern : public SelectableContainerPattern   │
│   源码: frameworks/core/components_ng/pattern/list/     │
│         list_pattern.cpp                                  │
│                                                          │
│ 核心职责:                                                │
│ - 位置管理 (itemPosition_, posMap_)                     │
│ - 创建布局算法 (CreateLayoutAlgorithm)                  │
│ - 滚动事件处理 (继承自 ScrollablePattern)               │
│ - 链式动画管理 (chainAnimation_)                        │
│ - 编辑模式处理 (SelectableContainerPattern)             │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│ LayoutAlgorithm Layer (布局计算)                          │
│                                                          │
│ class ListLayoutAlgorithm : public LayoutAlgorithm      │
│   源码: frameworks/core/components_ng/pattern/list/     │
│         list_layout_algorithm.cpp                        │
│                                                          │
│ 核心方法:                                                │
│ - Measure() - 测量可见区域子节点                        │
│ - Layout() - 定位子节点                                 │
│ - LayoutALineForward() - 向前布局一行                   │
│ - LayoutALineBackward() - 向后布局一行                  │
└─────────────────────────────────────────────────────────┘
                          ↓
                    [虚拟化列表显示在屏幕上]
```

### 2. 滚动操作完整调用链

#### 用户滑动手势 → 偏移量更新

```
用户手指滑动
    ↓
PanGestureRecognizer (识别滑动手势)
    ↓
ScrollablePattern::HandleScrollDelta()
    ↓
ListPattern::UpdateCurrentOffset(float offset, int32_t source)
    ↓
① ValidateOffset() - 验证偏移量是否合法
② 调整偏移量（考虑边界、边缘效果）
③ 更新 currentOffset_
④ CalculateCurrentOffset() - 更新 itemPosition_
⑤ FireOnDidScroll() - 触发 onScroll
⑥ 请求重新布局
    ↓
OnScrollEndCallback() - 滚动结束
    ↓
FireOnScrollIndex(start, end, center) - 触发可见索引变化
FireOnReachStart() / FireOnReachEnd() - 如果到达边界
```

#### ScrollToIndex() API 调用链

```
scroller.scrollToIndex(10) (ArkTS)
    ↓
ListPositionController::JumpToIndex()
    ↓
ListPattern::ScrollToIndex(10, smooth, align)
    ↓
① 计算目标索引位置 (从 posMap_ 获取)
② 判断是否需要滚动
③ 启动滚动动画 (SpringMotion)
④ 请求重新布局
    ↓
ListLayoutAlgorithm::Measure() - 使用 jumpIndex_ 参数
    ↓
[滚动到目标索引位置]
```

---

## 目录结构

### 完整目录树

```
frameworks/core/components_ng/pattern/list/
├── list_pattern.h/cpp                  # ListPattern 主类
├── list_layout_algorithm.h/cpp         # 布局算法核心
├── list_lanes_layout_algorithm.h/cpp   # 多列布局算法
├── list_layout_property.h/cpp          # 布局属性
├── list_paint_method.h/cpp             # 绘制方法
├── list_event_hub.h/cpp                # 事件中心
├── list_accessibility_property.h/cpp   # 无障碍属性
├── list_content_modifier.h/cpp         # 内容修饰器
├── list_divider_arithmetic.h/cpp       # 分割线计算
│
├── Model 层
├── list_model_ng.h/cpp                 # NG Model 接口
├── list_model_static.h/cpp             # 静态 Model
│
├── 控制器
├── list_position_controller.h/cpp      # 滚动控制器
│
├── ListItem
├── list_item_pattern.h/cpp             # ListItem Pattern
├── list_item_layout_algorithm.h/cpp    # ListItem 布局
├── list_item_layout_property.h/cpp     # ListItem 属性
├── list_item_event_hub.h/cpp           # ListItem 事件
├── list_item_drag_manager.h/cpp        # ListItem 拖拽管理
│
├── ListItemGroup
├── list_item_group_pattern.h/cpp       # ListItemGroup Pattern
├── list_item_group_layout_algorithm.h/cpp  # ListItemGroup 布局
├── list_item_group_layout_property.h/cpp   # ListItemGroup 属性
├── list_item_group_paint_method.h/cpp     # ListItemGroup 绘制
│
├── 工具类
├── list_position_map.h/cpp             # 位置映射管理
├── list_children_main_size.h/cpp       # 子组件尺寸管理
├── list_height_offset_calculator.h/cpp # 高度偏移计算
│
└── 文档
    └── CLAUDE.md                        # 组件规则说明
```

### 关键文件说明

| 文件 | 职责 | 核心类/方法 |
|-----|------|-----------|
| **list_pattern.h/cpp** | 核心业务逻辑 | `ListPattern::OnModifyDone()`, `OnDirtyLayoutWrapperSwap()` |
| **list_layout_algorithm.h/cpp** | 布局计算 | `ListLayoutAlgorithm::Measure()`, `LayoutALineForward()` |
| **list_lanes_layout_algorithm.h/cpp** | 多列布局 | `ListLanesLayoutAlgorithm::LayoutALineForward()` |
| **list_model_ng.h/cpp** | ArkTS API 接口 | `ListModelNG::Create()`, `SetLanes()` |
| **list_position_map.h/cpp** | 位置管理 | `ListPositionMap::GetPos()`, `UpdatePosMap()` |
| **list_children_main_size.h/cpp** | 子组件尺寸 | `ListChildrenMainSize::GetChildSize()` |
| **list_item_pattern.h/cpp** | ListItem 实现 | `ListItemPattern::OnModifyDone()`, 滑动操作 |
| **list_item_group_pattern.h/cpp** | ListItemGroup 实现 | 分组布局、header/footer 管理 |

---

## 核心类继承关系

### 1. Pattern 层继承关系

```
Pattern (基类)
    ↓
ScrollablePattern (滚动基类)
    ├─ 手势识别 (PanGestureRecognizer)
    ├─ 滚动控制器 (ScrollableController)
    ├─ 边缘效果 (EdgeEffect)
    └─ 滚动事件处理
         ↓
SelectableContainerPattern (可选择容器)
    ├─ 多选支持 (multiSelectable_)
    ├─ 编辑模式 (editMode_)
    └─ 选择状态管理
         ↓
ListPattern (List 组件实现)
    ├─ 虚拟化滚动逻辑
    ├─ 位置管理 (双层位置系统)
    ├─ 链式动画 (chainAnimation_)
    ├─ 多列布局 (lanes_)
    └─ 分组管理
         ├─ ListItemPattern
         └─ ListItemGroupPattern
```

### 2. 关键类定义

#### ListPattern

**文件**: `list_pattern.h:56`

```cpp
class ACE_FORCE_EXPORT ListPattern : public SelectableContainerPattern
{
    DECLARE_ACE_TYPE(ListPattern, SelectableContainerPattern);

public:
    // 核心状态变量
    int32_t maxListItemIndex_ = 0;       // 最大项索引
    int32_t startIndex_ = -1;             // 当前可见起始索引
    int32_t endIndex_ = -1;               // 当前可见结束索引
    int32_t centerIndex_ = -1;            // 当前可见中心索引
    float contentMainSize_ = 0.0f;        // 组件内容区视口大小
    float currentOffset_ = 0.0f;          // 当前滚动偏移
    float spaceWidth_ = 0.0f;             // 项间距

    // 位置管理 (双层系统)
    ListLayoutAlgorithm::PositionMap itemPosition_;    // 当前帧相对位置
    ListLayoutAlgorithm::PositionMap cachedItemPosition_;  // 缓存项位置
    RefPtr<ListPositionMap> posMap_;        // 绝对位置映射 (持久化)
    RefPtr<ListChildrenMainSize> childrenSize_;  // 子组件尺寸预设

    // 链式动画
    RefPtr<ChainAnimation> chainAnimation_;

    // 多列布局
    int32_t lanes_ = 1;
    float laneGutter_ = 0.0f;

    // 滚动控制
    RefPtr<ScrollControllerBase> positionController_;
    ScrollAlign scrollAlign_ = ScrollAlign::START;
    std::optional<int32_t> jumpIndex_;
    std::optional<int32_t> targetIndex_;
};
```

#### ListLayoutAlgorithm

**文件**: `list_layout_algorithm.h:86`

```cpp
class ACE_EXPORT ListLayoutAlgorithm : public LayoutAlgorithm
{
    DECLARE_ACE_TYPE(ListLayoutAlgorithm, LayoutAlgorithm);

public:
    using PositionMap = std::map<int32_t, ListItemInfo>;

    // 布局方法
    void Measure(LayoutWrapper* layoutWrapper) override;
    void Layout(LayoutWrapper* layoutWrapper) override;

    // 核心布局流程
    void LayoutForward(LayoutWrapper* layoutWrapper, int32_t startIndex, float startPos);
    void LayoutBackward(LayoutWrapper* layoutWrapper, int32_t endIndex, float endPos);

    // 跳转布局
    void HandleJumpAuto(LayoutWrapper* layoutWrapper, int32_t startIndex, int32_t endIndex);
    virtual void HandleJumpCenter(LayoutWrapper* layoutWrapper);
    void HandleJumpStart(LayoutWrapper* layoutWrapper);
    void HandleJumpEnd(LayoutWrapper* layoutWrapper);

    // 位置信息
    const PositionMap& GetItemPosition() const { return itemPosition_; }
    int32_t GetStartIndex() const;
    int32_t GetEndIndex() const;

private:
    PositionMap itemPosition_;           // 当前帧位置 (临时)
    PositionMap recycledItemPosition_;  // 复用项位置
    PositionMap cachedItemPosition_;    // 缓存项位置
    double currentOffset_ = 0.0;        // 帧偏移量
    float contentMainSize_ = 0.0f;      // 组件内容区视口大小
    int32_t totalItemCount_ = 0;        // 总项数
    float spaceWidth_ = 0.0f;           // 间距
};
```

#### ListItemPattern

**文件**: `list_item_pattern.h:50`

```cpp
class ACE_FORCE_EXPORT ListItemPattern : public SelectableItemPattern
{
    DECLARE_ACE_TYPE(ListItemPattern, SelectableItemPattern);

public:
    // 滑动操作
    void SwipeCommon(ListItemSwipeIndex targetState);
    void SwipeForward();
    void SwipeBackward();
    void ExpandSwipeAction(ListItemSwipeActionDirection direction);
    void CloseSwipeAction(OnFinishFunc&& onFinishCallback);

    // 拖拽排序
    void HandleDragStart(const GestureEvent& info);
    void HandleDragUpdate(const GestureEvent& info);
    void HandleDragEnd(const GestureEvent& info);

    // 状态管理
    V2::ListItemStyle listItemStyle_;
    int32_t indexInList_ = 0;              // 在 List 中的索引
    int32_t indexInListItemGroup_ = -1;    // 在 ListItemGroup 中的索引

private:
    // swiperAction 相关
    int32_t startNodeIndex_ = -1;          // startAction 节点索引
    int32_t endNodeIndex_ = -1;            // endAction 节点索引
    float curOffset_ = 0.0f;               // 当前滑动偏移
    ListItemSwipeIndex swiperIndex_;       // 当前滑动状态
    SwipeActionState swipeActionState_;    // 滑动操作状态

    // 拖拽相关
    RefPtr<ListItemDragManager> dragManager_;
};
```

#### ListItemGroupPattern

**文件**: `list_item_group_pattern.h:72`

```cpp
class ACE_EXPORT ListItemGroupPattern : public Pattern
{
    DECLARE_ACE_TYPE(ListItemGroupPattern, Pattern);

public:
    // Header/Footer 管理
    void AddHeader(const RefPtr<NG::UINode>& header);
    void AddFooter(const RefPtr<NG::UINode>& footer);
    void RemoveHeader();
    void RemoveFooter();
    bool IsHasHeader();
    bool IsHasFooter();

    // 子组件结构: [header] -> [ListItem_0, ListItem_1, ...] -> [footer]
    int32_t itemStartIndex_ = 0;           // 第一个 ListItem 在 children 中的索引
    int32_t headerIndex_ = -1;
    int32_t footerIndex_ = -1;
    int32_t itemTotalCount_ = -1;          // ListItem 总数

    // 位置信息
    ListItemGroupLayoutAlgorithm::PositionMap itemPosition_;
    float headerMainSize_ = 0.0f;
    float footerMainSize_ = 0.0f;

    // 缓存管理
    int32_t backwardCachedIndex_ = INT_MAX;
    int32_t forwardCachedIndex_ = -1;
    bool reCache_ = false;
};
```

---

## Pattern层详解

### ListPattern 核心职责

**ListPattern** 是 List 组件的核心逻辑层，负责:

1. **双层位置管理**
   - `itemPosition_`: 当前帧相对位置 (每帧重建)
   - `posMap_`: 绝对位置映射 (持久化，记录所有曾可见项)

2. **虚拟化滚动**
   - 配合 LayoutAlgorithm 实现懒加载
   - 管理可见范围和缓存范围

3. **布局算法协调**
   - 在 `CreateLayoutAlgorithm()` 中创建算法实例
   - 在 `OnDirtyLayoutWrapperSwap()` 中接收布局结果

4. **滚动控制**
   - 继承自 ScrollablePattern 的滚动功能
   - 实现位置到索引的映射

### 关键生命周期方法

#### 1. OnModifyDone()

**调用时机**: 组件属性修改完成时

**源码位置**: `list_pattern.cpp`

**执行流程**:
```cpp
void ListPattern::OnModifyDone()
{
    // 1. 处理轴变化
    auto axis = GetAxis();
    if (axis != lastAxis_) {
        // 重置布局方向
        lastAxis_ = axis;
    }

    // 2. 设置滚动条
    SetScrollBarDisplay();

    // 3. 设置边缘效果
    HandleScrollEffect();

    // 4. 初始化链式动画
    if (chainAnimationOptions_) {
        SetChainAnimation();
    }

    // 5. 检查滚动对齐
    if (scrollSnapUpdate_) {
        // 设置 ScrollSnap
    }

    // 6. 注册事件
    RegisterScrollBarEventTask();
}
```

#### 2. OnDirtyLayoutWrapperSwap()

**调用时机**: 布局结果交换时

**源码位置**: `list_pattern.cpp`

**执行流程**:
```cpp
bool ListPattern::OnDirtyLayoutWrapperSwap(
    const RefPtr<LayoutWrapper>& dirty,
    const DirtySwapConfig& config)
{
    // 1. 获取 LayoutAlgorithm
    auto algorithm = DynamicCast<ListLayoutAlgorithm>(
        dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(algorithm, false);

    // 2. 同步布局结果 - 核心步骤
    itemPosition_ = algorithm->GetItemPosition();
    contentMainSize_ = algorithm->GetContentMainSize();
    startIndex_ = algorithm->GetStartIndex();
    endIndex_ = algorithm->GetEndIndex();

    // 3. 更新绝对位置映射
    UpdatePosMap(itemPosition_);

    // 4. 计算当前偏移
    UpdateTotalOffset(algorithm, isJump);

    // 5. 更新滚动条
    UpdateScrollBarOffset();

    // 6. 触发事件回调
    FireOnScrollIndex(startIndex_, endIndex_, centerIndex_);

    return true;
}
```

**关键数据交换**:

| Pattern 变量 | 来自 LayoutAlgorithm | 说明 |
|-------------|-------------------|------|
| `itemPosition_` | `algorithm->GetItemPosition()` | 当前帧相对位置 |
| `startIndex_` | `algorithm->GetStartIndex()` | 可见起始索引 |
| `endIndex_` | `algorithm->GetEndIndex()` | 可见结束索引 |
| `contentMainSize_` | `algorithm->GetContentMainSize()` | 内容总尺寸 |

### 状态变量详解

#### itemPosition_ vs posMap_

List 组件使用**双层位置系统**:

```cpp
// 1. itemPosition_: 当前帧相对位置 (每帧重建)
ListLayoutAlgorithm::PositionMap itemPosition_;
// 示例: { 5: {startPos: -50, endPos: 50}, 6: {startPos: 50, endPos: 150}, ... }
// 含义: item5 的顶部在视口上方 50px 处 (相对视口)

// 2. posMap_: 绝对位置映射 (持久化)
RefPtr<ListPositionMap> posMap_;
// 示例: { 0: {mainPos: 0}, 1: {mainPos: 100}, 2: {mainPos: 200}, ... }
// 含义: item0 在内容起始位置 0px，item1 在 100px，item2 在 200px (相对内容)
```

**为什么需要双层系统？**

1. **itemPosition_** 用于当前帧布局:
   - 记录当前可见项的相对位置
   - 每帧由 LayoutAlgorithm 重建
   - 用于快速计算当前帧布局

2. **posMap_** 用于持久化位置记录:
   - 记录所有曾经可见过项的绝对位置
   - 在滚动到不可见区域时提供位置估算
   - 支持快速跳转到未渲染位置

**位置转换公式**:
```cpp
// itemPosition_[index].startPos = posMap_->GetPos(index) - currentOffset_
// 即: 相对位置 = 绝对位置 - 滚动偏移
```

#### childrenSize_

**含义**: 子组件尺寸预设

```cpp
RefPtr<ListChildrenMainSize> childrenSize_;
```

**用途**:
- 开发者可以预先设置 ListItem 的尺寸
- 用于优化布局性能，避免重复测量
- 支持两种模式:
  - `defaultSize_`: 默认尺寸
  - `childrenSize_`: 每个项的独立尺寸

```

---

## Model层详解

### ListModelNG 核心职责

**ListModelNG** 提供 ArkTS 声明式 API，负责:

1. **创建 List 节点**
2. **设置布局属性** (通过 ListLayoutProperty)
3. **注册事件处理** (通过 ListEventHub)
4. **管理滚动控制器** (ListPositionController)

### 关键 API 方法

#### 1. Create()

**源码位置**: `list_model_ng.cpp`

**功能**: 创建 List FrameNode

```cpp
void ListModelNG::Create(bool isCreateArc)
{
    // 1. 创建 List FrameNode
    auto frameNode = FrameNode::CreateFrameNode(
        V2::LIST_ETS_TAG,
        MakeRefPtr<ListPattern>());

    // 2. 添加到 ViewStack
    ViewStackProcessor::GetInstance()->Push(frameNode);

    // 3. 设置默认属性
    auto pattern = frameNode->GetPattern<ListPattern>();
    pattern->SetDirection(FlexDirection::COLUMN); // 默认垂直
}
```

**对应 ArkTS**:
```typescript
List() {
  // 子组件
}
```

#### 2. SetLanes()

**源码位置**: `list_model_ng.cpp`

**功能**: 设置列数

```cpp
void ListModelNG::SetLanes(int32_t lanes)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);

    auto layoutProperty = frameNode->GetLayoutProperty<ListLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);

    layoutProperty->SetLanes(lanes);
}
```

**对应 ArkTS**:
```typescript
List().lanes(3)  // 3列布局
```

#### 3. SetCachedCount()

**源码位置**: `list_model_ng.cpp`

**功能**: 设置预加载数量

```cpp
void ListModelNG::SetCachedCount(int32_t cachedCount, bool show)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto layoutProperty = frameNode->GetLayoutProperty<ListLayoutProperty>();

    layoutProperty->SetCachedCount(cachedCount);
    layoutProperty->SetShowCachedItems(show);
}
```

**对应 ArkTS**:
```typescript
List().cachedCount(5)  // 可见区域外各预加载 5 个
```

**API 12+**:
```typescript
List().cachedCount({ minCount: 3, maxCount: 10 })  // 范围控制
List().cachedCount(5, false)  // 预加载但不显示
```

#### 4. SetOnScrollIndex()

**源码位置**: `list_model_ng.cpp`

**功能**: 注册可见索引变化事件

```cpp
void ListModelNG::SetOnScrollIndex(OnScrollIndexEvent&& onScrollIndex)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto eventHub = frameNode->GetEventHub<ListEventHub>();

    eventHub->SetOnScrollIndex(std::move(onScrollIndex));
}
```

**对应 ArkTS**:
```typescript
List().onScrollIndex((start: number, end: number, center: number) => {
  console.info(`visible: ${start}-${end}, center: ${center}`)
})
```

### 完整 API 映射表

| ArkTS API | ListModelNG 方法 | LayoutProperty | Pattern 影响 |
|-----------|-----------------|----------------|-------------|
| `.space(value)` | `SetSpace()` | `SetSpace()` | 设置 spaceWidth_ |
| `.initialIndex(index)` | `SetInitialIndex()` | `SetInitialIndex()` | 设置初始索引 |
| `.lanes(count)` | `SetLanes()` | `SetLanes()` | 设置 lanes_ |
| `.laneConstrain(min, max)` | `SetLaneConstrain()` | - | 设置列约束 |
| `.laneGutter(value)` | `SetLaneGutter()` | `SetLaneGutter()` | 设置列间距 |
| `.listItemAlign(align)` | `SetListItemAlign()` | `SetListItemAlign()` | 设置交叉轴对齐 |
| `.cachedCount(count)` | `SetCachedCount()` | `SetCachedCount()` | 设置预加载数 |
| `.sticky(style)` | `SetSticky()` | `SetStickyStyle()` | 设置吸顶样式 |
| `.scrollSnap(align)` | `SetScrollSnapAlign()` | `SetScrollSnapAlign()` | 设置滚动对齐 |
| `.chainAnimation(options)` | `SetChainAnimationOptions()` | - | 设置链式动画 |
| `.editMode(enable)` | `SetEditMode()` | `SetEditMode()` | 设置编辑模式 |
| `.onScroll(callback)` | `SetOnScroll()` | - | 注册滚动事件 |
| `.onScrollIndex(callback)` | `SetOnScrollIndex()` | - | 注册索引变化 |
| `.onReachStart(callback)` | `SetOnReachStart()` | - | 注册到达顶部 |
| `.onReachEnd(callback)` | `SetOnReachEnd()` | - | 注册到达底部 |

---

## LayoutAlgorithm层详解

### ListLayoutAlgorithm 核心职责

**ListLayoutAlgorithm** 负责 List 的布局计算:

1. **Measure**: 测量可见区域子节点
2. **Layout**: 定位子节点
3. **位置管理**: 维护 itemPosition_
4. **跳转支持**: 处理 scrollToIndex 的布局

### Measure() 方法详解

**源码位置**: `list_layout_algorithm.cpp`

**布局策略选择**:

| 当前状态 | 布局方向 | 说明 |
|---------|---------|------|
| 正常滚动 | FORWARD/BACKWARD | 从可见区域起始/结束位置继续布局 |
| scrollToIndex | NONE → Jump | 从目标索引位置开始布局 |
| 首次布局 | FORWARD | 从索引 0 开始布局 |

### LayoutForward() 方法

**源码位置**: `list_layout_algorithm.cpp`

**功能**: 向前布局 (从起始索引向末尾)

```cpp
void ListLayoutAlgorithm::LayoutForward(
    LayoutWrapper* layoutWrapper, int32_t startIndex, float startPos)
{
    float endPos = startPos;
    int32_t currentIndex = startIndex;

    // 持续布局直到超出视口
    while (endPos < endMainPos_) {
        // 1. 获取或创建子节点
        auto childWrapper = GetListItem(layoutWrapper, currentIndex);
        CHECK_NULL_BREAK(childWrapper);

        // 2. 测量子节点
        MeasureChild(layoutWrapper, childWrapper, currentIndex);

        // 3. 记录位置信息
        float childSize = GetChildHeight(layoutWrapper, currentIndex);
        ListItemInfo info = {
            .id = currentIndex,
            .startPos = endPos,
            .endPos = endPos + childSize,
            .isGroup = IsListItemGroup(layoutWrapper, currentIndex)
        };
        itemPosition_[currentIndex] = info;

        // 4. 移动到下一个位置
        endPos += childSize + spaceWidth_;
        currentIndex++;

        // 5. 检查边界
        if (currentIndex > totalItemCount_) break;
    }
}
```

### HandleJumpCenter() 方法

**源码位置**: `list_layout_algorithm.cpp`

**功能**: 处理跳转到索引 (SCROLL_ALIGN.CENTER)

```cpp
void ListLayoutAlgorithm::HandleJumpCenter(LayoutWrapper* layoutWrapper)
{
    if (!jumpIndex_ || !targetIndex_) return;

    // 1. 获取目标索引
    int32_t targetIndex = targetIndex_.value();

    // 2. 从目标索引开始布局
    int32_t currentIndex = targetIndex;
    float currentPos = 0.0f; // 目标项在中心

    // 向前布局 (目标项之前的项)
    while (currentPos > startMainPos_) {
        // ... 布局逻辑
    }

    // 向后布局 (目标项之后的项)
    while (endPos < endMainPos_) {
        // ... 布局逻辑
    }
}
```

---

## 属性系统

### ListLayoutProperty

**文件**: `list_layout_property.h:41`

**核心属性**:

```cpp
class ACE_EXPORT ListLayoutProperty : public ScrollableLayoutProperty
{
public:
    // 基础布局属性
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Space, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(InitialIndex, int32_t, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ListDirection, Axis, PROPERTY_UPDATE_MEASURE);

    // 多列布局属性
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Lanes, int32_t, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(LaneMinLength, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(LaneMaxLength, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(LaneGutter, Dimension, PROPERTY_UPDATE_MEASURE);

    // 对齐属性
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ListItemAlign, V2::ListItemAlign, PROPERTY_UPDATE_MEASURE);

    // 缓存属性
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(CachedCount, int32_t, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ShowCachedItems, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(CacheRange, CacheRange, PROPERTY_UPDATE_MEASURE_SELF);

    // 其他属性
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(StickyStyle, V2::StickyStyle, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ScrollSnapAlign, ScrollSnapAlign, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ChainAnimation, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(EditMode, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Divider, V2::ItemDivider, PROPERTY_UPDATE_MEASURE);
};
```

### 属性传递流程

```
ArkTS API
    ↓
ListModelNG::SetXXX()
    ↓
ListLayoutProperty::SetXXX()
    ↓
OnModifyDone() (触发模式修改)
    ↓
ListPattern 读取属性
    ↓
应用相应逻辑
```

---

## 事件处理

### 事件类型

List 组件支持以下事件:

| 事件 | 触发时机 | 注册方法 |
|-----|---------|---------|
| **onScroll** | 滚动进行中 | `SetOnScroll()` |
| **onScrollStart** | 滚动开始 | `SetOnScrollStart()` |
| **onScrollStop** | 滚动停止 | `SetOnScrollStop()` |
| **onScrollIndex** | 可见索引变化 | `SetOnScrollIndex()` |
| **onScrollBegin** | 滚动即将开始 | `SetOnScrollBegin()` |
| **onReachStart** | 到达顶部 | `SetOnReachStart()` |
| **onReachEnd** | 到达底部 | `SetOnReachEnd()` |
| **onScrollVisibleContentChange** | 可见内容变化 | `SetOnScrollVisibleContentChange()` |
| **onItemMove** | 拖拽移动 | `SetOnItemMove()` |
| **onItemDragStart** | 拖拽开始 | `SetOnItemDragStart()` |

### 事件触发顺序

```
OnScrollStart() / OnScrollBegin()
    ↓
OnWillScroll()
    ↓
UpdateCurrentOffset()
    ↓
OnScroll() (可能多次调用)
    ↓
OnScrollIndex() (可见范围变化时)
    ↓
OnScrollStop()
    ↓
OnDidScroll()
    ↓
OnReachStart/OnReachEnd() (如果到达边界)
```

---

## 滚动控制

### ListPositionController

**文件**: `list_position_controller.h:22`

**功能**: 提供 List 特定的滚动控制 API

```cpp
class ACE_EXPORT ListPositionController : public ScrollableController
{
public:
    // 跳转到指定索引
    void JumpToIndex(int32_t index, bool smooth, ScrollAlign align, int32_t source);

    // 跳转到分组内的项
    void JumpToItemInGroup(int32_t index, int32_t indexInGroup, bool smooth,
        ScrollAlign align, int32_t source);

    // 获取分组内项的位置
    Rect GetItemRectInGroup(int32_t index, int32_t indexInGroup) const;

    // 获取分组内项的索引
    ListItemGroupIndex GetItemIndexInGroup(double x, double y) const;
};
```

### 关键滚动方法

#### ScrollToIndex()

**源码位置**: `list_pattern.cpp`

**功能**: 滚动到指定索引

```cpp
void ListPattern::ScrollToIndex(
    int32_t index, bool smooth, ScrollAlign align,
    std::optional<float> extraOffset)
{
    // 1. 验证索引
    if (index < 0 || index > maxListItemIndex_) {
        return;
    }

    // 2. 设置跳转参数
    targetIndex_ = index;
    scrollAlign_ = align;

    // 3. 计算目标位置
    float targetPos = CalculateTargetPos(startPos, endPos);

    // 4. 启动滚动动画
    if (smooth) {
        AnimateToTarget(index, std::nullopt, align);
    } else {
        currentOffset_ = targetPos;
        MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
}
```

**对应 ArkTS**:
```typescript
this.scroller.scrollToIndex(10)  // 跳转到索引 10
this.scroller.scrollToIndex(10, true, ScrollAlign.CENTER)  // 平滑滚动到中心
```

#### ScrollToItemInGroup()

**源码位置**: `list_pattern.cpp`

**功能**: 跳转到分组内的项

```cpp
void ListPattern::ScrollToItemInGroup(
    int32_t index, int32_t indexInGroup, bool smooth, ScrollAlign align)
{
    // 1. 验证目标
    if (!CheckTargetValid(index, indexInGroup)) {
        return;
    }

    // 2. 设置跳转参数
    targetIndex_ = index;
    targetIndexInGroup_ = indexInGroup;
    scrollAlign_ = align;

    // 3. 执行跳转
    AnimateToTarget(index, indexInGroup, align);
}
```

**对应 ArkTS**:
```typescript
this.scroller.scrollToIndex(10, 5)  // 跳转到第10组的第5项
```

---

## 特殊功能

### 1. 多列布局 (Lanes)

**功能**: 支持多列网格布局

**配置方式**:
```typescript
List().lanes(3)  // 3列布局
```

**实现原理**:

使用 `ListLanesLayoutAlgorithm`:

```cpp
class ListLanesLayoutAlgorithm : public ListLayoutAlgorithm
{
protected:
    int32_t LayoutALineForward(
        LayoutWrapper* layoutWrapper,
        int32_t& currentIndex,
        float startPos,
        float& endPos) override
    {
        // 1. 布局一行中的多个列
        for (int32_t lane = 0; lane < lanes_; lane++) {
            // 获取或创建子节点
            auto childWrapper = GetListItem(layoutWrapper, currentIndex);

            // 测量子节点
            MeasureChild(layoutWrapper, childWrapper, currentIndex);

            // 计算交叉轴位置
            float crossOffset = CalculateLaneCrossOffset(crossSize, childCrossSize, false);

            currentIndex++;
        }

        // 2. 计算行高 (取最高项)
        float rowHeight = GetMaxHeightInRow();
        endPos += rowHeight + spaceWidth_;

        return currentIndex;
    }
};
```

**行高计算**:
- 每行的高度由该行中最高的 ListItem 决定
- 同一行内的所有 ListItem 顶部对齐

### 2. 链式动画 (ChainAnimation)

**功能**: 滚动时项间距呈现弹簧动画效果

**配置方式**:
```typescript
List().chainAnimation(true)
List().chainAnimation({
  minSpace: 10,
  maxSpace: 60,
  conductivity: 10,
  intensity: 10,
  edgeEffect: 1,
  stiffness: 228,
  damping: 0.6
})
```

**实现原理**:

```cpp
class ListPattern {
    RefPtr<ChainAnimation> chainAnimation_;

    float FlushChainAnimation(float dragOffset)
    {
        if (!chainAnimation_) {
            return 0.0f;
        }

        // 计算链式偏移
        float chainOffset = 0.0f;
        for (auto& [index, item] : itemPosition_) {
            float distance = CalculateDistance(index);
            float effect = CalculateEffect(distance, dragOffset);
            chainOffset += effect;
        }

        return chainOffset;
    }
};
```

**限制条件**:
- 仅支持单列布局 (lanes = 1)
- 需要设置 `edgeEffect: EdgeEffect.Spring`

### 3. ListItem 滑动操作 (SwipeAction)

**功能**: ListItem 支持左右滑动显示操作按钮

**配置方式**:
```typescript
ListItem() {
  Text(item)
}
.swipeAction({ start: SwipeActionGroup(), end: SwipeActionGroup() })
```

**实现原理**:

```cpp
class ListItemPattern {
    // 滑动状态管理
    ListItemSwipeIndex swiperIndex_;
    float curOffset_ = 0.0f;

    void HandleDragUpdate(const GestureEvent& info)
    {
        // 1. 计算滑动偏移
        float offset = info.GetMainPoint().Get(mainAxis_) - dragStartPosition_;

        // 2. 限制滑动范围
        float maxOffset = startNodeSize_;
        curOffset_ = std::clamp(offset, -maxOffset, maxOffset);

        // 3. 更新子节点位置
        UpdatePostion(curOffset_);
    }
};
```

### 4. 滚动对齐 (ScrollSnap)

**功能**: 滚动停止时自动对齐到项边界

**配置方式**:
```typescript
List().scrollSnap(ScrollSnapAlign.START)  // 对齐到起始位置
List().scrollSnap(ScrollSnapAlign.CENTER) // 对齐到中心
List().scrollSnap(ScrollSnapAlign.END)    // 对齐到结束位置
```

---

## 缓存机制

### LazyForEach 懒加载

**含义**: 仅创建可见区域和预加载区域的子组件

**生命周期**:

**创建**:
```
List Measure 需要某个索引的子节点
    ↓
GetOrCreateChildByIndex(index)
    ↓
LazyForEachNode::GetFrameChildByIndex()
    ├─ 检查 CachedUINodeMap
    │   ├─ 命中 → 返回缓存
    │   └─ 未命中 ↓
    ├─ builder_->GetChild(index)
    │   └─ 调用 itemGenerator(item, index)
    └─ 存入缓存
```

**销毁**:
```
List Measure 完成，计算新的可见范围
    ↓
SetActiveChildRange(start, end, cacheStart, cacheEnd)
    ↓
LazyForEachNode::DoSetActiveChildRange()
    ├─ 找出超出范围的项
    ├─ 标记为待销毁 (添加到 removingNodes_)
    └─ 提交到 Idle 任务
        ↓
[在空闲时间执行]
    ├─ 调用 Detach
    ├─ 从缓存移除
    └─ 触发 aboutToRecycle() (如果可复用)
```

**关键点**:
- 项在离开屏幕时**不会立即销毁**，而是等待空闲时间
- 预加载范围内的项也会被创建
- 使用 `@Reusable` 装饰器的项会进入复用池而非销毁

### CachedCount 配置

**用途**: 创建可见区域外的少量项以减少滚动卡顿

```typescript
List().cachedCount(5)  // 可见区域外各预加载 5 个
```

**API 12+**:
```typescript
// 范围控制
List().cachedCount({ minCount: 3, maxCount: 10 })

// 预加载但不显示
List().cachedCount(5, false)
```

---

## 执行流程

### 1. 初始化流程

```
ArkTS: List() { ... }
    ↓
ListModelNG::Create()
    ↓
创建 FrameNode (V2::LIST_ETS_TAG)
    ↓
创建 ListPattern
    ↓
创建 ListLayoutProperty
    ↓
创建 ListEventHub
    ↓
OnAttachToMainTree()
    ↓
[初始化完成]
```

### 2. 布局流程

```
触发布局 (属性修改 / 尺寸变化)
    ↓
CreateLayoutAlgorithm()
    ├─ 创建 ListLayoutAlgorithm 或 ListLanesLayoutAlgorithm
    ├─ 传递 currentOffset_
    └─ 传递其他参数
    ↓
ListLayoutAlgorithm::Measure()
    ├─ 确定布局方向 (FORWARD/BACKWARD/JUMP)
    ├─ 获取或创建子节点
    ├─ 测量子节点
    ├─ 记录位置到 itemPosition_
    └─ 计算内容尺寸
    ↓
ListLayoutAlgorithm::Layout()
    ├─ 应用滚动偏移
    └─ 定位子节点
    ↓
OnDirtyLayoutWrapperSwap()
    ├─ 同步 itemPosition_
    ├─ 更新 startIndex_/endIndex_
    ├─ 更新 posMap_
    └─ 触发 onScrollIndex 事件
    ↓
[布局完成]
```

### 3. 滚动流程

```
用户滑动手势
    ↓
PanGestureRecognizer 识别
    ↓
ScrollablePattern::HandleScrollDelta()
    ↓
ListPattern::OnScrollCallback(offset, source)
    ├─ 计算链式动画偏移
    ├─ UpdateCurrentOffset()
    │   ├─ 更新 currentOffset_
    └─ 请求新帧
    ↓
[滚动中] (可能多次调用 OnScrollCallback)
    ↓
滚动停止
    ↓
OnScrollEndCallback()
    ├─ FireOnReachStart/End() - 边界事件
    └─ 停止动画
    ↓
[滚动完成]
```

---

## 完整API清单

### ArkTS API 列表

#### 创建和基础配置

```typescript
// 创建列表
List() { ... }
List(value: { space: Length | Resource }) { ... }

// 列表方向
.listDirection(Axis.Vertical)  // 默认
.listDirection(Axis.Horizontal)

// 项间距
.space(value: Length)
.space(value: Resource)

// 初始索引
.initialIndex(index: number)

// 多列布局
.lanes(length: number)  // 固定列数
.lanes(value: ResponsiveValues)  // 响应式列数

// 列约束
.laneConstrain(min: Length, max: Length)

// 列间距
.laneGutter(value: Length)

// 交叉轴对齐
.listItemAlign(ListItemAlign.Start)
.listItemAlign(ListItemAlign.Center)
.listItemAlign(ListItemAlign.End)

// 滚动条
.scrollBar(state: BarState)
.scrollBar(width: Length)
.scrollBar(color: ResourceColor)
.scrollBar(edgeEffect: ScrollBarEdgeEffect)
```

#### 缓存和性能

```typescript
// 预加载数量
.cachedCount(cachedCount: number)
.cachedCount(cachedCount: number, show: boolean)
.cachedCount(param: CachedCountParam)

// 同步加载
.syncLoad(enabled: boolean)
```

#### 高级功能

```typescript
// 分组吸顶
.sticky(value: StickyStyle)
// StickyStyle.None | Header | Footer | Both

// 滚动对齐
.scrollSnap(align: ScrollSnapAlign)

// 链式动画
.chainAnimation(enabled: boolean)
.chainAnimation(options: ChainAnimationOptions)

// 编辑模式
.editMode(editMode: boolean)

// 分割线
.divider(value: ItemDivider | null)

// 从底部开始布局
.stackFromEnd(enabled: boolean)

// 维持可见内容位置
.maintainVisibleContentPosition(enabled: boolean)
```

#### 滚动事件

```typescript
// 滚动事件
.onScroll(event: (xOffset: number, yOffset: number) => void)

// 滚动开始
.onScrollStart(event: () => void)

// 滚动停止
.onScrollStop(event: () => void)

// 滚动即将开始
.onScrollBegin(event: (dx: number, dy: number) => void)

// 可见索引变化
.onScrollIndex(event: (start: number, end: number, center: number) => void)

// 可见内容变化
.onScrollVisibleContentChange(event: (start: number, end: number) => void)

// 到达顶部
.onReachStart(event: () => void)

// 到达底部
.onReachEnd(event: () => void)
```

#### 拖拽事件

```typescript
// 项移动
.onItemMove(event: (from: number, to: number) => boolean)

// 拖拽开始
.onItemDragStart(event: (itemDragInfo: ItemDragInfo, itemIndex: number) => void)

// 拖拽进入
.onItemDragEnter(event: (itemDragInfo: ItemDragInfo) => void)

// 拖拽离开
.onItemDragLeave(event: (itemDragInfo: ItemDragInfo, itemIndex: number) => void)

// 拖拽移动
.onItemDragMove(event: (itemDragInfo: ItemDragInfo, itemIndex: number, insertIndex: number) => void)

// 拖拽释放
.onItemDrop(event: (itemDragInfo: ItemDragInfo, itemIndex: number, insertIndex: number, isSuccess: boolean) => void)
```

---

## ListItem和ListItemGroup

### ListItem

**定位**: 列表中的单个项

**特性**:
- 支持滑动操作 (swipeAction)
- 支持拖拽排序
- 支持卡片样式 (ListItemStyle.CARD)

**API**:
```typescript
ListItem() {
  Text("Item Content")
}
// 属性
.width(value: Length)
.height(value: Length)
.listItemStyle(value: ListItemStyle)  // NONE | CARD
.swipeAction(options: SwipeActionOptions)
.select(value: boolean)
.selected(value: boolean)
```

**内部结构** (swipeAction):
```
[startAction] -> [content] -> [endAction]
```

### ListItemGroup

**定位**: 列表中的分组容器

**特性**:
- 支持 header 和 footer
- 内部可以有多个 ListItem
- 支持独立的空间和样式

**API**:
```typescript
ListItemGroup() {
  ListItem() { Text("Item 1") }
  ListItem() { Text("Item 2") }
}
// 属性
.space(value: Length)
.header(header: CustomBuilder)
.footer(footer: CustomBuilder)
.listItemGroupStyle(value: ListItemGroupStyle)  // NONE | CARD
}
```

**索引结构**:
```
List level (全局索引):
  [0] ListItem                     index = 0
  [1] ListItemGroup                index = 1
       ├─ [0] ListItem (内部)           indexInGroup = 0
       ├─ [1] ListItem                   indexInGroup = 1
       └─ [2] ListItem                   indexInGroup = 2
  [2] ListItem                     index = 2

关键点:
- 整个 ListItemGroup 在 List 中占用一个索引 (index = 1)
- 内部有多个子项，各有一个 indexInGroup
```

**子组件结构**:
```
children array: [header, ListItem_0, ListItem_1, ..., footer]
```

---

## 使用示例

### 示例 1: 基础列表

```typescript
@Entry
@Component
struct BasicList {
  @State items: Array<string> = Array.from({ length: 20 }, (_, i) => `Item ${i}`)

  build() {
    List() {
      ForEach(this.items, (item: string, index: number) => {
        ListItem() {
          Text(item)
            .width('100%')
            .height(60)
        }
      })
    }
    .width('100%')
    .height('100%')
    .space(10)
    .cachedCount(5)
  }
}
```

### 示例 2: 分组列表

```typescript
@Entry
@Component
struct GroupedList {
  @State groups: Array<DataGroup> = [
    { title: 'Group 1', items: ['Item 1-1', 'Item 1-2'] },
    { title: 'Group 2', items: ['Item 2-1', 'Item 2-2'] }
  ]

  build() {
    List() {
      ForEach(this.groups, (group: DataGroup) => {
        ListItemGroup({ header: this.groupHeader(group.title) }) {
          ForEach(group.items, (item: string) => {
            ListItem() {
              Text(item).width('100%').height(60)
            }
          })
        }
        .space(10)
      })
    }
    .width('100%')
    .height('100%')
    .sticky(StickyStyle.Header)
  }

  @Builder groupHeader(title: string) {
    Text(title)
      .width('100%')
      .height(40)
      .backgroundColor('#f0f0f0')
  }
}
```

### 示例 3: 多列布局

```typescript
@Entry
@Component
struct LanesList {
  @State items: Array<string> = Array.from({ length: 50 }, (_, i) => `Item ${i}`)

  build() {
    List() {
      ForEach(this.items, (item: string) => {
        ListItem() {
          Text(item)
            .width('100%')
            .height(80)
            .backgroundColor(Color.White)
            .borderRadius(8)
        }
      })
    }
    .width('100%')
    .height('100%')
    .lanes(3)
    .laneGutter(10)
    .alignListItem(ListItemAlign.Center)
  }
}
```

### 示例 4: 带滚动控制的列表

```typescript
@Entry
@Component
struct ListWithController {
  private scroller: Scroller = new Scroller()
  @State scrollOffset: number = 0

  build() {
    Column() {
      List({ scroller: this.scroller }) {
        ForEach(Array.from({ length: 100 }), (_, index) => {
          ListItem() {
            Text(`Item ${index}`)
              .width('100%')
              .height(60)
          }
        })
      }
      .width('100%')
      .height('80%')
      .onScroll((xOffset: number, yOffset: number) => {
        this.scrollOffset = yOffset
      })

      Row() {
        Button('Scroll to Index 50')
          .onClick(() => {
            this.scroller.scrollToIndex(50, true, ScrollAlign.CENTER)
          })

        Button('Scroll to Top')
          .onClick(() => {
            this.scroller.scrollEdge(ScrollEdgeType.START)
          })
      }
      .justifyContent(FlexAlign.SpaceAround)
    }
  }
}
```

### 示例 5: ListItem 滑动操作

```typescript
@Entry
@Component
struct SwipeActionList {
  @State items: Array<string> = Array.from({ length: 20 }, (_, i) => `Item ${i}`)

  build() {
    List() {
      ForEach(this.items, (item: string, index: number) => {
        ListItem() {
          Text(item)
            .width('100%')
            .height(60)
        }
        .swipeAction({
          start: SwipeActionGroup({
            builder: () => {
              Button('Delete')
                .type(ButtonType.Destructive)
                .onClick(() => {
                  // 删除逻辑
                })
            }
          })
        })
      })
    }
    .width('100%')
    .height('100%')
  }
}
```

---

## 调试指南

### 1. 日志调试

**使用专用日志标签**:
```cpp
#include "base/log/ace_trace.h"

// List 相关日志
TAG_LOGI(AceLogTag::ACE_LIST, "ScrollToIndex: %{public}d", index);
TAG_LOGD(AceLogTag::ACE_LIST, "startIndex=%{public}d, endIndex=%{public}d",
    startIndex_, endIndex_);

// 布局相关日志
TAG_LOGD(AceLogTag::ACE_LAYOUT, "itemPosition size: %{public}zu", itemPosition_.size());
```

**实现 dump 方法**:
```cpp
// list_pattern.cpp
void ListPattern::DumpAdvanceInfo(std::unique_ptr<JsonValue>& json)
{
    json->Put("startIndex", startIndex_);
    json->Put("endIndex", endIndex_);
    json->Put("maxListItemIndex", maxListItemIndex_);
    json->Put("contentMainSize", contentMainSize_);
    json->Put("currentOffset", currentOffset_);
    json->Put("lanes", lanes_);

    // 链式动画信息
    json->Put("chainAnimation", chainAnimation_ != nullptr);

    // 位置映射信息
    json->Put("itemPositionSize", static_cast<int32_t>(itemPosition_.size()));
    json->Put("posMapSize", posMap_ ? posMap_->GetTotalHeight() : 0);
}
```

### 2. 调试器检查

**关键变量**:
```cpp
// Pattern 状态
startIndex_ / endIndex_          // 当前可见索引范围
maxListItemIndex_                // 最大项索引
contentMainSize_                 // 内容总尺寸
currentOffset_                   // 当前滚动偏移

// 位置信息
itemPosition_.size()             // 当前帧位置条目数
posMap_->GetTotalHeight()        // 持久化位置高度

// 缓存信息
cachedItemPosition_.size()       // 缓存项数量

// 多列布局
lanes_                           // 列数
```

### 3. 常见问题定位

#### 问题 1: 滚动位置不正确

**检查点**:
- `currentOffset_` 是否正确更新
- `itemPosition_` 是否与 `posMap_` 同步
- `CalculateCurrentOffset()` 是否正确调用

**定位方法**:
```cpp
// 在 UpdateCurrentOffset 中添加日志
TAG_LOGI(AceLogTag::ACE_LIST,
    "UpdateCurrentOffset: offset=%{public}f, currentOffset=%{public}f",
    offset, currentOffset_);
```

#### 问题 2: 懒加载不生效

**检查点**:
- LazyForEach 配置是否正确
- `SetActiveChildRange` 是否被调用
- cachedCount 设置是否合理

**定位方法**:
```cpp
// 检查 LazyForEach 状态
TAG_LOGI(AceLogTag::ACE_LIST,
    "LazyForEach: start=%{public}d, end=%{public}d, cacheStart=%{public}d, cacheEnd=%{public}d",
    start, end, cacheStart, cacheEnd);
```

#### 问题 3: 多列布局不正确

**检查点**:
- `lanes_` 是否正确设置
- `ListLanesLayoutAlgorithm` 是否被使用
- 行高计算是否正确

**定位方法**:
```cpp
// 在 LayoutALineForward 中添加日志
TAG_LOGI(AceLogTag::ACE_LIST,
    "LayoutALineForward: lanes=%{public}d, currentIndex=%{public}d",
    lanes_, currentIndex);
```

---

## 常见问题

### Q1: List 和 Scroll 组件有什么区别？

**A**:

| 特性 | List | Scroll |
|-----|------|-------|
| **虚拟化** | ✅ 支持 | ❌ 不支持 |
| **适用场景** | 大数据量列表 (>100 项) | 少量内容滚动 |
| **子组件** | ListItem / ListItemGroup | 任意组件 |
| **性能** | 高 (复用池 + 预加载) | 低 (全量创建) |
| **API** | scrollToIndex、onScrollIndex | scrollTo、onScroll |

### Q2: 如何优化 List 滚动性能？

**A**:
1. **设置合理的 cachedCount**
   ```typescript
   List().cachedCount(5)  // 预加载 5 个
   ```

2. **使用 @Reusable 装饰器**
   ```typescript
   @Reusable
   @Component
   struct MyListItem {
     // ...
   }
   ```

3. **预设子组件尺寸**
   ```typescript
   List().layoutSize({ defaultSize: 80 })
   ```

4. **避免在 onScroll 中执行重计算**
   ```typescript
   .onScroll((x, y) => {
     // ❌ 避免重计算
     // const result = heavyCalculation()

     // ✅ 使用防抖
     debounce(() => {
       this.updateUI()
     }, 100)
   })
   ```

### Q3: 如何实现分组列表？

**A**:
```typescript
List() {
  ForEach(this.groups, (group: DataGroup) => {
    ListItemGroup({ header: this.groupHeader(group.title) }) {
      ForEach(group.items, (item) => {
        ListItem() { Text(item) }
      })
    }
    .space(10)
  })
}
.sticky(StickyStyle.Header)
```

### Q4: 如何实现拖拽排序？

**A**:
```typescript
List()
.onItemMove((from: number, to: number) => {
  // 更新数据
  const movedItem = this.items.splice(from, 1)[0]
  this.items.splice(to, 0, movedItem)
  return true
})
```

### Q5: 如何获取当前可见的项？

**A**:
```typescript
List()
.onScrollIndex((start: number, end: number, center: number) => {
  console.info(`visible: ${start}-${end}, center: ${center}`)
  this.visibleStart = start
  this.visibleEnd = end
})
```

---

## 附录

### A. 术语表

| 术语 | 英文 | 描述 |
|-----|------|------|
| 虚拟化 | Virtualization | 仅创建可见区域子组件 |
| 懒加载 | Lazy Loading | 按需创建和销毁子组件 |
| 预加载 | Preload/CachedCount | 提前创建可见区域外的项 |
| 复用池 | Reuse Pool | 缓存可复用的组件 |
| 位置映射 | Position Map | 索引到位置的映射 |
| 链式动画 | Chain Animation | 滚动时项间距的弹性效果 |
| 多列布局 | Lanes | 列表的多列网格布局 |

### B. 源码文件索引

| 文件 | 行数 | 描述 |
|-----|------|------|
| `list_pattern.h` | 730 | ListPattern 类定义 |
| `list_pattern.cpp` | ~5000 | ListPattern 实现 |
| `list_layout_algorithm.h` | 728 | 布局算法定义 |
| `list_layout_algorithm.cpp` | ~2000 | 布局算法实现 |
| `list_lanes_layout_algorithm.h` | 98 | 多列布局算法定义 |
| `list_lanes_layout_algorithm.cpp` | ~600 | 多列布局实现 |
| `list_model_ng.h` | 228 | NG Model 定义 |
| `list_model_ng.cpp` | ~1500 | NG Model 实现 |
| `list_item_pattern.h` | 365 | ListItemPattern 定义 |
| `list_item_pattern.cpp` | ~2000 | ListItemPattern 实现 |
| `list_item_group_pattern.h` | 550 | ListItemGroupPattern 定义 |
| `list_item_group_pattern.cpp` | ~1500 | ListItemGroupPattern 实现 |
| `list_position_map.h` | 181 | 位置映射管理 |
| `list_position_map.cpp` | ~800 | 位置映射实现 |
| `list_children_main_size.h` | 183 | 子组件尺寸管理 |

### C. 相关文档

- [List 组件官方文档](https://developer.huawei.com/consumer/cn/doc/harmonyos-references-V5/ts-container-list-V5)
- [ListItem 组件文档](https://developer.huawei.com/consumer/cn/doc/harmonyos-references-V5/ts-container-listitem-V5)
- [ListItemGroup 组件文档](https://developer.huawei.com/consumer/cn/doc/harmonyos-references-V5/ts-container-listitemgroup-V5)
- [Scroller 对象](https://developer.huawei.com/consumer/cn/doc/harmonyos-references-V5/ts-container-list-V5#scroller)

### D. 版本历史

| 版本 | 日期 | 变更 |
|-----|------|------|
| v1.0 | 2026-01-31 | 初始版本 |

---

**文档结束**

> 本文档基于 OpenHarmony ace_engine 源码分析生成，如有错误或遗漏，欢迎指正。
