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

#include "adapter/ohos/capability/feature_config/features/ui_node_gc_params_parser.h"
#include "core/common/ace_application_info.h"
#include "frameworks/core/common/extra_modules/extra_modules_manager.h"
#include "adapter/ohos/capability/feature_config/feature_param_manager.h"
#include "base/log/log.h"
#include "bundlemgr/bundle_mgr_proxy.h"

namespace OHOS::Ace {
namespace {
constexpr char UI_NODE_GC_FEATURE_NAME[] = "ui_node_gc";
constexpr char UI_NODE_GC_CAPABILITY_NAME[] = "IsUINodeGcEnabledForApp";
using IsUINodeGcEnabledForAppFunc = bool (*)(const char*);
} // namespace

ParseErrCode UINodeGcParamParser::ParseFeatureParam(xmlNode& node)
{
    void* funcPtr = nullptr;
    auto errorCode = ExtraModulesManager::GetInstance().GetCapability(
        UI_NODE_GC_FEATURE_NAME, UI_NODE_GC_CAPABILITY_NAME, &funcPtr);
    if (errorCode != ErrCode::SUCCESS || funcPtr == nullptr) {
        LOGW("Get uiNode GC capability failed, ret:%{public}d, func is null:%{public}d",
            static_cast<int32_t>(errorCode), static_cast<int32_t>(funcPtr == nullptr));
        FeatureParamManager::GetInstance().SetUINodeGcEnabled(false);
        return PARSE_EXEC_SUCCESS;
    }

    auto isUINodeGcEnabledForApp = reinterpret_cast<IsUINodeGcEnabledForAppFunc>(funcPtr);
    const auto& bundleName = AceApplicationInfo::GetInstance().GetPackageName();
    if (!isUINodeGcEnabledForApp(bundleName.c_str())) {
        LOGI("UINode GC is disabled for bundleName:%{public}s", bundleName.c_str());
        FeatureParamManager::GetInstance().SetUINodeGcEnabled(false);
        return PARSE_EXEC_SUCCESS;
    }

    bool xmlEnable = ExtractPropertyValue("enable", node) == "true";
    // Priority ： (xml false) > (meta data ture & false) > (xml true)
    if (!parseWithMetaData_ || !xmlEnable) {
        FeatureParamManager::GetInstance().SetUINodeGcEnabled(xmlEnable);
    }

    return PARSE_EXEC_SUCCESS;
}

ParseErrCode UINodeGcParamParser::ParseMetaData(const AppExecFwk::Metadata& metaData)
{
    parseWithMetaData_ = true;
    FeatureParamManager::GetInstance().SetUINodeGcEnabled(metaData.value == "true");
    return PARSE_EXEC_SUCCESS;
}
}  // namespace OHOS::Ace
