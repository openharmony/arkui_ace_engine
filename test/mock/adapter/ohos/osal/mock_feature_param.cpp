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

#include <unordered_set>
#include <utility>
#include "base/utils/feature_param.h"

namespace {
constexpr int32_t DEFAULT_RESPONSE_DELAY = 50000000; // default max response delay is 50ms.

struct MockFeatureParamState {
    bool pageOverflowFixEnabled = false;
    std::unordered_set<std::string> pageOverflowFixWhitelist;
};

MockFeatureParamState& GetMockFeatureParamState()
{
    static MockFeatureParamState state;
    return state;
}
} // namespace

namespace OHOS::Ace {

bool FeatureParam::IsSyncLoadEnabled()
{
    return false;
}

uint32_t FeatureParam::GetSyncloadResponseDeadline()
{
    return DEFAULT_RESPONSE_DELAY;
}

int64_t FeatureParam::GetSyncLoadStartupDelay()
{
    return 0;
}

bool FeatureParam::IsUINodeGcEnabled()
{
    return false;
}

bool FeatureParam::IsPageOverflowEnabled()
{
    return false;
}

bool FeatureParam::IsRnOverflowEnable()
{
    return false;
}

bool FeatureParam::IsDialogCorrectionEnabled()
{
    return false;
}

std::string FeatureParam::GetArkWebAutoLayoutConfig()
{
    return "";
}

bool FeatureParam::IsSmartLayoutEnabled()
{
    return false;
}

bool FeatureParam::IsSmartLayoutPageOverflowFixEnabled(const std::string& pathHash)
{
    // Opt-in test hook: default flag stays false so existing tests see no behavior change.
    const auto& state = GetMockFeatureParamState();
    if (!state.pageOverflowFixEnabled) {
        return false;
    }
    if (pathHash.empty()) {
        return true;
    }
    return state.pageOverflowFixWhitelist.count(pathHash) > 0;
}

bool FeatureParam::IsSmartLayoutWidgetSplitEnabled(const std::string& pageUrl)
{
    return false;
}

// Test-only seam. ace_components_mock is a testonly library, so unconditional linkage is safe.
void SetMockFeatureParamPageOverflowFixEnabled(bool enabled)
{
    GetMockFeatureParamState().pageOverflowFixEnabled = enabled;
}

void SetMockFeatureParamPageOverflowFixWhitelist(std::unordered_set<std::string> whitelist)
{
    GetMockFeatureParamState().pageOverflowFixWhitelist = std::move(whitelist);
}

void ResetMockFeatureParam()
{
    GetMockFeatureParamState() = MockFeatureParamState {};
}
} // OHOS::Ace