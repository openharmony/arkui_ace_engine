/*
 * Copyright (c) 2021-2025 Huawei Device Co., Ltd.
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
#include "base/image/image_defines.h"
#include "base/memory/ace_type.h"
#include "base/network/download_manager.h"
#include "base/resource/internal_resource.h"
#include "base/resource/shared_image_manager.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/image_provider/image_data.h"
#include "core/components_ng/image_provider/image_loading_context.h"
#include "core/components_ng/render/drawing_forward.h"
#include "core/image/image_source_info.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace {

class ImageLoader : public virtual AceType {
    DECLARE_ACE_TYPE(ImageLoader, AceType);

public:
    virtual std::shared_ptr<RSData> LoadImageData(const ImageSourceInfo& imageSourceInfo,
        NG::ImageLoadResultInfo& errorInfo, const WeakPtr<PipelineBase>& context) = 0;
    virtual RefPtr<NG::ImageData> LoadDecodedImageData(const ImageSourceInfo& /*imageSourceInfo*/,
        NG::ImageLoadResultInfo& errorInfo, const WeakPtr<PipelineBase>& /*context*/)
    {
        return nullptr;
    }

    RefPtr<NG::ImageData> GetImageData(const ImageSourceInfo& imageSourceInfo,
        NG::ImageLoadResultInfo& errorInfo, const WeakPtr<PipelineBase>& context = nullptr);

    static std::string RemovePathHead(const std::string& uri);
    static RefPtr<ImageLoader> CreateImageLoader(const ImageSourceInfo& imageSourceInfo);

    static std::shared_ptr<RSData> LoadDataFromCachedFile(const std::string& uri);

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
    std::shared_ptr<RSData> LoadImageData(const ImageSourceInfo& imageSourceInfo,
        NG::ImageLoadResultInfo& errorInfo,
        const WeakPtr<PipelineBase>& context = nullptr) override;
};

// data provider image loader.
class DataProviderImageLoader : public ImageLoader {
public:
    DataProviderImageLoader() = default;
    ~DataProviderImageLoader() override = default;
    std::shared_ptr<RSData> LoadImageData(const ImageSourceInfo& imageSourceInfo,
        NG::ImageLoadResultInfo& errorInfo,
        const WeakPtr<PipelineBase>& context = nullptr) override;
};

class DecodedDataProviderImageLoader : public ImageLoader {
public:
    DecodedDataProviderImageLoader() = default;
    ~DecodedDataProviderImageLoader() override = default;
    std::shared_ptr<RSData> LoadImageData(const ImageSourceInfo& imageSourceInfo,
        NG::ImageLoadResultInfo& errorInfo,
        const WeakPtr<PipelineBase>& context = nullptr) override;
    RefPtr<NG::ImageData> LoadDecodedImageData(const ImageSourceInfo& imageSourceInfo,
        NG::ImageLoadResultInfo& errorInfo,
        const WeakPtr<PipelineBase>& context = nullptr) override;

private:
    static std::string GetThumbnailOrientation(const ImageSourceInfo& src);
};

class AssetImageLoader final : public ImageLoader {
public:
    AssetImageLoader() = default;
    ~AssetImageLoader() override = default;
    std::shared_ptr<RSData> LoadImageData(const ImageSourceInfo& imageSourceInfo,
        NG::ImageLoadResultInfo& errorInfo,
        const WeakPtr<PipelineBase>& context = nullptr) override;
    std::string LoadJsonData(const std::string& src, const WeakPtr<PipelineBase> context = nullptr);
};

// Network image provider: read image from network.
class NetworkImageLoader final : public ImageLoader {
public:
    NetworkImageLoader() = default;
    ~NetworkImageLoader() override = default;
    std::shared_ptr<RSData> LoadImageData(const ImageSourceInfo& imageSourceInfo,
        NG::ImageLoadResultInfo& errorInfo,
        const WeakPtr<PipelineBase>& context = nullptr) override;
    static bool DownloadImage(DownloadCallback&& downloadCallback, const std::string& src, bool sync);
};

class InternalImageLoader final : public ImageLoader {
public:
    InternalImageLoader() = default;
    ~InternalImageLoader() override = default;
    std::shared_ptr<RSData> LoadImageData(const ImageSourceInfo& imageSourceInfo,
        NG::ImageLoadResultInfo& errorInfo,
        const WeakPtr<PipelineBase>& context = nullptr) override;
};

class Base64ImageLoader final : public ImageLoader {
public:
    Base64ImageLoader() = default;
    ~Base64ImageLoader() override = default;
    static std::string_view GetBase64ImageCode(const std::string& uri);
    std::shared_ptr<RSData> LoadImageData(const ImageSourceInfo& imageSourceInfo,
        NG::ImageLoadResultInfo& errorInfo,
        const WeakPtr<PipelineBase>& context = nullptr) override;
};

class ResourceWrapper;

class ResourceImageLoader final : public ImageLoader {
public:
    ResourceImageLoader() = default;
    ~ResourceImageLoader() override = default;
    std::shared_ptr<RSData> LoadImageData(const ImageSourceInfo& imageSourceInfo,
        NG::ImageLoadResultInfo& errorInfo,
        const WeakPtr<PipelineBase>& context = nullptr) override;

private:
    bool GetResourceId(const std::string& uri, uint32_t& resId) const;
    bool GetResourceId(const std::string& uri, std::string& path) const;
    bool GetResourceName(const std::string& uri, std::string& resName) const;
};

class PixelMapImageLoader : public ImageLoader {
public:
    PixelMapImageLoader() = default;
    ~PixelMapImageLoader() override = default;
    std::shared_ptr<RSData> LoadImageData(const ImageSourceInfo& imageSourceInfo,
        NG::ImageLoadResultInfo& errorInfo,
        const WeakPtr<PipelineBase>& context = nullptr) override;
    RefPtr<NG::ImageData> LoadDecodedImageData(const ImageSourceInfo& imageSourceInfo,
        NG::ImageLoadResultInfo& errorInfo,
        const WeakPtr<PipelineBase>& context = nullptr) override;
};

class SharedMemoryImageLoader : public ImageLoader, public ImageProviderLoader {
    DECLARE_ACE_TYPE(SharedMemoryImageLoader, ImageLoader);

public:
    SharedMemoryImageLoader() = default;
    ~SharedMemoryImageLoader() override = default;
    std::shared_ptr<RSData> LoadImageData(const ImageSourceInfo& imageSourceInfo,
        NG::ImageLoadResultInfo& errorInfo, const WeakPtr<PipelineBase>& context) override;
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
    std::shared_ptr<RSData> LoadImageData(const ImageSourceInfo& imageSourceInfo,
        NG::ImageLoadResultInfo& errorInfo,
        const WeakPtr<PipelineBase>& context = nullptr) override;
    RefPtr<NG::ImageData> LoadDecodedImageData(const ImageSourceInfo& imageSourceInfo,
        NG::ImageLoadResultInfo& errorInfo,
        const WeakPtr<PipelineBase>& context = nullptr) override;

private:
    static std::string GetThumbnailOrientation(const ImageSourceInfo& src);
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_IMAGE_IMAGE_LOADER_H
