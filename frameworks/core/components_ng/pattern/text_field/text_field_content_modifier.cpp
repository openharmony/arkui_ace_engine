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

#include "core/components_ng/pattern/text_field/text_field_content_modifier.h"

#include "base/utils/utils.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/drawing_prop_convertor.h"
#include "core/components_ng/render/image_painter.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
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
    FontWeight::W700,
    FontWeight::W400,
    FontWeight::W900,
    FontWeight::W100,
    FontWeight::W500,
    FontWeight::W400,
};
constexpr Dimension ERROR_TEXT_UNDERLINE_MARGIN = 8.0_vp;
constexpr Dimension ERROR_TEXT_CAPSULE_MARGIN = 8.0_vp;
constexpr Dimension COUNTER_TEXT_AREA_MARGIN = 8.0_vp;

inline FontWeight ConvertFontWeight(FontWeight fontWeight)
{
    return FONT_WEIGHT_CONVERT_MAP[(int)fontWeight];
}
} // namespace

TextFieldContentModifier::TextFieldContentModifier(const WeakPtr<OHOS::Ace::NG::Pattern>& pattern) : pattern_(pattern)
{
    SetDefaultAnimatablePropertyValue();
    SetDefaultPropertyValue();
}

void TextFieldContentModifier::onDraw(DrawingContext& context)
{
    auto canvas = context.canvas;
    auto textFieldPattern = DynamicCast<TextFieldPattern>(pattern_.Upgrade());
    CHECK_NULL_VOID(textFieldPattern);
    auto offset = contentOffset_->Get();
    auto passwordIconCanvasImage = textObscured_->Get() ? textFieldPattern->GetHidePasswordIconCanvasImage()
                                                        : textFieldPattern->GetShowPasswordIconCanvasImage();
    auto paragraph = textFieldPattern->GetParagraph();
    CHECK_NULL_VOID(paragraph);
    auto contentSize = contentSize_->Get();
    auto textFrameRect = textFieldPattern->GetFrameRect();
    auto contentOffset = contentOffset_->Get();
    auto iconRect = textFieldPattern->GetImageRect();
    auto counterParagraph = textFieldPattern->GetCounterParagraph();
    auto errorParagraph = textFieldPattern->GetErrorParagraph();
    auto clipRectHeight = 0.0f;
    auto errorMargin = 0.0f;
    auto errorViewHeight = 0.0f;
    auto textPartten = pattern_.Upgrade();
    CHECK_NULL_VOID(textPartten);
    auto frameNode = textPartten->GetHost();
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (layoutProperty->GetShowUnderlineValue(false) && showErrorState_->Get()) {
        errorMargin = ERROR_TEXT_UNDERLINE_MARGIN.ConvertToPx();
    } else if (textFieldPattern->NeedShowPasswordIcon() && showErrorState_->Get()) {
        errorMargin = ERROR_TEXT_CAPSULE_MARGIN.ConvertToPx();
    } else if (showErrorState_->Get()) {
        errorMargin = ERROR_TEXT_CAPSULE_MARGIN.ConvertToPx();
    } else {
        errorMargin = 0;
    }
    if (errorParagraph && showErrorState_->Get()) {
        errorViewHeight = textFrameRect.Bottom() - textFrameRect.Top() + errorMargin;
    }
    if (showCounter_->Get() && counterParagraph && !textFieldPattern->GetIsCounterIdealHeight()) {
        clipRectHeight = contentOffset.GetY() + contentSize.Height() - textFieldPattern->GetCountHeight();
    } else {
        clipRectHeight = contentOffset.GetY() + contentSize.Height() + errorViewHeight;
    }
    canvas.Save();
    RSRect clipInnerRect = RSRect(offset.GetX(), contentOffset.GetY(), contentSize.Width() + contentOffset.GetX() -
        textFieldPattern->GetUnitWidth() + textFieldPattern->GetInlinePadding(), clipRectHeight);
    canvas.ClipRect(clipInnerRect, RSClipOp::INTERSECT);
    if (paragraph) {
        paragraph->Paint(
            &canvas, textRectX_->Get(), textFieldPattern->IsTextArea() ? textRectY_->Get() : contentOffset.GetY());
    }
    canvas.Restore();
    if (showCounter_->Get() && counterParagraph) {
        counterParagraph->Paint(&canvas, textRectX_->Get(),
            textFrameRect.Bottom() - textFrameRect.Top() - COUNTER_TEXT_AREA_MARGIN.ConvertToPx() -
                textFieldPattern->GetCountHeight());
    }
    canvas.Save();
    if (showErrorState_->Get() && errorParagraph && !textFieldPattern->IsDisabled()) {
        errorParagraph->Paint(&canvas, offset.GetX(), textFrameRect.Bottom() - textFrameRect.Top() + errorMargin);
    }

    clipInnerRect = RSRect(contentSize.Width() + contentOffset.GetX() - textFieldPattern->GetUnitWidth(),
        contentOffset.GetY(), contentSize.Width() + contentOffset.GetX(), contentOffset.GetY() + contentSize.Height());
    canvas.ClipRect(clipInnerRect, RSClipOp::INTERSECT);
    canvas.Restore();

    if (!textFieldPattern->NeedShowPasswordIcon()) {
        return;
    }
    CHECK_NULL_VOID(passwordIconCanvasImage);
    UpdatePaintConfig(passwordIconCanvasImage, context, iconRect);
    const ImagePainter passwordIconImagePainter(passwordIconCanvasImage);
    canvas.Save();
    auto iconRight = std::min(textFrameRect.Width(), iconRect.Width()) + iconRect.GetX();
    auto iconBottom = std::min(textFrameRect.Height(), iconRect.Height()) + iconRect.GetY();
    clipInnerRect = RSRect(iconRect.GetX(), iconRect.GetY(), iconRight, iconBottom);
    canvas.ClipRect(clipInnerRect, RSClipOp::INTERSECT);
    passwordIconImagePainter.DrawImage(canvas, iconRect.GetOffset(), iconRect.GetSize());
    canvas.Restore();
}

void TextFieldContentModifier::UpdatePaintConfig(
    RefPtr<CanvasImage>& passwordIconCanvasImage, DrawingContext context, RectF iconRect) const
{
    CHECK_NULL_VOID(passwordIconCanvasImage);
    auto&& config = passwordIconCanvasImage->GetPaintConfig();
    config.renderMode_ = ImageRenderMode::ORIGINAL;
    config.imageInterpolation_ = ImageInterpolation::NONE;
    config.imageRepeat_ = ImageRepeat::NO_REPEAT;
    config.imageFit_ = ImageFit::FILL;
    if (context.height == 0 || context.width == 0) {
        return;
    }
    config.scaleX_ = iconRect.GetSize().Width() / context.width;
    config.scaleY_ = iconRect.GetSize().Height() / context.height;
}

void TextFieldContentModifier::SetDefaultAnimatablePropertyValue()
{
    RefPtr<TextTheme> theme;
    RefPtr<TextFieldLayoutProperty> textFieldLayoutProperty;
    RefPtr<PipelineContext> pipelineContext;
    auto textPartten = pattern_.Upgrade();
    CHECK_NULL_VOID(textPartten);
    auto frameNode = textPartten->GetHost();
    CHECK_NULL_VOID(frameNode);
    pipelineContext = frameNode->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    theme = pipelineContext->GetTheme<TextTheme>();
    textFieldLayoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    TextStyle textStyle = CreateTextStyleUsingTheme(
        textFieldLayoutProperty->GetFontStyle(), textFieldLayoutProperty->GetTextLineStyle(), theme);
    SetDefaultFontSize(textStyle);
    SetDefaultFontWeight(textStyle);
    SetDefaultTextColor(textStyle);
    SetDefaultFontStyle(textStyle);
}

void TextFieldContentModifier::SetDefaultPropertyValue()
{
    RefPtr<TextFieldTheme> theme;
    RefPtr<PipelineContext> pipelineContext;
    auto textPattern = pattern_.Upgrade();
    CHECK_NULL_VOID(textPattern);
    auto frameNode = textPattern->GetHost();
    CHECK_NULL_VOID(frameNode);
    pipelineContext = frameNode->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    theme = pipelineContext->GetTheme<TextFieldTheme>();
    auto textFieldPattern = DynamicCast<TextFieldPattern>(pattern_.Upgrade());

    textObscured_ = AceType::MakeRefPtr<PropertyBool>(textFieldPattern->GetTextObscured());
    dragStatus_ = AceType::MakeRefPtr<PropertyBool>(false);
    contentOffset_ = AceType::MakeRefPtr<PropertyOffsetF>(
        OffsetF(textFieldPattern->GetTextRect().GetX(), textFieldPattern->GetTextRect().GetY()));
    contentSize_ = AceType::MakeRefPtr<PropertySizeF>(SizeF());
    textValue_ = AceType::MakeRefPtr<PropertyString>("");
    errorTextValue_ = AceType::MakeRefPtr<PropertyString>("");
    placeholderValue_ = AceType::MakeRefPtr<PropertyString>("");
    textRectY_ = AceType::MakeRefPtr<PropertyFloat>(textFieldPattern->GetTextRect().GetY());
    textRectX_ = AceType::MakeRefPtr<PropertyFloat>(textFieldPattern->GetTextRect().GetX());
    textAlign_ = AceType::MakeRefPtr<PropertyInt>(static_cast<int32_t>(TextAlign::START));
    showCounter_ = AceType::MakeRefPtr<PropertyBool>(false);
    showErrorState_ = AceType::MakeRefPtr<PropertyBool>(false);
    showPasswordIconSrc_ = AceType::MakeRefPtr<PropertyString>("");
    hidePasswordIconSrc_ = AceType::MakeRefPtr<PropertyString>("");
    fontFamilyString_ = AceType::MakeRefPtr<PropertyString>("");
    fontReady_ = AceType::MakeRefPtr<PropertyBool>(false);
    AttachProperty(contentOffset_);
    AttachProperty(contentSize_);
    AttachProperty(textValue_);
    AttachProperty(errorTextValue_);
    AttachProperty(placeholderValue_);
    AttachProperty(textRectY_);
    AttachProperty(textObscured_);
    AttachProperty(dragStatus_);
    AttachProperty(textRectX_);
    AttachProperty(textAlign_);
    AttachProperty(showCounter_);
    AttachProperty(showErrorState_);
    AttachProperty(showUnderline_);
    AttachProperty(showPasswordIconSrc_);
    AttachProperty(hidePasswordIconSrc_);
    AttachProperty(fontFamilyString_);
    AttachProperty(fontReady_);
}

void TextFieldContentModifier::SetDefaultFontSize(const TextStyle& textStyle)
{
    float fontSizeValue;
    auto pipelineContext = PipelineContext::GetCurrentContext();
    if (pipelineContext) {
        fontSizeValue = pipelineContext->NormalizeToPx(textStyle.GetFontSize());
        if (textStyle.IsAllowScale() || textStyle.GetFontSize().Unit() == DimensionUnit::FP) {
            fontSizeValue = pipelineContext->NormalizeToPx(textStyle.GetFontSize() * pipelineContext->GetFontScale());
        }
    } else {
        fontSizeValue = textStyle.GetFontSize().ConvertToPx();
    }

    fontSizeFloat_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(fontSizeValue);
    AttachProperty(fontSizeFloat_);
}

void TextFieldContentModifier::SetDefaultFontWeight(const TextStyle& textStyle)
{
    fontWeightFloat_ =
        AceType::MakeRefPtr<AnimatablePropertyFloat>(static_cast<float>(ConvertFontWeight(textStyle.GetFontWeight())));
    AttachProperty(fontWeightFloat_);
}

void TextFieldContentModifier::SetDefaultTextColor(const TextStyle& textStyle)
{
    animatableTextColor_ = AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor(textStyle.GetTextColor()));
    AttachProperty(animatableTextColor_);
}

void TextFieldContentModifier::SetDefaultFontStyle(const TextStyle& textStyle)
{
    fontStyle_ = AceType::MakeRefPtr<PropertyInt>(static_cast<int32_t>(textStyle.GetFontStyle()));
    AttachProperty(fontStyle_);
}

void TextFieldContentModifier::ModifyTextStyle(TextStyle& textStyle)
{
    if (fontSize_.has_value() && fontSizeFloat_) {
        textStyle.SetFontSize(Dimension(fontSizeFloat_->Get(), DimensionUnit::PX));
    }
    if (fontWeight_.has_value() && fontWeightFloat_) {
        textStyle.SetFontWeight(static_cast<FontWeight>(std::floor(fontWeightFloat_->Get() + 0.5f)));
    }
    if (textColor_.has_value() && animatableTextColor_) {
        textStyle.SetTextColor(Color(animatableTextColor_->Get().GetValue()));
    }
}

void TextFieldContentModifier::SetFontFamilies(const std::vector<std::string>& value)
{
    CHECK_NULL_VOID(fontFamilyString_);
    fontFamilyString_->Set(V2::ConvertFontFamily(value));
}

void TextFieldContentModifier::SetFontSize(const Dimension& value)
{
    auto valPx = static_cast<float>(value.ConvertToPx());
    fontSize_ = Dimension(valPx);
    CHECK_NULL_VOID(fontSizeFloat_);
    fontSizeFloat_->Set(valPx);
}

void TextFieldContentModifier::SetFontWeight(const FontWeight& value)
{
    fontWeight_ = ConvertFontWeight(value);
    CHECK_NULL_VOID(fontWeightFloat_);
    fontWeightFloat_->Set(static_cast<int>(ConvertFontWeight(value)));
}

void TextFieldContentModifier::SetTextColor(const Color& value)
{
    textColor_ = value;
    CHECK_NULL_VOID(animatableTextColor_);
    animatableTextColor_->Set(LinearColor(value));
}

void TextFieldContentModifier::SetFontStyle(const OHOS::Ace::FontStyle& value)
{
    if (fontStyle_->Get() != static_cast<int32_t>(value)) {
        fontStyle_->Set(static_cast<int32_t>(value));
    }
}

void TextFieldContentModifier::SetContentOffset(OffsetF& value)
{
    if (contentOffset_) {
        contentOffset_->Set(value);
    }
}

float TextFieldContentModifier::GetContentOffsetY()
{
    return contentOffset_->Get().GetY();
}

void TextFieldContentModifier::SetContentSize(SizeF& value)
{
    if (contentSize_) {
        contentSize_->Set(value);
    }
}

void TextFieldContentModifier::SetTextValue(std::string& value)
{
    if (textValue_->Get() != value) {
        textValue_->Set(value);
    }
}

void TextFieldContentModifier::SetErrorTextValue(const std::string& value)
{
    if (errorTextValue_->Get() != value) {
        errorTextValue_->Set(value);
    }
}

void TextFieldContentModifier::SetPlaceholderValue(std::string&& value)
{
    if (placeholderValue_->Get() != value) {
        placeholderValue_->Set(value);
    }
}

void TextFieldContentModifier::SetTextRectY(const float value)
{
    if (textRectY_->Get() != value) {
        textRectY_->Set(value);
    }
}

float TextFieldContentModifier::GetTextRectY()
{
    return textRectY_->Get();
}

void TextFieldContentModifier::SetTextObscured(bool value)
{
    if (textObscured_) {
        textObscured_->Set(value);
    }
}

void TextFieldContentModifier::ChangeDragStatus()
{
    dragStatus_->Set(!dragStatus_->Get());
}

void TextFieldContentModifier::SetTextRectX(const float value)
{
    if (textRectX_->Get() != value) {
        textRectX_->Set(value);
    }
}

float TextFieldContentModifier::GetTextRectX()
{
    return textRectX_->Get();
}

void TextFieldContentModifier::SetTextAlign(const TextAlign value)
{
    if (textAlign_->Get() != static_cast<int32_t>(value)) {
        textAlign_->Set(static_cast<int32_t>(value));
    }
}

void TextFieldContentModifier::SetShowCounter(bool value)
{
    if (showCounter_) {
        showCounter_->Set(value);
    }
}

void TextFieldContentModifier::SetShowErrorState(bool value)
{
    if (showErrorState_) {
        showErrorState_->Set(value);
    }
}

void TextFieldContentModifier::SetShowUnderlineState(bool value)
{
    if (showUnderline_) {
        showUnderline_->Set(value);
    }
}

void TextFieldContentModifier::SetShowPasswordIcon(const std::string& value)
{
    if (showPasswordIconSrc_->Get() != value) {
        showPasswordIconSrc_->Set(value);
    }
}

void TextFieldContentModifier::SetHidePasswordIcon(const std::string& value)
{
    if (hidePasswordIconSrc_->Get() != value) {
        hidePasswordIconSrc_->Set(value);
    }
}

void TextFieldContentModifier::SetFontReady(bool value)
{
    if (fontReady_) {
        fontReady_->Set(value);
    }
}

bool TextFieldContentModifier::NeedMeasureUpdate(PropertyChangeFlag& flag)
{
    flag = 0;
    if (fontSize_.has_value() && fontSizeFloat_ && !NearEqual(fontSize_.value().Value(), fontSizeFloat_->Get())) {
        flag |= PROPERTY_UPDATE_MEASURE;
    }
    if (fontWeight_.has_value() && fontWeightFloat_ &&
        !NearEqual(static_cast<float>(fontWeight_.value()), fontWeightFloat_->Get())) {
        flag |= PROPERTY_UPDATE_MEASURE;
    }
    if (textColor_.has_value() && animatableTextColor_ &&
        textColor_->GetValue() != animatableTextColor_->Get().GetValue()) {
        flag |= PROPERTY_UPDATE_MEASURE_SELF;
    }
    flag &= (PROPERTY_UPDATE_MEASURE | PROPERTY_UPDATE_MEASURE_SELF | PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
    return flag;
}
} // namespace OHOS::Ace::NG
