# Hyperlink Component Knowledge Base

> **文档版本**: v1.0
> **更新时间**: 2026-02-02
> **源代码版本**: OpenHarmony ace_engine (master branch)
> **组件标签**: `V2::HYPERLINK_ETS_TAG`

---

## 目录

1. [概述](#概述)
2. [目录结构](#目录结构)
3. [核心类层次](#核心类层次)
4. [Pattern 层](#pattern-层)
5. [Model 层](#model-层)
6. [属性系统](#属性系统)
7. [主题系统](#主题系统)
8. [桥接层](#桥接层)
9. [执行流程](#执行流程)
10. [完整 API 列表](#完整-api-列表)
11. [关键实现细节](#关键实现细节)
12. [使用示例](#使用示例)

---

## 概述

### 组件定位

**Hyperlink 组件**是 OpenHarmony ArkUI 框架中的超链接文本组件，用于显示可点击的链接文本并提供跳转功能。它提供：
- 可点击的链接文本显示
- 支持自定义链接地址和显示内容
- 鼠标悬停/点击状态变化（下划线、颜色变化）
- 支持键盘导航（Enter/Space 激活）
- 支持拖拽功能
- 支持禁用状态
- 继承自 TextPattern，复用文本渲染能力

### 子组件

Hyperlink 组件**不支持子组件**。

### API 版本支持

- **初始版本**: API version 10
- **原子化服务 API**: 暂未明确支持

### 技术栈

- **前端**: ArkTS/JavaScript
- **桥接层**: HyperlinkModelNG
- **核心层**: NG Pattern Architecture（继承自 TextPattern）
- **渲染层**: Rosen + Skia

### 代码规模

- 总文件数: 约 20 个文件
- 核心代码: 约 1,500+ 行 C++ 代码
- 3 个架构层

### 设计模式

Hyperlink 组件采用 **NG Pattern Architecture** + **继承模式**：

```
前端 (ArkTS)
    ↓ (桥接层)
HyperlinkModelNG (hyperlink_model_ng.cpp)
    ↓ (NG Pattern 层)
HyperlinkPattern (继承 TextPattern)
    ↓ (文本渲染)
TextPattern → RenderNode → 显示
```

---

## 目录结构

```
frameworks/core/components_ng/pattern/hyperlink/
├── hyperlink_pattern.h/cpp           # 主 Pattern 逻辑
├── hyperlink_model.h                 # Model 接口定义
├── hyperlink_model_ng.h/cpp          # NG Model 实现
├── hyperlink_model_static.h/cpp      # 静态 Model（用于 ArkTS）
├── hyperlink_layout_property.h       # 布局属性
└── bridge/                           # 桥接层
    ├── hyperlink_dynamic_modifier.cpp    # ArkTS 动态修饰器
    ├── hyperlink_static_modifier.cpp     # 静态 C API 修饰器
    ├── hyperlink_dynamic_module.h/cpp    # 动态模块
    └── hyperlink_model_impl.h/cpp        # Model 实现

frameworks/core/components/hyperlink/  # 旧版组件（兼容）
├── hyperlink_component.h/cpp
├── hyperlink_element.h
├── render_hyperlink.h/cpp
├── hyperlink_theme.h                 # 主题定义
└── hyperlink_resources.h/cpp

frameworks/bridge/declarative_frontend/ark_modifier/src/
└── hyperlink_modifier.ts             # ArkTS 修饰器

frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/generated/component/
└── hyperlink.ets                     # 生成的 ArkTS 组件
```

---

## 核心类层次

```
TextPattern (基类)
    ↓
HyperlinkPattern
    ├── Creates: HyperlinkLayoutProperty
    └── 继承 TextPattern 的文本渲染能力

HyperlinkModel (抽象接口)
    ↓
HyperlinkModelNG (实现)
    └── 静态方法用于 FrameNode 操作

HyperlinkLayoutProperty
    ↓
TextLayoutProperty (基类)
    └── 添加 Color 和 Address 属性
```

---

## Pattern 层

### HyperlinkPattern 类

**位置**: [hyperlink_pattern.h](frameworks/core/components_ng/pattern/hyperlink/hyperlink_pattern.h)

**类定义**:
```cpp
class HyperlinkPattern : public TextPattern {
public:
    // Factory methods
    RefPtr<LayoutProperty> CreateLayoutProperty() override;

    // Lifecycle methods
    void OnAttachToFrameNode() override;
    void OnDetachFromFrameNode(FrameNode* node) override;
    void OnAttachToMainTree() override;
    void OnDetachFromMainTree() override;
    void OnModifyDone() override;

    // Drag support
    void EnableDrag();
    bool DefaultSupportDrag() override;

    // Focus pattern
    FocusPattern GetFocusPattern() const override;

    // Property updates
    void UpdatePropertyImpl(const std::string& key, RefPtr<PropertyValueBase> value) override;

private:
    // Link navigation
    void LinkToAddress();

    // Event initialization
    void InitClickEvent(const RefPtr<GestureEventHub>& gestureHub) override;
    void InitInputEvent(const RefPtr<InputEventHub>& inputHub);
    void InitTouchEvent(const RefPtr<GestureEventHub>& gestureHub);
    void InitLongPressEvent(const RefPtr<GestureEventHub>& gestureHub);
    void InitOnKeyEvent(const RefPtr<FocusHub>& focusHub);

    // Event handlers
    void OnHoverEvent(bool isHovered);
    void OnMouseEvent(MouseInfo& info);
    void OnTouchEvent(const TouchEventInfo& info);
    bool OnKeyEvent(const KeyEvent& event);

    // Multi-thread support
    void OnAttachToFrameNodeMultiThread();
    void OnAttachToMainTreeMultiThread();
    void OnDetachFromMainTreeMultiThread();
    void OnDetachFromFrameNodeMultiThread(FrameNode* frameNode);

    // State tracking
    bool isLinked_ = false;
    bool isTouchPreventDefault_ = false;
    RefPtr<TouchEventImpl> onTouchEvent_;
    RefPtr<InputEvent> onHoverEvent_;
    RefPtr<InputEvent> onMouseEvent_;
    RefPtr<ClickEvent> clickListener_;
};
```

### 关键职责

1. **事件处理**:
   - 点击事件：触发链接跳转
   - 触摸事件：按下/抬起时的状态变化
   - 悬停事件：鼠标悬停时的样式变化
   - 键盘事件：Enter/Space 键激活

2. **样式管理**:
   - 未访问状态：无下划线，默认颜色
   - 悬停状态：下划线，默认颜色
   - 按下状态：下划线，触摸颜色
   - 已访问状态：下划线，访问后颜色

3. **拖拽支持**:
   - 创建 Udmf 链接记录
   - 设置拖拽数据

4. **字体管理**:
   - 添加/移除字体节点

---

## Model 层

### HyperlinkModel (抽象接口)

**位置**: [hyperlink_model.h](frameworks/core/components_ng/pattern/hyperlink/hyperlink_model.h)

```cpp
class ACE_FORCE_EXPORT HyperlinkModel {
public:
    static HyperlinkModel* GetInstance();

    // Core configuration
    virtual void Create(const std::string& address, const std::string& content) = 0;
    virtual void Pop() = 0;

    // Appearance
    virtual void SetColor(const Color& value) = 0;
    virtual void SetDraggable(bool draggable) = 0;

    // Response region
    virtual void SetResponseRegion(bool isUserSetResponseRegion) = 0;

private:
    static std::unique_ptr<HyperlinkModel> instance_;
    static std::mutex mutex_;
};
```

### HyperlinkModelNG (实现)

**位置**: [hyperlink_model_ng.h](frameworks/core/components_ng/pattern/hyperlink/hyperlink_model_ng.h)

**关键静态方法**:
- `CreateFrameNode(const std::string& address, const std::string& content)`
- `SetColor(FrameNode* frameNode, const Color& value)`
- `SetDraggable(FrameNode* frameNode, bool draggable)`
- `SetResponseRegion(FrameNode* frameNode, bool isUserSetResponseRegion)`
- `SetResponseRegion(FrameNode* frameNode, const std::vector<DimensionRect>& regions, bool isUserSetResponseRegion)`

**创建流程** (hyperlink_model_ng.cpp:23-39):
```cpp
void HyperlinkModelNG::Create(const std::string& address, const std::string& content)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto hyperlinkNode = FrameNode::GetOrCreateFrameNode(
        V2::HYPERLINK_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<HyperlinkPattern>(); });

    stack->Push(hyperlinkNode);
    SetTextStyle(hyperlinkNode, content, address);

    auto pipeline = PipelineContext::GetCurrentContext();
    auto draggable = pipeline->GetDraggable<HyperlinkTheme>();
    SetDraggable(draggable);
}
```

---

## 属性系统

### HyperlinkLayoutProperty

**位置**: [hyperlink_layout_property.h](frameworks/core/components_ng/pattern/hyperlink/hyperlink_layout_property.h)

```cpp
class ACE_EXPORT HyperlinkLayoutProperty : public TextLayoutProperty {
public:
    RefPtr<LayoutProperty> Clone() const override;
    void Reset() override;
    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override;
    void ToTreeJson(std::unique_ptr<JsonValue>& json, const InspectorConfig& config) const override;

    // Properties
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Color, Color, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Address, std::string, PROPERTY_UPDATE_NORMAL);
};
```

### 属性说明

| 属性 | 类型 | 更新策略 | 描述 |
|------|------|----------|------|
| Color | Color | PROPERTY_UPDATE_MEASURE | 链接文本颜色 |
| Address | std::string | PROPERTY_UPDATE_NORMAL | 链接地址 URL |

**继承自 TextLayoutProperty 的属性**:
- Content: 显示内容（文本）
- TextColor: 文本颜色（与 Color 属性同步）
- TextDecoration: 文本装饰（下划线）
- FontSize: 字体大小
- FontWeight: 字体粗细
- TextOverflow: 文本溢出处理
- AdaptMinFontSize/AdaptMaxFontSize: 自适应字体大小

### ToJsonValue 实现

```cpp
void HyperlinkLayoutProperty::ToJsonValue(...) const override
{
    // API 18+: 从主题获取默认颜色
    if (host->GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
        if (propColor_.has_value()) {
            json->PutExtAttr("color", propColor_.value().ColorToString().c_str(), filter);
        } else {
            auto theme = themeManager->GetTheme<HyperlinkTheme>();
            json->PutExtAttr("color", theme->GetTextColor().ColorToString().c_str(), filter);
        }
    } else {
        // API 10-17: 默认蓝色
        json->PutExtAttr("color", propColor_.value_or(Color::BLUE).ColorToString().c_str(), filter);
    }
    json->PutExtAttr("address", propAddress_.value_or("").c_str(), filter);
}
```

---

## 主题系统

### HyperlinkTheme

**位置**: [hyperlink_theme.h](frameworks/core/components/hyperlink/hyperlink_theme.h)

**默认值**:

```cpp
// 文本颜色（默认蓝色）
textColor_ = Color(0xff007dff);

// 触摸颜色（半透明灰色）
textTouchedColor_ = Color(0x19182431);

// 已访问颜色（半透明深灰色）
textLinkedColor_ = Color(0x66182431);

// 禁用状态不透明度
opacity_ = 0.0;

// 禁用颜色 = text_color * opacity
textDisabledColor_ = Color(0xff007dff).BlendOpacity(0.0);

// 聚焦颜色
textFocusedColor_ = Color(0xff007dff);

// 文本装饰
textSelectedDecoration_ = TextDecoration::UNDERLINE;
textUnSelectedDecoration_ = TextDecoration::NONE;

// 可拖拽
draggable_ = false;
```

### Builder 模式

```cpp
class HyperlinkTheme::Builder {
    RefPtr<HyperlinkTheme> Build(const RefPtr<ThemeConstants>& themeConstants) const
    {
        RefPtr<HyperlinkTheme> theme = AceType::MakeRefPtr<HyperlinkTheme>();
        theme->textSelectedDecoration_ = TextDecoration::UNDERLINE;
        theme->textUnSelectedDecoration_ = TextDecoration::NONE;
        ParsePattern(themeConstants, theme);
        return theme;
    }

private:
    void ParsePattern(const RefPtr<ThemeConstants>& themeConstants, ...)
    {
        RefPtr<ThemeStyle> pattern = themeConstants->GetPatternByName(THEME_PATTERN_HYPERLINK);
        theme->textColor_ = pattern->GetAttr<Color>("text_color", Color(0xff007dff));
        theme->textTouchedColor_ = pattern->GetAttr<Color>("text_touched_color", Color(0x19182431));
        theme->textLinkedColor_ = pattern->GetAttr<Color>("text_linked_color", Color(0x66182431));
        theme->opacity_ = pattern->GetAttr<double>("text_disabled_opacity", 0.0);
        theme->draggable_ = StringUtils::StringToInt(
            pattern->GetAttr<std::string>("draggable", "0"));
    }
};
```

---

## 桥接层

### ArkTS 生成的组件

**位置**: [hyperlink.ets](frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/generated/component/hyperlink.ets)

```typescript
export interface HyperlinkAttribute extends CommonMethod {
    setHyperlinkOptions(address: string | Resource | undefined, content?: string | Resource): this
    color(value: Color | int32 | string | Resource | undefined): this
    attributeModifier(value: AttributeModifier<HyperlinkAttribute> | ...): this
}

export class ArkHyperlinkComponent extends ArkCommonMethodComponent implements HyperlinkAttribute {
    public setHyperlinkOptions(address: string | Resource | undefined, content?: string | Resource): this {
        this.getPeer()?.setHyperlinkOptionsAttribute(address_casted, content_casted)
        return this
    }

    public color(value: Color | int32 | string | Resource | undefined): this {
        this.getPeer()?.setColorAttribute(value_casted)
        return this
    }
}

@memo
export function HyperlinkImpl(
    style: ((attributes: HyperlinkAttribute) => void) | undefined,
    content_?: () => void,
): void { ... }
```

### Bridge Layer 文件

| 文件 | 用途 |
|------|------|
| `hyperlink_dynamic_modifier.cpp` | ArkTS 动态修饰器实现 |
| `hyperlink_static_modifier.cpp` | 静态 C API 修饰器实现 |
| `hyperlink_model_impl.h/cpp` | 旧版 Model 实现 |
| `hyperlink_dynamic_module.h/cpp` | 动态模块 |

---

## 执行流程

### 创建流程

```
ArkTS: Hyperlink('https://example.com', 'Click here')
    ↓
HyperlinkModelNG::Create(address, content)
    ↓
FrameNode::GetOrCreateFrameNode(V2::HYPERLINK_ETS_TAG, nodeId, HyperlinkPattern)
    ↓
Create HyperlinkLayoutProperty
    UpdateContent(content)
    UpdateAddress(address)
    UpdateTextColor(theme->GetTextColor())
    UpdateTextDecoration(theme->GetTextUnSelectedDecoration()) // NONE
    ↓
OnModifyDone()
    ↓
InitClickEvent() - 添加点击监听
InitTouchEvent() - 添加触摸监听
InitInputEvent() - 添加鼠标悬停监听
InitOnKeyEvent() - 添加键盘监听
    ↓
Measure (继承自 TextPattern)
    ↓
Layout (继承自 TextPattern)
    ↓
Paint (继承自 TextPattern)
```

### 点击跳转流程

```
用户点击 Hyperlink
    ↓
ClickEvent 触发
    ↓
HyperlinkPattern::LinkToAddress()
    ↓
更新样式：
    UpdateTextColor(BlendColor(textLinkedColor))
    UpdateTextDecoration(UNDERLINE)
    ↓
PipelineContext::HyperlinkStartAbility(address)
    ↓
系统打开链接
```

### 触摸事件流程

```
用户触摸屏幕
    ↓
TouchEventInfo 触发
    ↓
OnTouchEvent(TouchType::DOWN)
    ↓
UpdateTextDecoration(UNDERLINE)
UpdateTextColor(textTouchedColor)
    ↓
OnTouchEvent(TouchType::UP)
    ↓
UpdateTextDecoration(NONE)
UpdateTextColor(defaultColor)
```

### 悬停事件流程

```
鼠标移入
    ↓
OnHoverEvent(true)
    ↓
ChangeMouseStyle(HAND_POINTING)
UpdateTextDecoration(UNDERLINE)
UpdateTextDecorationColor(defaultColor)
    ↓
鼠标移出
    ↓
OnHoverEvent(false)
    ↓
ChangeMouseStyle(DEFAULT)
UpdateTextDecoration(NONE)
```

### 拖拽流程

```
用户开始拖拽
    ↓
DragStart 事件触发
    ↓
EnableDrag() 设置的回调执行
    ↓
创建 UnifiedData
    添加 LinkRecord: address + content
    ↓
设置 extraInfo: JSON { url, title }
    ↓
返回 DragDropInfo
```

---

## 完整 API 列表

### 创建 API

| API | 描述 | 位置 |
|-----|-------------|----------|
| `Create(const std::string& address, const std::string& content)` | 创建超链接 | hyperlink_model_ng.cpp:23 |
| `CreateFrameNode(const std::string& address, const std::string& content)` | 静态创建方法 | hyperlink_model_ng.cpp:41 |

### 外观 API

| API | 描述 | 位置 |
|-----|-------------|----------|
| `SetColor(const Color& value)` | 设置文本颜色 | hyperlink_model_ng.cpp:60 |
| `SetColor(FrameNode* frameNode, const Color& value)` | 静态设置颜色 | hyperlink_model_ng.cpp:106 |

### 拖拽 API

| API | 描述 | 位置 |
|-----|-------------|----------|
| `SetDraggable(bool draggable)` | 设置是否可拖拽 | hyperlink_model_ng.cpp:94 |
| `SetDraggable(FrameNode* frameNode, bool draggable)` | 静态设置可拖拽 | hyperlink_model_ng.cpp:113 |

### 响应区域 API

| API | 描述 | 位置 |
|-----|-------------|----------|
| `SetResponseRegion(bool isUserSetResponseRegion)` | 设置用户自定义响应区域标志 | hyperlink_model_ng.cpp:124 |
| `SetResponseRegion(FrameNode* frameNode, bool isUserSetResponseRegion)` | 静态设置响应区域标志 | hyperlink_model_ng.cpp:131 |
| `SetResponseRegion(FrameNode*, const vector<DimensionRect>&, bool)` | 设置响应区域 | hyperlink_model_ng.cpp:138 |

---

## 关键实现细节

### 1. 状态颜色处理

Hyperlink 有多种状态颜色（hyperlink_pattern.cpp:169-195）：

```cpp
// 未访问状态
color = theme->GetTextColor(); // 0xff007dff (蓝色)
textDecoration = NONE;

// 悬停状态
color = theme->GetTextColor();
textDecoration = UNDERLINE;

// 按下状态
color = theme->GetTextColor().BlendColor(theme->GetTextTouchedColor()); // 混合半透明灰色
textDecoration = UNDERLINE;

// 已访问状态
color = theme->GetTextColor().BlendColor(theme->GetTextLinkedColor()); // 混合半透明深灰色
textDecoration = UNDERLINE;
```

### 2. 禁用状态处理

禁用时应用不透明度（hyperlink_pattern.cpp:147-167）：

```cpp
auto enabled = hub->IsEnabled();
if (!enabled) {
    auto disabledColor = hyperlinkLayoutProperty->GetColor()
        .value_or(theme->GetTextColor())
        .BlendOpacity(theme->GetOpacity());
    hyperlinkLayoutProperty->UpdateTextColor(disabledColor);
    renderContext->UpdateForegroundColor(disabledColor);
}
```

### 3. 链接跳转

实际跳转通过 PipelineContext 实现（hyperlink_pattern.cpp:193）：

```cpp
void HyperlinkPattern::LinkToAddress()
{
    isLinked_ = true; // 标记为已访问
    // 更新样式为已访问状态
    hyperlinkLayoutProperty->UpdateTextColor(
        hyperlinkLayoutProperty->GetColor()
            .value_or(color)
            .BlendColor(theme->GetTextLinkedColor()));
    hyperlinkLayoutProperty->UpdateTextDecoration(UNDERLINE);

    auto address = hyperlinkLayoutProperty->GetAddress().value_or("");
    pipeline->HyperlinkStartAbility(address); // 系统调用打开链接
}
```

### 4. 阻止默认行为

如果用户阻止了默认行为，则不会跳转（hyperlink_pattern.cpp:285-295）：

```cpp
auto clickAfterCallback = [weak = WeakClaim(this)](GestureEvent& info) {
    auto hyperlinkPattern = weak.Upgrade();
    if (!info.IsPreventDefault() && !hyperlinkPattern->isTouchPreventDefault_) {
        hyperlinkPattern->LinkToAddress();
    }
    hyperlinkPattern->isTouchPreventDefault_ = false;
};
```

### 5. 响应区域支持

Hyperlink 支持自定义响应区域，用于处理部分区域可点击的场景：

```cpp
void HyperlinkModelNG::SetResponseRegion(
    FrameNode* frameNode, const std::vector<DimensionRect>& regions, bool isUserSetResponseRegion)
{
    auto textPattern = frameNode->GetPattern<TextPattern>();
    auto gesture = frameNode->GetOrCreateGestureEventHub();
    gesture->SetResponseRegion(regions);
    textPattern->SetIsUserSetResponseRegion(isUserSetResponseRegion);
}
```

### 6. 拖拽数据格式

拖拽时创建 Udmf 链接记录（hyperlink_pattern.cpp:90-122）：

```cpp
auto dragStart = [](const RefPtr<DragEvent>& event, ...) -> DragDropInfo {
    DragDropInfo info;
    // 创建 JSON extraInfo
    auto json = JsonUtil::Create(true);
    json->Put("url", address.c_str());
    json->Put("title", content.c_str());
    info.extraInfo = json->ToString();

    // 创建 UnifiedData
    RefPtr<UnifiedData> unifiedData = UdmfClient::GetInstance()->CreateUnifiedData();
    UdmfClient::GetInstance()->AddLinkRecord(unifiedData, address, content);
    event->SetData(unifiedData);
    return info;
};
```

### 7. 键盘导航

支持 Enter 和 Space 键激活链接（hyperlink_pattern.cpp:307-317）：

```cpp
bool HyperlinkPattern::OnKeyEvent(const KeyEvent& event)
{
    if (event.action != KeyAction::DOWN) {
        return false;
    }
    if (event.code == KeyCode::KEY_SPACE || event.code == KeyCode::KEY_ENTER) {
        LinkToAddress();
        return true; // 消费事件
    }
    return false;
}
```

### 8. 鼠标样式管理

悬停时切换为手型指针（hyperlink_pattern.cpp:319-348）：

```cpp
void HyperlinkPattern::OnHoverEvent(bool isHovered)
{
    if (isHovered) {
        pipeline->SetMouseStyleHoldNode(frameId);
        pipeline->ChangeMouseStyle(frameId, MouseFormat::HAND_POINTING);
        // 更新下划线样式
    } else {
        pipeline->ChangeMouseStyle(frameId, MouseFormat::DEFAULT);
        pipeline->FreeMouseStyleHoldNode(frameId);
    }
}
```

---

## 使用示例

### 基础 Hyperlink

```typescript
Hyperlink('https://www.example.com', 'Click here')
```

### 带颜色的 Hyperlink

```typescript
Hyperlink('https://www.example.com', 'Visit Example')
  .color(Color.Red)
```

### 禁用状态的 Hyperlink

```typescript
Hyperlink('https://www.example.com', 'Disabled Link')
  .enabled(false)
```

### 带文本样式的 Hyperlink

```typescript
Hyperlink('https://www.example.com', 'Styled Link')
  .fontSize(20)
  .fontWeight(FontWeight.Bold)
  .color(Color.Blue)
```

### 完整示例

```typescript
@Entry
@Component
struct HyperlinkExample {
  build() {
    Column({ space: 20 }) {
      Text('Hyperlink 示例')
        .fontSize(24)

      Hyperlink('https://www.example.com', '示例网站链接')
        .fontSize(18)
        .color('#007DFF')

      Hyperlink('https://www.example.org', '示例链接')
        .fontSize(16)
        .color(Color.Green)

      Hyperlink('https://www.example.net', '示例网络链接')
        .fontSize(16)
        .color(Color.Orange)
    }
    .width('100%')
    .height('100%')
    .padding(20)
  }
}
```

---

## 文件引用

| 文件 | 行数 | 描述 |
|------|-------|-------------|
| [hyperlink_pattern.h](frameworks/core/components_ng/pattern/hyperlink/hyperlink_pattern.h) | 90 | 主 Pattern 类定义 |
| [hyperlink_pattern.cpp](frameworks/core/components_ng/pattern/hyperlink/hyperlink_pattern.cpp) | 419 | Pattern 实现 |
| [hyperlink_model_ng.h](frameworks/core/components_ng/pattern/hyperlink/hyperlink_model_ng.h) | 44 | NG Model 接口 |
| [hyperlink_model_ng.cpp](frameworks/core/components_ng/pattern/hyperlink/hyperlink_model_ng.cpp) | 150 | NG Model 实现 |
| [hyperlink_layout_property.h](frameworks/core/components_ng/pattern/hyperlink/hyperlink_layout_property.h) | 97 | 布局属性 |
| [hyperlink_theme.h](frameworks/core/components/hyperlink/hyperlink_theme.h) | 134 | 主题定义 |
| [hyperlink.ets](frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/generated/component/hyperlink.ets) | 197 | ArkTS 生成组件 |

---

*中文版本文档*
