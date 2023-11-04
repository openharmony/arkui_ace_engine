/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_GESTURES_CLICK_INFO_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_GESTURES_CLICK_INFO_H

#include "core/event/touch_event.h"

namespace OHOS::Ace {

class ClickInfo : public TouchLocationInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(ClickInfo, TouchLocationInfo);

public:
    explicit ClickInfo(int32_t fingerId) : TouchLocationInfo("onClick", fingerId) {}
    ~ClickInfo() override = default;
};
using ClickCallback = std::function<void(const ClickInfo&)>;

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_GESTURES_CLICK_INFO_H