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
#include "core/components_ng/render/drawing_prop_convertor.h"
#include "core/components_ng/render/font_collection.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
TextLayoutAlgorithm::TextLayoutAlgorithm() = default;

void TextLayoutAlgorithm::OnReset() {}

std::optional<SizeF> TextLayoutAlgorithm::MeasureContent(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(frameNode, std::nullopt);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_RETURN(pipeline, std::nullopt);
    auto textLayoutProperty = DynamicCast<TextLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(textLayoutProperty, std::nullopt);
    auto themeManager = pipeline->GetThemeManager();
    TextStyle textStyle = CreateTextStyleUsingTheme(textLayoutProperty->GetFontStyle(),
        textLayoutProperty->GetTextLineStyle(), themeManager ? themeManager->GetTheme<TextTheme>() : nullptr);
    if (!CreateParagraph(textStyle, pipeline, textLayoutProperty->GetContent().value_or(""))) {
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
    RSParagraphStyle paraStyle;
    paraStyle.textDirection_ = ToRSTextDirection(GetTextDirection(content));
    paraStyle.textAlign_ = ToRSTextAlign(textStyle.GetTextAlign());
    paraStyle.maxLines_ = textStyle.GetMaxLines();
    paraStyle.locale_ = Localization::GetInstance()->GetFontLocale();
    paraStyle.wordBreakType_ = ToRSWordBreakType(textStyle.GetWordBreak());

    std::unique_ptr<RSParagraphBuilder> builder =
        RSParagraphBuilder::CreateRosenBuilder(paraStyle, RSFontCollection::GetInstance());
    builder->PushStyle(ToRSTextStyle(context, textStyle));
    StringUtils::TransformStrCase(content, static_cast<int32_t>(textStyle.GetTextCase()));
    builder->AddText(StringUtils::Str8ToStr16(content));
    builder->Pop();

    auto paragraph = builder->Build();
    paragraph_.reset(paragraph.release());
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
    // TODO: need check Line count
    return paragraph_->GetLongestLine();
}

const std::shared_ptr<RSParagraph>& TextLayoutAlgorithm::GetParagraph()
{
    return paragraph_;
}

} // namespace OHOS::Ace::NG
