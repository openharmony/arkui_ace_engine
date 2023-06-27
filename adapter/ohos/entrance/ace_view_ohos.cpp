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

#include "flutter/fml/message_loop.h"
#include "flutter/shell/platform/ohos/platform_task_runner_adapter.h"

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
#include "core/common/container_scope.h"
#include "core/common/thread_checker.h"
#include "core/components/theme/app_theme.h"
#include "core/components/theme/theme_manager.h"
#include "core/event/axis_event.h"
#include "core/event/key_event.h"
#include "core/event/mouse_event.h"
#include "core/event/touch_event.h"
#include "core/image/image_cache.h"

namespace OHOS::Ace::Platform {
namespace {

constexpr int32_t ROTATION_DIVISOR = 64;

} // namespace

AceViewOhos* AceViewOhos::CreateView(int32_t instanceId, bool useCurrentEventRunner, bool usePlatformThread)
{
    auto* aceView = new AceViewOhos(instanceId, FlutterThreadModel::CreateThreadModel(useCurrentEventRunner,
                                                    !usePlatformThread, !SystemProperties::GetRosenBackendEnabled()));
    if (aceView != nullptr) {
        aceView->IncRefCount();
    }
    return aceView;
}

AceViewOhos::AceViewOhos(int32_t id, std::unique_ptr<FlutterThreadModel> threadModel)
    : instanceId_(id), threadModel_(std::move(threadModel))
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
    CHECK_NULL_VOID_NOLOG(view);
    view->NotifySurfacePositionChanged(posX, posY);
}

void AceViewOhos::SetViewportMetrics(AceViewOhos* view, const ViewportConfig& config)
{
    CHECK_NULL_VOID_NOLOG(view);
    view->NotifyDensityChanged(config.Density());
}

void AceViewOhos::DispatchTouchEvent(AceViewOhos* view, const std::shared_ptr<MMI::PointerEvent>& pointerEvent)
{
    CHECK_NULL_VOID_NOLOG(view);
    LogPointInfo(pointerEvent);
    if (pointerEvent->GetSourceType() == MMI::PointerEvent::SOURCE_TYPE_MOUSE) {
        // mouse event
        if (pointerEvent->GetPointerAction() >= MMI::PointerEvent::POINTER_ACTION_AXIS_BEGIN &&
            pointerEvent->GetPointerAction() <= MMI::PointerEvent::POINTER_ACTION_AXIS_END) {
            LOGD("ProcessAxisEvent");
            view->ProcessAxisEvent(pointerEvent);
        } else {
            LOGD("ProcessMouseEvent");
#ifdef ENABLE_DRAG_FRAMEWORK
            view->ProcessDragEvent(pointerEvent);
#endif // ENABLE_DRAG_FRAMEWORK
            view->ProcessMouseEvent(pointerEvent);
        }
    } else {
        // touch event
        LOGD("ProcessTouchEvent");
#ifdef ENABLE_DRAG_FRAMEWORK
        view->ProcessDragEvent(pointerEvent);
#endif // ENABLE_DRAG_FRAMEWORK
        view->ProcessTouchEvent(pointerEvent);
    }
}

bool AceViewOhos::DispatchKeyEvent(AceViewOhos* view, const std::shared_ptr<MMI::KeyEvent>& keyEvent)
{
    CHECK_NULL_RETURN(view, false);
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
    LOGD("Launch shell holder.");
}

void AceViewOhos::ProcessTouchEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent)
{
    CHECK_NULL_VOID_NOLOG(pointerEvent);
    TouchEvent touchPoint = ConvertTouchEvent(pointerEvent);
    if (SystemProperties::GetDebugEnabled()) {
        ACE_SCOPED_TRACE("ProcessTouchEvent pointX=%f pointY=%f type=%d timeStamp=%lld id=%d", touchPoint.x,
            touchPoint.y, (int)touchPoint.type, touchPoint.time.time_since_epoch().count(), touchPoint.id);
    }
    auto markProcess = [pointerEvent]() {
        CHECK_NULL_VOID_NOLOG(pointerEvent);
        LOGD("Mark %{public}d id Touch Event Processed", pointerEvent->GetPointerId());
        pointerEvent->MarkProcessed();
    };
    if (touchPoint.type != TouchType::UNKNOWN) {
        if (touchEventCallback_) {
            touchEventCallback_(touchPoint, markProcess);
        }
    } else {
        LOGW("Unknown event.");
    }
}

#ifdef ENABLE_DRAG_FRAMEWORK
void AceViewOhos::ProcessDragEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent)
{
    MMI::PointerEvent::PointerItem pointerItem;
    pointerEvent->GetPointerItem(pointerEvent->GetPointerId(), pointerItem);
    DragEventAction action;
    int32_t orgAction = pointerEvent->GetPointerAction();
    switch (orgAction) {
        case OHOS::MMI::PointerEvent::POINTER_ACTION_PULL_MOVE: {
            action = DragEventAction::DRAG_EVENT_MOVE;
            ProcessDragEvent(pointerItem.GetWindowX(), pointerItem.GetWindowY(), action);
            break;
        }
        case OHOS::MMI::PointerEvent::POINTER_ACTION_PULL_UP: {
            action = DragEventAction::DRAG_EVENT_END;
            ProcessDragEvent(pointerItem.GetWindowX(), pointerItem.GetWindowY(), action);
            break;
        }
        case OHOS::MMI::PointerEvent::POINTER_ACTION_PULL_IN_WINDOW: {
            action = DragEventAction::DRAG_EVENT_START;
            ProcessDragEvent(pointerItem.GetDisplayX(), pointerItem.GetDisplayY(), action);
            break;
        }
        case OHOS::MMI::PointerEvent::POINTER_ACTION_PULL_OUT_WINDOW: {
            action = DragEventAction::DRAG_EVENT_OUT;
            ProcessDragEvent(pointerItem.GetDisplayX(), pointerItem.GetDisplayY(), action);
            break;
        }
        default:
            LOGD("unknown type %{public}d", orgAction);
            break;
    }
}
#endif // ENABLE_DRAG_FRAMEWORK

void AceViewOhos::ProcessDragEvent(int32_t x, int32_t y, const DragEventAction& action)
{
    LOGD("ProcessDragEvent");
    CHECK_NULL_VOID_NOLOG(dragEventCallback_);
    dragEventCallback_(x, y, action);
}

void AceViewOhos::ProcessMouseEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent)
{
    MouseEvent event;
    if (pointerEvent) {
        ConvertMouseEvent(pointerEvent, event);
    }
    auto markProcess = [pointerEvent]() {
        CHECK_NULL_VOID_NOLOG(pointerEvent);
        LOGD("Mark %{public}d id Mouse Event Processed", pointerEvent->GetPointerId());
        pointerEvent->MarkProcessed();
    };

    CHECK_NULL_VOID_NOLOG(mouseEventCallback_);
    mouseEventCallback_(event, markProcess);
}

void AceViewOhos::ProcessAxisEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent)
{
    AxisEvent event;
    if (pointerEvent) {
        ConvertAxisEvent(pointerEvent, event);
    }
    auto markProcess = [pointerEvent]() {
        CHECK_NULL_VOID_NOLOG(pointerEvent);
        LOGD("Mark %{public}d id Axis Event Processed", pointerEvent->GetPointerId());
        pointerEvent->MarkProcessed();
    };

    CHECK_NULL_VOID_NOLOG(axisEventCallback_);
    axisEventCallback_(event, markProcess);
}

bool AceViewOhos::ProcessKeyEvent(const std::shared_ptr<MMI::KeyEvent>& keyEvent)
{
    CHECK_NULL_RETURN_NOLOG(keyEventCallback_, false);
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
    CHECK_NULL_RETURN_NOLOG(rotationEventCallBack_, false);
    RotationEvent event { .value = rotationValue * ROTATION_DIVISOR };
    return rotationEventCallBack_(event);
}

bool AceViewOhos::Dump(const std::vector<std::string>& params)
{
    if (params.empty() || params[0] != "-drawcmd") {
        LOGE("Unsupported parameters.");
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