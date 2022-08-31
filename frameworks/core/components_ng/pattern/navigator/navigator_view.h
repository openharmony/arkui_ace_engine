/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATOR_NAVIGATOR_VIEW_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATOR_NAVIGATOR_VIEW_H

#include <string>
#include "navigator_event_hub.h"
#include "base/utils/macros.h"
#include "core/components/common/layout/constants.h"
#include "core/event/ace_event_handler.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT NavigatorView {
public:
    static void Create();
    static void SetType(NavigatorType value);
    static void SetActive(bool active);
    static void SetUri(const std::string& uri);
    static void SetParams(const std::string& params);
    static void SetIsDefHeight(bool isDefHeight);
    static void SetIsDefWidth(bool isDefWidth);
    static void SetClickedEventId(const EventMarker& eventId);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATOR_VIEW_H
