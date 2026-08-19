# CAPI 手势接口 UAF 问题 Issue Context

> 文档版本：v1.0
> 更新时间：2026-08-08
> 来源：`docs/context_registry.json` 主题 `CapiGestureDisposeUaf`
> 关联功能域：04-05-07、04-04-06

## 问题概述

CAPI（NDK）手势场景下，业务侧调用 `OH_ArkUI_DisposeGesture` 释放手势后，仍概率性出现被踩内存/Use-After-Free。释放路径仅做了引用计数递减与 `disposeTag` 标记，但未清空对外暴露的 `userData` 指针，且各手势识别器在手势裁决阶段（`TriggerGestureJudgeCallback`）未感知 `disposeTag`，仍继续访问已释放或已失效的资源。

典型表现：
- CAPI 应用 dispose 手势后偶现进程崩溃，堆栈指向手势识别器裁决回调路径
- dispose 与手势事件处理的竞态下，访问到已释放的 `userData`/`FrameNode`/`GestureEventHub`
- 仅 CAPI（`interfaces/native/native_gesture.h`、`node_gesture_modifier.cpp`）路径触发，ArkTS 动态前端不涉及

## 关联模块

| kind | role | name | evidence | confidence |
|------|------|------|----------|------------|
| capability | symptom_surface | 手势识别器（Click/Pan/Pinch/Rotation/Swipe/LongPress Recognizer） | 各识别器 `TriggerGestureJudgeCallback` 入口未拦截 dispose 状态 | verified |
| architecture | root_cause_owner | CAPI 手势 dispose 路径（node_gesture_modifier）+ Gesture::SetUserData（gesture_info.h） | commit diff：dispose 未清空 userData，SetUserData 未同步到 gestureInfo_ | verified |
| capability | fix_location | 各识别器 `TriggerGestureJudgeCallback` 前置 disposeTag 检查 + dispose 清空 userData | commit 8924861586a941b97a3d1786201046b212c5d32b diff | verified |

kind: `component` / `capability` / `architecture`
role: `symptom_surface` / `trigger` / `root_cause_owner` / `fix_location` / `dependency`

## 根因分类

| 根因类别 | 触发条件 | 典型场景 |
|----------|----------|----------|
| dispose 后 userData 悬垂指针未同步清空 | `Gesture::SetUserData` 仅赋值本地 `userData_`，未传播到 `gestureInfo_`；dispose 调 `SetUserData(nullptr)` 无法清空 gestureInfo_ 侧的 userData | CAPI 侧为手势绑定 userData 后调用 `OH_ArkUI_DisposeGesture`，识别器后续仍从 `gestureInfo_->GetUserData()` 取到旧指针 |
| 识别器裁决回调未检查 disposeTag | `TriggerGestureJudgeCallback` 入口直接 `GetAttachedNode().Upgrade()` 访问 FrameNode/GestureEventHub，未先判断手势是否已 dispose | dispose 后手势裁决阶段仍触发回调，访问到已失效的 attached node 或 gesture 资源 |

## 排查路径

### 快速判断

1. 确认崩溃是否发生在 CAPI（NDK）手势路径，且堆栈指向某识别器的 `TriggerGestureJudgeCallback`
2. 确认崩溃前业务侧是否调用过 `OH_ArkUI_DisposeGesture` 或动态移除手势
3. 在 `node_gesture_modifier.cpp` 的 `dispose` 中确认是否同时执行 `SetDisposeTag(true)` + `SetUserData(nullptr)` + `DecRefCount()`
4. 在对应识别器 `TriggerGestureJudgeCallback` 入口确认是否有 `gestureInfo_->GetDisposeTag()` 前置拦截

### 详细排查

#### dispose 后 userData 悬垂指针未同步清空 排查

| 步骤 | 操作 | 预期结果 | 失败则 |
|------|------|----------|--------|
| 1 | 在 `gesture_info.h` 查看 `Gesture::SetUserData` 实现 | 应同时赋值 `userData_` 并向 `gestureInfo_->SetUserData(userData)` 传播 | 若未传播，dispose 清空 gestureInfo_ 无效 |
| 2 | 在 `node_gesture_modifier.cpp` 的 `dispose` 查看是否调用 `SetUserData(nullptr)` | dispose 必须清空 userData，避免悬垂 | 缺失则识别器仍可读到旧 C 侧指针 |
| 3 | 复现时检查崩溃是否访问 `userData` 指向的已释放内存 | dispose 后 userData 应为 nullptr | 命中即为此根因 |

关键代码定位：
- `frameworks/core/components_ng/gestures/gesture_info.h:266-272`：`Gesture::SetUserData`，需向 `gestureInfo_` 传播（修复新增 `if (gestureInfo_) gestureInfo_->SetUserData(userData);`）
- `frameworks/core/interfaces/native/node/node_gesture_modifier.cpp:222-228`：`dispose(ArkUIGesture*)`，依次 `SetDisposeTag(true)` → `SetUserData(nullptr)` → `DecRefCount()`
- `frameworks/core/components_ng/gestures/gesture_info.h:281-286`：`SetDisposeTag` 同样向 `gestureInfo_` 传播

#### 识别器裁决回调未检查 disposeTag 排查

| 步骤 | 操作 | 预期结果 | 失败则 |
|------|------|----------|--------|
| 1 | 在崩溃识别器的 `TriggerGestureJudgeCallback` 入口查看是否有 `gestureInfo_ && gestureInfo_->GetDisposeTag()` 判断 | 已 dispose 应直接 `return GestureJudgeResult::REJECT` | 缺失则继续访问已失效资源 |
| 2 | 排查所有 6 类识别器是否都补齐该检查 | Click/Pan/Pinch/Rotation/Swipe/LongPress 均应覆盖 | 任何一处遗漏即存在残留风险 |
| 3 | 检查 `gestureInfo_` 为 nullptr 的分支 | 应放行（`CONTINUE`），仅拦截已 dispose | nullptr 不应 REJECT |

关键代码定位（修复后均前置 disposeTag 检查）：
- `frameworks/core/components_ng/gestures/recognizers/click_recognizer.cpp:768-771`：`ClickRecognizer::TriggerGestureJudgeCallback`
- `frameworks/core/components_ng/gestures/recognizers/pan_recognizer.cpp:1013-1016`：`PanRecognizer::TriggerGestureJudgeCallback`
- `frameworks/core/components_ng/gestures/recognizers/long_press_recognizer.cpp:596-599`：`LongPressRecognizer::TriggerGestureJudgeCallback`
- `frameworks/core/components_ng/gestures/recognizers/pinch_recognizer.cpp:541-544`：`PinchRecognizer::TriggerGestureJudgeCallback`
- `frameworks/core/components_ng/gestures/recognizers/rotation_recognizer.cpp:470-473`：`RotationRecognizer::TriggerGestureJudgeCallback`
- `frameworks/core/components_ng/gestures/recognizers/swipe_recognizer.cpp:520-523`：`SwipeRecognizer::TriggerGestureJudgeCallback`

## 修复方案

| 根因类别 | 修复策略 | 关键代码改动点 | 修复/缓解变更 | 关系证据 |
|----------|----------|---------------|---------------|----------|
| dispose 后 userData 悬垂指针未同步清空 | `Gesture::SetUserData` 向 `gestureInfo_` 传播；dispose 时显式 `SetUserData(nullptr)` 清空两侧 userData | `gesture_info.h` SetUserData；`node_gesture_modifier.cpp` dispose | 8924861586a941b97a3d1786201046b212c5d32b (fixed) | commit diff：SetUserData 新增 gestureInfo_ 传播分支；dispose 新增 `gestureRef->SetUserData(nullptr)` |
| 识别器裁决回调未检查 disposeTag | 6 类识别器 `TriggerGestureJudgeCallback` 入口前置 `GetDisposeTag()` 检查，已 dispose 则 REJECT | 6 个 recognizer `.cpp` | 8924861586a941b97a3d1786201046b212c5d32b (fixed) | commit diff：每个识别器入口新增 3 行 disposeTag 拦截 |

核心修复代码（识别器侧，以 Click 为例）：
```cpp
GestureJudgeResult ClickRecognizer::TriggerGestureJudgeCallback()
{
    if (gestureInfo_ && gestureInfo_->GetDisposeTag()) {
        return GestureJudgeResult::REJECT;
    }
    auto frameNode = GetAttachedNode().Upgrade();
    ...
}
```

dispose 路径修复（`node_gesture_modifier.cpp:222-228`）：
```cpp
void dispose(ArkUIGesture* recognizer)
{
    Gesture* gestureRef = reinterpret_cast<Gesture*>(recognizer);
    gestureRef->SetDisposeTag(true);
    gestureRef->SetUserData(nullptr);   // 新增：清空 userData，避免悬垂
    gestureRef->DecRefCount();
}
```

## 关联变更

| 变更编号 | 变更简述 | 根因类别 | 变更关系 | 证据 | 确信度 |
|----------|----------|----------|----------|------|--------|
| CHG-01 | dispose 时清空 userData + SetUserData 传播到 gestureInfo_ | dispose 后 userData 悬垂指针未同步清空 | fixed | commit 8924861586a941b97a3d1786201046b212c5d32b diff | verified |
| CHG-02 | 6 类识别器 TriggerGestureJudgeCallback 前置 disposeTag 拦截 | 识别器裁决回调未检查 disposeTag | fixed | commit 8924861586a941b97a3d1786201046b212c5d32b diff | verified |
| CHG-03 | 为各识别器新增 TriggerGestureJudgeCallbackDisposeTag 单元测试 | 识别器裁决回调未检查 disposeTag | follow_up | commit 8924861586a941b97a3d1786201046b212c5d32b diff（click/pan/pinch/rotation/swipe/long_press *_test_ng.cpp） | verified |

## 预防措施

- CAPI dispose 路径必须将所有对外暴露的裸指针（userData 等）一并置空，不能只做引用计数递减
- 任何 `GestureInfo` 暴露给识别器的状态字段（如 disposeTag）变更时，`Gesture` 层 setter 都应同步传播到 `gestureInfo_`
- 新增手势识别器类型时，`TriggerGestureJudgeCallback` 入口必须复用 disposeTag 前置拦截模式
- 代码审查重点：CAPI `dispose`/`remove` 类函数与识别器异步回调之间的生命周期解耦是否完整

## 相关主题

- `docs/kb/capabilities/gesture-modifier.md`：手势 Modifier 代码型 KB（FuncID 04-05-07，含 node_gesture_modifier dispose）
- `docs/kb/capabilities/gesture-capability.md`：手势能力代码型 KB（FuncID 04-04-06，含各识别器与 GestureReferee）
- `docs/kb/capabilities/interaction-normalization.md`：交互归一化代码型 KB（FuncID 04-04-11）