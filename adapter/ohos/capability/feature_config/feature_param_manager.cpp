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

#include "adapter/ohos/capability/feature_config/feature_param_manager.h"

#include "adapter/ohos/capability/feature_config/config_xml_parser_base.h"
#include "adapter/ohos/capability/feature_config/features/sync_load_parser.h"
#include "adapter/ohos/capability/feature_config/features/ui_node_gc_params_parser.h"
#include "base/log/log.h"
#include "base/utils/system_properties.h"

namespace OHOS::Ace {
#define ADD_PARSER_MODLE(cls)         \
    {                                 \
        #cls, std::make_shared<cls>() \
    }

const std::unordered_map<std::string, std::shared_ptr<ConfigXMLParserBase>> FeatureParamManager::featureParamMap_ = {
    ADD_PARSER_MODLE(UINodeGcParamParser),
    ADD_PARSER_MODLE(SyncloadParser),
};

FeatureParamManager::FeatureParamManager() = default;
FeatureParamManager::~FeatureParamManager() = default;

void FeatureParamManager::Init(const std::string& bundleName)
{
    FeatureParamParseEntry(bundleName);
}

void FeatureParamManager::FeatureParamParseEntry(const std::string& bundleName)
{
    if (!featureParser_) {
        featureParser_ = std::make_shared<ConfigXMLParserBase>();
    }

    if (featureParser_->LoadPerformanceConfigXML() != PARSE_EXEC_SUCCESS) {
        LOGW("ArkUiFeatureParamManager failed to load xml file");
        return;
    }

    if (featureParser_->ParsePerformanceConfigXMLWithBundleName(bundleName) != PARSE_EXEC_SUCCESS) {
        LOGW("ArkUiFeatureParamManager failed to parse xml file");
    }
}

void FeatureParamManager::SetSyncLoadEnableParam(bool enabled, uint32_t deadline)
{
    syncLoadEnabled_ = enabled;
    syncloadResponseDeadline_ = deadline;
}

bool FeatureParamManager::IsSyncLoadEnabled() const
{
    return syncLoadEnabled_ || SystemProperties::IsSyncLoadEnabled();
}

uint32_t FeatureParamManager::GetSyncloadResponseDeadline() const
{
    return syncloadResponseDeadline_;
}

void FeatureParamManager::SetUINodeGcEnabled(bool enabled)
{
    uiNodeGcEnabled_ = enabled;
}

bool FeatureParamManager::IsUINodeGcEnabled() const
{
    return uiNodeGcEnabled_;
}
} // namespace OHOS::Ace
