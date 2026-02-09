# Progress 组件知识库

> **文档版本**: v1.0
> **更新时间**: 2026-02-02
> **源代码版本**: OpenHarmony ace_engine (master 分支)
> **组件标签**: `PROGRESS_ETS_TAG`

---

## 目录

1. [组件概述](#组件概述)
2. [目录结构](#目录结构)
3. [核心类层次](#核心类层次)
4. [Pattern 层](#pattern-层)
5. [Model 层](#model-层)
6. [布局算法](#布局算法)
7. [绘制方法](#绘制方法)
8. [属性系统](#属性系统)
9. [主题系统](#主题系统)
10. [桥接层](#桥接层)
11. [执行流程](#执行流程)
12. [完整 API 列表](#完整-api-列表)
13. [关键实现细节](#关键实现细节)
14. [使用示例](#使用示例)

---

## 组件概述

### 组件定位

**Progress 组件**是 OpenHarmony ArkUI 框架中的进度条组件，用于显示正在进行的操作的进度。它提供：
- 多种进度类型：线性、环形、刻度环形、胶囊形、月牙形
- 渐变色支持
- 扫光特效动画
- 进度状态显示（进行中/加载中）
- 可自定义文本显示
- 环形类型的阴影效果
- 焦点/悬停/按下状态处理

### 子组件

Progress 组件不支持子组件。

### API 版本支持

- **初始版本**: API 7
- **Widget 能力**: API 9 开始支持
- **原子化服务 API**: API 11 开始支持

### 技术栈

- **前端**: ArkTS/JavaScript
- **桥接层**: ProgressModelNG + ProgressModifier
- **核心层**: NG Pattern 架构
- **渲染层**: Rosen + Skia

### 代码规模

- 总文件数: ~18 个文件
- 核心代码: ~6,000+ 行 C++ 代码
- 4 个架构层次

### 设计模式

Progress 组件采用 **NG Pattern 架构** + **桥接模式**：

```
前端 (ArkTS)
    ↓ (桥接层)
ProgressModelNG (progress_model_ng.cpp)
    ↓ (NG Pattern 层)
ProgressPattern (progress_pattern.cpp)
    ↓ (NG LayoutAlgorithm 层)
ProgressLayoutAlgorithm (progress_layout_algorithm.cpp)
    ↓
ProgressModifier (progress_modifier.cpp) → 渲染显示
```

---

## 目录结构

```
frameworks/core/components_ng/pattern/progress/
├── progress_pattern.h/cpp                    # 主 Pattern 逻辑
├── progress_model.h                           # Model 接口定义
├── progress_model_ng.h/cpp                    # NG Model 实现
├── progress_model_static.h/cpp                # ArkTS 静态 Model
├── progress_layout_property.h                 # 布局属性
├── progress_paint_property.h/cpp              # 绘制属性
├── progress_layout_algorithm.h/cpp            # 布局计算
├── progress_paint_method.h/cpp                # 绘制方法
├── progress_modifier.h/cpp                    # 绘制修改器
├── progress_date.h                            # 数据结构和枚举
├── progress_theme_wrapper.h                   # 主题定义
├── progress_accessibility_property.h/cpp      # 无障碍支持
└── progress_pattern_multi_thread.cpp          # 多线程支持
```

---

## 核心类层次

```
Pattern (基类)
    ↓
ProgressPattern
    ├── 创建: ProgressPaintProperty
    ├── 创建: ProgressLayoutProperty
    ├── 创建: ProgressLayoutAlgorithm
    ├── 创建: ProgressAccessibilityProperty
    └── 创建: ProgressModifier → ProgressPaintMethod

ProgressModel (抽象接口)
    ↓
ProgressModelNG (实现)
    └── FrameNode 操作的静态方法

ProgressLayoutAlgorithm
    ↓
BoxLayoutAlgorithm (基类)

ProgressModifier
    ↓
ContentModifier (基类)

ProgressPaintMethod
    ↓
NodePaintMethod (基类)
```

---

## Pattern 层

### ProgressPattern 类

**位置**: [progress_pattern.h](frameworks/core/components_ng/pattern/progress/progress_pattern.h)

**类定义**:
```cpp
class ProgressPattern : public Pattern {
public:
    // 工厂方法
    RefPtr<NodePaintMethod> CreateNodePaintMethod() override;
    RefPtr<PaintProperty> CreatePaintProperty() override;
    RefPtr<LayoutProperty> CreateLayoutProperty() override;
    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override;
    RefPtr<AccessibilityProperty> CreateAccessibilityProperty() override;

    // 生命周期方法
    void OnModifyDone() override;
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;
    void OnAttachToFrameNode() override;
    void OnDetachFromFrameNode(FrameNode* frameNode) override;
    void OnDetachFromMainTree() override;
    void OnVisibleChange(bool isVisible) override;
    void OnColorModeChange(uint32_t colorMode) override;
    void OnColorConfigurationUpdate() override;
    void OnSensitiveStyleChange(bool isSensitive) override;
    void OnThemeScopeUpdate(int32_t themeScopeId) override;

    // 内容修改器的构建器函数
    void SetBuilderFunc(ProgressMakeCallback&& makeFunc);
    void SetBuilderFuncMultiThread();
    bool UseContentModifier() const;
    RefPtr<FrameNode> GetContentModifierNode();

    // 焦点和事件处理
    void InitFocusEvent();
    void InitTouchEvent();
    void InitHoverEvent();
    void SetFocusStyle();
    void ClearFocusStyle();

    // 无障碍
    void OnAccessibilityEvent();
    FocusPattern GetFocusPattern() const override;

private:
    // 颜色和渐变更新
    void UpdateGradientColor(const NG::Gradient& gradient, bool isFirstLoad);
    void UpdateColor(const Color& color, bool isFirstLoad);

    // 文本处理
    void SetTextColor(const Color& color);
    void ObscureText(bool isSensitive);

    // 状态管理
    void HandleEnabled();
    void HandleFocusEvent();
    void HandleBlurEvent();
    void OnPress(const TouchEventInfo& info);
    void OnHover(bool isHover);

    // 构建器
    void FireBuilder();
    RefPtr<FrameNode> BuildContentModifierNode();

    // 成员变量
    RefPtr<ProgressModifier> progressModifier_;
    RefPtr<TouchEventImpl> touchListener_;
    RefPtr<InputEvent> hoverEvent_;
    std::function<void(bool)> isFocusActiveUpdateEvent_;
    float strokeWidth_ = Dimension(4.0_vp).ConvertToPx();
    ProgressType progressType_ = ProgressType::LINEAR;
    bool isTextFromUser_ = false;
    bool visibilityProp_ = true;
    bool isRightToLeft_ = false;
    bool isUserInitiatedColor_ = false;
    bool isUserInitiatedBgColor_ = false;
    Color defaultTextColor_;
    Color focusedTextColor_;
    std::optional<Color> backgroundColorOptional_;
    std::optional<Color> selectColorOptional_;
    std::optional<Color> borderColorOptional_;
    double value_ = 0.0;
    bool initFlag_ = false;
    RefPtr<FrameNode> contentModifierNode_;
    std::optional<ProgressMakeCallback> makeFunc_;
};
```

### 主要职责

1. **属性更新**:
   - 颜色和渐变色更新
   - 描边宽度和边框更新
   - 值和最大值更新
   - 文本颜色和样式更新
   - 进度状态更新

2. **事件处理**:
   - 触摸事件（按下处理）
   - 焦点事件（获得/失去焦点）
   - 悬停事件（鼠标悬停）
   - 可见性变化事件

3. **状态管理**:
   - 启用/禁用状态
   - 带自定义样式的焦点状态
   - 隐私/敏感样式支持

4. **内容修改器**:
   - 自定义 UI 的构建器函数
   - 多线程构建器支持

5. **无障碍**:
   - 无障碍事件通知
   - 焦点模式配置

---

## Model 层

### ProgressModel (抽象接口)

**位置**: [progress_model.h](frameworks/core/components_ng/pattern/progress/progress_model.h)

```cpp
class ACE_FORCE_EXPORT ProgressModel {
public:
    static ProgressModel* GetInstance();

    // 核心配置
    virtual void Create(double min, double value, double cachedValue, double max, NG::ProgressType type) = 0;
    virtual void SetValue(double value) = 0;

    // 颜色
    virtual void SetColor(const Color& value) = 0;
    virtual void ResetColor() = 0;
    virtual void SetBackgroundColor(const Color& value) = 0;
    virtual void SetBackgroundColorByUser(bool value) = 0;
    virtual void ResetBackgroundColor() = 0;
    virtual void SetGradientColor(const NG::Gradient& value) = 0;
    virtual void ResetGradientColor() = 0;

    // 尺寸
    virtual void SetStrokeWidth(const Dimension& value) = 0;
    virtual void SetScaleCount(int32_t value) = 0;
    virtual void SetScaleWidth(const Dimension& value) = 0;
    virtual void SetBorderWidth(const Dimension& value) = 0;

    // 边框
    virtual void SetBorderColor(const Color& value) = 0;
    virtual void ResetBorderColor() = 0;

    // 文本
    virtual void SetFontSize(const Dimension& value) = 0;
    virtual void SetFontColor(const Color& value) = 0;
    virtual void ResetFontColor() = 0;
    virtual void SetText(const std::optional<std::string>& value) = 0;
    virtual void SetItalicFontStyle(const Ace::FontStyle& value) = 0;
    virtual void SetFontWeight(const FontWeight& value) = 0;
    virtual void SetFontFamily(const std::vector<std::string>& value) = 0;

    // 特效
    virtual void SetSweepingEffect(bool value) = 0;
    virtual void SetRingSweepingEffect(bool value) = 0;
    virtual void SetLinearSweepingEffect(bool value) = 0;
    virtual void SetSmoothEffect(bool value) = 0;
    virtual void SetPaintShadow(bool value) = 0;

    // 状态
    virtual void SetProgressStatus(NG::ProgressStatus value) = 0;
    virtual void SetShowText(bool value) = 0;

    // 描边半径（某些类型）
    virtual void SetStrokeRadius(const Dimension& value) = 0;
    virtual void ResetStrokeRadius() = 0;

    // 边框圆角（Capsule 类型）
    virtual void SetBorderRadius(const Dimension& value) = 0;
    virtual void ResetBorderRadius() = 0;

    // 资源支持
    virtual void CreateWithResourceObj(JsProgressResourceType jsResourceType,
        const RefPtr<ResourceObject>& resObj) = 0;
    virtual void SetGradientColorResObj(const NG::Gradient& value) = 0;

    // Capsule 特有
    virtual void SetCapsuleStyleFontColor(bool value) = 0;
    virtual void SetCapsuleStyle(bool value) = 0;
    virtual void SetGradientColorByUser(bool value) = 0;
};
```

### ProgressModelNG (实现)

**位置**: [progress_model_ng.h](frameworks/core/components_ng/pattern/progress/progress_model_ng.h)

**主要静态方法**:
- `CreateFrameNode(int32_t nodeId, double value, double max, NG::ProgressType type)`
- `SetValue(FrameNode* frameNode, double value)`
- `SetColor/ResetColor(FrameNode* frameNode, ...)`
- `SetGradientColor/ResetGradientColor(FrameNode* frameNode, ...)`
- `SetStrokeWidth(FrameNode* frameNode, const Dimension& value)`
- `SetProgressStatus(FrameNode* frameNode, ProgressStatus status)`
- `SetBuilderFunc(FrameNode* frameNode, ProgressMakeCallback&& jsMake)`

---

## 布局算法

### ProgressLayoutAlgorithm

**位置**: [progress_layout_algorithm.h](frameworks/core/components_ng/pattern/progress/progress_layout_algorithm.h)

**主要方法**:

```cpp
class ProgressLayoutAlgorithm : public BoxLayoutAlgorithm {
public:
    ProgressLayoutAlgorithm();
    ~ProgressLayoutAlgorithm() override = default;

    std::optional<SizeF> MeasureContent(
        const LayoutConstraintF& contentConstraint,
        LayoutWrapper* layoutWrapper) override;

    ProgressType GetType() const;
    float GetStrokeWidth() const;
    float GetChildHeight(LayoutWrapper* layoutWrapper, float width) const;

private:
    std::optional<SizeF> MeasureContentForApiNine(
        const LayoutConstraintF& contentConstraint,
        LayoutWrapper* layoutWrapper);

    ProgressType type_ = ProgressType::LINEAR;
    float strokeWidth_ = 2.0f;
};
```

**布局计算详情**:
- API 9+ 与早期版本的不同尺寸计算
- 文本覆盖的子高度计算
- 描边宽度影响内容尺寸

---

## 绘制方法

### ProgressPaintMethod

**位置**: [progress_paint_method.h](frameworks/core/components_ng/pattern/progress/progress_paint_method.h)

```cpp
class ACE_EXPORT ProgressPaintMethod : public NodePaintMethod {
public:
    explicit ProgressPaintMethod(ProgressType progressType, float strokeWidth,
        const RefPtr<ProgressModifier>& progressModifier, bool isUserInitiatedColor);

    RefPtr<Modifier> GetContentModifier(PaintWrapper* paintWrapper) override;
    void UpdateContentModifier(PaintWrapper* paintWrapper) override;
    void GetThemeData(int32_t themeScopeId);
    void CalculateStrokeWidth(const SizeF& contentSize);

private:
    Gradient GenerateRingProgressColor(PaintWrapper* paintWrapper);
    void SetCapsuleBorderRadius(PaintWrapper* paintWrapper);
    void UpdateCapsuleProgress(PaintWrapper* paintWrapper);

    ProgressType progressType_ = ProgressType::LINEAR;
    RefPtr<ProgressModifier> progressModifier_;
    bool sweepEffect_ = false;
    bool ringSweepEffect_ = false;
    bool linearSweepEffect_ = false;
    bool isItalic_ = false;
    bool isUserInitiatedColor_ = false;

    // 颜色属性
    Color color_ = Color::BLUE;
    Color bgColor_ = Color::GRAY;
    Color borderColor_ = Color::GRAY;

    // 尺寸属性
    float strokeWidth_ = 0.0f;
    float scaleWidth_ = 0.0f;
    int32_t scaleCount_ = 0;
    float maxValue_ = 100.0f;
    float value_ = 0.0f;
    Dimension capsuleBorderWidth_ = Dimension(DEFAULT_BORDER_WIDTH, DimensionUnit::VP);
};
```

---

## 属性系统

### ProgressType 枚举

**位置**: [progress_date.h](frameworks/core/components_ng/pattern/progress/progress_date.h:28-38)

```cpp
enum class ProgressType {
    LINEAR = 1,      // 线性水平进度条
    RING = 2,        // 环形进度条
    SCALE = 3,       // 刻度环形进度条
    CIRCLE = 4,      // 圆形进度条
    GAUGE = 5,       // 仪表盘进度条（已弃用，使用 Gauge 组件）
    ARC = 6,         // 弧形进度条
    MOON = 7,        // 月牙形进度条
    BUBBLE = 8,      // 气泡进度条
    CAPSULE = 9,     // 胶囊进度条
};
```

### ProgressStatus 枚举

**位置**: [progress_date.h](frameworks/core/components_ng/pattern/progress/progress_date.h:40-43)

```cpp
enum class ProgressStatus {
    PROGRESSING = 0,  // 正常进度状态
    LOADING           // 加载动画状态
};
```

### ProgressPaintProperty

**位置**: [progress_paint_property.h](frameworks/core/components_ng/pattern/progress/progress_paint_property.h)

**属性定义**:

```cpp
// ProgressDate 组（主要数据属性）
ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(ProgressPaintDate, MaxValue, double, PROPERTY_UPDATE_MEASURE);
ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(ProgressPaintDate, Value, double, PROPERTY_UPDATE_MEASURE);
ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(ProgressPaintDate, ScaleCount, int32_t, PROPERTY_UPDATE_MEASURE);
ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(ProgressPaintDate, ScaleWidth, Dimension, PROPERTY_UPDATE_MEASURE);
ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(ProgressPaintDate, BorderWidth, Dimension, PROPERTY_UPDATE_MEASURE);
ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(ProgressPaintDate, TextSize, Dimension, PROPERTY_UPDATE_MEASURE);
ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(ProgressPaintDate, Text, std::string, PROPERTY_UPDATE_MEASURE);
ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(ProgressPaintDate, EnableScanEffect, bool, PROPERTY_UPDATE_MEASURE);
ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(ProgressPaintDate, FontWeight, FontWeight, PROPERTY_UPDATE_MEASURE);
ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(ProgressPaintDate, FontFamily, std::vector<std::string>, PROPERTY_UPDATE_MEASURE);
ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(ProgressPaintDate, ItalicFontStyle, Ace::FontStyle, PROPERTY_UPDATE_MEASURE);
ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(ProgressPaintDate, TextColor, Color, PROPERTY_UPDATE_MEASURE);
ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(ProgressPaintDate, EnableRingScanEffect, bool, PROPERTY_UPDATE_MEASURE);
ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(ProgressPaintDate, EnableLinearScanEffect, bool, PROPERTY_UPDATE_MEASURE);
ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(ProgressPaintDate, EnableShowText, bool, PROPERTY_UPDATE_MEASURE);
ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(ProgressPaintDate, StrokeRadius, Dimension, PROPERTY_UPDATE_RENDER);
ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(ProgressPaintDate, BorderRadius, Dimension, PROPERTY_UPDATE_MEASURE);

// 独立属性
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Color, Color, PROPERTY_UPDATE_MEASURE);
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(BackgroundColor, Color, PROPERTY_UPDATE_MEASURE);
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ProgressType, ProgressType, PROPERTY_UPDATE_MEASURE);
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(BorderColor, Color, PROPERTY_UPDATE_MEASURE);
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(GradientColor, Gradient, PROPERTY_UPDATE_MEASURE);
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(PaintShadow, bool, PROPERTY_UPDATE_MEASURE);
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ProgressStatus, ProgressStatus, PROPERTY_UPDATE_MEASURE);
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(EnableSmoothEffect, bool, PROPERTY_UPDATE_MEASURE);
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IsSensitive, bool, PROPERTY_UPDATE_MEASURE);
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(BackgroundColorSetByUser, bool, PROPERTY_UPDATE_MEASURE);
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(GradientColorSetByUser, bool, PROPERTY_UPDATE_MEASURE);
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(CapsuleStyleSetByUser, bool, PROPERTY_UPDATE_RENDER);
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(CapsuleStyleFontColorSetByUser, bool, PROPERTY_UPDATE_RENDER);
```

### ProgressLayoutProperty

**位置**: [progress_layout_property.h](frameworks/core/components_ng/pattern/progress/progress_layout_property.h)

```cpp
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Type, ProgressType, PROPERTY_UPDATE_MEASURE);
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(StrokeWidth, Dimension, PROPERTY_UPDATE_MEASURE);
```

---

## 主题系统

### ProgressThemeWrapper

**位置**: [progress_theme_wrapper.h](frameworks/core/components_ng/pattern/progress/progress_theme_wrapper.h)

**主题颜色**:

```cpp
class ProgressThemeWrapper : public ProgressTheme, public TokenThemeWrapper {
public:
    void ApplyTokenTheme(const TokenTheme& theme) override
    {
        if (auto themeColors = theme.Colors(); themeColors) {
            // 图标/加载颜色
            loadingColor_ = themeColors->IconSecondary();

            // 背景颜色
            capsuleBgColor_ = themeColors->CompBackgroundTertiary();
            ringProgressBackgroundColor_ = themeColors->CompBackgroundTertiary();
            trackBgColor_ = themeColors->CompBackgroundTertiary();

            // 选中/进度颜色
            capsuleSelectColor_ = themeColors->CompEmphasizeSecondary();
            trackSelectedColor_ = themeColors->BackgroundEmphasize();
            borderColor_ = themeColors->CompEmphasizeSecondary();
        }
    }
};
```

---

## 桥接层

### ProgressModifier (绘制)

**位置**: [progress_modifier.h](frameworks/core/components_ng/pattern/progress/progress_modifier.h)

**主要绘制方法**:

```cpp
class ProgressModifier : public ContentModifier {
public:
    void onDraw(DrawingContext& context) override;

    // 属性设置器
    void SetStrokeWidth(float width);
    void SetColor(LinearColor color);
    void SetBackgroundColor(LinearColor color);
    void SetBorderColor(LinearColor color);
    void SetProgressType(ProgressType type);
    void SetMaxValue(float value);
    void SetValue(float value);
    void SetScaleWidth(float value);
    void SetScaleCount(int32_t value);
    void SetContentOffset(const OffsetF& offset);
    void SetContentSize(const SizeF& contentSize);
    void SetBorderWidth(float width);
    void SetSweepEffect(bool value);
    void SetRingProgressColor(const Gradient& color);
    void SetPaintShadow(bool paintShadow);
    void SetProgressStatus(ProgressStatus status);
    void SetVisible(bool isVisible);
    void SetRingSweepEffect(bool value);
    void SetLinearSweepEffect(bool value);
    void SetIsItalic(bool isItalic);
    void SetSmoothEffect(bool value);
    void SetStrokeRadius(float strokeRaidus);
    void SetUseContentModifier(bool useContentModifier);
    void SetIsRightToLeft(bool value);
    void SetCapsuleBorderRadius(float borderRadius);
    void SetIsHovered(bool value);
    void SetIsPressed(bool value);
    void SetIsFocused(bool value);
    void SetInVisibleArea(bool value);
    void UpdateProgress();
    void StopAllLoopAnimation();

private:
    // 按类型绘制的私有方法
    void PaintLinear(RSCanvas& canvas, const OffsetF& offset, const SizeF& contentSize) const;
    void PaintLinearWithGradient(RSCanvas& canvas, const OffsetF& offset, const SizeF& contentSize) const;
    void PaintLinearSweeping(RSCanvas& canvas, const OffsetF& offset, const RSPath& path,
        bool isHorizontal, const SizeF& contentSize) const;
    void PaintRing(RSCanvas& canvas, const OffsetF& offset, const SizeF& contentSize) const;
    void PaintRingBackground(RSCanvas& canvas, const RingProgressData& ringProgressData) const;
    void PaintRingProgressOrShadow(RSCanvas& canvas, const RingProgressData& ringProgressData,
        bool isShadow) const;
    void PaintRingSweeping(RSCanvas& canvas, const RingProgressData& ringProgressData) const;
    void PaintTrailing(RSCanvas& canvas, const RingProgressData& ringProgressData) const;
    void PaintScaleRing(RSCanvas& canvas, const OffsetF& offset, const SizeF& contentSize) const;
    void PaintMoon(RSCanvas& canvas, const OffsetF& offset, const SizeF& contentSize) const;
    void PaintCapsule(RSCanvas& canvas, const OffsetF& offset, const SizeF& contentSize,
        const float borderRadius) const;
    void PaintCapsuleWithGradient(RSCanvas& canvas, const OffsetF& offset, const SizeF& contentSize,
        const float borderRadius) const;
    void PaintVerticalCapsule(RSCanvas& canvas, const OffsetF& offset, const SizeF& contentSize,
        const float borderRadius) const;
    void PaintVerticalCapsuleWithGradient(RSCanvas& canvas, const OffsetF& offset,
        const SizeF& contentSize, const float borderRadius) const;
    void PaintCapsuleLightSweep(RSCanvas& canvas, const SizeF& contentSize, const OffsetF& offset,
        const RSPath& path, bool isVertical) const;

    // 动画方法
    void ProcessSweepingAnimation(ProgressType type, float value);
    void ProcessRingSweepingAnimation(float value);
    void ProcessLinearSweepingAnimation(float value);
    void StartRingSweepingAnimation(float value);
    void StartRingSweepingAnimationImpl(float date, float speed);
    void StartContinuousSweepingAnimation(float currentDate, float newDate, float speed);
    void StartLinearSweepingAnimation(float value);
    void StartLinearSweepingAnimationImpl(float date, float speed);
    void StartCapsuleSweepingAnimation(float value);
    void StartCapsuleSweepingAnimationImpl(float value, float speed);
    void StopSweepingAnimation(float date = 0.0f);
    void StartRingLoadingAnimation();
    void StartRingLoadingHeadAnimation();
    void StartRingLoadingTailAnimation();
    void StopRingLoadingHeadAnimation();
    void StopRingLoadingTailAnimation();

    // 辅助方法
    float CalcRingProgressAdditionalAngle() const;
    std::vector<GradientColor> GetRingProgressGradientColors() const;
    void GenerateLinearSweepingGradientInfo(std::vector<RSColorQuad>& colors,
        std::vector<float>& pos) const;
    void GenerateRingSweepingGradientInfo(std::vector<RSColorQuad>& colors,
        std::vector<float>& pos) const;
    Gradient CreateCapsuleGradient() const;
    Gradient SortGradientColorsByOffset(const Gradient& gradient) const;
    bool IsSweepEffectOn();
    Color CalculateHoverPressColor(const Color& color);
};
```

---

## 执行流程

### 创建流程

```
ArkTS: Progress({ value: 50, total: 100, type: ProgressType.Linear })
    ↓
ProgressModelNG::Create(min=0, value=50, cachedValue=0, max=100, type=LINEAR)
    ↓
FrameNode::GetOrCreateFrameNode(PROGRESS_ETS_TAG, nodeId, ProgressPattern)
    ↓
创建 PaintProperty (Value=50, Max=100)
创建 LayoutProperty (Type=LINEAR)
创建 ProgressPattern
    ↓
OnModifyDone() → InitFocusEvent(), InitTouchEvent(), InitHoverEvent()
    ↓
Measure (ProgressLayoutAlgorithm)
    ↓
Layout (位置计算)
    ↓
Paint (ProgressModifier::onDraw)
```

### 值更新流程

```
ArkTS: progress.value(75)
    ↓
ProgressModelNG::SetValue(75)
    ↓
ACE_UPDATE_PAINT_PROPERTY(ProgressPaintProperty, Value, 75)
    ↓
标记 PROPERTY_UPDATE_MEASURE (布局脏标记)
    ↓
OnModifyDone() → 测量/布局阶段
    ↓
ProgressModifier::SetValue(75) (通过 ProgressPaintMethod)
    ↓
使用新值重新渲染
```

**注意**: 由于 `Value` 在 `progress_paint_property.h:74` 中定义为 `PROPERTY_UPDATE_MEASURE`，值变化会触发布局传递后再渲染。

### 颜色更新流程

```
ArkTS: progress.color(Color.Red)
    ↓
ProgressModelNG::SetColor(Color.Red)
    ↓
ACE_UPDATE_PAINT_PROPERTY(ProgressPaintProperty, Color, Color.Red)
    ↓
标记 PROPERTY_UPDATE_MEASURE (布局脏标记)
    ↓
OnModifyDone() → 测量/布局阶段
    ↓
ProgressModifier::SetColor(LinearColor(Color.Red)) (通过 ProgressPaintMethod)
    ↓
使用新颜色重新渲染
```

**注意**: 由于 `Color` 在 `progress_paint_property.h:91` 中定义为 `PROPERTY_UPDATE_MEASURE`，颜色变化会触发布局传递后再渲染，而不是直接渲染。

---

## 完整 API 列表

### 创建 API

| API | 描述 | 位置 |
|-----|------|------|
| `Create(double min, double value, double cachedValue, double max, ProgressType type)` | 使用初始值创建进度条 | progress_model_ng.cpp:27 |
| `CreateFrameNode(int32_t nodeId, double value, double max, ProgressType type)` | 静态创建方法 | progress_model_ng.cpp:84 |

### 值 API

| API | 描述 | 位置 |
|-----|------|------|
| `SetValue(double value)` | 设置当前值 | progress_model_ng.cpp:27 |
| `SetValue(FrameNode*, double value)` | 静态设置器 | progress_model_ng.cpp:85 |
| `SetTotal(FrameNode*, double max)` | 设置最大值 | progress_model_ng.cpp:109 |
| `SetType(FrameNode*, ProgressType type)` | 设置进度类型 | progress_model_ng.cpp:110 |

### 颜色 API

| API | 描述 | 位置 |
|-----|------|------|
| `SetColor(const Color& value)` | 设置进度颜色 | progress_model_ng.cpp:28 |
| `SetColor(FrameNode*, const Color& value)` | 静态设置器 | progress_model_ng.cpp:86 |
| `ResetColor()` | 重置为默认颜色 | progress_model_ng.cpp:29 |
| `SetBackgroundColor(const Color& value)` | 设置背景颜色 | progress_model_ng.cpp:30 |
| `SetBackgroundColor(FrameNode*, const Color& value)` | 静态设置器 | progress_model_ng.cpp:108 |
| `ResetBackgroundColor()` | 重置背景颜色 | progress_model_ng.cpp:32 |
| `SetGradientColor(const Gradient& value)` | 设置渐变颜色 | progress_model_ng.cpp:47 |
| `SetGradientColor(FrameNode*, const Gradient& value)` | 静态设置器 | progress_model_ng.cpp:87 |
| `ResetGradientColor()` | 重置渐变颜色 | progress_model_ng.cpp:48 |

### 尺寸 API

| API | 描述 | 位置 |
|-----|------|------|
| `SetStrokeWidth(const Dimension& value)` | 设置描边/厚度宽度 | progress_model_ng.cpp:33 |
| `SetStrokeWidth(FrameNode*, const Dimension& value)` | 静态设置器 | progress_model_ng.cpp:89 |
| `SetScaleCount(int32_t value)` | 设置刻度数量 (ScaleRing 类型) | progress_model_ng.cpp:34 |
| `SetScaleCount(FrameNode*, int32_t value)` | 静态设置器 | progress_model_ng.cpp:94 |
| `SetScaleWidth(const Dimension& value)` | 设置刻度宽度 | progress_model_ng.cpp:35 |
| `SetScaleWidth(FrameNode*, const Dimension& value)` | 静态设置器 | progress_model_ng.cpp:95 |

### 边框 API

| API | 描述 | 位置 |
|-----|------|------|
| `SetBorderColor(const Color& value)` | 设置边框颜色 | progress_model_ng.cpp:36 |
| `SetBorderColor(FrameNode*, const Color& value)` | 静态设置器 | progress_model_ng.cpp:97 |
| `ResetBorderColor()` | 重置边框颜色 | progress_model_ng.cpp:37 |
| `SetBorderWidth(const Dimension& value)` | 设置边框宽度 | progress_model_ng.cpp:38 |
| `SetBorderWidth(FrameNode*, const Dimension& value)` | 静态设置器 | progress_model_ng.cpp:96 |
| `SetStrokeRadius(const Dimension& value)` | 设置描边半径 | progress_model_ng.cpp:55 |
| `SetStrokeRadius(FrameNode*, const Dimension& value)` | 静态设置器 | progress_model_ng.cpp:106 |
| `ResetStrokeRadius(FrameNode*)` | 重置描边半径 | progress_model_ng.cpp:107 |
| `SetBorderRadius(const Dimension& value)` | 设置边框圆角 | progress_model_ng.cpp:57 |
| `SetBorderRadius(FrameNode*, const Dimension& value)` | 静态设置器 | progress_model_ng.cpp:118 |
| `ResetBorderRadius(FrameNode*)` | 重置边框圆角 | progress_model_ng.cpp:119 |

### 文本 API

| API | 描述 | 位置 |
|-----|------|------|
| `SetFontSize(const Dimension& value)` | 设置文本字体大小 | progress_model_ng.cpp:39 |
| `SetFontSize(FrameNode*, const Dimension& value)` | 静态设置器 | progress_model_ng.cpp:102 |
| `SetFontColor(const Color& value)` | 设置文本字体颜色 | progress_model_ng.cpp:40 |
| `SetFontColor(FrameNode*, const Color& value)` | 静态设置器 | progress_model_ng.cpp:101 |
| `ResetFontColor()` | 重置字体颜色 | progress_model_ng.cpp:41 |
| `SetText(const std::optional<std::string>& value)` | 设置自定义文本 | progress_model_ng.cpp:42 |
| `SetText(FrameNode*, const std::optional<std::string>& value)` | 静态设置器 | progress_model_ng.cpp:100 |
| `SetItalicFontStyle(const Ace::FontStyle& value)` | 设置斜体字体样式 | progress_model_ng.cpp:43 |
| `SetItalicFontStyle(FrameNode*, const Ace::FontStyle& value)` | 静态设置器 | progress_model_ng.cpp:105 |
| `SetFontWeight(const FontWeight& value)` | 设置字体粗细 | progress_model_ng.cpp:44 |
| `SetFontWeight(FrameNode*, const FontWeight& value)` | 静态设置器 | progress_model_ng.cpp:103 |
| `SetFontFamily(const std::vector<std::string>& value)` | 设置字体族 | progress_model_ng.cpp:45 |
| `SetFontFamily(FrameNode*, const std::vector<std::string>& value)` | 静态设置器 | progress_model_ng.cpp:104 |
| `SetShowText(bool value)` | 显示/隐藏文本 | progress_model_ng.cpp:50 |

### 特效 API

| API | 描述 | 位置 |
|-----|------|------|
| `SetSweepingEffect(bool value)` | 设置扫光特效 | progress_model_ng.cpp:46 |
| `SetSweepingEffect(FrameNode*, bool value)` | 静态设置器 | progress_model_ng.cpp:98 |
| `SetRingSweepingEffect(bool value)` | 设置环形扫光特效 | progress_model_ng.cpp:52 |
| `SetRingSweepingEffect(FrameNode*, bool value)` | 静态设置器 | progress_model_ng.cpp:91 |
| `SetLinearSweepingEffect(bool value)` | 设置线性扫光特效 | progress_model_ng.cpp:53 |
| `SetLinearSweepingEffect(FrameNode*, bool value)` | 静态设置器 | progress_model_ng.cpp:90 |
| `SetSmoothEffect(bool value)` | 设置平滑特效 | progress_model_ng.cpp:54 |
| `SetSmoothEffect(FrameNode*, bool value)` | 静态设置器 | progress_model_ng.cpp:88 |
| `SetPaintShadow(bool value)` | 设置阴影特效 | progress_model_ng.cpp:49 |
| `SetPaintShadow(FrameNode*, bool value)` | 静态设置器 | progress_model_ng.cpp:92 |

### 状态 API

| API | 描述 | 位置 |
|-----|------|------|
| `SetProgressStatus(ProgressStatus status)` | 设置进度状态 | progress_model_ng.cpp:50 |
| `SetProgressStatus(FrameNode*, ProgressStatus status)` | 静态设置器 | progress_model_ng.cpp:93 |

### 内容修改器 API

| API | 描述 | 位置 |
|-----|------|------|
| `SetBuilderFunc(FrameNode*, ProgressMakeCallback)` | 设置自定义 UI 构建器 | progress_model_ng.cpp:115 |

---

## 关键实现细节

### 1. 进度类型处理

组件通过 `ProgressType` 枚举支持多种进度类型：

1. **LINEAR**: 水平线性进度条
2. **RING**: 圆环进度条
3. **SCALE**: 带刻度标记的圆环
4. **CAPSULE**: 胶囊形进度条
5. **MOON**: 月牙形进度条

**实现位置**: [progress_modifier.cpp](frameworks/core/components_ng/pattern/progress/progress_modifier.cpp) 中的 `ProgressModifier::onDraw()`

### 2. 扫光特效动画

扫光特效创建一个穿过进度条的光扫动画：

```cpp
// 环形扫光动画
void StartRingSweepingAnimation(float value) {
    float currentDate = sweepingDateBackup_;
    float newDate = value * 360.0f / maxValue_;
    float speed = newDate > currentDate ? 6.0f : 12.0f;
    StartContinuousSweepingAnimation(currentDate, newDate, speed);
}

// 线性/胶囊扫光动画
void StartLinearSweepingAnimation(float value) {
    float date = valueBackup_;
    float targetValue = value;
    float speed = 1.0f;
    StartLinearSweepingAnimationImpl(date, targetValue, speed);
}
```

### 3. 内容修改器支持

可以通过 `ProgressMakeCallback` 提供自定义 UI：

```cpp
using ProgressMakeCallback =
    std::function<RefPtr<FrameNode>(const ProgressConfiguration& config)>;

struct ProgressConfiguration : public CommonConfiguration {
    float value_;
    float total_;
};
```

### 4. 焦点状态处理

组件支持带自定义样式的焦点状态：

```cpp
void SetFocusStyle() {
    // 应用焦点文本颜色
    SetTextColor(focusedTextColor_);
    // 应用胶囊缩放效果
    capsuleFocusScale_ = 1.05f;
    // 应用阴影效果
    focusShadowStyle_ = ShadowStyle::SPACE;
}

void ClearFocusStyle() {
    // 恢复默认文本颜色
    SetTextColor(defaultTextColor_);
    // 重置胶囊缩放
    capsuleFocusScale_ = 1.0f;
    // 清除阴影效果
    focusShadowStyle_ = ShadowStyle::None;
}
```

### 5. 隐私/敏感样式

启用隐私模式时：
- 文本通过 `ObscureText()` 遮挡
- 渲染时值设置为 0
- `isSensitive` 标志在 paint property 上设置

### 6. 渐变色支持

渐变色在渲染前按偏移量排序：

```cpp
Gradient SortGradientColorsByOffset(const Gradient& gradient) const {
    Gradient sortedGradient = gradient;
    auto& gradientColors = sortedGradient.GetGradientColors();
    std::sort(gradientColors.begin(), gradientColors.end(),
        [](const GradientColor& a, const GradientColor& b) {
            return a.GetDimension().ConvertToVp() < b.GetDimension().ConvertToVp();
        });
    return sortedGradient;
}
```

### 7. RTL 支持

从右到左布局支持：

```cpp
bool isRtl = progressLayoutProperty->GetNonAutoLayoutDirection() == TextDirection::RTL;
progressModifier_->SetIsRightToLeft(isRtl);
```

---

## 使用示例

### 基础线性进度条

```typescript
Progress({ value: 50, total: 100, type: ProgressType.Linear })
```

### 环形进度条

```typescript
Progress({ value: 50, total: 100, type: ProgressType.Ring })
  .width(100)
  .height(100)
  .color(Color.Blue)
  .backgroundColor(Color.Gray)
```

### 刻度环形进度条

```typescript
Progress({ value: 70, total: 100, type: ProgressType.ScaleRing })
  .width(100)
  .height(100)
  .scaleCount(20)
  .scaleWidth(5)
```

### 胶囊进度条

```typescript
Progress({ value: 60, total: 100, type: ProgressType.Capsule })
  .width(200)
  .height(40)
  .color(Color.Green)
  .backgroundColor('#E0E0E0')
```

### 月牙形进度条

```typescript
Progress({ value: 80, total: 100, type: ProgressType.Eclipse })
  .width(100)
  .height(100)
  .color(Color.Orange)
```

### 带渐变色的进度条

```typescript
Progress({ value: 50, total: 100, type: ProgressType.Linear })
  .color(new LinearGradient([
    { color: '#FF0000', offset: 0 },
    { color: '#00FF00', offset: 0.5 },
    { color: '#0000FF', offset: 1 }
  ]))
```

### 带自定义文本的进度条

```typescript
Progress({ value: 75, total: 100, type: ProgressType.Linear })
  .text('下载中: 75%')
  .fontSize(16)
  .fontColor(Color.Black)
```

### 带阴影效果的进度条

```typescript
Progress({ value: 50, total: 100, type: ProgressType.Ring })
  .width(100)
  .height(100)
  .color(Color.Blue)
  .shadow(true)
```

### 带扫光特效的进度条

```typescript
Progress({ value: 60, total: 100, type: ProgressType.Ring })
  .width(100)
  .height(100)
  .color(Color.Red)
  .sweepingEffect(true)
```

### 垂直胶囊进度条

```typescript
Progress({ value: 50, total: 100, type: ProgressType.Capsule })
  .width(40)
  .height(200)
  .color(Color.Purple)
```

### 自定义内容修改器 (API 12+)

```typescript
@Builder
function buildProgress(config: ProgressConfiguration) {
  Column({ space: 10 }) {
    Text('进度: ' + config.value + '/' + config.total)
      .fontSize(16)
      .fontColor(Color.Black)
    Progress({
      value: config.value,
      total: config.total,
      type: ProgressType.Linear
    })
      .width('100%')
  }
}

class MyProgressStyle implements ContentModifier<ProgressConfiguration> {
  value: number = 0
  total: number = 0

  constructor(value: number, total: number) {
    this.value = value
    this.total = total
  }

  applyContent(): WrappedBuilder<[ProgressConfiguration]> {
    return wrapBuilder(buildProgress)
  }
}

Progress({ value: 20, total: 100, type: ProgressType.Linear })
  .contentModifier(new MyProgressStyle(20, 100))
```

---

## 文件引用

| 文件 | 行数 | 描述 |
|------|------|------|
| [progress_pattern.h](frameworks/core/components_ng/pattern/progress/progress_pattern.h) | 267 | 主 Pattern 类定义 |
| [progress_pattern.cpp](frameworks/core/components_ng/pattern/progress/progress_pattern.cpp) | ~1100 | Pattern 实现 |
| [progress_model_ng.h](frameworks/core/components_ng/pattern/progress/progress_model_ng.h) | 160 | NG Model 接口 |
| [progress_model_ng.cpp](frameworks/core/components_ng/pattern/progress/progress_model_ng.cpp) | ~1600 | NG Model 实现 |
| [progress_layout_algorithm.cpp](frameworks/core/components_ng/pattern/progress/progress_layout_algorithm.cpp) | ~300 | 布局计算 |
| [progress_modifier.cpp](frameworks/core/components_ng/pattern/progress/progress_modifier.cpp) | ~2600 | 绘制逻辑 |
| [progress_paint_property.h](frameworks/core/components_ng/pattern/progress/progress_paint_property.h) | 111 | 绘制属性 |
| [progress_date.h](frameworks/core/components_ng/pattern/progress/progress_date.h) | 121 | 数据结构和枚举 |

---

*英文版参见: [frameworks/core/components_ng/pattern/progress/CLAUDE.md](frameworks/core/components_ng/pattern/progress/CLAUDE.md)*
