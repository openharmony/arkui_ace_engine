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

#include "core/components_ng/pattern/text/text_layout_algorithm.h"

#include <unicode/uchar.h>

#include "base/i18n/localization.h"
#include "base/utils/utils.h"
#include "core/components/font/constants_converter.h"
#include "core/components/text/text_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/render/font_collection.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
TextLayoutAlgorithm::TextLayoutAlgorithm() = default;

void TextLayoutAlgorithm::OnReset()
{
    CHECK_NULL_VOID(paragraph_);
    paragraph_->Reset();
}

std::optional<SizeF> TextLayoutAlgorithm::MeasureContent(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(frameNode, std::nullopt);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_RETURN(pipeline, std::nullopt);
    auto textLayoutProperty = DynamicCast<TextLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(textLayoutProperty, std::nullopt);
    const auto& textParagraph = textLayoutProperty->GetTextParagraph();
    auto themeManager = pipeline->GetThemeManager();
    TextStyle textStyle =
        textParagraph
            ? CreateTextStyleUsingTheme(textParagraph->GetFontStyle(), textParagraph->propTextLineStyle_,
                  themeManager ? themeManager->GetTheme<TextTheme>() : nullptr)
            : CreateTextStyleUsingTheme(nullptr, nullptr, themeManager ? themeManager->GetTheme<TextTheme>() : nullptr);
    if (!CreateParagraph(textStyle, pipeline, textParagraph ? textParagraph->content_ : "")) {
        return std::nullopt;
    }
    if (contentConstraint.selfIdealSize.has_value() && NonNegative(contentConstraint.selfIdealSize->Width())) {
        paragraph_->Layout(contentConstraint.selfIdealSize->Width());
    } else {
        paragraph_->Layout(contentConstraint.maxSize.Width());
    }
    auto height = static_cast<float>(paragraph_->GetHeight());
    double baselineOffset = 0.0F;
    textStyle.GetBaselineOffset().NormalizeToPx(
        pipeline->GetDipScale(), pipeline->GetFontScale(), pipeline->GetLogicScale(), height, baselineOffset);
    float heightFinal =
        std::min(static_cast<float>(height + std::fabs(baselineOffset)), contentConstraint.maxSize.Height());
    return SizeF(static_cast<float>(GetTextWidth()), heightFinal);
}

bool TextLayoutAlgorithm::CreateParagraph(
    const TextStyle& textStyle, const RefPtr<PipelineContext>& context, std::string content)
{
    ParagraphStyle paraStyle = { .direction = GetTextDirection(content),
        .align = textStyle.GetTextAlign(),
        .maxLines = textStyle.GetMaxLines(),
        .fontLocale = Localization::GetInstance()->GetFontLocale(),
        .wordBreak = textStyle.GetWordBreak() };

    paragraph_ = Paragraph::Create(context, paraStyle, FontCollection::Current());
    CHECK_NULL_RETURN(paragraph_, false);
    paragraph_->PushStyle(textStyle);
    StringUtils::TransformStrCase(content, static_cast<int32_t>(textStyle.GetTextCase()));
    paragraph_->AddText(StringUtils::Str8ToStr16(content));
    paragraph_->Build();
    return true;
}

TextDirection TextLayoutAlgorithm::GetTextDirection(const std::string& content)
{
    TextDirection textDirection = TextDirection::LTR;
    auto showingTextForWString = StringUtils::ToWstring(content);
    for (const auto& charOfShowingText : showingTextForWString) {
        if (u_charDirection(charOfShowingText) == UCharDirection::U_LEFT_TO_RIGHT) {
            textDirection = TextDirection::LTR;
        } else if (u_charDirection(charOfShowingText) == UCharDirection::U_RIGHT_TO_LEFT) {
            textDirection = TextDirection::RTL;
        } else if (u_charDirection(charOfShowingText) == UCharDirection::U_RIGHT_TO_LEFT_ARABIC) {
            textDirection = TextDirection::RTL;
        }
    }
    return textDirection;
}

double TextLayoutAlgorithm::GetTextWidth() const
{
    CHECK_NULL_RETURN(paragraph_, 0.0);
    return paragraph_->GetTextWidth();
}

const RefPtr<Paragraph>& TextLayoutAlgorithm::GetTxtParagraph()
{
    return paragraph_;
}

} // namespace OHOS::Ace::NG
