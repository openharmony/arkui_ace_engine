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

#include "core/components_ng/image_provider/image_provider.h"

#include <cstdint>
#include <mutex>

#include "base/log/ace_trace.h"
#include "base/memory/referenced.h"
#include "core/common/container.h"
#include "core/common/container_scope.h"
#include "core/components_ng/image_provider/image_loading_context.h"
#include "core/components_ng/image_provider/image_object.h"
#include "core/components_ng/image_provider/pixel_map_image_object.h"
#include "core/components_ng/image_provider/static_image_object.h"
#include "core/components_ng/image_provider/svg_image_object.h"
#include "core/components_ng/render/adapter/svg_canvas_image.h"
#include "core/image/image_loader.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

std::mutex ImageProvider::taskMtx_;
std::unordered_map<std::string, ImageProvider::Task> ImageProvider::tasks_;

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

void ImageProvider::WrapTaskAndPostToUI(std::function<void()>&& task)
{
    CHECK_NULL_VOID(task);
    ImageProvider::WrapTaskAndPostTo(std::move(task), TaskExecutor::TaskType::UI, "UI");
}

void ImageProvider::WrapTaskAndPostToBackground(std::function<void()>&& task)
{
    CHECK_NULL_VOID(task);
    ImageProvider::WrapTaskAndPostTo(std::move(task), TaskExecutor::TaskType::BACKGROUND, "BACKGROUND");
}

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
    const RefPtr<NG::ImageData>& data, const ImageSourceInfo& src, ImageObjectType imageObjectType)
{
    switch (imageObjectType) {
        case ImageObjectType::STATIC_IMAGE_OBJECT:
            return ImageEncodedInfo::CreateImageEncodedInfoForStaticImage(data);
        case ImageObjectType::PIXEL_MAP_IMAGE_OBJECT:
            return ImageEncodedInfo::CreateImageEncodedInfoForDecodedPixelMap(data, src);
        case ImageObjectType::SVG_IMAGE_OBJECT:
            return ImageEncodedInfo::CreateImageEncodedInfoForSvg(data);
        case ImageObjectType::UNKNOWN:
        default:
            return nullptr;
    }
}

RefPtr<ImageEncodedInfo> ImageEncodedInfo::CreateImageEncodedInfoForDecodedPixelMap(
    const RefPtr<NG::ImageData>& data, const ImageSourceInfo& src)
{
    auto pixelMap = data->GetPixelMapData();
    if (!pixelMap) {
        LOGW("ImageData has no pixel map data when try CreateImageEncodedInfoForDecodedPixelMap, src: %{public}s",
            src.ToString().c_str());
        return nullptr;
    }
    return MakeRefPtr<ImageEncodedInfo>(SizeF(pixelMap->GetWidth(), pixelMap->GetHeight()), 1);
}

ImageObjectType ImageProvider::ParseImageObjectType(const RefPtr<NG::ImageData>& data, const ImageSourceInfo& src)
{
    if (!data) {
        LOGW("data is null when try ParseImageObjectType, src: %{public}s", src.ToString().c_str());
        return ImageObjectType::UNKNOWN;
    }
    if (src.IsSvg()) {
        return ImageObjectType::SVG_IMAGE_OBJECT;
    }
    if (src.IsPixmap()) {
        return ImageObjectType::PIXEL_MAP_IMAGE_OBJECT;
    }
    return ImageObjectType::STATIC_IMAGE_OBJECT;
}

RefPtr<ImageObject> ImageProvider::QueryImageObjectFromCache(const ImageSourceInfo& src)
{
    auto pipelineCtx = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineCtx, nullptr);
    auto imageCache = pipelineCtx->GetImageCache();
    if (!imageCache) {
        LOGD("No image cache %{private}s.", src.ToString().c_str());
        return nullptr;
    }
    RefPtr<ImageObject> imageObj = imageCache->GetCacheImgObjNG(src.GetKey());
    if (imageObj) {
        LOGD("imageObj found in cache %{private}s", src.ToString().c_str());
    }
    return imageObj;
}

void ImageProvider::FailCallback(const std::string& key, const std::string& errorMsg, bool sync)
{
    auto ctxs = EndTask(key);
    auto notifyLoadFailTask = [ctxs, errorMsg] {
        for (auto&& it : ctxs) {
            auto ctx = it.Upgrade();
            if (!ctx) {
                continue;
            }
            ctx->FailCallback(errorMsg);
        }
    };
    if (sync) {
        notifyLoadFailTask();
    } else {
        ImageProvider::WrapTaskAndPostToUI(std::move(notifyLoadFailTask));
    }
}

void ImageProvider::SuccessCallback(const RefPtr<CanvasImage>& canvasImage, const std::string& key, bool sync)
{
    auto ctxs = EndTask(key);
    // when upload success, pass back canvasImage to LoadingContext
    auto notifyLoadSuccess = [ctxs, canvasImage] {
        for (auto&& it : ctxs) {
            auto ctx = it.Upgrade();
            if (!ctx) {
                continue;
            }
            ctx->SuccessCallback(canvasImage);
        }
    };
    if (sync) {
        notifyLoadSuccess();
    } else {
        ImageProvider::WrapTaskAndPostToUI(std::move(notifyLoadSuccess));
    }
}

void ImageProvider::CreateImageObjHelper(const ImageSourceInfo& src, bool sync)
{
    ACE_FUNCTION_TRACE();
    // step1: load image data
    auto imageLoader = ImageLoader::CreateImageLoader(src);
    if (!imageLoader) {
        std::string errorMessage("Fail to create image loader, Image source type not supported");
        FailCallback(src.GetKey(), errorMessage, sync);
        return;
    }
    RefPtr<ImageData> data =
        imageLoader->GetImageData(src, WeakClaim(RawPtr(NG::PipelineContext::GetCurrentContext())));

    // step2: get image size and frame count from data
    ImageObjectType type = ImageProvider::ParseImageObjectType(data, src);
    auto encodedInfo = ImageEncodedInfo::CreateImageEncodedInfo(data, src, type);
    if (!encodedInfo) {
        std::string errorMessage("Fail to make encoded info, Image data is broken.");
        FailCallback(src.GetKey(), errorMessage, sync);
        return;
    }

    // step3: build ImageObject
    RefPtr<ImageObject> imageObj = ImageProvider::BuildImageObject(src, encodedInfo, data, type);
    if (!imageObj) {
        FailCallback(src.GetKey(), "Fail to build image object", sync);
    }

    auto ctxs = EndTask(src.GetKey());
    // callback to LoadingContext
    auto notifyDataReadyTask = [ctxs, imageObj, src] {
        for (auto&& it : ctxs) {
            auto ctx = it.Upgrade();
            if (!ctx) {
                continue;
            }
            ctx->DataReadyCallback(imageObj);
        }
    };
    if (sync) {
        notifyDataReadyTask();
    } else {
        ImageProvider::WrapTaskAndPostToUI(std::move(notifyDataReadyTask));
    }
}

bool ImageProvider::RegisterTask(const std::string& key, const WeakPtr<ImageLoadingContext>& ctx)
{
    std::scoped_lock<std::mutex> lock(taskMtx_);
    // key exists -> task is running
    auto it = tasks_.find(key);
    if (it != tasks_.end()) {
        it->second.ctxs_.insert(ctx);
        LOGD("task already exist %{public}s, callbacks size = %u", key.c_str(),
            static_cast<uint32_t>(it->second.ctxs_.size()));
        return false;
    }
    tasks_[key].ctxs_.insert(ctx);
    LOGD("task is new %{public}s", key.c_str());
    return true;
}

std::set<WeakPtr<ImageLoadingContext>> ImageProvider::EndTask(const std::string& key)
{
    std::scoped_lock<std::mutex> lock(taskMtx_);
    auto it = tasks_.find(key);
    if (it == tasks_.end()) {
        LOGW("task not found in map %{private}s", key.c_str());
        return std::set<WeakPtr<ImageLoadingContext>>();
    }
    auto ctxs = it->second.ctxs_;
    if (ctxs.empty()) {
        LOGW("registered task has empty context %{public}s", key.c_str());
    }
    tasks_.erase(it);
    LOGD("endTask %s, ctx size = %u", key.c_str(), static_cast<uint32_t>(ctxs.size()));
    return ctxs;
}

void ImageProvider::CancelTask(const std::string& key, const WeakPtr<ImageLoadingContext>& ctx)
{
    std::scoped_lock<std::mutex> lock(taskMtx_);
    auto it = tasks_.find(key);
    CHECK_NULL_VOID(it != tasks_.end());
    CHECK_NULL_VOID(it->second.ctxs_.find(ctx) != it->second.ctxs_.end());
    // only one LoadingContext waiting for this task, can just cancel
    if (it->second.ctxs_.size() == 1) {
        bool res = it->second.bgTask_.Cancel();
        LOGD("cancel bgTask %s, result: %d", key.c_str(), res);
        tasks_.erase(it);
    } else {
        // other LoadingContext still waiting for this task, remove ctx from set
        it->second.ctxs_.erase(ctx);
    }
}

void ImageProvider::CreateImageObject(const ImageSourceInfo& src, const WeakPtr<ImageLoadingContext>& ctx, bool sync)
{
    if (!RegisterTask(src.GetKey(), ctx)) {
        // task is already running, only register callbacks
        return;
    }
    if (sync) {
        CreateImageObjHelper(src, true);
    } else {
        std::scoped_lock<std::mutex> lock(taskMtx_);
        // wrap with [CancelableCallback] and record in [tasks_] map
        CancelableCallback<void()> task;
        task.Reset([src] { ImageProvider::CreateImageObjHelper(src); });
        tasks_[src.GetKey()].bgTask_ = task;
        WrapTaskAndPostToBackground(task);
    }
}

RefPtr<ImageObject> ImageProvider::BuildImageObject(const ImageSourceInfo& src,
    const RefPtr<ImageEncodedInfo>& encodedInfo, const RefPtr<ImageData>& data, ImageObjectType imageObjectType)
{
    switch (imageObjectType) {
        case ImageObjectType::STATIC_IMAGE_OBJECT:
            return StaticImageObject::Create(src, encodedInfo, data);
        // pixelMap always synchronous
        case ImageObjectType::PIXEL_MAP_IMAGE_OBJECT:
            return PixelMapImageObject::Create(src, encodedInfo, data);
        case ImageObjectType::SVG_IMAGE_OBJECT: {
            // SVG object needs to make SVG dom during creation
            return SvgImageObject::Create(src, encodedInfo, data);
        }
        case ImageObjectType::UNKNOWN:
            LOGE("Unknown ImageObject type, src: %{public}s", src.ToString().c_str());
            [[fallthrough]];
        default:
            return nullptr;
    }
}

std::string ImageProvider::GenerateImageKey(const ImageSourceInfo& src, const NG::SizeF& targetSize)
{
    return src.GetKey() + std::to_string(static_cast<int32_t>(targetSize.Width())) +
           std::to_string(static_cast<int32_t>(targetSize.Height()));
}
} // namespace OHOS::Ace::NG
