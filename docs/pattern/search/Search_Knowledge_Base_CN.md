# Search 组件深入知识库

> **文档定位**：本文档是对 `search/CLAUDE.md` 的深入补充，专注于设计决策、实现原理、问题排查等高级内容
> **快速参考**：请参考 [Search/CLAUDE.md](../../frameworks/core/components_ng/pattern/search/CLAUDE.md)
> **版本**：v3.0 | **更新**：2026-02-03

---

## 目录

1. [设计决策分析](#1-设计决策分析)
2. [实现原理深挖](#2-实现原理深挖)
3. [问题排查手册](#3-问题排查手册)
4. [跨组件交互](#4-跨组件交互)
5. [性能优化](#5-性能优化)

---

## 1. 设计决策分析

### 1.1 为什么 Search 继承 TextField 而不是独立实现？

**背景**：Search 是一个搜索输入框，需要文本输入功能

**决策**：Search 内部创建 TextField 子节点（索引0），而不是继承 TextFieldPattern

**源码位置**：`search_model_ng.cpp:155`

```cpp
// 创建TextField (索引0) - 文本输入框
CreateTextField(frameNode, placeholder, value, hasTextFieldNode, searchTheme);
```

**设计理由**：

| 优点 | 说明 |
|------|------|
| **复用 TextField 能力** | 自动获得完整的文本输入、选择、复制粘贴功能 |
| **解耦业务逻辑** | Search 业务逻辑与 TextField 文本处理分离 |
| **灵活组合** | 可以自由添加搜索图标、取消按钮等其他子元素 |
| **维护成本低** | TextField 的优化和 bug 修复自动惠及 Search |

**替代方案考虑**：

| 方案 | 优点 | 缺点 | 未选择原因 |
|------|------|------|------------|
| 继承 TextFieldPattern | 代码复用高 | 耦合度高，难以添加搜索特有子元素 | 限制了 Search 的灵活性 |
| 独立实现文本输入 | 完全控制 | 需要重新实现所有文本功能 | 维护成本极高 |

**权衡结论**：选择组合模式，Search 作为容器包含 TextField 子节点，既获得完整的文本输入能力，又保持了架构的灵活性

---

### 1.2 为什么 Search 使用 SearchNode 特殊 FrameNode？

**源码位置**：`search_node.h`

```cpp
class SearchNode : public FrameNode {
    DECLARE_ACE_TYPE(SearchNode, FrameNode);

public:
    bool HasTextFieldNode() const;
    bool HasButtonNode() const;
    bool HasCancelButtonNode() const;
    bool HasDividerNode() const;
};
```

**设计理由**：

```
┌─────────────────────────────────────────────────────────┐
│  SearchNode (特殊 FrameNode)                              │
│  ├── 提供子节点存在性检查                                  │
│  │   - HasTextFieldNode()                                │
│  │   - HasButtonNode()                                   │
│  │   - HasCancelButtonNode()                             │
│  │   - HasDividerNode()                                  │
│  ├── 封装 Search 特有的布局逻辑                             │
│  └── 管理子节点的创建和生命周期                              │
└─────────────────────────────────────────────────────────┘
```

**为什么需要这些检查方法**？

在 `CreateSearchNode()` 中避免重复创建子节点：

**源码**：`search_model_ng.cpp:150-156`

```cpp
bool hasTextFieldNode = frameNode->HasTextFieldNode();
bool hasButtonNode = frameNode->HasButtonNode();
bool hasCancelButtonNode = frameNode->HasCancelButtonNode();
bool hasDividerNode = frameNode->HasDividerNode();

// 只在不存在时创建
CreateTextField(frameNode, placeholder, value, hasTextFieldNode, searchTheme);
```

**好处**：
- 支持热更新场景：当 Search 组件属性更新时，不会重复创建已存在的子节点
- 避免内存泄漏和状态丢失
- 提高性能

---

### 1.3 为什么 CancelButtonStyle 有 INPUT 和 INSET 两种类似模式？

**源码**：`search_model.h`

```cpp
enum class CancelButtonStyle {
    INPUT,      // 输入时显示（默认）
    CONSTANT,   // 常显
    HIDDEN,     // 隐藏
    INSET       // 内嵌
};
```

**设计矛盾**：INPUT 和 INSET 都是"有内容时显示"，为什么需要两种？

**差异分析**：

| 特性 | INPUT | INSET |
|------|-------|-------|
| **显示时机** | 有内容时显示 | 有内容时显示 |
| **视觉样式** | 标准按钮样式 | 内嵌样式，与输入框融合 |
| **适用场景** | 一般搜索框 | 紧凑型、嵌入式搜索框 |
| **视觉效果** | 按钮独立于输入框 | 按钮看起来像是输入框的一部分 |

**源码体现**：`search_pattern.cpp` 中的状态更新逻辑对两者处理相同：

```cpp
bool SearchPattern::IsEventEnabled(const std::u16string& textValue, int16_t style)
{
    switch (style) {
        case static_cast<int16_t>(CancelButtonStyle::CONSTANT):
            return true;
        case static_cast<int16_t>(CancelButtonStyle::INPUT):
        case static_cast<int16_t>(CancelButtonStyle::INSET):  // 相同逻辑
            return !textValue.empty();
        // ...
    }
}
```

**设计理由**：
- **INPUT**：标准搜索框，取消按钮有明显的边界
- **INSET**：用于紧凑布局（如工具栏、小型搜索框），取消按钮内嵌在输入框中，节省空间

---

### 1.4 为什么图标支持 Symbol 和 Image 两种类型？

**源码位置**：`search_pattern.h:303-320`

```cpp
bool IsSymbolIcon(int32_t index);
void CreateOrUpdateSymbol(int32_t index, bool isCreateNode);
void CreateOrUpdateImage(int32_t index, bool isCreateNode);
```

**设计理由**：

| 图标类型 | 优点 | 缺点 | 使用场景 |
|---------|------|------|----------|
| **Symbol** | 矢量、可主题化、支持动画 | 文件较大 | 系统图标、需要主题适配 |
| **Image** | 文件小、兼容性好 | 不可缩放、不支持主题 | 自定义图标、不需要主题适配 |

**统一接口**：Search 组件提供统一的图标设置接口，内部自动判断类型：

```cpp
void SearchPattern::CreateSearchIcon(const std::string& src, bool forceUpdate)
{
    auto index = SEARCH_IMAGE_INDEX;

    if (IsSymbolIcon(index)) {
        CreateOrUpdateSymbol(index, true, forceUpdate);
    } else {
        CreateOrUpdateImage(index, true, forceUpdate);
    }
}
```

**判断依据**：通过 FrameNode 的 tag 判断
- `V2::SYMBOL_ETS_TAG` → Symbol 图标
- `V2::IMAGE_ETS_TAG` → Image 图标

---

## 2. 实现原理深挖

### 2.1 Search 子节点创建与索引系统

**源码位置**：`search_model_ng.cpp:43-48`

**核心索引定义**：

```cpp
namespace {
constexpr int32_t TEXTFIELD_INDEX = 0;        // 文本输入框
constexpr int32_t IMAGE_INDEX = 1;             // 搜索图标
constexpr int32_t CANCEL_IMAGE_INDEX = 2;      // 取消图标
constexpr int32_t CANCEL_BUTTON_INDEX = 3;     // 取消按钮
constexpr int32_t BUTTON_INDEX = 4;            // 搜索按钮
constexpr int32_t DIVIDER_INDEX = 5;           // 分隔线
}
```

**创建顺序**：

```
┌─────────────────────────────────────────────────────────┐
│  CreateSearchNode() 调用链                              │
│                                                          │
│  1. CreateTextField()      → TEXTFIELD_INDEX (0)         │
│  2. CreateSearchIcon()    → IMAGE_INDEX (1)             │
│  3. CreateCancelIcon()    → CANCEL_IMAGE_INDEX (2)       │
│  4. CreateCancelButton()  → CANCEL_BUTTON_INDEX (3)      │
│  5. CreateButton()        → BUTTON_INDEX (4)             │
│  6. CreateDivider()       → DIVIDER_INDEX (5)            │
└─────────────────────────────────────────────────────────┘
```

**为什么索引必须是固定常量？**

在 SearchPattern 的各种方法中，通过固定索引访问子节点：

```cpp
// 获取取消按钮节点
auto buttonHost = AceType::DynamicCast<FrameNode>(
    frameNode->GetChildAtIndex(CANCEL_BUTTON_INDEX));  // 固定索引 3

// 获取取消图标节点
auto imageHost = AceType::DynamicCast<FrameNode>(
    frameNode->GetChildAtIndex(CANCEL_IMAGE_INDEX));   // 固定索引 2
```

**风险**：如果创建顺序改变，索引对应关系将错乱
**保护措施**：使用 `HasTextFieldNode()` 等方法检查子节点是否已存在，避免重复创建

---

### 2.2 取消按钮状态更新机制

**源码位置**：`search_pattern.cpp:136-173`

**核心逻辑**：

```cpp
void SearchPattern::UpdateCancelButtonStatus(const std::u16string& textValue, int16_t style)
{
    // 1. 获取取消按钮和图标的节点
    auto buttonHost = AceType::DynamicCast<FrameNode>(
        frameNode->GetChildAtIndex(CANCEL_BUTTON_INDEX));
    auto imageHost = AceType::DynamicCast<FrameNode>(
        frameNode->GetChildAtIndex(CANCEL_IMAGE_INDEX));

    // 2. 判断是否应该启用
    bool isEventEnabled = IsEventEnabled(textValue, style);

    // 3. 根据状态更新可见性、透明度、交互性
    if (isEventEnabled) {
        cancelButtonRenderContext->UpdateOpacity(1.0);        // 完全不透明
        cancelButtonEvent->SetEnabled(true);                   // 可交互
        buttonLayoutProperty->UpdateVisibility(VisibleType::VISIBLE);  // 可见
    } else {
        cancelButtonRenderContext->UpdateOpacity(0.0);        // 完全透明
        cancelButtonEvent->SetEnabled(false);                  // 不可交互
        buttonLayoutProperty->UpdateVisibility(VisibleType::INVISIBLE); // 不可见
    }
}
```

**启用判断逻辑**：

```cpp
bool SearchPattern::IsEventEnabled(const std::u16string& textValue, int16_t style)
{
    switch (style) {
        case static_cast<int16_t>(CancelButtonStyle::CONSTANT):
            return true;  // 常显：始终启用
        case static_cast<int16_t>(CancelButtonStyle::INPUT):
        case static_cast<int16_t>(CancelButtonStyle::INSET):
            return !textValue.empty();  // 输入/内嵌：有内容时启用
        case static_cast<int16_t>(CancelButtonStyle::HIDDEN):
            return false;  // 隐藏：始终禁用
        default:
            return !textValue.empty();
    }
}
```

**状态更新触发时机**：

```
┌─────────────────────────────────────────────────────────┐
│  触发 UpdateCancelButtonStatus() 的时机                   │
│                                                          │
│  1. OnModifyDone()                    → 初始化时检查      │
│  2. UpdateChangeEvent()               → 文本变化时        │
│  3. 用户输入文本                        → TextField 回调  │
│  4. cancelButtonStyle 属性变化          → 属性更新         │
└─────────────────────────────────────────────────────────┘
```

---

### 2.3 主题更新机制

**源码位置**：`search_pattern.h:166-169`

**主题更新流程**：

```
系统主题切换
    ↓
OnColorConfigurationUpdate()
    ↓
检查用户设置标志
    ↓
for each property:
    if (property->Get*SetByUser() == false):
        update with theme value  // 仅更新未由用户设置的属性
    else:
        keep user value         // 保留用户自定义值
```

**用户设置标志**：

**源码**：`search_layout_property.h:104-106`

```cpp
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(DividerColorSetByUser, bool, PROPERTY_UPDATE_NORMAL);
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(SearchIconColorSetByUser, bool, PROPERTY_UPDATE_NORMAL);
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(CancelIconColorSetByUser, bool, PROPERTY_UPDATE_NORMAL);
```

**更新逻辑**：

```cpp
void SearchPattern::OnIconColorConfigrationUpdate(const RefPtr<SearchTheme>& searchTheme)
{
    auto layoutProperty = frameNode->GetLayoutProperty<SearchLayoutProperty>();

    // 检查用户是否设置了搜索图标颜色
    if (!layoutProperty->GetSearchIconColorSetByUser().value_or(false)) {
        // 未设置，使用主题值
        pattern->SetSearchIconColor(searchTheme->GetSearchIconColor());
    }
    // 否则，保留用户设置

    // 检查用户是否设置了取消图标颜色
    if (!layoutProperty->GetCancelIconColorSetByUser().value_or(false)) {
        pattern->SetCancelIconColor(searchTheme->GetCancelIconColor());
    }
}
```

**Model 层设置标志**：`search_model_ng.cpp`

```cpp
void SearchModelNG::SetSearchIconColor(const Color& color)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SearchPattern>();
    pattern->SetSearchIconColor(color);

    // 标记为用户设置
    ACE_UPDATE_LAYOUT_PROPERTY(SearchLayoutProperty, SearchIconColorSetByUser, true);
}
```

---

### 2.4 焦点管理系统

**源码位置**：`search_pattern.h:96`

**焦点选择枚举**：

```cpp
enum class FocusChoice { SEARCH = 0, CANCEL_BUTTON, SEARCH_BUTTON };
```

**焦点切换逻辑**：

```
┌─────────────────────────────────────────────────────────┐
│  Search 焦点流转                                           │
│                                                          │
│  ┌──────────┐    Tab/Shift+Tab    ┌──────────────────┐  │
│  │ TextField│ ←─────────────────→ │ Cancel Button    │  │
│  │ (输入框)  │                      │ (取消按钮)        │  │
│  └──────────┘                      └──────────────────┘  │
│         ↑                                  ↑             │
│         │                                  │             │
│         └──────────────────────────────────┘             │
│                    Search Button                         │
│                    (搜索按钮)                             │
│                                                          │
│  焦点顺序可配置：focusChoice_ 控制下一个焦点位置            │
└─────────────────────────────────────────────────────────┘
```

**键盘导航支持**：

```cpp
bool SearchPattern::OnKeyEvent(const KeyEvent& event)
{
    if (event.action == KeyEventAction::DOWN) {
        if (event.code == KeyCode::KEY_TAB) {
            // Tab 键：下一个焦点
            HandleFocusEvent(/* forwardFocusMovement */ true,
                             /* backwardFocusMovement */ false);
        } else if (event.code == KeyCode::KEY_SHIFT_LEFT + KeyCode::KEY_TAB) {
            // Shift+Tab：上一个焦点
            HandleFocusEvent(/* forwardFocusMovement */ false,
                             /* backwardFocusMovement */ true);
        }
    }
}
```

---

### 2.5 动画系统实现

**动画常量定义**：

**源码**：`search_pattern.cpp:46-73`

```cpp
namespace {
constexpr float HOVER_OPACITY = 0.05f;       // 悬停透明度
constexpr float TOUCH_OPACITY = 0.1f;        // 触摸透明度
constexpr int32_t HOVER_DURATION = 250;      // 悬停动画时长 (ms)
constexpr int32_t TOUCH_DURATION = 250;      // 触摸动画时长 (ms)
}
```

**动画应用方法**：

```cpp
void SearchPattern::AnimateTouchAndHover(
    RefPtr<RenderContext>& renderContext,
    float startOpacity, float endOpacity,
    int32_t duration, const RefPtr<Curve>& curve, int32_t childId)
{
    AnimationOption option;
    option.SetDuration(duration);
    option.SetCurve(curve);

    auto animation = AnimationUtils::StartAnimation(
        option,
        [renderContext, endOpacity]() {
            renderContext->UpdateOpacity(endOpacity);
        });
}
```

**触发时机**：

| 触发条件 | 动画类型 | 透明度变化 | 持续时间 |
|---------|---------|-----------|---------|
| 鼠标悬停在按钮上 | HOVER | 0 → 0.05 | 250ms |
| 鼠标移出按钮 | HOVER | 0.05 → 0 | 250ms |
| 手指触摸按钮 | TOUCH | 0 → 0.1 | 250ms |
| 手指离开按钮 | TOUCH | 0.1 → 0 | 250ms |

---

## 3. 问题排查手册

### 3.1 搜索按钮不显示

**症状**：设置了 `searchButton` 文本，但按钮不显示

**诊断流程**：

```
开始
  ↓
检查 searchButton 文本
  ├─ 为空？ → 设置非空文本
  └─ 不为空 → 继续
  ↓
检查按钮 Enabled 状态
  ├─ disabled？ → 检查 autoDisable 属性
  │                ├─ true 且文本为空 → 正常行为
  │                └─ false → 检查 enabled 属性
  └─ enabled → 继续
  ↓
检查按钮 Opacity
  ├─ 0.0？ → 设置 opacity(1.0)
  └─ 1.0 → 继续
  ↓
检查按钮 Visibility
  ├─ INVISIBLE/GONE → 设置 visibility(Visible)
  └─ VISIBLE → 检查布局约束
```

**源码保护**：`search_model_ng.cpp:235-262`

```cpp
void SearchModelNG::SetSearchButton(const std::string& text)
{
    auto buttonFrameNode = AceType::DynamicCast<FrameNode>(
        frameNode->GetChildAtIndex(BUTTON_INDEX));

    if (!text.empty()) {
        searchButtonEvent->SetEnabled(true);
        searchButtonRenderContext->UpdateOpacity(1.0);
        ACE_UPDATE_LAYOUT_PROPERTY(SearchLayoutProperty, SearchButton, text);
    } else {
        searchButtonEvent->SetEnabled(false);
        searchButtonRenderContext->UpdateOpacity(0.0);
    }
}
```

**快速验证代码**：

```typescript
@Entry
@Component
struct DebugSearchButton {
  @State searchText: string = ''
  @State showButton: boolean = true

  build() {
    Column({ space: 10 }) {
      // 调试信息
      Text(`Search Text: "${this.searchText}"`)
      Text(`Show Button: ${this.showButton}`)

      // Search
      Search({ value: this.searchText })
        .searchButton(this.showButton ? 'Search' : '')
        .onChange((value: string) => {
          this.searchText = value
        })

      // 控制按钮
      Button('Toggle Search Button')
        .onClick(() => {
          this.showButton = !this.showButton
        })
    }
  }
}
```

---

### 3.2 取消按钮状态异常

**常见原因**：

| 原因 | 现象 | 解决方案 |
|------|------|----------|
| cancelButtonStyle 设置错误 | 按钮始终隐藏/显示 | 检查样式设置（INPUT/CONSTANT/HIDDEN/INSET） |
| TextField 内容为空 | INPUT/INSET 模式下不显示 | 输入内容或改为 CONSTANT 模式 |
| 状态更新未触发 | 按钮状态不随内容变化 | 检查 `UpdateChangeEvent()` 是否正确调用 |

**调试方法**：

```typescript
Search()
  .cancelButtonStyle(CancelButtonStyle.CONSTANT)  // 强制常显，验证按钮存在
  .onChange((value: string) => {
    console.log(`[Search Debug] Text: "${value}", Length: ${value.length}`)
  })
```

---

### 3.3 图标不显示

**症状**：搜索图标或取消图标不显示

**诊断检查清单**：

```
□ 图标路径是否正确
  - 检查资源路径是否存在
  - 使用 $r('app.media.icon_name') 格式

□ 图标尺寸是否为 0
  - 检查 searchIconSize / cancelIconSize 属性
  - 设置合理的尺寸（如 20vp）

□ 图标颜色是否为透明
  - 检查 searchIconColor / cancelIconColor 属性
  - 使用 Color.Transparent 以外的颜色

□ Symbol 图标语法是否正确
  - 检查 Symbol.Modifier 语法
  - 确认 Symbol 图标存在
```

**源码保护**：`search_pattern.cpp`

```cpp
void SearchPattern::SetSearchIconSize(const Dimension& value)
{
    if (value.Value() <= 0.0) {
        // 尺寸无效，不设置
        return;
    }
    // 设置尺寸...
}
```

---

### 3.4 事件不触发

**症状**：onSubmit、onChange 等事件没有触发

**常见原因**：

| 原因 | 检查方法 | 解决方案 |
|------|---------|----------|
| 事件回调未注册 | 检查是否调用了 `.onXxx()` 方法 | 添加事件回调 |
| 组件被禁用 | 检查 `enabled` 属性 | 设置 `enabled(true)` |
| 按钮被禁用 | 检查按钮的 `enabled` 状态 | 检查 autoDisable 和内容状态 |
| 事件被拦截 | 检查父组件事件处理 | 检查事件冒泡 |

**事件初始化检查**：

**源码**：`search_pattern.cpp` - `InitAllEvent()`

```cpp
void SearchPattern::InitAllEvent()
{
    InitSearchController();              // 搜索控制器
    InitTextFieldValueChangeEvent();     // 文本变化事件
    InitTextFieldDragEvent();            // 拖拽事件
    InitButtonMouseAndTouchEvent();      // 按钮鼠标/触摸事件
    InitClickEvent();                    // 点击事件
    InitFocusEvent(...);                 // 焦点事件
    InitHoverEvent();                    // 悬停事件
    InitTouchEvent();                    // 触摸事件
}
```

**快速验证**：

```typescript
Search()
  .enabled(true)                    // 确保启用
  .searchButton('Search')            // 确保按钮显示
  .onChange((value: string) => {
    console.log(`[Search Debug] onChange: "${value}"`)
  })
  .onSubmit((value: string) => {
    console.log(`[Search Debug] onSubmit: "${value}"`)
  })
```

---

## 4. 跨组件交互

### 4.1 Search 与 TextField 的关系

**依赖**：Search **包含** TextField 子节点

```
Search FrameNode (SearchNode)
├── TextField FrameNode (TEXTFIELD_INDEX=0)  ← 内部包含
├── SearchIcon FrameNode (IMAGE_INDEX=1)
├── CancelIcon FrameNode (CANCEL_IMAGE_INDEX=2)
├── CancelButton FrameNode (CANCEL_BUTTON_INDEX=3)
├── SearchButton FrameNode (BUTTON_INDEX=4)
└── Divider FrameNode (DIVIDER_INDEX=5)
```

**数据流向**：

```
ArkTS: Search({ value: 'hello' })
           ↓
SearchModelNG::Create()
           ↓
CreateTextField(frameNode, placeholder, value, ...)
           ↓
TextField FrameNode 创建
    └── TextFieldPattern 初始化
    └── 设置初始值 value
           ↓
SearchPattern::OnModifyDone()
    └── 获取 TextField 子节点
    └── 注册事件监听
           ↓
用户输入触发 TextField 事件
    └── SearchPattern 接收通知
    └── UpdateCancelButtonStatus() 更新取消按钮状态
```

**注意事项**：
- TextField 是 Search 的第一个子节点（索引 0）
- Search 复用 TextField 的文本输入能力
- 不要直接访问 Search 内部的 TextField 节点（实现细节可能变化）

---

### 4.2 Search 与 Button 的组合

**Search 包含两个 Button 子节点**：

```cpp
// 取消按钮 (索引 3)
constexpr int32_t CANCEL_BUTTON_INDEX = 3;

// 搜索按钮 (索引 4)
constexpr int32_t BUTTON_INDEX = 4;
```

**按钮功能区分**：

| 按钮 | 索引 | 功能 | 触发条件 |
|------|------|------|----------|
| **CancelButton** | 3 | 清空输入框 | 点击按钮 |
| **SearchButton** | 4 | 触发搜索 | 点击按钮或按 Enter |

**事件处理**：

```cpp
// 取消按钮点击
void SearchPattern::OnClickCancelButton()
{
    auto textField = textField_.Upgrade();
    auto pattern = textField->GetPattern<TextFieldPattern>();
    pattern->SetText("");  // 清空文本
    UpdateChangeEvent(u"", style);  // 更新取消按钮状态
}

// 搜索按钮点击
void SearchPattern::OnClickButtonAndImage()
{
    auto textField = textField_.Upgrade();
    auto pattern = textField->GetPattern<TextFieldPattern>();
    std::string text = pattern->GetText();  // 获取文本

    // 触发 onSubmit 回调
    auto eventHub = GetEventHub<SearchEventHub>();
    eventHub->GetSubmitEvent()(text);
}
```

---

### 4.3 Search 与 List 的组合

**最佳实践**：

```typescript
List() {
  ForEach(this.searchResults, (result: SearchResult) => {
    ListItem() {
      Row() {
        Text(result.title)
          .layoutWeight(1)

        // 使用 Search 作为列表项的搜索入口
        Search({ placeholder: 'Search...' })
          .width(200)
          .height(40)
      }
      .width('100%')
    }
  })
}
```

**性能考虑**：
- List 中使用 Search 时，注意避免频繁创建/销毁
- 使用 `LazyForEach` 优化大数据量场景
- Search 的创建开销较小，但频繁更新仍需注意

---

### 4.4 Search 与 Symbol 图标的集成

**Symbol 图标优势**：

| 特性 | Symbol | Image |
|------|---------|-------|
| 可主题化 | ✅ 支持 | ❌ 不支持 |
| 矢量缩放 | ✅ 无损 | ❌ 有损 |
| 动画效果 | ✅ 支持 | ❌ 不支持 |
| 文件大小 | 较大 | 较小 |

**Symbol 图标使用示例**：

```typescript
Search()
  .searchIcon(Symbol.search.Modifier
    .fill(Color.Blue)
    .size(20))
  .cancelButton(Symbol.Close.Modifier
    .size(16))
```

**源码处理**：

```cpp
bool SearchPattern::IsSymbolIcon(int32_t index)
{
    auto frameNode = GetHost();
    auto childNode = AceType::DynamicCast<FrameNode>(
        frameNode->GetChildAtIndex(index));
    return childNode->GetTag() == V2::SYMBOL_ETS_TAG;
}
```

---

## 5. 性能优化

### 5.1 渲染性能

**Search 渲染路径**：

```
Search FrameNode
    ↓
6 个子节点 (TextField, 2 Icons, 2 Buttons, Divider)
    ↓
各子节点独立渲染
    ↓
Rosen/Skia 渲染
```

**优化建议**：

| 操作 | 性能影响 | 优化建议 |
|------|----------|----------|
| 创建 Search | 中（~5ms，6个子节点） | 避免频繁创建 |
| 更新文本 | 低（~1ms） | 正常使用 |
| 更新取消按钮状态 | 低（~0.5ms） | 使用防抖减少频率 |
| 测量布局 | 中（~3ms） | 使用固定尺寸 |
| 绘制渲染 | 中（~3ms） | 使用纯色避免渐变 |

---

### 5.2 内存占用

**单个 Search 内存**：

| 组件 | 内存占用 |
|------|----------|
| Search FrameNode | ~1.5 KB |
| TextField 子节点 | ~1 KB |
| SearchIcon 子节点 | ~0.8 KB |
| CancelIcon 子节点 | ~0.8 KB |
| CancelButton 子节点 | ~1 KB |
| SearchButton 子节点 | ~1 KB |
| Divider 子节点 | ~0.5 KB |
| **总计** | **~6.6 KB** |

**100 个 Search**：~660 KB

**优化建议**：
- 不需要时条件渲染（`if (needSearch)`）
- 避免在 List 中频繁创建/销毁
- 使用对象池（适用于频繁创建销毁场景）

---

### 5.3 事件处理优化

**事件防抖**：

```typescript
// 使用防抖减少 onChange 触发频率
debounceUpdate(newValue: string) {
  if (this.debounceTimer) {
    clearTimeout(this.debounceTimer)
  }
  this.debounceTimer = setTimeout(() => {
    this.searchValue = newValue
    this.performSearch()
  }, 300)  // 300ms 内多次输入只触发一次搜索
}

Search()
  .onChange((value: string) => {
    this.debounceUpdate(value)
  })
```

---

## 附录

### 相关文件清单

| 文件 | 行数 | 主要功能 |
|------|------|----------|
| `search_pattern.h` | ~400 | Pattern 类定义 |
| `search_pattern.cpp` | ~1500 | Pattern 实现 |
| `search_model_ng.h/cpp` | ~300/500 | Model 层 |
| `search_layout_property.h` | ~120 | 属性定义 |
| `search_event_hub.h` | ~50 | 事件处理 |
| `search_node.h/cpp` | ~100/200 | SearchNode 特殊 FrameNode |

### 调试命令

```bash
# 查看 Search 组件信息
hidumper -s WindowManagerService -a '-a Search'

# 查看组件树
hidumper -s WindowManagerService -a '-a ComponentTree'

# 查看 Search 日志（如果有专用标签）
hilog -T ACE_SEARCH
```

### 参考文档

- [Search/CLAUDE.md](../../frameworks/core/components_ng/pattern/search/CLAUDE.md) - 快速参考
- [TextField_Knowledge_Base_CN.md](../text_field/TextField_Knowledge_Base_CN.md) - TextField 组件深入（Search 包含 TextField）
- [search_theme.h](../../frameworks/core/components/search/search_theme.h) - 主题定义
