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

#ifndef FOUNDATION_ACE_INTERFACE_UI_TRANSLATE_REQUEST_UTIL_H
#define FOUNDATION_ACE_INTERFACE_UI_TRANSLATE_REQUEST_UTIL_H

#include <cstdint>
#include <string>
#include <utility>
#include <vector>

#include "iremote_object.h"
#include "ui_content_service_interface.h"

namespace OHOS::Ace::PageTranslateRequestUtil {
inline constexpr int32_t ARKWEB_TRANSLATE_SCOPE = static_cast<int32_t>(TranslateContentScope::ARKWEB_ONLY);
inline constexpr int32_t ARKUI_TRANSLATE_SCOPE = static_cast<int32_t>(TranslateContentScope::ARKUI_ONLY);
inline constexpr int32_t XCOMPONENT_TRANSLATE_SCOPE = static_cast<int32_t>(TranslateContentScope::XCOMPONENT);
inline constexpr int32_t CANVAS_TRANSLATE_SCOPE = static_cast<int32_t>(TranslateContentScope::CANVAS_NODE);
inline constexpr int32_t ARKUI_ARKWEB_TRANSLATE_SCOPE = static_cast<int32_t>(TranslateContentScope::ARKUI_ARKWEB);
inline constexpr int32_t PAGE_ALL_TRANSLATE_SCOPE = static_cast<int32_t>(TranslateContentScope::PAGE_ALL);

struct TranslateResult {
    int32_t nodeId = -1;
    int64_t version = 0;
    std::string translatedText;
};

bool IsTranslateScopeValid(int32_t scope);
bool IsPageTranslateRequestValid(const std::string& request);
std::string DecodeJsonUnicodeEscapes(const std::string& text);
std::vector<std::pair<int32_t, int64_t>> ParseTranslateResultIdentities(const std::string& content);
bool ParseTranslateResults(const std::string& content, std::vector<TranslateResult>& results);
} // namespace OHOS::Ace::PageTranslateRequestUtil

#endif // FOUNDATION_ACE_INTERFACE_UI_TRANSLATE_REQUEST_UTIL_H
