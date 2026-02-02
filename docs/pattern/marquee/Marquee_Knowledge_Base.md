# ArkUI Marquee 组件完整知识库

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
9. [动画控制](#动画控制)
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

**Marquee 组件**是 OpenHarmony ArkUI 框架中的**滚动文本组件**，提供单行文本的滚动播放功能，支持自定义滚动方向、速度、循环次数等特性，常用于公告、广告、通知等场景。

**技术栈**：
- **前端**：ArkTS/TypeScript
- **桥接层**：MarqueeModelNG
- **核心层**：NG Pattern 架构 (MarqueePattern)
- **布局算法**：MarqueeLayoutAlgorithm
- **渲染层**：Rosen + Skia

**代码规模**：
- 总文件数：约 15 个文件
- 核心代码：约 3,000+ 行 C++ 代码
- 涉及 4 个架构层次

### 功能特性

Marquee 组件支持：
- **滚动方向**：
  - 从左到右 (MarqueeDirection.LEFT - 默认)
  - 从右到左 (MarqueeDirection.RIGHT)
- **滚动控制**：
  - 播放/暂停状态控制
  - 滚动步长（速度）设置
  - 循环次数控制（-1 表示无限循环）
- **文本样式**：
  - 字体大小、颜色、粗细
  - 字体族设置
  - 文本方向自动检测（RTL/LTR）
- **动画效果**：
  - 平滑滚动动画
  - 可见性自动暂停/恢复
- **事件回调**：
  - onStart - 滚动开始
  - onBounce - 到达边缘
  - onFinish - 滚动完成

### 设计模式

Marquee 组件采用 **NG Pattern 架构**：

```
前端 (ArkTS)
    ↓ (Model Layer)
MarqueeModelNG (marquee_model_ng.cpp)
    ↓ (NG Pattern Layer)
MarqueePattern (marquee_pattern.cpp)
    ├─ 文本节点管理 (Text FrameNode)
    ├─ 动画控制 (Animation Controller)
    └─ 事件处理 (Event Hub)
    ↓ (NG LayoutAlgorithm Layer)
MarqueeLayoutAlgorithm (marquee_layout_algorithm.cpp)
    ↓
渲染显示
```

### 核心概念

**滚动方向**：
```typescript
MarqueeDirection.LEFT    // 从右向左滚动（默认）
MarqueeDirection.RIGHT   // 从左向右滚动
```

**关键配置**：
- `src` - 滚动文本内容
- `start` - 是否立即开始播放
- `step` - 滚动步长（速度），默认 50
- `loop` - 循环次数，-1 表示无限循环
- `fromStart` - 是否从起始位置开始

---

## 完整调用链

### 1. 从 ArkTS 到 Pattern 的调用链

#### 调用链图

```
┌─────────────────────────────────────────────────────────┐
│ 前端 ArkTS                                                │
│                                                          │
│ Marquee({                                               │
│   src: "Running Marquee starts rolling",               │
│   start: true,                                          │
│   step: 50,                                             │
│   loop: -1                                              │
│ })                                                       │
│   .fontSize(30)                                         │
│   .fontColor(Color.Red)                                 │
│   .width(200)                                           │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│ Model Layer (NG)                                         │
│                                                          │
│ class MarqueeModelNG                                     │
│   源码：frameworks/core/components_ng/pattern/marquee/   │
│         marquee_model_ng.cpp                              │
│                                                          │
│ 关键方法：                                                │
│ - Create() - 创建 Marquee 节点                           │
│ - SetValue() - 设置文本内容                              │
│ - SetPlayerStatus() - 设置播放状态                       │
│ - SetScrollAmount() - 设置滚动步长                       │
│ - SetLoop() - 设置循环次数                               │
│                                                          │
│ 执行流程：                                                 │
│ 1. 创建 FrameNode (MARQUEE_ETS_TAG)                     │
│ 2. 创建 MarqueePattern                                  │
│ 3. 创建文本子节点 (TEXT_ETS_TAG)                        │
│ 4. 应用布局和绘制属性                                    │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│ Pattern Layer (业务逻辑)                                  │
│                                                          │
│ class MarqueePattern : public Pattern                    │
│   源码：frameworks/core/components_ng/pattern/marquee/   │
│         marquee_pattern.cpp                               │
│                                                          │
│ 核心职责：                                                │
│ - 管理文本子节点                                         │
│ - 控制滚动动画                                           │
│ - 处理可见性变化                                         │
│ - 触发事件回调                                           │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│ LayoutAlgorithm Layer (布局计算)                          │
│                                                          │
│ class MarqueeLayoutAlgorithm : public BoxLayoutAlgorithm │
│   源码：frameworks/core/components_ng/pattern/marquee/   │
│         marquee_layout_algorithm.cpp                      │
│                                                          │
│ 核心方法：                                                │
│ - Measure() - 测量 Marquee 和文本尺寸                    │
│ - Layout() - 定位文本子节点                              │
└─────────────────────────────────────────────────────────┘
                          ↓
                    [滚动文本显示在屏幕上]
```

### 2. 创建完整调用链

```
ArkTS: Marquee({ src: "Hello World" })
    ↓
MarqueeModelNG::Create()
    ↓
ViewStackProcessor::ClaimNodeId()
    ↓
FrameNode::GetOrCreateFrameNode(MARQUEE_ETS_TAG, nodeId, []() {
    return AceType::MakeRefPtr<MarqueePattern>();
})
    ↓
创建文本子节点
    ↓
FrameNode::CreateFrameNode(TEXT_ETS_TAG, uniqueId, []() {
    return AceType::MakeRefPtr<TextPattern>();
})
    ↓
设置文本属性
    ↓
ViewStackProcessor::Push(frameNode)
    ↓
[创建完成]
```

### 3. 属性设置调用链

```
.start(true)
    ↓
MarqueeModelNG::SetPlayerStatus(true)
    ↓
ACE_UPDATE_PAINT_PROPERTY(MarqueePaintProperty, PlayerStatus, true)
    ↓
MarqueePattern::OnModifyDone()
    ↓
ChangeAnimationPlayStatus()
    ↓
[动画开始]

.step(50)
    ↓
MarqueeModelNG::SetScrollAmount(50)
    ↓
ACE_UPDATE_PAINT_PROPERTY(MarqueePaintProperty, ScrollAmount, 50)
    ↓
MarqueePattern::StartMarqueeAnimation()
    ↓
[更新滚动速度]
```

---

## 目录结构

### 完整目录树

```
frameworks/core/components_ng/pattern/marquee/
├── marquee_pattern.h                    # MarqueePattern 主类定义
├── marquee_pattern.cpp                  # MarqueePattern 实现
├── marquee_layout_algorithm.h           # 布局算法定义
├── marquee_layout_algorithm.cpp         # 布局算法实现
├── marquee_layout_property.h            # 布局属性定义
├── marquee_paint_property.h             # 绘制属性定义
├── marquee_event_hub.h                  # 事件中心
├── marquee_accessibility_property.h     # 无障碍属性定义
├── marquee_accessibility_property.cpp   # 无障碍属性实现
│
├── Model 层
├── marquee_model_ng.h                   # NG Model 定义
├── marquee_model_ng.cpp                 # NG Model 实现
│
└── Bridge 层 (桥接层)
    └── bridge/
        ├── marquee_dynamic_modifier.cpp  # 动态修饰器
        ├── marquee_static_modifier.cpp   # 静态修饰器
        ├── marquee_dynamic_module.h      # 动态模块
        └── marquee_dynamic_module.cpp    # 动态模块实现
```

### 关键文件说明

| 文件 | 职责 | 核心类/方法 |
|-----|------|-----------|
| **marquee_pattern.h/cpp** | 核心业务逻辑 | `MarqueePattern::OnModifyDone()`, `StartMarqueeAnimation()` |
| **marquee_layout_algorithm.h/cpp** | 布局计算 | `MarqueeLayoutAlgorithm::Measure()`, `Layout()` |
| **marquee_model_ng.h/cpp** | ArkTS API 接口 | `MarqueeModelNG::Create()`, `SetValue()` |
| **marquee_layout_property.h** | 布局属性定义 | 文本相关属性 |
| **marquee_paint_property.h** | 绘制属性定义 | 动画相关属性 |
| **marquee_event_hub.h** | 事件处理 | onStart, onBounce, onFinish |

---

## 核心类继承关系

### 1. Pattern 层继承关系

```
Pattern (基类)
    ↓
MarqueePattern (Marquee 组件实现)
    ├─ 文本子节点管理
    ├─ 动画控制
    ├─ 事件触发
    └─ 可见性处理
```

### 2. Model 层继承关系

```
MarqueeModel (基类)
    ↓
MarqueeModelNG (NG 架构实现)
    ├─ Create() - 创建组件
    ├─ SetValue() - 设置文本
    ├─ SetPlayerStatus() - 设置播放状态
    ├─ SetScrollAmount() - 设置步长
    └─ SetLoop() - 设置循环次数
```

### 3. LayoutAlgorithm 层继承关系

```
BoxLayoutAlgorithm (基类)
    ↓
MarqueeLayoutAlgorithm (Marquee 布局算法)
    └─ Measure() - 测量内容
    └─ Layout() - 定位文本
```

### 4. 关键类定义

#### MarqueePattern

**文件**：[marquee_pattern.h:50](frameworks/core/components_ng/pattern/marquee/marquee_pattern.h#L50)

```cpp
class MarqueePattern : public Pattern {
    DECLARE_ACE_TYPE(MarqueePattern, Pattern);

public:
    MarqueePattern();
    ~MarqueePattern() override = default;

    // 创建布局算法
    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<MarqueeLayoutAlgorithm>();
    }

    // 属性修改完成
    void OnModifyDone() override;

    // 布局交换
    bool OnDirtyLayoutWrapperSwap(
        const RefPtr<LayoutWrapper>& dirty,
        const DirtySwapConfig& config) override;

    // 可见性变化
    void OnVisibleAreaChange(bool isVisible) override;

    // 获取文本方向
    TextDirection GetTextDirection(const std::string& content, MarqueeDirection direction);

private:
    // 动画控制
    void StartMarqueeAnimation();
    void StopMarqueeAnimation(bool playStatus);
    void ChangeAnimationPlayStatus();
    void PauseAnimation();
    void ResumeAnimation();

    // 文本位置更新
    void UpdateTextTranslateXY(float position);

    // 事件触发
    void FireStartEvent();
    void FireBounceEvent();
    void FireFinishEvent();

    // 成员变量
    RefPtr<FrameNode> textNode_;
    float marqueeWidth_ = 0.0f;
    bool measureChanged_ = true;
    LastAnimationParam lastAnimationParam_;
};
```

#### MarqueeModelNG

**文件**：[marquee_model_ng.h:24](frameworks/core/components_ng/pattern/marquee/marquee_model_ng.h#L24)

```cpp
class ACE_EXPORT MarqueeModelNG : public OHOS::Ace::MarqueeModel {
public:
    // 创建 Marquee
    void Create() override;

    // 设置文本内容
    void SetValue(const std::optional<std::string>& value) override;

    // 设置播放状态
    void SetPlayerStatus(const std::optional<bool>& playerStatus) override;

    // 设置滚动步长
    void SetScrollAmount(const std::optional<double>& scrollAmount) override;

    // 设置循环次数
    void SetLoop(const std::optional<int32_t>& loop) override;

    // 设置滚动方向
    void SetDirection(const std::optional<MarqueeDirection>& direction) override;

    // 文本样式
    void SetTextColor(const std::optional<Color>& textColor) override;
    void SetFontSize(const std::optional<Dimension>& fontSize) override;
    void SetFontWeight(const std::optional<FontWeight>& fontWeight) override;
    void SetFontFamily(const std::optional<std::vector<std::string>>& fontFamilies) override;

    // 事件回调
    void SetOnStart(std::function<void()>&& onChange) override;
    void SetOnBounce(std::function<void()>&& onChange) override;
    void SetOnFinish(std::function<void()>&& onChange) override;
};
```

---

## Pattern层详解

### MarqueePattern 核心职责

**MarqueePattern** 是 Marquee 组件的核心逻辑层，负责：

1. **文本子节点管理**
   - 创建和管理 Text FrameNode
   - 更新文本内容和样式

2. **动画控制**
   - 启动/停止滚动动画
   - 暂停/恢复动画
   - 计算滚动位置和速度

3. **事件处理**
   - 触发 onStart 事件
   - 触发 onBounce 事件
   - 触发 onFinish 事件

4. **可见性管理**
   - 组件不可见时自动暂停
   - 组件可见时自动恢复

### 关键生命周期方法

#### 1. OnModifyDone()

**调用时机**：组件属性修改完成时

**源码位置**：[marquee_pattern.cpp:116-161](frameworks/core/components_ng/pattern/marquee/marquee_pattern.cpp#L116-L161)

**执行流程**：
```cpp
void MarqueePattern::OnModifyDone()
{
    Pattern::OnModifyDone();

    // 1. 获取主机节点和属性
    auto host = GetHost();
    auto layoutProperty = host->GetLayoutProperty<MarqueeLayoutProperty>();
    auto paintProperty = host->GetPaintProperty<MarqueePaintProperty>();
    auto textChild = DynamicCast<FrameNode>(host->GetFirstChild());

    // 2. 更新文本方向
    UpdateTextDirection(layoutProperty, textLayoutProperty);

    // 3. 设置文本节点属性
    textLayoutProperty->UpdateFontSize(fontSize);
    textLayoutProperty->UpdateFontWeight(fontWeight);
    textLayoutProperty->UpdateTextColor(textColor);

    // 4. 处理属性变更
    if (CheckMeasureFlag() || CheckLayoutFlag()) {
        measureChanged_ = true;
    } else if (OnlyPlayStatusChange()) {
        // 仅播放状态变化
        ChangeAnimationPlayStatus();
    } else {
        // 停止当前动画
        auto playStatus = paintProperty->GetPlayerStatus().value_or(false);
        StopMarqueeAnimation(playStatus);
    }
}
```

**注意事项**：
- ⚠️ **不要在 OnModifyDone 中触发布局**
- ✅ **可以访问 PaintProperty 和 LayoutProperty**
- ✅ **此时 geometryNode 可能还没有更新**

#### 2. OnDirtyLayoutWrapperSwap()

**调用时机**：布局结果交换时

**源码位置**：[marquee_pattern.cpp:97-114](frameworks/core/components_ng/pattern/marquee/marquee_pattern.cpp#L97-L114)

**执行流程**：
```cpp
bool MarqueePattern::OnDirtyLayoutWrapperSwap(
    const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);

    auto geoNode = host->GetGeometryNode();
    auto marqueeWidth = geoNode->GetFrameSize().Width();

    // 检查尺寸是否变化
    if (measureChanged_ || marqueeWidth_ != marqueeWidth) {
        measureChanged_ = true;
        auto paintProperty = host->GetPaintProperty<MarqueePaintProperty>();
        auto playStatus = paintProperty->GetPlayerStatus().value_or(false);
        StopMarqueeAnimation(playStatus);
    }

    marqueeWidth_ = marqueeWidth;
    return false;
}
```

**注意事项**：
- ✅ **这是访问布局结果的正确时机**
- ✅ **可以安全地获取 geometryNode 数据**
- ⚠️ **不要在此方法中修改 LayoutProperty**

### 动画控制方法

#### StartMarqueeAnimation()

**源码位置**：[marquee_pattern.cpp:163-184](frameworks/core/components_ng/pattern/marquee/marquee_pattern.cpp#L163-L184)

**功能**：启动滚动动画

```cpp
void MarqueePattern::StartMarqueeAnimation()
{
    // 1. 检查是否需要滚动
    if (!IsRunMarquee()) {
        UpdateTextTranslateXY(0.0f);
        StopAndResetAnimation();
        return;
    }

    // 2. 获取循环次数
    auto repeatCount = paintProperty->GetLoop().value_or(DEFAULT_MARQUEE_LOOP);

    // 3. 触发开始事件
    FireStartEvent();

    // 4. 判断是否需要第二次播放
    bool needSecondPlay = repeatCount != 1;

    // 5. 获取起始位置
    auto startPosition = GetTextOffset();

    // 6. 播放动画
    PlayMarqueeAnimation(startPosition, repeatCount, needSecondPlay);
}
```

**调用时机**：
- 组件首次加载且 `start = true`
- 播放状态从 false 变为 true
- 布局完成后需要重新播放

#### StopMarqueeAnimation()

**功能**：停止滚动动画

```cpp
void MarqueePattern::StopMarqueeAnimation(bool playStatus)
{
    StopAndResetAnimation();

    // 如果播放状态为 true，重新启动动画
    if (playStatus) {
        StartMarqueeAnimation();
    }
}
```

#### PauseAnimation() / ResumeAnimation()

**功能**：暂停/恢复动画（用于可见性控制）

```cpp
void MarqueePattern::PauseAnimation()
{
    if (animator_) {
        animator_->Pause();
    }
}

void MarqueePattern::ResumeAnimation()
{
    if (animator_) {
        animator_->Resume();
    }
}
```

### 可见性处理

#### OnVisibleAreaChange()

**源码位置**：[marquee_pattern.cpp:396-405](frameworks/core/components_ng/pattern/marquee/marquee_pattern.cpp#L396-L405)

**功能**：响应可见性变化

```cpp
void MarqueePattern::OnVisibleAreaChange(bool isVisible)
{
    if (isVisible) {
        // 组件可见，恢复动画
        ResumeAnimation();
    } else {
        // 组件不可见，暂停动画
        PauseAnimation();
    }
}
```

**优化效果**：当 Marquee 滚出屏幕时自动暂停，节省 CPU 和电池资源。

---

## Model层详解

### MarqueeModelNG 核心职责

**MarqueeModelNG** 提供 ArkTS 声明式 API，负责：

1. **创建 Marquee 节点**
2. **创建文本子节点**
3. **设置属性**（布局属性和绘制属性）
4. **注册事件回调**

### 关键 API 方法

#### 1. Create()

**源码位置**：[marquee_model_ng.cpp:24-45](frameworks/core/components_ng/pattern/marquee/marquee_model_ng.cpp#L24-L45)

**功能**：创建 Marquee FrameNode

```cpp
void MarqueeModelNG::Create()
{
    // 1. 获取 ViewStack 实例
    auto* stack = ViewStackProcessor::GetInstance();

    // 2. 获取节点 ID
    auto nodeId = stack->ClaimNodeId();

    // 3. 创建或获取 FrameNode
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        MARQUEE_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<MarqueePattern>(); });

    // 4. 创建文本子节点（如果不存在）
    if (frameNode->GetChildren().empty()) {
        auto textNode = FrameNode::CreateFrameNode(
            TEXT_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(),
            AceType::MakeRefPtr<TextPattern>()
        );

        // 设置文本属性
        auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
        textLayoutProperty->UpdateMaxLines(1);

        // 添加为子节点
        frameNode->AddChild(textNode);
    }

    // 5. 压入栈
    stack->Push(frameNode);
}
```

**对应 ArkTS**：
```typescript
Marquee({ src: "Hello World" })
```

#### 2. SetValue()

**源码位置**：[marquee_model_ng.cpp:47-52](frameworks/core/components_ng/pattern/marquee/marquee_model_ng.cpp#L47-L52)

**功能**：设置滚动文本内容

```cpp
void MarqueeModelNG::SetValue(const std::optional<std::string>& value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(MarqueeLayoutProperty, Src, value, frameNode);
}
```

**对应 ArkTS**：
```typescript
// 初始化设置
Marquee({ src: "滚动文本" })

// 动态更新
@State text: string = "Hello"
Marquee({ src: this.text })

Button('Update').onClick(() => {
  this.text = "Updated Text"
})
```

#### 3. SetPlayerStatus()

**源码位置**：[marquee_model_ng.cpp:54-59](frameworks/core/components_ng/pattern/marquee/marquee_model_ng.cpp#L54-L59)

**功能**：设置播放状态

```cpp
void MarqueeModelNG::SetPlayerStatus(const std::optional<bool>& playerStatus)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(MarqueePaintProperty, PlayerStatus, playerStatus, frameNode);
}
```

**对应 ArkTS**：
```typescript
.start(true)   // 开始播放
.start(false)  // 暂停播放
```

#### 4. SetScrollAmount()

**源码位置**：[marquee_model_ng.cpp:61-66](frameworks/core/components_ng/pattern/marquee/marquee_model_ng.cpp#L61-L66)

**功能**：设置滚动步长（速度）

```cpp
void MarqueeModelNG::SetScrollAmount(const std::optional<double>& scrollAmount)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(MarqueePaintProperty, ScrollAmount, scrollAmount, frameNode);
}
```

**对应 ArkTS**：
```typescript
.step(50)  // 滚动步长为 50
```

#### 5. SetLoop()

**源码位置**：[marquee_model_ng.cpp:68-73](frameworks/core/components_ng/pattern/marquee/marquee_model_ng.cpp#L68-L73)

**功能**：设置循环次数

```cpp
void MarqueeModelNG::SetLoop(const std::optional<int32_t>& loop)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(MarqueePaintProperty, Loop, loop, frameNode);
}
```

**对应 ArkTS**：
```typescript
.loop(-1)   // 无限循环
.loop(0)    // 不循环（播放一次）
.loop(5)    // 循环 5 次
```

#### 6. 事件回调方法

**onStart**:
```cpp
void MarqueeModelNG::SetOnStart(std::function<void()>&& onChange)
{
    auto eventHub = frameNode->GetEventHub<MarqueeEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnStart(std::move(onChange));
}
```

**对应 ArkTS**：
```typescript
.onStart(() => {
  console.info('Marquee started')
})
```

### 完整 API 映射表

| ArkTS API | MarqueeModelNG 方法 | Property 类型 | 说明 |
|-----------|--------------------|--------------|------|
| `Marquee({ src })` | `Create()` | - | 创建组件 |
| `.src(value)` | `SetValue()` | LayoutProperty | 设置文本 |
| `.start(value)` | `SetPlayerStatus()` | PaintProperty | 播放状态 |
| `.step(value)` | `SetScrollAmount()` | PaintProperty | 滚动步长 |
| `.loop(value)` | `SetLoop()` | PaintProperty | 循环次数 |
| `.direction(value)` | `SetDirection()` | PaintProperty | 滚动方向 |
| `.fontSize(value)` | `SetFontSize()` | LayoutProperty | 字体大小 |
| `.fontColor(value)` | `SetTextColor()` | LayoutProperty | 字体颜色 |
| `.fontWeight(value)` | `SetFontWeight()` | LayoutProperty | 字体粗细 |
| `.fontFamily(value)` | `SetFontFamily()` | LayoutProperty | 字体族 |
| `.onStart(callback)` | `SetOnStart()` | EventHub | 开始事件 |
| `.onBounce(callback)` | `SetOnBounce()` | EventHub | 到达边缘事件 |
| `.onFinish(callback)` | `SetOnFinish()` | EventHub | 完成事件 |

---

## LayoutAlgorithm层详解

### MarqueeLayoutAlgorithm 核心职责

**MarqueeLayoutAlgorithm** 负责 Marquee 的布局计算：

1. **Measure（测量）**：
   - 测量 Marquee 自身尺寸
   - 测量文本子节点尺寸
   - 计算自适应高度

2. **Layout（布局）**：
   - 定位文本子节点
   - 处理文本方向（LTR/RTL）

### Measure() 方法详解

**源码位置**：[marquee_layout_algorithm.cpp:30-77](frameworks/core/components_ng/pattern/marquee/marquee_layout_algorithm.cpp#L30-L77)

**执行流程**：
```cpp
void MarqueeLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    // 1. 获取布局约束和 padding
    const auto& layoutConstraint = layoutWrapper->GetLayoutProperty()->GetLayoutConstraint();
    const auto& padding = layoutWrapper->GetLayoutProperty()->CreatePaddingAndBorder();

    // 2. 获取文本子节点
    auto child = layoutWrapper->GetAllChildrenWithBuild().front();

    // 3. 设置文本约束
    LayoutConstraintF textLayoutConstraint;
    textLayoutConstraint.UpdateMaxSizeWithCheck(SizeF(Infinity<float>(), maxSize.Height()));

    // 4. 添加 padding 到文本节点
    PaddingProperty textPadding;
    textPadding.left = CalcLength(padding.left.value());
    textPadding.right = CalcLength(padding.right.value());
    child->GetLayoutProperty()->UpdatePadding(textPadding);

    // 5. 测量文本
    child->Measure(textLayoutConstraint);

    // 6. 计算自适应高度
    auto adaptiveSize = GetMeasureAdaptiveHeight(layoutWrapper, child);

    // 7. 设置 Marquee 尺寸
    auto frameSize = layoutWrapper->GetGeometryNode()->GetFrameSize();
    layoutWrapper->GetGeometryNode()->SetFrameSize(frameSize.ConvertToSizeT());
}
```

**关键计算**：
- 文本宽度：设置为无限大，让文本完整显示
- 文本高度：跟随 Marquee 高度
- 自适应高度：根据字体大小和 padding 计算

### Layout() 方法详解

**源码位置**：[marquee_layout_algorithm.cpp:79-110](frameworks/core/components_ng/pattern/marquee/marquee_layout_algorithm.cpp#L79-L110)

**执行流程**：
```cpp
void MarqueeLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    auto frameSize = layoutWrapper->GetGeometryNode()->GetFrameSize();
    auto child = layoutWrapper->GetAllChildrenWithBuild().front();
    CHECK_NULL_VOID(child);

    // 1. 获取文本内容和方向
    auto marqueeLayoutProperty = layoutWrapper->GetLayoutProperty<MarqueeLayoutProperty>();
    auto content = marqueeLayoutProperty->GetSrc().value_or("");
    auto direction = marqueeLayoutProperty->GetMarqueeDirection().value_or(MarqueeDirection::LEFT);

    // 2. 获取 Pattern 以检测文本方向
    auto pattern = layoutWrapper->GetHostNode()->GetPattern<MarqueePattern>();
    auto textDirection = pattern->GetTextDirection(content, direction);

    // 3. 计算对齐方式
    auto align = (textDirection == TextDirection::RTL) ?
        Alignment::CENTER_RIGHT : Alignment::CENTER_LEFT;

    // 4. 计算文本位置
    auto textGeoNode = child->GetGeometryNode();
    auto minusLen = frameSize.Width() - textGeoNode->GetMarginFrameSize().Width();
    OffsetF translate;
    translate.SetX((1.0 + align.GetHorizontal()) * minusLen / MULTIPLE);
    textGeoNode->SetMarginFrameOffset(translate);

    // 5. 布局文本子节点
    child->Layout();
}
```

**对齐逻辑**：
- **LTR 文本**：左对齐，从右向左滚动
- **RTL 文本**：右对齐，从左向右滚动

---

## 属性系统

### MarqueeLayoutProperty

**文件**：[marquee_layout_property.h](frameworks/core/components_ng/pattern/marquee/marquee_layout_property.h)

**核心属性**：

```cpp
// 文本内容
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Src, std::string, PROPERTY_UPDATE_LAYOUT);

// 字体样式
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(FontSize, Dimension, PROPERTY_UPDATE_LAYOUT);
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(FontWeight, FontWeight, PROPERTY_UPDATE_LAYOUT);
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(TextColor, Color, PROPERTY_UPDATE_RENDER);
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(FontFamily, std::vector<std::string>, PROPERTY_UPDATE_LAYOUT);

// 滚动方向
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(MarqueeDirection, MarqueeDirection, PROPERTY_UPDATE_RENDER);
```

### MarqueePaintProperty

**文件**：[marquee_paint_property.h](frameworks/core/components_ng/pattern/marquee/marquee_paint_property.h)

**核心属性**：

```cpp
// 播放控制
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(PlayerStatus, bool, PROPERTY_UPDATE_RENDER);

// 动画参数
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ScrollAmount, double, PROPERTY_UPDATE_RENDER);
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Loop, int32_t, PROPERTY_UPDATE_RENDER);
```

### 属性传递流程

```
ArkTS API
    ↓
MarqueeModelNG::SetXXX()
    ↓
ACE_UPDATE_NODE_LAYOUT_PROPERTY / ACE_UPDATE_NODE_PAINT_PROPERTY
    ↓
MarqueeLayoutProperty / MarqueePaintProperty::UpdateXXX()
    ↓
FrameNode::MarkDirtyNode(PROPERTY_UPDATE_MEASURE / PROPERTY_UPDATE_RENDER)
    ↓
Pattern::OnModifyDone()
    ↓
应用相应逻辑
```

---

## 动画控制

### 滚动原理

Marquee 使用 **平移动画** 实现滚动效果：

1. **起始位置**：文本在视口右侧（从右向左滚动）
2. **结束位置**：文本完全移出视口左侧
3. **动画过程**：不断更新文本的 X 偏移量

### 动画参数计算

#### 滚动距离

```cpp
float MarqueePattern::GetScrollDistance()
{
    auto textWidth = textNode_->GetGeometryNode()->GetMarginFrameSize().Width();
    auto marqueeWidth = marqueeWidth_;

    // 总滚动距离 = 文本宽度 + Marquee 宽度
    return textWidth + marqueeWidth;
}
```

#### 动画持续时间

```cpp
float MarqueePattern::GetDuration(float distance, float step)
{
    // 持续时间 = 距离 / 步长 * 默认延迟
    constexpr float DEFAULT_DELAY = 85.0f; // 每像素滚动延迟
    return distance / step * DEFAULT_DELAY;
}
```

#### 动画执行

```cpp
void MarqueePattern::PlayMarqueeAnimation(float start, int32_t repeatCount, bool needSecondPlay)
{
    // 1. 计算滚动距离和持续时间
    auto distance = GetScrollDistance();
    auto step = paintProperty->GetScrollAmount().value_or(DEFAULT_MARQUEE_SCROLL_AMOUNT);
    auto duration = GetDuration(distance, step);

    // 2. 创建动画
    auto animation = AnimationUtils::GetAnimation(
        duration,
        Curves::LINEAR,
        repeatCount
    );

    // 3. 设置动画回调
    animation->AddListener([this](float value) {
        UpdateTextTranslateXY(value);
    });

    // 4. 启动动画
    animator_->RunAnimation(animation);
}
```

### 滚动方向

**MarqueeDirection 枚举**：

```cpp
enum class MarqueeDirection {
    LEFT,           // 从右向左（默认）
    RIGHT,          // 从左向右
    DEFAULT,        // 默认方向（从右向左）
    DEFAULT_REVERSE // 默认反向（从左向右）
};
```

**实现逻辑**：
- **LEFT**: 起始位置在右侧，向左滚动
- **RIGHT**: 起始位置在左侧，向右滚动
- 自动检测文本方向（RTL/LTR）并调整

---

## 特殊功能

### 1. 文本方向自动检测

**功能**：根据文本内容自动检测 RTL/LTR 方向

**实现**：
```cpp
TextDirection MarqueePattern::GetTextDirection(const std::string& content, MarqueeDirection direction)
{
    // 检测是否为 RTL 文本
    if (!content.empty() && (content[0] == 0x0591 || content[0] == 0x0592)) {
        return TextDirection::RTL;
    }
    return TextDirection::LTR;
}
```

**支持的 RTL 语言**：
- 阿拉伯语
- 希伯来语
- 其他从右向左书写语言

### 2. 可见性自动暂停

**功能**：组件不可见时自动暂停动画

**实现**：
```cpp
void MarqueePattern::OnVisibleAreaChange(bool isVisible)
{
    if (isVisible) {
        ResumeAnimation();
    } else {
        PauseAnimation();
    }
}
```

**优化效果**：
- 节省 CPU 资源
- 减少电池消耗
- 提升整体性能

### 3. 循环控制

**循环次数含义**：

| loop 值 | 行为 |
|---------|------|
| `-1` | 无限循环 |
| `0` | 不循环（播放一次） |
| `> 0` | 循环指定次数 |

**实现逻辑**：
```cpp
void MarqueePattern::PlayMarqueeAnimation(float start, int32_t repeatCount, bool needSecondPlay)
{
    // repeatCount = -1 表示无限循环
    if (repeatCount == -1) {
        animation->SetIterationCount(ANIMATION_REPEAT_INFINITE);
    } else {
        animation->SetIterationCount(repeatCount);
    }
}
```

### 4. 事件系统

**支持的事件**：

| 事件 | 触发时机 | 回调函数 |
|-----|---------|---------|
| **onStart** | 滚动开始 | `SetOnStart()` |
| **onBounce** | 到达边缘 | `SetOnBounce()` |
| **onFinish** | 滚动完成 | `SetOnFinish()` |

**ArkTS 使用**：
```typescript
Marquee({ src: "Scrolling Text" })
  .onStart(() => {
    console.info('Animation started')
  })
  .onBounce(() => {
    console.info('Reached edge')
  })
  .onFinish(() => {
    console.info('Animation finished')
  })
```

---

## 执行流程

### 1. 初始化流程

```
ArkTS: Marquee({ src: "Hello World", start: true })
    ↓
MarqueeModelNG::Create()
    ↓
FrameNode::GetOrCreateFrameNode(MARQUEE_ETS_TAG)
    ↓
创建 MarqueePattern
    ↓
创建文本子节点
    ↓
设置初始属性
    ↓
OnAttachToFrameNode()
    ↓
OnModifyDone()
    ↓
StartMarqueeAnimation()
    ↓
[初始化完成，动画开始]
```

### 2. 布局流程

```
触发布局（属性修改 / 尺寸变化）
    ↓
CreateLayoutAlgorithm()
    ↓
MarqueeLayoutAlgorithm::Measure()
    ├─ 测量文本子节点
    ├─ 设置文本约束（无限宽度）
    ├─ 计算自适应高度
    └─ 设置 Marquee 尺寸
    ↓
MarqueeLayoutAlgorithm::Layout()
    ├─ 检测文本方向
    ├─ 计算对齐方式
    ├─ 定位文本子节点
    └─ 布局文本子节点
    ↓
OnDirtyLayoutWrapperSwap()
    ├─ 检查尺寸变化
    ├─ 停止当前动画
    └─ 重新启动动画
    ↓
[布局完成]
```

### 3. 动画流程

```
启动动画
    ↓
计算滚动距离
    ↓
计算动画持续时间
    ↓
创建动画对象
    ↓
设置动画回调
    ↓
逐帧更新文本位置
    ↓
UpdateTextTranslateXY(position)
    ↓
检查是否到达边缘
    ↓
FireBounceEvent()
    ↓
检查是否完成
    ↓
FireFinishEvent()
    ↓
[动画完成]
```

---

## 完整API清单

### ArkTS API 列表

#### 创建和基础配置

```typescript
// 创建 Marquee
Marquee(options: {
  src: string;
  start?: boolean;
  step?: number;
  loop?: number;
  fromStart?: boolean;
})

// 滚动方向
enum MarqueeDirection {
  Left,      // 从右向左
  Right,     // 从左向右
  Default,   // 默认方向
  DefaultReverse  // 默认反向
}
```

#### 属性配置

```typescript
// 设置文本内容
.src(value: string): this

// 播放控制
.start(value: boolean): this

// 滚动步长（速度）
.step(value: number): this

// 循环次数
.loop(value: number): this

// 滚动方向
.direction(value: MarqueeDirection): this
```

#### 文本样式

```typescript
// 字体大小
.fontSize(value: Length): this

// 字体颜色
.fontColor(value: ResourceColor): this

// 字体粗细
.fontWeight(value: FontWeight | number | string): this

// 字体族
.fontFamily(value: string | string[]): this
```

#### 事件回调

```typescript
// 滚动开始
.onStart(callback: () => void): this

// 到达边缘
.onBounce(callback: () => void): this

// 滚动完成
.onFinish(callback: () => void): this
```

### C++ API 列表

#### MarqueeModelNG 公共方法

```cpp
// 创建 Marquee
void Create() override;

// 设置文本
void SetValue(const std::optional<std::string>& value) override;

// 播放控制
void SetPlayerStatus(const std::optional<bool>& playerStatus) override;

// 滚动步长
void SetScrollAmount(const std::optional<double>& scrollAmount) override;

// 循环次数
void SetLoop(const std::optional<int32_t>& loop) override;

// 滚动方向
void SetDirection(const std::optional<MarqueeDirection>& direction) override;

// 文本样式
void SetTextColor(const std::optional<Color>& textColor) override;
void SetFontSize(const std::optional<Dimension>& fontSize) override;
void SetFontWeight(const std::optional<FontWeight>& fontWeight) override;
void SetFontFamily(const std::optional<std::vector<std::string>>& fontFamilies) override;

// 事件回调
void SetOnStart(std::function<void()>&& onChange) override;
void SetOnBounce(std::function<void()>&& onChange) override;
void SetOnFinish(std::function<void()>&& onChange) override;
```

---

## 关键实现细节

### 1. 文本子节点管理

**设计**：Marquee 内部包含一个 Text FrameNode 作为子节点

**创建时机**：在 `MarqueeModelNG::Create()` 中

**更新方式**：通过 `TextLayoutProperty` 设置文本属性

**优势**：
- 复用 Text 组件的文本渲染能力
- 支持所有 Text 样式属性
- 自动处理文本测量和换行

### 2. 滚动距离计算

**公式**：
```cpp
scrollDistance = textWidth + marqueeWidth
```

**说明**：
- 文本需要完全滚动出视口
- 因此需要额外滚动一个 Marquee 宽度的距离

### 3. 动画持续时间计算

**公式**：
```cpp
duration = (distance / step) * DEFAULT_DELAY
```

**参数**：
- `distance` - 滚动距离（像素）
- `step` - 滚动步长（像素/帧），默认 6.0
- `DEFAULT_DELAY` - 每像素滚动延迟（毫秒），默认 85

**示例**：
- 距离：300px
- 步长：6px
- 持续时间：(300 / 6) * 85 = 4250ms

### 4. RTL 文本处理

**检测方法**：
```cpp
bool IsRTLText(const std::string& content)
{
    if (content.empty()) return false;
    return content[0] == 0x0591 || content[0] == 0x0592;
}
```

**处理逻辑**：
- RTL 文本：右对齐，从左向右滚动
- LTR 文本：左对齐，从右向左滚动

### 5. 性能优化

**可见性优化**：
```cpp
void OnVisibleAreaChange(bool isVisible)
{
    if (isVisible) {
        ResumeAnimation();
    } else {
        PauseAnimation();
    }
}
```

**优化效果**：
- 滚出屏幕时暂停动画
- 节省 CPU 和电池资源

---

## 使用示例

### 示例 1：基础 Marquee

```typescript
@Entry
@Component
struct BasicMarquee {
  build() {
    Marquee({
      src: 'Running Marquee starts rolling',
      start: true,
      step: 50,
      loop: -1
    })
      .width(200)
      .fontSize(30)
      .fontColor(Color.Red)
  }
}
```

### 示例 2：自定义样式

```typescript
@Entry
@Component
struct StyledMarquee {
  build() {
    Marquee({
      src: 'This is a styled marquee text',
      start: true,
      step: 100,
      loop: 5
    })
      .width(300)
      .height(50)
      .fontSize(24)
      .fontColor(Color.Blue)
      .fontWeight(FontWeight.Bold)
      .fontFamily('Arial')
  }
}
```

### 示例 3：控制播放状态

```typescript
@Entry
@Component
struct ControlledMarquee {
  @State isPlaying: boolean = true

  build() {
    Column() {
      Marquee({
        src: 'Controllable Marquee',
        start: this.isPlaying,
        step: 50,
        loop: -1
      })
        .width(250)
        .fontSize(20)

      Row() {
        Button('Play')
          .onClick(() => {
            this.isPlaying = true
          })

        Button('Pause')
          .onClick(() => {
            this.isPlaying = false
          })
      }
      .margin({ top: 20 })
    }
  }
}
```

### 示例 4：事件监听

```typescript
@Entry
@Component
struct EventMarquee {
  @State message: string = 'Waiting...'

  build() {
    Column() {
      Marquee({
        src: 'Marquee with Events',
        start: true,
        step: 50,
        loop: 3
      })
        .width(300)
        .fontSize(22)
        .onStart(() => {
          this.message = 'Started!'
        })
        .onBounce(() => {
          this.message = 'Bounced!'
        })
        .onFinish(() => {
          this.message = 'Finished!'
        })

      Text(this.message)
        .margin({ top: 20 })
    }
  }
}
```

### 示例 5：滚动方向控制

```typescript
@Entry
@Component
struct DirectionMarquee {
  build() {
    Column() {
      // 从右向左（默认）
      Marquee({
        src: 'Scrolling Left',
        start: true,
        step: 50,
        loop: -1
      })
        .width(250)
        .direction(MarqueeDirection.Left)
        .margin({ bottom: 20 })

      // 从左向右
      Marquee({
        src: 'Scrolling Right',
        start: true,
        step: 50,
        loop: -1
      })
        .width(250)
        .direction(MarqueeDirection.Right)
    }
  }
}
```

### 示例 6：动态更新内容

```typescript
@Entry
@Component
struct DynamicMarquee {
  @State texts: string[] = ['Text 1', 'Text 2', 'Text 3']
  @State currentIndex: number = 0

  build() {
    Column() {
      Marquee({
        src: this.texts[this.currentIndex],
        start: true,
        step: 50,
        loop: 1
      })
        .width(300)
        .fontSize(24)
        .onFinish(() => {
          // 切换到下一个文本
          this.currentIndex = (this.currentIndex + 1) % this.texts.length
        })

      Button('Change Text')
        .onClick(() => {
          this.currentIndex = (this.currentIndex + 1) % this.texts.length
        })
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

// Marquee 相关日志
TAG_LOGI(AceLogTag::ACE_MARQUEE, "Marquee src: %{public}s", src.c_str());
TAG_LOGD(AceLogTag::ACE_MARQUEE, "step: %{public}f, loop: %{public}d", step, loop);

// 动画相关日志
TAG_LOGD(AceLogTag::ACE_ANIMATION, "Animation duration: %{public}f", duration);
```

**关键日志点**：
- `OnModifyDone()` - 属性修改完成
- `StartMarqueeAnimation()` - 动画启动
- `UpdateTextTranslateXY()` - 文本位置更新
- `FireStartEvent()` / `FireBounceEvent()` / `FireFinishEvent()` - 事件触发

### 2. 实现dump 方法

**示例**：
```cpp
void MarqueePattern::DumpInfo(std::unique_ptr<JsonValue>& json)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto paintProperty = host->GetPaintProperty<MarqueePaintProperty>();
    CHECK_NULL_VOID(paintProperty);

    auto layoutProperty = host->GetLayoutProperty<MarqueeLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);

    json->Put("src", layoutProperty->GetSrc().value_or("").c_str());
    json->Put("playerStatus", paintProperty->GetPlayerStatus().value_or(false) ? "true" : "false");
    json->Put("scrollAmount", paintProperty->GetScrollAmount().value_or(DEFAULT_MARQUEE_SCROLL_AMOUNT));
    json->Put("loop", paintProperty->GetLoop().value_or(DEFAULT_MARQUEE_LOOP));
    json->Put("marqueeWidth", marqueeWidth_);
}
```

### 3. 常见问题定位

#### 问题 1：文本不滚动

**检查点**：
- `start` 是否设置为 `true`
- `playerStatus` 是否为 `true`
- 文本宽度是否大于 Marquee 宽度

**定位方法**：
```cpp
auto playStatus = paintProperty->GetPlayerStatus().value_or(false);
TAG_LOGI(AceLogTag::ACE_MARQUEE, "playerStatus: %{public}d", playStatus);

auto textWidth = textNode_->GetGeometryNode()->GetMarginFrameSize().Width();
TAG_LOGI(AceLogTag::ACE_MARQUEE, "textWidth: %{public}f, marqueeWidth: %{public}f",
    textWidth, marqueeWidth_);
```

#### 问题 2：动画速度异常

**检查点**：
- `step` 值是否合理
- 动画持续时间计算是否正确

**定位方法**：
```cpp
auto step = paintProperty->GetScrollAmount().value_or(DEFAULT_MARQUEE_SCROLL_AMOUNT);
auto duration = GetDuration(distance, step);
TAG_LOGI(AceLogTag::ACE_MARQUEE, "step: %{public}f, duration: %{public}f", step, duration);
```

#### 问题 3：事件不触发

**检查点**：
- 是否正确注册事件回调
- 循环次数设置是否正确

**定位方法**：
```cpp
void MarqueePattern::FireStartEvent()
{
    TAG_LOGI(AceLogTag::ACE_MARQUEE, "Firing onStart event");
    // ... 触发事件
}
```

---

## 常见问题

### Q1: Marquee 组件和 Text 组件有什么区别？

**A**:
- **Marquee**：专用于滚动文本，自动处理滚动动画
- **Text**：静态文本显示，不包含滚动功能

**选择建议**：
- 需要滚动效果 → 使用 Marquee
- 静态文本显示 → 使用 Text

### Q2: 如何控制滚动速度？

**A**：通过 `step` 属性控制
```typescript
.step(50)   // 默认速度
.step(100)  // 更快
.step(25)   // 更慢
```

### Q3: 如何实现无限循环？

**A**：设置 `loop` 为 `-1`
```typescript
.loop(-1)  // 无限循环
```

### Q4: 如何动态更新文本内容？

**A**：使用 `@State` 装饰器
```typescript
@State text: string = "Hello"

Marquee({ src: this.text })

Button('Update').onClick(() => {
  this.text = "Updated Text"
})
```

### Q5: 为什么文本不滚动？

**A**：检查以下几点：
1. `start` 是否设置为 `true`
2. 文本宽度是否大于 Marquee 宽度
3. 组件是否可见

```typescript
// 正确的配置
Marquee({
  src: 'This is a long text that will scroll',
  start: true,  // 必须设置为 true
  step: 50
})
  .width(200)  // 宽度小于文本宽度
```

### Q6: 如何监听滚动事件？

**A**：使用事件回调
```typescript
.onStart(() => {
  console.info('Started')
})
.onBounce(() => {
  console.info('Bounced')
})
.onFinish(() => {
  console.info('Finished')
})
```

### Q7: 如何设置滚动方向？

**A**：使用 `direction` 属性
```typescript
.direction(MarqueeDirection.Left)   // 从右向左
.direction(MarqueeDirection.Right)  // 从左向右
```

### Q8: Marquee 支持多行文本吗？

**A**：不支持。Marquee 只支持单行文本滚动。

### Q9: 如何暂停和恢复滚动？

**A**：通过修改 `start` 属性
```typescript
@State isPlaying: boolean = true

Marquee({
  src: 'Text',
  start: this.isPlaying
})

Button('Toggle').onClick(() => {
  this.isPlaying = !this.isPlaying
})
```

### Q10: Marquee 性能如何？

**A**：Marquee 具有以下性能优化：
- 组件不可见时自动暂停动画
- 使用高效的平移动画
- 文本测量和布局优化

---

## 附录

### A. 术语表

| 术语 | 英文 | 描述 |
|-----|------|------|
| 跑马灯 | Marquee | 滚动文本组件 |
| 滚动步长 | Scroll Amount | 每帧滚动的像素数 |
| 循环次数 | Loop | 动画重复次数 |
| 播放状态 | Player Status | 动画播放/暂停状态 |
| 滚动方向 | Direction | 文本滚动方向 |
| RTL | Right-to-Left | 从右向左的文本方向 |
| LTR | Left-to-Right | 从左向右的文本方向 |

### B. 源码文件索引

| 文件 | 行数 | 描述 |
|-----|------|------|
| `marquee_pattern.h` | ~80 | MarqueePattern 类定义 |
| `marquee_pattern.cpp` | ~450 | MarqueePattern 实现 |
| `marquee_model_ng.h` | ~50 | NG Model 定义 |
| `marquee_model_ng.cpp` | ~100 | NG Model 实现 |
| `marquee_layout_algorithm.h` | ~40 | 布局算法定义 |
| `marquee_layout_algorithm.cpp` | ~120 | 布局算法实现 |
| `marquee_layout_property.h` | ~60 | 布局属性定义 |
| `marquee_paint_property.h` | ~50 | 绘制属性定义 |
| `marquee_event_hub.h` | ~40 | 事件中心定义 |

### C. 相关文档

- [Marquee 组件官方文档](https://developer.huawei.com/consumer/cn/doc/harmonyos-references-V5/ts-container-marquee-V5)
- [Text 组件文档](https://developer.huawei.com/consumer/cn/doc/harmonyos-references-V5/ts-basic-components-text-V5)
- [动画文档](https://developer.huawei.com/consumer/cn/doc/harmonyos-guides-V5/arkts-animating-attributes-V5)

### D. 常量定义

```cpp
// 默认滚动步长（像素/帧）
constexpr double DEFAULT_MARQUEE_SCROLL_AMOUNT = 6.0;

// 默认循环次数（-1 表示无限循环）
constexpr int32_t DEFAULT_MARQUEE_LOOP = -1;

// 默认滚动延迟（毫秒/像素）
constexpr double DEFAULT_MARQUEE_SCROLL_DELAY = 85.0;

// 对齐计算常量
constexpr double MULTIPLE = 2.0;
```

### E. 版本历史

| 版本 | 日期 | 变更 |
|-----|------|------|
| v1.0 | 2026-02-01 | 初始版本 |

---

**文档结束**

> 本文档基于 OpenHarmony ace_engine 源码分析生成，如有错误或遗漏，欢迎指正。
