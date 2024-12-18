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

#include "core/components_ng/pattern/select/select_layout_algorithm.h"

#include "core/components_ng/pattern/flex/flex_layout_property.h"
#include "core/components_ng/pattern/select/select_pattern.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_pattern.h"
#include "core/components_ng/pattern/menu/menu_theme.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float MIN_SPACE = 8.0f;
constexpr float MIN_CHAR_VAL = 2.0f;
constexpr float SMALL_MIN_CHAR_VAL = 1.0f;
} // namespace
void SelectLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    NeedAgingUpdateParams(layoutWrapper);
    auto layoutProps = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProps);
    auto childConstraint = layoutProps->CreateChildConstraint();
    // Measure child row to get row height and width.
    auto rowWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
    CHECK_NULL_VOID(rowWrapper);
    auto rowProps = DynamicCast<FlexLayoutProperty>(rowWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(rowProps);
    auto space = static_cast<float>(rowProps->GetSpaceValue(Dimension()).ConvertToPx());
    auto minSpace = Dimension(MIN_SPACE, DimensionUnit::VP);
    if (space < minSpace.ConvertToPx()) {
        space = minSpace.ConvertToPx();
        rowProps->UpdateSpace(minSpace);
    }
    auto host = layoutProps->GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);
    UpdateMargin(layoutWrapper, theme);
    auto spinnerSize = MeasureAndGetSize(rowWrapper->GetOrCreateChildByIndex(1), childConstraint);
    childConstraint.maxSize.MinusWidth(spinnerSize.Width() + space);
    auto textWrapper = rowWrapper->GetOrCreateChildByIndex(0);
    CHECK_NULL_VOID(textWrapper);
    std::optional<float> maxWidth = std::nullopt;
    if (childConstraint.parentIdealSize.Width().has_value()) {
        // Make the spinner icon layout at the right end
        maxWidth = childConstraint.parentIdealSize.Width().value() - spinnerSize.Width() - space;
    }
    auto textSize = MeasureSelectText(textWrapper, childConstraint, maxWidth);

    auto rowGeometry = rowWrapper->GetGeometryNode();
    CHECK_NULL_VOID(rowGeometry);

    auto rowWidth = textSize.Width() + space + spinnerSize.Width();
    auto rowHeight = std::max(textSize.Height(), spinnerSize.Height());
    rowGeometry->SetFrameSize(SizeF(rowWidth, rowHeight));
    rowWrapper->GetLayoutProperty()->UpdatePropertyChangeFlag(PROPERTY_UPDATE_LAYOUT);
    float defaultHeight = MeasureAndGetDefaultHeight(layoutProps, theme);
    layoutWrapper->GetGeometryNode()->SetContentSize(
        SizeF(rowWidth, rowHeight > defaultHeight ? rowHeight : defaultHeight));

    // Measure same as box, base on the child row.
    BoxLayoutAlgorithm::PerformMeasureSelf(layoutWrapper);
}

SizeF SelectLayoutAlgorithm::MeasureSelectText(
    RefPtr<LayoutWrapper> textWrapper, const LayoutConstraintF& childConstraint, std::optional<float> maxWidth)
{
    auto textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(textWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(textLayoutProperty, SizeF());
    auto textLayoutConstraint = textLayoutProperty->CreateContentConstraint();
    auto contentValue = textLayoutProperty->GetContentValue(u"");

    SizeF textSize;
    if (!contentValue.empty()) {
        textSize = MeasureAndGetSize(textWrapper, childConstraint);
    }
    if (maxWidth.has_value()) {
        // Make the spinner icon layout at the right end
        textSize.SetWidth(maxWidth.value());
    }
    auto fontSize = textLayoutProperty->GetFontSize().value().ConvertToPx();
    bool isTextMin = false;
    MeasureAndGetTextSize(fontSize, textSize, isTextMin);
    if (contentValue.empty()) {
        auto textGeometry = textWrapper->GetGeometryNode();
        CHECK_NULL_RETURN(textGeometry, SizeF());
        auto textMargin = textGeometry->GetMarginFrameSize() - textGeometry->GetFrameSize();
        textGeometry->SetFrameSize(textSize - textMargin);
    } else if (isTextMin || childConstraint.parentIdealSize.Width().has_value()) {
        textLayoutProperty->UpdateMarginSelfIdealSize(textSize);
        textLayoutConstraint.selfIdealSize = OptionalSize<float>(textSize.Width(), textSize.Height());
        textLayoutConstraint.maxSize.SetSizeT(textSize);
        textWrapper->Measure(textLayoutConstraint);
    }
    return textSize;
}

void SelectLayoutAlgorithm::MeasureAndGetTextSize(double fontSize, SizeF& textSize, bool& isTextMin)
{
    float minCharVal =
        Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWELVE) ? MIN_CHAR_VAL : SMALL_MIN_CHAR_VAL;
    if (textSize.Width() < fontSize * minCharVal) {
        textSize.SetWidth(fontSize * minCharVal);
        isTextMin = true;
    }
}

float SelectLayoutAlgorithm::MeasureAndGetDefaultHeight(RefPtr<LayoutProperty> layoutProps, RefPtr<SelectTheme> theme)
{
    float defaultHeight = 0.0f;
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        auto host = layoutProps->GetHost();
        auto selectPattern = host->GetPattern<SelectPattern>();
        defaultHeight =
            static_cast<float>(theme->GetSelectDefaultHeight(selectPattern->GetControlSize()).ConvertToPx());
    } else {
        defaultHeight = static_cast<float>(theme->GetSelectDefaultHeight().ConvertToPx());
    }
    return defaultHeight;
}

SizeF SelectLayoutAlgorithm::MeasureAndGetSize(
    const RefPtr<LayoutWrapper>& childLayoutWrapper, const LayoutConstraintF& constraint)
{
    CHECK_NULL_RETURN(childLayoutWrapper, SizeF());
    childLayoutWrapper->Measure(constraint);
    auto geometry = childLayoutWrapper->GetGeometryNode();
    CHECK_NULL_RETURN(geometry, SizeF());
    return geometry->GetMarginFrameSize();
}

void SelectLayoutAlgorithm::NeedAgingUpdateParams(LayoutWrapper* layoutWrapper)
{
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    if (fontScale_ == context->GetFontScale()) {
        return;
    }
    fontScale_ = context->GetFontScale();
    auto menuTheme = context->GetTheme<NG::MenuTheme>();
    CHECK_NULL_VOID(menuTheme);
    auto pattern = host->GetPattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    auto options = pattern->GetOptions();
    if (NearEqual(fontScale_, menuTheme->GetBigFontSizeScale()) ||
        NearEqual(fontScale_, menuTheme->GetLargeFontSizeScale()) ||
        NearEqual(fontScale_, menuTheme->GetMaxFontSizeScale())) {
        UpdateOptionsMaxLines(options, menuTheme->GetTextMaxLines());
    } else {
        UpdateOptionsMaxLines(options, 1);
    }
}

void SelectLayoutAlgorithm::UpdateOptionsMaxLines(const std::vector<RefPtr<FrameNode>>& options, int32_t maxLines)
{
    for (auto child :options) {
        auto optionPattern = child->GetPattern<MenuItemPattern>();
        CHECK_NULL_VOID(optionPattern);
        auto textNode = AceType::DynamicCast<FrameNode>(optionPattern->GetTextNode());
        CHECK_NULL_VOID(textNode);
        auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(textLayoutProperty);
        textLayoutProperty->UpdateMaxLines(maxLines);
    }
}

void SelectLayoutAlgorithm::UpdateMargin(LayoutWrapper* layoutWrapper, RefPtr<SelectTheme> theme)
{
    auto rowWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
    CHECK_NULL_VOID(rowWrapper);
    auto spinner = rowWrapper->GetOrCreateChildByIndex(1);
    auto spinnerLayoutProperty = spinner->GetLayoutProperty();
    auto layoutProps = layoutWrapper->GetLayoutProperty();
    auto rowProps = DynamicCast<FlexLayoutProperty>(rowWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(rowProps);
    auto arrowStart = rowProps->GetFlexDirection() == FlexDirection::ROW_REVERSE;
    CHECK_NULL_VOID(layoutProps);
    auto isRtl = layoutProps->GetNonAutoLayoutDirection() == TextDirection::RTL;
    MarginProperty spinnerMargin;
    MarginProperty TextMargin;
    if (arrowStart ^ isRtl) {
        spinnerMargin.left = CalcLength(theme->GetContentMargin());
        spinnerMargin.right = CalcLength();
        TextMargin.left = CalcLength();
        TextMargin.right = CalcLength(theme->GetContentMargin());
    } else {
        spinnerMargin.left = CalcLength();
        spinnerMargin.right = CalcLength(theme->GetContentMargin());
        TextMargin.left = CalcLength(theme->GetContentMargin());
        TextMargin.right = CalcLength();
    }
    spinnerLayoutProperty->UpdateMargin(spinnerMargin);
        auto textWrapper = rowWrapper->GetOrCreateChildByIndex(0);
    CHECK_NULL_VOID(textWrapper);
        auto textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(textWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(textLayoutProperty);
    textLayoutProperty->UpdateMargin(TextMargin);
}
} // namespace OHOS::Ace::NG
