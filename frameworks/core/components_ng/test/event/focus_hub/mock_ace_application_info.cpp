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

#include "adapter/ohos/entrance/ace_application_info.h"

namespace OHOS::Ace::Platform {
AceApplicationInfoImpl::AceApplicationInfoImpl() {}

AceApplicationInfoImpl::~AceApplicationInfoImpl() = default;

std::string AceApplicationInfoImpl::GetJsEngineParam(const std::string& /* key */) const
{
    return "";
}

void AceApplicationInfoImpl::ChangeLocale(const std::string& language, const std::string& countryOrRegion) {}

void AceApplicationInfoImpl::SetLocale(const std::string& language, const std::string& countryOrRegion,
    const std::string& script, const std::string& keywordsAndValues)
{}

bool AceApplicationInfoImpl::GetBundleInfo(const std::string& /* packageName */, AceBundleInfo& /* bundleInfo */)
{
    return false;
}

AceApplicationInfoImpl& AceApplicationInfoImpl::GetInstance()
{
    static AceApplicationInfoImpl instance;
    return instance;
}
} // namespace OHOS::Ace::Platform

namespace OHOS::Ace {
AceApplicationInfo& AceApplicationInfo::GetInstance()
{
    return Platform::AceApplicationInfoImpl::GetInstance();
}
} // namespace OHOS::Ace
