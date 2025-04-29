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

#ifndef FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_BASE_UTILS_MEASURE_UTILS_H
#define FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_BASE_UTILS_MEASURE_UTILS_H

#include <cstdint>
#include <string>

#include "ui/base/geometry/dimension.h"
#include "ui/base/geometry/ng/size_t.h"

namespace OHOS::Ace::Kit {

struct MeasureContext {
    std::string data;
    Dimension fontSize;
};

class ACE_FORCE_EXPORT MeasureUtils final {
public:
    static NG::SizeF GetMeasureTextSize(const MeasureContext& context);
};
} // OHOS::Ace::Kit

#endif // FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_BASE_UTILS_MEASURE_UTIL_H