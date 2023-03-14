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
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/drawing_prop_convertor.h"
#include "core/components_ng/render/image_painter.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
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

inline FontWeight ConvertFontWeight(FontWeight fontWeight)
{
    return FONT_WEIGHT_CONVERT_MAP[(int)fontWeight];
}
} // namespace

TextFieldContentModifier::TextFieldContentModifier(const WeakPtr<OHOS::Ace::NG::Pattern>& pattern)
    : pattern_(pattern)
{
    SetDefaultAnimatablePropertyValue();
    contentOffset_ = AceType::MakeRefPtr<PropertyOffsetF>(OffsetF());
    contentSize_ = AceType::MakeRefPtr<PropertySizeF>(SizeF());
    textValue_ = AceType::MakeRefPtr<PropertyString>("");
    auto textFieldPattern = DynamicCast<TextFieldPattern>(pattern_.Upgrade());
    textObscured_ = AceType::MakeRefPtr<PropertyBool>(textFieldPattern->GetTextObscured());

    AttachProperty(contentOffset_);
    AttachProperty(contentSize_);
    AttachProperty(textValue_);
    AttachProperty(textObscured_);
}

void TextFieldContentModifier::onDraw(DrawingContext& context)
{
    auto canvas = context.canvas;
    auto textFieldPattern = DynamicCast<TextFieldPattern>(pattern_.Upgrade());
    CHECK_NULL_VOID(textFieldPattern);
    auto offset = contentOffset_->Get();
    auto passwordIconCanvasImage = textObscured_->Get()
                                       ? textFieldPattern->GetHidePasswordIconCanvasImage()
                                       : textFieldPattern->GetShowPasswordIconCanvasImage();
    auto paragraph = textFieldPattern->GetParagraph();
    CHECK_NULL_VOID(paragraph);
    auto contentSize = contentSize_->Get();
    auto contentOffset = contentOffset_->Get();
    auto iconRect = textFieldPattern->GetImageRect();
    RSRect clipInnerRect = RSRect(offset.GetX(), contentOffset.GetY(),
        contentSize.Width() + contentOffset.GetX(), contentOffset.GetY() + contentSize.Height());
    canvas.ClipRect(clipInnerRect, RSClipOp::INTERSECT);
    if (paragraph) {
        paragraph->Paint(&canvas, textFieldPattern->GetTextRect().GetX(),
            textFieldPattern->IsTextArea() ? textFieldPattern->GetTextRect().GetY() : contentOffset.GetY());
    }
    canvas.Restore();
    if (!textFieldPattern->NeedShowPasswordIcon()) {
        return;
    }
    CHECK_NULL_VOID_NOLOG(passwordIconCanvasImage);
    clipInnerRect = RSRect(
        offset.GetX(), 0.0f, textFieldPattern->GetFrameRect().Width(), textFieldPattern->GetFrameRect().Height());
    canvas.ClipRect(clipInnerRect, RSClipOp::UNION);
    const ImagePainter passwordIconImagePainter(passwordIconCanvasImage);
    passwordIconImagePainter.DrawImage(canvas, iconRect.GetOffset(), iconRect.GetSize());
}

RefPtr<OHOS::Ace::NG::PipelineContext> TextFieldContentModifier::GetPipelineContext()
{
    RefPtr<PipelineContext> pipelineContext;
    auto textPartten = pattern_.Upgrade();
    CHECK_NULL_RETURN(textPartten, nullptr);
    auto frameNode = textPartten->GetHost();
    CHECK_NULL_RETURN(frameNode, nullptr);
    pipelineContext = frameNode->GetContext();
    return pipelineContext;
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
    TextStyle textStyle = CreateTextStyleUsingTheme(textFieldLayoutProperty->GetFontStyle(),
        textFieldLayoutProperty->GetTextLineStyle(), theme);
    SetDefaultFontSize(textStyle);
    SetDefaultFontWeight(textStyle);
    SetDefaultTextColor(textStyle);
}

void TextFieldContentModifier::SetDefaultFontSize(const TextStyle& textStyle)
{
    float fontSizeValue;
    auto pipelineContext = GetPipelineContext();
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
    fontWeightFloat_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(
        static_cast<float>(ConvertFontWeight(textStyle.GetFontWeight())));
    AttachProperty(fontWeightFloat_);
}

void TextFieldContentModifier::SetDefaultTextColor(const TextStyle& textStyle)
{
    animatableTextColor_ = AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor(textStyle.GetTextColor()));
    AttachProperty(animatableTextColor_);
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

void TextFieldContentModifier::SetFontSize(const Dimension& value)
{
    float fontSizeValue;
    auto pipelineContext = GetPipelineContext();
    if (pipelineContext) {
        fontSizeValue = pipelineContext->NormalizeToPx(value);
    } else {
        fontSizeValue = value.ConvertToPx();
    }
    fontSize_ = Dimension(fontSizeValue);
    CHECK_NULL_VOID(fontSizeFloat_);
    fontSizeFloat_->Set(fontSizeValue);
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

void TextFieldContentModifier::SetContentOffset(OffsetF& value)
{
    if (contentOffset_) {
        contentOffset_->Set(value);
    }
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

void TextFieldContentModifier::SetTextObscured(bool value)
{
    if (textObscured_) {
        textObscured_->Set(value);
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
