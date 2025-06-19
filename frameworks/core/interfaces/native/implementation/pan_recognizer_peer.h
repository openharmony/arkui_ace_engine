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
#include "core/gestures/gesture_info.h"

#include "arkoala_api_generated.h"

using OHOS::Ace::AceType;
using OHOS::Ace::PanDirection;
using OHOS::Ace::PanGestureOption;

struct PanRecognizerPeer {
    using PanGestureOptionRefPtr = OHOS::Ace::RefPtr<PanGestureOption>;

    void SetOptions(int32_t fingers, double distance, PanDirection direction)
    {
        options_ = AceType::MakeRefPtr<PanGestureOption>();
        options_->SetDirection(direction);
        options_->SetDistance(distance);
        options_->SetFingers(fingers);
    }

    PanGestureOptionRefPtr GetOptions()
    {
        return options_;
    }

private:
    PanGestureOptionRefPtr options_;
};
#endif //FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_PAN_RECOGNIZER_PEER_H
