# LazyForEach 组件知识库

**版本**: 1.0
**更新时间**: 2026-02-05
**源码分支**: master
**作者**: Claude Code

---

## 目录

- [概述](#概述)
- [完整调用链](#完整调用链)
- [目录结构](#目录结构)
- [类继承关系](#类继承关系)
- [核心功能](#核心功能)
  - [IDataSource 接口](#idatasource-接口)
  - [懒加载机制](#懒加载机制)
  - [缓存策略](#缓存策略)
  - [数据变化通知](#数据变化通知)
- [LazyForEachBuilder 算法](#lazyforeachbuilder-算法)
- [布局算法](#布局算法)
- [完整 API 清单](#完整-api-清单)
- [IDataSource 接口定义](#idatasource-接口定义)
- [使用示例](#使用示例)
- [调试指南](#调试指南)
- [最佳实践](#最佳实践)
- [性能优化](#性能优化)
- [Arkoala 前端支持](#arkoala-前端支持)

---

## 概述

### 组件定位

**LazyForEach** 是 OpenHarmony ArkUI 框架中用于**懒加载循环渲染**的组件。它通过按需渲染和缓存机制，高效处理大规模数据集（数千到数万项）的展示。

### 核心特性

- **按需渲染**: 仅渲染可见区域 + 预测区域的组件
- **数据源驱动**: 通过 IDataSource 接口实现数据变化通知
- **缓存管理**: 支持可配置的缓存策略，优化滚动性能
- **预测性渲染**: 利用空闲时间预渲染即将显示的组件
- **内存优化**: 自动回收远离可见区域的组件
- **无限滚动**: 支持动态加载数据的分页场景

---

## 完整调用链

### ArkTS → Pattern Node → Builder 调用流程

```
┌─────────────────────────────────────────────────────────────────┐
│  ArkTS 前端代码                                                  │
│  LazyForEach({ dataSource: this.dataSource })                   │
└─────────────────────────────────────────────────────────────────┘
                            ↓
┌─────────────────────────────────────────────────────────────────┐
│  Declarative Frontend (声明式前端)                               │
│  frameworks/bridge/declarative_frontend/jsview/models/          │
│    lazy_for_each_model_impl.cpp                                 │
│    - LazyForEachModelImpl::Create()                             │
│    - 创建 LazyForEachComponent + IDataSource 绑定                │
└─────────────────────────────────────────────────────────────────┘
                            ↓
┌─────────────────────────────────────────────────────────────────┐
│  Pattern Node (语法节点层)                                       │
│  frameworks/core/components_ng/syntax/lazy_for_each_node.cpp   │
│    - LazyForEachNode::GetOrCreateLazyForEachNode()              │
│    - LazyForEachNode::GetFrameChildByIndex()                    │
│    - LazyForEachNode::UpdateLazyForEachItems()                  │
└─────────────────────────────────────────────────────────────────┘
                            ↓
┌─────────────────────────────────────────────────────────────────┐
│  LazyForEachBuilder (构建器层)                                   │
│  frameworks/core/components_ng/syntax/lazy_for_each_builder.cpp│
│    - LazyForEachBuilder::GetChildByIndex()                      │
│    - LazyForEachBuilder::OnDataReloaded/Added/Deleted/Changed() │
│    - LazyForEachBuilder::PostIdleTask()                         │
└─────────────────────────────────────────────────────────────────┘
                            ↓
┌─────────────────────────────────────────────────────────────────┐
│  渲染显示                                                         │
│  - 按需创建 FrameNode                                            │
│  - Measure/Layout 计算                                           │
│  - RenderNode 绘制                                              │
└─────────────────────────────────────────────────────────────────┘
```

### 关键调用路径

**源码位置**：
- 前端桥接: `frameworks/bridge/declarative_frontend/jsview/models/lazy_for_each_model_impl.cpp`
- Pattern Node: `frameworks/core/components_ng/syntax/lazy_for_each_node.cpp`
- Builder: `frameworks/core/components_ng/syntax/lazy_for_each_builder.cpp`

---

## 目录结构

### 源码文件组织

```
frameworks/core/components_ng/syntax/
├── for_each_base_node.h                 # ForEach 基类（77 行）
├── lazy_for_each_node.h                 # LazyForEachNode 头文件
├── lazy_for_each_node.cpp               # LazyForEachNode 实现（35568 行）
├── lazy_for_each_builder.h              # LazyForEachBuilder 头文件
├── lazy_for_each_builder.cpp            # LazyForEachBuilder 实现（62289 行）
└── lazy_for_each_model_ng.cpp           # Model 层接口

frameworks/bridge/declarative_frontend/
├── jsview/models/
│   ├── lazy_for_each_model_impl.h       # 前端 Model 接口
│   └── lazy_for_each_model_impl.cpp     # 前端 Model 实现
└── ark_node/types/
    └── lazy_for_each.d.ts               # TypeScript 类型定义
```

### 代码规模

| 文件 | 行数 | 说明 |
|------|------|------|
| lazy_for_each_node.cpp | 35,568 | Pattern Node 实现 |
| lazy_for_each_builder.cpp | 62,289 | Builder 算法实现 |
| lazy_for_each_node.h | ~200 | 接口定义 |
| lazy_for_each_builder.h | ~400 | 接口定义 |
| lazy_for_each_model_impl.cpp | ~150 | 前端桥接 |
| **总计** | **~98,696** | **LazyForEach 完整实现** |

---

## 类继承关系

### 继承体系

```
UINode (frameworks/core/components_ng/base/ui_node.h)
    ↓
ForEachBaseNode (frameworks/core/components_ng/syntax/for_each_base_node.h)
    ↓
LazyForEachNode (frameworks/core/components_ng/syntax/lazy_for_each_node.h)
    ↓
    ├── LazyForEachBuilder (组合关系)
    └── DataChangeListener (接口实现)
```

### LazyForEachNode 类结构

**源码位置**: `lazy_for_each_node.h:42-150`

```cpp
class ACE_EXPORT LazyForEachNode : public ForEachBaseNode,
                                   public V2::DataChangeListener {
public:
    static RefPtr<LazyForEachNode> GetOrCreateLazyForEachNode(
        int32_t nodeId, const RefPtr<LazyForEachBuilder>& forEachBuilder);

    // 核心方法
    void UpdateLazyForEachItems(int32_t newStartIndex, int32_t newEndIndex,
        std::list<std::optional<std::string>>&& nodeIds,
        std::unordered_map<int32_t, std::optional<std::string>>&& cachedItems);

    // 数据变化通知
    void OnDataReloaded() override;
    void OnDataAdded(size_t index) override;
    void OnDataDeleted(size_t index) override;
    void OnDataChanged(size_t index) override;
    void OnDataMoved(size_t from, size_t to) override;

    // 按需创建
    RefPtr<UINode> GetFrameChildByIndex(uint32_t index, bool needBuild,
        bool isCache = false, bool addToRenderTree = false) override;

    // 活动范围
    void DoSetActiveChildRange(int32_t start, int32_t end,
        int32_t cacheStart, int32_t cacheEnd, bool showCache = false) override;

    // 空闲任务
    void PostIdleTask(std::list<int32_t>&& items,
        const std::optional<LayoutConstraintF>& itemConstraint = std::nullopt,
        bool longPredictTask = false);

private:
    RefPtr<LazyForEachBuilder> builder_;  // Builder 实例
    bool isLoop_ = false;                // 是否循环
    bool isActive_ = false;               // 是否激活
};
```

### LazyForEachBuilder 类结构

**源码位置**: `lazy_for_each_builder.h:57-150`

```cpp
class ACE_EXPORT LazyForEachBuilder : public virtual AceType {
public:
    // 获取子组件
    std::pair<std::string, RefPtr<UINode>> GetChildByIndex(
        int32_t index, bool needBuild, bool isCache = false);

    // 数据操作
    void OnDataReloaded();
    bool OnDataAdded(size_t index);
    bool OnDataBulkAdded(size_t index, size_t count);
    RefPtr<UINode> OnDataDeleted(size_t index);
    bool OnDataChanged(size_t index);

    // 数据集变化
    std::pair<int32_t, std::list<std::pair<std::string, RefPtr<UINode>>>>
        OnDatasetChange(std::list<V2::Operation> DataOperations);

    // 缓存管理
    void SetCacheCount(int32_t cacheCount);
    void RecycleItems(int32_t from, int32_t to) override;

    // 虚方法（子类实现）
    virtual int32_t OnGetTotalCount() = 0;
    virtual std::pair<std::string, RefPtr<UINode>> OnGetChildByIndex(
        int32_t index) = 0;

protected:
    std::map<int32_t, LazyForEachChild> cachedItems_;    // 缓存项
    std::map<int32_t, LazyForEachChild> expiringItem_;   // 即将过期项
    int32_t cacheCount_ = 0;                            // 缓存数量
};
```

---

## 核心功能

### IDataSource 接口

#### 接口定义

LazyForEach 通过 IDataSource 接口与数据源交互，实现数据变化通知：

```typescript
interface IDataSource {
  // 获取数据总数
  totalCount(): number;

  // 获取指定索引的数据
  getData(index: number): any;

  // 注册数据变化监听器
  registerDataChangeListener(listener: DataChangeListener): void;

  // 注销数据变化监听器
  unregisterDataChangeListener(listener: DataChangeListener): void;
}

interface DataChangeListener {
  // 数据重新加载
  onDataReloaded(): void;

  // 数据添加
  onDataAdded(index: number): void;

  // 数据删除
  onDataDeleted(index: number): void;

  // 数据变化
  onDataChanged(index: number): void;

  // 数据移动
  onDataMoved(from: number, to: number): void;
}
```

#### IDataSource 实现示例

```typescript
class MyDataSource implements IDataSource {
  private data: Array<Item> = [];
  private listeners: DataChangeListener[] = [];

  constructor(data: Array<Item>) {
    this.data = data;
  }

  totalCount(): number {
    return this.data.length;
  }

  getData(index: number): Item {
    return this.data[index];
  }

  registerDataChangeListener(listener: DataChangeListener): void {
    this.listeners.push(listener);
  }

  unregisterDataChangeListener(listener: DataChangeListener): void {
    const index = this.listeners.indexOf(listener);
    if (index >= 0) {
      this.listeners.splice(index, 1);
    }
  }

  // 数据操作方法
  addData(index: number, item: Item): void {
    this.data.splice(index, 0, item);
    this.listeners.forEach(listener => listener.onDataAdded(index));
  }

  removeData(index: number): void {
    this.data.splice(index, 1);
    this.listeners.forEach(listener => listener.onDataDeleted(index));
  }

  updateData(index: number, item: Item): void {
    this.data[index] = item;
    this.listeners.forEach(listener => listener.onDataChanged(index));
  }
}
```

---

### 懒加载机制

#### 工作原理

LazyForEach 通过**按需创建 + 自动回收**实现懒加载：

```
┌─────────────────────────────────────────────────────────────┐
│  滚动容器                                                      │
│                                                              │
│  ┌─────────────────────────────────────────────────┐        │
│  │  缓存区域                │        │  已销毁的组件            │
│  │  (可选)                    │        │  (内存已释放)            │
│  └─────────────────────────────────────────────────┘        │
└─────────────────────────────────────────────────────────────┘
```

#### 可见区域计算

```cpp
// 源码位置: lazy_for_each_node.cpp
void LazyForEachNode::DoSetActiveChildRange(
    int32_t start, int32_t end,
    int32_t cacheStart, int32_t cacheEnd,
    bool showCache)
{
    // start - end: 可见区域
    // cacheStart - cacheEnd: 缓存区域
    // 仅渲染可见区域 + 缓存区域的组件
}
```

#### 按需创建流程

```
1. 用户滚动
    ↓
2. 计算新的可见区域 (newStartIndex, newEndIndex)
    ↓
3. 调用 UpdateLazyForEachItems()
    ↓
4. 对比新旧可见区域
    ↓
5. 创建新进入可见区域的组件
    ↓
6. 销毁离开可见区域 + 缓存区域的组件
    ↓
7. 标记 Dirty → 触发布局 → 渲染更新
```

**源码位置**: `lazy_for_each_node.cpp` - `UpdateLazyForEachItems()` 方法

---

### 缓存策略

#### 缓存配置

LazyForEach 支持通过 `cachedCount` 参数配置缓存数量：

```typescript
LazyForEach({ dataSource: this.dataSource })
  .cachedCount(5)  // 缓存可见区域外各 5 个组件
```

#### 缓存区域划分

```
┌─────────────────────────────────────────────────────────────┐
│  缓存区域                                  │
│  (cacheStart ~ start)                                         │
│  用途: 减少进入可见区域时的创建开销                           │
└─────────────────────────────────────────────────────────────┘
                            ↓
┌─────────────────────────────────────────────────────────────┐
│  可见区域                                   │
│  (start ~ end)                                               │
│  用途: 用户实际看到的区域                                    │
└─────────────────────────────────────────────────────────────┘
                            ↓
┌─────────────────────────────────────────────────────────────┐
│  缓存区域                                  │
│  (end ~ cacheEnd)                                            │
│  用途: 减少进入可见区域时的创建开销                           │
└─────────────────────────────────────────────────────────────┘
```

#### 缓存管理实现

**源码位置**: `lazy_for_each_builder.cpp`

```cpp
// 缓存项存储
std::map<int32_t, LazyForEachChild> cachedItems_;

// 回收组件
void LazyForEachBuilder::RecycleItems(int32_t from, int32_t to) {
    // 将不在缓存区域的组件移动到 expiringItem_
    // 等待后续清理
}
```

---

### 数据变化通知

#### 变化通知机制

LazyForEach 通过 IDataSource 接口接收数据变化通知：

| 变化类型 | 通知方法 | 处理逻辑 |
|---------|---------|----------|
| 重新加载 | `onDataReloaded()` | 清空所有缓存，重新创建 |
| 新增数据 | `onDataAdded(index)` | 插入位置后的所有组件索引+1 |
| 删除数据 | `onDataDeleted(index)` | 删除位置后的所有组件索引-1 |
| 修改数据 | `onDataChanged(index)` | 更新指定索引的组件 |
| 移动数据 | `onDataMoved(from, to)` | 交换两个位置的组件 |

#### 数据变化处理流程

```
数据源变化
    ↓
IDataSource 通知监听器
    ↓
LazyForEachNode::OnData*() 方法
    ↓
LazyForEachBuilder::OnData*() 方法
    ↓
更新 cachedItems_ 和 expiringItem_
    ↓
标记 Dirty → 触发布局 → 渲染更新
```

**源码位置**:
- Pattern Node: `lazy_for_each_node.h:77-84`
- Builder: `lazy_for_each_builder.cpp` - `OnData*()` 方法

---

## LazyForEachBuilder 算法

### 算法概述

LazyForEachBuilder 是 LazyForEach 的核心算法实现，负责：

1. **按需创建**: 根据索引动态创建组件
2. **缓存管理**: 维护已创建组件的缓存
3. **数据操作**: 处理数据源的增删改操作
4. **索引映射**: 维护数据索引到组件的映射关系

### 核心数据结构

**源码位置**: `lazy_for_each_builder.h:41-56`

```cpp
// 操作信息
typedef struct OperationInfo {
    int32_t changeCount = 0;        // 变化数量
    int32_t fromDiffTo = 0;         // 从哪个索引开始不同
    std::string key;                // 组件键
    RefPtr<UINode> node;            // 组件节点
    bool isDeleting = false;        // 是否删除中
    bool isChanged = false;         // 是否已变化
    bool moveIn = false;            // 是否移入
    bool isExchange = false;        // 是否交换
    std::vector<std::string> extraKey;  // 额外键
} OperationInfo;

// 子组件类型
using LazyForEachChild = std::pair<std::string, RefPtr<UINode>>;  // 键 -> 节点
using LazyForEachCacheChild = std::pair<int32_t, RefPtr<UINode>>; // 索引 -> 节点
```

### GetChildByIndex 算法

**源码位置**: `lazy_for_each_builder.cpp`

```cpp
std::pair<std::string, RefPtr<UINode>> LazyForEachBuilder::GetChildByIndex(
    int32_t index, bool needBuild, bool isCache)
{
    // 1. 检查缓存中是否已有该索引的组件
    auto it = cachedItems_.find(index);
    if (it != cachedItems_.end()) {
        return it->second;  // 返回缓存的组件
    }

    // 2. 如果需要创建，调用虚方法 OnGetChildByIndex
    if (needBuild) {
        auto child = OnGetChildByIndex(index);  // 子类实现
        cachedItems_[index] = child;             // 加入缓存
        return child;
    }

    // 3. 不需要创建且缓存中没有，返回空
    return { "", nullptr };
}
```

### 数据操作算法

#### OnDatasetChange

**源码位置**: `lazy_for_each_builder.cpp:100-101`

```cpp
std::pair<int32_t, std::list<std::pair<std::string, RefPtr<UINode>>>>
LazyForEachBuilder::OnDatasetChange(std::list<V2::Operation> DataOperations)
{
    // 处理批量数据操作
    // 1. 分类操作：添加、删除、移动、修改、交换
    // 2. 逐个执行操作
    // 3. 更新索引映射
    // 4. 返回受影响的组件列表
}
```

#### 索引映射维护

```cpp
// 当在 index 位置插入数据时
void LazyForEachBuilder::OnDataAdded(size_t index) {
    // 将 index 之后的所有缓存项索引 +1
    std::map<int32_t, LazyForEachChild> newCachedItems;
    for (const auto& [idx, child] : cachedItems_) {
        if (static_cast<size_t>(idx) >= index) {
            newCachedItems[idx + 1] = child;
        } else {
            newCachedItems[idx] = child;
        }
    }
    cachedItems_ = std::move(newCachedItems);
}

// 当删除 index 位置的数据时
RefPtr<UINode> LazyForEachBuilder::OnDataDeleted(size_t index) {
    // 1. 找到 index 对应的组件
    auto it = cachedItems_.find(index);
    RefPtr<UINode> deletedNode = (it != cachedItems_.end()) ? it->second.second : nullptr;

    // 2. 将 index 之后的所有缓存项索引 -1
    std::map<int32_t, LazyForEachChild> newCachedItems;
    for (const auto& [idx, child] : cachedItems_) {
        if (static_cast<size_t>(idx) > index) {
            newCachedItems[idx - 1] = child;
        } else if (static_cast<size_t>(idx) < index) {
            newCachedItems[idx] = child;
        }
        // idx == index 的项不加入新缓存（已删除）
    }
    cachedItems_ = std::move(newCachedItems);

    return deletedNode;
}
```

---

## 布局算法

### Measure 流程

```
LazyForEachNode::OnDirtyLayoutWrapperSwap()
    ↓
LayoutWrapper::Measure()
    ↓
遍历可见区域 + 缓存区域的子组件，对每个调用 Measure()
    ↓
计算总尺寸（累加所有可见子组件尺寸）
    ↓
LazyForEachNode 自身的 Measure 结果
```

### Layout 流程

```
LazyForEachNode::OnDirtyLayoutWrapperSwap()
    ↓
LayoutWrapper::Layout()
    ↓
根据子组件顺序，计算每个子组件的位置
    ↓
应用 Offset 到每个子组件
    ↓
LazyForEachNode 自身的 Layout 结果
```

---

## 完整 API 清单

### ArkTS API

#### 基本语法

```typescript
LazyForEach(
  dataSource: IDataSource,
  itemGenerator: (item: any, index: number) => void
): void
```

#### 参数说明

| 参数 | 类型 | 必填 | 说明 |
|------|------|------|------|
| dataSource | `IDataSource` | 是 | 数据源对象，需实现 IDataSource 接口 |
| itemGenerator | `(item, index) => void` | 是 | UI 生成函数 |

#### 修饰符方法

| 方法 | 参数 | 说明 |
|------|------|------|
| cachedCount | `number` | 设置缓存数量（默认 0） |

#### 示例

```typescript
@Entry
@Component
struct LazyForEachExample {
  private dataSource = new MyDataSource([
    { id: 1, name: 'Item 1' },
    { id: 2, name: 'Item 2' },
    // ... 更多数据
  ])

  build() {
    List() {
      LazyForEach(this.dataSource, (item: Item, index: number) => {
        ListItem() {
          Text(`${index}: ${item.name}`)
            .fontSize(16)
        }
      })
    }
    .cachedCount(5)  // 缓存 5 个组件
  }
}
```

### C++ API

#### LazyForEachNode 核心方法

**源码位置**: `lazy_for_each_node.h:46-150`

```cpp
class ACE_EXPORT LazyForEachNode : public ForEachBaseNode {
public:
    // 创建或获取 LazyForEachNode
    static RefPtr<LazyForEachNode> GetOrCreateLazyForEachNode(
        int32_t nodeId, const RefPtr<LazyForEachBuilder>& forEachBuilder);

    // 更新懒加载项
    void UpdateLazyForEachItems(int32_t newStartIndex, int32_t newEndIndex,
        std::list<std::optional<std::string>>&& nodeIds,
        std::unordered_map<int32_t, std::optional<std::string>>&& cachedItems);

    // 数据变化通知
    void OnDataReloaded() override;
    void OnDataAdded(size_t index) override;
    void OnDataDeleted(size_t index) override;
    void OnDataChanged(size_t index) override;
    void OnDataMoved(size_t from, size_t to) override;

    // 按需获取子组件
    RefPtr<UINode> GetFrameChildByIndex(uint32_t index, bool needBuild,
        bool isCache = false, bool addToRenderTree = false) override;

    // 设置活动范围
    void DoSetActiveChildRange(int32_t start, int32_t end,
        int32_t cacheStart, int32_t cacheEnd, bool showCache = false) override;

    // 空闲任务
    void PostIdleTask(std::list<int32_t>&& items,
        const std::optional<LayoutConstraintF>& itemConstraint = std::nullopt,
        bool longPredictTask = false);
};
```

---

## IDataSource 接口定义

### 完整接口

```typescript
/**
 * IDataSource 接口定义
 * LazyForEach 数据源必须实现此接口
 */
interface IDataSource {
  /**
   * 获取数据总数
   * @returns 数据总数
   */
  totalCount(): number;

  /**
   * 获取指定索引的数据
   * @param index 数据索引
   * @returns 数据项
   */
  getData(index: number): Object;

  /**
   * 注册数据变化监听器
   * @param listener 数据变化监听器
   */
  registerDataChangeListener(listener: DataChangeListener): void;

  /**
   * 注销数据变化监听器
   * @param listener 数据变化监听器
   */
  unregisterDataChangeListener(listener: DataChangeListener): void;
}

/**
 * 数据变化监听器接口
 */
interface DataChangeListener {
  /**
   * 数据重新加载
   * 当整个数据集发生变化时调用
   */
  onDataReloaded(): void;

  /**
   * 数据添加
   * @param index 新数据添加的位置
   */
  onDataAdded(index: number): void;

  /**
   * 数据批量添加
   * @param index 新数据添加的起始位置
   * @param count 添加的数据数量
   */
  onDataBulkAdded(index: number, count: number): void;

  /**
   * 数据删除
   * @param index 被删除数据的位置
   */
  onDataDeleted(index: number): void;

  /**
   * 数据批量删除
   * @param index 被删除数据的起始位置
   * @param count 删除的数据数量
   */
  onDataBulkDeleted(index: number, count: number): void;

  /**
   * 数据变化
   * @param index 发生变化的数据位置
   */
  onDataChanged(index: number): void;

  /**
   * 数据移动
   * @param from 数据的原始位置
   * @param to 数据的目标位置
   */
  onDataMoved(from: number, to: number): void;
}
```

---

## 使用示例

### 示例 1: 基本 LazyForEach

```typescript
// 数据项定义
class Item {
  id: number
  name: string

  constructor(id: number, name: string) {
    this.id = id
    this.name = name
  }
}

// 数据源实现
class MyDataSource implements IDataSource {
  private data: Array<Item> = []
  private listeners: DataChangeListener[] = []

  constructor(data: Array<Item>) {
    this.data = data
  }

  totalCount(): number {
    return this.data.length
  }

  getData(index: number): Item {
    return this.data[index]
  }

  registerDataChangeListener(listener: DataChangeListener): void {
    this.listeners.push(listener)
  }

  unregisterDataChangeListener(listener: DataChangeListener): void {
    const index = this.listeners.indexOf(listener)
    if (index >= 0) {
      this.listeners.splice(index, 1)
    }
  }

  // 数据操作方法
  addData(item: Item): void {
    this.data.push(item)
    this.listeners.forEach(listener => listener.onDataAdded(this.data.length - 1))
  }
}

@Entry
@Component
struct BasicLazyForEach {
  private dataSource = new MyDataSource([
    new Item(1, 'Apple'),
    new Item(2, 'Banana'),
    new Item(3, 'Orange'),
    // ... 可以有数千个数据项
  ])

  build() {
    List() {
      LazyForEach(this.dataSource, (item: Item, index: number) => {
        ListItem() {
          Text(`${index}: ${item.name}`)
            .fontSize(16)
            .padding(10)
        }
      })
    }
    .cachedCount(5)
  }
}
```

### 示例 2: 动态数据更新

```typescript
class DynamicDataSource implements IDataSource {
  private data: Array<string> = []
  private listeners: DataChangeListener[] = []

  constructor() {
    // 初始数据
    for (let i = 1; i <= 100; i++) {
      this.data.push(`Item ${i}`)
    }
  }

  totalCount(): number {
    return this.data.length
  }

  getData(index: number): string {
    return this.data[index]
  }

  registerDataChangeListener(listener: DataChangeListener): void {
    this.listeners.push(listener)
  }

  unregisterDataChangeListener(listener: DataChangeListener): void {
    const index = this.listeners.indexOf(listener)
    if (index >= 0) {
      this.listeners.splice(index, 1)
    }
  }

  // 添加数据
  addData(index: number, value: string): void {
    this.data.splice(index, 0, value)
    this.listeners.forEach(listener => listener.onDataAdded(index))
  }

  // 删除数据
  removeData(index: number): void {
    this.data.splice(index, 1)
    this.listeners.forEach(listener => listener.onDataDeleted(index))
  }

  // 修改数据
  updateData(index: number, value: string): void {
    this.data[index] = value
    this.listeners.forEach(listener => listener.onDataChanged(index))
  }

  // 重新加载
  reload(newData: Array<string>): void {
    this.data = newData
    this.listeners.forEach(listener => listener.onDataReloaded())
  }
}

@Entry
@Component
struct DynamicLazyForEach {
  private dataSource = new DynamicDataSource()

  build() {
    Column() {
      Row() {
        Button('Add Item')
          .onClick(() => {
            const index = Math.floor(Math.random() * this.dataSource.totalCount())
            this.dataSource.addData(index, `New Item ${Date.now()}`)
          })

        Button('Remove Item')
          .onClick(() => {
            const index = Math.floor(Math.random() * this.dataSource.totalCount())
            if (this.dataSource.totalCount() > 0) {
              this.dataSource.removeData(index)
            }
          })
      }
      .margin(10)

      List() {
        LazyForEach(this.dataSource, (item: string, index: number) => {
          ListItem() {
            Text(item)
              .fontSize(16)
              .padding(10)
          }
        })
      }
      .cachedCount(10)
    }
  }
}
```

### 示例 3: 分页加载

```typescript
class PagedDataSource implements IDataSource {
  private data: Array<string> = []
  private listeners: DataChangeListener[] = []
  private pageSize = 20
  private currentPage = 0

  constructor() {
    this.loadMore()
  }

  totalCount(): number {
    return this.data.length
  }

  getData(index: number): string {
    return this.data[index]
  }

  registerDataChangeListener(listener: DataChangeListener): void {
    this.listeners.push(listener)
  }

  unregisterDataChangeListener(listener: DataChangeListener): void {
    const index = this.listeners.indexOf(listener)
    if (index >= 0) {
      this.listeners.splice(index, 1)
    }
  }

  // 加载更多数据
  loadMore(): void {
    this.currentPage++
    const start = (this.currentPage - 1) * this.pageSize
    const newData: Array<string> = []

    for (let i = 0; i < this.pageSize; i++) {
      newData.push(`Page ${this.currentPage} - Item ${start + i + 1}`)
    }

    const oldCount = this.data.length
    this.data.push(...newData)

    // 通知数据变化
    this.listeners.forEach(listener => {
      for (let i = 0; i < this.pageSize; i++) {
        listener.onDataAdded(oldCount + i)
      }
    })
  }
}

@Entry
@Component
struct PagedLazyForEach {
  private dataSource = new PagedDataSource()

  build() {
    List() {
      LazyForEach(this.dataSource, (item: string, index: number) => {
        ListItem() {
          Text(item)
            .fontSize(16)
            .padding(15)
            .width('100%')
        }
        .onAppear(() => {
          // 滚动到倒数第 5 个时加载更多
          if (index >= this.dataSource.totalCount() - 5) {
            this.dataSource.loadMore()
          }
        })
      })
    }
    .cachedCount(5)
  }
}
```

### 示例 4: 复杂数据类型

```typescript
interface User {
  id: number
  name: string
  avatar: string
  email: string
}

class UserDataSource implements IDataSource {
  private users: Array<User> = []
  private listeners: DataChangeListener[] = []

  constructor(users: Array<User>) {
    this.users = users
  }

  totalCount(): number {
    return this.users.length
  }

  getData(index: number): User {
    return this.users[index]
  }

  registerDataChangeListener(listener: DataChangeListener): void {
    this.listeners.push(listener)
  }

  unregisterDataChangeListener(listener: DataChangeListener): void {
    const index = this.listeners.indexOf(listener)
    if (index >= 0) {
      this.listeners.splice(index, 1)
    }
  }

  // 添加用户
  addUser(user: User): void {
    this.users.push(user)
    this.listeners.forEach(listener => listener.onDataAdded(this.users.length - 1))
  }

  // 更新用户
  updateUser(index: number, user: User): void {
    this.users[index] = user
    this.listeners.forEach(listener => listener.onDataChanged(index))
  }
}

@Entry
@Component
struct UserListLazyForEach {
  private dataSource = new UserDataSource([
    { id: 1, name: 'Alice', avatar: 'avatar1.png', email: 'alice@example.com' },
    { id: 2, name: 'Bob', avatar: 'avatar2.png', email: 'bob@example.com' },
    { id: 3, name: 'Charlie', avatar: 'avatar3.png', email: 'charlie@example.com' },
  ])

  build() {
    List() {
      LazyForEach(this.dataSource, (user: User, index: number) => {
        ListItem() {
          Row() {
            Image(user.avatar)
              .width(50)
              .height(50)
              .borderRadius(25)
              .margin({ right: 10 })

            Column() {
              Text(user.name)
                .fontSize(18)
                .fontWeight(FontWeight.Bold)

              Text(user.email)
                .fontSize(14)
                .fontColor('#666666')
            }
            .alignItems(HorizontalAlign.Start)
          }
          .width('100%')
          .padding(10)
        }
      })
    }
    .cachedCount(10)
  }
}
```

### 示例 5: 嵌套 LazyForEach

```typescript
interface Category {
  id: number
  name: string
  items: Array<string>
}

class CategoryDataSource implements IDataSource {
  private categories: Array<Category> = []
  private listeners: DataChangeListener[] = []

  constructor(categories: Array<Category>) {
    this.categories = categories
  }

  totalCount(): number {
    return this.categories.length
  }

  getData(index: number): Category {
    return this.categories[index]
  }

  registerDataChangeListener(listener: DataChangeListener): void {
    this.listeners.push(listener)
  }

  unregisterDataChangeListener(listener: DataChangeListener): void {
    const index = this.listeners.indexOf(listener)
    if (index >= 0) {
      this.listeners.splice(index, 1)
    }
  }
}

class ItemDataSource implements IDataSource {
  private items: Array<string> = []
  private listeners: DataChangeListener[] = []

  constructor(items: Array<string>) {
    this.items = items
  }

  totalCount(): number {
    return this.items.length
  }

  getData(index: number): string {
    return this.items[index]
  }

  registerDataChangeListener(listener: DataChangeListener): void {
    this.listeners.push(listener)
  }

  unregisterDataChangeListener(listener: DataChangeListener): void {
    const index = this.listeners.indexOf(listener)
    if (index >= 0) {
      this.listeners.splice(index, 1)
    }
  }
}

@Entry
@Component
struct NestedLazyForEach {
  private categoryDataSource = new CategoryDataSource([
    {
      id: 1,
      name: 'Fruits',
      items: ['Apple', 'Banana', 'Orange', 'Grape', 'Mango']
    },
    {
      id: 2,
      name: 'Vegetables',
      items: ['Carrot', 'Potato', 'Tomato', 'Onion', 'Cabbage']
    },
  ])

  build() {
    List() {
      LazyForEach(this.categoryDataSource, (category: Category) => {
        ListItem() {
          Column() {
            Text(category.name)
              .fontSize(20)
              .fontWeight(FontWeight.Bold)
              .margin({ top: 10, bottom: 5 })

            List() {
              LazyForEach(
                new ItemDataSource(category.items),
                (item: string) => item,
                (item: string) => {
                  ListItem() {
                    Text(`  - ${item}`)
                      .fontSize(16)
                  }
                }
              )
            }
            .height(200)
          }
          .width('100%')
          .padding(10)
          .backgroundColor('#f5f5f5')
          .borderRadius(8)
          .margin(5)
        }
      })
    }
    .cachedCount(5)
  }
}
```

---

## 调试指南

### 日志系统

LazyForEach 使用 ACE 的标准日志系统。启用日志：

```bash
# 设置日志级别
hdc shell shell_hilog -b D
hdc shell shell_hilog -t ACE | grep LazyForEach
```

### 关键日志标签

| 日志标签 | 用途 | 源码位置 |
|---------|------|----------|
| ACE_LAZY_FOR_EACH | LazyForEach 核心逻辑 | `lazy_for_each_node.cpp` |
| ACE_FOREACH_BUILDER | Builder 算法 | `lazy_for_each_builder.cpp` |
| ACE_VIEW | 视图更新 | `lazy_for_each_model_impl.cpp` |

### 常见问题排查

#### 问题 1: 组件不显示

**症状**: LazyForEach 渲染空白

**原因**:
- IDataSource 接口未正确实现
- totalCount() 返回 0
- 未正确注册数据变化监听器

**解决方案**:
```typescript
// ✅ 确保正确实现 IDataSource
class MyDataSource implements IDataSource {
  totalCount(): number {
    return this.data.length  // 必须返回正确的数量
  }

  getData(index: number): Object {
    return this.data[index]  // 必须返回有效对象
  }

  registerDataChangeListener(listener: DataChangeListener): void {
    if (!this.listeners.includes(listener)) {
      this.listeners.push(listener)  // 避免重复注册
    }
  }

  unregisterDataChangeListener(listener: DataChangeListener): void {
    const index = this.listeners.indexOf(listener)
    if (index >= 0) {
      this.listeners.splice(index, 1)
    }
  }
}
```

#### 问题 2: 数据更新不生效

**症状**: 数据源变化后 UI 不更新

**原因**: 未通知数据变化监听器

**解决方案**:
```typescript
// ✅ 在数据操作后通知监听器
addData(item: Item): void {
  this.data.push(item)
  // 必须通知监听器
  this.listeners.forEach(listener => {
    listener.onDataAdded(this.data.length - 1)
  })
}
```

#### 问题 3: 滚动卡顿

**症状**: 滚动时出现卡顿

**原因**:
- 组件创建过于复杂
- 缓存数量不足
- 数据源访问慢

**解决方案**:
```typescript
// ✅ 增加缓存数量
LazyForEach(this.dataSource, (item) => {
  // 简化组件结构
  SimpleItemComponent({ data: item })
})
.cachedCount(10)  // 增加缓存
```

#### 问题 4: 内存泄漏

**症状**: 长时间使用后内存占用持续增长

**原因**: 未正确注销监听器

**解决方案**:
```typescript
aboutToDisappear() {
  // 组件销毁时注销监听器
  this.dataSource.unregisterDataChangeListener(this.listener)
}
```

---

## 最佳实践

### 1. IDataSource 实现

```typescript
// ✅ 推荐实现
class OptimizedDataSource implements IDataSource {
  private data: Array<Item> = []
  private listeners: DataChangeListener[] = []

  totalCount(): number {
    return this.data.length
  }

  getData(index: number): Object {
    // 添加边界检查
    if (index < 0 || index >= this.data.length) {
      return null
    }
    return this.data[index]
  }

  registerDataChangeListener(listener: DataChangeListener): void {
    // 避免重复注册
    if (!this.listeners.includes(listener)) {
      this.listeners.push(listener)
    }
  }

  unregisterDataChangeListener(listener: DataChangeListener): void {
    const index = this.listeners.indexOf(listener)
    if (index >= 0) {
      this.listeners.splice(index, 1)
    }
  }

  // 批量操作时使用批量通知
  bulkAdd(items: Array<Item>): void {
    const startIndex = this.data.length
    this.data.push(...items)
    this.listeners.forEach(listener => {
      listener.onDataBulkAdded(startIndex, items.length)
    })
  }
}
```

### 2. 缓存策略配置

```typescript
// ✅ 根据设备性能和组件复杂度调整
@Entry
@Component
struct OptimizedLazyForEach {
  private dataSource = new MyDataSource()
  private cacheCount = 5  // 默认值

  aboutToAppear() {
    // 根据设备性能调整缓存
    const isHighEndDevice = this.checkDevicePerformance()
    this.cacheCount = isHighEndDevice ? 10 : 3
  }

  build() {
    List() {
      LazyForEach(this.dataSource, (item) => {
        ListItem() {
          ItemComponent({ data: item })
        }
      })
    }
    .cachedCount(this.cacheCount)
  }
}
```

### 3. 组件复用

```typescript
// ✅ 使用 @Reusable 装饰器标记可复用组件
@Reusable
@Component
struct ItemComponent {
  @Prop item: Item

  build() {
    Text(this.item.name)
      .fontSize(16)
  }
}

// 使用可复用组件
LazyForEach(this.dataSource, (item: Item) => {
  ListItem() {
    ItemComponent({ data: item })  // 可复用
  }
})
```

### 4. 数据预加载

```typescript
// ✅ 实现分页预加载
class PreloadDataSource implements IDataSource {
  private data: Array<Item> = []
  private listeners: DataChangeListener[] = []
  private pageSize = 20
  private preloadThreshold = 5  // 距离边界 5 个时开始预加载

  // 检查是否需要预加载
  checkPreload(currentIndex: number): void {
    if (currentIndex >= this.data.length - this.preloadThreshold) {
      this.loadNextPage()
    }
  }

  private loadNextPage(): void {
    // 加载下一页数据
    const newData = this.fetchDataFromServer(this.data.length, this.pageSize)
    const startIndex = this.data.length
    this.data.push(...newData)

    this.listeners.forEach(listener => {
      for (let i = 0; i < newData.length; i++) {
        listener.onDataAdded(startIndex + i)
      }
    })
  }
}
```

---

## 性能优化

### 1. 组件简化

```typescript
// ❌ 复杂组件（性能差)
LazyForEach(this.dataSource, (item) => {
  ListItem() {
    Stack() {
      Image(item.background)
      Column() {
        Text(item.title)
        Text(item.description)
        Row() {
          Button('Like')
          Button('Share')
          Button('Comment')
        }
      }
    }
  }
})

// ✅ 简化组件（性能优）
@Reusable
@Component
struct SimpleItem {
  @Prop item: Item
  build() {
    Row() {
      Text(item.title)
      Text(item.description)
    }
  }
}
```

### 2. 按需加载图片

```typescript
// ✅ 使用 onAppear/onDisappear 控制图片加载
LazyForEach(this.dataSource, (item: ImageItem) => {
  ListItem() {
    Image(item.loaded ? item.url : 'placeholder.png')
      .width(100)
      .height(100)
      .onAppear(() => {
        // 进入可见区域时加载图片
        item.load()
      })
      .onDisappear(() => {
        // 离开可见区域时释放资源
        item.unload()
      })
  }
})
```

### 3. 减少不必要的重建

```typescript
// ✅ 使用 key 值确保组件复用
LazyForEach(this.dataSource, (item: Item) => item.id, (item: Item) => {
  ListItem() {
    Text(item.name)
  }
})
```

---

## Arkoala 前端支持

### ArkoalaLazyForEachNode

Arkoala 语言也支持 LazyForEach 功能，通过 `ArkoalaLazyForEachNode` 实现。

### Arkoala vs ArkTS LazyForEach

| 特性 | ArkTS LazyForEachNode | Arkoala ArkoalaLazyForEachNode |
|------|----------------------|------------------------------|
| 前端语言 | ArkTS/TypeScript | Arkoala |
| 基类 | ForEachBaseNode | ForEachBaseNode |
| 核心接口 | 一致 | 一致 |
| 源码位置 | `lazy_for_each_node.cpp` | `arkoala_lazy_node.cpp` |

### Arkoala API

```arkoala
// Arkoala 伪代码示例
LazyForEach(
  dataSource: IDataSource,
  itemGenerator: (item: Object, index: Int32) -> Unit
): Unit
```

---

## 相关资源

### 源码文件

- **Pattern Node**: `frameworks/core/components_ng/syntax/lazy_for_each_node.cpp` (35,568 行)
- **Builder**: `frameworks/core/components_ng/syntax/lazy_for_each_builder.cpp` (62,289 行)
- **Base Class**: `frameworks/core/components_ng/syntax/for_each_base_node.h` (77 行)
- **Frontend Bridge**: `frameworks/bridge/declarative_frontend/jsview/models/lazy_for_each_model_impl.cpp` (~150 行)

### 相关文档

- [Syntax 模块架构总览](./Syntax_Architecture_Overview.md)

### API 参考

- [LazyForEach API 参考](https://developer.huawei.com/consumer/cn/doc/harmonyos-references/ts-rendering-control-lazyforeach)
- [LazyForEach 开发指南](https://developer.huawei.com/consumer/cn/doc/harmonyos-guides/arkts-rendering-control-lazyforeach)

---

**文档结束**

如有疑问或建议，请通过以下方式反馈：
- 提交 Issue 到代码仓库
- 联系框架团队
