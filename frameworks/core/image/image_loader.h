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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_IMAGE_IMAGE_LOADER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_IMAGE_IMAGE_LOADER_H

#include <condition_variable>
#include <regex>
#include <string>

#include "include/core/SkImage.h"

#include "base/geometry/size.h"
#include "base/memory/ace_type.h"
#include "base/network/download_manager.h"
#include "base/resource/internal_resource.h"
#include "base/resource/shared_image_manager.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/image_provider/image_data.h"
#include "core/components_ng/render/drawing_forward.h"
#include "core/image/image_source_info.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace {

class ImageLoader : public virtual AceType {
    DECLARE_ACE_TYPE(ImageLoader, AceType);

public:
#ifndef USE_ROSEN_DRAWING
    virtual sk_sp<SkData> LoadImageData(
        const ImageSourceInfo& imageSourceInfo, const WeakPtr<PipelineBase>& context) = 0;
#else
    virtual std::shared_ptr<RSData> LoadImageData(
        const ImageSourceInfo& imageSourceInfo, const WeakPtr<PipelineBase>& context) = 0;
#endif
    virtual RefPtr<NG::ImageData> LoadDecodedImageData(
        const ImageSourceInfo& /*imageSourceInfo*/, const WeakPtr<PipelineBase>& /*context*/)
    {
        return nullptr;
    }

    RefPtr<NG::ImageData> GetImageData(
        const ImageSourceInfo& imageSourceInfo, const WeakPtr<PipelineBase>& context = nullptr);

    static std::string RemovePathHead(const std::string& uri);
    static RefPtr<ImageLoader> CreateImageLoader(const ImageSourceInfo& imageSourceInfo);

#ifndef USE_ROSEN_DRAWING
    static sk_sp<SkData> LoadDataFromCachedFile(const std::string& uri);
#else
    static std::shared_ptr<RSData> LoadDataFromCachedFile(const std::string& uri);
#endif

    static std::shared_ptr<RSData> QueryImageDataFromImageCache(const ImageSourceInfo& sourceInfo);
    static void CacheImageData(const std::string& key, const RefPtr<NG::ImageData>& data);
    static RefPtr<NG::ImageData> LoadImageDataFromFileCache(const std::string& key, const std::string& suffix);

    static void WriteCacheToFile(const std::string& uri, const std::vector<uint8_t>& imageData);
    static void WriteCacheToFile(const std::string& uri, const std::string& imageData);
};

// File image provider: read image from file.
class FileImageLoader : public ImageLoader {
public:
    FileImageLoader() = default;
    ~FileImageLoader() override = default;
#ifndef USE_ROSEN_DRAWING
    sk_sp<SkData> LoadImageData(
        const ImageSourceInfo& imageSourceInfo, const WeakPtr<PipelineBase>& context = nullptr) override;
#else
    std::shared_ptr<RSData> LoadImageData(
        const ImageSourceInfo& imageSourceInfo, const WeakPtr<PipelineBase>& context = nullptr) override;
#endif
};

// data provider image loader.
class DataProviderImageLoader : public ImageLoader {
public:
    DataProviderImageLoader() = default;
    ~DataProviderImageLoader() override = default;
#ifndef USE_ROSEN_DRAWING
    sk_sp<SkData> LoadImageData(
        const ImageSourceInfo& imageSourceInfo, const WeakPtr<PipelineBase>& context = nullptr) override;
#else
    std::shared_ptr<RSData> LoadImageData(
        const ImageSourceInfo& imageSourceInfo, const WeakPtr<PipelineBase>& context = nullptr) override;
#endif
};

class DecodedDataProviderImageLoader : public ImageLoader {
public:
    DecodedDataProviderImageLoader() = default;
    ~DecodedDataProviderImageLoader() override = default;
#ifndef USE_ROSEN_DRAWING
    sk_sp<SkData> LoadImageData(
        const ImageSourceInfo& imageSourceInfo, const WeakPtr<PipelineBase>& context = nullptr) override;
#else
    std::shared_ptr<RSData> LoadImageData(
        const ImageSourceInfo& imageSourceInfo, const WeakPtr<PipelineBase>& context = nullptr) override;
#endif
    RefPtr<NG::ImageData> LoadDecodedImageData(
        const ImageSourceInfo& imageSourceInfo, const WeakPtr<PipelineBase>& context = nullptr) override;

private:
    static std::string GetThumbnailOrientation(const ImageSourceInfo& src);
};

class AssetImageLoader final : public ImageLoader {
public:
    AssetImageLoader() = default;
    ~AssetImageLoader() override = default;
#ifndef USE_ROSEN_DRAWING
    sk_sp<SkData> LoadImageData(
        const ImageSourceInfo& imageSourceInfo, const WeakPtr<PipelineBase>& context = nullptr) override;
#else
    std::shared_ptr<RSData> LoadImageData(
        const ImageSourceInfo& imageSourceInfo, const WeakPtr<PipelineBase>& context = nullptr) override;
#endif
    std::string LoadJsonData(const std::string& src, const WeakPtr<PipelineBase> context = nullptr);
};

// Network image provider: read image from network.
class NetworkImageLoader final : public ImageLoader {
public:
    NetworkImageLoader() = default;
    ~NetworkImageLoader() override = default;
#ifndef USE_ROSEN_DRAWING
    sk_sp<SkData> LoadImageData(
        const ImageSourceInfo& imageSourceInfo, const WeakPtr<PipelineBase>& context = nullptr) override;
#else
    std::shared_ptr<RSData> LoadImageData(
        const ImageSourceInfo& imageSourceInfo, const WeakPtr<PipelineBase>& context = nullptr) override;
#endif
    static bool DownloadImage(DownloadCallback&& downloadCallback, const std::string& src, bool sync, int32_t nodeId);
};

class InternalImageLoader final : public ImageLoader {
public:
    InternalImageLoader() = default;
    ~InternalImageLoader() override = default;
#ifndef USE_ROSEN_DRAWING
    sk_sp<SkData> LoadImageData(
        const ImageSourceInfo& imageSourceInfo, const WeakPtr<PipelineBase>& context = nullptr) override;
#else
    std::shared_ptr<RSData> LoadImageData(
        const ImageSourceInfo& imageSourceInfo, const WeakPtr<PipelineBase>& context = nullptr) override;
#endif
};

class Base64ImageLoader final : public ImageLoader {
public:
    Base64ImageLoader() = default;
    ~Base64ImageLoader() override = default;
    static std::string_view GetBase64ImageCode(const std::string& uri);
#ifndef USE_ROSEN_DRAWING
    sk_sp<SkData> LoadImageData(
        const ImageSourceInfo& imageSourceInfo, const WeakPtr<PipelineBase>& context = nullptr) override;
#else
    std::shared_ptr<RSData> LoadImageData(
        const ImageSourceInfo& imageSourceInfo, const WeakPtr<PipelineBase>& context = nullptr) override;
#endif
};

class ResourceImageLoader final : public ImageLoader {
public:
    ResourceImageLoader() = default;
    ~ResourceImageLoader() override = default;
#ifndef USE_ROSEN_DRAWING
    sk_sp<SkData> LoadImageData(
        const ImageSourceInfo& imageSourceInfo, const WeakPtr<PipelineBase>& context = nullptr) override;
#else
    std::shared_ptr<RSData> LoadImageData(
        const ImageSourceInfo& imageSourceInfo, const WeakPtr<PipelineBase>& context = nullptr) override;
#endif

private:
    bool GetResourceId(const std::string& uri, uint32_t& resId) const;
    bool GetResourceId(const std::string& uri, std::string& path) const;
    bool GetResourceName(const std::string& uri, std::string& resName) const;
};

class PixelMapImageLoader : public ImageLoader {
public:
    PixelMapImageLoader() = default;
    ~PixelMapImageLoader() override = default;
#ifndef USE_ROSEN_DRAWING
    sk_sp<SkData> LoadImageData(
        const ImageSourceInfo& imageSourceInfo, const WeakPtr<PipelineBase>& context = nullptr) override;
#else
    std::shared_ptr<RSData> LoadImageData(
        const ImageSourceInfo& imageSourceInfo, const WeakPtr<PipelineBase>& context = nullptr) override;
#endif
    RefPtr<NG::ImageData> LoadDecodedImageData(
        const ImageSourceInfo& imageSourceInfo, const WeakPtr<PipelineBase>& context = nullptr) override;
};

class SharedMemoryImageLoader : public ImageLoader, public ImageProviderLoader {
    DECLARE_ACE_TYPE(SharedMemoryImageLoader, ImageLoader);

public:
    SharedMemoryImageLoader() = default;
    ~SharedMemoryImageLoader() override = default;
#ifndef USE_ROSEN_DRAWING
    sk_sp<SkData> LoadImageData(const ImageSourceInfo& imageSourceInfo, const WeakPtr<PipelineBase>& context) override;
#else
    std::shared_ptr<RSData> LoadImageData(
        const ImageSourceInfo& imageSourceInfo, const WeakPtr<PipelineBase>& context) override;
#endif
    void UpdateData(const std::string& uri, const std::vector<uint8_t>& memData) override;

private:
    std::condition_variable cv_;
    std::mutex mtx_;
    std::vector<uint8_t> data_;
};
class AstcImageLoader : public ImageLoader {
public:
    AstcImageLoader() = default;
    ~AstcImageLoader() override = default;
#ifndef USE_ROSEN_DRAWING
    sk_sp<SkData> LoadImageData(
        const ImageSourceInfo& imageSourceInfo, const WeakPtr<PipelineBase>& context = nullptr) override;
#else
    std::shared_ptr<RSData> LoadImageData(
        const ImageSourceInfo& imageSourceInfo, const WeakPtr<PipelineBase>& context = nullptr) override;
#endif
    RefPtr<NG::ImageData> LoadDecodedImageData(
        const ImageSourceInfo& imageSourceInfo, const WeakPtr<PipelineBase>& context = nullptr) override;

private:
    static std::string GetThumbnailOrientation(const ImageSourceInfo& src);
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_IMAGE_IMAGE_LOADER_H
