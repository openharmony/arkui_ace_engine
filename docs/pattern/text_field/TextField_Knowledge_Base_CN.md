# ArkUI TextField 组件知识库

> **文档版本**：v1.0
> **更新时间**：2026-02-04
> **源码版本**：OpenHarmony ace_engine (master 分支)

---

## 📚 目录

1. [概述](#概述)
2. [目录结构](#目录结构)
3. [核心类继承关系](#核心类继承关系)
4. [Pattern层详解](#pattern层详解)
5. [属性系统](#属性系统)
6. [布局算法](#布局算法)
7. [事件系统](#事件系统)
8. [IME集成](#ime集成)
9. [文本选择与拖拽](#文本选择与拖拽)
10. [内容控制器](#内容控制器)
11. [自动填充](#自动填充)
12. [前端接口层](#前端接口层)
13. [执行流程](#执行流程)
14. [关键实现细节](#关键实现细节)
15. [与TextArea的关系](#与textarea的关系)
16. [使用示例](#使用示例)

---

## 概述

### 组件定位

**TextField 组件**是 OpenHarmony ArkUI 框架中的**文本输入组件基类**，提供完整的文本输入功能，支持单行输入（TextInput）和多行输入（TextArea）。它是 TextFieldPattern 和相关类的集合，实现了从用户输入到系统IME的完整交互链路。

### 技术架构

```
┌─────────────────────────────────────────────────────────┐
│  应用层 (ArkTS)                                           │
│  TextInput({ placeholder: '请输入' })                    │
│  TextArea({ placeholder: '多行输入' })                   │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│  桥接层 (Model Layer)                                    │
│  TextFieldModelNG                                       │
│  - CreateTextInput() - 创建单行输入                       │
│  - CreateTextArea() - 创建多行输入                       │
│  源码：text_field_model_ng.cpp                          │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│  核心层 (Pattern Layer)                                  │
│  TextFieldPattern (多重继承)                              │
│  ├── ScrollablePattern - 滚动功能                        │
│  ├── TextDragBase - 拖拽功能                             │
│  ├── ValueChangeObserver - 值变化观察                     │
│  ├── TextInputClient - IME客户端接口                     │
│  ├── TextBase - 文本基础功能                             │
│  ├── Magnifier - 放大镜功能                              │
│  ├── TextGestureSelector - 手势选择                      │
│  └── LayoutInfoInterface - 布局信息接口                   │
│  源码：text_field_pattern.h (98KB+ 文件)                │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│  布局层 (LayoutAlgorithm Layer)                          │
│  ├── TextInputLayoutAlgorithm - 单行布局                 │
│  └── TextAreaLayoutAlgorithm - 多行布局                  │
│  源码：text_field_layout_algorithm.h/cpp                │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│  渲染层 (Render Layer)                                   │
│  TextFieldPaintMethod                                    │
│  ├── TextFieldContentModifier - 内容修饰器               │
│  ├── TextFieldOverlayModifier - 覆盖修饰器               │
│  └── TextFieldForegroundModifier - 前景修饰器             │
│  源码：text_field_paint_method.h/cpp                    │
└─────────────────────────────────────────────────────────┘
```

### 功能特性

| 功能类别 | 具体功能 |
|---------|---------|
| **文本输入** | 单行/多行输入、IME集成、预览文本 |
| **文本编辑** | 插入、删除、撤销/重做、复制/剪切/粘贴 |
| **文本选择** | 鼠标拖拽、触摸手势、键盘选择、全选 |
| **文本拖拽** | 选中文本拖拽预览 |
| **光标管理** | 光标位置、光标样式、光标动画 |
| **密码模式** | 密码显示/隐藏、密码图标 |
| **自动填充** | 系统自动填充支持 |
| **计数器** | 字符计数显示 |
| **错误提示** | 错误文本和样式 |
| **下划线** | 动态下划线效果 |
| **样式支持** | 字体、颜色、装饰、边框、背景等 |

---

## 目录结构

### 核心代码目录

```
frameworks/core/components_ng/pattern/text_field/
├── text_field_pattern.h              # TextField Pattern 定义（核心文件）
├── text_field_pattern.cpp            # TextField Pattern 实现
├── text_field_layout_algorithm.h     # 布局算法基类
├── text_field_layout_algorithm.cpp   # 布局算法实现
├── text_field_layout_property.h      # 布局属性
├── text_field_paint_property.h       # 渲染属性
├── text_field_paint_method.h         # 绘制方法
├── text_field_paint_method.cpp       # 绘制实现
├── text_field_event_hub.h            # 事件中心
├── text_field_content_modifier.h     # 内容修饰器
├── text_field_content_modifier.cpp   # 内容修饰器实现
├── text_field_overlay_modifier.h     # 覆盖修饰器
├── text_field_overlay_modifier.cpp   # 覆盖修饰器实现
├── text_field_foreground_modifier.h  # 前景修饰器
├── text_field_foreground_modifier.cpp # 前景修饰器实现
├── text_field_model.h                # Model 接口
├── text_field_model_ng.h             # NG Model 实现
├── text_field_model_ng.cpp           # NG Model 实现
├── text_field_model_static.h         # 静态 Model
├── text_field_model_static.cpp       # 静态 Model 实现
├── text_field_model_ng_multi_thread.cpp # 多线程 Model
├── text_field_controller.h           # 控制器
├── text_field_controller.cpp         # 控制器实现
├── text_field_manager.h              # 管理器
├── text_field_manager.cpp            # 管理器实现
├── text_select_controller.h          # 选择控制器
├── text_select_controller.cpp        # 选择控制器实现
├── text_selector.h                   # 选择器
├── text_field_select_overlay.h       # 选择覆盖层
├── text_field_select_overlay.cpp     # 选择覆盖层实现
├── content_controller.h              # 内容控制器
├── content_controller.cpp            # 内容控制器实现
├── auto_fill_controller.h            # 自动填充控制器
├── auto_fill_controller.cpp          # 自动填充控制器实现
├── text_editing_value_ng.h           # 编辑值
├── text_content_type.h               # 内容类型
├── text_content_type.cpp             # 内容类型实现
├── text_keyboard_common_type.h       # 键盘通用类型
├── text_component_decorator.h        # 组件装饰器
├── text_component_decorator.cpp      # 组件装饰器实现
├── text_field_accessibility_property.h # 无障碍属性
├── text_field_accessibility_property.cpp # 无障碍属性实现
├── text_field_theme_wrapper.h        # 主题包装器
├── text_input_response_area.h        # 输入响应区域
├── text_input_response_area.cpp      # 输入响应区域实现
├── text_input_ai_checker.h           # AI 检查器
├── text_input_ai_checker.cpp         # AI 检查器实现
└── on_text_changed_listener_impl.h   # 文本变化监听器
```

### 代码规模

| 项目 | 数量 |
|-----|------|
| 核心文件 | 约 40+ 个文件 |
| 核心代码 | 约 30,000+ 行 C++ 代码 |
| Pattern文件 | text_field_pattern.h (98KB+, 2900+行声明) |
| Layout文件 | text_field_layout_algorithm.h/cpp |
| Event文件 | text_field_event_hub.h (515行) |
| Property文件 | text_field_layout_property.h (367行) |

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
    ├── TextInputPattern (单行输入模式)
    └── TextAreaPattern (多行输入模式)
```

### 多重继承结构

```
TextFieldPattern 继承:
├── ScrollablePattern          - 滚动功能
├── TextDragBase               - 文本拖拽功能
├── ValueChangeObserver        - 值变化观察
├── TextInputClient            - IME客户端接口
├── TextBase                   - 文本基础功能（选择、手势）
├── Magnifier                  - 放大镜功能
├── TextGestureSelector        - 手势选择功能
└── LayoutInfoInterface        - 布局信息接口
```

### 接口实现详情

#### 1. ScrollablePattern

提供滚动能力：
- 垂直滚动支持（TextArea）
- 滚动事件处理
- 滚动位置管理

#### 2. TextDragBase

提供文本拖拽能力：
- 创建拖拽预览节点
- 计算拖拽数据
- 管理拖拽生命周期

#### 3. TextInputClient

IME 客户端接口：
```cpp
// 插入文本
void InsertValue(const std::u16string& insertValue) override;
void InsertValue(const std::string& insertValue) override;

// 删除文本
void DeleteBackward(int32_t length) override;
void DeleteForward(int32_t length) override;

// 设置预览文本
int32_t SetPreviewText(const std::u16string& previewValue, const PreviewRange range) override;
void FinishTextPreview() override;

// 键盘控制
void SendKeyEventFromInputMethod(const KeyEvent& event) override;
void CommitAction(const std::u16string& text, int32_t position) override;

// 光标移动
void MoveCursor(const Offset& offset) override;
void SelectByMouse(const Offset& offset, const Offset& end) override;

// 获取文本
std::string GetText() const override;
int32_t GetTextLength() const override;

// 选择管理
void GetSelectRange(Position& start, Position& end) const override;
void SetSelectRange(int32_t start, int32_t end) override;

// 其他功能
bool GetSelectDetectEnable() const override;
void SetKeyboardStatus(bool status) override;
bool GetKeyboardStatus() const override;
void CloseKeyboard(bool forceClose) override;
```

#### 4. ValueChangeObserver

值变化观察者：
- 监听文本内容变化
- 触发 onChange 事件

#### 5. TextBase

文本基础功能：
- 文本选择管理
- 手势识别
- 复制/剪切/粘贴

#### 6. Magnifier

放大镜功能：
- 长按显示放大镜
- 光标位置放大显示

#### 7. TextGestureSelector

手势选择功能：
- 单击、双击、三击
- 长按选择
- 拖拽选择

---

## Pattern层详解

### TextFieldPattern

**源码位置**：[text_field_pattern.h](../../frameworks/core/components_ng/pattern/text_field/text_field_pattern.h)

#### 类定义

```cpp
class TextFieldPattern : public ScrollablePattern,
                         public TextDragBase,
                         public ValueChangeObserver,
                         public TextInputClient,
                         public TextBase,
                         public Magnifier,
                         public TextGestureSelector,
                         public LayoutInfoInterface {
    DECLARE_ACE_TYPE(TextFieldPattern, ScrollablePattern, TextDragBase,
        ValueChangeObserver, TextInputClient, TextBase, Magnifier, TextGestureSelector);

public:
    TextFieldPattern();
    ~TextFieldPattern() override;

    // 创建布局算法
    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        if (IsTextArea()) {
            return MakeRefPtr<TextAreaLayoutAlgorithm>();
        }
        return MakeRefPtr<TextInputLayoutAlgorithm>();
    }

    // 创建属性
    RefPtr<LayoutProperty> CreateLayoutProperty() override;
    RefPtr<EventHub> CreateEventHub() override;
    RefPtr<PaintProperty> CreatePaintProperty() override;
    RefPtr<AccessibilityProperty> CreateAccessibilityProperty() override;

    // 生命周期
    void OnModifyDone() override;
    void OnAttachToFrameNode() override;
    void OnDetachFromMainTree() override;

    // 文本操作
    void InsertValue(const std::u16string& insertValue, bool isIME = false) override;
    void DeleteBackward(int32_t length) override;
    void DeleteForward(int32_t length) override;

    // 预览文本
    int32_t SetPreviewText(const std::u16string& previewValue, const PreviewRange range) override;
    void FinishTextPreview() override;

    // 选择和拖拽
    void CreateHandles() override;
    const RefPtr<FrameNode>& MoveDragNode() override;

    // 键盘控制
    bool CloseKeyboard(bool forceClose) override;

    // 内容获取
    std::string GetTextValue() const;
    const std::u16string& GetTextUtf16Value() const;

protected:
    // 状态管理
    TextEditingValueNG textEditingValue_;
    RefPtr<ContentController> contentController_;
    RefPtr<AutoFillController> autoFillController_;

    // 装饰器
    RefPtr<TextComponentDecorator> counterDecorator_;
    RefPtr<TextComponentDecorator> errorDecorator_;

    // 控制器
    RefPtr<TextFieldController> textFieldController_;
    WeakPtr<Referenced> jsTextEditableController_;

    // 布局信息
    RectF textRect_;
    OffsetF parentGlobalOffset_;

    // 选择状态
    TextSelector textSelector_;

    // 键盘状态
    bool keyboardStatus_ = false;
    bool needToRequestKeyboardOnFocus_ = true;

private:
    // 撤销/重做
    std::deque<InputOperation> operationRecords_;
    std::deque<InputOperation> redoOperationRecords_;
};
```

#### 核心职责

1. **文本输入管理**：处理用户输入、IME输入、粘贴等
2. **文本编辑**：插入、删除、撤销/重做
3. **文本选择**：管理选择范围、手柄显示
4. **文本拖拽**：创建和管理拖拽预览
5. **IME集成**：与系统输入法交互
6. **键盘控制**：打开/关闭软键盘
7. **内容控制**：管理文本内容和状态
8. **自动填充**：处理系统自动填充
9. **UI装饰**：计数器、错误提示等

#### 关键方法

| 方法 | 说明 | 源码位置 |
|-----|------|---------|
| `CreateLayoutAlgorithm()` | 创建布局算法 | text_field_pattern.h:380-386 |
| `OnModifyDone()` | 修改完成回调 | text_field_pattern.cpp |
| `InsertValue()` | 插入文本 | text_field_pattern.cpp |
| `DeleteBackward()` | 向后删除 | text_field_pattern.cpp |
| `DeleteForward()` | 向前删除 | text_field_pattern.cpp |
| `SetPreviewText()` | 设置预览文本 | text_field_pattern.cpp |
| `FinishTextPreview()` | 完成预览 | text_field_pattern.cpp |
| `CreateHandles()` | 创建选择手柄 | text_field_pattern.cpp |
| `MoveDragNode()` | 移动拖拽节点 | text_field_pattern.cpp |
| `CloseKeyboard()` | 关闭键盘 | text_field_pattern.cpp |

---

## 属性系统

### TextFieldLayoutProperty

**源码位置**：[text_field_layout_property.h](../../frameworks/core/components_ng/pattern/text_field/text_field_layout_property.h)

#### 属性分组

| 属性组 | 包含属性 |
|-------|---------|
| **FontStyle** | FontSize, TextColor, ItalicFontStyle, FontWeight, FontFamily, FontFeature, LetterSpacing, AdaptMinFontSize, AdaptMaxFontSize, TextDecoration, TextDecorationColor, TextDecorationStyle, StrokeWidth, StrokeColor |
| **TextLineStyle** | TextAlign, LineBreakStrategy, MaxLength, MaxLines, OverflowMode, HeightAdaptivePolicy, LineHeight, HalfLeading, LineSpacing, IsOnlyBetweenLines, WordBreak, TextOverflow, TextIndent, NumberOfLines, EllipsisMode, CompressLeadingPunctuation, TextDirection |
| **PlaceholderFontStyle** | PlaceholderFontSize, PlaceholderTextColor, PlaceholderItalicFontStyle, PlaceholderFontWeight, PlaceholderFontFamily |
| **PlaceholderTextLineStyle** | PlaceholderLineHeight, PlaceholderTextAlign, PlaceholderMaxLength, PlaceholderMaxLines |
| **其他** | Value, Placeholder, ErrorText, ShowErrorText, TextContentType, TextInputType, InputFilter, ShowPasswordText, ShowPasswordIcon, ShowCounter, ShowUnderline, DisplayMode, MaxViewLines, MinLines, CopyOptions, WidthAuto, SelectionMenuHidden, PasswordRules, EnableAutoFill, EnableAutoFillAnimation |

#### 核心属性示例

```cpp
// 字体属性
ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(FontStyle, FontSize, Dimension, PROPERTY_UPDATE_MEASURE);
ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(FontStyle, TextColor, Color, PROPERTY_UPDATE_MEASURE_SELF);
ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(FontStyle, FontWeight, FontWeight, PROPERTY_UPDATE_MEASURE);
ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(FontStyle, FontFamily, std::vector<std::string>, PROPERTY_UPDATE_MEASURE);

// 文本布局属性
ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(TextLineStyle, TextAlign, TextAlign, PROPERTY_UPDATE_MEASURE_SELF);
ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(TextLineStyle, MaxLength, uint32_t, PROPERTY_UPDATE_MEASURE);
ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(TextLineStyle, MaxLines, uint32_t, PROPERTY_UPDATE_MEASURE);

// 值属性
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Value, std::u16string, PROPERTY_UPDATE_NORMAL);
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Placeholder, std::u16string, PROPERTY_UPDATE_MEASURE);

// 输入类型
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(TextInputType, TextInputType, PROPERTY_UPDATE_MEASURE);
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(TextContentType, TextContentType, PROPERTY_UPDATE_MEASURE);
```

### TextFieldPaintProperty

**源码位置**：[text_field_paint_property.h](../../frameworks/core/components_ng/pattern/text_field/text_field_paint_property.h)

#### 渲染属性

| 属性 | 类型 | 说明 |
|-----|------|------|
| PlaceholderColor | Color | 占位符颜色 |
| CursorColor | Color | 光标颜色 |
| CursorWidth | Dimension | 光标宽度 |
| SelectedBackgroundColor | Color | 选中背景色 |
| InputStyle | InputStyle | 输入样式 |
| BackgroundColor | Color | 背景色 |
| PressBgColor | Color | 按下背景色 |
| HoverBgColor | Color | 悬停背景色 |
| PreviewTextStart/End | int32_t | 预览文本范围 |
| PreviewTextStyle | string | 预览文本样式 |
| InnerBorderWidth | Dimension | 内边框宽度 |
| InnerBorderColor | Color | 内边框颜色 |

---

## 布局算法

### TextFieldLayoutAlgorithm

**源码位置**：[text_field_layout_algorithm.h](../../frameworks/core/components_ng/pattern/text_field/text_field_layout_algorithm.h)

#### 继承关系

```
LayoutAlgorithm (基类)
    ↓
TextAdaptFontSizer (字体自适应)
    ↓
TextFieldLayoutAlgorithm (TextField布局算法基类)
    ↓
    ├── TextInputLayoutAlgorithm (单行输入布局)
    └── TextAreaLayoutAlgorithm (多行输入布局)
```

#### 核心功能

1. **文本测量**：测量文本内容的尺寸
2. **段落创建**：创建 Paragraph 进行文本布局
3. **光标计算**：计算光标位置和尺寸
4. **选择区域**：计算文本选择的矩形区域
5. **装饰器布局**：布局计数器、错误提示等
6. **字体自适应**：动态调整字体大小

#### 布局流程

```
┌─────────────────────────────────────────────────────────┐
│  Measure 阶段                                            │
│  1. MeasureContent() - 测量内容尺寸                      │
│  2. ConstructTextStyles() - 构建文本样式                 │
│  3. CreateParagraphAndLayout() - 创建段落并布局          │
│  4. GetTextRect() - 获取文本区域                         │
│  5. CounterNodeMeasure() - 测量计数器节点                │
│  6. ErrorLayout() - 布局错误提示                         │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│  Layout 阶段                                             │
│  1. Layout() - 布局子节点                                │
│  2. CounterLayout() - 布局计数器                         │
│  3. UpdateTextRect() - 更新文本区域                      │
│  4. PositionChild() - 定位子节点                         │
└─────────────────────────────────────────────────────────┘
```

#### 关键方法

| 方法 | 说明 |
|-----|------|
| `MeasureContent()` | 测量内容尺寸 |
| `CreateParagraphAndLayout()` | 创建段落并布局 |
| `GetTextRect()` | 获取文本区域 |
| `UpdateTextStyle()` | 更新文本样式 |
| `CounterLayout()` | 布局计数器 |
| `ErrorLayout()` | 布局错误提示 |
| `DidExceedMaxLines()` | 检查是否超过最大行数 |
| `GetSuitableSize()` | 获取合适的尺寸 |

---

## 事件系统

### TextFieldEventHub

**源码位置**：[text_field_event_hub.h](../../frameworks/core/components_ng/pattern/text_field/text_field_event_hub.h)

#### 事件类型

| 事件 | 回调签名 | 说明 |
|-----|---------|------|
| `onEditChanged` | `void(bool)` | 编辑状态变化 |
| `onSubmit` | `void(int32_t, TextFieldCommonEvent&)` | 提交事件 |
| `onChange` | `void(const ChangeValueInfo&)` | 内容变化 |
| `onWillChange` | `bool(const ChangeValueInfo&)` | 内容将要变化 |
| `onSelectionChange` | `void(int32_t, int32_t)` | 选择范围变化 |
| `onCopy` | `void(const std::u16string&)` | 复制事件 |
| `onCut` | `void(const std::u16string&)` | 剪切事件 |
| `onPaste` | `void(const std::u16string&)` | 粘贴事件 |
| `onContentSizeChange` | `void(float, float)` | 内容尺寸变化 |
| `onScroll` | `OnScrollEvent` | 滚动事件 |
| `onInputFilterError` | `void(const std::u16string&)` | 输入过滤错误 |
| `onWillInsertValue` | `bool(const InsertValueInfo&)` | 将要插入值 |
| `onDidInsertValue` | `void(const InsertValueInfo&)` | 已插入值 |
| `onWillDelete` | `bool(const DeleteValueInfo&)` | 将要删除 |
| `onDidDelete` | `void(const DeleteValueInfo&)` | 已删除 |
| `onSecurityStateChange` | `void(bool)` | 安全状态变化 |
| `onWillAttachIME` | `void(IMEClient&)` | 将要附加IME |

#### 数据结构

**ChangeValueInfo**：
```cpp
struct ChangeValueInfo {
    std::u16string value;           // 新值
    PreviewText previewText;        // 预览文本
    TextRange rangeBefore;          // 变化前的范围
    TextRange rangeAfter;           // 变化后的范围
    std::u16string oldContent;      // 旧内容
    PreviewText oldPreviewText;     // 旧预览文本
};
```

**InsertValueInfo**：
```cpp
struct InsertValueInfo {
    int32_t insertOffset;           // 插入位置
    std::u16string insertValue;     // 插入值
};
```

**DeleteValueInfo**：
```cpp
struct DeleteValueInfo {
    int32_t deleteOffset;           // 删除位置
    TextDeleteDirection direction;  // 删除方向
    std::u16string deleteValue;     // 删除值
};
```

---

## IME集成

### TextInputClient 接口实现

TextFieldPattern 实现了完整的 TextInputClient 接口，与系统IME进行交互。

#### IME交互流程

```
┌─────────────────────────────────────────────────────────┐
│  用户点击输入框                                          │
│  TextFieldPattern 获得 Focus                            │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│  请求软键盘                                              │
│  TextFieldPattern::RequestKeyboard()                    │
│  → TextInputProxy::Attach()                             │
│  → 系统IME服务                                          │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│  IME输入事件                                             │
│  系统IME → TextInputProxy → TextFieldPattern            │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│  处理输入                                                │
│  TextFieldPattern::InsertValue()                        │
│  - 更新文本内容                                         │
│  - 更新UI显示                                           │
│  - 触发事件                                             │
└─────────────────────────────────────────────────────────┘
```

#### 预览文本机制

IME输入时支持预览：

```cpp
int32_t TextFieldPattern::SetPreviewText(
    const std::u16string& previewValue, const PreviewRange range)
{
    // 1. 保存当前文本状态
    // 2. 设置预览文本
    // 3. 触发UI更新
    // 4. 返回预览文本ID
}

void TextFieldPattern::FinishTextPreview()
{
    // 1. 确认预览文本
    // 2. 应用到实际内容
    // 3. 清除预览状态
}
```

---

## 文本选择与拖拽

### 文本选择

#### 选择模式

```cpp
enum class SelectionMode {
    SELECT,        // 普通选择
    SELECT_ALL,    // 全选
    NONE           // 无选择
};
```

#### 选择流程

```
用户手势
  → TextGestureSelector 识别
  → TextFieldPattern::HandleSelect()
  → TextSelector 更新选择范围
  → CreateHandles() 创建手柄
  → UpdateSelection() 更新UI
```

### 文本拖拽

作为 TextDragBase 的实现，TextFieldPattern 支持文本拖拽：

```cpp
// 创建拖拽节点
const RefPtr<FrameNode>& TextFieldPattern::MoveDragNode()
{
    // 1. 检查是否有选择内容
    // 2. 调用 TextDragPattern::CreateDragNode()
    // 3. 返回拖拽节点
}

// 实现TextDragBase接口
bool IsTextArea() const override;
const RectF& GetTextRect() const override;
RectF GetTextContentRect(bool isActualText) const override;
float GetLineHeight() const override;
std::vector<RectF> GetTextBoxes() override;
OffsetF GetParentGlobalOffset() const override;
const RefPtr<Paragraph>& GetDragParagraph() const override;
```

---

## 内容控制器

### ContentController

**源码位置**：[content_controller.h](../../frameworks/core/components_ng/pattern/text_field/content_controller.h)

#### 功能职责

1. **文本内容管理**：存储和管理文本内容
2. **光标位置**：维护光标位置
3. **选择范围**：维护文本选择范围
4. **编辑历史**：支持撤销/重做
5. **内容过滤**：输入过滤器

#### 关键方法

| 方法 | 说明 |
|-----|------|
| `GetTextValue()` | 获取文本内容 |
| `GetTextUtf16Value()` | 获取UTF16文本 |
| `SetText()` | 设置文本内容 |
| `GetCursorPosition()` | 获取光标位置 |
| `SetCursorPosition()` | 设置光标位置 |
| `GetSelection()` | 获取选择范围 |
| `SetSelection()` | 设置选择范围 |

---

## 自动填充

### AutoFillController

**源码位置**：[auto_fill_controller.h](../../frameworks/core/components_ng/pattern/text_field/auto_fill_controller.h)

#### 功能职责

1. **自动填充请求**：向系统请求自动填充
2. **自动填充响应**：处理系统返回的填充数据
3. **填充应用**：将填充数据应用到输入框

#### 触发条件

```cpp
enum class RequestAutoFillReason {
    UNKNOWN = 0,
    SINGLE_CLICK,              // 单击
    FIELD_FOCUS_EVENT,         // 焦点事件
    REQUEST_AGAIN_NOT_FOCUS,   // 重新请求
    TEXT_MENU_MANUAL_REQUEST   // 手动请求
};
```

---

## 前端接口层

### JSTextField

**源码位置**：[js_textfield.h](../../frameworks/bridge/declarative_frontend/jsview/js_textfield.h)

#### 前端API

| ArkTS API | C++ 实现 | 说明 |
|-----------|----------|------|
| `TextInput()` / `TextArea()` | `CreateTextInput/TextArea()` | 创建组件 |
| `.type()` | `SetType()` | 设置输入类型 |
| `.placeholder()` | `UpdatePlaceholder()` | 设置占位符 |
| `.placeholderColor()` | `SetPlaceholderColor()` | 占位符颜色 |
| `.placeholderFont()` | `SetPlaceholderFont()` | 占位符字体 |
| `.textAlign()` | `SetTextAlign()` | 文本对齐 |
| `.caretColor()` | `SetCaretColor()` | 光标颜色 |
| `.caretStyle()` | `SetCaretStyle()` | 光标样式 |
| `.maxLength()` | `SetMaxLength()` | 最大长度 |
| `.maxLines()` | `SetMaxLines()` | 最大行数 |
| `.fontSize()` | `SetFontSize()` | 字体大小 |
| `.fontColor()` | `SetTextColor()` | 字体颜色 |
| `.fontWeight()` | `SetFontWeight()` | 字体粗细 |
| `.fontStyle()` | `SetFontStyle()` | 字体样式 |
| `.fontFamily()` | `SetFontFamily()` | 字体家族 |
| `.onChange()` | `SetOnChange()` | 内容变化事件 |
| `.onSubmit()` | `SetOnSubmit()` | 提交事件 |
| `.onEditChanged()` | `SetOnEditChanged()` | 编辑状态变化 |
| `.onCopy()` | `SetOnCopy()` | 复制事件 |
| `.onCut()` | `SetOnCut()` | 剪切事件 |
| `.onPaste()` | `SetOnPaste()` | 粘贴事件 |
| `.showPasswordIcon()` | `SetShowPasswordIcon()` | 显示密码图标 |
| `.passwordIcon()` | `SetPasswordIcon()` | 密码图标 |
| `.enableAutoFill()` | `SetEnableAutoFill()` | 启用自动填充 |

---

## 执行流程

### 组件创建流程

```
ArkTS代码
  TextInput({ placeholder: '请输入' })
    ↓
JSTextField::CreateTextInput()
  [js_textfield.cpp]
    ↓
TextFieldModelNG::CreateTextInput()
  [text_field_model_ng.cpp]
    ↓
FrameNode::GetOrCreateFrameNode(tag, nodeId, ...)
  创建 TextFieldPattern 实例
    ↓
TextFieldPattern::OnAttachToFrameNode()
  1. 初始化 ContentController
  2. 初始化 AutoFillController
  3. 注册字体管理器
  4. 初始化选择功能
  5. 初始化手势识别
  6. 初始化拖拽功能
    ↓
ViewStackProcessor::Push(frameNode)
  推入视图栈
```

### 输入处理流程

```
用户输入（键盘或IME）
    ↓
TextInputClient::InsertValue()
  [text_field_pattern.cpp]
    ↓
ContentController::UpdateText()
  更新文本内容
    ↓
TextFieldPattern::UpdateEditingValue()
  更新编辑值
    ↓
TextFieldPattern::UpdateParagraph()
  更新段落布局
    ↓
TextFieldPattern::MarkNeedRender()
  标记需要重绘
    ↓
TextFieldEventHub::FireOnChange()
  触发onChange事件
```

### 选择流程

```
用户长按或拖拽
    ↓
TextGestureSelector::HandleLongPress/HandleDrag
  识别手势
    ↓
TextFieldPattern::UpdateSelection()
  更新选择范围
    ↓
TextFieldPattern::CreateHandles()
  创建选择手柄
    ↓
TextFieldPattern::ShowSelectOverlay()
  显示选择菜单
```

---

## 关键实现细节

### 1. 撤销/重做机制

TextFieldPattern 实现了完整的撤销/重做功能：

```cpp
std::deque<InputOperation> operationRecords_;       // 操作历史
std::deque<InputOperation> redoOperationRecords_;  // 重做历史

enum class InputOperation {
    INSERT,
    DELETE_BACKWARD,
    DELETE_FORWARD,
    CURSOR_UP,
    CURSOR_DOWN,
    CURSOR_LEFT,
    CURSOR_RIGHT,
    SET_PREVIEW_TEXT,
    SET_PREVIEW_FINISH,
    INPUT,
    PERFORM_ACTION,
};
```

### 2. 密码模式

密码输入时显示掩码：

- 默认使用 `•` 或 `*` 掩码
- 支持显示/隐藏切换
- 支持自定义密码图标

### 3. 输入过滤

支持正则表达式过滤：

```cpp
void SetInputFilter(const std::string& value,
    const std::function<void(const std::u16string&)>&& func)
```

### 4. 字符计数

实时显示字符计数：

```cpp
// 启用计数器
void SetShowCounter(bool value)

// 设置计数器文本颜色
void SetCounterTextColor(const Color& value)

// 设置计数器类型
void SetCounterType(int32_t value)
```

### 5. 错误提示

支持显示错误文本和样式：

```cpp
void SetShowError(const std::u16string& errorText, bool visible)
```

### 6. 下划线效果

动态下划线显示输入状态：

```cpp
// 普通状态颜色
Color normalColor
// 输入状态颜色
Color typingColor
// 错误状态颜色
Color errorColor
// 禁用状态颜色
Color disableColor
```

### 7. 预览文本

IME输入时的预览机制：

1. 用户通过IME输入
2. 调用 `SetPreviewText()` 显示预览
3. 用户确认输入
4. 调用 `FinishTextPreview()` 应用预览

---

## 与TextArea的关系

### 继承关系

```
TextFieldPattern (基类)
    ↓
TextAreaPattern (多行输入)
```

### 主要区别

| 特性 | TextField (TextInput) | TextArea |
|-----|----------------------|----------|
| **默认行数** | 单行 | 多行 |
| **布局算法** | TextInputLayoutAlgorithm | TextAreaLayoutAlgorithm |
| **高度策略** | 固定高度 | 自适应高度 |
| **滚动** | 通常不需要 | 支持垂直滚动 |
| **maxLines** | 默认1 | 可配置多行 |
| **minLines** | 不支持 | 支持 |
| **换行符** | 不支持 | 支持 |

### IsTextArea() 判断

```cpp
bool TextFieldPattern::IsTextArea() const
{
    auto textFieldLayoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(textFieldLayoutProperty, false);
    auto type = textFieldLayoutProperty->GetTextInputType().value_or(TextInputType::UNSPECIFIED);
    return type == TextInputType::MULTILINE;
}
```

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

// 限制长度
TextInput()
  .maxLength(11)
  .type(InputType.Number)

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
  .backgroundColor(Color.Pink)
  .borderColor(Color.Blue)
  .borderWidth(2)
  .borderRadius(10)
  .padding(10)
  .fontSize(16)
  .fontColor(Color.Black)
```

### 控制器使用

```typescript
// 创建控制器
textController: TextInputController = new TextInputController()

// 使用控制器
TextInput({ textController: this.textController })

// 通过控制器操作
this.textController.setText('新文本')
this.textController.delete(0, 5)  // 删除前5个字符
```

---

## 调试指南

### 常用日志标签

| 日志标签 | 说明 |
|---------|------|
| `AceLogTag::ACE_TEXT_FIELD` | TextField相关日志 |

### 关键断点位置

| 文件 | 方法 | 说明 |
|-----|------|------|
| text_field_pattern.cpp | `OnModifyDone()` | 修改完成 |
| text_field_pattern.cpp | `InsertValue()` | 插入文本 |
| text_field_pattern.cpp | `DeleteBackward()` | 向后删除 |
| text_field_layout_algorithm.cpp | `MeasureContent()` | 内容测量 |
| text_field_event_hub.cpp | `FireOnChange()` | 触发变化事件 |

---

## 参考源码

### 核心文件

1. **Pattern层**：
   - [text_field_pattern.h](../../frameworks/core/components_ng/pattern/text_field/text_field_pattern.h)
   - [text_field_pattern.cpp](../../frameworks/core/components_ng/pattern/text_field/text_field_pattern.cpp)

2. **Layout算法**：
   - [text_field_layout_algorithm.h](../../frameworks/core/components_ng/pattern/text_field/text_field_layout_algorithm.h)
   - [text_field_layout_algorithm.cpp](../../frameworks/core/components_ng/pattern/text_field/text_field_layout_algorithm.cpp)

3. **属性**：
   - [text_field_layout_property.h](../../frameworks/core/components_ng/pattern/text_field/text_field_layout_property.h)
   - [text_field_paint_property.h](../../frameworks/core/components_ng/pattern/text_field/text_field_paint_property.h)

4. **事件**：
   - [text_field_event_hub.h](../../frameworks/core/components_ng/pattern/text_field/text_field_event_hub.h)

5. **渲染**：
   - [text_field_paint_method.h](../../frameworks/core/components_ng/pattern/text_field/text_field_paint_method.h)
   - [text_field_paint_method.cpp](../../frameworks/core/components_ng/pattern/text_field/text_field_paint_method.cpp)

6. **修饰器**：
   - [text_field_content_modifier.h](../../frameworks/core/components_ng/pattern/text_field/text_field_content_modifier.h)
   - [text_field_overlay_modifier.h](../../frameworks/core/components_ng/pattern/text_field/text_field_overlay_modifier.h)
   - [text_field_foreground_modifier.h](../../frameworks/core/components_ng/pattern/text_field/text_field_foreground_modifier.h)

7. **控制器**：
   - [text_field_controller.h](../../frameworks/core/components_ng/pattern/text_field/text_field_controller.h)
   - [content_controller.h](../../frameworks/core/components_ng/pattern/text_field/content_controller.h)
   - [auto_fill_controller.h](../../frameworks/core/components_ng/pattern/text_field/auto_fill_controller.h)

8. **Model层**：
   - [text_field_model_ng.h](../../frameworks/core/components_ng/pattern/text_field/text_field_model_ng.h)
   - [text_field_model_ng.cpp](../../frameworks/core/components_ng/pattern/text_field/text_field_model_ng.cpp)

9. **前端接口**：
   - [js_textfield.h](../../frameworks/bridge/declarative_frontend/jsview/js_textfield.h)
   - [js_textfield.cpp](../../frameworks/bridge/declarative_frontend/jsview/js_textfield.cpp)

---

**文档维护**：如有疑问或需要补充，请参考上述源码位置。
