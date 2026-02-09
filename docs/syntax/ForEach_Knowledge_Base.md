# ForEach 组件知识库

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
  - [数据驱动更新](#数据驱动更新)
  - [差分算法](#差分算法)
  - [ID 管理](#id-管理)
  - [拖拽排序](#拖拽排序)
- [布局算法](#布局算法)
- [事件处理](#事件处理)
- [完整 API 清单](#完整-api-清单)
- [使用示例](#使用示例)
- [调试指南](#调试指南)
- [最佳实践](#最佳实践)
- [Arkoala 前端支持](#arkoala-前端支持)

---

## 概述

### 组件定位

**ForEach** 是 OpenHarmony ArkUI 框架中用于**数据驱动的循环渲染**组件。它根据数据集合的变化，自动更新 UI 显示，支持高效的增量更新和拖拽排序功能。

### 核心特性

- **数据驱动更新**: 基于数据源变化自动触发 UI 更新
- **差分算法**: 通过 ID 识别变化，仅更新必要的组件
- **拖拽排序**: 内置拖拽排序支持，无需额外实现
- **全量渲染**: 适用于中小规模数据集（< 1000 项）
- **状态保留**: 组件更新时保留子组件状态

### 适用场景

- 中小型列表（< 1000 项）
- 动态数据集合
- 需要拖拽排序的场景

---

## 完整调用链

### ArkTS → Pattern Node 调用流程

```
┌─────────────────────────────────────────────────────────────────┐
│  ArkTS 前端代码                                                  │
│  ForEach(this.arr, (item: Item) => { ... })                    │
└─────────────────────────────────────────────────────────────────┘
                            ↓
┌─────────────────────────────────────────────────────────────────┐
│  Declarative Frontend (声明式前端)                               │
│  frameworks/bridge/declarative_frontend/jsview/models/          │
│    for_each_model_impl.cpp                                      │
│    - ForEachModelImpl::Create()                                 │
│    - 创建 ForEachComponent                                       │
└─────────────────────────────────────────────────────────────────┘
                            ↓
┌─────────────────────────────────────────────────────────────────┐
│  Pattern Node (语法节点层)                                       │
│  frameworks/core/components_ng/syntax/for_each_node.cpp        │
│    - ForEachNode::GetOrCreateForEachNode()                      │
│    - ForEachNode::CompareAndUpdateChildren()                    │
│    - ForEachNode::FlushUpdateAndMarkDirty()                     │
└─────────────────────────────────────────────────────────────────┘
                            ↓
┌─────────────────────────────────────────────────────────────────┐
│  渲染显示                                                         │
│  - FrameNode 创建和更新                                          │
│  - Measure/Layout 计算                                           │
│  - RenderNode 绘制                                              │
└─────────────────────────────────────────────────────────────────┘
```

### 关键调用路径

**源码位置**：
- 前端桥接: `frameworks/bridge/declarative_frontend/jsview/models/for_each_model_impl.cpp:26-52`
- Pattern Node: `frameworks/core/components_ng/syntax/for_each_node.cpp`

---

## 目录结构

### 源码文件组织

```
frameworks/core/components_ng/syntax/
├── for_each_base_node.h              # ForEach 基类（77 行）
├── for_each_node.h                   # ForEachNode 头文件
├── for_each_node.cpp                 # ForEachNode 实现（16144 行）
└── for_each_model_ng.cpp             # Model 层接口

frameworks/bridge/declarative_frontend/
├── jsview/models/
│   ├── for_each_model_impl.h         # 前端 Model 接口
│   └── for_each_model_impl.cpp       # 前端 Model 实现
└── ark_node/types/
    └── for_each.d.ts                 # TypeScript 类型定义
```

### 代码规模

| 文件 | 行数 | 说明 |
|------|------|------|
| for_each_node.cpp | 16,144 | 核心实现 |
| for_each_node.h | ~105 | 接口定义 |
| for_each_base_node.h | 77 | 基类定义 |
| for_each_model_impl.cpp | ~85 | 前端桥接 |
| **总计** | **~16,411** | **ForEach 完整实现** |

---

## 类继承关系

### 继承体系

```
UINode (frameworks/core/components_ng/base/ui_node.h)
    ↓
ForEachBaseNode (frameworks/core/components_ng/syntax/for_each_base_node.h)
    ↓
ForEachNode (frameworks/core/components_ng/syntax/for_each_node.h)
```

### ForEachBaseNode 基类

**源码位置**: `for_each_base_node.h:22-76`

```cpp
class ACE_EXPORT ForEachBaseNode : public UINode {
public:
    // 纯虚函数 - 子类必须实现
    virtual void MoveData(int32_t from, int32_t to) = 0;
    virtual RefPtr<FrameNode> GetFrameNode(int32_t index) = 0;
    virtual void RecycleItems(int32_t from, int32_t to) {}

    // 拖拽相关事件
    virtual void FireOnMove(int32_t from, int32_t to);
    virtual void FireOnLongPress(int32_t index);
    virtual void FireOnDragStart(int32_t index);
    virtual void FireOnMoveThrough(int32_t from, int32_t through);
    virtual void FireOnDrop(int32_t index);

    bool IsSyntaxNode() const override { return true; }

protected:
    std::function<void(int32_t, int32_t)> onMoveEvent_;
    std::function<void(int32_t)> onLongPressEvent_;
    std::function<void(int32_t)> onDragStartEvent_;
    std::function<void(int32_t, int32_t)> onMoveThroughEvent_;
    std::function<void(int32_t)> onDropEvent_;
};
```

### ForEachNode 派生类

**源码位置**: `for_each_node.h:32-100`

```cpp
class ACE_EXPORT ForEachNode : public ForEachBaseNode {
public:
    static RefPtr<ForEachNode> GetOrCreateForEachNode(int32_t nodeId);

    // 核心更新方法
    void CreateTempItems();
    void CollectRemovingIds(std::list<int32_t>& removedElmtId);
    void CompareAndUpdateChildren();
    void FlushUpdateAndMarkDirty() override;

    // 拖拽相关
    void SetItemDragHandler(
        std::function<void(int32_t)>&& onLongPress,
        std::function<void(int32_t)>&& onDragStart,
        std::function<void(int32_t, int32_t)>&& onMoveThrough,
        std::function<void(int32_t)>&& onDrop);
    void SetOnMove(std::function<void(int32_t, int32_t)>&& onMove);
    void MoveData(int32_t from, int32_t to) override;
    RefPtr<FrameNode> GetFrameNode(int32_t index) override;

private:
    std::list<std::string> ids_;            // ID 列表
    std::list<std::string> tempIds_;        // 临时 ID 列表（用于差分比较）
    std::list<RefPtr<UINode>> tempChildren_; // 临时子组件列表
    std::map<std::string, RefPtr<UINode>> oldNodeByIdMap_; // ID → Node 映射
};
```

---

## 核心功能

### 数据驱动更新

#### 工作原理

ForEach 通过监听数据源变化，自动触发 UI 更新：

1. **数据变化检测**: 前端检测到数组变化
2. **生成新 ID 列表**: 调用 `keyGenerator` 为每个数据项生成唯一 ID
3. **差分比较**: 对比新旧 ID 列表，识别变化类型
4. **增量更新**: 仅更新变化的组件

#### 完整更新流程

```
数据源变化
    ↓
ArkTS 前端检测
    ↓
ForEachModelImpl::Create()
    ↓
生成新 ID 列表 (keyGenerator)
    ↓
ForEachNode::SetIds(newIds)
    ↓
ForEachNode::CompareAndUpdateChildren()
    ↓
ForEachNode::FlushUpdateAndMarkDirty()
    ↓
标记 Dirty → 触发布局 → 渲染更新
```

**源码位置**: `for_each_node.cpp` - `CompareAndUpdateChildren()` 和 `FlushUpdateAndMarkDirty()` 方法

---

### 差分算法

#### 算法概述

ForEach 使用**基于 ID 的差分算法**来识别数据变化：

| 变化类型 | 检测方法 | 操作 |
|---------|---------|------|
| 新增项 | 新 ID 出现在列表中 | 创建新组件 |
| 删除项 | 旧 ID 从列表消失 | 销毁对应组件 |
| 移动项 | ID 位置变化 | 调整组件顺序 |
| 更新项 | ID 相同但位置相同 | 复用现有组件 |

#### 差分比较实现

**源码位置**: `for_each_node.cpp` - `CompareAndUpdateChildren()` 方法

**核心逻辑**：
```cpp
// 伪代码示例
void ForEachNode::CompareAndUpdateChildren() {
    // 1. 创建临时 ID 集合用于快速查找
    std::unordered_set<std::string> oldIdsSet(oldIds.begin(), oldIds.end());

    // 2. 遍历新 ID 列表
    for (const auto& newId : newIds) {
        if (oldIdsSet.find(newId) != oldIdsSet.end()) {
            // ID 存在：复用现有组件
            // 检查是否需要移动位置
        } else {
            // ID 不存在：创建新组件
            CreateNewChild(newId);
        }
    }

    // 3. 清理不再使用的组件
    for (const auto& oldId : oldIds) {
        if (newIdsSet.find(oldId) == newIdsSet.end()) {
            // 旧 ID 不在新列表中：删除组件
            RemoveChild(oldId);
        }
    }
}
```

#### 差分算法优化

1. **哈希表查找**: 使用 `std::unordered_set` 实现 O(1) 查找
2. **ID 映射**: 使用 `std::map<std::string, RefPtr<UINode>>` 缓存节点
3. **批量更新**: 一次性处理所有变化，减少布局次数

---

### ID 管理

#### ID 生成策略

ForEach 通过 `keyGenerator` 函数为每个数据项生成唯一标识符：

```typescript
ForEach(
  this.itemArray,
  (item: Item, index: number) => item.id,  // keyGenerator
  (item: Item, index: number) => {        // ItemGenerator
    ItemComponent({ item: item })
  }
)
```

#### ID 管理要求

| 要求 | 说明 | 错误示例 |
|------|------|----------|
| 唯一性 | 每个 ID 必须唯一 | ❌ 使用数组索引作为 ID |
| 稳定性 | 数据项的 ID 在更新前后应保持一致 | ❌ 使用随机值作为 ID |
| 可哈希 | ID 必须可以作为 Map 的键 | ❌ 使用对象作为 ID |

#### 正确的 keyGenerator 示例

```typescript
// ✅ 正确：使用数据项的唯一标识
ForEach(this.users, (user: User) => user.id, ...)

// ✅ 正确：使用复合键
ForEach(this.items, (item: Item) => `${item.type}_${item.id}`, ...)

// ❌ 错误：使用索引（数据变化时 ID 不稳定）
ForEach(this.items, (item: Item, index: number) => index, ...)

// ❌ 错误：使用随机值（每次生成都不同）
ForEach(this.items, (item: Item) => Math.random(), ...)
```

**源码位置**:
- ID 存储: `for_each_node.h:83` - `ids_` 成员变量
- 临时 ID: `for_each_node.h:86` - `tempIds_` 成员变量

---

### 拖拽排序

#### 拖拽事件流

```
用户长按
    ↓
onLongPress 触发
    ↓
开始拖拽
    ↓
onDragStart 触发
    ↓
拖拽移动过程中
    ↓
onMoveThrough 触发（持续触发）
    ↓
用户松手
    ↓
onDrop 触发
    ↓
数据更新（MoveData）
    ↓
onMove 触发（通知最终位置）
```

#### 拖拽 API 设置

**源码位置**: `for_each_node.h:72-74`

```cpp
void SetItemDragHandler(
    std::function<void(int32_t)>&& onLongPress,      // 长按开始
    std::function<void(int32_t)>&& onDragStart,       // 拖拽开始
    std::function<void(int32_t, int32_t)>&& onMoveThrough, // 拖拽经过
    std::function<void(int32_t)>&& onDrop            // 拖拽结束
);
```

#### 拖拽实现示例

```typescript
ForEach(this.items, (item: Item) => item.id, (item: Item) => {
  ListItem() {
    Text(item.name)
  }
  .transition(TransitionType.All, AnimationCurve.Ease)
  .onDragStart((event: DragEvent) => {
    // 拖拽开始
    this.isDragging = true
  })
  .onDrop((event: DragEvent) => {
    // 拖拽结束
    this.isDragging = false
  })
})
.onMove((from: number, to: number) => {
  // 数据移动
  const item = this.items.splice(from, 1)[0]
  this.items.splice(to, 0, item)
})
```

#### 拖拽性能优化

1. **启用 Transition**: 使用 `.transition()` 启用动画过渡
2. **延迟布局**: 拖拽过程中延迟布局计算

---

## 布局算法

### Measure 流程

ForEach 的布局算法遵循 NG Pattern 的标准流程：

```
ForEachNode::OnDirtyLayoutWrapperSwap()
    ↓
LayoutWrapper::Measure()
    ↓
遍历子组件，对每个子组件调用 Measure()
    ↓
计算总尺寸（累加所有子组件尺寸）
    ↓
ForEachNode 自身的 Measure 结果
```

### Layout 流程

```
ForEachNode::OnDirtyLayoutWrapperSwap()
    ↓
LayoutWrapper::Layout()
    ↓
根据子组件顺序，计算每个子组件的位置
    ↓
应用 Offset 到每个子组件
    ↓
ForEachNode 自身的 Layout 结果
```

**源码位置**:
- Measure: `for_each_node.cpp` - `OnDirtyLayoutWrapperSwap()` 方法
- Layout: NG Pattern 标准布局算法

---

## 事件处理

### 支持的事件类型

ForEach 主要处理以下事件：

| 事件类型 | 触发时机 | 回调函数 |
|---------|---------|----------|
| onMove | 数据项位置移动 | `(from: number, to: number) => void` |
| onLongPress | 长按拖拽开始 | `(index: number) => void` |
| onDragStart | 拖拽开始 | `(index: number) => void` |
| onMoveThrough | 拖拽经过其他项 | `(from: number, through: number) => void` |
| onDrop | 拖拽结束 | `(index: number) => void` |

### 事件处理实现

**源码位置**: `for_each_base_node.h:30-63`

```cpp
// 拖拽相关事件回调
virtual void FireOnMove(int32_t from, int32_t to);
virtual void FireOnLongPress(int32_t index);
virtual void FireOnDragStart(int32_t index);
virtual void FireOnMoveThrough(int32_t from, int32_t through);
virtual void FireOnDrop(int32_t index);
```

---

## 完整 API 清单

### ArkTS API

#### 基本语法

```typescript
ForEach(
  arr: Array<any>,
  keyGenerator: (item: any, index?: number) => string,
  itemGenerator: (item: any, index?: number) => void
): void
```

#### 参数说明

| 参数 | 类型 | 必填 | 说明 |
|------|------|------|------|
| arr | `Array<any>` | 是 | 数据源数组 |
| keyGenerator | `(item, index?) => string` | 是 | ID 生成函数 |
| itemGenerator | `(item, index?) => void` | 是 | UI 生成函数 |

#### 示例

```typescript
@Entry
@Component
struct ForEachExample {
  @State fruits: Array<string> = ['Apple', 'Banana', 'Orange']

  build() {
    Column() {
      ForEach(
        this.fruits,
        (fruit: string, index: number) => `${fruit}_${index}`,
        (fruit: string, index: number) => {
          Text(`${index}: ${fruit}`)
            .fontSize(16)
            .margin(10)
        }
      )
    }
  }
}
```

### C++ API

#### ForEachNode 核心方法

**源码位置**: `for_each_node.h:36-80`

```cpp
class ACE_EXPORT ForEachNode : public ForEachBaseNode {
public:
    // 创建或获取 ForEachNode
    static RefPtr<ForEachNode> GetOrCreateForEachNode(int32_t nodeId);

    // 核心更新方法
    void CreateTempItems();
    void CollectRemovingIds(std::list<int32_t>& removedElmtId);
    void CompareAndUpdateChildren();
    void FlushUpdateAndMarkDirty() override;

    // ID 管理
    void SetIds(std::list<std::string>&& ids);
    const std::list<std::string>& GetTempIds() const;

    // 拖拽相关
    void SetItemDragHandler(/* ... */);
    void SetOnMove(std::function<void(int32_t, int32_t)>&& onMove);
    void MoveData(int32_t from, int32_t to) override;
    RefPtr<FrameNode> GetFrameNode(int32_t index) override;
};
```

---

## 使用示例

### 示例 1: 基本列表渲染

```typescript
@Entry
@Component
struct BasicForEach {
  @State items: Array<string> = ['Item 1', 'Item 2', 'Item 3']

  build() {
    Column() {
      ForEach(
        this.items,
        (item: string) => item,  // 使用 item 本身作为 ID
        (item: string) => {
          Text(item)
            .fontSize(18)
            .padding(10)
            .margin(5)
            .backgroundColor('#f0f0f0')
            .borderRadius(5)
        }
      )
    }
    .width('100%')
    .padding(20)
  }
}
```

### 示例 2: 数据对象列表

```typescript
interface User {
  id: number
  name: string
  age: number
}

@Entry
@Component
struct UserList {
  @State users: Array<User> = [
    { id: 1, name: 'Alice', age: 25 },
    { id: 2, name: 'Bob', age: 30 },
    { id: 3, name: 'Charlie', age: 35 }
  ]

  build() {
    List() {
      ForEach(
        this.users,
        (user: User) => user.id.toString(),  // 使用唯一 ID
        (user: User) => {
          ListItem() {
            Row() {
              Text(user.name)
                .fontSize(16)
              Text(`${user.age} years old`)
                .fontSize(14)
                .margin({ left: 10 })
            }
            .width('100%')
            .padding(10)
          }
        }
      )
    }
    .width('100%')
    .height('100%')
  }
}
```

### 示例 3: 动态数据更新

```typescript
@Entry
@Component
struct DynamicForEach {
  @State numbers: Array<number> = [1, 2, 3, 4, 5]

  build() {
    Column() {
      Button('Add Number')
        .onClick(() => {
          this.numbers.push(this.numbers.length + 1)
        })
        .margin(10)

      Button('Remove Last')
        .onClick(() => {
          if (this.numbers.length > 0) {
            this.numbers.pop()
          }
        })
        .margin(10)

      ForEach(
        this.numbers,
        (num: number) => `num_${num}`,
        (num: number) => {
          Text(`Number: ${num}`)
            .fontSize(16)
            .padding(10)
            .margin(5)
        }
      )
    }
    .width('100%')
    .padding(20)
  }
}
```

### 示例 4: 拖拽排序

```typescript
@Entry
@Component
struct DraggableForEach {
  @State items: Array<string> = [
    'Item 1', 'Item 2', 'Item 3', 'Item 4', 'Item 5'
  ]

  build() {
    Column() {
      ForEach(
        this.items,
        (item: string) => item,
        (item: string) => {
          Text(item)
            .fontSize(16)
            .padding(15)
            .margin(5)
            .backgroundColor('#e0e0e0')
            .borderRadius(8)
            .width('90%')
            .textAlign(TextAlign.Center)
            .transition(TransitionType.All, AnimationCurve.Ease)
            .onDragStart((event: DragEvent) => {
              console.info(`Drag start: ${item}`)
            })
            .onDrop((event: DragEvent) => {
              console.info(`Drop: ${item}`)
            })
        }
      )
    }
    .onMove((from: number, to: number) => {
      // 更新数据源
      const item = this.items.splice(from, 1)[0]
      this.items.splice(to, 0, item)
    })
    .width('100%')
    .height('100%')
  }
}
```

### 示例 5: 嵌套 ForEach

```typescript
interface Category {
  id: number
  name: string
  items: Array<string>
}

@Entry
@Component
struct NestedForEach {
  @State categories: Array<Category> = [
    {
      id: 1,
      name: 'Fruits',
      items: ['Apple', 'Banana', 'Orange']
    },
    {
      id: 2,
      name: 'Vegetables',
      items: ['Carrot', 'Potato', 'Tomato']
    }
  ]

  build() {
    Column() {
      ForEach(
        this.categories,
        (category: Category) => category.id.toString(),
        (category: Category) => {
          Column() {
            Text(category.name)
              .fontSize(20)
              .fontWeight(FontWeight.Bold)
              .margin({ top: 10, bottom: 5 })

            ForEach(
              category.items,
              (item: string) => `${category.id}_${item}`,
              (item: string) => {
                Text(`  - ${item}`)
                  .fontSize(16)
                  .margin(2)
              }
            )
          }
          .width('100%')
          .padding(10)
          .backgroundColor('#f5f5f5')
          .borderRadius(8)
          .margin(5)
        }
      )
    }
    .width('100%')
    .padding(15)
  }
}
```

---

## 调试指南

### 日志系统

ForEach 使用 ACE 的标准日志系统。启用日志：

```bash
# 设置日志级别
hdc shell shell_hilog -b D
hdc shell shell_hilog -t ACE | grep ForEach
```

### 关键日志标签

| 日志标签 | 用途 | 源码位置 |
|---------|------|----------|
| ACE_FOREACH | ForEach 核心逻辑 | `for_each_node.cpp` |
| ACE_VIEW | 视图更新 | `for_each_model_impl.cpp` |

### 常见问题排查

#### 问题 1: 组件状态丢失

**症状**: 数据更新后，子组件的状态（如输入框内容）丢失

**原因**: `keyGenerator` 返回的 ID 不稳定，导致组件被重新创建

**解决方案**:
```typescript
// ❌ 错误：使用索引作为 ID
ForEach(this.items, (item, index) => index, ...)

// ✅ 正确：使用数据项的唯一标识
ForEach(this.items, (item) => item.id, ...)
```

#### 问题 2: 性能问题

**症状**: 数据量大时（> 1000 项）滚动卡顿

**原因**: ForEach 全量渲染所有子组件

**解决方案**:
- 减少数据项数量
- 简化子组件结构
- 优化渲染性能

#### 问题 3: 拖拽不生效

**症状**: 拖拽时没有任何反应

**原因**: 未正确设置 `onMove` 回调

**解决方案**:
```typescript
Column() {
  ForEach(...)
}
.onMove((from: number, to: number) => {
  // 必须更新数据源
  const item = this.items.splice(from, 1)[0]
  this.items.splice(to, 0, item)
})
```

---

## 最佳实践

### 1. keyGenerator 设计

**原则**:
- 使用数据项的唯一标识符
- 确保在数据更新前后保持一致
- 避免使用索引或随机值

**推荐方案**:
```typescript
// ✅ 方案 1: 使用唯一 ID
ForEach(items, (item) => item.id, ...)

// ✅ 方案 2: 使用复合键
ForEach(items, (item) => `${item.type}_${item.id}`, ...)

// ✅ 方案 3: 使用内容哈希（无 ID 时）
ForEach(items, (item) => HashCode(item), ...)
```

### 2. 性能优化

#### 中小型数据集（< 1000）

```typescript
// ✅ 使用 ForEach
ForEach(this.items, (item) => item.id, (item) => {
  ItemComponent({ data: item })
})
```

#### 大型数据集（> 1000）

```typescript
// ⚠️ 考虑使用 LazyForEach
LazyForEach(this.dataSource, (item) => item.id, (item) => {
  ItemComponent({ data: item })
})
```

### 3. 状态管理

```typescript
@Component
struct ItemComponent {
  @Prop item: Item          // 父组件传递的数据
  @State isSelected: boolean = false  // 组件内部状态

  build() {
    Row() {
      Text(this.item.name)
      Checkbox()
        .select(this.isSelected)
        .onChange((value: boolean) => {
          this.isSelected = value  // 内部状态更新
        })
    }
  }
}
```

### 4. 嵌套使用

```typescript
ForEach(
  this.categories,
  (category) => category.id,
  (category) => {
    Column() {
      Text(category.name)

      // 嵌套 ForEach 时，确保 ID 唯一性
      ForEach(
        category.items,
        (item) => `${category.id}_${item.id}`,
        (item) => {
          ItemComponent({ data: item })
        }
      )
    }
  }
)
```

### 5. 错误处理

```typescript
ForEach(
  this.items.filter(item => item.isValid),  // 过滤无效数据
  (item) => item.id,
  (item) => {
    if (item.id) {  // 检查 ID 有效性
      ValidItemComponent({ data: item })
    } else {
      ErrorComponent({ message: 'Invalid item' })
    }
  }
)
```

---

## Arkoala 前端支持

### ArkoalaForEachNode

Arkoala 语言也支持 ForEach 功能，通过 `ArkoalaForEachNode` 实现。

### Arkoala vs ArkTS ForEach

| 特性 | ArkTS ForEachNode | Arkoala ArkoalaForEachNode |
|------|-------------------|---------------------------|
| 前端语言 | ArkTS/TypeScript | Arkoala |
| 基类 | ForEachBaseNode | ForEachBaseNode |
| 核心接口 | 一致 | 一致 |
| 源码位置 | `for_each_node.cpp` | `arkoala_for_each_node.cpp` |

### Arkoala API

```arkoala
// Arkoala 伪代码示例
ForEach(
  array: Array<Item>,
  keyGenerator: (item: Item) => String,
  itemGenerator: (item: Item) => Unit
): Unit
```

---

## 相关资源

### 源码文件

- **Pattern Node**: `frameworks/core/components_ng/syntax/for_each_node.cpp` (16,144 行)
- **Base Class**: `frameworks/core/components_ng/syntax/for_each_base_node.h` (77 行)
- **Frontend Bridge**: `frameworks/bridge/declarative_frontend/jsview/models/for_each_model_impl.cpp` (~85 行)

### 相关文档

- [Syntax 模块架构总览](./Syntax_Architecture_Overview.md)

### API 参考

- [ForEach API 参考](https://developer.huawei.com/consumer/cn/doc/harmonyos-references/ts-rendering-control-foreach)
- [ForEach 开发指南](https://developer.huawei.com/consumer/cn/doc/harmonyos-guides/arkts-rendering-control-foreach)

---

**文档结束**

如有疑问或建议，请通过以下方式反馈：
- 提交 Issue 到代码仓库
- 联系框架团队
