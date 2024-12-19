/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/scrollable/axis/axis_animator.h"

#include "base/utils/time_util.h"
#include "core/common/container.h"

namespace OHOS::Ace::NG {

void AxisAnimator::Initialize(const WeakPtr<PipelineBase>& context)
{
    context_ = context;
}

void AxisAnimator::OnAxis(float mainDelta, float scrollablePos)
{
    CHECK_NULL_VOID(axisAnimationCallback_ && !NearZero(mainDelta));
    if (!axisScrollMotion_ || !axisScrollAnimator_) {
        CreateAnimator();
    }
    if (IsRunning()) {
        auto finalPos = axisScrollMotion_->GetFinalPosition();
        auto currentPos = axisScrollMotion_->GetCurrentPosition();
        if ((GreatNotEqual(currentPos, finalPos) && Positive(mainDelta)) ||
            (LessNotEqual(currentPos, finalPos) && !Positive(mainDelta))) {
            axisScrollAnimator_->Stop();
            return;
        }
        auto distance = finalPos + mainDelta - currentPos;
        axisScrollMotion_->Reset(currentPos, distance);
    } else {
        if (!axisScrollMotion_) {
            return;
        }
        axisScrollMotion_->Reset(scrollablePos, mainDelta);
        axisScrollAnimator_->PlayMotion(axisScrollMotion_);
    }
}

void AxisAnimator::CreateAnimator()
{
    if (!axisScrollMotion_) {
        axisScrollMotion_ = AceType::MakeRefPtr<AxisScrollMotion>(0.f, 0.f);
        axisScrollMotion_->AddListener([weak = AceType::WeakClaim(this)](double offset) {
            auto axisAnimator = weak.Upgrade();
            CHECK_NULL_VOID(axisAnimator && axisAnimator->axisAnimationCallback_);
            axisAnimator->axisAnimationCallback_(offset);
        });
    }
    if (!axisScrollAnimator_) {
        auto context = context_.Upgrade();
        CHECK_NULL_VOID(context);
        axisScrollAnimator_ = CREATE_ANIMATOR(context);
        axisScrollAnimator_->AddStopListener([weak = AceType::WeakClaim(this)]() {
            auto axisAnimator = weak.Upgrade();
            CHECK_NULL_VOID(axisAnimator);
            CHECK_NULL_VOID(axisAnimator->axisAnimationFinishCallback_);
            axisAnimator->axisAnimationFinishCallback_();
            auto axisScrollMotion = axisAnimator->GeAxisScrollMotion();
            CHECK_NULL_VOID(axisScrollMotion);
            axisScrollMotion->ResetCurrentTime();
        });
    }
}

} // namespace OHOS::Ace::NG