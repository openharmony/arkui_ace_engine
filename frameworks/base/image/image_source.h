/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_IMAGE_ACE_IMAGE_SOURCE_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_IMAGE_ACE_IMAGE_SOURCE_H

#include "base/image/pixel_map.h"
#include "base/memory/ace_type.h"
#include "core/components/common/layout/constants.h"

namespace OHOS::Ace {
class PixelMap;

class ACE_FORCE_EXPORT ImageSource : public AceType {
    DECLARE_ACE_TYPE(ImageSource, AceType)

public:
    using Size = std::pair<int32_t, int32_t>;

    static RefPtr<ImageSource> Create(int32_t fd);
    static RefPtr<ImageSource> Create(const uint8_t* data, uint32_t size);
    static RefPtr<ImageSource> Create(const std::string& filePath);
    static bool IsAstc(const uint8_t* data, size_t size);
    static Size GetASTCInfo(const uint8_t* data, size_t size);

    virtual std::string GetProperty(const std::string& key) = 0;

    virtual RefPtr<PixelMap> CreatePixelMap(const Size& size, AIImageQuality imageQuality = AIImageQuality::NONE,
        bool isHdrDecoderNeed = false, PixelFormat photoDecodeFormat = PixelFormat::UNKNOWN) = 0;
    virtual RefPtr<PixelMap> CreatePixelMap(uint32_t index, const Size& size,
        AIImageQuality imageQuality = AIImageQuality::NONE, bool isHdrDecoderNeed = false,
        PixelFormat photoDecodeFormat = PixelFormat::UNKNOWN) = 0;
    virtual RefPtr<PixelMap> CreatePixelMap() = 0;
    virtual Size GetImageSize() = 0;
    virtual uint32_t GetFrameCount() = 0;
    virtual std::string GetEncodedFormat() = 0;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_IMAGE_ACE_IMAGE_SOURCE_H
