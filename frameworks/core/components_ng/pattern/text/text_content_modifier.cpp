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

#include "base/utils/utils.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_v2/inspector/utils.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float RACE_MOVE_PERCENT_MIN = 0.0f;
constexpr float RACE_MOVE_PERCENT_MAX = 100.0f;
constexpr float RACE_TEMPO = 0.2f;
constexpr uint32_t RACE_DURATION = 2000;
constexpr float RACE_SPACE_WIDTH = 48.0f;
constexpr float ROUND_VALUE = 0.5f;
constexpr uint32_t POINT_COUNT = 4;
constexpr float OBSCURED_ALPHA = 0.2f;
const FontWeight FONT_WEIGHT_CONVERT_MAP[] = {
    FontWeight::W100,
    FontWeight::W200,
    FontWeight::W300,
    FontWeight::W400,
    FontWeight::W500,
    FontWeight::W600,
    FontWeight::W700,
    FontWeight::W800,
    FontWeight::W900,
    FontWeight::W700,       // FontWeight::BOLD
    FontWeight::W400,       // FontWeight::NORMAL
    FontWeight::W900,       // FontWeight::BOLDER,
    FontWeight::W100,       // FontWeight::LIGHTER
    FontWeight::W500,       // FontWeight::MEDIUM
    FontWeight::W400,       // FontWeight::REGULAR
};

inline FontWeight ConvertFontWeight(FontWeight fontWeight)
{
    return FONT_WEIGHT_CONVERT_MAP[(int)fontWeight];
}
} // namespace

TextContentModifier::TextContentModifier(const std::optional<TextStyle>& textStyle)
{
    contentChange_ = MakeRefPtr<PropertyInt>(0);
    AttachProperty(contentChange_);
    contentOffset_ = MakeRefPtr<PropertyOffsetF>(OffsetF());
    contentSize_ = MakeRefPtr<PropertySizeF>(SizeF());
    AttachProperty(contentOffset_);
    AttachProperty(contentSize_);

    if (textStyle.has_value()) {
        SetDefaultAnimatablePropertyValue(textStyle.value());
    }

    racePercentFloat_ = MakeRefPtr<AnimatablePropertyFloat>(0.0f);
    AttachProperty(racePercentFloat_);
    clip_ = MakeRefPtr<PropertyBool>(true);
    AttachProperty(clip_);
    fontFamilyString_ = MakeRefPtr<PropertyString>("");
    AttachProperty(fontFamilyString_);
    fontReady_ = MakeRefPtr<PropertyBool>(false);
    AttachProperty(fontReady_);
}

void TextContentModifier::SetDefaultAnimatablePropertyValue(const TextStyle& textStyle)
{
    SetDefaultFontSize(textStyle);
    SetDefaultFontWeight(textStyle);
    SetDefaultTextColor(textStyle);
    SetDefaultTextShadow(textStyle);
    SetDefaultTextDecoration(textStyle);
    SetDefaultBaselineOffset(textStyle);
}

void TextContentModifier::SetDefaultFontSize(const TextStyle& textStyle)
{
    float fontSizeValue = textStyle.GetFontSize().Value();
    auto pipelineContext = PipelineContext::GetCurrentContext();
    if (pipelineContext) {
        fontSizeValue = pipelineContext->NormalizeToPx(textStyle.GetFontSize());
        if (textStyle.IsAllowScale() || textStyle.GetFontSize().Unit() == DimensionUnit::FP) {
            fontSizeValue = pipelineContext->NormalizeToPx(textStyle.GetFontSize() * pipelineContext->GetFontScale());
        }
    }

    fontSizeFloat_ = MakeRefPtr<AnimatablePropertyFloat>(fontSizeValue);
    AttachProperty(fontSizeFloat_);
}

void TextContentModifier::SetDefaultFontWeight(const TextStyle& textStyle)
{
    fontWeightFloat_ =
        MakeRefPtr<AnimatablePropertyFloat>(static_cast<float>(ConvertFontWeight(textStyle.GetFontWeight())));
    AttachProperty(fontWeightFloat_);
}

void TextContentModifier::SetDefaultTextColor(const TextStyle& textStyle)
{
    animatableTextColor_ = MakeRefPtr<AnimatablePropertyColor>(LinearColor(textStyle.GetTextColor()));
    AttachProperty(animatableTextColor_);
}

void TextContentModifier::SetDefaultTextShadow(const TextStyle& textStyle)
{
    auto&& textShadows = textStyle.GetTextShadows();
    if (textShadows.empty()) {
        AddDefaultShadow();
        return;
    }
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
    shadows_.emplace_back(ShadowProp { .shadow = shadow,
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
    textDecoration_ = textStyle.GetTextDecoration();
    textDecorationStyle_ = textStyle.GetTextDecorationStyle();
    textDecorationColor_ = textStyle.GetTextDecorationColor();
    textDecorationColorAlpha_ = MakeRefPtr<AnimatablePropertyFloat>(
        textDecoration_ == TextDecoration::NONE ? 0.0f : textDecorationColor_->GetAlpha());
    AttachProperty(textDecorationColorAlpha_);
}
void TextContentModifier::SetDefaultBaselineOffset(const TextStyle& textStyle)
{
    float baselineOffset = textStyle.GetBaselineOffset().Value();
    auto pipelineContext = PipelineContext::GetCurrentContext();
    if (pipelineContext) {
        baselineOffset = pipelineContext->NormalizeToPx(textStyle.GetBaselineOffset());
    }

    baselineOffsetFloat_ = MakeRefPtr<AnimatablePropertyFloat>(baselineOffset);
    AttachProperty(baselineOffsetFloat_);
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

void TextContentModifier::onDraw(DrawingContext& drawingContext)
{
    bool ifPaintObscuration = std::any_of(obscuredReasons_.begin(), obscuredReasons_.end(),
        [](const auto& reason) { return reason == ObscuredReasons::PLACEHOLDER; });
    if (!ifPaintObscuration || ifHaveSpanItemChildren_) {
        CHECK_NULL_VOID(paragraph_);
        auto& canvas = drawingContext.canvas;
        canvas.Save();
        if (!textRacing_) {
            auto contentSize = contentSize_->Get();
            auto contentOffset = contentOffset_->Get();
            if (clip_ && clip_->Get() &&
                (!fontSize_.has_value() || !fontSizeFloat_ ||
                    NearEqual(fontSize_.value().Value(), fontSizeFloat_->Get()))) {
                RSRect clipInnerRect = RSRect(contentOffset.GetX(), contentOffset.GetY(),
                    contentSize.Width() + contentOffset.GetX(), contentSize.Height() + contentOffset.GetY());
                canvas.ClipRect(clipInnerRect, RSClipOp::INTERSECT);
            }

            paragraph_->Paint(canvas, paintOffset_.GetX(), paintOffset_.GetY());
        } else {
            // Racing
            float textRacePercent = GetTextRacePercent();
            if (clip_ && clip_->Get()) {
                canvas.ClipRect(RSRect(0, 0, drawingContext.width, drawingContext.height), RSClipOp::INTERSECT);
            }
            float paragraph1Offset =
                (paragraph_->GetTextWidth() + textRaceSpaceWidth_) * textRacePercent / RACE_MOVE_PERCENT_MAX * -1;
            if ((paintOffset_.GetX() + paragraph1Offset + paragraph_->GetTextWidth()) > 0) {
                paragraph_->Paint(drawingContext.canvas, paintOffset_.GetX() + paragraph1Offset, paintOffset_.GetY());
            }
            float paragraph2Offset = paragraph1Offset + paragraph_->GetTextWidth() + textRaceSpaceWidth_;
            if ((paintOffset_.GetX() + paragraph2Offset) < drawingContext.width) {
                paragraph_->Paint(drawingContext.canvas, paintOffset_.GetX() + paragraph2Offset, paintOffset_.GetY());
            }
        }
        canvas.Restore();
    } else {
        DrawObscuration(drawingContext);
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
            if (i == drawObscuredRects_.size() - 1) {
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
    int32_t obscuredLineCount = std::min(maxLineCount, static_cast<int32_t>(textLineWidth.size()));
    float offsetY = (contentSize_->Get().Height() - (obscuredLineCount * fontSize)) / (obscuredLineCount + 1);
    for (auto i = 0; i < obscuredLineCount; i++) {
        RSRoundRect rSRoundRect(
            RSRect(contentOffset_->Get().GetX(),
                contentOffset_->Get().GetY() + std::max(offsetY + ((offsetY + fontSize) * i), 0.0f),
                contentOffset_->Get().GetX() + std::min(textLineWidth[i], contentSize_->Get().Width()),
                contentOffset_->Get().GetY() +
                    std::min(offsetY + ((offsetY + fontSize) * i) + fontSize, contentSize_->Get().Height())),
            radiusXY);
        canvas.DrawRoundRect(rSRoundRect);
    }
}

void TextContentModifier::ModifyFontSizeInTextStyle(TextStyle& textStyle)
{
    if (fontSize_.has_value() && fontSizeFloat_) {
        textStyle.SetFontSize(Dimension(fontSizeFloat_->Get(), DimensionUnit::PX));
    }
}

void TextContentModifier::ModifyFontWeightInTextStyle(TextStyle& textStyle)
{
    if (fontWeight_.has_value() && fontWeightFloat_) {
        textStyle.SetFontWeight(static_cast<FontWeight>(std::floor(fontWeightFloat_->Get() + ROUND_VALUE)));
    }
}

void TextContentModifier::ModifyTextColorInTextStyle(TextStyle& textStyle)
{
    if (textColor_.has_value() && animatableTextColor_) {
        textStyle.SetTextColor(Color(animatableTextColor_->Get().GetValue()));
    }
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
        shadows.emplace_back(blurRadius, 0, Offset(offsetX, offsetY), Color(color.GetValue()));
    }
    textStyle.SetTextShadows(shadows);
}

void TextContentModifier::ModifyDecorationInTextStyle(TextStyle& textStyle)
{
    if (textDecoration_.has_value() && textDecorationColor_.has_value() && textDecorationColorAlpha_) {
        if (textDecorationAnimatable_) {
            uint8_t alpha = static_cast<int>(std::floor(textDecorationColorAlpha_->Get() + ROUND_VALUE));
            if (alpha == 0) {
                textStyle.SetTextDecoration(TextDecoration::NONE);
                textStyle.SetTextDecorationColor(textDecorationColor_.value());
            } else {
                textStyle.SetTextDecoration(TextDecoration::UNDERLINE);
                textStyle.SetTextDecorationColor(Color(textDecorationColor_.value()).ChangeAlpha(alpha));
            }
        } else {
            textStyle.SetTextDecoration(textDecoration_.value());
            textStyle.SetTextDecorationColor(textDecorationColor_.value());
        }
    }
    if (textDecorationStyle_.has_value()) {
        textStyle.SetTextDecorationStyle(textDecorationStyle_.value());
    }
}

void TextContentModifier::ModifyBaselineOffsetInTextStyle(TextStyle& textStyle)
{
    if (baselineOffset_.has_value() && baselineOffsetFloat_) {
        textStyle.SetBaselineOffset(Dimension(baselineOffsetFloat_->Get(), DimensionUnit::PX));
    }
}

void TextContentModifier::ModifyTextStyle(TextStyle& textStyle)
{
    ModifyFontSizeInTextStyle(textStyle);
    ModifyFontWeightInTextStyle(textStyle);
    ModifyTextColorInTextStyle(textStyle);
    ModifyTextShadowsInTextStyle(textStyle);
    ModifyDecorationInTextStyle(textStyle);
    ModifyBaselineOffsetInTextStyle(textStyle);
}

void TextContentModifier::UpdateFontSizeMeasureFlag(PropertyChangeFlag& flag)
{
    if (fontSize_.has_value() && fontSizeFloat_ && !NearEqual(fontSize_.value().Value(), fontSizeFloat_->Get())) {
        flag |= PROPERTY_UPDATE_MEASURE;
    }
}

void TextContentModifier::UpdateFontWeightMeasureFlag(PropertyChangeFlag& flag)
{
    if (fontWeight_.has_value() && fontWeightFloat_ &&
        !NearEqual(static_cast<float>(static_cast<int>(fontWeight_.value())), fontWeightFloat_->Get())) {
        flag |= PROPERTY_UPDATE_MEASURE;
    }
}

void TextContentModifier::UpdateTextColorMeasureFlag(PropertyChangeFlag& flag)
{
    if (textColor_.has_value() && animatableTextColor_ &&
        textColor_->GetValue() != animatableTextColor_->Get().GetValue()) {
        flag |= PROPERTY_UPDATE_MEASURE_SELF;
    }
}

void TextContentModifier::UpdateTextShadowMeasureFlag(PropertyChangeFlag& flag)
{
    for (auto&& shadow : shadows_) {
        auto blurRadius = shadow.blurRadius->Get();
        auto offsetX = shadow.offsetX->Get();
        auto offsetY = shadow.offsetY->Get();
        auto color = shadow.color->Get();
        if (shadow.shadow != Shadow(blurRadius, 0, Offset(offsetX, offsetY), Color(color.GetValue()))) {
            flag |= PROPERTY_UPDATE_MEASURE;
            return;
        }
    }
}

void TextContentModifier::UpdateTextDecorationMeasureFlag(PropertyChangeFlag& flag)
{
    if (textDecoration_.has_value() && textDecorationColor_.has_value() && textDecorationColorAlpha_) {
        uint8_t alpha = static_cast<int>(std::floor(textDecorationColorAlpha_->Get() + ROUND_VALUE));
        if (textDecoration_.value() == TextDecoration::UNDERLINE && alpha != textDecorationColor_.value().GetAlpha()) {
            flag |= PROPERTY_UPDATE_MEASURE;
        } else if (textDecoration_.value() == TextDecoration::NONE && alpha != 0.0) {
            flag |= PROPERTY_UPDATE_MEASURE;
        }
    }
}

void TextContentModifier::UpdateBaselineOffsetMeasureFlag(PropertyChangeFlag& flag)
{
    if (baselineOffset_.has_value() && baselineOffsetFloat_ &&
        !NearEqual(baselineOffset_.value().Value(), baselineOffsetFloat_->Get())) {
        flag |= PROPERTY_UPDATE_MEASURE;
    }
}

bool TextContentModifier::NeedMeasureUpdate(PropertyChangeFlag& flag)
{
    flag = 0;
    UpdateFontSizeMeasureFlag(flag);
    UpdateFontWeightMeasureFlag(flag);
    UpdateTextColorMeasureFlag(flag);
    UpdateTextShadowMeasureFlag(flag);
    UpdateTextDecorationMeasureFlag(flag);
    UpdateBaselineOffsetMeasureFlag(flag);
    flag &= (PROPERTY_UPDATE_MEASURE | PROPERTY_UPDATE_MEASURE_SELF | PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
    return flag;
}

void TextContentModifier::SetFontFamilies(const std::vector<std::string>& value)
{
    CHECK_NULL_VOID(fontFamilyString_);
    fontFamilyString_->Set(V2::ConvertFontFamily(value));
}

void TextContentModifier::SetFontSize(const Dimension& value)
{
    float fontSizeValue;
    auto pipelineContext = PipelineContext::GetCurrentContext();
    if (pipelineContext) {
        fontSizeValue = pipelineContext->NormalizeToPx(value);
    } else {
        fontSizeValue = value.Value();
    }
    fontSize_ = Dimension(fontSizeValue);
    CHECK_NULL_VOID(fontSizeFloat_);
    fontSizeFloat_->Set(fontSizeValue);
}

void TextContentModifier::SetFontWeight(const FontWeight& value)
{
    fontWeight_ = ConvertFontWeight(value);
    CHECK_NULL_VOID(fontWeightFloat_);
    fontWeightFloat_->Set(static_cast<int>(ConvertFontWeight(value)));
}

void TextContentModifier::SetTextColor(const Color& value)
{
    textColor_ = value;
    CHECK_NULL_VOID(animatableTextColor_);
    animatableTextColor_->Set(LinearColor(value));
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
        shadows_[i].shadow = newShadow;
        shadows_[i].blurRadius->Set(newShadow.GetBlurRadius());
        shadows_[i].offsetX->Set(newShadow.GetOffset().GetX());
        shadows_[i].offsetY->Set(newShadow.GetOffset().GetY());
        shadows_[i].color->Set(LinearColor(newShadow.GetColor()));
    }
}

void TextContentModifier::SetTextDecoration(const TextDecoration& type)
{
    auto oldTextDecoration = textDecoration_.value_or(TextDecoration::NONE);
    if (oldTextDecoration == type) {
        return;
    }

    textDecorationAnimatable_ = (oldTextDecoration == TextDecoration::NONE && type == TextDecoration::UNDERLINE) ||
                                (oldTextDecoration == TextDecoration::UNDERLINE && type == TextDecoration::NONE);

    textDecoration_ = type;
    CHECK_NULL_VOID(textDecorationColorAlpha_);

    oldColorAlpha_ = textDecorationColorAlpha_->Get();
    if (textDecoration_ == TextDecoration::NONE) {
        textDecorationColorAlpha_->Set(0.0f);
    } else {
        textDecorationColorAlpha_->Set(static_cast<float>(textDecorationColor_.value().GetAlpha()));
    }
}

void TextContentModifier::SetTextDecorationStyle(const TextDecorationStyle textDecorationStyle)
{
    textDecorationStyle_ = textDecorationStyle;
}

void TextContentModifier::SetTextDecorationColor(const Color& color)
{
    textDecorationColor_ = color;
}

void TextContentModifier::SetBaselineOffset(const Dimension& value)
{
    float baselineOffsetValue;
    auto pipelineContext = PipelineContext::GetCurrentContext();
    if (pipelineContext) {
        baselineOffsetValue = pipelineContext->NormalizeToPx(value);
    } else {
        baselineOffsetValue = value.Value();
    }
    baselineOffset_ = Dimension(baselineOffsetValue);
    CHECK_NULL_VOID(baselineOffsetFloat_);
    baselineOffsetFloat_->Set(baselineOffsetValue);
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

void TextContentModifier::StartTextRace()
{
    if (textRacing_) {
        return;
    }

    textRacing_ = true;

    textRaceSpaceWidth_ = RACE_SPACE_WIDTH;
    auto pipeline = PipelineContext::GetCurrentContext();
    if (pipeline) {
        textRaceSpaceWidth_ *= pipeline->GetDipScale();
    }

    AnimationOption option = AnimationOption();
    RefPtr<Curve> curve = MakeRefPtr<LinearCurve>();
    option.SetDuration(RACE_DURATION);
    option.SetDelay(0);
    option.SetCurve(curve);
    option.SetIteration(-1);
    option.SetTempo(RACE_TEMPO);
    raceAnimation_ = AnimationUtils::StartAnimation(option, [&]() { racePercentFloat_->Set(RACE_MOVE_PERCENT_MAX); });
}

void TextContentModifier::StopTextRace()
{
    if (!textRacing_) {
        return;
    }

    if (raceAnimation_) {
        AnimationUtils::StopAnimation(raceAnimation_);
    }

    textRacing_ = false;
    racePercentFloat_->Set(RACE_MOVE_PERCENT_MIN);
}

float TextContentModifier::GetTextRacePercent()
{
    float percent = 0;
    if (racePercentFloat_) {
        percent = racePercentFloat_->Get();
    }
    return percent;
}

void TextContentModifier::ContentChange()
{
    CHECK_NULL_VOID(contentChange_);
    contentChange_->Set(contentChange_->Get()+ 1);
}

void TextContentModifier::AddDefaultShadow()
{
    Shadow emptyShadow;
    auto blurRadius = MakeRefPtr<AnimatablePropertyFloat>(emptyShadow.GetBlurRadius());
    auto offsetX = MakeRefPtr<AnimatablePropertyFloat>(emptyShadow.GetOffset().GetX());
    auto offsetY = MakeRefPtr<AnimatablePropertyFloat>(emptyShadow.GetOffset().GetY());
    auto color = MakeRefPtr<AnimatablePropertyColor>(LinearColor(emptyShadow.GetColor()));
    shadows_.emplace_back(
        ShadowProp { .blurRadius = blurRadius, .offsetX = offsetX, .offsetY = offsetY, .color = color });
    AttachProperty(blurRadius);
    AttachProperty(offsetX);
    AttachProperty(offsetY);
    AttachProperty(color);
}
} // namespace OHOS::Ace::NG
