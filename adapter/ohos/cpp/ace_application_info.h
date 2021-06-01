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

#ifndef FOUNDATION_ACE_ADAPTER_COMMON_CPP_ACE_APPLICATION_INFO_H
#define FOUNDATION_ACE_ADAPTER_COMMON_CPP_ACE_APPLICATION_INFO_H

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "base/utils/noncopyable.h"
#include "core/common/ace_application_info.h"

namespace OHOS::Ace::Platform {

class AceApplicationInfoImpl : public AceApplicationInfo {
public:
    AceApplicationInfoImpl();
    ~AceApplicationInfoImpl() override;

    static AceApplicationInfoImpl& GetInstance();

    void SetLocale(const std::string& language, const std::string& countryOrRegion, const std::string& script,
        const std::string& keywordsAndValues) override;
    void ChangeLocale(const std::string& language, const std::string& countryOrRegion) override;
    std::vector<std::string> GetLocaleFallback(const std::vector<std::string>& localeList) const override;
    std::vector<std::string> GetResourceFallback(const std::vector<std::string>& resourceList) const override
    {
        return std::vector<std::string>();
    }
    double GetLifeTime() const override { return 0.0f; }
    std::string GetCurrentDeviceResTag() const override { return std::string(); };
    bool GetFiles(const std::string& filePath, std::vector<std::string>& fileList) const override;

    bool GetBundleInfo(const std::string& packageName, AceBundleInfo& bundleInfo) override;

    std::string GetJsEngineParam(const std::string& key) const override;

    void SetJsEngineParam(const std::string& key, const std::string& value);

    void SetResourceManager(std::shared_ptr<Global::Resource::ResourceManager>& resourceManager) override
    {
        resourceManager_ = resourceManager;
    }

private:
    std::vector<std::string> SplitLocale(const std::string& desireLocales);

    std::map<std::string, std::string> jsEngineParams_;
    std::shared_ptr<Global::Resource::ResourceManager> resourceManager_;
};

} // namespace OHOS::Ace::Platform

#endif // FOUNDATION_ACE_ADAPTER_COMMON_CPP_ACE_APPLICATION_INFO_H
