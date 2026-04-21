# Grid 组件完整知识库

> **文档版本**: v1.0
> **更新时间**: 2026-02-07
> **源码版本**: OpenHarmony ace_engine (master 分支)

---

## 目录

1. [概述](#概述)
2. [目录结构](#目录结构)
3. [核心类继承关系](#核心类继承关系)
4. [Pattern层详解](#pattern层详解)
5. [Model层详解](#model层详解)
6. [布局算法详解](#布局算法详解)
7. [GridLayoutInfo数据结构](#gridlayoutinfo数据结构)
8. [GridItem子组件](#griditem子组件)
9. [完整API清单](#完整api清单)
10. [事件系统](#事件系统)
11. [滚动控制](#滚动控制)
12. [使用示例](#使用示例)
13. [性能优化](#性能优化)
14. [调试指南](#调试指南)
15. [测试覆盖](#测试覆盖)
16. [常见问题](#常见问题)

---

## 概述

### 组件定位

**Grid 组件**是 OpenHarmony ArkUI 框架中的**网格布局容器组件**，用于按照行列形式排列子组件。Grid 支持五种布局算法模式，可以适应从简单的自适应网格到复杂的不规则跨行列项目等各种布局需求。

### 技术架构

```
┌─────────────────────────────────────────────────────────┐
│  应用层 (ArkTS)                                           │
│  Grid(scroller, layoutOptions) { GridItem() }           │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│  桥接层 (Model Layer)                                    │
│  GridModelNG::Create() → FrameNode创建                  │
│  源码：grid_model_ng.cpp                                 │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│  核心层 (Pattern Layer)                                  │
│  GridPattern → SelectableContainerPattern               │
│  ├── GridLayoutInfo - 布局状态管理                       │
│  ├── GridEventHub - 事件处理                             │
│  ├── GridFocus - 焦点管理                                │
│  └── GridAccessibilityProperty - 无障碍                 │
│  源码：grid_pattern.h/cpp                                │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│  布局算法层 (LayoutAlgorithm Layer)                      │
│  根据配置选择5种算法之一:                                 │
│  1. GridAdaptiveLayoutAlgorithm - 自适应布局             │
│  2. GridLayoutAlgorithm - 静态布局（无滚动）            │
│  3. GridCustomLayoutAlgorithm - 自定义布局               │
│  4. GridIrregularLayoutAlgorithm - 不规则布局            │
│  5. GridScrollLayoutAlgorithm - 可滚动布局               │
│  源码：grid_*/grid_*_layout_algorithm.cpp                │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│  渲染层 (Render Layer)                                   │
│  Rosen + Skia 渲染                                       │
└─────────────────────────────────────────────────────────┘
```

### 代码规模

| 项目 | 数量 |
|-----|------|
| 核心文件 | 约 70 个文件 |
| 核心代码 | 约 25,000+ 行 C++ 代码 |
| Pattern文件 | grid_pattern.h (367行), grid_pattern.cpp |
| Model文件 | grid_model_ng.h (187行), grid_model_ng.cpp |
| 布局算法 | 5 种算法，分布在不同子目录 |
| 测试文件 | 约 30 个测试文件 |

### 功能特性

| 功能类别 | 具体功能 |
|---------|---------|
| **布局模式** | 自适应布局、静态布局、自定义布局、不规则布局、可滚动布局 |
| **行列控制** | columnsTemplate、rowsTemplate、columnsGap、rowsGap |
| **滚动支持** | Scroller控制器、滚动事件、边缘效果、嵌套滚动 |
| **不规则项目** | 跨行列项目、layoutOptions自定义 |
| **交互功能** | 多选模式、拖拽编辑、焦点导航 |
| **性能优化** | 虚拟滚动、行跳跃优化、预加载机制 |

---

## 目录结构

### 源码目录

```
frameworks/core/components_ng/pattern/grid/
├── Core Implementation (核心实现)
│   ├── grid_pattern.cpp/h              # Grid 主逻辑和生命周期管理
│   ├── grid_model_ng.cpp/h             # Grid 数据模型 (ArkTS API 层)
│   ├── grid_model_static.cpp/h         # 静态 Grid 模型
│   └── grid_view.h                     # Grid 视图接口
│
├── Layout Algorithms (布局算法 - 5种类型)
│   ├── grid_adaptive/                  # 自适应布局算法
│   │   └── grid_adaptive_layout_algorithm.cpp/h
│   │       # 使用场景: 无 columnsTemplate 且无 rowsTemplate
│   │       # 行为: 项目自适应填充可用空间
│   │
│   ├── grid_layout/                    # 静态布局算法
│   │   └── grid_layout_algorithm.cpp/h
│   │       # 使用场景: columnsTemplate 和 rowsTemplate 都设置
│   │       # 行为: 固定网格大小, 无滚动
│   │
│   ├── grid_custom/                   # 自定义布局算法
│   │   └── grid_custom_layout_algorithm.cpp/h
│   │       # 使用场景: layoutOptions双回调设置
│   │       # 行为: 完全自定义, 带滚动
│   │
│   ├── irregular/                      # 不规则布局算法
│   │   ├── grid_irregular_filler.cpp/h      # 填充不规则网格
│   │   ├── grid_irregular_layout_algorithm.cpp/h
│   │   ├── grid_layout_range_solver.cpp/h   # 求解布局范围
│   │   └── grid_layout_utils.cpp/h          # 布局工具
│   │
│   ├── grid_scroll/                    # 可滚动布局算法
│   │   ├── grid_scroll_layout_algorithm.cpp/h       # 标准可滚动
│   │   └── grid_scroll_with_options_layout_algorithm.cpp/h  # 带选项
│   │
│   ├── grid_layout_base_algorithm.cpp/h # 布局算法基类
│   └── grid_item_layout_algorithm.cpp/h  # GridItem 布局算法
│
├── Data Structures (数据结构)
│   ├── grid_layout_info.cpp/h          # 核心布局数据结构
│   ├── grid_layout_property.cpp/h      # 布局属性
│   └── grid_layout_options.h           # 布局配置选项
│
├── GridItem (子组件)
│   ├── grid_item_pattern.cpp/h         # GridItem 核心逻辑
│   ├── grid_item_model_ng.cpp/h        # GridItem 模型
│   ├── grid_item_model_static.cpp/h    # GridItem 静态模型
│   ├── grid_item_layout_property.cpp/h # GridItem 布局属性
│   ├── grid_item_layout_algorithm.cpp/h
│   └── grid_item_event_hub.cpp/h       # GridItem 事件处理
│
├── Functional Modules (功能模块)
│   ├── grid_event_hub.cpp/h            # 事件处理
│   ├── grid_focus.cpp/h                # 焦点管理
│   ├── grid_accessibility_property.cpp/h # 无障碍支持
│   ├── grid_content_modifier.cpp/h     # 内容修饰器
│   └── grid_paint_method.cpp/h         # 绘制/渲染
│
└── Utilities (工具类)
    ├── grid_utils.cpp/h                # 工具函数
    ├── grid_constants.h                # 常量定义
    └── grid_item_theme.h               # 主题配置
```

### 测试目录

```
test/unittest/core/pattern/grid/
├── GridTestNg (测试基类)
│   └── grid_test_ng.cpp/h              # 测试基类
│
├── 通用测试
│   ├── grid_attr_test_ng.cpp           # 属性测试
│   ├── grid_common_test_ng.cpp         # 通用测试
│   ├── grid_layout_test_ng.cpp         # 布局测试
│   ├── grid_pattern_test_ng.cpp        # Pattern 测试
│   ├── grid_scroller_test_ng.cpp       # 滚动测试
│   ├── grid_focus_test_ng.cpp          # 焦点测试
│   ├── grid_event_test_ng.cpp          # 事件测试
│   ├── grid_accessibility_test_ng.cpp  # 无障碍测试
│   ├── grid_cache_layout_test_ng.cpp   # 缓存布局测试
│   ├── grid_static_test_ng.cpp         # 静态布局测试
│   ├── grid_sync_load_test_ng.cpp      # 同步加载测试
│   ├── grid_option_layout_test_ng.cpp  # 布局选项测试
│   └── selectable_item_test.cpp        # 可选择项目测试
│
├── custom/                             # 自定义布局测试
│   ├── custom_layout_options.cpp/h
│   ├── grid_custom_algorithm_test_ng.cpp
│   ├── grid_custom_layout_test_ng.cpp
│   └── grid_custom_scroller_test_ng.cpp
│
└── irregular/                          # 不规则布局测试
    ├── grid_irregular_filler_test.cpp
    ├── grid_irregular_layout_test.cpp
    ├── grid_irregular_layout_testtwo.cpp
    ├── grid_layout_range_solver_test.cpp
    ├── irregular_matrices.h
    └── irregular_matrics.cpp
```

---

## 核心类继承关系

### Grid 核心类

```
                     ┌─────────────────────────┐
                     │   UI Pattern Base       │
                     └───────────┬─────────────┘
                                 │
                                 │ 继承
                                 ↓
         ┌───────────────────────────────────────────────┐
         │   SelectableContainerPattern                  │
         │   (可选择的容器模式基类)                        │
         └───────────────────────┬───────────────────────┘
                                 │
                                 │ 继承
                                 ↓
         ┌───────────────────────────────────────────────┐
         │   GridPattern                                 │
         │   - GridLayoutInfo info_                      │
         │   - GridFocus focusHandler_                   │
         │   - bool irregular_                           │
         │   - bool userDefined_                         │
         └───────────────────────────────────────────────┘
```

### 布局算法类

```
                     ┌─────────────────────────┐
                     │ LayoutAlgorithm         │
                     └───────────┬─────────────┘
                                 │
                                 │ 继承
                                 ↓
         ┌───────────────────────────────────────────────┐
         │   GridLayoutBaseAlgorithm                     │
         │   (布局算法基类)                               │
         └───────────┬───────────────────────────────────┘
                     │
         ┌───────────┼───────────┬───────────┬───────────┐
         │           │           │           │           │
         ↓           ↓           ↓           ↓           ↓
┌────────────────┐ ┌──────┐ ┌──────────┐ ┌──────────┐ ┌──────────────┐
│ GridAdaptive   │ │Grid  │ │GridScroll│ │GridCustom│ │GridIrregular │
│LayoutAlgorithm │ │Layout│ │Layout    │ │Layout    │ │Layout        │
│                │ │      │ │Algorithm │ │Algorithm │ │Algorithm     │
└────────────────┘ └──────┘ └──────────┘ └──────────┘ └──────────────┘
```

**源码验证**:
- `GridLayoutAlgorithm`: [grid_layout_algorithm.h:30](OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/grid/grid_layout/grid_layout_algorithm.h#L30)
- `GridAdaptiveLayoutAlgorithm`: [grid_adaptive_layout_algorithm.h:29](OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/grid/grid_adaptive/grid_adaptive_layout_algorithm.h#L29)
- `GridScrollLayoutAlgorithm`: [grid_scroll_layout_algorithm.h:27](OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/grid/grid_scroll/grid_scroll_layout_algorithm.h#L27)
- `GridCustomLayoutAlgorithm`: [grid_custom_layout_algorithm.h:25](OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/grid/grid_custom/grid_custom_layout_algorithm.h#L25)
- `GridIrregularLayoutAlgorithm`: [grid_irregular_layout_algorithm.h:32](OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/grid/irregular/grid_irregular_layout_algorithm.h#L32)
- `GridLayoutBaseAlgorithm`: [grid_layout_base_algorithm.h:28](OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/grid/grid_layout_base_algorithm.h#L28)

---

## Pattern层详解

### GridPattern 核心类

**源码位置**: `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/grid/grid_pattern.h`

**继承关系**: `GridPattern : public SelectableContainerPattern`

#### 核心职责

- 组件初始化和生命周期管理
- 布局算法选择与协调
- 滚动位置更新和事件处理
- 焦点管理和鼠标框选支持
- 拖拽编辑功能

#### 关键成员变量

```cpp
// 源码: grid_pattern.h:358-361
GridLayoutInfo info_;                  // 核心布局状态信息
GridFocus focusHandler_;               // 焦点处理器
bool irregular_ = false;              // 是否使用不规则布局
bool userDefined_ = false;            // 是否使用自定义布局
bool supportAnimation_ = false;       // 是否支持动画
bool multiSelectable_ = false;        // 是否支持鼠标框选（box select）
std::list<GridPreloadItem> preloadItemList_;  // 预加载项列表
```

#### 关键方法

| 方法名 | 说明 | 源码位置 |
|--------|------|----------|
| `CreateLayoutAlgorithm()` | 根据配置选择布局算法 | grid_pattern.cpp |
| `OnModifyDone()` | 属性修改完成回调 | grid_pattern.cpp |
| `UpdateCurrentOffset()` | 更新滚动偏移 | grid_pattern.cpp |
| `ScrollToIndex()` | 滚动到指定索引 | grid_pattern.cpp |
| `ScrollToEdge()` | 滚动到边界 | grid_pattern.cpp |
| `GetGridLayoutInfo()` | 获取布局信息 | grid_pattern.h:108 |
| `ResetGridLayoutInfo()` | 重置布局信息 | grid_pattern.h:119 |

### 布局算法选择逻辑

**源码**: `grid_pattern.cpp:CreateLayoutAlgorithm()`

Grid 根据以下逻辑选择布局算法：

```cpp
// 简化的选择逻辑
RefPtr<LayoutAlgorithm> GridPattern::CreateLayoutAlgorithm()
{
    auto layoutProperty = GetLayoutProperty<GridLayoutProperty>();

    bool setColumns = layoutProperty->HasColumnsTemplate();
    bool setRows = layoutProperty->HasRowsTemplate();

    // 1. 自适应布局: 无任何模板
    if (!setColumns && !setRows) {
        return MakeRefPtr<GridAdaptiveLayoutAlgorithm>();
    }

    // 2. 静态布局: 双模板都设置
    if (setColumns && setRows) {
        return MakeRefPtr<GridLayoutAlgorithm>();  // 无滚动
    }

    // 3. 自定义布局: layoutOptions 双回调
    if (userDefined_) {
        return MakeRefPtr<GridCustomLayoutAlgorithm>();
    }

    // 4. 不规则布局: 检测到跨行列项目
    if (UseIrregularLayout()) {
        return MakeRefPtr<GridIrregularLayoutAlgorithm>();
    }

    // 5. 可滚动布局: 仅设置一个模板
    return MakeRefPtr<GridScrollLayoutAlgorithm>();
}
```

**配置与算法映射表**:

| columnsTemplate | rowsTemplate | layoutOptions | 回调 | 不规则项目? | 算法 |
|:---------------:|:------------:|:-------------:|:----:|:----------:|:-----:|
| ❌ | ❌ | ❌ | - | - | `GridAdaptiveLayoutAlgorithm` |
| ✅ | ✅ | - | - | - | `GridLayoutAlgorithm` (无滚动) |
| ✅ | ❌ | ✅ | 双 | - | `GridCustomLayoutAlgorithm` |
| ❌ | ✅ | ✅ | 双 | - | `GridCustomLayoutAlgorithm` |
| ✅ | ❌ | ❌ 部分/无 | - | ✅ | `GridIrregularLayoutAlgorithm` |
| ❌ | ✅ | ❌ 部分/无 | - | ✅ | `GridIrregularLayoutAlgorithm` |
| ✅ | ❌ | ❌ 无 | - | ❌ | `GridScrollLayoutAlgorithm` |
| ❌ | ✅ | ❌ 无 | - | ❌ | `GridScrollLayoutAlgorithm` |
| ✅ | ❌ | ✅ 部分 | 非双 | ❌ | `GridScrollWithOptionsLayoutAlgorithm` |
| ❌ | ✅ | ✅ 部分 | 非双 | ❌ | `GridScrollWithOptionsLayoutAlgorithm` |

---

## Model层详解

### GridModelNG 类

**源码位置**: `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/grid/grid_model_ng.h`

**继承关系**: `GridModelNG : public GridModel`

#### 核心职责

- ArkTS API 到 C++ 实现的桥接
- FrameNode 创建和初始化
- 属性设置和更新
- 事件回调注册

#### 关键方法

| 方法名 | 说明 | 源码位置 |
|--------|------|----------|
| `Create()` | 创建 Grid FrameNode | grid_model_ng.cpp |
| `SetColumnsTemplate()` | 设置列模板 | grid_model_ng.cpp |
| `SetRowsTemplate()` | 设置行模板 | grid_model_ng.cpp |
| `SetColumnsGap()` | 设置列间距 | grid_model_ng.cpp |
| `SetRowsGap()` | 设置行间距 | grid_model_ng.cpp |
| `SetCachedCount()` | 设置缓存数量 | grid_model_ng.cpp |
| `SetLayoutOptions()` | 设置布局选项 | grid_model_ng.cpp |
| `SetEditable()` | 设置编辑模式 | grid_model_ng.cpp |
| `SetMultiSelectable()` | 设置多选模式 | grid_model_ng.cpp |
| `SetOnScrollIndex()` | 设置滚动索引事件 | grid_model_ng.cpp |
| `SetScrollToIndex()` | 滚动到指定索引 | grid_model_ng.cpp |

---

## 布局算法详解

Grid 支持**五种不同的布局算法**，根据 `columnsTemplate`、`rowsTemplate` 和 `layoutOptions` 自动选择。

### 1. GridAdaptiveLayoutAlgorithm - 自适应布局

**源码位置**: `grid_adaptive/grid_adaptive_layout_algorithm.cpp/h`

**使用场景**: 无 `columnsTemplate` 且无 `rowsTemplate`

**特性**:
- 项目自适应填充可用空间
- 根据容器大小自动计算行列数
- 无固定行列数限制

**支持的属性**:
- `columnsGap` - 列间距
- `rowsGap` - 行间距
- `layoutDirection` - 布局方向
- `maxCount` - 最大数量
- `minCount` - 最小数量
- `cellLength` - 单元格长度

### 2. GridLayoutAlgorithm - 静态布局

**源码位置**: `grid_layout/grid_layout_algorithm.cpp/h`

**使用场景**: `columnsTemplate` 和 `rowsTemplate` 都设置

**特性**:
- 静态网格，完全固定
- **不支持滚动**
- 适用于行列数已知的固定网格展示

### 3. GridCustomLayoutAlgorithm - 自定义布局

**源码位置**: `grid_custom/grid_custom_layout_algorithm.cpp/h`

**使用场景**: `layoutOptions` 中**同时提供** `getStartIndexByIndex` 和 `getStartIndexByOffset`

**特性**:
- 完全自定义布局
- 支持滚动
- 开发者控制布局逻辑

**关键方法**:
- `Measure()` - 测量所有项目大小
- `Layout()` - 定位元素
- `MeasureOnJump()` - 处理滚动到指定索引

### 4. GridIrregularLayoutAlgorithm - 不规则布局

**源码位置**: `irregular/grid_irregular_layout_algorithm.cpp/h`

**使用场景**: 检测到 `rowSpan > 1` 或 `columnSpan > 1` 的项目

**特性**:
- 处理跨行列项目
- 支持滚动
- 复杂的网格矩阵计算

**相关类**:
- `GridIrregularFiller` - 填充不规则网格
- `GridLayoutRangeSolver` - 计算可见范围
- `GridLayoutUtils` - 布局工具函数

### 5. GridScrollLayoutAlgorithm - 可滚动布局

**源码位置**: `grid_scroll/grid_scroll_layout_algorithm.cpp/h`

**使用场景**: 仅设置一个模板，无特殊布局需求

**变体**:
- **5A** `GridScrollLayoutAlgorithm` - 纯标准滚动
- **5B** `GridScrollWithOptionsLayoutAlgorithm` - 支持部分 `layoutOptions`

**特性**:
- 标准 Grid 布局
- 单方向滚动
- 虚拟滚动优化

---

## GridLayoutInfo数据结构

**源码位置**: `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/grid/grid_layout_info.h`

Grid 布局的核心数据结构，维护网格矩阵、行高、项目位置等状态。

### 核心数据成员

```cpp
// 源码: grid_layout_info.h:373-443
struct GridLayoutInfo {
    Axis axis_ = Axis::VERTICAL;                  // 主轴方向 (VERTICAL/HORIZONTAL)
    double currentOffset_ = 0.0;                  // 当前滚动偏移
    double prevOffset_ = 0.0;                     // 上一次偏移
    float currentHeight_ = 0.0f;                  // 当前高度
    float lastMainSize_ = 0.0f;                   // 上次主轴尺寸

    int32_t startIndex_ = 0;                      // 视口首项索引
    int32_t endIndex_ = -1;                       // 视口末项索引
    int32_t startMainLineIndex_ = 0;              // 视口首行索引
    int32_t endMainLineIndex_ = 0;                // 视口末行索引
    int32_t crossCount_ = 0;                      // 交叉轴数量 (列数或行数)
    int32_t childrenCount_ = 0;                   // 子组件总数

    // 网格矩阵: [行号, [列号, itemIdx]]
    std::map<int32_t, std::map<int32_t, int32_t>> gridMatrix_;

    // 行高映射: [行号, 行高]
    std::map<int32_t, float> lineHeightMap_;

    // 不规则项目位置: [索引, 最后单元格]
    std::map<int32_t, int32_t> irregularItemsPosition_;

    bool reachEnd_ = false;                       // 是否到达末尾
    bool reachStart_ = false;                     // 是否到达起始
    bool offsetEnd_ = false;                      // 内容底部是否真正到达
    bool hasBigItem_ = false;                     // 是否有跨多列项目
    bool hasMultiLineItem_ = false;               // 是否有跨多行项目

    ScrollAlign scrollAlign_ = ScrollAlign::AUTO;
};
```

### 关键方法

| 方法名 | 说明 | 源码位置 |
|--------|------|----------|
| `GetTotalHeightOfItemsInView()` | 获取视口内项目总高度 | grid_layout_info.h:69 |
| `GetContentHeight()` | 获取内容总高度 | grid_layout_info.h:286 |
| `FindInMatrix()` | 在网格矩阵中查找项目 | grid_layout_info.h:206 |
| `GetItemPos()` | 获取项目位置 | grid_layout_info.h:212 |
| `UpdateStartIndexByStartLine()` | 根据起始行更新起始索引 | grid_layout_info.h:79 |
| `SkipLinesAboveView()` | 跳过视口上方的行 | grid_layout_info.h:77 |

---

## GridItem子组件

### 核心文件

- **Pattern**: `grid_item_pattern.h/cpp` - GridItem 主逻辑
- **Model**: `grid_item_model_ng.h/cpp` - GridItem 模型
- **Property**: `grid_item_layout_property.h/cpp` - GridItem 布局属性
- **Algorithm**: `grid_item_layout_algorithm.h/cpp` - GridItem 布局算法
- **Event**: `grid_item_event_hub.h/cpp` - GridItem 事件处理

### GridItem 属性

```cpp
// 行列跨度 (用于不规则布局)
rowStart / rowEnd        // 行起始/结束
columnStart / columnEnd  // 列起始/结束

// 选择
selected                 // 是否选中
```

### 生效规则

| 场景 | 行列号设置 | 布局结果 |
|------|----------|----------|
| 双模板都设置 | 合理行列号 | 按指定行列号布局 |
| 双模板都设置 | rowStart/rowEnd 或 columnStart/columnEnd | 按一行一列布局 |
| 仅 columnsTemplate | 列号 | 按列数布局，位置冲突则换行 |
| 仅 rowsTemplate | 行号 | 按行数布局，位置冲突则换列 |
| 无模板 | 任意 | 行列号属性无效 |

### 性能优化建议

> **重要**: 当 Grid 中存在大量 GridItem 时，使用 columnStart/columnEnd/rowStart/rowEnd 设置跨行列会导致 scrollToIndex 性能问题。建议使用 layoutOptions 布局。

**推荐做法**:
```typescript
// 不推荐 - 性能差
GridItem() { }
.rowStart(0).rowEnd(1).columnStart(0).columnEnd(1)

// 推荐 - 性能好
layoutOptions: {
    irregularIndexes: [0],
    onGetIrregularSizeByIndex: (index) => {
        if (index === 0) return [2, 2];  // 2行2列
        return [1, 1];
    }
}
```

---

## 完整API清单

### ArkTS API

#### 创建 Grid

```typescript
Grid(scroller?: Scroller, options?: GridLayoutOptions)
```

#### 列行模板

| API | 类型 | 说明 |
|-----|------|------|
| `columnsTemplate(value: string)` | string | 列模板，如 `"1fr 1fr 2fr"` |
| `rowsTemplate(value: string)` | string | 行模板 |
| `columnsGap(value: Length)` | Length | 列间距 |
| `rowsGap(value: Length)` | Length | 行间距 |

#### 滚动控制

| API | 类型 | 说明 |
|-----|------|------|
| `cachedCount(value: number)` | number | 缓存行数 |
| `layoutDirection(value: FlexDirection)` | FlexDirection | 布局方向 |
| `enableScrollInteraction(value: boolean)` | boolean | 是否启用滚动交互（Legacy JS API） |

**注意**: `scrollEnabled` 是 C++ 内部实现属性名，在 ArkTS/JS API 中暴露为 `enableScrollInteraction`。

#### 布局选项

| API | 类型 | 说明 |
|-----|------|------|
| `maxCount(value: number)` | number | 最大数量（自适应模式） |
| `minCount(value: number)` | number | 最小数量（自适应模式） |
| `cellLength(value: number)` | number | 单元格长度（自适应模式） |
| `editMode(value: boolean)` | boolean | 编辑模式 |
| `alignItems(value: GridItemAlignment)` | GridItemAlignment | 项目对齐方式 |

#### 事件

| API | 说明 |
|-----|------|
| `onScrollToIndex(callback: (index: number) => void)` | 滚动到索引事件 |
| `onScrollFrameBegin(callback: (offset: number, state: ScrollState) => ScrollResult)` | 滚动帧开始事件 |
| `onScrollStart(callback: () => void)` | 滚动开始事件 |
| `onScrollStop(callback: () => void)` | 滚动停止事件 |
| `onScrollIndex(callback: (first: number, last: number) => void)` | 索引变化事件 |
| `onReachStart(callback: () => void)` | 到达起始事件 |
| `onReachEnd(callback: () => void)` | 到达末尾事件 |

#### 拖拽事件

| API | 说明 |
|-----|------|
| `onItemDragStart(callback: (info: ItemDragInfo, index: number) => void)` | 拖拽开始 |
| `onItemDragEnter(callback: (info: ItemDragInfo) => void)` | 拖拽进入 |
| `onItemDragMove(callback: (info: ItemDragInfo) => void)` | 拖拽移动 |
| `onItemDragLeave(callback: (info: ItemDragInfo) => void)` | 拖拽离开 |
| `onItemDrop(callback: (info: ItemDragInfo) => void)` | 拖拽放下 |

### C++ API

#### GridModelNG 方法

**源码**: `grid_model_ng.h:32-183`

```cpp
// 创建和初始化
void Create(const RefPtr<ScrollControllerBase>& positionController,
            const RefPtr<ScrollProxy>& scrollProxy) override;

// 列行模板设置
void SetColumnsTemplate(const std::string& value) override;
void SetRowsTemplate(const std::string& value) override;
void SetColumnsGap(const Dimension& value) override;
void SetRowsGap(const Dimension& value) override;

// 缓存和滚动
void SetCachedCount(int32_t value, bool show = false) override;
void SetScrollEnabled(bool scrollEnabled) override;

// 布局选项
void SetLayoutOptions(GridLayoutOptions options) override;
void SetMaxCount(int32_t value) override;
void SetMinCount(int32_t value) override;
void SetCellLength(int32_t value) override;

// 编辑和选择
void SetEditable(bool value) override;
void SetMultiSelectable(bool value) override;
void SetSupportAnimation(bool value) override;

// 对齐和方向
void SetLayoutDirection(FlexDirection value) override;
void SetAlignItems(GridItemAlignment itemAlign) override;

// 事件回调
void SetOnScrollToIndex(ScrollToIndexFunc&& value) override;
void SetOnScrollIndex(ScrollIndexFunc&& onScrollIndex) override;
void SetOnScrollStart(OnScrollStartEvent&& onScrollStart) override;
void SetOnScrollStop(OnScrollStopEvent&& onScrollStop) override;
void SetOnReachStart(OnReachEvent&& onReachStart) override;
void SetOnReachEnd(OnReachEvent&& onReachEnd) override;

// 拖拽事件
void SetOnItemDragStart(std::function<void(const ItemDragInfo&, int32_t)>&& value) override;
void SetOnItemDragEnter(ItemDragEnterFunc&& value) override;
void SetOnItemDragMove(ItemDragMoveFunc&& value) override;
void SetOnItemDragLeave(ItemDragLeaveFunc&& value) override;
void SetOnItemDrop(ItemDropFunc&& value) override;
```

---

## 事件系统

### GridEventHub

**源码位置**: `grid_event_hub.h/cpp`

处理 Grid 组件的各种事件。

#### 事件类型

| 事件 | 说明 | 注册方法 |
|------|------|----------|
| 滚动事件 | 滚动时触发 | `SetOnScroll()` |
| 滚动开始 | 滚动开始时触发 | `SetOnScrollStart()` |
| 滚动停止 | 滚动停止时触发 | `SetOnScrollStop()` |
| 滚动索引 | 视口索引变化 | `SetOnScrollIndex()` |
| 到达起始 | 到达顶部时触发 | `SetOnReachStart()` |
| 到达末尾 | 到达底部时触发 | `SetOnReachEnd()` |
| 拖拽事件 | 拖拽相关事件 | `SetOnItemDragXXX()` |

---

## 滚动控制

### Scroller 接口

```typescript
// 创建 Scroller
scroller: Scroller = new Scroller();

// 主要方法
scroller.scrollTo(options: ScrollOptions);           // 滑动到指定位置
scroller.scrollEdge(value: Edge);                   // 滚动到边缘
scroller.scrollToIndex(value: number,
                     smooth?: boolean,
                     align?: ScrollAlign,
                     options?: ScrollToIndexOptions);  // 滚动到指定索引
scroller.scrollBy(dx: Length, dy: Length);        // 滑动指定距离
scroller.currentOffset(): OffsetResult;             // 获取当前偏移
scroller.isAtEnd(): boolean;                        // 是否到达底部
scroller.isAtStart(): boolean;                      // 是否到达顶部
scroller.getItemRect(index: number): RectResult;  // 获取子组件位置
```

### ScrollAlign 枚举

```typescript
enum ScrollAlign {
    START = 0,   // 首部对齐
    CENTER = 1,  // 居中对齐
    END = 2,     // 尾部对齐
    AUTO = 3     // 自动对齐
}
```

---

## 使用示例

### 1. 自适应布局

```typescript
Grid() {
  ForEach(this.items, (item) => {
    GridItem() {
      Text(item)
    }
  })
}
// → GridAdaptiveLayoutAlgorithm
```

### 2. 静态网格

```typescript
Grid() {
}
.columnsTemplate("1fr 1fr 1fr")
.rowsTemplate("1fr 1fr")
// → GridLayoutAlgorithm (无滚动)
```

### 3. 标准滚动

```typescript
Grid(this.scroller) {
  ForEach(this.items, (item) => {
    GridItem() {
      Text(item)
    }
  })
}
.columnsTemplate("1fr 1fr 1fr")
.cachedCount(2)
// → GridScrollLayoutAlgorithm
```

### 4. 不规则项目

```typescript
layoutOptions: {
  irregularIndexes: [0],
  onGetIrregularSizeByIndex: (index) => {
    if (index === 0) return { rows: 2, columns: 2 };
    return { rows: 1, columns: 1 };
  }
}

Grid(this.scroller, this.layoutOptions) {
  ForEach(this.items, (item) => {
    GridItem() {
      Text(item)
    }
  })
}
.columnsTemplate("1fr 1fr")
// → GridIrregularLayoutAlgorithm
```

### 5. 完全自定义

```typescript
layoutOptions: {
  onGetStartIndexByIndex: (index) => {
    return { startIndex: 0, startLine: 0, startOffset: 0, totalOffset: 0 };
  },
  onGetStartIndexByOffset: (offset) => {
    return { startIndex: 0, startLine: 0, startOffset: 0, totalOffset: 0 };
  }
}

Grid(this.scroller, this.layoutOptions) {
}
.columnsTemplate("1fr 1fr")
// → GridCustomLayoutAlgorithm
```

---

## 性能优化

### 虚拟滚动

- Grid 使用虚拟滚动，仅渲染可见 + 缓存的项目
- 通过 `cachedCount` 控制缓存数量
- 默认值: 1 (API 11+ 改为屏幕可见行数，最大16)

### 行跳跃 (Line Skipping)

当滚动偏移较大时，算法可以跳过中间项目的测量，直接跳转到估计位置：

```cpp
bool TrySkipping(float mainSize) {
    float delta = std::abs(info_.currentOffset_ - info_.prevOffset_);
    if (enableSkip_ && delta > mainSize) {
        info_.jumpIndex_ = Negative(delta) ? SkipLinesForward() : SkipLinesBackward();
        Jump(mainSize);
        return true;
    }
    return false;
}
```

### 预加载

- `preloadItemList_` 存储需要预加载的项目
- 通过 `PreloadItems()` 和 `SyncPreloadItems()` 实现

### 推荐用法

1. **使用 LazyForEach**: 配合 Grid 使用虚拟滚动
2. **设置合理的 cachedCount**: 平衡内存和滚动流畅度
3. **优先使用 layoutOptions**: 替代 rowStart/rowEnd 设置跨行列项目
4. **避免大量 GridItem 跨行列**: 会导致 scrollToIndex 性能问题
5. **开启行跳跃**: 大幅度滚动时启用 `enableSkip` 优化

---

## 调试指南

### DumpInfo

```cpp
// 源码: grid_pattern.cpp
void GridPattern::DumpAdvanceInfo()
{
    // 输出 Grid 详细信息
    // - 布局状态
    // - 网格矩阵
    // - 滚动位置
    // - 焦点信息
}
```

### 常见问题排查

| 症状 | 可能位置 |
|------|----------|
| 项目位置错误 | 布局算法的 `Layout()` 方法 |
| 大小计算错误 | `Measure()` 方法或 `grid_layout_info` |
| 滚动问题 | `MeasureOnOffset()` 或滚动偏移计算 |
| 项目缺失 | `GridIrregularFiller` 或范围计算 |
| 焦点问题 | `grid_focus.cpp` |

---

## 测试覆盖

### 测试基类

**文件**: `test/unittest/core/pattern/grid/grid_test_ng.h`

```cpp
class GridTestNg : public ScrollableUtilsTestNG {
    // Grid 创建
    GridModelNG CreateGrid();
    GridModelNG CreateRepeatGrid(int32_t itemNumber, ...);

    // GridItem 创建
    GridItemModelNG CreateGridItem(float width, float height, ...);
    void CreateGridItems(int32_t itemNumber = 10, ...);

    // 滚动操作
    void UpdateCurrentOffset(float offset, int32_t source);

    // 成员
    RefPtr<GridPattern> pattern_;
    RefPtr<GridEventHub> eventHub_;
    RefPtr<GridLayoutProperty> layoutProperty_;
};
```

### 运行测试

```bash
# 进入测试目录
cd test/unittest

# 运行所有 Grid 测试
python run.py -t grid_test_ng

# 运行特定测试
python run.py -t grid_pattern_test_ng
python run.py -t grid_custom_layout_test_ng
python run.py -t grid_irregular_layout_test
```

---

## 常见问题

### Q1: 为什么 scrollToIndex 性能差？

**原因**: 使用 `rowStart/rowEnd/columnStart/columnEnd` 设置跨行列时，Grid 需要遍历所有项目来定位目标索引。

**解决方案**: 使用 `layoutOptions` 替代：
```typescript
layoutOptions: {
    irregularIndexes: [0, 5, 10],
    onGetIrregularSizeByIndex: (index) => { /* ... */ }
}
```

### Q2: 如何选择合适的布局算法？

参考以下决策表：

| 需求 | 推荐配置 |
|------|----------|
| 自适应填充 | 不设置 template |
| 固定网格无滚动 | 同时设置 columnsTemplate 和 rowsTemplate |
| 单向滚动 | 仅设置一个 template |
| 跨行列项目 | 使用 layoutOptions.irregularIndexes |
| 完全自定义 | 使用 layoutOptions 双回调 |

### Q3: cachedCount 如何设置？

- **API 10-**: 默认值 1，需要手动设置
- **API 11+**: 自动设置为屏幕可见行数（最大16）
- 建议：保持默认值，除非有特殊需求

### Q4: 如何优化大量数据的滚动性能？

1. 使用 `LazyForEach` 而非 `ForEach`
2. 合理设置 `cachedCount`
3. 使用 `layoutOptions` 而非行列跨度属性
4. 开启行跳跃优化
5. 避免频繁的属性更新

---

## 相关资源

### 源码位置

| 模块 | 路径 |
|------|------|
| Grid Pattern | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/grid/` |
| Grid Model | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/grid/grid_model_ng.cpp` |
| 布局算法 | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/grid/*/` |
| 测试 | `OpenHarmony/foundation/arkui/ace_engine/test/unittest/core/pattern/grid/` |

### API 文档

| 文档 | 路径 |
|------|------|
| Grid API | `OpenHarmony/interface/sdk-js/api/arkui/component/grid.static.d.ets` |
| GridItem API | `OpenHarmony/interface/sdk-js/api/arkui/component/gridItem.static.d.ets` |
| Grid Modifier | `OpenHarmony/interface/sdk-js/api/arkui/GridModifier.d.ts` |

### 相关知识库

- [Flex_Knowledge_Base.md](../flex/Flex_Knowledge_Base.md) - 弹性布局组件
- [Scroll_Knowledge_Base.md](../scroll/Scroll_Knowledge_Base.md) - 滚动容器组件
- [LazyGrid_Knowledge_Base.md](../lazy_layout/LazyGrid_Knowledge_Base.md) - 懒加载网格组件
