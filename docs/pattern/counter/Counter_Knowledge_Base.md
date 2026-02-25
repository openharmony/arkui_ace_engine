# ArkUI Counter 组件完整知识库

> **文档版本**：v1.0
> **更新时间**：2026-02-01
> **源码版本**：OpenHarmony ace_engine (master 分支)
> **作者**：基于 CLAUDE.md 规范自动生成

---

## 📚 目录

1. [概述](#概述)
2. [完整调用链](#完整调用链)
3. [目录结构](#目录结构)
4. [核心类继承关系](#核心类继承关系)
5. [Pattern层详解](#pattern层详解)
6. [Model层详解](#model层详解)
7. [LayoutAlgorithm层详解](#layoutalgorithm层详解)
8. [属性系统](#属性系统)
9. [按钮控制](#按钮控制)
10. [特殊功能](#特殊功能)
11. [执行流程](#执行流程)
12. [完整API清单](#完整api清单)
13. [关键实现细节](#关键实现细节)
14. [使用示例](#使用示例)
15. [调试指南](#调试指南)
16. [常见问题](#常见问题)
17. [附录](#附录)

---

## 概述

### 组件定位

**Counter 组件**是 OpenHarmony ArkUI 框架中的**计数器组件**，提供数值的增加、减少操作，由减号按钮、内容区域、加号按钮三部分组成，常用于数量选择、数值调整等场景。

**技术栈**：
- **前端**：ArkTS/TypeScript
- **桥接层**：CounterModelNG
- **核心层**：NG Pattern 架构 (CounterPattern)
- **布局算法**：CounterLayoutAlgorithm
- **渲染层**：Rosen + Skia

**代码规模**：
- 总文件数：约 15 个文件
- 核心代码：约 2,500+ 行 C++ 代码
- 涉及 4 个架构层次

### 功能特性

Counter 组件支持：
- **三个子节点**：
  - 减号按钮（-）- 减少数值
  - 内容区域 - 显示当前数值
  - 加号按钮（+）- 增加数值
- **按钮控制**：
  - 启用/禁用加号按钮
  - 启用/禁用减号按钮
  - 禁用时显示半透明效果
- **尺寸设置**：
  - 自定义高度和宽度
  - 控制按钮宽度（预留功能）
- **样式设置**：
  - 背景颜色
  - 边框样式
  - 文本颜色
- **事件回调**：
  - onInc - 加号按钮点击
  - onDec - 减号按钮点击
- **国际化支持**：
  - RTL/LTR 布局自动切换
  - 无障碍支持

### 设计模式

Counter 组件采用 **NG Pattern 架构**：

```
前端 (ArkTS)
    ↓ (Model Layer)
CounterModelNG (counter_model_ng.cpp)
    ↓ (NG Pattern Layer)
CounterPattern (counter_pattern.cpp)
    ├─ 减号按钮管理
    ├─ 内容区域管理
    └─ 加号按钮管理
    ↓ (NG LayoutAlgorithm Layer)
CounterLayoutAlgorithm (counter_layout_algorithm.cpp)
    ↓
渲染显示
```

### 核心概念

**Counter 结构**：
```
┌─────┬────────────┬─────┐
│  -  │   内容区域   │  +  │
└─────┴────────────┴─────┘
 减号    显示数值    加号
 按钮                按钮
```

**关键配置**：
- 无直接的 value 属性（由外部状态管理）
- 通过 onInc/onDec 回调处理值变化
- 支持自定义高度、宽度、背景色

---

## 完整调用链

### 1. 从 ArkTS 到 Pattern 的调用链

#### 调用链图

```
┌─────────────────────────────────────────────────────────┐
│ 前端 ArkTS                                                │
│                                                          │
│ Counter() {                                              │
│   // 子组件                                              │
│ }                                                       │
│   .height(40)                                           │
│   .width(200)                                           │
│   .enableInc(true)                                      │
│   .enableDec(true)                                      │
│   .onInc(() => {                                        │
│     console.info('Increment')                           │
│   })                                                    │
│   .onDec(() => {                                        │
│     console.info('Decrement')                           │
│   })                                                    │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│ Model Layer (NG)                                         │
│                                                          │
│ class CounterModelNG                                     │
│   源码：frameworks/core/components_ng/pattern/counter/   │
│         counter_model_ng.cpp                              │
│                                                          │
│ 关键方法：                                                │
│ - Create() - 创建 Counter 节点                           │
│ - SetEnableInc() - 设置加号按钮启用状态                 │
│ - SetEnableDec() - 设置减号按钮启用状态                 │
│ - SetHeight() - 设置高度                                │
│ - SetWidth() - 设置宽度                                 │
│ - SetBackgroundColor() - 设置背景色                     │
│ - SetOnInc() - 设置加号按钮事件                         │
│ - SetOnDec() - 设置减号按钮事件                         │
│                                                          │
│ 执行流程：                                                 │
│ 1. 创建 FrameNode (COUNTER_ETS_TAG)                     │
│ 2. 创建 CounterPattern                                  │
│ 3. 创建三个子节点                                       │
│ 4. 应用布局和绘制属性                                    │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│ Pattern Layer (业务逻辑)                                  │
│                                                          │
│ class CounterPattern : public LinearLayoutPattern         │
│   源码：frameworks/core/components_ng/pattern/counter/   │
│         counter_pattern.cpp                               │
│                                                          │
│ 核心职责：                                                │
│ - 管理三个子节点 ID                                     │
│ - 提供布局算法创建                                     │
│ - 处理主题更新                                          │
│ - 管理焦点模式                                          │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│ LayoutAlgorithm Layer (布局计算)                          │
│                                                          │
│ class CounterLayoutAlgorithm : public LayoutAlgorithm    │
│   源码：frameworks/core/components_ng/pattern/counter/   │
│         counter_layout_algorithm.cpp                      │
│                                                          │
│ 核心方法：                                                │
│ - Measure() - 测量三个子节点尺寸                         │
│ - Layout() - 布局三个子节点位置                          │
│ - LayoutItem() - 布局单侧按钮                            │
└─────────────────────────────────────────────────────────┘
                          ↓
                    [计数器显示在屏幕上]
```

### 2. 创建完整调用链

```
ArkTS: Counter()
    ↓
CounterModelNG::Create()
    ↓
CounterNode::GetOrCreateCounterNode(COUNTER_ETS_TAG)
    ↓
创建 CounterPattern
    ↓
创建三个子节点：
    ├─ 减号按钮 (Button)
    ├─ 内容区域 (Text)
    └─ 加号按钮 (Button)
    ↓
ViewStackProcessor::Push(frameNode)
    ↓
[创建完成]
```

### 3. 属性设置调用链

```
.enableInc(true)
    ↓
CounterModelNG::SetEnableInc(true)
    ↓
获取加号按钮节点
    ↓
ButtonEventHub::SetEnabled(true)
    ↓
更新透明度（禁用时为 0.4）
    ↓
[加号按钮启用]

.enableDec(false)
    ↓
CounterModelNG::SetEnableDec(false)
    ↓
获取减号按钮节点
    ↓
ButtonEventHub::SetEnabled(false)
    ↓
RenderContext::UpdateOpacity(0.4)
    ↓
[减号按钮禁用，半透明]
```

---

## 目录结构

### 完整目录树

```
frameworks/core/components_ng/pattern/counter/
├── counter_pattern.h                    # CounterPattern 主类定义
├── counter_pattern.cpp                  # CounterPattern 实现
├── counter_model_ng.h                   # NG Model 定义
├── counter_model_ng.cpp                 # NG Model 实现
├── counter_model.h                      # 基础 Model 接口
├── counter_layout_algorithm.h           # 布局算法定义
├── counter_layout_algorithm.cpp         # 布局算法实现
├── counter_layout_property.h            # 布局属性定义
├── counter_node.h                       # 节点定义
├── counter_node.cpp                     # 节点实现
├── counter_theme.h                      # 主题定义
├── counter_model_static.h               # 静态 Model 定义
├── counter_model_static.cpp             # 静态 Model 实现
│
└── Bridge 层 (桥接层)
    └── bridge/
        ├── counter_dynamic_modifier.cpp  # 动态修饰器
        ├── counter_static_modifier.cpp   # 静态修饰器
        ├── counter_dynamic_module.h      # 动态模块
        ├── counter_dynamic_module.cpp    # 动态模块实现
        ├── counter_model_impl.h          # 模型实现
        └── counter_model_impl.cpp        # 模型实现
```

### 关键文件说明

| 文件 | 职责 | 核心类/方法 |
|-----|------|-----------|
| **counter_pattern.h/cpp** | 核心业务逻辑 | `CounterPattern::GetSubId()`, `GetContentId()`, `GetAddId()` |
| **counter_layout_algorithm.h/cpp** | 布局计算 | `CounterLayoutAlgorithm::Measure()`, `Layout()` |
| **counter_model_ng.h/cpp** | ArkTS API 接口 | `CounterModelNG::Create()`, `SetEnableInc()`, `SetEnableDec()` |
| **counter_layout_property.h** | 布局属性定义 | 高度、宽度等属性 |
| **counter_node.h/cpp** | 节点管理 | `CounterNode::GetOrCreateCounterNode()` |
| **counter_theme.h** | 主题定义 | 默认样式、颜色、透明度 |

---

## 核心类继承关系

### 1. Pattern 层继承关系

```
Pattern<FrameNode> (基类)
    ↓
LinearLayoutPattern (线性布局 Pattern)
    ↓
CounterPattern (Counter 组件实现)
    ├─ 减号按钮管理
    ├─ 内容区域管理
    └─ 加号按钮管理
```

### 2. Model 层继承关系

```
CounterModel (基类)
    ↓
CounterModelNG (NG 架构实现)
    ├─ Create() - 创建组件
    ├─ SetEnableInc() - 设置加号按钮状态
    ├─ SetEnableDec() - 设置减号按钮状态
    ├─ SetHeight() - 设置高度
    ├─ SetWidth() - 设置宽度
    └─ SetBackgroundColor() - 设置背景色
```

### 3. LayoutAlgorithm 层继承关系

```
LayoutAlgorithm (基类)
    ↓
CounterLayoutAlgorithm (Counter 布局算法)
    └─ Measure() - 测量三个子节点
    └─ Layout() - 布局三个子节点
```

### 4. 关键类定义

#### CounterPattern

**文件**：[counter_pattern.h:30](frameworks/core/components_ng/pattern/counter/counter_pattern.h#L30)

```cpp
class CounterPattern : public LinearLayoutPattern {
    DECLARE_ACE_TYPE(CounterPattern, LinearLayoutPattern);

public:
    CounterPattern() = default;
    ~CounterPattern() override = default;

    // 创建布局算法
    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<CounterLayoutAlgorithm>();
    }

    // 创建布局属性
    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<CounterLayoutProperty>();
    }

    // 获取焦点模式
    FocusPattern GetFocusPattern() const override;

    // 节点 ID 管理
    bool HasSubNode() const;
    int32_t GetSubId();
    int32_t GetContentId();
    int32_t GetAddId();

    // 主题更新
    void OnColorConfigurationUpdate() override;

private:
    std::optional<int32_t> subId_;      // 减号按钮 ID
    std::optional<int32_t> contentId_;  // 内容区域 ID
    std::optional<int32_t> addId_;      // 加号按钮 ID
};
```

#### CounterModelNG

**文件**：[counter_model_ng.h:26](frameworks/core/components_ng/pattern/counter/counter_model_ng.h#L26)

```cpp
class ACE_EXPORT CounterModelNG : public OHOS::Ace::CounterModel {
public:
    // 创建 Counter
    void Create() override;

    // 设置事件回调
    void SetOnInc(CounterEventFunc&& onInc) override;
    void SetOnDec(CounterEventFunc&& onDec) override;

    // 设置尺寸
    void SetHeight(const Dimension& value) override;
    void SetWidth(const Dimension& value) override;

    // 设置按钮状态
    void SetEnableDec(bool enableDec) override;
    void SetEnableInc(bool enableInc) override;

    // 设置背景色
    void SetBackgroundColor(const Color& value) override;

    // 资源对象创建
    void CreateWithResourceObj(
        JsCounterResourceType resourceType,
        const RefPtr<ResourceObject>& resObj) override;

    // 静态方法
    static void SetEnableDec(FrameNode* frameNode, bool enableDec);
    static void SetEnableInc(FrameNode* frameNode, bool enableInc);
    static void SetHeight(FrameNode* frameNode, const Dimension& value);
    static void SetWidth(FrameNode* frameNode, const Dimension& value);
    static void SetBackgroundColor(FrameNode* frameNode, const Color& value);
    static void ResetBackgroundColor(FrameNode* frameNode);
    static void SetOnInc(FrameNode* frameNode, CounterEventFunc&& onInc);
    static void SetOnDec(FrameNode* frameNode, CounterEventFunc&& onDec);
};
```

---

## Pattern层详解

### CounterPattern 核心职责

**CounterPattern** 是 Counter 组件的核心逻辑层，负责：

1. **节点 ID 管理**
   - 管理减号按钮、内容区域、加号按钮的 ID
   - 提供 GetSubId(), GetContentId(), GetAddId() 方法

2. **布局算法创建**
   - 创建 CounterLayoutAlgorithm 实例
   - 创建 CounterLayoutProperty 实例

3. **主题更新**
   - 响应颜色配置变化
   - 更新按钮和文本样式

### 节点 ID 管理

#### GetSubId()

**源码位置**：[counter_pattern.h:39-49](frameworks/core/components_ng/pattern/counter/counter_pattern.h#L39-L49)

**功能**：获取或创建减号按钮 ID

```cpp
bool HasSubNode() const
{
    return subId_.has_value();
}

int32_t GetSubId()
{
    if (!subId_.has_value()) {
        subId_ = ElementRegister::GetInstance()->MakeUniqueId();
    }
    return subId_.value();
}
```

**说明**：
- 首次调用时创建唯一 ID
- 后续调用返回缓存的 ID
- 用于标识和访问减号按钮节点

#### GetContentId() / GetAddId()

**功能**：类似地管理内容区域和加号按钮的 ID

```cpp
int32_t GetContentId()
{
    if (!contentId_.has_value()) {
        contentId_ = ElementRegister::GetInstance()->MakeUniqueId();
    }
    return contentId_.value();
}

int32_t GetAddId()
{
    if (!addId_.has_value()) {
        addId_ = ElementRegister::GetInstance()->MakeUniqueId();
    }
    return addId_.value();
}
```

---

## Model层详解

### CounterModelNG 核心职责

**CounterModelNG** 提供 ArkTS 声明式 API，负责：

1. **创建 Counter 节点**
2. **创建三个子节点**（减号按钮、内容区域、加号按钮）
3. **设置属性**（尺寸、背景色、按钮状态）
4. **注册事件回调**（onInc、onDec）

### 关键 API 方法

#### 1. Create()

**源码位置**：[counter_model_ng.cpp:33-70](frameworks/core/components_ng/pattern/counter/counter_model_ng.cpp#L33-L70)

**功能**：创建 Counter FrameNode

```cpp
void CounterModelNG::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();

    // 创建 Counter 节点
    auto counterNode = CounterNode::GetOrCreateCounterNode(
        COUNTER_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<CounterPattern>(); });

    stack->Push(counterNode);

    // 创建减号按钮
    auto subNode = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<ButtonPattern>());
    subButtonPattern->SetButtonStyle(ButtonStyle::NORMAL);
    counterNode->AddChild(subNode);

    // 创建内容区域（文本）
    auto textNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<TextPattern>());
    counterNode->AddChild(textNode);

    // 创建加号按钮
    auto addNode = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<ButtonPattern>());
    addButtonPattern->SetButtonStyle(ButtonStyle::NORMAL);
    counterNode->AddChild(addNode);
}
```

**对应 ArkTS**：
```typescript
Counter() {
  // 内容
}
```

#### 2. SetEnableInc()

**源码位置**：[counter_model_ng.cpp:122-164](frameworks/core/components_ng/pattern/counter/counter_model_ng.cpp#L122-L164)

**功能**：设置加号按钮启用状态

```cpp
void CounterModelNG::SetEnableInc(bool enableInc)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = stack->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);

    auto pattern = frameNode->GetPattern<CounterPattern>();
    CHECK_NULL_VOID(pattern);

    // 获取加号按钮节点
    auto addId = pattern->GetAddId();
    auto addNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(addId));
    CHECK_NULL_VOID(addNode);

    // 设置启用状态
    auto eventHub = addNode->GetEventHub<ButtonEventHub>();
    eventHub->SetEnabled(enableInc);

    // 更新透明度
    auto renderContext = addNode->GetRenderContext();
    if (!eventHub->IsEnabled()) {
        renderContext->UpdateOpacity(counterTheme->GetAlphaDisabled()); // 0.4
    } else {
        renderContext->UpdateOpacity(1.0);
    }
}
```

**对应 ArkTS**：
```typescript
.enableInc(true)   // 启用加号按钮
.enableInc(false)  // 禁用加号按钮（半透明）
```

#### 3. SetEnableDec()

**功能**：设置减号按钮启用状态

**实现**：与 SetEnableInc 类似，但操作减号按钮节点

**对应 ArkTS**：
```typescript
.enableDec(true)   // 启用减号按钮
.enableDec(false)  // 禁用减号按钮（半透明）
```

#### 4. SetHeight() / SetWidth()

**源码位置**：[counter_model_ng.cpp:72-90](frameworks/core/components_ng/pattern/counter/counter_model_ng.cpp#L72-L90)

**功能**：设置 Counter 组件的高度和宽度

```cpp
void CounterModelNG::SetHeight(const Dimension& value)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = stack->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);

    auto layoutProperty = frameNode->GetLayoutProperty<CounterLayoutProperty>();
    layoutProperty->SetHeight(value);

    // 更新所有子节点的高度
    auto pattern = frameNode->GetPattern<CounterPattern>();
    UpdateChildHeight(pattern->GetSubId(), value);
    UpdateChildHeight(pattern->GetContentId(), value);
    UpdateChildHeight(pattern->GetAddId(), value);
}

void CounterModelNG::SetWidth(const Dimension& value)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = stack->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);

    auto layoutProperty = frameNode->GetLayoutProperty<CounterLayoutProperty>();
    layoutProperty->SetWidth(value);
}
```

**对应 ArkTS**：
```typescript
.height(40)
.width(200)
```

#### 5. SetBackgroundColor()

**源码位置**：[counter_model_ng.cpp:100-120](frameworks/core/components_ng/pattern/counter/counter_model_ng.cpp#L100-L120)

**功能**：设置背景颜色

```cpp
void CounterModelNG::SetBackgroundColor(const Color& value)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = stack->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);

    auto renderContext = frameNode->GetRenderContext();
    renderContext->UpdateBackgroundColor(value);
    renderContext->UpdateBackgroundFlag(true);
}
```

**对应 ArkTS**：
```typescript
.backgroundColor(Color.Red)
```

#### 6. 事件回调方法

**onInc**:
```cpp
void CounterModelNG::SetOnInc(CounterEventFunc&& onInc)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = stack->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);

    auto pattern = frameNode->GetPattern<CounterPattern>();
    CHECK_NULL_VOID(pattern);

    // 获取加号按钮节点
    auto addId = pattern->GetAddId();
    auto addNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(addId));
    CHECK_NULL_VOID(addNode);

    // 设置点击事件
    auto eventHub = addNode->GetEventHub<GestureEventHub>();
    eventHub->SetUserOnClick(std::move(onInc));
}
```

**对应 ArkTS**：
```typescript
.onInc(() => {
  console.info('Increment clicked')
})
```

**onDec**: 类似实现，但操作减号按钮

### 完整 API 映射表

| ArkTS API | CounterModelNG 方法 | 说明 |
|-----------|-------------------|------|
| `Counter()` | `Create()` | 创建组件 |
| `.enableInc(value)` | `SetEnableInc()` | 设置加号按钮状态 |
| `.enableDec(value)` | `SetEnableDec()` | 设置减号按钮状态 |
| `.height(value)` | `SetHeight()` | 设置高度 |
| `.width(value)` | `SetWidth()` | 设置宽度 |
| `.backgroundColor(value)` | `SetBackgroundColor()` | 设置背景色 |
| `.onInc(callback)` | `SetOnInc()` | 设置加号按钮事件 |
| `.onDec(callback)` | `SetOnDec()` | 设置减号按钮事件 |

---

## LayoutAlgorithm层详解

### CounterLayoutAlgorithm 核心职责

**CounterLayoutAlgorithm** 负责 Counter 的布局计算：

1. **Measure（测量）**：
   - 测量三个子节点的尺寸
   - 计算整体尺寸

2. **Layout（布局）**：
   - 布局三个子节点的位置
   - 处理 RTL/LTR 布局方向

### 节点索引常量

**定义**：[counter_layout_algorithm.cpp:25-29](frameworks/core/components_ng/pattern/counter/counter_layout_algorithm.cpp#L25-L29)

```cpp
constexpr int32_t SUB_BUTTON = 0;   // 减号按钮索引
constexpr int32_t CONTENT = 1;      // 内容区域索引
constexpr int32_t ADD_BUTTON = 2;   // 加号按钮索引
```

### Measure() 方法详解

**源码位置**：[counter_layout_algorithm.cpp:40-212](frameworks/core/components_ng/pattern/counter/counter_layout_algorithm.cpp#L40-L212)

**执行流程**：
```cpp
void CounterLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    // 1. 获取布局约束和属性
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    auto constraint = layoutProperty->GetLayoutConstraint();
    auto geometryNode = layoutWrapper->GetGeometryNode();

    // 2. 计算整体尺寸
    SizeF selfContentSize(frameSize.Width(), frameSize.Height());

    // 3. 测量内容区域
    auto contentWrapper = layoutWrapper->GetOrCreateChildByIndex(CONTENT);
    // ... 设置内容区域尺寸

    // 4. 测量减号按钮
    auto subButtonWrapper = layoutWrapper->GetOrCreateChildByIndex(SUB_BUTTON);
    // ... 设置按钮尺寸、边框、文本颜色

    // 5. 测量加号按钮
    auto addButtonWrapper = layoutWrapper->GetOrCreateChildByIndex(ADD_BUTTON);
    // ... 设置按钮尺寸、边框、文本颜色
}
```

### Layout() 方法详解

**源码位置**：[counter_layout_algorithm.cpp:256-264](frameworks/core/components_ng/pattern/counter/counter_layout_algorithm.cpp#L256-L264)

**执行流程**：
```cpp
void CounterLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    auto layoutDirection = layoutWrapper->GetLayoutProperty()->GetNonAutoLayoutDirection();

    // 根据布局方向决定按钮顺序
    if (layoutDirection == TextDirection::RTL) {
        // RTL：加号在左，减号在右
        LayoutItem(layoutWrapper, ADD_BUTTON, SUB_BUTTON);
    } else {
        // LTR：减号在左，加号在右
        LayoutItem(layoutWrapper, SUB_BUTTON, ADD_BUTTON);
    }
}
```

### LayoutItem() 方法

**源码位置**：[counter_layout_algorithm.cpp:214-254](frameworks/core/components_ng/pattern/counter/counter_layout_algorithm.cpp#L214-L254)

**功能**：布局三个子节点

```cpp
static void LayoutItem(LayoutWrapper* layoutWrapper, int32_t leftButton, int32_t rightButton)
{
    // 1. 布局左侧按钮
    auto leftButtonWrapper = layoutWrapper->GetOrCreateChildByIndex(leftButton);
    OffsetF leftButtonOffset(0.0f, 0.0f);
    leftButtonWrapper->GetGeometryNode()->SetMarginFrameOffset(leftButtonOffset);
    leftButtonWrapper->Layout();

    // 2. 布局内容区域（居中）
    auto contentWrapper = layoutWrapper->GetOrCreateChildByIndex(CONTENT);
    float contentX = leftButtonWrapper->GetGeometryNode()->GetFrameSize().Width();
    OffsetF contentOffset(contentX, 0.0f);
    contentWrapper->GetGeometryNode()->SetMarginFrameOffset(contentOffset);
    contentWrapper->Layout();

    // 3. 布局右侧按钮
    auto rightButtonWrapper = layoutWrapper->GetOrCreateChildByIndex(rightButton);
    float rightButtonX = contentX + contentWrapper->GetGeometryNode()->GetFrameSize().Width();
    OffsetF rightButtonOffset(rightButtonX, 0.0f);
    rightButtonWrapper->GetGeometryNode()->SetMarginFrameOffset(rightButtonOffset);
    rightButtonWrapper->Layout();
}
```

---

## 属性系统

### CounterLayoutProperty

**文件**：[counter_layout_property.h](frameworks/core/components_ng/pattern/counter/counter_layout_property.h)

**核心属性**：

```cpp
// 尺寸属性
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Height, Dimension, PROPERTY_UPDATE_LAYOUT);
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Width, Dimension, PROPERTY_UPDATE_LAYOUT);
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ControlWidth, Dimension, PROPERTY_UPDATE_LAYOUT);
```

### 属性传递流程

```
ArkTS API
    ↓
CounterModelNG::SetXXX()
    ↓
CounterLayoutProperty::UpdateXXX()
    ↓
FrameNode::MarkDirtyNode(PROPERTY_UPDATE_MEASURE)
    ↓
CounterLayoutAlgorithm::Measure()
    ↓
应用属性到子节点
```

---

## 按钮控制

### 启用/禁用状态

**实现机制**：
1. 通过 `ButtonEventHub::SetEnabled()` 设置启用状态
2. 通过 `RenderContext::UpdateOpacity()` 更新透明度
3. 禁用时透明度为 0.4，启用时为 1.0

**源码位置**：[counter_model_ng.cpp:122-164](frameworks/core/components_ng/pattern/counter/counter_model_ng.cpp#L122-L164)

```cpp
void CounterModelNG::SetEnableInc(bool enableInc)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = stack->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);

    auto pattern = frameNode->GetPattern<CounterPattern>();
    CHECK_NULL_VOID(pattern);

    // 获取加号按钮节点
    auto addId = pattern->GetAddId();
    auto addNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(addId));
    CHECK_NULL_VOID(addNode);

    // 设置启用状态
    auto eventHub = addNode->GetEventHub<ButtonEventHub>();
    eventHub->SetEnabled(enableInc);

    // 更新透明度
    auto renderContext = addNode->GetRenderContext();
    if (!eventHub->IsEnabled()) {
        renderContext->UpdateOpacity(counterTheme->GetAlphaDisabled()); // 0.4
    } else {
        renderContext->UpdateOpacity(1.0);
    }
}
```

### 透明度常量

**定义**：[counter_theme.h:29](frameworks/core/components/counter/counter_theme.h#L29)

```cpp
constexpr double BUTTON_ALPHA_DISABLED = 0.4;
```

**说明**：按钮禁用时显示为半透明（40% 不透明度）

---

## 特殊功能

### 1. RTL/LTR 布局支持

**功能**：根据文本方向自动调整按钮顺序

**实现**：[counter_layout_algorithm.cpp:256-264](frameworks/core/components_ng/pattern/counter/counter_layout_algorithm.cpp#L256-L264)

```cpp
void CounterLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    auto layoutDirection = layoutWrapper->GetLayoutProperty()->GetNonAutoLayoutDirection();

    if (layoutDirection == TextDirection::RTL) {
        // RTL：加号在左，减号在右
        LayoutItem(layoutWrapper, ADD_BUTTON, SUB_BUTTON);
    } else {
        // LTR：减号在左，加号在右
        LayoutItem(layoutWrapper, SUB_BUTTON, ADD_BUTTON);
    }
}
```

**布局对比**：
```
LTR (默认)：
┌─────┬────────────┬─────┐
│  -  │   内容区域   │  +  │
└─────┴────────────┴─────┘

RTL：
┌─────┬────────────┬─────┐
│  +  │   内容区域   │  -  │
└─────┴────────────┴─────┘
```

### 2. 主题系统

**支持的主题属性**：

**定义**：[counter_theme.h:140-152](frameworks/core/components/counter/counter_theme.h#L140-L152)

```cpp
class CounterTheme {
public:
    Dimension height_ = 32.0_vp;         // 默认高度
    Dimension width_ = 100.0_vp;        // 默认宽度
    Dimension controlWidth_ = 32.0_vp;   // 控制按钮宽度
    double alphaDisabled_ = 0.4;        // 禁用状态透明度

    // 颜色属性
    Color backgroundColor_;
    Color textColor_;
    Color buttonBackgroundColor_;
};
```

### 3. 资源对象支持

**功能**：支持通过资源对象设置属性

**实现**：[counter_model_ng.cpp:251-273](frameworks/core/components_ng/pattern/counter/counter_model_ng.cpp#L251-L273)

```cpp
void CounterModelNG::CreateWithResourceObj(
    JsCounterResourceType resourceType,
    const RefPtr<ResourceObject>& resObj)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = stack->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);

    switch (resourceType) {
        case JsCounterResourceType::Height:
            // 从资源对象获取高度
            SetHeight(frameNode, resObj->GetDimension());
            break;
        case JsCounterResourceType::Width:
            // 从资源对象获取宽度
            SetWidth(frameNode, resObj->GetDimension());
            break;
        case JsCounterResourceType::BackgroundColor:
            // 从资源对象获取背景色
            SetBackgroundColor(frameNode, resObj->GetColor());
            break;
    }
}
```

---

## 执行流程

### 1. 初始化流程

```
ArkTS: Counter()
    ↓
CounterModelNG::Create()
    ↓
CounterNode::GetOrCreateCounterNode(COUNTER_ETS_TAG)
    ↓
创建 CounterPattern
    ↓
创建三个子节点：
    ├─ 减号按钮 (ButtonPattern)
    ├─ 内容区域 (TextPattern)
    └─ 加号按钮 (ButtonPattern)
    ↓
添加子节点到 Counter 节点
    ↓
ViewStackProcessor::Push(counterNode)
    ↓
[初始化完成]
```

### 2. 布局流程

```
触发布局（属性修改 / 尺寸变化）
    ↓
CreateLayoutAlgorithm()
    ↓
CounterLayoutAlgorithm::Measure()
    ├─ 测量减号按钮
    ├─ 测量内容区域
    └─ 测量加号按钮
    ↓
CounterLayoutAlgorithm::Layout()
    ├─ 检查布局方向 (RTL/LTR)
    ├─ 布局左侧按钮
    ├─ 布局内容区域
    └─ 布局右侧按钮
    ↓
[布局完成]
```

### 3. 事件处理流程

```
按钮点击
    ↓
GestureEventHub::SetUserOnClick()
    ↓
CounterEventFunc 回调
    ↓
用户代码处理（如更新状态）
    ↓
[事件处理完成]
```

---

## 完整API清单

### ArkTS API 列表

#### 创建和基础配置

```typescript
// 创建 Counter
Counter() {
  // 内容
}
```

#### 属性配置

```typescript
// 设置尺寸
.height(value: Length): this
.width(value: Length): this

// 设置背景色
.backgroundColor(value: ResourceColor): this

// 设置按钮状态
.enableInc(value: boolean): this
.enableDec(value: boolean): this
```

#### 事件回调

```typescript
// 加号按钮点击
.onInc(callback: () => void): this

// 减号按钮点击
.onDec(callback: () => void): this
```

### C++ API 列表

#### CounterModelNG 公共方法

```cpp
// 创建 Counter
void Create() override;

// 设置事件回调
void SetOnInc(CounterEventFunc&& onInc) override;
void SetOnDec(CounterEventFunc&& onDec) override;

// 设置尺寸
void SetHeight(const Dimension& value) override;
void SetWidth(const Dimension& value) override;

// 设置按钮状态
void SetEnableDec(bool enableDec) override;
void SetEnableInc(bool enableInc) override;

// 设置背景色
void SetBackgroundColor(const Color& value) override;

// 资源对象创建
void CreateWithResourceObj(
    JsCounterResourceType resourceType,
    const RefPtr<ResourceObject>& resObj) override;

// 静态方法
static void SetEnableDec(FrameNode* frameNode, bool enableDec);
static void SetEnableInc(FrameNode* frameNode, bool enableInc);
static void SetHeight(FrameNode* frameNode, const Dimension& value);
static void SetWidth(FrameNode* frameNode, const Dimension& value);
static void SetBackgroundColor(FrameNode* frameNode, const Color& value);
static void ResetBackgroundColor(FrameNode* frameNode);
static void SetOnInc(FrameNode* frameNode, CounterEventFunc&& onInc);
static void SetOnDec(FrameNode* frameNode, CounterEventFunc&& onDec);
```

---

## 关键实现细节

### 1. 三节点结构

**设计**：Counter 由三个子节点组成

```cpp
// 节点索引
constexpr int32_t SUB_BUTTON = 0;   // 减号按钮
constexpr int32_t CONTENT = 1;      // 内容区域
constexpr int32_t ADD_BUTTON = 2;   // 加号按钮
```

**创建顺序**：
1. 减号按钮（Button）
2. 内容区域（Text）
3. 加号按钮（Button）

### 2. 节点 ID 管理

**目的**：通过唯一 ID 访问特定子节点

**实现**：
```cpp
std::optional<int32_t> subId_;      // 减号按钮 ID
std::optional<int32_t> contentId_;  // 内容区域 ID
std::optional<int32_t> addId_;      // 加号按钮 ID
```

**使用方式**：
```cpp
auto pattern = frameNode->GetPattern<CounterPattern>();
auto subId = pattern->GetSubId();
auto subNode = frameNode->GetChildAtIndex(subId);
```

### 3. 禁用状态的视觉效果

**实现方式**：通过调整透明度

**启用状态**：透明度 = 1.0（完全不透明）
**禁用状态**：透明度 = 0.4（半透明）

**源码**：
```cpp
if (!eventHub->IsEnabled()) {
    renderContext->UpdateOpacity(0.4);
} else {
    renderContext->UpdateOpacity(1.0);
}
```

### 4. RTL 布局处理

**检测方式**：通过 `GetNonAutoLayoutDirection()` 获取布局方向

**处理逻辑**：
- **LTR**：减号在左，加号在右（默认）
- **RTL**：加号在左，减号在右

---

## 使用示例

### 示例 1：基础 Counter

```typescript
@Entry
@Component
struct BasicCounter {
  @State value: number = 0

  build() {
    Row() {
      Counter()
        .height(40)
        .width(200)
        .enableInc(true)
        .enableDec(true)
        .onInc(() => {
          this.value++
        })
        .onDec(() => {
          this.value--
        })

      Text(`Value: ${this.value}`)
        .margin({ left: 20 })
    }
  }
}
```

### 示例 2：自定义样式

```typescript
@Entry
@Component
struct StyledCounter {
  @State value: number = 10

  build() {
    Counter()
      .height(50)
      .width(300)
      .backgroundColor(Color.Pink)
      .enableInc(this.value < 100)  // 达到最大值时禁用
      .enableDec(this.value > 0)    // 达到最小值时禁用
      .onInc(() => {
        this.value++
      })
      .onDec(() => {
        this.value--
      })
  }
}
```

### 示例 3：控制按钮状态

```typescript
@Entry
@Component
struct ControlledCounter {
  @State value: number = 5
  @State canInc: boolean = true
  @State canDec: boolean = true

  build() {
    Column() {
      Counter()
        .height(40)
        .width(200)
        .enableInc(this.canInc)
        .enableDec(this.canDec)
        .onInc(() => {
          if (this.value < 10) {
            this.value++
          }
          this.canInc = this.value < 10
          this.canDec = this.value > 0
        })
        .onDec(() => {
          if (this.value > 0) {
            this.value--
          }
          this.canInc = this.value < 10
          this.canDec = this.value > 0
        })

      Text(`Value: ${this.value}`)
        .margin({ top: 20 })
    }
  }
}
```

### 示例 4：商品数量选择

```typescript
@Entry
@Component
struct ProductCounter {
  @State quantity: number = 1
  private min: number = 1
  private max: number = 99

  build() {
    Row() {
      Counter()
        .height(36)
        .width(150)
        .backgroundColor(Color.Grey)
        .enableInc(this.quantity < this.max)
        .enableDec(this.quantity > this.min)
        .onInc(() => {
          if (this.quantity < this.max) {
            this.quantity++
          }
        })
        .onDec(() => {
          if (this.quantity > this.min) {
            this.quantity--
          }
        })

      Text(`数量: ${this.quantity}`)
        .margin({ left: 10 })
        .fontSize(16)
    }
  }
}
```

### 示例 5：动态背景色

```typescript
@Entry
@Component
struct DynamicBackgroundCounter {
  @State value: number = 0
  @State bgColor: ResourceColor = Color.White

  build() {
    Column() {
      Counter()
        .height(50)
        .width(250)
        .backgroundColor(this.bgColor)
        .onInc(() => {
          this.value++
          this.bgColor = this.value % 2 === 0 ? Color.White : Color.LightBlue
        })
        .onDec(() => {
          this.value--
          this.bgColor = this.value % 2 === 0 ? Color.White : Color.LightBlue
        })

      Text(`Value: ${this.value}`)
        .margin({ top: 20 })
    }
  }
}
```

---

## 调试指南

### 1. 日志调试

**使用专用日志标签**：
```cpp
#include "base/log/ace_trace.h"

// Counter 相关日志
TAG_LOGI(AceLogTag::ACE_COUNTER, "Counter created with id: %{public}d", nodeId);
TAG_LOGD(AceLogTag::ACE_COUNTER, "Sub button id: %{public}d", subId_);
```

**关键日志点**：
- `Create()` - 组件创建
- `SetEnableInc/Dec()` - 按钮状态变化
- `Measure()` - 测量过程
- `Layout()` - 布局过程

### 2. 节点检查

**检查子节点是否存在**：
```cpp
auto pattern = frameNode->GetPattern<CounterPattern>();
if (pattern->HasSubNode()) {
    // 减号按钮已创建
    auto subId = pattern->GetSubId();
}
```

**获取所有子节点 ID**：
```cpp
auto subId = pattern->GetSubId();
auto contentId = pattern->GetContentId();
auto addId = pattern->GetAddId();
```

### 3. 常见问题定位

#### 问题 1：按钮点击无响应

**检查点**：
- 是否注册了事件回调（onInc/onDec）
- 按钮是否被禁用

**定位方法**：
```cpp
auto eventHub = addNode->GetEventHub<ButtonEventHub>();
TAG_LOGI(AceLogTag::ACE_COUNTER, "Button enabled: %{public}d", eventHub->IsEnabled());
```

#### 问题 2：布局异常

**检查点**：
- 三个子节点是否正确创建
- Measure() 和 Layout() 是否正确执行

**定位方法**：
```cpp
auto geometryNode = layoutWrapper->GetGeometryNode();
auto frameSize = geometryNode->GetFrameSize();
TAG_LOGI(AceLogTag::ACE_LAYOUT, "Counter size: %{public}f x %{public}f",
    frameSize.Width(), frameSize.Height());
```

---

## 常见问题

### Q1: Counter 组件如何管理数值？

**A**：Counter 组件本身不管理数值，需要通过外部状态管理。

**示例**：
```typescript
@State value: number = 0

Counter()
  .onInc(() => { this.value++ })
  .onDec(() => { this.value-- })
```

### Q2: 如何设置数值范围限制？

**A**：通过控制按钮的启用状态

**示例**：
```typescript
@State value: number = 5
private min: number = 0
private max: number = 10

Counter()
  .enableInc(this.value < this.max)
  .enableDec(this.value > this.min)
  .onInc(() => { this.value++ })
  .onDec(() => { this.value-- })
```

### Q3: 如何禁用按钮？

**A**：使用 `.enableInc()` 或 `.enableDec()`

**效果**：禁用时按钮显示为半透明（40% 不透明度）

**示例**：
```typescript
.enableInc(false)  // 禁用加号按钮
.enableDec(false)  // 禁用减号按钮
```

### Q4: Counter 支持自定义按钮样式吗？

**A**：Counter 组件使用标准的 Button 组件作为子节点，按钮样式由主题系统控制。

### Q5: 如何在 RTL 布局中使用 Counter？

**A**：Counter 会自动检测并适配 RTL 布局方向。

**效果**：
- **LTR**：减号在左，加号在右
- **RTL**：加号在左，减号在右

### Q6: Counter 的默认尺寸是多少？

**A**：
- **默认高度**：32.0 vp
- **默认宽度**：100.0 vp

**源码**：[counter_theme.h:140](frameworks/core/components/counter/counter_theme.h#L140)

### Q7: 为什么禁用的按钮是半透明的？

**A**：这是设计规范，禁用时透明度设置为 0.4

**源码**：[counter_theme.h:29](frameworks/core/components/counter/counter_theme.h#L29)

```cpp
constexpr double BUTTON_ALPHA_DISABLED = 0.4;
```

### Q8: 如何动态更新 Counter 的样式？

**A**：通过 `@State` 装饰器

**示例**：
```typescript
@State bgColor: ResourceColor = Color.White

Counter()
  .backgroundColor(this.bgColor)

Button('Change Color').onClick(() => {
  this.bgColor = Color.Pink
})
```

### Q9: Counter 支持键盘操作吗？

**A**：Counter 的子按钮支持键盘操作（继承自 Button 组件）

### Q10: 如何获取当前值？

**A**：Counter 组件不存储值，需要在外部维护状态

**示例**：
```typescript
@State value: number = 0

Text(`Current Value: ${this.value}`)
```

---

## 附录

### A. 术语表

| 术语 | 英文 | 描述 |
|-----|------|------|
| 计数器 | Counter | 数值增减组件 |
| 减号按钮 | Sub Button | 减少数值的按钮（-） |
| 加号按钮 | Add Button | 增加数值的按钮（+） |
| 内容区域 | Content | 显示数值的区域 |
| 禁用状态 | Disabled | 按钮不可点击的状态 |
| RTL | Right-to-Left | 从右向左的布局方向 |
| LTR | Left-to-Right | 从左向右的布局方向 |

### B. 源码文件索引

| 文件 | 行数 | 描述 |
|-----|------|------|
| `counter_pattern.h` | ~80 | CounterPattern 类定义 |
| `counter_pattern.cpp` | ~100 | CounterPattern 实现 |
| `counter_model_ng.h` | ~60 | NG Model 定义 |
| `counter_model_ng.cpp` | ~300 | NG Model 实现 |
| `counter_layout_algorithm.h` | ~40 | 布局算法定义 |
| `counter_layout_algorithm.cpp` | ~350 | 布局算法实现 |
| `counter_layout_property.h` | ~60 | 布局属性定义 |
| `counter_node.h` | ~100 | 节点定义 |
| `counter_node.cpp` | ~200 | 节点实现 |
| `counter_theme.h` | ~200 | 主题定义 |

### C. 相关文档

- [Counter 组件官方文档](https://developer.huawei.com/consumer/cn/doc/harmonyos-references-V5/ts-container-counter-V5)
- [Button 组件文档](https://developer.huawei.com/consumer/cn/doc/harmonyos-references-V5/ts-basic-components-button-V5)
- [Text 组件文档](https://developer.huawei.com/consumer/cn/doc/harmonyos-references-V5/ts-basic-components-text-V5)

### D. 常量定义

```cpp
// 节点索引
constexpr int32_t SUB_BUTTON = 0;
constexpr int32_t CONTENT = 1;
constexpr int32_t ADD_BUTTON = 2;

// 禁用状态透明度
constexpr double BUTTON_ALPHA_DISABLED = 0.4;
```

### E. 版本历史

| 版本 | 日期 | 变更 |
|-----|------|------|
| v1.0 | 2026-02-01 | 初始版本 |

---

**文档结束**

> 本文档基于 OpenHarmony ace_engine 源码分析生成，如有错误或遗漏，欢迎指正。
