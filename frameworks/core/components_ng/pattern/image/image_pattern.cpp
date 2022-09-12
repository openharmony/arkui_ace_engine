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

#include "core/components_ng/pattern/image/image_pattern.h"

#include "base/utils/utils.h"
#include "core/components_ng/pattern/image/image_paint_method.h"
#include "core/components_ng/render/image_painter.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

namespace OHOS::Ace::NG {

ImagePattern::ImagePattern(const ImageSourceInfo& imageSourceInfo)
{
    LoadNotifier loadNotifier(CreateDataReadyCallback(), CreateLoadSuccessCallback(), CreateLoadFailCallback());
    loadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(imageSourceInfo, std::move(loadNotifier));
    loadingCtx_->LoadImageData();
}

DataReadyNotifyTask ImagePattern::CreateDataReadyCallback()
{
    auto task = [weak = WeakClaim(this)](const ImageSourceInfo& sourceInfo) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto imageLayoutProperty = pattern->GetLayoutProperty<ImageLayoutProperty>();
        CHECK_NULL_VOID(imageLayoutProperty);
        auto currentSourceInfo = imageLayoutProperty->GetImageSourceInfo().value_or(ImageSourceInfo(""));
        if (currentSourceInfo != sourceInfo) {
            LOGW("sourceInfo does not match, ignore current callback. current: %{public}s vs callback's: %{public}s",
                currentSourceInfo.ToString().c_str(), sourceInfo.ToString().c_str());
            return;
        }
        pattern->OnImageDataReady();
    };
    return task;
}

LoadSuccessNotifyTask ImagePattern::CreateLoadSuccessCallback()
{
    auto task = [weak = WeakClaim(this)](const ImageSourceInfo& sourceInfo) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto imageLayoutProperty = pattern->GetLayoutProperty<ImageLayoutProperty>();
        CHECK_NULL_VOID(imageLayoutProperty);
        auto currentSourceInfo = imageLayoutProperty->GetImageSourceInfo().value_or(ImageSourceInfo(""));
        if (currentSourceInfo != sourceInfo) {
            LOGW("sourceInfo does not match, ignore current callback. current: %{public}s vs callback's: %{public}s",
                currentSourceInfo.ToString().c_str(), sourceInfo.ToString().c_str());
            return;
        }
        pattern->OnImageLoadSuccess();
    };
    return task;
}

LoadFailNotifyTask ImagePattern::CreateLoadFailCallback()
{
    auto task = [weak = WeakClaim(this)](const ImageSourceInfo& sourceInfo) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto imageLayoutProperty = pattern->GetLayoutProperty<ImageLayoutProperty>();
        CHECK_NULL_VOID(imageLayoutProperty);
        auto currentSourceInfo = imageLayoutProperty->GetImageSourceInfo().value_or(ImageSourceInfo(""));
        if (currentSourceInfo != sourceInfo) {
            LOGW("sourceInfo does not match, ignore current callback. current: %{public}s vs callback's: %{public}s",
                currentSourceInfo.ToString().c_str(), sourceInfo.ToString().c_str());
            return;
        }
        pattern->OnImageLoadFail();
    };
    return task;
}

void ImagePattern::OnImageLoadSuccess()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    const auto& geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto imageEventHub = GetEventHub<ImageEventHub>();
    CHECK_NULL_VOID(imageEventHub);
    LoadImageSuccessEvent loadImageSuccessEvent_(
        loadingCtx_->GetImageSize().Width(), loadingCtx_->GetImageSize().Height(),
        geometryNode->GetFrameSize().Width(), geometryNode->GetFrameSize().Height(), 1);
    imageEventHub->FireCompleteEvent(std::move(loadImageSuccessEvent_));
    // update src data
    lastCanvasImage_ = loadingCtx_->GetCanvasImage();
    lastSrcRect_ = loadingCtx_->GetSrcRect();
    lastDstRect_ = loadingCtx_->GetDstRect();
    // clear alt data
    altLoadingCtx_ = nullptr;
    lastAltCanvasImage_ = nullptr;
    lastAltDstRect_.reset();
    lastAltSrcRect_.reset();
    // TODO: only do paint task when the pattern is active
    // figure out why here is always inactive
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void ImagePattern::CacheImageObject()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    // TODO: do cache
}

void ImagePattern::OnImageDataReady()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    const auto& geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto imageEventHub = GetEventHub<ImageEventHub>();
    CHECK_NULL_VOID(imageEventHub);
    LoadImageSuccessEvent loadImageSuccessEvent_(
        loadingCtx_->GetImageSize().Width(), loadingCtx_->GetImageSize().Height(),
        geometryNode->GetFrameSize().Width(), geometryNode->GetFrameSize().Height(), 0);
    imageEventHub->FireCompleteEvent(std::move(loadImageSuccessEvent_));

    if (!geometryNode->GetContent() || (geometryNode->GetContent() && altLoadingCtx_)) {
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        return;
    }
    host->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
}

void ImagePattern::OnImageLoadFail()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    const auto& geometryNode = host->GetGeometryNode();
    auto imageEventHub = GetEventHub<ImageEventHub>();
    CHECK_NULL_VOID(imageEventHub);
    LoadImageFailEvent loadImageFailEvent_(
        geometryNode->GetFrameSize().Width(), geometryNode->GetFrameSize().Height(), "");
    // TODO: remove errorMsg in fail event
    imageEventHub->FireErrorEvent(std::move(loadImageFailEvent_));
}

RefPtr<NodePaintMethod> ImagePattern::CreateNodePaintMethod()
{
    auto imageRenderProperty = GetPaintProperty<ImageRenderProperty>();
    CHECK_NULL_RETURN(imageRenderProperty, nullptr);
    ImagePaintConfig imagePaintConfig(lastSrcRect_, lastDstRect_);
    imagePaintConfig.renderMode_ = imageRenderProperty->GetImageRenderMode().value_or(ImageRenderMode::ORIGINAL);
    imagePaintConfig.imageInterpolation_ =
        imageRenderProperty->GetImageInterpolation().value_or(ImageInterpolation::NONE);
    imagePaintConfig.imageRepeat_ = imageRenderProperty->GetImageRepeat().value_or(ImageRepeat::NOREPEAT);
    if (lastCanvasImage_) {
        return MakeRefPtr<ImagePaintMethod>(lastCanvasImage_, imagePaintConfig);
    }
    if (lastAltCanvasImage_ && lastAltDstRect_ && lastAltSrcRect_) {
        imagePaintConfig.srcRect_ = *lastAltSrcRect_;
        imagePaintConfig.dstRect_ = *lastAltDstRect_;
        return MakeRefPtr<ImagePaintMethod>(lastAltCanvasImage_, imagePaintConfig);
    }
    return nullptr;
}

bool ImagePattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, bool skipMeasure, bool skipLayout)
{
    if (skipMeasure || dirty->SkipMeasureContent()) {
        return false;
    }
    return lastCanvasImage_;
}

void ImagePattern::OnModifyDone()
{
    auto imageLayoutProperty = GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(imageLayoutProperty);
    if (loadingCtx_->GetSourceInfo() != imageLayoutProperty->GetImageSourceInfo().value_or(ImageSourceInfo(""))) {
        LoadNotifier loadNotifier(CreateDataReadyCallback(), CreateLoadSuccessCallback(), CreateLoadFailCallback());
        loadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(
            imageLayoutProperty->GetImageSourceInfo().value_or(ImageSourceInfo("")), std::move(loadNotifier));
        loadingCtx_->LoadImageData();
    }
    if (loadingCtx_->NeedAlt()) {
        auto altImageSourceInfo = imageLayoutProperty->GetAlt().value_or(ImageSourceInfo(""));
        LoadNotifier altLoadNotifier(CreateDataReadyCallbackForAlt(), CreateLoadSuccessCallbackForAlt(), nullptr);
        if (!altLoadingCtx_ || altLoadingCtx_->GetSourceInfo() != altImageSourceInfo) {
            altLoadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(altImageSourceInfo, std::move(altLoadNotifier));
        }
        altLoadingCtx_->LoadImageData();
    }
}

DataReadyNotifyTask ImagePattern::CreateDataReadyCallbackForAlt()
{
    auto task = [weak = WeakClaim(this)](const ImageSourceInfo& sourceInfo) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto imageLayoutProperty = pattern->GetLayoutProperty<ImageLayoutProperty>();
        CHECK_NULL_VOID(imageLayoutProperty);
        auto currentAltSourceInfo = imageLayoutProperty->GetAlt().value_or(ImageSourceInfo(""));
        if (currentAltSourceInfo != sourceInfo) {
            LOGW("alt image sourceInfo does not match, ignore current callback. current: %{public}s vs callback's: "
                 "%{public}s",
                currentAltSourceInfo.ToString().c_str(), sourceInfo.ToString().c_str());
            return;
        }
        auto host = pattern->GetHost();
        CHECK_NULL_VOID(host);
        const auto& geometryNode = host->GetGeometryNode();
        CHECK_NULL_VOID(geometryNode);
        if (!geometryNode->GetContent()) {
            host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
            return;
        }

        // calculate params for [altLoadingCtx] to do [MakeCanvasImage] if component size is already settled
        ImageLoadingContext::MakeCanvasImageIfNeed(pattern->altLoadingCtx_, geometryNode->GetContentSize(), true,
            imageLayoutProperty->GetImageFit().value_or(ImageFit::COVER));
    };
    return task;
}

LoadSuccessNotifyTask ImagePattern::CreateLoadSuccessCallbackForAlt()
{
    auto task = [weak = WeakClaim(this)](const ImageSourceInfo& sourceInfo) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto imageLayoutProperty = pattern->GetLayoutProperty<ImageLayoutProperty>();
        auto currentAltSourceInfo = imageLayoutProperty->GetAlt().value_or(ImageSourceInfo(""));
        if (currentAltSourceInfo != sourceInfo) {
            LOGW("alt image sourceInfo does not match, ignore current callback. current: %{public}s vs callback's: "
                 "%{public}s",
                currentAltSourceInfo.ToString().c_str(), sourceInfo.ToString().c_str());
            return;
        }
        auto host = pattern->GetHost();
        CHECK_NULL_VOID(host);
        host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
        pattern->lastAltCanvasImage_ = pattern->altLoadingCtx_->GetCanvasImage();
        pattern->lastAltSrcRect_ = std::make_unique<RectF>(pattern->altLoadingCtx_->GetSrcRect());
        pattern->lastAltDstRect_ = std::make_unique<RectF>(pattern->altLoadingCtx_->GetDstRect());
    };
    return task;
}

} // namespace OHOS::Ace::NG
