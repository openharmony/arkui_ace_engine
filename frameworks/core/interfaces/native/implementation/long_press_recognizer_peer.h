/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include "core/components_ng/gestures/recognizers/long_press_recognizer.h"
#include "core/components_ng/gestures/recognizers/multi_fingers_recognizer.h"
#include "gesture_recognizer_peer_impl.h"
#include "arkoala_api_generated.h"

const int32_t DEFAULT_DURATION = 500;
const bool DEFAULT_REPEAT = false;

struct LongPressRecognizerPeer : public MultiFingerRecognizerPeer {
    void Update(const OHOS::Ace::RefPtr<OHOS::Ace::NG::LongPressRecognizer>& recognizer)
    {
        MultiFingerRecognizerPeer::Update(recognizer);
        duration_ = recognizer->GetDuration();
        repeat = recognizer->GetIsRepeat();
    }
    int32_t GetDuration()
    {
        auto recognizer = GestureRecognizerPeer::GetRecognizer().Upgrade();
        if (recognizer) {
            return duration_;
        }
        return DEFAULT_DURATION;
    }
    bool GetRepeat()
    {
        auto recognizer = GestureRecognizerPeer::GetRecognizer().Upgrade();
        if (recognizer) {
            return repeat;
        }
        return DEFAULT_REPEAT;
    }
    void SetRepeat(const bool value)
    {
        repeat = value;
    }

protected:
    LongPressRecognizerPeer() = default;
    ~LongPressRecognizerPeer() override = default;
    friend OHOS::Ace::NG::PeerUtils;

private:
    int32_t duration_ = DEFAULT_DURATION;
    bool repeat = DEFAULT_REPEAT;
};
