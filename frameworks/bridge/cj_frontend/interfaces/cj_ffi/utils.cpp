/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "bridge/cj_frontend/interfaces/cj_ffi/utils.h"


using namespace OHOS::Ace;
using namespace OHOS::Ace::Framework;

ExternalString Utils::MallocCString(const std::string& origin)
{
    if (origin.empty()) {
        return {nullptr, nullptr};
    }
    auto len = origin.length() + 1;
    char* res = (char*)malloc(sizeof(char) * len);
    if (res == nullptr) {
        return {nullptr, nullptr};
    }
    std::char_traits<char>::copy(res, origin.c_str(), len);
    return {res, reinterpret_cast<void(*)(const void*)>(free)};
}

RefPtr<Frontend> Utils::GetCurrentFrontend()
{
    auto container = Container::Current();
    if (!container) {
        container = Container::GetActive();
        if (!container) {
            LOGE("Can not found valid container");
            return nullptr;
        }
    }
    return container->GetFrontend();
}

std::string Utils::GetFunctionKey(int32_t functionKey)
{
    std::map<FunctionKey, std::string> keyNameMap {
        {FunctionKey::ESC, "ESC"},
        {FunctionKey::F1, "F1"},
        {FunctionKey::F2, "F2"},
        {FunctionKey::F3, "F3"},
        {FunctionKey::F4, "F4"},
        {FunctionKey::F5, "F5"},
        {FunctionKey::F6, "F6"},
        {FunctionKey::F7, "F7"},
        {FunctionKey::F8, "F8"},
        {FunctionKey::F9, "F9"},
        {FunctionKey::F10, "F10"},
        {FunctionKey::F11, "F11"},
        {FunctionKey::F12, "F12"},
        {FunctionKey::TAB, "TAB"},
        {FunctionKey::DPAD_UP, "DPAD_UP"},
        {FunctionKey::DPAD_DOWN, "DPAD_DOWN"},
        {FunctionKey::DPAD_LEFT, "DPAD_LEFT"},
        {FunctionKey::DPAD_RIGHT, "DPAD_RIGHT"}
    };
    auto result = keyNameMap.find(static_cast<FunctionKey>(functionKey));
    return (result != keyNameMap.end()) ? result->second : std::string();
}
