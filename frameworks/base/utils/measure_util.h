/*
 * Copyright (c) 2022-2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_UTILS_MEASURE_UTIL_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_UTILS_MEASURE_UTIL_H

#include <string>

namespace OHOS::Ace {
struct MeasureContext {
    std::string textContent;
    double fontSize = 0.0;
    int32_t fontStyle = 0;
    std::string fontWeight;
    std::string fontFamily;
    double letterSpacing = 0.0;
};

class MeasureUtil {
public:
    static double MeasureText(const MeasureContext& context);
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_UTILS_MEASURE_UTIL_H
