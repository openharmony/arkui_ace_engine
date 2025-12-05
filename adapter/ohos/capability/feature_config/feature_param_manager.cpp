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

#include "adapter/ohos/capability/feature_config/config_parser_base.h"
#include "adapter/ohos/capability/feature_config/features/sync_load_parser.h"
#include "adapter/ohos/capability/feature_config/features/ui_node_gc_params_parser.h"
#include "adapter/ohos/capability/feature_config/features/ui_correction_parser.h"
#include "base/log/log.h"
#include "base/utils/system_properties.h"
#include "bundlemgr/bundle_mgr_proxy.h"

namespace OHOS::Ace {
#define ADD_PARSER_MODEL(cls)         \
    {                                 \
        #cls, std::make_shared<cls>() \
    }

const std::unordered_map<std::string, std::shared_ptr<ConfigParserBase>> FeatureParamManager::featureParamMap_ = {
    ADD_PARSER_MODEL(UINodeGcParamParser),
    ADD_PARSER_MODEL(SyncLoadParser),
    ADD_PARSER_MODEL(UICorrectionParser),
};

const std::unordered_map<std::string, std::string> FeatureParamManager::metaDataMappingMap_ = {
    { "idle_delete", "UINodeGcParamParser" },
};

FeatureParamManager::FeatureParamManager() = default;
FeatureParamManager::~FeatureParamManager() = default;

void FeatureParamManager::Init(const std::string& bundleName, std::vector<OHOS::AppExecFwk::Metadata>& metaData)
{
    MetaDataParseEntry(metaData);
    FeatureParamParseEntry(bundleName);
    UICorrectionParamParseEntry(bundleName);
}

void FeatureParamManager::MetaDataParseEntry(std::vector<OHOS::AppExecFwk::Metadata>& metaData)
{
    for (const auto& meta : metaData) {
        auto metaIt = metaDataMappingMap_.find(meta.name);
        if (metaIt == metaDataMappingMap_.end()) {
            continue;
        }
        auto featureIt = featureParamMap_.find(metaIt->second);
        if (featureIt == featureParamMap_.end()) {
            continue;
        }

        auto ret = featureIt->second->ParseMetaData(meta);
        if (ret != PARSE_EXEC_SUCCESS) {
            LOGW("meta data name:%{public}s value:%{public}s resource:%{public}s ret:%{public}d",
                meta.name.c_str(), meta.value.c_str(), meta.resource.c_str(), static_cast<int32_t>(ret));
        }
    }
}

void FeatureParamManager::UICorrectionParamParseEntry(const std::string& bundleName)
{
    if (!uiCorrectionParser_) {
        uiCorrectionParser_ = std::make_shared<ConfigParserBase>();
    }
    if (uiCorrectionParser_->LoadUICorrectionConfigXML() != PARSE_EXEC_SUCCESS) {
        LOGW("ArkUiFeatureParamManager failed to load UI correction config file");
        return;
    }
    if (uiCorrectionParser_->ParseUICorrectionConfigXMLWithBundleName(bundleName) != PARSE_EXEC_SUCCESS) {
        LOGW("ArkUiFeatureParamManager failed to parse UI correction config file");
    }
}

void FeatureParamManager::FeatureParamParseEntry(const std::string& bundleName)
{
    if (!featureParser_) {
        featureParser_ = std::make_shared<ConfigParserBase>();
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

bool FeatureParamManager::IsPageOverflowEnabled() const
{
    return pageOverflowEnabled_;
}

bool FeatureParamManager::IsDialogCorrectionEnabled() const
{
    return dialogCorrectionEnabled_;
}

void FeatureParamManager::SetUiCorrectionEnableParam(bool pageOverflowEnabled, bool dialogCorrectionEnabled)
{
    pageOverflowEnabled_ = pageOverflowEnabled;
    dialogCorrectionEnabled_ = dialogCorrectionEnabled;
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
