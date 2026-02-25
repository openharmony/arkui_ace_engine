# ArkUI TextInput 组件知识库

> **文档版本**：v1.0
> **更新时间**：2026-02-04
> **源码版本**：OpenHarmony ace_engine (master 分支)

---

## 📚 目录

1. [概述](#概述)
2. [目录结构](#目录结构)
3. [核心类继承关系](#核心类继承关系)
4. [布局算法](#布局算法)
5. [前端接口层](#前端接口层)
6. [执行流程](#执行流程)
7. [关键实现细节](#关键实现细节)
8. [与TextField/TextArea的关系](#与textfieldtextarea的关系)
9. [使用示例](#使用示例)

---

## 概述

### 组件定位

**TextInput 组件**是 OpenHarmony ArkUI 框架中的**单行文本输入组件**，用于接收用户输入的单行文本。它是 TextFieldPattern 的单行输入实现，使用 TextInputLayoutAlgorithm 进行布局。

### 技术架构

```
┌─────────────────────────────────────────────────────────┐
│  应用层 (ArkTS)                                           │
│  TextInput({ placeholder: '请输入用户名' })               │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│  桥接层 (Model Layer)                                    │
│  TextFieldModelNG::CreateTextInput()                    │
│  源码：text_field_model_ng.cpp                          │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│  核心层 (Pattern Layer)                                  │
│  TextFieldPattern                                        │
│  使用 TextInputLayoutAlgorithm                          │
│  源码：text_field_pattern.h                             │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│  布局层 (LayoutAlgorithm Layer)                          │
│  TextInputLayoutAlgorithm                                │
│  源码：text_input_layout_algorithm.h/cpp                │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│  渲染层 (Render Layer)                                   │
│  TextFieldPaintMethod                                    │
│  渲染单行输入框                                          │
└─────────────────────────────────────────────────────────┘
```

### 功能特性

| 功能类别 | 具体功能 |
|---------|---------|
| **单行输入** | 专用于单行文本输入 |
| **IME集成** | 与系统输入法集成 |
| **输入类型** | 支持多种输入类型（文本、数字、密码等） |
| **响应区域** | 支持左右响应区域（图标等） |
| **自动填充图标** | 支持自动填充图标显示 |
| **计数器** | 字符计数显示 |
| **取消按钮** | 清除内容按钮 |
| **语音按钮** | 语音输入按钮 |
| **继承功能** | 继承 TextField 的所有功能 |

---

## 目录结构

### 核心代码目录

```
frameworks/core/components_ng/pattern/text_input/
└── text_input_layout_algorithm.h      # TextInput 布局算法

frameworks/core/components_ng/pattern/text_field/
├── text_field_pattern.h                # TextField Pattern (共享)
├── text_field_layout_algorithm.h       # 布局算法基类 (共享)
└── ... (其他共享文件)

frameworks/bridge/declarative_frontend/jsview/
├── js_textinput.h                      # TextInput 前端接口
└── js_textinput.cpp                    # TextInput 前端实现
```

### 代码规模

| 项目 | 说明 |
|-----|------|
| 核心文件 | text_input_layout_algorithm.h |
| Layout文件 | text_input_layout_algorithm.h (73行) |
| 前端接口 | js_textinput.h/cpp |
| 共享功能 | 使用 TextField 的所有共享代码 |

---

## 核心类继承关系

### 类继承图

```
Pattern (基类)
    ↓
ScrollablePattern (滚动模式基类)
    ↓
TextFieldPattern (TextField核心模式)
    ↓
    └── (使用 TextInputLayoutAlgorithm)
```

### TextInputLayoutAlgorithm 继承关系

```
LayoutAlgorithm (基类)
    ↓
TextAdaptFontSizer (字体自适应)
    ↓
TextFieldLayoutAlgorithm (TextField布局算法基类)
    ↓
TextInputLayoutAlgorithm (TextInput布局算法)
```

### 与其他组件的关系

```
TextFieldLayoutAlgorithm (基类)
    ↓
    ├── TextInputLayoutAlgorithm (单行输入布局)
    └── TextAreaLayoutAlgorithm (多行输入布局)
```

---

## 布局算法

### TextInputLayoutAlgorithm

**源码位置**：[text_input_layout_algorithm.h](../../frameworks/core/components_ng/pattern/text_input/text_input_layout_algorithm.h)

#### 类定义

```cpp
class TextInputLayoutAlgorithm : public TextFieldLayoutAlgorithm {
    DECLARE_ACE_TYPE(TextInputLayoutAlgorithm, TextFieldLayoutAlgorithm);

public:
    TextInputLayoutAlgorithm() = default;
    ~TextInputLayoutAlgorithm() override = default;

    // 测量
    void Measure(LayoutWrapper* layoutWrapper) override;
    std::optional<SizeF> MeasureContent(
        const LayoutConstraintF& contentConstraint,
        LayoutWrapper* layoutWrapper) override;

    // 布局
    void Layout(LayoutWrapper* layoutWrapper) override;

    // 获取默认高度
    float GetDefaultHeightByType(LayoutWrapper* layoutWrapper);

protected:
    // 创建段落（扩展方法）
    bool CreateParagraphEx(const TextStyle& textStyle,
        const std::u16string& content,
        const LayoutConstraintF& contentConstraint,
        LayoutWrapper* layoutWrapper) override;

private:
    // 更新内容位置
    void UpdateContentPosition(const UpdateContentPositionParams& params,
        const std::unique_ptr<GeometryProperty>& content);

    // 更新文本区域
    void UpdateTextRect(const UpdateTextRectParams& params);

    // 检查字体大小是否非正
    bool IsFontSizeNonPositive(const TextStyle& textStyle) const;

    // 测量自动填充图标
    void MeasureAutoFillIcon(LayoutWrapper* layoutWrapper);
    void LayoutAutoFillIcon(LayoutWrapper* layoutWrapper, float unitNodeWidth);

    // 使用策略测量计数器
    void MeasureCounterWithPolicy(LayoutWrapper* layoutWrapper, float nonContentWidth);

    // 获取文本方向
    TextDirection GetTextDirection(const RefPtr<LayoutProperty>& layoutProperty);

    // 自动填充图标尺寸
    SizeF autoFillIconSizeMeasure_;
};
```

#### 核心职责

1. **单行内容测量**：测量单行文本内容的尺寸
2. **响应区域布局**：布局左右响应区域（图标等）
3. **自动填充图标**：布局自动填充图标
4. **计数器布局**：布局字符计数器
5. **默认高度计算**：计算单行输入框的默认高度

#### 数据结构

**UpdateContentPositionParams**：
```cpp
struct UpdateContentPositionParams {
    bool isRTL = false;                    // 是否从右到左
    OffsetF offsetBase = OffsetF(0.0f, 0.0f);
    SizeT<float> size = SizeT<float>(0.0f, 0.0f);
    SizeT<float> contentSize = SizeT<float>(0.0f, 0.0f);
    Alignment align = Alignment::CENTER;
    float allResponseAreaWidth = 0.0f;     // 所有响应区域宽度
};
```

**UpdateTextRectParams**：
```cpp
struct UpdateTextRectParams {
    RefPtr<TextFieldLayoutProperty> layoutProperty = nullptr;
    RefPtr<TextFieldPattern> pattern = nullptr;
    SizeT<float> contentSize = SizeT<float>(0.0f, 0.0f);
    bool isRTL = false;
    OffsetF contentOffset = OffsetF(0.0f, 0.0f);
    float allResponseAreaWidth = 0.0f;
};
```

#### 布局流程

```
┌─────────────────────────────────────────────────────────┐
│  Measure 阶段                                            │
│  1. MeasureContent() - 测量内容尺寸                      │
│     - TextInputMeasureContent() - 单行文本测量            │
│     - MeasureAutoFillIcon() - 测量自动填充图标            │
│     - MeasureCounterWithPolicy() - 测量计数器             │
│  2. GetDefaultHeightByType() - 获取默认高度               │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│  Layout 阶段                                             │
│  1. Layout() - 布局子节点                                │
│  2. LayoutAutoFillIcon() - 布局自动填充图标               │
│  3. UpdateContentPosition() - 更新内容位置                │
│  4. UpdateTextRect() - 更新文本区域                       │
└─────────────────────────────────────────────────────────┘
```

#### 关键方法

| 方法 | 说明 | 源码位置 |
|-----|------|---------|
| `Measure()` | 测量布局 | text_input_layout_algorithm.cpp |
| `MeasureContent()` | 测量内容 | text_input_layout_algorithm.cpp |
| `Layout()` | 布局子节点 | text_input_layout_algorithm.cpp |
| `GetDefaultHeightByType()` | 获取默认高度 | text_input_layout_algorithm.cpp |
| `CreateParagraphEx()` | 创建段落 | text_input_layout_algorithm.cpp |
| `UpdateContentPosition()` | 更新内容位置 | text_input_layout_algorithm.cpp |
| `UpdateTextRect()` | 更新文本区域 | text_input_layout_algorithm.cpp |
| `MeasureAutoFillIcon()` | 测量自动填充图标 | text_input_layout_algorithm.cpp |
| `LayoutAutoFillIcon()` | 布局自动填充图标 | text_input_layout_algorithm.cpp |
| `MeasureCounterWithPolicy()` | 测量计数器 | text_input_layout_algorithm.cpp |

---

## 前端接口层

### JSTextInput

**源码位置**：[js_textinput.h](../../frameworks/bridge/declarative_frontend/jsview/js_textinput.h)

#### 类定义

```cpp
class JSTextInput : public JSViewAbstract {
public:
    static void JSBind(BindingTarget globalObj);
    static void Create(const JSCallbackInfo& info);
};

class JSTextInputController final : public virtual AceType {
    DECLARE_ACE_TYPE(JSTextInputController, AceType);

public:
    JSTextInputController() = default;
    ~JSTextInputController() override = default;

    static void JSBind(BindingTarget globalObj);

private:
    ACE_DISALLOW_COPY_AND_MOVE(JSTextInputController);
};
```

#### 前端 API

JSTextInput 实际上使用 JSTextField 的实现，共享大部分 API：

| ArkTS API | C++ 实现 | 说明 |
|-----------|----------|------|
| `TextInput()` | `JSTextField::CreateTextInput()` | 创建组件 |
| `.type()` | `JSTextField::SetType()` | 设置输入类型 |
| `.placeholder()` | `UpdatePlaceholder()` | 设置占位符 |
| `.placeholderColor()` | `SetPlaceholderColor()` | 占位符颜色 |
| `.placeholderFont()` | `SetPlaceholderFont()` | 占位符字体 |
| `.caretColor()` | `SetCaretColor()` | 光标颜色 |
| `.maxLength()` | `SetMaxLength()` | 最大长度 |
| `.maxLines()` | `SetMaxLines()` | 最大行数（通常为1） |
| `.fontSize()` | `SetFontSize()` | 字体大小 |
| `.fontColor()` | `SetTextColor()` | 字体颜色 |
| `.onChange()` | `SetOnChange()` | 内容变化事件 |
| `.onSubmit()` | `SetOnSubmit()` | 提交事件 |

### JSTextInputController

```cpp
class JSTextInputController final : public virtual AceType {
    DECLARE_ACE_TYPE(JSTextInputController, AceType);

public:
    JSTextInputController() = default;
    ~JSTextInputController() override = default;

    static void JSBind(BindingTarget globalObj);

private:
    ACE_DISALLOW_COPY_AND_MOVE(JSTextInputController);
};
```

---

## 执行流程

### 组件创建流程

```
ArkTS代码
  TextInput({ placeholder: '请输入' })
    ↓
JSTextInput::Create()
  [js_textinput.cpp]
    ↓
JSTextField::CreateTextInput()
  [js_textfield.cpp]
    ↓
TextFieldModelNG::CreateTextInput()
  [text_field_model_ng.cpp]
    ↓
FrameNode::GetOrCreateFrameNode(tag, nodeId, ...)
  创建 TextFieldPattern 实例
  使用 TextInputLayoutAlgorithm
    ↓
TextFieldPattern::OnAttachToFrameNode()
  初始化功能
    ↓
ViewStackProcessor::Push(frameNode)
  推入视图栈
```

### 布局流程

```
┌─────────────────────────────────────────────────────────┐
│  TextInputLayoutAlgorithm::Measure()                     │
│  源码：text_input_layout_algorithm.cpp                   │
│                                                          │
│  1. MeasureContent() - 测量内容                          │
│     - 获取布局约束                                        │
│     - 测量文本内容                                        │
│     - 测量自动填充图标                                    │
│     - 测量计数器                                         │
│     - 计算内容尺寸                                        │
│  2. 获取默认高度                                          │
│     - GetDefaultHeightByType()                           │
│  3. 更新布局属性                                          │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│  TextInputLayoutAlgorithm::Layout()                      │
│  源码：text_input_layout_algorithm.cpp                   │
│                                                          │
│  1. 调用父类 Layout()                                     │
│  2. LayoutAutoFillIcon() - 布局自动填充图标                │
│  3. UpdateContentPosition() - 更新内容位置                │
│  4. UpdateTextRect() - 更新文本区域                       │
│  5. 定位子节点                                            │
└─────────────────────────────────────────────────────────┘
```

### 内容测量流程

```
TextInputMeasureContent()
    ↓
┌─────────────────────────────────────────────────────────┐
│  1. 获取布局约束                                          │
│     LayoutConstraintF contentConstraint                  │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│  2. 计算非内容宽度                                         │
│     - 左响应区域（取消按钮等）                            │
│     - 右响应区域（语音按钮等）                            │
│     - 自动填充图标                                        │
│     - 计数器                                             │
│     float nonContentWidth = ...                          │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│  3. 测量文本内容                                          │
│     - 创建 Paragraph                                      │
│     - 测量文本宽度                                        │
│     - 计算内容高度                                        │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│  4. 计算最终尺寸                                          │
│     - width = contentWidth + nonContentWidth              │
│     - height = contentHeight 或默认高度                    │
│     return SizeF(width, height)                          │
└─────────────────────────────────────────────────────────┘
```

---

## 关键实现细节

### 1. 单行输入限制

TextInput 通过以下方式实现单行输入：

1. **布局算法**：使用 TextInputLayoutAlgorithm 而非 TextAreaLayoutAlgorithm
2. **换行处理**：不支持换行符输入
3. **maxLines 默认值**：默认为 1
4. **段落创建**：创建单行 Paragraph

### 2. 响应区域布局

TextInput 支持左右响应区域（如取消按钮、语音按钮等）：

```cpp
// 更新内容位置时考虑响应区域
void UpdateContentPosition(const UpdateContentPositionParams& params,
    const std::unique_ptr<GeometryProperty>& content)
{
    // 计算响应区域宽度
    float allResponseAreaWidth = params.allResponseAreaWidth;

    // 根据文本方向和响应区域调整内容位置
    if (params.isRTL) {
        // 从右到左布局
        contentOffset.SetX(params.size.Width() - params.contentSize.Width()
            - allResponseAreaWidth);
    } else {
        // 从左到右布局
        contentOffset.SetX(allResponseAreaWidth);
    }
}
```

### 3. 自动填充图标

支持自动填充图标的显示和布局：

```cpp
void MeasureAutoFillIcon(LayoutWrapper* layoutWrapper)
{
    // 测量自动填充图标尺寸
    // 存储到 autoFillIconSizeMeasure_
}

void LayoutAutoFillIcon(LayoutWrapper* layoutWrapper, float unitNodeWidth)
{
    // 布局自动填充图标
    // 定位到合适位置
}
```

### 4. 默认高度

TextInput 的默认高度计算：

```cpp
float GetDefaultHeightByType(LayoutWrapper* layoutWrapper)
{
    // 根据输入类型和字体计算默认高度
    // 通常为字体高度的 1.2-1.5 倍
    float fontSize = GetFontSize();
    float lineHeight = GetLineHeight();
    return std::max(fontSize, lineHeight) * DEFAULT_HEIGHT_RATIO;
}
```

### 5. RTL 支持

支持从右到左的语言布局：

```cpp
TextDirection GetTextDirection(const RefPtr<LayoutProperty>& layoutProperty)
{
    // 获取文本方向
    // TextDirection::LTR 或 TextDirection::RTL
}
```

### 6. 字符计数策略

使用特定策略测量和布局计数器：

```cpp
void MeasureCounterWithPolicy(LayoutWrapper* layoutWrapper, float nonContentWidth)
{
    // 根据策略测量计数器
    // 确保计数器不超出可用宽度
}
```

---

## 与TextField/TextArea的关系

### 继承关系

```
TextFieldPattern (基类)
    ├── 使用 TextInputLayoutAlgorithm → TextInput
    └── 继承 → TextAreaPattern → TextArea
```

### 主要区别

| 特性 | TextField (基类) | TextInput | TextArea |
|-----|------------------|-----------|----------|
| **默认行数** | 取决于子类 | 单行 (maxLines=1) | 多行 |
| **布局算法** | TextFieldLayoutAlgorithm | TextInputLayoutAlgorithm | TextAreaLayoutAlgorithm |
| **高度策略** | 取决于子类 | 固定高度 | 自适应高度 |
| **响应区域** | 支持 | 强调使用 | 通常不使用 |
| **自动填充图标** | 支持 | 强调使用 | 通常不使用 |
| **换行支持** | 取决于子类 | 不支持 | 支持 |
| **minLines** | 取决于子类 | 不支持 | 支持 |

### 代码复用

- **Pattern 层**：完全共享 TextFieldPattern
- **属性系统**：共享 TextFieldLayoutProperty 和 TextFieldPaintProperty
- **事件系统**：共享 TextFieldEventHub
- **渲染层**：共享 TextFieldPaintMethod 和修饰器
- **前端接口**：JSTextInput 实际使用 JSTextField 的实现

---

## 使用示例

### ArkTS 基本用法

```typescript
// 基本输入框
TextInput({ placeholder: '请输入用户名' })

// 带初始值
TextInput({ text: this.username })

// 密码输入
TextInput({ type: InputType.Password })
  .placeholder('请输入密码')

// 数字输入
TextInput({ type: InputType.Number })
  .maxLength(11)

// 带事件
TextInput()
  .onChange((value) => {
    this.text = value
  })
  .onSubmit(() => {
    console.log('提交: ' + this.text)
  })

// 完整配置
TextInput({
  placeholder: '请输入',
  text: this.text
})
  .type(InputType.Text)
  .placeholderColor(Color.Gray)
  .caretColor(Color.Blue)
  .maxLength(20)
  .height(40)
  .backgroundColor(Color.White)
  .borderRadius(8)
  .onChange((value) => {
    this.text = value
  })
  .onSubmit(() => {
    // 处理提交
  })
```

### 样式定制

```typescript
TextInput()
  .backgroundColor(Color.White)
  .borderColor(Color.Blue)
  .borderWidth(2)
  .borderRadius(10)
  .padding(10)
  .fontSize(16)
  .fontColor(Color.Black)
```

### 输入类型

```typescript
// 普通文本
TextInput().type(InputType.Text)

// 数字
TextInput().type(InputType.Number)

// 电话号码
TextInput().type(InputType.Phone)

// 邮箱
TextInput().type(InputType.Email)

// 密码
TextInput().type(InputType.Password)

// URL
TextInput().type(InputType.URL)
```

### 控制器使用

```typescript
// 创建控制器
controller: TextInputController = new TextInputController()

// 使用控制器
TextInput({ textController: this.controller })

// 通过控制器操作
this.controller.setText('新文本')
```

---

## 调试指南

### 常用日志标签

| 日志标签 | 说明 |
|---------|------|
| `AceLogTag::ACE_TEXT_FIELD` | TextInput相关日志 |

### 关键断点位置

| 文件 | 方法 | 说明 |
|-----|------|------|
| text_input_layout_algorithm.cpp | `Measure()` | 布局测量 |
| text_input_layout_algorithm.cpp | `MeasureContent()` | 内容测量 |
| text_input_layout_algorithm.cpp | `Layout()` | 节点布局 |
| text_input_layout_algorithm.cpp | `UpdateContentPosition()` | 内容位置更新 |
| text_input_layout_algorithm.cpp | `UpdateTextRect()` | 文本区域更新 |
| text_input_layout_algorithm.cpp | `MeasureAutoFillIcon()` | 自动填充图标测量 |

---

## 参考源码

### 核心文件

1. **Layout算法**：
   - [text_input_layout_algorithm.h](../../frameworks/core/components_ng/pattern/text_input/text_input_layout_algorithm.h)
   - [text_input_layout_algorithm.cpp](../../frameworks/core/components_ng/pattern/text_input/text_input_layout_algorithm.cpp)

2. **Pattern层（共享）**：
   - [text_field_pattern.h](../../frameworks/core/components_ng/pattern/text_field/text_field_pattern.h)
   - [text_field_pattern.cpp](../../frameworks/core/components_ng/pattern/text_field/text_field_pattern.cpp)

3. **Layout算法基类（共享）**：
   - [text_field_layout_algorithm.h](../../frameworks/core/components_ng/pattern/text_field/text_field_layout_algorithm.h)
   - [text_field_layout_algorithm.cpp](../../frameworks/core/components_ng/pattern/text_field/text_field_layout_algorithm.cpp)

4. **前端接口**：
   - [js_textinput.h](../../frameworks/bridge/declarative_frontend/jsview/js_textinput.h)
   - [js_textinput.cpp](../../frameworks/bridge/declarative_frontend/jsview/js_textinput.cpp)

5. **Model层（共享）**：
   - [text_field_model_ng.h](../../frameworks/core/components_ng/pattern/text_field/text_field_model_ng.h)
   - [text_field_model_ng.cpp](../../frameworks/core/components_ng/pattern/text_field/text_field_model_ng.cpp)

---

**文档维护**：如有疑问或需要补充，请参考上述源码位置。
