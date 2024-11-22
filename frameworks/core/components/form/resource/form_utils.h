/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_FORM_RESOURCE_FORM_UTILS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_FORM_RESOURCE_FORM_UTILS_H

#include <string>
#include "want.h"

namespace OHOS::Ace {

class FormUtils {
public:
    FormUtils() = default;
    virtual ~FormUtils() = default;

    virtual int32_t RouterEvent(const int64_t formId, const std::string& action, const int32_t containerId,
        const std::string& defualtbundleName);

    virtual int32_t RequestPublishFormEvent(const AAFwk::Want& want,
        const std::string& formBindingDataStr, int64_t& formId, std::string &errMsg);

    virtual int32_t BackgroundEvent(const int64_t formId, const std::string& action, const int32_t containerId,
        const std::string& defualtbundleName);
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_FORM_RESOURCE_FORM_UTILS_H