/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_IMAGE_ACE_PICTURE_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_IMAGE_ACE_PICTURE_H

#include <memory>

#include "base/image/pixel_map.h"
#include "base/memory/ace_type.h"

namespace OHOS {

namespace Media {
class Picture;
class PixelMap;
} // namespace Media

namespace Ace {

enum class AuxiliaryPictureType : int32_t {
    NONE = 0,
    GAINMAP = 1,
    DEPTH_MAP = 2,
    UNREFOCUS_MAP = 3,
    LINEAR_MAP = 4,
    FRAGMENT_MAP = 5,
    SNAP_MAP = 6,
    SNAP_GAINMAP = 7,
    PAN_MAP = 8,
    PAN_GAINMAP = 9,
    LHDR_GAINMAP = 10,
    THUMBNAIL = 101,
};

class ACE_FORCE_EXPORT Picture : public AceType {
    DECLARE_ACE_TYPE(Picture, AceType);

public:
    static RefPtr<Picture> Create(void* picture);

    virtual RefPtr<PixelMap> GetMainPixel() = 0;
    virtual RefPtr<PixelMap> GetAuxPicturePixelMap(AuxiliaryPictureType type) = 0;
    virtual RefPtr<PixelMap> GetHdrComposedPixelMap(PixelFormat format) = 0;
};

} // namespace Ace
} // namespace OHOS

#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_IMAGE_ACE_PICTURE_H
