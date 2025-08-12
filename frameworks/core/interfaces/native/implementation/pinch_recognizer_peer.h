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

#include "core/components_ng/gestures/recognizers/pinch_recognizer.h"
#include "core/pipeline/pipeline_context.h"
#include "gesture_recognizer_peer_impl.h"

const double DEFAULT_DISTANCE = 5.0;

struct PinchRecognizerPeer : public MultiFingerRecognizerPeer {
    void Update(const OHOS::Ace::RefPtr<OHOS::Ace::NG::PinchRecognizer>& recognizer)
    {
        MultiFingerRecognizerPeer::Update(recognizer);
        distance = recognizer->GetDistance();
    }
    double GetDistance()
    {
        auto recognizer = GestureRecognizerPeer::GetRecognizer().Upgrade();
        if (recognizer) {
            auto context = OHOS::Ace::PipelineContext::GetCurrentContextSafely();
            CHECK_NULL_RETURN(context, DEFAULT_DISTANCE);
            double value = context->ConvertPxToVp(OHOS::Ace::Dimension(distance, OHOS::Ace::DimensionUnit::PX));
            return OHOS::Ace::RoundToMaxPrecision(value);
        }
        return DEFAULT_DISTANCE;
    }

protected:
    PinchRecognizerPeer() = default;
    ~PinchRecognizerPeer() override = default;
    friend OHOS::Ace::NG::PeerUtils;

private:
    double distance = DEFAULT_DISTANCE;
};
