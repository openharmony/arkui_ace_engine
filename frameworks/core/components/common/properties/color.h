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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_PROPERTIES_COLOR_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_PROPERTIES_COLOR_H

#include <cstdint>
#include <string>

#include "base/utils/macros.h"
#include "base/utils/string_utils.h"

#include "ui/properties/color.h"
#include "ui/properties/linear_color.h"

namespace OHOS::Ace {

enum class ForegroundColorStrategy : char {
    NONE,
    INVERT,
};

namespace StringUtils {

inline void StringSplitter(const std::string& source, char delimiter, std::vector<Color>& out)
{
    using Func = Color (*)(const std::string&);
    Func func = [](const std::string& value) { return Color::FromString(value); };
    StringSplitter(source, delimiter, func, out);
}

} // namespace StringUtils

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_PROPERTIES_COLOR_H
