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
#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_GESTURE_RECOGNIZER_PEER_IMPL_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_GESTURE_RECOGNIZER_PEER_IMPL_H

#include "core/components_ng/gestures/recognizers/gesture_recognizer.h"
#include "core/components_ng/gestures/recognizers/multi_fingers_recognizer.h"
#include "core/interfaces/native/utility/peer_utils.h"

const int32_t DEFAULT_FINGERS = 1;
const bool DEFAULT_LIMIT = false;

struct GestureRecognizerPeer {
    OHOS::Ace::WeakPtr<OHOS::Ace::NG::NGGestureRecognizer> GetRecognizer()
    {
        return recognizer_;
    }
    void Update(const OHOS::Ace::RefPtr<OHOS::Ace::NG::NGGestureRecognizer>& recognizer)
    {
        recognizer_ = recognizer;
    }
    int32_t GetFingers()
    {
        return fingers_;
    }
    bool IsFingerCountLimit()
    {
        return isLimitFingerCount;
    }

protected:
    GestureRecognizerPeer() = default;
    virtual ~GestureRecognizerPeer() = default;
    friend OHOS::Ace::NG::PeerUtils;

    bool isLimitFingerCount = DEFAULT_LIMIT;
    int32_t fingers_ = DEFAULT_FINGERS;

private:
    OHOS::Ace::WeakPtr<OHOS::Ace::NG::NGGestureRecognizer> recognizer_;
};

struct MultiFingerRecognizerPeer : public GestureRecognizerPeer {
    void Update(const OHOS::Ace::RefPtr<OHOS::Ace::NG::MultiFingersRecognizer>& recognizer)
    {
        GestureRecognizerPeer::Update(recognizer);
        isLimitFingerCount = recognizer->GetLimitFingerCount();
        fingers_ = recognizer->GetFingers();
    }

protected:
    MultiFingerRecognizerPeer() = default;
    ~MultiFingerRecognizerPeer() override = default;
    friend OHOS::Ace::NG::PeerUtils;
};
#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_GESTURE_RECOGNIZER_PEER_IMPL_H
