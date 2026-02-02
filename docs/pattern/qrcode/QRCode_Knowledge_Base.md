# QRCode 组件知识库

## 目录

- [1. 组件概述](#1-组件概述)
- [2. 目录结构](#2-目录结构)
- [3. 架构设计](#3-架构设计)
- [4. Pattern 层](#4-pattern-层)
- [5. Model 层](#5-model-层)
- [6. Property 层](#6-property-层)
- [7. Modifier 层](#7-modifier-层)
- [8. 布局算法](#8-布局算法)
- [9. 绘制流程](#9-绘制流程)
- [10. 生命周期](#10-生命周期)
- [11. Bridge 层](#11-bridge-层)
- [12. 测试覆盖](#12-测试覆盖)

---

## 1. 组件概述

**QRCode** 是 OpenHarmony ACE Engine 中用于生成和显示二维码的组件。

### 核心功能

- 将字符串内容编码为二维码图像
- 支持自定义二维码颜色和背景色
- 支持内容透明度设置
- 支持主题配置和系统颜色变化响应
- 始终保持正方形布局

### 技术依赖

- **qrcodegen 库**: 用于二维码编码生成 (`qrcodegen.hpp`)
- **RSBitmap/RSImage**: 渲染子系统位图和图像
- **QrcodeTheme**: 主题配置管理

### 源码位置

```
frameworks/core/components_ng/pattern/qrcode/
```

---

## 2. 目录结构

```
components_ng/pattern/qrcode/
├── qrcode_pattern.h/cpp                    # 主 Pattern 类
├── qrcode_paint_property.h                 # 绘制属性定义
├── qrcode_layout_algorithm.h/cpp           # 布局算法
├── qrcode_paint_method.h/cpp               # 绘制方法
├── qrcode_modifier.h/cpp                   # 核心渲染 Modifier
├── qrcode_model.h                          # 抽象 Model 接口
├── qrcode_model_ng.h/cpp                   # NG Model 实现
├── qrcode_model_static.h/cpp               # 静态 Model 实现
├── qrcode_napi.h/cpp                       # NAPI 接口
├── qrcode_modifier.h/cpp                   # 通用 Modifier
├── arkui_qrcode.js                         # JavaScript 接口
└── bridge/                                 # Bridge 层
    ├── arkts_native_qrcode_bridge.h/cpp    # ArkTS Native Bridge
    ├── qrcode_dynamic_module.h/cpp         # 动态模块
    ├── qrcode_dynamic_modifier.cpp         # 动态 Modifier
    └── qrcode_static_modifier.cpp          # 静态 Modifier
```

---

## 3. 架构设计

### 3.1 四层架构

QRCode 组件遵循 NG 组件的标准四层架构：

```
┌─────────────────────────────────────────────┐
│  Model 层 (qrcode_model_*.h/cpp)            │
│  - 数据模型和创建接口                        │
│  - 属性设置 API                              │
└─────────────────────────────────────────────┘
                    ↓
┌─────────────────────────────────────────────┐
│  Pattern 层 (qrcode_pattern.h/cpp)          │
│  - 业务逻辑和生命周期管理                    │
│  - 协调 Model、Property、Modifier            │
└─────────────────────────────────────────────┘
                    ↓
┌─────────────────────────────────────────────┐
│  Property 层 (qrcode_paint_property.h)      │
│  - 绘制属性定义和存储                        │
│  - JSON 序列化                               │
└─────────────────────────────────────────────┘
                    ↓
┌─────────────────────────────────────────────┐
│  Modifier 层 (qrcode_modifier.h/cpp)        │
│  - 二维码位图生成                            │
│  - 实际绘制逻辑                              │
└─────────────────────────────────────────────┘
```

### 3.2 关键类关系

```
QRCodePattern
    ├── QRCodePaintProperty (绘制属性)
    ├── QRCodeLayoutAlgorithm (布局算法)
    ├── QRCodePaintMethod (绘制方法)
    │       └── QRCodeModifier (绘制执行)
    └── QRCodeTheme (主题)
```

---

## 4. Pattern 层

### 4.1 QRCodePattern 类

**位置**: `qrcode_pattern.h:31-77`

```cpp
class QRCodePattern : public Pattern
{
public:
    // 创建绘制属性
    RefPtr<PaintProperty> CreatePaintProperty() override;

    // 创建布局算法
    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override;

    // 创建绘制方法
    RefPtr<NodePaintMethod> CreateNodePaintMethod() override;

    // 支持父容器大小匹配
    bool IsEnableMatchParent() override;

    // 属性更新方法
    void UpdateQRCodeCreate(const std::string& value);
    void UpdateColor(const Color& color, bool isFristLoad = false);
    void UpdateBackgroundColor(const Color& color, bool isFristLoad = false);
    void UpdateContentOpacity(double opacity, bool isFristLoad = false);

private:
    void OnAttachToFrameNode() override;
    void OnModifyDone() override;
    void OnColorConfigurationUpdate() override;
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty,
                                   bool skipMeasure, bool skipLayout) override;

    float qrCodeSize_ = 0.0f;
    RefPtr<QRCodeModifier> qrCodeModifier_;
};
```

### 4.2 生命周期方法

#### OnAttachToFrameNode()

**位置**: `qrcode_pattern.cpp:24-30`

```cpp
void QRCodePattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetRenderContext()->SetClipToFrame(true);      // 裁剪到边界
    host->GetRenderContext()->UpdateBackgroundColor(Color::WHITE);  // 默认白色背景
}
```

**功能**:
- 设置裁剪到边界 (`SetClipToFrame`)
- 设置默认白色背景

#### OnModifyDone()

**位置**: `qrcode_pattern.cpp:45-58`

```cpp
void QRCodePattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    // 设置默认对齐方式为 CENTER
    if (layoutProperty->GetPositionProperty()) {
        layoutProperty->UpdateAlignment(
            layoutProperty->GetPositionProperty()->GetAlignment().value_or(Alignment::CENTER));
    } else {
        layoutProperty->UpdateAlignment(Alignment::CENTER);
    }
}
```

**功能**:
- 调用父类实现
- 设置默认对齐方式为 `Alignment::CENTER`

#### OnDirtyLayoutWrapperSwap()

**位置**: `qrcode_pattern.cpp:32-43`

```cpp
bool QRCodePattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty,
                                              bool skipMeasure, bool skipLayout)
{
    if (skipMeasure && skipLayout) {
        return false;
    }
    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto layoutAlgorithm = DynamicCast<QRCodeLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithm, false);
    qrCodeSize_ = layoutAlgorithm->GetQRCodeSize();  // 更新二维码尺寸
    return true;
}
```

**功能**:
- 在布局计算完成后更新 `qrCodeSize_`
- 返回 `true` 表示需要重新绘制

#### OnColorConfigurationUpdate()

**位置**: `qrcode_pattern.cpp:179-200`

```cpp
void QRCodePattern::OnColorConfigurationUpdate()
{
    if (!SystemProperties::ConfigChangePerform()) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContextWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<QrcodeTheme>();
    CHECK_NULL_VOID(theme);
    auto pops = host->GetPaintProperty<QRCodePaintProperty>();
    CHECK_NULL_VOID(pops);

    // 仅当用户未设置颜色时，使用主题颜色
    if (!pops->HasQRCodeColorSetByUser() ||
        (pops->HasQRCodeColorSetByUser() && !pops->GetQRCodeColorSetByUserValue())) {
        UpdateColor(theme->GetQrcodeColor(), false);
    }
    if (!pops->HasQRBackgroundColorSetByUser() ||
        (pops->HasQRBackgroundColorSetByUser() && !pops->GetQRBackgroundColorSetByUserValue())) {
        UpdateBackgroundColor(theme->GetBackgroundColor(), false);
    }
}
```

**功能**:
- 响应系统颜色主题变化
- 只更新用户未显式设置的颜色属性

### 4.3 属性更新方法

#### UpdateColor()

**位置**: `qrcode_pattern.cpp:123-142`

```cpp
void QRCodePattern::UpdateColor(const Color& color, bool isFristLoad)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto paintProperty = host->GetPaintProperty<QRCodePaintProperty>();
    CHECK_NULL_VOID(paintProperty);

    if (pipelineContext->IsSystmColorChange() || isFristLoad) {
        paintProperty->UpdateColor(color);
        auto renderContext = host->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        renderContext->UpdateForegroundColor(color);
        renderContext->ResetForegroundColorStrategy();
        renderContext->UpdateForegroundColorFlag(true);
    }
    if (host->GetRerenderable()) {
        host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
}
```

**更新流程**:
1. 检查是否为系统颜色变化或首次加载
2. 更新 PaintProperty 中的颜色
3. 更新 RenderContext 中的前景色
4. 标记节点为脏节点触发重绘

#### UpdateBackgroundColor()

**位置**: `qrcode_pattern.cpp:144-161`

```cpp
void QRCodePattern::UpdateBackgroundColor(const Color& color, bool isFristLoad)
{
    // ... 类似 UpdateColor
    paintProperty->UpdateBackgroundColor(color);
    renderContext->UpdateBackgroundColor(color);
}
```

#### UpdateContentOpacity()

**位置**: `qrcode_pattern.cpp:163-177`

```cpp
void QRCodePattern::UpdateContentOpacity(double opacity, bool isFristLoad)
{
    // ... 检查逻辑
    paintProperty->UpdateOpacity(opacity);
    // ... 标记脏节点
}
```

---

## 5. Model 层

### 5.1 QRCodeModel (抽象接口)

**位置**: `qrcode_model.h`

定义了 QRCode 组件的标准接口。

### 5.2 QRCodeModelNG

**位置**: `qrcode_model_ng.h:23-39`

```cpp
class QRCodeModelNG : public OHOS::Ace::QRCodeModel
{
public:
    void Create(const std::string& value) override;
    void SetQRCodeColor(const Color& color) override;
    void SetQRBackgroundColor(const Color& color) override;
    void SetContentOpacity(const double opacity) override;
    void CreateWithResourceObj(QRCodeResourceType jsResourceType,
                               const RefPtr<ResourceObject>& resObj) override;

    // 静态方法，用于直接操作 FrameNode
    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId);
    static void SetQRCodeValue(FrameNode* frameNode, const std::string& value);
    static void SetQRCodeColor(FrameNode* frameNode, const Color& color);
    static void SetQRBackgroundColor(FrameNode* frameNode, const Color& color);
    static void SetContentOpacity(FrameNode* frameNode, const double opacity);
};
```

### 5.3 Create() 方法

**位置**: `qrcode_model_ng.cpp:29-44`

```cpp
void QRCodeModelNG::Create(const std::string& value)
{
    auto* stack = ViewStackProcessor::GetInstance();
    int32_t nodeId = (stack == nullptr ? 0 : stack->ClaimNodeId());
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", QRCODE_ETS_TAG, nodeId);

    // 创建或获取 FrameNode
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        QRCODE_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<QRCodePattern>(); });
    ViewStackProcessor::GetInstance()->Push(frameNode);

    // 重置用户设置标记
    auto pros = frameNode->GetPaintProperty<QRCodePaintProperty>();
    if (pros) {
        pros->ResetQRCodeColorSetByUser();
        pros->ResetQRBackgroundColorSetByUser();
    }
    ACE_UPDATE_PAINT_PROPERTY(QRCodePaintProperty, Value, value);
}
```

**创建流程**:
1. 从 ViewStackProcessor 获取或创建 nodeId
2. 创建 FrameNode 并关联 QRCodePattern
3. 将 FrameNode 压入 ViewStack
4. 重置颜色用户设置标记
5. 更新二维码内容值

### 5.4 SetQRCodeColor() 方法

**位置**: `qrcode_model_ng.cpp:46-53`

```cpp
void QRCodeModelNG::SetQRCodeColor(const Color& color)
{
    ACE_UPDATE_PAINT_PROPERTY(QRCodePaintProperty, Color, color);
    ACE_UPDATE_RENDER_CONTEXT(ForegroundColor, color);
    ACE_RESET_RENDER_CONTEXT(RenderContext, ForegroundColorStrategy);
    ACE_UPDATE_RENDER_CONTEXT(ForegroundColorFlag, true);
    ACE_UPDATE_PAINT_PROPERTY(QRCodePaintProperty, QRCodeColorSetByUser, true);
}
```

**关键点**: 设置 `QRCodeColorSetByUser` 标志为 `true`，防止主题覆盖

### 5.5 资源对象支持

QRCodeModelNG 支持通过资源对象动态更新属性：

- `CreateWithResourceObj()`: 根据资源类型更新相应属性
- `HandleCreateResource()`: 处理内容资源
- `HandleColorResource()`: 处理颜色资源
- `HandleBackgroundColorResource()`: 处理背景色资源
- `HandleContentOpacityResource()`: 处理透明度资源

**位置**: `qrcode_model_ng.cpp:100-179`

---

## 6. Property 层

### 6.1 QRCodePaintProperty 类

**位置**: `qrcode_paint_property.h:28-80`

```cpp
class QRCodePaintProperty : public PaintProperty
{
public:
    // 属性克隆
    RefPtr<PaintProperty> Clone() const override;

    // 属性重置
    void Reset() override;

    // JSON 序列化（用于 Devtools）
    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override;

    // 属性定义
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Value, std::string, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Color, Color, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(BackgroundColor, Color, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Opacity, double, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(QRCodeColorSetByUser, bool, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(QRBackgroundColorSetByUser, bool, PROPERTY_UPDATE_RENDER);
};
```

### 6.2 属性说明

| 属性 | 类型 | 说明 |
|------|------|------|
| `Value` | `std::string` | 二维码内容字符串 |
| `Color` | `Color` | 二维码前景色 |
| `BackgroundColor` | `Color` | 二维码背景色 |
| `Opacity` | `double` | 内容透明度 (0.0-1.0) |
| `QRCodeColorSetByUser` | `bool` | 用户是否显式设置了前景色 |
| `QRBackgroundColorSetByUser` | `bool` | 用户是否显式设置了背景色 |

### 6.3 ToJsonValue() 实现

**位置**: `qrcode_paint_property.h:55-72`

```cpp
void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override
{
    PaintProperty::ToJsonValue(json, filter);
    if (filter.IsFastFilter()) {
        return;
    }
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    RefPtr<QrcodeTheme> qrCodeTheme = pipeline->GetTheme<QrcodeTheme>();
    CHECK_NULL_VOID(qrCodeTheme);

    json->PutExtAttr("value", propValue_.value_or("").c_str(), filter);
    json->PutExtAttr("color",
        propColor_.value_or(qrCodeTheme->GetQrcodeColor()).ColorToString().c_str(), filter);
    json->PutExtAttr("backgroundColor",
        propBackgroundColor_.value_or(qrCodeTheme->GetBackgroundColor()).ColorToString().c_str(), filter);
    json->PutExtAttr("opacity", propOpacity_.value_or(1.0f), filter);
}
```

---

## 7. Modifier 层

### 7.1 QRCodeModifier 类

**位置**: `qrcode_modifier.h:33-72`

```cpp
class QRCodeModifier : public ContentModifier
{
public:
    QRCodeModifier();
    void onDraw(DrawingContext& context) override;

    // 属性设置方法
    void SetQRCodeOpacity(float opacity);
    void SetQRCodeSize(float qrCodeSize);
    void SetQRCodeValue(const std::string& value);
    void SetPaintOffset(const OffsetF& paintOffset);
    void SetQRCodeColor(const Color& color);
    void SetQRCodeBackgroundColor(const Color& bgColor);

private:
    // 位图生成
    RSBitmap CreateBitMap(int32_t width, const qrcodegen::QrCode& qrCode,
                          const Color& color, const Color& backgroundColor) const;

    // 颜色转换
    uint32_t ConvertColorFromHighToLow(const Color& color) const;

    // 属性成员
    RefPtr<AnimatablePropertyFloat> opacity_;           // 支持动画的透明度
    RefPtr<PropertyFloat> qrCodeSize_;
    RefPtr<PropertyString> value_;
    RefPtr<PropertyOffsetF> paintOffset_;
    RefPtr<PropertyColor> color_;
    RefPtr<PropertyColor> backgroundColor_;
};
```

### 7.2 onDraw() 方法

**位置**: `qrcode_modifier.cpp:34-73`

```cpp
void QRCodeModifier::onDraw(DrawingContext& context)
{
    auto& canvas = context.canvas;
    auto opacity = opacity_->Get();
    auto qrCodeSize = qrCodeSize_->Get();
    auto value = value_->Get();
    auto paintOffset = paintOffset_->Get();
    auto color = color_->Get();
    auto backgroundColor = backgroundColor_->Get();

    // 使用 qrcodegen 库编码二维码
    auto qrCode = qrcodegen::QrCode::encodeText(value.c_str(), qrcodegen::QrCode::Ecc::LOW);

    // 验证有效性
    if (!qrCode.getFlag() || qrCode.getSize() == 0 || qrCodeSize <= 0 ||
        qrCodeSize < static_cast<float>(qrCode.getSize())) {
        TAG_LOGE(AceLogTag::ACE_QRCODE, "QRCodeSize is too small. QRCodeSize: %{public}f", qrCodeSize);
        return;
    }

    // 应用透明度
    color = color.BlendOpacity(opacity);

    // 创建位图
    auto bitMap = CreateBitMap(static_cast<int32_t>(qrCodeSize), qrCode, color, backgroundColor);

    // 构建图像
    RSImage image;
    image.BuildFromBitmap(bitMap);

    // 计算缩放
    int32_t blockCounts = static_cast<int32_t>(qrCodeSize) / qrCode.getSize();
    int32_t sizeInPixel = blockCounts * qrCode.getSize();
    if (sizeInPixel == 0) {
        return;
    }

    auto scale = qrCodeSize / sizeInPixel;

    // 绘制
    RSBrush brush;
    brush.SetAntiAlias(true);
    canvas.AttachBrush(brush);
    canvas.Save();
    canvas.Scale(scale, scale);
    canvas.DrawImage(image, paintOffset.GetX() / scale, paintOffset.GetY() / scale, RSSamplingOptions());
    canvas.DetachBrush();
    canvas.Restore();
}
```

**绘制流程**:
1. 获取所有属性值
2. 使用 qrcodegen 库编码字符串为 QrCode 对象
3. 验证二维码有效性
4. 应用透明度到颜色
5. 创建位图
6. 计算缩放比例
7. 绘制到画布

### 7.3 CreateBitMap() 方法

**位置**: `qrcode_modifier.cpp:75-110`

```cpp
RSBitmap QRCodeModifier::CreateBitMap(
    int32_t width, const qrcodegen::QrCode& qrCode, const Color& color, const Color& backgroundColor) const
{
    RSBitmap bitMap;
    RSBitmapFormat colorType = { RSColorType::COLORTYPE_RGBA_8888, RSAlphaType::ALPHATYPE_OPAQUE };
    if (!bitMap.Build(width, width, colorType)) {
        TAG_LOGW(AceLogTag::ACE_QRCODE, "rsBitmap build fail.");
        return bitMap;
    }

    void* rawData = bitMap.GetPixels();
    auto* data = reinterpret_cast<uint32_t*>(rawData);
    int32_t blockWidth = width / qrCode.getSize();
    int32_t maxWidth = 0;
    int32_t maxHeight = 0;

    // 绘制前景色模块
    for (int32_t i = 0; i < width; i++) {
        for (int32_t j = 0; j < width; j++) {
            if (qrCode.getModule(i / blockWidth, j / blockWidth)) {
                data[i * width + j] = ConvertColorFromHighToLow(color);
                maxWidth = i > maxWidth ? i : maxWidth;
                maxHeight = j > maxHeight ? j : maxHeight;
            }
        }
    }

    // API 12 之前需要填充背景色
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        return bitMap;
    }

    // 绘制背景色模块
    for (int32_t i = 0; i <= maxWidth; i++) {
        for (int32_t j = 0; j <= maxHeight; j++) {
            if (!qrCode.getModule(i / blockWidth, j / blockWidth)) {
                data[i * width + j] = ConvertColorFromHighToLow(backgroundColor);
            }
        }
    }
    return bitMap;
}
```

**关键逻辑**:
1. 创建 RGBA_8888 格式的位图
2. 遍历像素，根据 qrcode 模块设置前景色
3. API 12 之前版本需要手动填充背景色
4. 记录最大宽高用于限制背景填充范围

### 7.4 ConvertColorFromHighToLow()

**位置**: `qrcode_modifier.cpp:112-120`

```cpp
uint32_t QRCodeModifier::ConvertColorFromHighToLow(const Color& color) const
{
    BGRA convertedColor;
    convertedColor.argb.blue = color.GetBlue();
    convertedColor.argb.green = color.GetGreen();
    convertedColor.argb.red = color.GetRed();
    convertedColor.argb.alpha = color.GetAlpha();
    return convertedColor.value;
}
```

**功能**: 将 ACE Color 类型转换为 BGRA 格式的 32 位整数值

---

## 8. 布局算法

### 8.1 QRCodeLayoutAlgorithm 类

**位置**: `qrcode_layout_algorithm.h:30-51`

```cpp
class ACE_FORCE_EXPORT QRCodeLayoutAlgorithm : public BoxLayoutAlgorithm
{
public:
    std::optional<SizeF> MeasureContent(
        const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper) override;

    void Measure(LayoutWrapper* layoutWrapper) override;

    float GetQRCodeSize() const { return qrCodeSize_; }

private:
    Color color_ = Color::BLACK;
    Color backgroundColor_ = Color::WHITE;
    float qrCodeSize_ = 0.0f;
};
```

### 8.2 MeasureContent() 实现

**位置**: `qrcode_layout_algorithm.cpp:27-102`

```cpp
std::optional<SizeF> QRCodeLayoutAlgorithm::MeasureContent(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    // ... 获取主题和布局属性

    auto pipeline = PipelineContext::GetCurrentContext();
    auto qrcodeTheme = pipeline->GetTheme<QrcodeTheme>();
    Dimension defaultSize = qrcodeTheme->GetQrcodeDefaultSize();
    auto layoutPolicy = layoutProperty->GetLayoutPolicyProperty();

    if (pipeline->GetMinPlatformVersion() >= PLATFORM_VERSION_11) {
        // API 11+ 的尺寸计算逻辑
        // 1. 获取 padding
        // 2. 计算考虑 padding 后的默认尺寸
        // 3. 应用布局策略 (match/wrap/fix)
        // 4. 确保正方形 (width = height = min(width, height))

        auto qrCodeSize = std::min(width, height);
        qrCodeSize_ = qrCodeSize;
        return SizeF(qrCodeSize, qrCodeSize);
    } else {
        // API 11 之前的尺寸计算逻辑
        auto idealSize = CreateIdealSize(contentConstraint, Axis::HORIZONTAL, ...);
        if (LessNotEqual(idealSize.Width(), idealSize.Height())) {
            idealSize.SetHeight(idealSize.Width());
        } else if (LessNotEqual(idealSize.Height(), idealSize.Width())) {
            idealSize.SetWidth(idealSize.Height());
        }
        qrCodeSize_ = idealSize.Width();
        return idealSize;
    }
}
```

**布局策略**:

| 策略 | 行为 |
|------|------|
| `Match` | 使用父容器约束尺寸 |
| `Wrap` | 使用 min(默认尺寸, 父容器约束) |
| `Fix` | 使用默认尺寸 (theme.GetQrcodeDefaultSize()) |

**关键点**:
1. **API >= 11**: 考虑 padding，更精确的尺寸计算
2. **API < 11**: 简化的约束计算
3. **始终正方形**: `qrCodeSize = min(width, height)`

### 8.3 Measure() 实现

**位置**: `qrcode_layout_algorithm.cpp:104-135`

```cpp
void QRCodeLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    const auto& layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto layoutPolicy = layoutProperty->GetLayoutPolicyProperty();

    if (layoutPolicy.has_value() && layoutPolicy->IsFix()) {
        // Fix 策略的特殊处理
        auto contentConstraint = layoutProperty->GetLayoutConstraint();
        auto pipeline = PipelineContext::GetCurrentContext();
        auto qrcodeTheme = pipeline->GetTheme<QrcodeTheme>();
        Dimension defaultSize = qrcodeTheme->GetQrcodeDefaultSize();
        auto defaultHeight = defaultSize.ConvertToPx();
        OptionalSizeF qrcodeFrameSize = { defaultHeight, defaultHeight };

        // 应用用户指定尺寸
        if (contentConstraint->selfIdealSize.Width().has_value()) {
            qrcodeFrameSize.SetWidth(contentConstraint->selfIdealSize.Width().value());
        }
        if (contentConstraint->selfIdealSize.Height().has_value()) {
            qrcodeFrameSize.SetHeight(contentConstraint->selfIdealSize.Height().value());
        }

        // Wrap 策略使用默认尺寸
        if (layoutPolicy->IsWidthWrap()) {
            qrcodeFrameSize.SetWidth(defaultHeight);
        }
        if (layoutPolicy->IsHeightWrap()) {
            qrcodeFrameSize.SetHeight(defaultHeight);
        }

        layoutWrapper->GetGeometryNode()->SetFrameSize(qrcodeFrameSize.ConvertToSizeT());
    } else {
        BoxLayoutAlgorithm::Measure(layoutWrapper);
    }
}
```

---

## 9. 绘制流程

### 9.1 QRCodePaintMethod 类

**位置**: `qrcode_paint_method.h:28-47`

```cpp
class QRCodePaintMethod : public NodePaintMethod
{
public:
    QRCodePaintMethod(const WeakPtr<Pattern>& pattern, float qrCodeSize,
                      const RefPtr<QRCodeModifier>& qrCodeModifier)
        : pattern_(pattern), qrCodeSize_(qrCodeSize), qrCodeModifier_(qrCodeModifier)
    {}

    RefPtr<Modifier> GetContentModifier(PaintWrapper* paintWrapper) override
    {
        CHECK_NULL_RETURN(qrCodeModifier_, nullptr);
        return qrCodeModifier_;
    }

    void UpdateContentModifier(PaintWrapper* paintWrapper) override;

private:
    WeakPtr<Pattern> pattern_;
    float qrCodeSize_ = 0.0f;
    RefPtr<QRCodeModifier> qrCodeModifier_;
};
```

### 9.2 绘制调用链

```
Pattern::CreateNodePaintMethod()
    ↓
QRCodePaintMethod 构造
    ↓
PaintWrapper::GetContentModifier()
    ↓
QRCodeModifier::onDraw()
    ↓
qrcodegen::QrCode::encodeText() + CreateBitMap()
    ↓
Canvas::DrawImage()
```

---

## 10. 生命周期

### 10.1 完整生命周期

```
┌─────────────────────────────────────────────────────────┐
│ 1. 创建阶段                                              │
│    QRCodeModelNG::Create()                              │
│    → FrameNode::GetOrCreateFrameNode()                  │
│    → QRCodePattern 构造                                  │
│    → ViewStackProcessor::Push()                         │
└─────────────────────────────────────────────────────────┘
                         ↓
┌─────────────────────────────────────────────────────────┐
│ 2. 附加阶段                                              │
│    QRCodePattern::OnAttachToFrameNode()                 │
│    → SetClipToFrame(true)                               │
│    → UpdateBackgroundColor(WHITE)                       │
└─────────────────────────────────────────────────────────┘
                         ↓
┌─────────────────────────────────────────────────────────┐
│ 3. 属性设置阶段                                          │
│    SetQRCodeColor() / SetQRBackgroundColor() / ...      │
│    → ACE_UPDATE_PAINT_PROPERTY                          │
│    → MarkDirtyNode(PROPERTY_UPDATE_RENDER)              │
└─────────────────────────────────────────────────────────┘
                         ↓
┌─────────────────────────────────────────────────────────┐
│ 4. 修改完成阶段                                          │
│    QRCodePattern::OnModifyDone()                        │
│    → UpdateAlignment(CENTER)                            │
└─────────────────────────────────────────────────────────┘
                         ↓
┌─────────────────────────────────────────────────────────┐
│ 5. 布局阶段                                              │
│    QRCodeLayoutAlgorithm::MeasureContent()              │
│    QRCodeLayoutAlgorithm::Measure()                     │
└─────────────────────────────────────────────────────────┘
                         ↓
┌─────────────────────────────────────────────────────────┐
│ 6. 布局交换阶段                                          │
│    QRCodePattern::OnDirtyLayoutWrapperSwap()            │
│    → qrCodeSize_ = layoutAlgorithm->GetQRCodeSize()     │
└─────────────────────────────────────────────────────────┘
                         ↓
┌─────────────────────────────────────────────────────────┐
│ 7. 绘制阶段                                              │
│    QRCodePaintMethod::UpdateContentModifier()           │
│    QRCodeModifier::onDraw()                             │
│    → qrcodegen::QrCode::encodeText()                    │
│    → CreateBitMap()                                     │
│    → Canvas::DrawImage()                                │
└─────────────────────────────────────────────────────────┘
```

### 10.2 属性更新触发重绘

```
SetQRCodeColor(value)
    ↓
ACE_UPDATE_PAINT_PROPERTY
    ↓
PaintProperty::UpdateProperty
    ↓
FrameNode::MarkDirtyNode(PROPERTY_UPDATE_RENDER)
    ↓
RenderContext 需要更新
    ↓
下一帧绘制时 QRCodeModifier::onDraw() 被调用
```

---

## 11. Bridge 层

### 11.1 Bridge 层结构

```
bridge/
├── arkts_native_qrcode_bridge.h/cpp      # ArkTS Native 接口
├── qrcode_dynamic_module.h/cpp           # 动态加载模块
├── qrcode_dynamic_modifier.cpp           # 动态 Modifier
└── qrcode_static_modifier.cpp            # 静态 Modifier
```

### 11.2 动态加载支持

QRCode 组件支持动态模块加载，实现按需加载。

**QRCodeDynamicModule** 实现 `DynamicModule` 接口：
- 提供模块初始化和清理
- 支持运行时动态加载组件

### 11.3 NAPI 接口

**位置**: `qrcode_napi.h/cpp`

提供 Node.js API 绑定：
- `JsCreate()`: JavaScript 创建函数
- `JsColor()`: JavaScript 颜色设置函数
- `JsBackgroundColor()`: JavaScript 背景色设置函数

### 11.4 JavaScript 接口

**位置**: `arkui_qrcode.js`

```javascript
// ArkTS 中使用 QRCode 组件
QRCode.create("https://example.com")
    .color(Color.Black)
    .backgroundColor(Color.White)
    .opacity(1.0)
    .width(200)
    .height(200)
```

---

## 12. 测试覆盖

### 12.1 单元测试

**位置**: `test/unittest/core/pattern/qrcode/qrcode_test_ng.cpp`

测试覆盖包括：
- Pattern 生命周期方法
- 属性更新方法
- 布局算法计算
- 绘制方法调用

### 12.2 关键测试场景

| 测试场景 | 验证内容 |
|----------|----------|
| 创建测试 | FrameNode 和 Pattern 正确创建 |
| 颜色更新 | 前景色和背景色正确更新 |
| 透明度更新 | Opacity 属性正确应用 |
| 布局测试 | 正方形布局约束 |
| 主题变化 | 系统颜色变化响应 |
| 有效性验证 | 二维码尺寸过小处理 |

### 12.3 测试注意事项

1. **Mock 准备**: 需要 mock `PipelineContext` 和 `QrcodeTheme`
2. **边界条件**: 测试二维码尺寸为 0 或负值的情况
3. **平台差异**: 测试 API 11 前后不同的布局行为

---

## 附录

### A. 主题配置

QrcodeTheme 提供的默认配置：

| 属性 | 默认值 |
|------|--------|
| 默认尺寸 | 通常为 300x300 |
| 前景色 | 黑色 |
| 背景色 | 白色 |
| FocusStyleType | INNER_BORDER |
| FocusedColor | 主题指定 |

### B. 常见问题

**Q1: 为什么二维码始终是正方形？**

A: 在 `QRCodeLayoutAlgorithm::MeasureContent()` 中，最终返回 `SizeF(qrCodeSize, qrCodeSize)`，其中 `qrCodeSize = min(width, height)`。

**Q2: 如何处理超长字符串？**

A: qrcodegen 库会自动处理，但过长的字符串可能导致二维码过于密集。建议限制字符串长度或使用更高级别的纠错 (`Ecc::MEDIUM`, `Ecc::HIGH`)。

**Q3: API 11 前后有什么区别？**

A: API 11+ 更精确地处理 padding 对尺寸的影响，而 API 11 之前使用简化的计算方式。

### C. 相关文件索引

| 文件 | 关键内容 |
|------|----------|
| `qrcode_pattern.h:24-30` | OnAttachToFrameNode |
| `qrcode_pattern.cpp:45-58` | OnModifyDone |
| `qrcode_pattern.cpp:32-43` | OnDirtyLayoutWrapperSwap |
| `qrcode_pattern.cpp:179-200` | OnColorConfigurationUpdate |
| `qrcode_layout_algorithm.cpp:27-102` | MeasureContent |
| `qrcode_modifier.cpp:34-73` | onDraw |
| `qrcode_modifier.cpp:75-110` | CreateBitMap |
| `qrcode_model_ng.cpp:29-44` | Create 方法 |
| `qrcode_model_ng.cpp:46-53` | SetQRCodeColor |

### D. 版本历史

| 版本 | 日期 | 变更 |
|-----|------|------|
| v1.0 | 2026-02-02 | 初始版本 |

---

**文档结束**

> 本文档基于 OpenHarmony ace_engine 源码分析生成，如有错误或遗漏，欢迎指正。
