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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_SVG_UTILS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_SVG_UTILS_H

#include "base/geometry/rect.h"

namespace OHOS::Ace::NG {

class SvgUtils {
private:
    SvgUtils() = default;
    ~SvgUtils() = default;
public:
    static void CalculateSvgConentSize(Size& svgContentSize, const Size& svgContainerSize,
        const Size& svgSize, const Rect& viewBox);
    static bool IsFeatureEnable(uint32_t featureVersion, uint32_t usrConfigVersion);
};
}
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_SVG_UTILS_H