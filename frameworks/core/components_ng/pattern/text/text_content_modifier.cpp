/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/text/text_content_modifier.h"
#include <cstdint>
#include <optional>

#include "base/log/ace_trace.h"
#include "base/utils/utils.h"
#include "core/components_ng/pattern/text/text_layout_adapter.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/render/animation_utils.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/drawing_prop_convertor.h"
#include "core/components_ng/render/image_painter.h"
#include "core/components_v2/inspector/utils.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "frameworks/core/components_ng/render/adapter/animated_image.h"
#include "frameworks/core/components_ng/render/adapter/pixelmap_image.h"
#ifdef ENABLE_ROSEN_BACKEND
#include "render_service_client/core/ui/rs_ui_director.h"
#include "2d_graphics/include/recording/draw_cmd_list.h"
#endif

namespace OHOS::Ace::NG {
namespace {
constexpr float RACE_DURATION_RATIO = 85.0f;
constexpr float RACE_MIN_GRADIENTPERCENT = 0.5f;
constexpr float DEFAULT_FADEOUT_GRADIENTPERCENT = 0.033f;
constexpr float RACE_MOVE_PERCENT_MIN = 0.0f;
constexpr float RACE_MOVE_PERCENT_MAX = 100.0f;
constexpr float RACE_SPACE_WIDTH = 48.0f;
constexpr float ROUND_VALUE = 0.5f;
constexpr uint32_t POINT_COUNT = 4;
constexpr float OBSCURED_ALPHA = 0.2f;
} // namespace

TextContentModifier::TextContentModifier(const std::optional<TextStyle>& textStyle, const WeakPtr<Pattern>& pattern)
    : pattern_(pattern)
{
    contentChange_ = MakeRefPtr<PropertyInt>(0);
    AttachProperty(contentChange_);
    auto patternUpgrade = pattern_.Upgrade();
    CHECK_NULL_VOID(patternUpgrade);
    auto textPattern = DynamicCast<TextPattern>(patternUpgrade);
    CHECK_NULL_VOID(textPattern);
    auto host = textPattern->GetHost();
    CHECK_NULL_VOID(host);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);

    auto contentRect = geometryNode->GetContentRect();
    contentOffset_ = MakeRefPtr<PropertyOffsetF>(contentRect.GetOffset());
    contentSize_ = MakeRefPtr<PropertySizeF>(contentRect.GetSize());
    AttachProperty(contentOffset_);
    AttachProperty(contentSize_);
    dragStatus_ = MakeRefPtr<PropertyBool>(false);
    AttachProperty(dragStatus_);
    if (textStyle.has_value()) {
        SetDefaultAnimatablePropertyValue(textStyle.value(), host);
    }

    textRaceSpaceWidth_ = RACE_SPACE_WIDTH;
    auto pipeline = host->GetContext();
    if (pipeline) {
        textRaceSpaceWidth_ *= pipeline->GetDipScale();
    }

    racePercentFloat_ = MakeRefPtr<AnimatablePropertyFloat>(0.0f);
    AttachProperty(racePercentFloat_);

    if (host->LessThanAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        clip_ = MakeRefPtr<PropertyBool>(true);
    } else {
        clip_ = MakeRefPtr<PropertyBool>(false);
    }
    AttachProperty(clip_);
    fontReady_ = MakeRefPtr<PropertyBool>(false);
    AttachProperty(fontReady_);

    auto baselineOffset = textPattern->GetBaselineOffset();
    paintOffset_ = contentRect.GetOffset() - OffsetF(0.0, std::min(baselineOffset, 0.0f));
}

void TextContentModifier::ChangeDragStatus()
{
    CHECK_NULL_VOID(dragStatus_);
    dragStatus_->Set(!dragStatus_->Get());
}

void TextContentModifier::SetDefaultAnimatablePropertyValue(
    const TextStyle& textStyle, const RefPtr<FrameNode>& frameNode)
{
    SetDefaultFontSize(textStyle);
    SetDefaultAdaptMinFontSize(textStyle);
    SetDefaultAdaptMaxFontSize(textStyle);
    SetDefaultFontWeight(textStyle);
    SetDefaultTextColor(textStyle);
    if (frameNode->GetTag() == V2::SYMBOL_ETS_TAG) {
        SetDefaultSymbolColor(textStyle);
    }
    SetDefaultTextShadow(textStyle);
    SetDefaultTextDecoration(textStyle);
    SetDefaultBaselineOffset(textStyle);
    SetDefaultLineHeight(textStyle);
}

void TextContentModifier::SetDefaultFontSize(const TextStyle& textStyle)
{
    float fontSizeValue = textStyle.GetFontSize().ConvertToPxDistribute(
        textStyle.GetMinFontScale(), textStyle.GetMaxFontScale(), textStyle.IsAllowScale());
    fontSizeFloat_ = MakeRefPtr<AnimatablePropertyFloat>(fontSizeValue);
    AttachProperty(fontSizeFloat_);
}

void TextContentModifier::SetDefaultAdaptMinFontSize(const TextStyle& textStyle)
{
    float fontSizeValue = textStyle.GetFontSize().Value();
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    if (pipelineContext) {
        fontSizeValue = textStyle.GetAdaptMinFontSize().ConvertToPxDistribute(
            textStyle.GetMinFontScale(), textStyle.GetMaxFontScale(), textStyle.IsAllowScale());
    }

    adaptMinFontSizeFloat_ = MakeRefPtr<AnimatablePropertyFloat>(fontSizeValue);
    AttachProperty(adaptMinFontSizeFloat_);
}

void TextContentModifier::SetDefaultAdaptMaxFontSize(const TextStyle& textStyle)
{
    float fontSizeValue = textStyle.GetFontSize().Value();
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    if (pipelineContext) {
        fontSizeValue = textStyle.GetAdaptMaxFontSize().ConvertToPxDistribute(
            textStyle.GetMinFontScale(), textStyle.GetMaxFontScale(), textStyle.IsAllowScale());
    }

    adaptMaxFontSizeFloat_ = MakeRefPtr<AnimatablePropertyFloat>(fontSizeValue);
    AttachProperty(adaptMaxFontSizeFloat_);
}

void TextContentModifier::SetDefaultFontWeight(const TextStyle& textStyle)
{
    fontWeightFloat_ =
        MakeRefPtr<AnimatablePropertyFloat>(static_cast<float>(V2::ConvertFontWeight(textStyle.GetFontWeight())));
    AttachProperty(fontWeightFloat_);
}

void TextContentModifier::SetDefaultTextColor(const TextStyle& textStyle)
{
    animatableTextColor_ = MakeRefPtr<AnimatablePropertyColor>(LinearColor(textStyle.GetTextColor()));
    AttachProperty(animatableTextColor_);
}

void TextContentModifier::SetDefaultSymbolColor(const TextStyle& textStyle)
{
    animatableSymbolColor_ =
        MakeRefPtr<AnimatablePropertyVectorLinearVector>(Convert2VectorLinearColor(textStyle.GetSymbolColorList()));
    AttachProperty(animatableSymbolColor_);
}

void TextContentModifier::SetSymbolColors(const LinearVector<LinearColor>& value)
{
    CHECK_NULL_VOID(animatableSymbolColor_);
    animatableSymbolColor_->Set(value);
}

LinearVector<LinearColor> TextContentModifier::Convert2VectorLinearColor(const std::vector<Color>& colorList)
{
    LinearVector<LinearColor> colors;
    for (auto color : colorList) {
        colors.emplace_back(LinearColor(color));
    }
    return colors;
}

void TextContentModifier::SetDefaultTextShadow(const TextStyle& textStyle)
{
    auto&& textShadows = textStyle.GetTextShadows();
    shadows_.clear();
    shadows_.reserve(textShadows.size());
    for (auto&& textShadow : textShadows) {
        AddShadow(textShadow);
    }
}

void TextContentModifier::AddShadow(const Shadow& shadow)
{
    auto shadowBlurRadiusFloat = MakeRefPtr<AnimatablePropertyFloat>(shadow.GetBlurRadius());
    auto shadowOffsetXFloat = MakeRefPtr<AnimatablePropertyFloat>(shadow.GetOffset().GetX());
    auto shadowOffsetYFloat = MakeRefPtr<AnimatablePropertyFloat>(shadow.GetOffset().GetY());
    auto shadowColor = MakeRefPtr<AnimatablePropertyColor>(LinearColor(shadow.GetColor()));
    Shadow textShadow;
    textShadow.SetBlurRadius(shadow.GetBlurRadius());
    textShadow.SetOffset(shadow.GetOffset());
    textShadow.SetColor(shadow.GetColor());
    shadows_.emplace_back(ShadowProp { .shadow = textShadow,
        .lastShadow = textShadow,
        .blurRadius = shadowBlurRadiusFloat,
        .offsetX = shadowOffsetXFloat,
        .offsetY = shadowOffsetYFloat,
        .color = shadowColor });
    AttachProperty(shadowBlurRadiusFloat);
    AttachProperty(shadowOffsetXFloat);
    AttachProperty(shadowOffsetYFloat);
    AttachProperty(shadowColor);
}

void TextContentModifier::SetDefaultTextDecoration(const TextStyle& textStyle)
{
    textDecoration_ = textStyle.GetTextDecorationFirst();
    textDecorationColor_ = textStyle.GetTextDecorationColor();
    auto alpha = textDecoration_ == TextDecoration::NONE ? 0.0f : textDecorationColor_->GetAlpha();
    textDecorationColorAlpha_ = MakeRefPtr<AnimatablePropertyFloat>(alpha);
    lastTextDecorationColorAlpha_ = alpha;
    AttachProperty(textDecorationColorAlpha_);
}
void TextContentModifier::SetDefaultBaselineOffset(const TextStyle& textStyle)
{
    float baselineOffset = textStyle.GetBaselineOffset().Value();
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    if (pipelineContext) {
        baselineOffset = textStyle.GetBaselineOffset().ConvertToPxDistribute(
            textStyle.GetMinFontScale(), textStyle.GetMaxFontScale(), textStyle.IsAllowScale());
    }

    baselineOffsetFloat_ = MakeRefPtr<AnimatablePropertyFloat>(baselineOffset);
    AttachProperty(baselineOffsetFloat_);
}

void TextContentModifier::SetDefaultLineHeight(const TextStyle& textStyle)
{
    float lineHeight = textStyle.GetLineHeight().Value();
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    if (pipelineContext) {
        lineHeight = textStyle.GetLineHeight().ConvertToPxDistribute(
            textStyle.GetMinFontScale(), textStyle.GetMaxFontScale(), textStyle.IsAllowScale());
    }

    lineHeightFloat_ = MakeRefPtr<AnimatablePropertyFloat>(lineHeight);
    AttachProperty(lineHeightFloat_);
}

void TextContentModifier::SetClip(bool clip)
{
    if (clip_) {
        clip_->Set(clip);
    }
}

void TextContentModifier::SetFontReady(bool value)
{
    if (fontReady_) {
        fontReady_->Set(value);
    }
}

void TextContentModifier::UpdateImageNodeVisible(const VisibleType visible)
{
    for (const auto& imageWeak : imageNodeList_) {
        auto imageNode = imageWeak.Upgrade();
        if (!imageNode) {
            continue;
        }
        auto layoutProperty = imageNode->GetLayoutProperty();
        if (!layoutProperty) {
            continue;
        }
        layoutProperty->UpdateVisibility(visible, true);
    }
}

void TextContentModifier::PaintImage(RSCanvas& canvas, float x, float y)
{
    if (!AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        return;
    }
    auto pattern = DynamicCast<TextPattern>(pattern_.Upgrade());
    CHECK_NULL_VOID(pattern);
    size_t index = 0;
    auto rectsForPlaceholders = pattern->GetRectsForPlaceholders();
    auto placeHolderIndexVector = pattern->GetPlaceHolderIndex();
    auto placeholdersSize = rectsForPlaceholders.size();
    auto placeHolderIndexSize = static_cast<int32_t>(placeHolderIndexVector.size());
    for (const auto& imageWeak : imageNodeList_) {
        auto imageChild = imageWeak.Upgrade();
        if (!imageChild) {
            continue;
        }
        if (index >= placeholdersSize) {
            return;
        }
        auto tmp = static_cast<int32_t>(placeHolderIndexVector.at(index));
        if (tmp >= placeHolderIndexSize || tmp < 0) {
            return;
        }
        auto rect = rectsForPlaceholders.at(tmp);
        if (!DrawImage(imageChild, canvas, x, y, rect)) {
            continue;
        }
        ++index;
    }
}

bool TextContentModifier::DrawImage(const RefPtr<FrameNode>& imageNode, RSCanvas& canvas, float x, float y,
    const RectF& rect)
{
    CHECK_NULL_RETURN(imageNode, false);
    auto imagePattern = DynamicCast<ImagePattern>(imageNode->GetPattern());
    if (!imagePattern) {
        return false;
    }
    auto layoutProperty = imageNode->GetLayoutProperty<ImageLayoutProperty>();
    if (!layoutProperty) {
        return false;
    }
    const auto& marginProperty = layoutProperty->GetMarginProperty();
    float marginTop = 0.0f;
    float marginLeft = 0.0f;
    if (marginProperty) {
        marginLeft = marginProperty->left.has_value() ? marginProperty->left->GetDimension().ConvertToPx() : 0.0f;
        marginTop = marginProperty->top.has_value() ? marginProperty->top->GetDimension().ConvertToPx() : 0.0f;
    }
    auto canvasImage = imagePattern->GetCanvasImage();
    if (!canvasImage) {
        canvasImage = imagePattern->GetAltCanvasImage();
    }
    if (AceType::InstanceOf<AnimatedImage>(canvasImage)) {
        auto animatedImage = DynamicCast<AnimatedImage>(canvasImage);
        if (!animatedImage->GetIsAnimating()) {
            animatedImage->ControlAnimation(true);
        }
    }
    auto geometryNode = imageNode->GetGeometryNode();
    if (!canvasImage || !geometryNode) {
        return false;
    }
    RectF imageRect(rect.Left() + x + marginLeft, rect.Top() + y + marginTop,
        geometryNode->GetFrameSize().Width(), geometryNode->GetFrameSize().Height());
    const auto config = canvasImage->GetPaintConfig();
    SizeF imageSize(canvasImage->GetWidth(), canvasImage->GetHeight());
    SizeF contentSize(geometryNode->GetFrameSize().Width(), geometryNode->GetFrameSize().Height());
    RectF srcRect;
    RectF dstRect;
    ImagePainter::ApplyImageFit(config.imageFit_, imageSize, contentSize, srcRect, dstRect);
    canvasImage->DrawRect(canvas, ToRSRect(srcRect), ToRSRect(imageRect));
    return true;
}

void TextContentModifier::PaintCustomSpan(DrawingContext& drawingContext)
{
    auto pattern = DynamicCast<TextPattern>(pattern_.Upgrade());
    CHECK_NULL_VOID(pattern);
    auto pManager = pattern->GetParagraphManager();
    CHECK_NULL_VOID(pManager);
    auto rectsForPlaceholders = pattern->GetRectsForPlaceholders();
    auto customSpanPlaceholderInfo = pattern->GetCustomSpanPlaceholderInfo();
    auto x = paintOffset_.GetX();
    auto y = paintOffset_.GetY();
    auto rectsForPlaceholderSize = rectsForPlaceholders.size();
    for (const auto& customSpanPlaceholder : customSpanPlaceholderInfo) {
        if (!customSpanPlaceholder.onDraw) {
            continue;
        }
        auto index = customSpanPlaceholder.customSpanIndex;
        if (index >= static_cast<int32_t>(rectsForPlaceholderSize) || index < 0) {
            return;
        }
        auto rect = rectsForPlaceholders.at(index);
        auto lineMetrics = pManager->GetLineMetricsByRectF(rect, customSpanPlaceholder.paragraphIndex);
        CustomSpanOptions customSpanOptions;
        customSpanOptions.x = static_cast<float>(rect.Left()) + x;
        customSpanOptions.lineTop = lineMetrics.y + y;
        customSpanOptions.lineBottom = lineMetrics.y + lineMetrics.height + y;
        customSpanOptions.baseline = lineMetrics.y + lineMetrics.ascender + y;
        customSpanPlaceholder.onDraw(drawingContext, customSpanOptions);
    }
}

void TextContentModifier::onDraw(DrawingContext& drawingContext)
{
    auto info = GetFadeoutInfo(drawingContext);
    if (!info.IsFadeout()) {
        DrawContent(drawingContext, info);
    } else {
        DrawFadeout(drawingContext, info);
    }
}

void TextContentModifier::DrawContent(DrawingContext& drawingContext, const FadeoutInfo& fadeoutInfo)
{
    auto textPattern = DynamicCast<TextPattern>(pattern_.Upgrade());
    CHECK_NULL_VOID(textPattern);
    auto pManager = textPattern->GetParagraphManager();
    CHECK_NULL_VOID(pManager);
    auto host = textPattern->GetHost();
    CHECK_NULL_VOID(host);
    if (pManager->GetParagraphs().empty()) {
        textPattern->DumpRecord("onDraw GetParagraphs empty:" + std::to_string(host->GetId()));
        return;
    }
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto contentRect = geometryNode->GetContentRect();
    ACE_SCOPED_TRACE("[Text][id:%d] paint[offset:%f,%f][contentRect:%s]", host->GetId(), paintOffset_.GetX(),
        paintOffset_.GetY(), contentRect.ToString().c_str());

    SetHybridRenderTypeIfNeeded(drawingContext, textPattern, pManager, host);
    PropertyChangeFlag flag = 0;
    if (NeedMeasureUpdate(flag)) {
        host->MarkDirtyNode(flag);
    }
    if (!ifPaintObscuration_) {
        DrawActualText(drawingContext, textPattern, pManager, fadeoutInfo);
    } else {
        DrawObscuration(drawingContext);
    }
    PaintCustomSpan(drawingContext);
}

void TextContentModifier::DrawActualText(DrawingContext& drawingContext, const RefPtr<TextPattern>& textPattern,
    const RefPtr<ParagraphManager>& pManager, const FadeoutInfo& fadeoutInfo)
{
    auto& canvas = drawingContext.canvas;
    CHECK_NULL_VOID(contentSize_);
    CHECK_NULL_VOID(contentOffset_);
    auto contentSize = contentSize_->Get();
    auto contentOffset = contentOffset_->Get();
    canvas.Save();
    if (clip_ && clip_->Get() &&
        (!fontSize_.has_value() || !fontSizeFloat_ ||
            NearEqual(fontSize_.value().Value(), fontSizeFloat_->Get()))) {
        RSRect clipInnerRect = RSRect(contentOffset.GetX(), contentOffset.GetY(),
            contentSize.Width() + contentOffset.GetX(), contentSize.Height() + contentOffset.GetY());
        canvas.ClipRect(clipInnerRect, RSClipOp::INTERSECT);
    }
    if (!marqueeSet_) {
        auto textEffect = textPattern->GetTextEffect();
        if (!textEffect) {
            DrawText(canvas, pManager, textPattern);
        } else {
            if (SystemProperties::GetTextTraceEnabled()) {
                ACE_TEXT_SCOPED_TRACE("TextContentModifier::DrawContent StartEffect");
            }
            textEffect->StartEffect(canvas, paintOffset_.GetX(), paintOffset_.GetY());
        }
    } else {
        // Racing
        DrawTextRacing(drawingContext, fadeoutInfo, pManager);
    }
    canvas.Restore();
}

void TextContentModifier::SetHybridRenderTypeIfNeeded(DrawingContext& drawingContext,
    const RefPtr<TextPattern>& textPattern, const RefPtr<ParagraphManager>& pManager, RefPtr<FrameNode>& host)
{
#ifdef ENABLE_ROSEN_BACKEND
    RSRecordingCanvas* recordingCanvas = static_cast<RSRecordingCanvas*>(&drawingContext.canvas);
    if (recordingCanvas != nullptr && recordingCanvas->GetDrawCmdList() != nullptr) {
        if (host->IsAtomicNode()) {
            if (Rosen::RSUIDirector::GetHybridRenderSwitch(Rosen::ComponentEnableSwitch::HMSYMBOL)) {
                recordingCanvas->GetDrawCmdList()->SetHybridRenderType(RSHybridRenderType::HMSYMBOL);
            }
        } else {
            if (Rosen::RSUIDirector::GetHybridRenderSwitch(Rosen::ComponentEnableSwitch::TEXTBLOB) &&
                static_cast<uint32_t>(pManager->GetLineCount()) >=
                Rosen::RSUIDirector::GetHybridRenderTextBlobLenCount()) {
                recordingCanvas->GetDrawCmdList()->SetHybridRenderType(RSHybridRenderType::TEXT);
                auto baselineOffset = LessOrEqual(textPattern->GetBaselineOffset(), 0.0) ?
                    std::fabs(textPattern->GetBaselineOffset()) : 0.0;
                const RectF& contentRect = textPattern->GetTextRect();
                RectF boundsRect;
                pManager->GetPaintRegion(boundsRect, contentRect.GetX(), contentRect.GetY() + baselineOffset);
                recordingCanvas->ResetHybridRenderSize(
                    std::max(boundsRect.Width(), pManager->GetLongestLineWithIndent()),
                    std::max(boundsRect.Height(), pManager->GetHeight()));
            }
        }
    }
#endif
}

void TextContentModifier::DrawText(
    RSCanvas& canvas, const RefPtr<ParagraphManager>& pManager, const RefPtr<TextPattern>& textPattern)
{
    auto paintOffsetY = paintOffset_.GetY();
    auto paragraphs = pManager->GetParagraphs();
    std::u16string paragraphContent;
    for (auto&& info : paragraphs) {
        auto paragraph = info.paragraph;
        CHECK_NULL_VOID(paragraph);
        ChangeParagraphColor(paragraph);
        paragraph->Paint(canvas, paintOffset_.GetX(), paintOffsetY);
        paintOffsetY += paragraph->GetHeight();
        paragraphContent += paragraph->GetParagraphText();
    }
    auto host = textPattern->GetHost();
    CHECK_NULL_VOID(host);
    CHECK_NULL_VOID(paragraphContent.length() == 1 && host->GetHostTag() == V2::TEXT_ETS_TAG);
    RSRecordingCanvas* recordingCanvas = static_cast<RSRecordingCanvas*>(&canvas);
    if (recordingCanvas != nullptr && recordingCanvas->GetDrawCmdList() != nullptr &&
        recordingCanvas->GetDrawCmdList()->IsEmpty()) {
        TAG_LOGI(AceLogTag::ACE_TEXT,
            "TextContentModifier::DrawText GetDrawCmdList empty! id:%{public}d LongestLineWithIndent:%{public}f "
            "MaxIntrinsicWidth:%{public}f MaxWidth:%{public}f height:%{public}f lineCount:%{public}d paragraphs "
            "size:%{public}d",
            host->GetId(), pManager->GetLongestLineWithIndent(), pManager->GetMaxIntrinsicWidth(),
            pManager->GetMaxWidth(), pManager->GetHeight(), static_cast<int32_t>(pManager->GetLineCount()),
            static_cast<int32_t>(paragraphs.size()));
    }
}

void TextContentModifier::DrawTextRacing(DrawingContext& drawingContext, const FadeoutInfo& info,
    RefPtr<ParagraphManager> pManager)
{
    CHECK_NULL_VOID(pManager);
    auto paragraph = pManager->GetParagraphs().front().paragraph;
    CHECK_NULL_VOID(paragraph);
    ChangeParagraphColor(paragraph);
    RSCanvas& canvas = drawingContext.canvas;
    if (info.paragraph1EndPosition > 0) {
        paragraph->Paint(canvas, info.paragraph1StartPosition, paintOffset_.GetY());
        PaintImage(canvas, info.paragraph1StartPosition, paintOffset_.GetY());
    }
    if (info.paragraph2StartPosition < drawingContext.width) {
        paragraph->Paint(canvas, info.paragraph2StartPosition, paintOffset_.GetY());
        PaintImage(canvas, info.paragraph2StartPosition, paintOffset_.GetY());
    }
}

void TextContentModifier::ChangeParagraphColor(const RefPtr<Paragraph>& paragraph)
{
    CHECK_NULL_VOID(paragraph);
    if (onlyTextColorAnimation_ && animatableTextColor_) {
        if (SystemProperties::GetTextTraceEnabled()) {
            ACE_TEXT_SCOPED_TRACE("TextContentModifier::ChangeParagraphColor[animatableTextColor:%s]",
                Color(animatableTextColor_->Get().GetValue()).ColorToString().c_str());
        }
        auto length = paragraph->GetParagraphText().length();
        paragraph->UpdateColor(0, length, Color(animatableTextColor_->Get().GetValue()));
    }
}

void TextContentModifier::DrawObscuration(DrawingContext& drawingContext)
{
    RSCanvas& canvas = drawingContext.canvas;
    RSBrush brush;
    std::vector<RSPoint> radiusXY(POINT_COUNT);
    Dimension borderRadius = Dimension(2.0, DimensionUnit::VP);
    for (auto& radius : radiusXY) {
        radius.SetX(static_cast<float>(borderRadius.ConvertToPx()));
        radius.SetY(static_cast<float>(borderRadius.ConvertToPx()));
    }
    CHECK_NULL_VOID(animatableTextColor_);
    Color fillColor = Color(animatableTextColor_->Get().GetValue());
    RSColor rrSColor(fillColor.GetRed(), fillColor.GetGreen(), fillColor.GetBlue(),
        (uint32_t)(fillColor.GetAlpha() * OBSCURED_ALPHA));
    brush.SetColor(rrSColor);
    brush.SetAntiAlias(true);
    canvas.AttachBrush(brush);
    CHECK_NULL_VOID(fontSizeFloat_);
    float fontSize = fontSizeFloat_->Get();
    std::vector<float> textLineWidth;
    float currentLineWidth = 0.0f;
    int32_t maxLineCount = 0;
    CHECK_NULL_VOID(contentSize_);
    CHECK_NULL_VOID(contentOffset_);
    for (auto i = 0U; i < drawObscuredRects_.size(); i++) {
        if (!NearEqual(drawObscuredRects_[i].Width(), 0.0f) && !NearEqual(drawObscuredRects_[i].Height(), 0.0f)) {
            currentLineWidth += drawObscuredRects_[i].Width();
            if (i == (!drawObscuredRects_.empty() ? drawObscuredRects_.size() - 1 : 0)) {
                textLineWidth.push_back(currentLineWidth);
                maxLineCount += LessOrEqual(drawObscuredRects_[i].Bottom(), contentSize_->Get().Height()) ? 1 : 0;
            } else if (!NearEqual(drawObscuredRects_[i].Bottom(), drawObscuredRects_[i + 1].Bottom())) {
                textLineWidth.push_back(currentLineWidth);
                maxLineCount += LessOrEqual(drawObscuredRects_[i].Bottom(), contentSize_->Get().Height()) ? 1 : 0;
                currentLineWidth = 0;
            } else {
                /** nothing to do **/
            }
        }
    }
    CHECK_NULL_VOID(baselineOffsetFloat_);
    auto baselineOffset = baselineOffsetFloat_->Get();
    int32_t obscuredLineCount = std::min(maxLineCount, static_cast<int32_t>(textLineWidth.size()));
    float offsetY = (contentSize_->Get().Height() - std::fabs(baselineOffset) - (obscuredLineCount * fontSize)) /
                    (obscuredLineCount + 1);
    for (auto i = 0; i < obscuredLineCount; i++) {
        RSRoundRect rSRoundRect(
            RSRect(contentOffset_->Get().GetX(),
                contentOffset_->Get().GetY() - std::min(baselineOffset, 0.0f) +
                    std::max(offsetY + ((offsetY + fontSize) * i), 0.0f),
                contentOffset_->Get().GetX() + std::min(textLineWidth[i], contentSize_->Get().Width()),
                contentOffset_->Get().GetY() - std::min(baselineOffset, 0.0f) +
                    std::min(offsetY + ((offsetY + fontSize) * i) + fontSize, contentSize_->Get().Height())),
            radiusXY);
        canvas.DrawRoundRect(rSRoundRect);
    }
    canvas.DetachBrush();
}

void TextContentModifier::ModifyFontSizeInTextStyle(TextStyle& textStyle)
{
    if (fontSize_.has_value() && fontSizeFloat_) {
        lastFontSize_ = fontSizeFloat_->Get();
        textStyle.SetFontSize(Dimension(fontSizeFloat_->Get(), DimensionUnit::PX));
    }
}

void TextContentModifier::ModifyAdaptMinFontSizeInTextStyle(TextStyle& textStyle)
{
    if (adaptMinFontSize_.has_value() && adaptMinFontSizeFloat_) {
        lastMinFontSize_ = adaptMinFontSizeFloat_->Get();
        textStyle.SetAdaptMinFontSize(Dimension(adaptMinFontSizeFloat_->Get(), DimensionUnit::PX));
    }
}

void TextContentModifier::ModifyAdaptMaxFontSizeInTextStyle(TextStyle& textStyle)
{
    if (adaptMaxFontSize_.has_value() && adaptMaxFontSizeFloat_) {
        lastMaxFontSize_ = adaptMaxFontSizeFloat_->Get();
        textStyle.SetAdaptMaxFontSize(Dimension(adaptMaxFontSizeFloat_->Get(), DimensionUnit::PX));
    }
}

void TextContentModifier::ModifyFontWeightInTextStyle(TextStyle& textStyle)
{
    if (fontWeight_.has_value() && fontWeightFloat_) {
        lastFontWeight_ = fontWeightFloat_->Get();
        textStyle.SetFontWeight(static_cast<FontWeight>(std::floor(fontWeightFloat_->Get() + ROUND_VALUE)));
    }
}

void TextContentModifier::ModifyTextColorInTextStyle(Color& textColor)
{
    if (textColor_.has_value() && animatableTextColor_) {
        lastTextColor_.SetValue(animatableTextColor_->Get().GetValue());
        textColor = Color(animatableTextColor_->Get().GetValue());
    }
}

void TextContentModifier::ModifySymbolColorInTextStyle(TextStyle& textStyle)
{
    if (symbolColors_.has_value() && animatableSymbolColor_) {
        lastSymbolColors_= animatableSymbolColor_->Get();
        textStyle.SetSymbolColorList(Convert2VectorColor(animatableSymbolColor_->Get()));
    }
}

std::vector<Color> TextContentModifier::Convert2VectorColor(const LinearVector<LinearColor>& colorList)
{
    std::vector<Color> colors;
    for (auto color : colorList) {
        colors.emplace_back(Color(color.GetValue()));
    }
    return colors;
}

void TextContentModifier::ModifyTextShadowsInTextStyle(TextStyle& textStyle)
{
    std::vector<Shadow> shadows;
    shadows.reserve(shadows_.size());
    for (auto&& shadow : shadows_) {
        auto blurRadius = shadow.blurRadius->Get();
        auto offsetX = shadow.offsetX->Get();
        auto offsetY = shadow.offsetY->Get();
        auto color = shadow.color->Get();
        auto shadowValue = Shadow(blurRadius, 0, Offset(offsetX, offsetY), Color(color.GetValue()));
        shadow.lastShadow = shadowValue;
        shadows.emplace_back(shadowValue);
    }
    textStyle.SetTextShadows(shadows);
}

void TextContentModifier::ModifyDecorationInTextStyle(TextStyle& textStyle)
{
    if (textDecoration_.has_value() && textDecorationColor_.has_value() && textDecorationColorAlpha_) {
        if (textDecorationAnimatable_) {
            uint8_t alpha = static_cast<uint8_t>(std::floor(textDecorationColorAlpha_->Get() + ROUND_VALUE));
            if (alpha == 0) {
                textStyle.SetTextDecoration(TextDecoration::NONE);
                textStyle.SetTextDecorationColor(textDecorationColor_.value());
            } else {
                textStyle.SetTextDecoration(TextDecoration::UNDERLINE);
                textStyle.SetTextDecorationColor(Color(textDecorationColor_.value()).ChangeAlpha(alpha));
            }
            lastTextDecorationColorAlpha_ = textDecorationColorAlpha_->Get();
        } else {
            textStyle.SetTextDecoration(textDecoration_.value());
            textStyle.SetTextDecorationColor(textDecorationColor_.value());
        }
    }
}

void TextContentModifier::ModifyBaselineOffsetInTextStyle(TextStyle& textStyle)
{
    if (baselineOffset_.has_value() && baselineOffsetFloat_) {
        lastBaselineOffsetFloat_ = baselineOffsetFloat_->Get();
        textStyle.SetBaselineOffset(Dimension(baselineOffsetFloat_->Get(), DimensionUnit::PX));
    }
}

void TextContentModifier::ModifyLineHeightInTextStyle(TextStyle& textStyle)
{
    if (lineHeight_.has_value() && lineHeightFloat_) {
        lastLineHeight_ = lineHeightFloat_->Get();
        textStyle.SetLineHeight(Dimension(lineHeightFloat_->Get(), DimensionUnit::PX));
    }
}

void TextContentModifier::ModifyTextStyle(TextStyle& textStyle, Color& textColor)
{
    ModifyFontSizeInTextStyle(textStyle);
    ModifyAdaptMinFontSizeInTextStyle(textStyle);
    ModifyAdaptMaxFontSizeInTextStyle(textStyle);
    ModifyFontWeightInTextStyle(textStyle);
    ModifyTextColorInTextStyle(textColor);
    ModifySymbolColorInTextStyle(textStyle);
    ModifyTextShadowsInTextStyle(textStyle);
    ModifyDecorationInTextStyle(textStyle);
    ModifyBaselineOffsetInTextStyle(textStyle);
    ModifyLineHeightInTextStyle(textStyle);
}

bool TextContentModifier::CheckNeedMeasure(float finalValue, float lastValue, float currentValue)
{
    return !NearEqual(finalValue, currentValue) || !NearEqual(lastValue, currentValue);
}

void TextContentModifier::UpdateFontSizeMeasureFlag(PropertyChangeFlag& flag)
{
    if (fontSize_.has_value() && fontSizeFloat_ &&
        CheckNeedMeasure(fontSize_.value().Value(), lastFontSize_, fontSizeFloat_->Get())) {
        flag |= PROPERTY_UPDATE_MEASURE;
        if (SystemProperties::GetTextTraceEnabled()) {
            ACE_TEXT_SCOPED_TRACE(
                "TextContentModifier::UpdateFontSizeMeasureFlag[fontSize:%f][lastFontSize:%f][fontSizeFloat:%f]",
                fontSize_.value().Value(), lastFontSize_, fontSizeFloat_->Get());
        }
        lastFontSize_ = fontSizeFloat_->Get();
    }
}

void TextContentModifier::UpdateAdaptMinFontSizeMeasureFlag(PropertyChangeFlag& flag)
{
    if (adaptMinFontSize_.has_value() && adaptMinFontSizeFloat_ &&
        CheckNeedMeasure(adaptMinFontSize_.value().Value(), lastMinFontSize_, adaptMinFontSizeFloat_->Get())) {
        flag |= PROPERTY_UPDATE_MEASURE;
        if (SystemProperties::GetTextTraceEnabled()) {
            ACE_TEXT_SCOPED_TRACE("TextContentModifier::UpdateAdaptMinFontSizeMeasureFlag[adaptMinFontSize:%f]["
                                  "lastMinFontSize:%f][adaptMinFontSizeFloat:%f]",
                adaptMinFontSize_.value().Value(), lastMinFontSize_, adaptMinFontSizeFloat_->Get());
        }
        lastMinFontSize_ = adaptMinFontSizeFloat_->Get();
    }
}

void TextContentModifier::UpdateAdaptMaxFontSizeMeasureFlag(PropertyChangeFlag& flag)
{
    if (adaptMaxFontSize_.has_value() && adaptMaxFontSizeFloat_ &&
        CheckNeedMeasure(adaptMaxFontSize_.value().Value(), lastMaxFontSize_, adaptMaxFontSizeFloat_->Get())) {
        flag |= PROPERTY_UPDATE_MEASURE;
        if (SystemProperties::GetTextTraceEnabled()) {
            ACE_TEXT_SCOPED_TRACE("TextContentModifier::UpdateAdaptMaxFontSizeMeasureFlag[adaptMaxFontSize:%f]["
                                  "lastMaxFontSize:%f][adaptMaxFontSizeFloat:%f]",
                adaptMaxFontSize_.value().Value(), lastMaxFontSize_, adaptMaxFontSizeFloat_->Get());
        }
        lastMaxFontSize_ = adaptMaxFontSizeFloat_->Get();
    }
}

void TextContentModifier::UpdateFontWeightMeasureFlag(PropertyChangeFlag& flag)
{
    if (fontWeight_.has_value() && fontWeightFloat_ &&
        CheckNeedMeasure(
            static_cast<float>(static_cast<int>(fontWeight_.value())), lastFontWeight_, fontWeightFloat_->Get())) {
        flag |= PROPERTY_UPDATE_MEASURE;
        if (SystemProperties::GetTextTraceEnabled()) {
            ACE_TEXT_SCOPED_TRACE("TextContentModifier::UpdateFontWeightMeasureFlag[fontWeight:%f][lastFontWeight:%f]["
                                  "fontWeightFloat:%f]",
                static_cast<float>(static_cast<int>(fontWeight_.value())), lastFontWeight_, fontWeightFloat_->Get());
        }
        lastFontWeight_ = fontWeightFloat_->Get();
    }
}

void TextContentModifier::UpdateTextColorMeasureFlag(PropertyChangeFlag& flag)
{
    if (textColor_.has_value() && animatableTextColor_ &&
        (textColor_->GetValue() != animatableTextColor_->Get().GetValue() ||
            lastTextColor_.GetValue() != animatableTextColor_->Get().GetValue())) {
        flag |= PROPERTY_UPDATE_MEASURE_SELF;
        if (SystemProperties::GetTextTraceEnabled()) {
            ACE_TEXT_SCOPED_TRACE("TextContentModifier::UpdateTextColorMeasureFlag[textColor:%s][lastTextColor:%s]["
                                  "animatableTextColor:%s]",
                textColor_->ColorToString().c_str(), lastTextColor_.ColorToString().c_str(),
                Color(animatableTextColor_->Get().GetValue()).ColorToString().c_str());
        }
        lastTextColor_.SetValue(animatableTextColor_->Get().GetValue());
    }
}

void TextContentModifier::UpdateSymbolColorMeasureFlag(PropertyChangeFlag& flag)
{
    if (!symbolColors_.has_value()) {
        return;
    }
    auto pattern = DynamicCast<TextPattern>(pattern_.Upgrade());
    auto host = pattern->GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto symbolColors = layoutProperty->GetSymbolColorList();
    CHECK_NULL_VOID(symbolColors);
    if (!symbolColors.has_value()) {
        return;
    }
    symbolColors_ = Convert2VectorLinearColor(symbolColors.value());
    if (symbolColors_.has_value() && animatableSymbolColor_ &&
        (symbolColors_ != animatableSymbolColor_->Get() || lastSymbolColors_ != animatableSymbolColor_->Get())) {
        flag |= PROPERTY_UPDATE_MEASURE_SELF;
        if (SystemProperties::GetTextTraceEnabled()) {
            ACE_TEXT_SCOPED_TRACE(
                "TextContentModifier::UpdateSymbolColorMeasureFlag");
        }
        lastSymbolColors_ = animatableSymbolColor_->Get();
    }
}

void TextContentModifier::UpdateTextShadowMeasureFlag(PropertyChangeFlag& flag)
{
    for (auto&& shadow : shadows_) {
        auto blurRadius = shadow.blurRadius->Get();
        auto offsetX = shadow.offsetX->Get();
        auto offsetY = shadow.offsetY->Get();
        auto color = shadow.color->Get();
        auto compareShadow = Shadow(blurRadius, 0, Offset(offsetX, offsetY), Color(color.GetValue()));
        if (shadow.shadow != compareShadow || shadow.lastShadow != compareShadow) {
            flag |= PROPERTY_UPDATE_MEASURE;
            if (SystemProperties::GetTextTraceEnabled()) {
                ACE_TEXT_SCOPED_TRACE(
                    "TextContentModifier::UpdateTextShadowMeasureFlag");
            }
            shadow.lastShadow = compareShadow;
            return;
        }
    }
}

void TextContentModifier::UpdateTextDecorationMeasureFlag(PropertyChangeFlag& flag)
{
    if (textDecoration_.has_value() && textDecorationColor_.has_value() && textDecorationColorAlpha_) {
        uint8_t alpha = static_cast<uint8_t>(std::floor(textDecorationColorAlpha_->Get() + ROUND_VALUE));
        if (textDecoration_.value() == TextDecoration::UNDERLINE &&
            (alpha != textDecorationColor_.value().GetAlpha() ||
                !NearEqual(textDecorationColorAlpha_->Get(), lastTextDecorationColorAlpha_))) {
            ACE_TEXT_SCOPED_TRACE(
                "TextContentModifier::UpdateTextDecorationMeasureFlag UNDERLINE");
            flag |= PROPERTY_UPDATE_MEASURE;
        } else if (textDecoration_.value() == TextDecoration::NONE &&
                   (alpha != 0.0 || !NearZero(lastTextDecorationColorAlpha_))) {
            ACE_TEXT_SCOPED_TRACE(
                "TextContentModifier::UpdateTextDecorationMeasureFlag NONE");
            flag |= PROPERTY_UPDATE_MEASURE;
        }
        lastTextDecorationColorAlpha_ = textDecorationColorAlpha_->Get();
    }
}

void TextContentModifier::UpdateBaselineOffsetMeasureFlag(PropertyChangeFlag& flag)
{
    if (baselineOffset_.has_value() && baselineOffsetFloat_ &&
        CheckNeedMeasure(baselineOffset_.value().Value(), lastBaselineOffsetFloat_, baselineOffsetFloat_->Get())) {
        flag |= PROPERTY_UPDATE_MEASURE;
        if (SystemProperties::GetTextTraceEnabled()) {
            ACE_TEXT_SCOPED_TRACE("TextContentModifier::UpdateBaselineOffsetMeasureFlag[baselineOffset:%f]["
                                  "lastBaselineOffsetFloat:%f][baselineOffsetFloat:%f]",
                baselineOffset_.value().Value(), lastBaselineOffsetFloat_, baselineOffsetFloat_->Get());
        }
        lastBaselineOffsetFloat_ = baselineOffsetFloat_->Get();
    }
}

void TextContentModifier::UpdateLineHeightMeasureFlag(PropertyChangeFlag& flag)
{
    if (lineHeight_.has_value() && lineHeightFloat_ &&
        CheckNeedMeasure(lineHeight_.value().Value(), lastLineHeight_, lineHeightFloat_->Get())) {
        flag |= PROPERTY_UPDATE_MEASURE;
        if (SystemProperties::GetTextTraceEnabled()) {
            ACE_TEXT_SCOPED_TRACE("TextContentModifier::UpdateLineHeightMeasureFlag[lineHeight:%f][lastLineHeight:%f]["
                                  "lineHeightFloat:%f]",
                lineHeight_.value().Value(), lastLineHeight_, lineHeightFloat_->Get());
        }
        lastLineHeight_ = lineHeightFloat_->Get();
    }
}

bool TextContentModifier::NeedMeasureUpdate(PropertyChangeFlag& flag)
{
    flag = 0;
    UpdateFontSizeMeasureFlag(flag);
    UpdateAdaptMinFontSizeMeasureFlag(flag);
    UpdateAdaptMaxFontSizeMeasureFlag(flag);
    UpdateFontWeightMeasureFlag(flag);
    UpdateTextShadowMeasureFlag(flag);
    UpdateTextDecorationMeasureFlag(flag);
    UpdateBaselineOffsetMeasureFlag(flag);
    UpdateLineHeightMeasureFlag(flag);
    flag &= (PROPERTY_UPDATE_MEASURE | PROPERTY_UPDATE_MEASURE_SELF | PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
    if (flag) {
        onlyTextColorAnimation_ = false;
    }
    if (!onlyTextColorAnimation_) {
        UpdateTextColorMeasureFlag(flag);
        flag &= (PROPERTY_UPDATE_MEASURE | PROPERTY_UPDATE_MEASURE_SELF | PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
    }
    UpdateSymbolColorMeasureFlag(flag);
    return flag;
}

void TextContentModifier::SetFontSize(const Dimension& value, const TextStyle& textStyle, bool isReset)
{
    auto fontSizeValue =
        value.ConvertToPxDistribute(textStyle.GetMinFontScale(), textStyle.GetMaxFontScale(), textStyle.IsAllowScale());
    if (!isReset) {
        fontSize_ = Dimension(fontSizeValue);
    } else {
        fontSize_ = std::nullopt;
    }
    CHECK_NULL_VOID(fontSizeFloat_);
    fontSizeFloat_->Set(fontSizeValue);
}

void TextContentModifier::SetAdaptMinFontSize(const Dimension& value, const TextStyle& textStyle, bool isReset)
{
    auto fontSizeValue =
        value.ConvertToPxDistribute(textStyle.GetMinFontScale(), textStyle.GetMaxFontScale(), textStyle.IsAllowScale());
    if (!isReset) {
        adaptMinFontSize_ = Dimension(fontSizeValue);
    } else {
        adaptMinFontSize_ = std::nullopt;
    }
    CHECK_NULL_VOID(adaptMinFontSizeFloat_);
    adaptMinFontSizeFloat_->Set(fontSizeValue);
}

void TextContentModifier::SetAdaptMaxFontSize(const Dimension& value, const TextStyle& textStyle, bool isReset)
{
    auto fontSizeValue =
        value.ConvertToPxDistribute(textStyle.GetMinFontScale(), textStyle.GetMaxFontScale(), textStyle.IsAllowScale());
    if (!isReset) {
        adaptMaxFontSize_ = Dimension(fontSizeValue);
    } else {
        adaptMaxFontSize_ = std::nullopt;
    }
    CHECK_NULL_VOID(adaptMaxFontSizeFloat_);
    adaptMaxFontSizeFloat_->Set(fontSizeValue);
}

void TextContentModifier::SetFontWeight(const FontWeight& value, bool isReset)
{
    if (!isReset) {
        fontWeight_ = V2::ConvertFontWeight(value);
    } else {
        fontWeight_ = std::nullopt;
    }
    CHECK_NULL_VOID(fontWeightFloat_);
    fontWeightFloat_->Set(static_cast<int>(V2::ConvertFontWeight(value)));
}

void TextContentModifier::SetTextColor(const Color& value, bool isReset)
{
    onlyTextColorAnimation_ = false;
    if (!isReset) {
        textColor_ = value;
    } else {
        textColor_ = std::nullopt;
    }
    CHECK_NULL_VOID(animatableTextColor_);
    animatableTextColor_->Set(LinearColor(value));
}

void TextContentModifier::TextColorModifier(const Color& value)
{
    SetTextColor(value);
    onlyTextColorAnimation_ = true;
}

void TextContentModifier::SetSymbolColor(const std::vector<Color>& value, bool isReset)
{
    auto colors = Convert2VectorLinearColor(value);
    if (!isReset) {
        symbolColors_ = colors;
    } else {
        symbolColors_ = std::nullopt;
    }
    CHECK_NULL_VOID(animatableSymbolColor_);
    auto animatableColors = animatableSymbolColor_->Get();
    if (colors.size() != animatableColors.size()) {
        AnimationUtils::ExecuteWithoutAnimation([weak = AceType::WeakClaim(this), colors]() {
            auto modifier = weak.Upgrade();
            CHECK_NULL_VOID(modifier);
            modifier->SetSymbolColors(colors);
        });
    } else {
        animatableSymbolColor_->Set(colors);
    }
}

void TextContentModifier::SetTextShadow(const std::vector<Shadow>& value)
{
    while (value.size() > shadows_.size()) {
        AddDefaultShadow();
    }
    // else
    while (value.size() < shadows_.size()) {
        shadows_.pop_back();
    }

    for (size_t i = 0; i < shadows_.size(); ++i) {
        auto&& newShadow = value[i];
        Shadow textShadow;
        textShadow.SetBlurRadius(newShadow.GetBlurRadius());
        textShadow.SetOffset(newShadow.GetOffset());
        textShadow.SetColor(newShadow.GetColor());
        shadows_[i].shadow = textShadow;
        shadows_[i].blurRadius->Set(newShadow.GetBlurRadius());
        shadows_[i].offsetX->Set(newShadow.GetOffset().GetX());
        shadows_[i].offsetY->Set(newShadow.GetOffset().GetY());
        shadows_[i].color->Set(LinearColor(newShadow.GetColor()));
    }
}

void TextContentModifier::SetTextDecoration(const TextDecoration& type, bool isReset)
{
    auto oldTextDecoration = textDecoration_.value_or(TextDecoration::NONE);
    textDecorationAnimatable_ = (oldTextDecoration == TextDecoration::NONE && type == TextDecoration::UNDERLINE) ||
                                (oldTextDecoration == TextDecoration::UNDERLINE && type == TextDecoration::NONE);
    if (oldTextDecoration == type) {
        UpdateTextDecorationColorAlpha();
        return;
    }
    if (!isReset) {
        textDecoration_ = type;
    } else {
        textDecoration_ = std::nullopt;
    }
    UpdateTextDecorationColorAlpha();
}

void TextContentModifier::UpdateTextDecorationColorAlpha()
{
    CHECK_NULL_VOID(textDecorationColorAlpha_);
    if (textDecoration_.has_value() && textDecoration_.value() == TextDecoration::NONE) {
        textDecorationColorAlpha_->Set(0.0f);
    } else if (textDecorationColor_.has_value()) {
        textDecorationColorAlpha_->Set(static_cast<float>(textDecorationColor_.value().GetAlpha()));
    }
}

void TextContentModifier::SetTextDecorationColor(const Color& color, bool isReset)
{
    if (!isReset) {
        textDecorationColor_ = color;
    } else {
        textDecorationColor_ = std::nullopt;
    }
}

void TextContentModifier::SetBaselineOffset(const Dimension& value, const TextStyle& textStyle, bool isReset)
{
    float baselineOffsetValue = 0.0f;
    if (!isReset) {
        baselineOffsetValue = value.ConvertToPxDistribute(
            textStyle.GetMinFontScale(), textStyle.GetMaxFontScale(), textStyle.IsAllowScale());
        baselineOffset_ = Dimension(baselineOffsetValue);
    } else {
        baselineOffset_ = std::nullopt;
    }
    CHECK_NULL_VOID(baselineOffsetFloat_);
    baselineOffsetFloat_->Set(baselineOffsetValue);
}

void TextContentModifier::SetLineHeight(const Dimension& value, const TextStyle& textStyle, bool isReset)
{
    float lineHeightValue = 0.0f;
    if (!isReset) {
        lineHeightValue = value.ConvertToPxDistribute(
            textStyle.GetMinFontScale(), textStyle.GetMaxFontScale(), textStyle.IsAllowScale());
        lineHeight_ = Dimension(lineHeightValue);
    } else {
        lineHeight_ = std::nullopt;
    }
    CHECK_NULL_VOID(lineHeightFloat_);
    lineHeightFloat_->Set(lineHeightValue);
}

void TextContentModifier::SetContentOffset(OffsetF& value)
{
    CHECK_NULL_VOID(contentOffset_);
    contentOffset_->Set(value);
}

void TextContentModifier::SetContentSize(SizeF& value)
{
    CHECK_NULL_VOID(contentSize_);
    contentSize_->Set(value);
}

void TextContentModifier::StartTextRace(const MarqueeOption& option)
{
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        UpdateImageNodeVisible(VisibleType::INVISIBLE);
    }
    if (!SetTextRace(option)) {
        return;
    }

    if (!CheckMarqueeState(MarqueeState::IDLE) && !CheckMarqueeState(MarqueeState::STOPPED)) {
        PauseTextRace();
    }

    marqueeSet_ = true;
    ResumeTextRace(false);

    if (!IsMarqueeVisible()) {
        PauseAnimation();
    }
}

void TextContentModifier::StopTextRace()
{
    marqueeSet_ = false;
    if (!CheckMarqueeState(MarqueeState::RUNNING) && !CheckMarqueeState(MarqueeState::PAUSED)) {
        return;
    }
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        UpdateImageNodeVisible(VisibleType::VISIBLE);
    }
    PauseTextRace();
}

void TextContentModifier::ResumeAnimation()
{
    CHECK_NULL_VOID(raceAnimation_);
    if (!CheckMarqueeState(MarqueeState::PAUSED) || !IsMarqueeVisible()) {
        return;
    }
    AnimationUtils::ResumeAnimation(raceAnimation_);
    SetMarqueeState(MarqueeState::RUNNING);
}

void TextContentModifier::PauseAnimation()
{
    CHECK_NULL_VOID(raceAnimation_);
    if (!CheckMarqueeState(MarqueeState::RUNNING)) {
        return;
    }
    AnimationUtils::PauseAnimation(raceAnimation_);
    SetMarqueeState(MarqueeState::PAUSED);
}

float TextContentModifier::GetTextRacePercent()
{
    float percent = 0;
    if (racePercentFloat_) {
        percent = racePercentFloat_->Get();
    }
    return percent;
}

TextDirection TextContentModifier::GetTextRaceDirection() const
{
    auto textPattern = DynamicCast<TextPattern>(pattern_.Upgrade());
    CHECK_NULL_RETURN(textPattern, TextDirection::LTR);
    auto frameNode = textPattern->GetHost();
    CHECK_NULL_RETURN(frameNode, TextDirection::LTR);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, TextDirection::LTR);
    auto direction = layoutProperty->GetLayoutDirection();
    if (direction == TextDirection::AUTO) {
        direction = GetTextRaceDirectionByContent();
    }
    return direction;
}

TextDirection TextContentModifier::GetTextRaceDirectionByContent() const
{
    auto textPattern = DynamicCast<TextPattern>(pattern_.Upgrade());
    CHECK_NULL_RETURN(textPattern, TextDirection::LTR);
    auto pManager = textPattern->GetParagraphManager();
    CHECK_NULL_RETURN(pManager, TextDirection::LTR);
    if (pManager->GetParagraphs().size() == 0) {
        return TextDirection::LTR;
    }
    auto paragraph = pManager->GetParagraphs().front().paragraph;
    CHECK_NULL_RETURN(paragraph, TextDirection::LTR);
    auto paragraphText = StringUtils::Str16ToStr8(paragraph->GetParagraphText());
    auto content = StringUtils::ToWstring(paragraphText);
    for (const auto& charFromContent : content) {
        if (TextLayoutadapter::IsLeftToRight(charFromContent)) {
            return TextDirection::LTR;
        } else if (TextLayoutadapter::IsRightToLeft(charFromContent)) {
            return TextDirection::RTL;
        } else if (TextLayoutadapter::IsRightTOLeftArabic(charFromContent)) {
            return TextDirection::RTL;
        }
    }
    return AceApplicationInfo::GetInstance().IsRightToLeft() ?
        TextDirection::RTL : TextDirection::LTR;
}

void TextContentModifier::SetRacePercentFloat(float value)
{
    CHECK_NULL_VOID(racePercentFloat_);
    racePercentFloat_->Set(value);
}

void TextContentModifier::ResetTextRacePercent()
{
    if (GetTextRaceDirection() == TextDirection::LTR) {
        // LTR start 0%
        AnimationUtils::ExecuteWithoutAnimation([weak = AceType::WeakClaim(this)]() {
            auto modifier = weak.Upgrade();
            CHECK_NULL_VOID(modifier);
            modifier->SetRacePercentFloat(RACE_MOVE_PERCENT_MIN);
        });
        marqueeRaceMaxPercent_ = RACE_MOVE_PERCENT_MAX + RACE_MOVE_PERCENT_MIN;
        return;
    }
    // RTL
    auto textPattern = DynamicCast<TextPattern>(pattern_.Upgrade());
    CHECK_NULL_VOID(textPattern);
    auto pManager = textPattern->GetParagraphManager();
    CHECK_NULL_VOID(pManager);
    if (pManager->GetParagraphs().size() == 0) {
        return;
    }
    auto paragraph = pManager->GetParagraphs().front().paragraph;
    CHECK_NULL_VOID(paragraph);
    auto textRectWidth = textPattern->GetTextRect().Width();
    float textWidth = paragraph->GetTextWidth();
    float racePercentFloat = 0.0f;
    if (marqueeOption_.direction == MarqueeDirection::LEFT) {
        racePercentFloat = (textWidth - textRectWidth) / (textWidth + textRaceSpaceWidth_) * RACE_MOVE_PERCENT_MAX;
    } else {
        racePercentFloat =
            (textRaceSpaceWidth_ + textRectWidth) / (textWidth + textRaceSpaceWidth_) * RACE_MOVE_PERCENT_MAX -
            RACE_MOVE_PERCENT_MAX;
    }
    marqueeRaceMaxPercent_ = RACE_MOVE_PERCENT_MAX + racePercentFloat;
    AnimationUtils::ExecuteWithoutAnimation([weak = AceType::WeakClaim(this), racePercentFloat]() {
        auto modifier = weak.Upgrade();
        CHECK_NULL_VOID(modifier);
        modifier->SetRacePercentFloat(racePercentFloat);
    });
}

void TextContentModifier::ContentChange()
{
    CHECK_NULL_VOID(contentChange_);
    contentChange_->Set(contentChange_->Get() + 1);
}

void TextContentModifier::AddDefaultShadow()
{
    Shadow emptyShadow;
    auto blurRadius = MakeRefPtr<AnimatablePropertyFloat>(emptyShadow.GetBlurRadius());
    auto offsetX = MakeRefPtr<AnimatablePropertyFloat>(emptyShadow.GetOffset().GetX());
    auto offsetY = MakeRefPtr<AnimatablePropertyFloat>(emptyShadow.GetOffset().GetY());
    auto color = MakeRefPtr<AnimatablePropertyColor>(LinearColor(emptyShadow.GetColor()));
    Shadow textShadow;
    textShadow.SetBlurRadius(emptyShadow.GetBlurRadius());
    textShadow.SetOffset(emptyShadow.GetOffset());
    textShadow.SetColor(emptyShadow.GetColor());
    shadows_.emplace_back(ShadowProp {
        .shadow = textShadow, .blurRadius = blurRadius, .offsetX = offsetX, .offsetY = offsetY, .color = color });
    AttachProperty(blurRadius);
    AttachProperty(offsetX);
    AttachProperty(offsetY);
    AttachProperty(color);
}

void TextContentModifier::SetMarqueeState(MarqueeState state)
{
    auto prevState = marqueeState_;
    marqueeState_ = state;
    auto pattern = DynamicCast<TextPattern>(pattern_.Upgrade());
    CHECK_NULL_VOID(pattern);
    auto host = pattern->GetHost();
    CHECK_NULL_VOID(host);
    TAG_LOGI(AceLogTag::ACE_TEXT, "SetMarqueeState: id %{public}d, from state %{public}d to state %{public}d",
        host->GetId(), prevState, state);
}

void TextContentModifier::ContentModifierDump()
{
    auto& dumpLog = DumpLog::GetInstance();
    if (animatableTextColor_) {
        dumpLog.AddDesc(
            std::string("animatableTextColor: ").append(Color(animatableTextColor_->Get().GetValue()).ColorToString()));
    }
    dumpLog.AddDesc(std::string("onlyTextColorAnimation: ").append(std::to_string(onlyTextColorAnimation_)));
}

void TextContentModifier::SetIsFocused(const bool isFocused)
{
    marqueeFocused_ = isFocused;
    DetermineTextRace();
}

void TextContentModifier::SetIsHovered(const bool isHovered)
{
    marqueeHovered_ = isHovered;
    DetermineTextRace();
}

bool TextContentModifier::SetTextRace(const MarqueeOption& option)
{
    auto textPattern = DynamicCast<TextPattern>(pattern_.Upgrade());
    CHECK_NULL_RETURN(textPattern, false);
    auto pManager = textPattern->GetParagraphManager();
    CHECK_NULL_RETURN(pManager, false);
    textRaceSpaceWidth_ = RACE_SPACE_WIDTH;
    auto pipeline = PipelineContext::GetCurrentContext();
    if (pipeline) {
        textRaceSpaceWidth_ *= pipeline->GetDipScale();
    }

    auto duration =
        static_cast<int32_t>(std::abs(pManager->GetTextWidth() + textRaceSpaceWidth_) * RACE_DURATION_RATIO);
    if (option.step > 0) {
        duration = static_cast<int32_t>(duration / option.step);
    }
    if (duration <= 0) {
        return false;
    }
    auto optionTemp = option;
    if (optionTemp.direction == MarqueeDirection::DEFAULT ||
        optionTemp.direction == MarqueeDirection::DEFAULT_REVERSE) {
        auto textDirection = GetTextRaceDirection();
        optionTemp.direction =
            ((textDirection == TextDirection::LTR && optionTemp.direction == MarqueeDirection::DEFAULT) ||
                (textDirection == TextDirection::RTL && optionTemp.direction == MarqueeDirection::DEFAULT_REVERSE))
                ? MarqueeDirection::LEFT
                : MarqueeDirection::RIGHT;
    }
    if (CheckMarqueeState(MarqueeState::RUNNING) && marqueeOption_ == optionTemp && duration == marqueeDuration_) {
        return false;
    }

    marqueeDuration_ = duration;
    marqueeOption_ = optionTemp;
    ResetTextRacePercent();
    marqueeGradientPercent_ = GetFadeoutPercent();
    return true;
}

void TextContentModifier::ResumeTextRace(bool bounce)
{
    if (!AllowTextRace()) {
        return;
    }
    if (!bounce) {
        marqueeCount_ = 0;
        auto textPattern = DynamicCast<TextPattern>(pattern_.Upgrade());
        CHECK_NULL_VOID(textPattern);
        textPattern->FireOnMarqueeStateChange(TextMarqueeState::START);
    }

    AnimationOption option = AnimationOption();
    RefPtr<Curve> curve = MakeRefPtr<LinearCurve>();
    option.SetDuration(marqueeDuration_);
    option.SetDelay(bounce ? marqueeOption_.delay : 0);
    option.SetCurve(curve);
    option.SetIteration(1);
    SetTextRaceAnimation(option);
}

void TextContentModifier::SetTextRaceAnimation(const AnimationOption& option)
{
    marqueeAnimationId_++;
    ResetTextRacePercent();
    raceAnimation_ = AnimationUtils::StartAnimation(
        option, [weak = AceType::WeakClaim(this)]() {
             auto modifier = weak.Upgrade();
            CHECK_NULL_VOID(modifier);
            float startPercent = modifier->GetTextRacePercent();
            modifier->racePercentFloat_->Set(RACE_MOVE_PERCENT_MAX + startPercent);
        },
        [weak = AceType::WeakClaim(this), marqueeAnimationId = marqueeAnimationId_, id = Container::CurrentId()]() {
            auto modifier = weak.Upgrade();
            CHECK_NULL_VOID(modifier);

            ContainerScope scope(id);
            auto taskExecutor = Container::CurrentTaskExecutor();
            CHECK_NULL_VOID(taskExecutor);

            auto onFinish = [weak, marqueeAnimationId]() {
                auto modifier = weak.Upgrade();
                CHECK_NULL_VOID(modifier);

                if (marqueeAnimationId != modifier->marqueeAnimationId_) {
                    return;
                }
                auto textPattern = DynamicCast<TextPattern>(modifier->pattern_.Upgrade());
                CHECK_NULL_VOID(textPattern);
                if (NearEqual(modifier->GetTextRacePercent(), modifier->marqueeRaceMaxPercent_)) {
                    textPattern->FireOnMarqueeStateChange(TextMarqueeState::BOUNCE);
                    modifier->marqueeCount_++;
                }
                if (!modifier->AllowTextRace()) {
                    textPattern->FireOnMarqueeStateChange(TextMarqueeState::FINISH);
                } else {
                    auto frameNode = textPattern->GetHost();
                    CHECK_NULL_VOID(frameNode);
                    frameNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
                    modifier->ResumeTextRace(true);
                }
            };

            if (taskExecutor->WillRunOnCurrentThread(TaskExecutor::TaskType::UI)) {
                onFinish();
            } else {
                taskExecutor->PostTask(
                    [onFinish]() { onFinish(); }, TaskExecutor::TaskType::UI, "ArkUITextStartTextRace");
            }
        });
    SetMarqueeState(MarqueeState::RUNNING);
}

void TextContentModifier::PauseTextRace()
{
    if (CheckMarqueeState(MarqueeState::IDLE) || CheckMarqueeState(MarqueeState::STOPPED)) {
        return;
    }
    if (raceAnimation_) {
        AnimationUtils::StopAnimation(raceAnimation_);
    }

    SetMarqueeState(MarqueeState::STOPPED);
    ResetTextRacePercent();
}

bool TextContentModifier::AllowTextRace()
{
    if (!marqueeSet_ || !marqueeOption_.start) {
        return false;
    }
    if (marqueeOption_.loop > 0 && marqueeCount_ >= marqueeOption_.loop) {
        return false;
    }
    if (marqueeOption_.startPolicy == MarqueeStartPolicy::ON_FOCUS && !(marqueeFocused_ || marqueeHovered_)) {
        return false;
    }

    return true;
}

void TextContentModifier::DetermineTextRace()
{
    if (!marqueeSet_ || !marqueeOption_.start || marqueeOption_.startPolicy != MarqueeStartPolicy::ON_FOCUS) {
        return;
    }

    auto textRaceing = CheckMarqueeState(MarqueeState::RUNNING);
    if (textRaceing && !marqueeFocused_ && !marqueeHovered_) {
        PauseTextRace();
        return;
    }
    if (!textRaceing && (marqueeFocused_ || marqueeHovered_)) {
        ResumeTextRace(false);
    }
}

float TextContentModifier::GetFadeoutPercent()
{
    marqueeGradientPercent_ = DEFAULT_FADEOUT_GRADIENTPERCENT;

    auto contentWidth = contentSize_->Get().Width();
    if (contentWidth > 0) {
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_RETURN(pipeline, marqueeGradientPercent_);
        auto theme = pipeline->GetTheme<TextTheme>();
        CHECK_NULL_RETURN(theme, marqueeGradientPercent_);
        auto fadeoutWidth = theme->GetFadeoutWidth();
        marqueeGradientPercent_ = fadeoutWidth.ConvertToPx() / contentWidth;
    }
    return marqueeGradientPercent_;
}

FadeoutInfo TextContentModifier::GetFadeoutInfo(DrawingContext& drawingContext)
{
    FadeoutInfo info;
    if (!marqueeSet_) {
        return info;
    }
    CHECK_NULL_RETURN(contentSize_, info);
    CHECK_NULL_RETURN(contentOffset_, info);
    auto textPattern = DynamicCast<TextPattern>(pattern_.Upgrade());
    CHECK_NULL_RETURN(textPattern, info);
    auto pManager = textPattern->GetParagraphManager();
    CHECK_NULL_RETURN(pManager, info);
    float racePercent = GetTextRacePercent();
    float textRacePercent =
        marqueeOption_.direction == MarqueeDirection::LEFT ? racePercent : RACE_MOVE_PERCENT_MAX - racePercent;
    auto paragraphText = pManager->GetParagraphs().front().paragraph;
    float textWidth = paragraphText->GetTextWidth();
    info.paragraph1StartPosition =
        paintOffset_.GetX() + (textWidth + textRaceSpaceWidth_) * textRacePercent / RACE_MOVE_PERCENT_MAX * -1;
    info.paragraph1EndPosition = info.paragraph1StartPosition + textWidth;
    info.paragraph2StartPosition = info.paragraph1EndPosition + textRaceSpaceWidth_;
    info.paragraph2EndPosition = info.paragraph2StartPosition + textWidth;
    if (marqueeOption_.fadeout) {
        auto contentSize = contentSize_->Get();
        auto contentOffset = contentOffset_->Get();
        float contentStartPosition = contentOffset.GetX();
        float contentEndPosition = contentStartPosition + contentSize.Width();
        info.isLeftFadeout = (LessNotEqual(info.paragraph1StartPosition, contentStartPosition) &&
                                 GreatNotEqual(info.paragraph1EndPosition, contentStartPosition)) ||
                             (LessNotEqual(info.paragraph2StartPosition, contentStartPosition) &&
                                 GreatNotEqual(info.paragraph2EndPosition, contentStartPosition));
        info.isRightFadeout = (LessNotEqual(info.paragraph1StartPosition, contentEndPosition) &&
                                  GreatNotEqual(info.paragraph1EndPosition, contentEndPosition)) ||
                              (LessNotEqual(info.paragraph2StartPosition, contentEndPosition) &&
                                  GreatNotEqual(info.paragraph2EndPosition, contentEndPosition));
    } else {
        info.isLeftFadeout = false;
        info.isRightFadeout = false;
    }
    if (info.IsFadeout()) {
        marqueeGradientPercent_ = GetFadeoutPercent();
        if (marqueeGradientPercent_ > RACE_MIN_GRADIENTPERCENT) {
            marqueeGradientPercent_ = RACE_MIN_GRADIENTPERCENT;
        }
        info.fadeoutPercent = marqueeGradientPercent_;
    }
    return info;
}

void TextContentModifier::DrawFadeout(DrawingContext& drawingContext, const FadeoutInfo& info)
{
    auto textPattern = DynamicCast<TextPattern>(pattern_.Upgrade());
    CHECK_NULL_VOID(textPattern);

    RSCanvas& canvas = drawingContext.canvas;
    auto contentRect = textPattern->GetTextContentRect();
    auto contentSize = contentSize_->Get();
    RSRect clipInnerRect = RSRect(0, 0, drawingContext.width + ROUND_VALUE, drawingContext.height);

    RSSaveLayerOps slo(&clipInnerRect, nullptr);
    canvas.SaveLayer(slo);

    DrawContent(drawingContext, info);

    RSBrush brush;
    auto contentOffset = contentOffset_->Get();
    std::vector<RSPoint> points = { RSPoint(contentRect.Left(), contentRect.Top()),
        RSPoint(contentSize.Width() + contentOffset.GetX(), contentRect.Top()) };
    std::vector<RSColorQuad> colors = { Color::TRANSPARENT.GetValue(), Color::WHITE.GetValue(), Color::WHITE.GetValue(),
        Color::TRANSPARENT.GetValue() };
    std::vector<RSScalar> pos = { 0.0f, info.isLeftFadeout ? info.fadeoutPercent : 0.0f,
        info.isRightFadeout ? (1 - info.fadeoutPercent) : 1.0f, 1.0f };
    brush.SetShaderEffect(
        RSShaderEffect::CreateLinearGradient(points.at(0), points.at(1), colors, pos, RSTileMode::CLAMP));
    brush.SetBlendMode(RSBlendMode::DST_IN);
    canvas.AttachBrush(brush);
    canvas.DrawRect(clipInnerRect);
    canvas.DetachBrush();
    canvas.Restore();
}

bool TextContentModifier::IsMarqueeVisible() const
{
    auto textPattern = DynamicCast<TextPattern>(pattern_.Upgrade());
    CHECK_NULL_RETURN(textPattern, true);
    auto host = textPattern->GetHost();
    CHECK_NULL_RETURN(host, true);
    RectF visibleRect;
    RectF visibleInnerRect;
    RectF frameRect;
    host->GetVisibleRectWithClip(visibleRect, visibleInnerRect, frameRect);
    return Positive(visibleInnerRect.Width()) && Positive(visibleInnerRect.Height());
}
} // namespace OHOS::Ace::NG
