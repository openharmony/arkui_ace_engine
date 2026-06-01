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
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_WEB_UTIL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_WEB_UTIL_H

#include <string>
#include <string_view>
#include <vector>
#include <unordered_set>
#include <map>

namespace OHOS::Ace {
class WebUtil {
public:
    static bool HasJSONDuplicateKeys(std::string_view json);
    template<typename T>
    static bool GetParamValue(const std::map<std::string, std::string>& param, const std::string& key, T& value)
    {
        auto it = param.find(key);
        if (it == param.end() || it->second.empty()) {
            return false;
        }

        const std::string& str = it->second;
        char* endptr = nullptr;

        if constexpr (std::is_same_v<T, int32_t>) {
            long result = std::strtol(str.c_str(), &endptr, 10);
            if (endptr == str || *endptr != '\0') {
                return false;
            }
            value = static_cast<int32_t>(result);
            return true;
        } else if constexpr (std::is_same_v<T, double>) {
            double result = std::strtod(str.c_str(), &endptr);
            if (endptr == str || *endptr != '\0') {
                return false;
            }
            value = result;
            return true;
        } else if constexpr (std::is_same_v<T, bool>) {
            value = (it->second == "true" || it->second == "1");
            return true;
        } else if constexpr (std::is_same_v<T, std::string>) {
            value = it->second;
            return true;
        }

        return false;
    }

private:
    WebUtil() = delete;
    static const size_t maxJsonDepth = 128; // depth limit

    static void SkipWhitespace(std::string_view json, size_t& i);
    static std::string ExtractString(std::string_view json, size_t& i);
    static void SkipNestedStructure(std::string_view json, size_t& i);
    static void SkipValue(std::string_view json, size_t& i);
    static bool HandleKeyDetection(std::string_view json, size_t& i,
                                   std::vector<std::unordered_set<std::string>>& stack);
};
} // namespace OHOS::Ace
#endif