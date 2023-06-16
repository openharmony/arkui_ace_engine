/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/event/input_event.h"

#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {

InputEventActuator::InputEventActuator(const WeakPtr<InputEventHub>& inputEventHub) : inputEventHub_(inputEventHub)
{
    auto refInputEventHub = inputEventHub_.Upgrade();
    CHECK_NULL_VOID(refInputEventHub);
    auto frameNode = refInputEventHub->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    mouseEventTarget_ = MakeRefPtr<MouseEventTarget>(frameNode->GetTag(), frameNode->GetId());
    hoverEventTarget_ = MakeRefPtr<HoverEventTarget>(frameNode->GetTag(), frameNode->GetId());
    hoverEffectTarget_ = MakeRefPtr<HoverEffectTarget>(frameNode->GetTag(), frameNode->GetId());
    axisEventTarget_ = MakeRefPtr<AxisEventTarget>(frameNode->GetTag());
}

void InputEventActuator::OnCollectMouseEvent(
    const OffsetF& coordinateOffset, const GetEventTargetImpl& getEventTargetImpl, TouchTestResult& result)
{
    if (inputEvents_.empty() && !userCallback_) {
        return;
    }

    auto onMouseCallback = [weak = WeakClaim(this)](MouseInfo& info) {
        auto actuator = weak.Upgrade();
        CHECK_NULL_VOID(actuator);
        for (const auto& callback : actuator->inputEvents_) {
            if (callback) {
                (*callback)(info);
            }
        }
        if (actuator->userCallback_) {
            (*actuator->userCallback_)(info);
        }
    };
    mouseEventTarget_->SetCallback(onMouseCallback);
    mouseEventTarget_->SetCoordinateOffset(Offset(coordinateOffset.GetX(), coordinateOffset.GetY()));
    mouseEventTarget_->SetGetEventTargetImpl(getEventTargetImpl);
    result.emplace_back(mouseEventTarget_);
}

void InputEventActuator::OnCollectHoverEvent(
    const OffsetF& coordinateOffset, const GetEventTargetImpl& getEventTargetImpl, TouchTestResult& result)
{
    if (inputEvents_.empty() && !userCallback_) {
        return;
    }

    auto onHoverCallback = [weak = WeakClaim(this)](bool info, HoverInfo& hoverInfo) {
        auto actuator = weak.Upgrade();
        CHECK_NULL_VOID(actuator);
        for (const auto& callback : actuator->inputEvents_) {
            if (callback) {
                (*callback)(info);
            }
        }
        if (actuator->userCallback_) {
            (*actuator->userCallback_)(info, hoverInfo);
        }
    };
    hoverEventTarget_->SetCallback(onHoverCallback);
    hoverEventTarget_->SetCoordinateOffset(Offset(coordinateOffset.GetX(), coordinateOffset.GetY()));
    hoverEventTarget_->SetGetEventTargetImpl(getEventTargetImpl);
    result.emplace_back(hoverEventTarget_);
}

void InputEventActuator::OnCollectHoverEffect(
    const OffsetF& coordinateOffset, const GetEventTargetImpl& getEventTargetImpl, TouchTestResult& result)
{
    auto inputEventHub = inputEventHub_.Upgrade();
    CHECK_NULL_VOID(inputEventHub);
    auto frameNode = inputEventHub->GetFrameNode();
    CHECK_NULL_VOID(frameNode);

    hoverEffectTarget_->SetCoordinateOffset(Offset(coordinateOffset.GetX(), coordinateOffset.GetY()));
    hoverEffectTarget_->SetGetEventTargetImpl(getEventTargetImpl);
    hoverEffectTarget_->SetHoverNode(AceType::WeakClaim(AceType::RawPtr(frameNode)));
    result.emplace_back(hoverEffectTarget_);
}

void InputEventActuator::OnCollectAxisEvent(
    const OffsetF& coordinateOffset, const GetEventTargetImpl& getEventTargetImpl, AxisTestResult& onAxisResult)
{
    auto inputEventHub = inputEventHub_.Upgrade();
    CHECK_NULL_VOID(inputEventHub);
    auto frameNode = inputEventHub->GetFrameNode();
    CHECK_NULL_VOID(frameNode);

    if (inputEvents_.empty() && !userCallback_) {
        return;
    }

    auto onAxisCallback = [weak = WeakClaim(this)](AxisInfo& info) {
        auto actuator = weak.Upgrade();
        CHECK_NULL_VOID(actuator);
        for (const auto& callback : actuator->inputEvents_) {
            if (callback) {
                (*callback)(info);
            }
        }
        if (actuator->userCallback_) {
            (*actuator->userCallback_)(info);
        }
    };
    axisEventTarget_->SetOnAxisCallback(onAxisCallback);
    axisEventTarget_->SetCoordinateOffset(coordinateOffset);
    axisEventTarget_->SetGetEventTargetImpl(getEventTargetImpl);
    onAxisResult.emplace_back(axisEventTarget_);
}

} // namespace OHOS::Ace::NG