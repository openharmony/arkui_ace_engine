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

#include "adapter/ohos/capability/feature_config/feature_param_manager.h"

namespace OHOS::Ace {
ParseErrCode UINodeGcParamParser::ParseFeatureParam(xmlNode& node)
{
    auto& instance = FeatureParamManager::GetInstance();
    instance.SetUINodeGcEnabled(ExtractPropertyValue("enable", node) == "true");
    return PARSE_EXEC_SUCCESS;
}

}  // namespace OHOS::Ace
