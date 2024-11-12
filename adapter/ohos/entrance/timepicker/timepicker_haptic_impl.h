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

#ifndef FOUNDATION_ACE_ENGINE_ADAPTER_OHOS_TIMEPICKER_AUDIO_HAPTIC_IMPL_H
#define FOUNDATION_ACE_ENGINE_ADAPTER_OHOS_TIMEPICKER_AUDIO_HAPTIC_IMPL_H

#include "adapter/ohos/entrance/timepicker/timepicker_haptic_controller.h"
#include "core/components_ng/pattern/time_picker/timepicker_haptic_interface.h"

namespace OHOS::Ace::NG {
class TimepickerAudioHapticImpl : public ITimepickerAudioHaptic {
public:
    TimepickerAudioHapticImpl();
    ~TimepickerAudioHapticImpl() = default;
    void Play(size_t speed) override;
    void PlayOnce() override;
    void Stop() override;
    void HandleDelta(double dy) override;
private:
    std::unique_ptr<TimePickerHapticController> handler_ = nullptr;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_ENGINE_ADAPTER_OHOS_TIMEPICKER_AUDIO_HAPTIC_IMPL_H
