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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_PAGE_URL_CHECKER_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_PAGE_URL_CHECKER_H

#include "base/memory/ace_type.h"

namespace OHOS::Ace {
extern const char BUNDLE_TAG[];

class ACE_EXPORT PageUrlChecker : public AceType {
    DECLARE_ACE_TYPE(PageUrlChecker, AceType)

public:
    virtual void LoadPageUrl(const std::string& url, const std::function<void()>& callback,
        const std::function<void(int32_t, const std::string&)>& silentInstallErrorCallBack) = 0;
    virtual void CheckPreload(const std::string& url) {}

    virtual void NotifyPageShow(const std::string& pageName) {}
    virtual void NotifyPageHide(const std::string& pageName) {}
    virtual void SetModuleNameCallback(std::function<std::string(const std::string&)>&& callback) {}
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_PAGE_URL_CHECKER_H