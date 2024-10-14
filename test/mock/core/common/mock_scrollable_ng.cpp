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

#include "core/components_ng/pattern/scrollable/scrollable.h"

namespace OHOS::Ace::NG {
Scrollable::~Scrollable() = default;

void Scrollable::Initialize(const WeakPtr<PipelineBase>& context) {}

bool Scrollable::Idle() const
{
    return false;
}

bool Scrollable::IsStopped() const
{
    return true;
}

void Scrollable::StopScrollable() {}

void Scrollable::StartSpringMotion(
    double mainPosition, double mainVelocity, const ExtentPair& extent, const ExtentPair& initExtent)
{}

void Scrollable::UpdateScrollSnapStartOffset(double offset)
{}

void Scrollable::StartListSnapAnimation(float predictSnapOffset, float scrollSnapVelocity)
{
    endPos_ = currentPos_ + predictSnapOffset;
}

void Scrollable::UpdateScrollSnapEndWithOffset(double offset)
{}

void Scrollable::SetAxis(Axis axis)
{}

bool Scrollable::IsSpringStopped() const
{
    return true;
}

void Scrollable::StartScrollSnapAnimation(float scrollSnapDelta, float scrollSnapVelocity) {}
void Scrollable::StartScrollAnimation(float, float) {}

RefPtr<NodeAnimatablePropertyFloat> Scrollable::GetFrictionProperty()
{
    return AceType::MakeRefPtr<NodeAnimatablePropertyFloat>(0.0, nullptr);
}

RefPtr<NodeAnimatablePropertyFloat> Scrollable::GetSpringProperty()
{
    return AceType::MakeRefPtr<NodeAnimatablePropertyFloat>(0.0, nullptr);
}

RefPtr<NodeAnimatablePropertyFloat> Scrollable::GetSnapProperty()
{
    return AceType::MakeRefPtr<NodeAnimatablePropertyFloat>(0.0, nullptr);
}
} // namespace OHOS::Ace::NG
