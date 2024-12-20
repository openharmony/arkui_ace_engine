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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_WEB_VIEW_DATA_COMMON_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_WEB_VIEW_DATA_COMMON_H

#include "nweb_autofill.h"

namespace OHOS::Ace::NG {
class ViewDataCommon {
public:
    ViewDataCommon() = default;
    ~ViewDataCommon() = default;

    OHOS::NWeb::NWebAutofillEvent GetEventType() const
    {
        return eventType_;
    }

    void SetEventType(OHOS::NWeb::NWebAutofillEvent eventType)
    {
        eventType_ = eventType;
    }

    std::string GetPageUrl() const
    {
        return pageUrl_;
    }

    void SetPageUrl(const std::string& pageUrl)
    {
        pageUrl_ = pageUrl;
    }

    bool IsUserSelected() const
    {
        return isUserSelected_;
    }

    void SetUserSelectedFlag(bool isUserSelected)
    {
        isUserSelected_ = isUserSelected;
    }

    bool IsOtherAccount() const
    {
        return isOtherAccount_;
    }

    void SetOtherAccountFlag(bool isOtherAccount)
    {
        isOtherAccount_ = isOtherAccount;
    }

    std::string GetSource() const
    {
        return source_;
    }

    void SetSource(const std::string& source)
    {
        source_ = source;
    }

private:
    OHOS::NWeb::NWebAutofillEvent eventType_ = OHOS::NWeb::NWebAutofillEvent::UNKNOWN;
    std::string pageUrl_;
    bool isUserSelected_ = false;
    bool isOtherAccount_ = false;
    std::string source_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_WEB_VIEW_DATA_COMMON_H