/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_TEST_CORE_PATTERN_MOCK_PICKER_HAPTIC_IMPL_H
#define FOUNDATION_ACE_TEST_CORE_PATTERN_MOCK_PICKER_HAPTIC_IMPL_H

#include "adapter/ohos/entrance/picker/picker_haptic_interface.h"

namespace OHOS::Ace::NG {
class MockPickerAudioHapticImpl : public IPickerAudioHaptic {
public:
    enum class ThreadStatus {
        NONE,
        START,
        READY,
        PLAYING,
        PLAY_ONCE,
        HANDLE_DELTA,
    };

    void Play(size_t speed) override
    {
        playThreadStatus_ = ThreadStatus::PLAYING;
    }

    void PlayOnce() override
    {
        playThreadStatus_ = ThreadStatus::PLAY_ONCE;
    }

    void Stop() override
    {
    }

    void HandleDelta(double dy) override
    {
        playThreadStatus_ = ThreadStatus::HANDLE_DELTA;
    }

    ThreadStatus playThreadStatus_ = ThreadStatus::NONE;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_TEST_CORE_PATTERN_MOCK_PICKER_HAPTIC_IMPL_H
