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

#include "form_special_style.h"

namespace OHOS::Ace::NG {
constexpr char TIME_LIMIT_RESOURCE_NAME[] = "form_disable_time_limit";
constexpr char APP_LOCK_RESOURCE_NAME[] = "ohos_app_has_locked";

void FormSpecialStyle::SetIsForbiddenByParentControl(bool isForbiddenByParentControl)
{
    isForbiddenByParentControl_ = isForbiddenByParentControl;
}

void FormSpecialStyle::SetIsLockedByAppLock(bool isLockedByAppLock)
{
    isLockedByAppLock_ = isLockedByAppLock;
}

const char* FormSpecialStyle::GetResource()
{
    auto formStyleAttribution = GetFormStyleAttribution();
    if (formStyleAttribution == FormStyleAttribution::PARENT_CONTROL) {
        return TIME_LIMIT_RESOURCE_NAME;
    }
    if (formStyleAttribution == FormStyleAttribution::APP_LOCK) {
        return APP_LOCK_RESOURCE_NAME;
    }
    return nullptr;
}

FormOperation FormSpecialStyle::GetOperationToNewFormStyle(const FormSpecialStyle& formSpecialStyle)
{
    auto oldFormStyleAttribution = GetFormStyleAttribution();
    auto newFormStyleAttribution = formSpecialStyle.GetFormStyleAttribution();
    if (oldFormStyleAttribution == newFormStyleAttribution) {
        return FormOperation::KEEP;
    }
    if (oldFormStyleAttribution == FormStyleAttribution::NORMAL) {
        return FormOperation::LOAD;
    }
    if (newFormStyleAttribution == FormStyleAttribution::NORMAL) {
        return FormOperation::UNLOAD;
    }
    return FormOperation::REFRESH;
}

FormStyleAttribution FormSpecialStyle::GetFormStyleAttribution() const
{
    if (isForbiddenByParentControl_) {
        return FormStyleAttribution::PARENT_CONTROL;
    }
    if (isLockedByAppLock_) {
        return FormStyleAttribution::APP_LOCK;
    }
    return FormStyleAttribution::NORMAL;
}

bool FormSpecialStyle::IsNeedToShowSpecialStyle()
{
    return GetFormStyleAttribution() != FormStyleAttribution::NORMAL;
}
} // namespace OHOS::Ace::NG
