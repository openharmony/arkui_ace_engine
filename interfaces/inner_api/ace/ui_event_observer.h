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

#ifndef FOUNDATION_ACE_INTERFACE_INNERKITS_ACE_UI_EVENT_OBSERVER_H
#define FOUNDATION_ACE_INTERFACE_INNERKITS_ACE_UI_EVENT_OBSERVER_H

#include <functional>
#include <string>
#include <unordered_map>

#include "macros.h"

namespace OHOS::Ace {
using OnInspectorTreeResult = std::function<void(const std::shared_ptr<std::string>)>;

struct ACE_FORCE_EXPORT TreeParams {
    bool isNewVersion = true;
    bool isVisibleOnly = false;
    bool isContentOnly = false;
    bool enableWeb = false;
    std::string webContentJs;
    bool isWindowIdOnly = false;
};

class ACE_FORCE_EXPORT UIEventObserver {
public:
    virtual ~UIEventObserver() = default;
    virtual void NotifyUIEvent(int32_t eventType, const std::unordered_map<std::string, std::string>& eventParams) = 0;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_INTERFACE_INNERKITS_ACE_UI_EVENT_OBSERVER_H
