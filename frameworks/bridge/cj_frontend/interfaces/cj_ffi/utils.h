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

#ifndef OHOS_ACE_FRAMEWORK_UTILS_H
#define OHOS_ACE_FRAMEWORK_UTILS_H

#include <cstdint>
#include <memory>
#include <string>

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"
#include "core/common/container.h"
#include "core/common/frontend.h"

extern "C" struct ExternalString {
    const char* value;
    void (*free)(const void*);
};

namespace OHOS::Ace::Framework {

class CJ_EXPORT Utils {
public:
    static bool CheckParamsValid(int32_t index, size_t length)
    {
        return size_t(index) < length;
    }

    static ExternalString MallocCString(const std::string& origin);

    static RefPtr<Frontend> GetCurrentFrontend();

    static std::string GetFunctionKey(int32_t functionKey);

    template<typename T>
    static T CheckRange(T min, T max, T defaultValue, T value)
    {
        if (value < min || value > max) {
            return defaultValue;
        }
        return value;
    }

    template<typename T>
    static T CheckMin(T min, T defaultValue, T value)
    {
        if (value < min) {
            return defaultValue;
        }
        return value;
    }
};

}
#endif // OHOS_ACE_FRAMEWORK_UTILS_H
