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

#include "core/components_ng/pattern/scroll/scroll_spring_effect.h"

namespace OHOS::Ace::NG {

void ScrollSpringEffect::RegisterSpringCallback()
{
    CHECK_NULL_VOID(scrollable_);
    scrollable_->SetOutBoundaryCallback(outBoundaryCallback_);
    scrollable_->SetScrollOverCallBack([weakEffect = AceType::WeakClaim(this)](double velocity) {
        auto effect = weakEffect.Upgrade();
        CHECK_NULL_VOID(effect);
        effect->ProcessScrollOver(velocity);
    });
    scrollable_->SetCurrentPositionCallback(currentPositionCallback_);
    scrollable_->SetOverScrollOffsetCallback([weakEffect = AceType::WeakClaim(this)]() {
        auto effect = weakEffect.Upgrade();
        if (effect) {
            double position = effect->currentPositionCallback_();
            double minExtent = effect->leadingCallback_();
            double maxExtent = effect->trailingCallback_();
            return std::max(minExtent - position, position - maxExtent);
        }
        return 0.0;
    });
}

void ScrollSpringEffect::InitialEdgeEffect()
{
    RegisterSpringCallback();
}

void ScrollSpringEffect::ProcessScrollOver(double velocity)
{
    if (!currentPositionCallback_ || !leadingCallback_ || !trailingCallback_ || !initLeadingCallback_ ||
        !initTrailingCallback_ || !scrollable_) {
        return;
    }
    if (onWillStartSpringCallback_) {
        onWillStartSpringCallback_();
    }
    double position = currentPositionCallback_();
    double minExtent = leadingCallback_();
    double maxExtent = trailingCallback_();
    double initMinExtent = initLeadingCallback_();
    double initMaxExtent = initTrailingCallback_();
    if (!scrollable_->Available() && minExtent < 0.0) {
        minExtent = 0.0;
    }
    scrollable_->StartSpringMotion(
        position, velocity, ExtentPair(minExtent, maxExtent), ExtentPair(initMinExtent, initMaxExtent));
}

void ScrollSpringEffect::ProcessSpringUpdate()
{
    if (!currentPositionCallback_ || !leadingCallback_ || !trailingCallback_ || !initLeadingCallback_ ||
        !initTrailingCallback_ || !scrollable_) {
        return;
    }
    if (onWillStartSpringCallback_) {
        onWillStartSpringCallback_();
    }
    double position = currentPositionCallback_();
    double minExtent = leadingCallback_();
    double maxExtent = trailingCallback_();
    double initMinExtent = initLeadingCallback_();
    double initMaxExtent = initTrailingCallback_();
    if (!scrollable_->Available() && minExtent < 0.0) {
        minExtent = 0.0;
    }
    scrollable_->UpdateSpringMotion(
        position, ExtentPair(minExtent, maxExtent), ExtentPair(initMinExtent, initMaxExtent));
}
} // namespace OHOS::Ace::NG
