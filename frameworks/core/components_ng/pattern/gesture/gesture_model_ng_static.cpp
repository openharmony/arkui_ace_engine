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

#include "core/components_ng/pattern/gesture/gesture_model_ng_static.h"

#include "core/components_ng/gestures/tap_gesture.h"

namespace OHOS::Ace::NG {

bool GestureModelNGStatic::IsTapClick(const RefPtr<NG::Gesture>& gesture)
{
    auto tap = AceType::DynamicCast<NG::TapGesture>(gesture);
    return tap && (tap->GetTapCount() == 1) && (tap->GetFingers() == 1);
}

GestureEventFunc GestureModelNGStatic::GetTapGestureEventFunc(const RefPtr<NG::Gesture>& gesture)
{
    if (IsTapClick(gesture)) {
        auto tapGesture = AceType::DynamicCast<NG::TapGesture>(gesture);
        auto onActionId = tapGesture->GetOnActionId();
        return onActionId ? *onActionId : nullptr;
    }
    auto group = AceType::DynamicCast<NG::GestureGroup>(gesture);
    if (!group) {
        return nullptr;
    }
    auto list = group->GetGestures();
    for (const auto& tap : list) {
        if (IsTapClick(tap)) {
            auto tapGesture = AceType::DynamicCast<NG::TapGesture>(tap);
            auto onActionId = tapGesture->GetOnActionId();
            return onActionId ? *onActionId : nullptr;
        }
    }
    return nullptr;
}
} // namespace OHOS::Ace::NG
