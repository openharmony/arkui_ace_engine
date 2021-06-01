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

#include "base/log/log.h"
#include "base/utils/utils.h"
#include "core/components/align/render_align.h"
#include "core/components/image/image_component.h"
#include "core/components/image/image_event.h"
#include "core/event/ace_event_helper.h"

namespace OHOS::Ace {
namespace {

constexpr double RESIZE_AGAIN_THRESHOLD = 1.2;

} // namespace

void RenderImage::Update(const RefPtr<Component>& component)
{
    const RefPtr<ImageComponent> image = AceType::DynamicCast<ImageComponent>(component);
    if (image) {
        currentSrcRect_ = srcRect_;
        currentDstRectList_ = rectList_;
        imageSrc_ = image->GetSrc();
        imageAlt_ = image->GetAlt();
        resourceId_ = image->GetResourceId();

        width_ = image->GetWidth();
        height_ = image->GetHeight();
        alignment_ = image->GetAlignment();
        imageFit_ = image->GetImageFit();
        fitMaxSize_ = image->GetFitMaxSize();
        imageRepeat_ = image->GetImageRepeat();
        color_ = image->GetColor();
        isColorSet_ = image->IsColorSet();
        previousLayoutSize_ = Size();
        SetTextDirection(image->GetTextDirection());
        matchTextDirection_ = image->IsMatchTextDirection();
        SetRadius(image->GetBorder());
        auto context = context_.Upgrade();
        if (context && context->GetIsDeclarative()) {
            loadImgSuccessEvent_ = AceAsyncEvent<void(const std::shared_ptr<BaseEventInfo>&)>::Create(
                image->GetLoadSuccessEventId(), context_);
            loadImgFailEvent_ = AceAsyncEvent<void(const std::shared_ptr<BaseEventInfo>&)>::Create(
                image->GetLoadFailEventId(), context_);
        } else {
            loadSuccessEvent_ =
                AceAsyncEvent<void(const std::string&)>::Create(image->GetLoadSuccessEventId(), context_);
            loadFailEvent_ = AceAsyncEvent<void(const std::string&)>::Create(image->GetLoadFailEventId(), context_);
        }
    }
}

void RenderImage::PerformLayout()
{
    if (background_) {
        PerformLayoutBgImage();
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
    SetLayoutSize(GetLayoutParam().Constrain(imageComponentSize_.IsValid() && !imageComponentSize_.IsInfinite() ?
        imageComponentSize_ : CalculateBackupImageSize(pictureSize)));
    if (rawImageSizeUpdated_) {
        previousLayoutSize_ = GetLayoutSize();
    }
    srcRect_.SetRect(Offset(), pictureSize);
    dstRect_.SetRect(Offset(), GetLayoutSize());
    ApplyImageFit(srcRect_, dstRect_);
    // Restore image size.
    srcRect_.ApplyScale(scale_);
    if (paddingHorizontal_ > 0.0 || paddingVertical_ > 0.0) {
        GenerateRepeatRects(dstRect_,
            GetLayoutSize() - Size(paddingHorizontal_ * (horizontalRepeatNum_ * 2 - 1), paddingVertical_ * 2),
            imageRepeat_);
        ACE_DCHECK(!rectList_.empty());
        auto iter = rectList_.begin();
        iter->SetOffset(iter->GetOffset() + Offset(paddingHorizontal_, paddingVertical_));
        for (int32_t index = 1; index < static_cast<int32_t>(rectList_.size()); index++) {
            iter++;
            iter->SetOffset(iter->GetOffset() + Offset(paddingHorizontal_ * (2 * index + 1), paddingVertical_));
        }
    } else {
        GenerateRepeatRects(dstRect_, GetLayoutSize(), imageRepeat_);
    }
    if (!imageComponentSize_.IsValid()) {
        SetLayoutSize(dstRect_.GetSize());
        std::for_each(
            rectList_.begin(), rectList_.end(), [offset = dstRect_.GetOffset()](Rect& rect) { rect -= offset; });
    }
    if (renderAltImage_) {
        LayoutParam altLayoutParam;
        altLayoutParam.SetFixedSize(GetLayoutSize());
        renderAltImage_->Layout(altLayoutParam);
    }
    CalculateResizeTarget();
}

Size RenderImage::CalculateBackupImageSize(const Size& pictureSize) const
{
    if (!pictureSize.IsValid()) {
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
        case ImageFit::SCALEDOWN:
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

void RenderImage::GenerateRepeatRects(
    const Rect& fundamentalRect, const Size& parentSize, const ImageRepeat& imageRepeat)
{
    rectList_.clear();
    if (!(fundamentalRect.GetSize() < parentSize)) {
        if (fundamentalRect.GetSize() != parentSize) {
            LOGW("Invalid input! Please check fundamentalRect size and parentSize.");
        }
        rectList_.push_back(fundamentalRect);
        return;
    }
    if (!fundamentalRect.GetSize().IsValid()) {
        LOGW("Invalid fundamentalRect size! Please check fundamentalRect size.");
        return;
    }

    double beforeCeilNum = fundamentalRect.Left() / fundamentalRect.Width();
    double leftRepeatNum = NearZero(beforeCeilNum - floor(beforeCeilNum)) ? floor(beforeCeilNum) : ceil(beforeCeilNum);
    beforeCeilNum = (parentSize.Width() - fundamentalRect.Right()) / fundamentalRect.Width();
    double rightRepeatNum = NearZero(beforeCeilNum - floor(beforeCeilNum)) ? floor(beforeCeilNum) : ceil(beforeCeilNum);
    beforeCeilNum = fundamentalRect.Top() / fundamentalRect.Height();
    double upRepeatNum = NearZero(beforeCeilNum - floor(beforeCeilNum)) ? floor(beforeCeilNum) : ceil(beforeCeilNum);
    beforeCeilNum = (parentSize.Height() - fundamentalRect.Bottom()) / fundamentalRect.Height();
    double bottomRepeatNum =
        NearZero(beforeCeilNum - floor(beforeCeilNum)) ? floor(beforeCeilNum) : ceil(beforeCeilNum);
    switch (imageRepeat) {
        case ImageRepeat::REPEAT:
            break;
        case ImageRepeat::REPEATX:
            upRepeatNum = 0.0;
            bottomRepeatNum = 0.0;
            break;
        case ImageRepeat::REPEATY:
            leftRepeatNum = 0.0;
            rightRepeatNum = 0.0;
            break;
        default:
            upRepeatNum = 0.0;
            bottomRepeatNum = 0.0;
            leftRepeatNum = 0.0;
            rightRepeatNum = 0.0;
            break;
    }
    for (int32_t i = -1 * upRepeatNum; i <= bottomRepeatNum; i++) {
        for (int32_t j = -1 * leftRepeatNum; j <= rightRepeatNum; j++) {
            rectList_.push_back(fundamentalRect + Offset(j * fundamentalRect.Width(), i * fundamentalRect.Height()));
        }
    }
}

void RenderImage::FireLoadEvent(const Size& picSize) const
{
    auto context = context_.Upgrade();
    if (context && context->GetIsDeclarative()) {
        if (loadImgSuccessEvent_ && (imageLoadingStatus_ == ImageLoadingStatus::LOAD_SUCCESS)) {
            loadImgSuccessEvent_(std::make_shared<LoadImageSuccessEvent>(picSize.Width(), picSize.Height()));
        }
        if (loadImgFailEvent_ && (imageLoadingStatus_ == ImageLoadingStatus::LOAD_FAIL)) {
            loadImgFailEvent_(std::make_shared<LoadImageFailEvent>());
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
    // 4 is the length of ".svg".
    return (src.size() > 4 && src.substr(src.size() - 4) == ".svg") ||
           (src.empty() && resourceId > InternalResource::ResourceId::SVG_START &&
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
    if (imageRepeat == ImageRepeat::REPEAT || imageRepeat == ImageRepeat::REPEATX) {
        if (LessOrEqual(imageRenderPosition_.GetX(), 0.0)) {
            minX = 0;
            maxX = std::ceil((boxPaintSize_.Width() - imageRenderPosition_.GetX()) / imageRenderSize_.Width());
        } else {
            minX = std::floor((-imageRenderPosition_.GetX()) / imageRenderSize_.Width());
            maxX = std::ceil((boxPaintSize_.Width() - imageRenderPosition_.GetX()) / imageRenderSize_.Width());
        }
    }

    if (imageRepeat == ImageRepeat::REPEAT || imageRepeat == ImageRepeat::REPEATY) {
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
    LOGD("[BOX][Dep:%{public}d][%{public}p][IMAGE] Result: X:%{public}d-%{public}d, Y:%{public}d-%{public}d",
        GetDepth(), this, minX, maxX, minY, maxY);
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
    imageRepeat_ = ImageRepeat::NOREPEAT;
    rectList_.clear();
    color_ = Color::TRANSPARENT;
    resourceId_ = InternalResource::ResourceId::NO_ID;
    singleWidth_ = 0.0;
    displaySrcWidth_ = 0.0;
    scale_ = 1.0;
    paddingHorizontal_ = 0.0;
    paddingVertical_ = 0.0;
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

    imageUpdateFunc_ = nullptr;
    background_ = false;
    boxPaintSize_ = Size();
    boxMarginOffset_ = Offset();
    imageSize_ = BackgroundImageSize();
    imagePosition_ = BackgroundImagePosition();

    imageRenderSize_ = Size();
    imageRenderPosition_ = Offset();
}

void RenderImage::PrintImageLog(const Size& srcSize, const BackgroundImageSize& imageSize, ImageRepeat imageRepeat,
    const BackgroundImagePosition& imagePosition) const
{
    LOGD("[BOX][IMAGE][Dep:%{public}d] Param:Src W:%{public}.1lf, H:%{public}.1lf, Size:%{public}.1lf|%{public}d, "
         "%{public}.1lf|%{public}d, Rep:%{public}u, Pos X:%{public}.1lf|%{public}d, Y:%{public}.1lf|%{public}d, "
         "BoxPaint:%{public}.1lf * %{public}.1lf, MarginOffset: %{public}.1lf * %{public}.1lf",
        GetDepth(), srcSize.Width(), srcSize.Height(), imageSize.GetSizeValueX(), imageSize.GetSizeTypeX(),
        imageSize.GetSizeValueY(), imageSize.GetSizeTypeY(), imageRepeat, imagePosition.GetSizeValueX(),
        imagePosition.GetSizeTypeX(), imagePosition.GetSizeValueY(), imagePosition.GetSizeTypeY(),
        boxPaintSize_.Width(), boxPaintSize_.Height(), boxMarginOffset_.GetX(), boxMarginOffset_.GetY());
    LOGD("[BOX][IMAGE][Dep:%{public}d] Result: Size:(%{public}.1lf*%{public}.1lf), Pos(%{public}.1lf,%{public}.1lf), "
         "rect:%{public}s",
        GetDepth(), imageRenderSize_.Width(), imageRenderSize_.Height(), imageRenderPosition_.GetX(),
        imageRenderPosition_.GetY(), rectList_.front().ToString().c_str());
}

} // namespace OHOS::Ace
