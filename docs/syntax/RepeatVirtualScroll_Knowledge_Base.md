# RepeatVirtualScroll 组件知识库

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
  - [虚拟滚动](#虚拟滚动)
  - [L1/L2 缓存系统](#l1l2-缓存系统)
  - [懒加载机制](#懒加载机制)
  - [数据变化通知](#数据变化通知)
- [缓存系统详解](#缓存系统详解)
- [布局算法](#布局算法)
- [版本兼容性](#版本兼容性)
- [完整 API 清单](#完整-api-清单)
- [使用示例](#使用示例)
- [调试指南](#调试指南)
- [最佳实践](#最佳实践)
- [性能优化](#性能优化)

---

## 概述

### 组件定位

**RepeatVirtualScroll** 是 OpenHarmony ArkUI 框架中用于**虚拟滚动和懒加载**的高级组件。它通过 L1/L2 双级缓存系统和按需渲染机制，实现超大规模数据集（数万项）的高性能滚动。

### 核心特性

- **虚拟滚动**: 仅渲染可见区域 + 预测区域的组件
- **L1/L2 双级缓存**: L1 缓存活跃项，L2 缓存非活跃但保留的项
- **懒加载机制**: 按需创建和销毁组件，最小化内存占用
- **数据源驱动**: 支持动态数据更新和变化通知
- **拖拽排序**: 内置拖拽支持
- **预测性渲染**: 利用空闲时间预渲染即将显示的组件
- **API 16+**: 新架构实现，性能和功能更优

---

## 完整调用链

### ArkTS → Pattern Node → Cache System 调用流程

```
┌─────────────────────────────────────────────────────────────────┐
│  ArkTS 前端代码                                                  │
│  RepeatVirtualScroll({ dataSource: this.dataSource })           │
└─────────────────────────────────────────────────────────────────┘
                            ↓
┌─────────────────────────────────────────────────────────────────┐
│  Declarative Frontend (声明式前端)                               │
│  frameworks/bridge/declarative_frontend/jsview/models/          │
│    repeat_virtual_scroll_2_model_impl.cpp                       │
│    - RepeatVirtualScrollModelImpl::Create()                     │
│    - 注册 TS 回调函数                                           │
└─────────────────────────────────────────────────────────────────┘
                            ↓
┌─────────────────────────────────────────────────────────────────┐
│  Pattern Node (语法节点层)                                       │
│  frameworks/core/components_ng/syntax/                         │
│    repeat_virtual_scroll_2_node.cpp                            │
│    - RepeatVirtualScroll2Node::GetOrCreateRepeatNode()         │
│    - RepeatVirtualScroll2Node::GetFrameChildByIndex()          │
│    - RepeatVirtualScroll2Node::DoSetActiveChildRange()         │
│    - RepeatVirtualScroll2Node::RecycleItems()                  │
└─────────────────────────────────────────────────────────────────┘
                            ↓
┌─────────────────────────────────────────────────────────────────┐
│  Cache System (缓存系统)                                        │
│  frameworks/core/components_ng/syntax/                         │
│    repeat_virtual_scroll_2_caches.cpp                          │
│    - RepeatVirtualScroll2Caches::GetFrameChild()               │
│    - RepeatVirtualScroll2Caches::GetL1UINode4Index()           │
│    - RepeatVirtualScroll2Caches::MoveBetweenL1L2()             │
│    - RepeatVirtualScroll2Caches::PurgeCache()                  │
└─────────────────────────────────────────────────────────────────┘
                            ↓
┌─────────────────────────────────────────────────────────────────┐
│  渲染显示                                                         │
│  - 按需创建/复用 FrameNode                                       │
│  - Measure/Layout 计算                                           │
│  - RenderNode 绘制                                              │
└─────────────────────────────────────────────────────────────────┘
```

### 关键调用路径

**源码位置**：
- 前端桥接: `frameworks/bridge/declarative_frontend/jsview/models/repeat_virtual_scroll_2_model_impl.cpp`
- Pattern Node: `frameworks/core/components_ng/syntax/repeat_virtual_scroll_2_node.cpp`
- Cache System: `frameworks/core/components_ng/syntax/repeat_virtual_scroll_2_caches.cpp`

---

## 目录结构

### 源码文件组织

```
frameworks/core/components_ng/syntax/
├── for_each_base_node.h                         # 基类（77 行）
├── repeat_virtual_scroll_2_node.h               # RepeatVirtualScroll2Node 头文件
├── repeat_virtual_scroll_2_node.cpp             # RepeatVirtualScroll2Node 实现（48573 行）
├── repeat_virtual_scroll_2_caches.h             # 缓存系统头文件
├── repeat_virtual_scroll_2_caches.cpp           # 缓存系统实现（27695 行）
└── repeat_virtual_scroll_2_model_ng.cpp         # Model 层接口

frameworks/bridge/declarative_frontend/
├── jsview/models/
│   └── repeat_virtual_scroll_2_model_impl.cpp   # 前端 Model 实现
└── ark_node/types/
    └── repeat_virtual_scroll.d.ts               # TypeScript 类型定义
```

### 代码规模

| 文件 | 行数 | 说明 |
|------|------|------|
| repeat_virtual_scroll_2_node.cpp | 48,573 | Pattern Node 实现 |
| repeat_virtual_scroll_2_caches.cpp | 27,695 | 缓存系统实现 |
| repeat_virtual_scroll_2_node.h | ~250 | 接口定义 |
| repeat_virtual_scroll_2_caches.h | ~350 | 缓存接口定义 |
| repeat_virtual_scroll_2_model_impl.cpp | ~200 | 前端桥接 |
| **总计** | **~77,068** | **RepeatVirtualScroll 完整实现** |

---

## 类继承关系

### 继承体系

```
UINode (frameworks/core/components_ng/base/ui_node.h)
    ↓
ForEachBaseNode (frameworks/core/components_ng/syntax/for_each_base_node.h)
    ↓
RepeatVirtualScroll2Node (frameworks/core/components_ng/syntax/repeat_virtual_scroll_2_node.h)
    ↓
    ├── RepeatVirtualScroll2Caches (组合关系)
    └── TS Callback Functions (接口关系)
```

### RepeatVirtualScroll2Node 类结构

**源码位置**: `repeat_virtual_scroll_2_node.h:93-150`

```cpp
class ACE_EXPORT RepeatVirtualScroll2Node : public ForEachBaseNode {
public:
    static RefPtr<RepeatVirtualScroll2Node> GetOrCreateRepeatNode(
        int32_t nodeId, uint32_t arrLen, uint32_t totalCount,
        const std::function<std::pair<RIDType, uint32_t>(IndexType)>& onGetRid4Index,
        const std::function<void(IndexType, IndexType)>& onRecycleItems,
        const std::function<void(int32_t, int32_t, int32_t, int32_t, bool, bool)>& onActiveRange,
        const std::function<void(IndexType, IndexType)>& onMoveFromTo,
        const std::function<void()>& onPurge,
        const std::function<void()>& onUpdateDirty);

    // 核心方法
    uint32_t GetTotalCount() const;
    void UpdateTotalCount(uint32_t totalCount);
    void UpdateArrLen(uint32_t arrLen);
    int32_t FrameCount() const override;

    // 获取子组件
    RefPtr<UINode> GetFrameChildByIndex(uint32_t index, bool needBuild,
        bool isCache = false, bool addToRenderTree = false) override;

    // 活动范围
    void DoSetActiveChildRange(int32_t start, int32_t end,
        int32_t cacheStart, int32_t cacheEnd, bool showCache = false) override;

    // 回收组件
    void RecycleItems(int32_t from, int32_t to) override;

    // 容器重布局
    void RequestContainerReLayout(IndexType startIndex = INT_MIN);

    // 获取子组件列表
    const std::list<RefPtr<UINode>>& GetChildren(bool notDetach = false) const override;

private:
    RefPtr<RepeatVirtualScroll2Caches> caches_;  // 缓存系统
    uint32_t totalCount_;                        // 总数据项数
    uint32_t arrLen_;                            // 数组长度
    std::function<std::pair<RIDType, uint32_t>(IndexType)> onGetRid4Index_;
    std::function<void(IndexType, IndexType)> onRecycleItems_;
    std::function<void(int32_t, int32_t, int32_t, int32_t, bool, bool)> onActiveRange_;
    std::function<void(IndexType, IndexType)> onMoveFromTo_;
    std::function<void()> onPurge_;
    std::function<void()> onUpdateDirty_;
};
```

### RepeatVirtualScroll2Caches 类结构

**源码位置**: `repeat_virtual_scroll_2_caches.h:132-150`

```cpp
class RepeatVirtualScroll2Caches {
public:
    using CacheItem = RefPtr<RepeatVirtualScroll2CacheItem>;
    using GetFrameChildResult = std::pair<uint32_t, CacheItem>;

    // 获取子组件
    GetFrameChildResult GetFrameChild(IndexType index, bool needBuild);

    // L1 缓存操作
    OptCacheItem GetL1UINode4Index(IndexType index);
    void SetL1(IndexType index, RIDType rid, CacheItem item);

    // L2 缓存操作
    void MoveFromL1ToL2(CacheItem item);
    void MoveFromL2ToL1(IndexType index, RIDType rid, CacheItem item);

    // 缓存清理
    void PurgeCache();
    void RemoveNode(RIDType rid);

    // 缓存状态管理
    void SetActive(IndexType index, bool isActive);
    void SetOnRenderTree(IndexType index, bool isOnRenderTree);

private:
    // L1 缓存：活跃项（index -> CacheItem）
    std::unordered_map<IndexType, CacheItem> l1Cache_;

    // L2 缓存：非活跃但保留的项（rid -> CacheItem）
    std::unordered_map<RIDType, CacheItem> l2Cache_;

    // 索引映射（index -> rid）
    std::unordered_map<IndexType, RIDType> index2rid_;

    // RID 映射（rid -> CacheItem）
    std::unordered_map<RIDType, CacheItem> rid2CacheItem_;
};
```

---

## 核心功能

### 虚拟滚动

#### 工作原理

虚拟滚动通过**仅渲染可见区域**的组件，大幅降低内存占用和渲染开销：

```
┌─────────────────────────────────────────────────────────────┐
│  可见区域                                     │
│  用户当前看到的区域                                            │
│  - 组件已创建并显示                                            │
│  - 存储在 L1 缓存                                             │
│  - isOnRenderTree = true                                      │
└─────────────────────────────────────────────────────────────┘
                            ↓ 滚动
┌─────────────────────────────────────────────────────────────┐
│  L2 缓存区域（预测区域）                        │
│  即将进入可见区域的组件                                        │
│  - 组件已创建但不在渲染树                                       │
│  - 存储在 L2 缓存                                             │
│  - isOnRenderTree = false, isActive = true                    │
└─────────────────────────────────────────────────────────────┘
                            ↓
┌─────────────────────────────────────────────────────────────┐
│  未缓存区域                                                  │
│  远离可见区域的组件                                            │
│  - 组件已销毁或从未创建                                        │
│  - 不在缓存中                                                 │
│  - 可通过 GetFrameChild 重新创建                               │
└─────────────────────────────────────────────────────────────┘
```

#### GetFrameChild 流程

**源码位置**: `repeat_virtual_scroll_2_caches.cpp`

```cpp
GetFrameChildResult RepeatVirtualScroll2Caches::GetFrameChild(IndexType index, bool needBuild) {
    // 1. 检查 L1 缓存
    auto l1Item = GetL1UINode4Index(index);
    if (l1Item.has_value()) {
        return { UNCHANGED_NODE, l1Item.value() };  // L1 命中
    }

    // 2. 调用 TS 获取或创建组件
    auto [rid, result] = CallOnGetRid4Index(index);

    // 3. 处理结果
    switch (result) {
        case CREATED_NEW_NODE:
            // 新创建的组件，加入 L1
            SetL1(index, rid, cacheItem);
            break;
        case UPDATED_NODE:
            // 更新现有组件
            UpdateL1(index, rid, cacheItem);
            break;
        case NO_NODE:
            // 创建失败
            return { FAILED_NODE, nullptr };
    }

    return { result, cacheItem };
}
```

---

### L1/L2 缓存系统

#### 缓存级别划分

**L1 缓存（Level 1 Cache）**:
- 存储当前可见区域的组件
- `index -> CacheItem` 映射
- `isActive = true`, `isOnRenderTree = true`
- 快速访问，直接返回给渲染树

**L2 缓存（Level 2 Cache）**:
- 存储预测区域的组件（即将进入可见区域）
- `rid -> CacheItem` 映射
- `isActive = true`, `isOnRenderTree = false`
- 从 L1 降级的组件，等待可能的重用

#### 缓存状态转换

```
新创建
    ↓
L1 缓存 (active + onRenderTree)
    ↓
    移出可见区域
    ↓
L2 缓存 (active + !onRenderTree)
    ↓
    缓存满或过期
    ↓
清理 (PurgeCache)
```

#### 缓存策略

**源码位置**: `repeat_virtual_scroll_2_caches.cpp`

```cpp
void RepeatVirtualScroll2Caches::PurgeCache() {
    // 1. 遍历 L1，标记不在活动范围的项
    for (const auto& [index, item] : l1Cache_) {
        if (!IsInActiveRange(index)) {
            MoveFromL1ToL2(item);  // L1 -> L2
        }
    }

    // 2. 遍历 L2，清理过期的项
    auto it = l2Cache_.begin();
    while (it != l2Cache_.end()) {
        if (IsExpired(it->second)) {
            RemoveNode(it->first);  // 从 L2 删除
        }
        ++it;
    }

    // 3. 调用 TS 清理
    onPurge_();
}
```

---

### 懒加载机制

#### 按需创建

RepeatVirtualScroll 采用**完全按需创建**策略：

1. **初始状态**: 不创建任何子组件
2. **滚动触发**: 计算新的可见区域
3. **按需创建**: 对新进入可见区域的索引调用 `GetFrameChild`
4. **自动回收**: 对离开可见区域 + L2 缓存的组件进行清理

#### 预测性渲染

利用空闲时间预渲染即将显示的组件：

```cpp
// 在 DoSetActiveChildRange 中触发
void RepeatVirtualScroll2Node::DoSetActiveChildRange(...) {
    // 1. 设置活动范围
    onActiveRange_(start, end, cacheStart, cacheEnd, ...);

    // 2. 触发预测性渲染（空闲任务）
    PostIdleTask(...);
}
```

---

### 数据变化通知

#### 变化通知机制

RepeatVirtualScroll 通过 TS 回调函数接收数据变化：

| 变化类型 | 回调函数 | 处理逻辑 |
|---------|---------|----------|
| 获取组件 | `onGetRid4Index` | 创建或更新组件 |
| 回收组件 | `onRecycleItems` | 标记组件为无效 |
| 活动范围 | `onActiveRange` | 更新可见区域 |
| 移动组件 | `onMoveFromTo` | 处理拖拽移动 |
| 清理缓存 | `onPurge` | 清理过期缓存 |
| 更新脏标记 | `onUpdateDirty` | 标记需要重渲染 |

#### 数据变化处理流程

```
数据源变化
    ↓
TS 侧检测变化
    ↓
调用 C++ 回调函数
    ↓
RepeatVirtualScroll2Node 处理
    ↓
更新 L1/L2 缓存
    ↓
标记 Dirty → 触发布局 → 渲染更新
```

---

## 缓存系统详解

### CacheItem 结构

**源码位置**: `repeat_virtual_scroll_2_caches.h:96-113`

```cpp
class RepeatVirtualScroll2CacheItem : public virtual AceType {
public:
    bool isL1_;           // 是否在 L1 缓存
    bool isActive_;       // 是否活跃（在活动范围内）
    bool isOnRenderTree_; // 是否在渲染树中
    RefPtr<UINode> node_; // 实际的 UINode
};
```

### 缓存操作场景

#### 场景 1: 新建组件

```
1. GetFrameChild(index)
2. GetL1UINode4Index(index) 返回空
3. CallOnGetRid4Index(index)
    → TS 创建新组件
    → AddNodeFromVSP(rid) 添加到缓存
4. GetCacheItem4RID(rid) 返回新组件
5. 返回给渲染树
```

#### 场景 2: 复用 L1 组件

```
1. GetFrameChild(index)
2. GetL1UINode4Index(index) 返回缓存组件
3. 直接返回，无需创建
```

#### 场景 3: L1 → L2 降级

```
1. 滚动，组件离开可见区域
2. DoSetActiveChildRange 调用
3. 检测到 index 不在活动范围
4. MoveFromL1ToL2(item)
    → 从 L1 移除
    → 添加到 L2
    → isOnRenderTree = false
```

#### 场景 4: L2 → L1 提升

```
1. 滚动，组件重新进入可见区域
2. GetFrameChild(index)
3. L1 未命中，检查 L2
4. MoveFromL2ToL1(index, rid, item)
    → 从 L2 移除
    → 添加到 L1
    → isOnRenderTree = true
```

### 缓存清理策略

**源码位置**: `repeat_virtual_scroll_2_caches.cpp`

```cpp
void RepeatVirtualScroll2Caches::PurgeCache() {
    // 1. L1 → L2：将离开活动范围的项降级
    for (const auto& [index, item] : l1Cache_) {
        if (!IsInActiveRange(index)) {
            MoveFromL1ToL2(item);
        }
    }

    // 2. L2 清理：删除过期项
    auto it = l2Cache_.begin();
    while (it != l2Cache_.end()) {
        if (IsExpired(it->second)) {
            it = l2Cache_.erase(it);  // 删除
        } else {
            ++it;
        }
    }

    // 3. 调用 TS 清理
    onPurge_();
}
```

---

## 布局算法

### Measure 流程

```
RepeatVirtualScroll2Node::OnDirtyLayoutWrapperSwap()
    ↓
LayoutWrapper::Measure()
    ↓
遍历 L1 缓存中的子组件，对每个调用 Measure()
    ↓
计算可见区域总尺寸
    ↓
RepeatVirtualScroll2Node 自身的 Measure 结果
```

### Layout 流程

```
RepeatVirtualScroll2Node::OnDirtyLayoutWrapperSwap()
    ↓
LayoutWrapper::Layout()
    ↓
根据子组件顺序，计算每个子组件的位置
    ↓
应用 Offset 到每个子组件
    ↓
RepeatVirtualScroll2Node 自身的 Layout 结果
```

---

## 版本兼容性

### API 16+ vs API 15- 差异

| 特性 | API 15 及以下 | API 16+ |
|------|---------------|---------|
| 缓存实现 | `repeat_virtual_scroll_caches.cpp` | `repeat_virtual_scroll_2_caches.cpp` |
| Node 实现 | `repeat_virtual_scroll_node.cpp` | `repeat_virtual_scroll_2_node.cpp` |
| Model | `repeat_virtual_scroll_model_ng.cpp` | `repeat_virtual_scroll_2_model_ng.cpp` |
| 缓存级别 | 单级缓存 | L1/L2 双级缓存 |
| 性能优化 | 基础优化 | 高级优化（预测渲染、智能缓存） |
| 组件复用 | 有限复用 | 高级复用 |

### API 16+ 新特性

1. **L1/L2 双级缓存**: 更智能的缓存管理
2. **预测性渲染**: 利用空闲时间预渲染
3. **动态高度支持**: 支持不同高度的子组件
4. **优化的拖拽**: 更流畅的拖拽体验
5. **改进的缓存置换**: 更高效的缓存算法

---

## 完整 API 清单

### ArkTS API

#### 基本语法

```typescript
RepeatVirtualScroll(
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
| cachedCount | `number` | 设置缓存数量（L1 + L2 总缓存） |

#### 示例

```typescript
@Entry
@Component
struct RepeatVirtualScrollExample {
  private dataSource = new MyDataSource([
    // ... 数千个数据项
  ])

  build() {
    List() {
      RepeatVirtualScroll(this.dataSource, (item: Item, index: number) => {
        ListItem() {
          Text(`${index}: ${item.name}`)
            .fontSize(16)
        }
      })
    }
    .cachedCount(10)  // 缓存 10 个组件（L1 + L2）
  }
}
```

### C++ API

#### RepeatVirtualScroll2Node 核心方法

**源码位置**: `repeat_virtual_scroll_2_node.h:97-150`

```cpp
class ACE_EXPORT RepeatVirtualScroll2Node : public ForEachBaseNode {
public:
    // 创建或获取 RepeatVirtualScroll2Node
    static RefPtr<RepeatVirtualScroll2Node> GetOrCreateRepeatNode(
        int32_t nodeId, uint32_t arrLen, uint32_t totalCount,
        const std::function<std::pair<RIDType, uint32_t>(IndexType)>& onGetRid4Index,
        const std::function<void(IndexType, IndexType)>& onRecycleItems,
        const std::function<void(int32_t, int32_t, int32_t, int32_t, bool, bool)>& onActiveRange,
        const std::function<void(IndexType, IndexType)>& onMoveFromTo,
        const std::function<void()>& onPurge,
        const std::function<void()>& onUpdateDirty);

    // 获取子组件
    RefPtr<UINode> GetFrameChildByIndex(uint32_t index, bool needBuild,
        bool isCache = false, bool addToRenderTree = false) override;

    // 设置活动范围
    void DoSetActiveChildRange(int32_t start, int32_t end,
        int32_t cacheStart, int32_t cacheEnd, bool showCache = false) override;

    // 回收组件
    void RecycleItems(int32_t from, int32_t to) override;

    // 容器重布局
    void RequestContainerReLayout(IndexType startIndex = INT_MIN);

    // 获取子组件列表
    const std::list<RefPtr<UINode>>& GetChildren(bool notDetach = false) const override;
};
```

#### RepeatVirtualScroll2Caches 核心方法

**源码位置**: `repeat_virtual_scroll_2_caches.h:132-150`

```cpp
class RepeatVirtualScroll2Caches {
public:
    // 获取子组件
    GetFrameChildResult GetFrameChild(IndexType index, bool needBuild);

    // L1 缓存操作
    OptCacheItem GetL1UINode4Index(IndexType index);
    void SetL1(IndexType index, RIDType rid, CacheItem item);

    // L2 缓存操作
    void MoveFromL1ToL2(CacheItem item);
    void MoveFromL2ToL1(IndexType index, RIDType rid, CacheItem item);

    // 缓存清理
    void PurgeCache();
    void RemoveNode(RIDType rid);

    // 缓存状态管理
    void SetActive(IndexType index, bool isActive);
    void SetOnRenderTree(IndexType index, bool isOnRenderTree);
};
```

---

## 使用示例

### 示例 1: 基本虚拟滚动

```typescript
class Item {
  id: number
  name: string

  constructor(id: number, name: string) {
    this.id = id
    this.name = name
  }
}

class MyDataSource implements IDataSource {
  private data: Array<Item> = []
  private listeners: DataChangeListener[] = []

  constructor(count: number) {
    for (let i = 0; i < count; i++) {
      this.data.push(new Item(i, `Item ${i}`))
    }
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
}

@Entry
@Component
struct BasicRepeatVirtualScroll {
  private dataSource = new MyDataSource(10000)  // 10000 个数据项

  build() {
    List() {
      RepeatVirtualScroll(this.dataSource, (item: Item, index: number) => {
        ListItem() {
          Text(`${index}: ${item.name}`)
            .fontSize(16)
            .padding(10)
            .width('100%')
        }
      })
    }
    .cachedCount(10)  // L1 + L2 总缓存 10 个组件
    .height('100%')
  }
}
```

### 示例 2: 动态数据更新

```typescript
class DynamicDataSource implements IDataSource {
  private data: Array<string> = []
  private listeners: DataChangeListener[] = []

  constructor() {
    // 初始 100 个数据
    for (let i = 1; i <= 100; i++) {
      this.data.push(`Initial Item ${i}`)
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

  // 更新数据
  updateData(index: number, value: string): void {
    this.data[index] = value
    this.listeners.forEach(listener => listener.onDataChanged(index))
  }
}

@Entry
@Component
struct DynamicRepeatVirtualScroll {
  private dataSource = new DynamicDataSource()

  build() {
    Column() {
      Row() {
        Button('Add')
          .onClick(() => {
            const index = Math.floor(Math.random() * this.dataSource.totalCount())
            this.dataSource.addData(index, `New Item ${Date.now()}`)
          })

        Button('Remove')
          .onClick(() => {
            const index = Math.floor(Math.random() * this.dataSource.totalCount())
            if (this.dataSource.totalCount() > 0) {
              this.dataSource.removeData(index)
            }
          })

        Button('Update')
          .onClick(() => {
            const index = Math.floor(Math.random() * this.dataSource.totalCount())
            this.dataSource.updateData(index, `Updated ${Date.now()}`)
          })
      }
      .margin(10)

      List() {
        RepeatVirtualScroll(this.dataSource, (item: string, index: number) => {
          ListItem() {
            Text(`${index}: ${item}`)
              .fontSize(16)
              .padding(10)
          }
        })
      }
      .cachedCount(15)
      .layoutWeight(1)
    }
  }
}
```

### 示例 3: 带拖拽排序

```typescript
@Entry
@Component
struct DraggableRepeatVirtualScroll {
  private dataSource = new MyDataSource(1000)

  build() {
    List() {
      RepeatVirtualScroll(this.dataSource, (item: Item, index: number) => {
        ListItem() {
          Text(`${index}: ${item.name}`)
            .fontSize(16)
            .padding(15)
            .width('90%')
            .backgroundColor('#e0e0e0')
            .borderRadius(8)
            .margin(5)
        }
        .transition(TransitionType.All, AnimationCurve.Ease)
      })
    }
    .cachedCount(10)
    .onMove((from: number, to: number) => {
      // 实现拖拽排序的数据更新
      console.info(`Move from ${from} to ${to}`)
      // 这里需要更新 dataSource 中的数据顺序
    })
  }
}
```

### 示例 4: 分页加载

```typescript
class PagedDataSource implements IDataSource {
  private data: Array<string> = []
  private listeners: DataChangeListener[] = []
  private pageSize = 50
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

  loadMore(): void {
    this.currentPage++
    const start = (this.currentPage - 1) * this.pageSize
    const newData: Array<string> = []

    for (let i = 0; i < this.pageSize; i++) {
      newData.push(`Page ${this.currentPage} - Item ${start + i + 1}`)
    }

    const oldCount = this.data.length
    this.data.push(...newData)

    this.listeners.forEach(listener => {
      for (let i = 0; i < this.pageSize; i++) {
        listener.onDataAdded(oldCount + i)
      }
    })
  }
}

@Entry
@Component
struct PagedRepeatVirtualScroll {
  private dataSource = new PagedDataSource()

  build() {
    List() {
      RepeatVirtualScroll(this.dataSource, (item: string, index: number) => {
        ListItem() {
          Text(item)
            .fontSize(16)
            .padding(15)
            .width('100%')
        }
        .onAppear(() => {
          // 滚动到倒数第 10 个时加载更多
          if (index >= this.dataSource.totalCount() - 10) {
            this.dataSource.loadMore()
          }
        })
      })
    }
    .cachedCount(15)
    .height('100%')
  }
}
```

---

## 调试指南

### 日志系统

RepeatVirtualScroll 使用 ACE 的标准日志系统。启用日志：

```bash
# 设置日志级别
hdc shell shell_hilog -b D
hdc shell shell_hilog -t ACE | grep RepeatVirtualScroll
```

### 关键日志标签

| 日志标签 | 用途 | 源码位置 |
|---------|------|----------|
| ACE_REPEAT_VIRTUAL_SCROLL | 核心逻辑 | `repeat_virtual_scroll_2_node.cpp` |
| ACE_REPEAT_VIRTUAL_SCROLL_CACHE | 缓存操作 | `repeat_virtual_scroll_2_caches.cpp` |
| ACE_VIEW | 视图更新 | `repeat_virtual_scroll_2_model_impl.cpp` |

### 常见问题排查

#### 问题 1: 组件不显示

**症状**: RepeatVirtualScroll 渲染空白

**原因**:
- IDataSource 接口未正确实现
- totalCount() 返回 0
- 活动范围设置不正确

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
      this.listeners.push(listener)
    }
  }
}
```

#### 问题 2: 滚动卡顿

**症状**: 滚动时出现卡顿

**原因**:
- 组件创建过于复杂
- 缓存数量不足
- L1/L2 缓存配置不当

**解决方案**:
```typescript
// ✅ 增加缓存数量
RepeatVirtualScroll(this.dataSource, (item) => {
  SimpleItemComponent({ data: item })
})
.cachedCount(20)  // 增加 L1 + L2 缓存
```

#### 问题 3: 内存占用高

**症状**: 长时间使用后内存占用持续增长

**原因**: 缓存未正确清理

**解决方案**:
```typescript
// ✅ 组件销毁时清理
aboutToDisappear() {
  // 框架会自动调用 PurgeCache 清理缓存
}
```

---

## 最佳实践

### 1. 缓存配置

```typescript
// ✅ 根据设备性能和组件复杂度调整
@Entry
@Component
struct OptimizedRepeatVirtualScroll {
  private dataSource = new MyDataSource()
  private cacheCount = 10  // 默认值

  aboutToAppear() {
    // 高端设备增加缓存
    const isHighEndDevice = this.checkDevicePerformance()
    this.cacheCount = isHighEndDevice ? 20 : 8
  }

  build() {
    List() {
      RepeatVirtualScroll(this.dataSource, (item) => {
        ListItem() {
          ItemComponent({ data: item })
        }
      })
    }
    .cachedCount(this.cacheCount)
  }
}
```

### 2. 组件复用

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
RepeatVirtualScroll(this.dataSource, (item: Item) => {
  ListItem() {
    ItemComponent({ data: item })  // 可复用
  }
})
```

### 3. 数据预加载

```typescript
// ✅ 实现分页预加载
class PreloadDataSource implements IDataSource {
  private data: Array<Item> = []
  private listeners: DataChangeListener[] = []
  private pageSize = 100
  private preloadThreshold = 20  // 距离边界 20 个时开始预加载

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

### 1. 简化组件结构

```typescript
// ❌ 复杂组件（性能差）
RepeatVirtualScroll(this.dataSource, (item) => {
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

### 2. 动态高度优化

```typescript
// ✅ 使用固定高度或动态高度缓存
RepeatVirtualScroll(this.dataSource, (item) => {
  ListItem() {
    Text(item.content)
      .fontSize(16)
  }
  // 固定高度或高度缓存可以提升性能
})
```

### 3. 按需加载图片

```typescript
// ✅ 使用 onAppear/onDisappear 控制图片加载
RepeatVirtualScroll(this.dataSource, (item: ImageItem) => {
  ListItem() {
    Image(item.loaded ? item.url : 'placeholder.png')
      .width(100)
      .height(100)
      .onAppear(() => {
        item.load()  // 进入可见区域时加载
      })
      .onDisappear(() => {
        item.unload()  // 离开可见区域时释放
      })
  }
})
```

---

## 相关资源

### 源码文件

- **Pattern Node**: `frameworks/core/components_ng/syntax/repeat_virtual_scroll_2_node.cpp` (48,573 行)
- **Cache System**: `frameworks/core/components_ng/syntax/repeat_virtual_scroll_2_caches.cpp` (27,695 行)
- **Base Class**: `frameworks/core/components_ng/syntax/for_each_base_node.h` (77 行)
- **Frontend Bridge**: `frameworks/bridge/declarative_frontend/jsview/models/repeat_virtual_scroll_2_model_impl.cpp` (~200 行)

### 相关文档

- [Syntax 模块架构总览](./Syntax_Architecture_Overview.md)

### API 参考

- [Repeat 组件 API 参考](https://developer.huawei.com/consumer/cn/doc/harmonyos-references/ts-rendering-control-repeat) - 注：RepeatVirtualScroll 作为 Repeat 组件的虚拟滚动增强实现，API 文档参见 Repeat 组件文档中的 virtualScroll 参数说明
- [虚拟滚动开发指南](https://developer.huawei.com/consumer/cn/doc/harmonyos-guides/arkts-rendering-control-repeat) - 参见虚拟滚动部分

---

**文档结束**

如有疑问或建议，请通过以下方式反馈：
- 提交 Issue 到代码仓库
- 联系框架团队
