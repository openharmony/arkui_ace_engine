# SafeArea 安全区域机制知识库

> **文档版本**: v1.0
> **更新时间**: 2026-02-26
> **源码版本**: OpenHarmony ace_engine (master 分支)

---

## 📚 目录

1. [概述](#概述)
2. [核心概念](#核心概念)
3. [数据结构](#数据结构)
4. [API 流程](#api-流程)
5. [递归执行机制](#递归执行机制)
6. [典型场景](#典型场景)
7. [性能优化](#性能优化)

---

## 概述

### SafeArea 机制定位

**SafeArea (安全区域)** 是 OpenHarmony ACE Engine 中处理系统安全区域（如刘海屏、圆角、状态栏、键盘等）的核心机制。通过自动计算和扩展安全区域，确保应用内容不会被系统 UI 遮挡，同时提供灵活的 API 让开发者控制组件的避让行为。

### 技术架构

**核心组成**:
- **safeAreaPadding**: 组件的安全区域内边距
- **accumulatedSafeAreaExpand**: 累积的安全区域扩展
- **SafeAreaManager**: 安全区域管理器
- **expandSafeArea**: 扩展安全区域 API
- **ignoreLayoutSafeArea**: 忽略安全区域 API

**核心特征**:
- **自动避让**: 自动检测系统安全区域并避让
- **向上累积**: 递归向上查找父组件链
- **灵活控制**: 支持按类型和边进行控制
- **性能优化**: 缓存机制减少重复计算

---

## 核心概念

### safeAreaPadding

**定义**: 组件为了避免系统安全区域而增加的内边距，是组件总内边距的一部分。

**特点**:
- **组件独有**: 每个组件都有自己的 safeAreaPadding
- **自动计算**: 由 SafeAreaManager 根据系统安全区域自动计算
- **可继承**: 子组件会继承父组件的 safeAreaPadding
- **叠加生效**: 与组件的 padding 叠加

**获取方式**:
```cpp
// layout_property.cpp:936
PaddingPropertyF LayoutProperty::GetOrCreateSafeAreaPadding(bool forceReCreate)
{
    auto host = GetHost();
    auto pipeline = host ? host->GetContext() : nullptr;
    auto safeAreaManager = pipeline ? pipeline->GetSafeAreaManager() : nullptr;

    // 从 SafeAreaManager 获取系统安全区域
    safeAreaPadding = safeAreaManager->SafeAreaToPadding(false, ignoreType);

    // 与组件自身的 padding 合并
    return CombinePaddingsAndBorder(safeAreaPadding, padding, borderWidth, {});
}
```

**作用**:
- 影响组件的测量结果
- 影响子组件的约束传递
- 在 Layout 阶段用于调整节点位置

---

### accumulatedSafeAreaExpand

**定义**: 从当前组件向上遍历父组件链，计算累积的可扩展到安全区域的总距离。

**特点**:
- **向上累积**: 向父组件方向递归查找
- **实时计算**: 每次调用时实时计算（有缓存优化）
- **向外延伸**: 计算从组件外边缘到安全区域边缘的距离
- **停止条件**: 遇到 padding/border/margin 填满或到达根节点时停止

**计算逻辑**:
```cpp
// layout_wrapper.cpp:523-578
void LayoutWrapper::GetAccumulatedSafeAreaExpandHelper(
    RectF& adjustingRect, ExpandEdges& totalExpand, bool fromSelf, LayoutSafeAreaType ignoreType)
{
    // 1. 确定递归起始节点（自身或父节点）
    auto recursiveHost = fromSelf ? host : host->GetAncestorNodeOfFrame(false);

    // 2. 获取节点的 safeAreaPadding
    safeAreaPadding = layoutProperty->GetOrCreateSafeAreaPadding();

    // 3. 累加到 totalExpand
    totalExpand = totalExpand.Plus(fromSelf ? safeAreaPadding : rollingExpand);

    // 4. 检查停止条件
    if (innerSpace.AllSidesFilled(true) || margin.AllSidesFilled(true) ||
        (recursiveHost->GetTag() == V2::STAGE_ETS_TAG)) {
        return;  // 停止向上遍历
    }

    // 5. 递归调用，继续向上查找
    recursiveHost->GetAccumulatedSafeAreaExpandHelper(adjustingRect, totalExpand, false, ignoreType);
}
```

**执行时机**:
- **Layout 阶段**: `OffsetNodeToSafeArea()` 调用
- **扩展阶段**: `ExpandSafeArea()` 调用

**关键源码**:
- `layout_wrapper.cpp:422-438` - GetAccumulatedSafeAreaExpand
- `layout_wrapper.cpp:440-478` - GetAccumulatedSafeAreaExpandForAllEdges
- `layout_wrapper.cpp:523-578` - GetAccumulatedSafeAreaExpandHelper

---

### 两者的关系

| 特性 | safeAreaPadding | accumulatedSafeAreaExpand |
|------|-----------------|---------------------------|
| **方向** | 向下（父→子） | 向上（子→父） |
| **来源** | SafeAreaManager 计算 | 递归查找父组件 |
| **作用** | 影响测量和约束 | 影响位置调整 |
| **时机** | Measure 阶段 | Layout 阶段 |
| **缓存** | GeometryNode 缓存 | GeometryNode 缓存 |

---

## 数据结构

### ExpandEdges (扩展边)

**位置**: `frameworks/core/components_ng/property/safe_area_property.h`

```cpp
struct ExpandEdges {
    std::optional<float> top;    // 上边扩展距离
    std::optional<float> bottom; // 下边扩展距离
    std::optional<float> left;   // 左边扩展距离
    std::optional<float> right;  // 右边扩展距离

    // 辅助方法
    float Width() const;   // 总宽度扩展 (left + right)
    float Height() const;  // 总高度扩展 (top + bottom)
    float Size() const;    // 总扩展大小

    ExpandEdges Plus(const ExpandEdges& other) const;  // 累加
    bool OptionalValueCover(const ExpandEdges& other) const;  // 是否覆盖
};
```

---

### SafeAreaExpandOpts (扩展选项)

**位置**: `frameworks/core/components_ng/property/safe_area_property.h`

```cpp
struct SafeAreaExpandOpts {
    LayoutSafeAreaType type;   // 扩展类型（系统/键盘/全部）
    LayoutSafeAreaEdge edges;  // 扩展边（上/下/左/右/全部）
    bool switchToNone;         // 是否切换到无扩展

    bool Expansive() const;    // 是否需要扩展
    bool ExpansiveToKeyboard() const;  // 是否扩展到键盘区域
};
```

---

### IgnoreLayoutSafeAreaOpts (忽略选项)

**位置**: `frameworks/core/components_ng/property/safe_area_property.h`

```cpp
struct IgnoreLayoutSafeAreaOpts {
    LayoutSafeAreaType type;        // 忽略的类型
    LayoutSafeAreaEdge rawEdges;     // 原始边选项
    bool ignore;                     // 是否忽略
};
```

---

### LayoutSafeAreaType (安全区域类型)

**位置**: `frameworks/core/components_ng/property/safe_area_property.h`

```cpp
enum LayoutSafeAreaType {
    LAYOUT_SAFE_AREA_TYPE_NONE = 0,       // 无
    LAYOUT_SAFE_AREA_TYPE_SYSTEM = 1 << 0,  // 系统安全区域（刘海屏等）
    LAYOUT_SAFE_AREA_TYPE_KEYBOARD = 1 << 1, // 键盘避让
};
```

---

### LayoutSafeAreaEdge (安全区域边)

**位置**: `frameworks/core/components_ng/property/safe_area_property.h`

```cpp
enum LayoutSafeAreaEdge {
    LAYOUT_SAFE_AREA_EDGE_NONE = 0,
    LAYOUT_SAFE_AREA_EDGE_TOP = 1 << 0,     // 上
    LAYOUT_SAFE_AREA_EDGE_BOTTOM = 1 << 1,  // 下
    LAYOUT_SAFE_AREA_EDGE_START = 1 << 2,    // 左（LTR）或右（RTL）
    LAYOUT_SAFE_AREA_EDGE_END = 1 << 3,      // 右（LTR）或左（RTL）
    LAYOUT_SAFE_AREA_EDGE_ALL = 0xFF         // 全部
};
```

---

## API 流程

### 前端 API 设置

#### expandSafeArea API

**ArkTS 代码**:
```typescript
.expandSafeArea(
  [SafeAreaType.SYSTEM],           // 类型数组
  [SafeAreaEdge.TOP, SafeAreaEdge.BOTTOM]  // 边数组
)
```

**前端解析** (`js_view_abstract.cpp:9381-9412`):

```cpp
void JSViewAbstract::JsExpandSafeArea(const JSCallbackInfo& info)
{
    NG::SafeAreaExpandOpts opts {
        .type = NG::SAFE_AREA_TYPE_ALL,
        .edges = NG::SAFE_AREA_EDGE_ALL
    };

    // 1. 解析类型数组
    if (info.Length() >= 1 && info[0]->IsArray()) {
        auto paramArray = JSRef<JSArray>::Cast(info[0]);
        uint32_t safeAreaType = NG::LAYOUT_SAFE_AREA_TYPE_NONE;
        for (size_t i = 0; i < paramArray->Length(); ++i) {
            safeAreaType |= (1 << paramArray->GetValueAt(i)->ToNumber<uint32_t>());
        }
        opts.type = safeAreaType;
    }

    // 2. 解析边数组
    if (info.Length() >= 2 && info[1]->IsArray()) {
        auto paramArray = JSRef<JSArray>::Cast(info[1]);
        uint32_t safeAreaEdge = NG::LAYOUT_SAFE_AREA_EDGE_NONE;
        for (size_t i = 0; i < paramArray->Length(); ++i) {
            safeAreaEdge |= (1 << paramArray->GetValueAt(i)->ToNumber<uint32_t>());
        }
        opts.edges = safeAreaEdge;
    }

    // 3. 更新到 Model
    ViewAbstractModel::GetInstance()->UpdateSafeAreaExpandOpts(opts);
}
```

#### ignoreLayoutSafeArea API

**ArkTS 代码**:
```typescript
.ignoreLayoutSafeArea(
  [SafeAreaType.KEYBOARD],  // 忽略键盘避让
  [SafeAreaEdge.BOTTOM]       // 忽略下边
)
```

**前端解析** (`js_view_abstract.cpp:9414-9445`):

```cpp
void JSViewAbstract::JsIgnoreLayoutSafeArea(const JSCallbackInfo& info)
{
    NG::IgnoreLayoutSafeAreaOpts opts {
        .type = NG::LAYOUT_SAFE_AREA_TYPE_SYSTEM,
        .rawEdges = NG::LAYOUT_SAFE_AREA_EDGE_ALL
    };

    // 1. 解析类型数组
    // 2. 解析边数组
    // 3. 更新到 Model
    ViewAbstractModel::GetInstance()->UpdateIgnoreLayoutSafeAreaOpts(opts);
}
```

---

### Model → Pattern 流程

```cpp
// view_abstract_model_impl.h
void ViewAbstractModel::UpdateSafeAreaExpandOpts(const SafeAreaExpandOpts& opts)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);

    // 设置到 LayoutProperty
    auto layoutProperty = frameNode->GetLayoutProperty();
    layoutProperty->UpdateSafeAreaExpandOpts(opts);

    // 标记需要重新布局
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
}
```

---

## 递归执行机制

### 向上递归的核心流程

```
GetAccumulatedSafeAreaExpand()  [入口函数]
  │
  ├─> FilterEdges()  [过滤边]
  │
  └─> GetAccumulatedSafeAreaExpandForAllEdges()  [获取所有边]
       │
       └─> GetAccumulatedSafeAreaExpandHelper()  [递归核心]
            │
            ├─> 1. 获取父节点
            │     recursiveHost = host->GetAncestorNodeOfFrame(false)
            │
            ├─> 2. 获取父节点的 safeAreaPadding
            │     safeAreaPadding = layoutProperty->GetOrCreateSafeAreaPadding()
            │
            ├─> 3. 解析父节点的 safeAreaPadding
            │     ParseSafeAreaPaddingSides(safeAreaPadding, ...)
            │
            ├─> 4. 累加到 totalExpand
            │     totalExpand = totalExpand.Plus(rollingExpand)
            │
            ├─> 5. 检查停止条件
            │     if (innerSpace.AllSidesFilled() ||
            │         margin.AllSidesFilled() ||
            │         IsStageNode()) {
            │         return;  // 停止递归
            │     }
            │
            └─> 6. 递归调用，继续向上
                 recursiveHost->GetAccumulatedSafeAreaExpandHelper(...)
```

---

### 关键函数详解

#### FilterEdges

**位置**: `layout_wrapper.cpp:63-79`

**作用**: 根据指定的边过滤扩展距离

```cpp
ExpandEdges FilterEdges(const ExpandEdges& rawExpand, LayoutSafeAreaEdge edges)
{
    ExpandEdges res;
    if (edges & LAYOUT_SAFE_AREA_EDGE_TOP) {
        res.top = rawExpand.top;
    }
    if (edges & LAYOUT_SAFE_AREA_EDGE_BOTTOM) {
        res.bottom = rawExpand.bottom;
    }
    if (edges & LAYOUT_SAFE_AREA_EDGE_START) {
        res.left = rawExpand.left;
    }
    if (edges & LAYOUT_SAFE_AREA_EDGE_END) {
        res.right = rawExpand.right;
    }
    return res;
}
```

**使用场景**: 组件只需要扩展部分边时使用

---

#### GetAccumulatedSafeAreaExpand

**位置**: `layout_wrapper.cpp:422-438`

**作用**: 获取累积的安全区域扩展（入口函数）

```cpp
ExpandEdges LayoutWrapper::GetAccumulatedSafeAreaExpand(
    bool includingSelf,              // 是否包含自身
    IgnoreLayoutSafeAreaOpts options, // 忽略选项
    IgnoreStrategy strategy)          // 策略
{
    StartPoint startPoint = StartPoint::NORMAL;

    // 1. 根据策略选择起始点
    if (strategy == IgnoreStrategy::FROM_MARGIN) {
        startPoint = StartPoint::FROM_MARGIN;
    } else if (strategy == IgnoreStrategy::AXIS_INSENSITIVE) {
        isScrollableAxis_ = true;
        auto sae = FilterEdges(
            GetAccumulatedSafeAreaExpandForAllEdges(
                includingSelf ? StartPoint::INCLUDING_SELF : startPoint,
                options.type
            ),
            options.edges
        );
        isScrollableAxis_ = false;
        return sae;
    } else if (includingSelf) {
        startPoint = StartPoint::INCLUDING_SELF;
    }

    // 2. 调用核心函数
    return FilterEdges(
        GetAccumulatedSafeAreaExpandForAllEdges(startPoint, options.type),
        options.edges
    );
}
```

**参数说明**:
- `includingSelf`: 是否包含当前节点的 safeAreaPadding
- `options`: 忽略安全区域的选项（类型和边）
- `strategy`: 策略（NORMAL/FROM_MARGIN/AXIS_INSENSITIVE）

**策略说明**:
- **NORMAL**: 正常模式，从 frameRect 开始
- **FROM_MARGIN**: 从 marginRect 开始
- **AXIS_INSENSITIVE**: 轴不敏感模式（用于滚动组件）

---

#### GetAccumulatedSafeAreaExpandForAllEdges

**位置**: `layout_wrapper.cpp:440-478`

**作用**: 获取所有边的累积安全区域扩展

```cpp
ExpandEdges LayoutWrapper::GetAccumulatedSafeAreaExpandForAllEdges(
    StartPoint startPoint,
    LayoutSafeAreaType ignoreType)
{
    ExpandEdges totalExpand;
    auto host = GetHostNode();
    const auto& geometryNode = host->GetGeometryNode();

    // 1. 确定起始矩形
    RectF adjustingRect;
    if (startPoint == StartPoint::FROM_MARGIN) {
        adjustingRect = geometryNode->GetMarginFrameRect();
    } else {
        adjustingRect = geometryNode->GetFrameRect();
    }

    const auto& layoutProperty = host->GetLayoutProperty();

    // 2. 如果包含自身，先累加自身的 safeAreaPadding
    if (startPoint == StartPoint::INCLUDING_SELF) {
        GetAccumulatedSafeAreaExpandHelper(adjustingRect, totalExpand, true, ignoreType);
        return totalExpand;
    }

    // 3. 检查是否可以跳过累加
    auto hostMargin = layoutProperty->CreateMargin();
    if (startPoint != StartPoint::FROM_MARGIN && hostMargin.AllSidesFilled(true)) {
        return totalExpand;  // margin 填满所有边，无需累加
    }

    // 4. 执行累加
    GetAccumulatedSafeAreaExpandHelper(adjustingRect, totalExpand, false, ignoreType);

    // 5. 设置缓存（仅针对 SYSTEM 类型）
    if (IsIgnoreTypeTrivial(ignoreType) && !isScrollableAxis_) {
        geometryNode->SetAccumulatedSafeAreaEdges(totalExpand);
    }

    return totalExpand;
}
```

**关键点**:
- **缓存优化**: 只对 SYSTEM 类型缓存，KEYBOARD 类型不缓存（因为键盘高度动态变化）
- **提前终止**: margin 填满时直接返回

---

#### GetAccumulatedSafeAreaExpandHelper

**位置**: `layout_wrapper.cpp:523-578`

**作用**: 递归向上查找父组件，累加安全区域扩展（核心函数）

```cpp
void LayoutWrapper::GetAccumulatedSafeAreaExpandHelper(
    RectF& adjustingRect,       // 当前调整矩形
    ExpandEdges& totalExpand,   // 累积的扩展距离
    bool fromSelf,              // 是否从自身开始
    LayoutSafeAreaType ignoreType)  // 忽略类型
{
    auto host = GetHostNode();

    // 1. 确定递归起始节点
    auto recursiveHost = host;
    if (!fromSelf) {
        auto parent = host->GetAncestorNodeOfFrame(false);
        CHECK_NULL_VOID(parent);
        recursiveHost = parent;  // 从父节点开始
    }

    const auto& geometryNode = recursiveHost->GetGeometryNode();
    const auto& layoutProperty = recursiveHost->GetLayoutProperty();

    // 2. 获取节点的 safeAreaPadding
    PaddingPropertyF safeAreaPadding;
    if (recursiveHost->GetTag() == V2::STAGE_ETS_TAG) {
        // Stage 节点：从 SafeAreaManager 获取
        const auto& pipeline = recursiveHost->GetContext();
        auto safeAreaManager = pipeline->GetSafeAreaManager();
        safeAreaPadding = safeAreaManager->SafeAreaToPadding(false, ignoreType);
    } else {
        // 普通节点：从 LayoutProperty 获取
        safeAreaPadding = layoutProperty->GetOrCreateSafeAreaPadding();
    }

    // 3. 获取内边距（padding + border）
    auto innerSpace = layoutProperty->CreatePaddingAndBorder(false, false);

    // 4. Pattern 自定义处理
    auto pattern = recursiveHost->GetPattern();
    if (!isScrollableAxis_ && pattern && pattern->NeedCustomizeSafeAreaPadding()) {
        innerSpace.Plus(pattern->CustomizeSafeAreaPadding(safeAreaPadding, true), true);
        safeAreaPadding = pattern->CustomizeSafeAreaPadding(safeAreaPadding, false);
    }

    // 5. 根据是否包含自身，采用不同处理
    if (fromSelf) {
        // 包含自身：adjustingRect 减去 innerSpace
        ReduceRectByRolling(adjustingRect, innerSpace, -1.0);
    } else {
        // 不包含自身：解析父节点的 safeAreaPadding
        ParseSafeAreaPaddingSides(safeAreaPadding, innerSpace, adjustingRect, rollingExpand);

        // adjustingRect 加上 rollingExpand
        ReduceRectByRolling(adjustingRect, rollingExpand, 1.0);

        // 调整坐标系到父节点
        adjustingRect.SetOffset(adjustingRect.GetOffset() + geometryNode->GetFrameOffset());
    }

    // 6. 累加扩展
    totalExpand = totalExpand.Plus(fromSelf ? safeAreaPadding : rollingExpand);

    // 7. 检查停止条件
    auto margin = layoutProperty->CreateMargin();
    if (innerSpace.AllSidesFilled(true) || margin.AllSidesFilled(true) ||
        (recursiveHost->GetTag() == V2::STAGE_ETS_TAG)) {
        return;  // 停止递归
    }

    // 8. Pattern 自定义终止条件
    if (pattern && pattern->AccumulatingTerminateHelper(
        adjustingRect, totalExpand, fromSelf, ignoreType)) {
        return;  // 停止递归
    }

    // 9. 递归调用，继续向上查找
    recursiveHost->GetAccumulatedSafeAreaExpandHelper(
        adjustingRect, totalExpand, false, ignoreType);
}
```

**关键步骤**:
1. **向上遍历**: 递归查找父组件
2. **获取 padding**: 从父组件获取 safeAreaPadding
3. **解析边**: ParseSafeAreaPaddingSides 解析各边
4. **累加计算**: 将父组件的扩展累加到 totalExpand
5. **停止检查**: 检查是否应该停止累加
6. **继续递归**: 继续向上查找父组件

**停止条件**:
1. `innerSpace.AllSidesFilled(true)`: padding 和 border 填满所有边
2. `margin.AllSidesFilled(true)`: margin 填满所有边
3. `recursiveHost->GetTag() == V2::STAGE_ETS_TAG`: 到达根节点
4. `pattern->AccumulatingTerminateHelper()`: Pattern 自定义终止条件

---

#### ParseSafeAreaPaddingSides

**位置**: `layout_wrapper.cpp:472-521`

**作用**: 解析父节点的 safeAreaPadding，计算当前节点可以向各边扩展的距离

```cpp
void LayoutWrapper::ParseSafeAreaPaddingSides(
    const PaddingPropertyF& parentSafeAreaPadding,  // 父节点的 safeAreaPadding
    const PaddingPropertyF& parentInnerSpace,       // 父节点的 padding+border
    const RectF& adjustingRect,                    // 当前调整矩形
    ExpandEdges& rollingExpand)                    // 输出：滚动扩展距离
{
    auto parent = host->GetAncestorNodeOfFrame(false);
    const auto& parentGeometryNode = parent->GetGeometryNode();

    // 检查当前矩形是否与父节点的 safeAreaPadding 重叠
    if (!NearZero(parentSafeAreaPadding.left.value_or(0.0f))) {
        auto innerSpaceLeftLength = parentInnerSpace.left.value_or(0.0f);
        // 左边 safeArea 范围是 [border+padding, border+padding+safeAreaPadding]
        if (InRangeStart(adjustingRect.Left(), innerSpaceLeftLength,
            innerSpaceLeftLength + parentSafeAreaPadding.left.value_or(0.0f))) {
            rollingExpand.left = adjustingRect.Left() - innerSpaceLeftLength;
        }
    }

    if (!NearZero(parentSafeAreaPadding.top.value_or(0.0f))) {
        auto innerSpaceTopLength = parentInnerSpace.top.value_or(0.0f);
        // 上边 safeArea 范围是 [border+padding, border+padding+safeAreaPadding]
        if (InRangeStart(adjustingRect.Top(), innerSpaceTopLength,
            innerSpaceTopLength + parentSafeAreaPadding.top.value_or(0.0f))) {
            rollingExpand.top = adjustingRect.Top() - innerSpaceTopLength;
        }
    }

    if (!NearZero(parentSafeAreaPadding.right.value_or(0.0f))) {
        auto parentWidth = parentGeometryNode->GetFrameRect().Width();
        auto innerSpaceRightLength = parentInnerSpace.right.value_or(0.0f);
        // 右边 safeArea 范围是 [width-border-padding-safeArea, width-border-padding]
        if (InRangeEnd(adjustingRect.Right(),
            parentWidth - innerSpaceRightLength - parentSafeAreaPadding.right.value_or(0.0f),
            parentWidth - innerSpaceRightLength)) {
            rollingExpand.right = parentWidth - innerSpaceRightLength - adjustingRect.Right();
        }
    }

    if (!NearZero(parentSafeAreaPadding.bottom.value_or(0.0f))) {
        auto parentHeight = parentGeometryNode->GetFrameRect().Height();
        auto innerSpaceBottomLength = parentInnerSpace.bottom.value_or(0.0f);
        // 下边 safeArea 范围是 [height-border-padding-safeArea, height-border-padding]
        if (InRangeEnd(adjustingRect.Bottom(),
            parentHeight - innerSpaceBottomLength - parentSafeAreaPadding.bottom.value_or(0.0f),
            parentHeight - innerSpaceBottomLength)) {
            rollingExpand.bottom = parentHeight - innerSpaceBottomLength - adjustingRect.Bottom();
        }
    }
}
```

**逻辑说明**:
- **InRangeStart**: 检查当前边的起始位置是否在父节点的 safeAreaPadding 范围内
- **InRangeEnd**: 检查当前边的结束位置是否在父节点的 safeAreaPadding 范围内
- **计算扩展**: 如果在范围内，计算可以扩展的距离

---

#### SafeAreaToPadding

**位置**: `safe_area_manager.cpp:330-350`

**作用**: 将系统安全区域转换为 Padding

```cpp
PaddingPropertyF SafeAreaManager::SafeAreaToPadding(
    bool withoutProcess,
    LayoutSafeAreaType ignoreType)
{
    // 1. 检查是否忽略安全区域
    if (!withoutProcess) {
        if (ignoreSafeArea_ || (!isFullScreen_ && !isNeedAvoidWindow_)) {
            return {};  // 非全屏或不需要避让窗口，返回空
        }
    }

    // 2. 合并各种安全区域
    SafeAreaInsets combinedSafeArea;
    auto cutoutSafeArea = useCutout_ ? cutoutSafeArea_ : SafeAreaInsets();
    combinedSafeArea += cutoutSafeArea_;    // 刘海屏、圆角等
    combinedSafeArea += keyboardSafeArea_; // 键盘区域
    combinedSafeArea += systemSafeArea_;   // 系统区域

    // 3. 转换为 Padding
    PaddingPropertyF padding;
    padding.left = CalcLength(combinedSafeArea.left_);
    padding.right = CalcLength(combinedSafeArea.right_);
    padding.top = CalcLength(combinedSafeArea.top_);
    padding.bottom = CalcLength(combinedSafeArea.bottom_);

    return padding;
}
```

**安全区域来源**:
- **cutoutSafeArea_:** 刘海屏、挖孔屏等物理安全区域
- **keyboardSafeArea_:** 键盘避让区域
- **systemSafeArea_:** 系统状态栏、导航栏等

---

#### AccumulatingTerminateHelper

**作用**: Pattern 实现的自定义终止条件

**默认实现**: 不终止，继续向上查找

**自定义场景**:
- **Scroll 组件**: 超出可视区域时终止累加
- **自定义容器**: 根据特定条件终止

**示例**:
```cpp
bool ScrollablePattern::AccumulatingTerminateHelper(
    const RectF& adjustingRect,
    const ExpandEdges& totalExpand,
    bool fromSelf,
    LayoutSafeAreaType ignoreType)
{
    // 如果组件不可见或超出滚动范围，终止累加
    if (!GetHostNode()->IsActive()) {
        return true;
    }
    return false;  // 默认不终止
}
```

---

## 典型场景

### 场景 1: 全屏应用避免刘海屏

**场景描述**: 全屏应用顶部有刘海屏，需要避免内容被遮挡

**组件树**:
```
Stage (根节点)
  ├─ safeAreaPadding: top=44dp (刘海屏高度)
  │
  └─ Column (.expandSafeArea([SYSTEM], [TOP]))
       ├─ safeAreaExpandOpts: type=SYSTEM, edges=TOP
       ├─ GetAccumulatedSafeAreaExpand(): 44dp
       └─ 实际效果: Column 向下偏移 44dp
```

**执行流程**:
```
1. 用户调用:
   Column().expandSafeArea([SafeAreaType.SYSTEM], [SafeAreaEdge.TOP])

2. 前端解析:
   JSViewAbstract::JsExpandSafeArea()
   └─> ViewAbstractModel::UpdateSafeAreaExpandOpts()

3. Layout 阶段:
   FrameNode::Layout()
   └─> OffsetNodeToSafeArea()
        └─> GetAccumulatedSafeAreaExpand()
             └─> GetAccumulatedSafeAreaExpandHelper()
                  递归向上查找 Stage 的 safeAreaPadding
                  └─> 返回: top=44dp

4. 结果:
   Column 向下偏移 44dp，避免刘海屏
```

---

### 场景 2: 键盘避让

**场景描述**: 底部输入框被键盘遮挡，需要向上避让

**组件树**:
```
Page (页面节点)
  ├─ safeAreaPadding: bottom=300dp (键盘高度)
  │
  └─ Column
       └─ TextInput (.ignoreLayoutSafeArea([KEYBOARD], [BOTTOM]))
            ├─ ignoreLayoutSafeAreaOpts: type=KEYBOARD, edges=BOTTOM
            ├─ GetAccumulatedSafeAreaExpand(): 0dp (忽略键盘)
            └─ 实际效果: TextInput 不被键盘推开
```

**执行流程**:
```
1. 用户调用:
   TextInput().ignoreLayoutSafeArea([SafeAreaType.KEYBOARD], [SafeAreaEdge.BOTTOM])

2. 前端解析:
   JSViewAbstract::JsIgnoreLayoutSafeArea()
   └─> ViewAbstractModel::UpdateIgnoreLayoutSafeAreaOpts()

3. Layout 阶段:
   TextInput::GetAccumulatedSafeAreaExpand()
   └─> ignoreType=KEYBOARD，跳过键盘 safeAreaPadding 的累加
   └─> 返回: 0dp

4. 结果:
   TextInput 不被键盘推开，保持原位置
```

---

### 场景 3: 嵌套组件的累积扩展

**场景描述**: 多层嵌套组件的 safeAreaPadding 累积

**组件树**:
```
Stage (safeAreaPadding: top=44dp)
  │
  └─ Column (padding: 10dp, border: 5dp)
       │
       └─ Row (padding: 20dp)
            │
            └─ Text (.expandSafeArea([SYSTEM], [TOP]))
                 │
                 └─ GetAccumulatedSafeAreaExpand()
                      递归向上查找:
                      ├─ Text 自身: 0 (无 safeAreaPadding)
                      ├─ Row: padding=20, border=0 (未填满)
                      │    继续向上
                      ├─ Column: padding=10, border=5 (未填满)
                      │    继续向上
                      ├─ Stage: safeAreaPadding=44 (根节点)
                      │    停止查找
                      └─> 返回: 44dp
```

**关键点**:
- Row 和 Column 的 padding 未填满所有边，继续向上查找
- 到达 Stage 根节点时停止
- 最终返回 44dp

---

### 场景 4: 停止条件触发

**场景描述**: 父组件的 padding 填满所有边，停止向上查找

**组件树**:
```
Stage (safeAreaPadding: top=44dp)
  │
  └─ Column (padding: top=20, bottom=20, left=20, right=20)  // 填满
       │
       └─ Text (.expandSafeArea([SYSTEM], [TOP]))
            │
            └─ GetAccumulatedSafeAreaExpand()
                 递归向上查找:
                 ├─ Text 自身: 0
                 ├─ Column: padding 填满所有边
                 │    innerSpace.AllSidesFilled(true) == true
                 │    停止查找
                 └─> 返回: 0dp
```

**关键点**:
- Column 的 padding 填满所有边（上下左右都有值）
- 触发停止条件，不再向上查找 Stage
- Text 只能使用 Column 的 20dp padding，无法到达 Stage 的 44dp

---

## 性能优化

### 1. 缓存机制

**位置**: `layout_wrapper.cpp:376-420`

**原理**: 缓存累积扩展结果，避免重复计算

```cpp
bool LayoutWrapper::AccumulateExpandCacheHit(
    ExpandEdges& totalExpand,
    const PaddingPropertyF& innerSpace,
    const RectF& adjustingRect,
    LayoutSafeAreaType ignoreType)
{
    auto host = GetHostNode();
    const auto& geometryNode = host->GetGeometryNode();
    auto& selfAccumulateExpand = geometryNode->GetAccumulatedSafeAreaExpand();

    // 1. 检查缓存是否覆盖需要的扩展
    CHECK_NULL_RETURN(selfAccumulateExpand, false);
    if (selfAccumulateExpand->OptionalValueCover(totalExpand)) {
        // 2. 检查 PaddingBorderGap
        if (CheckPaddingBorderGap(totalExpand, innerSpace)) {
            // 3. 使用缓存
            totalExpand += *selfAccumulateExpand;
            return true;  // 缓存命中
        }
    }

    return false;  // 缓存未命中
}
```

**缓存策略**:
- **缓存位置**: GeometryNode::accumulatedSafeAreaExpand_
- **缓存条件**: 只对 SYSTEM 类型缓存（KEYBOARD 不缓存）
- **缓存覆盖**: 检查缓存是否完全覆盖需要的扩展

**优化效果**:
- 避免重复向上遍历父组件链
- 减少递归深度
- 提升性能

---

### 2. 提前终止

**位置**: `layout_wrapper.cpp:569-576`

**停止条件**:
1. **Padding/Border 填满**: `innerSpace.AllSidesFilled(true)`
2. **Margin 存在**: `margin.AllSidesFilled(true)`
3. **到达根节点**: `recursiveHost->GetTag() == V2::STAGE_ETS_TAG`
4. **Pattern 自定义终止**: `pattern->AccumulatingTerminateHelper()`

**优化效果**:
- 减少不必要的递归
- 提升查找效率
- 降低 CPU 占用

---

### 3. 懒加载策略

**实现**: 只在需要时才计算累积扩展

**时机**:
- Layout 阶段的 `OffsetNodeToSafeArea()`
- 扩展阶段的 `ExpandSafeArea()`

**优化效果**:
- 避免不必要的计算
- 按需计算，节省资源

---

## 执行时机总结

### Layout 阶段

```
FrameNode::Layout (frame_node.cpp:5682)
  │
  ├─> OffsetNodeToSafeArea()  // line:5697
  │     │
  │     └─> GetAccumulatedSafeAreaExpand()
  │          └─> 递归向上查找父组件
  │
  ├─> layoutAlgorithm_->Layout(this)
  │
  └─> OnLayoutFinish()
```

### 扩展阶段

```
UITaskScheduler::FlushSyncGeometryNodeTasks (ui_task_scheduler.cpp:116)
  │
  ├─> ExpandSafeArea()  // line:119
  │     │
  │     └─> SafeAreaManager::ExpandSafeArea()
  │          └─> LayoutWrapper::ExpandSafeArea()
  │               └─> GetAccumulatedSafeAreaExpand()
  │                    └─> 递归向上查找父组件
  │
  ├─> SetLayoutNodeRect()
  │
  └─> 执行所有同步任务
```

---

## 附录

### 关键文件位置

| 文件 | 路径 | 作用 |
|------|------|------|
| **前端 API** | `frameworks/bridge/declarative_frontend/jsview/js_view_abstract.cpp` | expandSafeArea/ignoreLayoutSafeArea API |
| **Model 层** | `frameworks/bridge/declarative_frontend/jsview/models/view_abstract_model_impl.h` | 更新 SafeAreaExpandOpts |
| **FrameNode** | `frameworks/core/components_ng/base/frame_node.cpp` | 布局阶段调用 |
| **LayoutProperty** | `frameworks/core/components_ng/layout/layout_property.cpp/h` | safeAreaPadding 管理 |
| **LayoutWrapper** | `frameworks/core/components_ng/layout/layout_wrapper.cpp` | 累积扩展计算 |
| **SafeAreaManager** | `frameworks/core/components_ng/manager/safe_area/safe_area_manager.cpp` | 系统安全区域管理 |

### 关键函数位置

| 函数 | 文件 | 行号 |
|------|------|------|
| FilterEdges | layout_wrapper.cpp | 63-79 |
| GetAccumulatedSafeAreaExpand | layout_wrapper.cpp | 422-438 |
| GetAccumulatedSafeAreaExpandForAllEdges | layout_wrapper.cpp | 440-478 |
| GetAccumulatedSafeAreaExpandHelper | layout_wrapper.cpp | 523-578 |
| ParseSafeAreaPaddingSides | layout_wrapper.cpp | 472-521 |
| SafeAreaToPadding | safe_area_manager.cpp | 330-350 |
| GetOrCreateSafeAreaPadding | layout_property.cpp | 936-950 |
| JsExpandSafeArea | js_view_abstract.cpp | 9381-9412 |
| JsIgnoreLayoutSafeArea | js_view_abstract.cpp | 9414-9445 |

---

**文档维护**: 本文档应随代码变更同步更新，确保准确反映当前实现。
