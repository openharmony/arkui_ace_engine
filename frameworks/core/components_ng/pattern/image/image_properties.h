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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_IMAGE_IMAGE_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_IMAGE_IMAGE_PROPERTY_H

#include <string>

#include "base/geometry/calc_dimension.h"
#include "base/image/pixel_map.h"

namespace OHOS::Ace {

struct ImageProperties {
    std::string src;
    RefPtr<PixelMap> pixelMap;
    std::string bundleName;
    std::string moduleName;
    CalcDimension width;
    CalcDimension height;
    CalcDimension top;
    CalcDimension left;
    int32_t duration = 0;

    bool operator==(const ImageProperties& info) const
    {
        bool pixelMapEqual = false;
        if (!pixelMap && !info.pixelMap) {
            pixelMapEqual = true;
        } else if (pixelMap && info.pixelMap) {
            pixelMapEqual = pixelMap->GetPixels() == info.pixelMap->GetPixels() &&
                            pixelMap->GetRawPixelMapPtr() == info.pixelMap->GetRawPixelMapPtr();
        }
        return src == info.src && pixelMapEqual &&
               bundleName == info.bundleName && moduleName == info.moduleName && width == info.width &&
               height == info.height && top == info.top && left == info.left && duration == info.duration;
    }
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_IMAGE_IMAGE_PROPERTY_H
