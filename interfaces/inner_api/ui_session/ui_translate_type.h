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

#ifndef FOUNDATION_ACE_INTERFACE_UI_TRANSLATE_TYPE_H
#define FOUNDATION_ACE_INTERFACE_UI_TRANSLATE_TYPE_H

#include <cstdint>
#include <string>

namespace OHOS::Ace {
enum class TranslateContentScope : int32_t {
    ARKWEB_ONLY = 1 << 0,
    ARKUI_ONLY = 1 << 1,
    XCOMPONENT = 1 << 2,
    CANVAS_NODE = 1 << 3,
    ARKUI_ARKWEB = static_cast<int32_t>(ARKUI_ONLY) | static_cast<int32_t>(ARKWEB_ONLY),
    PAGE_ALL = static_cast<int32_t>(ARKUI_ARKWEB) | static_cast<int32_t>(XCOMPONENT) |
               static_cast<int32_t>(CANVAS_NODE),
};

struct TranslateTextRequest {
    TranslateContentScope scope = TranslateContentScope::ARKUI_ARKWEB;
    std::string extraData;
};

struct TranslateTextNode {
    int32_t nodeId = -1;
    std::string text;
    int64_t version = 0;
};

struct TranslateResult {
    int32_t nodeId = -1;
    std::string translatedText;
    int64_t version = 0;
};

struct AbilityLanguageInfo {
    std::string language;
    std::string region;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_INTERFACE_UI_TRANSLATE_TYPE_H
