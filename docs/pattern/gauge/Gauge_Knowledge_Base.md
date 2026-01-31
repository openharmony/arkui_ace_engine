# ArkUI 仪表盘组件完整知识库

> **文档版本**：v1.0
> **更新时间**：2026-01-31
> **源码版本**：OpenHarmony ace_engine (master 分支)
> **组件标签**：`GAUGE_ETS_TAG`

---

## 目录

1. [概述](#概述)
2. [目录结构](#目录结构)
3. [核心类继承关系](#核心类继承关系)
4. [Pattern 层详解](#pattern-层详解)
5. [Model 层详解](#model-层详解)
6. [布局算法](#布局算法)
7. [绘制方法](#绘制方法)
8. [属性系统](#属性系统)
9. [主题系统](#主题系统)
10. [桥接层](#桥接层)
11. [执行流程](#执行流程)
12. [完整 API 清单](#完整-api-清单)
13. [关键实现细节](#关键实现细节)
14. [使用示例](#使用示例)

---

## 概述

### 组件定位

**仪表盘组件 (Gauge)** 是 OpenHarmony ArkUI 框架中的**数据量规图表组件**，用于将数据展示为环形图表。提供：
- 圆形仪表盘显示，可视化数值
- 三种类型：多段渐变、单段渐变、单色
- 自定义指示器支持（默认或自定义图标）
- 圆环阴影效果
- 最小值/最大值文本显示
- 自定义描述内容
- 子组件支持（单个子组件）

### 子组件

Gauge 组件可以包含**单个子组件**。

**说明**：
- 支持的子组件类型：系统组件和自定义组件
- 支持条件渲染控制 `if/else`，不支持循环渲染控制 `ForEach` 和 `LazyForEach`
- 建议使用文本组件构建当前数值文本和辅助文本
- 若子组件宽高为百分比形式，则基准范围为以外圆环做为内切圆的矩形

### API 版本支持

- **起始版本**：API version 8
- **卡片能力**：API version 9 开始支持
- **原子化服务 API**：API version 11 开始支持

### 技术栈

- **前端**：ArkTS/JavaScript
- **桥接层**：GaugeModelNG + GaugeModifier
- **核心层**：NG Pattern 架构
- **渲染层**：Rosen + Skia

### 代码规模

- 总文件数：约 26 个文件
- 核心代码：约 4,000+ 行 C++ 代码
- 涉及 4 个架构层次

### 设计模式

仪表盘组件采用 **NG Pattern 架构** + **桥接模式**：

```
前端 (ArkTS)
    ↓ (桥接层)
GaugeModelNG (gauge_model_ng.cpp)
    ↓ (NG Pattern 层)
GaugePattern (gauge_pattern.cpp)
    ↓ (NG LayoutAlgorithm 层)
GaugeLayoutAlgorithm (gauge_layout_algorithm.cpp)
    ↓
GaugeModifier (gauge_modifier.cpp) → 渲染显示
```

---

## GaugeOptions 对象说明

GaugeOptions 是创建仪表盘组件时的参数对象（API 18+）。

| 名称 | 类型 | 必填 | 说明 |
|------|------|------|------|
| value | number | 否 | 量规图的当前数据值，表示图中指示器指向的位置。用于组件创建时量规图初始值的预置。**说明**：value 不在 min 和 max 范围内时使用 min 作为默认值。 |
| min | number | 否 | 当前数据段最小值。默认值：0。max 小于 min 时使用默认值 0 和 100。max 和 min 支持负数。 |
| max | number | 否 | 当前数据段最大值。默认值：100。 |

## 目录结构

```
frameworks/core/components_ng/pattern/gauge/
├── gauge_pattern.h/cpp              # 主 Pattern 业务逻辑
├── gauge_model.h                     # Model 接口定义
├── gauge_model_ng.h/cpp              # NG Model 实现
├── gauge_model_static.h/cpp          # ArkTS 静态 Model
├── gauge_layout_property.h           # 布局属性
├── gauge_paint_property.h            # 绘制属性
├── gauge_layout_algorithm.h/cpp      # 布局计算
├── gauge_paint_method.h/cpp          # 绘制方法
├── gauge_modifier.h/cpp              # 绘制修饰器
├── gauge_theme.h                     # 主题定义
├── gauge_accessibility_property.h/cpp# 无障碍支持
├── gauge_pattern_multi_thread.cpp    # 多线程支持
├── BUILD.gn                          # 构建配置
└── bridge/                           # 桥接层
    ├── gauge_dynamic_modifier.cpp    # ArkTS 动态修饰器
    ├── gauge_static_modifier.cpp     # C API 静态修饰器
    ├── gauge_dynamic_module.h/cpp    # 动态模块
    ├── gauge_model_impl.h/cpp        # Model 实现
    ├── arkts_native_gauge_bridge.h/cpp# ArkTS 原生桥接
    └── content_modifier_helper.h     # 内容修饰器辅助
```

---

## 核心类继承关系

```
Pattern (基类)
    ↓
GaugePattern
    ├── 创建: GaugePaintProperty
    ├── 创建: GaugeLayoutProperty
    ├── 创建: GaugeLayoutAlgorithm
    ├── 创建: GaugeAccessibilityProperty
    └── 创建: GaugeModifier → GaugePaintMethod

GaugeModel (抽象接口)
    ↓
GaugeModelNG (实现)
    └── FrameNode 操作的静态方法

GaugeLayoutAlgorithm
    ↓
BoxLayoutAlgorithm (基类)

GaugeModifier
    ↓
ForegroundModifier (基类)

GaugePaintMethod
    ↓
NodePaintMethod (基类)
```

---

## Pattern 层详解

### GaugePattern 类

**源码位置**：[gauge_pattern.h](frameworks/core/components_ng/pattern/gauge/gauge_pattern.h)

**类定义**：
```cpp
class GaugePattern : public Pattern {
public:
    // 工厂方法
    RefPtr<NodePaintMethod> CreateNodePaintMethod() override;
    RefPtr<PaintProperty> CreatePaintProperty() override;
    RefPtr<LayoutProperty> CreateLayoutProperty() override;
    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override;
    RefPtr<AccessibilityProperty> CreateAccessibilityProperty() override;

    // 生命周期方法
    void OnModifyDone() override;
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty,
        bool skipMeasure, bool skipLayout) override;
    void OnSensitiveStyleChange(bool isSensitive) override;
    void OnColorModeChange(uint32_t colorMode) override;
    void OnColorConfigurationUpdate() override;

    // 子节点管理
    bool HasDescriptionNode() const;
    bool HasMinValueTextNode() const;
    bool HasMaxValueTextNode() const;
    bool HasTitleChildNode() const;

    // 内容修饰器
    void SetBuilderFunc(GaugeMakeCallback&& makeFunc);
    const RefPtr<FrameNode>& GetContentModifierNode() const;
    bool UseContentModifier() const;

private:
    // 子节点初始化
    void InitDescriptionNode();
    void InitLimitValueText(int32_t valueTextId, bool isMin);
    void InitIndicatorImage();
    void InitTitleContent();

    // 属性更新
    void UpdateStrokeWidth(const CalcDimension& strokeWidth, bool isFirstLoad = false);
    void UpdateIndicatorIconPath(const std::string& iconPath, ...);
    void UpdateIndicatorSpace(const CalcDimension& space, bool isFirstLoad = false);

    // 图片加载回调
    LoadSuccessNotifyTask CreateLoadSuccessCallback();
    DataReadyNotifyTask CreateDataReadyCallback();
    LoadFailNotifyTask CreateLoadFailCallback();

    // 成员变量
    std::optional<int32_t> descriptionNodeId_;
    std::optional<int32_t> minValueTextId_;
    std::optional<int32_t> maxValueTextId_;
    std::optional<int32_t> titleChildId_;
    RefPtr<UINode> descriptionNode_;
    RefPtr<ImageLoadingContext> indicatorIconLoadingCtx_;
    RefPtr<CanvasImage> indicatorIconCanvasImage_;
    RefPtr<GaugeModifier> gaugeModifier_;
    RefPtr<FrameNode> contentModifierNode_;
};
```

### 关键职责

1. **节点管理**：
   - 描述节点（自定义内容）
   - 极值文本节点（最小值/最大值显示）
   - 标题子节点
   - 内容修饰器节点（用于自定义 UI）

2. **属性更新**：
   - 圆环厚度、指示器图标、指示器间距
   - 颜色模式变更
   - 隐私/敏感样式变更

3. **图片加载**：
   - 指示器图标图片加载，带回调
   - 图片数据就绪、加载成功和加载失败处理

### OnModifyDone 执行流程

**源码位置**：[gauge_pattern.cpp:36-79](frameworks/core/components_ng/pattern/gauge/gauge_pattern.cpp)

```cpp
void GaugePattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    FireBuilder();  // 触发自定义 UI 构建
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    // 设置对齐方式为居中
    auto layoutProperty = host->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateAlignment(Alignment::CENTER);

    // API 11+ 特性
    if (!Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        InitTitleContent();           // 初始化标题
        InitIndicatorImage();         // 初始化指示器图片
        InitLimitValueText(minId, true);   // 初始化最小值文本
        InitLimitValueText(maxId, false);  // 初始化最大值文本
        InitDescriptionNode();        // 初始化描述节点
    }
}
```

---

## Model 层详解

### GaugeModel（抽象接口）

**源码位置**：[gauge_model.h](frameworks/core/components_ng/pattern/gauge/gauge_model.h)

```cpp
class ACE_FORCE_EXPORT GaugeModel {
public:
    static GaugeModel* GetInstance();

    // 核心配置
    virtual void Create(float values, float min, float max) = 0;
    virtual void SetValue(float value) = 0;

    // 角度和外观
    virtual void SetStartAngle(float startAngle) = 0;
    virtual void SetEndAngle(float endAngle) = 0;
    virtual void SetStrokeWidth(const Dimension& strokeWidth) = 0;

    // 颜色
    virtual void SetColors(const std::vector<Color>& colors,
        const std::vector<float>& values) = 0;
    virtual void SetGradientColors(
        const std::vector<NG::ColorStopArray>& colors,
        const std::vector<float>& values,
        const NG::GaugeType& type) = 0;
    virtual void ResetGradientColors() = 0;

    // 描述和标签
    virtual void SetDescription(const RefPtr<AceType>& customNode) = 0;
    virtual void SetLabelMarkedText(const std::string labelTextString) = 0;
    virtual void SetMarkedTextColor(const Color& color) = 0;
    virtual void SetIsShowLimitValue(bool isShowLimitValue) = 0;
    virtual void SetIsShowDescription(bool isShowDescription) = 0;

    // 阴影
    virtual void SetShadowOptions(const NG::GaugeShadowOptions& shadowOptions) = 0;
    virtual void ResetShadowOptions() = 0;

    // 指示器
    virtual void SetIsShowIndicator(bool isShowIndicator) = 0;
    virtual void SetIndicatorIconPath(const std::string& iconPath,
        const std::string& bundleName, const std::string& moduleName) = 0;
    virtual void SetIndicatorSpace(const Dimension& space) = 0;
    virtual void ResetIndicatorIconPath() = 0;
    virtual void ResetIndicatorSpace() = 0;

    // 资源支持
    virtual void CreateWithResourceObj(GaugeResourceType jsResourceType,
        const RefPtr<ResourceObject>& resObj) = 0;

    // 渐变设置
    virtual void SetUseGradient(bool useGradient) = 0;
    virtual void SetUseSpecialDefaultIndicator(bool useSpecialDefaultIndicator) = 0;
    virtual void SetGradientColorModeInit() = 0;
    virtual void SetGradientInit(const std::vector<NG::ColorStopArray>& colors) = 0;
};
```

### GaugeModelNG（实现）

**源码位置**：[gauge_model_ng.h](frameworks/core/components_ng/pattern/gauge/gauge_model_ng.h)

**关键静态方法**：
- `CreateFrameNode(float value, float min, float max)` - 创建 FrameNode
- `SetValue(FrameNode* frameNode, float value)` - 设置数值
- `SetStartAngle/EndAngle(FrameNode* frameNode, float value)` - 设置角度
- `SetGradientColors(...)` - 设置渐变颜色
- `SetBuilderFunc(FrameNode* frameNode, NG::GaugeMakeCallback&& jsMake)` - 设置自定义 UI

### Create 方法详解

**源码位置**：[gauge_model_ng.cpp:25-41](frameworks/core/components_ng/pattern/gauge/gauge_model_ng.cpp)

```cpp
void GaugeModelNG::Create(float value, float min, float max)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        GAUGE_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<GaugePattern>(); });
    stack->Push(frameNode);

    // 设置初始值
    ACE_UPDATE_PAINT_PROPERTY(GaugePaintProperty, Value, value);
    ACE_UPDATE_PAINT_PROPERTY(GaugePaintProperty, Max, max);
    ACE_UPDATE_PAINT_PROPERTY(GaugePaintProperty, Min, min);

    // 配置变更支持
    if (SystemProperties::ConfigChangePerform()) {
        SetUseGradient(false);
        SetUseSpecialDefaultIndicator(false);
    }
}
```

---

## 布局算法

### GaugeLayoutAlgorithm

**源码位置**：[gauge_layout_algorithm.h](frameworks/core/components_ng/pattern/gauge/gauge_layout_algorithm.h)

**关键方法**：

```cpp
class GaugeLayoutAlgorithm : public BoxLayoutAlgorithm {
public:
    void Measure(LayoutWrapper* layoutWrapper) override;
    void Layout(LayoutWrapper* layoutWrapper) override;
    std::optional<SizeF> MeasureContent(
        const LayoutConstraintF& contentConstraint,
        LayoutWrapper* layoutWrapper) override;

private:
    void MeasureLimitValueText(LayoutWrapper* layoutWrapper,
        const SizeF& parentSize, bool isMin);
    void MeasureDescription(LayoutWrapper* layoutWrapper,
        const SizeF& parentSize);
    void MeasureTitleChild(LayoutWrapper* layoutWrapper,
        const SizeF& parentSize);
    void MeasureLimitValueTextWidth(LayoutWrapper* layoutWrapper);
    void MeasureFontSize(LayoutWrapper* layoutWrapper);

    bool CheckDescriptionIsImageNode(const RefPtr<LayoutWrapper>& layoutWrapper) const;
    bool GetLimitFontSize(LayoutWrapper* layoutWrapper, bool isMin, Dimension& fontSize);
    void SetLimitFontSize(LayoutWrapper* layoutWrapper, bool isMin, const Dimension& fontSize);

    RefPtr<ImageLoadingContext> indicatorIconLoadingCtx_;
    double limitValueTextWidth_ = 0.0;
    double startAngleOffsetX_ = 0.0;
    double endAngleOffsetX_ = 0.0;
};
```

### 布局计算常量

**源码位置**：[gauge_theme.h:41-63](frameworks/core/components_ng/pattern/gauge/gauge_theme.h)

```cpp
// 描述节点尺寸比例
constexpr float DESCRIPTION_NODE_WIDTH_RATIO = 0.4444f;
constexpr float DESCRIPTION_NODE_HEIGHT_RATIO = 0.254f;
constexpr float DESCRIPTION_IMAGE_NODE_WIDTH_RATIO = 0.286f;
constexpr float DESCRIPTION_IMAGE_NODE_HEIGHT_RATIO = 0.286f;

// 描述节点位置比例
constexpr float DESCRIPTION_X = 0.2778f;
constexpr float DESCRIPTION_Y = 0.746f;
constexpr float DESCRIPTION_IMAGE_X = 0.357f;
constexpr float DESCRIPTION_IMAGE_Y = 0.714f;

// 极值文本位置比例
constexpr float LIMIT_VALUE_MIN_OR_MAX_HEIGHT_RATIO = 0.2222f;
constexpr float LIMIT_VALUE_Y = 0.722f;

// 指示器尺寸比例
constexpr float INDICATOR_WIDTH_RADIO = 0.135f;
constexpr float INDICATOR_HEIGHT_RADIO = 0.095f;

// 极值文本安全距离
constexpr float LIMIT_VALUE_MIN_SAFE_DISTANCE_RATIO = 0.031;
constexpr float LIMIT_VALUE_MAX_SAFE_DISTANCE_RATIO = 0.031;
constexpr float LIMIT_VALUE_SPACE_SAFE_DISTANCE_RATIO = 0.0635;
```

### MeasureContent 方法

**源码位置**：[gauge_layout_algorithm.cpp:83-135](frameworks/core/components_ng/pattern/gauge/gauge_layout_algorithm.cpp)

```cpp
std::optional<SizeF> GaugeLayoutAlgorithm::MeasureContent(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    auto layoutProperty = AceType::DynamicCast<LayoutProperty>(
        layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(layoutProperty, std::nullopt);
    auto layoutPolicy = layoutProperty->GetLayoutPolicyProperty();

    // Wrap 或 Fix 模式返回零尺寸
    if (layoutPolicy.has_value() &&
        (layoutPolicy->IsWrap() || layoutPolicy->IsFix())) {
        return SizeF(ZERO_MEASURE_CONTENT_SIZE, ZERO_MEASURE_CONTENT_SIZE);
    }

    // 自定义内容修饰器模式
    auto pattern = host->GetPattern<GaugePattern>();
    CHECK_NULL_RETURN(pattern, std::nullopt);
    if (pattern->UseContentModifier()) {
        host->GetGeometryNode()->ResetContent();
        return std::nullopt;
    }

    // 使用指定尺寸或默认主题尺寸
    if (contentConstraint.selfIdealSize.IsValid()) {
        auto len = std::min(contentConstraint.selfIdealSize.Height().value(),
                           contentConstraint.selfIdealSize.Width().value());
        return SizeF(len, len);
    }

    // 使用主题默认值
    auto gaugeTheme = pipeline->GetTheme<ProgressTheme>();
    auto defaultThickness = gaugeTheme->GetTrackWidth().ConvertToPx();
    return SizeF(defaultThickness, defaultThickness);
}
```

### Layout 方法

**源码位置**：[gauge_layout_algorithm.cpp:275-330](frameworks/core/components_ng/pattern/gauge/gauge_layout_algorithm.cpp)

```cpp
void GaugeLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    auto hostNode = layoutWrapper->GetHostNode();
    auto gaugePattern = hostNode->GetPattern<GaugePattern>();

    // 内容修饰器模式使用默认布局
    if (gaugePattern->UseContentModifier()) {
        BoxLayoutAlgorithm::Layout(layoutWrapper);
        return;
    }

    // 计算圆心和半径
    auto paddingSize = layoutGeometryNode->GetPaddingSize();
    auto diameter = std::min(paddingSize.Width(), paddingSize.Height());
    auto radius = diameter / 2.0f;
    OffsetF circularOffset = offset + OffsetF(left, top);

    // 遍历子节点进行布局
    for (const auto& child : allChildrenWrapperList) {
        auto nodeId = child->GetHostNode()->GetId();
        OffsetF childOffset;

        if (nodeId == gaugePattern->GetDescriptionNodeId()) {
            // 描述节点位置
            childOffset = circularOffset + OffsetF(DESCRIPTION_X * diameter,
                                                   DESCRIPTION_Y * diameter);
        } else if (nodeId == gaugePattern->GetMinValueTextId()) {
            // 最小值文本位置
            childOffset = circularOffset + OffsetF(
                startAngleOffsetX_ + LIMIT_VALUE_MIN_SAFE_DISTANCE_RATIO * diameter - left,
                LIMIT_VALUE_Y * diameter);
        } else if (nodeId == gaugePattern->GetMaxValueTextId()) {
            // 最大值文本位置
            childOffset = circularOffset + OffsetF(
                endAngleOffsetX_ - limitValueTextWidth_ -
                LIMIT_VALUE_MAX_SAFE_DISTANCE_RATIO * diameter - left,
                LIMIT_VALUE_Y * diameter);
        } else if (nodeId == gaugePattern->GetTitleChildId()) {
            // 标题子节点位置
            childOffset = circularOffset;
        }

        childGeometryNode->SetMarginFrameOffset(childOffset);
        child->Layout();
    }

    // 处理指示器图片尺寸
    indicatorIconLoadingCtx_->MakeCanvasImage(
        SizeF(INDICATOR_WIDTH_RADIO * diameter, INDICATOR_HEIGHT_RADIO * diameter),
        true, ImageFit::FILL);
}
```

---

## 绘制方法

### GaugePaintMethod

**源码位置**：[gauge_paint_method.h](frameworks/core/components_ng/pattern/gauge/gauge_paint_method.h)

```cpp
class GaugePaintMethod : public NodePaintMethod {
public:
    GaugePaintMethod(const WeakPtr<Pattern>& pattern,
        const RefPtr<GaugeModifier>& gaugeModifier);

    void UpdateForegroundModifier(PaintWrapper* paintWrapper) override;
    RefPtr<Modifier> GetForegroundModifier(PaintWrapper* paintWrapper) override;
    void SetBoundsRect();

private:
    WeakPtr<Pattern> pattern_;
    RefPtr<GaugeModifier> gaugeModifier_;
    RectF boundsRect_;
};
```

### SetBoundsRect 方法

**源码位置**：[gauge_paint_method.cpp:26-56](frameworks/core/components_ng/pattern/gauge/gauge_paint_method.cpp)

```cpp
void GaugePaintMethod::SetBoundsRect()
{
    auto gaugePattern = DynamicCast<GaugePattern>(pattern_.Upgrade());
    auto host = gaugePattern->GetHost();
    auto paintProperty = host->GetPaintProperty<GaugePaintProperty>();

    GaugeShadowOptions shadowOptions;
    if (paintProperty->HasShadowOptions()) {
        shadowOptions = paintProperty->GetShadowOptionsValue();
    }

    auto frameSize = hostGeometryNode->GetFrameSize();

    // 计算包含阴影的边界矩形
    float x = std::min<float>(shadowOptions.offsetX - shadowOptions.radius,
                              boundsRect_.GetX());
    float y = std::min<float>(shadowOptions.offsetY - shadowOptions.radius,
                              boundsRect_.GetY());
    float width = std::max<float>({
        boundsRect_.Width(),
        shadowOptions.offsetX - x + frameSize.Width() + shadowOptions.radius * 2.0f,
        std::abs(shadowOptions.offsetX) + frameSize.Width() + shadowOptions.radius * 2.0f
    });
    float height = std::max<float>({
        boundsRect_.Height(),
        shadowOptions.offsetY - y + frameSize.Height() + shadowOptions.radius * 2.0f,
        std::abs(shadowOptions.offsetY) + frameSize.Height() + shadowOptions.radius * 2.0f
    });

    boundsRect_.SetRect(x, y, width, height);
    gaugeModifier_->SetBoundsRect(boundsRect_);
}
```

---

## 属性系统

### colors 属性详解

从 API version 11 开始，colors 属性使用以下规则：

| 参数类型 | 圆环类型 | 说明 |
|---------|---------|------|
| `ResourceColor` | 单色环 | 设置单一纯色 |
| `LinearGradient` | 渐变环 | 整个圆弧渐变 |
| `Array<[ResourceColor\|LinearGradient, number]>` | 分段渐变环 | 多段颜色带权重，最多 9 段 |

**分段渐变环规则**：
- 最大显示段数为 9 段，若多于 9 段则多于部分不显示
- 第一个参数为颜色值，若设置为非颜色类型，则置为 `0xFFE84026`（红色）
- 第二个参数为颜色所占比重，若设置为负数或是非数值类型，则将比重置为 0
- 若对应颜色的比重为 0，则该颜色在圆环中不显示
- 若所有颜色比重均为 0，圆环不显示

**默认颜色规则**：
- 若不传颜色，或者数组为空，无法确定圆环类型及颜色，则圆环颜色为 `0xFF64BB5C`（绿色）、`0xFFF7CE00`（黄色）、`0xFFE84026`（红色）的渐变环
- 若传入颜色，但颜色值有误，则该颜色为 `0xFFE84026`（红色）

### strokeWidth 属性详解

| 项目 | 值 |
|------|-----|
| 默认值 | 4 |
| 单位 | vp |
| 说明 | 用于设置圆环的环形厚度。设置小于等于 0 的值时，按默认值显示；环形厚度的最大值为圆环的半径，超过最大值按最大值处理；不支持百分比 |

### description 属性详解（API 11+）

| 项目 | 说明 |
|------|------|
| 类型 | CustomBuilder |
| 说明 | @Builder 中的内容由开发者自定义，建议使用文本或者图片 |
| 基准范围 | 圆环直径的 44.4% × 25.4% 的矩形（图片为 28.6% × 28.6%） |
| 位置 | 距离圆环底部 0vp，左右居中 |
| 行为 | 设置 null 则不显示内容；不设置则依赖是否设置数据最大最小值 |

**description 默认行为**：
- 若设置最大最小值或者只设置其中一个，则显示最大最小值
- 若未设置最大最小值，则不显示内容
- 最大最小值显示在圆环底部，位置不可移动，若圆环开口角度设置不恰当，存在圆环遮挡文字的情况

### trackShadow 属性详解（API 11+）

**GaugeShadowOptions** 继承自 **MultiShadowOptions**，具有 MultiShadowOptions 的全部属性。

| 项目 | 说明 |
|------|------|
| 阴影颜色 | 与圆环颜色相同 |
| 设置 null | 阴影效果被禁用 |
| radius | 阴影模糊半径 |
| offsetX | X 轴偏移量 |
| offsetY | Y 轴偏移量 |

### indicator 属性详解（API 11+）

**GaugeIndicatorOptions** 对象说明：

| 名称 | 类型 | 说明 |
|------|------|------|
| icon | ResourceStr | 图标资源路径。不配置则使用系统默认样式（三角形指针）。**仅支持使用 svg 格式的图标**，若使用其它格式则使用默认的三角形样式指针。 |
| space | Dimension | 指针距离圆环外边的间距。默认值：8vp；**不支持百分比**。若设置值小于 0，则使用默认值；若设置值大于圆环半径，则使用默认值。 |

### privacySensitive 属性详解（API 12+）

设置仪表盘的隐私敏感模式。

| 项目 | 说明 |
|------|------|
| 参数 | `Optional<boolean>` |
| 行为 | 启用隐私敏感模式时，仪表盘指示器指向最小值（0）位置，最大值和最小值文本将被遮罩，量程显示灰色或底色 |
| 设置 null | 不敏感 |

### contentModifier 属性详解（API 12+）

定制 Gauge 内容区的方法。

**GaugeConfiguration** 对象说明（继承自 CommonConfiguration）：

| 名称 | 类型 | 说明 |
|------|------|------|
| value | number | 当前数据值 |
| min | number | 当前数据段最小值 |
| max | number | 当前数据段最大值 |
| enabled | boolean | 是否可用 |

### GaugePaintProperty

**源码位置**：[gauge_paint_property.h](frameworks/core/components_ng/pattern/gauge/gauge_paint_property.h)

**属性列表**：

```cpp
// 数值属性
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Value, float, PROPERTY_UPDATE_RENDER);
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Min, float, PROPERTY_UPDATE_RENDER);
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Max, float, PROPERTY_UPDATE_RENDER);

// 角度属性
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(StartAngle, float, PROPERTY_UPDATE_RENDER);
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(EndAngle, float, PROPERTY_UPDATE_RENDER);

// 颜色属性
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Colors, std::vector<Color>, PROPERTY_UPDATE_RENDER);
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(GradientColors, std::vector<ColorStopArray>, PROPERTY_UPDATE_RENDER);
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Values, std::vector<float>, PROPERTY_UPDATE_RENDER);

// 类型
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(GaugeType, GaugeType, PROPERTY_UPDATE_RENDER);

// 外观
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(StrokeWidth, Dimension, PROPERTY_UPDATE_RENDER);
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ShadowOptions, GaugeShadowOptions, PROPERTY_UPDATE_RENDER);

// 指示器
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IsShowIndicator, bool, PROPERTY_UPDATE_RENDER);
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IndicatorIconSourceInfo, ImageSourceInfo, PROPERTY_UPDATE_RENDER);
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IndicatorSpace, Dimension, PROPERTY_UPDATE_RENDER);
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IndicatorChange, bool, PROPERTY_UPDATE_RENDER);

// 隐私
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IsSensitive, bool, PROPERTY_UPDATE_RENDER);

// 渐变设置
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(UseJsLinearGradient, bool, PROPERTY_UPDATE_RENDER);
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(UseSpecialDefaultIndicator, bool, PROPERTY_UPDATE_RENDER);
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(GradientColorsInit, std::vector<ColorStopArray>, PROPERTY_UPDATE_RENDER);
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ColorModeInit, int, PROPERTY_UPDATE_RENDER);
```

### GaugeType 枚举

```cpp
enum class GaugeType : int32_t {
    TYPE_CIRCULAR_MULTI_SEGMENT_GRADIENT = 0,  // 多段渐变，带权重
    TYPE_CIRCULAR_SINGLE_SEGMENT_GRADIENT = 1, // 单段渐变
    TYPE_CIRCULAR_MONOCHROME = 2,              // 单色
};
```

### GaugeShadowOptions 结构体

```cpp
struct GaugeShadowOptions {
    bool isShadowVisible = true;
    float radius = DEFAULT_GAUGE_SHADOW_RADIUS;      // 默认: 20.0f
    float offsetX = DEFAULT_GAUGE_SHADOW_OFFSETX;    // 默认: 5.0f
    float offsetY = DEFAULT_GAUGE_SHADOW_OFFSETY;    // 默认: 5.0f

    // 资源管理
    void AddResource(const std::string& key,
        const RefPtr<ResourceObject>& resObj, UpdateFunc&& updateFunc);
    void ReloadResources();
};
```

### GaugeLayoutProperty

**源码位置**：[gauge_layout_property.h](frameworks/core/components_ng/pattern/gauge/gauge_layout_property.h)

```cpp
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IsShowLimitValue, bool, PROPERTY_UPDATE_MEASURE_SELF);
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IsShowDescription, bool, PROPERTY_UPDATE_MEASURE_SELF);
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(StrokeWidth, Dimension, PROPERTY_UPDATE_MEASURE_SELF);
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(StartAngle, float, PROPERTY_UPDATE_MEASURE_SELF);
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(EndAngle, float, PROPERTY_UPDATE_MEASURE_SELF);
```

---

## 主题系统

### GaugeTheme

**源码位置**：[gauge_theme.h](frameworks/core/components_ng/pattern/gauge/gauge_theme.h)

**默认值**：

```cpp
// 角度默认值
constexpr float DEFAULT_START_DEGREE = 0.0f;
constexpr float DEFAULT_END_DEGREE = 360.0f;

// 数值默认值
constexpr float DEFAULT_MIN_VALUE = 0.0f;
constexpr float DEFAULT_MAX_VALUE = 100.0f;

// 阴影默认值
constexpr float DEFAULT_GAUGE_SHADOW_RADIUS = 20.0f;
constexpr float DEFAULT_GAUGE_SHADOW_OFFSETX = 5.0f;
constexpr float DEFAULT_GAUGE_SHADOW_OFFSETY = 5.0f;

// 描边默认值
constexpr Dimension TRACK_THICKNESS = 4.0_vp;

// 指示器默认值
constexpr float INDICATOR_WIDTH_RATIO = 0.135f;
constexpr float INDICATOR_HEIGHT_RATIO = 0.087f;
constexpr Dimension INDICATOR_DISTANCE_TO_TOP = 8.0_vp;

// 极值文本
constexpr Dimension LIMIT_VALUE_MAX_FONTSIZE = 40.0_vp;
constexpr int32_t COLORS_MAX_COUNT = 9;

// 默认颜色
// 注意：默认颜色顺序为绿色、黄色、红色
constexpr std::vector<Color> GAUGE_DEFAULT_COLOR {
    Color(0xFF64BB5C),  // 绿色 - 0xFF64BB5C
    Color(0xFFF7CE00),  // 黄色 - 0xFFF7CE00
    Color(0xFFE84026)   // 红色 - 0xFFE84026
};

// 颜色错误时的默认值
constexpr Color COLOR_ERROR_DEFAULT = Color(0xFFE84026);  // 红色
```

### 主题属性

| 属性 | 类型 | 默认值 | 描述 |
|------|------|--------|------|
| `indicatorColor_` | Color | Color::BLACK | 指示器颜色 |
| `indicatorBorderColor_` | Color | Color::WHITE | 指示器边框颜色 |
| `limitValueMinFontSize_` | Dimension | 10.0_vp | 极值文本最小字号 |
| `trackThickness_` | Dimension | 4.0_vp | 轨道厚度 |
| `indicatorWidthRatio_` | float | 0.135f | 指示器宽度比例 |
| `indicatorHeightRatio_` | float | 0.087f | 指示器高度比例 |
| `indicatorRadiusRatio_` | float | 0.01f | 指示器圆角比例 |
| `indicatorBorderRatio_` | float | 0.06f | 指示器边框比例 |
| `intervalRatio_` | float | 0.08f | 间隔比例 |

---

## 桥接层

### GaugeModifier（绘制）

**源码位置**：[gauge_modifier.h](frameworks/core/components_ng/pattern/gauge/gauge_modifier.h)

**关键绘制方法**：

```cpp
class GaugeModifier : public ForegroundModifier {
public:
    void onDraw(DrawingContext& context) override;
    void UpdateValue();

private:
    void PaintCircularAndIndicator(RSCanvas& canvas);
    void NewPaintCircularAndIndicator(RSCanvas& canvas);
    void NewDrawIndicator(RSCanvas& canvas, RefPtr<GaugePaintProperty>& paintProperty,
        RenderRingInfo& data);
    void NewDrawImageIndicator(RSCanvas& canvas, RefPtr<GaugePaintProperty>& paintProperty,
        RenderRingInfo& data);

    // 三种仪表盘类型
    void PaintMonochromeCircular(RSCanvas& canvas, RenderRingInfo data,
        RefPtr<GaugePaintProperty>& paintProperty);
    void PaintSingleSegmentGradientCircular(RSCanvas& canvas, RenderRingInfo data,
        RefPtr<GaugePaintProperty>& paintProperty);
    void PaintMultiSegmentGradientCircular(RSCanvas& canvas, RenderRingInfo data,
        RefPtr<GaugePaintProperty>& paintProperty);

    // 阴影绘制
    void PaintMonochromeCircularShadow(...);
    void PaintSingleSegmentGradientCircularShadow(...);
    void PaintMultiSegmentGradientCircularShadow(...);

    // 辅助方法
    void CalculateStartAndSweepDegree(RefPtr<GaugePaintProperty>& paintProperty,
        RenderRingInfo& data);
    float GetOffsetDegree(RenderRingInfo& data, float oppositeSide);
    bool ShouldHighLight(float start, float interval, float percent);
};
```

### 桥接层文件

| 文件 | 用途 |
|------|------|
| `gauge_dynamic_modifier.cpp` | ArkTS 动态修饰器实现 |
| `gauge_static_modifier.cpp` | 静态 C API 修饰器实现 |
| `gauge_model_impl.h/cpp` | 传统 Model 实现 |
| `arkts_native_gauge_bridge.h/cpp` | ArkTS 原生桥接 |

### 动态修饰器

**源码位置**：[gauge_dynamic_modifier.cpp](frameworks/core/components_ng/pattern/gauge/bridge/gauge_dynamic_modifier.cpp)

**关键接口**：

```cpp
// 构造函数
Ark_NativePointer ConstructImpl(Ark_Int32 id, Ark_Int32 flags);

// 设置选项
void SetGaugeOptionsImpl(Ark_NativePointer node, const Ark_GaugeOptions* options);

// 属性设置
void SetValueImpl(Ark_NativePointer node, const Opt_Float64* value);
void SetStartAngleImpl(Ark_NativePointer node, const Opt_Float64* value);
void SetEndAngleImpl(Ark_NativePointer node, const Opt_Float64* value);
void SetColorsImpl(Ark_NativePointer node, ...);
void SetStrokeWidthImpl(Ark_NativePointer node, const Opt_Length* value);
void SetPrivacySensitiveImpl(Ark_NativePointer node, const Opt_Boolean* value);

// 扩展访问器
void SetIndicatorImpl(Ark_NativePointer node, const Opt_GaugeIndicatorOptions* value);
void SetTrackShadowImpl(Ark_NativePointer node, const Opt_GaugeShadowOptions* value);
void SetDescriptionImpl(Ark_NativePointer node, const Opt_CustomNodeBuilder* value);
```

---

## 执行流程

### 创建流程

```
ArkTS: Gauge({ value: 50, min: 0, max: 100 })
    ↓
GaugeModelNG::Create(50, 0, 100)
    ↓
FrameNode::GetOrCreateFrameNode(GAUGE_ETS_TAG, nodeId, GaugePattern)
    ↓
创建 PaintProperty (Value=50, Min=0, Max=100)
创建 LayoutProperty
创建 GaugePattern
    ↓
OnModifyDone() → InitDescriptionNode(), InitLimitValueText(), InitIndicatorImage()
    ↓
Measure (GaugeLayoutAlgorithm)
    ↓
Layout (定位子节点)
    ↓
Paint (GaugeModifier::onDraw)
```

### 数值更新流程

```
ArkTS: gauge.value(75)
    ↓
GaugeModelNG::SetValue(75)
    ↓
ACE_UPDATE_PAINT_PROPERTY(GaugePaintProperty, Value, 75)
    ↓
标记 PROPERTY_UPDATE_RENDER
    ↓
GaugeModifier::UpdateValue() (通过 GaugePaintMethod)
    ↓
使用新值重新渲染
```

### 图片加载流程

```
SetIndicatorIconPath(iconPath, bundleName, moduleName)
    ↓
GaugePaintProperty::UpdateIndicatorIconSourceInfo(ImageSourceInfo)
    ↓
InitIndicatorImage()
    ↓
创建 ImageLoadingContext，设置回调:
    - OnImageDataReady() → MarkNeedFrameFlushDirty(MEASURE_SELF)
    - OnImageLoadSuccess() → MarkNeedRenderOnly()
    - OnImageLoadFail() → ResetIndicatorIconSourceInfo()
```

### 颜色模式变更流程

```
系统深色模式切换
    ↓
OnColorConfigurationUpdate()
    ↓
检查是否使用渐变色
    ↓
处理颜色反转
    ├─ ProcessSingleColorStop() - 单色处理
    └─ ProcessGradientColors() - 渐变色处理
    ↓
更新 GradientColors
    ↓
标记 PROPERTY_UPDATE_RENDER
```

---

## 完整 API 清单

### 创建 API

| API | 描述 | 源码位置 |
|-----|------|----------|
| `Create(float value, float min, float max)` | 创建仪表盘 | gauge_model_ng.cpp:25 |
| `CreateFrameNode(float value, float min, float max)` | 静态创建方法 | gauge_model_ng.cpp:181 |

### 数值 API

| API | 描述 | 源码位置 |
|-----|------|----------|
| `SetValue(float value)` | 设置当前值 | gauge_model_ng.cpp:43 |
| `SetValue(FrameNode*, float value)` | 静态设置方法 | gauge_model_ng.cpp:199 |

### 角度 API

| API | 描述 | 源码位置 |
|-----|------|----------|
| `SetStartAngle(float startAngle)` | 设置起始角度（度） | gauge_model_ng.cpp:48 |
| `SetEndAngle(float endAngle)` | 设置结束角度（度） | gauge_model_ng.cpp:54 |

### 颜色 API

| API | 描述 | 源码位置 |
|-----|------|----------|
| `SetColors(vector<Color>, vector<float>)` | 设置颜色与权重（传统） | gauge_model_ng.cpp:60 |
| `SetGradientColors(vector<ColorStopArray>, vector<float>, GaugeType)` | 设置渐变颜色 | gauge_model_ng.cpp:66 |
| `ResetGradientColors()` | 重置为默认颜色 | gauge_model_ng.cpp:155 |

### 外观 API

| API | 描述 | 源码位置 |
|-----|------|----------|
| `SetStrokeWidth(Dimension)` | 设置圆环厚度 | gauge_model_ng.cpp:76 |
| `SetShadowOptions(GaugeShadowOptions)` | 设置圆环阴影 | gauge_model_ng.cpp:116 |
| `ResetShadowOptions()` | 重置阴影 | gauge_model_ng.cpp:166 |

### 描述 API

| API | 描述 | 源码位置 |
|-----|------|----------|
| `SetDescription(RefPtr<AceType>)` | 设置自定义描述节点 | gauge_model_ng.cpp:82 |
| `SetIsShowDescription(bool)` | 显示/隐藏描述 | gauge_model_ng.cpp:107 |
| `SetIsShowLimitValue(bool)` | 显示/隐藏极值 | gauge_model_ng.cpp:102 |

### 指示器 API

| API | 描述 | 源码位置 |
|-----|------|----------|
| `SetIsShowIndicator(bool)` | 显示/隐藏指示器 | gauge_model_ng.cpp:138 |
| `SetIndicatorIconPath(string, string, string)` | 设置自定义指示器图标 | gauge_model_ng.cpp:143 |
| `SetIndicatorSpace(Dimension)` | 设置指示器与轨道间距 | gauge_model_ng.cpp:150 |
| `ResetIndicatorIconPath()` | 重置为默认指示器 | gauge_model_ng.cpp:171 |
| `ResetIndicatorSpace()` | 重置指示器间距 | gauge_model_ng.cpp:176 |

### 内容修饰器 API

| API | 描述 | 源码位置 |
|-----|------|----------|
| `SetBuilderFunc(FrameNode*, GaugeMakeCallback)` | 设置自定义 UI 构建器 | gauge_model_ng.cpp:314 |

### 资源 API

| API | 描述 | 源码位置 |
|-----|------|----------|
| `CreateWithResourceObj(GaugeResourceType, RefPtr<ResourceObject>)` | 创建带资源的仪表盘 | gauge_model_ng.cpp:386 |

---

## 关键实现细节

### 1. 仪表盘类型处理

组件通过 `GaugeType` 枚举支持三种类型：

1. **TYPE_CIRCULAR_MONOCHROME**：单一纯色
2. **TYPE_CIRCULAR_SINGLE_SEGMENT_GRADIENT**：整个圆弧渐变
3. **TYPE_CIRCULAR_MULTI_SEGMENT_GRADIENT**：多段颜色带权重

**实现位置**：`GaugeModifier::onDraw()` in [gauge_modifier.cpp](frameworks/core/components_ng/pattern/gauge/gauge_modifier.cpp)

### 2. 极值文本布局计算

极值文本位置基于起始/结束角度使用三角函数计算：

**源码位置**：[gauge_layout_algorithm.cpp:173-178](frameworks/core/components_ng/pattern/gauge/gauge_layout_algorithm.cpp)

```cpp
auto startDegree = startAngle * ACE_PI / HALF_CIRCLE;
auto endDegree = endAngle * ACE_PI / HALF_CIRCLE;
startAngleOffsetX_ = center.GetX() + (radius - strokeWidthValue) * std::cos(startDegree);
endAngleOffsetX_ = center.GetX() + (radius - strokeWidthValue) * std::cos(endDegree);
```

### 3. 内容修饰器支持

可通过 `GaugeMakeCallback` 提供自定义 UI：

```cpp
using GaugeMakeCallback =
    std::function<RefPtr<FrameNode>(const GaugeConfiguration& gaugeConfiguration)>;

struct GaugeConfiguration : public CommonConfiguration {
    float value_;
    float min_;
    float max_;
};
```

### 4. 阴影实现

圆环阴影在主圆环之前渲染：

- **单色**：`PaintMonochromeCircularShadow()`
- **单段渐变**：`PaintSingleSegmentGradientCircularShadow()`
- **多段渐变**：`PaintMultiSegmentGradientCircularShadow()`

### 5. 指示器渲染

两种指示器类型：
1. **默认指示器**：使用 RSPath 绘制三角形
2. **图片指示器**：通过 `ImageLoadingContext` 加载 SVG

### 6. 颜色模式变更支持

深色模式支持与资源检查：

**源码位置**：[gauge_pattern.cpp:416-427](frameworks/core/components_ng/pattern/gauge/gauge_pattern.cpp)

```cpp
bool CheckDarkResource(uint32_t resId) {
    auto colorMode = Container::CurrentColorMode();
    if (colorMode != ColorMode::DARK) {
        return true;
    }
    // 检查深色资源是否存在
    return resourceAdapter->ExistDarkResById(std::to_string(resId));
}
```

### 7. 隐私/敏感样式

启用隐私模式时：
- 极值文本通过 `ObscureText()` 遮蔽
- 在 paint property 上设置 `isSensitive` 标志

**源码位置**：[gauge_pattern.cpp:324-354](frameworks/core/components_ng/pattern/gauge/gauge_pattern.cpp)

```cpp
void GaugePattern::OnSensitiveStyleChange(bool isSensitive)
{
    // 遮蔽极值文本
    ObscureLimitValueText(isSensitive);

    auto frameNode = GetHost();
    auto gaugePaintProperty = frameNode->GetPaintProperty<NG::GaugePaintProperty>();
    gaugePaintProperty->UpdateIsSensitive(isSensitive);
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}
```

### 8. 圆环厚度资源更新

圆环厚度支持资源动态更新：

**源码位置**：[gauge_model_ng.cpp:322-338](frameworks/core/components_ng/pattern/gauge/gauge_model_ng.cpp)

```cpp
void HandleStrokeWidthResource(const RefPtr<ResourceObject>& resObj,
    const RefPtr<GaugePattern>& pattern)
{
    const std::string key = "gauge.strokeWidth";
    pattern->RemoveResObj(key);

    auto&& updateFunc = [weak = AceType::WeakClaim(AceType::RawPtr(pattern))](
                            const RefPtr<ResourceObject>& resObj, bool isFirstLoad = false) {
        auto pattern = weak.Upgrade();
        CalcDimension result;
        if (!ResourceParseUtils::ParseResDimensionVpNG(resObj, result) ||
            result.Unit() == DimensionUnit::PERCENT) {
            result = CalcDimension(0);
        }
        pattern->UpdateStrokeWidth(result, isFirstLoad);
    };
    pattern->AddResObj(key, resObj, std::move(updateFunc));
}
```

### 9. 指示器图标加载

指示器图标支持异步加载与回调：

**源码位置**：[gauge_pattern.cpp:248-322](frameworks/core/components_ng/pattern/gauge/gauge_pattern.cpp)

```cpp
void GaugePattern::InitIndicatorImage()
{
    auto gaugePaintProperty = GetPaintProperty<GaugePaintProperty>();
    ImageSourceInfo sourceInfo =
        gaugePaintProperty->GetIndicatorIconSourceInfo().value_or(ImageSourceInfo(""));

    // 创建加载上下文，设置回调
    LoadNotifier iconLoadNotifier(
        CreateDataReadyCallback(),   // OnImageDataReady
        CreateLoadSuccessCallback(), // OnImageLoadSuccess
        CreateLoadFailCallback()     // OnImageLoadFail
    );
    indicatorIconLoadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(
        sourceInfo, std::move(iconLoadNotifier), true);
    indicatorIconLoadingCtx_->LoadImageData();
}

void GaugePattern::OnImageDataReady()
{
    auto host = GetHost();
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void GaugePattern::OnImageLoadSuccess()
{
    auto host = GetHost();
    host->MarkNeedRenderOnly();

    // 仅支持 SVG
    if (!indicatorIconLoadingCtx_->GetSourceInfo().IsSvg()) {
        gaugePaintProperty->ResetIndicatorIconSourceInfo();
        return;
    }
    // 设置 Canvas 图片
    indicatorIconCanvasImage_ = indicatorIconLoadingCtx_->MoveCanvasImage();
}
```

---

## 使用示例

### 基础仪表盘

```typescript
Gauge({ value: 50, min: 0, max: 100 })
```

### 单色仪表盘

```typescript
Gauge({ value: 50, min: 1, max: 100 })
  .startAngle(210)
  .endAngle(150)
  .colors('#cca5d61d')  // 单色
  .strokeWidth(18)
```

### 多段渐变仪表盘

```typescript
Gauge({ value: 50, min: 1, max: 100 })
  .startAngle(210)
  .endAngle(150)
  .colors([
    [new LinearGradient([{ color: '#deb6fb', offset: 0 }, { color: '#ac49f5', offset: 1 }]), 9],
    [new LinearGradient([{ color: '#bbb7fc', offset: 0 }, { color: '#564af7', offset: 1 }]), 8],
    [new LinearGradient([{ color: '#f5b5c2', offset: 0 }, { color: '#e64566', offset: 1 }]), 7],
    [new LinearGradient([{ color: '#f8c5a6', offset: 0 }, { color: '#ed6f21', offset: 1 }]), 6],
    [new LinearGradient([{ color: '#fceb99', offset: 0 }, { color: '#f7ce00', offset: 1 }]), 5],
    [new LinearGradient([{ color: '#dbefa5', offset: 0 }, { color: '#a5d61d', offset: 1 }]), 4],
    [new LinearGradient([{ color: '#c1e4be', offset: 0 }, { color: '#64bb5c', offset: 1 }]), 3],
    [new LinearGradient([{ color: '#c0ece5', offset: 0 }, { color: '#61cfbe', offset: 1 }]), 2],
    [new LinearGradient([{ color: '#b5e0f4', offset: 0 }, { color: '#46b1e3', offset: 1 }]), 1]
  ])
  .strokeWidth(18)
```

### 单段渐变仪表盘

```typescript
Gauge({ value: 50, min: 1, max: 100 })
  .startAngle(225)
  .endAngle(135)
  .colors(new LinearGradient([
    { color: '#e84026', offset: 0 },
    { color: '#f7ce00', offset: 0.6 },
    { color: '#64bb5c', offset: 1 }
  ]))
  .strokeWidth(18)
```

### 带阴影的仪表盘

```typescript
Gauge({ value: 80 })
  .trackShadow({
    radius: 20,
    offsetX: 5,
    offsetY: 5
  })
```

### 自定义指示器

```typescript
Gauge({ value: 50, min: 1, max: 100 })
  .indicator({
    space: 10,
    icon: $r('app.media.indicator')  // SVG 格式图标
  })
  .startAngle(210)
  .endAngle(150)
  .strokeWidth(18)
```

### 不显示指示器

```typescript
Gauge({ value: 50 })
  .indicator(null)
```

### 带描述的仪表盘

```typescript
@Builder
descriptionBuilder() {
  Text('说明文本')
    .maxFontSize('30sp')
    .minFontSize('10.0vp')
    .fontColor('#fffa2a2d')
    .fontWeight(FontWeight.Medium)
    .width('100%')
    .height('100%')
    .textAlign(TextAlign.Center)
}

Gauge({ value: 50, min: 1, max: 100 })
  .description(this.descriptionBuilder)
```

### 带图片描述的仪表盘

```typescript
@Builder
descriptionBuilderImage() {
  Image($r('sys.media.ohos_ic_public_clock')).width(72).height(72)
}

Gauge({ value: 50, min: 1, max: 100 })
  .description(this.descriptionBuilderImage)
```

### 带子组件的仪表盘

```typescript
Gauge({ value: 50, min: 1, max: 100 }) {
  Column() {
    Text('50')
      .fontWeight(FontWeight.Medium)
      .maxFontSize('60.0vp')
      .minFontSize('30.0vp')
      .textAlign(TextAlign.Center)
    Text('辅助文本')
      .maxFontSize('16.0fp')
      .minFontSize('10.0vp')
  }
}
```

### 隐私敏感模式

```typescript
Gauge({ value: 60, min: 20, max: 100 })
  .startAngle(225)
  .endAngle(135)
  .colors(Color.Red)
  .strokeWidth(18)
  .privacySensitive(true)
```

### 自定义内容修饰器（API 12+）

```typescript
@Builder
function buildGauge(config: GaugeConfiguration) {
  Column({ space: 30 }) {
    Text('value: ' + config.value)
    Text('min: ' + config.min)
    Text('max: ' + config.max)
    Gauge({
      value: config.value,
      min: config.min,
      max: config.max
    }).width('50%')
  }
}

class MyGaugeStyle implements ContentModifier<GaugeConfiguration> {
  value: number = 0
  min: number = 0
  max: number = 0

  constructor(value: number, min: number, max: number) {
    this.value = value
    this.min = min
    this.max = max
  }

  applyContent(): WrappedBuilder<[GaugeConfiguration]> {
    return wrapBuilder(buildGauge)
  }
}

Gauge({ value: 20, min: 0, max: 100 })
  .contentModifier(new MyGaugeStyle(30, 10, 100))
```

---

## 文件引用

| 文件 | 行数 | 描述 |
|------|------|------|
| [gauge_pattern.h](frameworks/core/components_ng/pattern/gauge/gauge_pattern.h) | 234 | 主 Pattern 类定义 |
| [gauge_pattern.cpp](frameworks/core/components_ng/pattern/gauge/gauge_pattern.cpp) | 507 | Pattern 实现 |
| [gauge_model_ng.h](frameworks/core/components_ng/pattern/gauge/gauge_model_ng.h) | 94 | NG Model 接口 |
| [gauge_model_ng.cpp](frameworks/core/components_ng/pattern/gauge/gauge_model_ng.cpp) | 471 | NG Model 实现 |
| [gauge_layout_algorithm.cpp](frameworks/core/components_ng/pattern/gauge/gauge_layout_algorithm.cpp) | 399 | 布局计算 |
| [gauge_modifier.cpp](frameworks/core/components_ng/pattern/gauge/gauge_modifier.cpp) | ~1500+ | 绘制逻辑 |
| [gauge_paint_property.h](frameworks/core/components_ng/pattern/gauge/gauge_paint_property.h) | 312 | 绘制属性 |
| [gauge_theme.h](frameworks/core/components_ng/pattern/gauge/gauge_theme.h) | 175 | 主题定义 |
| [gauge_dynamic_modifier.cpp](frameworks/core/components_ng/pattern/gauge/bridge/gauge_dynamic_modifier.cpp) | 393 | 动态修饰器 |
| [gauge_static_modifier.cpp](frameworks/core/components_ng/pattern/gauge/bridge/gauge_static_modifier.cpp) | 846 | 静态修饰器 |

---

## 测试要点

### 单元测试要点

1. **Pattern 层测试**：
   - `OnModifyDone()` 各种分支覆盖
   - `OnDirtyLayoutWrapperSwap()` 返回值测试
   - 子节点初始化（description, limitValueText, indicator）
   - 颜色模式变更处理

2. **Model 层测试**：
   - `Create()` 参数验证
   - `SetValue()` 边界值测试
   - `SetGradientColors()` 类型设置
   - 资源对象更新

3. **LayoutAlgorithm 测试**：
   - `MeasureContent()` 各种约束条件
   - 子节点 Measure/Layout
   - 极值文本宽度计算

4. **Modifier 测试**：
   - 三种类型绘制分支
   - 阴影绘制
   - 指示器绘制（默认/图片）

### 分支覆盖关键点

1. **OnModifyDone 分支**：
   - API 版本判断 (`< API 11`)
   - `isShowIndicator` 条件
   - `isShowLimitValue` 条件
   - `hasGradientColors` 条件
   - 子节点 ID 存在性检查

2. **颜色模式变更分支**：
   - `useJsLinearGradient` 检查
   - `colorModeInit` 比较
   - 暗色资源存在性检查
   - 单色/渐变色处理

3. **图片加载分支**：
   - SVG 类型检查
   - 加载成功/失败处理
   - 数据就绪回调

---

*英文版本请参阅 [CLAUDE.md](../../frameworks/core/components_ng/pattern/gauge/CLAUDE.md)*
