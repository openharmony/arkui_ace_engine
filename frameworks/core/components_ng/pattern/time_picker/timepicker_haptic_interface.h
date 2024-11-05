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
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TIME_PICKER_AUDIO_HAPTIC_INTERFACE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TIME_PICKER_AUDIO_HAPTIC_INTERFACE_H

#include <stddef.h>

namespace OHOS::Ace::NG {
class ITimepickerAudioHaptic {
public:
    ITimepickerAudioHaptic() = default;
    virtual ~ITimepickerAudioHaptic() = default;
    virtual void Play(size_t speed) = 0;
    virtual void PlayOnce() = 0;
    virtual void Stop() = 0;
    virtual void HandleDelta(double dy) = 0;
    virtual void ClearVelocityInfo() = 0;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TIME_PICKER_AUDIO_HAPTIC_INTERFACE_H
