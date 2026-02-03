# ArkUI Refresh 组件完整知识库

> **文档版本**：v1.0
> **更新时间**：2026-02-03
> **源码版本**：OpenHarmony ace_engine (master 分支)
> **作者**：基于 CLAUDE.md 规范自动生成

---

##  目录

1. [概述](#概述)
2. [目录结构](#目录结构)
3. [核心类继承关系](#核心类继承关系)
4. [Pattern层详解](#pattern层详解)
5. [Model层详解](#model层详解)
6. [Property系统](#property系统)
7. [EventHub详解](#eventhub详解)
8. [布局算法](#布局算法)
9. [绘制与动画](#绘制与动画)
10. [完整API清单](#完整api清单)
11. [关键实现细节](#关键实现细节)
12. [使用示例](#使用示例)
13. [调试指南](#调试指南)
14. [常见问题](#常见问题)
15. [附录](#附录)

---

## 概述

### 组件定位

**Refresh** 组件是 OpenHarmony ArkUI 框架中的**下拉刷新组件**，提供下拉刷新功能，支持自定义刷新 UI、加载文本提示、刷新状态监听等多种场景。Refresh 通常作为可滚动组件（List、Grid、WaterFlow 等）的父容器使用。

### 技术栈

- **前端**：ArkTS/TypeScript
- **桥接层**：RefreshModelNG + RefreshModifier
- **核心层**：NG Pattern 架构 (RefreshPattern)
- **渲染层**：Rosen + Skia
- **依赖组件**：LoadingProgress、Text、Column

### 代码规模

- 总文件数：17 个文件
- 核心代码：约 4,200+ 行 C++ 代码
- 涉及 3 个架构层次（Pattern/Property/Event）

### 功能特性

- 支持下拉触发刷新操作
- 支持自定义刷新 UI（Custom Builder）
- 支持加载文本提示
- 支持多版本兼容（API 10-）
- 支持父子组件嵌套滚动协调
- 支持弹簧动画效果
- 支持键盘快捷键触发刷新（F5 / Ctrl+R）
- 支持无障碍访问

---

## 目录结构

### 源码文件组织

```
components_ng/pattern/refresh/
├── refresh_pattern.h                  # Pattern 层头文件（主模式类）
├── refresh_pattern.cpp                # Pattern 层实现（业务逻辑）
├── refresh_model.h                    # Model 层接口定义
├── refresh_model_multi_thread.cpp     # Model 层多线程实现
├── refresh_layout_property.h          # 布局属性定义
├── refresh_event_hub.h                # 事件处理中心
├── refresh_accessibility_property.h   # 无障碍属性
├── refresh_accessibility_property.cpp # 无障碍属性实现
├── refresh_layout_algorithm.h         # 布局算法
├── refresh_layout_algorithm.cpp       # 布局算法实现
├── refresh_animation_state.h          # 动画状态枚举
├── refresh_theme_ng.h                 # 主题样式定义
├── refresh_constant.h                 # 常量定义
├── refresh_pattern_multi_thread.cpp   # 多线程支持
└── refresh_model_static.cpp           # 静态 Model 实现
```

### 文件职责说明

| 文件名 | 职责描述 |
|--------|----------|
| `refresh_pattern.h/cpp` | 核心业务逻辑，处理下拉手势、状态切换、动画控制 |
| `refresh_layout_property.h` | 布局属性定义（refreshOffset、friction、loadingText 等） |
| `refresh_event_hub.h` | 事件处理（onStateChange、onRefreshing、onOffsetChange 等） |
| `refresh_accessibility_property.h/cpp` | 无障碍功能支持 |
| `refresh_layout_algorithm.h/cpp` | 布局算法实现，计算子组件位置 |
| `refresh_animation_state.h` | 动画状态枚举（FOLLOW_HAND、FOLLOW_TO_RECYCLE、RECYCLE） |
| `refresh_constant.h` | 常量定义（RefreshStatus 枚举） |
| `refresh_theme_ng.h` | 主题配置（进度颜色、大小、文本样式等） |
| `refresh_model.h` | Model 层接口，连接前端与后端 |

---

## 核心类继承关系

### 类图

```
                    ┌─────────────────────┐
                    │   Pattern (Base)    │
                    └──────────┬──────────┘
                               │
                               │ 继承
                               ▼
              ┌──────────────────────────────┐
              │  NestableScrollContainer      │
              │  (可嵌套滚动容器基类)         │
              └──────────────────┬───────────┘
                                 │
                                 │ 继承
                                 ▼
              ┌──────────────────────────────┐
              │      RefreshPattern          │
              │  (下拉刷新模式类)             │
              └──────────────────────────────┘
                               │
                               │ 创建
                               ├─────────────────────────────┐
                               │                             │
                               ▼                             ▼
                    ┌──────────────────┐        ┌─────────────────────┐
                    │RefreshEventHub   │        │RefreshLayoutProperty│
                    └──────────────────┘        └─────────────────────┘

                               │
                               │ 创建
                               ▼
                    ┌──────────────────────┐
                    │RefreshAccessibility  │
                    │Property              │
                    └──────────────────────┘
```

### 核心类说明

#### RefreshPattern

**继承关系**：
- 父类：`NestableScrollContainer`
- 子类：无

**职责**：
- 处理下拉手势识别
- 管理刷新状态转换
- 控制 LoadingProgress 动画
- 协调父子组件嵌套滚动

**核心方法**：
- `OnModifyDone()` - 属性修改完成时的初始化
- `HandleDragStart/Update/End()` - 处理拖拽手势
- `UpdateRefreshStatus()` - 更新刷新状态
- `UpdateLoadingProgressStatus()` - 更新加载动画状态
- `AddCustomBuilderNode()` - 添加自定义刷新 UI
- `InitPanEvent()` - 初始化滑动手势

---

## Pattern层详解

### RefreshPattern

**文件位置**：`frameworks/core/components_ng/pattern/refresh/refresh_pattern.h:41`

#### 生命周期方法

| 方法名 | 调用时机 | 功能说明 |
|--------|----------|----------|
| `OnAttachToFrameNode()` | 组件附加到节点时 | 设置裁剪属性，检查 API 版本 |
| `OnAttachToMainTree()` | 附加到主树时 | 多线程安全检查 |
| `OnModifyDone()` | 属性修改完成时 | 初始化手势、子节点、键盘事件 |
| `OnDirtyLayoutWrapperSwap()` | 布局包装器交换时 | 更新子组件位置和动画状态 |

#### 核心状态

**文件位置**：`refresh_pattern.h:187-234`

```cpp
RefreshStatus refreshStatus_ = RefreshStatus::INACTIVE;  // 刷新状态
RefPtr<PanEvent> panEvent_;                              // 滑动手势
float scrollOffset_ = 0.0f;                              // 滚动偏移量
bool isRefreshing_ = false;                              // 是否正在刷新
bool isSourceFromAnimation_ = false;                     // 动画源标志
RefPtr<FrameNode> progressChild_;                        // 加载进度子节点
RefPtr<FrameNode> loadingTextNode_;                      // 加载文本子节点
RefPtr<FrameNode> customBuilder_;                        // 自定义构建器
RefPtr<NodeAnimatablePropertyFloat> offsetProperty_;     // 偏移动画属性
```

#### 核心业务逻辑

##### 1. 下拉手势处理

**实现位置**：`refresh_pattern.cpp:164-211`

**功能描述**：初始化 Pan 手势，处理垂直方向的下拉操作

**关键代码片段**：

```cpp
void RefreshPattern::InitPanEvent(const RefPtr<FrameNode>& host)
{
    auto actionStartTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto speed = static_cast<float>(info.GetMainVelocity());
        pattern->UpdateDragFRCSceneInfo(REFRESH_DRAG_SCENE, speed, SceneStatus::START);
        pattern->HandleDragStart(true, speed);
    };
    auto actionUpdateTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleDragUpdate(static_cast<float>(info.GetMainDelta()),
                                  static_cast<float>(info.GetMainVelocity()));
    };
    auto actionEndTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto speed = static_cast<float>(info.GetMainVelocity());
        pattern->UpdateDragFRCSceneInfo(REFRESH_DRAG_SCENE, speed, SceneStatus::END);
        pattern->HandleDragEnd(speed);
    };
    // ... 注册手势事件
}
```

**实现细节**：
- 使用 `PanEvent` 监听垂直方向滑动手势
- 通过 `HandleDragStart/Update/End` 处理手势阶段
- 支持速度传递用于惯性动画

##### 2. 状态转换管理

**实现位置**：`refresh_pattern.cpp:668-698`

**功能描述**：管理刷新状态转换，触发对应事件和动画

**状态转换图**：

```
          ┌─────────────┐
          │  INACTIVE   │  (初始状态)
          └──────┬──────┘
                 │ 下拉
                 ▼
          ┌─────────────┐
          │    DRAG     │  (拖拽中，未达到阈值)
          └──────┬──────┘
                 │ 继续下拉超过阈值
                 ▼
          ┌─────────────┐
          │ OVER_DRAG   │  (超过阈值，可触发刷新)
          └──────┬──────┘
                 │ 松手
                 ▼
          ┌─────────────┐
          │  REFRESH    │  (正在刷新)
          └──────┬──────┘
                 │ 刷新完成
                 ▼
          ┌─────────────┐
          │    DONE     │  (完成，返回顶部)
          └──────┬──────┘
                 │
                 ▼
          ┌─────────────┐
          │  INACTIVE   │
          └─────────────┘
```

**关键代码**：

```cpp
void RefreshPattern::UpdateRefreshStatus(RefreshStatus newStatus)
{
    if (refreshStatus_ == newStatus) {
        return;
    }
    refreshStatus_ = newStatus;
    isRefreshing_ = (refreshStatus_ == RefreshStatus::REFRESH);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto refreshEventHub = host->GetEventHub<RefreshEventHub>();
    CHECK_NULL_VOID(refreshEventHub);
    if (refreshStatus_ == RefreshStatus::REFRESH) {
        refreshEventHub->FireChangeEvent("true");
        refreshEventHub->FireOnRefreshing();
    } else {
        refreshEventHub->FireChangeEvent("false");
    }
    refreshEventHub->FireOnStateChange(static_cast<int>(refreshStatus_));
}
```

##### 3. 自定义 UI 支持

**实现位置**：`refresh_pattern.cpp:582-621`

**功能描述**：支持开发者自定义刷新视图

**关键代码**：

```cpp
void RefreshPattern::AddCustomBuilderNode(const RefPtr<NG::UINode>& builder)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (!builder) {
        if (isCustomBuilderExist_) {
            host->RemoveChild(customBuilder_);
            isCustomBuilderExist_ = false;
            customBuilder_ = nullptr;
            isRemoveCustomBuilder_ = true;
        }
        return;
    }

    if (!isCustomBuilderExist_) {
        if (progressChild_) {
            if (columnNode_) {
                host->RemoveChild(columnNode_);
                columnNode_ = nullptr;
                loadingTextNode_ = nullptr;
            }
            host->RemoveChild(progressChild_);
            progressChild_ = nullptr;
        }
        host->AddChild(builder, 0);
        UpdateFirstChildPlacement();
        UpdateScrollTransition(host, 0.f);
    }
    customBuilder_ = AceType::DynamicCast<FrameNode>(builder);
    isCustomBuilderExist_ = true;
}
```

##### 4. 嵌套滚动协调

**实现位置**：`refresh_pattern.cpp:1255-1348`

**功能描述**：与子滚动组件协调滚动事件

**关键方法**：
- `HandleScroll()` - 处理滚动事件，根据嵌套模式决定处理顺序
- `OnScrollStartRecursive()` - 递归通知滚动开始
- `HandleScrollVelocity()` - 处理滚动速度
- `OnScrollEndRecursive()` - 递归通知滚动结束

---

## Model层详解

### RefreshModelNG

**文件位置**：`frameworks/core/components_ng/pattern/refresh/refresh_model_ng.h`

#### Model 接口定义

RefreshModelNG 是连接前端 ArkTS 代码和后端 Pattern 的桥接层，负责：
- 解析 ArkTS 属性设置
- 创建和配置 FrameNode
- 注册事件回调

#### 主要方法

| 方法名 | 功能 |
|--------|------|
| `Create()` | 创建 Refresh 组件节点 |
| `SetRefreshOffset()` | 设置触发刷新的距离 |
| `SetFriction()` | 设置摩擦系数 |
| `SetLoadingText()` | 设置加载文本 |
| `SetOnStateChange()` | 注册状态变化回调 |
| `SetOnRefreshing()` | 注册刷新事件回调 |

---

## Property系统

### LayoutProperty

**类名**：`RefreshLayoutProperty`

**文件位置**：`frameworks/core/components_ng/pattern/refresh/refresh_layout_property.h:38`

#### 属性列表

| 属性名 | 类型 | 默认值 | 说明 |
|--------|------|--------|------|
| `IsRefreshing` | bool | false | 是否正在刷新 |
| `IndicatorOffset` | Dimension | 16.0_vp | 指示器偏移量（API 10-） |
| `Friction` | int32_t | 62 | 摩擦系数（影响拖拽阻力） |
| `LoadingText` | std::string | "" | 加载提示文本 |
| `PullToRefresh` | bool | true | 是否允许下拉刷新 |
| `PullUpToCancelRefresh` | bool | true | 是否上滑取消刷新 |
| `RefreshOffset` | Dimension | 64.0_vp | 触发刷新的距离 |
| `PullDownRatio` | float | 主题配置 | 下拉比例系数 |
| `MaxPullDownDistance` | float | 无限 | 最大下拉距离 |
| `IsCustomBuilderExist` | bool | false | 是否存在自定义构建器 |

#### 属性修改函数

这些属性通过 ArkTS 前端代码设置，通过 Modifier 模式更新到 LayoutProperty：

```typescript
// ArkTS 示例
Refresh()
  .refreshOffset(80)        // 设置刷新偏移
  .friction(80)             // 设置摩擦系数
  .loadingText("加载中...") // 设置加载文本
```

### AccessibilityProperty

**类名**：`RefreshAccessibilityProperty`

**文件位置**：`frameworks/core/components_ng/pattern/refresh/refresh_accessibility_property.h:23`

#### 功能

- 标识组件为可滚动
- 支持向前滚动操作（触发刷新）
- 支持无障碍级别设置

---

## EventHub详解

### RefreshEventHub

**文件位置**：`frameworks/core/components_ng/pattern/refresh/refresh_event_hub.h:30`

#### 事件列表

| 事件名 | 类型 | 触发条件 | 回调参数 |
|--------|------|----------|----------|
| `onStateChange` | StateChangeEvent | 状态变化时 | int32_t (状态值) |
| `onRefreshing` | RefreshingEvent | 触发刷新时 | 无 |
| `onChange` | RefreshChangeEvent | refreshing 状态变化 | string ("true"/"false") |
| `onOffsetChange` | OffsetChangeEvent | 偏移量变化时 | float (偏移值 vp) |
| `onOffsetChange` | OffsetStepChangeEvent | 单次偏移变化 | float, bool (是否拖拽) |

#### 事件初始化

事件通过 ArkTS 前端注册，在 ModelNG 层设置到 EventHub：

```typescript
// ArkTS 示例
Refresh()
  .onStateChange((value: number) => {
    console.log('状态变化:', value);
  })
  .onRefreshing(() => {
    // 执行刷新逻辑
    loadData().then(() => {
      this.refreshing = false;
    });
  })
  .onOffsetChange((value: number) => {
    console.log('偏移量:', value);
  })
```

---

## 布局算法

### RefreshLayoutAlgorithm

**文件位置**：`frameworks/core/components_ng/pattern/refresh/refresh_layout_algorithm.h`

#### 算法类型

Refresh 组件使用自定义布局算法，主要职责：

1. **测量子组件**：计算 LoadingProgress/CustomBuilder 和内容区域的大小
2. **定位子组件**：根据 scrollOffset 定位子组件位置
3. **处理自定义构建器**：支持自定义 UI 的特殊布局

#### 算法实现细节

**文件位置**：`refresh_layout_algorithm.cpp`

布局流程：
1. 如果存在自定义构建器，设置其为第一个子组件
2. 根据 `builderMeasureBaseHeight`（高版本）或 `customBuilderOffset`（低版本）调整布局
3. 应用 scrollOffset 到子组件位置

---

## 绘制与动画

### 动画状态

**文件位置**：`refresh_animation_state.h:26`

```cpp
enum class RefreshAnimationState : int32_t {
    FOLLOW_HAND = 1,         // 跟随手势移动
    FOLLOW_TO_RECYCLE = 2,   // 过渡到循环动画
    RECYCLE = 3,             // 循环加载动画
};
```

### 动画控制

**实现位置**：`refresh_pattern.cpp:852-902`

#### SpeedTriggerAnimation

基于手速度触发弹簧动画：

```cpp
void RefreshPattern::SpeedTriggerAnimation(float speed)
{
    auto targetOffset = (isSourceFromAnimation_ ||
                            LessNotEqual(scrollOffset_, refreshOffset_.ConvertToPx()) ||
                            !pullToRefresh_) ? 0.0f : refreshOffset_.ConvertToPx();
    auto dealSpeed = 0.0f;
    if (!NearEqual(scrollOffset_, targetOffset)) {
        auto pullDownRatio = CalculatePullDownRatio();
        dealSpeed = (pullDownRatio * speed) / (targetOffset - scrollOffset_);
    }

    bool recycle = true;
    if (pullToRefresh_ && !isSourceFromAnimation_ && refreshStatus_ == RefreshStatus::OVER_DRAG) {
        UpdateRefreshStatus(RefreshStatus::REFRESH);
        UpdateLoadingProgressStatus(RefreshAnimationState::FOLLOW_TO_RECYCLE, GetFollowRatio());
    } else if (NearZero(targetOffset)) {
        recycle = false;
        if (pullUpToCancelRefresh_ || refreshStatus_ == RefreshStatus::DRAG) {
            SwitchToFinish();
        }
    }

    AnimationOption option;
    auto curve = AceType::MakeRefPtr<InterpolatingSpring>(dealSpeed, 1.0f, 228.0f, 30.0f);
    option.SetCurve(curve);
    // ... 执行动画
}
```

### 渲染属性更新

**UpdateLoadingProgressStatus** - 更新 LoadingProgress 的动画状态：

```cpp
void RefreshPattern::UpdateLoadingProgressStatus(RefreshAnimationState state, float ratio)
{
    CHECK_NULL_VOID(progressChild_);
    auto progressPaintProperty = progressChild_->GetPaintProperty<LoadingProgressPaintProperty>();
    CHECK_NULL_VOID(progressPaintProperty);
    progressPaintProperty->UpdateRefreshAnimationState(state);
    switch (state) {
        case RefreshAnimationState::FOLLOW_HAND:
        case RefreshAnimationState::RECYCLE:
            progressPaintProperty->UpdateRefreshSizeScaleRatio(ratio);
            break;
        default:
            break;
    }
    progressChild_->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}
```

---

## 完整API清单

### ArkTS API

#### 构件创建

```typescript
// 基本用法
Refresh()
  .onRefreshing(() => {
    // 刷新逻辑
  })

// 带状态绑定
Refresh() {
  Text('内容')
}
.refreshing(this.isRefreshing)
.onRefreshing(() => {
  this.isRefreshing = true
  // 执行刷新
  setTimeout(() => {
    this.isRefreshing = false
  }, 2000)
})
```

#### 属性设置

| 属性名 | 类型 | 必填 | 默认值 | 说明 |
|--------|------|------|--------|------|
| `refreshing` | boolean | 是 | false | 是否正在刷新（双向绑定） |
| `refreshOffset` | number / string / Resource | 否 | 64.0_vp | 触发刷新的下拉距离 |
| `friction` | number | 否 | 62 | 摩擦系数，值越大阻力越大 |
| `loadingText` | string / Resource | 否 | "" | 加载提示文本 |
| `pullToRefresh` | boolean | 否 | true | 是否允许下拉触发刷新 |
| `pullUpToCancelRefresh` | boolean | 否 | true | 是否上滑取消刷新 |
| `pullDownRatio` | number | 否 | 主题默认 | 下拉阻尼比例系数 |
| `maxPullDownDistance` | number / string | 否 | 无限 | 最大下拉距离 |
| `state` | RefreshStatus | 只读 | - | 当前刷新状态 |

#### 事件

| 事件名 | 类型 | 说明 |
|--------|------|------|
| `onStateChange` | (value: RefreshStatus) => void | 状态变化回调 |
| `onRefreshing` | () => void | 触发刷新回调 |
| `onOffsetChange` | (value: number) => void | 偏移量变化回调（vp 单位） |
| `onChange` | (value: boolean) => void | refreshing 状态变化回调 |

#### RefreshStatus 枚举

```typescript
enum RefreshStatus {
  Inactive = 0,    // 初始状态
  Drag = 1,        // 拖拽中
  OverDrag = 2,    // 超过阈值
  Refresh = 3,     // 刷新中
  Done = 4         // 完成
}
```

### C++ 内部 API

#### RefreshPattern 公共方法

```cpp
// 状态查询
bool IsRefreshing() const;
float GetScrollOffsetValue() const;

// 自定义构建器
void AddCustomBuilderNode(const RefPtr<NG::UINode>& builder);

// 嵌套滚动
ScrollResult HandleScroll(float offset, int32_t source, NestedState state, float velocity);
void OnScrollStartRecursive(WeakPtr<NestableScrollContainer> child, float position, float velocity);
void OnScrollEndRecursive(const std::optional<float>& velocity);

// 生命周期
void OnModifyDone() override;
void OnColorModeChange(uint32_t colorMode) override;
RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override;
```

---

## 关键实现细节

### 1. 版本兼容处理

**需求**：支持 API 10- 和 API 11+ 不同行为

**实现位置**：`refresh_pattern.cpp:79-90, 138-143`

**实现方案**：
- 通过 `context->GetMinPlatformVersion()` 判断版本
- 高版本（API 11+）使用新的动画属性系统
- 低版本使用 `lowVersionOffset_` 属性

**关键代码**：

```cpp
void RefreshPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    THREAD_SAFE_NODE_CHECK(host, OnAttachToFrameNode);
    CHECK_NULL_VOID(host);
    host->GetRenderContext()->SetClipToBounds(true);
    host->GetRenderContext()->UpdateClipEdge(true);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    isHigherVersion_ = context->GetMinPlatformVersion() >=
                       static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN);
}

void RefreshPattern::OnModifyDone()
{
    // ...
    if (!isHigherVersion_) {
        triggerLoadingDistance_ = static_cast<float>(
            std::clamp(layoutProperty->GetIndicatorOffset().value_or(triggerLoadingDistanceTheme_).ConvertToPx(),
                -1.0f * triggerLoadingDistanceTheme_.ConvertToPx(),
                GetTriggerRefreshDisTance().ConvertToPx()));
        InitLowVersionOffset();
    }
    // ...
}
```

### 2. 下拉阻尼计算

**需求**：下拉时根据距离增加阻力，提供更好的交互体验

**实现位置**：`refresh_pattern.cpp:512-539`

**实现方案**：
- 使用指数衰减函数 `exp(-ratio * gamma)`
- `gamma` 为当前偏移与内容高度的比例
- `ratio` 为主题配置的阻尼系数

**关键代码**：

```cpp
float RefreshPattern::CalculatePullDownRatio()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, 1.0f);
    auto layoutProperty = GetLayoutProperty<RefreshLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, 1.f);
    if (layoutProperty->GetPullDownRatio().has_value()) {
        return layoutProperty->GetPullDownRatio().value();
    }
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, 1.0f);
    auto contentHeight = geometryNode->GetPaddingSize().Height();
    if (NearZero(contentHeight)) {
        return 1.0f;
    }
    if (!ratio_.has_value()) {
        auto context = host->GetContext();
        CHECK_NULL_RETURN(context, 1.0f);
        auto refreshTheme = context->GetTheme<RefreshThemeNG>();
        CHECK_NULL_RETURN(refreshTheme, 1.0f);
        ratio_ = refreshTheme->GetRatio();
    }
    auto gamma = scrollOffset_ / contentHeight;
    if (GreatOrEqual(gamma, 1.0)) {
        gamma = 1.0f;
    }
    return exp(-ratio_.value() * gamma);
}
```

### 3. 键盘快捷键支持

**需求**：支持 F5 和 Ctrl+R 触发刷新

**实现位置**：`refresh_pattern.cpp:444-453`

**关键代码**：

```cpp
bool RefreshPattern::OnKeyEvent(const KeyEvent& event)
{
    if (event.code == KeyCode::KEY_F5 ||
        (event.IsCombinationKey() && event.IsCtrlWith(KeyCode::KEY_R))) {
        if (!isRefreshing_) {
            QuickStartFresh();
        }
        return true;
    }
    return false;
}
```

### 4. FRC 性能优化

**需求**：优化拖拽时的帧率

**实现位置**：`refresh_pattern.cpp:1019-1024`

**实现方案**：
- 通过 `AddFRCSceneInfo` 上报场景信息
- 在拖拽开始/进行/结束时更新场景状态

**关键代码**：

```cpp
void RefreshPattern::UpdateDragFRCSceneInfo(const std::string& scene, float speed, SceneStatus sceneStatus)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->AddFRCSceneInfo(scene, std::abs(speed), sceneStatus);
}
```

### 5. 动画可追踪性

**需求**：支持性能追踪和问题定位

**实现位置**：`refresh_pattern.cpp:1350-1372`

**关键代码**：

```cpp
void RefreshPattern::BeginTrailingTrace()
{
    if (!hasBeginTrailingTrace_) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto id = host->GetAccessibilityId();
        AceAsyncTraceBeginCommercial(
            id, (TRAILING_ANIMATION + std::to_string(id) + std::string(" ") + host->GetTag()).c_str());
        hasBeginTrailingTrace_ = true;
    }
}

void RefreshPattern::EndTrailingTrace()
{
    if (hasBeginTrailingTrace_) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto id = host->GetAccessibilityId();
        AceAsyncTraceEndCommercial(
            id, (TRAILING_ANIMATION + std::to_string(id) + std::string(" ") + host->GetTag()).c_str());
        hasBeginTrailingTrace_ = false;
    }
}
```

---

## 使用示例

### 基础用法

```typescript
@Entry
@Component
struct RefreshExample {
  @State isRefreshing: boolean = false
  @State dataArray: string[] = ['Item 1', 'Item 2', 'Item 3']

  build() {
    Refresh() {
      List() {
        ForEach(this.dataArray, (item: string) => {
          ListItem() {
            Text(item)
              .width('100%')
              .height(50)
              .textAlign(TextAlign.Center)
          }
        })
      }
      .width('100%')
      .height('100%')
    }
    .refreshing(this.isRefreshing)
    .onRefreshing(() => {
      this.isRefreshing = true
      // 模拟网络请求
      setTimeout(() => {
        this.dataArray.push(`Item ${this.dataArray.length + 1}`)
        this.isRefreshing = false
      }, 2000)
    })
  }
}
```

### 自定义刷新 UI

```typescript
@Entry
@Component
struct CustomRefreshExample {
  @State isRefreshing: boolean = false

  @Builder
  customRefreshUI() {
    Column() {
      LoadingProgress()
        .width(40)
        .height(40)
        .color(Color.Blue)
      Text('正在刷新...')
        .fontSize(14)
        .margin({ top: 10 })
    }
    .width('100%')
    .height(100)
    .justifyContent(FlexAlign.Center)
  }

  build() {
    Refresh() {
      List() {
        // 内容
      }
    }
    .refreshing(this.isRefreshing)
    .onRefreshing(() => {
      this.isRefreshing = true
      setTimeout(() => {
        this.isRefreshing = false
      }, 2000)
    })
  }
}
```

### 带加载文本

```typescript
Refresh() {
  List() {
    // 内容
  }
}
.loadingText($r('app.string.loading'))
.refreshOffset(96)
.refreshing(this.isRefreshing)
.onRefreshing(() => {
  // 刷新逻辑
})
```

### 监听状态变化

```typescript
Refresh() {
  List() {
    // 内容
  }
}
.onStateChange((value: RefreshStatus) => {
  console.log('刷新状态:', value)
  // 0: Inactive, 1: Drag, 2: OverDrag, 3: Refresh, 4: Done
})
.onOffsetChange((value: number) => {
  console.log('偏移量:', value, 'vp')
})
```

### 性能优化建议

1. **避免复杂计算**：在 `onRefreshing` 回调中避免同步执行大量计算
2. **合理设置 friction**：根据内容特性调整摩擦系数
3. **控制刷新频率**：添加防抖或节流逻辑避免频繁触发

```typescript
// 优化示例：防抖处理
private lastRefreshTime: number = 0
private readonly REFRESH_COOLDOWN = 1000 // 1秒冷却

.onRefreshing(() => {
  const now = Date.now()
  if (now - this.lastRefreshTime < this.REFRESH_COOLDOWN) {
    return
  }
  this.lastRefreshTime = now
  this.isRefreshing = true
  // 执行刷新
})
```

---

## 调试指南

### 常用日志

**日志标签**：`AceLogTag::ACE_REFRESH`

**关键日志位置**：
- `refresh_pattern.cpp:175` - Drag start 日志
- `refresh_pattern.cpp:188` - Drag end 日志
- `refresh_pattern.cpp:196` - Drag cancel 日志
- `refresh_pattern.cpp:653` - 子组件触发拖拽开始
- `refresh_pattern.cpp:660` - 子组件触发拖拽结束
- `refresh_pattern.cpp:697` - 状态变化日志

**日志查看**：

```bash
# 过滤 Refresh 相关日志
hdc shell hilog | grep ACE_REFRESH
```

### Dump 调试

Refresh 组件支持 dump 功能，可在运行时查看内部状态：

```cpp
// 文件位置：refresh_pattern.cpp:1398-1419
void RefreshPattern::DumpInfo()
{
    DumpLog::GetInstance().AddDesc(
        std::string("RefreshStatus: ").append(std::to_string(static_cast<int32_t>(refreshStatus_))));
    DumpLog::GetInstance().AddDesc(
        std::string("LoadingProgressOpacity: ").append(std::to_string(GetLoadingProgressOpacity())));
    DumpLog::GetInstance().AddDesc(
        std::string("LoadingTextOpacity: ").append(std::to_string(GetLoadingTextOpacity())));
    // ...
}
```

### DevTools 调试

1. 使用 DevEco Studio 的 Inspector 工具查看组件树
2. 检查 `refreshing` 状态值
3. 监控 `onOffsetChange` 回调输出

### 常见问题排查

1. **刷新不触发**：检查 `pullToRefresh` 属性和 `refreshOffset` 设置
2. **动画卡顿**：检查 FRC 日志，优化 `onRefreshing` 回调逻辑
3. **自定义 UI 不显示**：确保使用 `@Builder` 装饰器

---

## 常见问题

### Q1: Refresh 与 List 嵌套使用时，滚动冲突怎么办？

**A**: Refresh 内部已实现嵌套滚动协调，默认情况下会正确处理。如果仍有问题，可以检查：

1. 确认 List 的 `width` 和 `height` 已正确设置
2. 不要在 Refresh 和 List 上同时设置相同方向的手势

### Q2: 如何判断刷新是否完成？

**A**: 使用双向绑定的 `refreshing` 状态：

```typescript
@State isRefreshing: boolean = false

Refresh()
  .refreshing(this.isRefreshing)
  .onRefreshing(() => {
    this.isRefreshing = true
    // 执行刷新
    fetchData().then(() => {
      this.isRefreshing = false // 完成后重置
    })
  })
```

### Q3: 自定义刷新 UI 时，如何获取当前下拉距离？

**A**: Refresh 不直接向自定义 UI 传递距离参数。如果需要，可以：

1. 使用 `onOffsetChange` 监听偏移量
2. 在自定义 UI 中使用 `@State` 变量存储和更新距离

### Q4: 为什么刷新没有触发？

**A**: 检查以下几点：
1. 是否设置了 `onRefreshing` 回调
2. 下拉距离是否达到 `refreshOffset` 阈值
3. `pullToRefresh` 是否为 `true`

### Q5: 如何禁用刷新功能？

**A**: 设置 `pullToRefresh` 为 `false`：

```typescript
Refresh() {
  // 内容
}
.pullToRefresh(false)
```

---

## 附录

### 参考资料

- [OpenHarmony Refresh 组件文档](https://developer.openharmony.cn/cn/docs/documentation/doc-references-V3/ts-basic-components-refresh)
- [LoadingProgress 组件文档](https://developer.openharmony.cn/cn/docs/documentation/doc-references-V3/ts-basic-components-loadingprogress)
- [手势事件文档](https://developer.openharmony.cn/cn/docs/documentation/doc-references-V3/ts-basic-gestures)

### 相关组件文档

- [Scroll 组件知识库](../scroll/Scroll_Knowledge_Base.md)
- [List 组件文档](https://developer.openharmony.cn/cn/docs/documentation/doc-references-V3/ts-container-list)

### 版本历史

| 版本 | 日期 | 变更说明 |
|------|------|----------|
| v1.0 | 2026-02-03 | 初始版本，完整描述 Refresh 组件架构和实现 |

### 文件索引

| 文件 | 行数 | 主要内容 |
|------|------|----------|
| `refresh_pattern.h` | 238 | Pattern 类定义 |
| `refresh_pattern.cpp` | 1421 | 核心业务逻辑实现 |
| `refresh_layout_property.h` | 122 | 布局属性定义 |
| `refresh_event_hub.h` | 111 | 事件处理定义 |
| `refresh_accessibility_property.h` | 47 | 无障碍属性 |
| `refresh_layout_algorithm.cpp` | ~150 | 布局算法实现 |
| `refresh_animation_state.h` | 34 | 动画状态枚举 |
| `refresh_constant.h` | 36 | 常量定义 |

---


**文档维护**：
- 版本：v1.0 (Unified)
- 最后更新：2026-02-03
- 维护者：基于 CLAUDE.md 规范自动生成

**相关文档**：
- [CLAUDE.md](../../../../CLAUDE.md) - 项目代码规范
- [测试文件](../../../../../test/unittest/core/pattern/refresh/) - 单元测试

**反馈**：
如有问题或建议，请在项目根目录的 `CLAUDE.md` 中更新。
