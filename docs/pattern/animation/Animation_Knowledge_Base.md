# ArkUI Animation 模块完整知识库

> **文档版本**：v2.0 (Extended) 🆕
> **更新时间**：2026-02-02
> **源码版本**：OpenHarmony ace_engine (master 分支)
> **作者**：基于 CLAUDE.md 规范自动生成
>
> **v2.0 更新内容**：
> - ✅ 新增 Evaluator 评估器系统详解（5种评估器类型）
> - ✅ 新增 Animatable 属性系统完整列表（40+种属性）
> - ✅ 扩展 Spring 物理模型数学公式（三种阻尼模式）
> - ✅ 扩展曲线系统完整实现（20+种预设曲线）
> - ✅ 新增动画编排系统详解（AnimatorGroup、ChainAnimation）
> - ✅ 扩展过渡效果系统（SharedTransition、CardTransition详细实现）
> - ✅ 新增高级动画特性（BezierVariableVelocityMotion、PictureAnimation）
> - ✅ 新增性能优化专题（异步动画、帧率优化、缓存机制）
> - ✅ 扩展SVG动画详细实现（完整API、高级特性、使用示例）

---

## 📚 目录

1. [概述](#概述)
2. [架构设计](#架构设计)
3. [目录结构](#目录结构)
4. [核心类继承关系](#核心类继承关系)
5. [Animator 详解](#animator-详解)
6. [Animation 层详解](#animation-层详解)
7. [Evaluator 评估器系统](#evaluator-评估器系统) 🆕
8. [Animatable 属性系统](#animatable-属性系统) 🆕
9. [曲线系统](#曲线系统)
10. [运动系统](#运动系统)
11. [调度系统](#调度系统)
12. [动画编排](#动画编排) 🆕
13. [过渡效果](#过渡效果)
14. [高级动画特性](#高级动画特性) 🆕
15. [性能优化](#性能优化) 🆕
16. [SVG 动画](#svg-动画)
17. [完整 API 清单](#完整-api-清单)
18. [使用示例](#使用示例)
19. [调试指南](#调试指南)
20. [常见问题](#常见问题)
21. [附录](#附录)

---

## 概述

### 模块定位

**Animation 模块**是 OpenHarmony ArkUI 框架中的**核心动画引擎**，提供完整的动画基础设施，支持基于时间插值的动画、基于物理的运动动画、弹簧动画、关键帧动画、属性动画等多种动画形式。

**技术栈**：
- **语言**：C++ (模板类设计)
- **调度**：基于 VSync 的帧回调调度
- **物理模拟**：弹簧模型、摩擦力模型
- **渲染集成**：与 Rosen 渲染引擎集成

**代码规模**：
- 总文件数：约 90 个文件
- 核心代码：约 25,000+ 行 C++ 代码
- 涉及 3 个架构层次

### 功能特性

Animation 模块支持：

- **多种动画类型**：
  - 基于时间的插值动画（Interpolator）
  - 基于物理的运动动画（Motion）
  - 弹簧动画（SpringAnimation）
  - 关键帧动画（KeyframeAnimation）
  - 属性动画（PropertyAnimation）
  - SVG 动画（SvgAnimate）

- **丰富的曲线类型**：
  - 线性曲线（Linear）
  - 三次贝塞尔曲线（CubicCurve）
  - 弹簧曲线（SpringCurve）
  - 预设曲线（Ease、EaseIn、EaseOut、EaseInOut 等）

- **完整的控制能力**：
  - 播放控制（Play、Pause、Resume、Stop、Finish、Cancel）
  - 方向控制（Forward、Backward、Reverse）
  - 重复控制（Iteration、Repeat）
  - 速度控制（Tempo、Duration）
  - 填充模式（FillMode）

- **动画编排**：
  - 动画链（ChainAnimation）
  - 动画组（AnimatorGroup）
  - 代理控制器（ProxyController）

- **过渡效果**：
  - 共享元素过渡（SharedTransition）
  - 卡片过渡（CardTransition）
  - 页面过渡（PageTransition）

### 设计模式

Animation 模块采用**分层架构** + **模板模式**：

```
┌─────────────────────────────────────────────────────────┐
│  应用层 (ArkTS/JS)                                        │
│  - 显式动画 API (animateTo)                              │
│  - 隐式动画 (组件属性变化)                                │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│  控制层 (Controller Layer)                                │
│  - Animator: 动画控制器                                  │
│  - Scheduler: 动画调度器                                 │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│  插值层 (Interpolator Layer)                              │
│  - Animation<T>: 模板动画基类                             │
│  - CurveAnimation<T>: 曲线动画                           │
│  - KeyframeAnimation<T>: 关键帧动画                      │
│  - SpringAnimation: 弹簧动画                             │
│  - PropertyAnimation: 属性动画                           │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│  曲线层 (Curve Layer)                                     │
│  - Curve: 曲线抽象接口                                   │
│  - CubicCurve: 三次贝塞尔曲线                            │
│  - SpringCurve: 弹簧曲线                                 │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│  运动层 (Motion Layer)                                     │
│  - Motion: 运动抽象基类                                  │
│  - SpringMotion: 弹簧运动                                │
│  - ScrollMotion: 滚动运动                                │
│  - FrictionMotion: 摩擦力运动                            │
└─────────────────────────────────────────────────────────┘
```

---

## 架构设计

### 核心概念

**动画的双轨设计**：

Animation 模块支持两种动画类型：

1. **插值动画（Interpolator）**：基于时间插值的传统动画
   - 支持设置持续时间（Duration）
   - 支持重复和方向控制
   - 支持曲线调整
   - 适用于：属性过渡、淡入淡出、位移等

2. **运动动画（Motion）**：基于物理模拟的动画
   - 无固定持续时间，由物理参数决定
   - 更自然、更流畅
   - 适用于：弹簧效果、滚动回弹、手势跟随等

**关键状态枚举** - `animator.h:46-51`：

```cpp
enum class Status {
    IDLE,    // 未启动或已取消
    RUNNING, // 正在运行
    PAUSED,  // 已暂停
    STOPPED  // 已停止（自然结束或调用 Stop/Finish）
};
```

### 数据流向

```
用户触发（属性变化 / API 调用）
    ↓
创建 Animator
    ↓
添加 Interpolator 或 Motion
    ├─ CurveAnimation: 曲线插值
    ├─ KeyframeAnimation: 关键帧插值
    ├─ SpringAnimation: 弹簧插值
    └─ Motion: 物理运动
    ↓
Animator::Play() / PlayMotion()
    ↓
Scheduler 注册动画
    ↓
VSync 回调 → OnFrame(int64_t duration)
    ↓
 NotifyInterpolator() / NotifyMotion()
    ↓
Interpolator::OnNormalizedTimestampChanged()
Motion::Move()
    ↓
更新属性值 → 触发重绘
```

---

## 目录结构

### 完整目录树

```
frameworks/core/animation/
├── 核心动画类
├── animator.h/cpp                    # Animator 动画控制器
├── animation.h                       # Animation 模板基类
├── animation_pub.h/cpp               # 动画公共接口
├── interpolator.h                    # Interpolator 插值器接口
├── curve_animation.h                 # CurveAnimation 曲线动画
├── keyframe_animation.h              # KeyframeAnimation 关键帧动画
├── spring_animation.h/cpp            # SpringAnimation 弹簧动画
├── property_animation.h/cpp          # PropertyAnimation 属性动画
│
├── 曲线系统
├── curve.h                           # Curve 抽象接口
├── curves.h                          # 预设曲线集合
├── cubic_curve.h/cpp                 # CubicCurve 三次贝塞尔曲线
├── spring_curve.h/cpp                # SpringCurve 弹簧曲线
├── anticipate_curve.h/cpp            # AnticipateCurve 预期曲线
│
├── 运动系统
├── motion.h                          # Motion 运动抽象基类
├── spring_motion.h/cpp               # SpringMotion 弹簧运动
├── scroll_motion.h/cpp               # ScrollMotion 滚动运动
├── friction_motion.h/cpp             # FrictionMotion 摩擦力运动
├── velocity_motion.h                 # VelocityMotion 速度运动
├── select_motion.h                   # SelectMotion 选择运动
│
├── 弹簧模型
├── spring_model.h/cpp                # SpringModel 弹簧模型
├── spring_node.h                     # SpringNode 弹簧节点
├── simple_spring_node.h/cpp          # SimpleSpringNode 简化弹簧节点
├── bilateral_spring_node.h/cpp       # BilateralSpringNode 双向弹簧节点
├── simple_spring_chain.h/cpp         # SimpleSpringChain 弹簧链
├── simple_spring_adapter.h/cpp       # SimpleSpringAdapter 弹簧适配器
├── bilateral_spring_adapter.h/cpp    # BilateralSpringAdapter 双向弹簧适配器
│
├── 关键帧系统
├── keyframe.h                        # Keyframe 关键帧定义
│
├── 评估器
├── evaluator.h                       # Evaluator 评估器模板
│
├── 属性动画支持
├── animatable.h                      # Animatable 可动画属性接口
├── animatable_base.h                 # AnimatableBase 可动画属性基类
├── animatable_data.h/cpp             # AnimatableData 可动画属性数据
├── animatable_properties.h/cpp       # AnimatableProperties 可动画属性集合
├── animatable_transform_operation.h  # AnimatableTransformOperation 变换操作
├── property_animatable.h             # PropertyAnimatable 属性可动画化
├── property_animatable_helper.h      # PropertyAnimatableHelper 属性动画助手
│
├── 调度系统
├── scheduler.h/cpp                   # Scheduler 动画调度器
├── schedule_task.h                   # ScheduleTask 调度任务
│
├── 状态监听
├── status_listener.h                 # StatusListener 状态监听器
├── time_event.h                      # TimeEvent 时间事件
├── flush_event.h                     # FlushEvent 刷新事件
│
├── 动画编排
├── animator_group.h/cpp              # AnimatorGroup 动画组
├── chain_animation.h/cpp             # ChainAnimation 动画链
│
├── 过渡效果
├── shared_transition.h               # SharedTransition 共享过渡
├── shared_transition_controller.h/cpp # SharedTransitionController 共享过渡控制器
├── shared_transition_effect.h/cpp    # SharedTransitionEffect 共享过渡效果
├── card_transition_controller.h/cpp  # CardTransitionController 卡片过渡控制器
├── page_transition_common.h          # PageTransitionCommon 页面过渡通用
├── page_transition_listener.h        # PageTransitionListener 页面过渡监听器
│
├── SVG 动画
├── svg_animate.h/cpp                 # SvgAnimate SVG 动画
├── picture_animation.h               # PictureAnimation 图片动画
│
├── 其余工具
├── animation_util.h/cpp              # AnimationUtil 动画工具
├── native_curve_helper.h/cpp         # NativeCurveHelper 原生曲线助手
├── param_transfer.h                  # ParamTransfer 参数传递
├── animator_info.h                   # AnimatorInfo 动画信息
│
├── 测试
└── test/                             # 单元测试目录
```

### 关键文件说明

| 文件 | 职责 | 核心类/方法 |
|-----|------|-----------|
| **animator.h/cpp** | 动画控制器，管理动画生命周期 | `Animator::Play()`, `OnFrame()` |
| **animation.h** | 模板动画基类 | `Animation<T>::GetValue()` |
| **curve_animation.h** | 曲线动画实现 | `CurveAnimation::Calculate()` |
| **keyframe_animation.h** | 关键帧动画实现 | `KeyframeAnimation::AddKeyframe()` |
| **spring_animation.h/cpp** | 弹簧动画实现 | `SpringAnimation::UpdatePosition()` |
| **property_animation.h/cpp** | 属性动画实现 | `PropertyAnimation::OnNormalizedTimestampChanged()` |
| **scheduler.h/cpp** | 动画调度器 | `Scheduler::StartFrame()` |
| **spring_model.h/cpp** | 弹簧物理模型 | `SpringModel::GetPosition()` |
| **svg_animate.h/cpp** | SVG 动画支持 | `SvgAnimate::SetAttribute()` |

---

## 核心类继承关系

### 1. Animator 继承关系

```
AceType (基类)
    ↓
StatusListenable (状态监听接口)
    ↓
Animator (动画控制器)
    ├─ 管理多个 Interpolator
    ├─ 管理 Motion 动画
    ├─ 连接 Scheduler
    └─ 控制动画生命周期
```

### 2. Animation 层继承关系

```
AceType (基类)
    ↓
Interpolator (插值器接口)
    ↓
├─ Animation<T> (模板动画基类)
│   ├─ CurveAnimation<T> (曲线动画)
│   ├─ KeyframeAnimation<T> (关键帧动画)
│   ├─ SpringAnimation (弹簧动画)
│   └─ PropertyAnimation (属性动画)
│
└─ ValueListenable<T> (值监听接口)
```

### 3. Curve 继承关系

```
Curve (曲线抽象接口)
    ↓
├─ CubicCurve (三次贝塞尔曲线)
├─ SpringCurve (弹簧曲线)
├─ AnticipateCurve (预期曲线)
└─ Curves (预设曲线集合)
    ├─ LINEAR
    ├─ EASE
    ├─ EASE_IN
    ├─ EASE_OUT
    ├─ EASE_IN_OUT
    └─ ...
```

### 4. Motion 继承关系

```
TimeEvent (时间事件接口)
    ↓
ValueListenable<double> (值监听接口)
    ↓
Motion (运动抽象基类)
    ↓
├─ SpringMotion (弹簧运动)
├─ ScrollMotion (滚动运动)
├─ FrictionMotion (摩擦力运动)
└─ VelocityMotion (速度运动)
```

### 5. SpringModel 继承关系

```
AceType (基类)
    ↓
SpringModel (弹簧模型抽象类)
    ↓
├─ CriticalDampedSpring (临界阻尼弹簧)
├─ OverdampedSpring (过阻尼弹簧)
└─ UnderdampedSpring (欠阻尼弹簧)
```

---

## Animator 详解

### Animator 核心职责

**Animator** 是 Animation 模块的**核心控制器**，负责：

1. **动画生命周期管理**
   - 启动、停止、暂停、恢复、取消
   - 方向控制（正向、反向、自动反转）
   - 重复控制（迭代次数）

2. **时间管理**
   - 持续时间控制（Duration）
   - 启动延迟（StartDelay）
   - 速度控制（Tempo）
   - 全局动画缩放（DurationScale）

3. **插值器管理**
   - 添加/移除 Interpolator
   - 代理控制器管理（ProxyController）

4. **调度集成**
   - 连接 Scheduler
   - 接收 VSync 回调
   - 触发帧更新

### 关键类定义

**文件**：`animator.h:42-289`

```cpp
class ACE_FORCE_EXPORT Animator : public AceType, public StatusListenable {
    DECLARE_ACE_TYPE(Animator, AceType);

public:
    enum class Status {
        IDLE,    // 未启动或已取消
        RUNNING, // 正在运行
        PAUSED,  // 已暂停
        STOPPED  // 已停止
    };

    // 构造函数
    Animator(const WeakPtr<PipelineBase>& context, const char* name = nullptr);
    Animator(const char* name = nullptr);

    // === 插值器管理 ===
    void AddInterpolator(const RefPtr<Interpolator>& animation);
    void RemoveInterpolator(const RefPtr<Interpolator>& animation);
    void ClearInterpolators();

    // === 代理控制器管理 ===
    void AddProxyController(const RefPtr<Animator>& proxy);
    void RemoveProxyController(const RefPtr<Animator>& proxy);
    void ClearProxyControllers();

    // === 状态查询 ===
    Status GetStatus() const;
    bool IsStopped() const;
    bool IsRunning() const;
    bool IsPending() const;

    // === 时间控制 ===
    void SetDuration(int32_t duration);      // 设置持续时间（毫秒）
    int32_t GetDuration() const;
    void SetStartDelay(int32_t startDelay);  // 设置启动延迟（毫秒）
    bool SetIteration(int32_t iteration);    // 设置迭代次数

    // === 填充模式 ===
    void SetFillMode(FillMode fillMode);     // FORWARDS / BACKWARDS / BOTH
    FillMode GetFillMode() const;

    // === 方向控制 ===
    void SetAnimationDirection(AnimationDirection direction); // NORMAL / ALTERNATE
    void Play();      // 基于当前方向播放
    void Reverse();   // 反转方向并播放
    void Forward();   // 正向播放
    void Backward();  // 反向播放

    // === 播放控制 ===
    void Pause();     // 暂停（可恢复）
    void Resume();    // 恢复
    void Stop();      // 停止在当前帧（不可恢复）
    void Finish();    // 停止在结束帧
    void Cancel();    // 停止在开始帧

    // === Motion 动画 ===
    void PlayMotion(const RefPtr<Motion>& motion);

    // === 速度控制 ===
    void SetTempo(float tempo);               // 设置播放速度
    static void SetDurationScale(float scale); // 设置全局动画缩放

    // === 帧控制 ===
    void UpdatePlayedTime(int32_t playedTime, bool checkReverse = false);
    void TriggerFrame(int32_t playedTime, bool checkReverse = false);

private:
    // VSync 回调
    void OnFrame(int64_t duration);
    void NotifyInterpolator(int32_t playedTime);
    void NotifyMotion(int32_t playedTime);

    // 内部状态
    std::list<RefPtr<Interpolator>> interpolators_;
    std::list<RefPtr<Animator>> proxyControllers_;
    RefPtr<Scheduler> scheduler_;
    RefPtr<Motion> motion_;
    FillMode fillMode_ = FillMode::FORWARDS;
    AnimationDirection direction_ = AnimationDirection::NORMAL;
    int32_t duration_ = 0;        // 持续时间（毫秒）
    int64_t elapsedTime_ = 0;     // 已播放时间（毫秒）
    int32_t startDelay_ = 0;      // 启动延迟（毫秒）
    int32_t repeatTimes_ = 0;     // 用户配置的重复次数
    int32_t iteration_ = 1;       // 用户配置的迭代次数
    int32_t repeatTimesLeft_ = 0; // 剩余重复次数
    float tempo_ = 1.0f;          // 播放速度
    bool isReverse_ = false;       // 是否反向
    Status status_ = Status::IDLE;
    static float scale_;           // 全局动画缩放
};
```

### 关键生命周期方法

#### 1. Play()

**调用时机**：启动动画或继续播放

**源码位置**：`animator.cpp`

**执行流程**：
```cpp
void Animator::Play()
{
    // 1. 检查是否已停止
    if (status_ == Status::STOPPED) {
        // 已停止的动画需要重置
        elapsedTime_ = 0;
        repeatTimesLeft_ = repeatTimes_;
    }

    // 2. 设置方向
    if (!isReverse_) {
        isCurDirection_ = false; // 正向
    } else {
        isCurDirection_ = true;  // 反向
    }

    // 3. 启动动画
    StartInner(true);
}
```

**注意事项**：
- ⚠️ **已停止的动画**会重置 elapsedTime_ 和 repeatTimesLeft_
- ✅ **暂停的动画**会从暂停处继续播放
- ✅ **支持方向控制**（正向/反向）

#### 2. OnFrame()

**调用时机**：每个 VSync 信号触发

**源码位置**：`animator.cpp`

**执行流程**：
```cpp
void Animator::OnFrame(int64_t duration)
{
    // 1. 更新已播放时间
    elapsedTime_ += duration;

    // 2. 检查启动延迟
    if (elapsedTime_ < startDelay_) {
        return; // 仍在延迟期内
    }

    // 3. 计算实际播放时间
    int32_t playedTime = elapsedTime_ - startDelay_;

    // 4. 应用 Tempo 和全局缩放
    playedTime = playedTime * tempo_ * scale_;

    // 5. 处理重复和方向
    int32_t playedLoops = 0;
    int32_t remaining = 0;
    GetPlayedLoopsAndRemaining(playedTime, playedLoops, remaining);

    // 6. 检查是否完成
    if (UpdateRepeatTimesLeftAndCheckFinished(playedLoops)) {
        status_ = Status::STOPPED;
        NotifyStopListener();
        return;
    }

    // 7. 通知 Interpolator 或 Motion
    if (motion_) {
        NotifyMotion(remaining);
    } else {
        NotifyInterpolator(remaining);
    }
}
```

**注意事项**：
- ⚠️ **启动延迟**期间不触发动画
- ⚠️ **Tempo 和 Scale** 会影响实际播放速度
- ✅ **自动处理重复和方向切换**

#### 3. NotifyInterpolator()

**调用时机**：OnFrame 中通知插值器更新

**源码位置**：`animator.cpp`

**执行流程**：
```cpp
void Animator::NotifyInterpolator(int32_t playedTime)
{
    // 1. 计算归一化时间 [0.0, 1.0]
    float normalizedTime = GetNormalizedTime(playedTime, false);

    // 2. 处理方向
    bool needReverse = isReverse_ ^ isOddRound_;

    // 3. 通知所有 Interpolator
    for (const auto& interpolator : interpolators_) {
        if (interpolator) {
            interpolator->OnNormalizedTimestampChanged(normalizedTime, needReverse);
        }
    }

    // 4. 触发代理控制器
    for (const auto& proxy : proxyControllers_) {
        if (proxy) {
            proxy->TriggerFrame(playedTime, needReverse);
        }
    }
}
```

**注意事项**：
- ✅ **归一化时间**范围 [0.0, 1.0]
- ✅ **自动处理反向播放**
- ✅ **支持代理控制器联动**

### 状态转换图

```
    IDLE
      ↓
    [Play / Forward / Backward]
      ↓
   RUNNING
      ↓
    [Pause]
      ↓
   PAUSED
      ↓
    [Resume]
      ↓
   RUNNING
      ↓
    [Stop / Finish / Cancel]
      ↓
  STOPPED
```

**状态说明**：
- **IDLE**：初始状态，动画未启动
- **RUNNING**：正在播放
- **PAUSED**：已暂停，可恢复
- **STOPPED**：已停止，不可恢复（除非重新创建）

---

## Animation 层详解

### Animation<T> 模板基类

**文件**：`animation.h:26-58`

**功能**：提供类型安全的动画值管理

```cpp
template<typename T>
class ACE_FORCE_EXPORT Animation : public Interpolator, public ValueListenable<T> {
    DECLARE_ACE_TYPE(Animation, Interpolator);

public:
    virtual const T& GetValue() const = 0;

    void OnInitNotify(float normalizedTime, bool reverse) override
    {
        // 如果用户设置了初始值，动画保持在初始值
        if (inited_) {
            ValueListenable<T>::NotifyListener(initValue_);
        } else {
            OnNormalizedTimestampChanged(normalizedTime, reverse);
        }
    }

    void SetInitValue(const T& initValue)
    {
        initValue_ = initValue;
        inited_ = true;
    }

    bool HasInitValue() const
    {
        return inited_;
    }

    virtual void SetCurve(const RefPtr<Curve>& curve) {}

private:
    T initValue_ {};
    bool inited_ = false;
};
```

**支持的类型 T**：
- `float`：浮点数（位置、缩放、透明度等）
- `Color`：颜色
- `Dimension`：尺寸
- `Offset`：偏移
- `Size`：大小

### CurveAnimation<T> 详解

**文件**：`curve_animation.h:27-134`

**功能**：基于曲线的插值动画

**类定义**：
```cpp
template<typename T>
class ACE_FORCE_EXPORT CurveAnimation : public Animation<T> {
public:
    CurveAnimation(const T& begin, const T& end, const RefPtr<Curve>& curve)
        : begin_(begin), end_(end), currentValue_(begin)
    {
        if (curve) {
            curve_ = curve;
        } else {
            curve_ = Curves::EASE; // 默认使用 EASE 曲线
        }
        reverseCurve_ = curve_;
    }

    const T& GetValue() const override
    {
        return currentValue_;
    }

    void SetCurve(const RefPtr<Curve>& curve) override
    {
        curve_ = curve;
        reverseCurve_ = curve;
    }

    void SetReverseCurve(const RefPtr<Curve>& reverseCurve)
    {
        reverseCurve_ = reverseCurve;
    }

    void SetEvaluator(const RefPtr<Evaluator<T>>& evaluator)
    {
        if (evaluator) {
            isSupportedRunningAsync_ = false;
            evaluator_ = evaluator;
        }
    }

private:
    void Calculate(float time, const RefPtr<Curve>& curve)
    {
        if (NearZero(time)) {
            currentValue_ = begin_;
            return;
        }
        if (NearEqual(time, 1.0)) {
            currentValue_ = end_;
            return;
        }
        // 使用 Evaluator 计算中间值
        currentValue_ = evaluator_->Evaluate(begin_, end_, curve->Move(time));
    }

    void OnNormalizedTimestampChanged(float normalized, bool reverse) override
    {
        Calculate(normalized, reverse ? reverseCurve_ : curve_);
        ValueListenable<T>::NotifyListener(currentValue_);
    }

    T begin_;
    T end_;
    T currentValue_;
    RefPtr<Curve> curve_;
    RefPtr<Curve> reverseCurve_;
    RefPtr<Evaluator<T>> evaluator_ = AceType::MakeRefPtr<LinearEvaluator<T>>();
};
```

**关键特性**：
- ✅ **类型安全**：模板设计，支持任意可插值类型
- ✅ **独立反向曲线**：可以设置不同的反向曲线
- ✅ **自定义 Evaluator**：支持自定义插值算法
- ⚠️ **异步限制**：使用非线性 Evaluator 时不支持异步运行

**使用示例**：
```cpp
// 创建从 0.0 到 1.0 的淡入动画
auto curve = Curves::EASE_IN;
auto fadeAnimation = AceType::MakeRefPtr<CurveAnimation<float>>(0.0f, 1.0f, curve);

// 添加监听器
fadeAnimation->AddListener([](float opacity) {
    // 更新透明度
    SetOpacity(opacity);
});

// 添加到 Animator
animator->AddInterpolator(fadeAnimation);
animator->Play();
```

### KeyframeAnimation<T> 详解

**文件**：`keyframe_animation.h:31-195`

**功能**：关键帧动画，支持多个关键点和不同曲线

**类定义**：
```cpp
template<typename T>
class KeyframeAnimation : public Animation<T> {
public:
    // 添加关键帧
    void AddKeyframe(const RefPtr<Keyframe<T>>& keyframe)
    {
        if (!keyframe || !keyframe->IsValid()) {
            return;
        }
        keyframes_.emplace_back(keyframe);
        ++keyframeNum_;
    }

    void AddKeyframe(const std::list<RefPtr<Keyframe<T>>>& keyframes)
    {
        for (const auto& keyframe : keyframes) {
            AddKeyframe(keyframe);
        }
        // 按时间排序
        keyframes_.sort([](const RefPtr<Keyframe<T>>& a, const RefPtr<Keyframe<T>>& b) {
            return a->GetKeyTime() < b->GetKeyTime();
        });
    }

    // 替换关键帧
    void ReplaceKeyframe(const RefPtr<Keyframe<T>>& keyframeReplace)
    {
        for (auto& keyframe : keyframes_) {
            if (NearEqual(keyframe->GetKeyTime(), keyframeReplace->GetKeyTime())) {
                keyframe = keyframeReplace;
            }
        }
    }

    const T& GetValue() const override
    {
        return currentValue_;
    }

private:
    void Calculate(float keyTime)
    {
        if (keyframes_.empty()) {
            return;
        }

        auto begin = keyframes_.front()->GetKeyValue();
        auto end = keyframes_.back()->GetKeyValue();

        // keyTime < 0: 保持初始状态
        if (keyTime < 0.0f) {
            currentValue_ = begin;
            return;
        }

        // keyTime > 1.0 或只有一个关键帧: 保持最终状态
        if (keyTime > 1.0f || keyframeNum_ == 1) {
            currentValue_ = end;
            return;
        }

        // 在关键帧之间插值
        auto preKeyframe = keyframes_.front();
        for (const auto& keyframe : keyframes_) {
            if (keyTime < keyframe->GetKeyTime()) {
                float preKeyTime = preKeyframe->GetKeyTime();
                if (NearEqual(keyframe->GetKeyTime(), preKeyTime)) {
                    return;
                }

                // 计算区间内的归一化时间
                float intervalKeyTime = (keyTime - preKeyTime) / (keyframe->GetKeyTime() - preKeyTime);

                auto& curve = keyframe->GetCurve();
                begin = preKeyframe->GetKeyValue();
                end = keyframe->GetKeyValue();

                if (curve) {
                    currentValue_ = evaluator_->Evaluate(begin, end, curve->Move(intervalKeyTime));
                } else {
                    currentValue_ = evaluator_->Evaluate(begin, end, Curves::EASE->Move(intervalKeyTime));
                }
                return;
            }
            preKeyframe = keyframe;
        }

        currentValue_ = end;
    }

    void OnNormalizedTimestampChanged(float normalized, bool reverse) override
    {
        Calculate(normalized);
        ValueListenable<T>::NotifyListener(currentValue_);
    }

    T currentValue_ {};
    int32_t keyframeNum_ = 0;
    std::list<RefPtr<Keyframe<T>>> keyframes_;
    RefPtr<Evaluator<T>> evaluator_ = AceType::MakeRefPtr<LinearEvaluator<T>>();
};
```

**关键特性**：
- ✅ **多关键点支持**：可以添加任意数量的关键帧
- ✅ **独立曲线**：每个关键帧可以有独立的曲线
- ✅ **自动排序**：按时间自动排序关键帧
- ✅ **区间插值**：在相邻关键帧之间插值

**使用示例**：
```cpp
// 创建关键帧动画
auto keyframeAnimation = AceType::MakeRefPtr<KeyframeAnimation<float>>();

// 添加关键帧
auto keyframe1 = AceType::MakeRefPtr<Keyframe<float>>(0.0f, 0.0f);  // t=0, value=0
auto keyframe2 = AceType::MakeRefPtr<Keyframe<float>>(0.5f, 0.5f);  // t=0.5, value=0.5
keyframe2->SetCurve(Curves::EASE_IN); // 设置区间曲线

auto keyframe3 = AceType::MakeRefPtr<Keyframe<float>>(1.0f, 1.0f);  // t=1, value=1
keyframe3->SetCurve(Curves::EASE_OUT);

keyframeAnimation->AddKeyframe({keyframe1, keyframe2, keyframe3});

// 添加到 Animator
animator->AddInterpolator(keyframeAnimation);
```

### SpringAnimation 详解

**文件**：`spring_animation.h:26-68`

**功能**：弹簧动画，基于物理模拟的弹性效果

**类定义**：
```cpp
class SpringAnimation : public Animation<float> {
    DECLARE_ACE_TYPE(SpringAnimation, Animation);

public:
    explicit SpringAnimation(const RefPtr<SpringProperty>& property);
    SpringAnimation(const RefPtr<SpringProperty>& property, float velocity);
    SpringAnimation(const RefPtr<SpringProperty>& property, float velocity, float valueThreshold);

    const float& GetValue() const override
    {
        return currentPosition_;
    }

private:
    void SetEndPosition(float endPosition, float startVelocity);

    void UpdatePosition(float normalized)
    {
        // 使用 SpringModel 计算当前位置
        currentPosition_ = solution_->GetPosition(normalized * estimateDuration_);
        currentVelocity_ = solution_->GetVelocity(normalized * estimateDuration_);
    }

    void InitEstimateDuration();

    void OnNormalizedTimestampChanged(float normalized, bool reverse) override
    {
        UpdatePosition(normalized);
        NotifyListener(currentPosition_);
    }

    RefPtr<Curve> GetCurve() override;

    float estimateDuration_ = 1.0f;        // 预估持续时间
    float currentPosition_ = 0.0f;          // 当前位置
    float currentVelocity_ = 0.0f;          // 当前速度
    float valueThreshold_ = 0.001f;         // 值阈值
    float velocityThreshold_ = 0.001f;      // 速度阈值
    float startPosition_ = 0.0f;
    float endPosition_ = 0.0f;
    RefPtr<SpringProperty> property_;       // 质量、刚度、阻尼
    RefPtr<SpringModel> solution_;          // 弹簧模型（临界/过/欠阻尼）
};
```

**SpringProperty 参数**：
- **Mass**：质量（默认 1.0），影响惯性
- **Stiffness**：刚度（默认 100.0），影响弹性强度
- **Damping**：阻尼（默认 15.0），影响衰减速度

**关键特性**：
- ✅ **物理真实感**：基于物理模拟的弹性效果
- ✅ **自动停止**：检测值和速度阈值自动停止
- ✅ **三种阻尼模式**：
  - **欠阻尼（Underdamped）**：振荡衰减
  - **临界阻尼（CriticalDamped）**：快速收敛
  - **过阻尼（Overdamped）**：缓慢收敛

**使用示例**：
```cpp
// 创建弹簧属性（质量、刚度、阻尼）
auto springProperty = AceType::MakeRefPtr<SpringProperty>(1.0f, 100.0f, 15.0f);

// 创建弹簧动画
auto springAnimation = AceType::MakeRefPtr<SpringAnimation>(springProperty);
springAnimation->AddListener([](float value) {
    // 更新位置
    SetPosition(value);
});

// 使用 Motion 方式播放
animator->PlayMotion(springAnimation);
```

### PropertyAnimation 详解

**文件**：`property_animation.h:28-72`

**功能**：属性动画，用于 Animatable 属性的动画

**类定义**：
```cpp
class PropertyAnimation : public Interpolator {
    DECLARE_ACE_TYPE(PropertyAnimation, Interpolator);

public:
    using PropCallback = std::function<void(const RefPtr<Animatable>&)>;

    explicit PropertyAnimation(AnimatableType type);

    void SetStart(const RefPtr<Animatable>& animatable);
    void AddAnimatable(const RefPtr<Animatable>& animatable);

    void SetCurve(const RefPtr<Curve>& curve);

    void AddListener(const PropCallback& callback)
    {
        animateTo_ = callback;
    }

private:
    void OnNormalizedTimestampChanged(float normalized, bool reverse) override;
    void OnInitNotify(float normalizedTime, bool reverse) override;

    RefPtr<Curve> GetCurve() override;
    void Calculate(float keyTime);
    void TriggerFrame(const RefPtr<Animatable>& start, const RefPtr<Animatable>& end, float time);

    AnimatableType type_;
    std::list<RefPtr<Animatable>> animatables_;
    PropCallback animateTo_ = nullptr;
    RefPtr<Animatable> init_;
};
```

**支持的 AnimatableType**：
- `POSITION`：位置
- `SIZE`：尺寸
- `COLOR`：颜色
- `OPACITY`：透明度
- `TRANSFORM`：变换

---

## 曲线系统

### Curve 抽象接口

**文件**：`curve.h` (引用 `ui/animation/curve.h`)

**核心方法**：
```cpp
class Curve {
public:
    // 移动到指定时间点的值（归一化时间 [0.0, 1.0]）
    virtual float Move(float time) = 0;

    // 克隆曲线
    virtual RefPtr<Curve> Clone() const = 0;
};
```

### CubicCurve 三次贝塞尔曲线

**文件**：`cubic_curve.h/cpp`

**功能**：三次贝塞尔曲线插值

**类定义**：
```cpp
class CubicCurve : public Curve {
public:
    CubicCurve(float x1, float y1, float x2, float y2)
        : x1_(x1), y1_(y1), x2_(x2), y2_(y2) {}

    float Move(float time) override
    {
        // 三次贝塞尔曲线计算
        return CalculateBezier(time, x1_, y1_, x2_, y2_);
    }

private:
    float x1_, y1_; // 第一个控制点
    float x2_, y2_; // 第二个控制点
};
```

**常用预设**：
- **Ease**：`(0.25, 0.1, 0.25, 1.0)` - 慢-快-慢
- **EaseIn**：`(0.42, 0.0, 1.0, 1.0)` - 慢-快
- **EaseOut**：`(0.0, 0.0, 0.58, 1.0)` - 快-慢
- **EaseInOut**：`(0.42, 0.0, 0.58, 1.0)` - 慢-快-慢（更平滑）

### SpringCurve 弹簧曲线

**文件**：`spring_curve.h/cpp`

**功能**：弹簧响应曲线

**参数**：
- **response**：响应速度（默认 0.6）
- **dampingRatio**：阻尼比（默认 0.5）
- **initialVelocity**：初始速度（默认 0.0）

### Curves 预设曲线集合

**文件**：`curves.h` (引用 `ui/animation/curves.h`)

**常用曲线**：
```cpp
class Curves {
public:
    static const RefPtr<Curve> LINEAR;        // 线性
    static const RefPtr<Curve> EASE;          // 缓动
    static const RefPtr<Curve> EASE_IN;       // 缓入
    static const RefPtr<Curve> EASE_OUT;      // 缓出
    static const RefPtr<Curve> EASE_IN_OUT;   // 缓入缓出
    static const RefPtr<Curve> FAST_OUT_SLOW_IN;  // 快出慢入
    static const RefPtr<Curve> LINEAR_OUT_SLOW_IN; // 线出慢入
    static const RefPtr<Curve> FRICTION;      // 摩擦力曲线
    static const RefPtr<Curve> EXTREME_DECELERATION; // 极速减速
    static const RefPtr<Curve> EXTREME_ACCELERATION; // 极速加速
    static const RefPtr<Curve> SHARP;         // 锐利曲线
};
```

**完整预设曲线列表**（20+种）：

#### 基础曲线

| 曲线 | 控制点 (x1, y1, x2, y2) | 效果描述 |
|-----|---------------------|---------|
| **LINEAR** | (0.0, 0.0, 1.0, 1.0) | 线性匀速 |
| **DECELE** | 减速曲线类 | 持续减速 |
| **SINE** | 正弦曲线类 | 正弦波变化 |

#### 三次贝塞尔曲线

| 曲线 | 控制点 (x1, y1, x2, y2) | 效果描述 | 应用场景 |
|-----|---------------------|---------|---------|
| **EASE** | (0.25, 0.1, 0.25, 1.0) | 慢-快-慢 | 通用过渡 |
| **EASE_IN** | (0.42, 0.0, 1.0, 1.0) | 慢-快 | 进入场景 |
| **EASE_OUT** | (0.0, 0.0, 0.58, 1.0) | 快-慢 | 离开场景 |
| **EASE_IN_OUT** | (0.42, 0.0, 0.58, 1.0) | 慢-快-慢（平滑） | 通用过渡 |
| **FAST_OUT_SLOW_IN** | (0.4, 0.0, 0.2, 1.0) | 快出慢入 | 快速弹出 |
| **LINEAR_OUT_SLOW_IN** | (0.0, 0.0, 0.2, 1.0) | 线出慢入 | 平滑进入 |
| **FAST_OUT_LINEAR_IN** | (0.4, 0.0, 1.0, 1.0) | 快出线入 | 快速过渡 |
| **FRICTION** | (0.2, 0.0, 0.2, 1.0) | 摩擦力效果 | 滚动场景 |
| **EXTREME_DECELERATION** | (0.0, 0.0, 0.0, 1.0) | 极速减速 | 紧急停止 |
| **SHARP** | (0.33, 0.0, 0.67, 1.0) | 锐利变化 | 强调变化 |
| **RHYTHM** | (0.7, 0.0, 0.2, 1.0) | 节奏感 | 律动动画 |
| **SMOOTH** | (0.4, 0.0, 0.4, 1.0) | 平滑过渡 | 柔和动画 |

#### 特殊效果曲线

| 曲线 | 类型 | 参数 | 效果描述 | 应用场景 |
|-----|------|------|---------|---------|
| **ANTICIPATE** | AnticipateCurve | tension = 2.0 | 先回退再前进 | 按压效果 |
| **MAGNETIC** | CubicCurve | (0.8, 0.0, 1.0, 0.6) | 磁吸效果 | 吸附动画 |
| **ELASTICS** | ElasticsCurve | tension = 2.0 | 弹性效果 | 弹性按钮 |

### 三次贝塞尔曲线算法详解

**文件**：`cubic_curve.cpp:29-89`

**核心算法**：使用**二分查找法**求解三次贝塞尔方程

**三次贝塞尔曲线公式**：

```
B(t) = (1 - t)³ * P0 + 3 * (1 - t)² * t * P1 + 3 * (1 - t) * t² * P2 + t³ * P3
```

简化后（P0 = (0,0), P3 = (1,1)）：

```
y = CalculateCubic(x1, y1, x2, y2, x)
```

其中：
```
CalculateCubic(a, b, m) = 3*a*(1-m)²*m + 3*b*(1-m)*m² + m³
```

**求解过程**：

1. **给定时间 t**，求解曲线上的 x 坐标
2. **使用二分查找**反解出对应的 t 值
3. **代入 t 值**计算 y 坐标

**误差控制**：
```cpp
constexpr float cubicErrorBound_ = 0.001f;  // 允许误差
```

**反向曲线实现**：

通过交换控制点实现反向播放：

```cpp
void SetReverseCurve(const RefPtr<Curve>& reverseCurve)
{
    reverseCurve_ = reverseCurve;
}

// 在反向播放时使用反向曲线
Calculate(normalized, reverse ? reverseCurve_ : curve_);
```

### 创建自定义曲线

#### 方法 1：使用三次贝塞尔曲线

```cpp
// 创建自定义三次贝塞尔曲线
auto customCurve = AceType::MakeRefPtr<CubicCurve>(x1, y1, x2, y2);

// 示例：自定义快速进入曲线
auto fastInCurve = AceType::MakeRefPtr<CubicCurve>(0.6f, 0.0f, 0.8f, 0.2f);

// 使用自定义曲线
auto animation = AceType::MakeRefPtr<CurveAnimation<float>>(0.0f, 100.0f, fastInCurve);
```

#### 方法 2：使用 AnticipateCurve（预期曲线）

```cpp
// 创建预期曲线（先回退再前进）
auto anticipateCurve = AceType::MakeRefPtr<AnticipateCurve>(tension);

// tension 参数：
// - 1.0: 标准预期
// - 2.0: 强预期（回退更多）
// - >2.0: 超强预期

// 示例
auto strongAnticipate = AceType::MakeRefPtr<AnticipateCurve>(3.0f);
```

**AnticipateCurve 效果图**：
```
值
 ↑
1 |      ╱╲
  |     ╱  ╲
  |    ╱    ╲
  |   ╱      ╲___
0 |__╱          ╲___
  +------------------→ 时间
   回退   前进
```

#### 方法 3：使用 ElasticsCurve（弹性曲线）

```cpp
// 创建弹性曲线
auto elasticsCurve = AceType::MakeRefPtr<ElasticsCurve>(tension);

// tension 参数：
// - 1.0: 轻微弹性
// - 2.0: 标准弹性
// - >2.0: 强弹性

// 示例
auto bouncyCurve = AceType::MakeRefPtr<ElasticsCurve>(2.5f);
```

**ElasticsCurve 效果图**：
```
值
 ↑
1 |╲      ╱╲      ╱
  | ╲    ╱  ╲    ╱
  |  ╲  ╱    ╲  ╱
  |   ╲╱      ╲╱
0 |____╲________╲___
  +------------------→ 时间
  振荡衰减
```

### 曲线选择指南

| 场景 | 推荐曲线 | 理由 |
|-----|---------|------|
| **UI 元素进入** | EASE_OUT 或 FAST_OUT_SLOW_IN | 快速进入，缓慢停止 |
| **UI 元素离开** | EASE_IN 或 FAST_OUT_LINEAR_IN | 快速离开 |
| **位置过渡** | EASE_IN_OUT | 双向平滑 |
| **尺寸变化** | SMOOTH | 避免突变 |
| **透明度变化** | LINEAR 或 FRICTION | 线性过渡 |
| **滚动回弹** | FRICTION 或 DECELE | 模拟摩擦 |
| **按钮按压** | ANTICIPATE | 先回退再前进 |
| **弹性效果** | ELASTICS | 振荡衰减 |
| **强调变化** | SHARP | 锐利变化 |
| **列表滑动** | RHYTHM | 律动节奏 |
| **快速停止** | EXTREME_DECELERATION | 紧急制动 |

### 曲线性能对比

| 曲线类型 | 计算复杂度 | 性能 | 适用场景 |
|---------|----------|------|---------|
| **LINEAR** | O(1) | ⭐⭐⭐⭐⭐ | 高频更新 |
| **CubicCurve** | O(log n)（二分查找） | ⭐⭐⭐⭐ | 通用场景 |
| **AnticipateCurve** | O(log n) + 预计算 | ⭐⭐⭐ | 按压效果 |
| **ElasticsCurve** | O(log n) + 多次振荡 | ⭐⭐ | 弹性效果 |

**性能优化建议**：
- ✅ **高频动画**使用 LINEAR
- ✅ **预计算常用曲线**（如 EASE）
- ⚠️ **复杂曲线**控制使用频率
- ⚠️ **避免在每一帧**创建新 Curve 对象

---

---

## Evaluator 评估器系统

### Evaluator 抽象接口

**文件**：`evaluator.h:29-46`

**功能**：计算两个值之间的插值

**核心方法**：
```cpp
template<typename T>
class Evaluator {
public:
    virtual T Evaluate(const T& begin, const T& end, float fraction) = 0;
    virtual ~Evaluator() = default;
};
```

**参数说明**：
- `begin`：起始值
- `end`：结束值
- `fraction`：插值分数 [0.0, 1.0]

### LinearEvaluator 线性评估器

**文件**：`evaluator.h:52-59`

**功能**：执行线性插值

**实现**：
```cpp
template<typename T>
class LinearEvaluator : public Evaluator<T> {
public:
    T Evaluate(const T& begin, const T& end, float fraction) override
    {
        return begin + (end - begin) * fraction;
    }
};
```

**数学公式**：
```
Result = begin + (end - begin) × fraction
```

**应用场景**：
- 位置插值
- 尺寸插值
- 透明度插值

### ColorEvaluator 颜色评估器

**文件**：`evaluator.h:68-93`

**功能**：带伽马校正的颜色插值

**核心特性**：
- 使用伽马校正（GAMMA_FACTOR = 2.2）
- 确保颜色过渡自然

**实现原理**：
```cpp
template<>
class LinearEvaluator<Color> : public Evaluator<Color> {
public:
    Color Evaluate(const Color& begin, const Color& end, float fraction) override
    {
        // 1. 转换到线性空间（去除伽马）
        Color beginLinear = ToLinear(begin);
        Color endLinear = ToLinear(end);

        // 2. 在线性空间中插值
        Color resultLinear = beginLinear + (endLinear - beginLinear) * fraction;

        // 3. 转换回sRGB空间（应用伽马）
        return ToGamma(resultLinear);
    }

private:
    static constexpr double GAMMA_FACTOR = 2.2;
};
```

**为什么需要伽马校正？**
- 人眼对暗部变化更敏感
- sRGB 使用伽马编码（≈2.2）
- 直接插值会导致颜色过渡不自然
- 伽马校正确保感知均匀的颜色变化

### BorderStyleEvaluator 边框样式评估器

**文件**：`evaluator.h:99-119`

**功能**：边框样式的二值插值

**实现**：
```cpp
template<>
class LinearEvaluator<BorderStyle> : public Evaluator<BorderStyle> {
public:
    BorderStyle Evaluate(const BorderStyle& begin, const BorderStyle& end, float fraction) override
    {
        // 使用50%阈值进行二值判断
        if (fraction < 0.5f) {
            return begin;
        } else {
            return end;
        }
    }
};
```

**应用场景**：
- 边框样式切换（solid → dashed）
- 需要突变效果而非渐变

### TransformOperationEvaluator 变换操作评估器

**文件**：`evaluator.h:125-140`

**功能**：复杂变换操作的插值

**实现**：
```cpp
template<>
class LinearEvaluator<TransformOperation> : public Evaluator<TransformOperation> {
public:
    TransformOperation Evaluate(const TransformOperation& begin,
                               const TransformOperation& end,
                               float fraction) override
    {
        // 使用Blend方法进行插值
        return begin.Blend(end, fraction);
    }
};
```

**支持的变换类型**：
- 平移（Translate）
- 缩放（Scale）
- 旋转（Rotate）
- 倾斜（Skew）

### 自定义 Evaluator

**如何创建自定义评估器**：

```cpp
template<typename T>
class CustomEvaluator : public Evaluator<T> {
public:
    T Evaluate(const T& begin, const T& end, float fraction) override
    {
        // 自定义插值逻辑

        // 示例1：平方缓动
        // return begin + (end - begin) * (fraction * fraction);

        // 示例2：三次缓动
        // return begin + (end - begin) * (fraction * fraction * fraction);

        // 示例3：平滑步进
        // float smoothFraction = fraction * fraction * (3.0f - 2.0f * fraction);
        // return begin + (end - begin) * smoothFraction;

        return begin + (end - begin) * fraction; // 默认线性
    }
};
```

**使用自定义 Evaluator**：
```cpp
auto customEvaluator = AceType::MakeRefPtr<CustomEvaluator<float>>();

auto animation = AceType::MakeRefPtr<CurveAnimation<float>>(0.0f, 100.0f, Curves::LINEAR);
animation->SetEvaluator(customEvaluator);
```

### Evaluator 与异步动画

**重要限制**：❌ **非线性Evaluator不支持异步动画**

**文件**：`curve_animation.h:67-78`

```cpp
void SetEvaluator(const RefPtr<Evaluator<T>>& evaluator)
{
    if (evaluator) {
        isSupportedRunningAsync_ = false;  // 标记为不支持异步
        evaluator_ = evaluator;
    }
}
```

**原因**：
- 异步动画需要预先计算所有帧
- 非线性Evaluator（如ColorEvaluator）的计算成本高
- 线性Evaluator可以在GPU上并行计算

**实践**：
- 需要异步性能 → 使用LinearEvaluator
- 需要精确插值 → 使用专用Evaluator（同步）

---

## Animatable 属性系统

### AnimatableType 枚举

**文件**：`animatable.h:27-66`

**功能**：定义所有可动画属性的类型

**完整列表**（40+种属性）：

```cpp
enum class AnimatableType {
    // === 基础属性 ===
    PROPERTY_WIDTH,           // 宽度
    PROPERTY_HEIGHT,          // 高度
    PROPERTY_BG_COLOR,        // 背景颜色
    PROPERTY_OPACITY,         // 透明度

    // === 边距属性 ===
    PROPERTY_MARGIN_LEFT,     // 左边距
    PROPERTY_MARGIN_TOP,      // 上边距
    PROPERTY_MARGIN_RIGHT,    // 右边距
    PROPERTY_MARGIN_BOTTOM,   // 下边距

    // === 内边距属性 ===
    PROPERTY_PADDING_LEFT,    // 左内边距
    PROPERTY_PADDING_TOP,     // 上内边距
    PROPERTY_PADDING_RIGHT,   // 右内边距
    PROPERTY_PADDING_BOTTOM,  // 下内边距

    // === 背景属性 ===
    PROPERTY_BACKGROUND_POSITION, // 背景位置
    PROPERTY_BACKGROUND_SIZE,      // 背景大小

    // === 边框属性 ===
    PROPERTY_BORDER_LEFT_WIDTH,    // 左边框宽度
    PROPERTY_BORDER_TOP_WIDTH,     // 上边框宽度
    PROPERTY_BORDER_RIGHT_WIDTH,   // 右边框宽度
    PROPERTY_BORDER_BOTTOM_WIDTH,  // 下边框宽度
    PROPERTY_BORDER_LEFT_COLOR,     // 左边框颜色
    PROPERTY_BORDER_TOP_COLOR,      // 上边框颜色
    PROPERTY_BORDER_RIGHT_COLOR,    // 右边框颜色
    PROPERTY_BORDER_BOTTOM_COLOR,   // 下边框颜色
    PROPERTY_BORDER_TOP_LEFT_RADIUS,     // 左上角圆角
    PROPERTY_BORDER_TOP_RIGHT_RADIUS,    // 右上角圆角
    PROPERTY_BORDER_BOTTOM_LEFT_RADIUS,  // 左下角圆角
    PROPERTY_BORDER_BOTTOM_RIGHT_RADIUS, // 右下角圆角
    PROPERTY_BORDER_LEFT_STYLE,          // 左边框样式
    PROPERTY_BORDER_RIGHT_STYLE,         // 右边框样式
    PROPERTY_BORDER_TOP_STYLE,           // 上边框样式
    PROPERTY_BORDER_BOTTOM_STYLE,        // 下边框样式

    // === 滤镜属性 ===
    PROPERTY_FILTER_BLUR,           // 模糊滤镜
    PROPERTY_BACKDROP_FILTER_BLUR,   // 背景模糊滤镜
    PROPERTY_WINDOW_FILTER_BLUR,    // 窗口模糊滤镜

    // === 阴影属性 ===
    PROPERTY_BOX_SHADOW,            // 盒子阴影

    // === 位置属性 ===
    PROPERTY_POSITION_LEFT,         // 左位置
    PROPERTY_POSITION_TOP,          // 上位置
    PROPERTY_POSITION_RIGHT,        // 右位置
    PROPERTY_POSITION_BOTTOM,       // 下位置
};
```

### AnimatableProperties 类

**文件**：`animatable_properties.h:32-76`

**功能**：管理组件的可动画属性

**核心方法**：

#### 尺寸属性
```cpp
void SetPropWidth(const Dimension& width);
void SetPropHeight(const Dimension& height);
```

#### 颜色属性
```cpp
void SetPropBgColor(const Color& color);
```

#### 透明度
```cpp
void SetPropOpacity(double opacity);
```

#### 阴影
```cpp
void SetPropShadow(const Shadow& shadow);
```

#### 背景属性
```cpp
void SetPropBackgroundPosition(const BackgroundPosition& position);
void SetPropBackgroundSize(const BackgroundSize& size);
```

#### 边距属性
```cpp
void SetMargin(const Edge& margin);
Edge GetMargin() const;
```

#### 边框属性
```cpp
void SetBorderWidth(const BorderWidth& width);
void SetBorderColor(const BorderColor& color);
void SetBorderStyle(const BorderStyle& style);
void SetBorderRadius(const BorderRadius& radius);
```

#### 滤镜属性
```cpp
void SetBlurRadius(float radius);
void SetBackdropRadius(float radius);
void SetWindowBlurProgress(float progress);
```

#### 位置属性
```cpp
void SetPositionLeft(const Dimension& left);
void SetPositionTop(const Dimension& top);
void SetPositionRight(const Dimension& right);
void SetPositionBottom(const Dimension& bottom);
```

### 如何添加新的可动画属性

**步骤指南**：

#### 1. 在 AnimatableType 枚举中添加新类型

**文件**：`animatable.h:27-66`

```cpp
enum class AnimatableType {
    // ... 现有类型 ...
    PROPERTY_CUSTOM_PROPERTY,  // 新增属性
};
```

#### 2. 在 AnimatableProperties 中添加设置和获取方法

**文件**：`animatable_properties.h:32-76`

```cpp
class AnimatableProperties : public AnimatableBase {
public:
    // 添加新属性的setter
    void SetCustomProperty(const CustomType& value) {
        customProperty_ = value;
        MarkPropertyDirty(AnimatableType::PROPERTY_CUSTOM_PROPERTY);
    }

    // 添加新属性的getter
    CustomType GetCustomProperty() const {
        return customProperty_;
    }

private:
    CustomType customProperty_;
};
```

#### 3. 在 PropertyAnimation 中添加处理逻辑

**文件**：`property_animation.cpp`

```cpp
void PropertyAnimation::Calculate(float keyTime)
{
    // 处理新属性类型
    if (type_ == AnimatableType::PROPERTY_CUSTOM_PROPERTY) {
        Next<CustomType>(start, end, keyTime);
        return;
    }

    // ... 其余属性的处理 ...
}
```

#### 4. 实现对应的 Evaluator

**文件**：`evaluator.h`

```cpp
template<>
class LinearEvaluator<CustomType> : public Evaluator<CustomType> {
public:
    CustomType Evaluate(const CustomType& begin,
                       const CustomType& end,
                       float fraction) override
    {
        // 自定义插值逻辑
        return begin.Blend(end, fraction);
    }
};
```

### AnimatableData 属性数据

**文件**：`animatable_data.h/cpp`

**功能**：存储单个动画属性的数据

**类定义**：
```cpp
class AnimatableData : public Animatable {
    DECLARE_ACE_TYPE(AnimatableData, Animatable);

public:
    AnimatableData(AnimatableType type, const Variant& value);

    AnimatableType GetType() const override;
    const Variant& GetValue() const;
    void SetValue(const Variant& value);

    RefPtr<Evaluator<Variant>> GetEvaluator() const override;

private:
    AnimatableType type_;
    Variant value_;
    RefPtr<Evaluator<Variant>> evaluator_;
};
```

### 使用示例

**示例 1：创建属性动画**

```cpp
// 创建属性动画
auto propertyAnimation = AceType::MakeRefPtr<PropertyAnimation>(AnimatableType::PROPERTY_OPACITY);

// 设置起始值
auto startValue = AceType::MakeRefPtr<AnimatableData>(
    AnimatableType::PROPERTY_OPACITY,
    Variant(0.0)
);
propertyAnimation->SetStart(startValue);

// 添加动画帧
auto endValue = AceType::MakeRefPtr<AnimatableData>(
    AnimatableType::PROPERTY_OPACITY,
    Variant(1.0)
);
propertyAnimation->AddAnimatable(endValue);

// 设置曲线
propertyAnimation->SetCurve(Curves::EASE_IN);

// 添加监听器
propertyAnimation->AddListener([](const RefPtr<Animatable>& animatable) {
    auto data = AceType::DynamicCast<AnimatableData>(animatable);
    if (data) {
        double opacity = data->GetValue().GetDouble();
        SetOpacity(opacity);
    }
});

// 添加到Animator
animator->AddInterpolator(propertyAnimation);
animator->Play();
```

**示例 2：多属性组合动画**

```cpp
// 创建宽度动画
auto widthAnim = AceType::MakeRefPtr<PropertyAnimation>(AnimatableType::PROPERTY_WIDTH);
widthAnim->SetStart(CreateAnimatableData(AnimatableType::PROPERTY_WIDTH, 100.0_vp));
widthAnim->AddAnimatable(CreateAnimatableData(AnimatableType::PROPERTY_WIDTH, 200.0_vp));
widthAnim->SetCurve(Curves::EASE_IN_OUT);

// 创建透明度动画
auto opacityAnim = AceType::MakeRefPtr<PropertyAnimation>(AnimatableType::PROPERTY_OPACITY);
opacityAnim->SetStart(CreateAnimatableData(AnimatableType::PROPERTY_OPACITY, 0.0));
opacityAnim->AddAnimatable(CreateAnimatableData(AnimatableType::PROPERTY_OPACITY, 1.0));
opacityAnim->SetCurve(Curves::EASE_IN);

// 添加到同一个Animator
animator->AddInterpolator(widthAnim);
animator->AddInterpolator(opacityAnim);
animator->Play();
```

---

## 运动系统

### Motion 抽象基类

**文件**：`motion.h:24-46`

**功能**：基于物理的运动动画抽象

**类定义**：
```cpp
class Motion : public TimeEvent, public ValueListenable<double> {
    DECLARE_ACE_TYPE(Motion, TimeEvent);

public:
    virtual double GetCurrentPosition() = 0;
    virtual double GetCurrentVelocity() = 0;
    virtual bool IsCompleted() = 0;

    virtual std::string GetMotionType() const
    {
        return "motion";
    }

    // 每个子类应重写此方法以执行运动
    virtual void Move(float offsetTime) = 0;

    // Motion 没有持续时间，normalizedTime 总是零
    void OnTimestampChanged(float timestamp, float normalizedTime, bool reverse) final
    {
        Move(timestamp);
        NotifyListener(GetCurrentPosition());
    }
};
```

**关键特性**：
- ⚠️ **无固定持续时间**：由物理参数决定何时停止
- ✅ **自动停止检测**：通过 `IsCompleted()` 判断
- ✅ **速度信息**：提供 `GetCurrentVelocity()`

### SpringMotion 弹簧运动

**文件**：`spring_motion.h/cpp`

**功能**：基于胡克定律的弹簧运动

**物理公式**：
```
F = -k * x - c * v
```
其中：
- `F`：力
- `k`：刚度（Stiffness）
- `x`：位移
- `c`：阻尼（Damping）
- `v`：速度

### Spring 物理模型详解

**文件**：`spring_model.h:90-153`

弹簧运动遵循**阻尼谐振动**方程：

```
m * x'' + c * x' + k * x = 0
```

其中：
- `m`：质量（Mass）
- `c`：阻尼系数（Damping）
- `k`：刚度系数（Stiffness）
- `x`：位移
- `x'`：速度（一阶导数）
- `x''`：加速度（二阶导数）

**阻尼比（Damping Ratio, ζ）**：

```
ζ = c / (2 * √(m * k))
```

根据阻尼比的不同，弹簧运动分为三种模式：

#### 1. 临界阻尼（Critical Damped, ζ = 1）

**特点**：快速收敛到平衡位置，不产生振荡

**数学实现**：

**文件**：`spring_model.h:92-107`

```cpp
class CriticalDampedSpring : public SpringModel {
private:
    double r_ = 0.0;      // 阻尼系数
    double c1_ = 0.0;     // 常数1
    double c2_ = 0.0;     // 常数2

    double Position(double time) const override
    {
        return (c1_ + c2_ * time) * exp(-r_ * time);
    }

    double Velocity(double time) const override
    {
        return (c2_ - r_ * (c1_ + c2_ * time)) * exp(-r_ * time);
    }
};
```

**位移公式**：
```
x(t) = (c1 + c2 * t) * e^(-r * t)
```

**速度公式**：
```
v(t) = (c2 - r * (c1 + c2 * t)) * e^(-r * t)
```

**应用场景**：
- UI 元素快速归位
- 滑动回弹效果
- 需要快速收敛的动画

#### 2. 欠阻尼（Underdamped, ζ < 1）

**特点**：产生振荡，振幅逐渐衰减

**数学实现**：

**文件**：`spring_model.h:127-144`

```cpp
class UnderdampedSpring : public SpringModel {
private:
    double w_ = 0.0;      // 角频率
    double r_ = 0.0;      // 阻尼系数
    double c1_ = 0.0;     // 常数1
    double c2_ = 0.0;     // 常数2

    double Position(double time) const override
    {
        return exp(-r_ * time) * (c1_ * cos(w_ * time) + c2_ * sin(w_ * time));
    }

    double Velocity(double time) const override
    {
        return exp(-r_ * time) * (
            (-r_ * c1_ + w_ * c2_) * cos(w_ * time) +
            (-r_ * c2_ - w_ * c1_) * sin(w_ * time)
        );
    }
};
```

**位移公式**：
```
x(t) = e^(-r * t) * (c1 * cos(w * t) + c2 * sin(w * t))
```

**速度公式**：
```
v(t) = e^(-r * t) * ((-r * c1 + w * c2) * cos(w * t) + (-r * c2 - w * c1) * sin(w * t))
```

**其中**：
- `w`：角频率（ω）
- `r`：阻尼系数（r = ζ * ω₀）

**应用场景**：
- 弹性按钮效果
- 物理真实的弹跳动画
- 游戏中的物理效果

#### 3. 过阻尼（Overdamped, ζ > 1）

**特点**：缓慢收敛到平衡位置，不产生振荡

**数学实现**：

**文件**：`spring_model.h:109-125`

```cpp
class OverdampedSpring : public SpringModel {
private:
    double r1_ = 0.0;     // 根1
    double r2_ = 0.0;     // 根2
    double c1_ = 0.0;     // 常数1
    double c2_ = 0.0;     // 常数2

    double Position(double time) const override
    {
        return c1_ * exp(r1_ * time) + c2_ * exp(r2_ * time);
    }

    double Velocity(double time) const override
    {
        return c1_ * r1_ * exp(r1_ * time) + c2_ * r2_ * exp(r2_ * time);
    }
};
```

**位移公式**：
```
x(t) = c1 * e^(r1 * t) + c2 * e^(r2 * t)
```

**速度公式**：
```
v(t) = c1 * r1 * e^(r1 * t) + c2 * r2 * e^(r2 * t)
```

**应用场景**：
- 缓慢、平滑的过渡效果
- 避免振荡的场景
- 需要精确控制的动画

### Spring 参数默认值

**文件**：`spring_model.h:56-68`

```cpp
static constexpr double DEFAULT_STIFFNESS = 228.0;    // 默认刚度
static constexpr double DEFAULT_DAMPING = 30.0;       // 默认阻尼
static constexpr double DEFAULT_MASS = 1.0;          // 默认质量
```

**参数影响**：

| 参数 | 增大 | 减小 | 推荐范围 |
|-----|------|------|---------|
| **Stiffness（刚度）** | 更快速、更有力 | 更慢速、更柔和 | 100-500 |
| **Damping（阻尼）** | 更快停止 | 更多振荡 | 10-50 |
| **Mass（质量）** | 更慢、更重 | 更快、更轻 | 0.5-2.0 |

**实际效果对比**：

```
刚度大 + 阻尼小 → 快速弹跳（过度）
刚度小 + 阻尼大 → 缓慢滑动
刚度大 + 阻尼大 → 快速归位（临界阻尼）
刚度小 + 阻尼小 → 慢速振荡（欠阻尼）
```

### SpringChain 弹簧链

**文件**：`simple_spring_chain.h:25-276`

**功能**：实现多个弹簧节点的链式运动

**核心概念**：

1. **控制节点（Control Node）**：
   - 控制整个弹簧链的运动
   - 其余节点跟随控制节点运动

2. **参数传递**：
   - `stiffnessTransfer_`：刚度传递曲线
   - `dampingTransfer_`：阻尼传递曲线
   - 支持不同节点有不同的物理参数

3. **间隔控制**：
   - `interval_`：节点间的时间间隔
   - `minInterval_`：最小间隔
   - `maxInterval_`：最大间隔

4. **帧延迟**：
   - `frameDelay_`：控制节点间的延迟效果

**使用示例**：

```cpp
// 创建弹簧链属性
auto springChainProperty = AceType::MakeRefPtr<SpringChainProperty>();
springChainProperty->SetControlStiffness(228.0);
springChainProperty->SetControlDamping(30.0);
springChainProperty->SetInterval(20.0_vp);

// 创建弹簧适配器
auto springAdapter = AceType::MakeRefPtr<SimpleSpringAdapter>();

// 创建弹簧链
auto springChain = AceType::MakeRefPtr<SimpleSpringChain>(springAdapter);
springChain->SetProperty(springChainProperty);

// 添加节点
for (int i = 0; i < 10; i++) {
    auto node = AceType::MakeRefPtr<SimpleSpringNode>();
    springChain->AddNode(node);
}

// 设置参数传递（可选）
auto stiffnessTransfer = AceType::MakeRefPtr<CustomStiffnessTransfer>();
springChain->SetStiffnessTransfer(stiffnessTransfer);
```

**应用场景**：
- 列表项的连锁动画
- 波纹效果
- 蛇形运动

### ScrollMotion 滚动运动

**文件**：`scroll_motion.h/cpp`

**功能**：滚动回弹效果

### FrictionMotion 摩擦力运动

**文件**：`friction_motion.h/cpp`

**功能**：带摩擦力的减速运动

---

## 调度系统

### Scheduler 调度器

**文件**：`scheduler.h/cpp`

**功能**：管理所有动画的调度和帧同步

**类定义**：
```cpp
class Scheduler : public AceType {
    DECLARE_ACE_TYPE(Scheduler, AceType);

public:
    // 启动帧回调
    void StartFrame();

    // 添加/移除动画
    void AddAnimator(const RefPtr<Animator>& animator);
    void RemoveAnimator(const RefPtr<Animator>& animator);

    // VSync 回调
    void OnVsync(int64_t timestamp);

private:
    std::list<RefPtr<Animator>> animators_;
    RefPtr<VsyncClient> vsyncClient_;
};
```

**调度流程**：
```
VSync 信号
    ↓
Scheduler::OnVsync()
    ↓
遍历所有 Animator
    ↓
Animator::OnFrame(duration)
    ↓
Interpolator::OnNormalizedTimestampChanged()
Motion::Move()
    ↓
更新属性值
    ↓
触发重绘
```

---

## 动画编排

### AnimatorGroup 动画组

**文件**：`animator_group.h/cpp`

**功能**：同时控制多个动画，实现批量动画管理

**类定义**：
```cpp
class AnimatorGroup : public AceType {
    DECLARE_ACE_TYPE(AnimatorGroup, AceType);

public:
    // 添加动画到组
    void AddAnimator(const RefPtr<Animator>& animator);

    // 移除动画
    void RemoveAnimator(const RefPtr<Animator>& animator);

    // 播放所有动画
    void Play();

    // 停止所有动画
    void Stop();

    // 暂停所有动画
    void Pause();

    // 恢复所有动画
    void Resume();

private:
    std::list<RefPtr<Animator>> animators_;  // 动画列表
    std::set<RefPtr<Animator>> runningAnimators_;  // 正在运行的动画
    Status status_ = Status::STOPPED;
};
```

**状态管理**：
```cpp
enum class Status {
    STOPPED,  // 所有动画已停止
    RUNNING,  // 至少有一个动画正在运行
};
```

**使用场景**：
- **并行动画**：多个属性同时变化
- **协调动画**：多个组件同步动画
- **批量控制**：统一管理多个动画

**使用示例**：
```cpp
// 创建动画组
auto animatorGroup = AceType::MakeRefPtr<AnimatorGroup>();

// 创建第一个动画（透明度）
auto animator1 = CREATE_ANIMATOR(context, "FadeIn");
auto fadeAnim = AceType::MakeRefPtr<CurveAnimation<float>>(0.0f, 1.0f, Curves::EASE_IN);
fadeAnim->AddListener([](float opacity) {
    SetOpacity(opacity);
});
animator1->AddInterpolator(fadeAnim);
animator1->SetDuration(300);

// 创建第二个动画（位移）
auto animator2 = CREATE_ANIMATOR(context, "SlideIn");
auto slideAnim = AceType::MakeRefPtr<CurveAnimation<float>>(-100.0f, 0.0f, Curves::EASE_OUT);
slideAnim->AddListener([](float offset) {
    SetXPosition(offset);
});
animator2->AddInterpolator(slideAnim);
animator2->SetDuration(300);

// 添加到动画组
animatorGroup->AddAnimator(animator1);
animatorGroup->AddAnimator(animator2);

// 播放所有动画
animatorGroup->Play();
```

**关键特性**：
- ✅ **统一控制**：一次操作控制所有动画
- ✅ **状态同步**：跟踪每个动画的状态
- ✅ **事件回调**：单个动画完成时触发
- ⚠️ **无时序控制**：所有动画同时启动（如需时序控制使用ChainAnimation）

### ChainAnimation 动画链

**文件**：`chain_animation.h/cpp`

**功能**：实现链式动画效果（如列表项的连锁反应）

**核心概念**：使用弹簧模型实现自然的连锁运动传递

**关键参数**：
```cpp
static constexpr float DEFAULT_CONDUCTIVITY = 0.7f;  // 传导性
static constexpr float DEFAULT_INTENSITY = 0.3f;      // 强度
static constexpr float DEFAULT_EDGE_EFFECT_INTENSITY = 0.04f;  // 边缘效应强度
```

**边缘效果类型**：
```cpp
enum ChainEdgeEffect {
    DEFAULT,   // 默认效果
    STRETCH,   // 拉伸效果
};
```

**核心方法**：
```cpp
class ChainAnimation : public Animation<float> {
public:
    // 设置传导性（控制运动传递）
    void SetConductivity(float conductivity);

    // 设置强度（控制运动幅度）
    void SetIntensity(float intensity);

    // 设置边缘效果
    void SetEdgeEffect(ChainEdgeEffect edgeEffect);

    // 设置边缘效应强度
    void SetEdgeEffectIntensity(float intensity);
};
```

**传导性（Conductivity）**：
- **含义**：控制运动从一个节点传递到下一个节点的效率
- **范围**：[0.0, 1.0]
- **效果**：
  - 0.0：不传递（仅第一个节点运动）
  - 0.5：缓慢传递（波浪效果）
  - 1.0：完全传递（所有节点同步）

**强度（Intensity）**：
- **含义**：控制运动的幅度
- **范围**：[0.0, 1.0]
- **效果**：
  - 0.0：无运动
  - 0.5：中等幅度
  - 1.0：最大幅度

**边缘效果（Edge Effect）**：
- **DEFAULT**：无特殊效果
- **STRETCH**：边缘节点拉伸效果

**应用场景**：
- **列表连锁动画**：如抽屉菜单逐个展开
- **波浪效果**：链式传递产生波浪
- **物理真实感**：基于弹簧的自然运动

**使用示例**：
```cpp
// 创建链式动画
auto chainAnimation = AceType::MakeRefPtr<ChainAnimation>();

// 设置传导性（控制传递速度）
chainAnimation->SetConductivity(0.7f);  // 中等传导速度

// 设置强度（控制运动幅度）
chainAnimation->SetIntensity(0.3f);  // 中等强度

// 设置边缘效果
chainAnimation->SetEdgeEffect(ChainEdgeEffect::STRETCH);
chainAnimation->SetEdgeEffectIntensity(0.04f);

// 添加监听器
chainAnimation->AddListener([](float value) {
    // value 是当前节点的运动值
    UpdateNodePosition(index, value);
});

// 添加到Animator
animator->PlayMotion(chainAnimation);
```

**物理模型**：

ChainAnimation 内部使用弹簧链（SimpleSpringChain）实现：

```
节点1 → 节点2 → 节点3 → 节点4 → ...
  ↓       ↓       ↓       ↓
 弹簧    弹簧     弹簧     弹簧
```

每个节点的运动会影响下一个节点，形成连锁反应。

**传导性算法**：
```
节点的位移 = 前一节点的位移 × conductivity
```

**与 AnimatorGroup 的区别**：

| 特性 | AnimatorGroup | ChainAnimation |
|-----|---------------|----------------|
| **启动方式** | 所有动画同时启动 | 依次传递启动 |
| **时序控制** | 无时序控制 | 有传递时序 |
| **运动模型** | 独立动画 | 弹簧链物理模型 |
| **应用场景** | 并行动画 | 连锁反应动画 |
| **参数控制** | 无传递参数 | conductivity、intensity |

### 动画编排实践

#### 场景 1：复杂的进入动画

**需求**：组件从左侧滑入，同时淡入，透明度和位移同时变化

**方案 1：使用 AnimatorGroup（推荐）**
```cpp
auto group = AceType::MakeRefPtr<AnimatorGroup>();

// 透明度动画
auto opacityAnimator = CREATE_ANIMATOR(context, "Fade");
auto opacityAnim = AceType::MakeRefPtr<CurveAnimation<float>>(0.0f, 1.0f, Curves::EASE_IN);
opacityAnim->AddListener(UpdateOpacity);
opacityAnimator->AddInterpolator(opacityAnim);
opacityAnimator->SetDuration(300);

// 位移动画
auto offsetAnimator = CREATE_ANIMATOR(context, "Slide");
auto offsetAnim = AceType::MakeRefPtr<CurveAnimation<float>>(-100.0f, 0.0f, Curves::EASE_OUT);
offsetAnim->AddListener(UpdateOffset);
offsetAnimator->AddInterpolator(offsetAnim);
offsetAnimator->SetDuration(300);

group->AddAnimator(opacityAnimator);
group->AddAnimator(offsetAnimator);
group->Play();
```

**方案 2：使用单个 Animator（更高效）**
```cpp
auto animator = CREATE_ANIMATOR(context, "Enter");

// 添加多个插值器到同一个Animator
auto opacityAnim = AceType::MakeRefPtr<CurveAnimation<float>>(0.0f, 1.0f, Curves::EASE_IN);
opacityAnim->AddListener(UpdateOpacity);

auto offsetAnim = AceType::MakeRefPtr<CurveAnimation<float>>(-100.0f, 0.0f, Curves::EASE_OUT);
offsetAnim->AddListener(UpdateOffset);

animator->AddInterpolator(opacityAnim);
animator->AddInterpolator(offsetAnim);
animator->SetDuration(300);
animator->Play();
```

**推荐**：方案 2 更高效，因为只需要一个 Animator

#### 场景 2：列表项连锁动画

**需求**：列表项从上到下依次展开，产生波浪效果

**方案**：使用 ChainAnimation
```cpp
auto chainAnimation = AceType::MakeRefPtr<ChainAnimation>();

// 设置参数以产生波浪效果
chainAnimation->SetConductivity(0.5f);   // 较慢的传递速度
chainAnimation->SetIntensity(0.3f);      // 中等强度
chainAnimation->SetEdgeEffect(ChainEdgeEffect::STRETCH);

// 为每个列表项创建节点
for (int i = 0; i < itemCount; i++) {
    auto node = AceType::MakeRefPtr<SimpleSpringNode>();
    node->SetPosition(initialPositions[i]);
    chainAnimation->AddNode(node);
}

// 添加监听器更新UI
chainAnimation->AddListener([this](float value) {
    UpdateListItemPositions();
});

// 使用Motion方式播放
animator->PlayMotion(chainAnimation);
```

#### 场景 3：顺序动画（一个接一个）

**需求**：先执行动画A，完成后执行动画B

**方案 1：使用停止监听器**
```cpp
auto animatorA = CREATE_ANIMATOR(context, "AnimA");
// ... 配置动画A ...

auto animatorB = CREATE_ANIMATOR(context, "AnimB");
// ... 配置动画B ...

// 在动画A停止时启动动画B
animatorA->AddStopListener([animatorB]() {
    animatorB->Play();
});

animatorA->Play();
```

**方案 2：使用延迟**
```cpp
auto animator = CREATE_ANIMATOR(context, "Sequence");

// 动画A（0-300ms）
auto animA = CreateAnimationA();
animA->SetDuration(300);

// 动画B（300-600ms）- 延迟300ms启动
auto animB = CreateAnimationB();
animB->SetStartDelay(300);
animB->SetDuration(300);

animator->AddInterpolator(animA);
animator->AddInterpolator(animB);
animator->Play();
```

**推荐**：方案 2 更简洁

---

## 过渡效果

### SharedTransition 共享元素过渡

**文件**：
- `shared_transition.h`
- `shared_transition_controller.h/cpp`
- `shared_transition_effect.h/cpp`

**功能**：实现页面间共享元素的平滑过渡动画

**核心概念**：共享元素在不同页面之间保持视觉连续性

**过渡效果类型**：

```cpp
enum SharedTransitionEffectType {
    SHARED_EFFECT_EXCHANGE,  // 交换式：元素位置互换
    SHARED_EFFECT_STATIC,     // 静态式：元素原地变换
};
```

#### SharedTransitionEffect 实现详解

**文件**：`shared_transition_effect.h/cpp`

**核心方法**：

```cpp
class SharedTransitionEffect : public AceType {
public:
    // 获取共享过渡效果实例
    static RefPtr<SharedTransitionEffect> GetSharedTransitionEffect(
        SharedTransitionEffectType effect,
        const ShareId& shareId);

    // 设置共享元素
    void SetSharedElement(
        const WeakPtr<SharedTransitionElement>& src,
        const WeakPtr<SharedTransitionElement>& dest);

    // 创建动画
    virtual bool CreateAnimation(
        TweenOption& option,
        TransitionEvent event,
        bool isLazy) = 0;

    // 应用动画
    virtual bool ApplyAnimation(
        RefPtr<OverlayElement>& overlay,
        RefPtr<Animator>& controller,
        TweenOption& option,
        TransitionEvent event) = 0;
};
```

**关键机制**：

##### 1. CheckIn/TakeOff 机制

**概念**：模拟飞机"登机/下机"的过程

```cpp
// CheckIn：元素登机（准备过渡）
void CheckIn(const RefPtr<SharedTransitionElement>& element) {
    // 保存元素状态
    element->SaveOriginalState();

    // 添加到过渡管理器
    transitionManager_->AddElement(element);
}

// TakeOff：元素下机（完成过渡）
void TakeOff(const RefPtr<SharedTransitionElement>& element) {
    // 恢复元素状态
    element->RestoreOriginalState();

    // 从过渡管理器移除
    transitionManager_->RemoveElement(element);
}
```

##### 2. 动画创建流程

```cpp
bool CreateAnimation(TweenOption& option, TransitionEvent event, bool isLazy)
{
    switch (event) {
        case TransitionEvent::ENTER:
            // 进入动画：创建位移、尺寸、透明度动画
            CreateTranslateAnimation(option);
            CreateSizeAnimation(option);
            CreateOpacityAnimation(option);
            break;

        case TransitionEvent::EXIT:
            // 退出动画：反向动画
            CreateReverseAnimation(option);
            break;

        case TransitionEvent::POP:
            // 返回动画：特殊处理
            CreatePopAnimation(option);
            break;
    }

    return true;
}
```

##### 3. 懒加载回调

```cpp
void AddLazyLoadCallback(std::function<void()>&& callback)
{
    // 当尺寸不确定时延迟处理
    lazyLoadCallbacks_.emplace_back(callback);
}

// 当尺寸确定后触发
void OnSizeDetermined()
{
    for (auto& callback : lazyLoadCallbacks_) {
        if (callback) {
            callback();
        }
    }
    lazyLoadCallbacks_.clear();
}
```

#### Exchange 模式 vs Static 模式

**Exchange 模式**（SHARED_EFFECT_EXCHANGE）：

```
页面A                 页面B
┌─────────┐         ┌─────────┐
│  图片   │   →     │         │
│  (小)   │ 交换   │  图片   │
└─────────┘         └─────────┘
                      (大)

效果：图片从小位置移动到大位置
```

**Static 模式**（SHARED_EFFECT_STATIC）：

```
页面A                 页面B
┌─────────┐         ┌─────────┐
│  图片   │         │  图片   │
│  (小)   │  变换  │  (大)   │
└─────────┘         └─────────┘
原地变换（位置不变）

效果：图片在原位置逐渐变大
```

#### 使用示例

```cpp
// 页面A：定义共享元素
Image()
    .width(100)
    .height(100)
    .id("sharedImage")
    .sharedTransition("sharedId", SharedTransitionEffectType::EXCHANGE)

// 页面B：使用相同的共享ID
Image()
    .width(200)
    .height(200)
    .id("sharedImage")
    .sharedTransition("sharedId", SharedTransitionEffectType::EXCHANGE)
```

**过渡参数配置**：

```cpp
SharedTransitionOptions options;
options.duration = 300;           // 过渡时长
options.curve = Curves::EASE_IN_OUT;  // 过渡曲线
options.zIndex = 100;             // 层级
options.type = SharedTransitionEffectType::EXCHANGE;
```

### CardTransition 卡片过渡

**文件**：`card_transition_controller.h/cpp`

**功能**：控制卡片切换的过渡动画

**支持的动画类型**：

```cpp
enum CardTransitionType {
    CARD_POSITION,      // 位置动画
    CARD_OPACITY,       // 透明度动画
    CARD_SCALE,         // 缩放动画
    CARD_LIST,          // 列表动画
};
```

**核心方法**：

```cpp
class CardTransitionController : public AceType {
public:
    // 创建卡片动画
    bool CreateCardAnimation(
        const RefPtr<Animator>& animator,
        const TweenOption& option);

    // 创建卡片透明度动画
    bool CreateCardOpacityAnimation(
        const RefPtr<Animator>& animator,
        const TweenOption& option);

    // 创建卡片位置动画
    bool CreateCardPositionAnimation(
        const RefPtr<Animator>& animator,
        const TweenOption& option);

    // 创建卡片缩放动画
    bool CreateCardScaleAnimation(
        const RefPtr<Animator>& animator,
        const TweenOption& option);

    // 注册过渡监听器
    void RegisterTransitionListener(
        const RefPtr<PageTransitionListener>& listener);
};
```

**RenderTransform 集成**：

```cpp
// 与渲染节点集成
void ApplyToRenderNode(const RefPtr<RenderNode>& renderNode)
{
    auto transform = renderNode->GetTransform();

    // 应用变换矩阵
    transform.SetTranslation(x_, y_);
    transform.SetScale(scale_, scale_);
    transform.SetRotation(rotation_);

    renderNode->SetTransform(transform);
    renderNode->MarkDirty();
}
```

**使用场景**：
- 卡片堆叠切换
- 卡片翻转效果
- 卡片3D旋转
- 卡片滑动切换

### PageTransitionCommon 页面过渡

**文件**：`page_transition_common.h`

**功能**：定义页面过渡的通用配置

**页面过渡类型**：

```cpp
enum class PageTransitionType {
    NONE,
    ENTER,          // 进入
    EXIT,           // 退出
    PUSH,           // 推入
    POP,            // 弹出
};
```

**路由类型**：

```cpp
enum class RouteType {
    NONE,
    PUSH,           // 推入新页面
    POP,            // 弹出当前页面
    REPLACE,        // 替换当前页面
};
```

**滑动效果**：

```cpp
enum class SlideEffect {
    NONE,           // 无滑动
    LEFT,           // 向左滑动
    RIGHT,          // 向右滑动
    UP,             // 向上滑动
    DOWN,           // 向下滑动
};
```

**页面过渡选项**：

```cpp
struct PageTransitionOption {
    PageTransitionType type = PageTransitionType::NONE;
    RouteType routeType = RouteType::PUSH;
    SlideEffect slideEffect = SlideEffect::NONE;
    uint32_t duration = 300;
    RefPtr<Curve> curve = Curves::EASE_IN_OUT;
};
```

**使用示例**：

```cpp
// 配置页面过渡
PageTransitionOption option;
option.type = PageTransitionType::ENTER;
option.routeType = RouteType::PUSH;
option.slideEffect = SlideEffect::RIGHT;
option.duration = 300;
option.curve = Curves::EASE_IN_OUT;

// 应用到页面路由
Router::PushRoute(targetPage, option);
```

---

## 高级动画特性

### BezierVariableVelocityMotion 贝塞尔变速运动

**文件**：`bezier_variable_velocity_motion.h`

**功能**：基于贝塞尔曲线的变速运动，主要用于滚动场景

**核心概念**：定义热区（Hot Zone）实现动态速度控制

**关键常量**：
```cpp
constexpr float HOT_ZONE_HEIGHT_VP = 15.0f;    // 热区高度（vp）
constexpr float HOT_ZONE_WIDTH_VP = 15.0f;     // 热区宽度（vp）
constexpr float MAX_SPEED = 2400.0f;            // 最大速度
```

**速度计算算法**：

```cpp
double ComputeVelocity(float offsetPct)
{
    // 1. 计算距离热区中心的偏移百分比
    float offsetFromCenter = std::abs(offsetPct);

    // 2. 使用SHARP曲线映射到速度
    double curveValue = Curves::SHARP->MoveInternal(offsetFromCenter);

    // 3. 计算最终速度
    return curveValue * MAX_SPEED;
}
```

**热区概念图**：

```
滚动位置
    ↓
┌─────────────────────┐
│   非热区（慢速）     │
├─────────────────────┤
│   热区（变速）      │ ← 在这里速度变化
├─────────────────────┤
│   非热区（慢速）     │
└─────────────────────┘
```

**应用场景**：
- **滚动阻尼**：接近边界时自动减速
- **快速滚动**：中间区域快速滚动
- **边界回弹**：超出边界后的回弹效果

**使用示例**：

```cpp
// 创建贝塞尔变速运动
auto motion = AceType::MakeRefPtr<BezierVariableVelocityMotion>();

// 设置热区参数
motion->SetHotZoneHeight(15.0f);
motion->SetHotZoneWidth(15.0f);

// 添加监听器
motion->AddListener([](double position) {
    UpdateScrollPosition(position);
});

// 使用Motion方式播放
animator->PlayMotion(motion);
```

### PictureAnimation 帧动画

**文件**：`picture_animation.h`

**功能**：实现帧动画（如精灵图动画）

**类定义**：
```cpp
template<typename T>
class PictureAnimation : public Animation<T> {
public:
    // 添加动画帧
    bool AddPicture(float duration, const T& pictureInfo);

    // 自动缩放总时长到1.0（标准化）
    void AutoScale();

    // 获取当前帧
    const T& GetCurrentPicture() const;

    // 获取总时长
    float GetTotalDuration() const;
};
```

**核心特性**：

##### 1. 帧持续时间控制

```cpp
struct PictureFrame<T> {
    float duration;      // 帧持续时间（秒）
    T pictureInfo;      // 帧数据（图片路径、纹理等）
};

// 添加帧
bool AddPicture(float duration, const T& pictureInfo)
{
    PictureFrame<T> frame;
    frame.duration = duration;
    frame.pictureInfo = pictureInfo;

    frames_.emplace_back(frame);
    totalDuration_ += duration;

    return true;
}
```

##### 2. 自动缩放（标准化）

```cpp
void AutoScale()
{
    if (NearZero(totalDuration_)) {
        return;
    }

    // 计算缩放比例
    float scale = 1.0f / totalDuration_;

    // 更新所有帧的持续时间
    for (auto& frame : frames_) {
        frame.duration *= scale;
    }

    totalDuration_ = 1.0f;  // 标准化到1.0
}
```

##### 3. 时序控制

```cpp
void OnNormalizedTimestampChanged(float normalized, bool reverse) override
{
    // 1. 初始状态（normalized < 0）
    if (normalized < 0.0f) {
        currentFrameIndex_ = 0;
        NotifyListener(frames_[0].pictureInfo);
        return;
    }

    // 2. 计算当前帧
    float accumulatedTime = 0.0f;
    for (size_t i = 0; i < frames_.size(); ++i) {
        accumulatedTime += frames_[i].duration;

        if (normalized <= accumulatedTime) {
            if (currentFrameIndex_ != i) {
                currentFrameIndex_ = i;
                // 触发帧切换
                NotifyListener(frames_[i].pictureInfo);
            }
            return;
        }
    }

    // 3. 结束状态（normalized > 1.0）
    currentFrameIndex_ = frames_.size() - 1;
    NotifyListener(frames_.back().pictureInfo);
}
```

**使用示例**：

```cpp
// 创建帧动画
auto pictureAnimation = AceType::MakeRefPtr<PictureAnimation<std::string>>();

// 添加帧（图片路径）
pictureAnimation->AddPicture(0.1f, "resources/frame1.png");
pictureAnimation->AddPicture(0.1f, "resources/frame2.png");
pictureAnimation->AddPicture(0.1f, "resources/frame3.png");
pictureAnimation->AddPicture(0.1f, "resources/frame4.png");

// 自动缩放（可选）
pictureAnimation->AutoScale();

// 添加监听器
pictureAnimation->AddListener([](const std::string& imagePath) {
    SetImage(imagePath);
});

// 添加到Animator
animator->AddInterpolator(pictureAnimation);
animator->Play();
```

**应用场景**：
- **精灵图动画**：角色行走、攻击等
- **加载动画**：进度指示器
- **状态指示器**：在线/离线图标切换
- **逐帧动画**：任何需要逐帧控制的场景

### AnimatorInfo 动画信息

**文件**：`animator_info.h`

**功能**：封装动画的配置信息，统一管理动画属性

**核心定义**：

```cpp
struct AnimatorInfo {
    // 状态枚举
    enum AnimationStatus {
        INITIAL,
        RUNNING,
        PAUSED,
        STOPPED,
    };

    // 事件操作枚举
    enum EventOperation {
        NONE,
        START,
        PAUSE,
        REPEAT,
        CANCEL,
        FINISH,
    };

    // 核心属性
    RefPtr<Curve> curve;              // 动画曲线
    FillMode fillMode;                // 填充模式
    AnimationDirection playMode;      // 播放方向
    RefPtr<Motion> motion;            // 运动对象
    int32_t duration;                 // 持续时间
    int32_t startDelay;               // 启动延迟
    int32_t repeat;                   // 重复次数

    // 事件回调
    AnimatorEventFunc frameEvent;     // 帧事件回调
    AnimatorEventFunc finishEvent;    // 完成事件回调

    // 状态管理
    AnimationStatus status;           // 当前状态
    EventOperation lastOperation;     // 最后的操作
};
```

**事件系统**：

```cpp
// 帧事件回调类型
using AnimatorEventFunc = std::function<void(const AnimatorEventInfo& info)>;

struct AnimatorEventInfo {
    float progress;        // 进度 [0.0, 1.0]
    int64_t elapsedTime;   // 已播放时间（毫秒）
    bool isReverse;        // 是否反向播放
};

// 设置帧事件
void SetFrameEvent(AnimatorEventFunc callback)
{
    frameEvent_ = callback;
}

// 设置完成事件
void SetFinishEvent(AnimatorEventFunc callback)
{
    finishEvent_ = callback;
}
```

**与 JS 引擎集成**：

```cpp
// JS 引擎销毁时的清理
void OnJsEngineDestroy()
{
    // 清理 JS 回调
    frameEvent_ = nullptr;
    finishEvent_ = nullptr;

    // 停止动画
    if (status == AnimationStatus::RUNNING) {
        Stop();
    }
}
```

**使用场景**：
- **统一配置管理**：避免多个参数传递
- **事件通知**：帧事件、完成事件
- **跨语言集成**：C++ 与 JavaScript 交互

---

## 性能优化

### 异步动画机制

**文件**：`interpolator.h:63-92`

**核心方法**：

```cpp
virtual bool RunAsync(
    const WeakPtr<Scheduler>& weakScheduler,
    const AnimationOption& option,
    const std::function<void()>& prepareCallback = nullptr,
    const std::function<void()>& finishCallback = nullptr)
{
    auto scheduler = weakScheduler.Upgrade();
    if (!scheduler) {
        LOGE("run async failed, scheduler is null.");
        return false;
    }

    if (prepareCallback) {
        prepareCallback();
    }

    return scheduler->Animate(option, GetCurve(),
        [weak = AceType::WeakClaim(this), callback = prepareCallback]() -> void {
            auto animation = weak.Upgrade();
            if (!animation) {
                LOGE("property change failed, animation is null.");
                return;
            }

            if (callback) {
                callback();
            }

            animation->OnNormalizedTimestampChanged(NORMALIZED_DURATION_MAX, false);
        }, finishCallback);
}
```

**关键限制**：❌ **非线性Evaluator不支持异步动画**

**文件**：`curve_animation.h:67-78`

```cpp
void SetEvaluator(const RefPtr<Evaluator<T>>& evaluator)
{
    if (evaluator) {
        isSupportedRunningAsync_ = false;  // 标记为不支持异步
        evaluator_ = evaluator;
    }
}

bool IsSupportedRunningAsynchronously() override
{
    return isSupportedRunningAsync_;
}
```

**支持异步的条件**：
- ✅ 使用默认的 LinearEvaluator
- ✅ 使用线性插值的简单动画
- ❌ 使用 ColorEvaluator（伽马校正）
- ❌ 使用 TransformOperationEvaluator（复杂变换）
- ❌ 使用自定义的非线性Evaluator

**性能对比**：

| 方式 | 优点 | 缺点 | 适用场景 |
|-----|------|------|---------|
| **同步动画** | 简单、可靠 | 主线程执行，可能阻塞 | 简单动画、低频更新 |
| **异步动画** | 不阻塞主线程 | 仅支持线性插值 | 复杂场景、大量动画 |

### 帧率优化策略

**动态帧率范围**：

**文件**：`animator.h:107`

```cpp
bool SetExpectedFrameRateRange(const FrameRateRange& frameRateRange)
{
    if (!scheduler_) {
        return false;
    }

    return scheduler_->SetExpectedFrameRateRange(frameRateRange);
}
```

**FrameRateRange 定义**：

```cpp
struct FrameRateRange {
    uint32_t min;    // 最小帧率
    uint32_t max;    // 最大帧率
    uint32_t preferred;
};
```

**使用示例**：

```cpp
// 设置帧率范围（30-60 FPS）
FrameRateRange range;
range.min = 30;
range.max = 60;
range.preferred = 60;

animator->SetExpectedFrameRateRange(range);
```

**VSync 同步**：

```cpp
// 使用 UIDisplaySync 进行帧同步
RefPtr<UIDisplaySync> displaySync_ =
    AceType::MakeRefPtr<UIDisplaySync>(UIObjectType::DISPLAYSYNC_ANIMATOR);

// 注册VSync回调
displaySync_->Start(callback);
```

**帧跳过策略**：

```cpp
void OnFrame(int64_t duration)
{
    // 计算时间间隔
    int64_t interval = currentTime - lastFrameTime_;

    // 如果间隔太短（超过帧率），跳过此帧
    if (interval < minFrameInterval_) {
        return;  // 跳过此帧
    }

    // 更新动画
    NotifyInterpolator(playedTime);

    lastFrameTime_ = currentTime;
}
```

### 缓存机制

**多层缓存策略**：

#### 1. 状态缓存

```cpp
// Animator状态缓存
enum class Status {
    IDLE,     // 空闲状态
    RUNNING,  // 运行状态
    PAUSED,   // 暂停状态
    STOPPED,  // 停止状态
};

Status status_ = Status::IDLE;  // 缓存当前状态
```

#### 2. 曲线值缓存

```cpp
// CurveAnimation中的值缓存
T currentValue_;  // 当前计算值缓存

const T& GetValue() const override
{
    return currentValue_;  // 直接返回缓存，无需重新计算
}
```

#### 3. 时间点缓存

```cpp
// AnimatableBase中的时间点缓存
float timePoint_ = 0.0f;  // 当前时间点缓存

void SetTimePoint(float timePoint)
{
    timePoint_ = timePoint;  // 缓存时间点
}
```

**缓存失效策略**：

```cpp
// 当属性变化时，清除缓存
void InvalidateCache()
{
    currentValue_ = T{};        // 清除值缓存
    timePoint_ = 0.0f;          // 清除时间点缓存
    isCached_ = false;          // 标记缓存无效
}
```

### 性能监控

**帧率监控**：

```cpp
class PerformanceMonitor {
public:
    void OnFrameStart()
    {
        frameStartTime_ = GetHighResolutionTicks();
    }

    void OnFrameEnd()
    {
        auto frameEndTime = GetHighResolutionTicks();
        auto frameDuration = frameEndTime - frameStartTime_;

        // 计算FPS
        if (frameDuration > 0) {
            float fps = 1000000.0f / frameDuration;  // ticks per second

            // 记录FPS
            fpsHistory_.emplace_back(fps);

            // 保持最近60帧
            if (fpsHistory_.size() > 60) {
                fpsHistory_.pop_front();
            }
        }
    }

    float GetAverageFPS()
    {
        if (fpsHistory_.empty()) {
            return 0.0f;
        }

        float sum = 0.0f;
        for (auto fps : fpsHistory_) {
            sum += fps;
        }

        return sum / fpsHistory_.size();
    }

private:
    std::deque<float> fpsHistory_;  // FPS历史记录
};
```

### 性能优化实践

#### 1. 减少监听器中的计算

```cpp
// ❌ 错误：每帧都重计算
animation->AddListener([](float value) {
    auto result = HeavyCalculation(value);  // 每帧都计算
    UpdateUI(result);
});

// ✅ 正确：预先计算或缓存
auto cachedResults = PreComputeResults();
animation->AddListener([cachedResults](float value) {
    auto index = static_cast<int>(value * cachedResults.size());
    UpdateUI(cachedResults[index]);
});
```

#### 2. 合并属性更新

```cpp
// ❌ 错误：多次触发重绘
animation->AddListener([](float value) {
    SetX(value);
    RequestFrame();  // 第一次重绘
    SetY(value);
    RequestFrame();  // 第二次重绘
});

// ✅ 正确：一次更新多个属性
animation->AddListener([](float value) {
    SetX(value);
    SetY(value);
    RequestFrame();  // 只触发一次重绘
});
```

#### 3. 使用合适的曲线

```cpp
// ✅ 简单动画使用线性曲线（计算快）
auto linearAnim = AceType::MakeRefPtr<CurveAnimation<float>>(
    0.0f, 1.0f, Curves::LINEAR);

// ⚠️ 复杂曲线增加计算开销
auto complexAnim = AceType::MakeRefPtr<CurveAnimation<float>>(
    0.0f, 1.0f, Curves::ELASTICS);  // 需要多次振荡计算
```

#### 4. 控制动画数量

```cpp
// 限制同时运行的动画数量
constexpr int MAX_ANIMATORS = 50;

if (activeAnimatorCount >= MAX_ANIMATORS) {
    LOGW("Too many active animators, skipping new animation");
    return false;
}
```

#### 5. 使用异步动画（适用场景）

```cpp
// 检查是否支持异步
if (animation->IsSupportedRunningAsynchronously()) {
    // 使用异步执行
    animation->RunAsync(weakScheduler, option, prepareCallback, finishCallback);
} else {
    // 同步执行
    animator->AddInterpolator(animation);
    animator->Play();
}
```

### 性能分析工具

**动画性能分析器**：

```cpp
class AnimationProfiler {
public:
    void BeginSample(const std::string& name)
    {
        samples_[name].startTime = GetHighResolutionTicks();
    }

    void EndSample(const std::string& name)
    {
        auto endTime = GetHighResolutionTicks();
        samples_[name].duration = endTime - samples_[name].startTime;
        samples_[name].count++;
    }

    void DumpReport()
    {
        for (const auto& [name, sample] : samples_) {
            float avgDuration = sample.duration / sample.count;
            LOGI("Animation[%s]: avg=%{public}lld us, count=%{public}d",
                name.c_str(), avgDuration, sample.count);
        }
    }

private:
    struct Sample {
        int64_t startTime = 0;
        int64_t duration = 0;
        int32_t count = 0;
    };

    std::unordered_map<std::string, Sample> samples_;
};
```

---

## SVG 动画

### SvgAnimate SVG 动画支持

**文件**：`svg_animate.h/cpp`

**功能**：实现 SVG 元素的属性动画，支持 W3C SVG 动画规范

**动画类型**：

```cpp
enum class SvgAnimateType {
    ANIMATE,     // 基础属性动画
    MOTION,      // 路径动画（沿路径运动）
    TRANSFORM,   // 变换动画
};
```

**计算模式**：

```cpp
enum class CalcMode {
    LINEAR,      // 线性插值
    PACED,       // 均匀速度
    DISCRETE,    // 离散跳变
    SPLINE,      // 样条曲线插值
};
```

**填充模式**：

```cpp
enum class Fill {
    FREEZE,      // 冻结在结束状态
    REMOVE,      // 动画后移除（恢复初始状态）
};
```

### 支持的 SVG 属性

**位置属性**：
- `x` - 横坐标
- `y` - 纵坐标
- `cx` - 圆心横坐标
- `cy` - 圆心纵坐标
- `fx` - 焦点横坐标
- `fy` - 焦点纵坐标

**尺寸属性**：
- `width` - 宽度
- `height` - 高度
- `r` - 半径

**颜色属性**：
- `fill` - 填充颜色
- `stroke` - 描边颜色
- `stop-color` - 渐变停止点颜色
- `flood-color` - 填充颜色

**变换属性**：
- `transform` - 2D/3D 变换

**其余属性**：
- `opacity` - 透明度
- `filter` - 滤镜效果

### 核心类定义

**文件**：`svg_animate.h:45-484`

```cpp
class SvgAnimate : public SvgNode {
public:
    // === 动画类型设置 ===
    void SetAnimateType(SvgAnimateType type);

    // === 属性设置 ===
    void SetAttributeName(const std::string& attributeName);
    void SetAttributeType(SvgAttributeType attributeType);
    void SetFrom(const std::string& from);
    void SetTo(const std::string& to);
    void SetValues(const std::vector<std::string>& values);
    void SetKeyTimes(const std::vector<std::string>& keyTimes);
    void SetKeySplines(const std::vector<std::string>& keySplines);

    // === 时长控制 ===
    void SetDur(const std::string& dur);  // 格式："2s", "500ms"
    void SetBegin(const std::string& begin);
    void SetRepeatCount(const std::string& repeatCount);  // "indefinite", "3"

    // === 计算模式 ===
    void SetCalcMode(const CalcMode& calcMode);

    // === 填充模式 ===
    void SetFill(const std::string& fill);  // "freeze", "remove"

    // === 路径动画 ===
    void SetPath(const std::string& path);
    void SetRotate(float rotate);
    void SetKeyPoints(const std::string& keyPoints);

    // === 变换动画 ===
    void SetTransformType(SvgTransformType type);
    void SetTransformOrigin(const Dimension& originX, const Dimension& originY);

    // === 播放控制 ===
    void Play();
    void Pause();
    void Stop();

private:
    SvgAnimateType type_;
    std::string attributeName_;
    std::string from_;
    std::string to_;
    std::string dur_;
    std::string begin_;
    std::string repeatCount_;
    CalcMode calcMode_;
    Fill fill_;
    std::vector<std::string> values_;
    std::vector<std::string> keyTimes_;
    std::vector<std::string> keySplines_;
    RefPtr<Animator> animator_;
};
```

### 曲线生成

**根据计算模式生成曲线**：

```cpp
RefPtr<Curve> GetCurve(const std::string& param = "") const
{
    switch (calcMode_) {
        case CalcMode::DISCRETE:
            // 离散跳变：使用Steps曲线
            return AceType::MakeRefPtr<StepsCurve>(1, StepsCurvePosition::START);

        case CalcMode::PACED:
            // 均匀速度：使用线性曲线
            return Curves::LINEAR;

        case CalcMode::SPLINE:
            // 样条曲线插值：使用三次贝塞尔曲线
            return CubicCurveCreator(param);

        case CalcMode::LINEAR:
        default:
            // 默认：线性曲线
            return Curves::LINEAR;
    }
}
```

**CubicCurveCreator 实现**：

```cpp
RefPtr<Curve> CubicCurveCreator(const std::string& param)
{
    // 解析参数格式："x1 y1 x2 y2"
    std::vector<float> values = ParseCurveParams(param);

    if (values.size() == 4) {
        // 创建三次贝塞尔曲线
        return AceType::MakeRefPtr<CubicCurve>(
            values[0], values[1], values[2], values[3]
        );
    }

    // 解析失败，使用默认曲线
    return Curves::LINEAR;
}
```

### 动画创建方法

#### 属性动画创建

**文件**：`svg_animate.h:200-230`

```cpp
template<typename T>
bool CreatePropertyAnimate(
    std::function<void(T)>&& callback,
    const T& originalValue,
    const RefPtr<Animator>& animator)
{
    // 创建属性动画
    auto animation = AceType::MakeRefPtr<CurveAnimation<T>>(
        originalValue, targetValue, GetCurve());

    // 添加回调
    animation->AddListener([callback](const T& value) {
        callback(value);
    });

    // 添加到Animator
    animator->AddInterpolator(animation);

    return true;
}
```

**使用示例**：

```cpp
// 创建x坐标属性动画
auto animateX = AceType::MakeRefPtr<SvgAnimate>();
animateX->SetAttributeName("x");
animateX->SetFrom("0");
animateX->SetTo("100");
animateX->SetDur("2s");
animateX->SetCalcMode(CalcMode::LINEAR);

// 创建Animator并播放
auto animator = CREATE_ANIMATOR(context);
animateX->CreatePropertyAnimate<float>(
    [](float x) {
        SetAttribute("x", std::to_string(x));
    },
    0.0f,
    animator
);
animator->Play();
```

#### 运动动画创建

**文件**：`svg_animate.h:232-250`

```cpp
bool CreateMotionAnimate(
    std::function<void(double)>&& callback,
    const RefPtr<Animator>& animator)
{
    // 使用Motion实现路径动画
    auto motion = AceType::MakeRefPtr<SvgMotion>();

    // 设置路径
    motion->SetPath(path_);

    // 添加回调
    motion->AddListener([callback](double position) {
        callback(position);
    });

    // 使用Motion方式播放
    animator->PlayMotion(motion);

    return true;
}
```

### 高级特性

#### 1. 关键帧支持

```cpp
// 设置关键帧值
animate->SetValues({
    "10",   // 0%
    "50",   // 33%
    "100",  // 66%
    "200"   // 100%
});

// 设置关键时间
animate->SetKeyTimes({
    "0; 0.33; 0.66; 1"
});

// 设置关键曲线
animate->SetKeySplines({
    "0.4 0 0.2 1",    // 0-33%区间
    "0.4 0 0.2 1",    // 33-66%区间
    "0.4 0 0.2 1"     // 66-100%区间
});
```

#### 2. 变换动画

```cpp
auto animateTransform = AceType::MakeRefPtr<SvgAnimate>();
animateTransform->SetAnimateType(SvgAnimateType::TRANSFORM);

// 设置变换类型
animateTransform->SetTransformType(SvgTransformType::TRANSLATE);

// 设置变换原点
animateTransform->SetTransformOrigin(50.0_vp, 50.0_vp);

// 设置from和to
animateTransform->SetFrom("translate(0, 0)");
animateTransform->SetTo("translate(100, 100)");
```

**支持的变换类型**：
- `TRANSLATE` - 平移
- `SCALE` - 缩放
- `ROTATE` - 旋转
- `SKEWX` - X轴倾斜
- `SKEWY` - Y轴倾斜

### SVG 动画示例

#### 示例 1：基础属性动画

```xml
<svg width="200" height="200">
  <circle cx="50" cy="50" r="20" fill="red">
    <animate attributeName="r"
             from="20"
             to="50"
             dur="2s"
             fill="freeze" />
  </circle>
</svg>
```

#### 示例 2：颜色动画

```xml
<svg width="200" height="200">
  <rect x="50" y="50" width="100" height="100" fill="blue">
    <animate attributeName="fill"
             from="blue"
             to="red"
             dur="3s"
             calcMode="linear"
             fill="freeze" />
  </rect>
</svg>
```

#### 示例 3：关键帧动画

```xml
<svg width="200" height="200">
  <circle cx="100" cy="100" r="20" fill="green">
    <animate attributeName="r"
             values="20; 40; 60; 40; 20"
             keyTimes="0; 0.25; 0.5; 0.75; 1"
             dur="4s"
             calcMode="linear"
             fill="freeze" />
  </circle>
</svg>
```

#### 示例 4：路径动画

```xml
<svg width="300" height="200">
  <path id="motionPath" d="M10,80 Q95,10 180,80" fill="none" stroke="black"/>
  <circle r="10" fill="blue">
    <animateMotion dur="3s" repeatCount="indefinite">
      <mpath href="#motionPath"/>
    </animateMotion>
  </circle>
</svg>
```

#### 示例 5：变换动画

```xml
<svg width="200" height="200">
  <rect x="50" y="50" width="50" height="50" fill="purple">
    <animateTransform attributeName="transform"
                        type="rotate"
                        from="0 100 100"
                        to="360 100 100"
                        dur="4s"
                        fill="freeze" />
  </rect>
</svg>
```

### 与 SVG 规范的兼容性

**支持的 W3C SVG 规范特性**：

✅ **完全支持**：
- 基础属性动画（`<animate>`）
- 路径动画（`<animateMotion>`）
- 变换动画（`<animateTransform>`）
- 关键帧（`values`, `keyTimes`, `keySplines`）
- 计算模式（`calcMode`）
- 填充模式（`fill`）
- 重复控制（`repeatCount`）

⚠️ **部分支持**：
- `begin` 属性（简化版）
- `end` 属性（简化版）

❌ **不支持**：
- `additive` 属性（累加动画）
- `accumulate` 属性（累积动画）
- `min` / `max` 属性（值限制）

### FlushEvent 机制

**文件**：`flush_event.h`

**功能**：控制SVG动画的刷新时机

```cpp
class FlushEvent : public AceType {
public:
    // 触发刷新事件
    void FlushAnimation();

    // 判断是否需要刷新
    bool NeedFlush();
};
```

**使用场景**：
- 控制SVG动画的更新频率
- 优化性能，避免不必要的刷新
- 与VSync同步

---

## 完整 API 清单

### Animator API

```cpp
// === 创建 ===
Animator(const WeakPtr<PipelineBase>& context, const char* name = nullptr);
static RefPtr<Animator> CreateAnimator(...);

// === 插值器管理 ===
void AddInterpolator(const RefPtr<Interpolator>& animation);
void RemoveInterpolator(const RefPtr<Interpolator>& animation);
void ClearInterpolators();

// === 代理控制器 ===
void AddProxyController(const RefPtr<Animator>& proxy);
void RemoveProxyController(const RefPtr<Animator>& proxy);
void ClearProxyControllers();

// === 状态查询 ===
Status GetStatus() const;
bool IsStopped() const;
bool IsRunning() const;
bool IsPending() const;

// === 时间控制 ===
void SetDuration(int32_t duration);
int32_t GetDuration() const;
void SetStartDelay(int32_t startDelay);
bool SetIteration(int32_t iteration);
void SetTempo(float tempo);
int64_t GetPlayedTime() const;

// === 填充模式 ===
void SetFillMode(FillMode fillMode);
FillMode GetFillMode() const;

// === 方向控制 ===
void SetAnimationDirection(AnimationDirection direction);
void Play();
void Reverse();
void Forward();
void Backward();

// === 播放控制 ===
void Pause();
void Resume();
void Stop();
void Finish();
void Cancel();

// === Motion 动画 ===
void PlayMotion(const RefPtr<Motion>& motion);

// === 全局控制 ===
static void SetDurationScale(float scale);
float GetAnimationScale() const;
```

### CurveAnimation API

```cpp
// === 创建 ===
CurveAnimation(const T& begin, const T& end, const RefPtr<Curve>& curve);

// === 配置 ===
void SetCurve(const RefPtr<Curve>& curve);
void SetReverseCurve(const RefPtr<Curve>& reverseCurve);
void SetEvaluator(const RefPtr<Evaluator<T>>& evaluator);

// === 值获取 ===
const T& GetValue() const;
```

### KeyframeAnimation API

```cpp
// === 关键帧管理 ===
void AddKeyframe(const RefPtr<Keyframe<T>>& keyframe);
void AddKeyframe(const std::list<RefPtr<Keyframe<T>>>& keyframes);
void ReplaceKeyframe(const RefPtr<Keyframe<T>>& keyframeReplace);

// === 值获取 ===
const T& GetValue() const;
const std::list<RefPtr<Keyframe<T>>>& GetKeyframes() const;
```

### SpringAnimation API

```cpp
// === 创建 ===
explicit SpringAnimation(const RefPtr<SpringProperty>& property);
SpringAnimation(const RefPtr<SpringProperty>& property, float velocity);
SpringAnimation(const RefPtr<SpringProperty>& property, float velocity, float valueThreshold);

// === 配置 ===
void SetEndPosition(float endPosition, float startVelocity);

// === 值获取 ===
const float& GetValue() const;
```

---

## 使用示例

### 示例 1：基础淡入动画

```cpp
// 创建 Animator
auto animator = CREATE_ANIMATOR(context, "FadeIn");

// 创建曲线动画（从透明到不透明）
auto curve = Curves::EASE_IN;
auto fadeAnimation = AceType::MakeRefPtr<CurveAnimation<float>>(0.0f, 1.0f, curve);

// 添加监听器
fadeAnimation->AddListener([](float opacity) {
    SetOpacity(opacity);
    RequestFrame();
});

// 配置并播放
animator->AddInterpolator(fadeAnimation);
animator->SetDuration(300); // 300ms
animator->Play();
```

### 示例 2：位移动画（带曲线）

```cpp
// 创建 Animator
auto animator = CREATE_ANIMATOR(context, "SlideIn");

// 创建三次贝塞尔曲线
auto curve = AceType::MakeRefPtr<CubicCurve>(0.25f, 0.1f, 0.25f, 1.0f);

// 创建位移动画（从 -100 到 0）
auto offsetAnimation = AceType::MakeRefPtr<CurveAnimation<float>>(
    -100.0f, 0.0f, curve);

// 添加监听器
offsetAnimation->AddListener([](float offset) {
    SetOffset(offset, 0.0f);
    RequestFrame();
});

// 配置并播放
animator->AddInterpolator(offsetAnimation);
animator->SetDuration(500); // 500ms
animator->SetFillMode(FillMode::FORWARDS);
animator->Play();
```

### 示例 3：关键帧动画

```cpp
// 创建关键帧动画
auto keyframeAnimation = AceType::MakeRefPtr<KeyframeAnimation<float>>();

// 创建关键帧
auto keyframe1 = AceType::MakeRefPtr<Keyframe<float>>(0.0f, 0.0f);
auto keyframe2 = AceType::MakeRefPtr<Keyframe<float>>(0.3f, 50.0f);
keyframe2->SetCurve(Curves::EASE_IN);

auto keyframe3 = AceType::MakeRefPtr<Keyframe<float>>(0.7f, 100.0f);
keyframe3->SetCurve(Curves::EASE_OUT);

auto keyframe4 = AceType::MakeRefPtr<Keyframe<float>>(1.0f, 150.0f);

// 添加关键帧
keyframeAnimation->AddKeyframe({keyframe1, keyframe2, keyframe3, keyframe4});

// 添加监听器
keyframeAnimation->AddListener([](float value) {
    SetScale(value);
    RequestFrame();
});

// 添加到 Animator
animator->AddInterpolator(keyframeAnimation);
animator->SetDuration(1000); // 1000ms
animator->Play();
```

### 示例 4：弹簧动画

```cpp
// 创建弹簧属性（质量、刚度、阻尼）
auto springProperty = AceType::MakeRefPtr<SpringProperty>(1.0f, 100.0f, 15.0f);

// 创建弹簧动画
auto springAnimation = AceType::MakeRefPtr<SpringAnimation>(springProperty);
springAnimation->SetEndPosition(100.0f, 0.0f);

// 添加监听器
springAnimation->AddListener([](float position) {
    SetPosition(position);
    RequestFrame();
});

// 使用 Motion 方式播放
animator->PlayMotion(springAnimation);
```

### 示例 5：重复和反向动画

```cpp
// 创建 Animator
auto animator = CREATE_ANIMATOR(context, "Bounce");

// 创建动画
auto animation = AceType::MakeRefPtr<CurveAnimation<float>>(0.0f, 100.0f, Curves::EASE_IN_OUT);
animation->AddListener([](float value) {
    SetYPosition(value);
    RequestFrame();
});

// 配置重复和反向
animator->AddInterpolator(animation);
animator->SetDuration(500);
animator->SetIteration(3); // 重复 3 次
animator->SetAnimationDirection(AnimationDirection::ALTERNATE); // 自动反向
animator->SetFillMode(FillMode::FORWARDS);
animator->Play();
```

### 示例 6：动画链

```cpp
// 创建动画链
auto chainAnimation = AceType::MakeRefPtr<ChainAnimation>();

// 创建第一个动画
auto animator1 = CREATE_ANIMATOR(context, "Step1");
auto anim1 = AceType::MakeRefPtr<CurveAnimation<float>>(0.0f, 100.0f, Curves::EASE_IN);
animator1->AddInterpolator(anim1);
animator1->SetDuration(300);

// 创建第二个动画
auto animator2 = CREATE_ANIMATOR(context, "Step2");
auto anim2 = AceType::MakeRefPtr<CurveAnimation<float>>(100.0f, 200.0f, Curves::EASE_OUT);
animator2->AddInterpolator(anim2);
animator2->SetDuration(300);

// 添加到链中
chainAnimation->AddAnimator(animator1);
chainAnimation->AddAnimator(animator2);

// 播放动画链
chainAnimation->Play();
```

### 示例 7：带延迟的动画

```cpp
// 创建 Animator
auto animator = CREATE_ANIMATOR(context, "DelayedFade");

// 创建动画
auto fadeAnimation = AceType::MakeRefPtr<CurveAnimation<float>>(0.0f, 1.0f, Curves::EASE_IN);
fadeAnimation->AddListener([](float opacity) {
    SetOpacity(opacity);
    RequestFrame();
});

// 配置延迟
animator->AddInterpolator(fadeAnimation);
animator->SetDuration(500);
animator->SetStartDelay(1000); // 延迟 1000ms
animator->Play();
```

### 示例 8：速度控制（Tempo）

```cpp
// 创建 Animator
auto animator = CREATE_ANIMATOR(context, "FastAnimation");

// 创建动画
auto animation = AceType::MakeRefPtr<CurveAnimation<float>>(0.0f, 100.0f, Curves::LINEAR);
animation->AddListener([](float value) {
    SetXPosition(value);
    RequestFrame();
});

// 设置速度为 2 倍
animator->AddInterpolator(animation);
animator->SetDuration(1000);
animator->SetTempo(2.0f); // 2 倍速播放
animator->Play();
```

### 示例 9：全局动画缩放

```cpp
// 设置全局动画缩放为 0.5（所有动画速度减半）
Animator::SetDurationScale(0.5f);

// 后续创建的所有动画都会受影响
auto animator = CREATE_ANIMATOR(context, "ScaledAnimation");
// ...
```

### 示例 10：暂停和恢复

```cpp
// 创建并播放动画
auto animator = CREATE_ANIMATOR(context, "PausableAnimation");
// ... 配置动画 ...
animator->Play();

// 在某个时刻暂停
if (needPause) {
    animator->Pause();
}

// 稍后恢复
if (needResume) {
    animator->Resume();
}
```

---

## 调试指南

### 1. 日志调试

**使用专用日志标签**：
```cpp
#include "base/log/ace_trace.h"

// 动画相关日志
TAG_LOGI(AceLogTag::ACE_ANIMATION, "Animator::Play called");
TAG_LOGD(AceLogTag::ACE_ANIMATION, "Current status: %{public}d", static_cast<int>(status_));

// 插值器日志
TAG_LOGD(AceLogTag::ACE_ANIMATION, "Normalized time: %{public}f", normalizedTime);

// 曲线日志
TAG_LOGD(AceLogTag::ACE_ANIMATION, "Curve value: %{public}f", curve->Move(time));
```

**关键日志点**：
- `Animator::Play()` - 播放动画
- `Animator::OnFrame()` - 帧回调
- `Interpolator::OnNormalizedTimestampChanged()` - 插值更新
- `Motion::Move()` - 运动更新
- `Scheduler::OnVsync()` - VSync 回调

### 2. 状态检查

**检查 Animator 状态**：
```cpp
// 检查是否正在运行
if (animator->IsRunning()) {
    TAG_LOGI(AceLogTag::ACE_ANIMATION, "Animator is running");
}

// 检查是否已停止
if (animator->IsStopped()) {
    TAG_LOGI(AceLogTag::ACE_ANIMATION, "Animator is stopped");
}

// 获取当前状态
auto status = animator->GetStatus();
```

**检查播放时间**：
```cpp
// 获取已播放时间
int64_t playedTime = animator->GetPlayedTime();

// 获取持续时间
int32_t duration = animator->GetDuration();

// 计算进度
float progress = static_cast<float>(playedTime) / duration;
```

### 3. 常见问题定位

#### 问题 1：动画不播放

**检查点**：
- Animator 是否已创建
- Interpolator 是否已添加
- `Play()` 是否已调用
- 是否触发了 Stop/Cancel

**定位方法**：
```cpp
// 在 Animator::Play() 中添加日志
TAG_LOGI(AceLogTag::ACE_ANIMATION,
    "Play called: status=%{public}d, interpolators.size=%{public}zu",
    static_cast<int>(status_), interpolators_.size());

// 检查 Scheduler 是否正常
if (!scheduler_) {
    TAG_LOGE(AceLogTag::ACE_ANIMATION, "No scheduler attached!");
}
```

#### 问题 2：动画速度异常

**检查点**：
- `duration_` 是否正确设置
- `tempo_` 是否正确设置
- 全局 `scale_` 是否被修改
- `startDelay_` 是否导致延迟

**定位方法**：
```cpp
// 打印时间相关信息
TAG_LOGI(AceLogTag::ACE_ANIMATION,
    "Duration: %{public}d, Tempo: %{public}f, Scale: %{public}f, StartDelay: %{public}d",
    duration_, tempo_, scale_, startDelay_);
```

#### 问题 3：动画卡顿

**检查点**：
- 监听器中是否有耗时操作
- 是否频繁触发重绘
- 是否有内存泄漏

**定位方法**：
```cpp
// 在监听器中添加性能日志
auto startTime = std::chrono::high_resolution_clock::now();

// 监听器逻辑
UpdateProperty(value);

auto endTime = std::chrono::high_resolution_clock::now();
auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
TAG_LOGD(AceLogTag::ACE_ANIMATION, "Listener execution time: %{public}lld us", duration.count());
```

#### 问题 4：弹簧动画不停止

**检查点**：
- `valueThreshold_` 和 `velocityThreshold_` 是否合理
- 弹簧参数是否导致持续振荡

**定位方法**：
```cpp
// 在 SpringAnimation::UpdatePosition() 中添加日志
TAG_LOGD(AceLogTag::ACE_ANIMATION,
    "Position: %{public}f, Velocity: %{public}f",
    currentPosition_, currentVelocity_);

// 检查是否完成
if (std::abs(currentVelocity_) < velocityThreshold_ &&
    std::abs(currentPosition_ - endPosition_) < valueThreshold_) {
    TAG_LOGI(AceLogTag::ACE_ANIMATION, "Spring animation completed");
}
```

### 4. 性能分析

**动画帧率监控**：
```cpp
// 在 Scheduler::OnVsync() 中统计帧率
static int64_t lastFrameTime = 0;
static int frameCount = 0;

int64_t currentTime = timestamp;
if (currentTime - lastFrameTime >= 1000000) { // 每秒
    float fps = frameCount * 1000000.0f / (currentTime - lastFrameTime);
    TAG_LOGI(AceLogTag::ACE_ANIMATION, "Current FPS: %{public}f", fps);
    frameCount = 0;
    lastFrameTime = currentTime;
}
frameCount++;
```

---

## 常见问题

### Q1: Animator 和 Interpolator 的区别是什么？

**A**:
- **Animator（控制器）**：管理动画生命周期、时间控制、调度集成
- **Interpolator（插值器）**：负责具体的数值计算和属性更新

**类比**：
- Animator = 导演（控制整个动画流程）
- Interpolator = 演员（执行具体的表演）

### Q2: CurveAnimation 和 KeyframeAnimation 如何选择？

**A**:
- **CurveAnimation**：适合简单的 A → B 过渡
  - 例如：淡入淡出、位移、缩放
  - 只有一个起始值和一个结束值
  - 使用一条曲线控制整个动画

- **KeyframeAnimation**：适合复杂的多段动画
  - 例如：弹跳效果、变速运动
  - 有多个关键点
  - 每个区间可以使用不同的曲线

### Q3: SpringAnimation 和 Motion 有什么区别？

**A**:
- **SpringAnimation**：继承自 `Animation<float>`，可以设置持续时间
- **Motion**：基于物理模拟，无固定持续时间，自动停止

**使用场景**：
- 需要精确控制时间 → 使用 SpringAnimation
- 需要物理真实感 → 使用 Motion（如 SpringMotion）

### Q4: 如何实现动画结束后执行回调？

**A**：有多种方法：

**方法 1：使用 StatusListener**
```cpp
animator->AddStopListener([]() {
    LOGI("Animation stopped");
    // 执行后续逻辑
});
```

**方法 2：检查状态**
```cpp
// 在某个地方定期检查
if (animator->IsStopped()) {
    // 执行后续逻辑
}
```

**方法 3：使用 FillMode + 延迟**
```cpp
animator->SetFillMode(FillMode::FORWARDS);
animator->Play();

// 延迟执行回调
auto delayTask = [&animator]() {
    if (animator->IsStopped()) {
        // 执行回调
    }
};
ScheduleTask(delayTask, animator->GetDuration() + animator->GetStartDelay());
```

### Q5: 如何实现无限循环动画？

**A**：
```cpp
// 方法 1：设置大迭代次数
animator->SetIteration(-1); // -1 表示无限循环
animator->Play();

// 方法 2：在停止监听器中重新播放
animator->AddStopListener([animator]() {
    animator->Play();
});
animator->Play();
```

### Q6: 动画性能优化有哪些方法？

**A**:
1. **减少监听器中的计算**
```cpp
// ❌ 避免在监听器中重计算
animation->AddListener([](float value) {
    auto result = heavyCalculation(value); // 每帧都计算
    UpdateUI(result);
});

// ✅ 预先计算或缓存
animation->AddListener([cachedResult](float value) {
    UpdateUI(cachedResult);
});
```

2. **合并属性更新**
```cpp
// ❌ 多次触发重绘
animation->AddListener([](float value) {
    SetX(value);
    RequestFrame(); // 第一次重绘
    SetY(value);
    RequestFrame(); // 第二次重绘
});

// ✅ 一次更新多个属性
animation->AddListener([](float value) {
    SetX(value);
    SetY(value);
    RequestFrame(); // 只触发一次重绘
});
```

3. **使用合适的曲线**
```cpp
// ✅ 简单动画使用线性曲线（计算快）
auto linearAnimation = AceType::MakeRefPtr<CurveAnimation<float>>(0.0f, 1.0f, Curves::LINEAR);

// ⚠️ 复杂曲线会增加计算开销
customComplexAnimation = AceType::MakeRefPtr<CurveAnimation<float>>(0.0f, 1.0f, customComplexCurve);
```

4. **控制动画数量**
```cpp
// 避免同时运行过多动画
if (activeAnimatorCount > MAX_ANIMATORS) {
    LOGW("Too many active animators");
    return;
}
```

### Q7: 如何实现动画的暂停和恢复？

**A**：
```cpp
// 暂停
animator->Pause();

// 恢复
animator->Resume();

// 检查状态
if (animator->GetStatus() == Animator::Status::PAUSED) {
    LOGI("Animation is paused");
}
```

### Q8: 如何实现动画的倒放？

**A**：有两种方法：

**方法 1：使用 Reverse()**
```cpp
animator->Reverse(); // 反转方向并播放
```

**方法 2：使用 Backward()**
```cpp
animator->Backward(); // 反向播放
```

### Q9: 全局动画缩放有什么作用？

**A**：
```cpp
// 设置全局动画缩放
Animator::SetDurationScale(0.5f); // 所有动画速度减半
```

**应用场景**：
- 开发调试：加快动画速度，快速查看效果
- 辅助功能：为视觉障碍用户提供更慢的动画
- 性能测试：减慢动画速度，观察每一帧

### Q10: 如何实现动画链（依次播放）？

**A**：
```cpp
// 使用 ChainAnimation
auto chainAnimation = AceType::MakeRefPtr<ChainAnimation>();

// 创建多个动画
auto animator1 = CREATE_ANIMATOR(context, "Step1");
// ... 配置 animator1 ...

auto animator2 = CREATE_ANIMATOR(context, "Step2");
// ... 配置 animator2 ...

// 添加到链中
chainAnimation->AddAnimator(animator1);
chainAnimation->AddAnimator(animator2);

// 播放动画链
chainAnimation->Play();
```

---

## 附录

### A. 术语表

| 术语 | 英文 | 描述 |
|-----|------|------|
| 动画控制器 | Animator | 管理动画生命周期的控制器 |
| 插值器 | Interpolator | 基于时间插值的动画 |
| 运动 | Motion | 基于物理模拟的动画 |
| 曲线 | Curve | 定义动画时间-速度关系的曲线 |
| 关键帧 | Keyframe | 动画中的关键时间点 |
| 弹簧动画 | SpringAnimation | 基于弹簧物理模型的动画 |
| 评估器 | Evaluator | 计算两个值之间插值的评估器 |
| 调度器 | Scheduler | 管理动画调度和帧同步 |
| VSync | Vertical Sync | 垂直同步信号 |
| 填充模式 | FillMode | 动画结束后的状态保持方式 |
| 迭代 | Iteration | 动画重复播放次数 |
| 方向 | Direction | 动画播放方向（正向/反向） |

### B. 源码文件索引

| 文件 | 行数 | 描述 |
|-----|------|------|
| `animator.h` | 294 | Animator 类定义 |
| `animator.cpp` | ~900 | Animator 实现 |
| `animation.h` | 63 | Animation 模板基类 |
| `curve_animation.h` | 135 | CurveAnimation 定义 |
| `keyframe_animation.h` | 200 | KeyframeAnimation 定义 |
| `spring_animation.h` | 73 | SpringAnimation 定义 |
| `spring_animation.cpp` | ~150 | SpringAnimation 实现 |
| `property_animation.h` | 76 | PropertyAnimation 定义 |
| `property_animation.cpp` | ~100 | PropertyAnimation 实现 |
| `scheduler.h` | 96 | Scheduler 定义 |
| `scheduler.cpp` | ~200 | Scheduler 实现 |
| `spring_model.h` | 128 | SpringModel 定义 |
| `spring_model.cpp` | ~300 | SpringModel 实现 |
| `svg_animate.h` | 300+ | SVG 动画支持 |

### C. 版本历史

| 版本 | 日期 | 变更 |
|-----|------|------|
| v1.0 | 2026-02-02 | 初始版本 |

---

**文档结束**

> 本文档基于 OpenHarmony ace_engine 源码分析生成，如有错误或遗漏，欢迎指正。
