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

#include "interfaces/inner_api/ace/ui_content.h"
#include "base/json/json_util.h"
#include "base/utils/feature_manager.h"
#include "adapter/ohos/capability/feature_config/feature_param_manager.h"

#include "adapter/ohos/capability/feature_config/config_parser_base.h"
#include "adapter/ohos/capability/feature_config/features/sync_load_parser.h"
#include "adapter/ohos/capability/feature_config/features/ui_node_gc_params_parser.h"
#include "adapter/ohos/capability/feature_config/features/ui_correction_parser.h"
#include "base/log/log.h"
#include "base/utils/system_properties.h"
#include "bundlemgr/bundle_mgr_proxy.h"
#include "frameworks/core/common/extra_modules/extra_modules_manager.h"

namespace OHOS::Ace {
namespace {
bool ParseConfigBool(const std::unique_ptr<JsonValue>& jsonObject, const std::string& key)
{
    if (!jsonObject || !jsonObject->Contains(key)) {
        return false;
    }
    auto value = jsonObject->GetValue(key);
    if (!value) {
        return false;
    }
    if (value->IsBool()) {
        return value->GetBool();
    }
    if (value->IsString()) {
        return value->GetString() == "true";
    }
    return false;
}

FeatureParamManager::SmartLayoutFeatureConfig ParseSmartLayoutFeature(
    const std::unique_ptr<JsonValue>& jsonObject, const std::string& key)
{
    FeatureParamManager::SmartLayoutFeatureConfig config;
    if (!jsonObject || !jsonObject->Contains(key)) {
        return config;
    }
    auto featureObj = jsonObject->GetObject(key);
    if (!featureObj || !featureObj->IsObject()) {
        return config;
    }
    config.enabled = ParseConfigBool(featureObj, "enabled");
    if (!featureObj->Contains("values")) {
        return config;
    }
    auto valueArray = featureObj->GetValue("values");
    if (!valueArray || !valueArray->IsArray()) {
        return config;
    }
    int32_t size = valueArray->GetArraySize();
    for (int32_t i = 0; i < size; ++i) {
        auto item = valueArray->GetArrayItem(i);
        if (item && item->IsString()) {
            config.values.insert(item->GetString());
        }
    }
    return config;
}
} // namespace

#define ADD_PARSER_MODEL(cls)         \
    {                                 \
        #cls, std::make_shared<cls>() \
    }

SINGLETON_INSTANCE_IMPL(FeatureParamManager);

const std::unordered_map<std::string, std::shared_ptr<ConfigParserBase>> FeatureParamManager::featureParamMap_ = {
    ADD_PARSER_MODEL(UINodeGcParamParser),
    ADD_PARSER_MODEL(SyncLoadParser),
    ADD_PARSER_MODEL(UICorrectionParser),
};

const std::unordered_map<std::string, std::string> FeatureParamManager::metaDataMappingMap_ = {
    { "idle_delete", "UINodeGcParamParser" },
};

std::mutex FeatureParamManager::arkui_cloud_config_mutex_;
std::mutex FeatureParamManager::arkweb_cloud_config_mutex_;

FeatureParamManager::FeatureParamManager() = default;
FeatureParamManager::~FeatureParamManager() = default;

void FeatureParamManager::Init(const std::string& bundleName, std::vector<OHOS::AppExecFwk::Metadata>& metaData)
{
    MetaDataParseEntry(metaData);
    FeatureParamParseEntry(bundleName);
    UICorrectionParamParseEntry(bundleName);
    ExtraModulesManager::GetInstance().Init();
    ParseUICorrectionStrategyConfig();
}

void FeatureParamManager::ParseUICorrectionStrategyConfig()
{
    std::string strategyConfig;
    if (FeatureManager::GetInstance().GetFeatureParam("UICorrectionStrategy", strategyConfig) !=
        FeatureManager::SUCCESS) {
        LOGW("FeatureParamManager get UICorrectionStrategy from FeatureManager failed");
        return;
    }
    auto jsonValue = JsonUtil::ParseJsonString(strategyConfig);
    if (!jsonValue || !jsonValue->IsValid() || !jsonValue->IsObject()) {
        LOGW("FeatureParamManager failed to parse UICorrectionStrategy json string");
        return;
    }
    strategyPageOverflowEnabled_ = ParseConfigBool(jsonValue, "pageOverflowEnabled");
    strategyDialogOverflowEnabled_ = ParseConfigBool(jsonValue, "dialogOverflowEnabled");
    strategyRnOverflowEnabled_ = ParseConfigBool(jsonValue, "RNPageOverflowEnabled");
    if (!jsonValue->Contains("smartlayout")) {
        return;
    }
    auto smartlayoutObj = jsonValue->GetObject("smartlayout");
    if (!smartlayoutObj || !smartlayoutObj->IsObject()) {
        return;
    }
    smartlayoutPageOverflowFix_ = ParseSmartLayoutFeature(smartlayoutObj, "PageOverflowFix");
    smartlayoutWidgetSplit_ = ParseSmartLayoutFeature(smartlayoutObj, "WidgetSplit");
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
    if (uiCorrectionParser_ != nullptr) {
        LOGW("UICorrectionParamParseEntry init twice");
        return;
    }
    uiCorrectionParser_ = std::make_shared<ConfigParserBase>();
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
    if (featureParser_ != nullptr) {
        LOGW("FeatureParamParseEntry init twice");
        return;
    }
    featureParser_ = std::make_shared<ConfigParserBase>();
    if (featureParser_->LoadPerformanceConfigXML() != PARSE_EXEC_SUCCESS) {
        LOGW("ArkUiFeatureParamManager failed to load xml file");
        return;
    }

    if (featureParser_->ParsePerformanceConfigXMLWithBundleName(bundleName) != PARSE_EXEC_SUCCESS) {
        LOGW("ArkUiFeatureParamManager failed to parse xml file");
    }
}

void FeatureParamManager::SetSyncLoadEnableParam(bool enabled, uint32_t deadline, int64_t startupDelay)
{
    syncLoadEnabled_ = enabled;
    syncloadResponseDeadline_ = deadline;
    syncLoadStartupDelay_ = startupDelay;
}

bool FeatureParamManager::IsSyncLoadEnabled() const
{
    return syncLoadEnabled_ || SystemProperties::IsSyncLoadEnabled();
}

bool FeatureParamManager::IsPageOverflowEnabled()
{
    ParseArkUICorrectionConfigFromUIContent();
    std::lock_guard<std::mutex> lock(arkui_cloud_config_mutex_);
    return pageOverflowEnabledFromCloud_.value_or(pageOverflowEnabled_) || strategyPageOverflowEnabled_;
}

bool FeatureParamManager::IsDialogCorrectionEnabled()
{
    ParseArkUICorrectionConfigFromUIContent();
    std::lock_guard<std::mutex> lock(arkui_cloud_config_mutex_);
    return dialogCorrectionEnabledFromCloud_.value_or(dialogCorrectionEnabled_) || strategyDialogOverflowEnabled_;
}

bool FeatureParamManager::IsRnOverflowEnable()
{
    ParseArkUICorrectionConfigFromUIContent();
    std::lock_guard<std::mutex> lock(arkui_cloud_config_mutex_);
    return rnOverflowEnabledFromCloud_.value_or(rnOverflowEnabled_) || strategyRnOverflowEnabled_;
}

void FeatureParamManager::SetUiCorrectionEnableParam(bool pageOverflowEnabled, bool dialogCorrectionEnabled)
{
    pageOverflowEnabled_ = pageOverflowEnabled;
    dialogCorrectionEnabled_ = dialogCorrectionEnabled;
}

void FeatureParamManager::SetUiCorrectionRnEnableParam(bool rnOverflowEnabled)
{
    rnOverflowEnabled_ = rnOverflowEnabled;
}

bool FeatureParamManager::IsSmartLayoutEnabled() const
{
    return smartlayoutEnabled_;
}

void FeatureParamManager::SetSmartLayoutEnabled(bool enabled)
{
    smartlayoutEnabled_ = enabled;
}

bool FeatureParamManager::IsSmartLayoutPageOverflowFixEnabled(const std::string& pathHash) const
{
    if (!smartlayoutPageOverflowFix_.enabled) {
        return false;
    }
    if (pathHash.empty()) {
        return true;
    }
    return smartlayoutPageOverflowFix_.values.count(pathHash) > 0;
}

bool FeatureParamManager::IsSmartLayoutWidgetSplitEnabled(const std::string& pageUrl) const
{
    if (!smartlayoutWidgetSplit_.enabled) {
        return false;
    }
    if (pageUrl.empty()) {
        return true;
    }
    return smartlayoutWidgetSplit_.values.count(pageUrl) > 0;
}

uint32_t FeatureParamManager::GetSyncloadResponseDeadline() const
{
    return syncloadResponseDeadline_;
}

int64_t FeatureParamManager::GetSyncLoadStartupDelay() const
{
    return syncLoadStartupDelay_;
}

void FeatureParamManager::SetUINodeGcEnabled(bool enabled)
{
    uiNodeGcEnabled_ = enabled;
}

bool FeatureParamManager::IsUINodeGcEnabled() const
{
    return uiNodeGcEnabled_;
}

void FeatureParamManager::ParseArkUICorrectionConfigFromUIContent()
{
    std::lock_guard<std::mutex> lock(arkui_cloud_config_mutex_);
    if (hasParseArkUICorrectionConfig_) {
        return;
    }
    hasParseArkUICorrectionConfig_ = true;
    auto &configJsonStr = UIContent::GetUICorrectionConfig();
    if (configJsonStr.empty()) {
        return;
    }
    auto jsonValue = JsonUtil::ParseJsonString(configJsonStr);
    if (!jsonValue || !jsonValue->IsValid() || !jsonValue->IsObject()) {
        LOGE("FeatureParamManager failed to parse ui correction json string");
        return;
    }
    if (jsonValue->Contains("arkui")) {
        pageOverflowEnabledFromCloud_ = false;
        dialogCorrectionEnabledFromCloud_ = false;
        rnOverflowEnabledFromCloud_ = false;
    }
    auto arkUiConfig = jsonValue->GetObject("arkui");
    if (!arkUiConfig || !arkUiConfig->IsObject()) {
        LOGW("FeatureParamManager key of ui correction config is missing or invalid");
        return;
    }
    auto featureConfig = arkUiConfig->GetObject("feature");
    if (!featureConfig || !featureConfig->IsObject()) {
        LOGW("FeatureParamManager feature is missing or invalid");
        return;
    }
    pageOverflowEnabledFromCloud_ = ParseConfigBool(featureConfig, "pageOverflowEnabled");
    dialogCorrectionEnabledFromCloud_ = ParseConfigBool(featureConfig, "dialogOverflowEnabled");
    rnOverflowEnabledFromCloud_ = ParseConfigBool(featureConfig, "RNPageOverflowEnabled");
}

void FeatureParamManager::ParseArkWebAutoLayoutConfigFromUIContent()
{
    std::lock_guard<std::mutex> lock(arkweb_cloud_config_mutex_);
    if (hasParseArkWebAutoLayoutConfig_) {
        return;
    }
    hasParseArkWebAutoLayoutConfig_ = true;
    auto &configJsonStr = UIContent::GetUICorrectionConfig();
    if (configJsonStr.empty()) {
        arkWebJsonConfigStr_ = "";
        return;
    }
    auto jsonValue = JsonUtil::ParseJsonString(configJsonStr);
    if (!jsonValue || !jsonValue->IsValid() || !jsonValue->IsObject()) {
        LOGE("FeatureParamManager failed to parse auto layout config json string");
        return;
    }
    if (jsonValue->Contains("arkweb")) {
        arkWebJsonConfigStr_ = "{}";
    }
    auto arkWebConfig = jsonValue->GetObject("arkweb");
    if (!arkWebConfig || !arkWebConfig->IsObject()) {
        LOGW("FeatureParamManager: key of auto layout config is missing or invalid");
        return;
    }
    arkWebJsonConfigStr_ = arkWebConfig->ToString();
}

std::string FeatureParamManager::GetArkWebAutoLayoutConfig()
{
    ParseArkWebAutoLayoutConfigFromUIContent();
    std::lock_guard<std::mutex> lock(arkweb_cloud_config_mutex_);
    return arkWebJsonConfigStr_;
}
} // namespace OHOS::Ace
