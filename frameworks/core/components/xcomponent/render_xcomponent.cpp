/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "core/components/xcomponent/render_xcomponent.h"

#include "base/ressched/ressched_report.h"
namespace OHOS::Ace {
namespace {
#ifdef OHOS_PLATFORM
constexpr int64_t INCREASE_CPU_TIME_ONCE = 4000000000; // 4s(unit: ns)
#endif
OH_NativeXComponent_TouchPointToolType ConvertNativeXComponentTouchToolType(const SourceTool& toolType)
{
    switch (toolType) {
        case SourceTool::FINGER:
            return OH_NativeXComponent_TouchPointToolType::OH_NATIVEXCOMPONENT_TOOL_TYPE_FINGER;
        case SourceTool::PEN:
            return OH_NativeXComponent_TouchPointToolType::OH_NATIVEXCOMPONENT_TOOL_TYPE_PEN;
        case SourceTool::RUBBER:
            return OH_NativeXComponent_TouchPointToolType::OH_NATIVEXCOMPONENT_TOOL_TYPE_RUBBER;
        case SourceTool::BRUSH:
            return OH_NativeXComponent_TouchPointToolType::OH_NATIVEXCOMPONENT_TOOL_TYPE_BRUSH;
        case SourceTool::PENCIL:
            return OH_NativeXComponent_TouchPointToolType::OH_NATIVEXCOMPONENT_TOOL_TYPE_PENCIL;
        case SourceTool::AIRBRUSH:
            return OH_NativeXComponent_TouchPointToolType::OH_NATIVEXCOMPONENT_TOOL_TYPE_AIRBRUSH;
        case SourceTool::MOUSE:
            return OH_NativeXComponent_TouchPointToolType::OH_NATIVEXCOMPONENT_TOOL_TYPE_MOUSE;
        case SourceTool::LENS:
            return OH_NativeXComponent_TouchPointToolType::OH_NATIVEXCOMPONENT_TOOL_TYPE_LENS;
        default:
            return OH_NativeXComponent_TouchPointToolType::OH_NATIVEXCOMPONENT_TOOL_TYPE_UNKNOWN;
    }
}
} // namespace
RenderXComponent::RenderXComponent()
{
    Initialize();
}

RenderXComponent::~RenderXComponent()
{
    NativeXComponentDestroy();
}

void RenderXComponent::Initialize()
{
    auto wp = AceType::WeakClaim(this);
    touchRecognizer_ = AceType::MakeRefPtr<RawRecognizer>();
    touchRecognizer_->SetOnTouchDown([wp](const TouchEventInfo& info) {
        auto xcomponent = wp.Upgrade();
        if (xcomponent) {
            xcomponent->HandleTouchEvent(info, TouchType::DOWN);
        }
    });
    touchRecognizer_->SetOnTouchUp([wp](const TouchEventInfo& info) {
        auto xcomponent = wp.Upgrade();
        if (xcomponent) {
            xcomponent->HandleTouchEvent(info, TouchType::UP);
        }
    });
    touchRecognizer_->SetOnTouchMove([wp](const TouchEventInfo& info) {
        auto xcomponent = wp.Upgrade();
        if (xcomponent) {
            xcomponent->HandleTouchEvent(info, TouchType::MOVE);
        }
    });
    touchRecognizer_->SetOnTouchCancel([wp](const TouchEventInfo& info) {
        auto xcomponent = wp.Upgrade();
        if (xcomponent) {
            xcomponent->HandleTouchEvent(info, TouchType::CANCEL);
        }
    });
}

void RenderXComponent::OnTouchTestHit(
    const Offset& coordinateOffset, const TouchRestrict& touchRestrict, TouchTestResult& result)
{
    if (!touchRecognizer_) {
        return;
    }
    touchRecognizer_->SetCoordinateOffset(coordinateOffset);
    result.emplace_back(touchRecognizer_);
}

void RenderXComponent::HandleTouchEvent(const TouchEventInfo& info, const TouchType& touchType)
{
    std::list<TouchLocationInfo> touchInfoList;
#ifdef OHOS_STANDARD_SYSTEM
    touchInfoList = info.GetChangedTouches();
#else
    if (touchType == TouchType::UP || touchType == TouchType::CANCEL) {
        touchInfoList = info.GetChangedTouches();
    } else {
        touchInfoList = info.GetTouches();
    }
#endif
#ifdef OHOS_PLATFORM
    // increase cpu frequency
    if (touchType == TouchType::MOVE) {
        auto currentTime = GetSysTimestamp();
        auto increaseCpuTime = currentTime - startIncreaseTime_;
        if (increaseCpuTime >= INCREASE_CPU_TIME_ONCE) {
            startIncreaseTime_ = currentTime;
            ResSchedReport::GetInstance().ResSchedDataReport("slide_on");
        }
    } else if (touchType == TouchType::UP) {
        startIncreaseTime_ = 0;
        ResSchedReport::GetInstance().ResSchedDataReport("slide_off");
    }
#endif
    if (touchInfoList.empty()) {
        return;
    }
    const auto& locationInfo = touchInfoList.front();
    const auto& screenOffset = locationInfo.GetGlobalLocation();
    const auto& localOffset = locationInfo.GetLocalLocation();
    touchEventPoint_.id = locationInfo.GetFingerId();
    touchEventPoint_.screenX = screenOffset.GetX();
    touchEventPoint_.screenY = screenOffset.GetY();
    touchEventPoint_.x = localOffset.GetX();
    touchEventPoint_.y = localOffset.GetY();
    touchEventPoint_.size = locationInfo.GetSize();
    touchEventPoint_.force = locationInfo.GetForce();
    touchEventPoint_.deviceId = locationInfo.GetTouchDeviceId();
    const auto timeStamp = info.GetTimeStamp().time_since_epoch().count();
    touchEventPoint_.timeStamp = timeStamp;
    touchEventPoint_.type = ConvertNativeXComponentTouchEvent(touchType);
#ifdef OHOS_STANDARD_SYSTEM
    SetTouchPoint(info.GetTouches(), timeStamp, touchType);
#endif
    NativeXComponentDispatchTouchEvent(touchEventPoint_, nativeXComponentTouchPoints_);
}

void RenderXComponent::SetTouchPoint(
    const std::list<TouchLocationInfo>& touchInfoList, const int64_t timeStamp, const TouchType& touchType)
{
    touchEventPoint_.numPoints =
        touchInfoList.size() <= OH_MAX_TOUCH_POINTS_NUMBER ? touchInfoList.size() : OH_MAX_TOUCH_POINTS_NUMBER;
    nativeXComponentTouchPoints_.clear();
    uint32_t i = 0;
    for (auto iterator = touchInfoList.begin(); iterator != touchInfoList.end() && i < OH_MAX_TOUCH_POINTS_NUMBER;
         iterator++) {
        OH_NativeXComponent_TouchPoint ohTouchPoint;
        const auto& pointTouchInfo = *iterator;
        const auto& pointScreenOffset = pointTouchInfo.GetGlobalLocation();
        const auto& pointLocalOffset = pointTouchInfo.GetLocalLocation();
        ohTouchPoint.id = pointTouchInfo.GetFingerId();
        ohTouchPoint.screenX = pointScreenOffset.GetX();
        ohTouchPoint.screenY = pointScreenOffset.GetY();
        ohTouchPoint.x = pointLocalOffset.GetX();
        ohTouchPoint.y = pointLocalOffset.GetY();
        ohTouchPoint.type = ConvertNativeXComponentTouchEvent(touchType);
        ohTouchPoint.size = pointTouchInfo.GetSize();
        ohTouchPoint.force = pointTouchInfo.GetForce();
        ohTouchPoint.timeStamp = timeStamp;
        ohTouchPoint.isPressed = (touchType == TouchType::DOWN);
        touchEventPoint_.touchPoints[i++] = ohTouchPoint;
        // set tiltX, tiltY and sourceToolType
        XComponentTouchPoint xcomponentTouchPoint;
        xcomponentTouchPoint.tiltX = pointTouchInfo.GetTiltX().value_or(0.0f);
        xcomponentTouchPoint.tiltY = pointTouchInfo.GetTiltY().value_or(0.0f);
        xcomponentTouchPoint.sourceToolType = ConvertNativeXComponentTouchToolType(pointTouchInfo.GetSourceTool());
        nativeXComponentTouchPoints_.emplace_back(xcomponentTouchPoint);
    }
    while (i < OH_MAX_TOUCH_POINTS_NUMBER) {
        OH_NativeXComponent_TouchPoint ohTouchPoint;
        ohTouchPoint.id = 0;
        ohTouchPoint.screenX = 0;
        ohTouchPoint.screenY = 0;
        ohTouchPoint.x = 0;
        ohTouchPoint.y = 0;
        ohTouchPoint.type = OH_NativeXComponent_TouchEventType::OH_NATIVEXCOMPONENT_UNKNOWN;
        ohTouchPoint.size = 0;
        ohTouchPoint.force = 0;
        ohTouchPoint.timeStamp = 0;
        ohTouchPoint.isPressed = false;
        touchEventPoint_.touchPoints[i++] = ohTouchPoint;
    }
}

OH_NativeXComponent_TouchEventType RenderXComponent::ConvertNativeXComponentTouchEvent(const TouchType& touchType)
{
    switch (touchType) {
        case TouchType::DOWN:
            return OH_NativeXComponent_TouchEventType::OH_NATIVEXCOMPONENT_DOWN;
        case TouchType::UP:
            return OH_NativeXComponent_TouchEventType::OH_NATIVEXCOMPONENT_UP;
        case TouchType::MOVE:
            return OH_NativeXComponent_TouchEventType::OH_NATIVEXCOMPONENT_MOVE;
        case TouchType::CANCEL:
            return OH_NativeXComponent_TouchEventType::OH_NATIVEXCOMPONENT_CANCEL;
        default:
            return OH_NativeXComponent_TouchEventType::OH_NATIVEXCOMPONENT_UNKNOWN;
    }
}

void RenderXComponent::PushTask(const TaskFunction& func)
{
    tasks_.emplace_back(func);
    MarkNeedRender();
}

void RenderXComponent::Update(const RefPtr<Component>& component)
{
    const RefPtr<XComponentComponent> xcomponent = AceType::DynamicCast<XComponentComponent>(component);
    if (!xcomponent) {
        return;
    }

    textureId_ = xcomponent->GetTextureId();

    const auto& taskPool = xcomponent->GetTaskPool();
    if (taskPool) {
        taskPool->SetRenderNode(AceType::WeakClaim(this));
        pool_ = taskPool;
        tasks_ = std::list<TaskFunction>(taskPool->GetTasks().begin(), taskPool->GetTasks().end());
        taskPool->ClearTasks();
        pool_->SetPushToRenderNodeFunc([weak = AceType::WeakClaim(this)](const TaskFunction& taskFunc) {
            auto client = weak.Upgrade();
            if (client) {
                client->PushTask(taskFunc);
            }
        });
    }

    MarkNeedLayout();
}

void RenderXComponent::PerformLayout()
{
    if (!NeedLayout()) {
        return;
    }

    // render xcomponent do not support child.
    drawSize_ = Size(GetLayoutParam().GetMaxSize().Width(),
        (GetLayoutParam().GetMaxSize().Height() == Size::INFINITE_SIZE) ? Size::INFINITE_SIZE
                                                                        : (GetLayoutParam().GetMaxSize().Height()));
    SetLayoutSize(drawSize_);
    SetNeedLayout(false);
    MarkNeedRender();
}

void RenderXComponent::Paint(RenderContext& context, const Offset& offset)
{
    position_ = GetGlobalOffset();
    if (!isSurfaceInit_) {
        prePosition_ = position_;
        preDrawSize_ = drawSize_;

        NativeXComponentOffset(position_.GetX(), position_.GetY());

        // The first time enter the Paint(), drawSize is (0, 0)
        // If the width or height equal to zero, it will not
        if (NearEqual(drawSize_.Width(), 0) || NearEqual(drawSize_.Height(), 0)) {
            RenderNode::Paint(context, offset);
            return;
        }

        if (xcomponentSizeInitEvent_ && (!drawSize_.IsHeightInfinite())) {
            xcomponentSizeInitEvent_(textureId_, drawSize_.Width(), drawSize_.Height());
            // Save the size in case it changes before OnSurfaceCreated() is called
            initDrawSize_ = drawSize_;
            isSurfaceInit_ = true;
        }
    } else {
        if ((!NearEqual(prePosition_.GetX(), position_.GetX())) ||
            (!NearEqual(prePosition_.GetY(), position_.GetY()))) {
            prePosition_ = position_;
            positionChange_ = true;
        }

        if ((!NearEqual(preDrawSize_.Width(), drawSize_.Width())) ||
            (!NearEqual(preDrawSize_.Height(), drawSize_.Height()))) {
            preDrawSize_ = drawSize_;
            sizeChange_ = true;
        }
    }

    if (positionChange_) {
        positionChange_ = false;
        NativeXComponentOffset(position_.GetX(), position_.GetY());
    }

    if (sizeChange_) {
        sizeChange_ = false;
        if (xcomponentSizeChangeEvent_ && (!drawSize_.IsHeightInfinite())) {
            xcomponentSizeChangeEvent_(textureId_, drawSize_.Width(), drawSize_.Height());
        }
    }

    RenderNode::Paint(context, offset);
}

void RenderXComponent::OnGlobalPositionChanged()
{
    if (SystemProperties::GetExtSurfaceEnabled() && xcomponentPositionChangeEvent_) {
        position_ = GetGlobalOffset();
        xcomponentPositionChangeEvent_(position_.GetX(), position_.GetY());
    }
}

void RenderXComponent::NativeXComponentInit(
    OH_NativeXComponent* nativeXComponent, WeakPtr<NativeXComponentImpl> nativeXComponentImpl)
{
    auto pipelineContext = context_.Upgrade();
    if (!pipelineContext) {
        LOGE("NativeXComponentInit pipelineContext is null");
        return;
    }
    nativeXComponent_ = nativeXComponent;
    nativeXComponentImpl_ = nativeXComponentImpl;

    pipelineContext->GetTaskExecutor()->PostTask(
        [weakNXCompImpl = nativeXComponentImpl_, nXComp = nativeXComponent_, w = initDrawSize_.Width(),
            h = initDrawSize_.Height()] {
            auto nXCompImpl = weakNXCompImpl.Upgrade();
            if (nXComp && nXCompImpl) {
                nXCompImpl->SetXComponentWidth((int)(w));
                nXCompImpl->SetXComponentHeight((int)(h));
                auto surface = const_cast<void*>(nXCompImpl->GetSurface());
                auto callback = nXCompImpl->GetCallback();
                if (callback && callback->OnSurfaceCreated != nullptr) {
                    callback->OnSurfaceCreated(nXComp, surface);
                }
            } else {
                LOGE("Native XComponent nullptr");
            }
        },
        TaskExecutor::TaskType::JS, "ArkUIXComponentInit");
}

void RenderXComponent::NativeXComponentChange()
{
    auto pipelineContext = context_.Upgrade();
    if (!pipelineContext) {
        LOGE("PipelineContext is null");
        return;
    }

    pipelineContext->GetTaskExecutor()->PostTask(
        [weakNXCompImpl = nativeXComponentImpl_, nXComp = nativeXComponent_, w = drawSize_.Width(),
            h = drawSize_.Height()] {
            auto nXCompImpl = weakNXCompImpl.Upgrade();
            if (nXComp && nXCompImpl) {
                nXCompImpl->SetXComponentWidth((int)(w));
                nXCompImpl->SetXComponentHeight((int)(h));
                auto surface = const_cast<void*>(nXCompImpl->GetSurface());
                auto callback = nXCompImpl->GetCallback();
                if (callback && callback->OnSurfaceChanged != nullptr) {
                    callback->OnSurfaceChanged(nXComp, surface);
                }
            } else {
                LOGE("Native XComponent nullptr");
            }
        },
        TaskExecutor::TaskType::JS, "ArkUIXComponentChange");
}

void RenderXComponent::NativeXComponentDestroy()
{
    if (!isSurfaceInit_) {
        return;
    }
    isSurfaceInit_ = false;

    auto pipelineContext = context_.Upgrade();
    if (!pipelineContext) {
        LOGE("NativeXComponentDestroy context null");
        return;
    }

    pipelineContext->GetTaskExecutor()->PostTask(
        [weakNXCompImpl = nativeXComponentImpl_, nXComp = nativeXComponent_] {
            auto nXCompImpl = weakNXCompImpl.Upgrade();
            if (nXComp != nullptr && nXCompImpl) {
                auto surface = const_cast<void*>(nXCompImpl->GetSurface());
                auto callback = nXCompImpl->GetCallback();
                if (callback != nullptr && callback->OnSurfaceDestroyed != nullptr) {
                    callback->OnSurfaceDestroyed(nXComp, surface);
                }
            } else {
                LOGE("Native XComponent nullptr");
            }
        },
        TaskExecutor::TaskType::JS, "ArkUIXComponentDestroy");
}

void RenderXComponent::NativeXComponentDispatchTouchEvent(
    const OH_NativeXComponent_TouchEvent& touchEvent, const std::vector<XComponentTouchPoint>& xComponentTouchPoints)
{
    auto pipelineContext = context_.Upgrade();
    if (!pipelineContext) {
        LOGE("NativeXComponentDispatchTouchEvent context null");
        return;
    }
    pipelineContext->GetTaskExecutor()->PostTask(
        [weakNXCompImpl = nativeXComponentImpl_, nXComp = nativeXComponent_, touchEvent, xComponentTouchPoints] {
            auto nXCompImpl = weakNXCompImpl.Upgrade();
            if (nXComp != nullptr && nXCompImpl) {
                nXCompImpl->SetTouchEvent(touchEvent);
                nXCompImpl->SetTouchPoint(xComponentTouchPoints);
                auto* surface = const_cast<void*>(nXCompImpl->GetSurface());
                const auto* callback = nXCompImpl->GetCallback();
                if (callback != nullptr && callback->DispatchTouchEvent != nullptr) {
                    callback->DispatchTouchEvent(nXComp, surface);
                }
            } else {
                LOGE("Native XComponent nullptr");
            }
        },
        TaskExecutor::TaskType::JS, "ArkUIXComponentDispatchTouchEvent");
}

void RenderXComponent::HandleMouseHoverEvent(MouseState mouseState)
{
    auto pipelineContext = context_.Upgrade();
    if (!pipelineContext) {
        LOGE("NativeXComponentDispatchMouseEvent context null");
        return;
    }
    pipelineContext->GetTaskExecutor()->PostTask(
        [weakNXCompImpl = nativeXComponentImpl_, nXComp = nativeXComponent_, mouseState] {
            auto nXCompImpl = weakNXCompImpl.Upgrade();
            if (nXComp != nullptr && nXCompImpl) {
                bool isHover = static_cast<int>(mouseState);
                auto callback = nXCompImpl->GetMouseEventCallback();
                if (callback != nullptr && callback->DispatchHoverEvent != nullptr) {
                    callback->DispatchHoverEvent(nXComp, isHover);
                }
            } else {
                LOGE("Native XComponent nullptr");
            }
        },
        TaskExecutor::TaskType::JS, "ArkUIXComponentMouseHoverEvent");
}

bool RenderXComponent::HandleMouseEvent(const MouseEvent& event)
{
    OH_NativeXComponent_MouseEvent mouseEventPoint;
    mouseEventPoint.x = event.GetOffset().GetX() - GetCoordinatePoint().GetX();
    mouseEventPoint.y = event.GetOffset().GetY() - GetCoordinatePoint().GetY();
    mouseEventPoint.screenX = event.GetOffset().GetX();
    mouseEventPoint.screenY = event.GetOffset().GetY();
    switch (event.action) {
        case MouseAction::PRESS:
            mouseEventPoint.action = OH_NativeXComponent_MouseEventAction::OH_NATIVEXCOMPONENT_MOUSE_PRESS;
            break;
        case MouseAction::RELEASE:
            mouseEventPoint.action = OH_NativeXComponent_MouseEventAction::OH_NATIVEXCOMPONENT_MOUSE_RELEASE;
            break;
        case MouseAction::MOVE:
            mouseEventPoint.action = OH_NativeXComponent_MouseEventAction::OH_NATIVEXCOMPONENT_MOUSE_MOVE;
            break;
        case MouseAction::CANCEL:
            mouseEventPoint.action = OH_NativeXComponent_MouseEventAction::OH_NATIVEXCOMPONENT_MOUSE_CANCEL;
            break;
        default:
            mouseEventPoint.action = OH_NativeXComponent_MouseEventAction::OH_NATIVEXCOMPONENT_MOUSE_NONE;
            break;
    }
    switch (event.button) {
        case MouseButton::LEFT_BUTTON:
            mouseEventPoint.button = OH_NativeXComponent_MouseEventButton::OH_NATIVEXCOMPONENT_LEFT_BUTTON;
            break;
        case MouseButton::RIGHT_BUTTON:
            mouseEventPoint.button = OH_NativeXComponent_MouseEventButton::OH_NATIVEXCOMPONENT_RIGHT_BUTTON;
            break;
        case MouseButton::MIDDLE_BUTTON:
            mouseEventPoint.button = OH_NativeXComponent_MouseEventButton::OH_NATIVEXCOMPONENT_MIDDLE_BUTTON;
            break;
        case MouseButton::BACK_BUTTON:
            mouseEventPoint.button = OH_NativeXComponent_MouseEventButton::OH_NATIVEXCOMPONENT_BACK_BUTTON;
            break;
        case MouseButton::FORWARD_BUTTON:
            mouseEventPoint.button = OH_NativeXComponent_MouseEventButton::OH_NATIVEXCOMPONENT_FORWARD_BUTTON;
            break;
        default:
            mouseEventPoint.button = OH_NativeXComponent_MouseEventButton::OH_NATIVEXCOMPONENT_NONE_BUTTON;
            break;
    }
    mouseEventPoint.timestamp = event.time.time_since_epoch().count();
    return NativeXComponentDispatchMouseEvent(mouseEventPoint);
}

bool RenderXComponent::NativeXComponentDispatchMouseEvent(const OH_NativeXComponent_MouseEvent& mouseEvent)
{
    auto pipelineContext = context_.Upgrade();
    if (!pipelineContext) {
        LOGE("NativeXComponentDispatchMouseEvent context null");
        return false;
    }
    pipelineContext->GetTaskExecutor()->PostTask(
        [weakNXCompImpl = nativeXComponentImpl_, nXComp = nativeXComponent_, mouseEvent] {
            auto nXCompImpl = weakNXCompImpl.Upgrade();
            if (nXComp != nullptr && nXCompImpl) {
                nXCompImpl->SetMouseEvent(mouseEvent);
                auto surface = const_cast<void*>(nXCompImpl->GetSurface());
                auto callback = nXCompImpl->GetMouseEventCallback();
                if (callback != nullptr && callback->DispatchMouseEvent != nullptr) {
                    callback->DispatchMouseEvent(nXComp, surface);
                }
            } else {
                LOGE("Native XComponent nullptr");
            }
        },
        TaskExecutor::TaskType::JS, "ArkUIXComponentDispatchMouseEvent");
    return true;
}

void RenderXComponent::NativeXComponentOffset(double x, double y)
{
    auto pipelineContext = context_.Upgrade();
    if (!pipelineContext) {
        LOGE("NativeXComponentOffset context null");
        return;
    }
    float scale = pipelineContext->GetViewScale();
    pipelineContext->GetTaskExecutor()->PostTask(
        [weakNXCompImpl = nativeXComponentImpl_, x, y, scale] {
            auto nXCompImpl = weakNXCompImpl.Upgrade();
            if (nXCompImpl) {
                nXCompImpl->SetXComponentOffsetX(x * scale);
                nXCompImpl->SetXComponentOffsetY(y * scale);
            }
        },
        TaskExecutor::TaskType::JS, "ArkUIXComponentOffset");
}
} // namespace OHOS::Ace