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

#include "flutter/third_party/txt/src/txt/paragraph_txt.h"

#include "base/i18n/localization.h"
#include "core/components/font/constants_converter.h"
#include "core/components/font/font_collection.h"
#include "core/components/text/text_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
TextLayoutAlgorithm::TextLayoutAlgorithm() = default;

void TextLayoutAlgorithm::Reset()
{
    paragraph_.reset();
}

std::optional<SizeF> TextLayoutAlgorithm::MeasureContent(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    auto frameNode = layoutWrapper->GetHostNode();
    if (!frameNode) {
        LOGE("fail to measure context due to frame node is nullptr");
        return std::nullopt;
    }
    auto pipeline = frameNode->GetContext().Upgrade();
    if (!pipeline) {
        LOGE("fail to measure context due to context nullptr");
        return std::nullopt;
    }
    auto textLayoutProperty = DynamicCast<TextLayoutProperty>(layoutWrapper->GetLayoutProperty());
    if (!textLayoutProperty) {
        LOGE("fail to measure context due to textLayoutProperty nullptr");
        return std::nullopt;
    }

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
    using namespace Constants;
    txt::ParagraphStyle style;
    const auto& textAlign = textStyle.GetTextAlign();
    style.text_direction = ConvertTxtTextDirection(GetTextDirection(content));
    style.text_align = ConvertTxtTextAlign(textAlign);
    style.max_lines = textStyle.GetMaxLines();
    style.locale = Localization::GetInstance()->GetFontLocale();
    style.word_break_type = static_cast<minikin::WordBreakType>(textStyle.GetWordBreak());
    auto fontCollection = FontCollection::GetInstance()->GetFontCollection();
    if (!fontCollection) {
        LOGW("UpdateParagraph: fontCollection is null");
        return false;
    }
    std::unique_ptr<txt::ParagraphBuilder> builder = txt::ParagraphBuilder::CreateTxtBuilder(style, fontCollection);

    txt::TextStyle txtStyle;
    ConvertTxtStyle(textStyle, context, txtStyle);
    builder->PushStyle(txtStyle);
    StringUtils::TransfromStrCase(content, static_cast<int32_t>(textStyle.GetTextCase()));
    builder->AddText(StringUtils::Str8ToStr16(content));
    paragraph_ = builder->Build();
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
    if (!paragraph_) {
        return 0.0;
    }
    auto* paragraphTxt = static_cast<txt::ParagraphTxt*>(paragraph_.get());
    if (paragraphTxt != nullptr && paragraphTxt->GetLineCount() == 1) {
        return std::max(paragraph_->GetLongestLine(), paragraph_->GetMaxIntrinsicWidth());
    }
    return paragraph_->GetLongestLine();
}

const std::unique_ptr<txt::Paragraph>& TextLayoutAlgorithm::GetTxtParagraph()
{
    return paragraph_;
}
} // namespace OHOS::Ace::NG
