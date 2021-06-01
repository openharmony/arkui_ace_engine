/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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
#include "core/event/ace_event_helper.h"

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
    auto context = context_.Upgrade();
    if (context && context->GetIsDeclarative()) {
        onTouchEventCallback_ = AceAsyncEvent<void(const std::shared_ptr<TouchCallBackInfo>&)>::Create(
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
    SetOnSwipe(AceAsyncEvent<void(const SwipeEventInfo&)>::Create(touchComponent->GetOnSwipeId(), context_));
}

void RenderTouchListener::OnTouchTestHit(
    const Offset& coordinateOffset, const TouchRestrict& touchRestrict, TouchTestResult& result)
{
    LOGD("render touch listener: on touch test hit!");
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

bool RenderTouchListener::DispatchEvent(const TouchPoint& point)
{
    return true;
}

bool RenderTouchListener::HandleEvent(const TouchPoint& point)
{
    auto context = context_.Upgrade();
    if (context && context->GetIsDeclarative() && onTouchEventCallback_) {
        auto event = std::make_shared<TouchCallBackInfo>(point.type);
        event->SetScreenX(point.x);
        event->SetScreenY(point.y);
        event->SetLocalX(point.x - coordinateOffset_.GetX());
        event->SetLocalY(point.y - coordinateOffset_.GetY());
        event->SetTimeStamp(point.time);
        event->SetPressure(point.pressure);
        event->SetDeviceId(point.deviceId);
        onTouchEventCallback_(event);
    }
    return true;
}

} // namespace OHOS::Ace