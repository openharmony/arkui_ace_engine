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


#include "base/log/dump_log.h"
#include "core/accessibility/hidumper/accessibility_hidumper.h"
#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace {

bool AccessibilityHidumper::DumpProcessInjectActionParameters(
    const std::vector<std::string>& params,
    int64_t& nodeId,
    int32_t& result,
    InjectActionType& actionType)
{
    constexpr int32_t NUM_PARAMETERS_DIMENSION = 1;
    if (params.size() < 1) {
        return false;
    }

    for (auto arg = params.begin(); arg != params.end(); ++arg) {
        if (*arg == "--inject-action") {
            if (std::distance(arg, params.end()) <= NUM_PARAMETERS_DIMENSION) {
                DumpLog::GetInstance().Print(std::string("Error: parameters need with data"));
                return false;
            }
            ++arg;
            nodeId = StringUtils::StringToLongInt(*arg, -1);
        } else if (*arg == "--NotifyChildAction") {
            if (std::distance(arg, params.end()) <= NUM_PARAMETERS_DIMENSION) {
                DumpLog::GetInstance().Print(std::string("Error: parameters need with data"));
                return false;
            }
            ++arg;
            result = StringUtils::StringToInt(*arg, 0);
            actionType = InjectActionType::NOTIFY_CHILD_ACTION;
            return true;
        }  else if (*arg == "--SecurityClickAction") {
            actionType = InjectActionType::SECURITY_CLICK_ACTION;
            return true;
        }
    }
    return false;
}
}  // namespace OHOS::Ace
