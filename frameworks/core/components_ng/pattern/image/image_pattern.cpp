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

#include <array>

#include "base/utils/utils.h"
#include "core/components/theme/icon_theme.h"
#include "core/components_ng/pattern/image/image_paint_method.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

namespace OHOS::Ace::NG {

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
    LoadImageSuccessEvent loadImageSuccessEvent_(loadingCtx_->GetImageSize().Width(),
        loadingCtx_->GetImageSize().Height(), geometryNode->GetFrameSize().Width(),
        geometryNode->GetFrameSize().Height(), 1);
    imageEventHub->FireCompleteEvent(loadImageSuccessEvent_);
    // update src data
    image_ = loadingCtx_->MoveCanvasImage();
    srcRect_ = loadingCtx_->GetSrcRect();
    dstRect_ = loadingCtx_->GetDstRect();
    SetImagePaintConfig(image_, srcRect_, dstRect_, loadingCtx_->GetSourceInfo().IsSvg());
    // clear alt data
    altLoadingCtx_ = nullptr;
    altImage_ = nullptr;
    altDstRect_.reset();
    altSrcRect_.reset();
    // TODO: only do paint task when the pattern is active
    // figure out why here is always inactive
    host->MarkNeedRenderOnly();
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
    LoadImageSuccessEvent loadImageSuccessEvent_(loadingCtx_->GetImageSize().Width(),
        loadingCtx_->GetImageSize().Height(), geometryNode->GetFrameSize().Width(),
        geometryNode->GetFrameSize().Height(), 0);
    imageEventHub->FireCompleteEvent(loadImageSuccessEvent_);
    if (!host->IsActive()) {
        return;
    }
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

void ImagePattern::SetImagePaintConfig(
    const RefPtr<CanvasImage>& canvasImage, const RectF& srcRect, const RectF& dstRect, bool isSvg)
{
    auto renderProps = GetPaintProperty<ImageRenderProperty>();
    auto layoutProps = GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(renderProps && layoutProps);

    ImagePaintConfig config {
        .srcRect_ = srcRect,
        .dstRect_ = dstRect,
    };
    config.imageFit_ = layoutProps->GetImageFit().value_or(ImageFit::COVER);
    if (renderProps->GetNeedBorderRadiusValue(false)) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto borderRadius = host->GetRenderContext()->GetBorderRadius();
        std::array<PointF, 4> radiusXY = { PointF(borderRadius->radiusTopLeft->ConvertToPx(),
                                               borderRadius->radiusTopLeft->ConvertToPx()),
            PointF(borderRadius->radiusTopRight->ConvertToPx(), borderRadius->radiusTopRight->ConvertToPx()),
            PointF(borderRadius->radiusBottomLeft->ConvertToPx(), borderRadius->radiusBottomLeft->ConvertToPx()),
            PointF(borderRadius->radiusBottomRight->ConvertToPx(), borderRadius->radiusBottomRight->ConvertToPx()) };
        config.borderRadiusXY_ = std::make_shared<std::array<PointF, 4>>(std::move(radiusXY));
    }
    config.isSvg_ = isSvg;

    canvasImage->SetPaintConfig(config);
}

RefPtr<NodePaintMethod> ImagePattern::CreateNodePaintMethod()
{
    if (image_) {
        return MakeRefPtr<ImagePaintMethod>(image_);
    }
    if (altImage_ && altDstRect_ && altSrcRect_) {
        return MakeRefPtr<ImagePaintMethod>(altImage_);
    }
    return nullptr;
}

bool ImagePattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (config.skipMeasure || dirty->SkipMeasureContent()) {
        return false;
    }
    return image_;
}

void ImagePattern::LoadImageDataIfNeed()
{
    auto imageLayoutProperty = GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(imageLayoutProperty);
    auto imageRenderProperty = GetPaintProperty<ImageRenderProperty>();
    CHECK_NULL_VOID(imageRenderProperty);
    auto currentSourceInfo = imageLayoutProperty->GetImageSourceInfo().value_or(ImageSourceInfo(""));
    UpdateInternalResource(currentSourceInfo);
    std::optional<Color> svgFillColorOpt = std::nullopt;
    if (currentSourceInfo.IsSvg()) {
        svgFillColorOpt = currentSourceInfo.GetFillColor();
    }

    if (!loadingCtx_ || loadingCtx_->GetSourceInfo() != currentSourceInfo ||
        (currentSourceInfo.IsSvg() && loadingCtx_->GetSvgFillColor() != svgFillColorOpt)) {
        LoadNotifier loadNotifier(CreateDataReadyCallback(), CreateLoadSuccessCallback(), CreateLoadFailCallback());

        bool syncLoad = imageLayoutProperty->GetSyncModeValue(false);
        loadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(currentSourceInfo, std::move(loadNotifier), syncLoad);

        loadingCtx_->SetSvgFillColor(svgFillColorOpt);
        loadingCtx_->LoadImageData();
    }
    if (loadingCtx_->NeedAlt() && imageLayoutProperty->GetAlt()) {
        auto altImageSourceInfo = imageLayoutProperty->GetAlt().value_or(ImageSourceInfo(""));
        std::optional<Color> altSvgFillColorOpt = std::nullopt;
        if (altImageSourceInfo.IsSvg()) {
            altSvgFillColorOpt = imageRenderProperty->GetSvgFillColor() ? imageRenderProperty->GetSvgFillColor()
                                                                        : altImageSourceInfo.GetFillColor();
        }
        LoadNotifier altLoadNotifier(CreateDataReadyCallbackForAlt(), CreateLoadSuccessCallbackForAlt(), nullptr);
        if (!altLoadingCtx_ || altLoadingCtx_->GetSourceInfo() != altImageSourceInfo ||
            (altLoadingCtx_ && altImageSourceInfo.IsSvg() && altSvgFillColorOpt.has_value() &&
                altLoadingCtx_->GetSvgFillColor() != altSvgFillColorOpt)) {
            altLoadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(altImageSourceInfo, std::move(altLoadNotifier));
            altLoadingCtx_->SetSvgFillColor(altSvgFillColorOpt);
            altLoadingCtx_->LoadImageData();
        }
    }
}

void ImagePattern::OnModifyDone()
{
    LoadImageDataIfNeed();
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
        if (!host->IsActive()) {
            return;
        }
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
        CHECK_NULL_VOID(pattern->altLoadingCtx_);
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
        pattern->altImage_ = pattern->altLoadingCtx_->MoveCanvasImage();
        pattern->altSrcRect_ = std::make_unique<RectF>(pattern->altLoadingCtx_->GetSrcRect());
        pattern->altDstRect_ = std::make_unique<RectF>(pattern->altLoadingCtx_->GetDstRect());
        pattern->SetImagePaintConfig(pattern->altImage_, *pattern->altSrcRect_, *pattern->altDstRect_,
            pattern->altLoadingCtx_->GetSourceInfo().IsSvg());
    };
    return task;
}

void ImagePattern::UpdateInternalResource(ImageSourceInfo& sourceInfo)
{
    if (!sourceInfo.IsInternalResource()) {
        return;
    }
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto iconTheme = pipeline->GetTheme<IconTheme>();
    CHECK_NULL_VOID(iconTheme);
    auto iconPath = iconTheme->GetIconPath(sourceInfo.GetResourceId());
    if (!iconPath.empty()) {
        sourceInfo.SetSrc(iconPath);
        auto imageLayoutProperty = GetLayoutProperty<ImageLayoutProperty>();
        CHECK_NULL_VOID(imageLayoutProperty);
        imageLayoutProperty->UpdateImageSourceInfo(sourceInfo);
    }
}

void ImagePattern::OnNotifyMemoryLevel(int32_t level)
{
    LOGI("Receive Memory level notification, level: %{public}d", level);
    // level = 0: MEMORY_LEVEL_MODERATE;
    // level = 1: MEMORY_LEVEL_LOW;
    // level = 2: MEMORY_LEVEL_CRITICAL;
    // TODO: do different data cleaning operation according to level
    // when image component is [onShow], do not clean image data
    // TODO: use [isActive_] to determine image data management
    if (isShow_) {
        return;
    }
    // TODO: clean cache data when cache mechanism is ready
    // Step1: drive stateMachine to reset loading procedure
    if (altLoadingCtx_) {
        altLoadingCtx_->ResetLoading();
    }
    if (loadingCtx_) {
        loadingCtx_->ResetLoading();
    }

    // Step2: clean data and reset params
    // clear src data
    image_ = nullptr;
    srcRect_ = RectF();
    dstRect_ = RectF();
    // clear alt data
    altLoadingCtx_ = nullptr;
    altImage_ = nullptr;
    altDstRect_.reset();
    altSrcRect_.reset();

    // Step3: clean rs node to release the sk_sp<SkImage> held by it
    // TODO: release PixelMap resource when use PixelMap resource to draw image
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    auto rsRenderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(rsRenderContext);
    rsRenderContext->ClearDrawCommands();
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->FlushMessages();
}

void ImagePattern::OnWindowHide()
{
    isShow_ = false;
}

void ImagePattern::OnWindowShow()
{
    isShow_ = true;
    LoadImageDataIfNeed();
}

void ImagePattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetRenderContext()->SetClipToBounds(true);
}

} // namespace OHOS::Ace::NG
