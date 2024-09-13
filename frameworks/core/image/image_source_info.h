/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_IMAGE_ACE_IMAGE_SOURCE_INFO_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_IMAGE_ACE_IMAGE_SOURCE_INFO_H

#include <optional>
#include <utility>

#include "base/geometry/dimension.h"
#include "base/geometry/size.h"
#include "base/image/pixel_map.h"
#include "base/resource/internal_resource.h"
#include "base/utils/device_config.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/pattern/image/image_dfx.h"

namespace OHOS::Ace {
class ACE_FORCE_EXPORT ImageSourceInfo {
public:
    // add constructor method for decompressed hap
    ImageSourceInfo(std::string imageSrc, std::string bundleName, std::string moduleName,
        Dimension width = Dimension(-1), Dimension height = Dimension(-1),
        InternalResource::ResourceId resourceId = InternalResource::ResourceId::NO_ID,
        const RefPtr<PixelMap>& pixmap = nullptr);

    ImageSourceInfo(const std::shared_ptr<std::string> &imageSrc, std::string bundleName, std::string moduleName,
        Dimension width = Dimension(-1), Dimension height = Dimension(-1),
        InternalResource::ResourceId resourceId = InternalResource::ResourceId::NO_ID,
        const RefPtr<PixelMap>& pixmap = nullptr);

    explicit ImageSourceInfo(std::string imageSrc, Dimension width = Dimension(-1), Dimension height = Dimension(-1),
        InternalResource::ResourceId resourceId = InternalResource::ResourceId::NO_ID,
        const RefPtr<PixelMap>& pixmap = nullptr)
        : ImageSourceInfo(std::move(imageSrc), "", "", width, height, resourceId, pixmap)
    {}

    explicit ImageSourceInfo(const RefPtr<PixelMap>& pixmap)
        : ImageSourceInfo("", Dimension(-1), Dimension(-1), InternalResource::ResourceId::NO_ID, pixmap)
    {}
    ImageSourceInfo() = default;
    ~ImageSourceInfo() = default;

    // static functions
    static bool IsSVGSource(const std::string& imageSrc, SrcType srcType, InternalResource::ResourceId resourceId);
    static bool IsPngSource(const std::string& src, InternalResource::ResourceId resourceId);
    static SrcType ResolveURIType(const std::string& uri);
    static bool IsValidBase64Head(const std::string& uri, const std::string& pattern);
    static bool IsUriOfDataAbilityEncoded(const std::string& uri, const std::string& pattern);

    // operators
    bool operator==(const ImageSourceInfo& info) const;
    bool operator!=(const ImageSourceInfo& info) const;

    // interfaces to change [ImageSourceInfo]
    void SetSrc(const std::string& src, std::optional<Color> fillColor = std::nullopt);
    void SetResourceId(InternalResource::ResourceId id, std::optional<Color> fillColor = std::nullopt);
    void SetPixMap(const RefPtr<PixelMap>& pixmap, std::optional<Color> fillColor = std::nullopt);
    void SetDimension(Dimension width, Dimension Height);

    [[deprecated("use ImageRenderProperty::SetFillColor or SvgCanvasImage::SetFillColor")]]
    void SetFillColor(const Color& color);
    void SetBundleName(const std::string& bundleName);
    void SetModuleName(const std::string& moduleName);
    void SetIsUriPureNumber(bool isUriPureNumber = false)
    {
        isUriPureNumber_ = isUriPureNumber;
    }
    void Reset();

    // interfaces to get infomation from [ImageSourceInfo]
    void GenerateCacheKey();
    bool IsInternalResource() const;
    bool IsValid() const;
    bool IsPng() const;
    bool IsSvg() const;
    bool IsPixmap() const;
    bool IsSourceDimensionValid() const;
    const std::string& GetBundleName() const;
    const std::string& GetModuleName() const;
    std::string ToString(bool isNeedTruncated = true) const;
    InternalResource::ResourceId GetResourceId() const;
    SrcType GetSrcType() const;
    Size GetSourceSize() const;
    const std::string& GetSrc() const;
    const std::optional<Color>& GetFillColor() const;
    const RefPtr<PixelMap>& GetPixmap() const;
    std::string GetKey() const;
    bool GetIsUriPureNumber() const
    {
        return isUriPureNumber_;
    }
    bool SupportObjCache() const;
    void SetNeedCache(bool needCache)
    {
        needCache_ = needCache;
    }

    ColorMode GetLocalColorMode() const
    {
        return localColorMode_;
    }
    bool IsFromReset()
    {
        return isFromReset_;
    }
    void SetIsFromReset(bool isFromReset)
    {
        isFromReset_ = isFromReset;
    }
    const std::string GetColorModeToString();

    void SetImageDfxConfig(const NG::ImageDfxConfig& imageDfxConfig)
    {
        imageDfxConfig_ = imageDfxConfig;
    }

    NG::ImageDfxConfig GetImageDfxConfig() const
    {
        return imageDfxConfig_;
    }

private:
    SrcType ResolveSrcType() const;

    std::string src_;
    std::shared_ptr<std::string> srcRef_ = nullptr;
    std::string cacheKey_;
    // Interim programme
    std::string bundleName_;
    std::string moduleName_;
    Dimension sourceWidth_ = Dimension(-1);
    Dimension sourceHeight_ = Dimension(-1);
    InternalResource::ResourceId resourceId_ = InternalResource::ResourceId::NO_ID;
    RefPtr<PixelMap> pixmap_;
    bool isSvg_ = false;
    bool isPng_ = false;
    bool needCache_ = true;
    bool isUriPureNumber_ = false;
    bool isFromReset_ = false;
    [[deprecated("in NG")]]
    std::optional<Color> fillColor_;
    const uint8_t* pixmapBuffer_ = nullptr;
    NG::ImageDfxConfig imageDfxConfig_;

    // image source type for example:FILE, ASSET, NETWORK, MEMORY, BASE64, INTERNAL, RESOURCE or DATA_ABILITY,
    SrcType srcType_ = SrcType::UNSUPPORTED;

    ColorMode localColorMode_ = ColorMode::COLOR_MODE_UNDEFINED;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_IMAGE_ACE_IMAGE_SOURCE_INFO_H
