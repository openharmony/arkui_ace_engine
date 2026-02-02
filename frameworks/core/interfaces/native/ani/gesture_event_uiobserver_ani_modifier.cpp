/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "gesture_event_uiobserver_ani_modifier.h"

#include "base/log/log.h"
#include "core/components_ng/base/observer_handler.h"

namespace OHOS::Ace::NG {

void RemovePanListenerCallback(const std::string& tag, ani_int instanceId, ani_int resourceId, bool isRemoveAll)
{
    if (tag == "beforePanStart") {
        UIObserverHandler::RemoveBeforePanStartListenerCallback(
            static_cast<int32_t>(instanceId), static_cast<int32_t>(resourceId), isRemoveAll);
    } else if (tag == "beforePanEnd") {
        UIObserverHandler::RemoveBeforePanEndListenerCallback(
            static_cast<int32_t>(instanceId), static_cast<int32_t>(resourceId), isRemoveAll);
    } else if (tag == "afterPanStart") {
        UIObserverHandler::RemoveAfterPanStartListenerCallback(
            static_cast<int32_t>(instanceId), static_cast<int32_t>(resourceId), isRemoveAll);
    } else if (tag == "afterPanEnd") {
        UIObserverHandler::RemoveAfterPanEndListenerCallback(
            static_cast<int32_t>(instanceId), static_cast<int32_t>(resourceId), isRemoveAll);
    }
}

void RemoveClickListenerCallback(const std::string& tag, ani_int instanceId, ani_int resourceId, bool isRemoveAll)
{
    if (tag == "willClick") {
        UIObserverHandler::RemoveWillClickListenerCallback(
            static_cast<int32_t>(instanceId), static_cast<int32_t>(resourceId), isRemoveAll);
    } else if (tag == "didClick") {
        UIObserverHandler::RemoveDidClickListenerCallback(
            static_cast<int32_t>(instanceId), static_cast<int32_t>(resourceId), isRemoveAll);
    }
}

void RemoveTapListenerCallback(const std::string& tag, ani_int instanceId, ani_int resourceId, bool isRemoveAll)
{
    if (tag == "willTap") {
        UIObserverHandler::RemoveWillTapListenerCallback(
            static_cast<int32_t>(instanceId), static_cast<int32_t>(resourceId), isRemoveAll);
    } else if (tag == "didTap") {
        UIObserverHandler::RemoveDidTapListenerCallback(
            static_cast<int32_t>(instanceId), static_cast<int32_t>(resourceId), isRemoveAll);
    }
}

void RemoveGlobalGestureListenerCallback(ani_int type, ani_int resourceId, bool isRemoveAll)
{
    if (isRemoveAll) {
        // Remove all callbacks for this gestureType across all phases
        // Note: This is equivalent to removing by gestureType only
        GestureActionPhase phases[] = {
            GestureActionPhase::WILL_START,
            GestureActionPhase::WILL_END
        };
        for (const auto& phase : phases) {
            UIObserverHandler::RemoveGlobalGestureListenerCallback(
                static_cast<GestureListenerType>(type),
                phase);
        }
    } else {
        // Remove callbacks matching the gestureType and resourceId
        UIObserverHandler::RemoveGlobalGestureListenerCallback(
            static_cast<GestureListenerType>(type),
            static_cast<int32_t>(resourceId));
    }
}

const ArkUIAniGestureEventUIObserverModifier* GetArkUIAniGestureEventUIObserverModifier()
{
    static const ArkUIAniGestureEventUIObserverModifier impl = {
        .removePanListenerCallback = OHOS::Ace::NG::RemovePanListenerCallback,
        .removeClickListenerCallback = OHOS::Ace::NG::RemoveClickListenerCallback,
        .removeTapListenerCallback = OHOS::Ace::NG::RemoveTapListenerCallback,
        .removeGlobalGestureListenerCallback = OHOS::Ace::NG::RemoveGlobalGestureListenerCallback,
    };
    return &impl;
}
} // namespace OHOS::Ace::NG