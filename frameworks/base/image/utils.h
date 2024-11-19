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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_IMAGE_UTILS_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_IMAGE_UTILS_H

#include "core/components/common/layout/constants.h"

namespace OHOS::Ace {

// convert image orientation to actual angle
inline int32_t ConvertOrientationToDegree(ImageRotateOrientation orientation)
{
    switch (orientation) {
        case ImageRotateOrientation::UP:
            return 0;
        case ImageRotateOrientation::RIGHT:
            return 90;
        case ImageRotateOrientation::DOWN:
            return 180;
        case ImageRotateOrientation::LEFT:
            return 270;
        case ImageRotateOrientation::AUTO:
            return 360;
        default:
            return 0;
    }
}

// convert actual angle to image orientation
inline ImageRotateOrientation ConvertDegreeToOrientation(int32_t degree)
{
    switch (degree) {
        case 0:
            return ImageRotateOrientation::UP;
        case 90:
            return ImageRotateOrientation::RIGHT;
        case 180:
            return ImageRotateOrientation::DOWN;
        case 270:
            return ImageRotateOrientation::LEFT;
        case 360:
            return ImageRotateOrientation::AUTO;
        default:
            return ImageRotateOrientation::UP;
    }
}
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_IMAGE_UTILS_H
