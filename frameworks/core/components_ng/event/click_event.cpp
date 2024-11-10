/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/event/click_event.h"

#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {

ClickEventActuator::ClickEventActuator(const WeakPtr<GestureEventHub>& gestureEventHub)
    : gestureEventHub_(gestureEventHub)
{}

void ClickEventActuator::OnCollectTouchTarget(const OffsetF& coordinateOffset, const TouchRestrict& touchRestrict,
    const GetEventTargetImpl& getEventTargetImpl, TouchTestResult& result, ResponseLinkResult& responseLinkResult)
{
    if (clickEvents_.empty() && !clickAfterEvents_ && !userCallback_ && !jsFrameNodeCallback_) {
        return;
    }
    auto gestureHub = gestureEventHub_.Upgrade();
    CHECK_NULL_VOID(gestureHub);
    auto frameNode = gestureHub->GetFrameNode();
    CHECK_NULL_VOID(frameNode);

    if (!clickRecognizer_) {
        clickRecognizer_ = MakeRefPtr<ClickRecognizer>();
    }
    clickRecognizer_->SetGestureInfo(MakeRefPtr<GestureInfo>(GestureTypeName::CLICK, true));
    clickRecognizer_->SetRecognizerType(GestureTypeName::CLICK);
    clickRecognizer_->SetOnAction(GetClickEvent());
    clickRecognizer_->SetCoordinateOffset(Offset(coordinateOffset.GetX(), coordinateOffset.GetY()));
    clickRecognizer_->SetGetEventTargetImpl(getEventTargetImpl);
    clickRecognizer_->SetDistanceThreshold(distanceThreshold_);
    auto sysJudgeFunc = GetSysJudgeFunc();
    if (sysJudgeFunc.has_value()) {
        clickRecognizer_->SetSysGestureJudge(sysJudgeFunc.value());
    }
    result.emplace_back(clickRecognizer_);
    responseLinkResult.emplace_back(clickRecognizer_);
}

std::optional<GestureJudgeFunc> ClickEventActuator::GetSysJudgeFunc() const
{
    for (const auto& callback : clickEvents_) {
        if (callback->HasSysGestureJudge()) {
            return callback->GetSysJudge();
        }
    }
    return nullptr;
}

GestureEventFunc ClickEventActuator::GetClickEvent()
{
    auto callback = [weak = WeakClaim(this)](GestureEvent& info) {
        auto actuator = weak.Upgrade();
        CHECK_NULL_VOID(actuator);
        auto clickEvents = actuator->clickEvents_;
        for (const auto& callback : clickEvents) {
            if (callback) {
                (*callback)(info);
            }
        }
        if (actuator->userCallback_) {
            // actuator->userCallback_ may be overwritten in its invoke so we copy it first
            auto userCallback = actuator->userCallback_;
            (*userCallback)(info);
        }
        if (actuator->clickAfterEvents_) {
            auto clickAfterEvents = actuator->clickAfterEvents_;
            (*clickAfterEvents)(info);
        }
        if (actuator->jsFrameNodeCallback_) {
            auto jsFrameNodeCallback = actuator->jsFrameNodeCallback_;
            (*jsFrameNodeCallback)(info);
        }
        if (actuator->onAccessibilityEventFunc_) {
            actuator->onAccessibilityEventFunc_(AccessibilityEventType::CLICK);
        }
    };
    return callback;
}

} // namespace OHOS::Ace::NG
