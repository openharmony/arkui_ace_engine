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

#include "core/components_ng/gestures/recognizers/swipe_recognizer.h"
#include "core/pipeline/pipeline_context.h"
#include "gesture_recognizer_peer_impl.h"

const double DEFAULT_SPEED = 100.0;
const OHOS::Ace::SwipeDirection DEFAULT_DIRECT = { .type = OHOS::Ace::SwipeDirection::ALL };

struct SwipeRecognizerPeer : public MultiFingerRecognizerPeer {
    void Update(const OHOS::Ace::RefPtr<OHOS::Ace::NG::SwipeRecognizer>& recognizer)
    {
        MultiFingerRecognizerPeer::Update(recognizer);
        direction_ = recognizer->GetDirection();
        speed = recognizer->GetSpeed();
    }
    OHOS::Ace::SwipeDirection GetDirection()
    {
        return direction_;
    }
    double GetSpeed()
    {
        auto recognizer = GestureRecognizerPeer::GetRecognizer().Upgrade();
        if (recognizer) {
            auto context = OHOS::Ace::PipelineContext::GetCurrentContextSafely();
            CHECK_NULL_RETURN(context, DEFAULT_SPEED);
            double value = context->ConvertPxToVp(OHOS::Ace::Dimension(speed, OHOS::Ace::DimensionUnit::PX));
            return OHOS::Ace::RoundToMaxPrecision(value);
        }
        return DEFAULT_SPEED;
    }

protected:
    SwipeRecognizerPeer() = default;
    ~SwipeRecognizerPeer() override = default;
    friend OHOS::Ace::NG::PeerUtils;

private:
    OHOS::Ace::SwipeDirection direction_;
    double speed = DEFAULT_SPEED;
};
