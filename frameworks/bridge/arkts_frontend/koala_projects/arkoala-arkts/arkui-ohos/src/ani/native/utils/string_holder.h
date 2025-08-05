/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef KOALA_PROJECTS_ARKOALA_ARKTS_ARKUI_OHOS_STRING_HOLDER_H
#define KOALA_PROJECTS_ARKOALA_ARKTS_ARKUI_OHOS_STRING_HOLDER_H

#include <cstring>
#include <list>
#include <string>

#include "log/log.h"
#include "securec.h"

namespace OHOS::Ace::Ani {

class StringHolder final {
public:
    StringHolder() = default;
    StringHolder(const StringHolder&) = delete; // disable copy
    StringHolder(StringHolder&&) = delete;
    StringHolder& operator=(const StringHolder&) = delete;
    StringHolder& operator=(StringHolder&&) = delete;
    ~StringHolder()
    {
        for (const auto& ptr: strings_) {
            delete[] ptr;
        }
    }
    const char* CreateCString(const std::string& str)
    {
        auto size = str.length() + 1;
        char* cStr = new char[size];
        auto errCode = strcpy_s(cStr, size, str.c_str());
        if (errCode != 0) {
            HILOGW("strcpy_s error in StringHolder, errorCode:%{public}d", errCode);
            cStr[0] = '\0';
        }
        strings_.emplace_back(cStr);
        return cStr;
    }

private:
    std::list<char*> strings_;
};
} // namespace OHOS::Ace::Ani

#endif // KOALA_PROJECTS_ARKOALA_ARKTS_ARKUI_OHOS_STRING_HOLDER_H
