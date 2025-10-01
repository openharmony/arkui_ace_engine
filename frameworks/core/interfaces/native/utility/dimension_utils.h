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

#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_DIMENSION_UTILS_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_DIMENSION_UTILS_H

#include "base/geometry/dimension.h"

namespace OHOS::Ace::NG::Converter {
class DimensionUtils {
public:
    inline static DimensionUnit DEFAULT_UNIT = DimensionUnit::VP;
};

class DefaultDimensionUnit {
public:
    DefaultDimensionUnit(DimensionUnit unit)
    {
        save_ = DimensionUtils::DEFAULT_UNIT;
        DimensionUtils::DEFAULT_UNIT = unit;
    }
    ~DefaultDimensionUnit()
    {
        DimensionUtils::DEFAULT_UNIT = save_;
    }

private:
    DimensionUnit save_;
};
} // namespace OHOS::Ace::NG::Converter
#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_DIMENSION_UTILS_H