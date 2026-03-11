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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_XCOMPONENT_RESOLUTION_CONFIG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_XCOMPONENT_RESOLUTION_CONFIG_H

#include <memory>
#include <mutex>
#include <string>
#include <vector>

#include "adapter/ohos/entrance/aps_monitor_impl.h"

namespace OHOS::Ace::NG {
enum class RatioValue : int32_t {
    RATIO_READ_FAIL = -1,
    RATIO_NOT_SET = 0,
    RATIO_DEFAULT = 1,
};

enum class IndexForUsingClient : int32_t {
    XCOMPONENT_SIZE = 1,
    XCOMPONENT_TOUCH = 2,
};
constexpr int32_t INDEX_FOR_USING_CLIENT_SIZE = 2;

inline std::vector<float> SDR_RATIOS =
    std::vector<float>(INDEX_FOR_USING_CLIENT_SIZE, static_cast<float>(RatioValue::RATIO_NOT_SET));
inline std::mutex SDR_RATIOS_MUTEX;

class XComponentResolutionConfig {
public:
    static XComponentResolutionConfig& GetInstance();
    void GetApsSdrRatio(const std::string& pkgName, int32_t indexForUsingClient);

private:
    XComponentResolutionConfig();
    ~XComponentResolutionConfig() noexcept;
    XComponentResolutionConfig(const XComponentResolutionConfig&) = delete;
    XComponentResolutionConfig(const XComponentResolutionConfig&&) = delete;
    XComponentResolutionConfig& operator=(const XComponentResolutionConfig&) = delete;
    XComponentResolutionConfig& operator=(const XComponentResolutionConfig&&) = delete;
};
} // namespace OHOS::Ace::NG
 
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_XCOMPONENT_RESOLUTION_CONFIG_H
