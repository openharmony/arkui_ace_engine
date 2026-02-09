# ArkUI WaterFlow 组件完整知识库

> **文档版本**：v1.0
> **更新时间**：2026-02-02
> **源码版本**：OpenHarmony ace_engine (master 分支)
> **作者**：基于 CLAUDE.md 规范自动生成

---

## 目录

1. [概述](#概述)
2. [架构与算法选择](#架构与算法选择)
3. [目录结构](#目录结构)
4. [核心类继承关系](#核心类继承关系)
5. [Pattern 层详解](#pattern-层详解)
6. [Model 层详解](#model-层详解)
7. [LayoutInfo 详解](#layoutinfo-详解)
8. [LayoutAlgorithm 层详解](#layoutalgorithm-层详解)
9. [属性系统](#属性系统)
10. [事件处理](#事件处理)
11. [Sections 分段机制](#sections-分段机制)
12. [生命周期与执行流程](#生命周期与执行流程)
13. [完整 API 清单](#完整-api-清单)
14. [关键实现细节](#关键实现细节)
15. [布局模式差异](#布局模式差异)
16. [使用示例](#使用示例)
17. [调试指南](#调试指南)
18. [常见问题](#常见问题)
19. [关键约束（DO NOT BREAK）](#关键约束do-not-break)
20. [附录](#附录)

---

## 概述

### 组件定位

**WaterFlow 组件**是 OpenHarmony ArkUI 框架中的**瀑布流容器组件**，提供可滚动的多列"瀑布流"布局。子元素会被放置到最短的列中，实现高度不等的子元素在多列中自动流动排列。

**技术栈**：
- **前端**：ArkTS/TypeScript
- **桥接层**：WaterFlowModelNG
- **核心层**：NG Pattern 架构 (WaterFlowPattern)
- **布局算法**：WaterFlowLayoutAlgorithm / WaterFlowSegmentedLayout / WaterFlowLayoutSW
- **渲染层**：Rosen + Skia

**代码规模**：
- 总文件数：约 60 个文件
- 核心代码：约 15,000+ 行 C++ 代码
- 涉及 4 个架构层次

### 功能特性

WaterFlow 组件支持：
- **两种布局模式**：
  - `TOP_DOWN` — 保留完整布局信息，精确滚动
  - `SLIDING_WINDOW` — 视口窗口模型，适合大数据集
- **分段布局（WaterFlowSections）**：支持多段不同配置的布局
- **列模板配置**：通过 `columnsTemplate` / `rowsTemplate` 定义列宽
- **自适应列宽**：`itemMinWidth` / `itemMaxWidth` / `itemMinHeight` / `itemMaxHeight`
- **滚动控制**：ScrollToIndex、ScrollTo、ScrollPage 等
- **Footer 支持**：在末尾添加自定义 Footer 节点
- **缓存预加载**：支持 cachedCount 配置
- **边缘效果**：Spring（弹性）、Fade（淡入淡出）、None（无效果）
- **嵌套滚动**：NestedScroll 支持
- **无障碍支持**：完整的 Accessibility 支持

### 设计模式

WaterFlow 组件采用 **NG Pattern 架构**：

```
前端 (ArkTS)
    ↓ (Model Layer)
WaterFlowModelNG (water_flow_model_ng.cpp)
    ↓ (NG Pattern Layer)
WaterFlowPattern (water_flow_pattern.cpp)
    ├─ ScrollablePattern (基类 - 手势处理)
    └─ WaterFlowLayoutInfoBase (布局状态)
    ↓ (NG LayoutAlgorithm Layer - 根据模式选择)
WaterFlowLayoutAlgorithm / WaterFlowSegmentedLayout / WaterFlowLayoutSW
    ↓
渲染显示
```

---

## 架构与算法选择

### 整体架构

```
WaterFlowPattern
├── layoutInfo_ (WaterFlowLayoutInfoBase)
│       ├── WaterFlowLayoutInfo      [TOP_DOWN]
│       └── WaterFlowLayoutInfoSW    [SLIDING_WINDOW]
└── CreateLayoutAlgorithm()
    ├── WaterFlowLayoutAlgorithm   [TOP_DOWN, 无 sections 且系统标志关闭]
    │   └── 继承自 WaterFlowLayoutBase
    ├── WaterFlowSegmentedLayout   [TOP_DOWN, 有 sections 或系统标志开启]
    │   └── 继承自 WaterFlowSegmentLayoutBase
    └── WaterFlowLayoutSW          [SLIDING_WINDOW, 通过继承支持 sections]
        └── 继承自 WaterFlowSegmentLayoutBase

其中 WaterFlowSegmentLayoutBase 继承自 WaterFlowLayoutBase
```

### 算法选择规则

**源码位置**：`water_flow_pattern.cpp:174-192`

```cpp
RefPtr<LayoutAlgorithm> WaterFlowPattern::CreateLayoutAlgorithm()
{
    if (layoutInfo_->Mode() == LayoutMode::SLIDING_WINDOW) {
        // 规则1: SLIDING_WINDOW 模式 → WaterFlowLayoutSW
        algorithm = MakeRefPtr<WaterFlowLayoutSW>(...);
    } else if (sections_ || SystemProperties::WaterFlowUseSegmentedLayout()) {
        // 规则2: 有 sections 或系统标志开启 → WaterFlowSegmentedLayout
        algorithm = MakeRefPtr<WaterFlowSegmentedLayout>(...);
    } else {
        // 规则3: 其他情况 → WaterFlowLayoutAlgorithm
        algorithm = MakeRefPtr<WaterFlowLayoutAlgorithm>(...);
    }
    return algorithm;
}
```

**选择规则总结**：
1. 如果模式是 **SLIDING_WINDOW** → `WaterFlowLayoutSW`
2. 否则如果存在 sections 或 `SystemProperties::WaterFlowUseSegmentedLayout()` → `WaterFlowSegmentedLayout`
3. 否则 → `WaterFlowLayoutAlgorithm`

### 继承层次

- `WaterFlowLayoutAlgorithm` 直接继承 `WaterFlowLayoutBase`
- `WaterFlowSegmentLayoutBase` 继承 `WaterFlowLayoutBase`，提供共享的 section 支持
- `WaterFlowSegmentedLayout` 和 `WaterFlowLayoutSW` 都继承 `WaterFlowSegmentLayoutBase`

---

## 目录结构

### 完整目录树

```
frameworks/core/components_ng/pattern/waterflow/
│
├── ======================== 核心文件 ========================
│
├── water_flow_pattern.h              # WaterFlowPattern 类定义，继承 ScrollablePattern
├── water_flow_pattern.cpp            # WaterFlowPattern 实现，包含滚动处理、布局算法选择、事件触发
│
├── ======================== Model 层 ========================
│
├── water_flow_model.h                # WaterFlowModel 抽象接口定义，声明所有 API 方法
├── water_flow_model_ng.h             # WaterFlowModelNG 类定义，NG 架构 Model 实现
├── water_flow_model_ng.cpp           # WaterFlowModelNG 实现，处理 ViewStack 和属性设置
├── water_flow_model_ng_multi_thread.cpp  # 多线程相关的 Model 方法实现（如 ScrollToIndex）
├── water_flow_model_static.h         # ArkTS 静态前端 Model 接口定义
├── water_flow_model_static.cpp       # ArkTS 静态前端 Model 实现
│
├── ======================== 属性与事件 ========================
│
├── water_flow_layout_property.h      # WaterFlowLayoutProperty 定义，包含列模板、间距、Item约束等
├── water_flow_layout_property.cpp    # 布局属性实现，包含 ToJsonValue、Clone 等
├── water_flow_event_hub.h            # WaterFlowEventHub 定义，继承 ScrollableEventHub，添加 onScrollIndex
├── water_flow_constants.h            # 常量定义（如默认值、枚举等）
│
├── ======================== 分段布局 ========================
│
├── water_flow_sections.h             # WaterFlowSections 类定义，Section 结构体，分段数据管理
├── water_flow_sections.cpp           # 分段数据变更处理，ChangeData、ReplaceFrom、通知回调
│
├── ======================== 绘制相关 ========================
│
├── water_flow_paint_method.h         # WaterFlowPaintMethod 定义，继承 NodePaintMethod
├── water_flow_paint_method.cpp       # 绘制方法实现，处理内容裁剪、方向判断
├── water_flow_content_modifier.h     # WaterFlowContentModifier 定义，内容绘制修饰器
├── water_flow_content_modifier.cpp   # 内容修饰器实现，处理 padding 裁剪
│
├── ======================== 无障碍支持 ========================
│
├── water_flow_accessibility_property.h    # WaterFlowAccessibilityProperty 定义
├── water_flow_accessibility_property.cpp  # 无障碍属性实现，提供滚动信息、项目数等
│
├── ======================== FlowItem 子组件 ========================
│
├── water_flow_item_pattern.h         # FlowItemPattern 定义，FlowItem 的 Pattern 类
├── water_flow_item_model.h           # FlowItemModel 抽象接口
├── water_flow_item_model_ng.h        # FlowItemModelNG 类定义
├── water_flow_item_model_ng.cpp      # FlowItemModelNG 实现，创建 FlowItem 节点
├── water_flow_item_layout_property.h # FlowItemLayoutProperty 定义，包含约束尺寸等
├── water_flow_item_node.h            # WaterFlowItemNode 定义，FlowItem 专用节点类
├── water_flow_item_node.cpp          # WaterFlowItemNode 实现，处理子节点布局
│
├── ======================== 构建配置 ========================
│
├── BUILD.gn                          # GN 构建配置，定义编译目标和依赖
├── CLAUDE.md                         # Claude Code 子目录规则文档
│
├── ======================== 布局算法目录 ========================
│
├── layout/
│   │
│   ├── -------- 基类与工具 --------
│   │
│   ├── water_flow_layout_algorithm_base.h   # WaterFlowLayoutBase 定义，所有布局算法的基类
│   ├── water_flow_layout_algorithm_base.cpp # 基类实现，通用 Measure/Layout 流程
│   ├── water_flow_layout_info_base.h        # WaterFlowLayoutInfoBase 定义，布局状态基类
│   ├── water_flow_layout_info_base.cpp      # 基类实现，Segment 管理、Margin 初始化
│   ├── water_flow_layout_utils.h            # 布局工具函数声明（列模板解析、尺寸计算等）
│   ├── water_flow_layout_utils.cpp          # 工具函数实现，ParseTemplateArgs、CalcLaneWidth 等
│   │
│   ├── -------- TOP_DOWN 模式 --------
│   │
│   ├── top_down/
│   │   ├── water_flow_layout_algorithm.h    # WaterFlowLayoutAlgorithm 定义，基础 TOP_DOWN 算法
│   │   ├── water_flow_layout_algorithm.cpp  # 实现 FillViewport、MeasureItem、直接更新位置
│   │   ├── water_flow_segmented_layout.h    # WaterFlowSegmentedLayout 定义，支持 Sections 的 TOP_DOWN
│   │   ├── water_flow_segmented_layout.cpp  # 分段布局实现，多次 Sync 调用
│   │   ├── water_flow_layout_info.h         # WaterFlowLayoutInfo 定义，完整布局信息存储
│   │   └── water_flow_layout_info.cpp       # TOP_DOWN 布局信息实现，itemInfos_、endPosArray_
│   │
│   └── -------- SLIDING_WINDOW 模式 --------
│   │
│   └── sliding_window/
│       ├── water_flow_layout_sw.h           # WaterFlowLayoutSW 定义，滑动窗口布局算法
│       ├── water_flow_layout_sw.cpp         # 实现窗口填充、Sync 后处理、Skip 优化
│       ├── water_flow_layout_info_sw.h      # WaterFlowLayoutInfoSW 定义，窗口模型状态
│       └── water_flow_layout_info_sw.cpp    # 滑动窗口布局信息，lanes_ 窗口管理、估算偏移
│
├── ======================== 桥接层目录 ========================
│
└── bridge/
    │
    ├── -------- WaterFlow 桥接 --------
    │
    ├── waterflow/
    │   ├── water_flow_model_impl.h              # Bridge Model 接口定义
    │   ├── water_flow_model_impl.cpp            # Bridge Model 实现，调用 WaterFlowModelNG
    │   ├── water_flow_dynamic_module.h          # 动态模块定义，ArkTS 动态加载支持
    │   ├── water_flow_dynamic_module.cpp        # 动态模块注册和初始化
    │   ├── water_flow_dynamic_modifier.cpp      # ArkTS 动态修饰器，处理运行时属性修改
    │   ├── water_flow_static_modifier.cpp       # C API 静态修饰器，处理编译时属性
    │   ├── water_flow_static_ani_modifier.cpp   # ArkTS 静态 ANI 修饰器
    │   ├── water_flow_static_sections_accessor.cpp  # Sections 静态访问器
    │   ├── water_flow_sections_accessor_peer_impl.h # Sections 访问器 Peer 实现
    │   ├── ui_water_flow_event_static_accessor.cpp  # 事件静态访问器
    │   ├── arkts_native_water_flow_bridge.h     # ArkTS Native 桥接定义
    │   └── arkts_native_water_flow_bridge.cpp   # ArkTS Native 桥接实现，NAPI 绑定
    │
    └── -------- FlowItem 桥接 --------
    │
    └── flowitem/
        ├── water_flow_item_model_impl.h         # FlowItem Bridge Model 接口
        ├── water_flow_item_model_impl.cpp       # FlowItem Bridge Model 实现
        ├── water_flow_item_dynamic_module.h     # FlowItem 动态模块定义
        ├── water_flow_item_dynamic_module.cpp   # FlowItem 动态模块注册
        ├── water_flow_item_dynamic_modifier.cpp # FlowItem 动态修饰器
        ├── water_flow_item_static_modifier.cpp  # FlowItem 静态修饰器
        ├── arkts_native_water_flow_item_bridge.h    # FlowItem ArkTS Native 桥接定义
        └── arkts_native_water_flow_item_bridge.cpp  # FlowItem ArkTS Native 桥接实现
```

### 关键文件说明

| 文件 | 职责 | 核心类/方法 |
|-----|------|-----------|
| **water_flow_pattern.h/cpp** | 核心业务逻辑，滚动处理，布局算法选择 | `WaterFlowPattern::OnModifyDone()`, `CreateLayoutAlgorithm()`, `UpdateCurrentOffset()`, `TriggerPostLayoutEvents()` |
| **water_flow_model_ng.h/cpp** | ArkTS 声明式 API 接口层 | `WaterFlowModelNG::Create()`, `SetColumnsTemplate()`, `SetOnScrollIndex()`, `GetOrCreateWaterFlowSections()` |
| **water_flow_layout_property.h/cpp** | 布局属性定义和管理 | `WaterFlowLayoutProperty`, `GetAxis()`, `IsReverse()`, `UpdateItemMinSize()` |
| **water_flow_event_hub.h** | 事件中心，管理 ScrollIndex 等事件 | `WaterFlowEventHub::SetOnScrollIndex()`, `GetOnScrollIndex()` |
| **water_flow_sections.h/cpp** | 分段布局配置和数据变更管理 | `WaterFlowSections::Section`, `ChangeData()`, `ReplaceFrom()` |
| **water_flow_layout_info_base.h/cpp** | 布局状态基类，通用接口定义 | `WaterFlowLayoutInfoBase`, `Offset()`, `Reset()`, `InitSegments()`, `NodeIdx()` |
| **layout/top_down/water_flow_layout_info.h/cpp** | TOP_DOWN 模式布局信息 | `WaterFlowLayoutInfo`, `itemInfos_`, `endPosArray_`, 精确偏移管理 |
| **layout/sliding_window/water_flow_layout_info_sw.h/cpp** | SLIDING_WINDOW 模式布局信息 | `WaterFlowLayoutInfoSW`, `lanes_`, `synced_`, 窗口模型、估算偏移 |
| **layout/top_down/water_flow_layout_algorithm.h/cpp** | TOP_DOWN 基础布局算法 | `WaterFlowLayoutAlgorithm::Measure()`, `Layout()`, `FillViewport()`, 直接更新位置 |
| **layout/top_down/water_flow_segmented_layout.h/cpp** | TOP_DOWN 分段布局算法 | `WaterFlowSegmentedLayout`, 支持 Sections, 多次 `Sync()` 调用 |
| **layout/sliding_window/water_flow_layout_sw.h/cpp** | SLIDING_WINDOW 布局算法 | `WaterFlowLayoutSW`, `Sync()` 后处理, `EnableSkip()` 优化 |
| **layout/water_flow_layout_algorithm_base.h/cpp** | 布局算法基类 | `WaterFlowLayoutBase`, 通用 `Measure()`/`Layout()` 框架 |
| **layout/water_flow_layout_utils.h/cpp** | 布局工具函数 | `ParseTemplateArgs()`, `CalcLaneWidth()`, 列模板解析 |
| **water_flow_paint_method.h/cpp** | 绘制方法 | `WaterFlowPaintMethod`, 内容裁剪、方向判断 |
| **water_flow_content_modifier.h/cpp** | 内容修饰器 | `WaterFlowContentModifier`, padding 裁剪 |
| **water_flow_item_pattern.h** | FlowItem Pattern | `FlowItemPattern`, 子项逻辑 |
| **water_flow_item_model_ng.h/cpp** | FlowItem Model 层 | `FlowItemModelNG::Create()` |
| **water_flow_item_node.h/cpp** | FlowItem 节点 | `WaterFlowItemNode`, 子节点布局处理 |
| **water_flow_accessibility_property.h/cpp** | 无障碍支持 | `WaterFlowAccessibilityProperty`, 滚动信息、项目数 |
| **bridge/waterflow/arkts_native_water_flow_bridge.h/cpp** | ArkTS Native 桥接 | NAPI 绑定、JS 调用 Native |
| **bridge/waterflow/water_flow_dynamic_modifier.cpp** | 动态修饰器 | 运行时属性修改处理 |
| **bridge/waterflow/water_flow_static_modifier.cpp** | 静态修饰器 | 编译时属性处理 |

---

## 核心类继承关系

### 1. Pattern 层继承关系

```
Pattern (基类)
    ↓
ScrollablePattern (滚动基类)
    ├─ 手势识别 (PanGestureRecognizer)
    ├─ 滚动控制器 (ScrollPositionController)
    ├─ 边缘效果 (EdgeEffect)
    └─ 滚动事件处理
         ↓
WaterFlowPattern (WaterFlow 组件实现)
    ├─ layoutInfo_ (WaterFlowLayoutInfoBase)
    │   ├─ WaterFlowLayoutInfo      [TOP_DOWN]
    │   └─ WaterFlowLayoutInfoSW    [SLIDING_WINDOW]
    ├─ sections_ (WaterFlowSections)
    ├─ footer_ (WeakPtr<UINode>)
    └─ 布局算法创建
```

### 2. 布局算法继承关系

```
LayoutAlgorithm (基类)
    ↓
WaterFlowLayoutBase (WaterFlow 布局基类)
    ├─ WaterFlowLayoutAlgorithm     [TOP_DOWN, 无 sections]
    │
    └─ WaterFlowSegmentLayoutBase   [分段布局基类]
        ├─ WaterFlowSegmentedLayout [TOP_DOWN, 有 sections]
        └─ WaterFlowLayoutSW        [SLIDING_WINDOW]
```

### 3. 布局信息继承关系

```
AceType (基类)
    ↓
WaterFlowLayoutInfoBase (布局信息基类)
    ├─ WaterFlowLayoutInfo      [TOP_DOWN 模式]
    │   ├─ itemInfos_ (所有项目位置信息)
    │   ├─ endPosArray_ (快速位置查找)
    │   └─ lanes_ (列状态)
    │
    └─ WaterFlowLayoutInfoSW    [SLIDING_WINDOW 模式]
        ├─ lanes_ (窗口范围内的列)
        ├─ synced_ (同步状态)
        └─ 窗口模型数据
```

---

## Pattern 层详解

### WaterFlowPattern 核心职责

**WaterFlowPattern** 是 WaterFlow 组件的核心逻辑层，负责：

1. **滚动状态与交互**
   - 处理滚动偏移 (offset)、速度 (velocity)、过度滚动 (overscroll)
   - 管理边界判断 (`IsAtTop()`, `IsAtBottom()`, `IsOutOfBoundary()`)

2. **布局算法选择**
   - 根据模式和配置选择合适的布局算法
   - 在 `CreateLayoutAlgorithm()` 中实现

3. **事件派发**
   - 触发 `ReachStart`, `ReachEnd`, `ScrollIndex` 事件
   - 通过 Observer 模式分发事件

4. **Sections 同步**
   - 通过回调处理 Sections 变更
   - 协调分段数据更新

5. **缓存预加载协调**
   - 管理 `preloadItems_` 列表
   - 控制缓存布局算法

### 关键生命周期方法

#### 1. OnModifyDone()

**调用时机**：组件属性修改完成时

**执行流程**：
```cpp
void WaterFlowPattern::OnModifyDone()
{
    // 1. 调用父类处理
    ScrollablePattern::OnModifyDone();

    // 2. 设置滚动条
    SetScrollBar(DisplayMode::OFF);

    // 3. 设置边缘效果回调
    SetEdgeEffectCallback(...);

    // 4. 处理 Sections 变更
    if (sections_) {
        sections_->SetOnDataChange(...);
    }
}
```

#### 2. BeforeCreateLayoutWrapper()

**调用时机**：创建布局包装器之前

**源码位置**：`water_flow_pattern.cpp:152-172`

**执行流程**：
```cpp
void WaterFlowPattern::BeforeCreateLayoutWrapper()
{
    // 1. 处理待处理的 section 变更
    for (const auto& start : sectionChangeStartPos_) {
        OnSectionChanged(start);
    }
    sectionChangeStartPos_.clear();

    // 2. 初始化 segments（如果有 sections 但 segmentTails_ 为空）
    if (sections_ && layoutInfo_->segmentTails_.empty()) {
        layoutInfo_->InitSegments(sections_->GetSectionInfo(), 0);
    }

    // 3. 处理 footer
    if (!sections_ && !SystemProperties::WaterFlowUseSegmentedLayout()) {
        auto footer = footer_.Upgrade();
        if (footer && footer->FrameCount() > 0) {
            layoutInfo_->footerIndex_ = 0;
        } else {
            layoutInfo_->ResetFooter();
        }
    }
}
```

#### 3. CreateLayoutAlgorithm()

**调用时机**：需要创建布局算法时

**执行流程**：
```cpp
RefPtr<LayoutAlgorithm> WaterFlowPattern::CreateLayoutAlgorithm()
{
    // 1. 传递 targetIndex
    if (targetIndex_.has_value()) {
        layoutInfo_->targetIndex_ = targetIndex_;
    }

    // 2. 根据模式选择算法
    RefPtr<WaterFlowLayoutBase> algorithm;
    if (layoutInfo_->Mode() == LayoutMode::SLIDING_WINDOW) {
        algorithm = MakeRefPtr<WaterFlowLayoutSW>(...);
    } else if (sections_ || SystemProperties::WaterFlowUseSegmentedLayout()) {
        algorithm = MakeRefPtr<WaterFlowSegmentedLayout>(...);
    } else {
        algorithm = MakeRefPtr<WaterFlowLayoutAlgorithm>(...);
    }

    // 3. 设置过度滚动能力
    algorithm->SetCanOverScrollStart(...);
    algorithm->SetCanOverScrollEnd(...);

    return algorithm;
}
```

#### 4. OnDirtyLayoutWrapperSwap()

**调用时机**：布局结果交换时

**执行流程**：
```cpp
bool WaterFlowPattern::OnDirtyLayoutWrapperSwap(
    const RefPtr<LayoutWrapper>& dirty,
    const DirtySwapConfig& config)
{
    // 1. 校准滚动状态
    // 可能调用 UpdateStartIndex() 进行状态同步

    // 2. 重置瞬态标志
    layoutInfo_->duringPositionCalc_ = false;

    // 3. 触发布局依赖的事件
    TriggerPostLayoutEvents();

    return true;
}
```

#### 5. TriggerPostLayoutEvents()

**调用时机**：布局完成后

**执行流程**：
```cpp
void WaterFlowPattern::TriggerPostLayoutEvents()
{
    // 1. 派发滚动事件
    // 2. 派发 ReachStart / ReachEnd 事件
    // 3. 派发 ScrollIndex 事件
    // 4. 派发 Observer 事件
}
```

### 状态变量详解

#### layoutInfo_

**类型**：`RefPtr<WaterFlowLayoutInfoBase>`

**含义**：存储布局状态信息

**关键成员**：
- `startIndex_` / `endIndex_`：视口范围
- `itemStart_` / `itemEnd_`：边界状态
- `offsetEnd_`：最后一项底部在视口内
- `delta_`：待消费的偏移变化
- `totalOffset_` / `currentOffset_`：滚动位置

#### sections_

**类型**：`RefPtr<WaterFlowSections>`

**含义**：分段配置

#### footer_

**类型**：`WeakPtr<UINode>`

**含义**：Footer 节点引用

---

## Model 层详解

### WaterFlowModelNG 核心职责

**WaterFlowModelNG** 提供 ArkTS 声明式 API，负责：

1. **创建 WaterFlow 节点**
2. **设置布局属性**（通过 WaterFlowLayoutProperty）
3. **注册事件处理**（通过 WaterFlowEventHub）
4. **管理滚动控制器**（ScrollPositionController）
5. **管理 Sections 配置**

### 关键 API 方法

#### 1. Create()

**源码位置**：`water_flow_model_ng.cpp`

**功能**：创建 WaterFlow FrameNode

```cpp
void WaterFlowModelNG::Create()
{
    // 1. 创建 WaterFlow FrameNode
    auto frameNode = FrameNode::CreateFrameNode(
        V2::WATERFLOW_ETS_TAG,
        MakeRefPtr<WaterFlowPattern>());

    // 2. 添加到 ViewStack
    ViewStackProcessor::GetInstance()->Push(frameNode);
}
```

**对应 ArkTS**：
```typescript
WaterFlow() {
  // 子组件
}
```

#### 2. SetColumnsTemplate() / SetRowsTemplate()

**功能**：设置列/行模板

```cpp
void WaterFlowModelNG::SetColumnsTemplate(const std::string& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(WaterFlowLayoutProperty, ColumnsTemplate, value);
}
```

**对应 ArkTS**：
```typescript
.columnsTemplate("1fr 1fr 1fr")
.rowsTemplate("1fr 1fr")
```

#### 3. SetLayoutMode()

**功能**：设置布局模式

```cpp
void WaterFlowModelNG::SetLayoutMode(WaterFlowLayoutMode mode)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto pattern = frameNode->GetPattern<WaterFlowPattern>();
    pattern->SetLayoutMode(mode);
}
```

**对应 ArkTS**：
```typescript
WaterFlow({
   layoutMode : WaterFlowLayoutMode.SLIDING_WINDOW
})
```

#### 4. SetOnScrollIndex()

**功能**：注册滚动索引变化事件

```cpp
void WaterFlowModelNG::SetOnScrollIndex(ScrollIndexFunc&& onScrollIndex)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto eventHub = frameNode->GetEventHub<WaterFlowEventHub>();
    eventHub->SetOnScrollIndex(std::move(onScrollIndex));
}
```

**对应 ArkTS**：
```typescript
.onScrollIndex((first: number, last: number) => {
  console.info(`Visible range: ${first} - ${last}`)
})
```

### 完整 API 映射表

| ArkTS API | WaterFlowModelNG 方法 | LayoutProperty | Pattern 影响 |
|-----------|----------------------|----------------|-------------|
| `.columnsTemplate(value)` | `SetColumnsTemplate()` | `SetColumnsTemplate()` | 触发重新布局 |
| `.rowsTemplate(value)` | `SetRowsTemplate()` | `SetRowsTemplate()` | 触发重新布局 |
| `.columnsGap(value)` | `SetColumnsGap()` | `SetColumnsGap()` | 列间距 |
| `.rowsGap(value)` | `SetRowsGap()` | `SetRowsGap()` | 行间距 |
| `.itemMinWidth(value)` | `SetItemMinWidth()` | `UpdateItemMinSize()` | Item 最小宽度 |
| `.itemMaxWidth(value)` | `SetItemMaxWidth()` | `UpdateItemMaxSize()` | Item 最大宽度 |
| `.itemMinHeight(value)` | `SetItemMinHeight()` | `UpdateItemMinSize()` | Item 最小高度 |
| `.itemMaxHeight(value)` | `SetItemMaxHeight()` | `UpdateItemMaxSize()` | Item 最大高度 |
| `.layoutMode(mode)` | `SetLayoutMode()` | - | 设置布局模式 |
| `.layoutDirection(dir)` | `SetLayoutDirection()` | `SetWaterflowDirection()` | 布局方向 |
| `.cachedCount(count)` | `SetCachedCount()` | `SetCachedCount()` | 缓存数量 |
| `.edgeEffect(effect)` | `SetEdgeEffect()` | - | 边缘效果 |
| `.nestedScroll(options)` | `SetNestedScroll()` | - | 嵌套滚动 |
| `.scrollEnabled(enabled)` | `SetScrollEnabled()` | `SetScrollEnabled()` | 是否可滚动 |
| `.friction(value)` | `SetFriction()` | - | 摩擦系数 |
| `.scrollBar(mode)` | `SetScrollBarMode()` | - | 滚动条模式 |
| `.onScrollIndex(callback)` | `SetOnScrollIndex()` | - | 注册事件 |
| `.onReachStart(callback)` | `SetOnReachStart()` | - | 注册事件 |
| `.onReachEnd(callback)` | `SetOnReachEnd()` | - | 注册事件 |

---

## LayoutInfo 详解

### WaterFlowLayoutInfoBase

**文件**：`layout/water_flow_layout_info_base.h`

**职责**：布局状态管理的基类，定义通用接口

**核心成员变量**：

```cpp
class WaterFlowLayoutInfoBase : public AceType {
public:
    // 边界状态
    bool itemStart_ = false;      // 是否在顶部
    bool itemEnd_ = false;        // 是否在底部（部分可见）
    bool offsetEnd_ = false;      // 最后一项底部在视口内

    // 视口范围
    int32_t startIndex_ = 0;      // 起始索引
    int32_t endIndex_ = -1;       // 结束索引
    int32_t footerIndex_ = -1;    // Footer 索引

    // 滚动状态
    float lastMainSize_ = 0.0f;   // 上次主轴尺寸
    float storedOffset_ = 0.0f;   // 存储的偏移（分布式迁移）
    float restoreOffset_ = 0.0f;  // 恢复偏移

    // 内容边距
    float contentStartOffset_ = 0.0f;
    float contentEndOffset_ = 0.0f;
    float footerHeight_ = 0.0f;

    // 分段信息
    std::vector<int32_t> segmentTails_;           // 每个段的尾部索引
    std::vector<PaddingPropertyF> margins_;       // 每个段的边距

    // 跳转状态
    int32_t jumpIndex_ = EMPTY_JUMP_INDEX;
    ScrollAlign align_ = ScrollAlign::START;
    std::optional<int32_t> targetIndex_;
    std::optional<float> extraOffset_;

    // 其他状态
    bool duringPositionCalc_ = false;             // 位置计算中
    bool measureInNextFrame_ = false;             // 延迟测量
    int32_t defCachedCount_ = 1;                  // 默认缓存数量
};
```

**核心方法**：

```cpp
// 纯虚方法 - 子类必须实现
virtual WaterFlowLayoutMode Mode() const = 0;
virtual float Offset() const = 0;
virtual void UpdateOffset(float delta) = 0;
virtual float CalibrateOffset() = 0;
virtual float EstimateTotalHeight() const = 0;
virtual int32_t GetCrossIndex(int32_t itemIndex) const = 0;
virtual OverScrollOffset GetOverScrolledDelta(float delta) const = 0;
virtual bool ReachStart(float prevPos, bool firstLayout) const = 0;
virtual bool ReachEnd(float prevPos, bool firstLayout) const = 0;
virtual bool OutOfBounds() const = 0;
virtual void Reset() = 0;
virtual bool IsMisaligned() const = 0;
virtual void InitSegments(const std::vector<WaterFlowSections::Section>& sections, int32_t start) = 0;

// 工具方法
int32_t NodeIdx(int32_t idx) const { return idx + footerIndex_ + 1; }
int32_t ItemCnt(int32_t childrenCount) const { return childrenCount - footerIndex_ - 1; }
int32_t GetSegment(int32_t itemIdx) const;
```

### WaterFlowLayoutInfo (TOP_DOWN 模式)

**文件**：`layout/top_down/water_flow_layout_info.h`

**特点**：
- 保留完整布局信息
- `currentOffset_` 始终精确
- `scrollTo()` / `animateTo()` 可靠
- 支持通过二分搜索快速位置查找 (`endPosArray_`)

**额外成员**：

```cpp
class WaterFlowLayoutInfo : public WaterFlowLayoutInfoBase {
    // 所有项目的位置信息
    std::map<int32_t, std::map<int32_t, ItemInfo>> itemInfos_;

    // 快速位置查找数组
    std::vector<float> endPosArray_;

    // 列状态
    std::vector<float> lanes_;

    // 偏移
    float currentOffset_ = 0.0f;
    float totalOffset_ = 0.0f;
};
```

### WaterFlowLayoutInfoSW (SLIDING_WINDOW 模式)

**文件**：`layout/sliding_window/water_flow_layout_info_sw.h`

**特点**：
- 仅维护视口 + 缓存窗口
- 滚动偏移在跳转或 section 变更后可能变为**估算值**
- 基于位置的 `scrollTo()` / `animateTo()` 可能不可靠 → 优先使用 `ScrollToIndex()`
- 使用基于列的窗口结构
- 可能触发错位校正重建布局

**额外成员**：

```cpp
class WaterFlowLayoutInfoSW : public WaterFlowLayoutInfoBase {
    // 窗口内的列
    std::vector<Lane> lanes_;

    // 同步状态
    bool synced_ = false;

    // 窗口边界
    float windowStart_;
    float windowEnd_;
};
```

---

## LayoutAlgorithm 层详解

### WaterFlowLayoutBase

**文件**：`layout/water_flow_layout_algorithm_base.h`

**职责**：布局算法基类

**核心方法**：

```cpp
class WaterFlowLayoutBase : public LayoutAlgorithm {
public:
    virtual void Measure(LayoutWrapper* layoutWrapper) override;
    virtual void Layout(LayoutWrapper* layoutWrapper) override;

    void SetCanOverScrollStart(bool can) { canOverScrollStart_ = can; }
    void SetCanOverScrollEnd(bool can) { canOverScrollEnd_ = can; }

protected:
    bool canOverScrollStart_ = false;
    bool canOverScrollEnd_ = false;
};
```

### WaterFlowLayoutAlgorithm (基础 TOP_DOWN)

**文件**：`layout/top_down/water_flow_layout_algorithm.h`

**特点**：
- 直接继承 `WaterFlowLayoutBase`
- 在 `FillViewport()` 中直接更新位置字段
- 不调用 `Sync()`

**核心方法**：

```cpp
class WaterFlowLayoutAlgorithm : public WaterFlowLayoutBase {
public:
    void Measure(LayoutWrapper* layoutWrapper) override;
    void Layout(LayoutWrapper* layoutWrapper) override;

private:
    void FillViewport(float mainSize);
    void MeasureItem(int32_t idx);
    void LayoutItem(int32_t idx, const OffsetF& offset);
    void UpdateStartIndex();
};
```

### WaterFlowSegmentedLayout (分段 TOP_DOWN)

**文件**：`layout/top_down/water_flow_segmented_layout.h`

**特点**：
- 继承 `WaterFlowSegmentLayoutBase`
- 支持多段不同配置
- 在不同场景下可能多次调用 `Sync()`

### WaterFlowLayoutSW (SLIDING_WINDOW)

**文件**：`layout/sliding_window/water_flow_layout_sw.h`

**特点**：
- 继承 `WaterFlowSegmentLayoutBase`
- 通过继承获得 section 支持
- 在 Measure 结束时调用一次 `Sync()` 作为后测量整合步骤

**Sync() 功能**：
- 从列数据计算 `startIndex_`, `endIndex_`
- 更新 `startPos_`, `endPos_`
- 设置边界标志 (`itemStart_`, `itemEnd_`, `offsetEnd_`)
- 重置 `delta_` 为 0
- 消费待处理的偏移变更

---

## 属性系统

### WaterFlowLayoutProperty

**文件**：`water_flow_layout_property.h`

**核心属性**：

```cpp
class WaterFlowLayoutProperty : public ScrollableLayoutProperty {
public:
    // 列/行模板
    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(ColumnsTemplate, std::string);
    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(RowsTemplate, std::string);

    // 间距
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP_AND_USING_CALLBACK(ColumnsGap, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP_AND_USING_CALLBACK(RowsGap, Dimension, PROPERTY_UPDATE_MEASURE);

    // 缓存
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(CachedCount, int32_t, PROPERTY_UPDATE_MEASURE_SELF);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ShowCachedItems, bool, PROPERTY_UPDATE_MEASURE_SELF);

    // 布局方向
    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(WaterflowDirection, FlexDirection);

    // 滚动使能
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ScrollEnabled, bool, PROPERTY_UPDATE_MEASURE);

    // 同步加载
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(SyncLoad, bool, PROPERTY_UPDATE_NORMAL);

    // Item 约束
    void UpdateItemMinSize(const CalcSize& value);
    void UpdateItemMaxSize(const CalcSize& value);
    std::optional<CalcSize> GetItemMinSize() const;
    std::optional<CalcSize> GetItemMaxSize() const;

    // 方向判断
    Axis GetAxis() const;
    bool IsReverse() const;
    bool IsVerticalReverse() const;
};
```

### 属性传递流程

```
ArkTS API
    ↓
WaterFlowModelNG::SetXXX()
    ↓
WaterFlowLayoutProperty::SetXXX()
    ↓
OnXXXUpdate() (触发模式修改)
    ↓
WaterFlowPattern 读取属性
    ↓
CreateLayoutAlgorithm() 使用属性
    ↓
应用到布局
```

---

## 事件处理

### 事件类型

WaterFlow 组件支持以下事件：

| 事件 | 触发时机 | 注册方法 |
|-----|---------|---------|
| **onScrollIndex** | 可见项索引变化 | `SetOnScrollIndex()` |
| **onReachStart** | 到达顶部 | `SetOnReachStart()` |
| **onReachEnd** | 到达底部 | `SetOnReachEnd()` |
| **onScroll** | 滚动进行中 | `SetOnScroll()` |
| **onScrollStart** | 滚动开始 | `SetOnScrollStart()` |
| **onScrollStop** | 滚动停止 | `SetOnScrollStop()` |
| **onScrollFrameBegin** | 每帧滚动前 | `SetOnScrollFrameBegin()` |

### 事件语义

#### ReachStart

**定义**：布局状态边界事件，检测何时到达内容顶部

**实现差异**：
- **TOP_DOWN 模式**：使用**偏移过渡检测**，比较前后滚动偏移与 `contentStartOffset`
- **SLIDING_WINDOW 模式**：使用**标志变化检测**（检查 `itemStart_` 标志过渡）结合**偏移过渡**过度滚动恢复

两种方式都检测起始边界，但通过不同机制适应各自的布局模型。

#### ReachEnd

**触发条件**：
- 布局指示内容结束边界，**且**
- `repeatDifference_ == 0`（所有重复项已加载）

#### ScrollIndex

**触发时机**：可见项范围变化时

**回调参数**：`(first: number, last: number)`

### WaterFlowEventHub

**文件**：`water_flow_event_hub.h`

```cpp
class WaterFlowEventHub : public ScrollableEventHub {
public:
    void SetOnScrollIndex(ScrollIndexFunc&& onScrollIndex);
    const ScrollIndexFunc& GetOnScrollIndex() const;

    void SetJSFrameNodeOnWaterFlowScrollIndex(ScrollIndexFunc&& onScroll);
    const ScrollIndexFunc& GetJSFrameNodeOnWaterFlowScrollIndex() const;

private:
    ScrollIndexFunc onScrollIndexEvent_;
    ScrollIndexFunc onJSFrameNodeScrollIndexEvent_;
};
```

---

## Sections 分段机制

### WaterFlowSections

**文件**：`water_flow_sections.h`

**功能**：支持多段不同配置的布局

### Section 结构

```cpp
struct Section {
    int32_t itemsCount = 0;                        // 该段的项目数量
    std::optional<int32_t> crossCount;             // 列数（可选）
    GetItemMainSizeByIndex onGetItemMainSizeByIndex; // 获取项目主轴尺寸的回调
    std::optional<Dimension> columnsGap;           // 列间距（可选）
    std::optional<Dimension> rowsGap;              // 行间距（可选）
    std::optional<MarginProperty> margin;          // 边距（可选）

    bool operator==(const Section& other) const;
    bool OnlyCountDiff(const Section& other) const;
};
```

### 使用方式

**ArkTS**：
```typescript
sections: WaterFlowSections = new WaterFlowSections()

aboutToAppear() {
   this.sections.push({
      itemsCount: 10,
      crossCount: 2,
      columnsGap: 10,
      rowsGap: 10,
      margin: { top: 20, bottom: 20 }
   })

   this.sections.push({
      itemsCount: 20,
      crossCount: 3,
      columnsGap: 5,
      rowsGap: 5
   })
}

WaterFlow({ sections: this.sections}) {
  LazyForEach(this.dataSource, (item) => {
    FlowItem() {
      // ...
    }
  })
}
```

### Section 变更流程

```
前端修改 sections 配置
    ↓
WaterFlowSections::ChangeData()
    ↓
触发 onSectionDataChange_ 回调
    ↓
WaterFlowPattern::OnSectionChanged(start)
    ↓
layoutInfo_->InitSegments() 重新初始化
    ↓
下次布局时应用新配置
```

---

## 生命周期与执行流程

### 生命周期不变量

1. **BeforeCreateLayoutWrapper()**
   - 处理待处理的 section 变更
   - 准备分段状态

2. **CreateLayoutAlgorithm()**
   - 根据模式 / sections / 系统标志选择算法

3. **Measure()**
   - 填充视口，测量项目
   - **WaterFlowLayoutSW**：在 Measure 结束时调用一次 `Sync()` 作为后测量整合
   - **WaterFlowSegmentedLayout**：在不同场景中可能多次调用 `Sync()`
   - **WaterFlowLayoutAlgorithm**：在 `FillViewport()` 中直接更新位置字段（不调用 `Sync()`）

4. **Layout()**
   - 定位项目（由 LayoutAlgorithm 执行）
   - 可能调用 `UpdateStartIndex()` 进行索引校准

5. **OnDirtyLayoutWrapperSwap()**
   - 校准滚动状态
   - 重置瞬态标志
   - 触发布局依赖的事件

6. **TriggerPostLayoutEvents()**
   - 派发滚动 / reach / observer 事件

### 规则

- **Pattern** 不直接执行布局定位（这是 LayoutAlgorithm 的责任）
- **Pattern** 可能在 `OnDirtyLayoutWrapperSwap()` 中调用状态同步方法（如 `UpdateStartIndex()`）
- **LayoutAlgorithm** 可能在 Layout 阶段执行索引调整
- `measureInNextFrame_` 延迟事件触发并在下一帧触发重新测量

### 完整执行流程图

```
触发布局（属性修改 / 尺寸变化 / 滚动）
    ↓
BeforeCreateLayoutWrapper()
    ├─ 处理 section 变更
    └─ 初始化 segments
    ↓
CreateLayoutAlgorithm()
    ├─ 选择布局算法
    └─ 传递状态
    ↓
LayoutAlgorithm::Measure()
    ├─ 计算列配置
    ├─ 填充视口
    ├─ 测量所有可见项
    └─ 更新布局信息（Sync 或直接更新）
    ↓
LayoutAlgorithm::Layout()
    ├─ 定位所有项目
    └─ 索引校准（如需要）
    ↓
OnDirtyLayoutWrapperSwap()
    ├─ 同步布局结果
    ├─ 重置瞬态标志
    └─ 检查边界
    ↓
TriggerPostLayoutEvents()
    ├─ FireOnScrollIndex()
    ├─ FireOnReachStart()
    ├─ FireOnReachEnd()
    └─ Observer 事件
    ↓
[布局完成]
```

---

## 完整 API 清单

### ArkTS API 列表

#### 创建和基础配置

```typescript
// 创建瀑布流容器
WaterFlow() { ... }
WaterFlow(options: WaterFlowOptions) { ... }

interface WaterFlowOptions {
  footer?: CustomBuilder
  scroller?: Scroller
  sections?: WaterFlowSections
  layoutMode?: WaterFlowLayoutMode
}

// 列/行模板
.columnsTemplate(value: string)
.rowsTemplate(value: string)

// 间距
.columnsGap(value: Length)
.rowsGap(value: Length)

// Item 尺寸约束
.itemMinWidth(value: Length)
.itemMaxWidth(value: Length)
.itemMinHeight(value: Length)
.itemMaxHeight(value: Length)

// 布局方向
.layoutDirection(value: FlexDirection)

// 布局模式
.layoutMode(value: WaterFlowLayoutMode)
// WaterFlowLayoutMode: TOP_DOWN | SLIDING_WINDOW

// 滚动条
.scrollBar(value: BarState)
.scrollBarColor(value: Color)
.scrollBarWidth(value: Length)

// 边缘效果
.edgeEffect(value: EdgeEffect)

// 嵌套滚动
.nestedScroll(options: NestedScrollOptions)

// 滚动使能
.scrollEnabled(value: boolean)

// 摩擦系数
.friction(value: number)

// 缓存
.cachedCount(value: number)
```

#### 滚动事件

```typescript
// 滚动索引变化
.onScrollIndex(event: (first: number, last: number) => void)

// 到达顶部
.onReachStart(event: () => void)

// 到达底部
.onReachEnd(event: () => void)

// 滚动进行中
.onScroll(event: (offset: number, state: ScrollState) => void)

// 滚动开始
.onScrollStart(event: () => void)

// 滚动停止
.onScrollStop(event: () => void)

// 每帧滚动前
.onScrollFrameBegin(event: (offset: number) => { offsetRemain: number })
```

#### 滚动控制（Scroller）

```typescript
// 滚动到指定索引
scroller.scrollToIndex(index: number, smooth?: boolean, align?: ScrollAlign)

// 滚动到指定位置
scroller.scrollTo(options: { xOffset: number, yOffset: number, animation?: ScrollAnimationOptions })

// 滚动指定距离
scroller.scrollBy(deltaX: number, deltaY: number)

// 滚动到边缘
scroller.scrollEdge(edge: Edge)

// 滚动一页
scroller.scrollPage(options: { next: boolean })

// 获取当前偏移
scroller.currentOffset(): { xOffset: number, yOffset: number }

// 获取项目矩形
scroller.getItemRect(index: number): RectResult
```

### C++ API 列表

#### WaterFlowPattern 公共方法

```cpp
// 位置相关
double GetTotalOffset() const;
int32_t GetBeginIndex() const;
int32_t GetEndIndex() const;
bool GetItemStart() const;
bool GetItemEnd() const;
int32_t GetRows() const;
int32_t GetColumns() const;

// 滚动控制
void ScrollTo(float position) override;
void AnimateTo(float position, float duration, const RefPtr<Curve>& curve, ...) override;
void ScrollToIndex(int32_t index, bool smooth, ScrollAlign align, ...) override;
void ScrollPage(bool reverse, bool smooth, ...) override;

// 边界判断
bool IsScrollable() const override;
bool IsAtTop() const override;
bool IsAtBottom(bool considerRepeat = false) const override;
bool IsReverse() const override;

// Sections 管理
RefPtr<WaterFlowSections> GetSections() const;
RefPtr<WaterFlowSections> GetOrCreateWaterFlowSections();
void ResetSections();

// Footer 管理
void AddFooter(const RefPtr<NG::UINode>& footer);
bool hasFooter();

// 布局模式
void SetLayoutMode(LayoutMode mode);
LayoutMode GetLayoutMode() const;

// 状态恢复
std::string ProvideRestoreInfo() override;
void OnRestoreInfo(const std::string& restoreInfo) override;

// 调试
void DumpInfo() override;
void DumpAdvanceInfo() override;
```

---

## 关键实现细节

### 1. 列配置解析

**源码位置**：`water_flow_layout_utils.cpp`

**功能**：解析 `columnsTemplate` 字符串为列宽数组

**示例**：
```
"1fr 1fr 1fr" → [1/3, 1/3, 1/3] * 可用宽度
"100px 1fr 2fr" → [100px, (剩余宽度)/3, (剩余宽度)*2/3]
```

### 2. 项目放置算法

**原理**：将每个项目放置到当前最短的列中

```cpp
// 伪代码
for (item in items) {
    int shortestLane = FindShortestLane(lanes);
    PlaceItem(item, shortestLane);
    lanes[shortestLane] += item.height + rowGap;
}
```

### 3. 偏移量管理

**TOP_DOWN 模式**：
```cpp
// 偏移始终精确
currentOffset_ += delta;
// 可直接用于 scrollTo
```

**SLIDING_WINDOW 模式**：
```cpp
// 偏移可能为估算值
// 跳转后需要通过 CalibrateOffset() 校准
float adjustment = layoutInfo_->CalibrateOffset();
```

### 4. 边界状态判断

```cpp
bool WaterFlowPattern::IsAtTop() const
{
    return layoutInfo_->itemStart_;  // 使用布局信息的标志
}

bool WaterFlowPattern::IsAtBottom(bool considerRepeat) const
{
    return considerRepeat
        ? (layoutInfo_->offsetEnd_ && layoutInfo_->repeatDifference_ == 0)
        : layoutInfo_->offsetEnd_;
}
```

### 5. Sync() 调用时机

**WaterFlowLayoutSW (SLIDING_WINDOW)**：
- 在 Measure 结束时调用一次
- 作为后测量整合步骤

**WaterFlowSegmentedLayout (TOP_DOWN 分段)**：
- 在不同场景下可能多次调用
- 偏移滚动、跳转操作、高度变化等

**WaterFlowLayoutAlgorithm (基础 TOP_DOWN)**：
- 不调用 Sync()
- 在 `FillViewport()` 中直接更新位置字段

---

## 布局模式差异

### TOP_DOWN

**特点**：
- 保留所有测量过的项目的完整布局信息
- `currentOffset_` 始终精确（非估算）
- `scrollTo()` / `animateTo()` 基于存储的项目位置可靠工作
- 支持通过二分搜索快速位置查找 (`endPosArray_`)

**适用场景**：
- 项目数量适中（< 10000）
- 需要精确滚动控制
- 频繁的 `scrollTo` 操作

### SLIDING_WINDOW

**特点**：
- 仅维护视口 + 缓存窗口（窗口模型）
- 滚动偏移在跳转或 section 变更后可能变为**估算值**
- 基于位置的 `scrollTo()` / `animateTo()` 可能不可靠 → 优先使用 `ScrollToIndex()`
- 使用基于列的窗口结构
- 可能触发错位校正重建布局

**适用场景**：
- 大数据集（> 10000 项目）
- 主要使用 `scrollToIndex`
- 内存敏感场景

### 共同特性

- 都支持通过 **WaterFlowSections** 进行分段布局
- 允许每段有不同的配置（列数、间距、边距）

---

## 使用示例

### 示例 1：基础瀑布流

```typescript
@Entry
@Component
struct BasicWaterFlow {
  @State items: number[] = Array.from({ length: 100 }, (_, i) => i)

  build() {
    WaterFlow() {
      ForEach(this.items, (item: number) => {
        FlowItem() {
          Text(`Item ${item}`)
            .width('100%')
            .height(80 + (item % 5) * 20)  // 不等高
            .backgroundColor(Color.Pink)
        }
      })
    }
    .columnsTemplate("1fr 1fr 1fr")
    .columnsGap(10)
    .rowsGap(10)
    .padding(10)
    .width('100%')
    .height('100%')
  }
}
```

### 示例 2：带滚动控制器

```typescript
@Entry
@Component
struct WaterFlowWithScroller {
  private scroller: Scroller = new Scroller()
  @State items: number[] = Array.from({ length: 200 }, (_, i) => i)

  build() {
    Column() {
      WaterFlow({ scroller: this.scroller }) {
        ForEach(this.items, (item: number) => {
          FlowItem() {
            Text(`${item}`)
              .width('100%')
              .height(100 + (item % 3) * 50)
          }
        })
      }
      .columnsTemplate("1fr 1fr")
      .rowsGap(5)
      .columnsGap(5)
      .height('80%')

      Row() {
        Button('Top')
          .onClick(() => this.scroller.scrollEdge(Edge.Top))

        Button('Index 50')
          .onClick(() => this.scroller.scrollToIndex(50, true))

        Button('Bottom')
          .onClick(() => this.scroller.scrollEdge(Edge.Bottom))
      }
      .justifyContent(FlexAlign.SpaceAround)
      .width('100%')
    }
  }
}
```

### 示例 3：带事件监听

```typescript
@Entry
@Component
struct WaterFlowWithEvents {
  @State firstIndex: number = 0
  @State lastIndex: number = 0

  build() {
    Column() {
      Text(`Visible: ${this.firstIndex} - ${this.lastIndex}`)
        .height(40)

      WaterFlow() {
        ForEach(Array.from({ length: 100 }), (_, index) => {
          FlowItem() {
            Text(`${index}`)
              .height(80 + (index % 4) * 30)
          }
        })
      }
      .columnsTemplate("1fr 1fr 1fr")
      .onScrollIndex((first, last) => {
        this.firstIndex = first
        this.lastIndex = last
      })
      .onReachStart(() => {
        console.info('Reached start')
      })
      .onReachEnd(() => {
        console.info('Reached end')
      })
    }
  }
}
```

### 示例 4：分段布局（Sections）

```typescript
@Entry
@Component
struct WaterFlowWithSections {
  private sections: WaterFlowSections = new WaterFlowSections()

  aboutToAppear() {
    this.sections.push({
      itemsCount: 10,
      crossCount: 2,
      columnsGap: 10,
      rowsGap: 10,
      margin: { top: 20 }
    })

    this.sections.push({
      itemsCount: 30,
      crossCount: 3,
      columnsGap: 5,
      rowsGap: 5
    })

    this.sections.push({
      itemsCount: 20,
      crossCount: 4,
      columnsGap: 3,
      rowsGap: 3,
      margin: { bottom: 20 }
    })
  }

  build() {
    WaterFlow({ sections: this.sections }) {
      ForEach(Array.from({ length: 60 }), (_, index) => {
        FlowItem() {
          Text(`${index}`)
            .height(60 + (index % 5) * 20)
        }
      })
    }
    .width('100%')
    .height('100%')
  }
}
```

### 示例 5：SLIDING_WINDOW 模式（大数据集）

```typescript
@Entry
@Component
struct LargeDataWaterFlow {
  private dataSource: LazyDataSource = new LazyDataSource(100000)
  private scroller: Scroller = new Scroller()

  build() {
    WaterFlow({
      scroller: this.scroller,
      layoutMode: WaterFlowLayoutMode.SLIDING_WINDOW
    }) {
      LazyForEach(this.dataSource, (item: number) => {
        FlowItem() {
          Text(`${item}`)
            .height(80 + (item % 6) * 20)
        }
      })
    }
    .columnsTemplate("1fr 1fr 1fr 1fr")
    .cachedCount(4)
    .onScrollIndex((first, last) => {
      console.info(`Range: ${first} - ${last}`)
    })
  }
}
```

### 示例 6：带 Footer

```typescript
@Entry
@Component
struct WaterFlowWithFooter {
  @Builder
  Footer() {
    Row() {
      Text('- End of List -')
        .textAlign(TextAlign.Center)
    }
    .width('100%')
    .height(60)
    .backgroundColor(Color.Gray)
  }

  build() {
    WaterFlow({ footer: this.Footer }) {
      ForEach(Array.from({ length: 50 }), (_, index) => {
        FlowItem() {
          Text(`Item ${index}`)
            .height(100)
        }
      })
    }
    .columnsTemplate("1fr 1fr")
    .width('100%')
    .height('100%')
  }
}
```

---

## 调试指南

### 1. 日志调试

**使用专用日志标签**：
```cpp
#include "base/log/ace_trace.h"

// WaterFlow 相关日志
TAG_LOGI(AceLogTag::ACE_WATERFLOW, "ScrollToIndex: %{public}d", index);
TAG_LOGD(AceLogTag::ACE_WATERFLOW, "offset: %{public}f, itemStart: %{public}d",
    layoutInfo_->Offset(), layoutInfo_->itemStart_);
```

### 2. 关键状态组

**视口范围**：
- `startIndex_`, `endIndex_`

**边界状态**：
- `itemStart_`, `itemEnd_`, `offsetEnd_`

**滚动过渡**：
- `delta_`, `totalOffset_`, `currentOffset_`

**跳转状态**：
- `jumpIndex_`, `duringPositionCalc_`

**延迟布局**：
- `measureInNextFrame_`, `synced_` (仅 SW)

**数据偏移**：
- `newStartIndex_`, `repeatDifference_`

### 3. Dump 方法

```cpp
void WaterFlowPattern::DumpAdvanceInfo()
{
    // 输出布局模式
    DumpLog::GetInstance().AddDesc("LayoutMode: %d", GetLayoutMode());

    // 输出视口范围
    DumpLog::GetInstance().AddDesc("StartIndex: %d, EndIndex: %d",
        layoutInfo_->startIndex_, layoutInfo_->endIndex_);

    // 输出边界状态
    DumpLog::GetInstance().AddDesc("ItemStart: %d, OffsetEnd: %d",
        layoutInfo_->itemStart_, layoutInfo_->offsetEnd_);

    // 输出偏移
    DumpLog::GetInstance().AddDesc("Offset: %f", layoutInfo_->Offset());
}
```

### 4. 常见问题定位

#### 问题 1：项目位置错误

**检查点**：
- 列模板解析是否正确
- 列间距计算是否正确
- 项目测量尺寸是否正确

#### 问题 2：滚动不流畅

**检查点**：
- 是否启用了 SLIDING_WINDOW 模式
- cachedCount 是否足够
- 是否有复杂的 onScroll 处理

#### 问题 3：ScrollToIndex 不准确

**检查点**：
- 在 SLIDING_WINDOW 模式下，位置可能是估算值
- 检查 `IsMisaligned()` 返回值
- 考虑使用动画滚动

#### 问题 4：Sections 不生效

**检查点**：
- sections 数据是否正确传递
- itemsCount 总和是否与实际项目数匹配
- `InitSegments()` 是否被调用

---

## 常见问题

### Q1: WaterFlow 和 Grid 有什么区别？

**A**：
- **WaterFlow**：瀑布流布局，项目放入最短列，高度可不等
- **Grid**：网格布局，项目按行列规则排列，通常等高

**选择建议**：
- 需要不等高项目的瀑布流效果 → WaterFlow
- 需要规则的网格布局 → Grid

### Q2: 如何选择布局模式？

**A**：
- **TOP_DOWN**：项目数量适中，需要精确滚动控制
- **SLIDING_WINDOW**：大数据集，内存敏感，主要使用 scrollToIndex

### Q3: cachedCount 如何设置？

**A**：
- 根据屏幕可见项目数设置
- 通常设置为可见项目数的 1-2 倍
- 过大会增加内存占用，过小会导致滚动时出现空白

### Q4: 如何处理分段布局中的边距？

**A**：
```typescript
sections.push({
  itemsCount: 10,
  margin: {
    top: 20,
    bottom: 10,
    left: 15,
    right: 15
  }
})
```

### Q5: 为什么 scrollTo 在 SLIDING_WINDOW 模式下不准确？

**A**：
SLIDING_WINDOW 模式的偏移可能是估算值，建议：
1. 优先使用 `scrollToIndex()`
2. 如果必须使用 `scrollTo()`，考虑切换到 TOP_DOWN 模式
3. 等待 `CalibrateOffset()` 校准后再执行精确滚动

### Q6: 如何实现无限滚动？

**A**：
```typescript
WaterFlow() {
  LazyForEach(this.dataSource, (item) => {
    FlowItem() { ... }
  })
}
.onReachEnd(() => {
  this.loadMoreData()
})
```

### Q7: Footer 何时显示？

**A**：
Footer 在滚动到内容末尾时显示。确保：
1. 所有项目都已加载（repeatDifference_ == 0）
2. 最后一个项目在视口内（offsetEnd_ == true）

---

## 关键约束（DO NOT BREAK）

1. **索引转换必须考虑 footer 参与**
   所有 FlowItem 索引 → 子节点索引转换必须使用布局提供的映射，
   以正确处理 footer 参与。

2. **瞬态状态清理**
   跳转和位置计算标志必须在布局交换后清除。
   遗漏重置会导致状态损坏。

3. **Sync 时机（仅 WaterFlowSegmentedLayout 和 WaterFlowLayoutSW）**
   - Sync 消费待处理的偏移变更
   - 不能在测量完成前运行
   - 注意：WaterFlowLayoutAlgorithm 在 `FillViewport()` 中直接更新位置字段，不使用 Sync

4. **错位校正**
   必须在以下时机检查：
   - 滚动结束
   - 动画停止
   - `OnDirtyLayoutWrapperSwap()` 中的布局交换后（特别是在段边界处）

   如果状态不一致，布局可能需要重置和重建。

5. **Section 变更流程**
   Section 更新通过回调传播 → 排队变更 → 在下次布局前处理。

6. **缓存预加载隔离（SW）**
   缓存测量不能永久修改可见布局窗口状态。

7. **Pattern–Algorithm 边界**
   - **Pattern** 不直接参与 LayoutAlgorithm 的 Layout 阶段执行
   - **Pattern** 可能在 `OnDirtyLayoutWrapperSwap()` 中调用状态同步方法（如 `UpdateStartIndex()`）
   - **LayoutAlgorithm** 可能在 Layout 阶段执行索引校准
   - 大多数位置更新来自 Measure 阶段（分段/SW 通过 `Sync()`，基础布局在 `FillViewport()` 中直接更新）
   - 缓存状态方法（`BeginCacheUpdate()` / `EndCacheUpdate()`）仅 SW 使用

---

## 附录

### A. 术语表

| 术语 | 英文 | 描述 |
|-----|------|------|
| 瀑布流 | WaterFlow | 多列不等高布局，项目放入最短列 |
| 列 | Lane | 瀑布流的垂直通道 |
| 分段 | Section | 一组具有相同配置的项目 |
| 视口 | Viewport | 可见区域 |
| 滑动窗口 | Sliding Window | 仅保留视口附近数据的布局模式 |
| 偏移 | Offset | 滚动位置 |
| 缓存数量 | Cached Count | 视口外预加载的项目数 |

### B. 源码文件索引

| 文件 | 行数（约） | 描述 |
|-----|------|------|
| `water_flow_pattern.h` | 300 | WaterFlowPattern 类定义 |
| `water_flow_pattern.cpp` | 1500 | WaterFlowPattern 实现 |
| `water_flow_layout_info_base.h` | 290 | 布局信息基类定义 |
| `water_flow_layout_algorithm.h/cpp` | 800 | TOP_DOWN 基础布局算法 |
| `water_flow_segmented_layout.h/cpp` | 600 | TOP_DOWN 分段布局算法 |
| `water_flow_layout_sw.h/cpp` | 700 | SLIDING_WINDOW 布局算法 |
| `water_flow_model_ng.h/cpp` | 500 | NG Model 实现 |
| `water_flow_sections.h/cpp` | 200 | 分段配置 |

### C. 相关文档

- [WaterFlow 组件官方文档](https://gitcode.com/openharmony/docs/blob/master/zh-cn/application-dev/reference/apis-arkui/arkui-ts/ts-container-waterflow.md)
- [FlowItem 组件](https://gitcode.com/openharmony/docs/blob/master/zh-cn/application-dev/reference/apis-arkui/arkui-ts/ts-container-flowitem.md)
- [Scroller 对象](https://gitcode.com/openharmony/docs/blob/master/zh-cn/application-dev/reference/apis-arkui/arkui-ts/ts-container-scroll.md#scroller)

### D. 版本历史

| 版本 | 日期 | 变更 |
|-----|------|------|
| v1.0 | 2026-02-02 | 初始版本 |

---

**文档结束**

> 本文档基于 OpenHarmony ace_engine 源码分析和 `frameworks/core/components_ng/pattern/waterflow/CLAUDE.md` 生成，如有错误或遗漏，欢迎指正。
