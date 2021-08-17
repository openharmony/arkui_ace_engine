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
#include "core/image/image_loader.h"
#include "core/image/render_image_provider.h"
#include "core/pipeline/pipeline_context.h"
#include "frameworks/core/components/svg/parse/svg_dom.h"

namespace OHOS::Ace {

class ImageProvider;
class LoadImageCallback : public virtual Referenced {
public:
    virtual void OnLoadSuccess(
        const fml::RefPtr<flutter::CanvasImage>& image, const RefPtr<ImageProvider>& imageProvider) = 0;
    virtual void OnAnimateImageSuccess(
        const RefPtr<ImageProvider>& provider, std::unique_ptr<SkCodec> codec, bool forceResize) = 0;
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
    explicit ImageProvider(InternalResource::ResourceId resourceId);
    ImageProvider(const std::string& uri, RefPtr<SharedImageManager> sharedImageManager = nullptr);
    ~ImageProvider() override = default;

    static void RemoveLoadingImage(const std::string& key);
    static sk_sp<SkImage> ApplySizeToSkImage(const sk_sp<SkImage>& rawImage, int32_t dstWidth, int32_t dstHeight);

    void LoadImage(const WeakPtr<PipelineContext> context, const std::string& src = std::string(),
        Size imageSize = Size(), bool forceResize = false);

    void GetSVGImageDOMAsync(
        const std::string& src,
        std::function<void(const sk_sp<SkSVGDOM>&)> callback,
        std::function<void()> failedCallback,
        const WeakPtr<PipelineContext> context,
        uint64_t svgThemeColor = 0);

    void GetSVGImageDOMAsyncCustom(
        const std::string& src,
        std::function<void(const RefPtr<SvgDom>&)> callback,
        std::function<void()> failedCallback,
        const WeakPtr<PipelineContext> context,
        const std::optional<Color>& svgThemeColor);

    sk_sp<SkImage> ResizeSkImage(const sk_sp<SkImage>& rawImage, Size imageSize, bool forceResize = false);
    void GetImageSize(bool syncMode, const WeakPtr<PipelineContext> context, const std::string& src = std::string());
    void AddListener(const WeakPtr<LoadImageCallback>& listener);
    void RemoveListener(const WeakPtr<LoadImageCallback>& listener);
    int32_t GetTotalFrames() const;
    void OnImageReady(const fml::RefPtr<flutter::CanvasImage>& image);
    void OnAnimateImageReady(const std::unique_ptr<SkCodec> codec, bool forceResize);
    void OnImageFailed();
    void OnImageSizeReady(Size rawImageSize, const std::string& imageSrc, bool syncMode);
    void UploadToGPUForRender(
        const sk_sp<SkImage>& image, const std::function<void(flutter::SkiaGPUObject<SkImage>)>& callback);

    sk_sp<SkImage> GetSkImage(
        const std::string& src,
        const WeakPtr<PipelineContext> context,
        Size targetSize = Size());

    bool Invalid() const
    {
        return !imageLoader_;
    }
    static bool IsWideGamut(const sk_sp<SkColorSpace>& colorSpace);

protected:
    ImageProvider() = default;

    static std::unique_ptr<SkCodec> GetCodec(const sk_sp<SkData>& data);

    void LoadFromRealSrc(
        const std::string& src,
        Size imageSize,
        const WeakPtr<PipelineContext> context,
        const RefPtr<ImageLoader> imageLoader,
        bool forceResize);

    // construct canvas image for rendering.
    void ConstructCanvasImageForRender(
        const std::string& key, sk_sp<SkData> data, Size imageSize, bool forceResize = false);

    void ConstructSingleCanvasImage(
        const std::string& key, const sk_sp<SkData>& data, Size imageSize, bool forceResize = false);

    // manager loading image using static unordered_map.
    static bool TrySetLoadingImage(const std::string& key, const WeakPtr<ImageProvider>& provider);

    std::string loadingUri_;
    RefPtr<ImageLoader> imageLoader_;
    sk_sp<SkData> imageSkData_;
    Size currentResolutionTargetSize_;

    // total frame count of this animated image
    int32_t totalFrames_ = 0;

    std::mutex listenersMutex_;
    std::mutex imageSkDataMutex_;
    std::set<WeakPtr<LoadImageCallback>> listeners_;

    static std::mutex loadingImageMutex_;
    static std::unordered_map<std::string, WeakPtr<ImageProvider>> loadingImage_;

    bool needCacheResizedImage = false;
    fml::RefPtr<flutter::SkiaUnrefQueue> unrefQueue_;
    fml::WeakPtr<flutter::IOManager> ioManager_;
    fml::RefPtr<fml::TaskRunner> ioTaskRunner_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_IMAGE_IMAGE_PROVIDER_H
