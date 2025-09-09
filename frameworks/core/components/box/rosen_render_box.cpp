/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#include "core/components/box/rosen_render_box.h"

#ifndef USE_ROSEN_DRAWING
#include "include/effects/SkGradientShader.h"
#include "include/utils/SkParsePath.h"
#endif

#include "core/common/rosen/rosen_convert_helper.h"
#include "core/components/box/rosen_mask_painter.h"
#include "core/components/common/painter/debug_boundary_painter.h"
#include "core/components/common/painter/rosen_decoration_painter.h"
#include "core/components/flex/render_flex.h"
#include "core/components/image/image_component.h"
#include "core/components_ng/render/animation_utils.h"
#ifndef USE_ROSEN_DRAWING
#include "core/components_ng/render/adapter/skia_image.h"
#else
#include "core/components_ng/render/adapter/drawing_image.h"
#endif
#include "render_service_client/core/ui/rs_ui_context.h"
#include "render_service_client/core/ui/rs_ui_director.h"

namespace OHOS::Ace {
namespace {

constexpr int32_t DOUBLE_WIDTH = 2;
constexpr int32_t HOVER_ANIMATION_DURATION = 250;
constexpr float EXTRA_WIDTH = 0.5f;
constexpr float SCALE_DEFAULT = 1.0f;
constexpr float SCALE_CHANGED = 1.05f;
const Color BOARD_CHANGED = Color::FromRGBO(0, 0, 0, 0.05);
const Rosen::RSAnimationTimingCurve SCALE_ANIMATION_TIMING_CURVE =
    Rosen::RSAnimationTimingCurve::CreateCubicCurve(0.2f, 0.0f, 0.2f, 1.0f);
constexpr uint32_t ACCESSIBILITY_FOCUS_COLOR = 0xbf39b500;
constexpr double ACCESSIBILITY_FOCUS_WIDTH = 4.0;
constexpr double ACCESSIBILITY_FOCUS_RADIUS_X = 2.0;
constexpr double ACCESSIBILITY_FOCUS_RADIUS_Y = 2.0;

constexpr uint32_t FOCUS_COLOR = 0xff0a59f7;
constexpr double FOCUS_WIDTH = 2.0;
constexpr double FOCUS_RADIUS_X = 4.0;
constexpr double FOCUS_RADIUS_Y = 4.0;
} // namespace

RosenRenderBox::RosenRenderBox()
{
    uploadSuccessCallback_ = [weak = AceType::WeakClaim(this)](
                                 ImageSourceInfo sourceInfo, const RefPtr<NG::CanvasImage>& image) {
        auto renderBox = weak.Upgrade();
        if (!renderBox) {
            LOGE("renderBox upgrade fail when image load success. callback image source info: %{private}s",
                sourceInfo.ToString().c_str());
            return;
        }
        renderBox->ImageDataPaintSuccess(image);
    };

    imageObjSuccessCallback_ = [weak = AceType::WeakClaim(this)](
                                   ImageSourceInfo info, const RefPtr<ImageObject>& imageObj) {
        auto renderBox = weak.Upgrade();
        if (!renderBox) {
            LOGE("renderBox upgrade fail when image object is ready. callback image source info: %{private}s",
                info.ToString().c_str());
            return;
        }
        renderBox->ImageObjReady(imageObj);
    };

    failedCallback_ = [weak = AceType::WeakClaim(this)](ImageSourceInfo info, const std::string& errorMsg = "") {
        auto renderBox = weak.Upgrade();
        if (renderBox) {
            renderBox->ImageObjFailed();
        }
    };

    onPostBackgroundTask_ = [weak = AceType::WeakClaim(this)](CancelableTask task) {
        auto renderBox = weak.Upgrade();
        if (renderBox) {
            renderBox->SetFetchImageObjBackgroundTask(task);
        }
    };
}

void RosenRenderBox::Update(const RefPtr<Component>& component)
{
    RenderBox::Update(component);
    SyncDecorationToRSNode();

    // use render image to render background image
    if (backDecoration_) {
        RefPtr<BackgroundImage> backgroundImage = backDecoration_->GetImage();
        UpdateBackgroundImage(backgroundImage);

        RefPtr<BorderImage> borderImage = backDecoration_->GetBorderImage();
        UpdateBorderImageProvider(borderImage);
    }

    if (mask_) {
        mask_->LoadMask(GetContext(), AceType::Claim(this));
    }
}

void RosenRenderBox::UpdateBorderImageProvider(const RefPtr<BorderImage>& bImage)
{
    auto context = GetContext().Upgrade();
    if (!context) {
        LOGE("pipeline context is null!");
        return;
    }
    if (!bImage) {
        return;
    }
    borderSrc_ = bImage->GetSrc();
    if (borderSrc_.empty()) {
        LOGE("borderImageSrc is null!");
        return;
    }
    image_ = nullptr;
    imageObj_ = nullptr;
}

void RosenRenderBox::FetchImageData()
{
    if (backDecoration_) {
        RefPtr<BorderImage> borderImage = backDecoration_->GetBorderImage();
        if (!borderImage) {
            return;
        }
        borderSrc_ = borderImage->GetSrc();
        if (borderSrc_.empty()) {
            LOGE("borderSrc_ is null!");
            return;
        }
        if (image_) {
            return;
        }
        ImageSourceInfo inComingSource(borderSrc_, Dimension(-1), Dimension(-1), InternalResource::ResourceId::NO_ID);
        ImageProvider::FetchImageObject(inComingSource, imageObjSuccessCallback_, uploadSuccessCallback_,
            failedCallback_, GetContext(), false, false, true, onPostBackgroundTask_);
    }
}

void RosenRenderBox::ImageObjReady(const RefPtr<ImageObject>& imageObj)
{
    imageObj_ = imageObj;
    if (imageObj_) {
        imageObj_->UploadToGpuForRender(
            GetContext(), uploadSuccessCallback_, failedCallback_, Size(0, 0), false, false);
    }
}

void RosenRenderBox::ImageObjFailed()
{
    image_ = nullptr;
    imageObj_ = nullptr;
    MarkNeedLayout();
}

void RosenRenderBox::ImageDataPaintSuccess(const RefPtr<NG::CanvasImage>& image)
{
#ifndef USE_ROSEN_DRAWING
    auto skiaImage = AceType::DynamicCast<NG::SkiaImage>(image);
    image_ = skiaImage->GetImage();
#else
    auto rosenImage = AceType::DynamicCast<NG::DrawingImage>(image);
    image_ = rosenImage->GetImage();
#endif
    MarkNeedLayout();
}

void RosenRenderBox::UpdateBackgroundImage(const RefPtr<BackgroundImage>& image)
{
    if (!image) {
        renderImage_ = nullptr;
        return;
    }

    if (!renderImage_) {
        renderImage_ = AceType::DynamicCast<RenderImage>(RenderImage::Create());
        if (!renderImage_) {
            return;
        }
        renderImage_->SetBackgroundImageFlag(true);
        renderImage_->Attach(GetContext());
        renderImage_->RegisterImageUpdateFunc([weakRenderBox = AceType::WeakClaim(this)]() {
            auto box = weakRenderBox.Upgrade();
            if (box) {
                box->MarkNeedLayout();
            }
        });
        renderImage_->RegisterImageRenderFunc([weakRenderBox = AceType::WeakClaim(this)]() {
            auto box = weakRenderBox.Upgrade();
            if (box) {
                box->MarkNeedRender();
            }
        });
    }

    auto imageComponent = AceType::MakeRefPtr<ImageComponent>(image->GetSrc());
    imageComponent->SetImageRepeat(image->GetImageRepeat());
    // set image size, x direction
    renderImage_->SetBgImageSize(image->GetImageSize().GetSizeTypeX(), image->GetImageSize().GetSizeValueX(), true);
    // set image size, y direction
    renderImage_->SetBgImageSize(image->GetImageSize().GetSizeTypeY(), image->GetImageSize().GetSizeValueY(), false);
    renderImage_->SetBgImagePosition(image->GetImagePosition());
    renderImage_->Update(imageComponent);
}

void RosenRenderBox::PerformLayout()
{
    RenderBox::PerformLayout();

    // calculate repeatParam.
    CalculateRepeatParam();

    // in case margin changed, have to call these function even if size/pos not changed.
    MarkNeedSyncGeometryProperties();

    auto flex = AceType::DynamicCast<RenderFlex>(GetFirstChild());
    bool childOverflow = flex ? isChildOverflow_ || flex->IsChildOverflow() : isChildOverflow_;
    if ((overflow_ != Overflow::CLIP || !childOverflow) && mask_ == nullptr && !boxClipFlag_ &&
        overflow_ != Overflow::FORCE_CLIP && (clipPath_ == nullptr || !clipPath_->NeedClip())) {
        return;
    }
    if (backDecoration_ &&
        (backDecoration_->GetHasBorderImageSource() || backDecoration_->GetHasBorderImageGradient())) {
        return;
    }
    auto rsNode = GetRSNode();
    if (!rsNode) {
        return;
    }

    rsNode->SetClipToBounds(true);
#ifdef OHOS_PLATFORM
#ifndef USE_ROSEN_DRAWING
    if (mask_ && mask_->IsValid() && mask_->IsPath()) {
        SkPath skPath;
        bool ret =
            CreateSkPath(mask_->GetMaskPath()->GetBasicShape(), mask_->GetMaskPath()->GetGeometryBoxType(), &skPath);
        if (!ret) {
            return;
        }
        // border should have be the same shape as mask
        rsNode->SetClipBounds(Rosen::RSPath::CreateRSPath(skPath));
    } else if (clipPath_ && clipPath_->NeedClip()) {
        SkPath skPath;
        bool ret = CreateSkPath(clipPath_->GetBasicShape(), clipPath_->GetGeometryBoxType(), &skPath);
        if (!ret) {
            return;
        }
        rsNode->SetClipBounds(Rosen::RSPath::CreateRSPath(skPath));
    }
#else
    if (mask_ && mask_->IsValid() && mask_->IsPath()) {
        RSRecordingPath drawingPath;
        bool ret =
            CreatePath(mask_->GetMaskPath()->GetBasicShape(), mask_->GetMaskPath()->GetGeometryBoxType(), &drawingPath);
        if (!ret) {
            return;
        }
        // border should have be the same shape as mask
        rsNode->SetClipBounds(Rosen::RSPath::CreateRSPath(drawingPath));
    } else if (clipPath_ && clipPath_->NeedClip()) {
        RSRecordingPath drawingPath;
        bool ret = CreatePath(clipPath_->GetBasicShape(), clipPath_->GetGeometryBoxType(), &drawingPath);
        if (!ret) {
            return;
        }
        rsNode->SetClipBounds(Rosen::RSPath::CreateRSPath(drawingPath));
    }
#endif // USE_ROSEN_DRAWING
#endif
}

void RosenRenderBox::Paint(RenderContext& context, const Offset& offset)
{
    if (backDecoration_ && backDecoration_->GetImage() && renderImage_ &&
        backDecoration_->GetBackgroundColor() == Color::TRANSPARENT) {
        // draw background image on current context/canvas
        renderImage_->RenderWithContext(context, offset);
    }
    auto rsNode = static_cast<RosenRenderContext*>(&context)->GetRSNode();
    auto pipeline = context_.Upgrade();
    if (!pipeline) {
        return;
    }
    SyncDecorationToRSNode();
    Rect paintSize = Rect(offset + margin_.GetOffsetInPx(pipeline->GetDipScale()), paintSize_);
    if (useLiteStyle_) {
        Size maxSize;
        maxSize.SetWidth(paintSize_.Width() > GetPaintRect().Width() ? paintSize_.Width() : GetPaintRect().Width());
        maxSize.SetHeight(
            paintSize_.Height() > GetPaintRect().Height() ? paintSize_.Height() : GetPaintRect().Height());
        paintSize.SetSize(maxSize);
    }
#ifndef USE_ROSEN_DRAWING
    SkRRect outerRRect =
        SkRRect::MakeRect(SkRect::MakeLTRB(paintSize.Left(), paintSize.Top(), paintSize.Right(), paintSize.Bottom()));
    SkRect focusRect = SkRect::MakeLTRB(paintSize.Left(), paintSize.Top(), paintSize.Right(), paintSize.Bottom());
#else
    RSRoundRect outerRRect = RSRoundRect();
    outerRRect.SetRect(RSRect(paintSize.Left(), paintSize.Top(), paintSize.Right(), paintSize.Bottom()));

    RSRect focusRect = RSRect(paintSize.Left(), paintSize.Top(), paintSize.Right(), paintSize.Bottom());
#endif
    Color bgColor = pipeline->GetAppBgColor();
    if (backDecoration_) {
        if (backDecoration_->GetHasBorderImageSource() || backDecoration_->GetHasBorderImageGradient()) {
            FetchImageData();
        }
        auto canvas = static_cast<RosenRenderContext*>(&context)->GetCanvas();
        if (canvas == nullptr) {
            LOGE("Paint canvas is null.");
            return;
        }
        auto context = context_.Upgrade();
        if (context->GetIsDeclarative()) {
            RosenDecorationPainter::PaintGrayScale(outerRRect, canvas, backDecoration_->GetGrayScale(), bgColor);
            RosenDecorationPainter::PaintBrightness(outerRRect, canvas, backDecoration_->GetBrightness(), bgColor);
            RosenDecorationPainter::PaintContrast(outerRRect, canvas, backDecoration_->GetContrast(), bgColor);
            RosenDecorationPainter::PaintSaturate(outerRRect, canvas, backDecoration_->GetSaturate(), bgColor);
            RosenDecorationPainter::PaintInvert(outerRRect, canvas, backDecoration_->GetInvert(), bgColor);
            RosenDecorationPainter::PaintSepia(outerRRect, canvas, backDecoration_->GetSepia(), bgColor);
            RosenDecorationPainter::PaintHueRotate(outerRRect, canvas, backDecoration_->GetHueRotate(), bgColor);
            RosenDecorationPainter::PaintColorBlend(outerRRect, canvas, backDecoration_->GetColorBlend(), bgColor);
        }
        auto position = Offset(0.0, 0.0);
        if (rsNode == nullptr) {
            LOGE("rsNode is null.");
            return;
        }
        rsNode->DrawOnNode(
#ifndef USE_ROSEN_DRAWING
            Rosen::ModifierNG::RSModifierType::OVERLAY_STYLE,
            [weak = WeakClaim(this), position](std::shared_ptr<SkCanvas> canvas) {
#else
            Rosen::ModifierNG::RSModifierType::OVERLAY_STYLE,
            [weak = WeakClaim(this), position](std::shared_ptr<RSCanvas> canvas) {
#endif
                auto renderBox = weak.Upgrade();
                if (renderBox == nullptr) {
                    LOGE("renderBox is null.");
                    return;
                }
                RosenDecorationPainter::PaintBorderImage(renderBox->backDecoration_, renderBox->paintSize_, position,
                    canvas.get(), renderBox->image_, renderBox->dipScale_);
            });
    }
    RenderNode::Paint(context, offset);
    if (frontDecoration_) {
        auto canvas = static_cast<RosenRenderContext*>(&context)->GetCanvas();
        if (canvas == nullptr) {
            LOGE("Paint canvas is null.");
            return;
        }
        auto context = context_.Upgrade();
        if (context->GetIsDeclarative()) {
            RosenDecorationPainter::PaintGrayScale(outerRRect, canvas, frontDecoration_->GetGrayScale(), bgColor);
            RosenDecorationPainter::PaintBrightness(outerRRect, canvas, frontDecoration_->GetBrightness(), bgColor);
            RosenDecorationPainter::PaintContrast(outerRRect, canvas, frontDecoration_->GetContrast(), bgColor);
            RosenDecorationPainter::PaintSaturate(outerRRect, canvas, frontDecoration_->GetSaturate(), bgColor);
            RosenDecorationPainter::PaintInvert(outerRRect, canvas, frontDecoration_->GetInvert(), bgColor);
            RosenDecorationPainter::PaintSepia(outerRRect, canvas, frontDecoration_->GetSepia(), bgColor);
            RosenDecorationPainter::PaintHueRotate(outerRRect, canvas, frontDecoration_->GetHueRotate(), bgColor);
            RosenDecorationPainter::PaintColorBlend(outerRRect, canvas, frontDecoration_->GetColorBlend(), bgColor);
        }
    }
    if (RenderBox::needPaintDebugBoundary_ && SystemProperties::GetDebugBoundaryEnabled()) {
        auto rsnode = static_cast<RosenRenderContext*>(&context)->GetRSNode();
        if (rsnode == nullptr) {
            LOGE("rsNode is null.");
            return;
        }
        rsnode->DrawOnNode(Rosen::ModifierNG::RSModifierType::OVERLAY_STYLE,
#ifndef USE_ROSEN_DRAWING
            [size = GetLayoutSize(), margin = GetMargin()](std::shared_ptr<SkCanvas> canvas) {
                SkAutoCanvasRestore acr(canvas.get(), true);
                auto overlayOffset = Offset(EXTRA_WIDTH, EXTRA_WIDTH) - margin.GetOffset();
                DebugBoundaryPainter::PaintDebugBoundary(canvas.get(), overlayOffset, size);
                DebugBoundaryPainter::PaintDebugCorner(canvas.get(), overlayOffset, size);
                DebugBoundaryPainter::PaintDebugMargin(canvas.get(), overlayOffset, size, margin);
#else
            [size = GetLayoutSize(), margin = GetMargin()](std::shared_ptr<RSCanvas> canvas) {
                RSAutoCanvasRestore acr(*canvas, true);
                auto overlayOffset = Offset(EXTRA_WIDTH, EXTRA_WIDTH) - margin.GetOffset();
                DebugBoundaryPainter::PaintDebugBoundary(canvas.get(), overlayOffset, size);
                DebugBoundaryPainter::PaintDebugCorner(canvas.get(), overlayOffset, size);
                DebugBoundaryPainter::PaintDebugMargin(canvas.get(), overlayOffset, size, margin);
#endif
            });
    }
    if (isAccessibilityFocus_) {
        PaintAccessibilityFocus(focusRect, context);
    }

    if (needFocusBorder_) {
        PaintFocus(focusRect, context);
    }

    if (rsNode == nullptr) {
        return;
    }

    RefPtr<RosenMaskPainter> mask = AceType::DynamicCast<RosenMaskPainter>(mask_);
    if (mask && mask->HasReady()) {
#ifndef USE_ROSEN_DRAWING
        SkPath skPath;
        if (mask_->IsPath()) {
            if (!CreateSkPath(
                    mask_->GetMaskPath()->GetBasicShape(), mask_->GetMaskPath()->GetGeometryBoxType(), &skPath)) {
                LOGE("CreateSkPath is failed.");
                return;
            }
        }
        rsNode->SetMask(mask->GetRSMask(GetPaintRect(), skPath));
#else
        RSRecordingPath drawingPath;
        if (mask_->IsPath()) {
            if (!CreatePath(mask_->GetMaskPath()->GetBasicShape(),
                mask_->GetMaskPath()->GetGeometryBoxType(), &drawingPath)) {
                LOGE("CreatePath is failed.");
                return;
            }
        }
        rsNode->SetMask(mask->GetRSMask(GetPaintRect(), drawingPath));
#endif
    }

    if ((!backDecoration_) || backDecoration_->GetImage() ||
        (backDecoration_->GetBackgroundColor() != Color::TRANSPARENT) || !(backDecoration_->GetGradient().IsValid())) {
        // no need to paint gradient
        if (backDecoration_->GetGradient().GetType() == GradientType::SWEEP) {
            rsNode->SetBackgroundShader(nullptr);
        }
        return;
    }

#ifndef USE_ROSEN_DRAWING
    auto size = SkSize::Make(GetLayoutSize().Width(), GetLayoutSize().Height());
#else
    auto size = RSSize(GetLayoutSize().Width(), GetLayoutSize().Height());
#endif
    auto shader = RosenDecorationPainter::CreateGradientShader(backDecoration_->GetGradient(), size, dipScale_);
    rsNode->SetBackgroundShader(Rosen::RSShader::CreateRSShader(shader));
}

#ifndef USE_ROSEN_DRAWING
SkColorType ConvertToSkColorType(PixelFormat pixelFormat)
{
    SkColorType colorType = kUnknown_SkColorType;
    switch (pixelFormat) {
        case PixelFormat::ALPHA_8: {
            colorType = kAlpha_8_SkColorType;
            break;
        }
        case PixelFormat::RGB_565: {
            colorType = kRGB_565_SkColorType;
            break;
        }
        case PixelFormat::RGBA_F16: {
            colorType = kRGBA_F16_SkColorType;
            break;
        }
        case PixelFormat::RGBA_8888:
        case PixelFormat::BGRA_8888: {
            colorType = kN32_SkColorType;
            break;
        }
        default: {
            LOGE("pixel format not supported.");
            break;
        }
    }

    return colorType;
}

SkAlphaType ConvertToSkAlphaType(AlphaType alphaType)
{
    SkAlphaType skAlphaType = kUnknown_SkAlphaType;
    switch (alphaType) {
        case AlphaType::IMAGE_ALPHA_TYPE_OPAQUE: {
            skAlphaType = kOpaque_SkAlphaType;
            break;
        }
        case AlphaType::IMAGE_ALPHA_TYPE_PREMUL: {
            skAlphaType = kPremul_SkAlphaType;
            break;
        }
        case AlphaType::IMAGE_ALPHA_TYPE_UNPREMUL: {
            skAlphaType = kUnpremul_SkAlphaType;
            break;
        }
        default: {
            LOGE("alpha type not supported.");
            break;
        }
    }
    return skAlphaType;
}
#else // USE_ROSEN_DRAWING
RSColorType ConvertToColorType(PixelFormat pixelFormat)
{
    switch (pixelFormat) {
        case PixelFormat::RGB_565:
            return RSColorType::COLORTYPE_RGB_565;
        case PixelFormat::RGBA_8888:
            return RSColorType::COLORTYPE_RGBA_8888;
        case PixelFormat::BGRA_8888:
            return RSColorType::COLORTYPE_BGRA_8888;
        case PixelFormat::ALPHA_8:
            return RSColorType::COLORTYPE_ALPHA_8;
        case PixelFormat::RGBA_F16:
            return RSColorType::COLORTYPE_RGBA_F16;
        case PixelFormat::UNKNOWN:
        case PixelFormat::ARGB_8888:
        case PixelFormat::RGB_888:
        case PixelFormat::NV21:
        case PixelFormat::NV12:
        case PixelFormat::CMYK:
        default:
            return RSColorType::COLORTYPE_UNKNOWN;
    }
}

RSAlphaType ConvertToAlphaType(AlphaType alphaType)
{
    switch (alphaType) {
        case AlphaType::IMAGE_ALPHA_TYPE_UNKNOWN:
            return RSAlphaType::ALPHATYPE_UNKNOWN;
        case AlphaType::IMAGE_ALPHA_TYPE_OPAQUE:
            return RSAlphaType::ALPHATYPE_OPAQUE;
        case AlphaType::IMAGE_ALPHA_TYPE_PREMUL:
            return RSAlphaType::ALPHATYPE_PREMUL;
        case AlphaType::IMAGE_ALPHA_TYPE_UNPREMUL:
            return RSAlphaType::ALPHATYPE_UNPREMUL;
        default:
            return RSAlphaType::ALPHATYPE_UNKNOWN;
    }
}
#endif // USE_ROSEN_DRAWING

#ifndef USE_ROSEN_DRAWING
void RosenRenderBox::PaintAccessibilityFocus(const SkRect& focusRect, RenderContext& context)
{
    auto canvas = static_cast<RosenRenderContext&>(context).GetCanvas();
    if (canvas == nullptr) {
        LOGE("Canvas is null, save failed.");
        return;
    }
    canvas->save();

    SkPaint paint;
    paint.setStyle(SkPaint::Style::kStroke_Style);
    paint.setColor(ACCESSIBILITY_FOCUS_COLOR);
    paint.setStrokeWidth(ACCESSIBILITY_FOCUS_WIDTH);

    SkRRect rRect = SkRRect::MakeRectXY(focusRect, ACCESSIBILITY_FOCUS_RADIUS_X, ACCESSIBILITY_FOCUS_RADIUS_Y);
    canvas->drawRRect(rRect, paint);
    canvas->restore();
}
#else
void RosenRenderBox::PaintAccessibilityFocus(const RSRect& focusRect, RenderContext& context)
{
    auto canvas = static_cast<RosenRenderContext&>(context).GetCanvas();
    if (canvas == nullptr) {
        LOGE("Canvas is null, save failed.");
        return;
    }
    canvas->Save();

    RSPen pen;
    pen.SetColor(ACCESSIBILITY_FOCUS_COLOR);
    pen.SetWidth(ACCESSIBILITY_FOCUS_WIDTH);

    RSRoundRect rRect(focusRect, ACCESSIBILITY_FOCUS_RADIUS_X, ACCESSIBILITY_FOCUS_RADIUS_Y);
    canvas->AttachPen(pen);
    canvas->DrawRoundRect(rRect);
    canvas->DetachPen();
    canvas->Restore();
}
#endif

#ifndef USE_ROSEN_DRAWING
void RosenRenderBox::PaintFocus(const SkRect& focusRect, RenderContext& context)
{
    auto canvas = static_cast<RosenRenderContext&>(context).GetCanvas();
    if (canvas == nullptr) {
        LOGE("Canvas is null, save failed.");
        return;
    }
    canvas->save();

    SkPaint paint;
    paint.setStyle(SkPaint::Style::kStroke_Style);
    paint.setColor(FOCUS_COLOR);
    paint.setStrokeWidth(FOCUS_WIDTH);
    paint.setAntiAlias(true);

    SkRRect rRect = SkRRect::MakeRectXY(focusRect, FOCUS_RADIUS_X, FOCUS_RADIUS_Y);
    canvas->drawRRect(rRect, paint);
    canvas->restore();
}
#else
void RosenRenderBox::PaintFocus(const RSRect& focusRect, RenderContext& context)
{
    auto canvas = static_cast<RosenRenderContext&>(context).GetCanvas();
    if (canvas == nullptr) {
        LOGE("Canvas is null, save failed.");
        return;
    }
    canvas->Save();

    RSPen pen;
    pen.SetColor(FOCUS_COLOR);
    pen.SetWidth(FOCUS_WIDTH);
    pen.SetAntiAlias(true);

    RSRoundRect rRect(focusRect, FOCUS_RADIUS_X, FOCUS_RADIUS_Y);
    canvas->AttachPen(pen);
    canvas->DrawRoundRect(rRect);
    canvas->DetachPen();
    canvas->Restore();
}
#endif

#ifndef USE_ROSEN_DRAWING
void RosenRenderBox::DrawOnPixelMap()
{
    if (pixelMap_ == nullptr) {
        LOGE("pixelMap_ or clipLayer_ is nullptr.");
        return;
    }
    auto width = paintSize_.Width();
    auto height = paintSize_.Height();
    if (LessOrEqual(width, 0.0) || LessOrEqual(height, 0.0)) {
        LOGE("invalidate size.");
        return;
    }
    auto imageInfo =
        SkImageInfo::Make(width, height, SkColorType::kBGRA_8888_SkColorType, SkAlphaType::kOpaque_SkAlphaType);
    SkBitmap tempCache;
    tempCache.allocPixels(imageInfo);
    SkCanvas tempCanvas(tempCache);

    uint8_t* dstPixels = const_cast<uint8_t*>(pixelMap_->GetPixels());
    if (dstPixels == nullptr) {
        LOGE("dstPixels is nullptr.");
        return;
    }
    SkImageInfo dstImageInfo = SkImageInfo::Make(pixelMap_->GetWidth(), pixelMap_->GetHeight(),
        ConvertToSkColorType(pixelMap_->GetPixelFormat()), ConvertToSkAlphaType(pixelMap_->GetAlphaType()));
    SkPixmap dstPixmap(dstImageInfo, dstPixels, pixelMap_->GetRowBytes());
    tempCache.readPixels(dstPixmap);
}
#else
void RosenRenderBox::DrawOnPixelMap()
{
    if (pixelMap_ == nullptr) {
        LOGE("pixelMap_ or clipLayer_ is nullptr.");
        return;
    }
    auto width = paintSize_.Width();
    auto height = paintSize_.Height();
    if (LessOrEqual(width, 0.0) || LessOrEqual(height, 0.0)) {
        LOGE("invalidate size.");
        return;
    }
    RSBitmap tempCache;
    RSBitmapFormat format { RSColorType::COLORTYPE_BGRA_8888, RSAlphaType::ALPHATYPE_OPAQUE };
    tempCache.Build(width, height, format);
    RSCanvas tempCanvas;
    tempCanvas.Bind(tempCache);

    uint8_t* dstPixels = const_cast<uint8_t*>(pixelMap_->GetPixels());
    if (dstPixels == nullptr) {
        LOGE("dstPixels is nullptr.");
        return;
    }
    RSBitmapFormat tempFormat { ConvertToColorType(pixelMap_->GetPixelFormat()),
        ConvertToAlphaType(pixelMap_->GetAlphaType()) };
    RSBitmap tempBitmap;
    tempBitmap.Build(pixelMap_->GetWidth(), pixelMap_->GetHeight(), tempFormat);
    tempBitmap.SetPixels(dstPixels);
    tempCache.CopyPixels(tempBitmap, 0, 0);
}
#endif

void RosenRenderBox::CalculateRepeatParam()
{
    if (backDecoration_) {
        RefPtr<BackgroundImage> backgroundImage = backDecoration_->GetImage();
        if (backgroundImage && renderImage_) {
            renderImage_->SetBgImageBoxPaintSize(paintSize_);
            renderImage_->SetBgImageBoxMarginOffset(margin_.GetOffset());
            LayoutParam param;
            param.SetFixedSize(paintSize_);
            renderImage_->Layout(param);
        }
    }
}

#ifndef USE_ROSEN_DRAWING
SkVector RosenRenderBox::GetSkRadii(const Radius& radius, double shrinkFactor, double borderWidth)
{
    SkVector fRadii;
    fRadii.set(SkDoubleToScalar(std::max(NormalizePercentToPx(radius.GetX(), false) - shrinkFactor * borderWidth, 0.0)),
        SkDoubleToScalar(std::max(NormalizePercentToPx(radius.GetY(), true) - shrinkFactor * borderWidth, 0.0)));
    return fRadii;
}
#else
RSPoint RosenRenderBox::GetRadii(const Radius& radius, double shrinkFactor, double borderWidth)
{
    return RSPoint(static_cast<RSScalar>(std::max(NormalizeToPx(radius.GetX()) - shrinkFactor * borderWidth, 0.0)),
        static_cast<RSScalar>(std::max(NormalizeToPx(radius.GetY()) - shrinkFactor * borderWidth, 0.0)));
}
#endif

bool RosenRenderBox::CheckBorderEdgeForRRect(const Border& border)
{
    double leftWidth = NormalizeToPx(border.Left().GetWidth());
    if (NearEqual(leftWidth, NormalizeToPx(border.Top().GetWidth())) &&
        NearEqual(leftWidth, NormalizeToPx(border.Right().GetWidth())) &&
        NearEqual(leftWidth, NormalizeToPx(border.Bottom().GetWidth()))) {
        BorderStyle leftStyle = border.Left().GetBorderStyle();
        return leftStyle == border.Top().GetBorderStyle() && leftStyle == border.Right().GetBorderStyle() &&
               leftStyle == border.Bottom().GetBorderStyle();
    }
    return false;
}

void RosenRenderBox::SyncGeometryProperties()
{
    auto rsNode = GetRSNode();
    if (!rsNode) {
        return;
    }
    Offset boundsOffset = GetPaintOffset() + margin_.GetOffset();
    Size boundsSize = paintSize_;
    rsNode->SetBounds(boundsOffset.GetX(), boundsOffset.GetY(), boundsSize.Width(), boundsSize.Height());
    if (IsTailRenderNode()) {
        Offset frameOffset = GetPaintOffset();
        Size frameSize = GetLayoutSize();
        rsNode->SetFrame(frameOffset.GetX(), frameOffset.GetY(), frameSize.Width(), frameSize.Height());
    }
}

#ifndef USE_ROSEN_DRAWING
SkRRect RosenRenderBox::GetBoxRRect(const Offset& offset, const Border& border, double shrinkFactor, bool isRound)
{
    SkRRect rRect;
    SkRect skRect {};
    SkVector fRadii[4] = { { 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 } };
    Size adjustedSize = GetPaintRect().GetSize() - (GetLayoutSize() - paintSize_);
    if (CheckBorderEdgeForRRect(border)) {
        BorderEdge borderEdge = border.Left();
        double borderWidth = NormalizeToPx(borderEdge.GetWidth());
        skRect.setXYWH(SkDoubleToScalar(offset.GetX() + shrinkFactor * borderWidth),
            SkDoubleToScalar(offset.GetY() + shrinkFactor * borderWidth),
            SkDoubleToScalar(adjustedSize.Width() - shrinkFactor * DOUBLE_WIDTH * borderWidth),
            SkDoubleToScalar(adjustedSize.Height() - shrinkFactor * DOUBLE_WIDTH * borderWidth));
        if (isRound) {
            fRadii[SkRRect::kUpperLeft_Corner] = GetSkRadii(border.TopLeftRadius(), shrinkFactor, borderWidth);
            fRadii[SkRRect::kUpperRight_Corner] = GetSkRadii(border.TopRightRadius(), shrinkFactor, borderWidth);
            fRadii[SkRRect::kLowerRight_Corner] = GetSkRadii(border.BottomRightRadius(), shrinkFactor, borderWidth);
            fRadii[SkRRect::kLowerLeft_Corner] = GetSkRadii(border.BottomLeftRadius(), shrinkFactor, borderWidth);
        }
    } else {
        float offsetX = SkDoubleToScalar(offset.GetX() + shrinkFactor * NormalizeToPx(border.Left().GetWidth()));
        float offsetY = SkDoubleToScalar(offset.GetY() + shrinkFactor * NormalizeToPx(border.Top().GetWidth()));
        float width = SkDoubleToScalar(
            adjustedSize.Width() - shrinkFactor * DOUBLE_WIDTH * NormalizeToPx(border.Right().GetWidth()));
        float height = SkDoubleToScalar(
            adjustedSize.Height() - shrinkFactor * DOUBLE_WIDTH * NormalizeToPx(border.Bottom().GetWidth()));
        skRect.setXYWH(offsetX, offsetY, width, height);
    }
    rRect.setRectRadii(skRect, fRadii);
    return rRect;
}
#else
RSRoundRect RosenRenderBox::GetBoxRRect(const Offset& offset, const Border& border, double shrinkFactor, bool isRound)
{
    RSRect drawingRect;
    std::vector<RSPoint> fRadii = { { 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 } };
    Size adjustedSize = GetPaintRect().GetSize() - (GetLayoutSize() - paintSize_);
    if (CheckBorderEdgeForRRect(border)) {
        BorderEdge borderEdge = border.Left();
        double borderWidth = NormalizeToPx(borderEdge.GetWidth());
        drawingRect = RSRect(
            static_cast<RSScalar>(offset.GetX() + shrinkFactor * borderWidth),
            static_cast<RSScalar>(offset.GetY() + shrinkFactor * borderWidth),
            static_cast<RSScalar>(adjustedSize.Width() - shrinkFactor * DOUBLE_WIDTH * borderWidth) +
            static_cast<RSScalar>(offset.GetX() + shrinkFactor * borderWidth),
            static_cast<RSScalar>(adjustedSize.Height() - shrinkFactor * DOUBLE_WIDTH * borderWidth) +
            static_cast<RSScalar>(offset.GetY() + shrinkFactor * borderWidth));
        if (isRound) {
            fRadii[RSRoundRect::TOP_LEFT_POS] = GetRadii(border.TopLeftRadius(), shrinkFactor, borderWidth);
            fRadii[RSRoundRect::TOP_RIGHT_POS] = GetRadii(border.TopRightRadius(), shrinkFactor, borderWidth);
            fRadii[RSRoundRect::BOTTOM_RIGHT_POS] = GetRadii(border.BottomRightRadius(), shrinkFactor, borderWidth);
            fRadii[RSRoundRect::BOTTOM_LEFT_POS] = GetRadii(border.BottomLeftRadius(), shrinkFactor, borderWidth);
        }
    } else {
        float offsetX = static_cast<RSScalar>(offset.GetX() + shrinkFactor * NormalizeToPx(border.Left().GetWidth()));
        float offsetY = static_cast<RSScalar>(offset.GetY() + shrinkFactor * NormalizeToPx(border.Top().GetWidth()));
        float width = static_cast<RSScalar>(
            adjustedSize.Width() - shrinkFactor * DOUBLE_WIDTH * NormalizeToPx(border.Right().GetWidth()));
        float height = static_cast<RSScalar>(
            adjustedSize.Height() - shrinkFactor * DOUBLE_WIDTH * NormalizeToPx(border.Bottom().GetWidth()));
        drawingRect = RSRect(offsetX, offsetY, width + offsetX, height + offsetY);
    }
    return RSRoundRect(drawingRect, fRadii);
}
#endif

bool RosenRenderBox::MaybeRelease()
{
    auto context = GetContext().Upgrade();
    if (context && context->GetRenderFactory() && context->GetRenderFactory()->GetRenderBoxFactory()->Recycle(this)) {
        ClearRenderObject();
        return false;
    }
    return true;
}

#ifndef USE_ROSEN_DRAWING
void RosenRenderBox::UpdateBlurRRect(const SkRRect& rRect, const Offset& offset)
{
    SkVector radius = rRect.radii(SkRRect::kUpperLeft_Corner);
    const SkRect& rect = rRect.rect();
    windowBlurRRect_.SetRectWithSimpleRadius(
        Rect(rect.left(), rect.top(), rect.width(), rect.height()), radius.fX, radius.fY);
    // this is relative offset
    Rect innerRect = windowBlurRRect_.GetRect();
    innerRect -= offset;
    windowBlurRRect_.SetRect(innerRect);
}
#else
void RosenRenderBox::UpdateBlurRRect(const RSRoundRect& rRect, const Offset& offset)
{
    RSPoint radius = rRect.GetCornerRadius(RSRoundRect::TOP_LEFT_POS);
    const RSRect& rect = rRect.GetRect();
    windowBlurRRect_.SetRectWithSimpleRadius(
        Rect(rect.GetLeft(), rect.GetTop(), rect.GetWidth(), rect.GetHeight()), radius.GetX(), radius.GetY());
    // this is relative offset
    Rect innerRect = windowBlurRRect_.GetRect();
    innerRect -= offset;
    windowBlurRRect_.SetRect(innerRect);
}
#endif

#ifndef USE_ROSEN_DRAWING
bool RosenRenderBox::CreateSkPath(const RefPtr<BasicShape>& basicShape, GeometryBoxType geometryBoxType, SkPath* skPath)
{
    Size size;
    Offset position;
    GetSizeAndPosition(geometryBoxType, size, position);
    if (basicShape == nullptr || basicShape->GetBasicShapeType() == BasicShapeType::NONE) {
        skPath->addRect(SkRect::MakeXYWH(position.GetX(), position.GetY(), size.Width(), size.Height()));
        return true;
    }
    bool ret = false;
    switch (basicShape->GetBasicShapeType()) {
        case BasicShapeType::INSET: {
            ret = CreateInset(basicShape, size, position, skPath);
            break;
        }
        case BasicShapeType::CIRCLE: {
            ret = CreateCircle(basicShape, size, position, skPath);
            break;
        }
        case BasicShapeType::ELLIPSE: {
            ret = CreateEllipse(basicShape, size, position, skPath);
            break;
        }
        case BasicShapeType::POLYGON: {
            ret = CreatePolygon(basicShape, size, position, skPath);
            break;
        }
        case BasicShapeType::PATH: {
            ret = CreatePath(basicShape, size, position, skPath);
            break;
        }
        case BasicShapeType::RECT: {
            ret = CreateRect(basicShape, size, position, skPath);
            break;
        }
        default: {
            LOGE("invalid BasicShapeType");
            ret = false;
            break;
        }
    }
    return ret;
}
#else
bool RosenRenderBox::CreatePath(
    const RefPtr<BasicShape>& basicShape, GeometryBoxType geometryBoxType, RSPath* drawingPath)
{
    Size size;
    Offset position;
    GetSizeAndPosition(geometryBoxType, size, position);
    if (basicShape == nullptr || basicShape->GetBasicShapeType() == BasicShapeType::NONE) {
        drawingPath->AddRect(RSRect(position.GetX(), position.GetY(),
            size.Width() + position.GetX(), size.Height() + position.GetY()));
        return true;
    }
    bool ret = false;
    switch (basicShape->GetBasicShapeType()) {
        case BasicShapeType::INSET: {
            ret = CreateInset(basicShape, size, position, drawingPath);
            break;
        }
        case BasicShapeType::CIRCLE: {
            ret = CreateCircle(basicShape, size, position, drawingPath);
            break;
        }
        case BasicShapeType::ELLIPSE: {
            ret = CreateEllipse(basicShape, size, position, drawingPath);
            break;
        }
        case BasicShapeType::POLYGON: {
            ret = CreatePolygon(basicShape, size, position, drawingPath);
            break;
        }
        case BasicShapeType::PATH: {
            ret = CreatePath(basicShape, size, position, drawingPath);
            break;
        }
        case BasicShapeType::RECT: {
            ret = CreateRect(basicShape, size, position, drawingPath);
            break;
        }
        default: {
            LOGE("invalid BasicShapeType");
            ret = false;
            break;
        }
    }
    return ret;
}
#endif

#ifndef USE_ROSEN_DRAWING
bool RosenRenderBox::CreateInset(
    const RefPtr<BasicShape>& basicShape, const Size& size, const Offset& position, SkPath* skPath)
#else
bool RosenRenderBox::CreateInset(
    const RefPtr<BasicShape>& basicShape, const Size& size, const Offset& position, RSPath* drawingPath)
#endif
{
    const auto& inset = AceType::DynamicCast<Inset>(basicShape);
    if (!inset) {
        LOGE("inset is null");
        return false;
    }
    double left = DimensionToPx(inset->GetLeft(), size, LengthMode::HORIZONTAL) + position.GetX();
    double top = DimensionToPx(inset->GetTop(), size, LengthMode::VERTICAL) + position.GetY();
    double right = size.Width() - DimensionToPx(inset->GetRight(), size, LengthMode::HORIZONTAL) + position.GetX();
    double bottom = size.Height() - DimensionToPx(inset->GetBottom(), size, LengthMode::VERTICAL) + position.GetY();
#ifndef USE_ROSEN_DRAWING
    SkRect rect = SkRect::MakeLTRB(left, top, right, bottom);
    auto radiusSize = Size(std::abs(rect.width()), std::abs(rect.height()));
#else
    RSRect rect = RSRect(left, top, right, bottom);
    auto radiusSize = Size(std::abs(rect.GetWidth()), std::abs(rect.GetHeight()));
#endif
    float topLeftRadiusX = DimensionToPx(inset->GetTopLeftRadius().GetX(), radiusSize, LengthMode::HORIZONTAL);
    float topLeftRadiusY = DimensionToPx(inset->GetTopLeftRadius().GetY(), radiusSize, LengthMode::VERTICAL);
    float topRightRadiusX = DimensionToPx(inset->GetTopRightRadius().GetX(), radiusSize, LengthMode::HORIZONTAL);
    float topRightRadiusY = DimensionToPx(inset->GetTopRightRadius().GetY(), radiusSize, LengthMode::VERTICAL);
    float bottomRightRadiusX = DimensionToPx(inset->GetBottomRightRadius().GetX(), radiusSize, LengthMode::HORIZONTAL);
    float bottomRightRadiusY = DimensionToPx(inset->GetBottomRightRadius().GetY(), radiusSize, LengthMode::VERTICAL);
    float bottomLeftRadiusX = DimensionToPx(inset->GetBottomLeftRadius().GetX(), radiusSize, LengthMode::HORIZONTAL);
    float bottomLeftRadiusY = DimensionToPx(inset->GetBottomLeftRadius().GetY(), radiusSize, LengthMode::VERTICAL);
#ifndef USE_ROSEN_DRAWING
    const SkVector fRadii[4] = { { topLeftRadiusX, topLeftRadiusY }, { topRightRadiusX, topRightRadiusY },
        { bottomRightRadiusX, bottomRightRadiusY }, { bottomLeftRadiusX, bottomLeftRadiusY } };
    SkRRect roundRect;
    roundRect.setRectRadii(rect, fRadii);
    skPath->addRRect(roundRect);
#else
    std::vector<RSPoint> fRadii;
    fRadii.push_back(RSPoint(topLeftRadiusX, topLeftRadiusY));
    fRadii.push_back(RSPoint(topRightRadiusX, topRightRadiusY));
    fRadii.push_back(RSPoint(bottomRightRadiusX, bottomRightRadiusY));
    fRadii.push_back(RSPoint(bottomLeftRadiusX, bottomLeftRadiusY));
    RSRoundRect roundRect(rect, fRadii);
    drawingPath->AddRoundRect(roundRect);
#endif
    return true;
}

#ifndef USE_ROSEN_DRAWING
bool RosenRenderBox::CreateCircle(
    const RefPtr<BasicShape>& basicShape, const Size& size, const Offset& position, SkPath* skPath)
#else
bool RosenRenderBox::CreateCircle(
    const RefPtr<BasicShape>& basicShape, const Size& size, const Offset& position, RSPath* drawingPath)
#endif
{
    const auto& circle = AceType::DynamicCast<Circle>(basicShape);
    if (!circle) {
        LOGE("circle is null");
        return false;
    }
    if (circle->GetRadius().IsValid()) {
#ifndef USE_ROSEN_DRAWING
        skPath->addCircle(DimensionToPx(circle->GetAxisX(), size, LengthMode::HORIZONTAL) + position.GetX(),
#else
        drawingPath->AddCircle(DimensionToPx(circle->GetAxisX(), size, LengthMode::HORIZONTAL) + position.GetX(),
#endif
            DimensionToPx(circle->GetAxisY(), size, LengthMode::VERTICAL) + position.GetY(),
            DimensionToPx(circle->GetRadius(), size, LengthMode::OTHER));
    } else {
        float width = DimensionToPx(circle->GetWidth(), size, LengthMode::HORIZONTAL);
        float height = DimensionToPx(circle->GetHeight(), size, LengthMode::VERTICAL);
        float offsetX = DimensionToPx(circle->GetOffset().GetX(), size, LengthMode::HORIZONTAL) + position.GetX();
        float offsetY = DimensionToPx(circle->GetOffset().GetY(), size, LengthMode::VERTICAL) + position.GetY();
#ifndef USE_ROSEN_DRAWING
        skPath->addCircle(width * 0.5 + offsetX, height * 0.5 + offsetY, std::min(width, height) * 0.5);
#else
        drawingPath->AddCircle(width * 0.5 + offsetX, height * 0.5 + offsetY, std::min(width, height) * 0.5);
#endif
    }

    return true;
}

#ifndef USE_ROSEN_DRAWING
bool RosenRenderBox::CreateEllipse(
    const RefPtr<BasicShape>& basicShape, const Size& size, const Offset& position, SkPath* skPath)
#else
bool RosenRenderBox::CreateEllipse(
    const RefPtr<BasicShape>& basicShape, const Size& size, const Offset& position, RSPath* drawingPath)
#endif
{
    const auto& ellipse = AceType::DynamicCast<Ellipse>(basicShape);
    if (!ellipse) {
        LOGE("ellipse is null");
        return false;
    }
    if (ellipse->GetRadiusX().IsValid()) {
        float rx = DimensionToPx(ellipse->GetRadiusX(), size, LengthMode::HORIZONTAL);
        float ry = DimensionToPx(ellipse->GetRadiusY(), size, LengthMode::VERTICAL);
        double x = DimensionToPx(ellipse->GetAxisX(), size, LengthMode::HORIZONTAL) + position.GetX() - rx;
        double y = DimensionToPx(ellipse->GetAxisY(), size, LengthMode::VERTICAL) + position.GetY() - ry;
#ifndef USE_ROSEN_DRAWING
        SkRect rect = SkRect::MakeXYWH(x, y, rx + rx, ry + ry);
        skPath->addOval(rect);
#else
        RSRect rect = RSRect(x, y, rx + rx + x, ry + ry + y);
        drawingPath->AddOval(rect);
#endif
    } else {
        auto width = DimensionToPx(ellipse->GetWidth(), size, LengthMode::HORIZONTAL);
        auto height = DimensionToPx(ellipse->GetHeight(), size, LengthMode::VERTICAL);
        float x = DimensionToPx(ellipse->GetOffset().GetX(), size, LengthMode::HORIZONTAL) + position.GetX();
        float y = DimensionToPx(ellipse->GetOffset().GetY(), size, LengthMode::VERTICAL) + position.GetY();
#ifndef USE_ROSEN_DRAWING
        SkRect rect = SkRect::MakeXYWH(x, y, width, height);
        skPath->addOval(rect);
#else
        RSRect rect = RSRect(x, y, width + x, height + y);
        drawingPath->AddOval(rect);
#endif
    }
    return true;
}

#ifndef USE_ROSEN_DRAWING
bool RosenRenderBox::CreatePolygon(
    const RefPtr<BasicShape>& basicShape, const Size& size, const Offset& position, SkPath* skPath)
{
    const auto& polygon = AceType::DynamicCast<Polygon>(basicShape);
    if (!polygon) {
        LOGE("polygon is null");
        return false;
    }
    std::vector<SkPoint> skPoints;
    for (auto [x, y] : polygon->GetPoints()) {
        skPoints.emplace_back(SkPoint::Make(DimensionToPx(x, size, LengthMode::HORIZONTAL) + position.GetX(),
            DimensionToPx(y, size, LengthMode::VERTICAL) + position.GetX()));
    }
    if (skPoints.empty()) {
        LOGW("points is null");
        return false;
    }
    skPath->addPoly(&skPoints[0], skPoints.size(), true);
    return true;
}
#else
bool RosenRenderBox::CreatePolygon(
    const RefPtr<BasicShape>& basicShape, const Size& size, const Offset& position, RSPath* drawingPath)
{
    const auto& polygon = AceType::DynamicCast<Polygon>(basicShape);
    if (!polygon) {
        LOGE("polygon is null");
        return false;
    }
    std::vector<RSPoint> drawingPoints;
    for (auto [x, y] : polygon->GetPoints()) {
        drawingPoints.emplace_back(RSPoint(DimensionToPx(x, size, LengthMode::HORIZONTAL) + position.GetX(),
            DimensionToPx(y, size, LengthMode::VERTICAL) + position.GetX()));
    }
    if (drawingPoints.empty()) {
        LOGW("points is null");
        return false;
    }
    drawingPath->AddPoly(drawingPoints, drawingPoints.size(), true);
    return true;
}
#endif

#ifndef USE_ROSEN_DRAWING
bool RosenRenderBox::CreatePath(
    const RefPtr<BasicShape>& basicShape, const Size& size, const Offset& position, SkPath* skPath)
#else
bool RosenRenderBox::CreatePath(
    const RefPtr<BasicShape>& basicShape, const Size& size, const Offset& position, RSPath* drawingPath)
#endif
{
    const auto& path = AceType::DynamicCast<Path>(basicShape);
    if (!path) {
        LOGE("path is null");
        return false;
    }
    if (path->GetValue().empty()) {
        LOGW("path value is null");
        return false;
    }
#ifndef USE_ROSEN_DRAWING
    SkPath tmpPath;
    bool ret = SkParsePath::FromSVGString(path->GetValue().c_str(), &tmpPath);
#else
    RSRecordingPath tmpPath;
    bool ret = tmpPath.BuildFromSVGString(path->GetValue());
#endif
    if (!ret) {
        LOGW("path value is invalid");
        return false;
    }
    float offsetX = DimensionToPx(path->GetOffset().GetX(), size, LengthMode::HORIZONTAL) + position.GetX();
    float offsetY = DimensionToPx(path->GetOffset().GetY(), size, LengthMode::VERTICAL) + position.GetY();
#ifndef USE_ROSEN_DRAWING
    skPath->addPath(tmpPath, offsetX, offsetY);
#else
    drawingPath->AddPath(tmpPath, offsetX, offsetY);
#endif
    return true;
}

#ifndef USE_ROSEN_DRAWING
bool RosenRenderBox::CreateRect(
    const RefPtr<BasicShape>& basicShape, const Size& size, const Offset& position, SkPath* skPath)
#else
bool RosenRenderBox::CreateRect(
    const RefPtr<BasicShape>& basicShape, const Size& size, const Offset& position, RSPath* drawingPath)
#endif
{
    const auto& rect = AceType::DynamicCast<ShapeRect>(basicShape);
    if (!rect) {
        LOGE("rect is null");
        return false;
    }
    double left = DimensionToPx(rect->GetOffset().GetX(), size, LengthMode::HORIZONTAL) + position.GetX();
    double top = DimensionToPx(rect->GetOffset().GetY(), size, LengthMode::VERTICAL) + position.GetY();
    double width = DimensionToPx(rect->GetWidth(), size, LengthMode::HORIZONTAL);
    double height = DimensionToPx(rect->GetHeight(), size, LengthMode::VERTICAL);
#ifndef USE_ROSEN_DRAWING
    SkRect skRect = SkRect::MakeXYWH(left, top, width, height);
#else
    RSRect drawingRect = RSRect(left, top, width + left, height + top);
#endif
    auto radiusSize = Size(width, height);
    float topLeftRadiusX = GetFloatRadiusValue(
        rect->GetTopLeftRadius().GetX(), rect->GetTopLeftRadius().GetY(), radiusSize, LengthMode::HORIZONTAL);
    float topLeftRadiusY = GetFloatRadiusValue(
        rect->GetTopLeftRadius().GetY(), rect->GetTopLeftRadius().GetX(), radiusSize, LengthMode::VERTICAL);
    float topRightRadiusX = GetFloatRadiusValue(
        rect->GetTopRightRadius().GetX(), rect->GetTopRightRadius().GetY(), radiusSize, LengthMode::HORIZONTAL);
    float topRightRadiusY = GetFloatRadiusValue(
        rect->GetTopRightRadius().GetY(), rect->GetTopRightRadius().GetX(), radiusSize, LengthMode::VERTICAL);
    float bottomRightRadiusX = GetFloatRadiusValue(
        rect->GetBottomRightRadius().GetX(), rect->GetBottomRightRadius().GetY(), radiusSize, LengthMode::HORIZONTAL);
    float bottomRightRadiusY = GetFloatRadiusValue(
        rect->GetBottomRightRadius().GetY(), rect->GetBottomRightRadius().GetX(), radiusSize, LengthMode::VERTICAL);
    float bottomLeftRadiusX = GetFloatRadiusValue(
        rect->GetBottomLeftRadius().GetX(), rect->GetBottomLeftRadius().GetY(), radiusSize, LengthMode::HORIZONTAL);
    float bottomLeftRadiusY = GetFloatRadiusValue(
        rect->GetBottomLeftRadius().GetY(), rect->GetBottomLeftRadius().GetX(), radiusSize, LengthMode::VERTICAL);
#ifndef USE_ROSEN_DRAWING
    const SkVector fRadii[4] = { { topLeftRadiusX, topLeftRadiusY }, { topRightRadiusX, topRightRadiusY },
        { bottomRightRadiusX, bottomRightRadiusY }, { bottomLeftRadiusX, bottomLeftRadiusY } };
    SkRRect roundRect;
    roundRect.setRectRadii(skRect, fRadii);
    skPath->addRRect(roundRect);
#else
    std::vector<RSPoint> fRadii;
    fRadii.push_back(RSPoint(topLeftRadiusX, topLeftRadiusY));
    fRadii.push_back(RSPoint(topRightRadiusX, topRightRadiusY));
    fRadii.push_back(RSPoint(bottomRightRadiusX, bottomRightRadiusY));
    fRadii.push_back(RSPoint(bottomLeftRadiusX, bottomLeftRadiusY));
    RSRoundRect roundRect(drawingRect, fRadii);
    drawingPath->AddRoundRect(roundRect);
#endif
    return true;
}

float RosenRenderBox::GetFloatRadiusValue(
    const Dimension& src, const Dimension& dest, const Size& size, LengthMode type)
{
    if (src.Value() < 0.0 && dest.Value() > 0.0) {
        return DimensionToPx(dest, size, type);
    }
    return DimensionToPx(src, size, type);
}

void RosenRenderBox::GetSizeAndPosition(GeometryBoxType geometryBoxType, Size& size, Offset& position)
{
    switch (geometryBoxType) {
        case GeometryBoxType::BORDER_BOX:
            size = GetPaintSize();
            position = GetPaintPosition();
            break;
        case GeometryBoxType::MARGIN_BOX:
            size = GetLayoutSize();
            position = Offset();
            break;
        case GeometryBoxType::PADDING_BOX:
            size = GetPaintSize() - GetBorderSize();
            position = GetPaintPosition() + GetBorderOffset();
            break;
        case GeometryBoxType::CONTENT_BOX:
            size = GetPaintSize() - GetBorderSize() - GetPaddingSize();
            position = GetPaintPosition() + GetBorderOffset() + padding_.GetOffset();
            break;
        default:
            size = GetPaintSize();
            position = GetPaintPosition();
            break;
    }
}

#ifndef USE_ROSEN_DRAWING
float RosenRenderBox::DimensionToPx(const Dimension& value, const Size& size, LengthMode type) const
{
    switch (value.Unit()) {
        case DimensionUnit::PERCENT: {
            if (type == LengthMode::HORIZONTAL) {
                return SkDoubleToScalar(value.Value() * size.Width());
            }
            if (type == LengthMode::VERTICAL) {
                return SkDoubleToScalar(value.Value() * size.Height());
            }
            if (type == LengthMode::OTHER) {
                return SkDoubleToScalar(value.Value() * sqrt(size.Width() * size.Height()));
            }
            return 0.0f;
        }
        case DimensionUnit::PX:
            return SkDoubleToScalar(value.Value());
        default:
            return SkDoubleToScalar(NormalizeToPx(value));
    }
}
#else
float RosenRenderBox::DimensionToPx(const Dimension& value, const Size& size, LengthMode type) const
{
    switch (value.Unit()) {
        case DimensionUnit::PERCENT: {
            if (type == LengthMode::HORIZONTAL) {
                return static_cast<RSScalar>(value.Value() * size.Width());
            }
            if (type == LengthMode::VERTICAL) {
                return static_cast<RSScalar>(value.Value() * size.Height());
            }
            if (type == LengthMode::OTHER) {
                return static_cast<RSScalar>(value.Value() * sqrt(size.Width() * size.Height()));
            }
            return 0.0f;
        }
        case DimensionUnit::PX:
            return static_cast<RSScalar>(value.Value());
        default:
            return static_cast<RSScalar>(NormalizeToPx(value));
    }
}
#endif

void RosenRenderBox::CalculateAlignDeclaration()
{
    RenderBox::CalculateAlignDeclaration();
    auto rsNode = GetRSNode();
    if (rsNode && isUseAlign_) {
        rsNode->SetTranslate({ alignOffset_.GetX(), alignOffset_.GetY() });
    }
}

void RosenRenderBox::SetWidth(double width)
{
    RenderBoxBase::SetWidth(width);
    auto& rsNode = GetRSNode();
    if (rsNode == nullptr) {
        LOGE("set width to rsNode failed, rsNode is null");
        return;
    }
    rsNode->SetBoundsWidth(GetBoundsWidth());
}

void RosenRenderBox::SetHeight(double height)
{
    RenderBoxBase::SetHeight(height);
    auto& rsNode = GetRSNode();
    if (rsNode == nullptr) {
        LOGE("set height to rsNode failed, rsNode is null");
        return;
    }
    rsNode->SetBoundsHeight(GetBoundsHeight());
}

void RosenRenderBox::SetWidth(const Dimension& width)
{
    RenderBoxBase::SetWidth(width);
    auto& rsNode = GetRSNode();
    if (rsNode == nullptr) {
        LOGE("set dimension width to rsNode failed, rsNode is null");
        return;
    }
    rsNode->SetBoundsWidth(GetBoundsWidth());
}

void RosenRenderBox::SetHeight(const Dimension& height)
{
    RenderBoxBase::SetHeight(height);
    auto& rsNode = GetRSNode();
    if (rsNode == nullptr) {
        LOGE("set dimension height to rsNode failed, rsNode is null");
        return;
    }
    rsNode->SetBoundsHeight(GetBoundsHeight());
}

void RosenRenderBox::SetColor(const Color& color, bool isBackground)
{
    RenderBox::SetColor(color, isBackground);
    auto& rsNode = GetRSNode();
    if (rsNode == nullptr) {
        LOGE("set color to rsNode failed, rsNode is null");
        return;
    }
    if (isBackground) {
        rsNode->SetBackgroundColor(color.GetValue());
    } else {
        rsNode->SetForegroundColor(color.GetValue());
    }
}

void RosenRenderBox::SetBackgroundSize(const BackgroundImageSize& size)
{
    RenderBox::SetBackgroundSize(size);
    auto& rsNode = GetRSNode();
    if (rsNode == nullptr) {
        LOGE("set background size to rsNode failed, rsNode is null");
        return;
    }
    rsNode->SetBgImageWidth(size.GetSizeValueX());
    rsNode->SetBgImageHeight(size.GetSizeValueY());
}

void RosenRenderBox::SetBackgroundPosition(const BackgroundImagePosition& position)
{
    RenderBox::SetBackgroundPosition(position);
    auto& rsNode = GetRSNode();
    if (rsNode == nullptr) {
        LOGE("set background position to rsNode failed, rsNode is null");
        return;
    }
    if (position.GetSizeTypeX() == BackgroundImagePositionType::PX) {
        rsNode->SetBgImagePositionX(position.GetSizeValueX());
    } else {
        rsNode->SetBgImagePositionX(position.GetSizeValueX() *
                                    (paintSize_.Width() - rsNode->GetStagingProperties().GetBgImageWidth()) /
                                    PERCENT_TRANSLATE);
    }
    if (position.GetSizeTypeX() == BackgroundImagePositionType::PX) {
        rsNode->SetBgImagePositionX(position.GetSizeValueX());
    } else {
        rsNode->SetBgImagePositionY(position.GetSizeValueY() *
                                    (paintSize_.Height() - rsNode->GetStagingProperties().GetBgImageHeight()) /
                                    PERCENT_TRANSLATE);
    }
}

void RosenRenderBox::SetShadow(const Shadow& shadow)
{
    RenderBox::SetShadow(shadow);
    auto& rsNode = GetRSNode();
    if (rsNode == nullptr) {
        LOGE("set shadow to rsNode failed, rsNode is null");
        return;
    }
    rsNode->SetShadowRadius(shadow.GetBlurRadius());
    rsNode->SetShadowColor(shadow.GetColor().GetValue());
    rsNode->SetShadowOffsetX(shadow.GetOffset().GetX());
    rsNode->SetShadowOffsetY(shadow.GetOffset().GetY());
    rsNode->SetShadowMask(shadow.GetShadowType() == ShadowType::BLUR);
}

void RosenRenderBox::SetBorderWidth(double width, const BorderEdgeHelper& helper)
{
    RenderBox::SetBorderWidth(width, helper);
    auto& rsNode = GetRSNode();
    if (rsNode == nullptr) {
        LOGE("set border width to rsNode failed, rsNode is null");
        return;
    }
    rsNode->SetBorderWidth(width);
}

void RosenRenderBox::SetBorderColor(const Color& color, const BorderEdgeHelper& helper)
{
    RenderBox::SetBorderColor(color, helper);
    auto& rsNode = GetRSNode();
    if (rsNode == nullptr) {
        LOGE("set border color to rsNode failed, rsNode is null");
        return;
    }
    rsNode->SetBorderColor(color.GetValue());
}

void RosenRenderBox::SetBorderStyle(BorderStyle borderStyle, const BorderEdgeHelper& helper)
{
    RenderBox::SetBorderStyle(borderStyle, helper);
    auto& rsNode = GetRSNode();
    if (rsNode == nullptr) {
        LOGE("set border style to rsNode failed, rsNode is null");
        return;
    }
    rsNode->SetBorderStyle(static_cast<uint32_t>(borderStyle));
}

void RosenRenderBox::SetBorderRadius(double radius, const BorderRadiusHelper& helper)
{
    RenderBox::SetBorderRadius(radius, helper);
    auto& rsNode = GetRSNode();
    if (rsNode == nullptr) {
        LOGE("set border radius to rsNode failed, rsNode is null");
        return;
    }
    rsNode->SetCornerRadius(radius);
}

void RosenRenderBox::SetBlurRadius(const AnimatableDimension& radius)
{
    RenderBox::SetBlurRadius(radius);
    auto& rsNode = GetRSNode();
    if (rsNode == nullptr) {
        LOGE("set blur radius to rsNode failed, rsNode is null");
        return;
    }
    rsNode->SetFilter(Rosen::RSFilter::CreateBlurFilter(radius.Value(), radius.Value()));
}

void RosenRenderBox::SetBackdropRadius(const AnimatableDimension& radius)
{
    RenderBox::SetBackdropRadius(radius);
    auto& rsNode = GetRSNode();
    if (rsNode == nullptr) {
        LOGE("set backdrop radius to rsNode failed, rsNode is null");
        return;
    }
    rsNode->SetBackgroundFilter(Rosen::RSFilter::CreateBlurFilter(radius.Value(), radius.Value()));
}

void RosenRenderBox::SetWindowBlurProgress(double progress)
{
    RenderBox::SetWindowBlurProgress(progress);
}

double RosenRenderBox::GetBoundsWidth()
{
    return ConvertHorizontalDimensionToPx(GetWidthDimension(), false);
}

double RosenRenderBox::GetBoundsHeight()
{
    return ConvertVerticalDimensionToPx(GetHeightDimension(), false);
}

void RosenRenderBox::SyncDecorationToRSNode()
{
    auto rsNode = GetRSNode();
    if (!rsNode) {
        return;
    }
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    dipScale_ = context->GetDipScale();
    Border border;
    Rosen::Vector4f cornerRadius;
    std::shared_ptr<Rosen::RSFilter> backFilter = nullptr;
    std::shared_ptr<Rosen::RSFilter> filter = nullptr;
    if (backDecoration_) {
        if (backDecoration_->GetBorder().HasValue()) {
            border = backDecoration_->GetBorder();
        }
        if (backDecoration_->GetBorder().HasRadius()) {
            cornerRadius.SetValues(NormalizePercentToPx(backDecoration_->GetBorder().TopLeftRadius().GetX(), false),
                NormalizePercentToPx(backDecoration_->GetBorder().TopRightRadius().GetX(), false),
                NormalizePercentToPx(backDecoration_->GetBorder().BottomRightRadius().GetX(), false),
                NormalizePercentToPx(backDecoration_->GetBorder().BottomLeftRadius().GetX(), false));
        }
        RosenDecorationPainter::PaintBoxShadows(backDecoration_->GetShadows(), rsNode);
        auto rosenBlurStyleValue = GetRosenBlurStyleValue(backDecoration_->GetBlurStyle());
        if (rosenBlurStyleValue != MATERIAL_BLUR_STYLE::NO_MATERIAL) {
            backFilter = Rosen::RSFilter::CreateMaterialFilter(static_cast<int>(rosenBlurStyleValue),
                static_cast<float>(dipScale_),
                static_cast<Rosen::BLUR_COLOR_MODE>(backDecoration_->GetBlurStyle().adaptiveColor));
        }
        if (backDecoration_->GetBlurRadius().IsValid()) {
            float radius = NormalizeToPx(backDecoration_->GetBlurRadius());
            float backblurRadius = RosenDecorationPainter::ConvertRadiusToSigma(radius);
            backFilter = Rosen::RSFilter::CreateBlurFilter(backblurRadius, backblurRadius);
        }
    }
    if (frontDecoration_) {
        if (frontDecoration_->GetBorder().HasValue()) {
            border = frontDecoration_->GetBorder();
        }
        if (frontDecoration_->GetBorder().HasRadius()) {
            cornerRadius.SetValues(NormalizePercentToPx(frontDecoration_->GetBorder().TopLeftRadius().GetX(), false),
                NormalizePercentToPx(frontDecoration_->GetBorder().TopRightRadius().GetX(), false),
                NormalizePercentToPx(frontDecoration_->GetBorder().BottomRightRadius().GetX(), false),
                NormalizePercentToPx(frontDecoration_->GetBorder().BottomLeftRadius().GetX(), false));
        }
        if (frontDecoration_->GetBlurRadius().IsValid()) {
            float radius = NormalizeToPx(frontDecoration_->GetBlurRadius());
            float frontblurRadius = RosenDecorationPainter::ConvertRadiusToSigma(radius);
            filter = Rosen::RSFilter::CreateBlurFilter(frontblurRadius, frontblurRadius);
        }
    }
    RosenDecorationPainter::PaintBorder(rsNode, border, dipScale_);
    rsNode->SetCornerRadius(cornerRadius);
    rsNode->SetBackgroundColor(backDecoration_ ? backDecoration_->GetBackgroundColor().GetValue() : 0);
    rsNode->SetForegroundColor(frontDecoration_ ? frontDecoration_->GetBackgroundColor().GetValue() : 0);
    rsNode->SetBackgroundFilter(backFilter);
    rsNode->SetFilter(filter);
    if (GetNeedMaterial() && Rosen::RSSystemProperties::GetUniRenderEnabled()) {
        backFilter = Rosen::RSFilter::CreateMaterialFilter(
            static_cast<int>(MATERIAL_BLUR_STYLE::STYLE_CARD_THICK_LIGHT), dipScale_);
        rsNode->SetBackgroundFilter(backFilter);
        rsNode->SetBackgroundColor(0x00000000);
    }
}

void RosenRenderBox::OnAttachContext()
{
    if (!backDecoration_) {
        backDecoration_ = AceType::MakeRefPtr<Decoration>();
    }
    backDecoration_->SetContextAndCallback(context_, [weak = WeakClaim(this)] {
        if (auto renderBox = weak.Upgrade()) {
            renderBox->SyncDecorationToRSNode();
            renderBox->OnAnimationCallback();
        }
    });
    if (!frontDecoration_) {
        frontDecoration_ = AceType::MakeRefPtr<Decoration>();
    }
    frontDecoration_->SetContextAndCallback(context_, [weak = WeakClaim(this)] {
        auto renderBox = weak.Upgrade();
        if (renderBox) {
            renderBox->SyncDecorationToRSNode();
            renderBox->OnAnimationCallback();
        }
    });
    width_.SetContextAndCallback(context_, [weak = WeakClaim(this)] {
        if (auto renderBox = weak.Upgrade()) {
            renderBox->OnAnimationCallback();
        }
    });
    height_.SetContextAndCallback(context_, [weak = WeakClaim(this)] {
        if (auto renderBox = weak.Upgrade()) {
            renderBox->OnAnimationCallback();
        }
    });
    marginOrigin_.SetContextAndCallback(context_, [weak = WeakClaim(this)] {
        auto renderBox = weak.Upgrade();
        if (renderBox) {
            renderBox->OnAnimationCallback();
        }
    });
    paddingOrigin_.SetContextAndCallback(context_, [weak = WeakClaim(this)] {
        auto renderBox = weak.Upgrade();
        if (renderBox) {
            renderBox->OnAnimationCallback();
        }
    });
    aspectRatio_.SetContextAndCallback(context_, [weak = WeakClaim(this)] {
        auto renderBox = weak.Upgrade();
        if (renderBox) {
            renderBox->OnAnimationCallback();
        }
    });
}

std::shared_ptr<Rosen::RSUIContext> RosenRenderBox::GetUIContext(const RefPtr<PipelineContext>& context)
{
    CHECK_NULL_RETURN(context, nullptr);
    auto rsUIDirector = context->GetRSUIDirector();
    CHECK_NULL_RETURN(rsUIDirector, nullptr);
    return rsUIDirector->GetRSUIContext();
}

void RosenRenderBox::AnimateMouseHoverEnter()
{
    if (hoverAnimationType_ == HoverAnimationType::SCALE) {
        auto rsNode = GetRSNode();
        if (!rsNode) {
            return;
        }
        float scaleBegin = SCALE_DEFAULT;
        float scaleEnd = SCALE_CHANGED;

        rsNode->SetScale(scaleBegin);
        Rosen::RSAnimationTimingProtocol protocol;
        protocol.SetDuration(HOVER_ANIMATION_DURATION);
        auto pipeline = context_.Upgrade();
        auto rsUIContext = GetUIContext(pipeline);
        RSNode::Animate(rsUIContext,
            protocol, SCALE_ANIMATION_TIMING_CURVE, [rsNode, scaleEnd]() {
            if (rsNode) {
                rsNode->SetScale(scaleEnd);
            }
        });
        isHoveredScale_ = true;
    } else if (hoverAnimationType_ == HoverAnimationType::BOARD) {
        ResetController(controllerExit_);
        if (!controllerEnter_) {
            controllerEnter_ = CREATE_ANIMATOR(context_);
        }
        if (!backDecoration_) {
            backDecoration_ = AceType::MakeRefPtr<Decoration>();
        }
        if (!colorAnimationEnter_) {
            colorAnimationEnter_ = AceType::MakeRefPtr<KeyframeAnimation<Color>>();
        }
        CreateColorAnimation(colorAnimationEnter_, hoverColorBegin_, BOARD_CHANGED);
        controllerEnter_->ClearInterpolators();
        controllerEnter_->AddInterpolator(colorAnimationEnter_);
        controllerEnter_->SetDuration(HOVER_ANIMATION_DURATION);
        controllerEnter_->SetFillMode(FillMode::FORWARDS);
        controllerEnter_->Play();
        isHoveredBoard_ = true;
    } else {
        return;
    }
}

void RosenRenderBox::AnimateMouseHoverExit()
{
    LOGI("RosenRenderBox::AnimateMouseHoverExit in. hoverAnimationType_ = %{public}d", hoverAnimationType_);
    if (hoverAnimationType_ == HoverAnimationType::SCALE || isHoveredScale_) {
        auto rsNode = GetRSNode();
        float scaleBegin = SCALE_CHANGED;
        float scaleEnd = SCALE_DEFAULT;

        if (rsNode) {
            rsNode->SetScale(scaleBegin);
        }
        Rosen::RSAnimationTimingProtocol protocol;
        protocol.SetDuration(HOVER_ANIMATION_DURATION);
        auto pipeline = context_.Upgrade();
        auto rsUIContext = GetUIContext(pipeline);
        RSNode::Animate(rsUIContext,
            protocol, SCALE_ANIMATION_TIMING_CURVE, [rsNode, scaleEnd]() {
            if (rsNode) {
                rsNode->SetScale(scaleEnd);
            }
        });
        isHoveredScale_ = false;
    }
    if (hoverAnimationType_ == HoverAnimationType::BOARD || isHoveredBoard_) {
        ResetController(controllerEnter_);
        if (!controllerExit_) {
            controllerExit_ = CREATE_ANIMATOR(context_);
        }
        if (!backDecoration_) {
            backDecoration_ = AceType::MakeRefPtr<Decoration>();
        }
        if (!colorAnimationExit_) {
            colorAnimationExit_ = AceType::MakeRefPtr<KeyframeAnimation<Color>>();
        }
        CreateColorAnimation(colorAnimationExit_, hoverColor_, hoverColorBegin_);
        controllerExit_->ClearInterpolators();
        controllerExit_->AddInterpolator(colorAnimationExit_);
        controllerExit_->SetDuration(HOVER_ANIMATION_DURATION);
        controllerExit_->Play();
        controllerExit_->SetFillMode(FillMode::FORWARDS);
        isHoveredBoard_ = false;
    }
}

} // namespace OHOS::Ace
