/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "base/i18n/localization.h"

#include <cstdarg>

#ifndef WINDOWS_PLATFORM
#include "securec.h"
#endif

namespace OHOS::Ace {
namespace {

const size_t MAX_FORMAT_BUFFER = 256;

}

const std::string FormatEntry(const char* fmt, ...)
{
    char buf[MAX_FORMAT_BUFFER] = { 0 };
    bool ret = false;
    va_list args;
    va_start(args, fmt);
    if (vsnprintf_s(buf, sizeof(buf), sizeof(buf) - 1, fmt, args) < 0) {
        ret = true;
    }
    va_end(args);
    return ret ? "" : buf;
}

} // namespace OHOS::Ace
