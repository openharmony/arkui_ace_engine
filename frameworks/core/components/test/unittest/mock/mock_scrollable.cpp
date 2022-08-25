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

#include "core/components/scroll/scrollable.h"

namespace OHOS::Ace {
// Static Functions.
double Scrollable::sFriction_ = 0.0;
double Scrollable::sVelocityScale_ = 0.0;

void Scrollable::SetVelocityScale(double sVelocityScale)
{
    sVelocityScale_ = sVelocityScale;
}

void Scrollable::SetFriction(double sFriction)
{
    sFriction_ = sFriction;
}

Scrollable::~Scrollable() = default;

void Scrollable::Initialize(const WeakPtr<PipelineBase>& context)
{
    context_ = context;
    controller_ = nullptr;
    springController_ = nullptr;

    spring_ = nullptr;
    available_ = true;
    scrollPause_ = false;
    touchUp_ = false;
    isDragUpdateStop_ = false;
    slipFactor_ = 0.0;
    startIncreaseTime_ = 0;
}

void Scrollable::HandleTouchDown()
{
    isTouching_ = true;
    currentPos_ = 0.0;
}

void Scrollable::HandleTouchUp()
{
}

bool Scrollable::IsAnimationNotRunning() const
{
    return !isTouching_ && !controller_->IsRunning() && !springController_->IsRunning();
}

bool Scrollable::Idle() const
{
    return !isTouching_ && controller_->IsStopped() && springController_->IsStopped();
}

bool Scrollable::IsStopped() const
{
    return (!springController_ || (springController_->IsStopped())) && (!controller_ || (controller_->IsStopped()));
}

void Scrollable::StopScrollable()
{
}

void Scrollable::HandleDragStart(const OHOS::Ace::GestureEvent& info)
{
}

void Scrollable::HandleDragUpdate(const GestureEvent& info)
{
}

void Scrollable::HandleDragEnd(const GestureEvent& info)
{
}

void Scrollable::ExecuteScrollBegin(double& mainDelta)
{
}

void Scrollable::FixScrollMotion(double position)
{
};

void Scrollable::StartSpringMotion(
    double mainPosition, double mainVelocity, const ExtentPair& extent, const ExtentPair& initExtent)
{
}

void Scrollable::ProcessScrollMotionStop()
{
}

void Scrollable::ProcessSpringMotion(double position)
{
    currentPos_ = position;
}

void Scrollable::ProcessScrollMotion(double position)
{
    currentPos_ = position;
}

bool Scrollable::UpdateScrollPosition(const double offset, int32_t source) const
{
    return false;
}

void Scrollable::ProcessScrollOverCallback(double velocity)
{
}

void Scrollable::SetSlipFactor(double SlipFactor)
{
}

const RefPtr<SpringProperty>& Scrollable::GetDefaultOverSpringProperty()
{
    return nullptr;
}
} // namespace OHOS::Ace
