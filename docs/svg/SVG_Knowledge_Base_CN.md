# SVG 组件深入知识库

> **文档定位**：本文档是对 `svg/CLAUDE.md` 的深入补充，专注于设计决策、实现原理、问题排查等高级内容
> **快速参考**：请参考 [SVG/CLAUDE.md](../../frameworks/core/components_ng/svg/CLAUDE.md)
> **版本**：v1.0 | **更新**：2026-02-03

---

## 目录

1. [设计决策分析](#1-设计决策分析)
2. [实现原理深挖](#2-实现原理深挖)
3. [问题排查手册](#3-问题排查手册)
4. [跨组件交互](#4-跨组件交互)
5. [性能优化](#5-性能优化)

---

## 1. 设计决策分析

### 1.1 SVG XML 解析方案

**背景**：SVG 是基于 XML 的矢量图形格式，需要解析 XML 结构

**当前实现**：使用 Skia 内置的 SkDOM 解析器

**源码位置**：`svg_dom.cpp:128-135`

```cpp
bool SvgDom::ParseSvg(SkStream& svgStream)
{
    SkDOM xmlDom;
    if (!xmlDom.build(svgStream)) {
        LOGE("Failed to parse xml file.");
        return false;
    }
    // ... translate to SvgNode tree
}
```

**设计考量**：

| 优点 | 说明 |
|------|------|
| **无额外依赖** | Skia 是 ACE 引擎的图形依赖，自带 XML 解析能力 |
| **性能良好** | SkDOM 是为图形场景优化的轻量级 DOM |

**待优化方向**：

> **注意**：当前渲染引擎已切换到 Rosen，SkDOM 对 Skia 的硬依赖存在架构耦合问题。未来可考虑：
> - 引入平台无关的 XML 解析器（如 tinyxml2）
> - 解耦 XML 解析与图形渲染依赖

**替代方案对比**：

| 方案 | 优点 | 缺点 | 当前状态 |
|------|------|------|------------|
| SkDOM（当前） | 无额外依赖，性能良好 | 与 Skia 强耦合 | 正在使用 |
| tinyxml2 | 成熟稳定，API 简洁 | 额外依赖 | 可选方案 |
| expat | 流式解析，内存友好 | 需手动构建 DOM 树 | 架构复杂度高 |
| libxml2 | 功能完整 | 过于重量级 | 不适合嵌入式场景 |

---

### 1.2 为什么采用三层继承架构？

**背景**：SVG 元素具有不同的行为特征

**决策**：设计三层继承结构

**源码位置**：`svg_node.h:44-46`

```cpp
// three level inherit class, for example:
// 1. SvgMask::SvgQuote::SvgNode
// 2. SvgPath::SvgGraphic::SvgNode
```

**层级划分**：

```
┌─────────────────────────────────────────────────────────┐
│  Level 1: SvgNode (基础层)                               │
│  - 所有 SVG 元素的基类                                    │
│  - 通用属性和绘制管道                                      │
│  - 样式继承和属性管理                                      │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│  Level 2: 中间层（分类抽象）                               │
│  - SvgGraphic: 可绘制的图形元素                           │
│  - SvgGroup: 容器元素                                     │
│  - SvgQuote: 引用元素（defs, mask, filter, pattern）     │
│  - SvgGradient: 渐变元素                                  │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│  Level 3: 具体元素实现                                     │
│  - SvgRect, SvgCircle, SvgPath (继承自 SvgGraphic)       │
│  - SvgSvg, SvgG, SvgUse (继承自 SvgGroup)                │
│  - SvgClipPath, SvgMask, SvgFilter (继承自 SvgQuote)     │
└─────────────────────────────────────────────────────────┘
```

**设计理由**：

| 层级 | 职责 | 好处 |
|------|------|------|
| **SvgNode** | 统一接口和通用逻辑 | 多态处理，代码复用 |
| **中间层** | 分类抽象 | 按特性分组，避免重复 |
| **实现层** | 具体元素 | 专注元素特性 |

**替代方案考虑**：

| 方案 | 优点 | 缺点 | 未选择原因 |
|------|------|------|------------|
| 单层继承 | 结构简单 | 所有逻辑集中在一个类，难以维护 | 扩展性差 |
| 组合模式 | 灵活，运行时组合 | 过度设计，性能开销 | 继承已满足需求 |
| 接口 + 组合 | 解耦 | C++ 接口抽象性能损耗 | 继承更直接 |

---

### 1.3 为什么使用 href 引用而不是直接复制内容？

**背景**：SVG 支持通过 `<use>` 元素和 href 属性复用定义

**决策**：实现引用机制，通过 ID 查找复用节点

**源码位置**：`svg_context.cpp:29-36`

```cpp
RefPtr<SvgNode> SvgContext::GetSvgNodeById(const std::string& id) const
{
    auto item = idMapper_.find(id);
    if (item != idMapper_.end()) {
        return item->second.Upgrade();
    }
    return nullptr;
}
```

**设计理由**：

| 优点 | 说明 |
|------|------|
| **减少文件大小** | 定义一次，多处使用 |
| **便于维护** | 修改定义，所有引用自动更新 |
| **符合 SVG 规范** | 标准做法 |
| **内存高效** | 共享节点实例 |

**引用场景**：

1. **`<use>` 元素**：复用图形定义
2. **`fill="url(#gradient)"`**：引用渐变
3. **`clip-path="url(#clip)"`**：引用剪切路径
4. **`mask="url(#mask)"`**：引用遮罩
5. **`filter="url(#filter)"`**：引用滤镜

---

### 1.4 为什么需要 SvgContext 作为解析上下文？

**背景**：SVG 解析需要维护全局状态

**决策**：设计 SvgContext 作为解析上下文管理器

**源码位置**：`svg_context.h:69-180`

```cpp
class SvgContext : public AceType {
    // ID to node mapping for href references
    std::unordered_map<std::string, WeakPtr<SvgNode>> idMapper_;

    // Animator management for animations
    std::unordered_map<int32_t, WeakPtr<Animator>> animators_;

    // CSS class style mapping
    ClassStyleMap styleMap_;

    // ViewBox and ViewPort
    Rect rootViewBox_;
    Size viewPort_;

    // Dimension normalization function
    FuncNormalizeToPx funcNormalizeToPx_;

    // Multi-instance callbacks
    std::map<WeakPtr<CanvasImage>, FuncAnimateFlush> animateCallbacks_;
};
```

**设计理由**：

| 功能 | 说明 |
|------|------|
| **ID 映射** | 解析时收集所有带 ID 的节点，供 href 引用查找 |
| **样式管理** | CSS 类样式映射 |
| **动画管理** | 管理所有动画的播放/暂停 |
| **坐标系统** | 根 ViewBox 和 ViewPort 信息 |
| **多实例共享** | 同一 SvgDom 可被多个 CanvasImage 引用 |

**多实例共享机制**：

```
SvgDom (共享)
    ↓
SvgContext (共享)
    ├── idMapper_ - 共享节点映射
    ├── animators_ - 共享动画管理
    └── animateCallbacks_ - 每个实例独立回调
        ├── CanvasImage A 回调
        └── CanvasImage B 回调
```

---

### 1.5 为什么支持 SVG 2.0 特性版本控制？

**背景**：SVG 2.0 引入了一些新特性，但需要向后兼容

**决策**：通过 `usrConfigVersion` 控制特性启用

**源码位置**：`svg_context.h:154-162`

```cpp
enum SVG_FEATURE_SUPPORT {
    SVG_FEATURE_SUPPORT_UNDEFINE = 0,
    SVG_FEATURE_SUPPORT_TWO = 2,
};

class SvgContext {
    uint32_t usrConfigVersion_ = SVG_FEATURE_SUPPORT_UNDEFINE;
};
```

**版本控制影响**：

| 特性 | SVG 1.1 | SVG 2.0 |
|------|---------|---------|
| 渐变实现 | SvgGradient | SvgLinearGradient/SvgRadialGradient |
| 属性继承 | 全部继承 | 有条件继承（通过 featureEnable） |
| 滤镜效果 | 基础支持 | 扩展支持 |

**源码位置**：`svg_node.cpp:77-81`

```cpp
void SvgNode::InheritAttr(const SvgBaseAttribute& parent)
{
    auto featureEnable = SvgUtils::IsFeatureEnable(SVG_FEATURE_SUPPORT_TWO, GetUsrConfigVersion());
    attributes_.Inherit(parent, !featureEnable);
}
```

---

## 2. 实现原理深挖

### 2.1 SVG 解析流程

**完整解析流程**：

```
┌─────────────────────────────────────────────────────────┐
│  1. SkDOM 解析                                           │
│                                                          │
│    SkDOM xmlDom;                                         │
│    xmlDom.build(svgStream);  // XML → DOM 树            │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│  2. 节点树转换                                           │
│                                                          │
│    root_ = TranslateSvgNode(xmlDom, xmlDom.getRootNode()); │
│    // 遍历 XML DOM，创建 SvgNode 树                      │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│  3. 元素工厂创建                                         │
│                                                          │
│    CreateSvgNodeFromDom();                              │
│    // 根据 tagName 查找工厂函数创建具体元素              │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│  4. 属性解析                                             │
│                                                          │
│    ParseAttrs(xmlDom, xmlNode, svgNode);                │
│    // 解析所有属性，包括 style 和 class                  │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│  5. 样式初始化                                           │
│                                                          │
│    InitStyles();                                        │
│    // DFS 遍历，初始化样式继承                           │
└─────────────────────────────────────────────────────────┘
```

**源码位置**：`svg_dom.cpp:146-150`

```cpp
RefPtr<SvgNode> SvgDom::TranslateSvgNode(const SkDOM& dom, const SkDOM::Node* xmlNode, const RefPtr<SvgNode>& parent)
{
    auto root = CreateSvgNodeFromDom(dom, xmlNode, parent);
    CHECK_NULL_RETURN(root, nullptr);
    std::stack<SvgTranslateProcessInfo> translateTaskSt;
    // ... 使用栈进行深度优先遍历
}
```

---

### 2.2 绘制管道详解

**完整绘制流程**：

```
┌─────────────────────────────────────────────────────────┐
│  1. 入口: Draw()                                         │
│                                                          │
│    void SvgNode::Draw(RSCanvas& canvas, ...)            │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│  2. 画布检查: OnCanvas()                                 │
│                                                          │
│    保存画布状态 (RSFuncContext)                         │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│  3. 剪裁: OnClipPath()                                   │
│                                                          │
│    if (hrefClipPath_) {                                 │
│        auto clipPath = context->GetSvgNodeById(id);     │
│        canvas.ClipPath(clipPath->AsPath());             │
│    }                                                    │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│  4. 遮罩: OnMask()                                       │
│                                                          │
│    if (hrefMaskId_) {                                   │
│        auto mask = context->GetSvgNodeById(id);         │
│        canvas.SaveLayer();                              │
│        mask->OnMaskEffect();                            │
│    }                                                    │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│  5. 滤镜: OnFilter()                                     │
│                                                          │
│    if (hrefFilterId_) {                                 │
│        auto filter = context->GetSvgNodeById(id);       │
│        filter->OnFilterEffect();                        │
│    }                                                    │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│  6. 变换: OnTransform()                                  │
│                                                          │
│    if (!transform_.empty()) {                           │
│        canvas.ConcatMatrix(matrix);                     │
│    }                                                    │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│  7. 绘制: OnDraw()                                       │
│                                                          │
│    // 子类实现具体绘制逻辑                               │
│    // SvgGraphic: 填充和描边                            │
│    // SvgGroup: 递归绘制子节点                          │
│    // SvgQuote: 绘制引用内容                            │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│  8. 恢复画布状态                                         │
│                                                          │
│    canvas.RestoreToCount(savedCount);                   │
└─────────────────────────────────────────────────────────┘
```

**源码位置**：`svg_node.cpp:300-400+`

---

### 2.3 属性继承机制

**继承标志控制**：

**源码位置**：`svg_node.h:261-265`

```cpp
// 控制属性继承行为的标志
bool hrefFill_ = true;      // 从 href 引用获取填充属性
bool hrefRender_ = true;     // 从 href 引用获取渲染属性
bool passStyle_ = true;      // 将样式属性传递给子节点
bool inheritStyle_ = true;   // 从父节点继承样式属性
bool drawTraversed_ = true;  // 启用 OnDraw 遍历
```

**不同元素类型的标志配置**：

| 元素类型 | hrefFill | hrefRender | passStyle | inheritStyle | drawTraversed |
|----------|----------|------------|-----------|--------------|---------------|
| **Graphic** (rect, circle...) | true | true | false | true | true |
| **Group** (g, svg) | true | true | true | true | true |
| **Quote** (defs, mask, filter) | true | false | true | false | false |
| **Gradient** | - | - | - | - | false |

**继承流程**：

```
父节点 SvgBaseAttribute
        ↓
    InheritAttr()
        ↓
    子节点合并属性
        ├── fillState.Inherit()
        ├── strokeState.Inherit()
        └── clipState.Inherit()
        ↓
    特殊处理：featureEnable 检查
        ├── SVG 1.1: 全部继承
        └── SVG 2.0: 有条件继承
```

---

### 2.4 坐标系统和长度缩放

**SvgLengthScaleRule** 处理不同的坐标单位：

**源码位置**：`base/svg_length_scale_rule.h`

| 单位类型 | 描述 | 使用场景 |
|----------|------|----------|
| `USER_SPACE_ON_USE` | 使用当前用户坐标系 | 变换、剪切路径 |
| `OBJECT_BOUNDING_BOX` | 使用引用元素的边界框 | 渐变、图案 |
| `STROKE_WIDTH` | 相对于描边宽度 | 某些特效 |

**长度转换流程**：

```cpp
// svg_node.cpp
double SvgNode::ConvertDimensionToPx(
    const Dimension& value,
    const Size& viewPort,
    SvgLengthType type) const
{
    // 1. 获取上下文
    auto svgContext = svgContext_.Upgrade();
    CHECK_NULL_RETURN(svgContext, 0.0);

    // 2. 使用归一化函数转换
    return svgContext->NormalizeToPx(value);
}
```

**viewBox 到 ViewPort 的转换**：

```cpp
// svg_attributes_parser.cpp
void SvgAttributesParser::ComputeScale(
    const Size& viewBox,
    const Size& viewPort,
    const SvgPreserveAspectRatio& preserveAspectRatio,
    float& scaleX,
    float& scaleY)
{
    // 1. 计算基础缩放
    scaleX = viewPort.Width() / viewBox.Width();
    scaleY = viewPort.Height() / viewBox.Height();

    // 2. 应用 preserveAspectRatio
    if (preserveAspectRatio.svgAlign != SvgAlign::ALIGN_NONE) {
        // MEET: 保持比例，适应 viewport
        if (preserveAspectRatio.meetOrSlice == SvgMeetOrSlice::MEET) {
            scaleX = scaleY = std::min(scaleX, scaleY);
        }
        // SLICE: 保持比例，覆盖 viewport
        else {
            scaleX = scaleY = std::max(scaleX, scaleY);
        }
    }

    // 3. 计算平移以对齐
    ComputeTranslate(viewBox, viewPort, scaleX, scaleY,
        preserveAspectRatio.svgAlign, translateX, translateY);
}
```

---

### 2.5 渐变实现

**渐变类型层次**：

```
SvgNode
    ↓
SvgGradient
    ↓
    ├── SvgLinearGradient (SVG 2.0)
    └── SvgRadialGradient (SVG 2.0)
```

**线性渐变属性**：

```cpp
struct SvgLinearGradientAttribute {
    Dimension x1 = Dimension(0.0, DimensionUnit::PERCENT);
    Dimension y1 = Dimension(0.0, DimensionUnit::PERCENT);
    Dimension x2 = Dimension(1.0, DimensionUnit::PERCENT);
    Dimension y2 = Dimension(0.0, DimensionUnit::PERCENT);
    std::string gradientTransform;
    SvgLengthScaleUnit gradientUnits = OBJECT_BOUNDING_BOX;
    SvgSpreadMethod spreadMethod = PAD;
};
```

**渐变填充流程**：

```
解析 <linearGradient>
        ↓
    收集 <stop> 子节点
        ↓
    构建 Gradient 对象
        ├── 颜色列表
        ├── 位置列表
        └── 变换矩阵
        ↓
    创建 RSBrush
        ├── SetGradientLinear()
        └── AttachBrush()
        ↓
    绘制路径
```

---

### 2.6 动画系统

**动画类型**：

| 类型 | 元素 | 描述 |
|------|------|------|
| `animate` | 任意属性 | 数值、颜色等属性动画 |
| `animateMotion` | 路径运动 | 沿路径移动 |
| `animateTransform` | 变换 | 旋转、缩放、倾斜等 |

**动画初始化**：

**源码位置**：`svg_animation.cpp`

```cpp
void SvgAnimation::OnInitStyle()
{
    // 1. 获取目标属性
    auto attributeName = animateAttr_.attributeName;

    // 2. 创建属性动画
    switch (svgAnimateType_) {
        case SvgAnimateType::ANIMATE:
            CreatePropertyAnimation(originalValue, callback);
            break;
        case SvgAnimateType::ANIMATE_TRANSFORM:
            AnimateTransform(animate_, originalValue);
            break;
        // ...
    }

    // 3. 添加到 SvgContext
    auto context = GetContext().Upgrade();
    context->AddAnimator(uniqueId, animator_);
}
```

**动画控制**：

```cpp
// svg_context.cpp
void SvgContext::ControlAnimators(bool play)
{
    for (auto it = animators_.begin(); it != animators_.end();) {
        auto animator = it->second.Upgrade();
        if (!animator) {
            it = animators_.erase(it);
            continue;
        }
        if (play) {
            animator->Play();
        } else {
            animator->Pause();
        }
        ++it;
    }
}
```

---

## 3. 问题排查手册

### 3.1 SVG 不显示

**症状**：加载 SVG 文件后没有显示任何内容

**诊断流程**：

```
开始
  ↓
SVG 文件是否有效？
  ├─ 否 → 检查 XML 语法
  │        ├─ 使用 XML 验证器验证
  │        └─ 检查是否为有效的 SVG
  │
  ├─ 是 → ParseSvg() 是否成功？
  │        ├─ 失败 → 检查 SkDOM 解析日志
  │        └─ 成功 → 继续
  │
  ├─ root_ 是否为空？
  │        ├─ 是 → 检查根元素是否为 <svg>
  │        └─ 否 → 继续
  │
  └─ DrawImage() 是否被调用？
           ├─ 否 → 检查 Image 组件加载流程
           └─ 是 → 检查画布状态
```

**常见原因与解决方案**：

| 原因 | 现象 | 解决方案 |
|------|------|----------|
| XML 语法错误 | ParseSvg 返回 false | 修复 SVG 文件语法 |
| 根元素不是 `<svg>` | root_ 为空 | 确保 SVG 以 `<svg>` 开头 |
| 画布未正确初始化 | 绘制无效果 | 检查 RSCanvas 状态 |
| viewBox 设置错误 | 显示空白/部分显示 | 检查 viewBox 与 ViewPort 关系 |

---

### 3.2 渐变不显示

**症状**：使用渐变填充时显示为黑色或透明

**可能原因**：

| 原因 | 说明 | 解决方案 |
|------|------|----------|
| ID 引用错误 | `fill="url(#gradient)"` 中的 ID 不存在 | 确保渐变定义的 ID 匹配 |
| 缺少 `<stop>` | 渐变没有颜色停止点 | 添加至少两个 `<stop>` |
| gradientUnits 错误 | 坐标系统不匹配 | 检查 `gradientUnits` 属性 |
| 渐变范围错误 | x1, y1, x2, y2 设置不当 | 调整渐变坐标 |

**验证代码**：

```xml
<!-- 正确的渐变定义 -->
<defs>
  <linearGradient id="myGradient" x1="0%" y1="0%" x2="100%" y2="0%">
    <stop offset="0%" stop-color="red" />
    <stop offset="100%" stop-color="blue" />
  </linearGradient>
</defs>

<rect fill="url(#myGradient)" width="100" height="100" />
```

---

### 3.3 动画不播放

**症状**：SVG 中的动画元素没有任何动画效果

**诊断流程**：

```
开始
  ↓
isStatic 标志是否为 false？
  ├─ 是 → 动画已禁用
  │        └── 检查 Image 组件配置
  │
  ├─ 否 → animator 是否注册？
  │        ├─ 否 → 检查动画元素解析
  │        └─ 是 → 继续
  │
  └── ControlAnimation(true) 是否被调用？
           ├─ 否 → 调用播放控制
           └─ 是 → 检查动画属性
```

**常见原因**：

| 原因 | 说明 | 解决方案 |
|------|------|----------|
| SVG 被标记为静态 | isStatic = true | 检查 ImageSourceInfo 配置 |
| 动画元素未解析 | 元素名称错误 | 确保使用 `<animate>`, `<animateTransform>` 等 |
| 持续时间未设置 | dur 属性缺失 | 添加 `dur="1s"` 等持续时间 |
| 回调未注册 | CanvasImage 未注册刷新回调 | 检查 SetAnimationCallback 调用 |

---

### 3.4 裁剪/遮罩不生效

**症状**：clip-path 或 mask 属性没有效果

**可能原因**：

| 原因 | 说明 | 解决方案 |
|------|------|----------|
| ID 引用错误 | href 指向不存在的元素 | 确保引用的 ID 存在 |
| clipPathUnits 错误 | 坐标系统不匹配 | 调整 `clipPathUnits` 属性 |
| 遮罩内容为空 | mask 内没有图形 | 添加有效的图形内容 |
| 绘制顺序错误 | 效果应用顺序问题 | 确保效果在绘制前应用 |

---

### 3.5 内存泄漏排查

**症状**：大量 SVG 加载后内存持续增长

**检查点**：

1. **WeakPtr 使用是否正确**：

> **线程安全提示**：当前实现中 `idMapper_` 访问未使用锁保护，若存在多线程访问场景需要添加同步机制。

**当前源码**：
```cpp
// svg_context.h:164
std::unordered_map<std::string, WeakPtr<SvgNode>> idMapper_;
```

**建议的线程安全实现**（如果需要多线程访问）：
```cpp
// 在 svg_context.h 中添加互斥锁
private:
    std::mutex idMapperMutex_;  // 添加互斥锁保护
    std::unordered_map<std::string, WeakPtr<SvgNode>> idMapper_;

// 定期清理失效的弱引用（线程安全版本）
void CleanDeadReferences() {
    std::lock_guard<std::mutex> lock(idMapperMutex_);
    for (auto it = idMapper_.begin(); it != idMapper_.end();) {
        if (!it->second.Upgrade()) {
            it = idMapper_.erase(it);
        } else {
            ++it;
        }
    }
}
```

**注意事项**：
- 当前代码假设在 UI 线程单线程环境下运行（如 `AnimateFlush()` 中的 `CHECK_RUN_ON(UI)` 检查）
- 若 SvgContext 需要跨线程共享，必须添加锁保护

2. **动画回调是否正确清理**：
```cpp
// svg_context.cpp:128-136
void SvgContext::AnimateFlush()
{
    for (auto it = animateCallbacks_.begin(); it != animateCallbacks_.end();) {
        if (it->first.Upgrade()) {
            ++it;
        } else {
            it = animateCallbacks_.erase(it);  // 清理失效回调
        }
    }
}
```

3. **SvgDom 生命周期管理**：
- 确保不再使用的 SvgDom 被正确释放
- 检查是否有循环引用

---

## 4. 跨组件交互

### 4.1 SVG 与 Image 组件的关系

**依赖关系**：

```
Image 组件
    ↓
CanvasImage (NG)
    ↓
SvgDom (共享)
    ├── SvgContext
    ├── SvgNode 树
    └── 动画管理器
```

**多实例共享**：

```cpp
// 同一个 SvgDom 可被多个 CanvasImage 引用
RefPtr<SvgDom> svgDom = SvgDom::CreateSvgDom(stream, src);
if (!svgDom) {
    LOGE("Failed to create SVG DOM");
    return;
}

// 实例 A
canvasImageA->SetSvgDom(svgDom);

// 实例 B - 共享同一个 SvgDom
canvasImageB->SetSvgDom(svgDom);

// 各自独立的刷新回调
svgDom->SetAnimationCallback(callbackA, imagePtrA);
svgDom->SetAnimationCallback(callbackB, imagePtrB);
```

---

### 4.2 SVG 与 Rosen 渲染引擎

**渲染路径**：

```
SvgNode::Draw()
    ↓
RSCanvas (Rosen 封装)
    ↓
RSRecordingPath (录制路径)
    ↓
Rosen RenderService
    ↓
Skia GPU 渲染
```

**绘制调用**：

```cpp
// svg_graphic.cpp
void SvgGraphic::OnGraphicFill()
{
    if (!path_.has_value() || !rsCanvas_) {
        return;
    }
    rsCanvas_->AttachBrush(fillBrush_);
    rsCanvas_->DrawPath(path_.value());
    rsCanvas_->DetachBrush();
}
```

---

### 4.3 SVG 与其他图形格式对比

| 特性 | SVG | PNG/JPG | Lottie |
|------|-----|---------|--------|
| **格式** | 矢量 XML | 位图 | JSON 动画 |
| **可缩放** | 是 | 否 | 是（基于矢量） |
| **动画** | 内置支持 | 否 | 内置支持 |
| **文件大小** | 小（简单图形）/大（复杂） | 大 | 中等 |
| **渲染性能** | 解析开销 + 绘制开销 | 解码开销 + 绘制开销 | 解析 + 每帧重绘 |
| **适用场景** | 图标、简单插图 | 照片、复杂图形 | 复杂动画 |

---

## 5. 性能优化

### 5.1 解析性能

**优化策略**：

| 操作 | 性能影响 | 优化建议 |
|------|----------|----------|
| SkDOM 解析 | 高 | 复杂 SVG 考虑预解析 |
| 节点树构建 | 中 | 减少不必要的嵌套 |
| 样式计算 | 中 | 使用 class 减少重复样式 |

**缓存策略**：

> **注意**：以下示例需要考虑线程安全问题。在多线程环境下使用缓存时，应添加互斥锁保护。

```cpp
// 同一个 SVG 文件可以共享解析结果（线程安全版本）
static std::unordered_map<std::string, RefPtr<SvgDom>> svgDomCache_;
static std::mutex cacheMutex_;

RefPtr<SvgDom> GetCachedDom(const std::string& path) {
    std::lock_guard<std::mutex> lock(cacheMutex_);
    auto it = svgDomCache_.find(path);
    if (it != svgDomCache_.end()) {
        return it->second;
    }
    auto dom = SvgDom::CreateSvgDom(...);
    if (dom) {
        svgDomCache_[path] = dom;
    }
    return dom;
}
```

**注意事项**：
- 缓存中的 `RefPtr<SvgDom>` 会保持 SVG DOM 的引用，可能导致内存长期占用
- 建议添加缓存清理策略（如 LRU 淘汰、定期清理等）
- 在多线程环境下必须使用互斥锁保护缓存访问

---

### 5.2 渲染性能

**渲染路径优化**：

```
RSRecordingPath (录制)
    ↓
缓存路径对象
    ↓
避免重复构建路径
```

**绘制优化**：

```cpp
// 避免每帧都重新计算路径
if (!path_.has_value()) {
    path_ = AsPath(viewPort);  // 首次计算
}
rsCanvas_->DrawPath(path_.value());  // 直接使用
```

---

### 5.3 内存占用

**单个 SVG DOM 内存**：

| 组件 | 内存占用 |
|------|----------|
| SvgDom | ~1-2 KB |
| SvgContext | ~2-3 KB |
| 每个 SvgNode | ~0.5-1 KB |
| 属性数据 | ~0.5-1 KB |

**100 个简单 SVG**：约 200-500 KB

**优化建议**：
- 复用 SvgDom（多实例共享）
- 及时清理失效的弱引用
- 避免在 SVG 中嵌入过多数据（如 base64 图片）

---

### 5.4 动画性能

**动画触发频率**：

```
标准频率：约 16ms（60 FPS）
```

**优化建议**：
- 简化动画路径
- 减少同时播放的动画数量
- 使用 CSS transform 代替 animateTransform（在某些场景）

---

## 附录

### 相关文件清单

| 文件 | 行数 | 主要功能 |
|------|------|----------|
| `svg_dom.cpp` | ~500+ | SVG 解析主流程 |
| `svg_node.cpp` | ~800+ | 节点基础实现 |
| `svg_graphic.cpp` | ~400+ | 图形元素实现 |
| `svg_context.cpp` | ~190 | 上下文管理 |
| `svg_animation.cpp` | ~200+ | 动画实现 |

### 调试命令

```bash
# 查看 SVG 组件信息
hidumper -s WindowManagerService -a '-a Svg'

# 查看组件树
hidumper -s WindowManagerService -a '-a ComponentTree'

# 获取 SVG dump 信息
svgDom->GetDumpInfo();
```

### 参考文档

- [SVG/CLAUDE.md](../../frameworks/core/components_ng/svg/CLAUDE.md) - 快速参考
- [W3C SVG 1.1 规范](https://www.w3.org/TR/SVG11/)
- [W3C SVG 2.0 规范](https://www.w3.org/TR/SVG2/)
- [Skia 文档](https://api.skia.org/)

---

**文档版本历史**

| 版本 | 日期 | 更新内容 |
|-----|------|---------|
| v1.0 | 2026-02-03 | 初始版本：设计决策、实现原理、问题排查、跨组件交互、性能优化 |
