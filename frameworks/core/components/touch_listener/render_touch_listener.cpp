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

#include "render_touch_listener.h"

#include "core/components/touch_listener/touch_listener_component.h"

namespace OHOS::Ace {

RenderTouchListener::RenderTouchListener() : rawRecognizer_(AceType::MakeRefPtr<RawRecognizer>()) {}

RefPtr<RenderNode> RenderTouchListener::Create()
{
    return AceType::MakeRefPtr<RenderTouchListener>();
}

void RenderTouchListener::Update(const RefPtr<Component>& component)
{
    auto touchComponent = AceType::DynamicCast<TouchListenerComponent>(component);
    ACE_DCHECK(touchComponent);
    responseRegion_ = touchComponent->GetResponseRegion();
    isResponseRegion_ = touchComponent->IsResponseRegion();
    auto context = context_.Upgrade();
    if (context && context->GetIsDeclarative()) {
        onTouchEventCallback_ = AceSyncEvent<void(const std::shared_ptr<TouchEventInfo>&)>::Create(
            touchComponent->GetOnTouchId(), context_);
        return;
    }

    for (uint32_t eventStage = 0; eventStage < EventStage::SIZE; eventStage++) {
        for (uint32_t touchEventType = 0; touchEventType < EventType::SIZE; touchEventType++) {
            auto& onEventId = touchComponent->GetEvent(EventAction::ON, eventStage, touchEventType);
            if (!onEventId.IsEmpty()) {
                rawRecognizer_->SetOnEventCallback(
                    AceAsyncEvent<void(const TouchEventInfo&)>::Create(onEventId, context_), eventStage,
                    touchEventType);
            }
            auto& catchEventId = touchComponent->GetEvent(EventAction::CATCH, eventStage, touchEventType);
            if (!catchEventId.IsEmpty()) {
                rawRecognizer_->SetCatchEventCallback(
                    AceAsyncEvent<void()>::Create(catchEventId, context_), eventStage, touchEventType);
            }
        }

        auto& onEventId = touchComponent->GetSwipeEvent(EventAction::ON, eventStage);
        if (!onEventId.IsEmpty()) {
            if (!swipeRecognizer_) {
                swipeRecognizer_ = AceType::MakeRefPtr<SwipeRecognizer>();
            }
            swipeRecognizer_->SetSwipeCallback(
                AceAsyncEvent<void(const SwipeEventInfo&)>::Create(onEventId, context_), eventStage);
        }
        auto& catchEventId = touchComponent->GetSwipeEvent(EventAction::CATCH, eventStage);
        if (!catchEventId.IsEmpty()) {
            if (!swipeRecognizer_) {
                swipeRecognizer_ = AceType::MakeRefPtr<SwipeRecognizer>();
            }
            swipeRecognizer_->SetCatchEventCallback(
                AceAsyncEvent<void(const SwipeEventInfo&)>::Create(catchEventId, context_), eventStage);
        }
    }
    touchable_ = touchComponent->IsTouchable();
    isVisible_ = touchComponent->IsVisible();
    interceptTouchEvent_ = !touchable_;

    if (!touchComponent->GetEvent(EventAction::CATCH, EventStage::CAPTURE, EventType::TOUCH_DOWN).IsEmpty()) {
        EventMarker eventMarker("catchEvent");
        auto event = AceAsyncEvent<void()>::Create(eventMarker, context_);
        rawRecognizer_->SetCatchEventCallback(event, EventStage::CAPTURE, EventType::TOUCH_UP);
        rawRecognizer_->SetCatchEventCallback(event, EventStage::CAPTURE, EventType::TOUCH_MOVE);
    }
}

void RenderTouchListener::OnTouchTestHit(
    const Offset& coordinateOffset, const TouchRestrict& touchRestrict, TouchTestResult& result)
{
    auto context = context_.Upgrade();
    if (context && context->GetIsDeclarative()) {
        coordinateOffset_ = coordinateOffset;
        result.emplace_back(Claim(this));
        return;
    }
    rawRecognizer_->SetCoordinateOffset(coordinateOffset);
    result.emplace_back(rawRecognizer_);
    if (swipeRecognizer_) {
        result.emplace_back(swipeRecognizer_);
    }
}

bool RenderTouchListener::GetVisible() const
{
    return RenderNode::GetVisible() && isVisible_;
}

bool RenderTouchListener::DispatchEvent(const TouchEvent& point)
{
    return true;
}

bool RenderTouchListener::HandleEvent(const TouchEvent& point)
{
    bool isPropagation = true;
    auto context = context_.Upgrade();
    if (context && context->GetIsDeclarative()) {
        if (point.type == TouchType::DOWN) {
            touchPointMap_[point.id] = point;
            isPropagation = TriggerTouchCallBack(point);
        } else if (point.type == TouchType::UP) {
            isPropagation = TriggerTouchCallBack(point);
            touchPointMap_.erase(point.id);
        } else {
            for (const auto& pointPair : touchPointMap_) {
                if (pointPair.first == point.id && (pointPair.second.x != point.x || pointPair.second.y != point.y)) {
                    touchPointMap_[point.id] = point;
                    isPropagation = TriggerTouchCallBack(point);
                    break;
                }
            }
        }
    }
    return isPropagation;
}

bool RenderTouchListener::TriggerTouchCallBack(const TouchEvent& changedPoint)
{
    LOGI("Trigger touch callback");
    if (!onTouchEventCallback_ && !onTouchFocusEventCallback_) {
        return true;
    }
    auto event = std::make_shared<TouchEventInfo>("touchEvent");
    event->SetTimeStamp(changedPoint.time);
    TouchLocationInfo changedInfo("onTouch", changedPoint.id);
    float localX = changedPoint.x - coordinateOffset_.GetX();
    float localY = changedPoint.y - coordinateOffset_.GetY();
    changedInfo.SetLocalLocation(Offset(localX, localY));
    changedInfo.SetGlobalLocation(Offset(changedPoint.x, changedPoint.y));
    changedInfo.SetScreenLocation(Offset(changedPoint.screenX, changedPoint.screenY));
    changedInfo.SetTouchType(changedPoint.type);
    changedInfo.SetForce(changedPoint.force);
    if (changedPoint.tiltX.has_value()) {
        changedInfo.SetTiltX(changedPoint.tiltX.value());
    }
    if (changedPoint.tiltY.has_value()) {
        changedInfo.SetTiltY(changedPoint.tiltY.value());
    }
    changedInfo.SetSourceTool(changedPoint.sourceTool);
    event->AddChangedTouchLocationInfo(std::move(changedInfo));

    // all fingers collection
    for (const auto& pointPair : touchPointMap_) {
        float globalX = pointPair.second.x;
        float globalY = pointPair.second.y;
        float screenX = pointPair.second.screenX;
        float screenY = pointPair.second.screenY;
        float localX = pointPair.second.x - coordinateOffset_.GetX();
        float localY = pointPair.second.y - coordinateOffset_.GetY();
        TouchLocationInfo info("onTouch", pointPair.second.id);
        info.SetGlobalLocation(Offset(globalX, globalY));
        info.SetLocalLocation(Offset(localX, localY));
        info.SetScreenLocation(Offset(screenX, screenY));
        info.SetTouchType(pointPair.second.type);
        info.SetForce(pointPair.second.force);
        if (pointPair.second.tiltX.has_value()) {
            info.SetTiltX(pointPair.second.tiltX.value());
        }
        if (pointPair.second.tiltY.has_value()) {
            info.SetTiltY(pointPair.second.tiltY.value());
        }
        info.SetSourceTool(pointPair.second.sourceTool);
        event->AddTouchLocationInfo(std::move(info));
    }
    event->SetSourceDevice(changedPoint.sourceType);
    event->SetForce(changedPoint.force);
    if (changedPoint.tiltX.has_value()) {
        event->SetTiltX(changedPoint.tiltX.value());
    }
    if (changedPoint.tiltY.has_value()) {
        event->SetTiltY(changedPoint.tiltY.value());
    }
    event->SetSourceTool(changedPoint.sourceTool);
    if (onTouchEventCallback_) {
        onTouchEventCallback_(event);
    }
    if (onTouchFocusEventCallback_ && changedPoint.type == TouchType::DOWN) {
        onTouchFocusEventCallback_();
    }
    return event->IsStopPropagation() ? false : true;
}

} // namespace OHOS::Ace