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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_IMAGE_PROVIDER_IMAGE_PROVIDER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_IMAGE_PROVIDER_IMAGE_PROVIDER_H

#include <functional>

#include "third_party/skia/include/core/SkData.h"

#include "base/geometry/ng/rect_t.h"
#include "core/components_ng/image_provider/image_data.h"
#include "core/components_ng/image_provider/image_state_manager.h"
#include "core/components_ng/render/canvas_image.h"
#include "core/image/image_source_info.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

enum class ImageObjectType {
    UNKNOWN = -1,
    STATIC_IMAGE_OBJECT,
    PIXEL_MAP_IMAGE_OBJECT,
    SVG_IMAGE_OBJECT,
};

using DataReadyNotifyTask = std::function<void(const ImageSourceInfo& sourceInfo)>;
using LoadSuccessNotifyTask = std::function<void(const ImageSourceInfo& sourceInfo)>;
using LoadFailNotifyTask = std::function<void(const ImageSourceInfo& sourceInfo)>;

struct LoadNotifier {
    LoadNotifier(DataReadyNotifyTask&& dataReadyNotifyTask, LoadSuccessNotifyTask&& loadSuccessNotifyTask,
        LoadFailNotifyTask&& loadFailNotifyTask)
        : dataReadyNotifyTask_(std::move(dataReadyNotifyTask)),
          loadSuccessNotifyTask_(std::move(loadSuccessNotifyTask)), loadFailNotifyTask_(std::move(loadFailNotifyTask))
    {}
    ~LoadNotifier() = default;

    DataReadyNotifyTask dataReadyNotifyTask_;
    LoadSuccessNotifyTask loadSuccessNotifyTask_;
    LoadFailNotifyTask loadFailNotifyTask_;
};

class ImageObject;
class StaticImageObject;
class SvgImageObject;
using DataReadyCallback = std::function<void(const ImageSourceInfo& sourceInfo, const RefPtr<ImageObject>& imageObj)>;
using LoadSuccessCallback = std::function<void(const ImageSourceInfo& sourceInfo)>;
using LoadFailCallback = std::function<void(
    const ImageSourceInfo& sourceInfo, const std::string& errorMsg, ImageLoadingCommand imageLoadingCommand)>;

struct LoadCallbacks {
    LoadCallbacks(DataReadyCallback&& dataReadyCallback, LoadSuccessCallback&& loadSuccessCallback,
        LoadFailCallback&& loadFailCallback)
        : dataReadyCallback_(std::move(dataReadyCallback)), loadSuccessCallback_(std::move(loadSuccessCallback)),
          loadFailCallback_(std::move(loadFailCallback))
    {}
    ~LoadCallbacks() = default;

    DataReadyCallback dataReadyCallback_;
    LoadSuccessCallback loadSuccessCallback_;
    LoadFailCallback loadFailCallback_;
};

class ImageEncodedInfo : public virtual AceType {
    DECLARE_ACE_TYPE(ImageEncodedInfo, AceType);

public:
    ImageEncodedInfo(const SizeF& imageSize, int32_t frameCount) : imageSize_(imageSize), frameCount_(frameCount) {}
    ~ImageEncodedInfo() override = default;

    static RefPtr<ImageEncodedInfo> CreateImageEncodedInfo(
        const RefPtr<NG::ImageData>& data, const ImageSourceInfo& imageSourceInfo, ImageObjectType imageObjectType);
    static RefPtr<ImageEncodedInfo> CreateImageEncodedInfoForStaticImage(const RefPtr<NG::ImageData>& data);
    static RefPtr<ImageEncodedInfo> CreateImageEncodedInfoForSvg(const RefPtr<NG::ImageData>& data);
    static RefPtr<ImageEncodedInfo> CreateImageEncodedInfoForDecodedPixelMap(
        const RefPtr<NG::ImageData>& data, const ImageSourceInfo& sourceInfo);
    const SizeF& GetImageSize() const
    {
        return imageSize_;
    }
    int32_t GetFrameCount() const
    {
        return frameCount_;
    }
    std::string ToString() const
    {
        return std::string("encoded info is: size = ")
            .append(imageSize_.ToString())
            .append(", frame count = ")
            .append(std::to_string(frameCount_));
    }

private:
    SizeF imageSize_;
    int32_t frameCount_ = 1;
};

struct RenderTaskHolder : public virtual AceType {
    DECLARE_ACE_TYPE(RenderTaskHolder, AceType);

public:
    RenderTaskHolder() = default;
    ~RenderTaskHolder() override = default;
};

class ImageProvider : public virtual AceType {
    DECLARE_ACE_TYPE(ImageProvider, AceType);

public:
    static RefPtr<RenderTaskHolder> CreateRenderTaskHolder();
    static void MakeSvgDom(const RefPtr<SvgImageObject>& imageObj, const LoadCallbacks& loadCallbacks,
        const std::optional<Color>& svgFillColor);
    static void PrepareImageData(const RefPtr<ImageObject>& imageObj, const LoadCallbacks& loadCallbacks);
    static void CreateImageObject(const ImageSourceInfo& sourceInfo, const LoadCallbacks& loadCallbacks,
        const std::optional<Color>& svgFillColor);
    static void MakeCanvasImage(const WeakPtr<ImageObject>& imageObjWp, const LoadCallbacks& loadCallbacks,
        const SizeF& resizeTarget, const RefPtr<RenderTaskHolder>& renderTaskHolder, bool forceResize = false);
    static void MakeCanvasImageForSVG(const WeakPtr<SvgImageObject>& imageObjWp, const LoadCallbacks& loadCallbacks);
    static void UploadImageToGPUForRender(const RefPtr<CanvasImage>& canvasImage,
        std::function<void(RefPtr<CanvasImage>)>&& callback, const RefPtr<RenderTaskHolder>& renderTaskHolder);
    static RefPtr<ImageObject> BuildImageObject(const ImageSourceInfo& sourceInfo,
        const RefPtr<ImageEncodedInfo>& encodedInfo, const RefPtr<ImageData>& data,
        const std::optional<Color>& svgFillColor, const LoadCallbacks& loadCallbacks, ImageObjectType imageObjectType);
    static ImageObjectType ParseImageObjectType(
        const RefPtr<NG::ImageData>& data, const ImageSourceInfo& imageSourceInfo);

protected:
    static void WrapTaskAndPostTo(
        std::function<void()>&& task, TaskExecutor::TaskType taskType, const char* taskTypeName);
    static void WrapTaskAndPostToUI(std::function<void()>&& task);
    static void WrapTaskAndPostToBackground(std::function<void()>&& task);
    static void WrapTaskAndPostToIO(std::function<void()>&& task);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_IMAGE_PROVIDER_IMAGE_PROVIDER_H
