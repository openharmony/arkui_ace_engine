# 手势系统完整知识库

> **文档版本**: v1.0  
> **更新时间**: 2026-02-11  
> **源码版本**: OpenHarmony ace_engine (master 分支)  
> **相关文档**: [拖拽系统](./Drag_Drop_Knowledge_Base_CN.md) (基于手势扩展)

---

## 📚 目录

1. [概述](#概述)
2. [系统架构](#系统架构)
3. [目录结构](#目录结构)
4. [手势识别系统](#手势识别系统)
5. [手势仲裁器](#手势仲裁器)
6. [完整API清单](#完整api清单)
7. [核心实现细节](#核心实现细节)
8. [使用示例](#使用示例)
9. [调试指南](#调试指南)
10. [常见问题](#常见问题)

---

## 概述

### 系统定位

**手势系统**是 OpenHarmony ArkUI 框架中的**用户交互识别核心模块**,负责识别和响应触摸、鼠标等输入事件,支持复杂的手势组合和手势仲裁机制。

手势系统是拖拽系统的基础,拖拽功能基于 Pan(滑动)手势识别实现。

### 技术架构

```
┌─────────────────────────────────────────────────────────────────┐
│  应用层 (ArkTS)                                        │
│  .onClick() / .onPan() / .onPinch() / .onRotation()  │
└─────────────────────────────────────────────────────────────────┘
                               ↓
┌─────────────────────────────────────────────────────────────────┐
│  桥接层 (Model Layer)                                   │
│  GestureModelNG → 创建 Gesture 对象                        │
│  源码：frameworks/core/components_ng/pattern/gesture/      │
└─────────────────────────────────────────────────────────────────┘
                               ↓
┌─────────────────────────────────────────────────────────────────┐
│  手势识别层 (GestureRecognizer Layer)                     │
│  ├── NGGestureRecognizer (基类)                            │
│  ├── TapRecognizer / ClickRecognizer                        │
│  ├── PanRecognizer / SwipeRecognizer                        │
│  ├── PinchRecognizer / RotationRecognizer                  │
│  ├── LongPressRecognizer                                  │
│  └── RecognizerGroup (组合手势)                          │
│  源码：frameworks/core/components_ng/gestures/            │
└─────────────────────────────────────────────────────────────────┘
                               ↓
┌─────────────────────────────────────────────────────────────────┐
│  手势仲裁层 (GestureReferee Layer)                       │
│  ├── GestureReferee (全局仲裁器)                          │
│  ├── GestureScope (手势作用域)                            │
│  └── 仲裁状态机 (ACCEPT/REJECT/PENDING)                  │
│  源码：frameworks/core/components_ng/gestures/            │
└─────────────────────────────────────────────────────────────────┘
                               ↓
┌─────────────────────────────────────────────────────────────────┐
│  平台适配层 (Adapter Layer)                               │
│  TouchEvent / PointerEvent 输入事件处理                     │
└─────────────────────────────────────────────────────────────────┘
```

### 代码规模

| 项目 | 数量 |
|-----|------|
| 核心文件 | 约 40 个文件 |
| 核心代码 | 约 15,000+ 行 C++ 代码 |
| 手势识别器 | 7 种基础手势 + 3 种组合模式 |
| 手势仲裁器 | 全局单例 + 按TouchId划分的Scope |

### 功能特性

| 功能类别 | 具体功能 |
|---------|---------|
| **基础手势** | 点击 (Click)、轻敲 (Tap)、长按 (LongPress) |
| **滑动手势** | 滑动 (Pan)、快速滑动 (Swipe)、方向控制 |
| **缩放旋转** | 捏合 (Pinch)、旋转 (Rotation)、多指手势 |
| **手势组合** | 并行 (Parallel)、序列 (Sequence)、互斥 (Exclusive) |
| **手势仲裁** | 优先级控制、手势竞争、状态同步 |
| **速度追踪** | 速度计算、惯性检测、最小二乘法拟合 |

### 与拖拽系统的关系

手势系统是拖拽系统的基础:
- **拖拽启动**: 基于 Pan 手势识别,当滑动距离超过阈值时触发拖拽
- **拖拽移动**: 延续 Pan 手势的 Move 事件处理
- **拖拽释放**: 对应 Pan 手势的 Up 事件

详细内容参见: [拖拽系统知识库](./Drag_Drop_Knowledge_Base_CN.md)

---

## 系统架构

### 完整调用链

```
┌─────────────────────────────────────────────────────────────────┐
① 输入事件触发                                               │
┌─────────────────────────────────────────────────────────────────┐
│ TouchDown / TouchMove / TouchUp 事件                        │
│ framework/event/touch_event.h                              │
└─────────────────────────────────────────────────────────────────┘
                               ↓
┌─────────────────────────────────────────────────────────────────┐
② 手势识别器接收事件                                         │
┌─────────────────────────────────────────────────────────────────┐
│ NGGestureRecognizer::HandleEvent(TouchEvent)                │
│ framework/components_ng/gestures/recognizers/              │
│           gesture_recognizer.cpp:130-135                     │
│                                                          │
│ 执行流程：                                                 │
│ 1. Transform 坐标变换 (全局→局部)                         │
│ 2. HandleTouchDown/Move/Up 具体处理                       │
│ 3. Adjudicate 提交仲裁结果                                 │
└─────────────────────────────────────────────────────────────────┘
                               ↓
┌─────────────────────────────────────────────────────────────────┐
③ 手势仲裁决策                                             │
┌─────────────────────────────────────────────────────────────────┐
│ GestureReferee::Adjudicate(recognizer, disposal)           │
│ framework/components_ng/gestures/gesture_referee.cpp:58-115  │
│                                                          │
│ 仲裁决策：                                                 │
│ - ACCEPT: 手势被接受,其他手势被拒绝                         │
│ - REJECT: 手势被拒绝                                       │
│ - PENDING: 等待其他手势结果                                │
└─────────────────────────────────────────────────────────────────┘
                               ↓
┌─────────────────────────────────────────────────────────────────┐
④ 手势回调触发                                             │
┌─────────────────────────────────────────────────────────────────┐
│ recognizer->OnAccepted() / OnRejected()                     │
│ 触发用户回调：                                           │
│ - onActionStart (手势开始)                                  │
│ - onActionUpdate (手势更新)                                 │
│ - onActionEnd (手势结束)                                   │
│ - onActionCancel (手势取消)                                 │
└─────────────────────────────────────────────────────────────────┘
```

### 状态机设计

#### 手势识别器状态

```
RefereeState (手势仲裁状态)
├── READY: 初始状态,等待事件
├── DETECTING: 检测中,收集事件
├── PENDING: 等待其他手势结果
├── PENDING_BLOCKED: 被阻塞的等待状态
├── SUCCEED_BLOCKED: 成功后被阻塞
├── SUCCEED: 识别成功
└── FAIL: 识别失败

CurrentCallbackState (回调触发状态)
├── READY: 回调就绪
├── START: 触发 onActionStart
├── UPDATE: 触发 onActionUpdate
├── END: 触发 onActionEnd
└── CANCEL: 触发 onActionCancel
```

---

## 目录结构

```
components_ng/gestures/
├── gesture_info.h                          # 手势基类和配置
├── gesture_referee.h/cpp                   # 手势仲裁器 (全局单例)
├── gesture_group.h/cpp                     # 手势组合器
├── tap_gesture.h/cpp                      # 轻敲手势配置
├── click_gesture.h/cpp                    # 点击手势配置
├── long_press_gesture.h/cpp                # 长按手势配置
├── pan_gesture.h/cpp                      # 滑动手势配置
├── pinch_gesture.h/cpp                    # 捏合手势配置
├── rotation_gesture.h/cpp                 # 旋转手势配置
├── swipe_gesture.h/cpp                    # 快速滑动手势配置
├── base_gesture_event.h                   # 基础手势事件
└── recognizers/                           # 手势识别器实现
    ├── gesture_recognizer.h/cpp           # 识别器基类
    ├── multi_fingers_recognizer.h/cpp     # 多指手势基类
    ├── recognizer_group.h/cpp             # 组合手势识别器
    ├── tap_recognizer.h/cpp             # 轻敲识别器
    ├── click_recognizer.h/cpp            # 点击识别器
    ├── long_press_recognizer.h/cpp       # 长按识别器
    ├── pan_recognizer.h/cpp             # 滑动识别器
    ├── pinch_recognizer.h/cpp           # 捏合识别器
    ├── rotation_recognizer.h/cpp        # 旋转识别器
    ├── swipe_recognizer.h/cpp          # 快速滑动识别器
    ├── sequenced_recognizer.h/cpp      # 序列组合识别器
    ├── parallel_recognizer.h/cpp       # 并行组合识别器
    └── exclusive_recognizer.h/cpp      # 互斥组合识别器

components_ng/pattern/gesture/
├── gesture_model_ng.h/cpp               # 手势 Model 实现
├── gesture_model_ng_static.h/cpp        # 静态 API 桥接
└── gesture_model.h                     # 手势 Model 接口

core/event/
├── touch_event.h                       # 触摸事件定义
└── pointer_event.h                     # 指针事件定义

core/gestures/
├── gesture_event.h                     # 手势事件 (Legacy)
├── gesture_info.h                      # 手势信息定义
├── gesture_type.h                     # 手势类型枚举
└── velocity_tracker.h                  # 速度追踪器
```

---

## 手势识别系统

### 核心类继承关系

```
                    TouchEventTarget (触摸事件目标)
                            ↑
        ┌───────────────────┴───────────────────┐
        │                                       │
NGGestureRecognizer                    MultiFingersRecognizer
(基类,状态机)                       (多指手势基类)
        │                                       │
    ┌───┴────┬────────┬────────┬─────┐     │
    │         │        │        │     │     └─ PanRecognizer
    │         │        │        │     │     └─ PinchRecognizer
TapRecognizer ClickRecognizer  ...    │     └─ RotationRecognizer
    │         │               LongPressRecognizer
    │         │
    └─ SwipeRecognizer
```

### NGGestureRecognizer 基类

**源码位置**: `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/gestures/recognizers/gesture_recognizer.h`

**核心职责**:

```cpp
class ACE_FORCE_EXPORT NGGestureRecognizer : public TouchEventTarget {
public:
    // 1. 仲裁相关接口
    virtual void OnAccepted() = 0;      // 手势被接受时调用
    virtual void OnRejected() = 0;      // 手势被拒绝时调用
    virtual void OnPending();            // 手势等待时调用
    virtual void OnBlocked();            // 手势被阻塞时调用

    // 2. 事件处理接口
    bool HandleEvent(const TouchEvent& point);
    bool HandleEvent(const AxisEvent& event);

    // 3. 状态管理
    enum class RefereeState {
        READY, DETECTING, PENDING, PENDING_BLOCKED,
        SUCCEED_BLOCKED, SUCCEED, FAIL
    };

    // 4. 回调设置
    void SetOnAction(const GestureEventFunc& onAction);
    void SetOnActionStart(const GestureEventFunc& onActionStart);
    void SetOnActionUpdate(const GestureEventFunc& onActionUpdate);
    void SetOnActionEnd(const GestureEventFunc& onActionEnd);
    void SetOnActionCancel(const GestureEventFunc& onActionCancel);
};
```

**关键实现** - `gesture_recognizer.cpp:130-135`
```cpp
bool NGGestureRecognizer::HandleEvent(const TouchEvent& point)
{
    // 坐标变换:全局坐标 → 局部坐标
    TransformForRecognizer(localPointF, node_, isRealTime_, isPostEventResult_, postEventNodeId_);

    // 分发到具体处理函数
    switch (point.type) {
        case TouchType::DOWN:
            HandleTouchDownEvent(point);
            break;
        case TouchType::MOVE:
            HandleTouchMoveEvent(point);
            break;
        case TouchType::UP:
        case TouchType::CANCEL:
            HandleTouchUpEvent(point);
            break;
    }

    return true;
}
```

### 基础手势识别器

#### 点击识别器 (ClickRecognizer)

**源码位置**: `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/gestures/recognizers/click_recognizer.h`

**识别逻辑**:

```cpp
// 配置参数
ClickRecognizer(
    int32_t fingers,        // 手指数量
    int32_t count,          // 点击次数
    double distanceThreshold  // 距离阈值
);

// 识别流程
void ClickRecognizer::HandleTouchDownEvent(const TouchEvent& event) {
    // 1. 记录按下时间和位置
    touchDownTime_ = event.time;
    focusPoint_ = event.GetLocalLocation();

    // 2. 启动超时检测
    tapDeadlineTimer_.Cancel();
    tapDeadlineTimer_.Reset([weak = WeakClaim(this)]() {
        auto recognizer = weak.Upgrade();
        if (recognizer) {
            recognizer->HandleOverdueDeadline();  // 超时判定为失败
        }
    });
    tapDeadlineTimer_.Start(userDT_);  // 用户配置的点击超时时间
}

void ClickRecognizer::HandleTouchUpEvent(const TouchEvent& event) {
    // 1. 检查移动距离是否在阈值内
    if (ExceedSlop()) {
        OnRejected();
        return;
    }

    // 2. 检查点击次数
    tappedCount_++;
    if (tappedCount_ >= count_) {
        // 达到点击次数,触发回调
        Adjudicate(AceType::Claim(this), GestureDisposal::ACCEPT);
    }

    // 3. 如果需要多次点击,继续等待
    if (tappedCount_ < count_) {
        tapDeadlineTimer_.Start(userDT_);
    }
}
```

**关键判断** - `click_recognizer.cpp:378-392`
```cpp
bool ClickRecognizer::ExceedSlop()
{
    // 计算从按下点到当前点的距离
    Offset offset = currentPoint_ - focusPoint_;
    double distance = std::sqrt(
        offset.GetX() * offset.GetX() + offset.GetY() * offset.GetY()
    );

    // 检查是否超过阈值
    double threshold = distanceThreshold_.ConvertToPx();
    return distance > threshold;
}
```

#### 长按识别器 (LongPressRecognizer)

**源码位置**: `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/gestures/recognizers/long_press_recognizer.h`

**识别逻辑**:

```cpp
void LongPressRecognizer::HandleTouchDownEvent(const TouchEvent& event) {
    // 1. 记录按下位置
    globalPoint_ = { event.x, event.y };

    // 2. 启动长按检测定时器
    longPressDeadlineTimer_.Cancel();
    longPressDeadlineTimer_.Reset([weak = WeakClaim(this)]() {
        auto recognizer = weak.Upgrade();
        CHECK_NULL_VOID(recognizer);

        // 触发长按手势
        recognizer->Adjudicate(
            AceType::Claim(recognizer),
            GestureDisposal::ACCEPT
        );
    });
    longPressDeadlineTimer_.Start(duration_);  // duration_ 为配置时长

    time_ = event.time;
}

void LongPressRecognizer::HandleTouchMoveEvent(const TouchEvent& event) {
    // 1. 检查移动距离
    Offset offset = Offset(event.x, event.y) - globalPoint_;
    double distance = std::sqrt(
        offset.GetX() * offset.GetX() + offset.GetY() * offset.GetY()
    );

    // 2. 超过阈值则拒绝长按
    if (distance > fingerIdToDistanceMap_[event.id]) {
        OnRejected();
        longPressDeadlineTimer_.Cancel();
    }
}
```

### 滑动手势识别器

#### Pan手势识别器 (PanRecognizer)

**源码位置**: `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/gestures/recognizers/pan_recognizer.h`

**识别逻辑**:

```cpp
enum GestureAcceptResult {
    ACCEPT,    // 接受
    REJECT,    // 拒绝
    DETECTING  // 继续检测
};

PanRecognizer::GestureAcceptResult PanRecognizer::IsPanGestureAccept() const
{
    double judgeDistance = GetDistance();

    // 根据方向判断
    switch (direction_) {
        case PanDirection::ALL:
            return IsPanGestureAcceptInAllDirection(judgeDistance);
        case PanDirection::HORIZONTAL:
            return IsPanGestureAcceptInHorizontalDirection(judgeDistance);
        case PanDirection::VERTICAL:
            return IsPanGestureAcceptInVerticalDirection(judgeDistance);
        default:
            return GestureAcceptResult::DETECTING;
    }
}

PanRecognizer::GestureAcceptResult
PanRecognizer::IsPanGestureAcceptInHorizontalDirection(double judgeDistance) const
{
    // 1. 计算水平移动距离
    double deltaX = std::abs(mainDelta_);

    // 2. 判断是否超过阈值
    if (deltaX >= judgeDistance) {
        // 3. 检查垂直移动是否过大 (防止误判)
        if (JudgeVerticalDistance()) {
            return GestureAcceptResult::REJECT;
        }
        return GestureAcceptResult::ACCEPT;
    }

    return GestureAcceptResult::DETECTING;
}

void PanRecognizer::HandleTouchMoveEvent(const TouchEvent& event) {
    // 1. 更新速度追踪
    panVelocity_.UpdateTouchPoint(event.id, event, false);

    // 2. 计算主轴移动距离
    mainDelta_ = GetMainAxisDelta();

    // 3. 判断是否接受滑动
    auto result = IsPanGestureAccept();
    if (result == GestureAcceptResult::ACCEPT) {
        // 提交接受
        Adjudicate(AceType::Claim(this), GestureDisposal::ACCEPT);
    } else if (result == GestureAcceptResult::REJECT) {
        // 提交拒绝
        OnRejected();
    }
}
```

**速度追踪** - `pan_recognizer.cpp:482-521`
```cpp
class PanRecognizer::PanVelocity {
public:
    void UpdateTouchPoint(int32_t id, const TouchEvent& event, bool end) {
        // 更新速度追踪器
        auto& tracker = trackerMap_[id];
        if (end) {
            tracker.EndMovement();
        } else {
            tracker.AddMovement(event);
        }
    }

    double GetMainAxisVelocity() {
        // 获取最快手指的主轴速度
        auto getVelocity = [this](VelocityTracker& tracker) {
            auto velocity = tracker.GetVelocity();
            switch (axis_) {
                case Axis::HORIZONTAL:
                    return velocity.GetX();
                case Axis::VERTICAL:
                    return velocity.GetY();
                default:
                    return std::max(std::abs(velocity.GetX()),
                                   std::abs(velocity.GetY()));
            }
        };

        return GetFastestTracker(getVelocity);
    }

private:
    std::map<int32_t, VelocityTracker> trackerMap_;  // 每个手指一个追踪器
    Axis axis_;
};
```

**重要**: Pan 手势识别是拖拽系统的基础,当滑动距离超过特定阈值时会触发拖拽启动。详见: [拖拽系统知识库](./Drag_Drop_Knowledge_Base_CN.md)

#### Swipe手势识别器 (SwipeRecognizer)

**源码位置**: `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/gestures/recognizers/swipe_recognizer.h`

**识别逻辑**: 快速滑动检测,基于速度和方向的组合判断

### 缩放旋转手势识别器

#### 捏合识别器 (PinchRecognizer)

**源码位置**: `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/gestures/recognizers/pinch_recognizer.h`

**识别逻辑**:

```cpp
void PinchRecognizer::HandleTouchMoveEvent(const TouchEvent& event) {
    if (currentFingers_ < 2) {
        return;  // 捏合至少需要两个手指
    }

    // 1. 计算两个手指之间的距离
    if (currentFingers_ == 2) {
        auto point1 = touchPoints_[fingersId_[0]].localLocation;
        auto point2 = touchPoints_[fingersId_[1]].localLocation;
        double currentDistance = (point1 - point2).GetLength();

        // 2. 计算缩放比例
        if (initialDistance_ > 0) {
            scale_ = currentDistance / initialDistance_;
        }

        // 3. 判断是否超过缩放阈值
        if (std::abs(scale_ - 1.0) >= distanceThreshold_) {
            Adjudicate(AceType::Claim(this), GestureDisposal::ACCEPT);
        }
    }
}
```

#### 旋转识别器 (RotationRecognizer)

**源码位置**: `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/gestures/recognizers/rotation_recognizer.h`

**识别逻辑**: 基于两个手指间的角度变化检测旋转手势

### 手势组合识别器

#### 并行手势 (ParallelRecognizer)

**源码位置**: `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/gestures/recognizers/parallel_recognizer.h`

**特性**: 所有的子手势同时识别,任何一个成功则整体成功

#### 序列手势 (SequencedRecognizer)

**源码位置**: `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/gestures/recognizers/sequenced_recognizer.h`

**特性**: 子手势按顺序识别,前一个成功才识别后一个

#### 互斥手势 (ExclusiveRecognizer)

**源码位置**: `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/gestures/recognizers/exclusive_recognizer.h`

**特性**: 子手势竞争识别,第一个成功则其他被拒绝

---

## 手势仲裁器

### GestureReferee (手势仲裁器)

**源码位置**: `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/gestures/gesture_referee.h`

**核心职责**: 解决多个手势识别器之间的竞争关系

```cpp
class GestureReferee : public virtual AceType {
public:
    // 1. 添加手势到作用域
    void AddGestureToScope(size_t touchId, const TouchTestResult& result);

    // 2. 仲裁决策
    void Adjudicate(
        const RefPtr<NGGestureRecognizer>& recognizer,
        GestureDisposal disposal  // ACCEPT/REJECT/PENDING
    );

    // 3. 检查是否有手势被接受
    bool HasGestureAccepted(size_t touchId) const;

    // 4. 清理手势作用域
    void CleanGestureScope(size_t touchId);

private:
    // 按TouchId划分的手势作用域
    std::unordered_map<size_t, RefPtr<GestureScope>> gestureScopes_;
};
```

### GestureScope (手势作用域)

**源码位置**: `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/gestures/gesture_referee.h:48-111`

```cpp
class GestureScope : public AceType {
public:
    explicit GestureScope(size_t touchId) : touchId_(touchId) {}

    // 添加手势识别器到作用域
    void AddMember(const RefPtr<NGGestureRecognizer>& recognizer);

    // 移除手势识别器
    void DelMember(const RefPtr<NGGestureRecognizer>& recognizer);

    // 关闭作用域
    void Close(bool isBlocked = false);

    // 检查是否所有手势都完成
    bool IsReady();

    // 检查是否有失败的手势
    bool HasFailRecognizer();

    // 检查是否有成功的手势
    bool IsAnySucceedRecognizerExist();

private:
    // 作用域内的所有手势识别器
    std::list<WeakPtr<NGGestureRecognizer>> recognizers_;

    size_t touchId_;  // 触摸点ID
    bool isDelay_;    // 是否延迟关闭
    bool hasGestureAccepted_;  // 是否有手势被接受
};
```

### 仲裁流程

**源码位置**: `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/gestures/gesture_referee.cpp:58-115`

```cpp
void GestureReferee::Adjudicate(
    const RefPtr<NGGestureRecognizer>& recognizer,
    GestureDisposal disposal)
{
    auto scope = gestureScopes_[touchId];
    CHECK_NULL_VOID(scope);

    switch (disposal) {
        case GestureDisposal::ACCEPT:
            HandleAcceptDisposal(recognizer, scope);
            break;

        case GestureDisposal::REJECT:
            HandleRejectDisposal(recognizer, scope);
            break;

        case GestureDisposal::PENDING:
            HandlePendingDisposal(recognizer, scope);
            break;

        default:
            break;
    }

    // 检查是否需要关闭作用域
    if (scope->IsReady()) {
        scope->Close();
    }
}

void GestureReferee::HandleAcceptDisposal(
    const RefPtr<NGGestureRecognizer>& recognizer,
    const RefPtr<GestureScope>& scope)
{
    // 1. 标记有手势被接受
    scope->OnAcceptGesture(recognizer);

    // 2. 阻塞其他PENDING手势
    for (const auto& item : scope->recognizers_) {
        auto r = item.Upgrade();
        if (r && r != recognizer) {
            if (r->GetGestureDisposal() == GestureDisposal::PENDING) {
                r->OnBlocked();  // 设置为PENDING_BLOCKED
            }
        }
    }

    // 3. 触发成功回调
    recognizer->OnAccepted();
}
```

---

## 完整API清单

### 基础手势API

#### 点击手势 (Click)

**ArkTS API**:
```typescript
.onClick(event: (event?: ClickEvent) => void)
```

**配置参数**:
```typescript
// gesture_model_ng_static.h
gesture(value: ClickGesture): void

// ClickGesture 定义
interface ClickGesture {
  count?: number;              // 点击次数,默认 1
  fingers?: number;            // 手指数量,默认 1
  distance?: number | Dimension; // 点击距离阈值
}
```

**回调事件** - `ClickEvent`:
```typescript
interface ClickEvent {
  repeat?: boolean;  // 是否为重复点击
  screenX?: number;  // 屏幕X坐标
  screenY?: number;  // 屏幕Y坐标
  x?: number;       // 相对组件X坐标
  y?: number;       // 相对组件Y坐标
  timestamp?: number; // 时间戳
  target?: UIComponent; // 目标组件
}
```

#### 轻敲手势 (Tap)

**ArkTS API**:
```typescript
.gesture(
  TapGesture({ count: 2, fingers: 1 })
    .onAction((event: GestureEvent) => void)
)
```

**配置参数**:
```typescript
interface TapGesture {
  count?: number;              // 轻敲次数
  fingers?: number;            // 手指数量
}
```

#### 长按手势 (LongPress)

**ArkTS API**:
```typescript
.gesture(
  LongPressGesture({ duration: 1000, repeat: false })
    .onAction(() => void)
    .onActionEnd(() => void)
)
```

**配置参数**:
```typescript
interface LongPressGesture {
  duration?: number;      // 长按持续时间 (ms),默认 500
  repeat?: boolean;       // 是否重复触发
  fingers?: number;       // 手指数量
}
```

### 滑动手势API

#### Pan手势 (滑动)

**ArkTS API**:
```typescript
.gesture(
  PanGesture({ direction: PanDirection.Horizontal, distance: 20 })
    .onActionStart((event: GestureEvent) => void)
    .onActionUpdate((event: GestureEvent) => void)
    .onActionEnd((event: GestureEvent) => void)
)
```

**配置参数**:
```typescript
enum PanDirection {
  All,
  Horizontal,
  Vertical,
  Left,
  Right,
  Up,
  Down,
  None
}

interface PanGesture {
  direction?: PanDirection;  // 滑动方向,默认 All
  distance?: number;        // 最小滑动距离
  fingers?: number;        // 手指数量
}
```

**回调事件** - `GestureEvent`:
```typescript
interface GestureEvent {
  offsetX?: number;    // X轴偏移
  offsetY?: number;    // Y轴偏移
  angle?: number;      // 滑动角度
  speed?: number;      // 滑动速度
  scale?: number;      // 缩放比例
  pinchCenterX?: number; // 捏合中心X
  pinchCenterY?: number; // 捏合中心Y
  timestamp?: number;
  target?: UIComponent;
}
```

#### Swipe手势 (快速滑动)

**ArkTS API**:
```typescript
.gesture(
  SwipeGesture({ direction: SwipeDirection.Horizontal, speed: 200 })
    .onAction((event: GestureEvent) => void)
)
```

**配置参数**:
```typescript
enum SwipeDirection {
  Horizontal,
  Vertical,
  Left,
  Right,
  Up,
  Down
}

interface SwipeGesture {
  direction?: SwipeDirection;  // 滑动方向
  speed?: number;           // 最小滑动速度
  fingers?: number;         // 手指数量
}
```

### 缩放旋转手势API

#### Pinch手势 (捏合)

**ArkTS API**:
```typescript
.gesture(
  PinchGesture({ fingers: 2, distance: 1.0 })
    .onActionStart((event: GestureEvent) => void)
    .onActionUpdate((event: GestureEvent) => void)
    .onActionEnd((event: GestureEvent) => void)
)
```

**配置参数**:
```typescript
interface PinchGesture {
  fingers?: number;  // 手指数量,至少2个
  distance?: number; // 捏合距离阈值
}
```

#### Rotation手势 (旋转)

**ArkTS API**:
```typescript
.gesture(
  RotationGesture({ angle: 10 })
    .onActionStart((event: GestureEvent) => void)
    .onActionUpdate((event: GestureEvent) => void)
    .onActionEnd((event: GestureEvent) => void)
)
```

**配置参数**:
```typescript
interface RotationGesture {
  fingers?: number;  // 手指数量,至少2个
  angle?: number;    // 旋转角度阈值
}
```

### 手势组合API

#### 并行手势 (Parallel)

```typescript
.gesture(
  ParallelGesture([
    TapGesture({ count: 1 }),
    LongPressGesture({ duration: 500 })
  ])
)
```

**特性**: 所有的子手势同时识别,任何一个成功则整体成功

#### 序列手势 (Sequence)

```typescript
.gesture(
  SequenceGesture([
    TapGesture({ count: 1 }),
    SwipeGesture({ direction: SwipeDirection.Right })
  ])
)
```

**特性**: 子手势按顺序识别,前一个成功才识别后一个

#### 互斥手势 (Exclusive)

```typescript
.gesture(
  ExclusiveGesture([
    TapGesture({ count: 1 }),
    LongPressGesture({ duration: 500 })
  ])
)
```

**特性**: 子手势竞争识别,第一个成功则其他被拒绝

---

## 核心实现细节

### 手势识别算法

#### 速度追踪算法

**源码位置**: `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/gestures/velocity_tracker.h`

```cpp
class VelocityTracker {
public:
    // 添加移动点
    void AddMovement(const PointerEvent& event);

    // 获取速度
    Velocity GetVelocity();

private:
    // 使用最小二乘法拟合速度
    void ComputeCurrentVelocity(int32_t units);

    // 历史移动点
    std::vector<PointerEvent> events_;

    // 计算出的速度
    Velocity velocity_;
};

void VelocityTracker::ComputeCurrentVelocity(int32_t units)
{
    if (events_.size() < 2) {
        return;
    }

    // 最小二乘法计算速度
    double sumX = 0, sumY = 0, sumXX = 0, sumXY = 0, sumYY = 0;
    int32_t n = events_.size();

    for (int32_t i = 0; i < n; i++) {
        double t = events_[i].time.time_since_epoch().count();
        double x = events_[i].x;
        double y = events_[i].y;

        sumX += x;
        sumY += y;
        sumXX += x * x;
        sumXY += x * y;
        sumYY += y * y;
    }

    // 计算X和Y方向的速度
    double vx = (sumXY - sumX * sumY / n) / (sumXX - sumX * sumX / n);
    double vy = (sumYY - sumY * sumY / n) / (sumXX - sumX * sumX / n);

    velocity_ = Velocity(vx, vy, units);
}
```

#### 距离计算算法

```cpp
// 计算欧几里得距离
double CalculateDistance(const Point& p1, const Point& p2) {
    double dx = p1.x - p2.x;
    double dy = p1.y - p2.y;
    return std::sqrt(dx * dx + dy * dy);
}

// 计算主轴移动距离 (用于Pan手势)
double GetMainAxisDelta() {
    switch (direction_) {
        case PanDirection::HORIZONTAL:
            return delta_.GetX();  // 只考虑X轴
        case PanDirection::VERTICAL:
            return delta_.GetY();  // 只考虑Y轴
        default:
            return std::max(
                std::abs(delta_.GetX()),
                std::abs(delta_.GetY())
            );
    }
}
```

### 手势仲裁机制

#### 仲裁决策策略

1. **ACCEPT 决策**:
   - 手势识别器确定识别成功
   - 其他 PENDING 状态的手势被阻塞 (OnBlocked)
   - 触发当前手势的 OnAccepted 回调

2. **REJECT 决策**:
   - 手势识别器确定识别失败
   - 不影响其他手势
   - 触发当前手势的 OnRejected 回调

3. **PENDING 决策**:
   - 手势识别器需要更多事件判断
   - 等待其他手势的最终结果
   - 如果其他手势被接受,则当前手势被阻塞

#### 作用域生命周期

```
TouchDown → 创建 GestureScope
    ↓
添加所有相关的识别器
    ↓
各识别器提交 ACCEPT/REJECT/PENDING
    ↓
所有识别器完成 → 关闭 Scope
    ↓
TouchUp → 清理 Scope
```

---

## 使用示例

### 基础手势示例

#### 点击手势

```typescript
@Entry
@Component
struct ClickExample {
  @State clickCount: number = 0;

  build() {
    Text('点击次数: ' + this.clickCount)
      .width(200)
      .height(100)
      .backgroundColor(Color.Pink)
      .onClick(() => {
        this.clickCount++;
      })
  }
}
```

#### 长按手势

```typescript
@Entry
@Component
struct LongPressExample {
  @State message: string = '长按我';

  build() {
    Text(this.message)
      .width(200)
      .height(100)
      .backgroundColor(Color.Orange)
      .gesture(
        LongPressGesture({ duration: 1000 })
          .onAction(() => {
            this.message = '长按触发!';
          })
          .onActionEnd(() => {
            this.message = '长按结束';
          })
      )
  }
}
```

#### 滑动手势

```typescript
@Entry
@Component
struct PanExample {
  @State offsetX: number = 0;
  @State offsetY: number = 0;

  build() {
    Text('滑动我')
      .width(200)
      .height(100)
      .backgroundColor(Color.Blue)
      .translate({ x: this.offsetX, y: this.offsetY })
      .gesture(
        PanGesture({ direction: PanDirection.All })
          .onActionUpdate((event: GestureEvent) => {
            this.offsetX += event.offsetX;
            this.offsetY += event.offsetY;
          })
      )
  }
}
```

#### 捏合缩放

```typescript
@Entry
@Component
struct PinchExample {
  @State scale: number = 1;

  build() {
    Text('捏合缩放')
      .width(200)
      .height(100)
      .backgroundColor(Color.Green)
      .scale({ x: this.scale, y: this.scale })
      .gesture(
        PinchGesture()
          .onActionUpdate((event: GestureEvent) => {
            this.scale = event.scale;
          })
      )
  }
}
```

### 手势组合示例

#### 并行手势

```typescript
@Entry
@Component
struct ParallelExample {
  @State message: string = '同时按下并长按';

  build() {
    Text(this.message)
      .width(200)
      .height(100)
      .backgroundColor(Color.Purple)
      .gesture(
        ParallelGesture([
          TapGesture({ count: 1 }),
          LongPressGesture({ duration: 500 })
        ])
          .onAction(() => {
            this.message = '并行手势触发';
          })
      )
  }
}
```

#### 序列手势

```typescript
@Entry
@Component
struct SequenceExample {
  @State message: string = '先点击再右滑';

  build() {
    Text(this.message)
      .width(200)
      .height(100)
      .backgroundColor(Color.Red)
      .gesture(
        SequenceGesture([
          TapGesture({ count: 1 }),
          SwipeGesture({ direction: SwipeDirection.Right })
        ])
          .onAction(() => {
            this.message = '序列手势完成';
          })
      )
  }
}
```

#### 互斥手势

```typescript
@Entry
@Component
struct ExclusiveExample {
  @State message: string = '点击或长按';

  build() {
    Text(this.message)
      .width(200)
      .height(100)
      .backgroundColor(Color.Yellow)
      .gesture(
        ExclusiveGesture([
          TapGesture({ count: 1 }),
          LongPressGesture({ duration: 500 })
        ])
          .onAction(() => {
            this.message = '某个手势触发';
          })
      )
  }
}
```

---

## 调试指南

### 手势识别调试

#### 启用手势调试日志

```cpp
// 在代码中启用调试
#define ENABLE_GESTURE_DEBUG 1

// 在 gesture_recognizer.h 中
#ifdef ENABLE_GESTURE_DEBUG
    #define GESTURE_LOG(content) LOGI("[Gesture] " content)
#else
    #define GESTURE_LOG(content)
#endif
```

#### 常见调试方法

1. **追踪事件流**:
   ```cpp
   bool NGGestureRecognizer::HandleEvent(const TouchEvent& point) {
       GESTURE_LOG("HandleEvent type=" + std::to_string(point.type));
       // ...
   }
   ```

2. **追踪仲裁决策**:
   ```cpp
   void GestureReferee::Adjudicate(...) {
       GESTURE_LOG("Adjudicate: " + std::to_string((int)disposal));
       // ...
   }
   ```

3. **追踪状态转换**:
   ```cpp
   void PanRecognizer::HandleTouchMoveEvent(const TouchEvent& event) {
       GESTURE_LOG("State=" + std::to_string((int)refereeState_));
       // ...
   }
   ```

### 手势冲突解决

#### 问题: 手势不触发

**可能原因**:
1. 手势被其他手势仲裁器拒绝
2. 移动距离未达到阈值
3. 超时时间未设置正确

**解决方法**:
```typescript
// 1. 降低阈值
PanGesture({ direction: PanDirection.All, distance: 5 })

// 2. 使用互斥手势避免冲突
ExclusiveGesture([
  PanGesture({ direction: PanDirection.Horizontal }),
  PanGesture({ direction: PanDirection.Vertical })
])

// 3. 检查父容器手势
// 确保父容器没有拦截事件
```

#### 问题: 多手势同时触发

**解决方法**:
```typescript
// 使用 ExclusiveGesture 确保只有一个手势触发
ExclusiveGesture([
  PanGesture(),
  LongPressGesture()
])
```

### 性能优化

#### 减少手势识别器数量

```typescript
// ❌ 不推荐: 创建多个独立手势
.gesture(PanGesture())
.gesture(LongPressGesture())
.gesture(PinchGesture())

// ✅ 推荐: 使用组合手势
.gesture(
  ExclusiveGesture([
    PanGesture(),
    LongPressGesture(),
    PinchGesture()
  ])
)
```

#### 优化阈值设置

```typescript
// 根据实际场景设置合适的阈值
PanGesture({ 
  direction: PanDirection.Horizontal,
  distance: 8  // 较小的阈值可以提高响应速度
})
```

---

## 常见问题

### Q1: 手势识别延迟高怎么办?

**A**: 可能原因和解决方法:
1. 检查是否设置了过大的阈值,适当降低
2. 检查是否有耗时操作阻塞在回调中
3. 使用更高效的手势组合策略

### Q2: 为什么手势总是被拒绝?

**A**: 可能原因:
1. 存在优先级更高的手势识别器
2. 移动距离未达到阈值
3. 手势配置的方向不匹配

解决方法: 使用 ExclusiveGesture 或调整手势优先级

### Q3: 如何实现自定义手势?

**A**: 继承 NGGestureRecognizer 并实现关键方法:

```cpp
class CustomRecognizer : public NGGestureRecognizer {
public:
    void OnAccepted() override {
        // 手势被接受时的处理
    }

    void OnRejected() override {
        // 手势被拒绝时的处理
    }

    void HandleTouchDownEvent(const TouchEvent& event) override {
        // 处理按下事件
    }

    void HandleTouchMoveEvent(const TouchEvent& event) override {
        // 处理移动事件
    }

    void HandleTouchUpEvent(const TouchEvent& event) override {
        // 处理抬起事件
    }
};
```

### Q4: 手势和拖拽系统是什么关系?

**A**: 手势系统是基础,拖拽系统基于 Pan 手势识别实现。当 Pan 手势识别到滑动距离超过特定阈值时,会触发拖拽启动。详细内容参见: [拖拽系统知识库](./Drag_Drop_Knowledge_Base_CN.md)

### Q5: 如何判断手势识别器当前状态?

**A**: 通过 RefereeState 枚举判断:

```cpp
enum class RefereeState {
    READY, DETECTING, PENDING, PENDING_BLOCKED,
    SUCCEED_BLOCKED, SUCCEED, FAIL
};

auto state = recognizer->GetRefereeState();
if (state == RefereeState::SUCCEED) {
    // 手势识别成功
}
```

### Q6: 手势仲裁器如何处理并发手势?

**A**: 手势仲裁器按以下策略处理:
1. 按 TouchId 划分作用域 (GestureScope)
2. 同一作用域内的手势通过 ACCEPT/REJECT/PENDING 机制竞争
3. 第一个 ACCEPT 的手势会阻塞其他 PENDING 手势
4. 作用域在所有手势完成后关闭

---

## 参考文档

- [拖拽系统知识库](./Drag_Drop_Knowledge_Base_CN.md) - 基于手势扩展的拖拽功能
- OpenHarmony ArkUI 官方文档: https://docs.openharmony.cn/
- 手势系统源码: `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/gestures/`

---

**文档维护**: 本文档随代码版本更新,如有疑问或建议,请查阅源码或提交 Issue。
