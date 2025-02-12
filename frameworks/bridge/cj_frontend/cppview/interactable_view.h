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

#ifndef FRAMEWORKS_BRIDGE_CJ_FRONTEND_CPP_VIEW_INTERACTABLE_H
#define FRAMEWORKS_BRIDGE_CJ_FRONTEND_CPP_VIEW_INTERACTABLE_H

#include "base/utils/macros.h"
#include "bridge/cj_frontend/cppview/view_abstract.h"
#include "core/event/key_event.h"
#include "core/gestures/raw_recognizer.h"
#include "core/gestures/tap_gesture.h"

namespace OHOS::Ace::Framework {

class ACE_EXPORT InteractableView {
public:
    static void SetFocusable(bool focusable);
    static void SetFocusNode(bool isFocusNode);
    static void OnClick(std::function<void(const ClickInfo& clickInfo)> callback);
    static void OnTouch(std::function<void(TouchEventInfo& touchInfo)> callback);
    static void OnAppear(std::function<void()> callback);
    static void OnDisAppear(std::function<void()> callback);
    static void OnHover(std::function<void(bool)> callback);
    static void OnHoverMove(std::function<void()> callback);
    static void OnKey(std::function<bool(KeyEventInfo& keyInfo)> callback);
    static void OnDelete(std::function<void()> callback);
    static EventMarker GetClickEventMarker(std::function<void(const ClickInfo& clickInfo)> callback);

private:
    static RefPtr<Gesture> GetTapGesture(std::function<void(const ClickInfo& clickInfo)> callback,
        int32_t countNum = 1, int32_t fingerNum = 1);
};

} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_CJ_FRONTEND_CPP_VIEW_INTERACTABLE_H
