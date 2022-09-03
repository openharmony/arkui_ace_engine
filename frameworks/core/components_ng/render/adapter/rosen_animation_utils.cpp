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

#include "core/components_ng/render/animation_utils.h"

#include "core/animation/native_curve_helper.h"
#include "render_service_client/core/ui/rs_node.h"

namespace OHOS::Ace {
void AnimationUtils::OpenImplicitAnimation(
    const AnimationOption& option, const RefPtr<Curve>& curve, const std::function<void()>& wrapFinishCallback)
{
    Rosen::RSAnimationTimingProtocol timingProtocol;
    timingProtocol.SetDuration(option.GetDuration());
    timingProtocol.SetStartDelay(option.GetDelay());
    timingProtocol.SetSpeed(option.GetTempo());
    timingProtocol.SetRepeatCount(option.GetIteration());
    timingProtocol.SetDirection(option.GetAnimationDirection() == AnimationDirection::NORMAL ||
                                option.GetAnimationDirection() == AnimationDirection::ALTERNATE);
    timingProtocol.SetAutoReverse(option.GetAnimationDirection() == AnimationDirection::ALTERNATE ||
                                  option.GetAnimationDirection() == AnimationDirection::ALTERNATE_REVERSE);
    timingProtocol.SetFillMode(static_cast<Rosen::FillMode>(option.GetFillMode()));
    Rosen::RSNode::OpenImplicitAnimation(timingProtocol, NativeCurveHelper::ToNativeCurve(curve), wrapFinishCallback);
}

bool AnimationUtils::CloseImplicitAnimation()
{
    auto animations = Rosen::RSNode::CloseImplicitAnimation();
    return !animations.empty();
}
} // namespace OHOS::Ace