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

#include "adapter/ohos/entrance/picker/picker_haptic_factory.h"
#include "mock_picker_haptic_impl.h"

namespace OHOS::Ace::NG {
std::weak_ptr<IPickerAudioHaptic> PickerAudioHapticFactory::instance_;
std::mutex PickerAudioHapticFactory::mutex_;

std::shared_ptr<IPickerAudioHaptic> PickerAudioHapticFactory::GetInstance(
    const std::string& uri, const std::string& effectId)
{
    std::lock_guard<std::mutex> lock(mutex_);
    auto exsiting = instance_.lock();
    if (exsiting) {
        return exsiting;
    }

    auto newInstance = std::make_shared<MockPickerAudioHapticImpl>();
    instance_ = newInstance;
    return newInstance;
}

} // namespace OHOS::Ace::NG
