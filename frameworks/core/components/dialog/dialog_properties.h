/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_ACE_ENGINE_FRAMEWORKS_CORE_COMPONENTS_COMMON_PROPERTIES_DIALOG_PROPERTIES_H
#define FOUNDATION_ACE_ACE_ENGINE_FRAMEWORKS_CORE_COMPONENTS_COMMON_PROPERTIES_DIALOG_PROPERTIES_H

#include "core/event/ace_event_handler.h"

namespace OHOS::Ace {

enum class DialogType {
    COMMON = 0,
    ALERT_DIALOG,
};

struct DialogProperties {
    DialogType type = DialogType::COMMON; // type of dialog, current support common dialog and alert dialog.
    std::string title; // title of dialog.
    std::string content; // message of dialog.
    bool autoCancel = true; // pop dialog when click mask if autoCancel is true.
    bool isMenu = false;
    std::vector<std::pair<std::string, std::string>> buttons; // <text of button, color of text>
    std::unordered_map<std::string, EventMarker> callbacks; // <callback type(success, cancel, complete), eventId>

    // These ids is used for AlertDialog of declarative.
    EventMarker primaryId; // first button's callback.
    EventMarker secondaryId; // second button's callback.

    RefPtr<Component> customComponent; // Used for CustomDialog in declarative.
    std::function<void(bool)> onStatusChanged; // Called when dialog appear or disappear.
};

}

#endif // FOUNDATION_ACE_ACE_ENGINE_FRAMEWORKS_CORE_COMPONENTS_COMMON_PROPERTIES_DIALOG_PROPERTIES_H
