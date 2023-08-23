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
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"

namespace OHOS::Ace {
class ImageSourceInfo {
public:
    // add constructor method for decompressed hap
    ImageSourceInfo(std::string imageSrc, std::string bundleName, std::string moduleName,
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
    static bool IsSVGSource(const std::string& imageSrc, InternalResource::ResourceId resourceId);
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
    void Reset();

    // interfaces to get infomation from [ImageSourceInfo]
    bool IsInternalResource() const;
    bool IsValid() const;
    bool IsPng() const;
    bool IsSvg() const;
    bool IsPixmap() const;
    bool IsSourceDimensionValid() const;
    const std::string& GetBundleName() const;
    const std::string& GetModuleName() const;
    std::string ToString() const;
    InternalResource::ResourceId GetResourceId() const;
    SrcType GetSrcType() const;
    Size GetSourceSize() const;
    const std::string& GetSrc() const;
    const std::optional<Color>& GetFillColor() const;
    const RefPtr<PixelMap>& GetPixmap() const;
    std::string GetKey() const;

    bool SupportObjCache() const;

private:
    SrcType ResolveSrcType() const;
    void GenerateCacheKey();

    std::string src_;
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

    [[deprecated("in NG")]]
    std::optional<Color> fillColor_;

    // image source type for example:FILE, ASSET, NETWORK, MEMORY, BASE64, INTERNAL, RESOURCE or DATA_ABILITY,
    SrcType srcType_ = SrcType::UNSUPPORTED;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_IMAGE_ACE_IMAGE_SOURCE_INFO_H
