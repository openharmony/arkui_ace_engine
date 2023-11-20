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
#include "core/components_ng/pattern/security_component/security_component_layout_element.h"

#include "base/log/ace_scoring_log.h"
#include "base/memory/ace_type.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/security_component/security_component_layout_property.h"
#include "core/components_ng/pattern/security_component/security_component_theme.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/property/measure_property.h"
#include "core/pipeline_ng/pipeline_context.h"
#ifdef ENABLE_ROSEN_BACKEND
#include "core/components/custom_paint/rosen_render_custom_paint.h"
#endif

namespace OHOS::Ace::NG {
void IconLayoutElement::Init(RefPtr<SecurityComponentLayoutProperty>& property,
    RefPtr<LayoutWrapper>& iconWrap)
{
    secCompProperty_ = property;
    iconWrap_ = iconWrap;
    CHECK_NULL_VOID(property);
    CHECK_NULL_VOID(iconWrap);
    if (property->GetIconStyle().value_or(-1) ==
        static_cast<int32_t>(SecurityComponentIconStyle::ICON_NULL)) {
        return;
    }
    isExist_ = true;

    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SecurityComponentTheme>();
    CHECK_NULL_VOID(theme);
    minIconSize_ = theme->GetMinIconSize().ConvertToPx();

    if (property->GetIconSize().has_value()) {
        isSetSize_ = true;
        width_ = height_ = property->GetIconSize().value().ConvertToPx();
    } else {
        width_ = height_ = theme->GetIconSize().ConvertToPx();
    }
}

void IconLayoutElement::DoMeasure()
{
    if (!isExist_) {
        return;
    }
    auto iconConstraint = secCompProperty_->CreateChildConstraint();
    iconConstraint.selfIdealSize.SetWidth(width_);
    iconConstraint.selfIdealSize.SetHeight(height_);
    iconWrap_->Measure(iconConstraint);
}

double IconLayoutElement::ShrinkWidth(double reduceSize)
{
    if (!isExist_ || isSetSize_) {
        return reduceSize;
    }
    if (GreatNotEqual(minIconSize_, (width_ - reduceSize))) {
        int remain = reduceSize - (width_ - minIconSize_);
        height_ = width_ = minIconSize_;
        return remain;
    }

    width_ -= reduceSize;
    height_ = width_;
    return 0.0;
}

double IconLayoutElement::ShrinkHeight(double reduceSize)
{
    if (!isExist_ || isSetSize_) {
        return reduceSize;
    }
    if (GreatNotEqual(minIconSize_, (height_ - reduceSize))) {
        double remain = reduceSize - (height_ - minIconSize_);
        width_ = height_ = minIconSize_;
        return remain;
    }
    height_ -= reduceSize;
    width_ = height_;
    return 0.0;
}

void TextLayoutElement::Init(RefPtr<SecurityComponentLayoutProperty>& property,
    RefPtr<LayoutWrapper>& textWrap)
{
    secCompProperty_ = property;
    textWrap_ = textWrap;
    CHECK_NULL_VOID(property);
    CHECK_NULL_VOID(textWrap);
    if (property->GetSecurityComponentDescription().value_or(-1) ==
            static_cast<int32_t>(SecurityComponentDescription::TEXT_NULL)) {
        return;
    }
    isExist_ = true;

    auto textProp = AceType::DynamicCast<TextLayoutProperty>(textWrap_->GetLayoutProperty());
    CHECK_NULL_VOID(textProp);
    auto theme = PipelineContext::GetCurrentContext()->GetTheme<SecurityComponentTheme>();
    CHECK_NULL_VOID(theme);
    minFontSize_ = theme->GetMinFontSize();
    if (property->GetFontSize().has_value()) {
        isSetSize_ = true;
    } else {
        defaultFontSize_ = theme->GetFontSize();
        textProp->UpdateFontSize(defaultFontSize_);
    }

    auto textConstraint = property->CreateChildConstraint();
    SizeT<float> maxSize { Infinity<float>(), Infinity<float>() };
    textConstraint.maxSize = maxSize;
    textWrap_->Measure(std::optional<LayoutConstraintF>(textConstraint));
    auto textSizeF = textWrap->GetGeometryNode()->GetFrameSize();
    width_ = textSizeF.Width();
    height_ = textSizeF.Height();
}

void TextLayoutElement::ChooseExactFontSize(RefPtr<TextLayoutProperty>& property, bool isWidth)
{
    if (!minTextSize_.has_value()) {
        property->UpdateFontSize(minFontSize_);
        return;
    }
    constexpr Dimension ADAPT_UNIT = 1.0_fp;
    Dimension step = ADAPT_UNIT;
    Dimension fontSize = (property->GetFontSize().has_value()) ? property->GetFontSize().value() : defaultFontSize_;
    while (fontSize > minFontSize_) {
        auto tempSize = GetMeasureTextSize(property->GetContent().value_or(""),
            fontSize,
            property->GetFontWeight().value_or(FontWeight::NORMAL));
        if (!tempSize.has_value()) {
            fontSize = minFontSize_;
            break;
        }
        if (isWidth) {
            if (GreatOrEqual(width_, tempSize.value().Width())) {
                break;
            }
        } else {
            if (GreatOrEqual(height_, tempSize.value().Height())) {
                break;
            }
        }
        fontSize -= step;
    }
    property->UpdateFontSize(fontSize);
}

void TextLayoutElement::UpdateSize(bool isWidth)
{
    auto textProp = AceType::DynamicCast<TextLayoutProperty>(textWrap_->GetLayoutProperty());
    CHECK_NULL_VOID(textProp);
    ChooseExactFontSize(textProp, isWidth);
    auto textConstraint = textProp->GetContentLayoutConstraint();
    CHECK_NULL_VOID(textConstraint);
    if (isWidth) {
        textConstraint->selfIdealSize.SetWidth(width_);
    } else {
        textConstraint->selfIdealSize.SetHeight(height_);
    }

    textWrap_->Measure(textConstraint);
    auto textSizeF = textWrap_->GetGeometryNode()->GetFrameSize();
    width_ = textSizeF.Width();
    height_ = textSizeF.Height();
}

std::optional<SizeF> TextLayoutElement::GetMeasureTextSize(const std::string& data,
    const Dimension& fontSize, FontWeight fontWeight)
{
#ifdef ENABLE_ROSEN_BACKEND
    MeasureContext content;
    content.textContent = data;
    content.fontSize = fontSize;
    auto fontweight = StringUtils::FontWeightToString(fontWeight);
    content.fontWeight = fontweight;
    auto size = RosenRenderCustomPaint::MeasureTextSizeInner(content);
    return SizeF(size.Width(), size.Height());
#else
    return std::nullopt;
#endif
}

void TextLayoutElement::MeasureMinTextSize()
{
    auto textProp = AceType::DynamicCast<TextLayoutProperty>(textWrap_->GetLayoutProperty());
    CHECK_NULL_VOID(textProp);
    minTextSize_ = GetMeasureTextSize(textProp->GetContent().value_or(""),
        minFontSize_,
        textProp->GetFontWeight().value_or(FontWeight::NORMAL));
}

double TextLayoutElement::ShrinkWidth(double reduceSize)
{
    if (!isExist_ || isSetSize_) {
        return reduceSize;
    }
    if (!minTextSize_.has_value()) {
        MeasureMinTextSize();
    }
    double minTextWidth = minTextSize_.value_or(SizeT(0.0F, 0.0F)).Width();
    if (GreatNotEqual(minTextWidth, (width_ - reduceSize))) {
        int remain = reduceSize - (width_ - minTextWidth);
        width_ = minTextWidth;
        UpdateSize(true);
        return remain;
    }

    width_ -= reduceSize;
    UpdateSize(true);
    return 0.0;
}

double TextLayoutElement::ShrinkHeight(double reduceSize)
{
    if (!isExist_ || isSetSize_) {
        return reduceSize;
    }
    if (!minTextSize_.has_value()) {
        MeasureMinTextSize();
    }

    double minTextHeight = minTextSize_.value_or(SizeT(0.0F, 0.0F)).Height();
    if (GreatNotEqual(minTextHeight, (height_ - reduceSize))) {
        double remain = reduceSize - (height_ - minTextHeight);
        height_ = minTextHeight;
        UpdateSize(false);
        return remain;
    }
    height_ -= reduceSize;
    UpdateSize(false);
    return 0.0;
}
};
