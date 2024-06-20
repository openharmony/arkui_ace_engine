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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_I18N_TIME_FORMAT_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_I18N_TIME_FORMAT_H

#include <cstdint>
#include <functional>
#include <future>
#include <memory>
#include <mutex>
#include <new>
#include <string>
#include <vector>

#include "base/utils/date_util.h"
#include "base/utils/macros.h"
#include "base/utils/noncopyable.h"

namespace OHOS::Ace {

    enum class ZeroPrefixType : int32_t {
        AUTO = 0,
        HIDE = 1,
        SHOW = 2,
        OFF = 3
    };

    struct DateTimeType {
        ZeroPrefixType hourType;
        ZeroPrefixType minuteType;
        ZeroPrefixType secondType;
    };

class ACE_FORCE_EXPORT TimeFormat : public NonCopyable {
public:

    virtual ~TimeFormat() = default;

    static std::string GetHourFormat(const int32_t hourType, bool is24Hour) {
        if (hourType == static_cast<int32_t>(ZeroPrefixType::AUTO)) {
            return is24Hour ? "2-digit" : "numeric";
        } else if (hourType == static_cast<int32_t>(ZeroPrefixType::HIDE)) {
            return "numeric";
        } else if (hourType == static_cast<int32_t>(ZeroPrefixType::SHOW)) {
            return "2-digit";
        }
        return ""; // Handle invalid enum values gracefully
    }

    static std::string GetMinuteFormat(const int32_t minuteType) {
        if (minuteType == static_cast<int32_t>(ZeroPrefixType::AUTO)) {
            return "2-digit";
        } else if (minuteType == static_cast<int32_t>(ZeroPrefixType::HIDE)) {
            return "numeric";
        } else if (minuteType == static_cast<int32_t>(ZeroPrefixType::SHOW)) {
            return "2-digit";
        }
        return "";
    }

    static std::string GetSecondFormat(const int32_t secondType) {
        if (secondType == static_cast<int32_t>(ZeroPrefixType::AUTO)) {
            return "2-digit";
        } else if (secondType == static_cast<int32_t>(ZeroPrefixType::HIDE)) {
            return "numeric";
        } else if (secondType == static_cast<int32_t>(ZeroPrefixType::SHOW)) {
            return "2-digit";
        }
        return "";
    }
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_I18N_TIME_FORMAT_H