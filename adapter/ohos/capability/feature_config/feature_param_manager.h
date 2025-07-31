/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_ADAPTER_OHOS_CAPABILITY_FEATURE_CONFIG_FEATURE_PARAM_MANAGER_H
#define FOUNDATION_ACE_ADAPTER_OHOS_CAPABILITY_FEATURE_CONFIG_FEATURE_PARAM_MANAGER_H

#include <string>

namespace OHOS::Ace {
class ConfigXMLParserBase;
class FeatureParamManager {
public:
    FeatureParamManager() = default;
    ~FeatureParamManager() = default;

    static FeatureParamManager& GetInstance()
    {
        static FeatureParamManager instance;
        return instance;
    }

    void Init(const std::string& bundleName);

    // SyncloadParser
    void SetSyncLoadEnableParam(bool enabled, uint32_t deadline);
    bool IsSyncLoadEnabled();
    uint32_t GetSyncloadResponseDeadline();
    // UINodeGcParamParser
    void SetUINodeGcEnabled(bool enabled);
    bool IsUINodeGcEnabled();

private:
    void FeatureParamParseEntry(const std::string& bundleName);
    static std::unordered_map<std::string, std::shared_ptr<ConfigXMLParserBase>> featureParamMap_;
    static constexpr uint32_t MAX_TIMER_SIZE = 3; // 3 is max size for responseDeadline
    static constexpr uint32_t DEFAULT_SYNCLOAD_DEADLINE = 50; // 50ms default time
    static constexpr uint32_t MS_TO_NS = 1000000; // 1000000 change time form ms to ns

    std::shared_ptr<ConfigXMLParserBase> featureParser_;
    // SyncloadParser
    bool syncLoadEnabled_ = false;
    uint32_t syncloadResponseDeadline_ = DEFAULT_SYNCLOAD_DEADLINE * MS_TO_NS;
    // UINodeGcParamParser
    bool uiNodeGcEnabled_ = false;

    friend class ConfigXMLParserBase;
    friend class SyncloadParser;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_ADAPTER_OHOS_CAPABILITY_FEATURE_CONFIG_FEATURE_PARAM_MANAGER_H
