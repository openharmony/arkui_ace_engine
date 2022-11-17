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

#include "core/components_ng/image_provider/image_loading_context.h"

namespace OHOS::Ace::NG {
ImageLoadingContext::ImageLoadingContext(const ImageSourceInfo& sourceInfo, const LoadNotifier& loadNotifier)
    : sourceInfo_(sourceInfo), loadNotifier_(loadNotifier),
      loadCallbacks_(GenerateDataReadyCallback(), GenerateLoadSuccessCallback(), GenerateLoadFailCallback())
{}

SizeF ImageLoadingContext::CalculateResizeTarget(const SizeF& srcSize, const SizeF& dstSize, const SizeF& rawImageSize)
{
    SizeF resizeTarget = rawImageSize;
    return resizeTarget;
}

void ImageLoadingContext::RegisterStateChangeCallbacks() {}

EnterStateTask ImageLoadingContext::CreateOnUnloadedTask()
{
    return nullptr;
}

void ImageLoadingContext::RestoreLoadingParams() {}

EnterStateTask ImageLoadingContext::CreateOnDataLoadingTask()
{
    return nullptr;
}

EnterStateTask ImageLoadingContext::CreateOnDataReadyTask()
{
    return nullptr;
}

EnterStateTask ImageLoadingContext::CreateOnMakeCanvasImageTask()
{
    return nullptr;
}

EnterStateTask ImageLoadingContext::CreateOnLoadSuccessTask()
{
    return nullptr;
}

EnterStateTask ImageLoadingContext::CreateOnLoadFailTask()
{
    return nullptr;
}

DataReadyCallback ImageLoadingContext::GenerateDataReadyCallback()
{
    return nullptr;
}

void ImageLoadingContext::OnDataReady(const ImageSourceInfo& sourceInfo, const RefPtr<ImageObject> imageObj) {}

LoadSuccessCallback ImageLoadingContext::GenerateLoadSuccessCallback()
{
    return nullptr;
}

void ImageLoadingContext::OnLoadSuccess(const ImageSourceInfo& sourceInfo) {}

LoadFailCallback ImageLoadingContext::GenerateLoadFailCallback()
{
    return nullptr;
}

void ImageLoadingContext::OnLoadFail(
    const ImageSourceInfo& sourceInfo, const std::string& errorMsg, const ImageLoadingCommand& command)
{}

const RectF& ImageLoadingContext::GetDstRect() const
{
    return dstRect_;
}

const RectF& ImageLoadingContext::GetSrcRect() const
{
    return srcRect_;
}

RefPtr<CanvasImage> ImageLoadingContext::GetCanvasImage() const
{
    return nullptr;
}

void ImageLoadingContext::LoadImageData() {}

void ImageLoadingContext::MakeCanvasImageIfNeed(const RefPtr<ImageLoadingContext>& loadingCtx, const SizeF& dstSize,
    bool incomingNeedResize, ImageFit incommingImageFit, const std::optional<SizeF>& sourceSize)
{}

void ImageLoadingContext::MakeCanvasImage(
    const SizeF& dstSize, bool needResize, ImageFit imageFit, const std::optional<SizeF>& sourceSize)
{}

SizeF ImageLoadingContext::GetImageSize() const
{
    return { -1.0f, -1.0f };
}

ImageFit ImageLoadingContext::GetImageFit() const
{
    return imageFit_;
}

void ImageLoadingContext::SetImageFit(ImageFit imageFit)
{
    imageFit_ = imageFit;
}

const ImageSourceInfo& ImageLoadingContext::GetSourceInfo() const
{
    return sourceInfo_;
}

void ImageLoadingContext::SetNeedResize(bool needResize)
{
    needResize_ = needResize;
}

const SizeF& ImageLoadingContext::GetDstSize() const
{
    return dstSize_;
}

bool ImageLoadingContext::GetNeedResize() const
{
    return needResize_;
}

void ImageLoadingContext::SetSourceSize(const std::optional<SizeF>& sourceSize) {}

std::optional<SizeF> ImageLoadingContext::GetSourceSize() const
{
    return std::optional<SizeF>();
}

bool ImageLoadingContext::NeedAlt() const
{
    return needAlt_;
}

const std::optional<Color>& ImageLoadingContext::GetSvgFillColor() const
{
    return svgFillColorOpt_;
}

void ImageLoadingContext::SetSvgFillColor(const std::optional<Color>& svgFillColorOpt) {}
void ImageLoadingContext::ResetLoading() {}
void ImageLoadingContext::ResumeLoading() {}
} // namespace OHOS::Ace::NG