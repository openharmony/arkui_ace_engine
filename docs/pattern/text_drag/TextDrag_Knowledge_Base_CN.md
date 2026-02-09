# ArkUI TextDrag 组件知识库

> **文档版本**：v1.0
> **更新时间**：2026-02-04
> **源码版本**：OpenHarmony ace_engine (master 分支)

---

## 📚 目录

1. [概述](#概述)
2. [目录结构](#目录结构)
3. [核心类继承关系](#核心类继承关系)
4. [Pattern层详解](#pattern层详解)
5. [拖拽数据结构](#拖拽数据结构)
6. [拖拽渲染](#拖拽渲染)
7. [拖拽计算](#拖拽计算)
8. [执行流程](#执行流程)
9. [关键实现细节](#关键实现细节)
10. [与TextPattern/TextFieldPattern的关系](#与textpatterntextfieldpattern的关系)

---

## 概述

### 组件定位

**TextDrag 组件**是 OpenHarmony ArkUI 框架中的**文本拖拽预览组件**，用于在文本选择后显示拖拽预览效果。它是一个独立的 FrameNode，悬浮在主内容之上，展示被选中的文本内容。

### 技术架构

```
┌─────────────────────────────────────────────────────────┐
│  文本选择状态                                             │
│  TextPattern 或 TextFieldPattern                         │
│  用户选择文本区域                                         │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│  TextDragBase 接口                                       │
│  源码：text_drag_base.h                                  │
│  提供拖拽所需的文本信息                                   │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│  TextDragPattern 创建拖拽节点                            │
│  源码：text_drag_pattern.cpp:87-123                      │
│  1. CreateDragNode() - 创建拖拽FrameNode                 │
│  2. CalculateTextDragData() - 计算拖拽数据               │
│  3. Initialize() - 初始化拖拽内容                        │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│  拖拽预览渲染                                             │
│  TextDragPaintMethod + TextDragOverlayModifier           │
│  绘制拖拽预览效果                                         │
└─────────────────────────────────────────────────────────┘
```

### 功能特性

| 功能类别 | 具体功能 |
|---------|---------|
| **拖拽预览** | 显示选中文本的预览效果 |
| **自适应尺寸** | 根据选中内容自动计算预览框大小 |
| **圆角背景** | 支持圆角背景渲染 |
| **透明度效果** | 支持半透明拖拽效果 |
| **图片支持** | 支持包含图片的文本拖拽 |
| **动画支持** | 支持拖拽动画效果 |
| **多行处理** | 正确处理跨行文本选择 |

---

## 目录结构

### 核心代码目录

```
frameworks/core/components_ng/pattern/text_drag/
├── text_drag_base.h               # TextDrag 基类接口
├── text_drag_pattern.h            # TextDrag Pattern 定义
├── text_drag_pattern.cpp          # TextDrag Pattern 实现
├── text_drag_paint_method.h       # 拖拽绘制方法
├── text_drag_paint_method.cpp     # 拖拽绘制实现
├── text_drag_overlay_modifier.h   # 拖拽覆盖修饰器
└── text_drag_overlay_modifier.cpp # 拖拽覆盖修饰器实现
```

### 代码规模

| 项目 | 说明 |
|-----|------|
| 核心文件 | 7 个文件 |
| Pattern文件 | text_drag_pattern.h (285行) |
| Paint文件 | text_drag_paint_method.h/cpp |
| Modifier文件 | text_drag_overlay_modifier.h/cpp |

---

## 核心类继承关系

### 类继承图

```
AceType (基类)
    ↓
TextDragBase (拖拽基类接口)
    ↑
    │ (被继承)
    │
TextPattern (纯文本显示)
TextFieldPattern (文本输入)
```

```
Pattern (基类)
    ↓
TextDragPattern (拖拽预览Pattern)
```

### TextDragBase 接口

**源码位置**：[text_drag_base.h](../../frameworks/core/components_ng/pattern/text_drag/text_drag_base.h)

#### 核心接口方法

```cpp
class TextDragBase : public virtual AceType {
public:
    // 判断是否为 TextArea
    virtual bool IsTextArea() const = 0;

    // 获取文本区域
    virtual const RectF& GetTextRect() const = 0;
    virtual RectF GetTextContentRect(bool isActualText = false) const = 0;

    // 获取行高
    virtual float GetLineHeight() const = 0;

    // 获取文本框（选中区域）
    virtual std::vector<RectF> GetTextBoxes() = 0;

    // 获取父节点全局偏移
    virtual OffsetF GetParentGlobalOffset() const = 0;

    // 拖拽节点管理
    virtual const RefPtr<FrameNode>& MoveDragNode() = 0;
    virtual const RefPtr<Paragraph>& GetDragParagraph() const = 0;

    // 拖拽生命周期回调
    virtual void OnDragNodeFloating() {}
    virtual void CloseSelectOverlay() = 0;
    virtual void CloseHandleAndSelect() { CloseSelectOverlay(); }

    // 手柄显示控制
    virtual void ShowHandles(const bool isNeedShowHandles) { ShowHandles(); }
    virtual void ShowHandles() { CreateHandles(); }
    virtual bool IsHandlesShow() { return true; }
    virtual void CreateHandles() {}

    // 键盘控制
    virtual bool CloseKeyboard(bool forceClose) = 0;

    // 拖拽坐标
    virtual OffsetF GetDragUpperLeftCoordinates() = 0;

    // Span图片布局
    virtual void InitSpanImageLayout(
        const std::vector<int32_t>& placeholderIndex,
        const std::vector<RectF>& rectsForPlaceholders,
        OffsetF contentOffset) {}

    virtual OffsetF GetContentOffset() { return OffsetF(0, 0); }

    // AI实体识别相关
    virtual void ResetAISelected(AIResetSelectionReason reason) {}
    virtual void ShowAIEntityMenuForCancel() {}
    virtual bool IsPreviewMenuShow() { return false; }

    // 拖拽节点分离回调
    virtual void OnDragNodeDetachFromMainTree() {}
};
```

#### 实现类

TextDragBase 被以下类实现：

1. **TextPattern** - 纯文本显示组件
2. **TextFieldPattern** - 文本输入组件（包括 TextArea）

---

## Pattern层详解

### TextDragPattern

**源码位置**：[text_drag_pattern.h](../../frameworks/core/components_ng/pattern/text_drag/text_drag_pattern.h)

#### 类定义

```cpp
class TextDragPattern : public Pattern {
    DECLARE_ACE_TYPE(TextDragPattern, Pattern);

public:
    TextDragPattern() = default;
    ~TextDragPattern() override = default;

    // 创建拖拽节点
    static RefPtr<FrameNode> CreateDragNode(const RefPtr<FrameNode>& hostNode);

    // 初始化拖拽数据
    void Initialize(const RefPtr<Paragraph>& paragraph, const TextDragData& data)
    {
        paragraph_ = paragraph;
        textDragData_ = data;
    }

    // 更新段落
    void UpdateParagraph(const RefPtr<Paragraph>& paragraph)
    {
        paragraph_ = paragraph;
    }

    // 创建绘制方法
    RefPtr<NodePaintMethod> CreateNodePaintMethod() override;

    // 获取拖拽信息
    const WeakPtr<Paragraph>& GetParagraph() const { return paragraph_; }
    const RectF& GetTextRect() const { return textDragData_.textRect_; }
    float GetFrameWidth() const { return textDragData_.frameWidth_; }
    float GetFrameHeight() const { return textDragData_.frameHeight_; }
    float GetLineHeight() const { return textDragData_.lineHeight_; }
    const SelectPositionInfo& GetSelectPosition() const { return textDragData_.selectPosition_; }
    bool OneLineSelected() const { return textDragData_.oneLineSelected_; }

    // 路径生成
    const std::shared_ptr<RSPath>& GetClipPath();
    const std::shared_ptr<RSPath>& GetBackgroundPath();
    const std::shared_ptr<RSPath>& GetSelBackgroundPath();

    // 动画状态
    bool IsAnimating() {
        return overlayModifier_ && overlayModifier_->IsAnimating();
    }

    // 节点分离回调
    void OnDetachFromMainTree() override;

protected:
    // 计算拖拽数据
    static TextDragData CalculateTextDragData(
        RefPtr<TextDragBase>& pattern,
        RefPtr<FrameNode>& dragNode,
        const RefPtr<FrameNode>& hostNode = nullptr);

    // 布局交换
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty,
        const DirtySwapConfig& config) override;

    // 路径生成方法
    std::shared_ptr<RSPath> GenerateClipPath();
    std::shared_ptr<RSPath> GenerateBackgroundPath(float offset, float radiusRatio = 1.0f);
    std::shared_ptr<RSPath> GenerateSelBackgroundPath(float offset);

    // 手柄计算
    static RectF GetHandler(const bool isLeftHandler,
        const std::vector<RectF> boxes,
        const RectF contentRect,
        const OffsetF globalOffset,
        const OffsetF textStartOffset);

    static void AdjustHandlers(const RectF contentRect,
        RectF& leftHandler, RectF& rightHandler);

    // 其他辅助方法
    void GenerateBackgroundPoints(std::vector<TextPoint>& points,
        float offset, bool needAdjust = true);
    void CalculateLineAndArc(std::vector<TextPoint>& points,
        std::shared_ptr<RSPath>& path, float radiusRatio);
    void CalculateLine(std::vector<TextPoint>& points, std::shared_ptr<RSPath>& path);

    static void CalculateOverlayOffset(RefPtr<FrameNode>& dragNode,
        OffsetF& offset, const RefPtr<FrameNode>& hostNode = nullptr);
    static void DropBlankLines(std::vector<RectF>& boxes);

private:
    RefPtr<TextDragOverlayModifier> overlayModifier_;
    TextDragData textDragData_;
    WeakPtr<Paragraph> paragraph_;
    RefPtr<Paragraph> animatingParagraph_;
    std::shared_ptr<RSPath> clipPath_;
    std::shared_ptr<RSPath> backGroundPath_;
    std::shared_ptr<RSPath> selBackGroundPath_;
    std::list<RefPtr<FrameNode>> imageChildren_;
    std::vector<RectF> rectsForPlaceholders_;
    TextDragInfo info_;
    std::function<void()> onDetachFromMainTree_ = nullptr;
};
```

#### 核心职责

1. **拖拽节点创建**：`CreateDragNode()` 静态方法创建拖拽 FrameNode
2. **拖拽数据计算**：`CalculateTextDragData()` 计算拖拽预览的位置和尺寸
3. **绘制管理**：通过 `CreateNodePaintMethod()` 创建绘制方法
4. **路径生成**：生成裁剪路径、背景路径、选中背景路径
5. **生命周期管理**：处理拖拽节点的附加和分离

---

## 拖拽数据结构

### TextDragData

**源码位置**：[text_drag_pattern.h:54-73](../../frameworks/core/components_ng/pattern/text_drag/text_drag_pattern.h)

```cpp
struct TextDragData {
    TextDragData() {}
    TextDragData(RectF textRect, float frameWidth, float frameHeight,
        float lineHeight, float lastLineHeight)
        : textRect_(textRect), frameWidth_(frameWidth),
          frameHeight_(frameHeight), lineHeight_(lineHeight),
          lastLineHeight_(lastLineHeight)
    {}

    RectF textRect_;              // 文本区域
    float frameWidth_ = 0;        // 框架宽度
    float frameHeight_ = 0;       // 框架高度
    float lineHeight_ = 0;        // 行高
    float lastLineHeight_ = 0;    // 最后一行高度
    SelectPositionInfo selectPosition_; // 选择位置信息
    bool oneLineSelected_ = false; // 是否单行选中

    void initSelecitonInfo(SelectPositionInfo selectionInfo, bool oneLineSelected)
    {
        selectPosition_ = selectionInfo;
        oneLineSelected_ = oneLineSelected;
    }
};
```

### SelectPositionInfo

**源码位置**：[text_drag_pattern.h:34-52](../../frameworks/core/components_ng/pattern/text_drag/text_drag_pattern.h)

```cpp
struct SelectPositionInfo {
    SelectPositionInfo() {}
    SelectPositionInfo(float startX, float startY, float endX, float endY)
        : startX_(startX), startY_(startY), endX_(endX), endY_(endY)
    {}

    void InitGlobalInfo(float globalX, float globalY)
    {
        globalX_ = globalX;
        globalY_ = globalY;
    }

    float startX_ = 0;      // 起始X坐标
    float startY_ = 0;      // 起始Y坐标
    float endX_ = 0;        // 结束X坐标
    float endY_ = 0;        // 结束Y坐标
    float globalX_ = 0;     // 全局X坐标
    float globalY_ = 0;     // 全局Y坐标
};
```

### TextDragInfo

```cpp
struct TextDragInfo {
    // 拖拽手柄动画信息
    // (具体定义在其他头文件中)
};
```

---

## 拖拽渲染

### TextDragPaintMethod

**源码位置**：[text_drag_paint_method.h](../../frameworks/core/components_ng/pattern/text_drag/text_drag_paint_method.h)

#### 类定义

```cpp
class TextDragPaintMethod : public NodePaintMethod {
    DECLARE_ACE_TYPE(TextDragPaintMethod, NodePaintMethod);

public:
    TextDragPaintMethod(const WeakPtr<TextDragPattern>& textDragPattern,
        const RefPtr<TextDragOverlayModifier>& overlayModifier);

    ~TextDragPaintMethod() override = default;

    RefPtr<Modifier> GetOverlayModifier(PaintWrapper* paintWrapper) override;
    void UpdateOverlayModifier(PaintWrapper* paintWrapper) override;

private:
    WeakPtr<TextDragPattern> textDragPattern_;
    RefPtr<TextDragOverlayModifier> overlayModifier_;
};
```

### TextDragOverlayModifier

**源码位置**：[text_drag_overlay_modifier.h](../../frameworks/core/components_ng/pattern/text_drag/text_drag_overlay_modifier.h)

#### 类定义

```cpp
class TextDragOverlayModifier : public OverlayModifier {
    DECLARE_ACE_TYPE(TextDragOverlayModifier, OverlayModifier);

public:
    explicit TextDragOverlayModifier(const WeakPtr<TextDragPattern>& textDragPattern);
    ~TextDragOverlayModifier() override = default;

    void onDraw(DrawingContext& context) override;

    // 动画状态
    bool IsAnimating() const { return isAnimating_; }
    void SetAnimating(bool animating) { isAnimating_ = animating; }

private:
    WeakPtr<TextDragPattern> textDragPattern_;
    bool isAnimating_ = false;
};
```

#### 渲染流程

```
┌─────────────────────────────────────────────────────────┐
│  TextDragOverlayModifier::onDraw()                      │
│  1. 获取 Paragraph                                       │
│  2. 获取 ClipPath（裁剪路径）                            │
│  3. 获取 BackgroundPath（背景路径）                      │
│  4. 获取 SelBackgroundPath（选中背景路径）               │
│  5. 绘制背景                                             │
│  6. 绘制选中内容                                         │
│  7. 应用裁剪                                             │
└─────────────────────────────────────────────────────────┘
```

---

## 拖拽计算

### CreateDragNode 流程

**源码位置**：[text_drag_pattern.cpp:87-123](../../frameworks/core/components_ng/pattern/text_drag/text_drag_pattern.cpp)

```cpp
RefPtr<FrameNode> TextDragPattern::CreateDragNode(const RefPtr<FrameNode>& hostNode)
{
    CHECK_NULL_RETURN(hostNode, nullptr);

    // 1. 获取 TextDragBase 接口
    auto hostPattern = hostNode->GetPattern<TextDragBase>();

    // 2. 创建唯一的节点ID
    const auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();

    // 3. 创建 TextDrag FrameNode
    auto dragNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTDRAG_ETS_TAG, nodeId,
        []() { return AceType::MakeRefPtr<TextDragPattern>(); });

    // 4. 复制前景色
    auto dragContext = dragNode->GetRenderContext();
    auto hostContext = hostNode->GetRenderContext();
    if (hostContext->HasForegroundColor()) {
        dragContext->UpdateForegroundColor(hostContext->GetForegroundColor().value());
    }

    // 5. 获取 TextDragPattern 并计算拖拽数据
    auto dragPattern = dragNode->GetPattern<TextDragPattern>();
    auto data = CalculateTextDragData(hostPattern, dragNode, hostNode);

    // 6. 初始化拖拽内容
    dragPattern->Initialize(hostPattern->GetDragParagraph(), data);
    dragPattern->SetLastLineHeight(data.lineHeight_);

    // 7. 设置拖拽节点尺寸
    CalcSize size(NG::CalcLength(dragPattern->GetFrameWidth()),
                  NG::CalcLength(dragPattern->GetFrameHeight()));
    dragNode->GetLayoutProperty()->UpdateUserDefinedIdealSize(size);

    // 8. 设置分离回调
    auto onDetachFromMainTreeCallback = [weak = WeakPtr<TextDragBase>(hostPattern)]() {
        auto textDragBasePattern = weak.Upgrade();
        CHECK_NULL_VOID(textDragBasePattern);
        textDragBasePattern->OnDragNodeDetachFromMainTree();
    };
    dragPattern->SetOnDetachFromMainTree(std::move(onDetachFromMainTreeCallback));

    return dragNode;
}
```

### CalculateTextDragData 流程

**源码位置**：[text_drag_pattern.cpp:157-200](../../frameworks/core/components_ng/pattern/text_drag/text_drag_pattern.cpp)

```cpp
TextDragData TextDragPattern::CalculateTextDragData(
    RefPtr<TextDragBase>& pattern,
    RefPtr<FrameNode>& dragNode,
    const RefPtr<FrameNode>& hostNode)
{
    // 1. 计算文本起始偏移
    OffsetF textStartOffset = {
        pattern->GetTextRect().GetX(),
        pattern->IsTextArea() ? pattern->GetTextRect().GetY()
                              : pattern->GetTextContentRect().GetY()
    };

    // 2. 获取内容区域
    auto contentRect = pattern->GetTextContentRect(true);

    // 3. 计算偏移量
    float bothOffset = TEXT_DRAG_OFFSET.ConvertToPx() * CONSTANT_HALF;

    // 4. 获取选中文本框
    auto boxes = pattern->GetTextBoxes();
    CHECK_NULL_RETURN(!boxes.empty(), {});

    // 5. 去除空白行
    DropBlankLines(boxes);

    // 6. 获取全局偏移并计算Overlay偏移
    auto globalOffset = pattern->GetParentGlobalOffset();
    CalculateOverlayOffset(dragNode, globalOffset, hostNode);

    // 7. 计算左右手柄位置
    RectF leftHandler = GetHandler(true, boxes, contentRect, globalOffset, textStartOffset);
    RectF rightHandler = GetHandler(false, boxes, contentRect, globalOffset, textStartOffset);

    // 8. 调整手柄位置
    AdjustHandlers(contentRect, leftHandler, rightHandler);

    // 9. 计算宽度和高度
    float width = rightHandler.GetX() - leftHandler.GetX();
    float height = rightHandler.GetY() - leftHandler.GetY() + rightHandler.Height();

    // 10. 计算全局坐标
    auto dragOffset = TEXT_DRAG_OFFSET.ConvertToPx();
    float globalX = leftHandler.GetX() + globalOffset.GetX() - dragOffset;
    float globalY = leftHandler.GetY() + globalOffset.GetY() - dragOffset;

    // 11. 处理最小宽度
    auto box = boxes.front();
    float delta = 0.0f;
    if (leftHandler.GetY() == rightHandler.GetY()) {
        if (width + bothOffset < TEXT_DRAG_MIN_WIDTH.ConvertToPx()) {
            delta = TEXT_DRAG_MIN_WIDTH.ConvertToPx() - (width + bothOffset);
            width += delta;
            globalX -= delta / CONSTANT_HALF;
        }
    } else {
        globalX = contentRect.Left() + globalOffset.GetX() - dragOffset;
        dragPattern->AdjustMaxWidth(width, contentRect, boxes);
    }

    // 12. 设置内容和位置
    // ... (省略部分代码)

    return TextDragData(...);
}
```

### 路径生成算法

#### GenerateBackgroundPath

**源码位置**：[text_drag_pattern.cpp](../../frameworks/core/components_ng/pattern/text_drag/text_drag_pattern.cpp)

```cpp
std::shared_ptr<RSPath> TextDragPattern::GenerateBackgroundPath(
    float offset, float radiusRatio)
{
    std::vector<TextPoint> points;
    GenerateBackgroundPoints(points, offset, true);

    auto path = std::make_shared<RSPath>();
    CalculateLineAndArc(points, path, radiusRatio);

    return path;
}
```

#### GenerateBackgroundPoints

生成背景路径的关键点，包括：
1. 左上角点
2. 右上角点
3. 右下角点
4. 左下角点
5. 圆角控制点

---

## 执行流程

### 拖拽创建流程

```
┌─────────────────────────────────────────────────────────┐
│  用户选择文本                                            │
│  TextPattern 或 TextFieldPattern                         │
│  用户长按或拖拽选择文本                                   │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│  创建拖拽节点                                            │
│  TextDragPattern::CreateDragNode(hostNode)              │
│  1. 创建 FrameNode(V2::TEXTDRAG_ETS_TAG)                │
│  2. 创建 TextDragPattern 实例                           │
│  3. CalculateTextDragData() - 计算拖拽数据               │
│  4. Initialize(paragraph, data) - 初始化                 │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│  添加到Overlay                                            │
│  OverlayManager::AddOverlayNode(dragNode)               │
│  拖拽节点作为Overlay显示在主内容之上                       │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│  渲染拖拽预览                                            │
│  TextDragPaintMethod::GetOverlayModifier()              │
│  TextDragOverlayModifier::onDraw()                      │
│  1. 获取/生成路径                                        │
│  2. 绘制圆角背景                                         │
│  3. 绘制选中文本                                         │
└─────────────────────────────────────────────────────────┘
```

### 拖拽更新流程

```
┌─────────────────────────────────────────────────────────┐
│  选择变化                                                │
│  用户调整选择范围                                        │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│  重新计算拖拽数据                                        │
│  CalculateTextDragData()                                 │
│  1. 获取新的 TextBoxes                                   │
│  2. 重新计算手柄位置                                     │
│  3. 更新尺寸和位置                                       │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│  更新拖拽节点                                            │
│  dragNode->GetLayoutProperty()->UpdateUserDefinedIdealSize() │
│  MarkDirty() - 标记需要重新布局和渲染                     │
└─────────────────────────────────────────────────────────┘
```

### 拖拽销毁流程

```
┌─────────────────────────────────────────────────────────┐
│  用户取消选择或完成操作                                  │
│  - 点击空白区域                                          │
│  - 按下ESC键                                            │
│  - 完成拖拽操作                                         │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│  关闭选择Overlay                                         │
│  TextDragBase::CloseSelectOverlay()                     │
│  TextFieldPattern::CloseSelectOverlay()                 │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│  从Overlay移除拖拽节点                                   │
│  OverlayManager::RemoveOverlayNode(dragNode)            │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│  触发分离回调                                            │
│  TextDragPattern::OnDetachFromMainTree()                │
│  调用 onDetachFromMainTree_ 回调                         │
│  通知宿主节点拖拽已分离                                  │
└─────────────────────────────────────────────────────────┘
```

---

## 关键实现细节

### 1. 手柄位置计算

**GetHandler** 方法计算左右手柄的位置：

```cpp
RectF GetHandler(const bool isLeftHandler,
    const std::vector<RectF> boxes,
    const RectF contentRect,
    const OffsetF globalOffset,
    const OffsetF textStartOffset)
{
    // isLeftHandler = true: 计算左手柄
    // isLeftHandler = false: 计算右手柄

    if (isLeftHandler) {
        // 获取第一个可见的box
        return GetFirstBoxRect(boxes, contentRect, textStartOffset.GetY());
    } else {
        // 获取最后一个可见的box
        return GetLastBoxRect(boxes, contentRect, textStartOffset.GetY());
    }
}
```

### 2. 跨行选择处理

当选择跨越多行时：

1. **左手柄**：位于第一行选中文本的左上角
2. **右手柄**：位于最后一行选中文本的右下角
3. **拖拽预览**：包含从第一行到最后一行的所有选中内容

### 3. 单行选择优化

当只有一行被选中时（`oneLineSelected_ = true`）：

- 拖拽预览宽度受限，最小为 `TEXT_DRAG_MIN_WIDTH` (64.0_vp)
- 背景路径使用简化的圆角矩形

### 4. 圆角背景实现

拖拽预览使用圆角背景，圆角半径为 `TEXT_DRAG_RADIUS` (18.0_vp)：

```cpp
constexpr Dimension TEXT_DRAG_RADIUS = 18.0_vp;
```

路径生成通过 `GenerateBackgroundPath()` 实现：
1. 生成四个角的控制点
2. 使用 `RSPath` 的 `arcTo()` 方法绘制圆角
3. 使用 `lineTo()` 方法连接直线段

### 5. 透明度效果

拖拽预览的背景色使用半透明效果：

```cpp
constexpr uint32_t TEXT_DRAG_COLOR_BG = 0xf2ffffff;
```

### 6. 图片支持

拖拽预览支持包含图片的文本：

```cpp
// 初始化Span图片布局
void InitSpanImageLayout(const std::list<RefPtr<FrameNode>>& imageChildren,
    const std::vector<RectF>& rectsForPlaceholders)
{
    imageChildren_ = imageChildren;
    rectsForPlaceholders_ = rectsForPlaceholders;
}
```

渲染时会将图片与文本一起绘制。

### 7. 动画支持

拖拽预览支持动画效果：

```cpp
bool IsAnimating() {
    return overlayModifier_ && overlayModifier_->IsAnimating();
}
```

---

## 与TextPattern/TextFieldPattern的关系

### TextDragBase 接口实现

| 实现类 | 说明 |
|-------|------|
| **TextPattern** | 纯文本显示组件，实现 TextDragBase 接口以支持文本拖拽 |
| **TextFieldPattern** | 文本输入组件，实现 TextDragBase 接口以支持输入内容的拖拽 |

### 调用关系

```
TextPattern / TextFieldPattern
    ↓ 实现
TextDragBase 接口
    ↓ 使用
TextDragPattern::CreateDragNode()
    ↓ 创建
独立的 TextDrag FrameNode (拖拽预览)
```

### 数据流向

```
TextPattern/TextFieldPattern
    ↓ 提供
- GetTextRect() - 文本区域
- GetTextBoxes() - 选中文本框
- GetParentGlobalOffset() - 全局偏移
- GetDragParagraph() - 文本段落
    ↓ 使用
TextDragPattern::CalculateTextDragData()
    ↓ 生成
TextDragData (拖拽数据)
    ↓ 初始化
TextDragPattern
    ↓ 渲染
拖拽预览效果
```

---

## 使用示例

### TextPattern 中的使用

TextPattern 在用户选择文本时创建拖拽预览：

```cpp
// TextPattern 实现了 TextDragBase
class TextPattern : public Pattern, public TextDragBase {
    // ...
};
```

### TextFieldPattern 中的使用

TextFieldPattern 在用户选择输入内容时创建拖拽预览：

```cpp
// TextFieldPattern 实现了 TextDragBase
class TextFieldPattern : public ScrollablePattern, public TextDragBase {
    // ...
};
```

---

## 调试指南

### 常用日志标签

| 日志标签 | 说明 |
|---------|------|
| `AceLogTag::ACE_TEXT` | 文本拖拽相关日志 |

### 关键断点位置

| 文件 | 方法 | 说明 |
|-----|------|------|
| text_drag_pattern.cpp | `CreateDragNode()` | 拖拽节点创建 |
| text_drag_pattern.cpp | `CalculateTextDragData()` | 拖拽数据计算 |
| text_drag_overlay_modifier.cpp | `onDraw()` | 拖拽渲染 |
| text_drag_pattern.cpp | `GenerateBackgroundPath()` | 背景路径生成 |

---

## 参考源码

### 核心文件

1. **基类接口**：
   - [text_drag_base.h](../../frameworks/core/components_ng/pattern/text_drag/text_drag_base.h)

2. **Pattern层**：
   - [text_drag_pattern.h](../../frameworks/core/components_ng/pattern/text_drag/text_drag_pattern.h)
   - [text_drag_pattern.cpp](../../frameworks/core/components_ng/pattern/text_drag/text_drag_pattern.cpp)

3. **渲染层**：
   - [text_drag_paint_method.h](../../frameworks/core/components_ng/pattern/text_drag/text_drag_paint_method.h)
   - [text_drag_paint_method.cpp](../../frameworks/core/components_ng/pattern/text_drag/text_drag_paint_method.cpp)

4. **修饰器**：
   - [text_drag_overlay_modifier.h](../../frameworks/core/components_ng/pattern/text_drag/text_drag_overlay_modifier.h)
   - [text_drag_overlay_modifier.cpp](../../frameworks/core/components_ng/pattern/text_drag/text_drag_overlay_modifier.cpp)

---

**文档维护**：如有疑问或需要补充，请参考上述源码位置。
