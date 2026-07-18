# ignoreLayoutSafeArea 忽略布局安全区边界机制知识库

> **文档版本**: v4.0
> **更新时间**: 2026-02-26
> **源码版本**: OpenHarmony ace_engine (master 分支)

---

## 📚目录

1. [概述](#概述)
2. [核心概念](#核心概念)
3. [循环依赖问题](#循环依赖问题)
4. [解决方案：后抛任务调度](#解决方案后抛任务调度)
5. [两种提交Bundle的机制](#两种提交bundle的机制)
6. [公共执行流程](#公共执行流程)
7. [关键机制](#关键机制)
8. [数据结构](#数据结构)
9. [典型场景](#典型场景)
10. [性能优化](#性能优化)

---

## 概述

### 机制定位

**ignoreLayoutSafeArea** 是 OpenHarmony ACE Engine 中处理组件**突破安全区域边界**的核心机制。通过后抛任务调度，解决 DFS 布局调用栈的限制，让组件能够延伸到刘海、状态栏、导航条等避让区中。

### 技术架构

**核心组成**:
- **PreMeasure**: 预测量检测机制
- **ChildPreMeasureHelper**: 父组件辅助检测
- **AddIgnoreLayoutSafeAreaBundle**: 延迟任务打包
- **FlushPostponedLayoutTask**: 公共执行入口
- **TraverseForIgnore**: 扩散标脏机制
- **GetAccumulatedSafeAreaExpand**: 累加延伸计算

**核心特征**:
- **后抛调度**: 子组件测量后抛到所有祖先布局完成后
- **两种提交机制**: 非侵入式Pattern Hook + 容器主动打包
- **扩散标脏**: 应对父约束不变但全局可延伸范围变化的场景
- **累加延伸**: 强依赖 accumulatedSafeAreaExpand 机制

### 解决的问题

**问题**: DFS 布局调用栈后进先出 vs 子组件需要感知所有祖先布局结果

**解决**: 通过后抛任务调度，将子组件测量延迟到所有祖先布局完成后执行

---

## 核心概念

### 安全区域（SafeArea）

**定义**: 不会被刘海、挖孔、状态栏、导航条遮挡显示或妨碍交互的区域

**特点**:
- 从 page 节点开始默认在安全区域内布局
- 组件布局范围被限制在安全区域内
- 不会延伸到避让区（AvoidArea）

**避让区类型**:
- **SYSTEM**: 刘海、挖孔、圆角等系统避让区
- **KEYBOARD**: 键盘避让区
- **CUSTOM**: 自定义避让区

**源码位置**: `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/property/safe_area_property.h`

---

### ignoreLayoutSafeArea

**定义**: 让组件突破安全区域边界，延伸到邻接的避让区中

**API**:
```typescript
.ignoreLayoutSafeArea({
  type: SafeAreaType.SYSTEM,    // 要突破的类型
  edges: SafeAreaEdges.TOP      // 要突破的边
})
```

**效果**:
- 组件布局范围延伸到状态栏区域
- 组件布局范围延伸到导航条区域
- 组件布局范围延伸到刘海区域

**源码位置**: 
- API入口: `OpenHarmony/foundation/arkui/ace_engine/frameworks/bridge/declarative_frontend/engine/js_view_abstract.cpp:9414-9445`
- 属性更新: `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/property/layout_property.cpp:1143-1164`

---

## 循环依赖问题

### DFS 布局调用栈的限制

**特点**: 后进先出（LIFO）

```
组件树 DFS 布局：
──────────────────────────
Column::Measure
  ├─ Scroll::Measure
  │   └─ List::Measure
  │       └─ ListItem::Measure  ◄── 最深的子组件先完成
  └─ Button::Measure          ◄── 然后父组件才完成
```

**源码位置**: `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/base/frame_node.cpp:5570+`

---

### ignoreLayoutSafeArea 的依赖需求

当组件使用 `ignoreLayoutSafeArea` 时，需要调用 `GetAccumulatedSafeAreaExpand` 来计算可以延伸的距离：

- 递归向上遍历所有祖先组件
- 需要所有祖先组件的**测量和定位完成后**才能准确计算
- 依赖祖先的 safeAreaPadding、位置、尺寸等信息

**矛盾**:
- DFS 调用栈要求：子组件 Measure → 父组件 Layout 完成（后进先出）
- ignoreLayoutSafeArea 要求：子组件需要感知所有祖先的布局结果（先全部完成）

无法在一次 DFS 遍历中同时满足这两个要求。

**源码位置**: `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/layout/layout_wrapper.cpp:422-470`

---

## 解决方案：后抛任务调度

### 核心思想

通过后抛任务调度，将子组件测量延迟到所有祖先布局完成后执行。

```
正常 DFS 布局（失败）：
────────────────────
Column::Measure
  └─ Scroll::Measure (调用 GetAccumulatedSafeAreaExpand)
      └─ ❌ 祖先未全部完成，无法准确计算

后抛任务调度（成功）：
────────────────────
Column::Measure
  └─ Scroll::PreMeasure → 返回 true
      └─ 本次跳过 Measure
      └─ 添加到 ignoreLayoutSafeAreaBundles_

Column::Layout 完成
其他祖先::Layout 完成

FlushPostponedLayoutTask
  └─ Scroll::Measure (MEASURE_FOR_IGNORE)
      └─ GetAccumulatedSafeAreaExpand
          └─ ✅ 所有祖先已完成布局，可以准确计算
```

**源码位置**:
- PreMeasure: `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/base/frame_node.cpp:5355-5367`
- PostTaskForIgnore: `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/base/frame_node.cpp:5407-5413`

---

### PreMeasure 的关键行为

```cpp
// frame_node.cpp:5595
if (PreMeasure(parentConstraint)) {
    return;  // 直接返回，跳过本次 Measure
}
```

**PreMeasure 返回 true 时**：
- 本次 Measure **直接跳过**，不执行任何测量操作
- 不是延迟执行，而是本次不执行
- 子组件的测量任务被后抛到所有祖先布局完成后

**源码位置**: `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/base/frame_node.cpp:5595`

---

## 两种提交Bundle的机制

ignoreLayoutSafeArea 机制内嵌了两种提交 Bundle 的方式，适应不同的使用场景。

### 非侵入式Pattern Hook机制

**目的**: 避免侵入式修改容器的布局算法

**核心组件**:
- `PreMeasure`: 预测量 Hook（Pattern 虚函数）
- `ChildPreMeasureHelper`: 父组件辅助检测（Pattern 虚函数）
- `PredictMeasureResult`: 预测测量结果（默认实现）
- `PostponedTaskForIgnore`: 应用延迟布局调整（Pattern 虚函数）

**特点**:
- 容器**不需要知道** ignoreLayoutSafeArea 机制
- 通过 Pattern Hook 自动处理
- 无需修改布局算法代码

**实现位置**: 
- `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/base/frame_node.cpp`

---

### 容器主动打包机制

**目的**: 让容器高度定制化控制 ignore 延伸行为

**核心组件**:
- `AddIgnoreLayoutSafeAreaBundle`: 容器在布局算法中主动调用
- `IsExpandConstraintNeeded`: 容器判断是否需要扩展约束
- 容器自己决定哪些子组件需要 ignore 处理

**特点**:
- 容器**主动控制** ignore 机制
- 在布局算法中精确控制子组件的测量时机
- 高度定制化，适应复杂的布局场景

**实现位置**: 
- 容器布局算法（如 Flex、Box、GridRow）
- `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/flex/flex_layout_algorithm.cpp`
- `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/layout/box_layout_algorithm.cpp`

---

### 两种机制的对比

| 特性 | 非侵入式Pattern Hook | 容器主动打包 |
|:-----|:------------------|:------------------|
| **控制方式** | Pattern Hook 自动处理 | 容器主动调用 |
| **侵入性** | 无需修改布局算法 | 需要在布局算法中集成 |
| **灵活性** | 自动化，适用于大多数场景 | 高度定制，适用于复杂场景 |
| **触发位置** | `frame_node.cpp` 的 PreMeasure | 布局算法内部 |
| **判断逻辑** | `ChildPreMeasureHelper` + `PredictMeasureResult` | `IsExpandConstraintNeeded` |
| **适用容器** | 所有容器 | Flex、Box、GridRow 等特定容器 |

---

## 公共执行流程

### FlushLayoutTask 的嵌套循环设计

**位置**: `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/pipeline_ng/ui_task_scheduler.cpp:129-191`

```cpp
void UITaskScheduler::FlushLayoutTask(bool forceUseMainThread)
{
    auto dirtyLayoutNodes = std::move(dirtyLayoutNodes_);
    PageDirtySet dirtyLayoutNodesSet(dirtyLayoutNodes.begin(), dirtyLayoutNodes.end());

    for (auto&& node : dirtyLayoutNodesSet) {
        // 1. 处理一个 dirty node（代表一整棵子树）
        node->CreateLayoutTask(forceUseMainThread);

        // 2. 立刻处理这棵子树"抖下来"的 bundles
        while (!ignoreLayoutSafeAreaBundles_.empty() || !traverseSafeAreaBundles_.empty()) {
            FlushPostponedLayoutTask(forceUseMainThread);
        }
    }
}
```

---

#### for-while-for 嵌套循环的设计原因

**为什么是嵌套循环，而非顺序执行？**

每个 dirty node 的 layoutTask 代表处理了一整棵子树。在这棵子树的 Measure 过程中，某些节点因为需要 ignoreLayoutSafeArea 而被"抖下来"，需要延迟到所有祖先布局完成后执行。

**关键理解**：
- 若不使用 ignoreLayoutSafeArea，这些被"抖下来"的节点本该在**下一个 dirty node 的 layoutTask 之前**执行（按 DFS 顺序）
- 使用延迟布局时，为了**保证节点间的相对执行顺序尽可能不变，减少兼容性影响**，这些 bundles 也应该在下一个 dirty node 的 layoutTask 之前执行
- 因此，每处理完一个 dirty node，就立即处理它产生的 bundles

**为什么是 while（嵌套）？**

处理 bundles 时，意味着要处理一批子树的子树。这些子树在 Measure 时同样可能"抖下来"一批新的 bundles。因此需要 while 循环持续处理，直到没有新的 bundles 产生。

---

### FlushPostponedLayoutTask 公共执行

**位置**: `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/pipeline_ng/ui_task_scheduler.cpp:193-226`

这是两种提交 Bundle 机制的**公共执行入口**。

```cpp
void UITaskScheduler::FlushPostponedLayoutTask(bool forceUseMainThread)
{
    // 1. 处理扩散标脏产生的 bundles
    auto traverseSafeAreaBundles = std::move(traverseSafeAreaBundles_);
    for (auto&& rit = traverseSafeAreaBundles.rbegin();
         rit != traverseSafeAreaBundles.rend(); ++rit) {
        auto& container = *rit;
        if (!container || container->IsInDestroying()) {
            continue;
        }
        const auto& layoutProperty = container->GetLayoutProperty();
        CHECK_NULL_CONTINUE(layoutProperty);
        // 标记 container dirty，防止 skipMeasure 或 skipLayout
        layoutProperty->UpdatePropertyChangeFlag(PROPERTY_UPDATE_MEASURE);
        container->CreateLayoutTask(forceUseMainThread,
            LayoutType::TRAVERSE_FOR_IGNORE);
    }

    // 2. 处理 ignoreLayoutSafeArea 产生的 bundles
    //    （来自非侵入式Hook和容器主动打包两种机制）
    auto ignoreLayoutSafeAreaBundles = std::move(ignoreLayoutSafeAreaBundles_);
    for (auto&& bundle = ignoreLayoutSafeAreaBundles.rbegin();
         bundle != ignoreLayoutSafeAreaBundles.rend(); ++bundle) {

        // 为子节点创建 MEASURE_FOR_IGNORE 任务
        for (auto&& node : bundle->first) {
            if (!node || node->IsInDestroying()) {
                continue;
            }
            node->CreateLayoutTask(forceUseMainThread,
                LayoutType::MEASURE_FOR_IGNORE);
        }

        // 为容器创建 LAYOUT_FOR_IGNORE 任务
        auto&& container = bundle->second;
        if (!container || container->IsInDestroying()) {
            continue;
        }
        if (!container->PostponedTaskForIgnore()) {
            container->CreateLayoutTask(forceUseMainThread,
                LayoutType::LAYOUT_FOR_IGNORE);
        }
    }
}
```

#### PostponedTaskForIgnore 分支：区分两种提交机制

`if (!container->PostponedTaskForIgnore())` 这个判断是区分两种提交 Bundle 机制的关键分支：

**非侵入式Pattern Hook机制**：
- 容器的 Pattern 实现了 `PostponedTaskForIgnore` 虚函数
- 在该函数内部完成子组件的 `ignoreAdjust` 应用
- 返回 `true`，表示已完成布局调整，**不需要**额外的 `LAYOUT_FOR_IGNORE` 任务

**容器主动打包机制**：
- 容器没有实现 `PostponedTaskForIgnore`（或返回 false）
- 需要创建 `LAYOUT_FOR_IGNORE` 任务来触发布局调整
- 在 `LAYOUT_FOR_IGNORE` 任务中通过组件算法的定制化实现来应用调整

**源码位置**: `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/base/frame_node.cpp:5425-5454`

---

#### 反向遍历 bundles 的原因

**为什么要反向遍历（rbegin）？**

在同一棵子树构造 bundles 时，因为 DFS 遍历顺序：
- **更深的侄节点**（侄辈）先抛出 bundle 入队
- **更浅的叔节点**（叔辈）后抛出 bundle入队

**依赖关系**：
- 侄辈需要延伸布局 → 依赖祖先需要先布局完成 → 依赖叔辈布局完成
- 因此**后入队的需要先执行**
- 所以需要反向遍历 bundles

**示例**：
```
Container (祖父辈)
  ├─ Child1 (叔辈，有ignore)
  └─ Child2 (父亲)
      └─ Grandchild (侄辈，有ignore)

DFS Measure 顺序：
1. Grandchild::PreMeasure → 返回 true，入队 bundle1（侄辈）
2. Child1::PreMeasure → 返回 true，入队 bundle2（叔辈）

bundle 队列：[bundle1, bundle2]
执行顺序（反向遍历）：bundle2 → bundle1
（先执行叔辈 Child1，再执行侄辈 Grandchild，满足依赖关系）
```

---

### 非侵入式Pattern Hook的完整流程

#### Measure 内部的处理

```
FrameNode::Measure
│
├─ PreMeasure 检测 (frame_node.cpp:5595)
│   └─ if (PreMeasure(parentConstraint)) { return; }
│       └─ FrameNode::PreMeasure (frame_node.cpp:5355-5367)
│           └─ 父组件::ChildPreMeasureHelper
│               ├─ 检查 Pattern->ChildPreMeasureHelperEnabled()
│               ├─ 检查 child->IsIgnoreOptsValid()
│               ├─ Pattern->ChildPreMeasureHelper() 或
│               │  PredictMeasureResult()
│               └─ 返回 true/false
│                   │
│                   ├─ 返回 true：跳过本次 Measure
│                   └─ 返回 false：继续执行
│
├─ [如果不跳过] 正常 Measure 执行
│   └─ 遍历子组件，对每个子组件：
│       └─ child->Measure(layoutConstraint)
│
└─ Measure 结束时：PostTaskForIgnore (frame_node.cpp:5670)
    └─ PostBundle()
        └─ AddIgnoreLayoutSafeAreaBundle()
            └─ 添加到全局队列
```

**源码位置**:
- PreMeasure: `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/base/frame_node.cpp:5355-5367`
- ChildPreMeasureHelper: `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/base/frame_node.cpp:5369-5397`
- PostTaskForIgnore: `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/base/frame_node.cpp:5670`

---

### 容器主动打包的完整流程

#### 容器布局算法中的处理

```
容器布局算法的 Measure 方法
│
└─ 遍历子组件
    │
    ├─ 对每个子组件：
    │   ├─ 检查 IsExpandConstraintNeeded()
    │   │
    │   ├─ 如果返回 true：
    │   │   └─ 添加到 bundle.first
    │   │       SetDelaySelfLayoutForIgnore()
    │   │       SetParentLayoutConstraint()
    │   │       continue;  // 本次跳过 Measure
    │   │
    │   └─ 如果返回 false：
    │       └─ child->Measure(layoutConstraint)  // 正常测量
    │
    └─ 遍历结束后：
        └─ 如果 bundle 不为空：
            └─ context->AddIgnoreLayoutSafeAreaBundle(std::move(bundle))
                └─ 添加到全局队列
```

**通用实现模式**:

```cpp
void ContainerLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto context = host->GetContext();
    IgnoreLayoutSafeAreaBundle bundle;

    for (const auto& child : children) {
        auto childNode = child->GetHostNode();

        // 检查是否需要 ignore 处理
        if (childNode && childNode->GetLayoutProperty() &&
            childNode->GetLayoutProperty()->IsExpandConstraintNeeded()) {

            // 添加到 bundle，本次跳过 Measure
            bundle.first.emplace_back(childNode);
            child->SetDelaySelfLayoutForIgnore();
            child->GetGeometryNode()->SetParentLayoutConstraint(layoutConstraint);
            continue;
        }

        // 正常测量
        child->Measure(layoutConstraint);
    }

    // 提交 bundle
    if (context && !bundle.first.empty()) {
        host->SetDelaySelfLayoutForIgnore();
        bundle.second = host;
        context->AddIgnoreLayoutSafeAreaBundle(std::move(bundle));
    }
}
```

**源码位置**:
- Box实现: `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/layout/box_layout_algorithm.cpp:203-229`
- Flex实现: `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/flex/flex_layout_algorithm.cpp`
- IsExpandConstraintNeeded: `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/property/layout_property.cpp:1166-1181`

---

## 关键机制

### 延迟布局任务机制

**ignoreLayoutSafeAreaBundles_** 是延迟布局的核心数据结构。

**来源**：
- 非侵入式Pattern Hook机制：`PostTaskForIgnore` → `AddIgnoreLayoutSafeAreaBundle`
- 容器主动打包机制：布局算法直接调用 `AddIgnoreLayoutSafeAreaBundle`

**处理**：
- `FlushPostponedLayoutTask` 反向遍历并执行
- 为子节点创建 `MEASURE_FOR_IGNORE` 任务
- 为容器创建 `LAYOUT_FOR_IGNORE` 任务

**目的**：
- 将需要 ignoreLayoutSafeArea 的节点测量延迟到所有祖先布局完成后
- 保证能准确计算 `GetAccumulatedSafeAreaExpand`

**源码位置**:
- AddIgnoreLayoutSafeAreaBundle: `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/pipeline_ng/ui_task_scheduler.cpp:58-66`

---

### 扩散标脏机制

#### 问题场景

原有的布局剪枝逻辑：父组件约束不变时，子组件会直接 skip measure。

ignoreLayoutSafeArea 引入的新场景：**父组件约束不变时，子组件感知到的全局可延伸范围依然会变化**。

**示例**：
```
Stack (祖父，safeAreaPadding 从 {top:0} 变为 {top:20})
  └─ Column (父亲，固定高度 500，无 ignore)
      └─ Scroll (当前关注的组件，ignore: TOP)
          └─ List (无 ignore)

当 Stack 的 safeAreaPadding 发生变化时：
  - Stack {top:0} → {top:20}
  - Column 的约束不变（仍然是 500 高度）
  - 但 Scroll 感知到的全局可延伸范围已变化
    - 之前：只能向上延伸 0
    - 之后：可以向上延伸 20
  - List 的布局需要调整（可滚动范围变化）

原有剪枝逻辑会错误地跳过 Scroll 和 List 的测量。
```

#### 解决方案

**位置**: `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/base/frame_node.cpp:5612`

```cpp
if (isConstraintNotChanged_) {
    if (!CheckNeedForceMeasureAndLayout()) {
        TraverseForIgnore();  // 扩散标脏
        // skip measure
    }
}
```

**工作机制**:

1. **子树 ignore 计数**：
   ```cpp
   void FrameNode::TraverseForIgnore()
   {
       if (!SubtreeWithIgnoreChild() ||
           (layoutProperty_ && layoutProperty_->IsIgnoreOptsValid())) {
           return;  // 子树无 ignore 子节点，或自己有 ignore 选项
       }

       std::vector<RefPtr<FrameNode>> effectedNodes;
       int recheckCount = 0;
       TraverseSubtreeToPostBundle(effectedNodes, recheckCount);

       // 更新 ignore 计数
       if (recheckCount != subtreeIgnoreCount_) {
           UpdateIgnoreCount(recheckCount - subtreeIgnoreCount_);
       }

       if (!effectedNodes.empty()) {
           PostBundle({}, true);  // postByTraverse = true
       }
   }
   ```

2. **递归遍历子树**：
   - 递归遍历子树，查找有 ignore 选项的节点
   - 收集需要重新布局的节点
   - 更新 subtreeIgnoreCount_

3. **指导剪枝**：
   - `subtreeIgnoreCount_`：子树中 ignore 节点的数量
   - 当这个计数变化时，说明子树中有节点需要重新布局
   - 即使父组件约束不变，也要遍历子树

**源码位置**:
- TraverseForIgnore: `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/base/frame_node.cpp:5463-5482`
- TraverseSubtreeToPostBundle: `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/base/frame_node.cpp:5484-5509`

#### 两种 Bundle 的区别

| 类型 | 存储位置 | 生成方式 | 用途 |
|:-----|:---------|:---------|:-----|
| **ignoreLayoutSafeAreaBundles_** | ignore 队列 | Measure 内部检测（两种机制） | 延迟布局任务 |
| **traverseSafeAreaBundles_** | 遍历队列 | TraverseForIgnore 遍历子树 | 扩散标脏机制 |

---

### 累加延伸距离计算

ignoreLayoutSafeArea 机制通过调用 `GetAccumulatedSafeAreaExpand` 来计算组件可以延伸的距离。

**机制说明**：

`GetAccumulatedSafeAreaExpand` 提供累加安全区域延伸的能力，递归向上遍历组件树，计算从当前节点到根节点的所有 safeAreaPadding 累加值。这个机制不仅服务于 ignoreLayoutSafeArea，也是通用属性 `safeAreaExpand` 的底层实现。

**为什么需要延迟布局？**

要准确计算累加延伸距离，必须满足以下条件：
- 所有祖先组件的 Measure 已完成（才能获取正确的 safeAreaPadding）
- 所有祖先组件的 Layout 已完成（才能获取正确的位置和尺寸）
- 递归向上遍历时能访问到完整的祖先信息链

这正是 ignoreLayoutSafeArea 需要使用后抛任务调度的根本原因：只有等所有祖先布局完成后，才能调用 `GetAccumulatedSafeAreaExpand` 获得准确的延伸距离。

**GetAccumulatedSafeAreaExpand 支持 ignore 选项**：

```cpp
// layout_wrapper.cpp:422-470
ExpandEdges LayoutWrapper::GetAccumulatedSafeAreaExpand(
    bool isSelf, const IgnoreLayoutSafeAreaOpts& opts)
{
    // opts 包含要忽略的类型和边
    // 在递归向上遍历时使用 opts 过滤安全区域

    // 1. 尝试缓存
    if (AccumulateExpandCacheHit(totalExpand, innerSpace,
        adjustingRect, opts.type)) {
        return totalExpand;
    }

    // 2. 解析父组件 safeAreaPadding
    ParseSafeAreaPaddingSides(parentSafeAreaPadding,
        parentInnerSpace, adjustingRect, rollingExpand);

    // 3. 检查停止条件
    if (startPoint != StartPoint::FROM_SELF &&
        hostMargin.AllSidesFilled(true)) {
        return totalExpand;
    }

    // 4. 执行累加（传入 ignore 类型）
    GetAccumulatedSafeAreaExpandHelper(
        adjustingRect, totalExpand, false, opts.type);

    // 5. 设置缓存（仅 SYSTEM 类型）
    if (IsIgnoreTypeTrivial(opts.type) && !isScrollableAxis_) {
        geometryNode->SetAccumulatedSafeAreaEdges(totalExpand);
    }

    return totalExpand;
}
```

**在 PostponedTaskForIgnore 中调用**：

```cpp
// frame_node.cpp:5425-5454
bool FrameNode::PostponedTaskForIgnore()
{
    for (auto&& node : delayLayoutChildren_) {
        // 1. 获取 ignore 选项
        IgnoreLayoutSafeAreaOpts options = { ... };
        auto property = node->GetLayoutProperty();
        if (property) {
            options = property->GenIgnoreOpts();
        }

        // 2. 调用 GetAccumulatedSafeAreaExpand（强依赖）
        ExpandEdges sae = node->GetAccumulatedSafeAreaExpand(
            false, options);

        // 3. 处理 RTL
        bool isRtl = false;
        auto containerProperty = GetLayoutProperty();
        if (containerProperty) {
            isRtl = containerProperty->DecideMirror();
        }
        auto selfIgnoreAdjust = isRtl ? sae.MirrorOffset() : sae.Offset();

        // 4. 应用调整
        auto geometryNode = node->GetGeometryNode();
        if (geometryNode) {
            geometryNode->SetIgnoreAdjust(selfIgnoreAdjust);
            auto offset = geometryNode->GetMarginFrameOffset();
            offset -= selfIgnoreAdjust;
            geometryNode->SetMarginFrameOffset(offset);
        }
    }

    delayLayoutChildren_.clear();
    return true;
}
```

**关键点**：
- 此时所有祖先的布局已完成，可以准确计算累加延伸
- 应用 `ignoreAdjust` 到子组件的 GeometryNode

**源码位置**:
- GetAccumulatedSafeAreaExpand: `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/layout/layout_wrapper.cpp:422-470`
- PostponedTaskForIgnore: `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/base/frame_node.cpp:5425-5454`

---

## 数据结构

### IgnoreLayoutSafeAreaBundle

**定义**: 延迟布局任务包

```cpp
using IgnoreLayoutSafeAreaBundle = 
    std::pair<std::vector<RefPtr<FrameNode>>, RefPtr<FrameNode>>;
//                     ^^^^^^                        ^^^^^^
//                     需要延迟的子节点              容器节点
```

**源码位置**: `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/base/frame_node.h:120`

---

### IgnoreLayoutSafeAreaOpts

**定义**: ignore 选项

```cpp
struct IgnoreLayoutSafeAreaOpts {
    uint8_t type;   // SafeAreaType: SYSTEM, KEYBOARD, CUSTOM
    uint8_t edges;  // SafeAreaEdges: TOP, BOTTOM, START, END
};
```

**源码位置**: `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/property/layout_property.h:180-188`

---

### LayoutType

**定义**: 布局任务类型

```cpp
enum class LayoutType {
    MEASURE,             // 正常测量
    LAYOUT,              // 正常布局
    MEASURE_FOR_IGNORE,  // 为 ignore 延迟测量
    LAYOUT_FOR_IGNORE,   // 为 ignore 延迟布局
    TRAVERSE_FOR_IGNORE  // 遍历标脏
};
```

**源码位置**: `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/base/frame_node.h:102-108`

---

## 典型场景

### 场景1：Scroll 突破顶部安全区域

**需求**: Scroll 组件延伸到状态栏区域

```typescript
Column() {
  Scroll() {
    List() {
      ForEach(data, (item) => {
        ListItem() { Text(item) }
      })
    }
  }
  .ignoreLayoutSafeArea({
    type: SafeAreaType.SYSTEM,
    edges: SafeAreaEdges.TOP
  })
}
```

**执行流程**：

```
1. FlushLayoutTask 开始
   └─ Column::CreateLayoutTask
       └─ Column::Measure
           └─ Scroll::PreMeasure
               └─ Column::ChildPreMeasureHelper (非侵入式Hook)
                   ├─ 检查 IsIgnoreOptsValid() → true
                   ├─ PredictMeasureResult 检查
                   │   └─ layoutWeight，无法预测
                   └─ 返回 true（需要后抛）

2. Scroll::Measure 本次跳过

3. Column::Measure 结束时：PostTaskForIgnore
   └─ AddIgnoreLayoutSafeAreaBundle
       └─ 添加到全局队列

4. FlushLayoutTask 内部的 while 循环
   └─ FlushPostponedLayoutTask
       └─ Scroll::Measure (MEASURE_FOR_IGNORE)
           └─ GetAccumulatedSafeAreaExpand(opts: {type:SYSTEM, edges:TOP})
               ├─ 递归向上遍历祖先（此时 Column 已完成）
               ├─ 过滤 TOP 边的 safeAreaPadding
               └─ 计算可延伸距离

5. Scroll::Layout (LAYOUT_FOR_IGNORE)
   └─ PostponedTaskForIgnore
       └─ 应用 ignore 调整
           └─ Scroll 延伸到状态栏区域
```

**结果**：
- Scroll 的布局范围延伸到状态栏区域
- Scroll 的内容可以显示在状态栏下方
- 只有一次 Measure（MEASURE_FOR_IGNORE）

---

### 场景2：嵌套 ignore 层次化过滤

**需求**: 父组件忽略顶部，子组件忽略底部

```typescript
Column() {
  Column() {
    Text('Inner Content')
  }
  .ignoreLayoutSafeArea({
    type: SafeAreaType.SYSTEM,
    edges: SafeAreaEdges.TOP
  })
}
.ignoreLayoutSafeArea({
  type: SafeAreaType.SYSTEM,
  edges: SafeAreaEdges.BOTTOM
})
```

**累加逻辑**：

```
内层 Column 的 GetAccumulatedSafeAreaExpand 计算：
──────────────────────────────────────────────

输入：opts = {type: SYSTEM, edges: TOP}

向上遍历：
  1. 内层 Column 自己
     └─ safeAreaPadding = {top: 0, bottom: 0}
     └─ 过滤 TOP → 无延伸

  2. 外层 Column
     └─ safeAreaPadding = {top: 20, bottom: 30}
         （假设系统 safeArea 是 top:20, bottom:30）
     └─ 过滤 TOP（opts.edges 包含 TOP）
         ├─ TOP 被忽略
         └─ BOTTOM 不被忽略（opts.edges 不包含 BOTTOM）
     └─ rollingExpand = {bottom: 30}

  3. 系统根节点
     └─ safeAreaPadding = {top: 20, bottom: 30}
     └─ 过滤 TOP → BOTTOM 累加

结果：totalExpand = {top: 0, bottom: 30, left: 0, right: 0}
```

---

### 场景3：键盘弹出动态调整

**需求**: 键盘弹出时，只有 Scroll 响应

```typescript
Column() {
  Text('Fixed Header').height(100)

  Scroll() {
    // 内容
  }
  .layoutWeight(1)
  .ignoreLayoutSafeArea({
    type: SafeAreaType.KEYBOARD,
    edges: SafeAreaEdges.BOTTOM
  })

  Text('Fixed Footer').height(50)
}
```

**执行时序**：

```
键盘弹出前：
──────────────
1. Column::Measure
   ├─ Header::Measure → height: 100
   ├─ Scroll::PreMeasure
   │   └─ 无键盘，无需后抛
   └─ Footer::Measure → height: 50

2. Scroll 测量：剩余空间

键盘弹出：
──────────────
1. SafeAreaManager 检测到键盘变化
   └─ 触发 OnSafeAreaChanged
       └─ 标记相关节点 dirty

2. FlushLayoutTask 开始
   └─ Column::CreateLayoutTask
       └─ Column::Measure
           ├─ Header::Measure → height: 100
           ├─ Scroll::PreMeasure
           │   └─ ChildPreMeasureHelper
           │       ├─ 检测到 ignoreLayoutSafeArea(KEYBOARD)
           │       ├─ PredictMeasureResult → 无法预测
           │       └─ 返回 true（需要后抛）
           └─ Footer::Measure → height: 50

3. Scroll::Measure 本次跳过

4. Column::Measure 结束时：PostTaskForIgnore
   └─ AddIgnoreLayoutSafeAreaBundle

5. FlushLayoutTask 内部的 while 循环
   └─ FlushPostponedLayoutTask
       └─ Scroll::Measure (MEASURE_FOR_IGNORE)
           └─ GetAccumulatedSafeAreaExpand(opts: {type:KEYBOARD})
               └─ 过滤 KEYBOARD 类型
                   └─ 不累加键盘区域

6. Scroll::Layout (LAYOUT_FOR_IGNORE)
   └─ 应用 ignore 调整
       └─ Scroll 延伸到键盘区域

结果：
- Header 和 Footer 位置不变
- Scroll 延伸到键盘区域，不被挤压
- 用户可以在键盘弹出时滚动内容
```

---

### 场景4：容器使用主动打包高度定制化控制

**需求**: 容器使用主动打包机制精确控制子组件的 ignore 行为

```typescript
Flex({ direction: FlexDirection.Column }) {
  Text('Item 1')
    .ignoreLayoutSafeArea({
      type: SafeAreaType.SYSTEM,
      edges: SafeAreaEdges.TOP
    })

  Text('Item 2')
    .layoutWeight(1)

  Text('Item 3')
}
```

**执行流程**：

```
Flex::CreateLayoutTask
└─ Flex::Measure
    └─ 遍历 layoutPolicyChildren_

        对于 Item 1：
          ├─ IsExpandConstraintNeeded() → true
          ├─ 添加到 bundle.first
          ├─ SetDelaySelfLayoutForIgnore()
          └─ continue;  // 本次跳过 Measure

        对于 Item 2：
          └─ 正常 Measure

        对于 Item 3：
          └─ 正常 Measure

    └─ 遍历结束后：
        └─ context->AddIgnoreLayoutSafeAreaBundle(bundle)

FlushLayoutTask 内部的 while 循环
└─ FlushPostponedLayoutTask
    ├─ Item 1::Measure (MEASURE_FOR_IGNORE)
    │   └─ GetAccumulatedSafeAreaExpand(opts)
    │       └─ 计算可延伸距离
    │
    └─ Flex::Layout (LAYOUT_FOR_IGNORE)
        └─ PostponedTaskForIgnore
            └─ 应用 ignore 调整到 Item 1
```

---

## 性能优化

### 避免过深的 traverse

**问题**: TraverseForIgnore 可能遍历很深的子树

**优化**:
- 使用 `subtreeIgnoreCount_` 指导剪枝
- 当计数为 0 时，直接跳过遍历

**源码位置**: `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/base/frame_node.cpp:5463-5482`

---

### 缓存累加结果

**问题**: 每次都递归向上遍历计算累加延伸

**优化**:
- 使用 `AccumulateExpandCacheHit` 检查缓存
- 仅对 SYSTEM 类型使用缓存（KEYBOARD 类型动态变化）

**源码位置**: `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/layout/layout_wrapper.cpp:422-470`

---

### 合理使用 PreMeasure

**问题**: 不必要的 PreMeasure 调用

**优化**:
- 检查 `ChildPreMeasureHelperEnabled()` 返回值
- 检查 `IsIgnoreOptsValid()` 返回值
- 使用 `PredictMeasureResult` 过滤不需要延迟的情况

**源码位置**: `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/base/frame_node.cpp:5369-5397`

---

## 源码位置汇总

### 核心文件

| 文件 | 位置 | 说明 |
|:-----|:-----|:-----|
| `frame_node.cpp` | `frameworks/core/components_ng/base/` | PreMeasure, PostTaskForIgnore, TraverseForIgnore |
| `frame_node.h` | `frameworks/core/components_ng/base/` | IgnoreLayoutSafeAreaBundle 定义 |
| `ui_task_scheduler.cpp` | `frameworks/core/pipeline_ng/` | FlushLayoutTask, FlushPostponedLayoutTask |
| `layout_wrapper.cpp` | `frameworks/core/components_ng/layout/` | GetAccumulatedSafeAreaExpand, PredictMeasureResult |
| `layout_property.cpp` | `frameworks/core/components_ng/property/` | IsExpandConstraintNeeded, UpdateIgnoreLayoutSafeAreaOpts |
| `box_layout_algorithm.cpp` | `frameworks/core/components_ng/layout/` | 容器主动打包示例 |
| `flex_layout_algorithm.cpp` | `frameworks/core/pattern/flex/` | Flex 容器主动打包 |
| `js_view_abstract.cpp` | `frameworks/bridge/declarative_frontend/engine/` | ArkTS API 入口 |

### 关键函数索引

| 函数 | 文件:行号 | 说明 |
|:-----|:---------|:-----|
| `PreMeasure` | frame_node.cpp:5355-5367 | 预测量入口 |
| `ChildPreMeasureHelper` | frame_node.cpp:5369-5397 | 父组件辅助检测 |
| `CollectDelayMeasureChild` | frame_node.cpp:5399-5405 | Measure 内部收集 |
| `PostTaskForIgnore` | frame_node.cpp:5407-5413, 5670 | Measure 结束时调用 |
| `PostBundle` | frame_node.cpp:5415-5423 | 打包 bundle |
| `PostponedTaskForIgnore` | frame_node.cpp:5425-5454 | 应用延迟布局调整 |
| `TraverseForIgnore` | frame_node.cpp:5463-5482 | 遍历子树扩散标脏 |
| `TraverseSubtreeToPostBundle` | frame_node.cpp:5484-5509 | 递归收集子树节点 |
| `FlushLayoutTask` | ui_task_scheduler.cpp:129-191 | 主循环 |
| `FlushPostponedLayoutTask` | ui_task_scheduler.cpp:193-226 | 公共执行入口 |
| `AddIgnoreLayoutSafeAreaBundle` | ui_task_scheduler.cpp:58-66 | 添加到调度队列 |
| `GetAccumulatedSafeAreaExpand` | layout_wrapper.cpp:422-470 | 获取累加延伸 |
| `PredictMeasureResult` | layout_wrapper.cpp:580-610 | 预测测量结果 |
| `IsExpandConstraintNeeded` | layout_property.cpp:1166-1181 | 检查是否需要扩展约束 |
| `UpdateIgnoreLayoutSafeAreaOpts` | layout_property.cpp:1143-1164 | 更新 ignore 选项 |
| `JsIgnoreLayoutSafeArea` | js_view_abstract.cpp:9414-9445 | ArkTS API 入口 |

---

## 相关文档

- [Layout Framework Context](../kb/architecture/layout-framework.md) - 布局框架机制
- [Safe Area Mechanism Knowledge Base](../layout/Safe_Area_Mechanism_Knowledge_Base.md) - 安全区域机制
- [IGNORE_LAYOUT_SAFE_AREA_GUIDE.md](../../frameworks/core/components_ng/IGNORE_LAYOUT_SAFE_AREA_GUIDE.md) - 开发者指南
