/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_IMAGE_PROVIDER_IMAGE_LOADING_CONTEXT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_IMAGE_PROVIDER_IMAGE_LOADING_CONTEXT_H

#include <cstdint>

#include "base/geometry/ng/size_t.h"
#include "base/thread/task_executor.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/image_provider/image_object.h"
#include "core/components_ng/image_provider/image_provider.h"
#include "core/components_ng/image_provider/image_state_manager.h"
#include "core/components_ng/pattern/image/image_dfx.h"

namespace OHOS::Ace::NG {

using PendingMakeCanvasImageTask = std::function<void()>;
// [ImageLoadingContext] do two things:
// 1. Provide interfaces for who owns it, notify it's owner when loading events come.
// 2. Drive [ImageObject] to load and make [CanvasImage].
class ACE_FORCE_EXPORT ImageLoadingContext : public AceType {
    DECLARE_ACE_TYPE(ImageLoadingContext, AceType);

public:
    // Create an empty ImageObject and initialize state machine when the constructor is called
    ImageLoadingContext(const ImageSourceInfo& src, LoadNotifier&& loadNotifier, bool syncLoad = false,
        const ImageDfxConfig& imageDfxConfig = {});
    ~ImageLoadingContext() override;

    // return true if calling MakeCanvasImage is necessary
    bool MakeCanvasImageIfNeed(const SizeF& dstSize, bool autoResize, ImageFit imageFit,
        const std::optional<SizeF>& sourceSize = std::nullopt, bool hasValidSlice = false);

    /* interfaces to drive image loading */
    void LoadImageData();
    void MakeCanvasImage(const SizeF& dstSize, bool needResize, ImageFit imageFit = ImageFit::COVER,
        const std::optional<SizeF>& sourceSize = std::nullopt);
    void ResetLoading();
    void ResumeLoading();

    /* interfaces to get properties */
    SizeF GetImageSize() const;
    SizeF GetOriginImageSize() const;
    const RectF& GetDstRect() const;
    const RectF& GetSrcRect() const;
    ImageFit GetImageFit() const;
    int32_t GetFrameCount() const;

    RefPtr<CanvasImage> MoveCanvasImage();
    RefPtr<ImageObject> MoveImageObject();
    RefPtr<ImageObject> GetImageObject()
    {
        return imageObj_;
    }

    const ImageSourceInfo& GetSourceInfo() const;
    const SizeF& GetDstSize() const;
    bool GetAutoResize() const;
    std::optional<SizeF> GetSourceSize() const;
    bool NeedAlt() const;

    /* interfaces to set properties */
    void SetImageFit(ImageFit imageFit);
    void SetAutoResize(bool needResize);
    void SetSourceSize(const std::optional<SizeF>& sourceSize = std::nullopt);
    const ImageSourceInfo GetSrc() const
    {
        return src_;
    }

    const RefPtr<ImageStateManager>& GetStateManger()
    {
        return stateManager_;
    }

    // callbacks that will be called by ImageProvider when load process finishes
    void DataReadyCallback(const RefPtr<ImageObject>& imageObj);
    void SuccessCallback(const RefPtr<CanvasImage>& canvasImage);
    void FailCallback(const std::string& errorMsg);
    const std::string GetCurrentLoadingState();
    void ResizableCalcDstSize();
    void DownloadImage();
    void PerformDownload();
    void CacheDownloadedImage();
    bool Downloadable();
    void OnDataReady();

    // Needed to restore the relevant containerId from the originating thread
    int32_t GetContainerId() const
    {
        return containerId_;
    }

    void SetDynamicRangeMode(DynamicRangeMode dynamicMode)
    {
        dynamicMode_ = dynamicMode;
    }

    void SetIsHdrDecoderNeed(bool isHdrDecoderNeed)
    {
        isHdrDecoderNeed_ = isHdrDecoderNeed;
    }

    bool GetIsHdrDecoderNeed()
    {
        return isHdrDecoderNeed_;
    }

    DynamicRangeMode GetDynamicRangeMode()
    {
        return dynamicMode_;
    }

    void SetImageQuality(AIImageQuality imageQuality)
    {
        imageQuality_ = imageQuality;
    }

    AIImageQuality GetImageQuality()
    {
        return imageQuality_;
    }

    void FinishMearuse()
    {
        measureFinish_ = true;
    }

    void CallbackAfterMeasureIfNeed();

    void OnDataReadyOnCompleteCallBack();
    void SetOnProgressCallback(std::function<void(const uint32_t& dlNow, const uint32_t& dlTotal)>&& onProgress);
    const std::string& GetErrorMsg()
    {
        return errorMsg_;
    }

    void SetImageDfxConfig(const ImageDfxConfig& imageDfxConfig)
    {
        imageDfxConfig_ = imageDfxConfig;
    }


    ImageDfxConfig GetImageDfxConfig()
    {
        return imageDfxConfig_;
    }

private:
#define DEFINE_SET_NOTIFY_TASK(loadResult)                                            \
    void Set##loadResult##NotifyTask(loadResult##NotifyTask&& loadResult##NotifyTask) \
    {                                                                                 \
        notifiers_.on##loadResult##_ = std::move(loadResult##NotifyTask);             \
    }

    // classes that use [ImageLoadingContext] can register three notify tasks to do things
    DEFINE_SET_NOTIFY_TASK(DataReady);
    DEFINE_SET_NOTIFY_TASK(LoadSuccess);
    DEFINE_SET_NOTIFY_TASK(LoadFail);

    // tasks that run when entering a new state
    void OnUnloaded();
    void OnDataLoading();
    void OnMakeCanvasImage();
    void OnLoadSuccess();
    void OnLoadFail();
    bool NotifyReadyIfCacheHit();
    void DownloadImageSuccess(const std::string& imageData);
    void DownloadImageFailed(const std::string& errorMessage);
    void DownloadOnProgress(const uint32_t& dlNow, const uint32_t& dlTotal);
    // round up int to the nearest 2-fold proportion of image width
    // REQUIRE: value > 0, image width > 0
    int32_t RoundUp(int32_t value);
    static SizeF CalculateTargetSize(const SizeF& srcSize, const SizeF& dstSize, const SizeF& rawImageSize);

    inline bool SizeChanging(const SizeF& dstSize)
    {
        return dstSize_.IsPositive() && dstSize != dstSize_;
    }

    ImageSourceInfo src_;
    RefPtr<ImageStateManager> stateManager_;
    RefPtr<ImageObject> imageObj_;
    RefPtr<CanvasImage> canvasImage_;
    std::string downloadedUrlData_;

    // [LoadNotifier] contains 3 tasks to notify whom uses [ImageLoadingContext] of loading results
    LoadNotifier notifiers_;

    // the container of the creator thread of this image loading context
    const int32_t containerId_ {0};

    bool isHdrDecoderNeed_ = false;
    bool autoResize_ = true;
    bool syncLoad_ = false;

    DynamicRangeMode dynamicMode_ = DynamicRangeMode::STANDARD;
    AIImageQuality imageQuality_ = AIImageQuality::NONE;

    RectF srcRect_;
    RectF dstRect_;
    SizeF dstSize_;
    std::atomic<bool> measureFinish_ = false;
    std::atomic<bool> needErrorCallBack_ = false;
    std::atomic<bool> needDataReadyCallBack_ = false;
    // to determine whether the image needs to be reloaded
    int32_t sizeLevel_ = -1;
    ImageDfxConfig imageDfxConfig_;
    // If the API version is greater or equal than 14, use the preload module to download the URL.
    const bool usePreload_ = false;

    ImageFit imageFit_ = ImageFit::COVER;
    std::unique_ptr<SizeF> sourceSizePtr_ = nullptr;
    std::function<void()> updateParamsCallback_ = nullptr;

    std::string errorMsg_;
    // to cancel MakeCanvasImage task
    std::string canvasKey_;

    bool firstLoadImage_ = true;

    // if another makeCanvasImage task arrives and current state cannot handle makeCanvasImage command,
    // save the least recent makeCanvasImage task and trigger it when the previous makeCanvasImage task end
    // and state becomes MAKE_CANVAS_IMAGE_SUCCESS
    PendingMakeCanvasImageTask pendingMakeCanvasImageTask_ = nullptr;

    friend class ImageStateManager;
    ACE_DISALLOW_COPY_AND_MOVE(ImageLoadingContext);

    std::function<void(const uint32_t& dlNow, const uint32_t& dlTotal)> onProgressCallback_ = nullptr;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_IMAGE_PROVIDER_IMAGE_LOADING_CONTEXT_H
