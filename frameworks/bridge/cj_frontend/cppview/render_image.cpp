/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include <string>

#include "bridge/cj_frontend/cppview/render_image.h"
#include "core/image/image_source_info.h"
#include "core/pipeline/pipeline_base.h"

using namespace OHOS;

namespace OHOS::Ace::Framework {
CJRenderImage::CJRenderImage() : FFIData() {}
CJRenderImage::CJRenderImage(const int32_t unit) : FFIData()
{
    SetUnit(static_cast<CanvasUnit>(unit));
}

void CJRenderImage::InitCJRenderImage(const std::string& src)
{
    this->LoadImage(src);
}

void CJRenderImage::InitCJRenderImage(const RefPtr<OHOS::Ace::PixelMap>& pixmap)
{
    this->LoadImage(pixmap);
}

void CJRenderImage::LoadImage(const ImageSourceInfo& sourceInfo)
{
    auto dataReadyCallback = [this](const ImageSourceInfo& sourceInfo) { this->OnImageDataReady(); };
    auto loadSuccessCallback = [this](const ImageSourceInfo& sourceInfo) { this->OnImageLoadSuccess(); };
    auto loadFailCallback = [this](const ImageSourceInfo& sourceInfo, const std::string& errorMsg,
                                ImageErrorInfo /* errorInfo */) { this->OnImageLoadFail(errorMsg); };
    NG::LoadNotifier loadNotifier(dataReadyCallback, loadSuccessCallback, loadFailCallback);
    loadingCtx_ = AceType::MakeRefPtr<NG::ImageLoadingContext>(sourceInfo, std::move(loadNotifier), true);
    loadingCtx_->LoadImageData();
}

void CJRenderImage::LoadImage(const std::string& src)
{
    src_ = src;
    auto sourceInfo = ImageSourceInfo(src);
    sourceInfo_ = sourceInfo;
    LoadImage(sourceInfo);
}

void CJRenderImage::LoadImage(const RefPtr<OHOS::Ace::PixelMap>& pixmap)
{
    auto sourceInfo = ImageSourceInfo(pixmap);
    sourceInfo_ = sourceInfo;
    LoadImage(sourceInfo);
}

void CJRenderImage::OnImageDataReady()
{
    CHECK_NULL_VOID(loadingCtx_);
    width_ = loadingCtx_->GetImageSize().Width();
    height_ = loadingCtx_->GetImageSize().Height();
    loadingCtx_->MakeCanvasImageIfNeed(loadingCtx_->GetImageSize(), true, ImageFit::NONE);
}

void CJRenderImage::OnImageLoadSuccess()
{
    CHECK_NULL_VOID(loadingCtx_);
    image_ = loadingCtx_->MoveCanvasImage();
    CHECK_NULL_VOID(image_);
    pixelMap_ = image_->GetPixelMap();
    imageFit_ = loadingCtx_->GetImageFit();
}

void CJRenderImage::OnImageLoadFail(const std::string& errorMsg)
{
    width_ = 0;
    height_ = 0;
    pixelMap_ = nullptr;
}

double CJRenderImage::GetHeight()
{
    double density = !NearZero(GetDensity()) ? GetDensity() : 1.0;
    return height_ / density;
}

double CJRenderImage::GetWidth()
{
    double density = !NearZero(GetDensity()) ? GetDensity() : 1.0;
    return width_ / density;
}

double CJRenderImage::GetDensity()
{
    double density = PipelineBase::GetCurrentDensity();
    return ((GetUnit() == CanvasUnit::DEFAULT) && !NearZero(density)) ? density : 1.0;
}
} // namespace OHOS::Ace::Framework