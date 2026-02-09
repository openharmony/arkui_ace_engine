# ArkUI LoadingProgress 组件完整知识库

> **文档版本**: v1.0
> **更新时间**: 2026-02-02
> **源码版本**: OpenHarmony ace_engine (master 分支)
> **作者**: 基于 CLAUDE.md 规范自动生成

---

## 📚 目录

1. [概述](#概述)
2. [完整调用链](#完整调用链)
3. [目录结构](#目录结构)
4. [核心类继承关系](#核心类继承关系)
5. [Pattern层详解](#pattern层详解)
6. [Model层详解](#model层详解)
7. [布局算法](#布局算法)
8. [属性系统](#属性系统)
9. [动画系统](#动画系统)
10. [可见性管理](#可见性管理)
11. [多线程支持](#多线程支持)
12. [执行流程](#执行流程)
13. [完整API清单](#完整api清单)
14. [关键实现细节](#关键实现细节)
15. [使用示例](#使用示例)
16. [测试指南](#测试指南)
17. [附录](#附录)

---

## 概述

### 组件定位

**LoadingProgress 组件**是 OpenHarmony ArkUI 框架中的**加载进度组件**,提供动态加载动画效果,支持自定义颜色、启用/禁用加载状态、自定义内容修饰器等功能,广泛应用于数据加载、页面切换、异步操作等场景。

**技术栈**:
- **前端**: ArkTS/JavaScript
- **桥接层**: LoadingProgressModifier + ViewAbstractModel
- **核心层**: NG Pattern 架构
- **渲染层**: Rosen + Skia

**代码规模**:
- 总文件数: 约 20 个文件
- 核心代码: 约 6,000+ 行 C++ 代码
- 涉及 3 个架构层次

### 功能特性

LoadingProgress 组件支持:
- **多种动画效果**: 默认提供循环加载动画
- **自定义颜色**: 支持设置进度条颜色
- **启用/禁用加载**: 可以控制动画播放
- **自定义内容修饰器**: 支持通过 Builder 自定义加载内容
- **可见性管理**: 自动管理可见区域内的动画播放
- **焦点支持**: 完整的焦点样式和键盘导航
- **多线程支持**: 支持多线程动画更新
- **窗口状态管理**: 根据窗口显示/隐藏自动启停动画
- **颜色锁定**: 支持锁定颜色不变
- **无障碍支持**: 完整的 Accessibility 支持

### 设计模式

LoadingProgress 组件采用 **NG Pattern 架构** + **Modifier 模式**:

```
前端 (ArkTS/JS)
    ↓ (Model Layer)
LoadingProgressModelNG (loading_progress_model_ng.cpp)
    ↓ (NG Pattern Layer)
LoadingProgressPattern (loading_progress_pattern.cpp)
    ↓ (NG LayoutAlgorithm Layer)
LoadingProgressLayoutAlgorithm (loading_progress_layout_algorithm.cpp)
    ↓ (Paint Method Layer)
LoadingProgressPaintMethod (loading_progress_paint_method.cpp)
    ↓ (Modifier Layer)
LoadingProgressModifier (loading_progress_modifier.cpp)
    ↓
渲染显示
```

---

## 完整调用链

### 1. 组件创建调用链

#### 调用链图

```
┌─────────────────────────────────────────────────────────┐
│ 前端 ArkTS/JavaScript                                    │
│                                                          │
│ LoadingProgress()                                       │
│     .color(Color.Red)                                   │
│     .enableLoading(true)                                │
│     .onComplete(callback)                               │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│ Model Layer (LoadingProgressModelNG)                    │
│                                                          │
│ LoadingProgressModelNG::Create()                        │
│   源码: frameworks/core/components_ng/pattern/          │
│         loading_progress/loading_progress_model_ng.cpp  │
│                                                          │
│ 执行流程:                                                 │
│ 1. 创建 FrameNode (V2::LOADING_PROGRESS_ETS_TAG)        │
│ 2. 设置初始颜色                                          │
│ 3. 应用布局属性                                          │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│ Pattern Layer (LoadingProgressPattern)                  │
│                                                          │
│ class LoadingProgressPattern                            │
│   : public Pattern                                      │
│   源码: frameworks/core/components_ng/pattern/          │
│         loading_progress/loading_progress_pattern.h     │
│                                                          │
│ 关键方法:                                                 │
│ - OnAttachToFrameNode() - 附加到节点树                   │
│ - OnModifyDone() - 属性修改完成                          │
│ - OnAttachToMainTree() - 附加到主树                      │
│ - StartAnimation() - 启动动画                            │
│ - StopAnimation() - 停止动画                             │
│ - FireBuilder() - 触发Builder回调                       │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│ LayoutAlgorithm Layer (布局计算)                         │
│                                                          │
│ class LoadingProgressLayoutAlgorithm                    │
│   : public BoxLayoutAlgorithm                           │
│   源码: frameworks/core/components_ng/pattern/          │
│         loading_progress/                               │
│         loading_progress_layout_algorithm.h             │
│                                                          │
│ 方法:                                                    │
│ - MeasureContent() - 测量内容大小                        │
│ - Measure() - 执行布局测量                               │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│ PaintMethod Layer (绘制方法)                             │
│                                                          │
│ class LoadingProgressPaintMethod                        │
│   源码: frameworks/core/components_ng/pattern/          │
│         loading_progress/                               │
│         loading_progress_paint_method.h                 │
│                                                          │
│ 方法:                                                    │
│ - UpdateModifier() - 更新绘制修饰器                      │
│ - Draw() - 执行绘制操作                                  │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│ Modifier Layer (绘制修饰器)                              │
│                                                          │
│ class LoadingProgressModifier                           │
│   源码: frameworks/core/components_ng/pattern/          │
│         loading_progress/loading_progress_modifier.h     │
│                                                          │
│ 绘制内容:                                                 │
│ - 绘制动态加载动画                                       │
│ - 支持自定义内容修饰器                                   │
└─────────────────────────────────────────────────────────┘
```

### 2. 动画生命周期调用链

```
组件附加到主树
    ↓
LoadingProgressPattern::OnAttachToMainTree()
    ├─ RegisterVisibleAreaChange() - 注册可见性变化监听
    ├─ StartAnimation() - 启动动画
    │   └─ LoadingProgressModifier::SetEnableLoading(true)
    └─ InitThemeValues() - 初始化主题值
    ↓
动画播放中...
    ↓
组件不可见/窗口隐藏/enableLoading=false
    ↓
LoadingProgressPattern::StopAnimation()
    └─ LoadingProgressModifier::SetEnableLoading(false)
```

### 3. 自定义内容修饰器调用链

```
用户设置 .contentModifier(builder)
    ↓
LoadingProgressModelNG::SetBuilderFunc(builder)
    ↓
LoadingProgressPattern::SetBuilderFunc(makeFunc)
    ↓
LoadingProgressPattern::FireBuilder()
    ├─ BuildContentModifierNode() - 创建自定义节点
    └─ contentModifierNode_ - 保存引用
    ↓
LoadingProgressModifier::UseContentModifier() - 使用自定义内容
    ↓
渲染自定义内容而非默认动画
```

---

## 目录结构

```
components_ng/pattern/loading_progress/
├── loading_progress_pattern.h/cpp              # Pattern层核心类
├── loading_progress_model.h                    # Model接口定义
├── loading_progress_model_ng.h/cpp             # NG Model实现
├── loading_progress_model_static.h/cpp         # Static Model实现
├── loading_progress_layout_property.h          # 布局属性
├── loading_progress_layout_algorithm.h/cpp     # 布局算法
├── loading_progress_paint_property.h           # 绘制属性
├── loading_progress_paint_method.h             # 绘制方法
├── loading_progress_modifier.h/cpp             # 绘制修饰器
├── loading_progress_owner.h                    # Owner定义
├── loading_progress_style.h                    # 样式定义
├── loading_progress_base.h                     # 基础定义
├── loading_progress_utill.h                    # 工具函数
├── loading_progress_pattern_multi_thread.cpp   # 多线程支持
└── BUILD.gn                                    # 构建配置
```

---

## 核心类继承关系

### Pattern 层

```cpp
LoadingProgressPattern
├── 继承: public Pattern
├── 生命周期:
│   ├── OnAttachToFrameNode() - 附加到节点
│   ├── OnDetachFromFrameNode() - 从节点分离
│   ├── OnAttachToMainTree() - 附加到主树
│   ├── OnDetachFromMainTree() - 从主树分离
│   ├── OnModifyDone() - 属性修改完成
│   ├── OnWindowHide() - 窗口隐藏
│   └── OnWindowShow() - 窗口显示
└── 创建方法:
    ├── CreateLayoutProperty() - 创建布局属性
    ├── CreatePaintProperty() - 创建绘制属性
    ├── CreateLayoutAlgorithm() - 创建布局算法
    └── CreateNodePaintMethod() - 创建绘制方法
```

### Model 层

```cpp
LoadingProgressModelNG
├── 继承: public LoadingProgressModel
├── 静态方法 (用于直接操作FrameNode):
│   ├── CreateFrameNode() - 创建节点
│   ├── SetColor() - 设置颜色
│   ├── SetEnableLoading() - 设置启用加载
│   ├── SetForegroundColor() - 设置前景色
│   ├── SetBuilderFunc() - 设置Builder函数
│   └── ResetColor() - 重置颜色
└── 实例方法 (用于链式调用):
    ├── Create() - 创建组件
    ├── SetColor() - 设置颜色
    ├── SetEnableLoading() - 设置启用加载
    ├── SetBuilderFunc() - 设置Builder函数
    └── ResetColor() - 重置颜色
```

### LayoutAlgorithm 层

```cpp
LoadingProgressLayoutAlgorithm
├── 继承: public BoxLayoutAlgorithm
└── 核心方法:
    └── MeasureContent() - 测量内容大小
```

---

## Pattern层详解

### LoadingProgressPattern 核心职责

**源码位置**: `frameworks/core/components_ng/pattern/loading_progress/loading_progress_pattern.h`

#### 1. 生命周期管理

```cpp
// 附加到节点树时调用
void LoadingProgressPattern::OnAttachToFrameNode()
{
    // 1. 初始化主题值
    InitThemeValues();

    // 2. 初始化焦点事件
    InitFocusEvent();
}

// 附加到主树时调用
void LoadingProgressPattern::OnAttachToMainTree()
{
    // 1. 注册可见性变化监听
    RegisterVisibleAreaChange();

    // 2. 启动动画
    StartAnimation();

    // 3. 触发Builder (如果有)
    FireBuilder();
}

// 从主树分离时调用
void LoadingProgressPattern::OnDetachFromMainTree()
{
    // 停止动画
    StopAnimation();

    // 移除可见性监听
    hasVisibleChangeRegistered_ = false;
}

// 属性修改完成时调用
void LoadingProgressPattern::OnModifyDone()
{
    auto paintProperty = GetPaintProperty<LoadingProgressPaintProperty>();

    // 1. 更新颜色
    if (paintProperty->GetColorValue()) {
        UpdateColor(paintProperty->GetColorValue().value());
    }

    // 2. 更新启用状态
    enableLoading_ = paintProperty->GetEnableLoadingValue(true);

    // 3. 启动/停止动画
    if (enableLoading_ && isVisibleArea_) {
        StartAnimation();
    } else {
        StopAnimation();
    }

    // 4. 触发Builder
    FireBuilder();
}
```

#### 2. 动画控制

```cpp
// 启动动画
void LoadingProgressPattern::StartAnimation()
{
    if (!loadingProgressModifier_) {
        return;
    }

    // 设置启用加载状态
    loadingProgressModifier_->SetEnableLoading(true);

    // 标记需要重绘
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PaintProperty::PAINT_PROPERTY);
}

// 停止动画
void LoadingProgressPattern::StopAnimation()
{
    if (!loadingProgressModifier_) {
        return;
    }

    // 设置禁用加载状态
    loadingProgressModifier_->SetEnableLoading(false);

    // 标记需要重绘
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PaintProperty::PAINT_PROPERTY);
}
```

#### 3. 可见性管理

```cpp
// 注册可见性变化监听
void LoadingProgressPattern::RegisterVisibleAreaChange()
{
    if (hasVisibleChangeRegistered_) {
        return;
    }

    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto callback = [weak = WeakClaim(this)](bool isVisible) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->OnVisibleChange(isVisible);
        }
    };

    // 注册可见性变化回调
    host->GetOrCreateVisibleAreaChangeNode()->Bind(
        VisibleType::CURRENT,
        0.0f,
        callback
    );

    hasVisibleChangeRegistered_ = true;
}

// 可见性变化处理
void LoadingProgressPattern::OnVisibleChange(bool isVisible)
{
    isVisibleArea_ = isVisible;

    // 根据可见性和启用状态控制动画
    if (enableLoading_ && isVisible) {
        StartAnimation();
    } else {
        StopAnimation();
    }
}
```

#### 4. 自定义内容修饰器

```cpp
// 设置Builder函数
void LoadingProgressPattern::SetBuilderFunc(LoadingProgressMakeCallback&& makeFunc)
{
    if (makeFunc == nullptr) {
        makeFunc_ = std::nullopt;
        contentModifierNode_ = nullptr;
        OnModifyDone();
        return;
    }

    makeFunc_ = std::move(makeFunc);
}

// 触发Builder
void LoadingProgressPattern::FireBuilder()
{
    if (!makeFunc_.has_value()) {
        return;
    }

    // 创建自定义内容节点
    contentModifierNode_ = BuildContentModifierNode();

    // 标记需要重绘
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PaintProperty::PAINT_PROPERTY);
}

// 构建内容修饰器节点
RefPtr<FrameNode> LoadingProgressPattern::BuildContentModifierNode()
{
    if (!makeFunc_.has_value()) {
        return nullptr;
    }

    // 调用Builder函数
    auto makeFunc = makeFunc_.value();
    LoadingProgressConfiguration config(enableLoading_, true);
    return makeFunc(config);
}
```

#### 5. 颜色管理

```cpp
// 更新颜色
void LoadingProgressPattern::UpdateColor(const Color& color, bool isFirstLoad)
{
    if (!loadingProgressModifier_) {
        return;
    }

    // 如果颜色锁定且不是首次加载,则不更新
    if (colorLock_ && !isFirstLoad) {
        return;
    }

    // 设置颜色
    loadingProgressModifier_->SetColor(color);

    // 标记需要重绘
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PaintProperty::PAINT_PROPERTY);
}

// 初始化主题值
void LoadingProgressPattern::InitThemeValues()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);

    // 获取LoadingProgress主题
    auto theme = pipelineContext->GetTheme<LoadingProgressTheme>();
    CHECK_NULL_VOID(theme);

    // 获取默认颜色
    defaultColor_ = theme->GetLoadingColor();

    // 如果用户未设置颜色,则使用主题颜色
    auto paintProperty = GetPaintProperty<LoadingProgressPaintProperty>();
    if (!paintProperty->GetColorValue().has_value()) {
        UpdateColor(defaultColor_, true);
    }
}
```

#### 6. 窗口状态管理

```cpp
// 窗口隐藏时调用
void LoadingProgressPattern::OnWindowHide()
{
    // 停止动画以节省资源
    StopAnimation();

    isShow_ = false;
}

// 窗口显示时调用
void LoadingProgressPattern::OnWindowShow()
{
    // 恢复动画
    if (enableLoading_ && isVisibleArea_) {
        StartAnimation();
    }

    isShow_ = true;
}
```

---

## Model层详解

### LoadingProgressModelNG 核心方法

**源码位置**: `frameworks/core/components_ng/pattern/loading_progress/loading_progress_model_ng.h`

#### 1. 创建组件

```cpp
void LoadingProgressModelNG::Create()
{
    // 1. 创建 FrameNode
    auto frameNode = FrameNode::CreateFrameNode(
        V2::LOADING_PROGRESS_ETS_TAG,
        -1,
        []() { return MakeRefPtr<LoadingProgressPattern>(); }
    );

    // 2. 设置默认属性
    auto paintProperty = frameNode->GetPaintProperty<LoadingProgressPaintProperty>();
    paintProperty->SetEnableLoading(true);

    // 3. 添加到ViewStack
    ViewStackProcessor::GetInstance()->Push(frameNode);
}
```

#### 2. 属性设置 (链式调用)

```cpp
// 设置颜色
void LoadingProgressModelNG::SetColor(const Color& value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);

    auto paintProperty = frameNode->GetPaintProperty<LoadingProgressPaintProperty>();
    paintProperty->SetColor(value);
    paintProperty->SetColorByUser(true);

    // 更新Pattern
    auto pattern = frameNode->GetPattern<LoadingProgressPattern>();
    pattern->UpdateColor(value);

    frameNode->MarkModifyDone();
}

// 设置启用加载
void LoadingProgressModelNG::SetEnableLoading(bool enable)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);

    auto paintProperty = frameNode->GetPaintProperty<LoadingProgressPaintProperty>();
    paintProperty->SetEnableLoading(enable);

    frameNode->MarkModifyDone();
}

// 重置颜色
void LoadingProgressModelNG::ResetColor()
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);

    auto paintProperty = frameNode->GetPaintProperty<LoadingProgressPaintProperty>();
    paintProperty->SetColor(std::nullopt);
    paintProperty->SetColorByUser(false);

    frameNode->MarkModifyDone();
}
```

#### 3. Builder函数设置

```cpp
void LoadingProgressModelNG::SetBuilderFunc(
    FrameNode* frameNode,
    NG::LoadingProgressMakeCallback&& jsMake)
{
    CHECK_NULL_VOID(frameNode);

    auto pattern = frameNode->GetPattern<LoadingProgressPattern>();
    pattern->SetBuilderFunc(std::move(jsMake));
}
```

#### 4. 静态方法 (直接操作 FrameNode)

```cpp
// 静态方法示例 - 用于直接操作已存在的 FrameNode
RefPtr<FrameNode> LoadingProgressModelNG::CreateFrameNode(int32_t nodeId)
{
    auto frameNode = FrameNode::CreateFrameNode(
        V2::LOADING_PROGRESS_ETS_TAG,
        nodeId,
        []() { return MakeRefPtr<LoadingProgressPattern>(); }
    );

    return frameNode;
}

void LoadingProgressModelNG::SetColor(FrameNode* frameNode, const Color& value)
{
    CHECK_NULL_VOID(frameNode);

    auto paintProperty = frameNode->GetPaintProperty<LoadingProgressPaintProperty>();
    paintProperty->SetColor(value);
    paintProperty->SetColorByUser(true);

    auto pattern = frameNode->GetPattern<LoadingProgressPattern>();
    pattern->UpdateColor(value);

    frameNode->MarkModifyDone();
}

void LoadingProgressModelNG::SetEnableLoading(FrameNode* frameNode, bool enable)
{
    CHECK_NULL_VOID(frameNode);

    auto paintProperty = frameNode->GetPaintProperty<LoadingProgressPaintProperty>();
    paintProperty->SetEnableLoading(enable);

    frameNode->MarkModifyDone();
}
```

---

## 布局算法

### LoadingProgressLayoutAlgorithm

**源码位置**: `frameworks/core/components_ng/pattern/loading_progress/loading_progress_layout_algorithm.h`

#### 测量流程

```cpp
std::optional<SizeF> LoadingProgressLayoutAlgorithm::MeasureContent(
    const LayoutConstraintF& contentConstraint,
    LayoutWrapper* layoutWrapper)
{
    // 1. 获取默认尺寸
    float defaultSize = 100.0f; // 默认100vp

    // 2. 应用约束
    float width = contentConstraint.selfIdealSize.Width().value_or(defaultSize);
    float height = contentConstraint.selfIdealSize.Height().value_or(defaultSize);

    // 3. 确保最小尺寸
    if (width < contentConstraint.minSize.Width()) {
        width = contentConstraint.minSize.Width();
    }
    if (height < contentConstraint.minSize.Height()) {
        height = contentConstraint.minSize.Height();
    }

    // 4. 应用最大尺寸约束
    if (contentConstraint.maxSize.Width().has_value() &&
        width > contentConstraint.maxSize.Width().value()) {
        width = contentConstraint.maxSize.Width().value();
    }
    if (contentConstraint.maxSize.Height().has_value() &&
        height > contentConstraint.maxSize.Height().value()) {
        height = contentConstraint.maxSize.Height().value();
    }

    // 5. 返回正方形尺寸 (1:1)
    return SizeF(width, height);
}
```

#### 布局特点

1. **固定宽高比**: LoadingProgress 默认为正方形 (1:1)
2. **默认尺寸**: 100vp × 100vp
3. **自适应大小**: 可根据容器约束调整
4. **最小尺寸**: 支持设置最小尺寸约束

---

## 属性系统

### LayoutProperty (布局属性)

**源码位置**: `frameworks/core/components_ng/pattern/loading_progress/loading_progress_layout_property.h`

| 属性 | 类型 | 默认值 | 说明 |
|------|------|--------|------|
| (无特殊布局属性) | - | - | 使用默认BoxLayout属性 |

### PaintProperty (绘制属性)

**源码位置**: `frameworks/core/components_ng/pattern/loading_progress/loading_progress_paint_property.h`

| 属性 | 类型 | 默认值 | 说明 |
|------|------|--------|------|
| `color` | Color | 主题颜色 | 进度条颜色 |
| `enableLoading` | bool | true | 是否启用加载动画 |
| `foregroundColor` | Color | - | 前景色 (可选) |
| `colorByUser` | bool | false | 颜色是否由用户设置 |

### LoadingProgressOwner

**源码位置**: `frameworks/core/components_ng/pattern/loading_progress/loading_progress_owner.h`

```cpp
enum class LoadingProgressOwner {
    SELF,       // 自己拥有
    PARENT,     // 父组件拥有
    // 用于决定修饰器的行为
};
```

### 属性更新流程

```
用户设置属性 (ArkTS)
    ↓
LoadingProgressModelNG::SetXxx()
    ↓
LoadingProgressPaintProperty::SetXxx()
    ↓
LoadingProgressPattern::OnModifyDone()
    ↓
LoadingProgressPattern::UpdateXxx()
    ↓
LoadingProgressModifier::SetXxx()
    ↓
标记需要重绘 (MarkDirtyNode)
```

---

## 动画系统

### LoadingProgressModifier 动画实现

**源码位置**: `frameworks/core/components_ng/pattern/loading_progress/loading_progress_modifier.h`

#### 动画状态控制

```cpp
class LoadingProgressModifier : public ContentModifier {
public:
    // 设置启用加载状态
    void SetEnableLoading(bool enable)
    {
        enableLoading_ = enable;

        // 触发动画更新
        if (enable) {
            StartAnimation();
        } else {
            StopAnimation();
        }

        MarkDirtyNode();
    }

private:
    bool enableLoading_ = true;
    Color color_;
    bool useContentModifier_ = false;

    // 动画相关
    float animationValue_ = 0.0f;
    RefPtr<AnimatablePropertyFloat>> animatableProperty_;
};
```

#### 动画绘制

```cpp
void LoadingProgressModifier::Draw(DrawingContext& context)
{
    // 如果使用内容修饰器,绘制自定义内容
    if (useContentModifier_ && contentModifierNode_) {
        DrawCustomContent(context);
        return;
    }

    // 如果未启用加载,不绘制动画
    if (!enableLoading_) {
        return;
    }

    // 绘制默认加载动画
    DrawDefaultAnimation(context);
}

void LoadingProgressModifier::DrawDefaultAnimation(DrawingContext& context)
{
    auto canvas = context.GetCanvas();

    // 获取当前尺寸
    auto width = GetWidth();
    auto height = GetHeight();
    auto centerX = width / 2.0f;
    auto centerY = height / 2.0f;

    // 获取动画值
    float progress = GetAnimationValue();

    // 绘制动态圆环
    float radius = std::min(width, height) / 2.0f * 0.8f;
    float startAngle = 0.0f;
    float sweepAngle = 270.0f * progress;

    // 设置画笔
    RSBrush brush;
    brush.SetColor(ToRSColor(color_));
    canvas->AttachBrush(brush);

    // 绘制圆弧
    canvas->DrawArc(
        RSRect(centerX - radius, centerY - radius,
               centerX + radius, centerY + radius),
        startAngle, sweepAngle
    );
}
```

### 动画性能优化

1. **可见性控制**: 组件不可见时停止动画
2. **窗口状态**: 窗口隐藏时停止动画
3. **启用状态**: enableLoading=false 时停止动画
4. **多线程支持**: 支持在独立线程中更新动画

---

## 可见性管理

### 可见性检测机制

```cpp
void LoadingProgressPattern::RegisterVisibleAreaChange()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto callback = [weak = WeakClaim(this)](bool isVisible) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->OnVisibleChange(isVisible);
        }
    };

    // 创建可见性比率回调
    auto ratioCallback = [weak = WeakClaim(this)](double ratio) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            // ratio >= 1.0 表示完全可见
            pattern->OnVisibleChange(ratio >= 1.0);
        }
    };

    auto visibleAreaChangeNode = host->GetOrCreateVisibleAreaChangeNode();

    // 注册当前可见性
    visibleAreaChangeNode->Bind(
        VisibleType::CURRENT,
        0.0f,
        callback
    );

    // 注册可见性比率
    visibleAreaChangeNode->BindWithVisibleRatio(
        VisibleType::CURRENT,
        ratioCallback
    );
}

void LoadingProgressPattern::OnVisibleChange(bool isVisible)
{
    // 保存可见性状态
    isVisibleArea_ = isVisible;

    // 根据可见性和启用状态控制动画
    if (enableLoading_) {
        if (isVisible) {
            StartAnimation();
        } else {
            StopAnimation();
        }
    }
}
```

### 可见性状态表

| 状态 | isVisibleArea_ | enableLoading_ | 动画状态 |
|------|----------------|----------------|----------|
| 完全可见 | true | true | 播放 |
| 部分可见 | true | true | 播放 |
| 不可见 | false | true | 停止 |
| 可见但禁用 | true | false | 停止 |
| 不可见且禁用 | false | false | 停止 |

---

## 多线程支持

### 多线程动画更新

**源码位置**: `frameworks/core/components_ng/pattern/loading_progress/loading_progress_pattern_multi_thread.cpp`

```cpp
// 附加到节点树 (多线程版本)
void LoadingProgressPattern::OnAttachToFrameNodeMultiThread()
{
    // 在独立线程中初始化
    InitThemeValues();
}

// 附加到主树 (多线程版本)
void LoadingProgressPattern::OnAttachToMainTreeMultiThread()
{
    // 在独立线程中启动动画
    RegisterVisibleAreaChange();
    StartAnimation();
    FireBuilder();
}

// 从主树分离 (多线程版本)
void LoadingProgressPattern::OnDetachFromMainTreeMultiThread()
{
    // 在独立线程中停止动画
    StopAnimation();
    hasVisibleChangeRegistered_ = false;
}
```

### 多线程优势

1. **性能提升**: 动画计算在独立线程执行,不阻塞主线程
2. **流畅度提升**: 主线程专注于UI渲染
3. **复杂动画**: 支持更复杂的动画效果

---

## 执行流程

### 完整生命周期

```
1. 创建阶段
   LoadingProgressModelNG::Create()
   → FrameNode::CreateFrameNode()
   → LoadingProgressPattern::OnAttachToFrameNode()
   → InitThemeValues()
   → InitFocusEvent()

2. 属性设置阶段
   LoadingProgressModelNG::SetColor()
   → LoadingProgressPaintProperty::SetColor()
   → LoadingProgressPattern::OnModifyDone()
   → LoadingProgressPattern::UpdateColor()

3. 附加到主树阶段
   LoadingProgressPattern::OnAttachToMainTree()
   → RegisterVisibleAreaChange()
   → StartAnimation()
   → FireBuilder()

4. 动画播放阶段
   LoadingProgressModifier::Draw()
   → DrawDefaultAnimation()
   → 持续更新动画值
   → MarkDirtyNode()

5. 可见性变化阶段
   组件滚动/窗口变化
   → OnVisibleChange(isVisible)
   → StartAnimation() / StopAnimation()

6. 销毁阶段
   LoadingProgressPattern::OnDetachFromMainTree()
   → StopAnimation()
   → 清理资源
   → LoadingProgressPattern::OnDetachFromFrameNode()
```

---

## 完整API清单

### ArkTS API

```typescript
// 创建组件
LoadingProgress(): void

// 属性设置
color(color: ResourceColor): void              // 设置进度条颜色
enableLoading(enable: boolean): void            // 设置启用/禁用加载
foregroundColor(color: ResourceColor): void     // 设置前景色
contentModifier(builder: LoadingProgressMakeCallback): void  // 自定义内容

// 方法
resetColor(): void                              // 重置颜色为默认值
```

### C++ Model API (LoadingProgressModelNG)

```cpp
// 创建组件
void Create() override;

// 属性设置
void SetColor(const Color& value) override;
void SetColorByUser(bool isSetByUser) override;
void SetEnableLoading(bool enable) override;
void SetForegroundColor(const Color& value);
void ResetColor() override;

// Builder设置
void SetBuilderFunc(LoadingProgressMakeCallback&& makeFunc);

// 静态方法
static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId);
static void SetColor(FrameNode* frameNode, const Color& value);
static void SetColorByUser(FrameNode* frameNode, bool isSetByUser);
static bool GetEnableLoading(FrameNode* frameNode);
static void SetEnableLoading(FrameNode* frameNode, bool enable);
static void SetForegroundColor(FrameNode* frameNode, const Color& value);
static void SetBuilderFunc(FrameNode* frameNode, NG::LoadingProgressMakeCallback&& jsMake);
static void ResetColor(FrameNode* frameNode);
static void ResetForegroundColor(FrameNode* frameNode);
```

---

## 关键实现细节

### 1. 主题颜色管理

**源码**: `loading_progress_pattern.cpp:InitThemeValues()`

```cpp
void LoadingProgressPattern::InitThemeValues()
{
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);

    // 获取LoadingProgress主题
    auto theme = pipelineContext->GetTheme<LoadingProgressTheme>();
    CHECK_NULL_VOID(theme);

    // 获取默认颜色
    defaultColor_ = theme->GetLoadingColor();
    focusedColor_ = theme->GetFocusColor();

    // 如果用户未设置颜色,则使用主题颜色
    auto paintProperty = GetPaintProperty<LoadingProgressPaintProperty>();
    if (!paintProperty->GetColorByUserValue(false)) {
        UpdateColor(defaultColor_, true);
    }
}
```

**主题属性**:
```cpp
class LoadingProgressTheme {
public:
    Color GetLoadingColor() const;      // 默认加载颜色
    Color GetFocusColor() const;        // 焦点颜色
};
```

### 2. 颜色锁定机制

**源码**: `loading_progress_pattern.cpp:UpdateColor()`

```cpp
void LoadingProgressPattern::UpdateColor(const Color& color, bool isFirstLoad)
{
    if (!loadingProgressModifier_) {
        return;
    }

    // 如果颜色锁定且不是首次加载,则不更新
    if (colorLock_ && !isFirstLoad) {
        return;
    }

    // 设置颜色
    loadingProgressModifier_->SetColor(color);

    // 标记需要重绘
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PaintProperty::PAINT_PROPERTY);
}

void LoadingProgressPattern::SetColorLock(bool colorLock)
{
    colorLock_ = colorLock;
}
```

**用途**: 防止外部修改已设置的颜色

### 3. 自定义内容修饰器实现

**源码**: `loading_progress_pattern.cpp:FireBuilder()`

```cpp
void LoadingProgressPattern::FireBuilder()
{
    if (!makeFunc_.has_value()) {
        return;
    }

    // 检查是否需要重建
    if (contentModifierNode_) {
        // 节点已存在,不重复创建
        return;
    }

    // 创建自定义内容节点
    auto makeFunc = makeFunc_.value();
    LoadingProgressConfiguration config(enableLoading_, true);
    contentModifierNode_ = makeFunc(config);

    CHECK_NULL_VOID(contentModifierNode_);

    // 设置使用内容修饰器
    if (loadingProgressModifier_) {
        loadingProgressModifier_->SetUseContentModifier(true);
        loadingProgressModifier_->SetContentModifierNode(contentModifierNode_);
    }

    // 标记需要重绘
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PaintProperty::PAINT_PROPERTY);
}
```

**LoadingProgressConfiguration 定义**:
```cpp
struct LoadingProgressConfiguration : public CommonConfiguration {
    bool enableloading_;

    LoadingProgressConfiguration(bool enableloading, bool enabled)
        : CommonConfiguration(enabled), enableloading_(enableloading)
    {}
};

using LoadingProgressMakeCallback =
    std::function<RefPtr<FrameNode>(const LoadingProgressConfiguration&)>;
```

### 4. 焦点样式管理

**源码**: `loading_progress_pattern.cpp:InitFocusEvent()`

```cpp
void LoadingProgressPattern::InitFocusEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto focusHub = host->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);

    // 监听焦点获取事件
    focusHub->AddOnFocusCallback([weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleFocusEvent();
        }
    });

    // 监听焦点失去事件
    focusHub->AddOnBlurCallback([weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleBlurEvent();
        }
    });
}

void LoadingProgressPattern::HandleFocusEvent()
{
    SetFocusStyle();
    AddIsFocusActiveUpdateEvent();
}

void LoadingProgressPattern::HandleBlurEvent()
{
    ClearFocusStyle();
    RemoveIsFocusActiveUpdateEvent();
}

void LoadingProgressPattern::SetFocusStyle()
{
    if (!focusedColor_.HasValue()) {
        return;
    }

    // 使用焦点颜色
    UpdateColor(focusedColor_, false);
}

void LoadingProgressPattern::ClearFocusStyle()
{
    // 恢复默认颜色
    UpdateColor(defaultColor_, false);
}
```

### 5. 可见区域优化

**源码**: `loading_progress_pattern.cpp:RegisterVisibleAreaChange()`

```cpp
void LoadingProgressPattern::RegisterVisibleAreaChange()
{
    if (hasVisibleChangeRegistered_) {
        return;
    }

    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto callback = [weak = WeakClaim(this)](bool isVisible) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->OnVisibleChange(isVisible);
        }
    };

    auto visibleAreaChangeNode = host->GetOrCreateVisibleAreaChangeNode();

    // 注册可见性变化回调
    visibleAreaChangeNode->Bind(
        VisibleType::CURRENT,
        0.0f,
        callback
    );

    hasVisibleChangeRegistered_ = true;
}

void LoadingProgressPattern::OnVisibleChange(bool isVisible)
{
    isVisibleArea_ = isVisible;

    // 根据可见性和启用状态控制动画
    if (enableLoading_) {
        if (isVisible) {
            StartAnimation();
        } else {
            StopAnimation();
        }
    }
}
```

**优化效果**:
- 组件滚动到不可见区域时自动停止动画
- 组件滚动到可见区域时自动启动动画
- 节省CPU和GPU资源

---

## 使用示例

### ArkTS 示例 1: 基础使用

```typescript
@Entry
@Component
struct LoadingProgressExample {
  @State isLoading: boolean = true

  build() {
    Column() {
      LoadingProgress()
        .color(Color.Blue)
        .width(100)
        .height(100)

      Button('Toggle Loading')
        .onClick(() => {
          this.isLoading = !this.isLoading
        })
    }
    .width('100%')
    .height('100%')
  }
}
```

### ArkTS 示例 2: 自定义颜色和大小

```typescript
@Entry
@Component
struct CustomLoadingProgress {
  build() {
    LoadingProgress()
      .color('#FF0000')     // 红色
      .width(200)
      .height(200)
      .enableLoading(true)
  }
}
```

### ArkTS 示例 3: 动态控制

```typescript
@Entry
@Component
struct DynamicLoadingProgress {
  @State enableLoading: boolean = false

  build() {
    Column({ space: 20 }) {
      LoadingProgress()
        .color(Color.Green)
        .enableLoading(this.enableLoading)
        .width(150)
        .height(150)

      Button(this.enableLoading ? 'Stop' : 'Start')
        .onClick(() => {
          this.enableLoading = !this.enableLoading
        })
    }
  }
}
```

### ArkTS 示例 4: 自定义内容修饰器

```typescript
@Entry
@Component
struct CustomContentLoadingProgress {
  @Builder
  customContent() {
    Row({ space: 10 }) {
      LoadingProgress()
        .width(50)
        .height(50)
        .color(Color.Blue)

      Text('Loading...')
        .fontSize(20)
        .fontColor(Color.Blue)
    }
    .padding(20)
    .backgroundColor(Color.Gray)
    .borderRadius(10)
  }

  build() {
    LoadingProgress()
      .contentModifier(this.customContent)
  }
}
```

### ArkTS 示例 5: 使用Controller控制

```typescript
@Entry
@Component
struct LoadingProgressWithController {
  @State text: string = 'Loading...'

  build() {
    Column() {
      LoadingProgress()
        .color(Color.Orange)
        .width(120)
        .height(120)
        .onAppear(() => {
          this.text = 'Loading started...'
        })

      Text(this.text)
        .margin({ top: 20 })
    }
  }
}
```

### ArkTS 示例 6: 列表中的加载指示器

```typescript
@Entry
@Component
struct ListWithLoadingProgress {
  @State data: string[] = ['Item 1', 'Item 2', 'Item 3']
  @State isLoading: boolean = false

  build() {
    Column() {
      List() {
        ForEach(this.data, (item: string) => {
          ListItem() {
            Text(item)
              .width('100%')
              .height(50)
          }
        })

        // 加载更多指示器
        ListItem() {
          Row() {
            if (this.isLoading) {
              LoadingProgress()
                .width(30)
                .height(30)
                .color(Color.Blue)
            } else {
              Text('Pull to load more')
            }
          }
          .width('100%')
          .height(80)
          .justifyContent(FlexAlign.Center)
        }
      }
      .onReachEnd(() => {
        if (!this.isLoading) {
          this.isLoading = true
          // 模拟加载更多数据
          setTimeout(() => {
            this.data.push(`Item ${this.data.length + 1}`)
            this.isLoading = false
          }, 2000)
        }
      })
    }
  }
}
```

---

## 测试指南

### 单元测试要点

#### LoadingProgressPattern 测试

**关键测试场景**:

1. **生命周期测试**:
   - `OnAttachToFrameNode()` - 验证初始化
   - `OnAttachToMainTree()` - 验证动画启动
   - `OnDetachFromMainTree()` - 验证动画停止
   - `OnModifyDone()` - 验证属性更新

2. **动画控制测试**:
   - `StartAnimation()` - 验证动画启动
   - `StopAnimation()` - 验证动画停止
   - 可见性变化时的动画控制

3. **颜色管理测试**:
   - `UpdateColor()` - 验证颜色更新
   - 颜色锁定机制
   - 主题颜色应用

4. **自定义内容测试**:
   - `SetBuilderFunc()` - 验证Builder设置
   - `FireBuilder()` - 验证Builder触发
   - `BuildContentModifierNode()` - 验证节点创建

5. **窗口状态测试**:
   - `OnWindowHide()` - 验证窗口隐藏处理
   - `OnWindowShow()` - 验证窗口显示处理

#### LoadingProgressLayoutAlgorithm 测试

**关键测试场景**:

1. **尺寸测量**:
   - 默认尺寸 (100vp)
   - 最小尺寸约束
   - 最大尺寸约束
   - 自定义宽高

2. **宽高比**:
   - 验证输出为正方形 (1:1)
   - 非正方形输入的处理

#### LoadingProgressModelNG 测试

**关键测试场景**:

1. **属性设置**:
   - 颜色属性
   - 启用加载属性

2. **静态方法**:
   - 直接操作 FrameNode
   - 属性更新同步

3. **Builder函数**:
   - Builder设置
   - Builder触发
   - 自定义内容创建

### 测试用例模板

```cpp
// LoadingProgressPatternTest.cpp

TEST_F(LoadingProgressPatternTest, OnAttachToMainTree_ShouldStartAnimation)
{
    // Arrange
    auto pattern = CreateLoadingProgressPattern();
    auto paintProperty = pattern->GetPaintProperty<LoadingProgressPaintProperty>();
    paintProperty->SetEnableLoading(true);

    // Act
    pattern->OnAttachToMainTree();

    // Assert
    auto modifier = pattern->GetLoadingProgressModifier();
    EXPECT_TRUE(modifier->GetEnableLoading());
    EXPECT_TRUE(pattern->hasVisibleChangeRegistered_);
}

TEST_F(LoadingProgressPatternTest, OnVisibleChange_WithEnableLoadingTrue_ShouldStartAnimation)
{
    // Arrange
    auto pattern = CreateLoadingProgressPattern();
    pattern->enableLoading_ = true;

    // Act
    pattern->OnVisibleChange(true);

    // Assert
    auto modifier = pattern->GetLoadingProgressModifier();
    EXPECT_TRUE(modifier->GetEnableLoading());
}

TEST_F(LoadingProgressPatternTest, OnVisibleChange_WithEnableLoadingFalse_ShouldStopAnimation)
{
    // Arrange
    auto pattern = CreateLoadingProgressPattern();
    pattern->enableLoading_ = false;
    pattern->isVisibleArea_ = true;

    // Act
    pattern->OnVisibleChange(true);

    // Assert
    auto modifier = pattern->GetLoadingProgressModifier();
    EXPECT_FALSE(modifier->GetEnableLoading());
}

TEST_F(LoadingProgressPatternTest, UpdateColor_WithColorLockTrue_ShouldNotUpdate)
{
    // Arrange
    auto pattern = CreateLoadingProgressPattern();
    pattern->SetColorLock(true);
    Color newColor(Color::RED);

    // Act
    pattern->UpdateColor(newColor, false);

    // Assert
    auto modifier = pattern->GetLoadingProgressModifier();
    EXPECT_NE(modifier->GetColor(), newColor);
}

TEST_F(LoadingProgressPatternTest, SetBuilderFunc_ShouldTriggerFireBuilder)
{
    // Arrange
    auto pattern = CreateLoadingProgressPattern();
    LoadingProgressMakeCallback makeFunc =
        [](const LoadingProgressConfiguration& config) {
            return FrameNode::CreateFrameNode(
                V2::TEXT_ETS_TAG, -1,
                []() { return MakeRefPtr<TextPattern>(); }
            );
        };

    // Act
    pattern->SetBuilderFunc(std::move(makeFunc));
    pattern->FireBuilder();

    // Assert
    EXPECT_NE(pattern->GetContentModifierNode(), nullptr);
}

TEST_F(LoadingProgressPatternTest, OnWindowHide_ShouldStopAnimation)
{
    // Arrange
    auto pattern = CreateLoadingProgressPattern();
    pattern->enableLoading_ = true;
    pattern->StartAnimation();

    // Act
    pattern->OnWindowHide();

    // Assert
    auto modifier = pattern->GetLoadingProgressModifier();
    EXPECT_FALSE(modifier->GetEnableLoading());
    EXPECT_FALSE(pattern->isShow_);
}

TEST_F(LoadingProgressPatternTest, OnWindowShow_ShouldStartAnimation)
{
    // Arrange
    auto pattern = CreateLoadingProgressPattern();
    pattern->enableLoading_ = true;
    pattern->isVisibleArea_ = true;
    pattern->OnWindowHide();

    // Act
    pattern->OnWindowShow();

    // Assert
    auto modifier = pattern->GetLoadingProgressModifier();
    EXPECT_TRUE(modifier->GetEnableLoading());
    EXPECT_TRUE(pattern->isShow_);
}
```

### 分支覆盖要点

#### LoadingProgressPattern::OnModifyDone

| 分支 | 条件 | 测试方法 |
|------|------|----------|
| 颜色存在 | GetColorValue() 有值 | OnModifyDone_WithColor |
| 颜色不存在 | GetColorValue() 无值 | OnModifyDone_WithoutColor |
| 启用加载 | enableLoading_=true | OnModifyDone_EnableLoading |
| 禁用加载 | enableLoading_=false | OnModifyDone_DisableLoading |
| 可见区域 | isVisibleArea_=true | OnModifyDone_VisibleArea |
| 不可见区域 | isVisibleArea_=false | OnModifyDone_NotVisibleArea |

#### LoadingProgressPattern::UpdateColor

| 分支 | 条件 | 测试方法 |
|------|------|----------|
| 正常更新 | colorLock_=false | UpdateColor_Normal |
| 颜色锁定 | colorLock_=true, isFirstLoad=false | UpdateColor_ColorLocked |
| 首次加载 | isFirstLoad=true | UpdateColor_FirstLoad |

#### LoadingProgressPattern::FireBuilder

| 分支 | 条件 | 测试方法 |
|------|------|----------|
| Builder存在 | makeFunc_ 有值 | FireBuilder_WithBuilder |
| Builder不存在 | makeFunc_ 无值 | FireBuilder_WithoutBuilder |
| 节点已存在 | contentModifierNode_ != nullptr | FireBuilder_NodeExists |

---

## 附录

### A. 源码位置索引

| 文件 | 路径 | 说明 |
|------|------|------|
| Pattern | `components_ng/pattern/loading_progress/loading_progress_pattern.h/cpp` | Pattern层核心 |
| Model | `components_ng/pattern/loading_progress/loading_progress_model_ng.h/cpp` | Model层实现 |
| LayoutAlgorithm | `components_ng/pattern/loading_progress/loading_progress_layout_algorithm.h/cpp` | 布局算法 |
| PaintMethod | `components_ng/pattern/loading_progress/loading_progress_paint_method.h` | 绘制方法 |
| Modifier | `components_ng/pattern/loading_progress/loading_progress_modifier.h/cpp` | 绘制修饰器 |
| LayoutProperty | `components_ng/pattern/loading_progress/loading_progress_layout_property.h` | 布局属性 |
| PaintProperty | `components_ng/pattern/loading_progress/loading_progress_paint_property.h` | 绘制属性 |
| Owner | `components_ng/pattern/loading_progress/loading_progress_owner.h` | Owner定义 |
| MultiThread | `components_ng/pattern/loading_progress/loading_progress_pattern_multi_thread.cpp` | 多线程支持 |

### B. 相关文档

- [CLAUDE.md](../../../../CLAUDE.md) - 项目级指导文档
- [如何新增一个组件.md](../../../../如何新增一个组件.md) - 组件开发指南
- [组件化重构通用方案.md](../../../../组件化重构通用方案.md) - 组件重构方案

### C. 关键常量

| 常量 | 值 | 说明 |
|------|------|------|
| DEFAULT_SIZE | 100.0f | 默认尺寸 (vp) |
| DEFAULT_ANIMATION_DURATION | 2000ms | 默认动画周期 |
| MIN_VISIBLE_RATIO | 1.0 | 最小可见比率 (完全可见) |

### D. 主题系统

LoadingProgress 使用 `LoadingProgressTheme` 获取默认样式:

```cpp
auto theme = pipelineContext->GetTheme<LoadingProgressTheme>();
Color defaultColor = theme->GetLoadingColor();
Color focusColor = theme->GetFocusColor();
```

**主题属性**:
- `loadingColor`: 默认加载颜色
- `focusColor`: 焦点颜色

### E. 性能优化建议

1. **使用可见性管理**: 自动启停动画,节省资源
2. **避免频繁创建/销毁**: 复用LoadingProgress组件
3. **合理设置尺寸**: 避免过大的尺寸影响性能
4. **多线程支持**: 复杂动画场景启用多线程
5. **自定义内容**: 简单场景使用自定义内容替代动画

---

**文档结束**

> **维护说明**: 本文档应随代码更新同步更新,特别是源码位置和 API 变更时。
