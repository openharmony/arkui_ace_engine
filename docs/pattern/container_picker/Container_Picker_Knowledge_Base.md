# ArkUI ContainerPicker 组件完整知识库

> **版本**: 1.0
> **更新时间**: 2026-02-02
> **基于**: OpenHarmony ace_engine (master 分支)

---

## 目录

1. [架构概述](#1-架构概述)
2. [核心类详解](#2-核心类详解)
3. [完整滚动流程](#3-完整滚动流程)
4. [关键技术点](#4-关键技术点)
5. [属性系统](#5-属性系统)
6. [事件系统](#6-事件系统)
7. [动画系统](#7-动画系统)
8. [触觉反馈](#8-触觉反馈)
9. [最佳实践](#9-最佳实践)
10. [问题排查](#10-问题排查)

---

## 1. 架构概述

### 1.1 系统架构

ContainerPicker 组件实现了一个可滚动的选择器容器，采用 4 层架构：

```
ArkTS 前端
    ↓
桥接层 (ContainerModifier) - 属性解析和应用
    ↓
模式层 (ContainerPickerPattern) - 业务逻辑和状态管理
    ↓
滚动层 (NestableScrollContainer) - 嵌套滚动支持
    ↓
动画层 (AxisAnimator) - 滚动动画和惯性
```

**设计原则**：
- **平滑滚动**: 物理模型驱动的惯性滚动
- **吸附对齐**: 自动吸附到最近的选项
- **循环滚动**: 支持无限循环选项列表
- **触觉反馈**: 滚动时提供震动反馈

### 1.2 线程模型

**主线程职责**：
- UI 更新和事件处理
- 滚动动画执行
- 选项位置计算
- 触觉反馈触发

---

## 2. 核心类详解

### 2.1 ContainerPickerPattern

**职责**：
- 管理选项列表和选中状态
- 处理拖拽手势
- 执行滚动动画
- 提供触觉反馈

**关键成员变量**：
```cpp
// 滚动参数
double yLast_;                    // 上次 Y 位置
double yOffset_;                  // Y 偏移量
double dragStartTime_;            // 拖拽开始时间
double dragEndTime_;              // 拖拽结束时间
double dragVelocity_;             // 拖拽速度
double currentPos_;               // 当前位置

float currentOffset_;             // 当前滚动偏移
float height_;                    // 容器高度
float contentMainSize_;           // 内容主轴尺寸
float pickerItemHeight_;          // 单项高度

// 动画
RefPtr<AxisAnimator> axisAnimator_;
RefPtr<NodeAnimatablePropertyFloat> scrollProperty_;
std::shared_ptr<AnimationUtils::Animation> scrollAnimation_;

// 状态
bool isDragging_;                 // 是否拖拽中
bool isAnimationRunning_;         // 动画是否运行
int32_t selectedIndex_;           // 选中索引
int32_t totalItemCount_;          // 总项数
int32_t displayCount_;            // 显示项数 (默认 7)

// 触觉反馈
std::shared_ptr<IPickerAudioHaptic> hapticController_;
bool isEnableHaptic_;             // 是否启用触觉
```

**关键方法**：

- **OnModifyDone()**: 初始化组件
  ```cpp
  void ContainerPickerPattern::OnModifyDone() {
      NestableScrollContainer::OnModifyDone();

      // 初始化默认参数
      InitDefaultParams();

      // 初始化动画
      InitAxisAnimator();

      // 初始化事件
      InitMouseAndPressEvent();
      UpdatePanEvent();

      // 初始化触觉反馈
      InitOrRefreshHapticController();
  }
  ```

- **HandleDragStart()**: 拖拽开始
  ```cpp
  void ContainerPickerPattern::HandleDragStart(const GestureEvent& info) {
      isDragging_ = true;
      yLast_ = info.GetMainPoint().GetY();
      dragStartTime_ = GetCurrentTime();
      StopAnimation();  // 停止当前动画

      // 通知滚动开始
      for (auto& listener : scrollingListener_) {
          listener->OnScrollStartRecursive();
      }
  }
  ```

- **HandleDragUpdate()**: 拖拽更新
  ```cpp
  void ContainerPickerPattern::HandleDragUpdate(const GestureEvent& info) {
      if (!isDragging_) return;

      double yCurrent = info.GetMainPoint().GetY();
      double deltaY = yCurrent - yLast_;
      yLast_ = yCurrent;

      // 更新偏移
      UpdateCurrentOffset(deltaY);

      // 计算 FRC 场景
      UpdateDragFRCSceneInfo(std::abs(deltaY), SceneStatus::SCENE_DRAG);
  }
  ```

- **HandleDragEnd()**: 拖拽结束
  ```cpp
  void ContainerPickerPattern::HandleDragEnd(double dragVelocity, float mainDelta) {
      isDragging_ = false;
      dragEndTime_ = GetCurrentTime();
      dragVelocity_ = dragVelocity;

      // 检查是否超出边界
      if (CheckDragOutOfBoundary()) {
          // 回弹动画
          PlaySpringAnimation();
      } else {
          // 惯性滚动
          PlayInertialAnimation();
      }

      // 通知滚动结束
      for (auto& listener : scrollingListener_) {
          listener->OnScrollEndRecursive(dragVelocity);
      }
  }
  ```

- **PlayInertialAnimation()**: 惯性滚动动画
  ```cpp
  void ContainerPickerPattern::PlayInertialAnimation() {
      if (std::abs(dragVelocity_) < MIN_FLING_VELOCITY) {
          // 速度太小，直接吸附
      SnapToNearestItem();
      return;
  }

  // 创建惯性动画
  CreateTargetAnimation(delta);

  auto targetAnimation = AnimationUtils::StartAnimation(
      &context_, animationOption_, [weak = WeakClaim(this)]() {
          auto pattern = weak.Upgrade();
          CHECK_NULL_VOID(pattern);
          pattern->HandleTargetIndex();
      }
  );

  isAnimationRunning_ = true;
  }
  ```

- **SnapToNearestItem()**: 吸附到最近项
  ```cpp
  void ContainerPickerPattern::SnapToNearestItem() {
      // 计算当前中间项
      auto [currentIndex, itemInfo] = CalcCurrentMiddleItem();

      // 计算目标偏移
      float targetOffset = CalculateMiddleLineOffset();

      // 吸附动画
      CreateSpringAnimation(targetOffset);
  }
  ```

### 2.2 AxisAnimator

**职责**：
- 管理滚动动画
- 处理惯性计算
- 执行弹簧动画

**核心接口**：
```cpp
class AxisAnimator {
public:
    void MoveTo(float position, float duration);  // 移动到位置
    void Stop();                                  // 停止动画
    bool IsRunning() const;                       // 是否运行中
};
```

---

## 3. 完整滚动流程

### 3.1 拖拽滚动

```
用户按下并拖动
    ↓
HandleDragStart()
    - 记录起始位置
    - 停止当前动画
    ↓
用户拖动中
    ↓
HandleDragUpdate()
    - 计算偏移量
    - UpdateCurrentOffset(deltaY)
    - 更新子项位置
    ↓
用户松手
    ↓
HandleDragEnd(dragVelocity)
    - 计算拖拽速度
    - 检查是否超出边界
    ↓
[超出边界] → PlaySpringAnimation() → 回弹
[未超出] → PlayInertialAnimation() → 惯性滚动
    ↓
吸附到最近项
    ↓
FireChangeEvent() → 触发 onChange 事件
```

### 3.2 选项点击

```
用户点击某个选项
    ↓
ItemClickEventListener
    ↓
计算点击项索引
    ↓
SwipeTo(index)
    - 计算目标偏移
    - PlayTargetAnimation()
    ↓
动画完成
    ↓
HandleTargetIndex()
    - 更新 selectedIndex_
    - FireChangeEvent()
```

---

## 4. 关键技术点

### 4.1 选项位置计算

```cpp
std::pair<int32_t, PickerItemInfo> ContainerPickerPattern::CalcCurrentMiddleItem() const {
    // 根据当前偏移计算中间项索引
    float middleOffset = currentOffset_ + height_ / 2.0f;

    int32_t index = static_cast<int32_t>(middleOffset / pickerItemHeight_);

    // 循环模式下调整索引
    if (isLoop_) {
        index = (index % totalItemCount_ + totalItemCount_) % totalItemCount_;
    }

    return { index, GetItemInfo(index) };
}
```

### 4.2 循环滚动

```cpp
bool ContainerPickerPattern::IsLoop() const {
    // 启用条件：选项数大于显示项数
    return totalItemCount_ > displayCount_ && isLoop_;
}

void ContainerPickerPattern::UpdateColumnChildPosition(double offsetY) {
    for (auto& [index, pos] : itemPosition_) {
        // 计算新位置
        float newPos = pos + offsetY;

        // 循环模式下处理边界
        if (IsLoop()) {
            if (newPos < -pickerItemHeight_) {
                newPos += totalItemCount_ * pickerItemHeight_;
            } else if (newPos > contentMainSize_) {
                newPos -= totalItemCount_ * pickerItemHeight_;
            }
        }

        itemPosition_[index] = newPos;
    }
}
```

### 4.3 惯性滚动计算

```cpp
void ContainerPickerPattern::PlayInertialAnimation() {
    // 计算惯性距离
    float dragDistance = dragVelocity_ * FLING_DURATION;
    float targetOffset = currentOffset_ + dragDistance;

    // 创建目标动画
    CreateTargetAnimation(targetOffset);

    // 使用弹簧曲线
    animationOption_.SetCurve(Curves::FRICTION);
    animationOption_.SetDuration(FLING_DURATION);

    AnimationUtils::StartAnimation(&context_, animationOption_, [weak = WeakClaim(this)]() {
        // 动画完成回调
    });
}
```

### 4.4 弹簧回弹

```cpp
void ContainerPickerPattern::PlaySpringAnimation() {
    float endOffset;

    if (IsOutOfStart()) {
        // 超出上边界
        CalcEndOffset(endOffset, 0.0);
    } else if (IsOutOfEnd()) {
        // 超出下边界
        CalcEndOffset(endOffset, 0.0);
    }

    // 使用弹簧曲线
    CreateSpringProperty();
    animationOption_.SetCurve(Curves::SPRING_OVERSHOOT);
    animationOption_.SetDuration(SPRING_DURATION);

    AnimationUtils::StartAnimation(&context_, animationOption_, [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->SnapToNearestItem();
    });
}

bool ContainerPickerPattern::IsOutOfBoundary(float mainOffset) const {
    // 检查是否超出边界
    float minOffset = 0.0f;
    float maxOffset = contentMainSize_ - height_;

    return mainOffset < minOffset || mainOffset > maxOffset;
}
```

### 4.5 FRC 性能优化

```cpp
void ContainerPickerPattern::UpdateDragFRCSceneInfo(float speed, SceneStatus sceneStatus) {
    // 根据滚动速度动态调整刷新率
    if (speed > FAST_SCROLL_THRESHOLD) {
        // 快速滚动：降低刷新率
        SetRefreshRate(60 Hz);
    } else if (speed > MEDIUM_SCROLL_THRESHOLD) {
        // 中速滚动：正常刷新率
        SetRefreshRate(90 Hz);
    } else {
        // 慢速或静止：高刷新率
        SetRefreshRate(120 Hz);
    }
}
```

---

## 5. 属性系统

### 5.1 布局属性 (ContainerPickerLayoutProperty)

| 属性 | 类型 | 默认值 | 说明 |
|------|------|--------|------|
| **selectedIndex** | int32_t | 0 | 选中索引 |
| **options** | vector\<string\> | - | 选项列表 |
| **loop** | bool | true | 是否循环 |
| **enableHaptic** | bool | true | 是否启用触觉 |
| **indicatorStyle** | PickerIndicatorStyle | - | 指示器样式 |

### 5.2 PickerIndicatorStyle

```cpp
struct PickerIndicatorStyle {
    bool enabled = true;              // 是否启用
    float width = 1.0f;              // 宽度
    Color color = Color::GRAY;       // 颜色
    Dimension startMargin;           // 起始边距
    Dimension endMargin;             // 结束边距
};
```

---

## 6. 事件系统

### 6.1 事件类型

**onChange** - 选择改变：
```cpp
void ContainerPickerPattern::FireChangeEvent() {
    auto eventHub = GetEventHub<ContainerPickerEventHub>();
    auto onChange = eventHub->GetChangeEvent();

    if (onChange) {
        onChange(selectedIndex_);  // 触发 ArkTS onChange 回调
    }
}
```

**onScrollStop** - 滚动停止：
```cpp
void ContainerPickerPattern::FireScrollStopEvent() {
    auto eventHub = GetEventHub<ContainerPickerEventHub>();
    auto onScrollStop = eventHub->GetScrollStopEvent();

    if (onScrollStop) {
        onScrollStop(selectedIndex_);
    }
}
```

---

## 7. 动画系统

### 7.1 动画类型

| 类型 | 曲线 | 用途 |
|------|------|------|
| **惯性滚动** | FRICTION | 拖拽后的惯性移动 |
| **弹簧动画** | SPRING_OVERSHOOT | 边界回弹 |
| **目标动画** | EASE_OUT | 吸附到目标项 |
| **复位动画** | EASE_IN_OUT | 快速复位 |

### 7.2 动画创建

```cpp
void ContainerPickerPattern::CreateTargetAnimation(float delta) {
    // 创建滚动属性
    CreateScrollProperty();

    // 设置目标值
    float targetOffset = currentOffset_ + delta;
    scrollProperty_->Set(targetOffset);

    // 创建动画
    auto animation = AnimationUtils::CreateAnimation(
        scrollProperty_,
        AnimationOption()
            .SetDuration(INERTIAL_DURATION)
            .SetCurve(Curves::FRICTION)
    );

    scrollAnimation_ = animation;
    isAnimationRunning_ = true;
}
```

---

## 8. 触觉反馈

### 8.1 触觉控制器

```cpp
class IPickerAudioHaptic {
public:
    virtual void Play() = 0;              // 播放震动
    virtual void Stop() = 0;              // 停止震动
    virtual void SetIntensity(float) = 0; // 设置强度
};
```

### 8.2 触觉触发时机

```cpp
void ContainerPickerPattern::PlayHaptic(float offset) {
    if (!IsEnableHaptic()) {
        return;
    }

    // 检查是否跨越选项边界
    int32_t newIndex = static_cast<int32_t>(offset / pickerItemHeight_);
    if (newIndex != selectedIndex_) {
        // 跨越边界，触发震动
        if (hapticController_) {
            hapticController_->Play();
        }
        selectedIndex_ = newIndex;
    }
}
```

---

## 9. 最佳实践

### 9.1 基本使用

**推荐做法**：
```typescript
// 1. 设置选项
ContainerPicker({ options: ['A', 'B', 'C'] })
  .selected(0)
  .onChange((index: number) => {
    console.log('Selected:', index);
  })

// 2. 启用循环
ContainerPicker()
  .loop(true)

// 3. 禁用触觉反馈
ContainerPicker()
  .enableHaptic(false)
```

### 9.2 性能优化

```typescript
// 1. 限制选项数量
ContainerPicker()
  .options(items.slice(0, 100))  // 避免过多选项

// 2. 使用虚拟滚动
// 内部自动实现，只需提供数据源
```

---

## 10. 问题排查

### 10.1 常见问题

| 症状 | 可能原因 | 解决方案 |
|------|---------|----------|
| 滚动卡顿 | 选项过多 | 减少选项数量 |
| 回弹不自然 | 弹簧参数错误 | 调整弹簧曲线 |
| 触觉无响应 | 权限问题 | 检查触觉权限 |
| 位置偏移 | 高度计算错误 | 检查布局配置 |

### 10.2 调试工具

**日志输出**：
```bash
# 查看滚动相关日志
hilog -T ArkUI | grep -i picker
```

---

## 相关目录

```
frameworks/core/components_ng/pattern/container_picker/
├── container_picker_pattern.h/cpp            # 主要逻辑
├── container_picker_layout_property.h        # 布局属性
├── container_picker_layout_algorithm.h/cpp   # 布局算法
├── container_picker_event_hub.h              # 事件处理
├── container_picker_paint_method.h/cpp       # 绘制方法
├── container_picker_utils.h                  # 工具类
└── container_picker_theme.h                  # 主题配置
```

---

## 关键要点总结

1. **平滑滚动**: 物理模型驱动的惯性滚动
2. **吸附对齐**: 自动吸附到最近的选项
3. **循环滚动**: 支持无限循环选项列表
4. **触觉反馈**: 滚动时提供震动反馈
5. **边界回弹**: 弹簧动画实现边界回弹
6. **FRC 优化**: 根据速度动态调整刷新率
7. **手势支持**: 完整的拖拽、点击手势支持
8. **嵌套滚动**: 继承 NestableScrollContainer，支持嵌套

---
