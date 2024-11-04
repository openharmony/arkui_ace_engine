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

#include "adapter/ohos/entrance/timepicker/timepicker_haptic_impl.h"

namespace OHOS::Ace::NG {

TimepickerAudioHapticImpl::TimepickerAudioHapticImpl()
{
    handler_ = std::make_unique<TimePickerHapticController>();
}

void TimepickerAudioHapticImpl::Play(size_t speed)
{
    if (handler_) {
        handler_->Play(speed);
    }
}

void TimepickerAudioHapticImpl::PlayOnce()
{
    if (handler_) {
        handler_->PlayOnce();
    }
}

void TimepickerAudioHapticImpl::Stop()
{
    if (handler_) {
        handler_->Stop();
    }
}

void TimepickerAudioHapticImpl::HandleDelta(double dy)
{
    if (handler_) {
        handler_->HandleDelta(dy);
    }
}

void TimepickerAudioHapticImpl::ClearVelocityInfo()
{
    if (handler_) {
        handler_->ClearVelocityInfo();
    }
}

} // namespace OHOS::Ace::NG
