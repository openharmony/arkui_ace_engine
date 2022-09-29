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
    eventTarget_ = MakeRefPtr<MouseEventTarget>();
    axisEventTarget_ = MakeRefPtr<AxisEventTarget>(frameNode->GetTag());
}

void InputEventActuator::OnCollectMouseEvent(const OffsetF& coordinateOffset,
    const GetEventTargetImpl& getEventTargetImpl, MouseTestResult& onMouseResult, RefPtr<FrameNode>& hoverNode)
{
    auto inputEventHub = inputEventHub_.Upgrade();
    CHECK_NULL_VOID(inputEventHub);
    auto frameNode = inputEventHub->GetFrameNode();
    CHECK_NULL_VOID(frameNode);

    if (!hoverNode && inputEventHub->GetHoverEffect() != HoverEffectType::UNKNOWN) {
        hoverNode = frameNode;
    }

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
    eventTarget_->SetOnMouseCallback(onMouseCallback);
    eventTarget_->SetCoordinateOffset(coordinateOffset);
    eventTarget_->SetGetEventTargetImpl(getEventTargetImpl);
    onMouseResult.emplace_back(eventTarget_);
}

void InputEventActuator::OnCollectHoverEvent(
    const OffsetF& coordinateOffset, const GetEventTargetImpl& getEventTargetImpl, MouseTestResult& onHoverResult)
{
    if (inputEvents_.empty() && !userCallback_) {
        return;
    }

    auto onHoverCallback = [weak = WeakClaim(this)](bool info) {
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
    eventTarget_->SetOnHoverCallback(onHoverCallback);
    eventTarget_->SetCoordinateOffset(coordinateOffset);
    eventTarget_->SetGetEventTargetImpl(getEventTargetImpl);
    onHoverResult.emplace_back(eventTarget_);
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