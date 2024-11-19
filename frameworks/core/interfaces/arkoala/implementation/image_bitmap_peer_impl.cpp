    
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
#include "core/interfaces/arkoala/implementation/image_bitmap_peer_impl.h"
#include "core/interfaces/arkoala/utility/reverse_converter.h"

using namespace OHOS::Ace;
using namespace OHOS::Ace::NG::Converter;

ImageBitmapPeer::ImageBitmapPeer()
    : width(0), 
      height(0),
      loadingCtx_(nullptr),
      canvasImage_(nullptr),
      imageObj_(nullptr),
      pixelMap_(nullptr),
      svgDom_(nullptr),
      imageFit_(ImageFit::NONE),
      bindingSize_(0)
{
}

void ImageBitmapPeer::Close()
{
    for (const auto& closeCallback : closeCallbacks_) {
        if (!closeCallback) {
            continue;
        }
        closeCallback();
    }
    closeCallbacks_.clear();
    width = 0;
    height = 0;

    loadingCtx_ = nullptr;
    canvasImage_ = nullptr;
    imageObj_ = nullptr;
    pixelMap_ = nullptr;
    svgDom_ = nullptr;
}

Ark_Int32 ImageBitmapPeer::GetHeight()
{
    return NG::Converter::ArkValue<Ark_Int32>(static_cast<int32_t>(height));
}

Ark_Int32 ImageBitmapPeer::GetWidth()
{
    return NG::Converter::ArkValue<Ark_Int32>(static_cast<int32_t>(width));
}

void ImageBitmapPeer::SetCloseCallback(std::function<void()>&& callback)
{
    closeCallbacks_.emplace_back(std::move(callback));
}

void ImageBitmapPeer::LoadImage(const std::string& src)
{
    src_ = src;
    auto sourceInfo = ImageSourceInfo(src);
    sourceInfo_ = sourceInfo;
    LoadImage(sourceInfo);
}

void ImageBitmapPeer::LoadImage(const ImageSourceInfo& sourceInfo)
{
    auto dataReadyCallback = [loader = this](const ImageSourceInfo& sourceInfo) {
        CHECK_NULL_VOID(loader);
        loader->OnImageDataReady();
    };
    auto loadSuccessCallback = [loader = this](const ImageSourceInfo& sourceInfo) {
        CHECK_NULL_VOID(loader);
        loader->OnImageLoadSuccess();
    };
    auto loadFailCallback = [loader = this](const ImageSourceInfo& sourceInfo, const std::string& errorMsg) {
        CHECK_NULL_VOID(loader);
        loader->OnImageLoadFail(errorMsg);
    };
    NG::LoadNotifier loadNotifier(dataReadyCallback, loadSuccessCallback, loadFailCallback);
    loadingCtx_ = AceType::MakeRefPtr<NG::ImageLoadingContext>(sourceInfo, std::move(loadNotifier), true);
    loadingCtx_->LoadImageData();
}

void ImageBitmapPeer::OnImageDataReady()
{
    CHECK_NULL_VOID(loadingCtx_);
    width = loadingCtx_->GetImageSize().Width();
    height = loadingCtx_->GetImageSize().Height();
    loadingCtx_->MakeCanvasImageIfNeed(loadingCtx_->GetImageSize(), true, ImageFit::NONE);
}

void ImageBitmapPeer::OnImageLoadSuccess()
{
    CHECK_NULL_VOID(loadingCtx_);
    canvasImage_ = loadingCtx_->MoveCanvasImage();
    CHECK_NULL_VOID(canvasImage_);
    imageObj_ = loadingCtx_->MoveImageObject();
    CHECK_NULL_VOID(imageObj_);
    pixelMap_ = canvasImage_->GetPixelMap();
    svgDom_ = imageObj_->GetSVGDom();
    imageFit_ = loadingCtx_->GetImageFit();
    imageSize_ = loadingCtx_->GetImageSize();
    bindingSize_ = pixelMap_ ? static_cast<size_t>(pixelMap_->GetByteCount()) : 0;
}

void ImageBitmapPeer::OnImageLoadFail(const std::string& errorMsg)
{
    width = 0;
    height = 0;
    pixelMap_ = nullptr;
    svgDom_ = nullptr;
}