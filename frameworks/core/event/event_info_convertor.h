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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_EVENT_EVENT_INFO_CONVERTOR_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_EVENT_EVENT_INFO_CONVERTOR_H

#include "core/event/mouse_event.h"
#include "core/event/touch_event.h"

namespace OHOS::Ace::NG {
class EventInfoConvertor final {
public:
    static bool ConvertMouseToTouchIfNeeded(const MouseInfo& mouseInfo, TouchEventInfo& touchEventInfo);
    static bool IsTouchEventNeedAbandoned(const TouchEventInfo& touchEventInfo);
    static bool MatchCompatibleCondition();
private:
    EventInfoConvertor() = default;
    ~EventInfoConvertor() = default;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_EVENT_EVENT_INFO_CONVERTOR_H
