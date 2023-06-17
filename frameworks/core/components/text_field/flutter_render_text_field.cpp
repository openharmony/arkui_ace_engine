/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "flutter_render_text_field.h"

#include <cmath>

#include "third_party/skia/include/effects/SkGradientShader.h"
#include "unicode/uchar.h"

#include "base/i18n/localization.h"
#include "base/utils/string_utils.h"
#include "base/utils/system_properties.h"
#include "core/common/text_field_manager.h"
#include "core/components/box/render_box_base.h"
#include "core/components/calendar/flutter_render_calendar.h"
#include "core/components/common/painter/flutter_decoration_painter.h"
#include "core/components/font/constants_converter.h"
#include "core/components/font/flutter_font_collection.h"
#include "core/pipeline/base/flutter_render_context.h"
#include "core/pipeline/base/scoped_canvas_state.h"
#include "rosen_text/typography_create.h"
#include "rosen_text/typography.h"

#if defined(ENABLE_STANDARD_INPUT)
#include "core/components/text_field/on_text_changed_listener_impl.h"
#endif

namespace OHOS::Ace {
namespace {

constexpr char16_t NEWLINE_CODE = u'\n';
// pixel for how far the caret to the top of paint rect. Sometimes may leave some space for the floor.
constexpr Color INLINE_STYLE_SELECTED_COLOR = Color(0x1A0A59F7);
constexpr double CARET_HEIGHT_OFFSET = 2.0;
constexpr Dimension CURSOR_WIDTH = 1.5_vp;
constexpr Dimension COUNT_SPACING = 4.0_vp;
constexpr double MAGNIFIER_GAIN = 1.25;
const char ELLIPSIS[] = "...";
constexpr Dimension DEFAULT_FOCUS_BORDER_WIDTH = 2.0_vp;
constexpr uint32_t DEFAULT_FOCUS_BORDER_COLOR = 0xFF254FF7;
constexpr double HALF = 0.5;

} // namespace

// The outer rect has a decoration, return the inner rect excluded the decoration.
Rect FlutterRenderTextField::GetInnerRect(const Decoration& decoration, const Rect& outer, double dipScale) const
{
    auto leftWidth = decoration.GetBorder().Left().GetWidth().ConvertToPx(dipScale) +
                     NormalizePercentToPx(decoration.GetPadding().Left(), false);
    auto topWidth = decoration.GetBorder().Top().GetWidth().ConvertToPx(dipScale) +
                    NormalizePercentToPx(decoration.GetPadding().Top(), true);
    auto rightWidth = decoration.GetBorder().Right().GetWidth().ConvertToPx(dipScale) +
                      NormalizePercentToPx(decoration.GetPadding().Right(), false);
    auto bottomWidth = decoration.GetBorder().Bottom().GetWidth().ConvertToPx(dipScale) +
                       NormalizePercentToPx(decoration.GetPadding().Bottom(), true);
    if (textDirection_ == TextDirection::RTL) {
        leftWidth += paddingHorizonForSearch_;
    } else {
        rightWidth += paddingHorizonForSearch_;
    }
    double iconSpacing = iconImage_ ? NormalizeToPx(iconHotZoneSizeInDimension_) : 0.0;
    double passwordIconSpacing = (keyboard_ == TextInputType::VISIBLE_PASSWORD && IsSelectiveDevice())
                                     ? NormalizeToPx(iconHotZoneSizeInDimension_)
                                     : 0.0;
    if (textDirection_ == TextDirection::RTL) {
        return Rect(outer.Left() + leftWidth + passwordIconSpacing, outer.Top() + topWidth,
            outer.Right() - rightWidth - leftWidth - iconSpacing - passwordIconSpacing,
            outer.Bottom() - bottomWidth - topWidth);
    } else {
        return Rect(outer.Left() + leftWidth + iconSpacing, outer.Top() + topWidth,
            outer.Right() - rightWidth - leftWidth - iconSpacing - passwordIconSpacing,
            outer.Bottom() - bottomWidth - topWidth);
    }
}

RenderLayer FlutterRenderTextField::GetRenderLayer()
{
    if (!layer_) {
        layer_ = AceType::MakeRefPtr<Flutter::ClipLayer>(
            0, GetLayoutSize().Width(), 0, GetLayoutSize().Height(), Flutter::Clip::HARD_EDGE);
    }
    return AceType::RawPtr(layer_);
}

bool FlutterRenderTextField::GetCaretRect(int32_t extent, Rect& caretRect, double caretHeightOffset) const
{
    CaretMetrics metrics;
    bool computeSuccess = false;
    DirectionStatus directionStatus = GetDirectionStatusOfPosition(extent);
    if (extent != 0 && extent != static_cast<int32_t>(GetEditingValue().GetWideText().length()) &&
        (directionStatus == DirectionStatus::LEFT_RIGHT || directionStatus == DirectionStatus::RIGHT_LEFT) &&
        cursorPositionType_ != CursorPositionType::NONE && LessOrEqual(clickOffset_.GetX(), innerRect_.Width())) {
        computeSuccess = ComputeOffsetForCaretCloserToClick(cursorPositionForShow_, metrics);
    } else {
        if (textAffinity_ == TextAffinity::DOWNSTREAM) {
            computeSuccess =
                ComputeOffsetForCaretDownstream(extent, metrics) || ComputeOffsetForCaretUpstream(extent, metrics);
        } else {
            computeSuccess =
                ComputeOffsetForCaretUpstream(extent, metrics) || ComputeOffsetForCaretDownstream(extent, metrics);
        }
    }
    if (computeSuccess && !GetEditingValue().text.empty()) {
        if (metrics.height <= 0 || std::isnan(metrics.height)) {
            // The reason may be text lines is exceed the paragraph maxline.
            LOGD("Illegal caret height. Consider release restriction of paragraph max_line.");
            return false;
        }
        caretRect.SetRect(metrics.offset.GetX(), metrics.offset.GetY() + caretHeightOffset, NormalizeToPx(CURSOR_WIDTH),
            metrics.height - caretHeightOffset * 2.0);
    } else {
        LOGD("Caret is at the begin of text. Make caret offset according to alignment.");
        // Use proto caret.
        caretRect = caretProto_ + MakeEmptyOffset();
    }

    return true;
}

void FlutterRenderTextField::PaintCaret(SkCanvas& canvas, const Rect& caretRect)
{
    // We simply not to draw the caret rather than do an alpha animation.
    if (!caretRect_.IsValid() || !showCursor_ || !cursorVisibility_) {
        return;
    }
    SkPaint paint;
    Color cursorColor = cursorColor_;
    if (!cursorColorIsSet_) {
        // Default strategy: Keep color same with text.
        cursorColor = style_.GetTextColor();
    }
    paint.setColor(Constants::ConvertSkColor(cursorColor));
    paint.setAntiAlias(true);
    if (NearZero(cursorRadius_.Value())) {
        canvas.drawRect(
            SkRect::MakeLTRB(caretRect.Left(), caretRect.Top(), caretRect.Right(), caretRect.Bottom()), paint);
    } else {
        const SkScalar radius = SkDoubleToScalar(NormalizeToPx(cursorRadius_));
        flutter::RRect rrect;
        rrect.sk_rrect.setRectXY(SkRect::MakeLTRB(SkDoubleToScalar(caretRect.Left()), SkDoubleToScalar(caretRect.Top()),
                                     SkDoubleToScalar(caretRect.Right()), SkDoubleToScalar(caretRect.Bottom())),
            radius, radius);
        canvas.drawRRect(rrect.sk_rrect, paint);
    }
}

void FlutterRenderTextField::PaintSelectCaret(SkCanvas* canvas)
{
    if (!isOverlayShowed_ || !paragraph_) {
        return;
    }

    SkPaint paint;
    paint.setAntiAlias(true);
    paint.setColor(cursorColor_.GetValue());
    paint.setStrokeWidth(caretRect_.Width());
    paint.setStrokeCap(SkPaint::Cap::kRound_Cap);

    Rect caretRect = caretRect_;
    // 1.0_dp is UX design.
    caretRect = caretRect + Offset(0.0, -CARET_HEIGHT_OFFSET - NormalizeToPx(1.0_vp)) +
                Size(0.0, (CARET_HEIGHT_OFFSET + NormalizeToPx(1.0_vp)) * 2.0);
    if (IsSingleHandle()) {
        canvas->drawLine((caretRect.Left() + caretRect.Right()) / 2.0, caretRect.Top(),
            (caretRect.Top(), caretRect.Left() + caretRect.Right()) / 2.0, caretRect.Bottom(), paint);
    }

    const auto& selection = GetEditingValue().selection;
    int32_t start = selection.GetStart();
    int32_t end = selection.GetEnd();

    const auto& boxes = paragraph_->GetTextRectsByBoundary(selection.GetStart(), selection.GetEnd(),
        Rosen::TextRectHeightStyle::COVER_TOP_AND_BOTTOM, Rosen::TextRectWidthStyle::TIGHT);
    if (!boxes.empty()) {
        Offset startCaretOffset = Offset(
            boxes.back().rect.GetRight() - boxes.front().rect.GetLeft(),
                boxes.back().rect.GetTop() - boxes.front().rect.GetTop());
        if (start >= GetInitIndex() && end >= GetInitIndex()) {
            startCaretRect_ = caretRect + startCaretOffset;
        } else {
            startCaretRect_ = caretRect - startCaretOffset;
        }
    } else {
        startCaretRect_ = caretRect;
    }

    // Draw line
    if (IsSingleHandle()) {
        canvas->drawLine((startCaretRect_.Left() + startCaretRect_.Right()) / 2.0, startCaretRect_.Top(),
            (startCaretRect_.Top(), startCaretRect_.Left() + startCaretRect_.Right()) / 2.0, startCaretRect_.Bottom(),
            paint);
    }
}

void FlutterRenderTextField::PaintDecoration(
    const Offset& offset, SkCanvas* canvas, const Size& size, RenderContext& context)
{
    auto pipelineContext = context_.Upgrade();
    if (!pipelineContext || !decoration_) {
        return;
    }
    pipelineContext->AddDirtyLayoutNode(AceType::Claim(this));

    Size deflateSize = ComputeDeflateSizeOfErrorAndCountText();
    RefPtr<FlutterDecorationPainter> decorationPainter = AceType::MakeRefPtr<FlutterDecorationPainter>(
        decoration_, GetPaintRect() - deflateSize, size - deflateSize, pipelineContext->GetDipScale());
    decorationPainter->PaintDecoration(offset, canvas, context);
}

void FlutterRenderTextField::PaintIcon(const Offset& offset, RenderContext& context)
{
    auto pipelineContext = context_.Upgrade();
    if (!pipelineContext) {
        return;
    }
    Offset verticalOffsetForCenter = ComputeVerticalOffsetForCenter(innerRect_.Height(), iconSize_);
    // Paint header icon.
    Offset iconOffset = offset;
    Offset hotZoneOffset = Offset((iconHotZoneSize_ - iconSize_) / 2.0, 0.0);
    if (iconImage_) {
        iconOffset += innerRect_.GetOffset() + verticalOffsetForCenter;
        if (textDirection_ == TextDirection::RTL) {
            iconOffset += Offset(innerRect_.Width(), 0.0) + hotZoneOffset;
        } else {
            iconOffset += hotZoneOffset - Offset(iconHotZoneSize_, 0.0);
        }
        iconImage_->RenderWithContext(context, iconOffset);
    }

    // Paint password icon.
    if (keyboard_ == TextInputType::VISIBLE_PASSWORD && renderShowIcon_ && renderHideIcon_) {
        Offset passwordIconOffset = offset + verticalOffsetForCenter + hotZoneOffset +
                                    Offset(GetLayoutSize().Width() - iconHotZoneSize_, innerRect_.GetOffset().GetY());
        if (textDirection_ == TextDirection::RTL) {
            passwordIconOffset += Offset(-(GetLayoutSize().Width() - iconHotZoneSize_), 0.0);
        }
        if (obscure_) {
            renderHideIcon_->RenderWithContext(context, passwordIconOffset);
        } else {
            renderShowIcon_->RenderWithContext(context, passwordIconOffset);
        }
        passwordIconRect_ = Rect(
            passwordIconOffset - Offset((iconHotZoneSize_ - iconSize_) / 2.0, (iconHotZoneSize_ - iconSize_) / 2.0),
            Size(iconHotZoneSize_, iconHotZoneSize_));
    }
}

void FlutterRenderTextField::PaintSelection(SkCanvas* canvas) const
{
    if (!IsSelectiveDevice()) {
        return;
    }
    if (!paragraph_ || (canvas == nullptr) || !canPaintSelection_) {
        return;
    }

    const auto& selection = GetEditingValue().selection;
    if (GetEditingValue().text.empty() || selection.GetStart() == selection.GetEnd()) {
        return;
    }

    DrawSelection(selection.GetStart(), selection.GetEnd(), canvas);
}

void FlutterRenderTextField::DrawSelection(unsigned start, unsigned end, SkCanvas* canvas) const
{
    using namespace Constants;
    const auto& boxes = paragraph_->GetTextRectsByBoundary(start, end,
        Rosen::TextRectHeightStyle::COVER_TOP_AND_BOTTOM, Rosen::TextRectWidthStyle::TIGHT);
    if (boxes.empty()) {
        return;
    }
    canvas->save();
    SkPaint paint;
    if (inputStyle_ == InputStyle::INLINE) {
        paint.setColor(INLINE_STYLE_SELECTED_COLOR.GetValue());
    } else {
        paint.setColor(selectedColor_.GetValue());
    }
    Offset effectiveOffset = innerRect_.GetOffset() + textOffsetForShowCaret_;
    for (const auto& box : boxes) {
        auto selectionRect = ConvertSkRect(box.rect) + effectiveOffset;
        switch (inputStyle_) {
            case InputStyle::INLINE:
                selectionRect.SetHeight(GetLayoutSize().Height());
                break;
            case InputStyle::DEFAULT:
                selectionRect += ComputeVerticalOffsetForCenter(innerRect_.Height(), paragraph_->GetHeight());
                break;
            default:
                LOGE("Unknown textinput style");
                break;
        }
        auto rect = SkRect::MakeLTRB(selectionRect.Right(), selectionRect.Top(), selectionRect.Left(),
            selectionRect.Bottom());

        if (box.direction == Rosen::TextDirection::LTR) {
            rect = SkRect::MakeLTRB(selectionRect.Left(), selectionRect.Top(), selectionRect.Right(),
                selectionRect.Bottom());
        }
        canvas->drawRect(rect, paint);
    }
    canvas->restore();
}

#if defined(IOS_PLATFORM)
void FlutterRenderTextField::PaintCompose(SkCanvas* canvas) const
{
    if (SystemProperties::GetDeviceType() != DeviceType::PHONE) {
        return;
    }

    if (!paragraph_ || (canvas == nullptr)) {
        return;
    }

    const auto& compose = GetEditingValue().compose;
    if (GetEditingValue().text.empty() || compose.GetStart() == compose.GetEnd()) {
        return;
    }

    DrawSelection(compose.GetStart(), compose.GetEnd(), canvas);
}
#endif

void FlutterRenderTextField::PaintTextAndPlaceholder(SkCanvas* canvas) const
{
    // Offset for the painting area of text
    Offset textAreaOffset = innerRect_.GetOffset();
    if (showPlaceholder_) {
        textAreaOffset += ComputeVerticalOffsetForCenter(innerRect_.Height(), placeholderParagraph_->GetHeight());
        placeholderParagraph_->Paint(canvas, textAreaOffset.GetX(), textAreaOffset.GetY());
    } else {
        textAreaOffset += ComputeVerticalOffsetForCenter(innerRect_.Height(), paragraph_->GetHeight());
        Offset textOffset = textOffsetForShowCaret_ + textAreaOffset;
        paragraph_->Paint(canvas, textOffset.GetX(), textOffset.GetY());
    }
}

void FlutterRenderTextField::PaintErrorText(SkCanvas* canvas) const
{
    if (!errorParagraph_ || (canvas == nullptr)) {
        return;
    }
    Offset errorOffset = innerRect_.GetOffset();
    if (errorIsInner_) {
        double errorSpacing =
            GreatOrEqual(errorParagraph_->GetActualWidth(), originInnerWidth_ - errorSpacing_) ? 0.0 : errorSpacing_;
        errorOffset +=
            Offset(innerRect_.Width() + errorSpacing, (innerRect_.Height() - errorParagraph_->GetHeight()) / 2.0);
    } else {
        double bottomPadding = 0.0;
        if (decoration_) {
            bottomPadding = NormalizeToPx(decoration_->GetPadding().Bottom());
        }
        errorOffset += Offset(0.0, innerRect_.Height() + bottomPadding + NormalizeToPx(COUNT_SPACING));
    }
    errorParagraph_->Paint(canvas, errorOffset.GetX(), errorOffset.GetY());
}

void FlutterRenderTextField::PaintCountText(SkCanvas* canvas) const
{
    if (!countParagraph_ || (canvas == nullptr)) {
        return;
    }
    if (ShowCounter()) {
        Offset countOffset = innerRect_.GetOffset() +
                             Offset(innerRect_.Width() - countParagraph_->GetActualWidth(), innerRect_.Height());
        if (maxLines_ == 1) {
            double bottomPadding = 0.0;
            if (decoration_) {
                bottomPadding = NormalizeToPx(decoration_->GetPadding().Bottom());
            }
            countOffset += Offset(0.0, bottomPadding + NormalizeToPx(COUNT_SPACING));
        }
        countParagraph_->Paint(canvas, countOffset.GetX(), countOffset.GetY());
    }
}

SkVector FlutterRenderTextField::GetSkRadii(const Radius& radius) const
{
    SkVector fRadii;
    fRadii.set(SkDoubleToScalar(NormalizeToPx(radius.GetX())), SkDoubleToScalar(NormalizeToPx(radius.GetY())));
    return fRadii;
}

void FlutterRenderTextField::PaintOverlayForHoverAndPress(const Offset& offset, SkCanvas* canvas) const
{
    if (canvas == nullptr) {
        return;
    }
    auto pipelineContext = context_.Upgrade();
    if (!pipelineContext) {
        return;
    }
    Size deflateSize = ComputeDeflateSizeOfErrorAndCountText();
    RefPtr<FlutterDecorationPainter> decorationPainter = AceType::MakeRefPtr<FlutterDecorationPainter>(decoration_,
        GetPaintRect() - deflateSize, GetPaintRect().GetSize() - deflateSize, pipelineContext->GetDipScale());
    Border border;
    if (decoration_) {
        border = decoration_->GetBorder();
    }
    flutter::RRect clipRRect = decorationPainter->GetBoxRRect(Offset(), border, 0.0, true);
    canvas->save();
    canvas->clipRRect(clipRRect.sk_rrect, true);

    SkPaint paint;
    paint.setColor(GetEventEffectColor().GetValue());
    paint.setStyle(SkPaint::Style::kFill_Style);
    paint.setAntiAlias(true);

    SkRect skRect = SkRect::MakeXYWH(offset.GetX(), offset.GetY(), GetLayoutSize().Width(), GetLayoutSize().Height());
    flutter::RRect rrect;
    SkVector fRadii[4] = { { 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 } };
    fRadii[SkRRect::kUpperLeft_Corner] = GetSkRadii(border.TopLeftRadius());
    fRadii[SkRRect::kUpperRight_Corner] = GetSkRadii(border.TopRightRadius());
    fRadii[SkRRect::kLowerRight_Corner] = GetSkRadii(border.BottomRightRadius());
    fRadii[SkRRect::kLowerLeft_Corner] = GetSkRadii(border.BottomLeftRadius());
    rrect.sk_rrect.setRectRadii(skRect, fRadii);
    canvas->drawRRect(rrect.sk_rrect, paint);
    canvas->restore();
}

void FlutterRenderTextField::PaintFocus(const Offset& offset, const Size& widthHeight, RenderContext& context)
{
    auto canvas = ScopedCanvas::Create(context);
    if (!canvas) {
        LOGE("canvas is null");
        return;
    }
    SkCanvas* skCanvas = canvas->canvas();
    if (!skCanvas) {
        LOGE("Paint skCanvas is null");
        return;
    }
    if (!skCanvas) {
        LOGE("Paint canvas is null");
        return;
    }
    SkPaint paint;
    paint.setColor(DEFAULT_FOCUS_BORDER_COLOR);
    paint.setStrokeWidth(NormalizeToPx(DEFAULT_FOCUS_BORDER_WIDTH));
    paint.setStyle(SkPaint::Style::kStroke_Style);
    paint.setAntiAlias(true);

    SkRect skRect = SkRect::MakeXYWH(offset.GetX() + NormalizeToPx(DEFAULT_FOCUS_BORDER_WIDTH) * HALF,
        offset.GetY() + NormalizeToPx(DEFAULT_FOCUS_BORDER_WIDTH) * HALF,
        widthHeight.Width() - NormalizeToPx(DEFAULT_FOCUS_BORDER_WIDTH),
        widthHeight.Height() - NormalizeToPx(DEFAULT_FOCUS_BORDER_WIDTH));
    flutter::RRect rrect;
    SkVector fRadii[4] = { { 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 } };
    fRadii[SkRRect::kUpperLeft_Corner] = GetSkRadii(decoration_->GetBorder().TopLeftRadius());
    fRadii[SkRRect::kUpperRight_Corner] = GetSkRadii(decoration_->GetBorder().TopRightRadius());
    fRadii[SkRRect::kLowerRight_Corner] = GetSkRadii(decoration_->GetBorder().BottomRightRadius());
    fRadii[SkRRect::kLowerLeft_Corner] = GetSkRadii(decoration_->GetBorder().BottomLeftRadius());
    rrect.sk_rrect.setRectRadii(skRect, fRadii);
    skCanvas->drawRRect(rrect.sk_rrect, paint);
}

void FlutterRenderTextField::Paint(RenderContext& context, const Offset& offset)
{
    if (layer_) {
        layer_->SetClip(0, GetLayoutSize().Width(), 0, GetLayoutSize().Height(), Flutter::Clip::HARD_EDGE);
    }

    auto canvas = ScopedCanvas::Create(context);
    if (!canvas) {
        LOGE("canvas fetch failed");
        return;
    }
    auto pipelineContext = context_.Upgrade();
    if (!(paragraph_ || placeholderParagraph_ || !pipelineContext) || IsInfiniteLayout()) {
        LOGE("Paint canvas or paragraph is null");
        return;
    }
    auto viewScale = pipelineContext->GetViewScale();
    SkCanvas* skCanvas = canvas->canvas();
    if (lastLayoutSize_ != GetLayoutSize() || !magnifierCanvas_) {
        auto imageInfo = SkImageInfo::Make(GetLayoutSize().Width() * viewScale * MAGNIFIER_GAIN,
            GetLayoutSize().Height() * viewScale * MAGNIFIER_GAIN, SkColorType::kRGBA_8888_SkColorType,
            SkAlphaType::kOpaque_SkAlphaType);
        if (imageInfo.width() < 0 || imageInfo.height() < 0) {
            LOGE("Paint imageInfo width is invalid");
            return;
        }
        canvasCache_.reset();
        canvasCache_.allocPixels(imageInfo);
        magnifierCanvas_ = std::make_unique<SkCanvas>(canvasCache_);
        lastLayoutSize_ = GetLayoutSize();
    }

    canvasCache_.eraseColor(SK_ColorTRANSPARENT);
    magnifierCanvas_->scale(viewScale * MAGNIFIER_GAIN, viewScale * MAGNIFIER_GAIN);

    PaintTextField(offset, context, skCanvas);
    PaintTextField(offset, context, magnifierCanvas_.get(), true);

    magnifierCanvas_->scale(1.0 / (viewScale * MAGNIFIER_GAIN), 1.0 / (viewScale * MAGNIFIER_GAIN));

    if ((SystemProperties::GetDeviceType() == DeviceType::PHONE ||
            SystemProperties::GetDeviceType() == DeviceType::TABLET) &&
        hasFocus_) {
        PaintFocus(offset, GetPaintRect().GetSize(), context);
    }
}

Size FlutterRenderTextField::Measure()
{
    ResetParagraphIfNeeded();

    UpdateCaretProto();

    auto pipelineContext = context_.Upgrade();
    if (!pipelineContext) {
        LOGE("No pipelineContext.");
        return Size();
    }

    double decorationHeight = 0.0;
    if (decoration_) {
        auto padding = decoration_->GetPadding();
        auto paddingOri = padding;
        padding.SetLeft(NormalizePercentToPx(padding.Left(), false));
        padding.SetTop(NormalizePercentToPx(padding.Top(), true));
        padding.SetRight(NormalizePercentToPx(padding.Right(), false));
        padding.SetBottom(NormalizePercentToPx(padding.Bottom(), true));
        decoration_->SetPadding(padding);
        decorationHeight = decoration_->VerticalSpaceOccupied(pipelineContext->GetDipScale());
        decoration_->SetPadding(paddingOri);
    }

    auto paragraphStyle = CreateParagraphStyle();
    std::unique_ptr<Rosen::TextStyle> txtStyle;
    double textAreaWidth = MeasureParagraph(paragraphStyle, txtStyle);
    ComputeExtendHeight(decorationHeight);

    double height = NearZero(extendHeight_) ? GetLayoutParam().GetMaxSize().Height() : extendHeight_;
    innerRect_ = { Offset::Zero(), GetLayoutParam().GetMaxSize() };
    innerRect_.SetHeight(height);
    Size size = innerRect_.GetSize();
    if (decoration_) {
        // Restrict painting rect to text area, excluding the decoration.
        innerRect_ = GetInnerRect(*decoration_, innerRect_, pipelineContext->GetDipScale());
    }
    originInnerWidth_ = innerRect_.Width();
    if (errorParagraph_ && errorIsInner_) {
        double deflateWidth = innerRect_.Width() - errorParagraph_->GetActualWidth() - errorSpacing_;
        innerRect_.SetWidth(GreatOrEqual(deflateWidth, 0.0) ? deflateWidth : 0.0);
    }

    // Get height of text
    if (paragraph_ != nullptr) {
        textHeight_ = paragraph_->GetHeight();
        textLines_ = paragraph_->GetLineCount();
    } else {
        textHeight_ = 0.0;
        textLines_ = 0;
    }

    ComputeOffsetAfterLayout();

    SetShaderIfNeeded(std::move(paragraphStyle), std::move(txtStyle), textAreaWidth);

    return ComputeLayoutSize(size, decorationHeight);
}

double FlutterRenderTextField::MeasureParagraph(
    const std::unique_ptr<Rosen::TypographyStyle>& paragraphStyle, std::unique_ptr<Rosen::TextStyle>& txtStyle)
{
    double maxWidth = GetLayoutParam().GetMaxSize().Width();
    // If single-line, give it infinity for layout and text will auto scroll following with caret.
    double textAreaWidth = std::numeric_limits<double>::infinity();

    auto pipelineContext = context_.Upgrade();
    if (!pipelineContext) {
        LOGE("No pipelineContext.");
        return textAreaWidth;
    }

    double limitWidth = maxWidth;
    if (decoration_) {
        limitWidth = maxWidth - decoration_->HorizontalSpaceOccupied(pipelineContext->GetDipScale());
    }
    if (iconImage_) {
        limitWidth -= iconHotZoneSize_;
    }
    if (keyboard_ == TextInputType::VISIBLE_PASSWORD) {
        limitWidth -= iconHotZoneSize_;
    }
    limitWidth -= paddingHorizonForSearch_;
    // If multi-line, set the maxWidth so that Paragraph can help us do soft-wrap.
    if (maxLines_ != 1 || resetToStart_) {
        textAreaWidth = limitWidth;
    }

    auto displayText = GetTextForDisplay(GetEditingValue().text);
    showPlaceholder_ = displayText.empty();
    double errorTextWidth = 0.0;
    paragraph_.reset(nullptr);
    errorParagraph_.reset(nullptr);
    countParagraph_.reset(nullptr);
    placeholderParagraph_.reset(nullptr);
    if (!errorText_.empty()) {
        std::unique_ptr<Rosen::TypographyCreate> errorBuilder =
            Rosen::TypographyCreate::Create(*CreateParagraphStyle(true), GetFontCollection());
        txtStyle = CreateTextStyle(errorTextStyle_);
        errorBuilder->PushStyle(*txtStyle);
        errorBuilder->AppendText(StringUtils::Str8ToStr16(errorText_));
        errorParagraph_ = errorBuilder->CreateTypography();
        errorParagraph_->Layout(textAreaWidth);
        errorTextWidth = errorIsInner_ ? errorParagraph_->GetActualWidth() : 0.0;
    }
    if (ShowCounter()) {
        std::unique_ptr<Rosen::TypographyCreate> countBuilder =
            Rosen::TypographyCreate::Create(*CreateParagraphStyle(), GetFontCollection());
        if (overCount_) {
            txtStyle = CreateTextStyle(maxLines_ == 1 ? overCountStyleOuter_ : overCountStyle_);
        } else {
            txtStyle = CreateTextStyle(maxLines_ == 1 ? countTextStyleOuter_ : countTextStyle_);
        }
        countBuilder->PushStyle(*txtStyle);
        countBuilder->AppendText(StringUtils::Str8ToStr16(
            std::to_string(GetEditingValue().GetWideText().size()) + "/" + std::to_string(maxLength_)));
        countParagraph_ = countBuilder->CreateTypography();
        countParagraph_->Layout(textAreaWidth);
    }
    if (!showPlaceholder_) {
        std::unique_ptr<Rosen::TypographyCreate> builder =
            Rosen::TypographyCreate::Create(*paragraphStyle, GetFontCollection());
        txtStyle = CreateTextStyle(style_);
        builder->PushStyle(*txtStyle);
        builder->AppendText(displayText);
        paragraph_ = builder->CreateTypography();
        paragraph_->Layout(textAreaWidth - errorTextWidth);
        if ((textDirection_ == TextDirection::RTL || realTextDirection_ == TextDirection::RTL) &&
            LessOrEqual(paragraph_->GetActualWidth(), innerRect_.Width())) {
            paragraph_->Layout(limitWidth);
        }
    } else {
        std::unique_ptr<Rosen::TypographyCreate> placeholderBuilder =
            Rosen::TypographyCreate::Create(*paragraphStyle, GetFontCollection());
        txtStyle = CreateTextStyle(style_, true);
        placeholderBuilder->PushStyle(*txtStyle);
        placeholderBuilder->AppendText(StringUtils::Str8ToStr16(placeholder_));
        placeholderParagraph_ = placeholderBuilder->CreateTypography();
        placeholderParagraph_->Layout(limitWidth - errorTextWidth);
        if (textDirection_ == TextDirection::RTL &&
            LessOrEqual(placeholderParagraph_->GetActualWidth(), innerRect_.Width())) {
            placeholderParagraph_->Layout(limitWidth);
        }
    }
    return textAreaWidth;
}

void FlutterRenderTextField::ComputeExtendHeight(double decorationHeight)
{
    // Compute extendHeight which adjust to paragraph's height and max height when extend.
    double heightInPx = 0.0;
    if (height_.Unit() == DimensionUnit::PERCENT) {
        auto parent = GetParent().Upgrade();
        // If textfield can't handle percent, traverse parent to handle, here set max depth 4.
        for (int32_t depth = 1; depth <= 4; ++depth) {
            if (!parent) {
                break;
            }
            auto boxParent = AceType::DynamicCast<RenderBoxBase>(parent);
            if (boxParent) {
                heightInPx = boxParent->CalculateHeightPercent(height_.Value());
                break;
            }
            parent = parent->GetParent().Upgrade();
        }
    } else {
        heightInPx = NormalizeToPx(height_);
    }
    double deflateHeight = 0.0;
    if (errorParagraph_ && !errorIsInner_) {
        deflateHeight = errorParagraph_->GetHeight() + errorSpacing_;
    }
    if (countParagraph_ && ShowCounter()) {
        deflateHeight = std::max(deflateHeight, countParagraph_->GetHeight() + errorSpacing_);
    }
    heightInPx = std::clamp(heightInPx, GetLayoutParam().GetMinSize().Height() - deflateHeight,
        GetLayoutParam().GetMaxSize().Height() - deflateHeight);
    if (paragraph_ && extend_ && GreatOrEqual(paragraph_->GetHeight(), heightInPx - decorationHeight)) {
        extendHeight_ = paragraph_->GetHeight() + decorationHeight;
    } else {
        extendHeight_ = std::max(heightInPx, decorationHeight);
    }
    extendHeight_ = std::min(extendHeight_, GetLayoutParam().GetMaxSize().Height());
}

void FlutterRenderTextField::ComputeOffsetAfterLayout()
{
    // Use glyphs dependent height.
    if (GetCaretRect(GetEditingValue().selection.extentOffset, caretRect_, CARET_HEIGHT_OFFSET)) {
        caretRect_ += innerRect_.GetOffset();
        textOffsetForShowCaret_ = caretRect_.MagneticAttractedBy(innerRect_);
        // Only single line input support reset to start.
        if (resetToStart_ && keyboard_ != TextInputType::MULTILINE) {
            caretRect_ -= textOffsetForShowCaret_;
            textOffsetForShowCaret_ = Offset();
        }
        if (showPlaceholder_) {
            caretRect_ += ComputeVerticalOffsetForCenter(innerRect_.Height(), placeholderParagraph_->GetHeight());
        } else {
            caretRect_ += ComputeVerticalOffsetForCenter(innerRect_.Height(), paragraph_->GetHeight());
        }
    }

#if defined(ENABLE_STANDARD_INPUT)
    auto globalOffset = GetGlobalOffset();
    MiscServices::CursorInfo cursorInfo { .left = caretRect_.Left() + globalOffset.GetX(),
        .top = caretRect_.Top() + globalOffset.GetY(),
        .width = caretRect_.Width(),
        .height = caretRect_.Height() };
    auto context = context_.Upgrade();
    if (!context) {
        LOGE("context is nullptr");
        return;
    }
    auto manager = context->GetTextFieldManager();
    if (!manager) {
        LOGE("manager is nullptr");
        return;
    }
    auto textFieldManager = AceType::DynamicCast<TextFieldManager>(manager);
    if (!textFieldManager) {
        LOGE("textFieldmanager is nullptr");
        return;
    }
    auto weakFocusedTextField = textFieldManager->GetOnFocusTextField();
    auto focusedTextField = weakFocusedTextField.Upgrade();
    if (focusedTextField && focusedTextField == AceType::Claim(this)) {
        MiscServices::InputMethodController::GetInstance()->OnCursorUpdate(cursorInfo);
        auto value = GetEditingValue();
        MiscServices::InputMethodController::GetInstance()->OnSelectionChange(
            StringUtils::Str8ToStr16(value.text), value.selection.GetStart(), value.selection.GetEnd());
    }
#endif
}

Offset FlutterRenderTextField::ComputeVerticalOffsetForCenter(double outerHeight, double innerHeight) const
{
    // Compute verticalOffsetForCenter_ when TextInputType is not MULTILINE.
    if (keyboard_ == TextInputType::MULTILINE) {
        return Offset();
    }
    return Offset(0.0, (outerHeight - innerHeight) / 2.0);
}

sk_sp<SkShader> FlutterRenderTextField::MakeGradientShader(double shadeWidth) const
{
    // If need move canvas for caret, the left side must be overflow.
    bool needShadeLeft = !NearZero(textOffsetForShowCaret_.GetX());
    // The actual width for text occupied.
    double textWidth = paragraph_->GetMaxIntrinsicWidth();
    // Width hidden on the right side. Attention: textOffsetForShowCaret_.GetX() is less than 0.
    double rightOverflow = textWidth + textOffsetForShowCaret_.GetX() - innerRect_.Width();
    bool needShadeRight = rightOverflow > 1.0;

    if (!needShadeLeft && !needShadeRight) {
        return nullptr;
    }
    if (!innerRect_.IsValid()) {
        return nullptr;
    }

    auto posLeft = static_cast<float>(shadeWidth / innerRect_.Width());
    float posRight = 1.0f - (posLeft * 2.0f);
    if (posRight < posLeft) {
        posRight = posLeft;
    }

    uint32_t originColor = style_.GetTextColor().GetValue();
    uint32_t transparentColor = originColor & 0x00FFFFFF;

    SkPoint pts[] = { SkPoint::Make(SkDoubleToScalar(innerRect_.Left()), SkDoubleToScalar(0.0)),
        SkPoint::Make(SkDoubleToScalar(innerRect_.Right()), SkDoubleToScalar(0.0)) };
    // Text or placeholder color from alpha 0 - 255
    SkColor colors[] = { transparentColor, originColor, originColor, transparentColor };
    float pos[] = { 0.0f, posLeft, posRight, 1.0f };

    int32_t start = 0;
    int32_t renderCount = sizeof(pos) / sizeof(pos[0]);
    int32_t totalCount = renderCount;
    if (!needShadeLeft) {
        start = 2;
        renderCount = 2;
    } else if (!needShadeRight) {
        start = 0;
        renderCount = 2;
    }
    if ((start + renderCount == totalCount) && blockRightShade_) {
        // when blocking right shade, ignore the last 2 points
        // in which case the renderCount must be greater or equal than 2
        renderCount -= 2;
        if (directionStatus_ == DirectionStatus::RIGHT_RIGHT) {
            start = 2;
        }
    }
#ifdef USE_SYSTEM_SKIA
    return SkGradientShader::MakeLinear(pts, &colors[start], &pos[start], renderCount, SkShader::kClamp_TileMode);
#else
    return SkGradientShader::MakeLinear(pts, &colors[start], &pos[start], renderCount, SkTileMode::kClamp);
#endif
}

void FlutterRenderTextField::SetShaderIfNeeded(std::unique_ptr<Rosen::TypographyStyle> paragraphStyle,
            std::unique_ptr<Rosen::TextStyle> txtStyle, double textAreaWidth)
{
    if (maxLines_ != 1 || showPlaceholder_ || !paragraph_ || !needFade_) {
        // Not support placeHolder or multiline.
        return;
    }

    const double shadeWidth = innerRect_.Left();
    if (shadeWidth * 2 > innerRect_.Width()) {
        LOGD("The region is too short to do shade.");
        return;
    }

    auto shader = MakeGradientShader(shadeWidth);
    if (!shader) {
        return;
    }

    std::unique_ptr<Rosen::TypographyCreate> builder =
        Rosen::TypographyCreate::Create(*paragraphStyle, GetFontCollection());
    txtStyle->foreground = SkPaint();
    txtStyle->foreground->setShader(shader);
    builder->PushStyle(*txtStyle);
    builder->AppendText(GetTextForDisplay(GetEditingValue().text));
    paragraph_ = builder->CreateTypography();
    paragraph_->Layout(textAreaWidth);
}

Size FlutterRenderTextField::ComputeLayoutSize(const Size& size, double decorationHeight)
{
    if (!extend_ || GreatOrEqual(innerRect_.GetSize().Height(), textHeight_)) {
        Size inflateSize;
        if (errorParagraph_ && !errorIsInner_) {
            // If error text is under textfield, height of textfield should add error text's height.
            inflateSize.SetHeight(errorParagraph_->GetHeight() + errorSpacing_);
        }
        if (countParagraph_ && ShowCounter()) {
            // If count text is under textfield, height of textfield should add count text's height.
            inflateSize.SetHeight(std::max(inflateSize.Height(), countParagraph_->GetHeight() + errorSpacing_));
        }
        return size + inflateSize;
    }
    if (GreatNotEqual(textHeight_, 0.0)) {
        innerRect_.SetHeight(textHeight_);
    }
    double maxWidth = GetLayoutParam().GetMaxSize().Width();
    return Size(maxWidth, innerRect_.Height() + decorationHeight);
}

std::unique_ptr<Rosen::TypographyStyle> FlutterRenderTextField::CreateParagraphStyle(bool isErrorText)
{
    using namespace Constants;

    auto style = std::make_unique<Rosen::TypographyStyle>();
    // If single-line, it shouldn't do soft-wrap for us.
    if (maxLines_ == 1 && resetToStart_) {
        style->maxLines = 1;
        if (showEllipsis_ && keyboard_ != TextInputType::VISIBLE_PASSWORD) {
            style->ellipsis = StringUtils::Str8ToStr16(ELLIPSIS);
        }
    }
    style->textAlign = ConvertTxtTextAlign(textAlign_);
    style->fontSize = NormalizeToPx(style_.GetFontSize());

    // If keyboard is password, don't change text_direction with first strong direction letter
    if (!isErrorText && keyboard_ == TextInputType::VISIBLE_PASSWORD && !GetEditingValue().text.empty()) {
        style->textDirection = ConvertTxtTextDirection(textDirection_);
        realTextDirection_ = textDirection_;
        UpdateDirectionStatus();
        return style;
    }
    std::string showingText;
    if (isErrorText) {
        showingText = errorText_;
    } else {
        showingText = GetEditingValue().text;
        if (showingText.empty()) {
            showingText = placeholder_;
        }
    }
    // Use first strong direction letter to decide text_direction.
    existStrongDirectionLetter_ = false;
    auto showingTextForWString = StringUtils::ToWstring(showingText);
    for (const auto& charOfShowingText : showingTextForWString) {
        auto charDirection = u_charDirection(charOfShowingText);
        if (charDirection == UCharDirection::U_LEFT_TO_RIGHT) {
            style->textDirection = ConvertTxtTextDirection(TextDirection::LTR);
            existStrongDirectionLetter_ = true;
            realTextDirection_ = TextDirection::LTR;
        } else if (charDirection == UCharDirection::U_RIGHT_TO_LEFT ||
                   charDirection == UCharDirection::U_RIGHT_TO_LEFT_ARABIC ||
                   charDirection == UCharDirection::U_ARABIC_NUMBER) {
            style->textDirection = ConvertTxtTextDirection(TextDirection::RTL);
            existStrongDirectionLetter_ = true;
            realTextDirection_ = TextDirection::RTL;
        }
        if (existStrongDirectionLetter_) {
            break;
        }
    }
    if (!existStrongDirectionLetter_) {
        style->textDirection = ConvertTxtTextDirection(textDirection_);
        realTextDirection_ = textDirection_;
    }
    UpdateDirectionStatus();
    if (keyboard_ != TextInputType::MULTILINE) {
        style->wordBreakType = Rosen::WordBreakType::BREAK_ALL;
    }
    return style;
}

std::unique_ptr<Rosen::TextStyle> FlutterRenderTextField::CreateTextStyle(const TextStyle& style, bool isPlaceholder)
{
    using namespace Constants;

    auto txtStyle = std::make_unique<Rosen::TextStyle>();
    if (isPlaceholder) {
        txtStyle->color = ConvertSkColor(placeholderColor_);
    } else {
        txtStyle->color = ConvertSkColor(style.GetTextColor());
    }

    txtStyle->fontFamilies = style.GetFontFamilies();
    txtStyle->fontWeight = ConvertTxtFontWeight(style.GetFontWeight());
    txtStyle->fontSize = NormalizeToPx(style.GetFontSize());
    txtStyle->fontStyle = ConvertTxtFontStyle(style.GetFontStyle());
    txtStyle->baseline = ConvertTxtTextBaseline(style.GetTextBaseline());
    txtStyle->locale = Localization::GetInstance()->GetFontLocale();
    return txtStyle;
}

void FlutterRenderTextField::UpdateCaretProto()
{
    caretProto_.SetRect(
        0.0, CARET_HEIGHT_OFFSET, NormalizeToPx(CURSOR_WIDTH), PreferredLineHeight() - 2.0 * CARET_HEIGHT_OFFSET);
}

double FlutterRenderTextField::GetBoundaryOfParagraph(bool isLeftBoundary) const
{
    if (!paragraph_ || GetEditingValue().text.empty()) {
        return 0.0;
    }
    auto boxes = paragraph_->GetTextRectsByBoundary(0, GetEditingValue().GetWideText().length(),
        Rosen::TextRectHeightStyle::COVER_TOP_AND_BOTTOM, Rosen::TextRectWidthStyle::TIGHT);
    if (boxes.empty()) {
        return 0.0;
    }
    double leftBoundaryOfParagraph = boxes.front().rect.GetLeft();
    double rightBoundaryOfParagraph = boxes.front().rect.GetLeft();
    double bottomBoundaryOfParagraph = boxes.front().rect.GetBottom();
    for (const auto& box : boxes) {
        if (cursorPositionType_ == CursorPositionType::END &&
                !NearEqual(box.rect.GetBottom(), bottomBoundaryOfParagraph)) {
            bottomBoundaryOfParagraph = box.rect.GetBottom();
            leftBoundaryOfParagraph = box.rect.GetLeft();
            rightBoundaryOfParagraph = box.rect.GetRight();
            continue;
        }
        leftBoundaryOfParagraph = std::min(static_cast<double>(box.rect.GetLeft()), leftBoundaryOfParagraph);
        rightBoundaryOfParagraph = std::max(static_cast<double>(box.rect.GetRight()), rightBoundaryOfParagraph);
    }
    return isLeftBoundary ? leftBoundaryOfParagraph : rightBoundaryOfParagraph;
}

bool FlutterRenderTextField::ComputeOffsetForCaretUpstream(int32_t extent, CaretMetrics& result) const
{
    auto text = GetTextForDisplay(GetEditingValue().text);
    if (!paragraph_ || text.empty()) {
        return false;
    }

    char16_t prevChar = 0;
    if (static_cast<size_t>(extent) <= text.length()) {
        prevChar = text[std::max(0, extent - 1)];
    }

    result.Reset();
    int32_t graphemeClusterLength = StringUtils::NotInUtf16Bmp(prevChar) ? 2 : 1;
    int32_t prev = extent - graphemeClusterLength;
    auto boxes = paragraph_->GetTextRectsByBoundary(
        prev, extent, Rosen::TextRectHeightStyle::COVER_TOP_AND_BOTTOM, Rosen::TextRectWidthStyle::TIGHT);
    while (boxes.empty() && !GetEditingValue().text.empty()) {
        graphemeClusterLength *= 2;
        prev = extent - graphemeClusterLength;
        if (prev < 0) {
            boxes = paragraph_->GetTextRectsByBoundary(
                0, extent, Rosen::TextRectHeightStyle::COVER_TOP_AND_BOTTOM, Rosen::TextRectWidthStyle::TIGHT);
            break;
        }
        boxes = paragraph_->GetTextRectsByBoundary(
            prev, extent, Rosen::TextRectHeightStyle::COVER_TOP_AND_BOTTOM, Rosen::TextRectWidthStyle::TIGHT);
    }
    if (boxes.empty()) {
        return false;
    }

    const auto& textBox = *boxes.begin();

    if (prevChar == NEWLINE_CODE) {
        // Return the start of next line.
        auto emptyOffset = MakeEmptyOffset();
        result.offset.SetX(emptyOffset.GetX());
        result.offset.SetY(textBox.rect.GetBottom());
        result.height = caretProto_.Height();
        return true;
    }

    bool isLtr = textBox.direction == Rosen::TextDirection::LTR;
    // Caret is within width of the upstream glyphs.
    double caretEnd = isLtr ? textBox.rect.GetRight() : textBox.rect.GetLeft();
    if (cursorPositionType_ == CursorPositionType::END) {
        caretEnd = GetBoundaryOfParagraph(realTextDirection_ != TextDirection::LTR);
    }
    double dx = isLtr ? caretEnd : caretEnd - caretProto_.Width();
    double offsetX = std::min(dx, paragraph_->GetMaxWidth());
    result.offset.SetX(offsetX);
    result.offset.SetY(textBox.rect.GetTop());
    result.height = textBox.rect.GetBottom() - textBox.rect.GetTop();
    return true;
}

bool FlutterRenderTextField::ComputeOffsetForCaretDownstream(int32_t extent, CaretMetrics& result) const
{
    if (!paragraph_ || static_cast<size_t>(extent) >= GetEditingValue().GetWideText().length()) {
        return false;
    }

    result.Reset();
    const int32_t graphemeClusterLength = 1;
    const int32_t next = extent + graphemeClusterLength;
    auto boxes = paragraph_->GetTextRectsByBoundary(
        extent, next, Rosen::TextRectHeightStyle::COVER_TOP_AND_BOTTOM, Rosen::TextRectWidthStyle::TIGHT);
    if (boxes.empty()) {
        return false;
    }

    const auto& textBox = *boxes.begin();
    bool isLtr = textBox.direction == Rosen::TextDirection::LTR;
    // Caret is within width of the downstream glyphs.
    double caretStart = isLtr ? textBox.rect.GetLeft() : textBox.rect.GetRight();
    if (cursorPositionType_ == CursorPositionType::END) {
        caretStart = GetBoundaryOfParagraph(realTextDirection_ != TextDirection::LTR);
    }
    double dx = isLtr ? caretStart : caretStart - caretProto_.Width();
    double offsetX = std::min(dx, paragraph_->GetMaxWidth());
    result.offset.SetX(offsetX);
    result.offset.SetY(textBox.rect.GetTop());
    result.height = textBox.rect.GetBottom() - textBox.rect.GetTop();
    return true;
}

bool FlutterRenderTextField::ComputeOffsetForCaretCloserToClick(int32_t extent, CaretMetrics& result) const
{
    CaretMetrics upStreamMetrics;
    bool upStreamSuccess = ComputeOffsetForCaretUpstream(extent, upStreamMetrics);
    CaretMetrics downStreamMetrics;
    bool downStreamSuccess = ComputeOffsetForCaretDownstream(extent, downStreamMetrics);
    bool nearToUpStream = LessOrEqual(std::abs(upStreamMetrics.offset.GetX() - clickOffset_.GetX()),
        std::abs(downStreamMetrics.offset.GetX() - clickOffset_.GetX()));
    result = nearToUpStream ? upStreamMetrics : downStreamMetrics;
    return upStreamSuccess || downStreamSuccess;
}

Offset FlutterRenderTextField::MakeEmptyOffset() const
{
    switch (textAlign_) {
        case TextAlign::LEFT: {
            return Offset::Zero();
        }
        case TextAlign::RIGHT: {
            return Offset(innerRect_.Width(), 0.0);
        }
        case TextAlign::JUSTIFY:
        case TextAlign::CENTER: {
            return Offset(innerRect_.Width() / 2.0, 0.0);
        }
        case TextAlign::END: {
            switch (realTextDirection_) {
                case TextDirection::RTL: {
                    return Offset::Zero();
                }
                case TextDirection::LTR:
                default: {
                    return Offset(innerRect_.Width(), 0.0);
                }
            }
        }
        case TextAlign::START:
        default: {
            // Default to start.
            switch (realTextDirection_) {
                case TextDirection::RTL: {
                    return Offset(innerRect_.Width(), 0.0);
                }
                case TextDirection::LTR:
                default: {
                    return Offset::Zero();
                }
            }
        }
    }
}

double FlutterRenderTextField::PreferredLineHeight()
{
    if (!template_) {
        std::unique_ptr<Rosen::TypographyCreate> builder =
            Rosen::TypographyCreate::Create(*CreateParagraphStyle(), GetFontCollection());
        builder->PushStyle(*CreateTextStyle(style_));
        // Use a space for estimating line height if there is no placeholder.
        // Actually it has slight differ between cases.
        if (placeholder_.empty()) {
            builder->AppendText(u" ");
        } else {
            builder->AppendText(StringUtils::Str8ToStr16(placeholder_));
        }
        template_ = builder->CreateTypography();
        template_->Layout(Size::INFINITE_SIZE);
    }
    return template_->GetHeight();
}

std::shared_ptr<Rosen::FontCollection> FlutterRenderTextField::GetFontCollection()
{
    return FlutterFontCollection::GetInstance().GetFontCollection();
}

void FlutterRenderTextField::ResetParagraphIfNeeded()
{
    // When custom font is loaded, reset the paragraph.
    if (isCallbackCalled_) {
        if (paragraph_) {
            paragraph_.reset();
        }
        if (placeholderParagraph_) {
            placeholderParagraph_.reset();
        }
    }
}

int32_t FlutterRenderTextField::GetCursorPositionForMoveUp()
{
    if (!paragraph_) {
        return 0;
    }
    double verticalOffset = -textOffsetForShowCaret_.GetY() - PreferredLineHeight();
    return static_cast<int32_t>(paragraph_->GetGlyphIndexByCoordinate(
        caretRect_.Left() - innerRect_.Left(), caretRect_.Top() + verticalOffset).index);
}

int32_t FlutterRenderTextField::GetCursorPositionForMoveDown()
{
    if (!paragraph_) {
        return 0;
    }
    double verticalOffset = -textOffsetForShowCaret_.GetY() + PreferredLineHeight();
    return static_cast<int32_t>(paragraph_->GetGlyphIndexByCoordinate(
        caretRect_.Left() - innerRect_.Left(), caretRect_.Top() + verticalOffset).index);
}

int32_t FlutterRenderTextField::GetCursorPositionForClick(const Offset& offset)
{
    if (!paragraph_) {
        return 0;
    }
    cursorPositionType_ = CursorPositionType::NORMAL;
    clickOffset_ = offset - GetGlobalOffset() - innerRect_.GetOffset() - textOffsetForShowCaret_;
    // Solve can't select right boundary of RTL language.
    double rightBoundary = GetBoundaryOfParagraph(false);
    if (realTextDirection_ == TextDirection::RTL && GreatOrEqual(clickOffset_.GetX(), rightBoundary)) {
        return 0;
    }
    return static_cast<int32_t>(
        paragraph_->GetGlyphIndexByCoordinate(clickOffset_.GetX(), clickOffset_.GetY()).index);
}

int32_t FlutterRenderTextField::AdjustCursorAndSelection(int32_t currentCursorPosition)
{
    int32_t result = currentCursorPosition;
    // Place cursor to the right boundary of paragraph when direction is LTR,
    // place to the left boundary of paragraph when direction is RTL.
    auto paragraphStyle = CreateParagraphStyle();
    std::unique_ptr<Rosen::TextStyle> txtStyle;
    MeasureParagraph(paragraphStyle, txtStyle);
    Rect tempRect;
    GetCaretRect(currentCursorPosition, tempRect);
    auto maxPosition = static_cast<int32_t>(GetEditingValue().GetWideText().length());
    double leftBoundary = GetBoundaryOfParagraph(true);
    double rightBoundary = GetBoundaryOfParagraph(false);
    if ((realTextDirection_ == TextDirection::LTR &&
            (NearEqual(tempRect.Left(), rightBoundary) || NearEqual(tempRect.Right(), rightBoundary))) ||
        (realTextDirection_ == TextDirection::RTL &&
            (NearEqual(tempRect.Left(), leftBoundary) || NearEqual(tempRect.Right(), leftBoundary)))) {
        result = maxPosition;
        cursorPositionType_ = CursorPositionType::END;
        return result;
    }

    // Get wstring before cursor.
    const char mark = ' ';
    std::string tempBefore = GetEditingValue().GetSelectedText(TextSelection(0, currentCursorPosition));
    StringUtils::DeleteAllMark(tempBefore, mark);
    const auto& textBeforeCursor = StringUtils::ToWstring(tempBefore);
    // Get wstring after cursor.
    std::string tempAfter = GetEditingValue().GetSelectedText(
        TextSelection(currentCursorPosition, GetEditingValue().GetWideText().length()));
    StringUtils::DeleteAllMark(tempAfter, mark);
    const auto& textAfterCursor = StringUtils::ToWstring(tempAfter);
    // Judge should or shouldn't adjust position.
    bool needAdjustPosition = NeedAdjustPosition(textBeforeCursor);
    if (!needAdjustPosition) {
        cursorPositionForShow_ = currentCursorPosition;
        return currentCursorPosition;
    }

    // Adjust position when click boundary of RTL and LTR.
    const auto& charBefore = textBeforeCursor.back();
    const auto& charAfter = textAfterCursor.front();
    bool isBeforeCharRtl =
        !textBeforeCursor.empty() && (u_charDirection(charBefore) == UCharDirection::U_RIGHT_TO_LEFT ||
                                         u_charDirection(charBefore) == UCharDirection::U_RIGHT_TO_LEFT_ARABIC);
    bool isAfterCharRtl =
        !textAfterCursor.empty() && (u_charDirection(charAfter) == UCharDirection::U_RIGHT_TO_LEFT ||
                                        u_charDirection(charAfter) == UCharDirection::U_RIGHT_TO_LEFT_ARABIC);
    bool adjustSuccess = true;
    if (realTextDirection_ == TextDirection::RTL) {
        adjustSuccess =
            AdjustCursorAndSelectionForRtl(isBeforeCharRtl, isAfterCharRtl, textBeforeCursor, textAfterCursor, result);
    } else if (realTextDirection_ == TextDirection::LTR) {
        adjustSuccess =
            AdjustCursorAndSelectionForLtr(isBeforeCharRtl, isAfterCharRtl, textBeforeCursor, textAfterCursor, result);
    }
    if (!adjustSuccess) {
        return currentCursorPosition;
    }

    if (isValueFromRemote_) {
        isValueFromRemote_ = false;
        return currentCursorPosition;
    }
    return result;
}

bool FlutterRenderTextField::NeedAdjustPosition(const std::wstring& textBeforeCursor)
{
    bool needAdjustPosition = false;
    if (!textBeforeCursor.empty()) {
        UCharDirection firstCharDirection = u_charDirection(*(textBeforeCursor.rbegin()));
        bool isFirstCharRtl = (firstCharDirection == UCharDirection::U_RIGHT_TO_LEFT ||
                               firstCharDirection == UCharDirection::U_RIGHT_TO_LEFT_ARABIC);
        for (auto iter = textBeforeCursor.rbegin(); iter != textBeforeCursor.rend(); ++iter) {
            auto charDirection = u_charDirection(*iter);
            bool isDirectionRtl = (charDirection == UCharDirection::U_RIGHT_TO_LEFT ||
                                   charDirection == UCharDirection::U_RIGHT_TO_LEFT_ARABIC);
            if (isDirectionRtl != isFirstCharRtl) {
                needAdjustPosition = true;
                break;
            }
        }
    }
    return needAdjustPosition;
}

bool FlutterRenderTextField::AdjustCursorAndSelectionForLtr(bool isBeforeCharRtl, bool isAfterCharRtl,
    const std::wstring& textBeforeCursor, const std::wstring& textAfterCursor, int32_t& result)
{
    int32_t currentCursorPosition = result;
    if (isBeforeCharRtl && !isAfterCharRtl) {
        if (textBeforeCursor.empty()) {
            return false;
        }
        int32_t count = 0;
        UCharDirection charDirection;
        for (auto iter = textBeforeCursor.rbegin(); iter != textBeforeCursor.rend(); ++iter) {
            charDirection = u_charDirection(*iter);
            if (charDirection != UCharDirection::U_RIGHT_TO_LEFT &&
                charDirection != UCharDirection::U_RIGHT_TO_LEFT_ARABIC) {
                break;
            }
            count++;
        }
        result = currentCursorPosition - count;
        cursorPositionType_ = CursorPositionType::BOUNDARY;
        cursorPositionForShow_ = currentCursorPosition;
    } else if (!isBeforeCharRtl && isAfterCharRtl) {
        if (textAfterCursor.empty()) {
            return false;
        }
        int32_t count = 0;
        UCharDirection charDirection;
        for (auto iter = textAfterCursor.begin(); iter != textAfterCursor.end(); ++iter) {
            charDirection = u_charDirection(*iter);
            if (charDirection != UCharDirection::U_RIGHT_TO_LEFT &&
                charDirection != UCharDirection::U_RIGHT_TO_LEFT_ARABIC) {
                break;
            }
            count++;
        }
        result = currentCursorPosition + count;
        cursorPositionType_ = CursorPositionType::BOUNDARY;
        cursorPositionForShow_ = currentCursorPosition;
    }
    return true;
}

bool FlutterRenderTextField::AdjustCursorAndSelectionForRtl(bool isBeforeCharRtl, bool isAfterCharRtl,
    const std::wstring& textBeforeCursor, const std::wstring& textAfterCursor, int32_t& result)
{
    int32_t currentCursorPosition = result;
    if (!isBeforeCharRtl && (isAfterCharRtl || textAfterCursor.empty())) {
        if (textBeforeCursor.empty()) {
            return false;
        }
        int32_t count = 0;
        UCharDirection charDirection;
        for (auto iter = textBeforeCursor.rbegin(); iter != textBeforeCursor.rend(); ++iter) {
            charDirection = u_charDirection(*iter);
            if (charDirection == UCharDirection::U_RIGHT_TO_LEFT ||
                charDirection == UCharDirection::U_RIGHT_TO_LEFT_ARABIC) {
                break;
            }
            count++;
        }
        result = currentCursorPosition - count;
        cursorPositionType_ = CursorPositionType::BOUNDARY;
        cursorPositionForShow_ = currentCursorPosition;
    } else if (isBeforeCharRtl && !isAfterCharRtl) {
        if (textAfterCursor.empty()) {
            return false;
        }
        int32_t count = 0;
        UCharDirection charDirection;
        for (auto iter = textAfterCursor.begin(); iter != textAfterCursor.end(); ++iter) {
            charDirection = u_charDirection(*iter);
            if (charDirection == UCharDirection::U_RIGHT_TO_LEFT ||
                charDirection == UCharDirection::U_RIGHT_TO_LEFT_ARABIC) {
                break;
            }
            count++;
        }
        result = currentCursorPosition + count;
        cursorPositionType_ = CursorPositionType::BOUNDARY;
        cursorPositionForShow_ = currentCursorPosition;
    }
    return true;
}

DirectionStatus FlutterRenderTextField::GetDirectionStatusOfPosition(int32_t position) const
{
    const char mark = ' ';
    std::string tempBefore = GetEditingValue().GetSelectedText(TextSelection(0, position));
    StringUtils::DeleteAllMark(tempBefore, mark);
    const auto& textBeforeCursor = StringUtils::ToWstring(tempBefore);

    std::string tempAfter =
        GetEditingValue().GetSelectedText(TextSelection(position, GetEditingValue().GetWideText().length()));
    StringUtils::DeleteAllMark(tempAfter, mark);
    const auto& textAfterCursor = StringUtils::ToWstring(tempAfter);

    bool isBeforeCharRtl = false;
    if (!textBeforeCursor.empty()) {
        const auto& charBefore = textBeforeCursor.back();
        isBeforeCharRtl = (u_charDirection(charBefore) == UCharDirection::U_RIGHT_TO_LEFT ||
                           u_charDirection(charBefore) == UCharDirection::U_RIGHT_TO_LEFT_ARABIC);
    }

    bool isAfterCharRtl = false;
    if (!textAfterCursor.empty()) {
        const auto& charAfter = textAfterCursor.front();
        isAfterCharRtl = (u_charDirection(charAfter) == UCharDirection::U_RIGHT_TO_LEFT ||
                          u_charDirection(charAfter) == UCharDirection::U_RIGHT_TO_LEFT_ARABIC);
    }
    return static_cast<DirectionStatus>(
        (static_cast<uint8_t>(isBeforeCharRtl) << 1) | static_cast<uint8_t>(isAfterCharRtl));
}

Offset FlutterRenderTextField::GetHandleOffset(int32_t extend)
{
    Rect result;
    GetCaretRect(extend, result);
    selectHeight_ = result.Bottom() - result.Top();
    Offset handleLocalOffset = Offset((result.Left() + result.Right()) / 2.0, result.Bottom());
    Offset handleOffset = handleLocalOffset + innerRect_.GetOffset() + GetOffsetToPage() + textOffsetForShowCaret_;
    if (paragraph_) {
        handleOffset += ComputeVerticalOffsetForCenter(innerRect_.Height(), paragraph_->GetHeight());
    } else if (placeholderParagraph_) {
        handleOffset += ComputeVerticalOffsetForCenter(innerRect_.Height(), placeholderParagraph_->GetHeight());
    } else {
        handleOffset += Offset(0.0, (innerRect_.Height() - PreferredLineHeight()) / 2.0);
    }
    return handleOffset;
}

Size FlutterRenderTextField::ComputeDeflateSizeOfErrorAndCountText() const
{
    Size deflateSize;
    if (errorParagraph_ && !errorIsInner_) {
        deflateSize.SetHeight(errorParagraph_->GetHeight() + errorSpacing_);
    }
    if (maxLines_ == 1 && countParagraph_ && ShowCounter()) {
        deflateSize.SetHeight(std::max(deflateSize.Height(), countParagraph_->GetHeight() + errorSpacing_));
    }
    return deflateSize;
}

void FlutterRenderTextField::PaintTextField(
    const Offset& offset, RenderContext& context, SkCanvas* canvas, bool isMagnifier)
{
    canvas->save();
    canvas->translate(offset.GetX(), offset.GetY());
    Rect clipRect(Offset::Zero(), GetLayoutSize());
    canvas->clipRect(
        SkRect::MakeLTRB(clipRect.Left(), clipRect.Top(), clipRect.Right(), clipRect.Bottom()), SkClipOp::kIntersect);
    if (!isMagnifier) {
        PaintDecoration(offset, canvas, GetPaintRect().GetSize(), context);
        PaintOverlayForHoverAndPress(offset, canvas);
        PaintIcon(offset, context);
    }

    canvas->save();
    // Restrict painting rect to text area, excluding the decoration.
    canvas->clipRect(SkRect::MakeLTRB(innerRect_.Left(), innerRect_.Top(), innerRect_.Right(), innerRect_.Bottom()),
        SkClipOp::kIntersect);
    auto pipelineContext = context_.Upgrade();
    if (!pipelineContext ||
        lastLayoutSize_.Height() < decoration_->VerticalSpaceOccupied(pipelineContext->GetDipScale())) {
        return;
    }
    PaintSelection(canvas);
#if defined(IOS_PLATFORM)
    PaintCompose(canvas);
#endif
    // Paint cursor.
    PaintCaret(*canvas, caretRect_);
    PaintTextAndPlaceholder(canvas);
    canvas->restore();

    PaintErrorText(canvas);
    canvas->restore();
    PaintCountText(canvas);
    if (isMagnifier) {
        PaintSelectCaret(canvas);
    }
}

void FlutterRenderTextField::ResetStatus()
{
    template_.reset();
}

} // namespace OHOS::Ace
