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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_IMAGE_IMAGE_PROVIDER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_IMAGE_IMAGE_PROVIDER_H

#include <string>

#include "experimental/svg/model/SkSVGDOM.h"
#include "flutter/fml/memory/ref_counted.h"
#include "flutter/lib/ui/painting/image.h"
#include "third_party/skia/include/codec/SkCodec.h"

#include "base/memory/ace_type.h"
#include "base/resource/internal_resource.h"
#include "core/components/common/layout/constants.h"
#include "core/image/render_image_provider.h"
#include "core/pipeline/pipeline_context.h"

namespace OHOS::Ace {

class ImageProvider;
class LoadImageCallback : public virtual Referenced {
public:
    virtual void OnLoadSuccess(
        const sk_sp<SkImage>& image, const RefPtr<ImageProvider>& imageProvider, const std::string& key) = 0;
    virtual void OnLoadGPUImageSuccess(
        const fml::RefPtr<flutter::CanvasImage>& image, const RefPtr<ImageProvider>& imageProvider) = 0;
    virtual void OnAnimateImageSuccess(
        const RefPtr<ImageProvider>& provider, std::unique_ptr<SkCodec> codec) = 0;
    virtual void OnLoadFail(const RefPtr<ImageProvider>& imageProvider) = 0;
    virtual void OnChangeProvider(const RefPtr<ImageProvider>& provider) = 0;
    virtual void OnLoadImageSize(
        Size imagSize, const std::string& imageSrc, const RefPtr<ImageProvider>& imageProvider, bool syncMode) = 0;
    virtual void MarkNeedReload() = 0;
};

class ImageProvider : public RenderImageProvider {
    DECLARE_ACE_TYPE(ImageProvider, RenderImageProvider);

public:
    // Create function can be used for create File, Asset, Network image provider.
    // the image from memory should be create by class MemoryImageProvider constructor,
    // by passing a vector<uint8_t> as image data source to it.
    static RefPtr<ImageProvider> Create(
        const std::string& uri, RefPtr<SharedImageManager> sharedImageManager = nullptr);
    ~ImageProvider() override = default;

    static SrcType ResolveURI(const std::string& uri);
    static std::string RemovePathHead(const std::string& uri);
    static bool IsValidBase64Head(const std::string& uri, const std::string& pattern);
    static sk_sp<SkImage> ResizeSkImage(const sk_sp<SkImage>& rawImage, Size imageSize);
    static void RemoveLoadingImage(const std::string& key);

    virtual std::string GenerateKey(const std::string& src, Size targetSize) const;
    virtual sk_sp<SkData> LoadImageData(const std::string& src, const RefPtr<AssetManager> assetManager) = 0;

    void LoadImage(
        const RefPtr<PipelineContext>& pipelineContext,
        const std::string& src = std::string(),
        Size imageSize = Size());

    void GetSVGImageDOMAsync(
        const std::string& src,
        std::function<void(const sk_sp<SkSVGDOM>&)> callback,
        std::function<void()> failedCallback,
        RefPtr<TaskExecutor>& taskExecutor,
        const RefPtr<AssetManager> assetManager,
        uint64_t svgThemeColor = 0);

    void GetImageSize(bool syncMode, const RefPtr<AssetManager> assetManager, const std::string& src = std::string());
    void AddListener(const WeakPtr<LoadImageCallback>& listener);
    void RemoveListener(const WeakPtr<LoadImageCallback>& listener);
    int32_t GetTotalFrames() const;
    void OnImageReady(const sk_sp<SkImage>& image, const std::string& key);
    void OnGPUImageReady(const fml::RefPtr<flutter::CanvasImage>& image);
    void OnAnimateImageReady(const std::unique_ptr<SkCodec> codec);
    void OnImageFailed();
    void OnImageSizeReady(Size rawImageSize, const std::string& imageSrc, bool syncMode);

    sk_sp<SkImage> GetSkImage(
        const std::string& src,
        const RefPtr<AssetManager> assetManager,
        Size targetSize = Size());

protected:
    ImageProvider() = default;

    static std::unique_ptr<SkCodec> GetCodec(const sk_sp<SkData>& data);

    void LoadFromRealSrc(
        const std::string& src,
        Size imageSize,
        const RefPtr<PipelineContext>& piplineContext);

    // construct canvas image for rendering.
    void ConstructCanvasImageForRender(
        const std::string& key,
        const sk_sp<SkData>& data,
        Size imageSize);

    void ConstructSingleCanvasImage(
        const std::string& key,
        const sk_sp<SkData>& data,
        Size imageSize);

    // manager loading image using static unordered_map.
    static bool TrySetLoadingImage(const std::string& key, const WeakPtr<ImageProvider>& provider);

    std::string loadingUri_;

    // total frame count of this animated image
    int32_t totalFrames_ = 0;

    std::mutex listenersMutex_;
    std::set<WeakPtr<LoadImageCallback>> listeners_;

    static std::mutex loadingImageMutex_;
    static std::unordered_map<std::string, WeakPtr<ImageProvider>> loadingImage_;

    sk_sp<SkData> imageSkData_;
};

// File image provider: read image from file.
class FileImageProvider final : public ImageProvider {
public:
    FileImageProvider() = default;
    ~FileImageProvider() override = default;

    std::string GenerateKey(const std::string& src, Size targetSize) const override;
    sk_sp<SkData> LoadImageData(const std::string& src, const RefPtr<AssetManager> assetManager = nullptr) override;
};

class AssetImageProvider final : public ImageProvider {
public:
    AssetImageProvider() = default;
    ~AssetImageProvider() override = default;

    std::string GenerateKey(const std::string& src, Size targetSize) const override;
    sk_sp<SkData> LoadImageData(const std::string& src, const RefPtr<AssetManager> assetManager = nullptr) override;
};

// Network image provider: read image from network.
class NetworkImageProvider final : public ImageProvider {
public:
    NetworkImageProvider() = default;
    ~NetworkImageProvider() override = default;
    std::string GenerateKey(const std::string& url, Size targetSize) const override;
    sk_sp<SkData> LoadImageData(const std::string& url, const RefPtr<AssetManager> assetManager = nullptr) override;
};

class ImageProviderLoader;
// this class is for load image data in memory.
// The memory data vector should not be released in the life circle of the image provider.
class MemoryImageProvider final : public ImageProvider, public ImageProviderLoader {
    DECLARE_ACE_TYPE(MemoryImageProvider, ImageProvider, ImageProviderLoader)

public:
    MemoryImageProvider() = default;
    ~MemoryImageProvider() override = default;
    sk_sp<SkData> LoadImageData(const std::string& url, const RefPtr<AssetManager> assetManager = nullptr) override;
    std::string GenerateKey(const std::string& url, Size targetSize) const override;
    void UpdateData(const std::string& uri, const std::vector<uint8_t>& memData) override;

private:
    sk_sp<SkData> skData_;
};

class InternalImageProvider final : public ImageProvider {
public:
    explicit InternalImageProvider(InternalResource::ResourceId resourceId)
        : resourceId_(resourceId)
    {}
    ~InternalImageProvider() override = default;

    std::string GenerateKey(const std::string& src, Size targetSize) const override;

    sk_sp<SkData> LoadImageData(const std::string& url, const RefPtr<AssetManager> assetManager = nullptr) override;

private:
    InternalResource::ResourceId resourceId_;
};

class Base64ImageProvider final : public ImageProvider {
public:
    Base64ImageProvider() = default;
    ~Base64ImageProvider() override = default;

    static std::string GetBase64ImageCode(const std::string& url, size_t& imagSize);
    static size_t GetBase64ImageSize(const std::string& code);
    sk_sp<SkData> LoadImageData(const std::string& url, const RefPtr<AssetManager> assetManager = nullptr) override;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_IMAGE_IMAGE_PROVIDER_H
