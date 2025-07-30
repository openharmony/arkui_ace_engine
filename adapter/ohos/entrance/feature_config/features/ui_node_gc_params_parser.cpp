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

#include "ui_node_gc_params_parser.h"

#include "base/utils/system_properties.h"
#include "interfaces/inner_api/ace/arkui_log.h"

namespace OHOS::Ace {
bool UINodeGcParamParser::enabled_ = false;

bool UINodeGcParamParser::IsUINodeGcEnable()
{
    return enabled_;
}

ParseErrCode UINodeGcParamParser::ParseFeatureParam(xmlNode& node)
{
    enabled_ = ExtractPropertyValue("enable", node) == "true";
    LOGI("UINodeGcParamParser::ParseFeatureParam UINodeGcParamParser, %{public}d", enabled_);
    SystemProperties::SetUINodeGcEnable(enabled_);
    return PARSE_EXEC_SUCCESS;
}

}  // namespace OHOS::Ace