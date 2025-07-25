/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "core/interfaces/native/utility/peer_utils.h"

namespace OHOS::Ace::NG {
std::vector<std::string> PeerUtils::CreateAIError(OHOS::Ace::ImageAnalyzerState state)
{
    constexpr auto ERROR_CODE_AI_ANALYSIS_UNSUPPORTED = 110001;
    constexpr auto ERROR_CODE_AI_ANALYSIS_IS_ONGOING = 110002;
    constexpr auto ERROR_CODE_AI_ANALYSIS_IS_STOPPED = 110003;
    std::vector<std::string> error;
    switch (state) {
        case OHOS::Ace::ImageAnalyzerState::UNSUPPORTED:
            error.push_back(std::to_string(ERROR_CODE_AI_ANALYSIS_UNSUPPORTED));
            break;
        case OHOS::Ace::ImageAnalyzerState::ONGOING:
            error.push_back(std::to_string(ERROR_CODE_AI_ANALYSIS_IS_ONGOING));
            break;
        case OHOS::Ace::ImageAnalyzerState::STOPPED:
            error.push_back(std::to_string(ERROR_CODE_AI_ANALYSIS_IS_STOPPED));
            break;
        default:
            break;
    }
    return error;
}
} // namespace OHOS::Ace::NG
