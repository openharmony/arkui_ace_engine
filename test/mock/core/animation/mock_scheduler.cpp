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

#include "core/animation/scheduler.h"

namespace OHOS::Ace {
void Scheduler::OnFrame(uint64_t nanoTimestamp) {}

void Scheduler::Start()
{
    isRunning_ = true;
}

void Scheduler::Stop()
{
    isRunning_ = false;
}

bool Scheduler::Animate(const AnimationOption& option, const RefPtr<Curve>& curve,
    const std::function<void()> propertyCallback, const std::function<void()>& finishCallBack)
{
    return false;
}

void Scheduler::OpenImplicitAnimation(
    const AnimationOption& option, const RefPtr<Curve>& curve, const std::function<void()>& finishCallBack)
{}

bool Scheduler::CloseImplicitAnimation()
{
    scheduleId_ = 0;
    startupTimestamp_ = 0;
    return false;
}

void Scheduler::AddKeyFrame(float fraction, const RefPtr<Curve>& curve, const std::function<void()>& propertyCallback)
{}

void Scheduler::AddKeyFrame(float fraction, const std::function<void()>& propertyCallback) {}

bool Scheduler::PrintVsyncInfoIfNeed() const
{
    return false;
}
} // namespace OHOS::Ace
