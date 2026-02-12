# ArcList 组件知识库

## 元信息

| 项目         | 内容                          |
|--------------|----------------------------------|
| 组件名       | ArcList（弧形列表）               |
| 分类         | 可滚动容器                        |
| 平台         | OpenHarmony 穿戴设备              |
| 版本         | 6.0                              |
| 作者         | ACE 引擎团队                     |
| 最后更新     | 2025-01-31                       |
| 状态         | 稳定版                           |

---

## 目录

- 1. 组件概述
  - 1.1 技术栈
  - 1.2 设计理念
  - 1.3 核心特性
  - 1.4 代码规模
- 2. 架构设计
  - 2.1 类层次结构
  - 2.2 调用链
  - 2.3 分层分析
- 3. 核心实现
  - 3.1 Pattern 层
  - 3.2 LayoutAlgorithm 层
  - 3.3 LayoutProperty 层
  - 3.4 ItemPattern 层
- 4. 关键算法
  - 4.1 动态缩放算法
  - 4.2 吸附滚动
  - 4.3 双向布局
  - 4.4 头部透明度渐变
- 5. 事件处理
  - 5.1 滚动事件
  - 5.2 数码表冠支持
  - 5.3 触摸事件
- 6. 完整 API 参考
  - 6.1 ArcListPattern API
  - 6.2 ArcListLayoutAlgorithm API
  - 6.3 ArcListLayoutProperty API
  - 6.4 ArcListItemPattern API
- 7. 使用示例
  - 7.1 基础用法
  - 7.2 带数码表冠
  - 7.3 带分组头部
- 8. 调试指南
  - 8.1 常见问题
  - 8.2 性能优化
  - 8.3 日志和诊断

---

## 1. 组件概述

ArcList 是专为**穿戴设备**（智能手表）设计的专用列表组件，采用弧形布局方式。

### 1.1 技术栈

```
┌─────────────────────────────────────────────────────────────┐
│                    应用层                                     │
│                   (ArkTS / JavaScript)                       │
└────────────────────────┬────────────────────────────────────┘
                         │
┌────────────────────────▼────────────────────────────────────┐
│                    桥接层                                     │
│              (声明式前端引擎)                                  │
│              pu_recycle_manager.ts                           │
└────────────────────────┬────────────────────────────────────┘
                         │
┌────────────────────────▼────────────────────────────────────┐
│                  框架层 (C++)                                 │
│  ┌─────────────────────────────────────────────────────┐   │
│  │  Pattern 层 (ArcListPattern)                         │   │
│  ├─────────────────────────────────────────────────────┤   │
│  │  Algorithm 层 (ArcListLayoutAlgorithm)               │   │
│  ├─────────────────────────────────────────────────────┤   │
│  │  Property 层 (ArcListLayoutProperty)                 │   │
│  └─────────────────────────────────────────────────────┘   │
└─────────────────────────────────────────────────────────────┘
                         │
┌────────────────────────▼────────────────────────────────────┐
│                    渲染层                                     │
│              (RenderContext / RenderNode)                    │
└─────────────────────────────────────────────────────────────┘
```

### 1.2 设计理念

ArcList 遵循以下设计原则：

1. **弧形布局**：列表项按弧形排列，而非传统线性布局
2. **动态缩放**：根据距离中心的远近，列表项自动缩放
3. **吸附滚动**：滚动停止时自动对齐到最近的列表项
4. **数码表冠支持**：支持旋转表冠输入，可调节灵敏度
5. **头部透明度渐变**：头部靠近顶部时逐渐变透明

### 1.3 核心特性

| 特性 | 描述 | 实现位置 |
|---------|-------------|-------------------------|
| 动态缩放 | 基于多项式的缩放计算 | arc_list_layout_algorithm.cpp:63-95 |
| 吸附滚动 | 自动居中对齐到最近项 | arc_list_pattern.cpp:293-355 |
| 数码表冠 | 三档灵敏度调节 | arc_list_pattern.h:82-91 |
| 粘性头部 | 透明度渐变效果 | arc_list_layout_algorithm.cpp:465-505 |
| 双向布局 | 从中心向两端布局 | arc_list_layout_algorithm.cpp:128-218 |

### 1.4 代码规模

```
frameworks/core/components_ng/pattern/arc_list/
├── arc_list_pattern.h             (136 行) - Pattern 类定义
├── arc_list_pattern.cpp           (477 行) - Pattern 实现
├── arc_list_layout_algorithm.h    (145 行) - 算法类定义
├── arc_list_layout_algorithm.cpp  (636 行) - 布局算法实现
├── arc_list_layout_property.h     (106 行) - 属性类定义
├── arc_list_layout_property.cpp   (126 行) - 属性实现
├── arc_list_position_map.h        (64 行)  - 位置映射
├── arc_list_item_pattern.h        (70 行)  - 列表项 Pattern
└── arc_list_item_pattern.cpp      (143 行) - 列表项 Pattern 实现
```

**总计**：约 1,900 行 C++ 代码

---

## 2. 架构设计

### 2.1 类层次结构

```
                                      ScrollablePattern
                                              │
                                              │ 继承
                                              ▼
                                         ListPattern
                                              │
                                              │ 继承
                                              ▼
┌─────────────────────────────────────────────────────────────┐
│                     ArcListPattern                           │
│  ┌───────────────────────────────────────────────────────┐  │
│  │  成员变量:                                            │  │
│  │  - header_: RefPtr<FrameNode>                         │  │
│  │  - scrollStartMidIndex_: int32_t                      │  │
│  │  - startHeaderPos_: float                             │  │
│  │  - headerOffset_: float                               │  │
│  │  - crownSensitivity_: CrownSensitivity                │  │
│  └───────────────────────────────────────────────────────┘  │
└─────────────────────────────────────────────────────────────┘
         │                            │
         │ 创建                       │ 创建
         ▼                            ▼
┌─────────────────────────┐  ┌──────────────────────────────────┐
│ ArcListLayoutAlgorithm  │  │    ArcListLayoutProperty          │
│ (继承 ListLayout        │  │    (继承 ListLayoutProperty)       │
│  Algorithm)             │  │                                   │
│ ┌─────────────────────┐ │  │ ┌───────────────────────────────┐ │
│ │ - headerIndex_      │ │  │ │ - propSpace_                  │ │
│ │ - headerMainSize_   │ │  │ │ - propInitialIndex_           │ │
│ │ - headerOffset_     │ │  │ │ - propDigitalCrownSensitivity_│ │
│ │ - pos2ScaleMap_     │ │  │ └───────────────────────────────┘ │
│ └─────────────────────┘ │  └──────────────────────────────────┘
└─────────────────────────┘
         │
         │ 管理
         ▼
┌─────────────────────────────────────────────────────────────┐
│                   ArcListPositionMap                        │
│                   (继承 ListPositionMap)                    │
│  - 映射列表项索引到位置和缩放值                               │
│  - 缓存位置信息以提升性能                                     │
└─────────────────────────────────────────────────────────────┘
                                      │
                                      │ 管理
                                      ▼
┌─────────────────────────────────────────────────────────────┐
│                   ArcListItemPattern                        │
│                   (继承 ListItemPattern)                    │
│  ┌───────────────────────────────────────────────────────┐  │
│  │  - 处理焦点、悬停、按下事件                             │  │
│  │  - 管理卡片样式和动画                                   │  │
│  │  - 控制禁用状态的透明度                                 │  │
│  └───────────────────────────────────────────────────────┘  │
└─────────────────────────────────────────────────────────────┘
```

### 2.2 调用链

#### 2.2.1 初始化调用链

```
ArkTS: ArcList({ space: 10, initialIndex: 0 })
    │
    ▼
[桥接层] ParseComponentStyle
    │
    ▼
[框架层] ArcListNode::CreateNode()
    │
    ├──► ArcListPattern::ArcListPattern()
    │        │
    │        ├──► SetFriction(ARC_LIST_FRICTION)  // 0.8
    │        ├──► scrollAlign_ = ScrollAlign::CENTER
    │        └──► SetVelocityScale(arcListTheme->GetVelocityScale())
    │
    ├──► ArcListLayoutProperty 创建
    │        │
    │        └──► Reset() - 初始化默认属性
    │
    └──► ArcListLayoutAlgorithm 创建
             │
             └──► ArcListLayoutAlgorithm(headerIndex, itemStartIndex)
```

#### 2.2.2 测量和布局调用链

```
FrameNode::OnDirtyLayoutWrapperSwap()
    │
    ▼
ArcListPattern::OnDirtyLayoutWrapperSwap()
    │
    ├──► ArcListLayoutAlgorithm::Measure()
    │        │
    │        ├──► MeasureHeader() - 测量头部
    │        ├──► MeasureList()
    │        │        │
    │        │        ├──► GetNearScale() - 计算各位置的缩放值
    │        │        ├──► InitItemOffset() - 初始化偏移量
    │        │        └──► GenerateItemOffset() - 生成缩放和偏移
    │        │
    │        └──► UpdateSnapCenterContentOffset() - 更新边界偏移
    │
    └──► ArcListLayoutAlgorithm::Layout()
             │
             ├──► HandleJumpCenter() - 跳转到指定索引
             ├──► LayoutHeader() - 布局头部
             ├──► LayoutALineForward() - 向下布局列表项
             ├──► LayoutALineBackward() - 向上布局列表项
             └──► FixItemLayoutOffset() - 应用缩放和平移
```

#### 2.2.3 滚动事件调用链

```
用户手势 (触摸 / 数码表冠)
    │
    ▼
Scrollable::OnScrollCallback()
    │
    ▼
ArcListPattern::OnScrollCallback()
    │
    ├──► FixScrollOffset() - 补偿缩放效果
    │        │
    │        └──► 计算实际尺寸与缩放后尺寸的比例
    │
    ├──► ListPattern::OnScrollCallback()
    │        │
    │        ├──► UpdateCurrentOffset() - 更新当前偏移
    │        └──► OnScrollPositionChange() - 触发位置变化事件
    │
    └──► FixScrollParam() - 应用吸附修正
             │
             └──► GetOneItemSnapPosByFinalPos() - 计算吸附位置
                      │
                      └──► GetItemSnapPosition() - 获取吸附范围
```

#### 2.2.4 数码表冠事件调用链

```
#ifdef SUPPORT_DIGITAL_CROWN
数码表冠旋转
    │
    ▼
Scrollable::ListenDigitalCrownEvent()
    │
    ├──► RegisterCrownEventCallback() - 注册回调
    │
    └──► OnDigitalCrownEventCallback()
             │
             ├──► 获取旋转步进 (θ)
             ├──► 应用灵敏度:
             │        ├── LOW: 0.5x 步进
             │        ├── MEDIUM: 1.0x 步进 (默认)
             │        └── HIGH: 2.0x 步进
             │
             └──► 转换为滚动偏移
                      │
                      └──► offset = θ × sensitivity × velocityScale
                               │
                               └──► OnScrollCallback()
#endif
```

### 2.3 分层分析

#### 2.3.1 Pattern 层（控制器）

**职责**：协调整个组件的行为，管理生命周期

**核心类**：
- ArcListPattern - 主控制器
- ArcListItemPattern - 列表项控制器

**核心职责**：
```cpp
// 1. 生命周期管理
void OnModifyDone() override;                    // arc_list_pattern.cpp:67-106
bool OnDirtyLayoutWrapperSwap(...) override;     // arc_list_pattern.cpp:108-123

// 2. 算法创建
RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm(); // arc_list_pattern.cpp:125-154

// 3. 事件处理
bool OnScrollCallback(float offset, int32_t source); // arc_list_pattern.cpp:156-163
void FixScrollParam(float mainPos, float& velocity, float& finalPos); // arc_list_pattern.cpp:231-239

// 4. 吸附滚动
bool GetOneItemSnapPosByFinalPos(float mainPos, float finalPos, float& snapPos); // arc_list_pattern.cpp:293-355
```

#### 2.3.2 Algorithm 层（模型层）

**职责**：计算布局、位置、缩放

**核心类**：
- ArcListLayoutAlgorithm - 布局计算器
- ArcListPositionMap - 位置缓存

**核心算法**：
```cpp
// 1. 动态缩放
float GetNearScale(float pos);  // arc_list_layout_algorithm.cpp:63-95
// 多项式公式: scale = SCALE_FACTOR_E + A*pos³ + B*pos² + C*pos + D*pos⁴
//           = 100 + 108*pos³ - 0.0124*pos² - 0.00159*pos + 3.08e-6*pos⁴

// 2. 双向布局
int32_t LayoutALineForward(...);   // arc_list_layout_algorithm.cpp:128-156 - 向下布局
int32_t LayoutALineBackward(...);  // arc_list_layout_algorithm.cpp:158-186 - 向上布局

// 3. 头部偏移计算
float CalculateHeaderOffset(...);  // arc_list_layout_algorithm.cpp:507-528

// 4. 缩放和偏移生成
void GenerateItemOffset(...);      // arc_list_layout_algorithm.cpp:392-463
```

#### 2.3.3 Property 层（视图模型）

**职责**：存储和序列化组件属性

**核心类**：
- ArcListLayoutProperty - 主属性
- ArcListItemLayoutProperty - 列表项属性

**属性**：
```cpp
// ArcListLayoutProperty
std::optional<Dimension> propSpace_;                      // 列表项间距
std::optional<int32_t> propInitialIndex_;                 // 初始索引
std::optional<CrownSensitivity> propDigitalCrownSensitivity_; // 表冠灵敏度
std::optional<bool> propSupportJump_;                     // 是否支持跳转

// ArcListItemLayoutProperty
std::optional<bool> propAutoScale_;                       // 是否自动缩放
```

---

## 3. 核心实现

### 3.1 Pattern 层

#### 3.1.1 ArcListPattern

**文件**：arc_list_pattern.h, arc_list_pattern.cpp

**关键成员变量**：
```cpp
RefPtr<FrameNode> header_;           // 粘性头部节点
int32_t scrollStartMidIndex_;        // 滚动开始时的中心索引（用于吸附计算）
float startHeaderPos_;               // 头部起始位置
float headerOffset_;                 // 计算出的头部偏移
float oldHeaderSize_;                // 之前的头部尺寸（用于变化检测）
float oldFirstItemSize_;             // 之前的首项尺寸
bool headerStayNear_;                // 头部是否保持在顶部
CrownSensitivity crownSensitivity_;  // 数码表冠灵敏度
```

**初始化流程**：
```
ArcListPattern 构造函数
    │
    ├──► SetScrollBarShape(ARC) - 设置为弧形滚动条
    ├──► SetFriction(0.8) - 设置滚动摩擦力
    ├──► scrollAlign_ = CENTER - 始终居中对齐
    └──► SetVelocityScale() - 从主题设置速度缩放
```

**OnModifyDone** - arc_list_pattern.cpp:67-106：
```cpp
void ArcListPattern::OnModifyDone()
{
    // 1. 初始化可滚动事件
    if (!GetScrollableEvent()) {
        AddScrollEvent();
        auto scrollable_ = scrollableEvent->GetScrollable();

        // 2. 注册数码表冠监听器
#ifdef SUPPORT_DIGITAL_CROWN
        scrollable_->ListenDigitalCrownEvent(host);
        scrollable_->SetDigitalCrownSensitivity(crownSensitivity_);
#endif

        // 3. 注册滚动参数修正回调
        scrollable_->RegisterFixScrollParamCallback(
            weak = WeakClaim(this) {
                auto pattern = weak.Upgrade();
                pattern->FixScrollParam(mainPos, velocity, finalPos);
            });
    }

    // 4. 设置边缘效果、滚动条、链式动画
    SetEdgeEffect();
    SetScrollBar(...);
    SetChainAnimation();

    // 5. 设置无障碍和拖放
    Register2DragDropManager();
    SetAccessibilityAction();
}
```

#### 3.1.2 ArcListItemPattern

**文件**：arc_list_item_pattern.h, arc_list_item_pattern.cpp

**关键特性**：
- 卡片模式支持，带焦点边框
- 悬停和按下动画
- 禁用状态透明度管理

**焦点模式** - arc_list_item_pattern.cpp:34-47：
```cpp
FocusPattern ArcListItemPattern::GetFocusPattern() const
{
    if (listItemStyle_ == V2::ListItemStyle::CARD) {
        auto paintParam = FocusPaintParam();
        paintParam.SetPaintColor(listItemTheme->GetItemFocusBorderColor());
        paintParam.SetPaintWidth(listItemTheme->GetItemFocusBorderWidth());
        return { FocusType::SCOPE, true, FocusStyleType::INNER_BORDER, paintParam };
    }
    return { FocusType::SCOPE, true };
}
```

### 3.2 LayoutAlgorithm 层

#### 3.2.1 测量阶段

**文件**：arc_list_layout_algorithm.cpp

**测量流程**：
```
ArcListLayoutAlgorithm::Measure(layoutWrapper)
    │
    ├──► MeasureHeader() - 测量头部尺寸
    │        │
    │        └──► 存储到 headerMainSize_
    │
    ├──► MeasureList()
    │        │
    │        ├──► GetNearScale() - 构建位置→缩放映射表
    │        │        │
    │        │        └──► CenterPos2ScaleMap pos2ScaleMap_
    │        │                 - 键: 距离中心的位置
    │        │                 - 值: 缩放因子 (中心处为 1.08)
    │        │
    │        ├──► InitItemOffset() - 初始化偏移计算
    │        │        │
    │        │        └──► 计算最大缩放区域
    │        │
    │        └──► GenerateItemOffset() - 计算每个列表项的缩放和偏移
    │                 │
    │                 └──► 对每个列表项:
    │                      1. 计算相对中心的位置
    │                      2. 从 pos2ScaleMap_ 获取缩放值
    │                      3. 计算 Y 方向偏移以产生弧形效果
    │
    └──► UpdateSnapCenterContentOffset() - 更新边界偏移
```

#### 3.2.2 布局阶段

**布局流程**：
```
ArcListLayoutAlgorithm::Layout(layoutWrapper)
    │
    ├──► HandleJumpCenter() - 跳转到初始/指定索引
    │        │
    │        └──► 计算跳转位置
    │
    ├──► LayoutHeader() - 布局头部，计算透明度
    │        │
    │        ├──► CalculateHeaderOffset()
    │        └──► 根据位置更新头部透明度
    │
    ├──► LayoutALineForward() - 从中心向下布局
    │        │
    │        └──► 对每个可见列表项:
    │             1. 获取列表项包装器
    │             2. 计算位置
    │             3. 应用缩放和偏移
    │
    ├──► LayoutALineBackward() - 从中心向上布局
    │        │
    │        └──► 与 Forward 相同但向上方向
    │
    └──► FixItemLayoutOffset() - 应用最终变换
             │
             └──► 对每个列表项:
                  1. UpdateTranslateInXY({0, offsetY})
                  2. UpdateTransformScale({scale, scale})
```

### 3.3 LayoutProperty 层

**文件**：arc_list_layout_property.h, arc_list_layout_property.cpp

**属性**：
```cpp
// 核心属性
std::optional<Dimension> propSpace_;                      // 列表项间距
std::optional<int32_t> propInitialIndex_;                 // 初始中心索引
std::optional<CrownSensitivity> propDigitalCrownSensitivity_; // 表冠灵敏度
std::optional<bool> propSupportJump_;                     // 支持跳转动画

// JSON 序列化
void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter);
```

**Reset 方法** - arc_list_layout_property.cpp:26-40：
```cpp
void ArcListLayoutProperty::Reset()
{
    ListLayoutProperty::Reset();
    propSpace_.reset();
    propInitialIndex_.reset();
    propDigitalCrownSensitivity_.reset();
    propSupportJump_.reset();
}
```

### 3.4 ItemPattern 层

**关键方法**：

**颜色混合** - arc_list_item_pattern.cpp:72-85：
```cpp
Color ArcListItemPattern::GetBlendGgColor()
{
    Color color = Color::TRANSPARENT;
    if (isPressed_) {
        color = color.BlendColor(theme->GetItemPressColor());
    } else if (isHover_) {
        color = color.BlendColor(theme->GetItemHoverColor());
    }
    return color;
}
```

**悬停事件** - arc_list_item_pattern.cpp:87-100：
```cpp
void ArcListItemPattern::HandleHoverEvent(bool isHover, const RefPtr<NG::FrameNode>& itemNode)
{
    isHover_ = isHover;
    auto hoverColor = GetBlendGgColor();
    AnimationUtils::BlendBgColorAnimation(
        renderContext, hoverColor,
        theme->GetHoverAnimationDuration(),
        Curves::FRICTION);
}
```

---

## 4. 关键算法

### 4.1 动态缩放算法

**目的**：根据列表项距离中心的远近计算缩放因子

**实现**：arc_list_layout_algorithm.cpp:63-95

**公式**：
```cpp
// 多项式缩放计算
static constexpr double SCALE_FACTOR_A = 108.0;
static constexpr double SCALE_FACTOR_B = -0.012414818053443355;
static constexpr double SCALE_FACTOR_C = -0.0015925017083441295;
static constexpr double SCALE_FACTOR_D = 3.0809306290456454E-06;
static constexpr double SCALE_FACTOR_E = 100.0;

float ArcListLayoutAlgorithm::GetNearScale(float pos)
{
    // pos 是距离中心的距离 (0 = 在中心)
    double absPos = std::abs(pos);

    // 多项式公式: scale = 100 + A*x³ + B*x² + C*x + D*x⁴
    double scale = SCALE_FACTOR_E
        + SCALE_FACTOR_A * pow(absPos, 3)
        + SCALE_FACTOR_B * pow(absPos, 2)
        + SCALE_FACTOR_C * absPos
        + SCALE_FACTOR_D * pow(absPos, 4);

    // 转换为缩放因子 (中心处 1.08，向外递减)
    return scale / 100.0f;
}
```

**缩放值对照表**：
| 位置 (像素) | 缩放  | 视觉效果 |
|---------------|--------|---------------|
| 0             | 1.08   | 放大 8%，高亮显示 |
| 50            | ~1.05  | 略微放大 |
| 100           | ~1.00  | 正常大小 |
| 150           | ~0.95  | 略微缩小 |
| 200           | ~0.90  | 缩小，淡出 |
| 300+          | ~0.80  | 明显缩小 |

**性能优化**：
```cpp
// 在映射表中缓存缩放计算结果
using CenterPos2ScaleMap = std::map<float, float, AscendingOrder>;
CenterPos2ScaleMap pos2ScaleMap_;

// 在 MeasureList 中填充映射表
for (float pos = 0; pos < maxDistance; pos += step) {
    pos2ScaleMap_[pos] = GetNearScale(pos);
}
```

### 4.2 吸附滚动

**目的**：滚动停止时自动将最近的列表项居中

**实现**：arc_list_pattern.cpp:293-355

**算法**：
```cpp
bool ArcListPattern::GetOneItemSnapPosByFinalPos(
    float mainPos,      // 当前位置
    float finalPos,     // 预测的最终位置
    float& snapPos)     // 输出: 修正后的吸附位置
{
    // 1. 获取当前中心索引
    int32_t nCurIdx = GetMidIndex();

    // 2. 计算预测停止位置
    float deltaPos = mainPos - finalPos;
    float stopOnScreen = contentMainSize_ / 2.0f;
    float predictStop = stopOnScreen + deltaPos;

    // 3. 搜索预测位置的列表项
    int32_t deltaIdx = (mainPos <= finalPos) ? -1 : 1;
    ListItemInfo itemInfo;

    for (index = nCurIdx; index >= 0 && index < totalCnt; index += deltaIdx) {
        itemInfo = GetItemDisplayInfo(index);
        // 检查预测停止位置是否在该列表项范围内
        if (predictStop >= itemInfo.startPos - space/2 &&
            predictStop < itemInfo.endPos + space/2) {
            break;
        }
    }

    // 4. 获取该列表项的吸附范围
    ItemSnapInfo snapInfo;
    if (!GetItemSnapPosition(index, snapInfo)) {
        return false;
    }

    // 5. 检查是否超过阈值 (吸附尺寸的 40%)
    float moveDis = 0.0f;
    if (predictStop < snapInfo.snapLow) {
        moveDis = snapInfo.snapLow - predictStop;
        deltaIdx = -1;
    } else if (predictStop > snapInfo.snapHigh) {
        moveDis = predictStop - snapInfo.snapHigh;
        deltaIdx = 1;
    }

    // 6. 决定吸附到当前项还是相邻项
    if (moveDis > snapInfo.moveThreshold && index + deltaIdx >= 0) {
        index += deltaIdx;
        if (!GetItemSnapPosition(index, snapInfo)) {
            return false;
        }
    } else {
        return false; // 不吸附，保持在当前位置
    }

    // 7. 计算最终吸附位置
    predictStop = std::clamp(predictStop, snapInfo.snapLow, snapInfo.snapHigh);
    snapPos = mainPos - (predictStop - stopOnScreen);

    return true;
}
```

**吸附范围计算**：arc_list_pattern.cpp:391-428
```cpp
bool ArcListPattern::GetItemSnapPosition(int32_t nIndex, ItemSnapInfo& snapInfo)
{
    float mainSize = geometryNode->GetMarginFrameSize().MainSize(axis);
    float itemStart = itemPosition_[nIndex].startPos;
    float itemEnd = itemPosition_[nIndex].endPos;

    if (mainSize <= GetItemSnapSize()) {
        // 小列表项：吸附到中心
        snapInfo.snapLow = snapInfo.snapHigh = (itemStart + itemEnd) / 2.0f;
        snapInfo.moveThreshold = mainSize * 0.4f; // 40% 阈值
    } else {
        // 大列表项：吸附范围是距离各边缘 snapSize 的范围
        float snapSize = GetItemSnapSize(); // 153.0f (来自主题)
        snapInfo.snapLow = itemStart + snapSize / 2.0f;
        snapInfo.snapHigh = itemEnd - snapSize / 2.0f;
        snapInfo.moveThreshold = snapSize * 0.4f;
    }

    return true;
}
```

### 4.3 双向布局

**目的**：从中心开始向两端布局列表项

**实现**：arc_list_layout_algorithm.cpp:128-218

**向下布局** (从中心向下)：
```cpp
int32_t ArcListLayoutAlgorithm::LayoutALineForward(
    LayoutWrapper* layoutWrapper,
    int32_t& currentIndex,   // 从中心索引开始
    float startPos,          // 中心位置
    float& endPos)           // 输出: 结束位置
{
    float space = spaceWidth_;
    float currentPos = startPos;
    int32_t layoutCount = 0;

    while (currentIndex < totalItemCount_) {
        auto wrapper = GetListItem(layoutWrapper, currentIndex);
        if (!wrapper) break;

        // 获取带缩放的列表项尺寸
        auto geometryNode = wrapper->GetGeometryNode();
        float itemSize = geometryNode->GetMarginFrameSize().MainSize(axis);
        float scale = posMap_->GetPositionInfo(currentIndex).scale;
        float scaledSize = itemSize * scale;

        // 检查是否仍然可见
        if (currentPos + scaledSize / 2.0f > contentMainSize_) {
            break;
        }

        // 计算列表项位置
        float itemStartPos = currentPos - scaledSize / 2.0f;
        ListItemInfo info(itemStartPos, itemStartPos + scaledSize, scale);

        // 存储位置信息
        itemPosition_[currentIndex] = info;

        // 移动到下一个列表项
        currentPos += scaledSize + space;
        currentIndex++;
        layoutCount++;
    }

    endPos = currentPos;
    return layoutCount;
}
```

**向上布局** (从中心向上)：
```cpp
int32_t ArcListLayoutAlgorithm::LayoutALineBackward(
    LayoutWrapper* layoutWrapper,
    int32_t& currentIndex,   // 从中心索引 - 1 开始
    float endPos,            // 中心位置
    float& startPos)         // 输出: 起始位置
{
    float space = spaceWidth_;
    float currentPos = endPos;
    int32_t layoutCount = 0;

    while (currentIndex >= 0) {
        auto wrapper = GetListItem(layoutWrapper, currentIndex);
        if (!wrapper) break;

        // 获取带缩放的列表项尺寸
        float itemSize = geometryNode->GetMarginFrameSize().MainSize(axis);
        float scale = posMap_->GetPositionInfo(currentIndex).scale;
        float scaledSize = itemSize * scale;

        // 检查是否仍然可见
        if (currentPos - scaledSize / 2.0f < 0) {
            break;
        }

        // 计算列表项位置
        currentPos -= scaledSize + space;
        float itemStartPos = currentPos;
        float itemEndPos = currentPos + scaledSize;

        // 存储位置信息
        itemPosition_[currentIndex] = ListItemInfo(itemStartPos, itemEndPos, scale);

        currentIndex--;
        layoutCount++;
    }

    startPos = currentPos;
    return layoutCount;
}
```

### 4.4 头部透明度渐变

**目的**：头部靠近顶部时逐渐变透明，避免遮挡列表项

**实现**：arc_list_layout_algorithm.cpp:465-505

**透明度计算**：
```cpp
void ArcListLayoutAlgorithm::LayoutHeader(
    LayoutWrapper* layoutWrapper,
    const OffsetF& paddingOffset,
    float crossSize)
{
    if (!headerWrapper) return;

    auto frameNode = headerWrapper->GetHostNode();
    auto renderContext = frameNode->GetRenderContext();

    // 获取第一个列表项的位置
    float firstItemStart = 0.0f;
    if (itemPosition_.count(0) > 0) {
        firstItemStart = itemPosition_[0].startPos;
    }

    // 根据头部位置计算透明度
    float transparency = 0.0f;
    constexpr float HEADER_DIST = 48.0f; // 距离顶部多少像素时完全透明

    if (firstItemStart > HEADER_DIST) {
        // 头部远离第一个列表项，完全透明
        transparency = 1.0f;
    } else if (firstItemStart > 0) {
        // 头部接近第一个列表项，部分透明
        transparency = firstItemStart / HEADER_DIST;
    } else {
        // 头部在顶部，完全不透明
        transparency = 0.0f;
    }

    renderContext->UpdateOpacity(transparency);
}
```

**头部偏移计算**：arc_list_layout_algorithm.cpp:507-528
```cpp
float ArcListLayoutAlgorithm::CalculateHeaderOffset(
    LayoutWrapper* layoutWrapper,
    const ListItemInfo& info)
{
    auto firstItemWrapper = GetListItem(layoutWrapper, 0);
    if (!firstItemWrapper) {
        return std::max(0.0f, startHeaderPos_ - HEADER_DIST);
    }

    // 计算第一个列表项居中时的位置
    auto autoScale = listItemLayoutProperty->GetAutoScale().value_or(true);
    auto scale = autoScale ? GetNearScale(0.0f) : 1.0f;
    auto itemHeight = (info.endPos - info.startPos) * scale;
    auto itemDispStartPosInCenter = (contentMainSize_ - itemHeight) / 2.0f;

    // 计算第一个列表项居中时头部的位置
    auto headerStartPosInTop = itemDispStartPosInCenter - headerMainSize_;
    headerStartPosInTop = std::min(headerStartPosInTop, HEADER_DIST);

    // 偏移是头部和列表项之间的距离
    return itemDispStartPosInCenter - (headerStartPosInTop + headerMainSize_);
}
```

---

## 5. 事件处理

### 5.1 滚动事件

**事件流程**：
```
用户输入 (触摸/数码表冠)
    │
    ▼
InputManager::DispatchTouchEvent()
    │
    ▼
Scrollable::HandleScrollEvent()
    │
    ├──► 从手势计算偏移
    │
    ▼
ArcListPattern::OnScrollCallback(offset, source)
    │
    ├──► FixScrollOffset() - 补偿缩放效果
    │        │
    │        └──► 计算: realTotal vs originTotal
    │             fixOffset = offset * (originTotal / realTotal)
    │
    ├──► ListPattern::OnScrollCallback()
    │        │
    │        ├──► UpdateCurrentOffset() - 更新当前偏移
    │        ├──► UpdateScrollState() - 更新滚动状态
    │        └────► 触发 onScroll 事件
    │
    └──► 滚动结束后:
             │
             └──► FixScrollParam() - 应用吸附
                      │
                      └──► GetOneItemSnapPosByFinalPos() - 计算吸附位置
                               │
                               └──► StartSnapAnimation() - 开始吸附动画
```

**滚动偏移修正**：arc_list_pattern.cpp:430-455
```cpp
float ArcListPattern::FixScrollOffset(float offset, int32_t source)
{
    if (!GetIsDragging() || itemPosition_.empty()) {
        return offset;
    }

    float originTotal = 0.0f;  // 无缩放的总尺寸
    float realTotal = 0.0f;    // 有缩放的总尺寸

    for (auto& pos : itemPosition_) {
        float height = pos.second.endPos - pos.second.startPos;
        float realHeight = height * pos.second.scale;  // 应用缩放
        originTotal += height + spaceWidth_;
        realTotal += realHeight + spaceWidth_;
    }

    originTotal -= spaceWidth_;
    realTotal -= spaceWidth_;

    if (realTotal > 0.0f) {
        // 调整偏移以补偿缩放效果
        float scale = (originTotal / realTotal - 1) * 0.85 + 1;
        return offset * scale;
    }

    return offset;
}
```

### 5.2 数码表冠支持

**启用条件**：`#ifdef SUPPORT_DIGITAL_CROWN`

**灵敏度级别**：arc_list_pattern.h:82-91
```cpp
enum class CrownSensitivity {
    LOW = 0,     // 0.5x 旋转步进
    MEDIUM = 1,  // 1.0x 旋转步进 (默认)
    HIGH = 2     // 2.0x 旋转步进
};

void SetDigitalCrownSensitivity(CrownSensitivity sensitivity)
{
    crownSensitivity_ = sensitivity;
    scrollable_->SetDigitalCrownSensitivity(crownSensitivity_);
}
```

**事件注册**：arc_list_pattern.cpp:76-78
```cpp
scrollable_->ListenDigitalCrownEvent(host);
scrollable_->SetDigitalCrownSensitivity(crownSensitivity_);
```

**JSON 序列化**：arc_list_pattern.cpp:209-219
```cpp
void ArcListPattern::ToJsonValue(...)
{
    std::string sensitivity = "CrownSensitivity.MEDIUM";
    if (crownSensitivity_ == CrownSensitivity::LOW) {
        sensitivity = "CrownSensitivity.LOW";
    } else if (crownSensitivity_ == CrownSensitivity::HIGH) {
        sensitivity = "CrownSensitivity.HIGH";
    }
    json->PutExtAttr("digitalCrownSensitivity", sensitivity.c_str(), filter);
}
```

### 5.3 触摸事件

**由父类处理**：ListPattern

**事件类型**：
- `OnScrollCallback()` - 滚动位置变化
- `HandleDragStart()` - 拖动手势开始
- `HandleDragUpdate()` - 拖动手势更新
- `HandleDragEnd()` - 拖动手势结束（触发吸附）

**ArcList 特定处理**：
- 针对缩放效果调整滚动偏移
- 拖拽结束时的吸附动画
- 考虑缩放列表项的边界检查

---

## 6. 完整 API 参考

### 6.1 ArcListPattern API

**文件**：arc_list_pattern.h, arc_list_pattern.cpp

#### 生命周期方法

##### `ArcListPattern()`
**位置**：arc_list_pattern.cpp:55-65
**描述**：构造函数，初始化 ArcList 特定属性
```cpp
ArcListPattern::ArcListPattern()
{
    SetScrollBarShape(ScrollBarShape::ARC);
    SetFriction(ARC_LIST_FRICTION);  // 0.8
    scrollAlign_ = ScrollAlign::CENTER;
    SetVelocityScale(arcListTheme->GetVelocityScale());
}
```

##### `OnModifyDone()`
**位置**：arc_list_pattern.cpp:67-106
**描述**：组件修改时调用，初始化事件
```cpp
void OnModifyDone() override;
```

##### `OnDirtyLayoutWrapperSwap()`
**位置**：arc_list_pattern.cpp:108-123
**描述**：交换布局包装器，更新算法参数
```cpp
bool OnDirtyLayoutWrapperSwap(
    const RefPtr<LayoutWrapper>& dirty,
    const DirtySwapConfig& config) override;
```

#### 创建方法

##### `CreateLayoutAlgorithm()`
**位置**：arc_list_pattern.cpp:125-154
**描述**：创建支持头部的布局算法
```cpp
RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override;
```

#### 滚动方法

##### `OnScrollCallback()`
**位置**：arc_list_pattern.cpp:156-163
**描述**：处理滚动事件，带偏移调整
```cpp
bool OnScrollCallback(float offset, int32_t source) override;
```
**参数**：
- `offset`: 滚动偏移量（像素）
- `source`: 滚动来源 (SCROLL_FROM_START, SCROLL_FROM_UPDATE 等)

##### `FixScrollOffset()`
**位置**：arc_list_pattern.cpp:430-455
**描述**：调整滚动偏移以补偿缩放效果
```cpp
float FixScrollOffset(float offset, int32_t source);
```

##### `FixScrollParam()`
**位置**：arc_list_pattern.cpp:231-239
**描述**：修正滚动速度和最终位置以实现吸附
```cpp
void FixScrollParam(float mainPos, float& correctVelocity, float& finalPos);
```

#### 吸附方法

##### `GetOneItemSnapPosByFinalPos()`
**位置**：arc_list_pattern.cpp:293-355
**描述**：计算最近列表项的吸附位置
```cpp
bool GetOneItemSnapPosByFinalPos(
    float mainPos,
    float finalPos,
    float& snapPos);
```

##### `GetItemSnapPosition()`
**位置**：arc_list_pattern.cpp:391-428
**描述**：获取特定列表项的吸附范围
```cpp
bool GetItemSnapPosition(int32_t nIndex, ItemSnapInfo& snapInfo);
```

##### `GetMidIndex()`
**位置**：arc_list_pattern.cpp:357-368
**描述**：获取当前位于中心的列表项索引
```cpp
int32_t GetMidIndex();
```

#### 焦点方法

##### `ScrollListForFocus()`
**位置**：arc_list_pattern.cpp:181-188
**描述**：滚动列表以聚焦特定列表项
```cpp
bool ScrollListForFocus(
    int32_t nextIndex,
    int32_t curIndex,
    int32_t nextIndexInGroup) override;
```

##### `GetScrollIndexAbility()`
**位置**：arc_list_pattern.cpp:165-179
**描述**：返回可滚动到指定索引的函数
```cpp
std::function<bool(int32_t)> GetScrollIndexAbility() override;
```

#### 头部方法

##### `AddHeader()`
**位置**：arc_list_pattern.h:57-69
**描述**：添加或替换粘性头部
```cpp
void AddHeader(const RefPtr<NG::FrameNode>& header);
```

#### 数码表冠方法

##### `SetDigitalCrownSensitivity()`
**位置**：arc_list_pattern.h:82-87
**描述**：设置数码表冠旋转灵敏度
```cpp
#ifdef SUPPORT_DIGITAL_CROWN
void SetDigitalCrownSensitivity(CrownSensitivity sensitivity);
#endif
```

##### `GetDigitalCrownSensitivity()`
**位置**：arc_list_pattern.h:88-91
**描述**：获取当前数码表冠灵敏度
```cpp
#ifdef SUPPORT_DIGITAL_CROWN
CrownSensitivity GetDigitalCrownSensitivity();
#endif
```

#### 工具方法

##### `ToJsonValue()`
**位置**：arc_list_pattern.cpp:198-220
**描述**：将组件属性序列化为 JSON
```cpp
void ToJsonValue(
    std::unique_ptr<JsonValue>& json,
    const InspectorFilter& filter) const override;
```

##### `OnChildrenSizeChanged()`
**位置**：arc_list_pattern.cpp:222-229
**描述**：子组件尺寸变化时调用
```cpp
void OnChildrenSizeChanged(
    std::tuple<int32_t, int32_t, int32_t> change,
    ListChangeFlag flag) override;
```

---

### 6.2 ArcListLayoutAlgorithm API

**文件**：arc_list_layout_algorithm.h, arc_list_layout_algorithm.cpp

#### 缩放方法

##### `GetNearScale()`
**位置**：arc_list_layout_algorithm.cpp:63-95
**描述**：根据距离中心的远近计算缩放因子
```cpp
float GetNearScale(float pos);
```
**参数**：
- `pos`: 距离中心的距离（像素，0 表示在中心）

**返回值**：缩放因子（中心处 1.08，向外递减）

**示例**：
```cpp
float scale = GetNearScale(50.0f);  // 返回 ~1.05
```

#### 布局方法

##### `MeasureList()`
**位置**：arc_list_layout_algorithm.cpp:97-126
**描述**：测量所有列表项并计算位置
```cpp
void MeasureList(LayoutWrapper* layoutWrapper) override;
```

##### `LayoutALineForward()`
**位置**：arc_list_layout_algorithm.cpp:128-156
**描述**：从中心向下布局列表项
```cpp
int32_t LayoutALineForward(
    LayoutWrapper* layoutWrapper,
    int32_t& currentIndex,
    float startPos,
    float& endPos) override;
```

##### `LayoutALineBackward()`
**位置**：arc_list_layout_algorithm.cpp:158-186
**描述**：从中心向上布局列表项
```cpp
int32_t LayoutALineBackward(
    LayoutWrapper* layoutWrapper,
    int32_t& currentIndex,
    float endPos,
    float& startPos) override;
```

##### `HandleJumpCenter()`
**位置**：arc_list_layout_algorithm.cpp:188-226
**描述**：处理跳转到指定索引的功能
```cpp
void HandleJumpCenter(LayoutWrapper* layoutWrapper) override;
```

##### `FixItemLayoutOffset()`
**位置**：arc_list_layout_algorithm.cpp:604-633
**描述**：对列表项应用缩放和平移变换
```cpp
void FixItemLayoutOffset(LayoutWrapper* layoutWrapper) override;
```

#### 偏移方法

##### `InitItemOffset()`
**位置**：arc_list_layout_algorithm.cpp:228-268
**描述**：初始化列表项偏移计算
```cpp
float InitItemOffset(LayoutWrapper* layoutWrapper);
```

##### `GenerateItemOffset()`
**位置**：arc_list_layout_algorithm.cpp:392-463
**描述**：为每个列表项生成缩放和 Y 偏移
```cpp
void GenerateItemOffset(LayoutWrapper* layoutWrapper);
```

#### 头部方法

##### `MeasureHeader()`
**位置**：arc_list_layout_algorithm.cpp:270-291
**描述**：测量头部尺寸
```cpp
void MeasureHeader(LayoutWrapper* layoutWrapper) override;
```

##### `LayoutHeader()`
**位置**：arc_list_layout_algorithm.cpp:465-505
**描述**：布局头部，计算透明度
```cpp
void LayoutHeader(
    LayoutWrapper* layoutWrapper,
    const OffsetF& paddingOffset,
    float crossSize) override;
```

##### `CalculateHeaderOffset()`
**位置**：arc_list_layout_algorithm.cpp:507-528
**描述**：计算头部偏移以实现粘性效果
```cpp
float CalculateHeaderOffset(
    LayoutWrapper* layoutWrapper,
    const ListItemInfo& info);
```

##### `CheckNeedUpdateHeaderOffset()`
**位置**：arc_list_layout_algorithm.cpp:530-562
**描述**：检查是否需要更新头部偏移
```cpp
bool CheckNeedUpdateHeaderOffset(LayoutWrapper* layoutWrapper);
```

#### 工具方法

##### `GetItemSnapSize()`
**位置**：arc_list_layout_algorithm.cpp:60-61
**描述**：从主题获取吸附尺寸
```cpp
static float GetItemSnapSize();
```
**返回值**：吸附尺寸（像素，默认：153.0f）

##### `UpdateSnapCenterContentOffset()`
**位置**：arc_list_layout_algorithm.cpp:573-597
**描述**：更新内容偏移以实现吸附对齐
```cpp
void UpdateSnapCenterContentOffset(LayoutWrapper* layoutWrapper) override;
```

##### `GetLayoutFixOffset()`
**位置**：arc_list_layout_algorithm.cpp:599-602
**描述**：获取布局修正偏移
```cpp
float GetLayoutFixOffset() override;
```

---

### 6.3 ArcListLayoutProperty API

**文件**：arc_list_layout_property.h, arc_list_layout_property.cpp

#### 属性方法

##### `Reset()`
**位置**：arc_list_layout_property.cpp:26-40
**描述**：重置所有属性为默认值
```cpp
void Reset() override;
```

##### `Clone()`
**位置**：arc_list_layout_property.cpp:42-48
**描述**：创建此属性对象的副本
```cpp
RefPtr<LayoutProperty> Clone() const override;
```

##### `ToJsonValue()`
**位置**：arc_list_layout_property.cpp:50-126
**描述**：将属性序列化为 JSON，用于调试工具和属性检查器
```cpp
void ToJsonValue(
    std::unique_ptr<JsonValue>& json,
    const InspectorFilter& filter) const override;
```

#### 属性访问器

##### Space 属性（间距）
```cpp
void UpdateSpace(const Dimension& space);              // 设置器
std::optional<Dimension> GetSpace() const;            // 获取器
```

##### InitialIndex 属性（初始索引）
```cpp
void UpdateInitialIndex(int32_t index);               // 设置器
std::optional<int32_t> GetInitialIndex() const;       // 获取器
```

##### DigitalCrownSensitivity 属性（表冠灵敏度）
```cpp
void UpdateDigitalCrownSensitivity(CrownSensitivity value);  // 设置器
std::optional<CrownSensitivity> GetDigitalCrownSensitivity() const; // 获取器
```

##### SupportJump 属性（支持跳转）
```cpp
void UpdateSupportJump(bool support);                 // 设置器
std::optional<bool> GetSupportJump() const;           // 获取器
```

---

### 6.4 ArcListItemPattern API

**文件**：arc_list_item_pattern.h, arc_list_item_pattern.cpp

#### 生命周期方法

##### 构造函数
**位置**：arc_list_item_pattern.h:28-31
```cpp
ArcListItemPattern(const RefPtr<ShallowBuilder>& shallowBuilder);
ArcListItemPattern(
    const RefPtr<ShallowBuilder>& shallowBuilder,
    V2::ListItemStyle listItemStyle);
```

##### `CreateLayoutProperty()`
**位置**：arc_list_item_pattern.h:34-37
```cpp
RefPtr<LayoutProperty> CreateLayoutProperty() override;
```

#### 事件方法

##### `GetFocusPattern()`
**位置**：arc_list_item_pattern.cpp:34-47
**描述**：返回列表项的焦点模式（卡片模式有边框）
```cpp
FocusPattern GetFocusPattern() const override;
```

##### `HandleHoverEvent()`
**位置**：arc_list_item_pattern.cpp:87-100
**描述**：处理鼠标悬停，带动画
```cpp
void HandleHoverEvent(
    bool isHover,
    const RefPtr<NG::FrameNode>& itemNode) override;
```

##### `HandlePressEvent()`
**位置**：arc_list_item_pattern.cpp:102-114
**描述**：处理按下状态，带动画
```cpp
void HandlePressEvent(
    bool isPressed,
    const RefPtr<NG::FrameNode>& itemNode) override;
```

##### `InitDisableEvent()`
**位置**：arc_list_item_pattern.cpp:116-140
**描述**：初始化禁用状态，设置透明度
```cpp
void InitDisableEvent() override;
```

#### 工具方法

##### `SetListItemDefaultAttributes()`
**位置**：arc_list_item_pattern.cpp:49-70
**描述**：为列表项设置默认属性
```cpp
void SetListItemDefaultAttributes(
    const RefPtr<FrameNode>& listItemNode) override;
```

##### `GetBlendGgColor()`
**位置**：arc_list_item_pattern.cpp:72-85
**描述**：根据悬停/按下状态获取混合颜色
```cpp
Color GetBlendGgColor() override;
```

#### 能力方法

##### `IsEnableChildrenMatchParent()`
**位置**：arc_list_item_pattern.h:45-48
```cpp
bool IsEnableChildrenMatchParent() override
{
    return true;
}
```

##### `IsEnableFix()`
**位置**：arc_list_item_pattern.h:50-53
```cpp
bool IsEnableFix() override
{
    return true;
}
```

##### `IsEnableMatchParent()`
**位置**：arc_list_item_pattern.h:55-58
```cpp
bool IsEnableMatchParent() override
{
    return true;
}
```

---

## 7. 使用示例

### 7.1 基础用法

```cpp
// ArkTS 示例
@Entry
@Component
struct ArcListExample {
  @State items: number[] = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9];

  build() {
    ArcList() {
      ForEach(this.items, (item: number) => {
        ListItem() {
          Text(`项目 ${item}`)
            .width('100%')
            .height(60)
        }
      }, (item: number) => item.toString())
    }
    .width('100%')
    .height('100%')
    .space(10)
    .initialIndex(0)
  }
}
```

### 7.2 带数码表冠

```cpp
@Component
struct ArcListWithDigitalCrown {
  @State sensitivity: CrownSensitivity = CrownSensitivity.MEDIUM;

  build() {
    ArcList() {
      // 列表项...
    }
    .digitalCrownSensitivity(this.sensitivity)
    .onScroll((scrollOffset: number, scrollState: ScrollState) => {
      console.info(`滚动偏移: ${scrollOffset}`);
    })
  }
}
```

### 7.3 带分组头部

```cpp
@Component
struct ArcListWithHeaders {
  build() {
    ArcList() {
      ListItemGroup({ header: this.HeaderBuilder }) {
        ForEach(this.group1Items, (item) => {
          ListItem() { Text(item) }
        })
      }

      ListItemGroup({ header: this.HeaderBuilder }) {
        ForEach(this.group2Items, (item) => {
          ListItem() { Text(item) }
        })
      }
    }
  }

  @Builder HeaderBuilder() {
    Text("分组标题")
      .fontColor(Color.Gray)
      .fontSize(14)
  }
}
```

---

## 8. 调试指南

### 8.1 常见问题

#### 问题 1：列表项无法居中

**症状**：滚动后列表项不居中

**可能原因**：
1. `GetOneItemSnapPosByFinalPos()` 返回 false
2. `snapInfo.moveThreshold` 未达到

**调试步骤**：
```cpp
// 在 ArcListPattern::GetOneItemSnapPosByFinalPos 中添加日志
CHECK_NULL_RETURN(host, false);
int32_t totalCnt = host->GetTotalChildCount() - itemStartIndex_;
TAG_LOGI(AceLogTag::ACE_LIST, "总数量: %{public}d", totalCnt);

TAG_LOGI(AceLogTag::ACE_LIST, "当前中心索引: %{public}d", nCurIdx);
TAG_LOGI(AceLogTag::ACE_LIST, "预测停止位置: %{public}f", predictStop);
TAG_LOGI(AceLogTag::ACE_LIST, "移动距离: %{public}f", moveDis);
TAG_LOGI(AceLogTag::ACE_LIST, "移动阈值: %{public}f", snapInfo.moveThreshold);
```

**解决方案**：检查 `moveDis > snapInfo.moveThreshold`。在 arc_list_pattern.cpp:420 调整阈值。

#### 问题 2：缩放未生效

**症状**：所有列表项显示为相同大小

**可能原因**：
1. `autoScale` 属性设置为 false
2. `GetNearScale()` 未被调用
3. 渲染上下文中未应用变换

**调试步骤**：
```cpp
// 检查 autoScale 属性
auto listItemLayoutProperty =
    AceType::DynamicCast<ArcListItemLayoutProperty>(wrapper->GetLayoutProperty());
auto autoScale = listItemLayoutProperty
    ? listItemLayoutProperty->GetAutoScale().value_or(true)
    : true;
TAG_LOGI(AceLogTag::ACE_LIST, "自动缩放: %{public}d", autoScale);

// 检查缩放计算
float scale = GetNearScale(0.0f);
TAG_LOGI(AceLogTag::ACE_LIST, "中心处缩放: %{public}f", scale);
```

**解决方案**：确保 `autoScale` 在 arc_list_layout_algorithm.cpp:514 为 true。

#### 问题 3：头部透明度不工作

**症状**：头部滚动时不淡出

**可能原因**：
1. `UpdateOpacity()` 未被调用
2. 渲染上下文不可用
3. 计算不正确

**调试步骤**：
```cpp
// 在 ArcListLayoutAlgorithm::LayoutHeader 中添加日志
float transparency = (firstItemStart > HEADER_DIST) ? 1.0f :
                    (firstItemStart > 0) ? (firstItemStart / HEADER_DIST) : 0.0f;
TAG_LOGI(AceLogTag::ACE_LIST, "头部透明度: %{public}f", transparency);
```

**解决方案**：检查 arc_list_layout_algorithm.cpp:480 的 `HEADER_DIST` 常量。

### 8.2 性能优化

#### 优化 1：缓存缩放计算

**当前**：每帧为每个位置计算缩放

**优化后**：使用缓存的 `pos2ScaleMap_`
```cpp
// 在 MeasureList 中，一次性构建映射表
for (float pos = 0; pos < contentMainSize_; pos += 1.0f) {
    pos2ScaleMap_[pos] = GetNearScale(pos);
}

// 在 GenerateItemOffset 中，使用缓存的值
float scale = 0.0f;
auto it = pos2ScaleMap_.upperBound(std::abs(pos));
if (it != pos2ScaleMap_.begin()) {
    --it;
    scale = it->second;
}
```

#### 优化 2：减少布局次数

**当前**：头部计算需要多次布局传递

**优化后**：单次传递，缓存头部偏移
```cpp
// 仅在以下情况更新头部偏移：
// 1. 第一个列表项尺寸变化
// 2. 头部尺寸变化
// 3. 之前未计算
if (CheckNeedUpdateHeaderOffset(layoutWrapper)) {
    headerOffset_ = CalculateHeaderOffset(layoutWrapper, info);
}
```

#### 优化 3：延迟列表项创建

**当前**：预先创建所有列表项

**优化后**：使用懒加载，配合 itemStartIndex_
```cpp
// 只创建将可见的列表项
int32_t startIdx = std::max(0, midIndex - 5);
int32_t endIdx = std::min(totalCount - 1, midIndex + 5);

for (int32_t i = startIdx; i <= endIdx; i++) {
    auto wrapper = GetListItem(layoutWrapper, i);
    // 布局列表项...
}
```

### 8.3 日志和诊断

#### 启用组件日志

```cpp
// 在 ace_log.h 中
#define ACE_LIST LOG_CORE
```

#### 关键日志位置

| 位置 | 用途 | 日志标签 |
|----------|---------|---------|
| arc_list_pattern.cpp:159 | 滚动开始索引 | ACE_LIST |
| arc_list_layout_algorithm.cpp:97 | 测量开始 | ACE_LIST |
| arc_list_layout_algorithm.cpp:128 | 向下布局 | ACE_LIST |
| arc_list_layout_algorithm.cpp:158 | 向上布局 | ACE_LIST |
| arc_list_layout_algorithm.cpp:507 | 头部偏移 | ACE_LIST |

#### 转储布局信息

```cpp
// 添加到 ArcListLayoutAlgorithm::Layout
void ArcListLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper) {
    // ... 布局代码 ...

    // 转储列表项位置
    TAG_LOGI(AceLogTag::ACE_LIST, "=== 列表项位置 ===");
    for (auto& pos : itemPosition_) {
        TAG_LOGI(AceLogTag::ACE_LIST, "索引: %{public}d, 起点: %{public}f, 终点: %{public}f, 缩放: %{public}f",
                 pos.first, pos.second.startPos, pos.second.endPos, pos.second.scale);
    }
}
```

---

## 附录 A：常量参考

### 缩放常量
```cpp
// [arc_list_layout_algorithm.cpp]
static constexpr double SCALE_FACTOR_A = 108.0;                   // 三次项系数
static constexpr double SCALE_FACTOR_B = -0.012414818053443355;   // 二次项系数
static constexpr double SCALE_FACTOR_C = -0.0015925017083441295;  // 一次项系数
static constexpr double SCALE_FACTOR_D = 3.0809306290456454E-06;  // 四次项系数
static constexpr double SCALE_FACTOR_E = 100.0;                   // 基础值
static constexpr float OFFSET_THRESHOLD = 348.5f;                 // 偏移计算阈值
```

### 布局常量
```cpp
// [arc_list_pattern.cpp]
constexpr float ARC_LIST_FRICTION = 0.8f;                         // 滚动摩擦力
constexpr float DRAG_FIX_OFFSET_RATIO = 0.85f;                    // 拖拽偏移修正比例
constexpr float ARC_LIST_DRAG_OVER_RATES = 0.6f;                  // 拖拽过度滚动率
constexpr float ARC_LIST_DRAG_OVER_KVALUE = 0.84f;                // 拖拽过度滚动 k 值
constexpr float ARC_LIST_ITEM_MOVE_THRESHOLD_RATIO = 0.4f;        // 吸附阈值 (40%)
constexpr float FLOAT_TWO = 2.0f;                                 // 常量 2.0
```

### 头部常量
```cpp
// [arc_list_layout_algorithm.cpp]
constexpr float HEADER_DIST = 48.0f;                              // 透明度变化的距离
```

### 主题常量
```cpp
// ArcListTheme 中的默认值
static constexpr float DEFAULT_ITEM_SNAP_SIZE = 153.0f;          // 吸附尺寸（像素）
static constexpr float DEFAULT_VELOCITY_SCALE = 1.0f;             // 速度缩放
```

---

## 附录 B：文件参考

### 实现文件

| 文件 | 行数 | 用途 |
|------|-------|---------|
| arc_list_pattern.h | 136 | Pattern 类定义 |
| arc_list_pattern.cpp | 477 | Pattern 实现 |
| arc_list_layout_algorithm.h | 145 | 算法类定义 |
| arc_list_layout_algorithm.cpp | 636 | 布局算法实现 |
| arc_list_layout_property.h | 106 | 属性类定义 |
| arc_list_layout_property.cpp | 126 | 属性实现 |
| arc_list_position_map.h | 64 | 位置映射 |
| arc_list_item_pattern.h | 70 | 列表项 Pattern 定义 |
| arc_list_item_pattern.cpp | 143 | 列表项 Pattern 实现 |
| arc_list_item_layout_property.h | ~50 | 列表项属性定义 |

### 测试文件

| 文件 | 测试数 | 用途 |
|------|-------|---------|
| arc_list_test_ng.cpp | ~50 | Pattern 单元测试 |
| arc_list_attr_test_ng.cpp | ~40 | 属性测试 |
| arc_list_layout_test.cpp | ~60 | 布局算法测试 |
| arc_list_event_test_ng.cpp | ~45 | 事件处理测试 |
| arc_list_scroller_test.cpp | ~30 | 滚动器测试 |
| list_item_event_test_ng.cpp | ~35 | 列表项事件测试 |
| arc_list_swipe_test_ng.cpp | ~40 | 滑动手势测试 |
| arc_list_scroll_test.cpp | ~25 | 滚动行为测试 |

---

**文档版本**：1.0
**最后更新**：2025-01-31
**维护者**：ACE 引擎团队
