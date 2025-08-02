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
#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_PAN_RECOGNIZER_PEER_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_PAN_RECOGNIZER_PEER_H

#include <optional>
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components_ng/gestures/recognizers/pan_recognizer.h"
#include "core/gestures/gesture_info.h"
#include "gesture_recognizer_peer_impl.h"

#include "arkoala_api_generated.h"

using OHOS::Ace::AceType;
using OHOS::Ace::PanDirection;
using OHOS::Ace::PanGestureOption;

struct PanRecognizerPeer : public MultiFingerRecognizerPeer {
    void Update(const OHOS::Ace::RefPtr<OHOS::Ace::NG::PanRecognizer>& recognizer)
    {
        MultiFingerRecognizerPeer::Update(recognizer);
        SetPanGestureOptions(recognizer->GetFingers(), recognizer->GetDistance(), recognizer->GetDirection());
        direction_ = recognizer->GetDirection();
        distance = recognizer->GetDistance();
    }
    OHOS::Ace::RefPtr<OHOS::Ace::PanGestureOption> GetPanGestureOptions()
    {
        return panGestureOption_;
    }
    PanDirection GetDirection()
    {
        return direction_;
    }
    double GetPanDistance()
    {
        return distance;
    }

protected:
    PanRecognizerPeer() = default;
    ~PanRecognizerPeer() override = default;
    friend OHOS::Ace::NG::PeerUtils;

private:
    void SetPanGestureOptions(int32_t fingers, double distances, PanDirection direction)
    {
        panGestureOption_ = OHOS::Ace::AceType::MakeRefPtr<PanGestureOption>();
        panGestureOption_->SetFingers(fingers);
        panGestureOption_->SetDistance(distances);
        panGestureOption_->SetDirection(direction);
    }

    OHOS::Ace::RefPtr<OHOS::Ace::PanGestureOption> panGestureOption_;
    PanDirection direction_;
    double distance;
};
#endif //FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_PAN_RECOGNIZER_PEER_H
