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

#ifndef FOUNDATION_ACE_INTERFACE_PARAM_CONFIG_H
#define FOUNDATION_ACE_INTERFACE_PARAM_CONFIG_H

#include <cstdint>

namespace OHOS::Ace {
struct ParamConfig {
    bool interactionInfo = false;
    bool accessibilityInfo = false;
    bool cacheNodes = true;
};

enum class ChangeType {
    PAGE = 0, // Navigation router
    SCROLL,   // scroll event
    SWIPER,   // Swiper content change
    TABS,     // Tabs content change
    TEXT,     // Text content significant change
    DIALOG,   // developer dialog pops up
    ARKWEB_PAGE,   // WebView transition content change
    ARKWEB_TEXT,   // WebView Text change
};

struct ContentChangeConfig {
    int32_t minReportTime = 100; // minimum report interval: 100 ms
    float textContentRatio = 0.15f; // ratio of a single text change bounding box area to window area: 0.15
};

} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_INTERFACE_PARAM_CONFIG_H
