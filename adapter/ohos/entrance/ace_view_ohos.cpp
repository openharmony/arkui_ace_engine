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

#include <memory>
#include "adapter/ohos/entrance/ace_container.h"
#include "adapter/ohos/entrance/mmi_event_convertor.h"
#include "base/log/ace_trace.h"
#include "base/log/dump_log.h"
#include "base/log/event_report.h"
#include "base/log/log.h"
#include "base/utils/macros.h"
#include "base/utils/system_properties.h"
#include "base/utils/utils.h"
#include "core/common/ace_engine.h"
#include "core/components/theme/theme_manager.h"
#include "core/event/axis_event.h"
#include "core/event/key_event.h"
#include "core/event/mouse_event.h"
#include "core/event/pointer_event.h"
#include "core/event/touch_event.h"

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

AceViewOhos* AceViewOhos::CreateView(int32_t instanceId, bool useCurrentEventRunner, bool usePlatformThread)
{
    auto* aceView =
        new AceViewOhos(instanceId, ThreadModelImpl::CreateThreadModel(useCurrentEventRunner, !usePlatformThread,
            !SystemProperties::GetRosenBackendEnabled()));
    if (aceView != nullptr) {
        aceView->IncRefCount();
    }
    return aceView;
}

AceViewOhos::AceViewOhos(int32_t id, std::unique_ptr<ThreadModelImpl> threadModelImpl)
    : instanceId_(id), threadModelImpl_(std::move(threadModelImpl))
{}

void AceViewOhos::SurfaceCreated(AceViewOhos* view, OHOS::sptr<OHOS::Rosen::Window> window)
{
    CHECK_NULL_VOID(window);
    CHECK_NULL_VOID(view);
}

void AceViewOhos::SurfaceChanged(AceViewOhos* view, int32_t width, int32_t height, int32_t orientation,
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

void AceViewOhos::SurfacePositionChanged(AceViewOhos* view, int32_t posX, int32_t posY)
{
    CHECK_NULL_VOID(view);
    view->NotifySurfacePositionChanged(posX, posY);
}

void AceViewOhos::SetViewportMetrics(AceViewOhos* view, const ViewportConfig& config)
{
    CHECK_NULL_VOID(view);
    view->NotifyDensityChanged(config.Density());
}

void AceViewOhos::DispatchTouchEvent(AceViewOhos* view, const std::shared_ptr<MMI::PointerEvent>& pointerEvent,
    const RefPtr<OHOS::Ace::NG::FrameNode>& node, const std::function<void()>& callback)
{
    CHECK_NULL_VOID(view);
    CHECK_NULL_VOID(pointerEvent);
    auto instanceId = view->GetInstanceId();
    LogPointInfo(pointerEvent, instanceId);
    DispatchEventToPerf(pointerEvent);
    int32_t pointerAction = pointerEvent->GetPointerAction();

    if (pointerEvent->GetSourceType() == MMI::PointerEvent::SOURCE_TYPE_MOUSE) {
        // mouse event
        if (pointerAction >= MMI::PointerEvent::POINTER_ACTION_AXIS_BEGIN &&
            pointerAction <= MMI::PointerEvent::POINTER_ACTION_AXIS_END) {
            view->ProcessAxisEvent(pointerEvent, node);
        } else {
            view->ProcessDragEvent(pointerEvent);
            view->ProcessMouseEvent(pointerEvent, node);
        }
    } else {
        // touch event
        view->ProcessDragEvent(pointerEvent);
        int32_t instanceId = view->GetInstanceId();
        auto container = Platform::AceContainer::GetContainer(instanceId);
        CHECK_NULL_VOID(container);
        if (container->IsScenceBoardWindow() &&
            (pointerAction == MMI::PointerEvent::POINTER_ACTION_PULL_MOVE ||
            pointerAction == MMI::PointerEvent::POINTER_ACTION_PULL_UP)) {
            view->ProcessMouseEvent(pointerEvent, node);
        } else {
            view->ProcessTouchEvent(pointerEvent, node, callback);
        }
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
    int64_t inputTime = pointerEvent->GetSensorInputTime() * US_TO_MS;
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
        || pointerAction == MMI::PointerEvent::POINTER_ACTION_AXIS_BEGIN) {
        inputType = LAST_DOWN;
        isFirstMove = true;
    } else if (pointerAction == MMI::PointerEvent::POINTER_ACTION_UP
        || pointerAction == MMI::PointerEvent::POINTER_ACTION_BUTTON_UP
        || pointerAction == MMI::PointerEvent::POINTER_ACTION_AXIS_END) {
        inputType = LAST_UP;
        isFirstMove = false;
    } else if (isFirstMove && (pointerAction == MMI::PointerEvent::POINTER_ACTION_MOVE
        || pointerAction == MMI::PointerEvent::POINTER_ACTION_AXIS_UPDATE)) {
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
    int64_t inputTime = (keyEvent->GetKeyItem())->GetDownTime() * US_TO_MS;
    pMonitor->RecordInputEvent(inputType, sourceType, inputTime);
}

bool AceViewOhos::DispatchKeyEvent(AceViewOhos* view, const std::shared_ptr<MMI::KeyEvent>& keyEvent)
{
    CHECK_NULL_RETURN(view, false);
    DispatchEventToPerf(keyEvent);
    return view->ProcessKeyEvent(keyEvent);
}

bool AceViewOhos::DispatchRotationEvent(AceViewOhos* view, float rotationValue)
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
    const RefPtr<OHOS::Ace::NG::FrameNode>& node, const std::function<void()>& callback)
{
    CHECK_NULL_VOID(pointerEvent);
    TouchEvent touchPoint = ConvertTouchEvent(pointerEvent);
    if (SystemProperties::GetDebugEnabled()) {
        ACE_SCOPED_TRACE("ProcessTouchEvent pointX=%f pointY=%f type=%d timeStamp=%lld id=%d", touchPoint.x,
            touchPoint.y, (int)touchPoint.type, touchPoint.time.time_since_epoch().count(), touchPoint.id);
    }
    auto markProcess = [pointerEvent, finallyCallback = callback]() {
        CHECK_NULL_VOID(pointerEvent);
        if (pointerEvent->GetPointerAction() != MMI::PointerEvent::POINTER_ACTION_MOVE) {
            TAG_LOGI(AceLogTag::ACE_INPUTTRACKING, "touchEvent markProcessed in ace_view, eventInfo: id:%{public}d",
                pointerEvent->GetId());
        }
        pointerEvent->MarkProcessed();
        if (finallyCallback) {
            finallyCallback();
        }
    };
    if (touchPoint.type != TouchType::UNKNOWN) {
        if (touchEventCallback_) {
            touchEventCallback_(touchPoint, markProcess, node);
        }
    }
}

void AceViewOhos::ProcessDragEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent)
{
    DragEventAction action;
    PointerEvent event;
    ConvertPointerEvent(pointerEvent, event);
    CHECK_NULL_VOID(dragEventCallback_);
    int32_t orgAction = pointerEvent->GetPointerAction();
    switch (orgAction) {
        case OHOS::MMI::PointerEvent::POINTER_ACTION_PULL_MOVE: {
            action = DragEventAction::DRAG_EVENT_MOVE;
            event.x = event.windowX;
            event.y = event.windowY;
            dragEventCallback_(event, action);
            break;
        }
        case OHOS::MMI::PointerEvent::POINTER_ACTION_PULL_UP: {
            action = DragEventAction::DRAG_EVENT_END;
            event.x = event.windowX;
            event.y = event.windowY;
            dragEventCallback_(event, action);
            break;
        }
        case OHOS::MMI::PointerEvent::POINTER_ACTION_PULL_IN_WINDOW: {
            action = DragEventAction::DRAG_EVENT_START;
            event.x = event.displayX;
            event.y = event.displayY;
            dragEventCallback_(event, action);
            break;
        }
        case OHOS::MMI::PointerEvent::POINTER_ACTION_PULL_OUT_WINDOW: {
            action = DragEventAction::DRAG_EVENT_OUT;
            event.x = event.displayX;
            event.y = event.displayY;
            dragEventCallback_(event, action);
            break;
        }
        default:
            break;
    }
}

void AceViewOhos::ProcessDragEvent(int32_t x, int32_t y, const DragEventAction& action)
{
    CHECK_NULL_VOID(dragEventCallback_);
    dragEventCallback_(PointerEvent(x, y), action);
}

void AceViewOhos::ProcessMouseEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent,
    const RefPtr<OHOS::Ace::NG::FrameNode>& node)
{
    MouseEvent event;
    if (pointerEvent) {
        auto container = Platform::AceContainer::GetContainer(instanceId_);
        CHECK_NULL_VOID(container);
        ConvertMouseEvent(pointerEvent, event, container->IsScenceBoardWindow());
    }
    auto markProcess = [pointerEvent]() {
        CHECK_NULL_VOID(pointerEvent);
        pointerEvent->MarkProcessed();
    };

    CHECK_NULL_VOID(mouseEventCallback_);
    mouseEventCallback_(event, markProcess, node);
}

void AceViewOhos::ProcessAxisEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent,
    const RefPtr<OHOS::Ace::NG::FrameNode>& node)
{
    CHECK_NULL_VOID(axisEventCallback_);
    AxisEvent event;
    if (!pointerEvent) {
        axisEventCallback_(event, nullptr, node);
        return;
    }

    auto markProcess = [pointerEvent]() {
        pointerEvent->MarkProcessed();
    };
    ConvertAxisEvent(pointerEvent, event);

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

bool AceViewOhos::ProcessKeyEvent(const std::shared_ptr<MMI::KeyEvent>& keyEvent)
{
    CHECK_NULL_RETURN(keyEventCallback_, false);
    KeyEvent event;
    ConvertKeyEvent(keyEvent, event);
    return keyEventCallback_(event);
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
