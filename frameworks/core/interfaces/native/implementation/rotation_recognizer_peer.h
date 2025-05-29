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

#include "core/components_ng/gestures/recognizers/rotation_recognizer.h"
#include "gesture_recognizer_peer_impl.h"

const double DEFAULT_ANGLE = 1.0;

struct RotationRecognizerPeer : public MultiFingerRecognizerPeer {
    void Update(const OHOS::Ace::RefPtr<OHOS::Ace::NG::RotationRecognizer>& recognizer)
    {
        MultiFingerRecognizerPeer::Update(recognizer);
        angle_ = recognizer->GetAngle();
    }
    double GetAngle()
    {
        auto recognizer = GestureRecognizerPeer::GetRecognizer().Upgrade();
        if (recognizer) {
            return angle_;
        }
        return DEFAULT_ANGLE;
    }

protected:
    RotationRecognizerPeer() = default;
    ~RotationRecognizerPeer() override = default;
    friend OHOS::Ace::NG::PeerUtils;

private:
    double angle_ = DEFAULT_ANGLE;
};