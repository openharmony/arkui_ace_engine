# Grid 组件文档

本文档记录 Grid 组件的核心架构、实现细节和使用指南。

## 目录结构

```
grid/
├── Core Implementation (核心实现)
│   ├── grid_pattern.cpp/h              # Grid 主逻辑和生命周期管理
│   ├── grid_model_ng.cpp/h             # Grid 数据模型 (ArkTS API 层)
│   ├── grid_model_static.cpp/h         # 静态 Grid 模型
│   └── grid_view.h                     # Grid 视图接口
│
├── Layout Algorithms (布局算法 - 5种类型)
│   │
│   ├── 1. grid_adaptive/               # 自适应布局算法
│   │   └── grid_adaptive_layout_algorithm.cpp/h
│   │       # 使用场景: 无 columnsTemplate 且无 rowsTemplate
│   │       # 行为: 项目自适应填充可用空间
│   │
│   ├── 2. grid_layout/                 # 静态布局算法
│   │   └── grid_layout_algorithm.cpp/h
│   │       # 使用场景: columnsTemplate 和 rowsTemplate 都设置
│   │       # 行为: 固定网格大小, 无滚动
│   │
│   ├── 3. grid_custom/                # 自定义布局算法
│   │   └── grid_custom_layout_algorithm.cpp/h
│   │       # 使用场景: userDefined_ 标志为 true
│   │       # 行为: 支持 layoutOptions, 带滚动
│   │       # 关键方法: Measure(), Layout(), MeasureOnJump()
│   │
│   ├── 4. irregular/                   # 不规则布局算法
│   │   ├── grid_irregular_filler.cpp/h     # 填充不规则网格
│   │   ├── grid_irregular_layout_algorithm.cpp/h
│   │   │   # 使用场景: UseIrregularLayout() 返回 true
│   │   │   # 行为: 处理跨多行/多列的项目
│   │   ├── grid_layout_range_solver.cpp/h  # 求解布局范围
│   │   └── grid_layout_utils.cpp/h         # 布局工具
│   │
│   ├── 5. grid_scroll/                 # 可滚动布局算法
│   │   ├── grid_scroll_layout_algorithm.cpp/h (5A)
│   │   │   # 使用场景: 设置一个模板, 无 layoutOptions
│   │   │   # 行为: 纯标准可滚动布局
│   │   └── grid_scroll_with_options_layout_algorithm.cpp/h (5B)
│   │       # 使用场景: 设置一个模板, 部分 layoutOptions
│   │       # 行为: 标准 + 支持 layoutOptions 回调
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
│   └── grid_item_layout_property.cpp/h # GridItem 布局属性
│
├── Functional Modules (功能模块)
│   ├── grid_event_hub.cpp/h            # 事件处理
│   ├── grid_focus.cpp/h                # 焦点管理
│   ├── grid_accessibility_property.cpp/h # 无障碍支持
│   └── grid_paint_method.cpp/h         # 绘制/渲染
│
└── Utilities (工具类)
    ├── grid_utils.cpp/h                # 工具函数
    ├── grid_constants.h                # 常量定义
    └── grid_item_theme.h               # 主题配置
```

## 核心数据流

```
用户 API 调用 (ArkTS/JS)
    ↓
grid_model_ng (接收 API 调用)
    ↓
grid_pattern (核心逻辑管理)
    ↓
grid_layout_algorithm (布局计算)
    ↓
grid_layout_info (存储布局状态)
    ↓
渲染和事件处理
```

## 核心类及其职责

### GridPattern
**文件**: [grid_pattern.h](grid_pattern.h)

Grid 组件的主 Pattern 类, 管理组件生命周期、状态和行为。

**核心职责**:
- 组件初始化和生命周期管理
- 布局协调和事件路由
- **创建适当的布局算法** ([CreateLayoutAlgorithm()](grid_pattern.cpp#L45))

**关键成员**:
```cpp
GridLayoutInfo info_;        // 布局状态信息
bool irregular_ = false;     // 是否使用不规则布局
bool userDefined_ = false;   // 是否使用自定义布局
GridFocus focusHandler_;     // 焦点处理器
std::list<GridPreloadItem> preloadItemList_;  // 预加载项列表
```

**关键方法**:
- `CreateLayoutAlgorithm()` - 根据配置选择布局算法
- `ScrollToIndex()` - 滚动到指定索引
- `UpdateCurrentOffset()` - 更新滚动偏移
- `OnModifyDone()` - 属性修改完成回调

### GridLayoutInfo
**文件**: [grid_layout_info.h](grid_layout_info.h)

Grid 布局的核心数据结构, 维护网格矩阵、行高、项目位置等状态。

**核心数据成员**:
```cpp
Axis axis_;                                    // 主轴方向 (VERTICAL/HORIZONTAL)
double currentOffset_;                         // 当前滚动偏移
int32_t startIndex_;                           // 视口首项索引
int32_t endIndex_;                             // 视口末项索引
int32_t startMainLineIndex_;                   // 视口首行索引
int32_t endMainLineIndex_;                     // 视口末行索引
int32_t crossCount_;                           // 交叉轴数量 (列数或行数)

std::map<int32_t, std::map<int32_t, int32_t>> gridMatrix_;  // [行, [列, itemIdx]]
std::map<int32_t, float> lineHeightMap_;       // [行号, 行高]
std::map<int32_t, int32_t> irregularItemsPosition_;  // 不规则项目位置
```

**关键方法**:
- `GetTotalHeightOfItemsInView()` - 获取视口内项目总高度
- `GetContentHeight()` - 获取内容总高度
- `FindInMatrix()` - 在网格矩阵中查找项目
- `GetItemPos()` - 获取项目位置
- `UpdateStartIndexByStartLine()` - 根据起始行更新起始索引

## 布局算法详解

### 算法选择逻辑

Grid 支持 **五种不同的布局算法**, 根据 `columnsTemplate`、`rowsTemplate` 和 `layoutOptions` 自动选择:

| 算法 | 文件位置 | 使用场景 | 特性 |
|------|----------|----------|------|
| **1. GridAdaptiveLayoutAlgorithm** | `grid_adaptive/` | 无模板设置 | 自适应布局, 项目填充可用空间 |
| **2. GridLayoutAlgorithm** | `grid_layout/` | 双模板都设置 | **静态布局**, 无滚动, 固定大小 |
| **3. GridCustomLayoutAlgorithm** | `grid_custom/` | layoutOptions 双回调 | 完全自定义, 支持滚动 |
| **4. GridIrregularLayoutAlgorithm** | `irregular/` | 检测到跨行列项目 | 处理跨行列项目, 支持滚动 |
| **5A. GridScrollLayoutAlgorithm** | `grid_scroll/` | 单模板, 无 layoutOptions | **标准可滚动** |
| **5B. GridScrollWithOptionsLayoutAlgorithm** | `grid_scroll/` | 单模板, 部分 layoutOptions | 可滚动 + 部分自定义选项 |

### 算法选择代码流程

来自 [GridPattern::CreateLayoutAlgorithm()](grid_pattern.cpp#L45):

```cpp
// 1. 自适应: 无任何模板
if (!setColumns && !setRows) {
    return GridAdaptiveLayoutAlgorithm();
}

// 2. 静态: 双模板都设置
if (setColumns && setRows) {
    return GridLayoutAlgorithm();  // 无滚动
}

// 3-5. 可滚动布局 (仅设置一个模板)
if (userDefined_) {
    return GridCustomLayoutAlgorithm();  // layoutOptions 双回调
}
if (UseIrregularLayout()) {
    return GridIrregularLayoutAlgorithm();  // 检测到不规则项目
}
return GridScrollLayoutAlgorithm();  // 标准滚动
```

### 标志检测逻辑

来自 [GridLayoutProperty::UpdateIrregularFlag()](grid_layout_property.cpp#137):

```cpp
// userDefined_ 设置为 TRUE 当:
if (layoutOptions.getStartIndexByIndex && layoutOptions.getStartIndexByOffset) {
    pattern->SetUserDefined(true);  // 双回调都提供
}

// irregular 设置为 TRUE 当:
bool vertical = IsVertical();
for (int32_t idx : layoutOptions.irregularIndexes) {
    auto size = layoutOptions.getSizeByIndex(idx);
    // 横向滚动: 检查 columns > 1
    // 纵向滚动: 检查 rows > 1
    if ((!vertical && size.columns > 1) || (vertical && size.rows > 1)) {
        pattern->SetIrregular(true);
    }
}
```

### 配置与算法映射表

| columnsTemplate | rowsTemplate | layoutOptions | 回调 | 不规则项目? | 算法 |
|:---------------:|:------------:|:-------------:|:----:|:----------:|:-----:|
| ❌ | ❌ | ❌ | - | - | `GridAdaptiveLayoutAlgorithm` |
| ✅ | ✅ | - | - | - | `GridLayoutAlgorithm` (无滚动) |
| ✅ | ❌ | ✅ | 双 | - | `GridCustomLayoutAlgorithm` |
| ❌ | ✅ | ✅ | 双 | - | `GridCustomLayoutAlgorithm` |
| ✅ | ❌ | ❌ 部分/无 | - | ✅ | `GridIrregularLayoutAlgorithm` |
| ❌ | ✅ | ❌ 部分/无 | - | ✅ | `GridIrregularLayoutAlgorithm` |
| ✅ | ❌ | ❌ 无 | - | ❌ | `GridScrollLayoutAlgorithm` (5A) |
| ❌ | ✅ | ❌ 无 | - | ❌ | `GridScrollLayoutAlgorithm` (5A) |
| ✅ | ❌ | ✅ 部分 | 非双 | ❌ | `GridScrollWithOptionsLayoutAlgorithm` (5B) |
| ❌ | ✅ | ✅ 部分 | 非双 | ❌ | `GridScrollWithOptionsLayoutAlgorithm` (5B) |

### 各算法详解

#### 1. GridAdaptiveLayoutAlgorithm
**特点**: 项目自适应填充可用空间, 无固定行列数
**支持的属性**: `columnsGap`, `rowsGap`, `layoutDirection`, `maxCount`, `minCount`, `cellLength`

#### 2. GridLayoutAlgorithm
**特点**: 静态网格, 完全固定, **不支持滚动**
**适用**: 行列数已知的固定网格展示

#### 3. GridCustomLayoutAlgorithm
**特点**: 完全自定义布局, 支持滚动
**触发条件**: `layoutOptions` 中 **同时提供** `getStartIndexByIndex` 和 `getStartIndexByOffset`

关键方法:
- `Measure()` - 测量所有项目大小
- `Layout()` - 定位元素
- `MeasureOnJump()` - 处理滚动到指定索引

#### 4. GridIrregularLayoutAlgorithm
**特点**: 处理跨行列项目, 支持滚动
**触发条件**: 检测到 `rowSpan > 1` 或 `columnSpan > 1` 的项目

相关类:
- `GridIrregularFiller` - 填充不规则网格
- `GridLayoutRangeSolver` - 计算可见范围

#### 5. GridScrollLayoutAlgorithm / GridScrollWithOptionsLayoutAlgorithm
**特点**: 标准 Grid 布局, 支持单方向滚动
- **5A** (`GridScrollLayoutAlgorithm`): 纯标准滚动
- **5B** (`GridScrollWithOptionsLayoutAlgorithm`): 支持部分 `layoutOptions`

## GridLayoutOptions (自定义布局)

**文件**: [grid_layout_options.h](grid_layout_options.h)

`layoutOptions` 支持完全自定义的网格布局。

### 数据结构

```cpp
// 项目大小 (行列数)
struct GridItemSize {
    int32_t rows = 1;
    int32_t columns = 1;
};

// 项目精确位置
struct GridItemRect {
    int32_t rowStart = -1;
    int32_t columnStart = -1;
    int32_t rowSpan = 1;
    int32_t columnSpan = 1;
};

// 滚动位置信息
struct GridStartLineInfo {
    int32_t startIndex = 0;
    int32_t startLine = 0;
    double startOffset = 0.0;
    double totalOffset = 0.0;
};
```

### 回调函数

```cpp
struct GridLayoutOptions {
    GridItemSize regularSize;                        // 常规项目大小
    std::set<int32_t> irregularIndexes;              // 不规则项目索引集合

    // 回调函数
    GetSizeByIndex getSizeByIndex;                   // 按索引获取大小
    GetRectByIndex getRectByIndex;                   // 按索引获取位置
    GetStartIndexByOffset getStartIndexByOffset;     // 偏移 → 位置
    GetStartIndexByIndex getStartIndexByIndex;       // 索引 → 位置
};
```

### 回调要求

要触发 `GridCustomLayoutAlgorithm` (userDefined_ = true), **必须同时提供**:
- ✅ `getStartIndexByIndex` - 必需, 用于 scrollToIndex
- ✅ `getStartIndexByOffset` - 必需, 用于滚动位置计算

可选:
- `getSizeByIndex` - 不规则项目大小 (irregularIndexes 非空时需要)
- `getRectByIndex` - 精确定位 (getSizeByIndex 的替代方案)

### 使用场景

- 瀑布流布局
- 日历应用 (可变大小事件)
- 图片画廊 (特色项目)
- 仪表盘 (不同尺寸小组件)

## GridItem (子组件)

### 核心文件

- [grid_item_pattern.h](grid_item_pattern.h) - GridItem 主逻辑
- [grid_item_model_ng.h](grid_item_model_ng.h) - GridItem 模型
- [grid_item_layout_property.h](grid_item_layout_property.h) - GridItem 布局属性

### GridItem 属性

```cpp
// 行列跨度 (用于不规则布局)
rowStart / rowEnd        // 行起始/结束
columnStart / columnEnd  // 列起始/结束

// 选择
selected                 // 是否选中
```

## 关键常量

**文件**: [grid_constants.h](grid_constants.h)

定义 Grid 组件使用的常量值。

## 布局属性 (GridLayoutProperty)

**文件**: [grid_layout_property.h](grid_layout_property.h)

### 核心属性

| 属性 | 类型 | 说明 |
|------|------|------|
| `columnsTemplate` | string | 列模板, 如 `"1fr 1fr 2fr"` |
| `rowsTemplate` | string | 行模板 |
| `columnsGap` | Dimension | 列间距 |
| `rowsGap` | Dimension | 行间距 |
| `cachedCount` | int32_t | 缓存行数 |
| `layoutOptions` | GridLayoutOptions | 自定义布局选项 |
| `scrollEnabled` | bool | 是否启用滚动 |
| `alignItems` | GridItemAlignment | 项目对齐方式 |

### 关键方法

```cpp
bool IsVertical() const;              // 是否为纵向网格
bool IsConfiguredScrollable() const;  // 是否可滚动
bool IsReverse() const;               // 是否反向 (RTL)
```

## 事件处理 (GridEventHub)

**文件**: [grid_event_hub.h](grid_event_hub.h)

处理 Grid 组件的各种事件:
- 滚动事件
- 项目点击事件
- 滚动到边界事件

## 焦点管理 (GridFocus)

**文件**: [grid_focus.h](grid_focus.h)

管理 Grid 内的焦点导航:
- 焦点移动
- 焦点包裹模式
- 键盘导航

## 常见维护任务

### 1. 添加新的 Grid 属性

1. 在 `grid_layout_property.h` 中添加属性定义
2. 在 `grid_model_ng.cpp` 中解析属性
3. 在 `grid_pattern.cpp` 或布局算法中应用属性
4. 在 `test/unittest/core/pattern/grid/` 中添加测试

### 2. 修改布局行为

根据场景选择正确的算法:

| 场景 | 修改的算法 | 文件位置 |
|------|-----------|----------|
| 自适应网格 (无模板) | GridAdaptiveLayoutAlgorithm | `grid_adaptive/` |
| 静态网格 (双模板) | GridLayoutAlgorithm | `grid_layout/` |
| 自定义布局 | GridCustomLayoutAlgorithm | `grid_custom/` |
| 不规则项目 (跨行列) | GridIrregularLayoutAlgorithm | `irregular/` |
| 单向滚动 | GridScrollLayoutAlgorithm | `grid_scroll/` |

**常用布局算法文件**:
- `grid_custom_layout_algorithm.cpp` - 自定义模板布局
- `grid_irregular_layout_algorithm.cpp` - 不规则/跨行列项目
- `grid_layout_info.cpp` - 状态管理 (所有算法共享)

**关键方法**:
- `Measure()` - 计算所有项目的大小
- `Layout()` - 定位网格中的元素
- `MeasureOnJump()` - 处理滚动到索引功能
- `MeasureOnOffset()` - 处理滚动偏移变化

### 3. 调试布局问题

| 症状 | 可能位置 |
|------|----------|
| 项目位置错误 | 布局算法的 `Layout()` 方法 |
| 大小计算错误 | `Measure()` 方法或 `grid_layout_info` |
| 滚动问题 | `MeasureOnOffset()` 或滚动偏移计算 |
| 项目缺失 | `GridIrregularFiller` 或范围计算 |
| 焦点问题 | `grid_focus.cpp` |

## 使用示例

### 1. 自适应布局
```typescript
Grid() {
  // 项目填充可用空间
}
// → GridAdaptiveLayoutAlgorithm
```

### 2A. 静态网格
```typescript
Grid() {
}
.columnsTemplate("1fr 1fr 1fr")
.rowsTemplate("1fr 1fr")
// → GridLayoutAlgorithm (无滚动)
```

### 2B. 静态网格 + 布局选项
```typescript
layoutOptions: {
    onGetGetRectByIndex:(index) => { /* ... */} //获取节点大小位置
}
Grid(undefined, this.layoutOptions) {
}
.columnsTemplate("1fr 1fr 1fr")
.rowsTemplate("1fr 1fr")
// → GridLayoutAlgorithm (无滚动)
```

### 3A. 标准滚动
```typescript
Grid() {
}
.columnsTemplate("1fr 1fr 1fr")
// → GridScrollLayoutAlgorithm
```

### 3B. 滚动 + 部分选项
```typescript
layoutOptions: {
    irregularIndexes:[0] //不规则节点
}
Grid(this.scroller, this.layoutOptions) {
}
.columnsTemplate("1fr 1fr 1fr")
// → GridScrollWithOptionsLayoutAlgorithm
```

### 4. 不规则项目
```typescript
layoutOptions: {
    irregularIndexes:[0], //不规则节点
    onGetIrregularSizeByIndex(index) => { /* ... */}
}
Grid() {
}
.columnsTemplate("1fr 1fr")
// → GridIrregularLayoutAlgorithm
```

### 5. 完全自定义
```typescript
layoutOptions: {
    onGetStartIndexByIndex: (index) => { /* ... */ },
    onGetStartIndexByOffset: (offset) => { /* ... */ }
}
Grid() {
}
.columnsTemplate("1fr 1fr")
// → GridCustomLayoutAlgorithm
```

## 测试 Grid 组件

测试位置: `test/unittest/core/pattern/grid/`

### 测试目录结构

```
test/unittest/core/pattern/grid/
├── BUILD.gn                           # 测试构建配置
├── grid_test_ng.cpp/h                 # 测试基类
│
├── 通用测试 (根目录)
│   ├── grid_attr_test_ng.cpp          # 属性测试
│   ├── grid_common_test_ng.cpp        # 通用测试
│   ├── grid_layout_test_ng.cpp        # 布局测试
│   ├── grid_pattern_test_ng.cpp       # Pattern 测试
│   ├── grid_scroller_test_ng.cpp      # 滚动测试
│   ├── grid_focus_test_ng.cpp         # 焦点测试
│   ├── grid_event_test_ng.cpp         # 事件测试
│   ├── grid_accessibility_test_ng.cpp # 无障碍测试
│   ├── grid_cache_layout_test_ng.cpp  # 缓存布局测试
│   ├── grid_static_test_ng.cpp        # 静态布局测试
│   ├── grid_sync_load_test_ng.cpp     # 同步加载测试
│   ├── grid_option_layout_test_ng.cpp # 布局选项测试
│   └── selectable_item_test.cpp       # 可选择项目测试
│
├── custom/                            # 自定义布局测试
│   ├── custom_layout_options.cpp/h    # 自定义布局选项工具
│   ├── grid_custom_algorithm_test_ng.cpp
│   ├── grid_custom_layout_test_ng.cpp
│   ├── grid_custom_layout_algorithm_test.cpp
│   └── grid_custom_scroller_test_ng.cpp
│
└── irregular/                         # 不规则布局测试
    ├── grid_irregular_filler_test.cpp      # GridIrregularFiller 测试
    ├── grid_irregular_layout_test.cpp      # GridIrregularLayout 测试
    ├── grid_irregular_layout_testtwo.cpp   # GridIrregularLayout 测试2
    ├── grid_layout_range_solver_test.cpp   # GridLayoutRangeSolver 测试
    ├── irregular_matrices.h                # 测试用矩阵数据
    └── irregular_matrics.cpp
```

### 测试基类 (GridTestNg)

**文件**: `test/unittest/core/pattern/grid/grid_test_ng.h`

`GridTestNg` 是所有 Grid 测试的基类, 提供测试辅助方法:

```cpp
class GridTestNg : public ScrollableUtilsTestNG {
    // Grid 创建
    GridModelNG CreateGrid();
    GridModelNG CreateRepeatGrid(int32_t itemNumber, ...);

    // GridItem 创建
    GridItemModelNG CreateGridItem(float width, float height, ...);
    void CreateGridItems(int32_t itemNumber = 10, ...);
    void CreateFixedItems(int32_t itemNumber, ...);
    void CreateBigItem(int32_t rowStart, int32_t rowEnd, ...);

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

# 运行不规则布局测试
python run.py -t grid_test_ng

# 运行常规Grid测试
python run.py -t grid_test_regular

# 运行自定义布局测试
python run.py -t grid_test_custom

# 运行不规则布局测试
python run.py -t grid_test_ng

# 运行arkts1.2测试
python run.py -t grid_test_static
```

### 测试覆盖范围

| 测试文件 | 测试内容 |
|----------|----------|
| `grid_attr_test_ng.cpp` | 属性设置与更新 |
| `grid_layout_test_ng.cpp` | 布局计算与定位 |
| `grid_scroll_layout_test_ng.cpp` | 可滚动布局 |
| `grid_pattern_test_ng.cpp` | Pattern 核心逻辑 |
| `grid_scroller_test_ng.cpp` | 滚动行为 |
| `grid_focus_test_ng.cpp` | 焦点导航 |
| `grid_event_test_ng.cpp` | 事件触发 |
| `grid_cache_layout_test_ng.cpp` | 缓存机制 |
| `grid_static_test_ng.cpp` | 静态布局 (arkts1.2) |
| `grid_option_layout_test_ng.cpp` | layoutOptions |
| `grid_custom_layout_test_ng.cpp` | 自定义布局 |
| `grid_irregular_layout_test.cpp` | 不规则布局 |
| `layout_info_test.cpp` | GridLayoutInfo 数据结构 |
| `grid_irregular_filler_test.cpp` | GridIrregularFiller |
| `grid_layout_range_solver_test.cpp` | GridLayoutRangeSolver |

## 相关文件

Grid 组件开发时可能需要参考:
- `frameworks/core/components_ng/pattern/scrollable/` - 可滚动基类
- `frameworks/core/layout/` - 通用布局算法
- `frameworks/core/common/` - 共享工具

## 设计模式

### 策略模式
Grid 使用策略模式根据配置选择不同的布局算法。`CreateLayoutAlgorithm()` 是策略选择器。

### 模板方法模式
`GridLayoutBaseAlgorithm` 定义了布局算法的骨架, 子类实现具体步骤。

### 观察者模式
Grid 通过 `GridEventHub` 处理和分发事件。

## JS 桥接层详解

### JS 到 C++ 的映射

**文件**: [js_grid.cpp](../../../bridge/declarative_frontend/jsview/js_grid.cpp)

Grid 组件通过 JS 桥接层将 ArkTS API 映射到 C++ 实现。

#### Grid 创建流程

```typescript
// ArkTS API
Grid(scroller, layoutOptions) {
  // GridItems...
}
.columnsTemplate("1fr 1fr 1fr")
.cachedCount(2)
```

```cpp
// C++ 实现 (js_grid.cpp)
void JSGrid::Create(const JSCallbackInfo& info) {
    // 1. 创建 Scroller 控制器
    JSScroller* jsScroller = ...;
    positionController = GridModel::GetInstance()->CreatePositionController();
    jsScroller->SetController(positionController);

    // 2. 创建 Grid 组件
    GridModel::GetInstance()->Create(positionController, scrollBarProxy);

    // 3. 解析并设置 layoutOptions
    SetGridLayoutOptions(info);
}
```

#### layoutOptions 解析

```cpp
void SetGridLayoutOptions(const JSCallbackInfo& info) {
    GridLayoutOptions option;
    auto obj = JSRef<JSObject>::Cast(info[1]);

    // 解析 regularSize
    ParseGridItemSize(obj->GetProperty("regularSize"), option.regularSize);

    // 解析 irregularIndexes
    auto indexes = obj->GetProperty("irregularIndexes");
    // 添加到 option.irregularIndexes

    // 解析回调函数
    ParseGetGridItemSize(info, obj, option);      // onGetIrregularSizeByIndex
    ParseGetGridItemRect(info, obj, option);      // onGetRectByIndex
    ParseGetStartIndexByOffset(info, obj, option); // onGetStartIndexByOffset
    ParseGetStartIndexByIndex(info, obj, option);  // onGetStartIndexByIndex

    GridModel::GetInstance()->SetLayoutOptions(option);
}
```

#### 回调函数封装

```cpp
// onGetIrregularSizeByIndex 回调
auto onGetIrregularSizeByIndex = [execCtx, func](int32_t index) {
    JAVASCRIPT_EXECUTION_SCOPE(execCtx);
    JSRef<JSVal> itemIndex = JSRef<JSVal>::Make(ToJSValue(index));
    auto result = func->ExecuteJS(1, &itemIndex);
    GridItemSize gridItemSize;
    ParseGridItemSize(result, gridItemSize);
    return gridItemSize;
};

// onGetStartIndexByOffset 回调
auto onGetStartIndexByOffset = [execCtx, func](float offset) {
    JAVASCRIPT_EXECUTION_SCOPE(execCtx);
    JSRef<JSVal> jsOffset = JSRef<JSVal>::Make(ToJSValue(Dimension(offset).ConvertToVp()));
    auto result = func->ExecuteJS(1, &jsOffset);

    GridStartLineInfo startLineInfo {
        .startIndex_ = ...,
        .startLine_ = ...,
        .startOffset_ = ...,
        .totalOffset_ = ...
    };
    return startLineInfo;
};
```

## Scroller 滚动控制

### Scroller 接口

**API 文档**: [ts-container-scroll.md](../../../../../docs/zh-cn/application-dev/reference/apis-arkui/arkui-ts/ts-container-scroll.md)

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
    START = 0,   // 首部对齐 - 指定item首部与滚动容器首部对齐
    CENTER = 1,  // 居中对齐 - 指定item主轴方向居中对齐于滚动容器
    END = 2,     // 尾部对齐 - 指定item尾部与滚动容器尾部对齐
    AUTO = 3     // 自动对齐 - 若item完全在显示区则不调整，否则按最短距离原则
}
```

### ScrollOptions 对象

```typescript
interface ScrollOptions {
    xOffset?: number | string;              // 水平滚动总偏移量
    yOffset?: number | string;              // 垂直滚动总偏移量
    animation?: ScrollAnimationOptions | boolean;  // 动画配置
    canOverScroll?: boolean;               // 是否可以越界停留
}

interface ScrollAnimationOptions {
    duration?: number;                     // 滚动时长，默认1000ms
    curve?: Curve | ICurve;                // 滚动曲线，默认Curve.Ease
    canOverScroll?: boolean;               // 滚动到边界后是否转换为回弹动画
}
```

## 滚动事件详解

### 通用滚动事件

**API 文档**: [ts-container-scrollable-common.md](../../../../../docs/zh-cn/application-dev/reference/apis-arkui/arkui-ts/ts-container-scrollable-common.md)

```typescript
// 滚动生命周期事件
.onReachStart(() => void)        // 到达起始位置时触发
.onReachEnd(() => void)          // 到达末尾位置时触发
.onScrollStart(() => void)       // 滚动开始时触发
.onScrollStop(() => void)        // 滚动停止时触发

// 滚动索引变化事件
.onScrollIndex((first: number, last: number) => void)
// first: 视口中第一个项目索引
// last: 视口中最后一个项目索引

// 滚动偏移事件 (已废弃，使用 onDidScroll 替代)
.onScroll((scrollOffset: number, scrollState: ScrollState) => void)
```

### 滚动帧事件

```typescript
// 滚动前回调 - 可修改滚动量
.onWillScroll((scrollOffset: number, scrollState: ScrollState, scrollSource: ScrollSource) => void | ScrollResult)
// scrollOffset: 即将滚动的偏移量
// scrollState: 当前滚动状态
// scrollSource: 滚动操作来源 (用户手势/程序调用)
// 返回值: 可选，指定实际滚动偏移

// 滚动时回调 - 只读
.onDidScroll((scrollOffset: number, scrollState: ScrollState) => void)
// scrollOffset: 当前帧滚动偏移量
// scrollState: 当前滚动状态
```

### 滚动帧开始事件

```typescript
.onScrollFrameBegin((offset: number, state: ScrollState) => ScrollResult)
// offset: 即将发生的滚动量
// state: 当前滚动状态
// 返回: { offsetRemain: number } - 实际滚动量
```

## 可滚动组件通用属性

**API 文档**: [ts-container-scrollable-common.md](../../../../../docs/zh-cn/application-dev/reference/apis-arkui/arkui-ts/ts-container-scrollable-common.md)

### 滚动条属性

```typescript
.scrollBar(barState: BarState)
// BarState.Auto - 自动显示
// BarState.On - 常驻显示
// BarState.Off - 不显示
// BarState.Auto - 默认值 (List/Grid/Scroll)

.scrollBarWidth(value: number | string)
// 默认值: 4
// 单位: vp

.scrollBarColor(value: Color | number | string | Resource)
// 默认值: '#182431' (40%不透明度)
```

### 边缘效果

```typescript
.edgeEffect(edgeEffect: EdgeEffect, options?: EdgeEffectOptions)
// EdgeEffect.Spring - 弹簧效果
// EdgeEffect.Fade - 阴影效果
// EdgeEffect.None - 无效果

// EdgeEffectOptions
interface EdgeEffectOptions {
    alwaysEnabled?: boolean;  // 内容小于组件时是否开启滑动效果
    effectEdge?: EffectEdge;    // 边缘生效方向 (START/END/BOTH)
}
```

### 嵌套滚动

```typescript
.nestedScroll(value: NestedScrollOptions)
interface NestedScrollOptions {
    scrollForward: NestedScrollMode;   // 向末尾端滚动时的嵌套滚动选项
    scrollBackward: NestedScrollMode;  // 向起始端滚动时的嵌套滚动选项
}

// NestedScrollMode
// NestedScrollMode.SELF_ONLY - 仅自身滚动
// NestedScrollMode.SELF_FIRST - 自身优先，父组件次之
// NestedScrollMode.PARENT_FIRST - 父组件优先，自身次之
// NestedScrollMode.PARALLEL - 自身和父组件同时滚动
```

### 通用滚动属性

```typescript
.enableScrollInteraction(value: boolean)     // 是否支持滚动手势
.friction(value: number | Resource)         // 摼擦系数 (0, +∞)
.flingSpeedLimit(speedLimit: number)        // Fling初始速度限制
.fadingEdge(enabled: boolean, options?)    // 边缘渐隐效果
.clipContent(clip: ContentClipMode)       // 内容裁剪区域
.contentStartOffset(offset: number | Resource)  // 内容起始偏移
.contentEndOffset(offset: number | Resource)    // 内容末尾偏移
```

## GridItem 行列跨度规则

### 行列号属性

**API 文档**: [ts-container-griditem.md](../../../../../docs/zh-cn/application-dev/reference/apis-arkui/arkui-ts/ts-container-griditem.md)

```typescript
GridItem() {
  Text("跨行列项目")
}
.rowStart(0)      // 起始行号
.rowEnd(1)         // 终止行号 (占据2行: 0-1)
.columnStart(0)   // 起始列号
.columnEnd(1)      // 终止列号 (占据2列: 0-1)
```

### 生效规则

| 场景 | 行列号设置 | 布局结果 |
|------|----------|----------|
| 双模板都设置 | 合理行列号 | 按指定行列号布局 |
| 双模板都设置 | rowStart/rowEnd 或 columnStart/columnEnd | 按一行一列布局 |
| 仅 columnsTemplate | 列号 | 按列数布局，位置冲突则换行 |
| 仅 rowsTemplate | 行号 | 按行数布局，位置冲突则换列 |
| 无模板 | 任意 | 行列号属性无效 |

### 异常处理

| 属性设置情况 | 异常类型 | 修正后布局规则 |
|:-------------|:---------|:-------------|
| 仅设置 columnsTemplate | 任意行列异常 | 按一行一列布局 |
| 仅设置 rowsTemplate | 任意行列异常 | 按一行一列布局 |
| 双模板都设置 | rowStart < rowEnd | 行跨度 = min(rowEnd-rowStart+1, 总行数) |
| 双模板都设置 | rowStart > rowEnd | 按一行一列布局 |
| 双模板都设置 | columnStart < columnEnd | 列跨度 = min(columnEnd-columnStart+1, 总列数) |
| 双模板都设置 | columnStart > columnEnd | 按一行一列布局 |

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

## 性能优化

### 虚拟滚动
- Grid 使用虚拟滚动, 仅渲染可见 + 缓存的项目
- 通过 `cachedCount` 控制缓存数量
- 默认值: 1 (API 11+ 改为屏幕可见行数，最大16)

### 行跳跃 (Line Skipping)
当滚动偏移较大时, 算法可以跳过中间项目的测量, 直接跳转到估计位置:

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
6. **使用 contentStartOffset/contentEndOffset**: 设置内容边距，避免首尾项目贴边

## API 映射关系总结

### ArkTS API → C++ 实现

```typescript
// ArkTS
Grid(this.scroller, this.layoutOptions) {
  ForEach(this.items, (item) => {
    GridItem() { Text(item) }
  })
}
.columnsTemplate("1fr 1fr 1fr")
.cachedCount(2)
.onScrollIndex((first, last) => {})
```

```cpp
// C++ 实现路径
Grid() → JSGrid::Create()
    ↓
GridModelNG::Create()
    ↓
GridPattern::OnAttachToFrameNode() [初始化]
    ↓
GridPattern::CreateLayoutAlgorithm() [选择算法]
    ↓
GridLayoutAlgorithm::Measure/Layout() [布局计算]
    ↓
GridLayoutInfo::UpdateStartIndexByStartLine() [更新索引]
```

### 事件流

```typescript
// ArkTS
.onScrollIndex((first: number, last: number) => void)
```

```cpp
// C++ 回调链
onScrollIndex
    → grid_event_hub.cpp
        → GridEventHub::SetOnScrollIndex()
            → JSGrid::JsOnScrollIndex()
                → 执行 JavaScript 回调
```

## 相关文件索引

### 核心实现
- [grid_pattern.cpp](grid_pattern.cpp) - Grid 主逻辑
- [grid_layout_property.cpp](grid_layout_property.cpp) - 布局属性
- [grid_layout_info.cpp](grid_layout_info.cpp) - 布局数据结构

### 布局算法
- [grid_scroll/grid_scroll_layout_algorithm.cpp](grid_scroll/grid_scroll_layout_algorithm.cpp)
- [irregular/grid_irregular_layout_algorithm.cpp](irregular/grid_irregular_layout_algorithm.cpp)
- [grid_custom/grid_custom_layout_algorithm.cpp](grid_custom/grid_custom_layout_algorithm.cpp)

### JS 桥接
- [js_grid.cpp](../../../bridge/declarative_frontend/jsview/js_grid.cpp) - JS 到 C++ 桥接
- [grid.d.ts](../../../../../interface/sdk-js/api/@internal/component/ets/grid.d.ts) - TypeScript 接口定义

### 文档
- [Grid API 文档](../../../../../docs/zh-cn/application-dev/reference/apis-arkui/arkui-ts/ts-container-grid.md)
- [GridItem API 文档](../../../../../docs/zh-cn/application-dev/reference/apis-arkui/arkui-ts/ts-container-griditem.md)
- [可滚动组件通用属性](../../../../../docs/zh-cn/application-dev/reference/apis-arkui/arkui-ts/ts-container-scrollable-common.md)
- [Scroll & Scroller](../../../../../docs/zh-cn/application-dev/reference/apis-arkui/arkui-ts/ts-container-scroll.md)