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
            task();
        },
        taskType);
}

#define WRAP_TASK_AND_POST_TO(thread, threadName)                                                       \
    void ImageProvider::WrapTaskAndPostTo##threadName(std::function<void()>&& task)                     \
    {                                                                                                   \
        ImageProvider::WrapTaskAndPostTo(std::move(task), TaskExecutor::TaskType::thread, #threadName); \
    }
WRAP_TASK_AND_POST_TO(UI, UI);
WRAP_TASK_AND_POST_TO(BACKGROUND, Background);
WRAP_TASK_AND_POST_TO(IO, IO);

void ImageProvider::PrepareImageData(const RefPtr<ImageObject>& imageObj, const LoadCallbacks& loadCallbacks)
{
    CHECK_NULL_VOID(imageObj);
    // if image object has no skData, reload data.
    if (imageObj->GetData()) {
        return;
    }
    std::string errorMessage("");
    do {
        auto imageLoader = ImageLoader::CreateImageLoader(imageObj->GetSourceInfo());
        if (!imageLoader) {
            LOGE("Fail to create image loader. source info: %{private}s", imageObj->GetSourceInfo().ToString().c_str());
            errorMessage = "Image source type is not supported";
            break;
        }
        auto newLoadedData = imageLoader->GetImageData(
            imageObj->GetSourceInfo(), WeakClaim(RawPtr(NG::PipelineContext::GetCurrentContext())));
        if (!newLoadedData) {
            errorMessage = "Fail to load data, please check if data source is invalid";
            break;
        }
        imageObj->SetData(newLoadedData);
    } while (false);
    if (!imageObj->GetData()) {
        auto notifyLoadFailTask = [errorMsg = std::move(errorMessage), sourceInfo = imageObj->GetSourceInfo(),
                                      loadCallbacks] {
            loadCallbacks.loadFailCallback_(sourceInfo, errorMsg, ImageLoadingCommand::MAKE_CANVAS_IMAGE_FAIL);
        };
        ImageProvider::WrapTaskAndPostToUI(std::move(notifyLoadFailTask));
        return;
    }
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
        LOGW(
            "data is null when try ParseImageObjectType, sourceInfo: %{public}s", imageSourceInfo.ToString().c_str());
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

void ImageProvider::CreateImageObject(
    const ImageSourceInfo& sourceInfo, const LoadCallbacks& loadCallbacks, const std::optional<Color>& svgFillColor)
{
    auto createImageObjectTask = [sourceInfo, loadCallbacks, svgFillColor] {
        // step1: load image data
        auto imageLoader = ImageLoader::CreateImageLoader(sourceInfo);
        if (!imageLoader) {
            LOGE("Fail to create image loader. source info: %{public}s", sourceInfo.ToString().c_str());
            std::string errorMessage("Image source type not supported");
            auto notifyLoadFailTask = [errorMsg = std::move(errorMessage), sourceInfo, loadCallbacks] {
                loadCallbacks.loadFailCallback_(sourceInfo, errorMsg, ImageLoadingCommand::LOAD_DATA_FAIL);
            };
            ImageProvider::WrapTaskAndPostToUI(std::move(notifyLoadFailTask));
            return;
        }
        RefPtr<ImageData> data =
            imageLoader->GetImageData(sourceInfo, WeakClaim(RawPtr(NG::PipelineContext::GetCurrentContext())));

        // step2: make codec to determine which ImageObject to create
        auto imageObjectType = ImageProvider::ParseImageObjectType(data, sourceInfo);
        auto encodedInfo = ImageEncodedInfo::CreateImageEncodedInfo(data, sourceInfo, imageObjectType);
        if (!encodedInfo) {
            LOGE("Fail to make encoded info. source info: %{public}s", sourceInfo.ToString().c_str());
            std::string errorMessage("Image data is broken.");
            auto notifyLoadFailTask = [errorMsg = std::move(errorMessage), sourceInfo, loadCallbacks] {
                loadCallbacks.loadFailCallback_(sourceInfo, errorMsg, ImageLoadingCommand::LOAD_DATA_FAIL);
            };
            ImageProvider::WrapTaskAndPostToUI(std::move(notifyLoadFailTask));
            return;
        }

        // step3: build ImageObject accroding to encoded info
        RefPtr<ImageObject> imageObj = ImageProvider::BuildImageObject(
            sourceInfo, encodedInfo, data, svgFillColor, loadCallbacks, imageObjectType);
        if (!imageObj) {
            return;
        }
        auto notifyDataReadyTask = [loadCallbacks, imageObj, sourceInfo] {
            loadCallbacks.dataReadyCallback_(sourceInfo, imageObj);
        };
        ImageProvider::WrapTaskAndPostToUI(std::move(notifyDataReadyTask));
    };
    ImageProvider::WrapTaskAndPostToBackground(std::move(createImageObjectTask));
}

RefPtr<ImageObject> ImageProvider::BuildImageObject(const ImageSourceInfo& sourceInfo,
    const RefPtr<ImageEncodedInfo>& encodedInfo, const RefPtr<ImageData>& data,
    const std::optional<Color>& svgFillColor, const LoadCallbacks& loadCallbacks, ImageObjectType imageObjectType)
{
    switch (imageObjectType) {
        case ImageObjectType::STATIC_IMAGE_OBJECT:
            return StaticImageObject::Create(sourceInfo, encodedInfo, data);
        case ImageObjectType::PIXEL_MAP_IMAGE_OBJECT:
            return PixelMapImageObject::Create(sourceInfo, encodedInfo, data);
        case ImageObjectType::SVG_IMAGE_OBJECT:
            return SvgImageObject::Create(sourceInfo, encodedInfo, data, svgFillColor, loadCallbacks);
        case ImageObjectType::UNKNOWN:
            LOGE("Unknown ImageObject type, sourceInfo: %{public}s", sourceInfo.ToString().c_str());
        default:
            return nullptr;
    }
}

void ImageProvider::MakeSvgDom(const RefPtr<SvgImageObject>& imageObj, const LoadCallbacks& loadCallbacks,
    const std::optional<Color>& svgFillColor)
{
    CHECK_NULL_VOID(imageObj);
    // if image object has no skData, reload data.
    ImageProvider::PrepareImageData(imageObj, loadCallbacks);
    // get SVGImageDOM
    if (!imageObj->MakeSvgDom(svgFillColor)) {
        LOGE("svg image MakeFromStream fail! source info: %{private}s", imageObj->GetSourceInfo().ToString().c_str());
        std::string errorMessage;
        auto notifyLoadFailTask = [errorMsg = std::move(errorMessage), loadCallbacks,
                                      sourceInfo = imageObj->GetSourceInfo()] {
            loadCallbacks.loadFailCallback_(sourceInfo, errorMsg, ImageLoadingCommand::LOAD_DATA_FAIL);
        };
        ImageProvider::WrapTaskAndPostToUI(std::move(notifyLoadFailTask));
        return;
    }
}

void ImageProvider::MakeCanvasImageForSVG(const WeakPtr<SvgImageObject>& imageObjWp, const LoadCallbacks& loadCallbacks)
{
    auto canvasImageMakingTask = [objWp = imageObjWp, loadCallbacks] {
        // update SVGSkiaDom to ImageObject and trigger loadSuccessCallback_
        auto notifyLoadSuccessTask = [objWp, loadCallbacks] {
            auto obj = objWp.Upgrade();
            CHECK_NULL_VOID(obj);
            CHECK_NULL_VOID(obj->GetSVGDom());
            // upload canvasImage, in order to set svgDom
            obj->SetCanvasImage(MakeRefPtr<NG::SvgCanvasImage>(obj->GetSVGDom()));
            loadCallbacks.loadSuccessCallback_(obj->GetSourceInfo());
        };
        ImageProvider::WrapTaskAndPostToUI(std::move(notifyLoadSuccessTask));
    };
    // TODO: add sync load
    ImageProvider::WrapTaskAndPostToBackground(std::move(canvasImageMakingTask));
}

} // namespace OHOS::Ace::NG
