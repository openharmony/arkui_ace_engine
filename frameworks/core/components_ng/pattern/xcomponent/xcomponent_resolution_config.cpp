/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/xcomponent/xcomponent_resolution_config.h"
#include "base/log/log.h"

namespace OHOS::Ace::NG {
XComponentResolutionConfig& XComponentResolutionConfig::GetInstance()
{
    static XComponentResolutionConfig instance;
    return instance;
}

XComponentResolutionConfig::XComponentResolutionConfig()
{
}

XComponentResolutionConfig::~XComponentResolutionConfig() noexcept
{
}

void XComponentResolutionConfig::GetApsSdrRatio(const std::string &pkgName, int32_t indexForUsingClient)
{
    if (indexForUsingClient < static_cast<int32_t>(IndexForUsingClient::XCOMPONENT_SIZE) ||
        indexForUsingClient > static_cast<int32_t>(IndexForUsingClient::XCOMPONENT_TOUCH)) {
        LOGE("[XComponentResolutionConfig]GetApsSdrRatio indexForUsingClient %{public}d invalid", indexForUsingClient);
        std::lock_guard<std::mutex> lock(SDR_RATIOS_MUTEX);
        SDR_RATIOS = std::vector<float>(INDEX_FOR_USING_CLIENT_SIZE, static_cast<float>(RatioValue::RATIO_READ_FAIL));
        return;
    }

    std::lock_guard<std::mutex> lock(SDR_RATIOS_MUTEX);
    int32_t sdrRatioVectorIndex = indexForUsingClient - 1;
    if (std::abs(SDR_RATIOS[sdrRatioVectorIndex]) - static_cast<float>(RatioValue::RATIO_NOT_SET) >
        std::numeric_limits<float>::epsilon()) {
        return;
    }
    SDR_RATIOS[sdrRatioVectorIndex] = ApsMonitorImpl::GetInstance().GetApsSdrRatio(pkgName, indexForUsingClient);
    if (SDR_RATIOS[sdrRatioVectorIndex] <= std::numeric_limits<float>::epsilon()) {
        SDR_RATIOS[sdrRatioVectorIndex] = static_cast<float>(RatioValue::RATIO_DEFAULT);
    }
    LOGD("XComponentResolutionConfig:GetApsSdrRatio pkg:%{public}s indexForUsingClient:%{public}d sdrRatio:%{public}f",
        pkgName.c_str(), indexForUsingClient, SDR_RATIOS[sdrRatioVectorIndex]);
}
};
