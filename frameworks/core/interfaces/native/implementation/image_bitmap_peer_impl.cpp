
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
#include "core/interfaces/native/implementation/image_bitmap_peer_impl.h"

using namespace OHOS::Ace;

ImageBitmapPeer::ImageBitmapPeer()
    : width(0),
      height(0),
      loadingCtx_(nullptr)
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
}

double ImageBitmapPeer::GetHeight()
{
    return height;
}

double ImageBitmapPeer::GetWidth()
{
    return width;
}

void ImageBitmapPeer::SetCloseCallback(std::function<void()>&& callback)
{
    closeCallbacks_.emplace_back(std::move(callback));
}

void ImageBitmapPeer::LoadImage(const std::string& src)
{
    auto sourceInfo = ImageSourceInfo(src);
    LoadImage(sourceInfo);
}

void ImageBitmapPeer::LoadImage(const ImageSourceInfo& sourceInfo)
{
    auto dataReadyCallback = [loader = this](const ImageSourceInfo& sourceInfo) {
        CHECK_NULL_VOID(loader);
        loader->OnImageDataReady();
    };
    auto loadSuccessCallback = [loader = this](const ImageSourceInfo& sourceInfo) {
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
}

void ImageBitmapPeer::OnImageLoadFail(const std::string& errorMsg)
{
    width = 0;
    height = 0;
}
