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

#include "core/components_ng/pattern/time_picker/timepicker_haptic_factory.h"
#if defined(AUDIO_FRAMEWORK_EXISTS) && defined(PLAYER_FRAMEWORK_EXISTS)
#include "adapter/ohos/entrance/timepicker/timepicker_haptic_impl.h"
#endif

namespace OHOS::Ace::NG {
std::shared_ptr<ITimepickerAudioHaptic> TimepickerAudioHapticFactory::instance_ { nullptr };
std::mutex TimepickerAudioHapticFactory::mutex_;

std::shared_ptr<ITimepickerAudioHaptic> TimepickerAudioHapticFactory::GetInstance()
{
    if (instance_ == nullptr) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (instance_ == nullptr) {
#if defined(AUDIO_FRAMEWORK_EXISTS) && defined(PLAYER_FRAMEWORK_EXISTS)
            instance_ = std::make_shared<TimepickerAudioHapticImpl>();
#endif
        }
    }
    return instance_;
}
} // namespace OHOS::Ace::NG
