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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_IMAGE_PROVIDER_IMAGE_PROVIDER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_IMAGE_PROVIDER_IMAGE_PROVIDER_H

#include <functional>
#include <set>
#include <unordered_map>

#include "base/geometry/ng/rect_t.h"
#include "base/thread/cancelable_callback.h"
#include "base/utils/noncopyable.h"
#include "core/components_ng/image_provider/image_data.h"
#include "core/components_ng/image_provider/image_state_manager.h"
#include "core/components_ng/render/canvas_image.h"
#include "core/image/image_source_info.h"

namespace OHOS::Ace::NG {

using DataReadyNotifyTask = std::function<void(const ImageSourceInfo& src)>;
using LoadSuccessNotifyTask = std::function<void(const ImageSourceInfo& src)>;
using LoadFailNotifyTask = std::function<void(const ImageSourceInfo& src)>;

struct LoadNotifier {
    LoadNotifier(DataReadyNotifyTask&& dataReadyNotifyTask, LoadSuccessNotifyTask&& loadSuccessNotifyTask,
        LoadFailNotifyTask&& loadFailNotifyTask)
        : dataReadyNotifyTask_(std::move(dataReadyNotifyTask)),
          loadSuccessNotifyTask_(std::move(loadSuccessNotifyTask)), loadFailNotifyTask_(std::move(loadFailNotifyTask))
    {}

    DataReadyNotifyTask dataReadyNotifyTask_;
    LoadSuccessNotifyTask loadSuccessNotifyTask_;
    LoadFailNotifyTask loadFailNotifyTask_;
};

class ImageObject;

struct RenderTaskHolder : public virtual AceType {
    DECLARE_ACE_TYPE(RenderTaskHolder, AceType);

public:
    RenderTaskHolder() = default;
    ~RenderTaskHolder() override = default;

    ACE_DISALLOW_COPY_AND_MOVE(RenderTaskHolder);
};

// load & paint images on background threads
// cache loaded/painted image data in memory
class ImageProvider : public virtual AceType {
    DECLARE_ACE_TYPE(ImageProvider, AceType);

public:
    static void CreateImageObject(const ImageSourceInfo& src, const WeakPtr<ImageLoadingContext>& ctxWp, bool sync);

    static void MakeCanvasImage(const WeakPtr<ImageObject>& objWp, const WeakPtr<ImageLoadingContext>& ctxWp,
        const SizeF& targetSize, bool forceResize = false, bool sync = false);

    // Query [CanvasImage] from cache, if hit, notify load success immediately and returns true
    static RefPtr<CanvasImage> QueryCanvasImageFromCache(const ImageSourceInfo& src, const SizeF& targetSize);

    // Query imageObj from cache, if hit, notify dataReady and returns true
    static RefPtr<ImageObject> QueryImageObjectFromCache(const ImageSourceInfo& src);
    // generate cache key for canvasImage, combining src and image size
    static std::string GenerateImageKey(const ImageSourceInfo& src, const NG::SizeF& targetSize);

    // cancel a scheduled background task
    static void CancelTask(const std::string& key, const WeakPtr<ImageLoadingContext>& ctx);

private:
    // create RenderTaskHolder for skiaGPUObject
    static RefPtr<RenderTaskHolder> CreateRenderTaskHolder();

    /** Check if task is already running and register task in the task map,
     * making sure the same task runs only once (CreateImageObject with same
     * [src], MakeCanvasImage with the same [imageObj] and [size]).
     *
     *    @param key              task key, based on [src] +? [size]
     *    @param ctx              ImageLoadingContext that initiates the task, to be stored in the amp
     *    @return                 true if task is new, false if task is already running
     */
    static bool RegisterTask(const std::string& key, const WeakPtr<ImageLoadingContext>& ctx);

    // mark a task as finished, erase from map and retrieve corresponding ctxs
    static std::set<WeakPtr<ImageLoadingContext>> EndTask(const std::string& key);

    /** Check if data is present in imageObj, if not, load image data.
     *
     *    @param imageObj         contains image source and image data
     *    @return                 true if image data is prepared
     */
    static bool PrepareImageData(const RefPtr<ImageObject>& imageObj);

    static RefPtr<ImageObject> BuildImageObject(const ImageSourceInfo& src, const RefPtr<ImageData>& data);

    static void CacheCanvasImage(const RefPtr<CanvasImage>& canvasImage, const std::string& key);

    // helper function to create image object from ImageSourceInfo
    static void CreateImageObjHelper(const ImageSourceInfo& src, bool sync = false);

    /** Helper function to create canvasImage and upload it to GPU for rendering.
     *
     *    @param imageObjWp           weakPtr of imageObj, contains image data
     *    @param renderTaskHolder     passed in to create SkiaGPUObject
     */
    static void MakeCanvasImageHelper(const WeakPtr<ImageObject>& imageObjWp, const SizeF& targetSize,
        const RefPtr<RenderTaskHolder>& renderTaskHolder, bool forceResize, bool sync = false);

    static void UploadImageToGPUForRender(const RefPtr<CanvasImage>& canvasImage,
        std::function<void(RefPtr<CanvasImage>)>&& callback, const RefPtr<RenderTaskHolder>& renderTaskHolder,
        const std::string& key, const SizeF& resizeTarget, const RefPtr<ImageData>& data, bool syncLoad);

    // helper functions to end task and callback to LoadingContexts
    static void SuccessCallback(const RefPtr<CanvasImage>& canvasImage, const std::string& key, bool sync = false);
    static void FailCallback(const std::string& key, const std::string& errorMsg, bool sync = false);

    struct Task {
        CancelableCallback<void()> bgTask_;
        std::set<WeakPtr<ImageLoadingContext>> ctxs_;
    };

    static std::mutex taskMtx_;
    static std::unordered_map<std::string, Task> tasks_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_IMAGE_PROVIDER_IMAGE_PROVIDER_H
