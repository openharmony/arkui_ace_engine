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

#include "base/image/pixel_map.h"
#include "base/thread/cancelable_callback.h"
#include "core/components_ng/image_provider/image_data.h"
#include "core/components_ng/image_provider/image_state_manager.h"
#include "core/components_ng/pattern/image/image_dfx.h"
#include "core/components_ng/render/canvas_image.h"
#include "core/image/image_source_info.h"

namespace OHOS::Ace::NG {

using DataReadyNotifyTask = std::function<void(const ImageSourceInfo& src)>;
using LoadSuccessNotifyTask = std::function<void(const ImageSourceInfo& src)>;
using LoadFailNotifyTask = std::function<void(const ImageSourceInfo& src, const std::string& errorMsg)>;
using OnCompleteInDataReadyNotifyTask = std::function<void(const ImageSourceInfo& src)>;

struct LoadNotifier {
    LoadNotifier(DataReadyNotifyTask&& dataReadyNotifyTask, LoadSuccessNotifyTask&& loadSuccessNotifyTask,
        LoadFailNotifyTask&& loadFailNotifyTask)
        : onDataReady_(std::move(dataReadyNotifyTask)), onLoadSuccess_(std::move(loadSuccessNotifyTask)),
          onLoadFail_(std::move(loadFailNotifyTask))
    {}

    DataReadyNotifyTask onDataReady_;
    LoadSuccessNotifyTask onLoadSuccess_;
    LoadFailNotifyTask onLoadFail_;
    OnCompleteInDataReadyNotifyTask onDataReadyComplete_;
};

struct ImageDecoderOptions {
    bool forceResize = false;
    bool sync = false;
    DynamicRangeMode dynamicMode = DynamicRangeMode::STANDARD;
    AIImageQuality imageQuality = AIImageQuality::NONE;
    bool isHdrDecoderNeed = false;
    PixelFormat photoDecodeFormat = PixelFormat::UNKNOWN;
    ImageDfxConfig imageDfxConfig;
};

struct UriDownLoadConfig {
    ImageSourceInfo src;
    ImageDfxConfig imageDfxConfig;
    std::string taskKey;
    bool sync;
    bool hasProgressCallback;
};

class ImageObject;

// load & decode images
class ImageProvider : public virtual AceType {
    DECLARE_ACE_TYPE(ImageProvider, AceType);

public:
    /** Fetch image data and create ImageObject from ImageSourceInfo.
     *
     *    @param src                  image source info
     *    @param ctxWp                ImageLoadingContext that initiates the task, to be stored in the map
     *    @param sync                 if true, run task synchronously
     */
    static void CreateImageObject(const ImageSourceInfo& src, const WeakPtr<ImageLoadingContext>& ctxWp, bool sync);

    /** Decode image data and make CanvasImage from ImageObject.
     *
     *    @param obj                  imageObject, contains image data
     *    @param targetSize           target size of canvasImage
     *    @param forceResize          force resize image to target size
     *    @param sync                 if true, run task synchronously
     *    @param dynamicMode          set dynamic range mode of image
     *    @param imageQuality         set the image quality enhancement level of image
     *    @return                     true if MakeCanvasImage was successful
     */
    static void MakeCanvasImage(const RefPtr<ImageObject>& obj, const WeakPtr<ImageLoadingContext>& ctxWp,
        const SizeF& targetSize, const ImageDecoderOptions& imageDecoderOptions);

    /** Check if data is present in imageObj, if not, reload image data.
     *
     *    @param imageObj         contains image source and image data
     *    @return                 true if image data is prepared
     */
    static bool PrepareImageData(const RefPtr<ImageObject>& imageObj);

    // Query imageObj from cache, if hit, notify dataReady and returns true
    static RefPtr<ImageObject> QueryImageObjectFromCache(const ImageSourceInfo& src);

    // cancel a scheduled background task
    static bool CancelTask(const std::string& key, const WeakPtr<ImageLoadingContext>& ctx);

    static RefPtr<ImageObject> BuildImageObject(const ImageSourceInfo& src, const RefPtr<ImageData>& data);

    static void CacheImageObject(const RefPtr<ImageObject>& obj);

    static RefPtr<ImageData> QueryDataFromCache(const ImageSourceInfo& src);

private:
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
    static std::set<WeakPtr<ImageLoadingContext>> EndTask(const std::string& key, bool isErase = true);

    static RefPtr<ImageObject> QueryThumbnailCache(const ImageSourceInfo& src);

    // helper function to create image object from ImageSourceInfo
    static void CreateImageObjHelper(const ImageSourceInfo& src, bool sync = false);

    static void DownLoadSuccessCallback(
        const RefPtr<ImageObject>& imageObj, const std::string& key, bool sync = false, int32_t containerId = 0);
    static void DownLoadOnProgressCallback(
        const std::string& key, bool sync, const uint32_t& dlNow, const uint32_t& dlTotal, int32_t containerId = 0);
    static void DownLoadImage(const UriDownLoadConfig& downLoadConfig);

    static void MakeCanvasImageHelper(const RefPtr<ImageObject>& obj, const SizeF& targetSize, const std::string& key,
        const ImageDecoderOptions& imagedecoderOptions);

    // helper functions to end task and callback to LoadingContexts
    static void SuccessCallback(
        const RefPtr<CanvasImage>& canvasImage, const std::string& key, bool sync = false, int32_t containerId = 0);
    static void FailCallback(
        const std::string& key, const std::string& errorMsg, bool sync = false, int32_t containerId = 0);

    struct Task {
        CancelableCallback<void()> bgTask_;
        std::set<WeakPtr<ImageLoadingContext>> ctxs_;
    };

    static std::timed_mutex taskMtx_;
    static std::unordered_map<std::string, Task> tasks_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_IMAGE_PROVIDER_IMAGE_PROVIDER_H
