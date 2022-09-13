/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

using EnterStateTask = std::function<void()>;
// [ImageLoadingContext] do two things:
// 1. Provide interfaces for who owns it, notify it's owner when loading events come.
// 2. Drive [ImageObject] to load and make [CanvasImage].
class ImageLoadingContext : public AceType {
    DECLARE_ACE_TYPE(ImageLoadingContext, AceType);

public:
    // Create an empty ImageObject and initialize state machine when the constructor is called
    ImageLoadingContext(const ImageSourceInfo& sourceInfo, const LoadNotifier& loadNotifier);
    ~ImageLoadingContext() override = default;

    static SizeF CalculateResizeTarget(const SizeF& srcSize, const SizeF& dstSize, const SizeF& rawImageSize);
    static void MakeCanvasImageIfNeed(const RefPtr<ImageLoadingContext>& loadingCtx, const SizeF& dstSize,
        bool incomingNeedResize, ImageFit incommingImageFit,
        const std::optional<std::pair<Dimension, Dimension>>& sourceSize = std::nullopt);

    void RegisterStateChangeCallbacks();

    /* interfaces to drive image loading */
    void LoadImageData();
    void MakeCanvasImage(const SizeF& dstSize, bool needResize, ImageFit imageFit = ImageFit::COVER,
        const std::optional<std::pair<Dimension, Dimension>>& sourceSize = std::nullopt);

    /* interfaces to get properties */
    SizeF GetImageSize() const;
    const RectF& GetDstRect() const;
    const RectF& GetSrcRect() const;
    ImageFit GetImageFit() const;
    RefPtr<CanvasImage> GetCanvasImage() const;
    const ImageSourceInfo& GetSourceInfo() const;
    const SizeF& GetDstSize() const;
    bool GetNeedResize() const;
    std::optional<SizeF> GetSourceSize() const;
    bool NeedAlt() const;

    /* interfaces to set properties */
    void SetImageFit(ImageFit imageFit);
    void SetNeedResize(bool needResize);
    void SetSourceSize(const std::optional<std::pair<Dimension, Dimension>>& sourceSize = std::nullopt);

private:
#define DEFINE_SET_NOTIFY_TASK(loadResult, loadResultNotifierName)                                         \
    void Set##loadResult##NotifyTask(loadResult##NotifyTask&& loadResultNotifierName##NotifyTask)          \
    {                                                                                                      \
        loadNotifier_.loadResultNotifierName##NotifyTask_ = std::move(loadResultNotifierName##NotifyTask); \
    }

    // classes that use [ImageLoadingContext] can register three notify tasks to do things
    DEFINE_SET_NOTIFY_TASK(DataReady, dataReady);
    DEFINE_SET_NOTIFY_TASK(LoadSuccess, loadSuccess);
    DEFINE_SET_NOTIFY_TASK(LoadFail, loadFail);

    // callbacks that will be set to [LoadCallbacks]
    DataReadyCallback GenerateDataReadyCallback();
    LoadSuccessCallback GenerateLoadSuccessCallback();
    LoadFailCallback GenerateLoadFailCallback();

    // things to do when load callback is triggered during image loading
    void OnDataReady(const ImageSourceInfo& sourceInfo, const RefPtr<ImageObject> imageObj);
    void OnLoadSuccess(const ImageSourceInfo& sourceInfo);
    void OnLoadFail(const ImageSourceInfo& sourceInfo, const std::string& errorMsg, const ImageLoadingCommand& command);

    // generate tasks relative to [ImageLoadingState] which will be run while entering a state
    EnterStateTask CreateOnUnloadedTask();
    EnterStateTask CreateOnDataLoadingTask();
    EnterStateTask CreateOnDataReadyTask();
    EnterStateTask CreateOnMakeCanvasImageTask();
    EnterStateTask CreateOnLoadSuccessTask();
    EnterStateTask CreateOnLoadFailTask();

    ImageSourceInfo sourceInfo_;
    RefPtr<ImageStateManager> stateManager_;
    RefPtr<ImageObject> imageObj_;

    // [LoadNotifier] contains 3 tasks to notify whom uses [ImageLoadingContext] of loading results
    LoadNotifier loadNotifier_;

    // [LoadCallbacks] contains 3 tasks to notify [ImageLoadingContext] itself to handle loading results
    LoadCallbacks loadCallbacks_;

    RectF srcRect_;
    RectF dstRect_;
    SizeF dstSize_;
    bool needResize_ = true;
    ImageFit imageFit_ = ImageFit::COVER;
    std::unique_ptr<std::pair<Dimension, Dimension>> sourceSizePtr_ = nullptr;
    bool needAlt_ = true;
    std::function<void()> updateParamsCallback_ = nullptr;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_IMAGE_PROVIDER_IMAGE_LOADING_CONTEXT_H
