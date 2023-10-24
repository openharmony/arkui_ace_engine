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

#include "base/geometry/ng/size_t.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/image_provider/image_object.h"
#include "core/components_ng/image_provider/image_provider.h"
#include "core/components_ng/image_provider/image_state_manager.h"

namespace OHOS::Ace::NG {

// [ImageLoadingContext] do two things:
// 1. Provide interfaces for who owns it, notify it's owner when loading events come.
// 2. Drive [ImageObject] to load and make [CanvasImage].
class ImageLoadingContext : public AceType {
    DECLARE_ACE_TYPE(ImageLoadingContext, AceType);

public:
    // Create an empty ImageObject and initialize state machine when the constructor is called
    ImageLoadingContext(const ImageSourceInfo& src, LoadNotifier&& loadNotifier, bool syncLoad = false);
    ~ImageLoadingContext() override;

    // return true if calling MakeCanvasImage is necessary
    bool MakeCanvasImageIfNeed(const SizeF& dstSize, bool autoResize, ImageFit imageFit,
        const std::optional<SizeF>& sourceSize = std::nullopt);

    /* interfaces to drive image loading */
    void LoadImageData();
    void MakeCanvasImage(const SizeF& dstSize, bool needResize, ImageFit imageFit = ImageFit::COVER,
        const std::optional<SizeF>& sourceSize = std::nullopt);
    void ResetLoading();
    void ResumeLoading();

    /* interfaces to get properties */
    SizeF GetImageSize() const;
    const RectF& GetDstRect() const;
    const RectF& GetSrcRect() const;
    ImageFit GetImageFit() const;

    RefPtr<CanvasImage> MoveCanvasImage();

    const ImageSourceInfo& GetSourceInfo() const;
    const SizeF& GetDstSize() const;
    bool GetAutoResize() const;
    std::optional<SizeF> GetSourceSize() const;
    bool NeedAlt() const;

    /* interfaces to set properties */
    void SetImageFit(ImageFit imageFit);
    void SetAutoResize(bool needResize);
    void SetSourceSize(const std::optional<SizeF>& sourceSize = std::nullopt);

    // callbacks that will be called by ImageProvider when load process finishes
    void DataReadyCallback(const RefPtr<ImageObject>& imageObj);
    void SuccessCallback(const RefPtr<CanvasImage>& canvasImage);
    void FailCallback(const std::string& errorMsg);
    const std::string GetCurrentLoadingState();

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
    void OnDataReady();
    void OnMakeCanvasImage();
    void OnLoadSuccess();
    void OnLoadFail();
    void DownloadImage();

    // round up int to the nearest 2-fold proportion of image width
    // REQUIRE: value > 0, image width > 0
    int32_t RoundUp(int32_t value);
    static SizeF CalculateTargetSize(const SizeF& srcSize, const SizeF& dstSize, const SizeF& rawImageSize);

    inline bool SizeChanging(const SizeF& dstSize)
    {
        return dstSize_.IsPositive() && dstSize != dstSize_;
    }

    const ImageSourceInfo src_;
    RefPtr<ImageStateManager> stateManager_;
    RefPtr<ImageObject> imageObj_;
    RefPtr<CanvasImage> canvasImage_;

    // [LoadNotifier] contains 3 tasks to notify whom uses [ImageLoadingContext] of loading results
    LoadNotifier notifiers_;

    bool autoResize_ = true;
    bool syncLoad_ = false;

    RectF srcRect_;
    RectF dstRect_;
    SizeF dstSize_;
    // to determine whether the image needs to be reloaded
    int32_t sizeLevel_ = -1;

    ImageFit imageFit_ = ImageFit::COVER;
    std::unique_ptr<SizeF> sourceSizePtr_ = nullptr;
    std::function<void()> updateParamsCallback_ = nullptr;

    std::string errorMsg_;
    // to cancel MakeCanvasImage task
    std::string canvasKey_;

    friend class ImageStateManager;
    ACE_DISALLOW_COPY_AND_MOVE(ImageLoadingContext);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_IMAGE_PROVIDER_IMAGE_LOADING_CONTEXT_H
