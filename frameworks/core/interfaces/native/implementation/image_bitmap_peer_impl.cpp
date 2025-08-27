
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
#include "core/common/container.h"

using namespace OHOS::Ace;

ImageBitmapPeer::ImageBitmapPeer()
{
    image_ = nullptr;
    imageObj_ = nullptr;
    loadingCtx_ = nullptr;
    pixelMap_ = nullptr;
    imageData_ = nullptr;
    svgDom_ = nullptr;
}
void ImageBitmapPeer::SetOptions(
    const std::string& textString, const OHOS::Ace::RefPtr<OHOS::Ace::PixelMap>& pixelMap)
{
    ContainerScope scope(Container::CurrentIdSafely());
    SetInstanceId(OHOS::Ace::Container::CurrentId());
    if (!textString.empty()) {
        auto context = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(context);
        if (context->IsFormRender() && NotFormSupport(textString)) {
            LOGE("ARKOALA ImageBitmapPeer::Constructor Not supported src : %{public}s when form render",
                textString.c_str());
            return;
        }
        LoadImage(textString);
    } else {
#ifdef PIXEL_MAP_SUPPORTED
        CHECK_NULL_VOID(pixelMap);
        LoadImage(pixelMap);
#endif
    }
}
void ImageBitmapPeer::OnClose()
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

    image_ = nullptr;
    imageObj_ = nullptr;
    loadingCtx_ = nullptr;
    pixelMap_ = nullptr;
    imageData_ = nullptr;
    svgDom_ = nullptr;
}
double ImageBitmapPeer::OnGetHeight()
{
    double fHeight = 0.0;
    double density = GetDensity();
    fHeight = height;
    if (density == 0) {
        return fHeight;
    }
    fHeight /= density;
    return fHeight;
}
double ImageBitmapPeer::OnGetWidth()
{
    double fWidth = 0.0;
    double density = GetDensity();
    fWidth = width;
    if (density == 0) {
        return fWidth;
    }
    fWidth /= density;
    return fWidth;
}
// service
double ImageBitmapPeer::GetWidth()
{
    return width;
}
void ImageBitmapPeer::SetWidth(double value)
{
    width = value;
}
double ImageBitmapPeer::GetHeight()
{
    return height;
}
void ImageBitmapPeer::SetHeight(double value)
{
    height = value;
}
std::string ImageBitmapPeer::GetSrc()
{
    return src_;
}
void ImageBitmapPeer::SetCloseCallback(std::function<void()>&& callback)
{
    closeCallbacks_.emplace_back(std::move(callback));
}
// pivate
void ImageBitmapPeer::LoadImage(const std::string& src)
{
    src_ = src;
    auto sourceInfo = ImageSourceInfo(src);
    sourceInfo_ = sourceInfo;
    LoadImage(sourceInfo);
}
void ImageBitmapPeer::LoadImage(const RefPtr<PixelMap>& pixmap)
{
    auto sourceInfo = ImageSourceInfo(pixmap);
    sourceInfo_ = sourceInfo;
    LoadImage(sourceInfo);
}
void ImageBitmapPeer::LoadImage(const OHOS::Ace::ImageSourceInfo& sourceInfo)
{
    // auto dataReadyCallback = [weak = WeakClaim(this)](const ImageSourceInfo& sourceInfo) {
    //     auto jsRenderImage = weak.Upgrade();
    //     CHECK_NULL_VOID(jsRenderImage);
    //     jsRenderImage->OnImageDataReady();
    // };
    // auto loadSuccessCallback = [weak = WeakClaim(this)](const ImageSourceInfo& sourceInfo) {
    //     auto jsRenderImage = weak.Upgrade();
    //     CHECK_NULL_VOID(jsRenderImage);
    //     jsRenderImage->OnImageLoadSuccess();
    // };
    // auto loadFailCallback = [weak = WeakClaim(this)](const ImageSourceInfo& sourceInfo, const std::string& errorMsg) {
    //     auto jsRenderImage = weak.Upgrade();
    //     CHECK_NULL_VOID(jsRenderImage);
    //     jsRenderImage->OnImageLoadFail(errorMsg);
    // };
    // NG::LoadNotifier loadNotifier(dataReadyCallback, loadSuccessCallback, loadFailCallback);
    // loadingCtx_ = AceType::MakeRefPtr<NG::ImageLoadingContext>(sourceInfo, std::move(loadNotifier), true);
    // loadingCtx_->LoadImageData();
}
void ImageBitmapPeer::OnImageDataReady()
{
    CHECK_NULL_VOID(loadingCtx_);
    width = loadingCtx_->GetImageSize().Width();
    height = loadingCtx_->GetImageSize().Height();
    loadingCtx_->MakeCanvasImageIfNeed(loadingCtx_->GetImageSize(), true, ImageFit::NONE);
}
void ImageBitmapPeer::OnImageLoadFail(const std::string& errorMsg)
{
    width = 0;
    height = 0;
    pixelMap_ = nullptr;
    svgDom_ = nullptr;
}
void ImageBitmapPeer::OnImageLoadSuccess()
{
    CHECK_NULL_VOID(loadingCtx_);
    image_ = loadingCtx_->MoveCanvasImage();
    CHECK_NULL_VOID(image_);
    imageObj_ = loadingCtx_->MoveImageObject();
    CHECK_NULL_VOID(imageObj_);
    pixelMap_ = image_->GetPixelMap();
    svgDom_ = imageObj_->GetSVGDom();
    imageFit_ = loadingCtx_->GetImageFit();
    imageSize_ = loadingCtx_->GetImageSize();
    bindingSize_ = pixelMap_ ? static_cast<size_t>(pixelMap_->GetByteCount()) : 0;
}
bool ImageBitmapPeer::NotFormSupport(const std::string& textString)
{
    SrcType srcType = ImageSourceInfo::ResolveURIType(textString);
    return (srcType == SrcType::NETWORK || srcType == SrcType::FILE || srcType == SrcType::DATA_ABILITY);
}