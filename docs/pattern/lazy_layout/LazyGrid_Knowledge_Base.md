# ArkUI LazyGrid 组件完整知识库

> **文档版本**：v1.0
> **更新时间**：2026-02-03
> **源码版本**：OpenHarmony ace_engine (master 分支)
> **作者**：基于 CLAUDE.md 规范自动生成

---

##  目录

1. [概述](#概述)
2. [目录结构](#目录结构)
3. [核心类继承关系](#核心类继承关系)
4. [Pattern层详解](#pattern层详解)
5. [Model层详解](#model层详解)
6. [Property系统](#property系统)
7. [LayoutAlgorithm详解](#layoutalgorithm详解)
8. [LayoutInfo详解](#layoutinfo详解)
9. [完整API清单](#完整api清单)
10. [关键实现细节](#关键实现细节)
11. [使用示例](#使用示例)
12. [调试指南](#调试指南)
13. [常见问题](#常见问题)
14. [附录](#附录)

---

## 概述

### 组件定位

**LazyGrid** 组件是 OpenHarmony ArkUI 框架中的**懒加载网格布局组件**，提供高性能的网格布局功能，支持按需加载子项、预测性渲染、位置缓存等优化特性。LazyGrid 通常用于展示大量数据的网格场景（如相册、商品列表等），通过懒加载机制显著提升性能和内存效率。

### 技术栈

- **前端**：ArkTS/TypeScript
- **桥接层**：LazyVGridLayoutModel + LazyVGridLayoutModifier
- **核心层**：NG Pattern 架构 (LazyGridLayoutPattern)
- **渲染层**：Rosen + Skia
- **依赖组件**：GridItem、WaterFlow

### 代码规模

- 总文件数：11 个文件
- 核心代码：约 2,500+ 行 C++ 代码
- 涉及 4 个架构层次（Pattern/Algorithm/Info/Property）

### 功能特性

- 支持懒加载（仅渲染可见区域+预测区域）
- 支持多列网格布局（ColumnsTemplate）
- 支持行列间距自定义（RowGap/ColumnGap）
- 支持预测性渲染（利用空闲时间预渲染）
- 支持位置缓存机制（快速滚动定位）
- 支持正向/反向布局方向
- 支持焦点管理（ScopeFocus）
- 必须作为 WaterFlow 的子组件使用

---

## 目录结构

### 源码文件组织

```
components_ng/pattern/lazy_layout/grid_layout/
├── lazy_grid_layout_pattern.h              # Pattern 层头文件（主模式类）
├── lazy_grid_layout_pattern.cpp            # Pattern 层实现（业务逻辑）
├── lazy_grid_layout_model.h                # Model 层接口定义
├── lazy_grid_layout_model.cpp              # Model 层实现
├── lazy_grid_layout_model_static.h         # 静态 Model 定义
├── lazy_grid_layout_model_static.cpp       # 静态 Model 实现
├── lazy_grid_layout_property.h             # 布局属性定义
├── lazy_grid_layout_info.h                 # 布局信息状态管理
├── lazy_grid_layout_info.cpp               # 布局信息实现
├── lazy_grid_layout_algorithm.h            # 布局算法定义
└── lazy_grid_layout_algorithm.cpp          # 布局算法实现
```

### 文件职责说明

| 文件名 | 职责描述 |
|--------|----------|
| `lazy_grid_layout_pattern.h/cpp` | 核心业务逻辑，处理懒加载生命周期、预测任务调度、父容器验证 |
| `lazy_grid_layout_algorithm.h/cpp` | 布局算法实现，包括懒加载测量、位置计算、缓存管理 |
| `lazy_grid_layout_info.h/cpp` | 布局状态管理，位置映射、缓存数据、预测截止时间 |
| `lazy_grid_layout_property.h` | 布局属性定义（RowGap、ColumnGap、ColumnsTemplate） |
| `lazy_grid_layout_model.h` | Model 层接口，连接前端与后端 |
| `lazy_grid_layout_model_static.h/cpp` | 静态 Model 实现，创建 FrameNode |

---

## 核心类继承关系

### 类图

```
                    ┌─────────────────────┐
                    │     Pattern         │
                    │    (Base Class)     │
                    └──────────┬──────────┘
                               │
                               │ 继承
                               ▼
              ┌──────────────────────────────┐
              │    LazyLayoutPattern         │
              │  (懒加载布局基类)             │
              └──────────────────┬───────────┘
                                 │
                                 │ 继承
                                 ▼
              ┌──────────────────────────────┐
              │  LazyGridLayoutPattern       │
              │  (懒加载网格布局模式类)        │
              └──────────────────┬───────────┘
                                 │
                                 │ 创建
                                 ├─────────────────────────────┐
                                 │                             │
                                 ▼                             ▼
                    ┌──────────────────┐        ┌─────────────────────┐
                    │LazyGridLayoutInfo│        │LazyGridLayoutProperty│
                    └──────────────────┘        └─────────────────────┘

                                 │
                                 │ 创建
                                 ▼
                    ┌──────────────────────┐
                    │LazyGridLayoutAlgorithm│
                    └──────────────────────┘
```

### 核心类说明

#### LazyGridLayoutPattern

**继承关系**：
- 父类：`LazyLayoutPattern` → `Pattern`
- 子类：无

**职责**：
- 管理懒加载生命周期
- 调度预测性渲染任务
- 验证父容器层级
- 提供焦点管理接口

**核心方法**：
- `OnAttachToMainTree()` - 附加到主树时验证父容器
- `OnDirtyLayoutWrapperSwap()` - 布局交换时触发预测
- `PostIdleTask()` - 投递预测任务
- `ProcessIdleTask()` - 处理预测任务
- `GetFocusPattern()` - 获取焦点模式
- `GetScopeFocusAlgorithm()` - 获取范围焦点算法

---

## Pattern层详解

### LazyGridLayoutPattern

**文件位置**：`frameworks/core/components_ng/pattern/lazy_layout/grid_layout/lazy_grid_layout_pattern.h:29`

#### 生命周期方法

| 方法名 | 调用时机 | 功能说明 |
|--------|----------|----------|
| `OnAttachToMainTree()` | 附加到主树时 | 验证父容器、设置懒加载标志 |
| `OnDirtyLayoutWrapperSwap()` | 布局包装器交换时 | 更新项总数、触发预测任务 |

#### 核心状态

**文件位置**：`lazy_grid_layout_pattern.h:77-80`

```cpp
Axis axis_ = Axis::VERTICAL;                 // 布局方向（垂直/水平）
int32_t itemTotalCount_ = 0;                 // 子项总数
RefPtr<LazyGridLayoutInfo> layoutInfo_;      // 布局信息容器
```

#### 核心业务逻辑

##### 1. 父容器验证

**实现位置**：`lazy_grid_layout_pattern.cpp:88-111`

**功能描述**：验证 LazyGrid 是否在正确的父容器下使用

**关键代码片段**：

```cpp
void LazyGridLayoutPattern::OnAttachToMainTree()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->SetNeedLazyLayout(true);
    auto parent = host->GetParent();
    while (parent) {
        auto frameNode = AceType::DynamicCast<FrameNode>(parent);
        if (!frameNode) {
            parent = parent->GetParent();
            continue;
        }
        // 允许的父容器类型
        if (parent->GetTag() == V2::COMMON_VIEW_ETS_TAG ||
            parent->GetTag() == V2::NODE_CONTAINER_ETS_TAG ||
            parent->GetTag() == "BuilderProxyNode" ||
            parent->GetTag() == V2::FLOW_ITEM_ETS_TAG) {
            frameNode->SetNeedLazyLayout(true);
            parent = parent->GetParent();
            continue;
        }
        // 必须是 WaterFlow 组件
        if (parent->GetTag() != V2::WATERFLOW_ETS_TAG) {
            LOGF_ABORT("LazyGridLayout cannot be used under the %{public}s",
                       parent->GetTag().c_str());
        }
        return;
    }
}
```

**设计要点**：
- LazyGrid 必须作为 WaterFlow 的子组件使用
- 支持通过特定容器节点（BuilderProxyNode、FlowItem 等）间接嵌套
- 设置 `needLazyLayout` 标志以优化布局性能

##### 2. 预测任务调度

**实现位置**：`lazy_grid_layout_pattern.cpp:57-86`

**功能描述**：利用空闲时间进行预测性渲染

**关键代码**：

```cpp
void LazyGridLayoutPattern::PostIdleTask()
{
    auto context = GetContext();
    CHECK_NULL_VOID(context);
    context->AddPredictTask([weak = WeakClaim(this)]
        (int64_t deadline, bool canUseLongPredictTask) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->ProcessIdleTask(deadline);
        }
    );
}

void LazyGridLayoutPattern::ProcessIdleTask(int64_t deadline)
{
    if (!layoutInfo_->NeedPredict()) {
        return;
    }
    if (GetSysTimestamp() > deadline) {
        PostIdleTask();
        return;
    }
    ACE_SCOPED_TRACE("LazyGridIdleTask");
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetLayoutProperty()->UpdatePropertyChangeFlag(PROPERTY_UPDATE_MEASURE_SELF);
    layoutInfo_->deadline_ = deadline;
    FrameNode::ProcessOffscreenNode(GetHost(), true);
    layoutInfo_->deadline_.reset();
}
```

**实现细节**：
- 通过 `AddPredictTask` 注册预测任务到上下文
- 传递 `deadline` 参数限制预测工作时间
- 使用 `GetSysTimestamp()` 检查是否超时
- 设置 `deadline_` 到 layoutInfo 供算法层使用
- 使用 `ACE_SCOPED_TRACE` 进行性能追踪

##### 3. 布局交换处理

**实现位置**：`lazy_grid_layout_pattern.cpp:41-55`

**功能描述**：布局交换后更新状态并触发预测

**关键代码**：

```cpp
bool LazyGridLayoutPattern::OnDirtyLayoutWrapperSwap(
    const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (config.skipMeasure && config.skipLayout) {
        return false;
    }
    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(
        dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto layoutAlgorithm = DynamicCast<LazyGridLayoutAlgorithm>(
        layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithm, false);
    itemTotalCount_ = layoutAlgorithm->GetTotalItemCount();
    if (layoutInfo_->NeedPredict()) {
        PostIdleTask();
    }
    return false;
}
```

**关键逻辑**：
- 跳过空白布局交换（skipMeasure && skipLayout）
- 从布局算法中获取最新的项总数
- 检查是否需要预测，如果需要则投递预测任务

##### 4. 焦点管理

**实现位置**：`lazy_grid_layout_pattern.cpp:30-39`

**功能描述**：提供范围焦点支持

**关键代码**：

```cpp
FocusPattern LazyGridLayoutPattern::GetFocusPattern() const
{
    return { FocusType::SCOPE, true };
}

ScopeFocusAlgorithm LazyGridLayoutPattern::GetScopeFocusAlgorithm()
{
    return ScopeFocusAlgorithm(ScopeFocusDirection::UNIVERSAL, false, true,
        ScopeType::OTHERS);
}
```

**特性**：
- 焦点类型：`SCOPE`（范围焦点）
- 焦点方向：`UNIVERSAL`（通用方向）
- 支持范围类型的 `OTHERS`

---

## Model层详解

### LazyGridLayoutModel

**文件位置**：`frameworks/core/components_ng/pattern/lazy_layout/grid_layout/lazy_grid_layout_model.h:29`

#### Model 接口定义

LazyGridLayoutModel 是连接前端 ArkTS 代码和后端 Pattern 的桥接层，负责：
- 解析 ArkTS 属性设置
- 创建和配置 FrameNode
- 设置布局属性

#### 主要方法

| 方法名 | 功能 |
|--------|------|
| `Create()` | 创建 LazyGrid 组件节点 |
| `SetRowGap()` | 设置行间距 |
| `SetColumnGap()` | 设置列间距 |
| `SetRowGap(FrameNode*, const Dimension&)` | 为指定节点设置行间距 |
| `SetColumnGap(FrameNode*, const Dimension&)` | 为指定节点设置列间距 |

### LazyVGridLayoutModel

**文件位置**：`frameworks/core/components_ng/pattern/lazy_layout/grid_layout/lazy_grid_layout_model.h:38`

#### 垂直网格专用接口

```cpp
class ACE_EXPORT LazyVGridLayoutModel : public LazyGridLayoutModel {
public:
    static void SetColumnsTemplate(const std::string& value);
    static void SetColumnsTemplate(FrameNode* frameNode, const std::string& value);
};
```

**功能**：
- 继承 LazyGridLayoutModel 的所有方法
- 新增 `SetColumnsTemplate` 方法用于设置列模板
- 支持动态和静态两种调用方式

---

## Property系统

### LayoutProperty

**类名**：`LazyGridLayoutProperty`

**文件位置**：`frameworks/core/components_ng/pattern/lazy_layout/grid_layout/lazy_grid_layout_property.h:27`

#### 属性列表

| 属性名 | 类型 | 默认值 | 说明 |
|--------|------|--------|------|
| `RowGap` | Dimension | 0.0_vp | 行间距（网格行之间的间距） |
| `ColumnGap` | Dimension | 0.0_vp | 列间距（网格列之间的间距） |
| `ColumnsTemplate` | std::string | "" | 列模板（如 "1fr 1fr 1fr" 表示三等分） |

#### 属性定义

**文件位置**：`lazy_grid_layout_property.h:66-68`

```cpp
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(RowGap, Dimension, PROPERTY_UPDATE_MEASURE);
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ColumnGap, Dimension, PROPERTY_UPDATE_MEASURE);
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ColumnsTemplate, std::string, PROPERTY_UPDATE_MEASURE);
```

#### 属性克隆

**文件位置**：`lazy_grid_layout_property.h:35-43`

```cpp
RefPtr<LayoutProperty> Clone() const override
{
    auto value = MakeRefPtr<LazyGridLayoutProperty>();
    value->LayoutProperty::UpdateLayoutProperty(DynamicCast<LayoutProperty>(this));
    value->propRowGap_ = CloneRowGap();
    value->propColumnGap_ = CloneColumnGap();
    value->propColumnsTemplate_ = CloneColumnsTemplate();
    return value;
}
```

#### 属性序列化

**文件位置**：`lazy_grid_layout_property.h:53-64`

```cpp
void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override
{
    LayoutProperty::ToJsonValue(json, filter);
    if (filter.IsFastFilter()) {
        return;
    }
    json->PutExtAttr("rowsGap", propRowGap_.value_or(Dimension(0, DimensionUnit::VP)).ToString().c_str(), filter);
    json->PutExtAttr("ColumnsGap",
        propColumnGap_.value_or(Dimension(0, DimensionUnit::VP)).ToString().c_str(), filter);
    json->PutExtAttr("columnsTemplate", propColumnsTemplate_.value_or("").c_str(), filter);
}
```

#### 属性修改函数

这些属性通过 ArkTS 前端代码设置，通过 Modifier 模式更新到 LayoutProperty：

```typescript
// ArkTS 示例
LazyVGridLayout()
  .columnsTemplate("1fr 1fr 1fr")  // 设置三列等宽
  .rowGap(10)                       // 设置行间距 10vp
  .columnGap(10)                    // 设置列间距 10vp
```

---

## LayoutAlgorithm详解

### LazyGridLayoutAlgorithm

**文件位置**：`frameworks/core/components_ng/pattern/lazy_layout/grid_layout/lazy_grid_layout_algorithm.h:29`

#### 算法类型

LazyGrid 组件使用自定义布局算法，主要职责：

1. **懒加载测量**：仅测量可见区域+预测区域内的子项
2. **位置计算**：计算每个网格项的位置
3. **缓存管理**：维护位置缓存以支持快速滚动
4. **预测布局**：利用空闲时间预渲染即将可见的子项

#### 核心状态

**文件位置**：`lazy_grid_layout_algorithm.h:98-129`

```cpp
// 基础配置
Axis axis_ = Axis::VERTICAL;              // 布局方向
TextDirection layoutDirection_ = TextDirection::LTR;  // 文本方向
int32_t totalItemCount_ = 0;              // 子项总数
float spaceWidth_ = 0.0f;                 // 间距宽度
float laneGutter_ = 0.0f;                 // 列间距
float crossSize_ = 0.0f;                  // 交叉轴尺寸
std::vector<double> crossLens_;           // 每列宽度
std::vector<double> crossPos_;            // 每列起始位置
float totalMainSize_ = 0.0f;              // 总主轴尺寸
float realMainSize_ = 0.0f;               // 实际主轴尺寸
bool needAllLayout_ = true;               // 是否需要全量布局
int32_t lanes_ = 1;                       // 列数

// 视口信息
float viewStart_ = 0.0f;                  // 视口起始位置
float viewEndPos_ = 0.0f;                 // 视口结束位置
float referencePos_ = 0.0f;               // 参考位置
bool forwardLayout_ = true;               // 是否正向布局

// 缓存信息
float cacheSize_ = 0.5f;                  // 缓存大小（屏幕比例）
float layoutedStart_ = 0.0f;              // 已布局起始位置
float layoutedEnd_ = 0.0f;                // 已布局结束位置
int32_t layoutedStartIndex_ = -1;         // 已布局起始索引
int32_t layoutedEndIndex_ = -1;           // 已布局结束索引
float cacheStartPos_ = 0.0f;              // 缓存起始位置
float cacheEndPos_ = 0.0f;                // 缓存结束位置
int32_t cachedStartIndex_ = -1;           // 缓存起始索引
int32_t cachedEndIndex_ = -1;             // 缓存结束索引

RefPtr<LazyGridLayoutInfo> layoutInfo_;   // 布局信息
```

#### 懒加载机制

##### 两阶段布局

**文件位置**：`lazy_grid_layout_algorithm.h:57-64`

```cpp
void SetRefencesPos(float startPos, float endPos, float referencePos, bool forwardLayout)
{
    viewStart_ = startPos;
    viewEndPos_ = endPos;
    referencePos_ = referencePos;
    forwardLayout_ = forwardLayout;
    needAllLayout_ = false;  // 启用懒加载模式
}
```

**设计原理**：
- `viewStart_` / `viewEndPos_`：定义当前可视区域
- `referencePos_`：滚动参考位置（用于快速滚动定位）
- `forwardLayout_`：布局方向标志
- `needAllLayout_`：false 表示懒加载模式，true 表示全量布局

##### 懒加载测量策略

**实现位置**：`lazy_grid_layout_algorithm.cpp:Measure()`

```cpp
void LazyGridLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    // ... 前置处理 ...

    if (layoutInfo_->deadline_) {
        // 预测模式：有时间限制
        return;
    } else if (totalItemCount_ == 0) {
        // 空数据
        layoutInfo_->SetTotalItemCount(0);
        totalMainSize_ = 0.0f;
    } else if (needAllLayout_) {
        // 全量布局：测量所有子项
        MeasureGridItemAll(layoutWrapper);
    } else {
        // 懒加载：仅测量可见+预测区域
        MeasureGridItemLazy(layoutWrapper);
    }
}
```

**策略选择**：
1. **预测模式**：`deadline_` 存在时，在时间限制内进行预测测量
2. **空数据模式**：`totalItemCount_` 为 0 时，清空布局
3. **全量布局模式**：`needAllLayout_` 为 true 时，测量所有子项
4. **懒加载模式**：默认模式，仅测量可见区域和预测区域

#### 预测/缓存机制

##### 正向预测布局

**实现位置**：`lazy_grid_layout_algorithm.cpp:PredictLayoutForward()`

```cpp
void LazyGridLayoutAlgorithm::PredictLayoutForward(
    LayoutWrapper* layoutWrapper, float crossSize, const OffsetF& paddingOffset)
{
    int32_t currIndex = layoutInfo_->layoutedEndIndex_;
    auto deadline = layoutInfo_->deadline_.value();
    while (currIndex < totalItemCount_ - 1 && LessNotEqual(layoutedEnd, layoutInfo_->cacheEndPos_)) {
        // 检查是否超时
        if (GetSysTimestamp() > deadline) {
            break;  // 时间用完，停止预测
        }
        // 测量并定位下一项
        // ...
    }
}
```

**关键特性**：
- 从已布局结束索引继续向前预测
- 检查系统时间戳，超时即停止
- 预测范围：`cacheEndPos_`（通常为视口大小 + 缓冲区）

##### 反向预测布局

**实现位置**：`lazy_grid_layout_algorithm.cpp:PredictLayoutBackward()`

```cpp
void LazyGridLayoutAlgorithm::PredictLayoutBackward(
    LayoutWrapper* layoutWrapper, float crossSize, const OffsetF& paddingOffset)
{
    // 类似正向预测，但方向相反
    // 从已布局起始索引向后预测
}
```

#### 网格列计算

##### LanesFloor - 向下取整

**文件位置**：`lazy_grid_layout_algorithm.cpp:LanesFloor()`

```cpp
int32_t LazyGridLayoutAlgorithm::LanesFloor(int32_t index) const
{
    int32_t tempIndex = std::min(index, totalItemCount_ - 1);
    return lanes_ <= 1 ? tempIndex : (tempIndex - tempIndex % lanes_);
}
```

**功能**：计算索引所在行的起始索引

**示例**：
- `lanes_ = 3`, `index = 7` → 返回 `6`
- `lanes_ = 3`, `index = 8` → 返回 `6`

##### LanesCeil - 向上取整

**文件位置**：`lazy_grid_layout_algorithm.cpp:LanesCeil()`

```cpp
int32_t LazyGridLayoutAlgorithm::LanesCeil(int32_t index) const
{
    int32_t tempIndex = lanes_ <= 1 ? index : (index - index % lanes_ + lanes_ - 1);
    return std::min(tempIndex, totalItemCount_ - 1);
}
```

**功能**：计算索引所在行的结束索引

**示例**：
- `lanes_ = 3`, `index = 7` → 返回 `8`
- `lanes_ = 3`, `index = 8` → 返回 `8`

#### 正向/反向布局

##### 正向布局 (MeasureForward)

**实现位置**：`lazy_grid_layout_algorithm.cpp:MeasureForward()`

```cpp
void LazyGridLayoutAlgorithm::MeasureForward(
    LayoutWrapper* layoutWrapper, int32_t startIndex, float startPos)
{
    float currentEndPos = startPos;
    int32_t curIndex = startIndex;
    while (LessOrEqual(currentEndPos, endPos_) && curIndex < totalItemCount_) {
        // 测量当前行的所有列
        // ...
        currentEndPos += lineMainSize + spaceWidth_;
        curIndex += lanes_;
    }
}
```

**特点**：
- 从起始索引开始，按行向后测量
- 每次测量一行（lanes_ 个子项）
- 直到超出视口或数据结束

##### 反向布局 (MeasureBackward)

**实现位置**：`lazy_grid_layout_algorithm.cpp:MeasureBackward()`

```cpp
void LazyGridLayoutAlgorithm::MeasureBackward(
    LayoutWrapper* layoutWrapper, int32_t endIndex, float endPos)
{
    float currentStartPos = endPos;
    int32_t curIndex = endIndex;
    while (GreatOrEqual(currentStartPos, startPos_) && curIndex >= 0) {
        // 反向测量当前行的所有列
        // ...
        currentStartPos -= lineMainSize + spaceWidth_;
        curIndex -= lanes_;
    }
}
```

**特点**：
- 从结束索引开始，按行向前测量
- 用于反向滚动场景
- 支持快速定位

---

## LayoutInfo详解

### LazyGridLayoutInfo

**文件位置**：`frameworks/core/components_ng/pattern/lazy_layout/grid_layout/lazy_grid_layout_info.h:42`

#### 数据结构

##### GridItemMainPos - 网格项位置信息

**文件位置**：`lazy_grid_layout_info.h:36-40`

```cpp
struct GridItemMainPos {
    int32_t laneIdx = 0;      // 列索引（第几列）
    float startPos = 0.0f;    // 主轴起始位置
    float endPos = 0.0f;      // 主轴结束位置
};
```

#### 状态管理

**文件位置**：`lazy_grid_layout_info.h:67-92`

```cpp
// 位置映射表
std::map<int32_t, GridItemMainPos> posMap_;      // 索引 → 位置映射

// 可见区域信息
int32_t startIndex_ = -1;                        // 第一个可见项索引
int32_t endIndex_ = -1;                          // 最后一个可见项索引

// 布局配置
int32_t totalItemCount_ = 0;                     // 子项总数
int32_t lanes_ = 1;                              // 列数
float totalMainSize_ = 0.0f;                    // 总主轴尺寸
float spaceWidth_ = 0.0f;                       // 间距宽度

// 更新追踪
int32_t updatedStart_ = INT_MAX;                // 更新起始索引
int32_t updatedEnd_ = -1;                       // 更新结束索引
bool spaceUpdated_ = false;                     // 间距是否更新
float estimateItemSize_ = -1.0f;                // 估算的子项尺寸
AdjustOffset adjustOffset_ {};                  // 调整偏移

// 缓存信息
float layoutedStart_ = 0.0f;                    // 已布局起始位置
float layoutedEnd_ = 0.0f;                      // 已布局结束位置
int32_t layoutedStartIndex_ = -1;               // 已布局起始索引
int32_t layoutedEndIndex_ = -1;                 // 已布局结束索引
float cacheStartPos_ = 0.0f;                    // 缓存起始位置
float cacheEndPos_ = 0.0f;                      // 缓存结束位置
int32_t cachedStartIndex_ = -1;                 // 缓存起始索引
int32_t cachedEndIndex_ = -1;                   // 缓存结束索引
int32_t cachedUpdatedStart_ = INT_MAX;          // 缓存更新起始
int32_t cachedUpdatedEnd_ = -1;                 // 缓存更新结束

// 预测控制
std::optional<int64_t> deadline_;               // 预测截止时间戳
```

#### 核心方法

| 方法名 | 功能 |
|--------|------|
| `EstimateItemSize()` | 估算子项尺寸（用于预测） |
| `UpdatePosMap()` | 更新位置映射表 |
| `SetPosMap()` | 设置单个子项的位置信息 |
| `SetCachedPosMap()` | 设置缓存子项的位置信息 |
| `SetSpace()` | 设置间距 |
| `SetLanes()` | 设置列数 |
| `SetTotalItemCount()` | 设置子项总数 |
| `LanesFloor()` | 计算行起始索引 |
| `LanesCeil()` | 计算行结束索引 |
| `LineCount()` | 计算行数 |
| `NeedPredict()` | 判断是否需要预测 |

---

## 完整API清单

### ArkTS API

#### 组件创建

```typescript
// 基本用法 - LazyVGridLayout（垂直网格）
LazyVGridLayout() {
  ForEach(this.dataArray, (item: DataType) => {
    GridItem() {
      // 子项内容
    }
  })
}
```

#### 属性设置

| 属性名 | 类型 | 必填 | 默认值 | 说明 |
|--------|------|------|--------|------|
| `columnsTemplate` | string | 否 | "1fr" | 列模板（如 "1fr 1fr 1fr" 三等分） |
| `rowsGap` | number / string / Resource | 否 | 0.0_vp | 行间距 |
| `columnsGap` | number / string / Resource | 否 | 0.0_vp | 列间距 |

#### 列模板语法

列模板使用类似 CSS Grid 的语法：

| 值 | 说明 |
|--------|------|
| `"1fr 1fr 1fr"` | 三列等宽 |
| `"1fr 2fr 1fr"` | 三列，中间列宽度是两侧的两倍 |
| `"100px 1fr 100px"` | 固定宽度 + 弹性宽度 |
| `"repeat(3, 1fr)"` | 重复语法（如果支持） |

### C++ 内部 API

#### LazyGridLayoutPattern 公共方法

```cpp
// 焦点管理
FocusPattern GetFocusPattern() const override;
ScopeFocusAlgorithm GetScopeFocusAlgorithm() override;

// 偏移调整
AdjustOffset GetAdjustOffset() const override;
AdjustOffset GetAndResetAdjustOffset() override;

// 生命周期
void OnAttachToMainTree() override;
bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;

// 创建方法
RefPtr<LayoutProperty> CreateLayoutProperty() override;
RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override;

// Dump 调试
void DumpAdvanceInfo() override;
void DumpAdvanceInfo(std::unique_ptr<JsonValue>& json) override;
```

#### LazyVGridLayoutModel 静态方法

```cpp
// 创建组件
static void Create();

// 属性设置
static void SetRowGap(const Dimension& space);
static void SetColumnGap(const Dimension& space);
static void SetColumnsTemplate(const std::string& value);

// 针对现有节点的属性设置
static void SetRowGap(FrameNode* frameNode, const Dimension& space);
static void SetColumnGap(FrameNode* frameNode, const Dimension& space);
static void SetColumnsTemplate(FrameNode* frameNode, const std::string& value);
```

---

## 关键实现细节

### 1. 懒加载模式

**需求**：仅渲染可见区域的子项，提升大数据量场景的性能

**实现位置**：`lazy_grid_layout_algorithm.cpp:Measure()`

**实现方案**：
- 通过 `SetRefencesPos()` 设置视口范围
- 根据视口范围计算需要测量的子项索引范围
- 使用 `MeasureForward()` / `MeasureBackward()` 仅测量可见区域
- 维护 `layoutedStartIndex_` / `layoutedEndIndex_` 追踪已布局范围

**关键代码**：

```cpp
void LazyGridLayoutAlgorithm::MeasureGridItemLazy(LayoutWrapper* layoutWrapper)
{
    // 1. 获取起始索引和位置
    GetStartIndexInfo(startIndex, startPos);
    GetEndIndexInfo(endIndex, endPos);

    // 2. 正向测量
    MeasureForward(layoutWrapper, startIndex, startPos);

    // 3. 反向测量
    MeasureBackward(layoutWrapper, endIndex, endPos);

    // 4. 更新布局信息
    layoutInfo_->startIndex_ = startIndex;
    layoutInfo_->endIndex_ = endIndex;
}
```

### 2. 位置缓存机制

**需求**：快速滚动时能快速定位到目标位置，避免重复测量

**实现位置**：`lazy_grid_layout_info.h:82-92`

**实现方案**：
- 使用 `std::map<int32_t, GridItemMainPos>` 存储索引到位置的映射
- 维护 `layoutedStart_` / `layoutedEnd_` 缓存范围
- 维护 `cacheStartPos_` / `cacheEndPos_` 扩展缓存范围（包含视口外的缓冲区）

**缓存策略**：
- **初始加载**：缓存仅包含可见区域
- **滚动中**：向滚动方向扩展缓存，清理反方向缓存
- **快速滚动**：利用缓存位置快速定位，减少测量量

### 3. 预测性渲染

**需求**：利用空闲时间预渲染即将可见的子项，提升滚动流畅度

**实现位置**：`lazy_grid_layout_pattern.cpp:57-86`

**实现方案**：
- Pattern 层通过 `AddPredictTask()` 注册预测任务
- 任务接收 `deadline` 参数（当前时间 + 预测时间预算）
- 算法层在 `Measure()` 中检查 `layoutInfo_->deadline_`
- 超时即停止预测，下次空闲时继续

**关键代码**：

```cpp
// Pattern 层调度
void LazyGridLayoutPattern::ProcessIdleTask(int64_t deadline)
{
    if (GetSysTimestamp() > deadline) {
        PostIdleTask();  // 重新投递任务
        return;
    }
    layoutInfo_->deadline_ = deadline;
    FrameNode::ProcessOffscreenNode(GetHost(), true);
    layoutInfo_->deadline_.reset();
}

// 算法层检查
void LazyGridLayoutAlgorithm::PredictLayoutForward(...)
{
    auto deadline = layoutInfo_->deadline_.value();
    while (currIndex < totalItemCount_ - 1) {
        if (GetSysTimestamp() > deadline) {
            break;  // 超时停止
        }
        // 继续预测测量
    }
}
```

### 4. 列模板解析

**需求**：支持灵活的列布局配置（如 "1fr 2fr 1fr"）

**实现位置**：`lazy_grid_layout_property.h:68`

**实现方案**：
- 层层传递 `columnsTemplate` 字符串到算法层
- 算法层解析字符串计算 `crossLens_`（每列宽度）和 `crossPos_`（每列起始位置）
- 支持绝对单位（px、vp）和相对单位（fr）

### 5. 焦点管理

**需求**：支持键盘导航和范围焦点

**实现位置**：`lazy_grid_layout_pattern.cpp:30-39`

**实现方案**：
- 实现 `GetFocusPattern()` 返回 `FocusType::SCOPE`
- 实现 `GetScopeFocusAlgorithm()` 配置焦点算法
- 焦点方向：`UNIVERSAL`（支持上下左右）
- 焦点类型：`OTHERS`（非列表/网格专用类型）

---

## 使用示例

### 基础用法

```typescript
@Entry
@Component
struct LazyGridExample {
  @State dataArray: string[] = []

  aboutToAppear() {
    // 初始化 1000 条数据
    for (let i = 0; i < 1000; i++) {
      this.dataArray.push(`Item ${i}`)
    }
  }

  build() {
    WaterFlow() {
      LazyVGridLayout() {
        ForEach(this.dataArray, (item: string, index: number) => {
          GridItem() {
            Text(item)
              .width('100%')
              .height(80)
              .textAlign(TextAlign.Center)
              .borderRadius(8)
              .backgroundColor(Color.White)
          }
          .margin(5)
        }, (item: string, index: number) => `${index}`)
      }
      .columnsTemplate("1fr 1fr 1fr")  // 三列等宽
      .rowGap(10)                       // 行间距 10vp
      .columnGap(10)                    // 列间距 10vp
    }
    .width('100%')
    .height('100%')
    .backgroundColor(Color.Grey)
  }
}
```

### 不同列宽配置

```typescript
LazyVGridLayout() {
  // ... 子项
}
.columnsTemplate("1fr 2fr 1fr")  // 中间列宽度是两侧的两倍
.rowGap(15)
.columnGap(15)
```

### 固定宽度 + 弹性宽度

```typescript
LazyVGridLayout() {
  // ... 子项
}
.columnsTemplate("100px 1fr 100px")  // 两侧固定 100px，中间自适应
```

### 动态更新数据

```typescript
@Entry
@Component
struct DynamicLazyGridExample {
  @State dataArray: string[] = []
  private dataSource: LazyDataSource = new LazyDataSource()

  aboutToAppear() {
    this.dataSource.setData(this.dataArray)
  }

  build() {
    WaterFlow() {
      LazyVGridLayout() {
        ForEach(this.dataArray, (item: string, index: number) => {
          GridItem() {
            Text(item)
          }
        }, (item: string, index: number) => `${index}`)
      }
      .columnsTemplate("1fr 1fr")
    }
  }

  // 添加新数据
  addData() {
    this.dataArray.push(`New Item ${this.dataArray.length}`)
  }

  // 删除数据
  removeData(index: number) {
    this.dataArray.splice(index, 1)
  }
}
```

### 性能优化建议

1. **合理设置缓存大小**：根据设备性能调整预测范围
2. **避免复杂子项**：GridItem 内部避免过深的组件嵌套
3. **使用唯一 key**：ForEach 的 keyGenerator 使用唯一标识
4. **避免频繁更新**：批量更新数据而非逐个添加

```typescript
// 推荐：批量更新
updateBatch() {
  let newData: string[] = []
  for (let i = 0; i < 100; i++) {
    newData.push(`Item ${this.dataArray.length + i}`)
  }
  this.dataArray = [...this.dataArray, ...newData]
}

// 避免：逐个添加
notRecommended() {
  for (let i = 0; i < 100; i++) {
    this.dataArray.push(`Item ${i}`)  // 会触发多次刷新
  }
}
```

---

## 调试指南

### 常用日志

**日志标签**：`AceLogTag::ACE_LAZY_LAYOUT`（推测，需验证）

**关键日志位置**：
- `lazy_grid_layout_pattern.cpp:107` - 父容器验证失败日志
- `lazy_grid_layout_pattern.cpp:79` - 预测任务追踪
- `lazy_grid_layout_info.cpp` - 布局信息更新日志
- `lazy_grid_layout_algorithm.cpp` - 测量/布局算法日志

**日志查看**：

```bash
# 过滤 LazyGrid 相关日志
hdc shell hilog | grep -i "lazy\|grid"

# 查看特定标签日志
hdc shell hilog -t ACE_LAZY_LAYOUT
```

### Dump 调试

LazyGrid 组件支持 dump 功能，可在运行时查看内部状态：

```cpp
// 文件位置：lazy_grid_layout_pattern.cpp:113-117
void LazyGridLayoutPattern::DumpAdvanceInfo()
{
    CHECK_NULL_VOID(layoutInfo_);
    layoutInfo_->DumpAdvanceInfo();
}

void LazyGridLayoutPattern::DumpAdvanceInfo(std::unique_ptr<JsonValue>& json)
{
    CHECK_NULL_VOID(layoutInfo_);
    layoutInfo_->DumpAdvanceInfo(json);
}
```

**Dump 信息包括**：
- 子项总数
- 可见范围索引
- 已布局范围
- 缓存范围
- 位置映射信息

### DevTools 调试

1. 使用 DevEco Studio 的 Inspector 工具查看组件树
2. 检查 WaterFlow 和 LazyVGridLayout 的嵌套关系
3. 监控可见区域的子项数量
4. 查看 `columnsTemplate` 和间距属性是否正确应用

### 常见问题排查

1. **父容器错误**：确认 LazyVGridLayout 是 WaterFlow 的直接或间接子组件
2. **子项不显示**：检查 `columnsTemplate` 是否正确设置
3. **滚动卡顿**：减少 GridItem 内部的组件复杂度
4. **内存占用高**：检查是否使用了过多的缓存

---

## 常见问题

### Q1: LazyVGridLayout 和 Grid 组件有什么区别？

**A**:
- **LazyVGridLayout**：懒加载网格，仅渲染可见区域+预测区域，适合大数据量场景
- **Grid**：传统网格组件，一次性渲染所有子项，适合小数据量场景

**选择建议**：
- 数据量 < 100：使用 Grid
- 数据量 >= 100：使用 LazyVGridLayout

### Q2: 为什么 LazyVGridLayout 必须在 WaterFlow 中使用？

**A**:
LazyVGridLayout 依赖 WaterFlow 提供的以下能力：
1. 滚动容器支持
2. 视口信息传递
3. 滚动事件协调
4. 布局边界管理

这是架构设计上的限制，如需在非 WaterFlow 场景使用，需要修改组件架构。

### Q3: 如何设置不同的列宽？

**A**: 使用 `columnsTemplate` 属性：

```typescript
// 三列等宽
.columnsTemplate("1fr 1fr 1fr")

// 两列，第二列是第一列的两倍
.columnsTemplate("1fr 2fr")

// 混合固定宽度和弹性宽度
.columnsTemplate("100px 1fr 100px")
```

### Q4: 如何优化滚动性能？

**A**:
1. **简化 GridItem 内容**：减少嵌套层级
2. **避免复杂的绑定**：减少 `@Watch` 和复杂计算
3. **使用稳定的 key**：ForEach 的 keyGenerator 使用唯一且稳定的标识
4. **批量更新数据**：避免频繁的单条数据更新

### Q5: 如何获取当前可见的子项索引？

**A**: LazyVGridLayout 不直接暴露可见范围信息。可以通过以下方式间接获取：

1. 使用 GridItem 的 `onAppear()` / `onDisappear()` 回调
2. 自定义监听器追踪可见状态
3. 使用 DevTools 查看组件状态

```typescript
GridItem() {
  Text(item)
}
.onAppear(() => {
  console.log(`Item ${index} appeared`)
})
.onDisappear(() => {
  console.log(`Item ${index} disappeared`)
})
```

### Q6: 如何实现无限滚动加载？

**A**: 结合数据源和滚动监听实现：

```typescript
@State dataArray: string[] = []
private loading: boolean = false

build() {
  WaterFlow() {
    LazyVGridLayout() {
      ForEach(this.dataArray, (item: string) => {
        GridItem() {
          Text(item)
        }
      })
    }
    .columnsTemplate("1fr 1fr")
  }
  .onReachEnd(() => {
    if (!this.loading) {
      this.loading = true
      this.loadMoreData().then(() => {
        this.loading = false
      })
    }
  })
}

async loadMoreData() {
  // 加载更多数据
  const newData = await fetchData()
  this.dataArray = [...this.dataArray, ...newData]
}
```

---

## 附录

### 参考资料

- [OpenHarmony WaterFlow 组件文档](https://developer.openharmony.cn/cn/docs/documentation/doc-references-V3/ts-container-waterflow)
- [Grid 组件文档](https://developer.openharmony.cn/cn/docs/documentation/doc-references-V3/ts-container-grid)
- [GridItem 组件文档](https://developer.openharmony.cn/cn/docs/documentation/doc-references-V3/ts-container-griditem)

### 相关组件文档

- [WaterFlow 组件知识库](../waterflow/WaterFlow_Knowledge_Base.md)（待创建）
- [List 组件知识库](../list/List_Knowledge_Base.md)（待创建）
- [Grid 组件知识库](../grid/Grid_Knowledge_Base.md)（待创建）

### 版本历史

| 版本 | 日期 | 变更说明 |
|------|------|----------|
| v1.0 | 2026-02-03 | 初始版本，完整描述 LazyGrid 组件架构和实现 |

### 文件索引

| 文件 | 行数 | 主要内容 |
|------|------|----------|
| `lazy_grid_layout_pattern.h` | 87 | Pattern 类定义 |
| `lazy_grid_layout_pattern.cpp` | 125 | 核心业务逻辑实现 |
| `lazy_grid_layout_algorithm.h` | 136 | 布局算法类定义 |
| `lazy_grid_layout_algorithm.cpp` | ~800 | 布局算法实现 |
| `lazy_grid_layout_info.h` | 100 | 布局信息状态定义 |
| `lazy_grid_layout_info.cpp` | ~300 | 布局信息实现 |
| `lazy_grid_layout_property.h` | 73 | 属性定义 |
| `lazy_grid_layout_model.h` | 46 | Model 层接口定义 |

### 相关架构文档

- [CLAUDE.md](../../../../CLAUDE.md) - 项目代码规范
- [如何新增一个组件.md](../../../../如何新增一个组件.md) - 组件开发指南
- [Pattern 层设计文档](../pattern_design.md)（待创建）

---

**文档维护**：
- 版本：v1.0
- 最后更新：2026-02-03
- 维护者：基于 CLAUDE.md 规范自动生成

**相关文档**：
- [CLAUDE.md](../../../../CLAUDE.md) - 项目代码规范
- [测试文件](../../../../../test/unittest/core/pattern/lazy_layout/) - 单元测试

**反馈**：
如有问题或建议，请在项目根目录的 `CLAUDE.md` 中更新。
