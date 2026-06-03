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

#include "picture_ohos.h"

#include "picture.h"
#include "image_type.h"
#include "pixel_map_ohos.h"

#include "base/log/log.h"

namespace OHOS::Ace {

namespace {

Media::AuxiliaryPictureType ConvertAuxPictureType(AuxiliaryPictureType type)
{
    switch (type) {
        case AuxiliaryPictureType::GAINMAP:
            return Media::AuxiliaryPictureType::GAINMAP;
        case AuxiliaryPictureType::DEPTH_MAP:
            return Media::AuxiliaryPictureType::DEPTH_MAP;
        case AuxiliaryPictureType::UNREFOCUS_MAP:
            return Media::AuxiliaryPictureType::UNREFOCUS_MAP;
        case AuxiliaryPictureType::LINEAR_MAP:
            return Media::AuxiliaryPictureType::LINEAR_MAP;
        case AuxiliaryPictureType::FRAGMENT_MAP:
            return Media::AuxiliaryPictureType::FRAGMENT_MAP;
        case AuxiliaryPictureType::SNAP_MAP:
            return Media::AuxiliaryPictureType::SNAP_MAP;
        case AuxiliaryPictureType::SNAP_GAINMAP:
            return Media::AuxiliaryPictureType::SNAP_GAINMAP;
        case AuxiliaryPictureType::PAN_MAP:
            return Media::AuxiliaryPictureType::PAN_MAP;
        case AuxiliaryPictureType::PAN_GAINMAP:
            return Media::AuxiliaryPictureType::PAN_GAINMAP;
        case AuxiliaryPictureType::LHDR_GAINMAP:
            return Media::AuxiliaryPictureType::LHDR_GAINMAP;
        case AuxiliaryPictureType::THUMBNAIL:
            return Media::AuxiliaryPictureType::THUMBNAIL;
        default:
            return Media::AuxiliaryPictureType::NONE;
    }
}

} // namespace

RefPtr<PixelMap> PictureOhos::GetMainPixel()
{
    if (!picture_) {
        return nullptr;
    }
    auto pixelMap = picture_->GetMainPixel();
    if (!pixelMap) {
        return nullptr;
    }
    return PixelMap::Create(pixelMap);
}

RefPtr<PixelMap> PictureOhos::GetAuxPicturePixelMap(AuxiliaryPictureType type)
{
    if (!picture_) {
        return nullptr;
    }
    auto auxType = ConvertAuxPictureType(type);
    auto pixelMap = picture_->GetAuxPicturePixelMap(auxType);
    if (!pixelMap) {
        return nullptr;
    }
    return PixelMap::Create(pixelMap);
}

RefPtr<PixelMap> PictureOhos::GetHdrComposedPixelMap(PixelFormat format)
{
    if (!picture_) {
        return nullptr;
    }
    auto pixelMap = picture_->GetHdrComposedPixelMap(PixelMapOhos::ConvertToMediaPixelFormat(format));
    if (!pixelMap) {
        return nullptr;
    }
    return PixelMap::Create(std::shared_ptr<Media::PixelMap>(pixelMap.release()));
}

RefPtr<Picture> Picture::Create(void* picture)
{
    auto* picturePtr = static_cast<std::shared_ptr<Media::Picture>*>(picture);
    if (!picturePtr || !*picturePtr) {
        return nullptr;
    }
    return AceType::MakeRefPtr<PictureOhos>(*picturePtr);
}

} // namespace OHOS::Ace
