/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "adapter/ohos/entrance/ace_view_ohos.h"

#include "adapter/ohos/entrance/ace_container.h"
#include "adapter/ohos/entrance/mmi_event_convertor.h"
#include "base/log/dump_log.h"
#include "core/common/transform/input_compatible_manager.h"
#include "core/event/event_info_convertor.h"

namespace OHOS::Ace::Platform {
namespace {

constexpr int32_t ROTATION_DIVISOR = 64;

bool IsMMIMouseScrollBegin(const AxisEvent& event)
{
    if (event.action != AxisAction::BEGIN ||
        event.sourceType != SourceType::MOUSE ||
        event.sourceTool != SourceTool::MOUSE) {
        return false;
    }
    return !(NearZero(event.horizontalAxis) && NearZero(event.verticalAxis));
}
} // namespace

RefPtr<AceViewOhos> AceViewOhos::CreateView(int32_t instanceId, bool useCurrentEventRunner, bool usePlatformThread)
{
    return AceType::MakeRefPtr<AceViewOhos>(
        instanceId, ThreadModelImpl::CreateThreadModel(
                        useCurrentEventRunner, !usePlatformThread, !SystemProperties::GetRosenBackendEnabled()));
}

AceViewOhos::AceViewOhos(int32_t id, std::unique_ptr<ThreadModelImpl> threadModelImpl)
    : instanceId_(id), threadModelImpl_(std::move(threadModelImpl))
{}

void AceViewOhos::SurfaceCreated(const RefPtr<AceViewOhos>& view, OHOS::sptr<OHOS::Rosen::Window> window)
{
    CHECK_NULL_VOID(window);
    CHECK_NULL_VOID(view);
}

void AceViewOhos::ChangeViewSize(const RefPtr<AceViewOhos>& view, int32_t width, int32_t height)
{
    CHECK_NULL_VOID(view);
    view->ChangeSize(width, height);
}

void AceViewOhos::SurfaceChanged(const RefPtr<AceViewOhos>& view, int32_t width, int32_t height, int32_t orientation,
    WindowSizeChangeReason type, const std::shared_ptr<Rosen::RSTransaction>& rsTransaction)
{
    CHECK_NULL_VOID(view);

    view->NotifySurfaceChanged(width, height, type, rsTransaction);

    auto instanceId = view->GetInstanceId();
    auto container = Platform::AceContainer::GetContainer(instanceId);
    if (container) {
        auto pipelineContext = container->GetPipelineContext();
        CHECK_NULL_VOID(pipelineContext);
        pipelineContext->HideOverlays();
    }
}

void AceViewOhos::SurfacePositionChanged(const RefPtr<AceViewOhos>& view, int32_t posX, int32_t posY)
{
    CHECK_NULL_VOID(view);
    view->NotifySurfacePositionChanged(posX, posY);
}

void AceViewOhos::SetViewportMetrics(const RefPtr<AceViewOhos>& view, const ViewportConfig& config)
{
    CHECK_NULL_VOID(view);
    view->NotifyDensityChanged(config.Density());
}

void AceViewOhos::TransformHintChanged(const RefPtr<AceViewOhos>& view, uint32_t transform)
{
    CHECK_NULL_VOID(view);
    view->NotifyTransformHintChanged(transform);
}

bool IsAxisEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent)
{
    return pointerEvent->GetAxes() != 0;
}

void AceViewOhos::HandleMouseEvent(const RefPtr<AceViewOhos>& view,
    const std::shared_ptr<MMI::PointerEvent>& pointerEvent, const RefPtr<OHOS::Ace::NG::FrameNode>& node,
    int32_t pointerAction, bool isInjected, int32_t toolType)
{
    if ((pointerAction >= MMI::PointerEvent::POINTER_ACTION_AXIS_BEGIN &&
            pointerAction <= MMI::PointerEvent::POINTER_ACTION_AXIS_END) ||
        (pointerAction >= MMI::PointerEvent::POINTER_ACTION_ROTATE_BEGIN &&
            pointerAction <= MMI::PointerEvent::POINTER_ACTION_ROTATE_END) ||
        (toolType == MMI::PointerEvent::TOOL_TYPE_TOUCHPAD &&
            pointerAction == MMI::PointerEvent::POINTER_ACTION_CANCEL) ||
        (pointerAction == MMI::PointerEvent::POINTER_ACTION_CANCEL && IsAxisEvent(pointerEvent))) {
        view->ProcessAxisEvent(pointerEvent, node, isInjected);
    } else {
        view->ProcessDragEvent(pointerEvent, node);
        view->ProcessMouseEvent(pointerEvent, node, isInjected);
    }
}

void AceViewOhos::DispatchTouchEvent(const RefPtr<AceViewOhos>& view,
    const std::shared_ptr<MMI::PointerEvent>& pointerEvent, const RefPtr<OHOS::Ace::NG::FrameNode>& node,
    const std::function<void()>& callback, bool isInjected)
{
    if (!pointerEvent) {
        TAG_LOGE(AceLogTag::ACE_INPUTTRACKING, "DispatchTouchEvent pointerEvent is null return.");
        return;
    }
    if (!view) {
        MMI::InputManager::GetInstance()->MarkProcessed(
            pointerEvent->GetId(), pointerEvent->GetActionTime(), pointerEvent->IsMarkEnabled());
        TAG_LOGE(AceLogTag::ACE_INPUTTRACKING, "DispatchTouchEvent eventId:%{public}d aceView is null return.",
            pointerEvent->GetId());
        return;
    }
    auto instanceId = view->GetInstanceId();
    LogPointInfo(pointerEvent, instanceId);
    DispatchEventToPerf(pointerEvent);
    int32_t pointerAction = pointerEvent->GetPointerAction();
    auto container = Platform::AceContainer::GetContainer(instanceId);
    if (!container) {
        MMI::InputManager::GetInstance()->MarkProcessed(
            pointerEvent->GetId(), pointerEvent->GetActionTime(), pointerEvent->IsMarkEnabled());
        TAG_LOGE(AceLogTag::ACE_INPUTTRACKING, "DispatchTouchEvent eventId:%{public}d container is null return.",
            pointerEvent->GetId());
        return;
    }
    container->SetCurPointerEvent(pointerEvent);
    if (pointerEvent->GetSourceType() == MMI::PointerEvent::SOURCE_TYPE_JOYSTICK) {
        view->ProcessFocusAxisEvent(pointerEvent);
    }

    if (pointerEvent->GetSourceType() == MMI::PointerEvent::SOURCE_TYPE_MOUSE) {
        int32_t toolType = MMI::PointerEvent::TOOL_TYPE_MOUSE;
        if (!GetPointerEventToolType(pointerEvent, toolType)) {
            return;
        }
        // mouse event
        HandleMouseEvent(view, pointerEvent, node, pointerAction, isInjected, toolType);
    } else if (pointerEvent->GetSourceType() == MMI::PointerEvent::SOURCE_TYPE_CROWN) {
        view->ProcessDigitalCrownEvent(pointerEvent, isInjected);
    } else {
        // touch event
        view->ProcessDragEvent(pointerEvent, node);
        view->ProcessTouchEvent(pointerEvent, node, callback, isInjected);
    }
}

void AceViewOhos::DispatchEventToPerf(const std::shared_ptr<MMI::PointerEvent>& pointerEvent)
{
    CHECK_NULL_VOID(pointerEvent);
    static bool isFirstMove = false;
    PerfMonitor* pMonitor = PerfMonitor::GetPerfMonitor();
    if (pMonitor == nullptr) {
        return;
    }
    uint64_t inputTime = pointerEvent->GetSensorInputTime() * US_TO_MS;
    if (inputTime <= 0) {
        inputTime = pointerEvent->GetActionTime() * US_TO_MS;
    }
    if (inputTime <= 0) {
        return;
    }
    PerfActionType inputType = UNKNOWN_ACTION;
    PerfSourceType sourceType = UNKNOWN_SOURCE;
    if (pointerEvent->GetSourceType() == MMI::PointerEvent::SOURCE_TYPE_MOUSE) {
        sourceType = PERF_MOUSE_EVENT;
    } else if (pointerEvent->GetSourceType() == MMI::PointerEvent::SOURCE_TYPE_TOUCHSCREEN) {
        sourceType = PERF_TOUCH_EVENT;
    } else if (pointerEvent->GetSourceType() == MMI::PointerEvent::SOURCE_TYPE_TOUCHPAD) {
        sourceType = PERF_TOUCH_PAD;
    } else if (pointerEvent->GetSourceType() == MMI::PointerEvent::SOURCE_TYPE_JOYSTICK) {
        sourceType = PERF_JOY_STICK;
    }
    int32_t pointerAction = pointerEvent->GetPointerAction();
    if (pointerAction == MMI::PointerEvent::POINTER_ACTION_DOWN
        || pointerAction == MMI::PointerEvent::POINTER_ACTION_BUTTON_DOWN
        || pointerAction == MMI::PointerEvent::POINTER_ACTION_AXIS_BEGIN
        || pointerAction == MMI::PointerEvent::POINTER_ACTION_ROTATE_BEGIN) {
        inputType = LAST_DOWN;
        isFirstMove = true;
    } else if (pointerAction == MMI::PointerEvent::POINTER_ACTION_UP
        || pointerAction == MMI::PointerEvent::POINTER_ACTION_BUTTON_UP
        || pointerAction == MMI::PointerEvent::POINTER_ACTION_AXIS_END
        || pointerAction == MMI::PointerEvent::POINTER_ACTION_ROTATE_END) {
        inputType = LAST_UP;
        isFirstMove = false;
    } else if (isFirstMove && (pointerAction == MMI::PointerEvent::POINTER_ACTION_MOVE
        || pointerAction == MMI::PointerEvent::POINTER_ACTION_AXIS_UPDATE
        || pointerAction == MMI::PointerEvent::POINTER_ACTION_ROTATE_UPDATE)) {
        inputType = FIRST_MOVE;
        isFirstMove = false;
    }
    pMonitor->RecordInputEvent(inputType, sourceType, inputTime);
}

void AceViewOhos::DispatchEventToPerf(const std::shared_ptr<MMI::KeyEvent>& keyEvent)
{
    CHECK_NULL_VOID(keyEvent);
    int32_t keyCode = keyEvent->GetKeyCode();
    if (keyCode != MMI::KeyEvent::KEYCODE_VOLUME_DOWN
        && keyCode != MMI::KeyEvent::KEYCODE_VOLUME_UP
        && keyCode != MMI::KeyEvent::KEYCODE_POWER
        && keyCode != MMI::KeyEvent::KEYCODE_META_LEFT
        && keyCode != MMI::KeyEvent::KEYCODE_ESCAPE) {
        return;
    }
    PerfMonitor* pMonitor = PerfMonitor::GetPerfMonitor();
    if (pMonitor == nullptr) {
        return;
    }
    PerfActionType inputType = UNKNOWN_ACTION;
    int32_t action = keyEvent->GetKeyAction();
    if (action == MMI::KeyEvent::KEY_ACTION_UP) {
        inputType = LAST_UP;
    } else if (action == MMI::KeyEvent::KEY_ACTION_DOWN) {
        inputType = LAST_DOWN;
    }
    PerfSourceType sourceType = PERF_KEY_EVENT;
    auto keyItem = keyEvent->GetKeyItem();
    if (keyItem.has_value()) {
        int64_t inputTime = keyItem->GetDownTime() * US_TO_MS;
        pMonitor->RecordInputEvent(inputType, sourceType, inputTime);
    } else {
        TAG_LOGE(AceLogTag::ACE_INPUTTRACKING, "DispatchEventToPerf keyItem is invalid.");
    }
}

bool AceViewOhos::DispatchKeyEvent(const RefPtr<AceViewOhos>& view,
    const std::shared_ptr<MMI::KeyEvent>& keyEvent, bool isPreIme)
{
    CHECK_NULL_RETURN(view, false);
    DispatchEventToPerf(keyEvent);
    return view->ProcessKeyEvent(keyEvent, isPreIme);
}

bool AceViewOhos::DispatchRotationEvent(const RefPtr<AceViewOhos>& view, float rotationValue)
{
    CHECK_NULL_RETURN(view, false);
    return view->ProcessRotationEvent(rotationValue);
}

void AceViewOhos::RegisterTouchEventCallback(TouchEventCallback&& callback)
{
    ACE_DCHECK(callback);
    touchEventCallback_ = std::move(callback);
}

void AceViewOhos::RegisterDragEventCallback(DragEventCallBack&& callback)
{
    ACE_DCHECK(callback);
    dragEventCallback_ = std::move(callback);
}

void AceViewOhos::RegisterKeyEventCallback(KeyEventCallback&& callback)
{
    ACE_DCHECK(callback);
    keyEventCallback_ = std::move(callback);
}

void AceViewOhos::RegisterNonPointerEventCallback(NonPointerEventCallback&& callback)
{
    ACE_DCHECK(callback);
    nonPointerEventCallback_ = std::move(callback);
}

void AceViewOhos::RegisterCrownEventCallback(CrownEventCallback&& callback)
{
    ACE_DCHECK(callback);
    crownEventCallback_ = std::move(callback);
}

void AceViewOhos::RegisterMouseEventCallback(MouseEventCallback&& callback)
{
    ACE_DCHECK(callback);
    mouseEventCallback_ = std::move(callback);
}

void AceViewOhos::RegisterAxisEventCallback(AxisEventCallback&& callback)
{
    ACE_DCHECK(callback);
    axisEventCallback_ = std::move(callback);
}

void AceViewOhos::RegisterRotationEventCallback(RotationEventCallBack&& callback)
{
    ACE_DCHECK(callback);
    rotationEventCallBack_ = std::move(callback);
}

void AceViewOhos::Launch()
{
}

void AceViewOhos::ProcessTouchEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent,
    const RefPtr<OHOS::Ace::NG::FrameNode>& node, const std::function<void()>& callback, bool isInjected)
{
    if (!pointerEvent) {
        TAG_LOGE(AceLogTag::ACE_INPUTTRACKING, "ProcessTouchEvent pointerEvent is null return.");
        return;
    }
    TouchEvent touchPoint = ConvertTouchEvent(pointerEvent);
    touchPoint.SetIsInjected(isInjected);
    if (SystemProperties::GetDebugEnabled()) {
        ACE_SCOPED_TRACE("ProcessTouchEvent pointX=%f pointY=%f type=%d timeStamp=%lld id=%d eventId=%d", touchPoint.x,
            touchPoint.y, (int)touchPoint.type, touchPoint.time.time_since_epoch().count(), touchPoint.id,
            touchPoint.touchEventId);
    }
    auto markProcess = [touchPoint, finallyCallback = callback, enabled = pointerEvent->IsMarkEnabled()]() {
        MMI::InputManager::GetInstance()->MarkProcessed(touchPoint.touchEventId,
            std::chrono::duration_cast<std::chrono::microseconds>(touchPoint.time.time_since_epoch()).count(),
            enabled);
        if (finallyCallback) {
            finallyCallback();
        }
    };
    if (touchPoint.type == TouchType::UNKNOWN) {
        TAG_LOGE(AceLogTag::ACE_INPUTTRACKING, "ProcessTouchEvent pointerEvent action is unknown return.");
        markProcess();
        return;
    }
    CHECK_NULL_VOID(touchEventCallback_);
    touchEventCallback_(touchPoint, markProcess, node);
}

void AceViewOhos::ProcessDragEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent,
    const RefPtr<OHOS::Ace::NG::FrameNode>& node)
{
    DragEventAction action;
    DragPointerEvent event;
    ConvertPointerEvent(pointerEvent, event);
    CHECK_NULL_VOID(dragEventCallback_);
    int32_t orgAction = pointerEvent->GetPointerAction();
    switch (orgAction) {
        case OHOS::MMI::PointerEvent::POINTER_ACTION_PULL_MOVE: {
            action = DragEventAction::DRAG_EVENT_MOVE;
            dragEventCallback_(event, action, node);
            break;
        }
        case OHOS::MMI::PointerEvent::POINTER_ACTION_PULL_UP: {
            action = DragEventAction::DRAG_EVENT_END;
            dragEventCallback_(event, action, node);
            break;
        }
        case OHOS::MMI::PointerEvent::POINTER_ACTION_PULL_IN_WINDOW: {
            action = DragEventAction::DRAG_EVENT_START;
            dragEventCallback_(event, action, node);
            break;
        }
        case OHOS::MMI::PointerEvent::POINTER_ACTION_PULL_OUT_WINDOW: {
            action = DragEventAction::DRAG_EVENT_OUT;
            dragEventCallback_(event, action, node);
            break;
        }
        case OHOS::MMI::PointerEvent::POINTER_ACTION_PULL_CANCEL: {
            action = DragEventAction::DRAG_EVENT_PULL_CANCEL;
            dragEventCallback_(event, action, node);
            break;
        }
        case OHOS::MMI::PointerEvent::POINTER_ACTION_PULL_THROW: {
            action = DragEventAction::DRAG_EVENT_PULL_THROW;
            dragEventCallback_(event, action, node);
            break;
        }
        default:
            break;
    }
}

void AceViewOhos::ProcessDragEvent(int32_t x, int32_t y, const DragEventAction& action,
    const RefPtr<OHOS::Ace::NG::FrameNode>& node)
{
    CHECK_NULL_VOID(dragEventCallback_);
    dragEventCallback_(DragPointerEvent(x, y), action, node);
}

void AceViewOhos::ProcessMouseEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent,
    const RefPtr<OHOS::Ace::NG::FrameNode>& node, bool isInjected)
{
    MouseEvent event;
    bool markEnabled = true;
    if (pointerEvent) {
        auto container = Platform::AceContainer::GetContainer(instanceId_);
        CHECK_NULL_VOID(container);
        ConvertMouseEvent(pointerEvent, event, container->IsSceneBoardWindow());
        markEnabled = pointerEvent->IsMarkEnabled();
    }
    event.isInjected = isInjected;
    if (SystemProperties::GetDebugEnabled()) {
        ACE_SCOPED_TRACE("ProcessMouseEvent pointX=%f pointY=%f type=%d timeStamp=%lld id=%d eventId=%d", event.x,
            event.y, (int)event.action, event.time.time_since_epoch().count(), event.id, event.touchEventId);
    }
    auto markProcess = [event, markEnabled]() {
        MMI::InputManager::GetInstance()->MarkProcessed(event.touchEventId,
            std::chrono::duration_cast<std::chrono::microseconds>(event.time.time_since_epoch()).count(),
            markEnabled);
    };

    if (InputCompatibleManager::GetInstance().IsCompatibleConvertingEnabledFor(
        Kit::InputCompatibleSource::LEFT_PRESS) &&
        ProcessMouseEventWithTouch(pointerEvent, event, node, markProcess)) {
        return;
    }
    CHECK_NULL_VOID(mouseEventCallback_);
    mouseEventCallback_(event, markProcess, node);
}

bool AceViewOhos::ProcessMouseEventWithTouch(const std::shared_ptr<MMI::PointerEvent>& pointerEvent,
    const MouseEvent& event, const RefPtr<OHOS::Ace::NG::FrameNode>& node, const std::function<void()>& markProcess)
{
    if (event.button == MouseButton::LEFT_BUTTON) {
        // Only process PRESS/MOVE/RELEASE/CANCEL event
        switch (pointerEvent->GetPointerAction()) {
            case OHOS::MMI::PointerEvent::POINTER_ACTION_BUTTON_DOWN:
            case OHOS::MMI::PointerEvent::POINTER_ACTION_BUTTON_UP:
            case OHOS::MMI::PointerEvent::POINTER_ACTION_CANCEL:
            case OHOS::MMI::PointerEvent::POINTER_ACTION_MOVE:
                break;
            default:
                return false;
        }
        TouchEvent touchEvent = event.CreateTouchPoint();
        touchEvent.SetSourceType(SourceType::TOUCH);
        CHECK_NULL_RETURN(touchEventCallback_, false);
        touchEventCallback_(touchEvent, markProcess, node);
        return true;
    } else {
        return false;
    }
}

void AceViewOhos::ProcessAxisEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent,
    const RefPtr<OHOS::Ace::NG::FrameNode>& node, bool isInjected)
{
    if (InputCompatibleManager::GetInstance().IsCompatibleConvertingEnabledFor(
        Kit::InputCompatibleSource::SCROLL_AXIS_EVENT)) {
        if (ProcessAxisEventWithTouch(pointerEvent, node, isInjected)) {
            return;
        }
    }
    CHECK_NULL_VOID(axisEventCallback_);
    AxisEvent event;
    event.isInjected = isInjected;
    if (!pointerEvent) {
        axisEventCallback_(event, nullptr, node);
        return;
    }

    ConvertAxisEvent(pointerEvent, event);
    auto markProcess = [event, enabled = pointerEvent->IsMarkEnabled()]() {
        MMI::InputManager::GetInstance()->MarkProcessed(event.touchEventId,
            std::chrono::duration_cast<std::chrono::microseconds>(event.time.time_since_epoch()).count(),
            enabled);
    };

    /* The first step of axis event of mouse is equivalent to touch event START + UPDATE.
     * Create a fake UPDATE event here to adapt to axis event of mouse.
     * e.g {START, END} turns into {START, UPDATE, END}.
     */
    if (IsMMIMouseScrollBegin(event)) {
        auto fakeAxisStart = std::make_shared<MMI::PointerEvent>(*pointerEvent);
        fakeAxisStart->SetAxisValue(MMI::PointerEvent::AxisType::AXIS_TYPE_SCROLL_VERTICAL, 0.0);
        fakeAxisStart->SetAxisValue(MMI::PointerEvent::AxisType::AXIS_TYPE_SCROLL_HORIZONTAL, 0.0);
        ConvertAxisEvent(fakeAxisStart, event);
        axisEventCallback_(event, nullptr, node);

        auto fakeAxisUpdate = std::make_shared<MMI::PointerEvent>(*pointerEvent);
        fakeAxisUpdate->SetPointerAction(MMI::PointerEvent::POINTER_ACTION_AXIS_UPDATE);
        ConvertAxisEvent(fakeAxisUpdate, event);
    }
    axisEventCallback_(event, markProcess, node);
}

bool AceViewOhos::ProcessAxisEventWithTouch(const std::shared_ptr<MMI::PointerEvent>& pointerEvent,
    const RefPtr<OHOS::Ace::NG::FrameNode>& node, bool isInjected)
{
    if (pointerEvent->HasAxis(MMI::PointerEvent::AxisType::AXIS_TYPE_ROTATE)) {
        return false;
    }
    if (pointerEvent->HasAxis(MMI::PointerEvent::AxisType::AXIS_TYPE_PINCH)) {
        return false;
    }
    TouchEvent event;
    event.isInjected = isInjected;

    if (pointerEvent->GetPointerAction() == MMI::PointerEvent::POINTER_ACTION_AXIS_BEGIN) {
        // The first step of axis event of mouse is equivalent to touch event START + UPDATE.
        // Create a fake UPDATE event here to adapt to axis event of mouse.
        // e.g {START, END} turns into {START, UPDATE, END}.
        auto fakeAxisRawEvt = std::make_shared<MMI::PointerEvent>(*pointerEvent);
        double axisScrollVertBak = fakeAxisRawEvt->GetAxisValue(MMI::PointerEvent::AxisType::AXIS_TYPE_SCROLL_VERTICAL);
        double axisScrollHoriBak =
            fakeAxisRawEvt->GetAxisValue(MMI::PointerEvent::AxisType::AXIS_TYPE_SCROLL_HORIZONTAL);
        fakeAxisRawEvt->SetAxisValue(MMI::PointerEvent::AxisType::AXIS_TYPE_SCROLL_VERTICAL, 0.0);
        fakeAxisRawEvt->SetAxisValue(MMI::PointerEvent::AxisType::AXIS_TYPE_SCROLL_HORIZONTAL, 0.0);
        ConvertAxisEventToTouchEvent(fakeAxisRawEvt, event, axisFakePntEvt_);
        // fakeAxisRawEvt aciton will be update lately, use original pointerEvent.
        event.SetPointerEvent(pointerEvent);
        touchEventCallback_(event, nullptr, node);
        fakeAxisRawEvt->SetAxisValue(MMI::PointerEvent::AxisType::AXIS_TYPE_SCROLL_VERTICAL, axisScrollVertBak);
        fakeAxisRawEvt->SetAxisValue(MMI::PointerEvent::AxisType::AXIS_TYPE_SCROLL_HORIZONTAL, axisScrollHoriBak);
        fakeAxisRawEvt->SetPointerAction(MMI::PointerEvent::POINTER_ACTION_AXIS_UPDATE);
        ConvertAxisEventToTouchEvent(fakeAxisRawEvt, event, axisFakePntEvt_);
    } else {
        ConvertAxisEventToTouchEvent(pointerEvent, event, axisFakePntEvt_);
    }

    auto markProcess = [event, enabled = pointerEvent->IsMarkEnabled()]() {
        MMI::InputManager::GetInstance()->MarkProcessed(event.touchEventId,
            std::chrono::duration_cast<std::chrono::microseconds>(event.time.time_since_epoch()).count(), enabled);
    };
    CHECK_NULL_RETURN(touchEventCallback_, false);
    touchEventCallback_(event, markProcess, node);
    return true;
}

bool AceViewOhos::ProcessKeyEvent(const std::shared_ptr<MMI::KeyEvent>& keyEvent, bool isPreIme)
{
    CHECK_NULL_RETURN(nonPointerEventCallback_, false);
    KeyEvent event;
    ConvertKeyEvent(keyEvent, event);
    event.isPreIme = isPreIme;
    return nonPointerEventCallback_(event, nullptr);
}

bool AceViewOhos::ProcessFocusAxisEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent)
{
    CHECK_NULL_RETURN(nonPointerEventCallback_, false);
    NG::FocusAxisEvent event;
    ConvertFocusAxisEvent(pointerEvent, event);
    auto markProcess = [event, enabled = pointerEvent->IsMarkEnabled()]() {
        MMI::InputManager::GetInstance()->MarkProcessed(event.touchEventId,
            std::chrono::duration_cast<std::chrono::microseconds>(event.time.time_since_epoch()).count(),
            enabled);
    };
    return nonPointerEventCallback_(event, std::move(markProcess));
}

void AceViewOhos::ProcessDigitalCrownEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent,
    bool isInjected)
{
    CrownEvent event;
    ConvertCrownEvent(pointerEvent, event);
    event.isInjected = isInjected;
    TAG_LOGI(AceLogTag::ACE_INPUTTRACKING, "crown event: action:%{public}d, AV:%{public}f, degree:%{public}f",
        event.action, event.angularVelocity, event.degree);

    auto markProcess = [event, enabled = pointerEvent->IsMarkEnabled()]() {
        MMI::InputManager::GetInstance()->MarkProcessed(event.touchEventId,
            std::chrono::duration_cast<std::chrono::microseconds>(event.timeStamp.time_since_epoch()).count(),
            enabled);
    };
    CHECK_NULL_VOID(crownEventCallback_);
    crownEventCallback_(event, markProcess);
}

const void* AceViewOhos::GetNativeWindowById(uint64_t textureId)
{
    return nullptr;
}

bool AceViewOhos::ProcessRotationEvent(float rotationValue)
{
    CHECK_NULL_RETURN(rotationEventCallBack_, false);
    RotationEvent event { .value = rotationValue * ROTATION_DIVISOR };
    return rotationEventCallBack_(event);
}

bool AceViewOhos::Dump(const std::vector<std::string>& params)
{
    if (params.empty() || params[0] != "-drawcmd") {
        return false;
    }
    if (DumpLog::GetInstance().GetDumpFile()) {
        DumpLog::GetInstance().AddDesc("Dump draw command not support on this version.");
        DumpLog::GetInstance().Print(0, "Info:", 0);
        return true;
    }
    return false;
}

uint32_t AceViewOhos::GetBackgroundColor()
{
    return Color::WHITE.GetValue();
}

} // namespace OHOS::Ace::Platform
