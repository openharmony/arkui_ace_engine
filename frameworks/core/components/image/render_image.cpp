/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "core/components/image/render_image.h"

#include "base/log/dump_log.h"
#include "core/common/ace_engine_ext.h"
#include "core/components/image/image_event.h"
#include "core/components/text_overlay/text_overlay_component.h"

namespace OHOS::Ace {
namespace {

constexpr double RESIZE_AGAIN_THRESHOLD = 1.2;

} // namespace

RenderImage::~RenderImage()
{
    auto textOverlayManager = GetTextOverlayManager(context_);
    if (textOverlayManager) {
        auto textOverlayBase = textOverlayManager->GetTextOverlayBase();
        if (textOverlayBase) {
            auto targetNode = textOverlayManager->GetTargetNode();
            if (targetNode == this) {
                textOverlayManager->PopTextOverlay();
                textOverlayBase->MarkIsOverlayShowed(false);
                targetNode->MarkNeedRender();
            }
        }
    }
}

void RenderImage::Update(const RefPtr<Component>& component)
{
    const RefPtr<ImageComponent> image = AceType::DynamicCast<ImageComponent>(component);
    if (!image) {
        LOGE("image component is null!");
        return;
    }
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    if (!clipboard_ && context) {
        clipboard_ = ClipboardProxy::GetInstance()->GetClipboard(context->GetTaskExecutor());
    }
    currentSrcRect_ = srcRect_;
    currentDstRect_ = dstRect_;
    currentDstRectList_ = rectList_;
    colorfilter_ = image->GetColorFilterMatrix();
    blurRadius_ = image->GetBlurRadius();
    width_ = image->GetWidth();
    syncMode_ = image->GetSyncMode();
    height_ = image->GetHeight();
    alignment_ = image->GetAlignment();
    imageObjectPosition_ = image->GetImageObjectPosition();
    fitMaxSize_ = image->GetFitMaxSize();
    hasObjectPosition_ = image->GetHasObjectPosition();
    color_ = image->GetColor();
    previousLayoutSize_ = Size();
    SetTextDirection(image->GetTextDirection());
    matchTextDirection_ = image->IsMatchTextDirection();
    SetRadius(image->GetBorder());
    if (context && context->GetIsDeclarative()) {
        loadImgSuccessEvent_ =
            AceAsyncEvent<void(const std::shared_ptr<BaseEventInfo>&)>::Create(image->GetLoadSuccessEvent(), context_);
        loadImgFailEvent_ =
            AceAsyncEvent<void(const std::shared_ptr<BaseEventInfo>&)>::Create(image->GetLoadFailEvent(), context_);
    } else {
        loadSuccessEvent_ = AceAsyncEvent<void(const std::string&)>::Create(image->GetLoadSuccessEvent(), context_);
        loadFailEvent_ = AceAsyncEvent<void(const std::string&)>::Create(image->GetLoadFailEvent(), context_);
    }
    svgAnimatorFinishEvent_ = image->GetSvgAnimatorFinishEvent();
    imageFit_ = image->GetImageFit();
    imageInterpolation_ = image->GetImageInterpolation();
    imageRenderMode_ = image->GetImageRenderMode();
    imageRepeat_ = image->GetImageRepeat();

#ifndef USE_ROSEN_DRAWING
    useSkiaSvg_ = image->GetUseSkiaSvg();
#else
    useSkiaSvg_ = false;
#endif
    autoResize_ = image->GetAutoResize();
    imageAlt_ = image->GetAlt();
    auto inComingSrc = image->GetSrc();
    ImageSourceInfo inComingSource(inComingSrc, image->GetBundleName(), image->GetModuleName(),
        image->GetImageSourceSize().first, image->GetImageSourceSize().second,
        inComingSrc.empty() ? image->GetResourceId() : InternalResource::ResourceId::NO_ID, image->GetPixmap());
    UpdateThemeIcon(inComingSource);
    auto fillColor = image->GetImageFill();
    if (fillColor.has_value()) {
        inComingSource.SetFillColor(fillColor.value());
    }
    border_ = image->GetBorder();

    onDragStart_ = image->GetOnDragStartId();
    onDragEnter_ = image->GetOnDragEnterId();
    onDragMove_ = image->GetOnDragMoveId();
    onDragLeave_ = image->GetOnDragLeaveId();
    onDrop_ = image->GetOnDropId();
    if (onDragStart_) {
        CreateDragDropRecognizer(context_);
    }

    copyOption_ = image->GetCopyOption();

    // this value is used for update frequency with same image source info.
    proceedPreviousLoading_ = sourceInfo_.IsValid() && sourceInfo_ == inComingSource;
    // perform layout only if loading new image
    if (!proceedPreviousLoading_) {
        sourceInfo_ = inComingSource;
        MarkNeedLayout(sourceInfo_.IsSvg());
    }
}

void RenderImage::UpdateThemeIcon(ImageSourceInfo& sourceInfo)
{
    if (sourceInfo.IsInternalResource()) {
        auto iconTheme = GetTheme<IconTheme>();
        if (!iconTheme) {
            LOGW("icon theme is null.");
            return;
        }
        auto iconPath = iconTheme->GetIconPath(sourceInfo.GetResourceId());
        if (!iconPath.empty()) {
            sourceInfo.SetSrc(iconPath);
        }
    }
}

void RenderImage::OnPaintFinish()
{
    UpdateOverlay();
}

void RenderImage::OnTouchTestHit(
    const Offset& coordinateOffset, const TouchRestrict& touchRestrict, TouchTestResult& result)
{
    if (dragDropGesture_) {
        result.emplace_back(dragDropGesture_);
    }

    if (copyOption_ != CopyOptions::None && imageLoadingStatus_ == ImageLoadingStatus::LOAD_SUCCESS &&
        !sourceInfo_.IsSvg()) {
        if (!textOverlayRecognizer_) {
            textOverlayRecognizer_ = AceType::MakeRefPtr<LongPressRecognizer>(context_);
            textOverlayRecognizer_->SetOnLongPress([weak = WeakClaim(this)](const LongPressInfo& info) {
                auto client = weak.Upgrade();
                if (client) {
                    client->OnLongPress(info);
                }
            });
        }
        textOverlayRecognizer_->SetCoordinateOffset(coordinateOffset);
        textOverlayRecognizer_->SetTouchRestrict(touchRestrict);
        textOverlayRecognizer_->SetUseCatchMode(false);
        result.emplace_back(textOverlayRecognizer_);
    }
}

void RenderImage::OnLongPress(const LongPressInfo& longPressInfo)
{
    auto textOverlayManager = GetTextOverlayManager(context_);
    if (textOverlayManager) {
        auto textOverlayBase = textOverlayManager->GetTextOverlayBase();
        if (textOverlayBase) {
            auto targetNode = textOverlayManager->GetTargetNode();
            if (targetNode) {
                textOverlayManager->PopTextOverlay();
                textOverlayBase->MarkIsOverlayShowed(false);
                targetNode->MarkNeedRender();
            }
        }
        textOverlayManager->SetTextOverlayBase(AceType::WeakClaim(this));
    }

    Offset longPressPosition = longPressInfo.GetGlobalLocation();
    ShowTextOverlay(longPressPosition);
}

bool RenderImage::HandleMouseEvent(const MouseEvent& event)
{
    if (copyOption_ == CopyOptions::None || imageLoadingStatus_ != ImageLoadingStatus::LOAD_SUCCESS ||
        sourceInfo_.IsSvg()) {
        return false;
    }
    if (event.button == MouseButton::RIGHT_BUTTON && event.action == MouseAction::PRESS) {
        Offset rightClickOffset = event.GetOffset();
        auto textOverlayManager = GetTextOverlayManager(context_);
        if (textOverlayManager) {
            auto textOverlayBase = textOverlayManager->GetTextOverlayBase();
            if (textOverlayBase) {
                auto targetNode = textOverlayManager->GetTargetNode();
                if (targetNode) {
                    textOverlayManager->PopTextOverlay();
                    textOverlayBase->MarkIsOverlayShowed(false);
                    targetNode->MarkNeedRender();
                }
            }
            textOverlayManager->SetTextOverlayBase(AceType::WeakClaim(this));
        }
        ShowTextOverlay(rightClickOffset);
        return true;
    }
    return false;
}

bool RenderImage::HandleKeyEvent(const KeyEvent& event)
{
    if (event.action != KeyAction::DOWN) {
        return false;
    }
    if (event.IsCtrlWith(KeyCode::KEY_C) && copyOption_ != CopyOptions::None) {
        HandleOnCopy();
        return true;
    }
    return false;
}

void RenderImage::ShowTextOverlay(const Offset& showOffset)
{
    popOverlayOffset_ = showOffset;
    Offset startHandleOffset = popOverlayOffset_;
    Offset endHandleOffset = popOverlayOffset_;
    if (isOverlayShowed_ && updateHandlePosition_) {
        OverlayShowOption option { .showMenu = isOverlayShowed_,
            .updateOverlayType = UpdateOverlayType::LONG_PRESS,
            .startHandleOffset = startHandleOffset,
            .endHandleOffset = endHandleOffset };
        updateHandlePosition_(option);
        if (!animator_) {
            LOGE("Show textOverlay error, animator is nullptr");
            return;
        }
        if (!animator_->IsStopped()) {
            animator_->Stop();
        }
        animator_->Play();
        return;
    }

    textOverlay_ =
        AceType::MakeRefPtr<TextOverlayComponent>(GetThemeManager(), context_.Upgrade()->GetAccessibilityManager());
    textOverlay_->SetWeakImage(WeakClaim(this));
    textOverlay_->SetNeedCilpRect(false);
    textOverlay_->SetStartHandleOffset(startHandleOffset);
    textOverlay_->SetEndHandleOffset(endHandleOffset);
    textOverlay_->SetContext(context_);
    InitAnimation(context_);
    RegisterCallbacksToOverlay();
    MarkNeedRender();
}

void RenderImage::RegisterCallbacksToOverlay()
{
    if (!textOverlay_) {
        return;
    }

    textOverlay_->SetOnCopy([weak = AceType::WeakClaim(this)] {
        auto image = weak.Upgrade();
        if (image) {
            image->HandleOnCopy();
        }
    });

    auto callback = [weak = WeakClaim(this), pipelineContext = context_, textOverlay = textOverlay_](
                        const RefPtr<PixelMap>& pixmap) {
        auto context = pipelineContext.Upgrade();
        if (!context) {
            return;
        }
        auto textOverlayManager = context->GetTextOverlayManager();
        if (!textOverlayManager) {
            return;
        }
        textOverlayManager->PushTextOverlayToStack(textOverlay, pipelineContext);

        auto image = weak.Upgrade();
        if (!image) {
            return;
        }
        image->UpdateOverlay();
        image->MarkIsOverlayShowed(true);
    };
    if (clipboard_) {
        clipboard_->GetPixelMapData(callback);
    }
}

void RenderImage::UpdateOverlay()
{
    if (isOverlayShowed_ && updateHandlePosition_) {
        OverlayShowOption option { .showMenu = isOverlayShowed_,
            .updateOverlayType = UpdateOverlayType::LONG_PRESS,
            .startHandleOffset = popOverlayOffset_,
            .endHandleOffset = popOverlayOffset_ };
        updateHandlePosition_(option);
    }
}

void RenderImage::HandleOnCopy()
{
    if (!clipboard_) {
        return;
    }
    auto renderImage = AceType::Claim(this);
    auto type = sourceInfo_.GetSrcType();
    switch (type) {
        case SrcType::PIXMAP: {
            clipboard_->SetPixelMapData(sourceInfo_.GetPixmap(), copyOption_);
            break;
        }
        case SrcType::BASE64: {
            clipboard_->SetData(sourceInfo_.GetSrc(), copyOption_);
            break;
        }
        case SrcType::DATA_ABILITY_DECODED:
        case SrcType::DATA_ABILITY: {
            clipboard_->SetData(sourceInfo_.GetSrc(), copyOption_);
            break;
        }
        default: {
#ifndef USE_ROSEN_DRAWING
            clipboard_->SetPixelMapData(renderImage->GetPixmapFromSkImage(), copyOption_);
#else
            clipboard_->SetPixelMapData(renderImage->GetPixmapFromDrawingImage(), copyOption_);
#endif
            break;
        }
    }

    auto textOverlayManager = GetTextOverlayManager(context_);
    if (textOverlayManager) {
        textOverlayManager->PopTextOverlay();
    }
    isOverlayShowed_ = false;
    MarkNeedRender();
}

void RenderImage::PerformLayout()
{
    if (background_) {
        PerformLayoutBgImage();
        if (imageRenderFunc_) {
            imageRenderFunc_();
        }
        return;
    }

    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    scale_ = context->GetViewScale();
    if (LessOrEqual(scale_, 0)) {
        scale_ = 1.0;
    }
    if (width_.IsValid() && height_.IsValid()) {
        imageComponentSize_ = Size(NormalizeToPx(width_), NormalizeToPx(height_));
        isImageSizeSet_ = true;
    }
    // Divided by the true pixel ratio to apply image fit.
    Size pictureSize = Measure() * (1.0 / scale_);
    auto maxSize = GetLayoutParam().GetMaxSize();
    if (fitMaxSize_ && (!imageComponentSize_.IsValid() || (!isImageSizeSet_ && maxSize != formerMaxSize_))) {
        imageComponentSize_ = maxSize;
        formerMaxSize_ = imageComponentSize_;
    }
    SetLayoutSize(GetLayoutParam().Constrain(imageComponentSize_.IsValid() && !imageComponentSize_.IsInfinite()
                                                 ? imageComponentSize_
                                                 : CalculateBackupImageSize(pictureSize)));
    if (rawImageSizeUpdated_) {
        previousLayoutSize_ = GetLayoutSize();
    }
    srcRect_.SetRect(Offset(), pictureSize);
    dstRect_.SetRect(Offset(), GetLayoutSize());
    ApplyImageFit(srcRect_, dstRect_);
    // Restore image size.
    srcRect_.ApplyScale(scale_);
    if (!imageComponentSize_.IsValid()) {
        SetLayoutSize(dstRect_.GetSize());
    }
    decltype(imageLayoutCallbacks_) imageLayoutCallbacks(std::move(imageLayoutCallbacks_));
    std::for_each(
        imageLayoutCallbacks.begin(), imageLayoutCallbacks.end(), [](std::function<void()> callback) { callback(); });
    LayoutImageObject();
    if (renderAltImage_) {
        LayoutParam altLayoutParam;
        altLayoutParam.SetFixedSize(GetLayoutSize());
        renderAltImage_->Layout(altLayoutParam);
    }

    CalculateResizeTarget();
    if (hasObjectPosition_) {
        ApplyObjectPosition();
    }
}

Size RenderImage::CalculateBackupImageSize(const Size& pictureSize)
{
    // Since the return value of this function is used to determine the layout size of Image Component, it is essential
    // to guarantee that there is no infinite edge to avoid thread stuck that may occur.
    //
    // Generally speaking, the size of the picture will not be infinite, but the size of the svg picture is equal to the
    // maximum value of the layout parameters, so there is the possibility of infinity.
    //
    // Note that [pictureSize] has been scaled by [scale_], so we need to obtain the original picture size via
    // [Measure()] to verify whether or not it has infinite edge.
    auto rawPicSize = Measure();
    if (!rawPicSize.IsValid() || rawPicSize.IsInfinite()) {
        return Size();
    }
    uint8_t infiniteStatus = (static_cast<uint8_t>(imageComponentSize_.IsWidthInfinite()) << 1) |
                             static_cast<uint8_t>(imageComponentSize_.IsHeightInfinite());
    double pictureSizeRatio = pictureSize.Width() / pictureSize.Height();
    Size backupImageSize = imageComponentSize_;
    switch (infiniteStatus) {
        case 0b00: // both width and height are infinite
            backupImageSize = pictureSize;
            break;
        case 0b01: // only height is infinite
            backupImageSize.SetHeight(imageComponentSize_.Width() / pictureSizeRatio);
            break;
        case 0b10: // only width is infinite
            backupImageSize.SetWidth(imageComponentSize_.Height() * pictureSizeRatio);
            break;
        default:
            backupImageSize = imageComponentSize_;
            break;
    }
    return backupImageSize;
}

bool RenderImage::NeedResize() const
{
    if (!resizeTarget_.IsValid()) {
        return false;
    }
    if (!previousResizeTarget_.IsValid()) {
        return true;
    }
    if (resizeTarget_ < previousResizeTarget_) {
        return false;
    }
    double widthEnlargedBy = resizeTarget_.Width() / previousResizeTarget_.Width();
    double heightEnlargedBy = resizeTarget_.Height() / previousResizeTarget_.Height();
    if (widthEnlargedBy > RESIZE_AGAIN_THRESHOLD || heightEnlargedBy > RESIZE_AGAIN_THRESHOLD) {
        return true;
    }
    return false;
}

void RenderImage::CalculateResizeTarget()
{
    if (!srcRect_.IsValid()) {
        return;
    }
    if (!autoResize_) {
        resizeTarget_ = rawImageSize_;
        resizeScale_ = Size(1.0, 1.0);
        return;
    }
    double widthScale = dstRect_.Width() / srcRect_.Width() * scale_;
    double heightScale = dstRect_.Height() / srcRect_.Height() * scale_;
    if (widthScale < 1.0 && heightScale < 1.0) {
        resizeScale_ = Size(widthScale, heightScale);
    } else {
        resizeScale_ = Size(1.0, 1.0);
    }
    resizeTarget_ = Size(rawImageSize_.Width() * resizeScale_.Width(), rawImageSize_.Height() * resizeScale_.Height());
}

void RenderImage::ApplyImageFit(Rect& srcRect, Rect& dstRect)
{
    Size rawPicSize = srcRect.GetSize();
    Size layoutSize = GetLayoutSize();
    switch (imageFit_) {
        case ImageFit::FILL:
            break;
        case ImageFit::NONE:
            ApplyNone(srcRect, dstRect, rawPicSize, layoutSize);
            break;
        case ImageFit::COVER:
            ApplyCover(srcRect, dstRect, rawPicSize, layoutSize);
            break;
        case ImageFit::FITWIDTH:
            ApplyFitWidth(srcRect, dstRect, rawPicSize, layoutSize);
            break;
        case ImageFit::FITHEIGHT:
            ApplyFitHeight(srcRect, dstRect, rawPicSize, layoutSize);
            break;
        case ImageFit::SCALE_DOWN:
            if (srcRect.GetSize() < dstRect.GetSize()) {
                ApplyNone(srcRect, dstRect, rawPicSize, layoutSize);
            } else {
                ApplyContain(srcRect, dstRect, rawPicSize, layoutSize);
            }
            break;
        case ImageFit::CONTAIN:
            ApplyContain(srcRect, dstRect, rawPicSize, layoutSize);
            break;
        default:
            ApplyContain(srcRect, dstRect, rawPicSize, layoutSize);
            break;
    }
}

void RenderImage::ApplyContain(Rect& srcRect, Rect& dstRect, const Size& rawPicSize, const Size& layoutSize)
{
    if (!rawPicSize.IsValid()) {
        return;
    }
    if (Size::CalcRatio(srcRect) > Size::CalcRatio(dstRect)) {
        dstRect.SetSize(rawPicSize * (layoutSize.Width() / rawPicSize.Width()));
    } else {
        dstRect.SetSize(rawPicSize * (layoutSize.Height() / rawPicSize.Height()));
    }
    dstRect.SetOffset(Alignment::GetAlignPosition(layoutSize, dstRect.GetSize(), alignment_));
}

void RenderImage::ApplyCover(Rect& srcRect, Rect& dstRect, const Size& rawPicSize, const Size& layoutSize)
{
    if (Size::CalcRatio(srcRect) > Size::CalcRatio(dstRect)) {
        srcRect.SetSize(layoutSize * (rawPicSize.Height() / layoutSize.Height()));
    } else {
        srcRect.SetSize(layoutSize * (rawPicSize.Width() / layoutSize.Width()));
    }
    srcRect.SetOffset(Alignment::GetAlignPosition(rawPicSize, srcRect.GetSize(), alignment_));
}

void RenderImage::ApplyFitWidth(Rect& srcRect, Rect& dstRect, const Size& rawPicSize, const Size& layoutSize)
{
    if (Size::CalcRatio(srcRect) > Size::CalcRatio(dstRect)) {
        dstRect.SetSize(rawPicSize * (layoutSize.Width() / rawPicSize.Width()));
        dstRect.SetOffset(Alignment::GetAlignPosition(layoutSize, dstRect.GetSize(), alignment_));
    } else {
        srcRect.SetSize(layoutSize * (rawPicSize.Width() / layoutSize.Width()));
        srcRect.SetOffset(Alignment::GetAlignPosition(rawPicSize, srcRect.GetSize(), alignment_));
    }
}

void RenderImage::ApplyFitHeight(Rect& srcRect, Rect& dstRect, const Size& rawPicSize, const Size& layoutSize)
{
    if (Size::CalcRatio(srcRect) > Size::CalcRatio(dstRect)) {
        srcRect.SetSize(layoutSize * (rawPicSize.Height() / layoutSize.Height()));
        srcRect.SetOffset(Alignment::GetAlignPosition(rawPicSize, srcRect.GetSize(), alignment_));
    } else {
        dstRect.SetSize(rawPicSize * (layoutSize.Height() / rawPicSize.Height()));
        dstRect.SetOffset(Alignment::GetAlignPosition(layoutSize, dstRect.GetSize(), alignment_));
    }
}

void RenderImage::ApplyNone(Rect& srcRect, Rect& dstRect, const Size& rawPicSize, const Size& layoutSize)
{
    Size srcSize =
        Size(std::min(layoutSize.Width(), rawPicSize.Width()), std::min(layoutSize.Height(), rawPicSize.Height()));
    dstRect.SetRect(Alignment::GetAlignPosition(layoutSize, srcSize, alignment_), srcSize);
    srcRect.SetRect(Alignment::GetAlignPosition(rawPicSize, srcSize, alignment_), srcSize);
}

void RenderImage::FireLoadEvent(const Size& picSize, const std::string& errorMsg) const
{
    auto context = context_.Upgrade();
    if (context && context->GetIsDeclarative()) {
        if (loadImgSuccessEvent_ && (imageLoadingStatus_ == ImageLoadingStatus::LOAD_SUCCESS)) {
            // here the last param of [loadImgSuccessEvent_] is [1],
            // which means the callback is triggered by [OnLoadSuccess]
            loadImgSuccessEvent_(std::make_shared<LoadImageSuccessEvent>(
                picSize.Width(), picSize.Height(), GetLayoutSize().Width(), GetLayoutSize().Height(), 1));
        }
        if (loadImgFailEvent_ && (imageLoadingStatus_ == ImageLoadingStatus::LOAD_FAIL)) {
            loadImgFailEvent_(
                std::make_shared<LoadImageFailEvent>(GetLayoutSize().Width(), GetLayoutSize().Height(), errorMsg));
        }
        return;
    }
    std::string param;
    if (loadSuccessEvent_ && (imageLoadingStatus_ == ImageLoadingStatus::LOAD_SUCCESS)) {
        param = std::string("\"complete\",{\"width\":")
                    .append(std::to_string(picSize.Width()))
                    .append(",\"height\":")
                    .append(std::to_string(picSize.Height()))
                    .append("}");
        loadSuccessEvent_(param);
    }
    if (loadFailEvent_ && (imageLoadingStatus_ == ImageLoadingStatus::LOAD_FAIL)) {
        param = std::string("\"error\",{\"width\":")
                    .append(std::to_string(picSize.Width()))
                    .append(",\"height\":")
                    .append(std::to_string(picSize.Height()))
                    .append("}");
        loadFailEvent_(param);
    }
    if (loadFailCallback_ && (imageLoadingStatus_ == ImageLoadingStatus::LOAD_FAIL)) {
        loadFailCallback_();
        loadFailCallback_ = nullptr;
    }
}

void RenderImage::SetRadius(const Border& border)
{
    auto leftEdgeWidth = border.Left().GetWidth();
    auto topEdgeWidth = border.Top().GetWidth();
    auto rightEdgeWidth = border.Right().GetWidth();
    auto bottomEdgeWidth = border.Bottom().GetWidth();
    topLeftRadius_ = Radius(border.TopLeftRadius() - Radius(topEdgeWidth, leftEdgeWidth));
    topRightRadius_ = Radius(border.TopRightRadius() - Radius(topEdgeWidth, rightEdgeWidth));
    bottomLeftRadius_ = Radius(border.BottomLeftRadius() - Radius(bottomEdgeWidth, leftEdgeWidth));
    bottomRightRadius_ = Radius(border.BottomRightRadius() - Radius(bottomEdgeWidth, rightEdgeWidth));
}

bool RenderImage::IsSVG(const std::string& src, InternalResource::ResourceId resourceId)
{
    return ImageComponent::IsSvgSuffix(src) || (src.empty() && resourceId > InternalResource::ResourceId::SVG_START &&
                                                   resourceId < InternalResource::ResourceId::SVG_END);
}

void RenderImage::PerformLayoutBgImage()
{
    if (!background_) {
        return;
    }
    if (!rawImageSize_.IsValid()) {
        return;
    }

    GenerateImageRects(rawImageSize_, imageSize_, imageRepeat_, imagePosition_);
    srcRect_.SetOffset(Offset());
    srcRect_.SetSize(rawImageSize_);
    dstRect_.SetOffset(Offset());
    dstRect_.SetSize(imageRenderSize_);
}

// objectPosition
void RenderImage::ApplyObjectPosition()
{
    Size layoutSize = GetLayoutSize();
    Offset offset;
    if (imageObjectPosition_.GetSizeTypeX() == BackgroundImagePositionType::PX) {
        offset.SetX((layoutSize.Width() - dstRect_.Width()) / 2 - imageObjectPosition_.GetSizeValueX());
    } else {
        offset.SetX((layoutSize.Width() - dstRect_.Width()) / 2 - // 2: left & right border of width
                    imageObjectPosition_.GetSizeValueX() * (layoutSize.Width() - dstRect_.Width()) / PERCENT_TRANSLATE);
    }

    if (imageObjectPosition_.GetSizeTypeY() == BackgroundImagePositionType::PX) {
        offset.SetY((layoutSize.Height() - dstRect_.Height()) / 2 - imageObjectPosition_.GetSizeValueY());
    } else {
        offset.SetY((layoutSize.Height() - dstRect_.Height()) / 2 - imageObjectPosition_.GetSizeValueY() *
                                                                        (layoutSize.Height() - dstRect_.Height()) /
                                                                        PERCENT_TRANSLATE);
    }
    imageRenderPosition_ = offset;
}

void RenderImage::GenerateImageRects(const Size& srcSize, const BackgroundImageSize& imageSize, ImageRepeat imageRepeat,
    const BackgroundImagePosition& imagePosition)
{
    rectList_.clear();
    if (NearEqual(boxPaintSize_.Width(), Size::INFINITE_SIZE) ||
        NearEqual(boxPaintSize_.Height(), Size::INFINITE_SIZE)) {
        boxPaintSize_ = viewPort_;
    }

    // Different with Image Repeat
    imageRenderSize_ = CalculateImageRenderSize(srcSize, imageSize);
    if (NearZero(imageRenderSize_.Width()) || NearZero(imageRenderSize_.Height())) {
        return;
    }
    // Ceil render size
    imageRenderSize_ = Size(ceil(imageRenderSize_.Width()), ceil(imageRenderSize_.Height()));

    CalculateImageRenderPosition(imagePosition);

    int32_t minX = 0;
    int32_t minY = 0;
    int32_t maxX = 0;
    int32_t maxY = 0;
    if (imageRepeat == ImageRepeat::REPEAT || imageRepeat == ImageRepeat::REPEAT_X) {
        if (LessOrEqual(imageRenderPosition_.GetX(), 0.0)) {
            minX = 0;
            maxX = std::ceil((boxPaintSize_.Width() - imageRenderPosition_.GetX()) / imageRenderSize_.Width());
        } else {
            minX = std::floor((-imageRenderPosition_.GetX()) / imageRenderSize_.Width());
            maxX = std::ceil((boxPaintSize_.Width() - imageRenderPosition_.GetX()) / imageRenderSize_.Width());
        }
    }

    if (imageRepeat == ImageRepeat::REPEAT || imageRepeat == ImageRepeat::REPEAT_Y) {
        if (LessOrEqual(imageRenderPosition_.GetY(), 0.0)) {
            minY = 0;
            maxY = std::ceil((boxPaintSize_.Height() - imageRenderPosition_.GetY()) / imageRenderSize_.Height());
        } else {
            minY = std::floor((-imageRenderPosition_.GetY()) / imageRenderSize_.Height());
            maxY = std::ceil((boxPaintSize_.Height() - imageRenderPosition_.GetY()) / imageRenderSize_.Height());
        }
    }

    Rect imageCell = Rect(imageRenderPosition_, Size(imageRenderSize_.Width(), imageRenderSize_.Height()));
    for (int32_t i = minY; i <= maxY; ++i) {
        for (int32_t j = minX; j <= maxX; ++j) {
            rectList_.emplace_back(imageCell + Offset(j * imageRenderSize_.Width(), i * imageRenderSize_.Height()));
        }
    }

    if (imageLoadingStatus_ == ImageLoadingStatus::LOAD_SUCCESS) {
        currentDstRectList_ = rectList_;
    }
}

Size RenderImage::CalculateImageRenderSize(const Size& srcSize, const BackgroundImageSize& imageSize) const
{
    Size renderSize;
    if (NearZero(srcSize.Width()) || NearZero(srcSize.Height()) || NearZero(boxPaintSize_.Width()) ||
        NearZero(boxPaintSize_.Height())) {
        return renderSize;
    }

    if (!imageSize.IsValid()) {
        return renderSize;
    }

    if (imageSize.GetSizeTypeX() == BackgroundImageSizeType::CONTAIN ||
        imageSize.GetSizeTypeX() == BackgroundImageSizeType::COVER) {
        renderSize = CalculateImageRenderSizeWithSingleParam(srcSize, imageSize);
    } else {
        renderSize = CalculateImageRenderSizeWithDoubleParam(srcSize, imageSize);
    }

    return renderSize;
}

Size RenderImage::CalculateImageRenderSizeWithSingleParam(
    const Size& srcSize, const BackgroundImageSize& imageSize) const
{
    Size sizeRet;
    if (NearZero(srcSize.Width()) || NearZero(srcSize.Height()) || NearZero(boxPaintSize_.Width()) ||
        NearZero(boxPaintSize_.Height())) {
        return sizeRet;
    }
    double renderSizeX = 0.0;
    double renderSizeY = 0.0;
    if (imageSize.GetSizeTypeX() == BackgroundImageSizeType::CONTAIN) {
        double srcAspectRatio = srcSize.Width() / srcSize.Height();
        double paintAspectRatio = boxPaintSize_.Width() / boxPaintSize_.Height();
        renderSizeX = paintAspectRatio >= srcAspectRatio ? srcSize.Width() * (boxPaintSize_.Height() / srcSize.Height())
                                                         : boxPaintSize_.Width();
        renderSizeY = paintAspectRatio >= srcAspectRatio ? boxPaintSize_.Height()
                                                         : srcSize.Height() * (boxPaintSize_.Width() / srcSize.Width());
    } else if (imageSize.GetSizeTypeX() == BackgroundImageSizeType::COVER) {
        double srcAspectRatio = srcSize.Width() / srcSize.Height();
        double paintAspectRatio = boxPaintSize_.Width() / boxPaintSize_.Height();
        renderSizeX = paintAspectRatio >= srcAspectRatio
                          ? boxPaintSize_.Width()
                          : srcSize.Width() * (boxPaintSize_.Height() / srcSize.Height());
        renderSizeY = paintAspectRatio >= srcAspectRatio ? srcSize.Height() * (boxPaintSize_.Width() / srcSize.Width())
                                                         : boxPaintSize_.Height();
    }

    sizeRet.SetWidth(renderSizeX);
    sizeRet.SetHeight(renderSizeY);
    return sizeRet;
}

Size RenderImage::CalculateImageRenderSizeWithDoubleParam(
    const Size& srcSize, const BackgroundImageSize& imageSize) const
{
    Size sizeRet;
    if (NearZero(srcSize.Width()) || NearZero(srcSize.Height()) || NearZero(boxPaintSize_.Width()) ||
        NearZero(boxPaintSize_.Height())) {
        return sizeRet;
    }

    double renderSizeX = 0.0;
    double renderSizeY = 0.0;
    if (imageSize.GetSizeTypeX() == BackgroundImageSizeType::LENGTH) {
        renderSizeX = imageSize.GetSizeValueX();
    } else if (imageSize.GetSizeTypeX() == BackgroundImageSizeType::PERCENT) {
        renderSizeX = boxPaintSize_.Width() * imageSize.GetSizeValueX() / PERCENT_TRANSLATE;
    }

    if (imageSize.GetSizeTypeY() == BackgroundImageSizeType::LENGTH) {
        renderSizeY = imageSize.GetSizeValueY();
    } else if (imageSize.GetSizeTypeY() == BackgroundImageSizeType::PERCENT) {
        renderSizeY = boxPaintSize_.Height() * imageSize.GetSizeValueY() / PERCENT_TRANSLATE;
    }

    if (imageSize.GetSizeTypeX() == BackgroundImageSizeType::AUTO &&
        imageSize.GetSizeTypeY() == BackgroundImageSizeType::AUTO) {
        renderSizeX = srcSize.Width();
        renderSizeY = srcSize.Height();
    } else if (imageSize.GetSizeTypeX() == BackgroundImageSizeType::AUTO) {
        renderSizeX = srcSize.Width() * (renderSizeY / srcSize.Height());
    } else if (imageSize.GetSizeTypeY() == BackgroundImageSizeType::AUTO) {
        renderSizeY = srcSize.Height() * (renderSizeX / srcSize.Width());
    }

    sizeRet.SetWidth(renderSizeX);
    sizeRet.SetHeight(renderSizeY);
    if (!sizeRet.IsValid()) {
        sizeRet = Size();
    }
    return sizeRet;
}

void RenderImage::CalculateImageRenderPosition(const BackgroundImagePosition& imagePosition)
{
    Offset offset;

    if (imagePosition.GetSizeTypeX() == BackgroundImagePositionType::PX) {
        offset.SetX(imagePosition.GetSizeValueX());
    } else {
        offset.SetX(
            imagePosition.GetSizeValueX() * (boxPaintSize_.Width() - imageRenderSize_.Width()) / PERCENT_TRANSLATE);
    }

    if (imagePosition.GetSizeTypeY() == BackgroundImagePositionType::PX) {
        offset.SetY(imagePosition.GetSizeValueY());
    } else {
        offset.SetY(
            imagePosition.GetSizeValueY() * (boxPaintSize_.Height() - imageRenderSize_.Height()) / PERCENT_TRANSLATE);
    }

    imageRenderPosition_ = offset;
}

void RenderImage::ClearRenderObject()
{
    RenderNode::ClearRenderObject();

    isImageSizeSet_ = false;
    rawImageSizeUpdated_ = false;
    matchTextDirection_ = false;
    imageComponentSize_ = Size();
    formerMaxSize_ = Size();
    alignment_ = Alignment::CENTER;
    imageLoadingStatus_ = ImageLoadingStatus::UNLOADED;

    imageFit_ = ImageFit::COVER;
    imageRepeat_ = ImageRepeat::NO_REPEAT;
    rectList_.clear();
    color_.reset();
    sourceInfo_.Reset();
    singleWidth_ = 0.0;
    displaySrcWidth_ = 0.0;
    scale_ = 1.0;
    horizontalRepeatNum_ = 1.0;
    rotate_ = 0.0;
    keepOffsetZero_ = false;
    resizeCallLoadImage_ = false;
    frameCount_ = 0;
    topLeftRadius_ = Radius(0.0);
    topRightRadius_ = Radius(0.0);
    bottomLeftRadius_ = Radius(0.0);
    bottomRightRadius_ = Radius(0.0);
    resizeScale_ = Size();
    resizeTarget_ = Size();
    previousResizeTarget_ = Size();
    currentResizeScale_ = Size();
    width_ = Dimension();
    height_ = Dimension();
    rawImageSize_ = Size();
    renderAltImage_ = nullptr;
    proceedPreviousLoading_ = false;
    imageUpdateFunc_ = nullptr;
    imageRenderFunc_ = nullptr;
    background_ = false;
    boxPaintSize_ = Size();
    boxMarginOffset_ = Offset();
    imageSize_ = BackgroundImageSize();
    imagePosition_ = BackgroundImagePosition();
    imageObjectPosition_ = ImageObjectPosition();
    imageRenderSize_ = Size();
    imageRenderPosition_ = Offset();
    forceResize_ = false;
    forceReload_ = false;
    imageSizeForEvent_ = { 0.0, 0.0 };
    retryCnt_ = 0;
}

void RenderImage::PrintImageLog(const Size& srcSize, const BackgroundImageSize& imageSize, ImageRepeat imageRepeat,
    const BackgroundImagePosition& imagePosition) const
{}

void RenderImage::Dump()
{
    DumpLog::GetInstance().AddDesc(std::string("UsingWideGamut: ").append(IsSourceWideGamut() ? "true" : "false"));
}

DragItemInfo RenderImage::GenerateDragItemInfo(const RefPtr<PipelineContext>& context, const GestureEvent& info)
{
    RefPtr<DragEvent> event = AceType::MakeRefPtr<DragEvent>();
    event->SetX(context->ConvertPxToVp(Dimension(info.GetGlobalPoint().GetX(), DimensionUnit::PX)));
    event->SetY(context->ConvertPxToVp(Dimension(info.GetGlobalPoint().GetY(), DimensionUnit::PX)));
    selectedItemSize_ = GetLayoutSize();
    auto extraParams = JsonUtil::Create(true);

    return onDragStart_(event, extraParams->ToString());
}

void RenderImage::PanOnActionStart(const GestureEvent& info)
{
    if (!onDragStart_) {
        return;
    }

    auto pipelineContext = context_.Upgrade();
    if (!pipelineContext) {
        LOGE("Context is null.");
        return;
    }

    GestureEvent newInfo = info;
    Point newPoint = UpdatePoint(pipelineContext, startPoint_);
    newInfo.SetGlobalPoint(newPoint);
    auto dragItemInfo = GenerateDragItemInfo(pipelineContext, newInfo);
#if !defined(PREVIEW)
    if (!dragItemInfo.pixelMap && !dragItemInfo.customComponent) {
        auto initRenderNode = AceType::Claim(this);
        isDragDropNode_ = true;
        pipelineContext->SetInitRenderNode(initRenderNode);

        AddDataToClipboard(pipelineContext, dragItemInfo.extraInfo, "", GetImageSrc());
        if (!dragWindow_) {
            auto rect = pipelineContext->GetCurrentWindowRect();
            dragWindow_ = DragWindow::CreateDragWindow("APP_DRAG_WINDOW",
                static_cast<int32_t>(info.GetGlobalPoint().GetX() + rect.Left()),
                static_cast<int32_t>(info.GetGlobalPoint().GetY() + rect.Top()),
                static_cast<uint32_t>(initRenderNode->GetPaintRect().Width()),
                static_cast<uint32_t>(initRenderNode->GetPaintRect().Height()));
            dragWindow_->SetOffset(static_cast<int32_t>(rect.Left()), static_cast<int32_t>(rect.Top()));
#ifndef USE_ROSEN_DRAWING
            auto image = initRenderNode->GetSkImage();
#else
            auto image = initRenderNode->GetDrawingImage();
#endif
            dragWindow_->DrawImage(image);
        }
        if (dragWindow_) {
            AceEngineExt::GetInstance().DragStartExt();
        }
        return;
    }

    if (dragItemInfo.pixelMap) {
        auto initRenderNode = AceType::Claim(this);
        isDragDropNode_ = true;
        pipelineContext->SetInitRenderNode(initRenderNode);

        AddDataToClipboard(pipelineContext, dragItemInfo.extraInfo, "", GetImageSrc());
        if (!dragWindow_) {
            auto rect = pipelineContext->GetCurrentWindowRect();
            dragWindow_ = DragWindow::CreateDragWindow("APP_DRAG_WINDOW",
                static_cast<int32_t>(info.GetGlobalPoint().GetX()) + rect.Left(),
                static_cast<int32_t>(info.GetGlobalPoint().GetY()) + rect.Top(), dragItemInfo.pixelMap->GetWidth(),
                dragItemInfo.pixelMap->GetHeight());
            dragWindow_->SetOffset(rect.Left(), rect.Top());
            dragWindow_->DrawPixelMap(dragItemInfo.pixelMap);
        }
        if (dragWindow_) {
            AceEngineExt::GetInstance().DragStartExt();
        }
        return;
    }
#endif
    if (!dragItemInfo.customComponent) {
        LOGW("the drag custom component is null");
        return;
    }

    hasDragItem_ = true;
    auto positionedComponent = AceType::MakeRefPtr<PositionedComponent>(dragItemInfo.customComponent);
    positionedComponent->SetTop(Dimension(GetGlobalOffset().GetY()));
    positionedComponent->SetLeft(Dimension(GetGlobalOffset().GetX()));
    SetLocalPoint(startPoint_ - GetGlobalOffset());
    auto updatePosition = [renderBox = AceType::Claim(this)](
                              const std::function<void(const Dimension&, const Dimension&)>& func) {
        if (!renderBox) {
            return;
        }
        renderBox->SetUpdateBuilderFuncId(func);
    };
    positionedComponent->SetUpdatePositionFuncId(updatePosition);
    auto stackElement = pipelineContext->GetLastStack();
    stackElement->PushComponent(positionedComponent);
}

void RenderImage::PanOnActionUpdate(const GestureEvent& info)
{
#if !defined(PREVIEW)
    if (isDragDropNode_ && dragWindow_) {
        int32_t x = static_cast<int32_t>(info.GetGlobalPoint().GetX());
        int32_t y = static_cast<int32_t>(info.GetGlobalPoint().GetY());
        if (lastDragMoveOffset_ == Offset(x, y)) {
            return;
        }
        lastDragMoveOffset_ = Offset(x, y);
        if (dragWindow_) {
            dragWindow_->MoveTo(x, y);
        }
        return;
    }
#endif
    auto pipelineContext = context_.Upgrade();
    if (!pipelineContext) {
        LOGE("Context is null.");
        return;
    }

    RefPtr<DragEvent> event = AceType::MakeRefPtr<DragEvent>();
    event->SetX(pipelineContext->ConvertPxToVp(Dimension(info.GetGlobalPoint().GetX(), DimensionUnit::PX)));
    event->SetY(pipelineContext->ConvertPxToVp(Dimension(info.GetGlobalPoint().GetY(), DimensionUnit::PX)));

    Offset offset = info.GetGlobalPoint() - GetLocalPoint();
    if (GetUpdateBuilderFuncId()) {
        GetUpdateBuilderFuncId()(Dimension(offset.GetX()), Dimension(offset.GetY()));
    }

    auto extraParams = JsonUtil::Create(true);
    auto targetDragDropNode = FindDragDropNode(pipelineContext, info);
    auto preDragDropNode = GetPreDragDropNode();
    if (preDragDropNode == targetDragDropNode) {
        if (targetDragDropNode && targetDragDropNode->GetOnDragMove()) {
            (targetDragDropNode->GetOnDragMove())(event, extraParams->ToString());
        }
        return;
    }
    if (preDragDropNode && preDragDropNode->GetOnDragLeave()) {
        (preDragDropNode->GetOnDragLeave())(event, extraParams->ToString());
    }
    if (targetDragDropNode && targetDragDropNode->GetOnDragEnter()) {
        (targetDragDropNode->GetOnDragEnter())(event, extraParams->ToString());
    }
    SetPreDragDropNode(targetDragDropNode);
}

void RenderImage::PanOnActionEnd(const GestureEvent& info)
{
    auto pipelineContext = context_.Upgrade();
    if (!pipelineContext) {
        LOGE("Context is null.");
        return;
    }
#if !defined(PREVIEW)
    if (isDragDropNode_) {
        isDragDropNode_ = false;
        RestoreCilpboardData(pipelineContext);

        if (GetOnDrop()) {
            RefPtr<DragEvent> event = AceType::MakeRefPtr<DragEvent>();
            RefPtr<PasteData> pasteData = AceType::MakeRefPtr<PasteData>();
            event->SetPasteData(pasteData);
            event->SetX(pipelineContext->ConvertPxToVp(Dimension(info.GetGlobalPoint().GetX(), DimensionUnit::PX)));
            event->SetY(pipelineContext->ConvertPxToVp(Dimension(info.GetGlobalPoint().GetY(), DimensionUnit::PX)));

            auto extraParams = JsonUtil::Create(true);
            (GetOnDrop())(event, extraParams->ToString());
            pipelineContext->SetInitRenderNode(nullptr);
        }
    }

    if (dragWindow_) {
        dragWindow_->Destroy();
        dragWindow_ = nullptr;
        return;
    }
#endif
    RefPtr<DragEvent> event = AceType::MakeRefPtr<DragEvent>();
    RefPtr<PasteData> pasteData = AceType::MakeRefPtr<PasteData>();
    event->SetPasteData(pasteData);
    event->SetX(pipelineContext->ConvertPxToVp(Dimension(info.GetGlobalPoint().GetX(), DimensionUnit::PX)));
    event->SetY(pipelineContext->ConvertPxToVp(Dimension(info.GetGlobalPoint().GetY(), DimensionUnit::PX)));

    Offset offset = info.GetGlobalPoint() - GetLocalPoint();
    if (GetUpdateBuilderFuncId()) {
        GetUpdateBuilderFuncId()(Dimension(offset.GetX()), Dimension(offset.GetY()));
    }
    if (hasDragItem_) {
        auto stackElement = pipelineContext->GetLastStack();
        stackElement->PopComponent();
    }
    hasDragItem_ = false;

    ACE_DCHECK(GetPreDragDropNode() == FindTargetRenderNode<DragDropEvent>(pipelineContext, info));
    auto targetDragDropNode = GetPreDragDropNode();
    if (!targetDragDropNode) {
        return;
    }
    if (targetDragDropNode->GetOnDrop()) {
        auto extraParams = JsonUtil::Create(true);
        (targetDragDropNode->GetOnDrop())(event, extraParams->ToString());
    }
    SetPreDragDropNode(nullptr);
}

void RenderImage::PanOnActionCancel(const GestureEvent& info)
{
    auto pipelineContext = context_.Upgrade();
    if (!pipelineContext) {
        LOGE("Context is null.");
        return;
    }

#if !defined(PREVIEW)
    if (isDragDropNode_) {
        isDragDropNode_ = false;
        RestoreCilpboardData(pipelineContext);
    }

    if (dragWindow_) {
        dragWindow_->Destroy();
        dragWindow_ = nullptr;
    }
#endif
    if (hasDragItem_) {
        auto stackElement = pipelineContext->GetLastStack();
        stackElement->PopComponent();
        hasDragItem_ = false;
    }
    SetPreDragDropNode(nullptr);
}

} // namespace OHOS::Ace
