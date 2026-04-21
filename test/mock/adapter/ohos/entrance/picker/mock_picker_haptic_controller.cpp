/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "adapter/ohos/entrance/picker/picker_haptic_controller.h"

namespace OHOS::Ace::NG {

PickerHapticController::PickerHapticController(const std::string& uri, const std::string& effectId) noexcept
{
    (void)uri;
    (void)effectId;
}

PickerHapticController::~PickerHapticController() noexcept = default;

void PickerHapticController::Play(size_t speed)
{
    (void)speed;
}

void PickerHapticController::PlayOnce() {}

void PickerHapticController::Stop() {}

void PickerHapticController::HandleDelta(double dy)
{
    (void)dy;
}

void PickerHapticController::ThreadLoop() {}

void PickerHapticController::ThreadRelease() {}

void PickerHapticController::InitPlayThread() {}

bool PickerHapticController::IsThreadReady()
{
    return false;
}

bool PickerHapticController::IsThreadPlaying()
{
    return false;
}

bool PickerHapticController::IsThreadPlayOnce()
{
    return false;
}

bool PickerHapticController::IsThreadNone()
{
    return true;
}

double PickerHapticController::ConvertPxToMillimeters(double px) const
{
    (void)px;
    return 0.0;
}

size_t PickerHapticController::GetCurrentSpeedInMm()
{
    return 0;
}

int8_t PickerHapticController::GetPlayStatus()
{
    return 0;
}

} // namespace OHOS::Ace::NG
