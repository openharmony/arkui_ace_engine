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

#include "core/components_ng/image_provider/image_provider.h"

#include "core/common/container.h"
#include "core/common/container_scope.h"
#include "core/components_ng/image_provider/image_object.h"
#include "core/components_ng/image_provider/pixel_map_image_object.h"
#include "core/components_ng/image_provider/static_image_object.h"
#include "core/components_ng/image_provider/svg_image_object.h"
#include "core/components_ng/render/adapter/svg_canvas_image.h"
#include "core/image/image_loader.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

void ImageProvider::WrapTaskAndPostTo(
    std::function<void()>&& task, TaskExecutor::TaskType taskType, const char* taskTypeName)
{
    auto taskExecutor = Container::CurrentTaskExecutor();
    if (!taskExecutor) {
        LOGE("taskExecutor is null when try post task to %{public}s", taskTypeName);
        return;
    }
    taskExecutor->PostTask(
        [task, id = Container::CurrentId()] {
            ContainerScope scope(id);
            CHECK_NULL_VOID(task);
            task();
        },
        taskType);
}

#define WRAP_TASK_AND_POST_TO(thread, threadName)                                                       \
    void ImageProvider::WrapTaskAndPostTo##threadName(std::function<void()>&& task)                     \
    {                                                                                                   \
        CHECK_NULL_VOID(task);                                                                          \
        ImageProvider::WrapTaskAndPostTo(std::move(task), TaskExecutor::TaskType::thread, #threadName); \
    }
WRAP_TASK_AND_POST_TO(UI, UI);
WRAP_TASK_AND_POST_TO(BACKGROUND, Background);
WRAP_TASK_AND_POST_TO(IO, IO);

bool ImageProvider::PrepareImageData(const RefPtr<ImageObject>& imageObj)
{
    CHECK_NULL_RETURN(imageObj, false);
    // data already loaded
    if (imageObj->GetData()) {
        return true;
    }
    // if image object has no skData, reload data.
    std::string errorMessage;
    do {
        auto imageLoader = ImageLoader::CreateImageLoader(imageObj->GetSourceInfo());
        if (!imageLoader) {
            errorMessage = "Fail to create image loader. Image source type is not supported";
            break;
        }
        auto newLoadedData = imageLoader->GetImageData(
            imageObj->GetSourceInfo(), WeakClaim(RawPtr(NG::PipelineContext::GetCurrentContext())));
        if (!newLoadedData) {
            errorMessage = "Fail to load data, please check if data source is invalid";
            break;
        }
        // load data success
        imageObj->SetData(newLoadedData);
        return true;
    } while (false);
    return false;
}

RefPtr<ImageEncodedInfo> ImageEncodedInfo::CreateImageEncodedInfo(
    const RefPtr<NG::ImageData>& data, const ImageSourceInfo& sourceInfo, ImageObjectType imageObjectType)
{
    switch (imageObjectType) {
        case ImageObjectType::STATIC_IMAGE_OBJECT:
            return ImageEncodedInfo::CreateImageEncodedInfoForStaticImage(data);
        case ImageObjectType::PIXEL_MAP_IMAGE_OBJECT:
            return ImageEncodedInfo::CreateImageEncodedInfoForDecodedPixelMap(data, sourceInfo);
        case ImageObjectType::SVG_IMAGE_OBJECT:
            return ImageEncodedInfo::CreateImageEncodedInfoForSvg(data);
        case ImageObjectType::UNKNOWN:
        default:
            return nullptr;
    }
}

RefPtr<ImageEncodedInfo> ImageEncodedInfo::CreateImageEncodedInfoForDecodedPixelMap(
    const RefPtr<NG::ImageData>& data, const ImageSourceInfo& sourceInfo)
{
    auto pixelMap = data->GetPixelMapData();
    if (!pixelMap) {
        LOGW(
            "ImageData has no pixel map data when try CreateImageEncodedInfoForDecodedPixelMap, sourceInfo: %{public}s",
            sourceInfo.ToString().c_str());
        return nullptr;
    }
    return MakeRefPtr<ImageEncodedInfo>(SizeF(pixelMap->GetWidth(), pixelMap->GetHeight()), 1);
}

ImageObjectType ImageProvider::ParseImageObjectType(
    const RefPtr<NG::ImageData>& data, const ImageSourceInfo& imageSourceInfo)
{
    if (!data) {
        LOGW("data is null when try ParseImageObjectType, sourceInfo: %{public}s", imageSourceInfo.ToString().c_str());
        return ImageObjectType::UNKNOWN;
    }
    if (imageSourceInfo.IsSvg()) {
        return ImageObjectType::SVG_IMAGE_OBJECT;
    }
    if (imageSourceInfo.IsPixmap()) {
        return ImageObjectType::PIXEL_MAP_IMAGE_OBJECT;
    }
    return ImageObjectType::STATIC_IMAGE_OBJECT;
}

bool ImageProvider::QueryImageObjectFromCache(const LoadCallbacks& loadCallbacks, const ImageSourceInfo& sourceInfo)
{
    auto pipelineCtx = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineCtx, false);
    auto imageCache = pipelineCtx->GetImageCache();
    if (!imageCache) {
        LOGD("No image cache.");
        return false;
    }
    RefPtr<ImageObject> imageObj = imageCache->GetCacheImgObjNG(sourceInfo.ToString());
    if (imageObj && imageObj->GetSourceInfo() == sourceInfo) {
        LOGD("imageObject cache found %{private}s", sourceInfo.ToString().c_str());
        // if [imageObj] of [sourceInfo] is already in cache, notify data ready immediately
        loadCallbacks.dataReadyCallback_(sourceInfo, imageObj);
        return true;
    }
    return false;
}

// helper function to run StateManager LoadFail callback
void ImageProvider::FailCallback(
    const LoadFailCallback& callback, const ImageSourceInfo& sourceInfo, const std::string& errorMsg, bool sync)
{
    if (sync) {
        callback(sourceInfo, errorMsg, ImageLoadingCommand::LOAD_DATA_FAIL);
        return;
    }
    auto notifyLoadFailTask = [sourceInfo, callback, errorMsg] {
        callback(sourceInfo, errorMsg, ImageLoadingCommand::LOAD_DATA_FAIL);
    };
    ImageProvider::WrapTaskAndPostToUI(std::move(notifyLoadFailTask));
}

void ImageProvider::SuccessCallback(const RefPtr<CanvasImage>& canvasImage, const WeakPtr<ImageObject>& objWp,
    const LoadSuccessCallback& callback, bool sync)
{
    // when upload success, update canvas image to ImageObject and trigger loadSuccessCallback_
    auto notifyLoadSuccessTask = [objWp, callback, canvasImage] {
        auto obj = objWp.Upgrade();
        CHECK_NULL_VOID(obj);
        obj->SetCanvasImage(canvasImage);
        obj->SetData(nullptr); // clear raw image data
        callback(obj->GetSourceInfo());
    };
    if (sync) {
        notifyLoadSuccessTask();
    } else {
        ImageProvider::WrapTaskAndPostToUI(std::move(notifyLoadSuccessTask));
    }
}

void ImageProvider::CreateImageObjHelper(const ImageSourceInfo& sourceInfo, const LoadCallbacks& loadCallbacks,
    const std::optional<Color>& svgFillColor, bool sync)
{
    // step1: load image data
    auto imageLoader = ImageLoader::CreateImageLoader(sourceInfo);
    if (!imageLoader) {
        std::string errorMessage("Fail to create image loader, Image source type not supported");
        FailCallback(loadCallbacks.loadFailCallback_, sourceInfo, errorMessage, sync);
        return;
    }
    RefPtr<ImageData> data =
        imageLoader->GetImageData(sourceInfo, WeakClaim(RawPtr(NG::PipelineContext::GetCurrentContext())));

    // step2: make codec to determine which ImageObject to create
    auto imageObjectType = ImageProvider::ParseImageObjectType(data, sourceInfo);
    auto encodedInfo = ImageEncodedInfo::CreateImageEncodedInfo(data, sourceInfo, imageObjectType);
    if (!encodedInfo) {
        std::string errorMessage("Fail to make encoded info, Image data is broken.");
        FailCallback(loadCallbacks.loadFailCallback_, sourceInfo, errorMessage, sync);
        return;
    }

    // step3: build ImageObject according to encoded info
    RefPtr<ImageObject> imageObj = ImageProvider::BuildImageObject(sourceInfo, encodedInfo, data, imageObjectType);
    if (!imageObj) {
        FailCallback(loadCallbacks.loadFailCallback_, sourceInfo, "Fail to build image object", sync);
    }
    if (sync) {
        loadCallbacks.dataReadyCallback_(sourceInfo, imageObj);
    } else {
        auto notifyDataReadyTask = [loadCallbacks, imageObj, sourceInfo] {
            loadCallbacks.dataReadyCallback_(sourceInfo, imageObj);
        };
        ImageProvider::WrapTaskAndPostToUI(std::move(notifyDataReadyTask));
    }
}

void ImageProvider::CreateImageObject(
    const ImageSourceInfo& sourceInfo, const LoadCallbacks& loadCallbacks, const std::optional<Color>& svgFillColor)
{
    if (ImageProvider::QueryImageObjectFromCache(loadCallbacks, sourceInfo)) {
        return;
    }
    auto createImageObjectTask = [sourceInfo, loadCallbacks, svgFillColor] {
        CreateImageObjHelper(sourceInfo, loadCallbacks, svgFillColor);
    };
    ImageProvider::WrapTaskAndPostToBackground(std::move(createImageObjectTask));
}

void SyncImageProvider::CreateImageObject(
    const ImageSourceInfo& sourceInfo, const LoadCallbacks& loadCallbacks, const std::optional<Color>& svgFillColor)
{
    if (ImageProvider::QueryImageObjectFromCache(loadCallbacks, sourceInfo)) {
        return;
    }
    ImageProvider::CreateImageObjHelper(sourceInfo, loadCallbacks, svgFillColor, true);
}

RefPtr<ImageObject> ImageProvider::BuildImageObject(const ImageSourceInfo& sourceInfo,
    const RefPtr<ImageEncodedInfo>& encodedInfo, const RefPtr<ImageData>& data, ImageObjectType imageObjectType)
{
    switch (imageObjectType) {
        case ImageObjectType::STATIC_IMAGE_OBJECT:
            return StaticImageObject::Create(sourceInfo, encodedInfo, data);
        // pixelMap always synchronous
        case ImageObjectType::PIXEL_MAP_IMAGE_OBJECT:
            return PixelMapImageObject::Create(sourceInfo, encodedInfo, data);
        case ImageObjectType::SVG_IMAGE_OBJECT: {
            // SVG object needs to make SVG dom during creation
            return SvgImageObject::Create(sourceInfo, encodedInfo, data);
        }
        case ImageObjectType::UNKNOWN:
            LOGE("Unknown ImageObject type, sourceInfo: %{public}s", sourceInfo.ToString().c_str());
            [[fallthrough]];
        default:
            return nullptr;
    }
}

void ImageProvider::MakeSvgCanvasImage(const WeakPtr<SvgImageObject>& imageObjWp, const LoadCallbacks& loadCallbacks)
{
    auto obj = imageObjWp.Upgrade();
    CHECK_NULL_VOID(obj && obj->GetSVGDom());
    // just set svgDom to canvasImage
    obj->SetCanvasImage(MakeRefPtr<NG::SvgCanvasImage>(obj->GetSVGDom()));
    loadCallbacks.loadSuccessCallback_(obj->GetSourceInfo());
}

std::string ImageProvider::GenerateCacheKey(const ImageSourceInfo& srcInfo, const NG::SizeF& targetImageSize)
{
    return srcInfo.GetCacheKey() + std::to_string(static_cast<int32_t>(targetImageSize.Width())) +
           std::to_string(static_cast<int32_t>(targetImageSize.Height()));
}

} // namespace OHOS::Ace::NG
