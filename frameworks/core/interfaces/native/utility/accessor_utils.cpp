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

#include "core/interfaces/native/utility/accessor_utils.h"

bool AccessorUtils::CheckKeysPressed(const std::vector<std::string>& keysStrs,
    const std::vector<OHOS::Ace::KeyCode>& keysCodes)
{
    auto intersects =
        [](const std::vector<OHOS::Ace::KeyCode>& lv, const std::vector<OHOS::Ace::KeyCode>& rv) -> bool {
        bool found = false;
        for (const auto& key : lv) {
            auto it = std::find(rv.begin(), rv.end(), key);
            if (it != rv.end()) {
                found = true;
                break;
            }
        }
        return found;
    };
    std::unordered_map<std::string, std::vector<OHOS::Ace::KeyCode>> validKeyCodes = {
        { "ctrl", { OHOS::Ace::KeyCode::KEY_CTRL_LEFT, OHOS::Ace::KeyCode::KEY_CTRL_RIGHT } },
        { "shift", { OHOS::Ace::KeyCode::KEY_SHIFT_LEFT, OHOS::Ace::KeyCode::KEY_SHIFT_RIGHT } },
        { "alt", { OHOS::Ace::KeyCode::KEY_ALT_LEFT, OHOS::Ace::KeyCode::KEY_ALT_RIGHT } },
        { "fn", { OHOS::Ace::KeyCode::KEY_FN } }
    };
    for (const auto& str : keysStrs) {
        std::string code;
        std::transform(str.begin(), str.end(), std::back_inserter(code),
            [](const char& c) { return std::tolower(c); });
        auto it = validKeyCodes.find(code);
        if (it == validKeyCodes.end()) {
            return false;
        }
        if (!intersects(keysCodes, it->second)) {
            return false;
        }
    }
    return true;
}