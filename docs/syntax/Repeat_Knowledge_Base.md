# Repeat 组件知识库

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
  - [简单重复渲染](#简单重复渲染)
  - [数值参数驱动](#数值参数驱动)
- [布局算法](#布局算法)
- [完整 API 清单](#完整-api-清单)
- [使用示例](#使用示例)
- [调试指南](#调试指南)
- [最佳实践](#最佳实践)

---

## 概述

### 组件定位

**Repeat** 是 OpenHarmony ArkUI 框架中用于**简单重复渲染**的组件。它根据指定的重复次数，多次渲染相同的子组件结构。

### 核心特性

- **数值参数驱动**: 通过重复次数参数控制渲染数量
- **全量渲染**: 渲染所有指定次数的组件
- **状态保留**: 每个重复的子组件独立维护状态
- **简单易用**: API 简洁，适合静态或简单的重复场景

---

## 完整调用链

### ArkTS → Pattern Node 调用流程

```
┌─────────────────────────────────────────────────────────────────┐
│  ArkTS 前端代码                                                  │
│  Repeat(this.valueArray, (item: Item, index: number) => { })    │
└─────────────────────────────────────────────────────────────────┘
                            ↓
┌─────────────────────────────────────────────────────────────────┐
│  Declarative Frontend (声明式前端)                               │
│  frameworks/bridge/declarative_frontend/jsview/models/          │
│    repeat_model_impl.cpp                                        │
│    - RepeatModelImpl::Create()                                  │
│    - 创建 RepeatComponent                                        │
└─────────────────────────────────────────────────────────────────┘
                            ↓
┌─────────────────────────────────────────────────────────────────┐
│  Pattern Node (语法节点层)                                       │
│  frameworks/core/components_ng/syntax/repeat_node.cpp          │
│    - RepeatNode::GetOrCreateRepeatNode()                        │
│    - RepeatNode::CreateTempItems()                              │
│    - RepeatNode::FinishRepeatRender()                           │
│    - RepeatNode::FlushUpdateAndMarkDirty()                      │
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
- 前端桥接: `frameworks/bridge/declarative_frontend/jsview/models/repeat_model_impl.cpp`
- Pattern Node: `frameworks/core/components_ng/syntax/repeat_node.cpp`

---

## 目录结构

### 源码文件组织

```
frameworks/core/components_ng/syntax/
├── for_each_base_node.h                 # 基类（77 行）
├── repeat_node.h                        # RepeatNode 头文件
├── repeat_node.cpp                      # RepeatNode 实现（10656 行）
└── repeat_model_ng.cpp                  # Model 层接口

frameworks/bridge/declarative_frontend/
├── jsview/models/
│   └── repeat_model_impl.cpp            # 前端 Model 实现
└── ark_node/types/
    └── repeat.d.ts                      # TypeScript 类型定义
```

### 代码规模

| 文件 | 行数 | 说明 |
|------|------|------|
| repeat_node.cpp | 10,656 | 核心实现 |
| repeat_node.h | ~95 | 接口定义 |
| for_each_base_node.h | 77 | 基类定义 |
| repeat_model_impl.cpp | ~80 | 前端桥接 |
| **总计** | **~10,908** | **Repeat 完整实现** |

---

## 类继承关系

### 继承体系

```
UINode (frameworks/core/components_ng/base/ui_node.h)
    ↓
ForEachBaseNode (frameworks/core/components_ng/syntax/for_each_base_node.h)
    ↓
RepeatNode (frameworks/core/components_ng/syntax/repeat_node.h)
```

### RepeatNode 类结构

**源码位置**: `repeat_node.h:31-90`

```cpp
class ACE_EXPORT RepeatNode : public ForEachBaseNode {
public:
    static RefPtr<RepeatNode> GetOrCreateRepeatNode(int32_t nodeId);

    explicit RepeatNode(int32_t nodeId)
        : ForEachBaseNode(V2::JS_REPEAT_ETS_TAG, nodeId) {}

    // 核心方法
    void CreateTempItems();
    void FinishRepeatRender(std::list<int32_t>& removedElmtId);
    void FlushUpdateAndMarkDirty() override;

    // ID 管理
    void SetIds(std::list<std::string>&& ids);
    const std::list<std::string>& GetTempIds() const;

    // 移动子组件
    void MoveChild(uint32_t fromIndex);
    void MoveData(int32_t from, int32_t to) override;
    RefPtr<FrameNode> GetFrameNode(int32_t index) override;

    // 拖拽支持
    void SetItemDragHandler(
        std::function<void(int32_t)>&& onLongPress,
        std::function<void(int32_t)>&& onDragStart,
        std::function<void(int32_t, int32_t)>&& onMoveThrough,
        std::function<void(int32_t)>&& onDrop);
    void SetOnMove(std::function<void(int32_t, int32_t)>&& onMove);

private:
    std::list<std::string> ids_;              // ID 列表
    int32_t from_ = -1;                        // 起始索引
    int32_t to_ = -1;                          // 结束索引
    std::list<std::string> tempIds_;          // 临时 ID 列表
    std::list<RefPtr<UINode>> tempChildren_;  // 临时子组件列表
    std::vector<RefPtr<UINode>> tempChildrenOfRepeat_; // Repeat 子组件
};
```

---

## 核心功能

### 简单重复渲染

#### 工作原理

Repeat 通过数值参数控制重复次数，每次迭代生成一个子组件：

```
重复次数 = 数组长度
    ↓
遍历数组 [0, 1, 2, ..., count-1]
    ↓
每次迭代调用 itemGenerator(index)
    ↓
创建对应的子组件
    ↓
添加到渲染树
```

#### 渲染流程

```cpp
// 伪代码示例
void RepeatNode::CreateTempItems() {
    // 1. 根据数组长度计算重复次数
    int32_t count = array.length;

    // 2. 遍历索引
    for (int32_t index = 0; index < count; index++) {
        // 3. 为每个索引生成唯一 ID
        std::string id = GenerateId(index);

        // 4. 调用 itemGenerator 创建子组件
        auto child = itemGenerator(index);

        // 5. 添加到临时列表
        tempChildren_.push_back(child);
        tempIds_.push_back(id);
    }

    // 6. 完成渲染
    FinishRepeatRender();
}
```

**源码位置**: `repeat_node.cpp` - `CreateTempItems()` 和 `FinishRepeatRender()` 方法

---

### 数值参数驱动

#### 参数类型

Repeat 接受一个数组作为参数，重复次数等于数组长度：

```typescript
Repeat(
  valueArray: Array<any>,
  itemGenerator: (item: any, index: number) => void
): void
```

#### 参数说明

| 参数 | 类型 | 必填 | 说明 |
|------|------|------|------|
| valueArray | `Array<any>` | 是 | 数组，重复次数 = 数组长度 |
| itemGenerator | `(item, index) => void` | 是 | 每次迭代执行的生成函数 |

#### 使用特点

- **数值驱动**: 重复次数由数组长度决定，而非数据内容
- **索引可用**: itemGenerator 接收当前项和索引
- **内容无关**: 数组元素值不影响渲染结果（除非 itemGenerator 使用）

---

## 布局算法

### Measure 流程

```
RepeatNode::OnDirtyLayoutWrapperSwap()
    ↓
LayoutWrapper::Measure()
    ↓
遍历所有子组件，对每个子组件调用 Measure()
    ↓
计算总尺寸（累加所有子组件尺寸）
    ↓
RepeatNode 自身的 Measure 结果
```

### Layout 流程

```
RepeatNode::OnDirtyLayoutWrapperSwap()
    ↓
LayoutWrapper::Layout()
    ↓
根据子组件顺序，计算每个子组件的位置
    ↓
应用 Offset 到每个子组件
    ↓
RepeatNode 自身的 Layout 结果
```

**源码位置**:
- Measure: `repeat_node.cpp` - `OnDirtyLayoutWrapperSwap()` 方法
- Layout: NG Pattern 标准布局算法

---

## 完整 API 清单

### ArkTS API

#### 基本语法

```typescript
Repeat(
  valueArray: Array<any>,
  itemGenerator: (item: any, index: number) => void
): void
```

#### 参数说明

| 参数 | 类型 | 必填 | 说明 |
|------|------|------|------|
| valueArray | `Array<any>` | 是 | 数组，重复次数 = 数组长度 |
| itemGenerator | `(item, index?) => void` | 是 | UI 生成函数 |

#### 示例

```typescript
@Entry
@Component
struct RepeatExample {
  build() {
    Column() {
      // 重复 5 次
      Repeat([1, 2, 3, 4, 5], (item: number, index: number) => {
        Text(`Item ${index}`)
          .fontSize(16)
          .padding(10)
      })
    }
  }
}
```

### C++ API

#### RepeatNode 核心方法

**源码位置**: `repeat_node.h:35-75`

```cpp
class ACE_EXPORT RepeatNode : public ForEachBaseNode {
public:
    // 创建或获取 RepeatNode
    static RefPtr<RepeatNode> GetOrCreateRepeatNode(int32_t nodeId);

    // 核心渲染方法
    void CreateTempItems();
    void FinishRepeatRender(std::list<int32_t>& removedElmtId);
    void FlushUpdateAndMarkDirty() override;

    // ID 管理
    void SetIds(std::list<std::string>&& ids);
    const std::list<std::string>& GetTempIds() const;

    // 移动子组件
    void MoveChild(uint32_t fromIndex);
    void MoveData(int32_t from, int32_t to) override;
    RefPtr<FrameNode> GetFrameNode(int32_t index) override;
};
```

---

## 使用示例

### 示例 1: 基本重复

```typescript
@Entry
@Component
struct BasicRepeat {
  build() {
    Column() {
      // 重复 5 次，渲染 5 个 Text 组件
      Repeat([1, 2, 3, 4, 5], (item: number, index: number) => {
        Text(`Item ${index}`)
          .fontSize(18)
          .padding(10)
          .margin(5)
          .backgroundColor('#f0f0f0')
          .borderRadius(5)
      })
    }
    .width('100%')
    .padding(20)
  }
}
```

### 示例 2: 使用数组值

```typescript
@Entry
@Component
struct RepeatWithValues {
  private colors: Array<string> = ['#FF0000', '#00FF00', '#0000FF', '#FFFF00', '#FF00FF']

  build() {
    Column() {
      Repeat(this.colors, (color: string, index: number) => {
        Text(`Color ${index}: ${color}`)
          .fontSize(16)
          .fontColor(color)
          .padding(10)
          .margin(5)
      })
    }
    .width('100%')
    .padding(20)
  }
}
```

### 示例 3: 动态重复次数

```typescript
@Entry
@Component
struct DynamicRepeat {
  @State repeatCount: number = 3

  build() {
    Column() {
      Row() {
        Button('Increase')
          .onClick(() => {
            if (this.repeatCount < 10) {
              this.repeatCount++
            }
          })
          .margin(10)

        Button('Decrease')
          .onClick(() => {
            if (this.repeatCount > 0) {
              this.repeatCount--
            }
          })
          .margin(10)
      }

      // 根据状态值生成数组
      Repeat(Array.from({ length: this.repeatCount }, (_, i) => i),
        (item: number, index: number) => {
          Text(`Repeated Item ${index}`)
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

### 示例 4: 嵌套 Repeat

```typescript
@Entry
@Component
struct NestedRepeat {
  build() {
    Column() {
      // 外层 Repeat：3 行
      Repeat([0, 1, 2], (rowItem: number, rowIndex: number) => {
        Row() {
          // 内层 Repeat：每行 4 列
          Repeat([0, 1, 2, 3], (colItem: number, colIndex: number) => {
            Text(`(${rowIndex}, ${colIndex})`)
              .fontSize(14)
              .width(80)
              .height(40)
              .textAlign(TextAlign.Center)
              .backgroundColor('#e0e0e0')
              .borderRadius(4)
              .margin(2)
          })
        }
        .justifyContent(FlexAlign.Center)
        .margin(5)
      })
    }
    .width('100%')
    .padding(20)
  }
}
```

### 示例 5: 带索引的卡片

```typescript
@Entry
@Component
struct CardRepeat {
  build() {
    Column() {
      Repeat([1, 2, 3, 4, 5], (item: number, index: number) => {
        Row() {
          Text(`Card ${index + 1}`)
            .fontSize(20)
            .fontWeight(FontWeight.Bold)

          Blank()

          Text(`#${item}`)
            .fontSize(16)
            .fontColor('#666666')
        }
        .width('90%')
        .height(60)
        .padding(15)
        .backgroundColor('#ffffff')
        .borderRadius(10)
        .shadow({ radius: 5, color: '#1f000000', offsetX: 0, offsetY: 2 })
        .margin(10)
      })
    }
    .width('100%')
    .height('100%')
    .backgroundColor('#f5f5f5')
  }
}
```

---

## 调试指南

### 日志系统

Repeat 使用 ACE 的标准日志系统。启用日志：

```bash
# 设置日志级别
hdc shell shell_hilog -b D
hdc shell shell_hilog -t ACE | grep Repeat
```

### 关键日志标签

| 日志标签 | 用途 | 源码位置 |
|---------|------|----------|
| ACE_REPEAT | Repeat 核心逻辑 | `repeat_node.cpp` |
| ACE_VIEW | 视图更新 | `repeat_model_impl.cpp` |

### 常见问题排查

#### 问题 1: 组件不显示

**症状**: Repeat 渲染空白

**原因**:
- 数组为空
- itemGenerator 未返回有效组件

**解决方案**:
```typescript
// ✅ 确保数组非空
Repeat([1, 2, 3], (item, index) => {
  Text(`Item ${index}`)  // 确保返回有效组件
})

// ❌ 错误：空数组
Repeat([], (item, index) => {
  Text(`Item ${index}`)
})
```

#### 问题 2: 索引值不正确

**症状**: index 参数显示不正确

**原因**: index 是从 0 开始的数组索引

**解决方案**:
```typescript
// ✅ 正确：从 0 开始
Repeat([1, 2, 3], (item, index) => {
  Text(`Index: ${index}`)  // 0, 1, 2
})

// ✅ 如果需要从 1 开始
Repeat([1, 2, 3], (item, index) => {
  Text(`Item: ${index + 1}`)  // 1, 2, 3
})
```

#### 问题 3: 性能问题

**症状**: 重复次数过多时卡顿

**原因**: Repeat 是全量渲染，大量重复时性能下降

**解决方案**:
```typescript
// ✅ 控制重复次数在合理范围内
Repeat(Array.from({ length: 50 }, (_, i) => i), ...)
```

---

## 最佳实践

### 1. 避免不必要的嵌套

```typescript
// ❌ 避免：过深的嵌套
Repeat([1, 2, 3], (item1, index1) => {
  Repeat([1, 2, 3], (item2, index2) => {
    Repeat([1, 2, 3], (item3, index3) => {
      Component()
    })
  })
})

// ✅ 推荐：使用扁平化结构
Column() {
  Repeat([1, 2, 3, 4, 5, 6, 7, 8, 9], (item, index) => {
    Component()
  })
}
```

### 2. 使用有意义的数组

```typescript
// ✅ 推荐：使用有意义的数组标识重复次数
Repeat(this.colors, (color, index) => {
  ColorBox({ color: color, index: index })
})

// ⚠️ 谨慎：仅使用计数
Repeat(Array.from({ length: count }), (_, index) => {
  SimpleBox({ index: index })
})
```

### 3. 保持 itemGenerator 简单

```typescript
// ✅ 推荐：简单的生成器
Repeat([1, 2, 3], (item, index) => {
  Text(`Item ${index}`)
})

// ❌ 避免：复杂的逻辑
Repeat([1, 2, 3], (item, index) => {
  // 复杂的计算和逻辑
  const result = complexCalculation(index)
  const style = computeStyle(result)

  Column() {
    // 大量嵌套组件
  }
})
```

### 4. 动态调整重复次数

```typescript
@Entry
@Component
struct AdaptiveRepeat {
  @State displayCount: number = 5

  build() {
    Column() {
      // 根据条件生成数组
      Repeat(
        Array.from({ length: this.displayCount }, (_, i) => i),
        (item, index) => {
          Text(`Item ${index}`)
        }
      )

      Button('Show More')
        .onClick(() => {
          if (this.displayCount < 20) {
            this.displayCount += 5
          }
        })
    }
  }
}
```

---

## 相关资源

### 源码文件

- **Pattern Node**: `frameworks/core/components_ng/syntax/repeat_node.cpp` (10,656 行)
- **Base Class**: `frameworks/core/components_ng/syntax/for_each_base_node.h` (77 行)
- **Frontend Bridge**: `frameworks/bridge/declarative_frontend/jsview/models/repeat_model_impl.cpp` (~80 行)

### 相关文档

- [Syntax 模块架构总览](./Syntax_Architecture_Overview.md)

### API 参考

- [Repeat API 参考](https://developer.huawei.com/consumer/cn/doc/harmonyos-references/ts-rendering-control-repeat)
- [Repeat 开发指南](https://developer.huawei.com/consumer/cn/doc/harmonyos-guides/arkts-new-rendering-control-repeat)

---

**文档结束**

如有疑问或建议，请通过以下方式反馈：
- 提交 Issue 到代码仓库
- 联系框架团队
