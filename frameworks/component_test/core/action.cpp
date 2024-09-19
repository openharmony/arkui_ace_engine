/*
 * Copyright (C) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "component_test/core/action.h"

#include <chrono>
#include <cmath>

#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::ComponentTest {
namespace {
static void DecomposeTap(EventMatrix& recv, const NG::PointF& point)
{
    constexpr uint32_t fingers = 1;
    constexpr uint32_t steps = 2;
    EventMatrix pointerEventMatrix(fingers, steps);
    pointerEventMatrix.PushEventAction(PointerEventAction { PointerActionState::DOWN, point, TAP_HOLD_MS });
    pointerEventMatrix.PushEventAction(PointerEventAction { PointerActionState::UP, point, 0 });
    recv = std::move(pointerEventMatrix);
}

static void DecomposeDoubleTap(EventMatrix& recv, const NG::PointF& point)
{
    constexpr uint32_t fingers = 1;
    constexpr uint32_t steps = 4;
    EventMatrix pointerEventMatrix(fingers, steps);
    pointerEventMatrix.PushEventAction(PointerEventAction { PointerActionState::DOWN, point, TAP_HOLD_MS });
    pointerEventMatrix.PushEventAction(PointerEventAction { PointerActionState::UP, point, TAP_HOLD_MS });

    pointerEventMatrix.PushEventAction(PointerEventAction { PointerActionState::DOWN, point, TAP_HOLD_MS });
    pointerEventMatrix.PushEventAction(PointerEventAction { PointerActionState::UP, point, 0 });
    recv = std::move(pointerEventMatrix);
}

static void DecomposePress(EventMatrix& recv, const NG::PointF& point, uint32_t duration)
{
    constexpr uint32_t fingers = 1;
    constexpr uint32_t steps = 2;
    EventMatrix pointerEventMatrix(fingers, steps);
    duration = duration > PRESS_HOLD_MS ? duration : PRESS_HOLD_MS;
    pointerEventMatrix.PushEventAction(PointerEventAction { PointerActionState::DOWN, point, duration });
    pointerEventMatrix.PushEventAction(PointerEventAction { PointerActionState::UP, point, 0 });
    recv = std::move(pointerEventMatrix);
}
} // namespace

EventSequenceManager& EventSequenceManager::GetInstance()
{
    static EventSequenceManager instance;
    return instance;
}

void EventSequenceManager::Execute(PointerAction* pointerAction) const
{
    EventMatrix pointerEventMatrix;
    pointerAction->Decompose(pointerEventMatrix);
    pointerAction->DispatchPointerEvent(pointerEventMatrix);
}

void PointerAction::DispatchPointerEvent(const EventMatrix& events)
{
    ComponentTestManagerProxy::ClaimLongOperation();
    uint32_t postDelay = 0;
    for (uint32_t step = 0; step < events.GetSteps(); step++) {
        for (uint32_t finger = 0; finger < events.GetFingers(); finger++) {
            auto pointerEvent = std::make_shared<OHOS::MMI::PointerEvent>();
            pointerEvent->sourceType = OHOS::MMI::PointerEvent::SOURCE_TYPE_TOUCHSCREEN;
            pointerEvent->sourceTool = OHOS::MMI::SourceTool::FINGER;
            pointerEvent->id = finger + 1;
            PointerEventAction& pointerEventAction = events.GetEventAction(finger, step);
            pointerEvent->x = pointerEventAction.point.GetX();
            pointerEvent->y = pointerEventAction.point.GetY();

            switch (pointerEventAction.stage) {
                case PointerActionState::DOWN:
                    pointerEvent->type = OHOS::MMI::TouchType::DOWN;
                    pointerEvent->pointerAction_ = OHOS::MMI::PointerEvent::POINTER_ACTION_DOWN;
                    break;
                case PointerActionState::MOVE:
                    pointerEvent->type = OHOS::MMI::TouchType::MOVE;
                    pointerEvent->pointerAction_ = OHOS::MMI::PointerEvent::POINTER_ACTION_MOVE;
                    break;
                case PointerActionState::UP:
                    pointerEvent->type = OHOS::MMI::TouchType::UP;
                    pointerEvent->pointerAction_ = OHOS::MMI::PointerEvent::POINTER_ACTION_UP;
                    break;
                default:
                    break;
            }
            pointerEvent->size = sizeof(OHOS::MMI::PointerEvent);
            taskExecutor_->PostDelayedTask(
                [pointerEvent]() {
                    struct timespec ts;
                    clock_gettime(CLOCK_MONOTONIC, &ts);
                    std::chrono::duration<int64_t, std::nano> duration(ts.tv_sec * SEC_TO_NANOSEC + ts.tv_nsec);
                    pointerEvent->time = std::chrono::high_resolution_clock::time_point(duration);
                    Platform::EventDispatcher::GetInstance().DispatchTouchEvent(pointerEvent);
                },
                TaskExecutor::TaskType::JS, postDelay, {});
            postDelay += pointerEventAction.holdMs;
        }
    }
    taskExecutor_->PostDelayedTask(
        ComponentTestManagerProxy::LongOperationComplete, TaskExecutor::TaskType::JS, postDelay, {});
}

void ClickAction::Decompose(EventMatrix& recv) const
{
    switch (touchType_) {
        case TouchType::TAP:
            DecomposeTap(recv, point_);
            break;
        case TouchType::DOUBLE_TAP:
            DecomposeDoubleTap(recv, point_);
            break;
        case TouchType::PRESS:
            DecomposePress(recv, point_, duration_);
            break;
        default:
            break;
    }
}

void MoveAction::Decompose(EventMatrix& recv) const
{
    float distanceX = to_.GetX() - from_.GetX();
    float distanceY = to_.GetY() - from_.GetY();
    uint32_t distance = sqrt(distanceX * distanceX + distanceY * distanceY);
    uint32_t timeCostMs = (distance * 1000) / speed_;
    if (distance < 1) {
        return;
    }

    uint32_t intervalMs = timeCostMs / steps_ + 1;
    constexpr uint32_t fingers = 1;
    EventMatrix pointer(fingers, steps_ + 1);
    pointer.PushEventAction(
        PointerEventAction { PointerActionState::DOWN, { from_.GetX(), from_.GetY() }, intervalMs });
    for (uint16_t step = 1; step < steps_; step++) {
        float pointX = from_.GetX() + (distanceX * step) / steps_;
        float pointY = from_.GetY() + (distanceY * step) / steps_;
        pointer.PushEventAction(PointerEventAction { PointerActionState::MOVE, { pointX, pointY }, intervalMs });
    }
    pointer.PushEventAction(PointerEventAction { PointerActionState::UP, { to_.GetX(), to_.GetY() }, 0 });
    if (touchType_ == TouchType::DRAG) {
        pointer.GetEventAction(0, 0).holdMs = PRESS_HOLD_MS;
    }

    recv = std::move(pointer);
}

void PinchAction::Decompose(EventMatrix& recv) const
{
    constexpr uint32_t steps = 50;
    constexpr uint32_t speed = 600;
    constexpr uint32_t fingers = 2;
    constexpr uint32_t actions = steps + 2;
    float centerX = rect_.GetX() + rect_.Width() / 2;
    float centerY = rect_.GetY() + rect_.Height() / 2;
    int32_t distanceFingerMove = abs(centerX - rect_.GetX()) * abs(scale_ - 1);
    std::pair<NG::PointF, NG::PointF> left;
    std::pair<NG::PointF, NG::PointF> right;
    if (scale_ >= 1) {
        left.first = NG::PointF(centerX - PINCH_OUT_POINT_OFFSET, centerY);
        left.second = NG::PointF(centerX - distanceFingerMove - PINCH_OUT_POINT_OFFSET, centerY);
        right.first = NG::PointF(centerX + PINCH_OUT_POINT_OFFSET, centerY);
        right.second = NG::PointF(centerX + distanceFingerMove + PINCH_OUT_POINT_OFFSET, centerY);
    } else {
        left.first = NG::PointF(rect_.Left() + PINCH_IN_POINT_OFFSET, centerY);
        left.second = NG::PointF(rect_.Left() + distanceFingerMove, centerY);
        right.first = NG::PointF(rect_.Right() - PINCH_IN_POINT_OFFSET, centerY);
        right.second = NG::PointF(rect_.Right() - distanceFingerMove - PINCH_IN_POINT_OFFSET, centerY);
    }
    float distance = left.second.GetX() - left.first.GetX();
    float intervalMs = distance * 1000 / speed / steps;
    intervalMs = intervalMs > 0 ? intervalMs : -intervalMs;
    recv = EventMatrix(fingers, actions);
    recv.PushEventAction(
        PointerEventAction { PointerActionState::DOWN, { left.first.GetX(), left.first.GetY() }, intervalMs });
    for (uint16_t step = 1; step <= steps; step++) {
        float pointX = left.first.GetX() + (distance * step) / steps;
        recv.PushEventAction(PointerEventAction { PointerActionState::MOVE, { pointX, centerY }, intervalMs });
    }
    recv.PushEventAction(
        PointerEventAction { PointerActionState::UP, { left.second.GetX(), left.second.GetY() }, intervalMs });

    recv.PushEventAction(
        PointerEventAction { PointerActionState::DOWN, { right.first.GetX(), right.first.GetY() }, intervalMs });
    for (uint16_t step = 1; step <= steps; step++) {
        float pointX = right.first.GetX() - (distance * step) / steps;
        recv.PushEventAction(PointerEventAction { PointerActionState::MOVE, { pointX, centerY }, intervalMs });
    }
    recv.PushEventAction(
        PointerEventAction { PointerActionState::UP, { right.second.GetX(), right.second.GetY() }, 0 });
}

void ScrollAction::Decompose(EventMatrix& recv) const
{
    auto container = AceEngine::Get().GetContainer(ACE_INSTANCE_ID);
    CHECK_NULL_VOID(container);
    auto context = AceType::DynamicCast<NG::PipelineContext>(container->GetPipelineContext());
    CHECK_NULL_VOID(context);

    auto scale = context->GetViewScale();
    auto rootHeight = context->GetRootHeight();
    auto rootWidth = context->GetRootWidth();
    NG::RectF screenRect(0, 0, rootWidth * scale, rootHeight * scale);
    NG::PointF from(screenRect.Width() * HALF, screenRect.Height() * HALF);

    auto deltaX = deltaX_;
    auto deltaY = deltaY_;
    float maxXScrollDelta = screenRect.Width() * QUARTER;
    float maxYScrollDelta = screenRect.Height() * QUARTER;
    std::vector<PointerEventAction> events;
    while (!NearZero(deltaX)) {
        float appliedDeltaX = std::min(std::abs(deltaX), maxXScrollDelta);
        float distanceX = GreatNotEqual(deltaX, 0) > 0 ? -appliedDeltaX : +appliedDeltaX;
        events.emplace_back(PointerEventAction { PointerActionState::DOWN, { from.GetX(), from.GetY() }, TAP_HOLD_MS });
        for (uint16_t step = 1; step < DEFAULT_STEP_CONUT + 1; step++) {
            float pointX = from.GetX() + (distanceX * step) / DEFAULT_STEP_CONUT;
            events.emplace_back(PointerEventAction { PointerActionState::MOVE, { pointX, from.GetY() }, TAP_HOLD_MS });
        }
        events.emplace_back(
            PointerEventAction { PointerActionState::DOWN, { from.GetX() + distanceX, from.GetY() }, TAP_HOLD_MS });
        events.emplace_back(
            PointerEventAction { PointerActionState::UP, { from.GetX() + distanceX, from.GetY() }, SWITCH_HOLD_MS });
        deltaX += distanceX;
    }

    while (!NearZero(deltaY)) {
        float appliedDeltaY = std::min(std::abs(deltaY), maxYScrollDelta);
        float distanceY = GreatNotEqual(deltaY, 0) ? -appliedDeltaY : +appliedDeltaY;
        events.emplace_back(PointerEventAction { PointerActionState::DOWN, { from.GetX(), from.GetY() }, TAP_HOLD_MS });
        for (uint16_t step = 1; step < DEFAULT_STEP_CONUT + 1; step++) {
            float pointY = from.GetY() + (distanceY * step) / DEFAULT_STEP_CONUT;
            events.emplace_back(PointerEventAction { PointerActionState::MOVE, { from.GetX(), pointY }, TAP_HOLD_MS });
        }
        events.emplace_back(
            PointerEventAction { PointerActionState::DOWN, { from.GetX(), from.GetY() + distanceY }, TAP_HOLD_MS });
        events.emplace_back(PointerEventAction { PointerActionState::UP, { from.GetX(), from.GetY() + distanceY }, 0 });
        deltaY += distanceY;
    }

    EventMatrix pointer(1, events.size());
    for (auto& event : events) {
        pointer.PushEventAction(event);
    }

    recv = std::move(pointer);
}

void ScrollToAction::Decompose(EventMatrix& recv) const
{
    auto container = AceEngine::Get().GetContainer(ACE_INSTANCE_ID);
    CHECK_NULL_VOID(container);
    auto context = AceType::DynamicCast<NG::PipelineContext>(container->GetPipelineContext());
    CHECK_NULL_VOID(context);
    auto scale = context->GetViewScale();
    auto rootHeight = context->GetRootHeight();
    auto rootWidth = context->GetRootWidth();
    NG::RectF screenRect(0, 0, rootWidth * scale, rootHeight * scale);
    NG::PointF from(screenRect.Width() * HALF, screenRect.Height() * HALF);
    constexpr uint32_t steps_ = 10;
    auto deltaYTime = deltaY_;
    uint32_t time = 0;
    float maxYScrollDelta = screenRect.Height() * QUARTER;
    if (deltaYTime < 0) {
        while (deltaYTime < 0) {
            float appliedDeltaY = std::min(std::abs(deltaYTime), maxYScrollDelta);
            deltaYTime += appliedDeltaY;
            time++;
        }
    } else {
        while (deltaYTime > 0) {
            float appliedDeltaY = std::min(std::abs(deltaYTime), maxYScrollDelta);
            deltaYTime -= appliedDeltaY;
            time++;
        }
    }
    float timeCostMs = std::abs(deltaY_ * 1000) / speed_;
    float intervalMs = timeCostMs / (steps_ + 1) / time;
    auto deltaY = deltaY_;
    std::vector<PointerEventAction> events;
    while (deltaY != 0) {
        float appliedDeltaY = std::min(std::abs(deltaY), maxYScrollDelta);
        float distanceY = deltaY > 0 ? -appliedDeltaY : +appliedDeltaY;
        events.emplace_back(PointerEventAction { PointerActionState::DOWN, { from.GetX(), from.GetY() }, intervalMs });
        for (uint16_t step = 1; step < steps_ + 1; step++) {
            float pointY = from.GetY() + (distanceY * step) / steps_;
            events.emplace_back(PointerEventAction { PointerActionState::MOVE, { from.GetX(), pointY }, intervalMs });
        }
        events.emplace_back(
            PointerEventAction { PointerActionState::UP, { from.GetX(), from.GetY() + distanceY }, intervalMs });
        deltaY += distanceY;
    }
    EventMatrix pointer(1, events.size());
    for (auto& event : events) {
        pointer.PushEventAction(event);
    }
    recv = std::move(pointer);
}

EventMatrix::EventMatrix(uint32_t fingersNum, uint32_t stepsNum)
{
    fingerNum_ = fingersNum;
    stepNum_ = stepsNum;
    capacity_ = fingerNum_ * stepNum_;
    size_ = 0;
    data_ = std::make_unique<PointerEventAction[]>(capacity_);
}

EventMatrix& EventMatrix::operator=(EventMatrix&& other)
{
    data_ = std::move(other.data_);
    fingerNum_ = other.fingerNum_;
    stepNum_ = other.stepNum_;
    capacity_ = other.capacity_;
    size_ = other.size_;
    return *this;
}

EventMatrix::EventMatrix(EventMatrix&& other)
{
    data_ = std::move(other.data_);
    fingerNum_ = other.fingerNum_;
    stepNum_ = other.stepNum_;
    capacity_ = other.capacity_;
    size_ = other.size_;
}

void EventMatrix::PushEventAction(const PointerEventAction& action)
{
    if (capacity_ == size_) {
        return;
    }
    *(data_.get() + size_) = action;
    size_++;
}

bool EventMatrix::Empty() const
{
    if (size_ == 0) {
        return true;
    }
    return false;
}

PointerEventAction& EventMatrix::GetEventAction(uint32_t fingerIndex, uint32_t stepIndex) const
{
    return *(data_.get() + (fingerIndex * stepNum_ + stepIndex));
}

uint32_t EventMatrix::GetCapacity() const
{
    return capacity_;
}

uint32_t EventMatrix::GetSize() const
{
    return size_;
}

uint32_t EventMatrix::GetSteps() const
{
    return stepNum_;
}

uint32_t EventMatrix::GetFingers() const
{
    return fingerNum_;
}

void CombinedKeysAction::CreateEvents()
{
    for (size_t i = 0; i < codeLength_; i++) {
        events_.push_back(KeyEvent { KeyActionState::DOWN, pressedCodes_[i], 0 });
    }

    for (size_t i = codeLength_ - 1; i >= 0; i--) {
        events_.push_back(KeyEvent { KeyActionState::UP, pressedCodes_[i], 0 });
    }
}

void CombinedKeysAction::Send()
{
    ComponentTestManagerProxy::ClaimLongOperation();
    uint32_t postDelay = 0;
    std::vector<OHOS::MMI::KeyCode> pressedCodesBuff;
    for (auto& event : events_) {
        if (event.stage_ == KeyActionState::DOWN) {
            pressedCodesBuff.push_back(event.code_);
        }
        taskExecutor_->PostDelayedTask(
            [event, pressedCodesBuff]() {
                auto keyEvent = std::make_shared<OHOS::MMI::KeyEvent>();
                keyEvent->code = event.code_;
                keyEvent->action = OHOS::MMI::KeyAction(event.stage_);
                keyEvent->pressedCodes = pressedCodesBuff;
                keyEvent->timeStamp = std::chrono::high_resolution_clock::now();
                std::string keyString = "";
                keyEvent->key = keyString.c_str();
                keyEvent->enableCapsLock_ = false;
                keyEvent->enableNumLock_ = false;
                OHOS::Ace::Platform::EventDispatcher::GetInstance().DispatchKeyEvent(keyEvent);
            },
            TaskExecutor::TaskType::JS, postDelay, {});
        postDelay += TAP_HOLD_MS;
        if (event.stage_ == KeyActionState::UP) {
            pressedCodesBuff.pop_back();
        }
    }
    taskExecutor_->PostDelayedTask(
        ComponentTestManagerProxy::LongOperationComplete, TaskExecutor::TaskType::JS, postDelay, {});
}

SingleKeyAction::SingleKeyAction(OHOS::MMI::KeyCode keyCode) : CombinedKeysAction()
{
    codeLength_ = 1;
    if (!IsSpecialKey(keyCode)) {
        pressedCodes_.push_back(keyCode);
        CreateEvents();
    }
}

SingleKeyAction::SingleKeyAction(const std::vector<OHOS::MMI::KeyCode>& keyCodes)
{
    codeLength_ = keyCodes.size();
    for (auto num : keyCodes) {
        pressedCodes_.push_back(OHOS::MMI::KeyCode(num));
    }
    CopyCreateEvents();
}

SingleKeyAction::SingleKeyAction(std::string& text, std::string& currentText) : CombinedKeysAction()
{
    codeLength_ = text.size();
    CreateClearEvent(currentText);
    for (int i = 0; i < codeLength_; i++) {
        if (text[i] == '\n') {
            CreateEnterEvents();
            continue;
        }
        if (text[i] == '\\') {
            CreateDoubleBackslashEvents();
            continue;
        }
        if (!keyValue[text[i] - KEY_VALUE_START].isShiftPressed) {
            pressedCodes_.push_back(keyValue[text[i] - KEY_VALUE_START].key);
            events_.push_back(KeyEvent { KeyActionState::DOWN, keyValue[text[i] - KEY_VALUE_START].key, 0 });
            events_.push_back(KeyEvent { KeyActionState::UP, keyValue[text[i] - KEY_VALUE_START].key, 0 });
        } else {
            pressedCodes_.push_back(OHOS::MMI::KeyCode::KEY_SHIFT_LEFT);
            pressedCodes_.push_back(OHOS::MMI::KeyCode(keyValue[text[i] - KEY_VALUE_START].key));
            events_.push_back(KeyEvent { KeyActionState::DOWN, OHOS::MMI::KeyCode::KEY_SHIFT_LEFT, 0 });
            events_.push_back(KeyEvent { KeyActionState::DOWN, keyValue[text[i] - KEY_VALUE_START].key, 0 });
            events_.push_back(KeyEvent { KeyActionState::UP, keyValue[text[i] - KEY_VALUE_START].key, 0 });
            events_.push_back(KeyEvent { KeyActionState::UP, OHOS::MMI::KeyCode::KEY_SHIFT_LEFT, 0 });
        }
    }
}

void SingleKeyAction::CopyCreateEvents()
{
    for (size_t i = 0; i < codeLength_; i++) {
        events_.push_back(KeyEvent { KeyActionState::DOWN, pressedCodes_[i], 0 });
        events_.push_back(KeyEvent { KeyActionState::UP, pressedCodes_[i], 0 });
    }
}

void SingleKeyAction::CreateClearEvent(std::string& currentText)
{
    pressedCodes_.push_back(OHOS::MMI::KeyCode::KEY_MOVE_END);
    events_.push_back(KeyEvent { KeyActionState::DOWN, OHOS::MMI::KeyCode::KEY_MOVE_END, 0 });
    events_.push_back(KeyEvent { KeyActionState::UP, OHOS::MMI::KeyCode::KEY_MOVE_END, 0 });
    for (size_t i = 0; i < currentText.length(); i++) {
        pressedCodes_.push_back(OHOS::MMI::KeyCode::KEY_FORWARD_DEL);
        events_.push_back(KeyEvent { KeyActionState::DOWN, OHOS::MMI::KeyCode::KEY_FORWARD_DEL, 0 });
        events_.push_back(KeyEvent { KeyActionState::UP, OHOS::MMI::KeyCode::KEY_FORWARD_DEL, 0 });
    }
}

void SingleKeyAction::CreateEnterEvents()
{
    pressedCodes_.push_back(OHOS::MMI::KeyCode::KEY_ENTER);
    events_.push_back(KeyEvent { KeyActionState::DOWN, OHOS::MMI::KeyCode::KEY_ENTER, 0 });
    events_.push_back(KeyEvent { KeyActionState::UP, OHOS::MMI::KeyCode::KEY_ENTER, 0 });
}

void SingleKeyAction::CreateDoubleBackslashEvents()
{
    pressedCodes_.push_back(OHOS::MMI::KeyCode::KEY_SLASH);
    events_.push_back(KeyEvent { KeyActionState::DOWN, OHOS::MMI::KeyCode::KEY_SLASH, 0 });
    events_.push_back(KeyEvent { KeyActionState::UP, OHOS::MMI::KeyCode::KEY_SLASH, 0 });
}

bool SingleKeyAction::IsSpecialKey(OHOS::MMI::KeyCode keyCode)
{
    OHOS::MMI::KeyCode convertedKeyCode = OHOS::MMI::KeyCode::KEY_UNKNOWN;
    if (keyCode == OHOS::MMI::KeyCode::KEY_STAR) {
        convertedKeyCode = OHOS::MMI::KeyCode::KEY_8;
    } else if (keyCode == OHOS::MMI::KeyCode::KEY_POUND) {
        convertedKeyCode = OHOS::MMI::KeyCode::KEY_9;
    } else if (keyCode == OHOS::MMI::KeyCode::KEY_AT) {
        convertedKeyCode = OHOS::MMI::KeyCode::KEY_2;
    } else if (keyCode == OHOS::MMI::KeyCode::KEY_PLUS) {
        convertedKeyCode = OHOS::MMI::KeyCode::KEY_EQUALS;
    }
    if (convertedKeyCode != OHOS::MMI::KeyCode::KEY_UNKNOWN) {
        pressedCodes_.push_back(OHOS::MMI::KeyCode::KEY_SHIFT_LEFT);
        pressedCodes_.push_back(convertedKeyCode);
        events_.push_back(KeyEvent { KeyActionState::DOWN, OHOS::MMI::KeyCode::KEY_SHIFT_LEFT, 0 });
        events_.push_back(KeyEvent { KeyActionState::DOWN, convertedKeyCode, 0 });
        events_.push_back(KeyEvent { KeyActionState::UP, convertedKeyCode, 0 });
        events_.push_back(KeyEvent { KeyActionState::UP, OHOS::MMI::KeyCode::KEY_SHIFT_LEFT, 0 });
        return true;
    }
    return false;
}
} // namespace OHOS::Ace::ComponentTest
