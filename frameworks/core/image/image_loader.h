/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_IMAGE_IMAGE_LOADER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_IMAGE_IMAGE_LOADER_H

#include <string>

#include "third_party/skia/include/core/SkImage.h"

#include "base/geometry/size.h"
#include "base/memory/ace_type.h"
#include "base/resource/internal_resource.h"
#include "base/resource/shared_image_manager.h"
#include "core/components/common/layout/constants.h"
#include "core/pipeline/pipeline_context.h"

namespace OHOS::Ace {

class ImageLoader : public virtual AceType {
    DECLARE_ACE_TYPE(ImageLoader, AceType);

public:
    virtual std::string GenerateKey(const std::string& src, Size targetSize) const
    {
        return "";
    }
    virtual sk_sp<SkData> LoadImageData(const std::string& src, const WeakPtr<PipelineContext> context = nullptr) = 0;
    virtual void CacheResizedImage(const sk_sp<SkImage>& image, const std::string& key);
    virtual Size CalculateOriImageMatchedResolutionSize(const std::string& assetSrc, double oriHeight, double oriWidth);

    static SrcType ResolveURI(const std::string& uri);
    static std::string RemovePathHead(const std::string& uri);
};

// File image provider: read image from file.
class FileImageLoader : public ImageLoader {
public:
    FileImageLoader() = default;
    ~FileImageLoader() override = default;

    std::string GenerateKey(const std::string& src, Size targetSize) const override;
    sk_sp<SkData> LoadImageData(const std::string& src, const WeakPtr<PipelineContext> context = nullptr) override;
};

// data provider image loader.
class DataProviderImageLoader : public ImageLoader {
public:
    DataProviderImageLoader() = default;
    ~DataProviderImageLoader() override = default;

    std::string GenerateKey(const std::string& src, Size targetSize) const override;
    sk_sp<SkData> LoadImageData(const std::string& src, const WeakPtr<PipelineContext> context = nullptr) override;
};

class AssetImageLoader final : public ImageLoader {
public:
    explicit AssetImageLoader(bool needResizeSrcImage) : needResizeSrcImage_(needResizeSrcImage) {}
    ~AssetImageLoader() override = default;

    std::string GenerateKey(const std::string& src, Size targetSize) const override;
    sk_sp<SkData> LoadImageData(const std::string& src, const WeakPtr<PipelineContext> context = nullptr) override;
    Size CalculateOriImageMatchedResolutionSize(const std::string& assetSrc, double oriHeight,
        double oriWidth) override;
private:
    bool needResizeSrcImage_ = false;
};

// Network image provider: read image from network.
class NetworkImageLoader final : public ImageLoader {
public:
    NetworkImageLoader() = default;
    ~NetworkImageLoader() override = default;
    std::string GenerateKey(const std::string& uri, Size targetSize) const override;
    sk_sp<SkData> LoadImageData(const std::string& uri, const WeakPtr<PipelineContext> context = nullptr) override;
};

// this class is for load image data in memory.
// The memory data vector should not be released in the life circle of the image provider.
class MemoryImageLoader final : public ImageLoader, public ImageProviderLoader {
    DECLARE_ACE_TYPE(MemoryImageLoader, ImageLoader, ImageProviderLoader)

public:
    using UriUpdatedCallback = std::function<void(const std::string& uri)>;
    using ImageDataUpdatedCallback = std::function<void(const std::string& uri)>;

    MemoryImageLoader(UriUpdatedCallback&& uriUpdated, ImageDataUpdatedCallback&& imageDataUpdated)
        : uriUpdatedCallback_(std::move(uriUpdated)), imageDataUpdatedCallback_(std::move(imageDataUpdated))
    {}
    ~MemoryImageLoader() override = default;

    sk_sp<SkData> LoadImageData(const std::string& uri, const WeakPtr<PipelineContext> context = nullptr) override;
    std::string GenerateKey(const std::string& uri, Size targetSize) const override;
    void UpdateData(const std::string& uri, const std::vector<uint8_t>& memData) override;
    void CacheResizedImage(const sk_sp<SkImage>& image, const std::string& key) override {}

private:
    sk_sp<SkData> skData_;
    UriUpdatedCallback uriUpdatedCallback_;
    ImageDataUpdatedCallback imageDataUpdatedCallback_;
};

class InternalImageLoader final : public ImageLoader {
public:
    explicit InternalImageLoader(InternalResource::ResourceId resourceId) : resourceId_(resourceId) {}
    ~InternalImageLoader() override = default;

    std::string GenerateKey(const std::string& src, Size targetSize) const override;
    sk_sp<SkData> LoadImageData(const std::string& uri, const WeakPtr<PipelineContext> context = nullptr) override;
    void CacheResizedImage(const sk_sp<SkImage>& image, const std::string& key) override {}

private:
    InternalResource::ResourceId resourceId_;
};

class Base64ImageLoader final : public ImageLoader {
public:
    Base64ImageLoader() = default;
    ~Base64ImageLoader() override = default;

    static std::string GetBase64ImageCode(const std::string& uri, size_t& imagSize);
    static size_t GetBase64ImageSize(const std::string& code);
    sk_sp<SkData> LoadImageData(const std::string& uri, const WeakPtr<PipelineContext> context = nullptr) override;
    void CacheResizedImage(const sk_sp<SkImage>& image, const std::string& key) override {}
};

class ResourceImageLoader final : public ImageLoader {
public:
    ResourceImageLoader() = default;
    ~ResourceImageLoader() override = default;

    std::string GenerateKey(const std::string& src, Size targetSize) const override;
    sk_sp<SkData> LoadImageData(const std::string& src, const WeakPtr<PipelineContext> context = nullptr) override;
    void CacheResizedImage(const sk_sp<SkImage>& image, const std::string& key) override {}

private:
    bool GetResourceId(const std::string& uri, const RefPtr<ThemeConstants>& themeContants, uint32_t& resId) const;
};

class FileCacheImageLoader final : public FileImageLoader {
public:
    FileCacheImageLoader() = default;
    ~FileCacheImageLoader() override = default;

    void CacheResizedImage(const sk_sp<SkImage>& image, const std::string& key) override {}
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_IMAGE_IMAGE_LOADER_H