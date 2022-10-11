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

#include "core/components_ng/pattern/search/search_layout_algorithm.h"

#include "core/components/search/search_theme.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/search/search_layout_property.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text_field/text_field_layout_algorithm.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

constexpr float DIVIDER_SPACE = 7.0;
constexpr float SEARCH_DIVIDER_WIDTH = 1.0;
constexpr float TEXT_PADDING = 18.0;
constexpr Dimension SEARCH_SPACING = 2.0_vp;
constexpr Dimension ICON_HEIGHT = 16.0_vp;
constexpr Dimension ICON_WIIDTH_OFFSET = 14.0_vp;

constexpr int TEXTFIELD_INDEX = 0;
constexpr int IMAGE_INDEX = 1;
constexpr int BUTTON_INDEX = 2;
constexpr int BUTTON_TEXT_INDEX = 0;


void SearchLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto children = host->GetChildren();
    if (children.empty()) {
        LOGW("Search has no child node.");
        return;
    }
    auto layoutProperty = AceType::DynamicCast<SearchLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto constraint = layoutProperty->GetLayoutConstraint();

    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto searchTheme = pipeline->GetThemeManager()->GetTheme<SearchTheme>();

    if (!constraint->selfIdealSize.Height().has_value()) {
        auto height = searchTheme->GetHeight().ConvertToPx();
        constraint->selfIdealSize.SetHeight(height);
    }

    auto idealSize = CreateIdealSize(constraint.value(), Axis::HORIZONTAL, layoutProperty->GetMeasureType(), true);
    if (GreatOrEqual(idealSize.Width(), Infinity<float>()) || GreatOrEqual(idealSize.Height(), Infinity<float>())) {
        LOGW("Size is infinity.");
        geometryNode->SetFrameSize(SizeF());
        return;
    }
    geometryNode->SetFrameSize(idealSize);
    geometryNode->SetContentSize(idealSize);

    auto childLayoutConstraint = layoutProperty->CreateChildConstraint();
    childLayoutConstraint.parentIdealSize = OptionalSizeF(idealSize);

    // First measure the Button for TextField needs to determine its size based on the size of the Button
    auto buttonWrapper = layoutWrapper->GetOrCreateChildByIndex(BUTTON_INDEX);
    CHECK_NULL_VOID(buttonWrapper);
    auto textWrapper = buttonWrapper->GetOrCreateChildByIndex(BUTTON_TEXT_INDEX);
    CHECK_NULL_VOID(textWrapper);

    auto searchButton = layoutProperty->GetSearchButton();
    if (searchButton.has_value() && !searchButton.value()->empty()) {
        auto textLayoutProperty = DynamicCast<TextLayoutProperty>(textWrapper->GetLayoutProperty());
        CHECK_NULL_VOID(textLayoutProperty);
        textLayoutProperty->UpdateContent(searchButton->value());

        PaddingProperty padding;
        padding.SetEdges(CalcLength(TEXT_PADDING));
        textLayoutProperty->UpdatePadding(padding);

        auto buttonLayoutConstraint = childLayoutConstraint;
        if (buttonWrapper) {
            buttonWrapper->Measure(buttonLayoutConstraint);
        }
    }

    // Measure TextField
    auto textFieldLayoutConstraint = childLayoutConstraint;
    auto buttonWidth = buttonWrapper->GetGeometryNode()->GetFrameSize().Width();
    auto textFieldWidth = idealSize.Width() - 2 * ICON_WIIDTH_OFFSET.ConvertToPx() - ICON_HEIGHT.ConvertToPx() -
                          buttonWidth - DIVIDER_SPACE;
    auto textFieldHeight = idealSize.Height();
    textFieldLayoutConstraint.selfIdealSize = OptionalSizeF(textFieldWidth, textFieldHeight);

    auto textFieldWrapper = layoutWrapper->GetOrCreateChildByIndex(TEXTFIELD_INDEX);
    CHECK_NULL_VOID(textFieldWrapper);
    if (textFieldWrapper) {
        textFieldWrapper->Measure(textFieldLayoutConstraint);
    }

    // Measure Image
    auto imageLayoutConstraint = childLayoutConstraint;
    auto imageWrapper = layoutWrapper->GetOrCreateChildByIndex(IMAGE_INDEX);
    CHECK_NULL_VOID(imageWrapper);
    if (imageWrapper) {
        imageWrapper->Measure(imageLayoutConstraint);
    }
}

void SearchLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto children = host->GetChildren();
    if (children.empty()) {
        LOGW("Search has no child node.");
        return;
    }
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto layoutProperty = DynamicCast<SearchLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);

    // Layout TextField
    auto textFieldWrapper = layoutWrapper->GetOrCreateChildByIndex(TEXTFIELD_INDEX);
    CHECK_NULL_VOID(textFieldWrapper);
    auto textFieldGeometryNode = textFieldWrapper->GetGeometryNode();
    CHECK_NULL_VOID(textFieldGeometryNode);

    float textFieldHorizontalOffset = 2 * ICON_WIIDTH_OFFSET.ConvertToPx() + ICON_HEIGHT.ConvertToPx();
    textFieldGeometryNode->SetMarginFrameOffset(OffsetF(textFieldHorizontalOffset, 0.0f));
    textFieldWrapper->Layout();

    // Layout Image
    auto searchSize = geometryNode->GetFrameSize();
    float imageHorizontalOffset = ICON_WIIDTH_OFFSET.ConvertToPx();
    float imageVerticalOffset = (searchSize.Height() - ICON_HEIGHT.ConvertToPx()) / 2.0;
    OffsetF imageOffset(imageHorizontalOffset, imageVerticalOffset);
    auto imageWrapper = layoutWrapper->GetOrCreateChildByIndex(IMAGE_INDEX);
    CHECK_NULL_VOID(imageWrapper);
    auto imageGeometryNode = imageWrapper->GetGeometryNode();
    CHECK_NULL_VOID(imageGeometryNode);
    imageGeometryNode->SetMarginFrameOffset(imageOffset);
    imageWrapper->Layout();

    // If SearchButton is set, layout SearchButton
    auto searchButton = layoutProperty->GetSearchButton();
    if (searchButton.has_value()) {
        auto buttonWrapper = layoutWrapper->GetOrCreateChildByIndex(BUTTON_INDEX);
        CHECK_NULL_VOID(buttonWrapper);
        auto buttonGeometryNode = buttonWrapper->GetGeometryNode();
        CHECK_NULL_VOID(buttonGeometryNode);
        auto buttonFrameSize = buttonGeometryNode->GetFrameSize();

        float buttonVerticalOffset = (searchSize.Height() - buttonFrameSize.Height()) / 2.0;
        float buttonHorizontalOffset = searchSize.Width() - buttonFrameSize.Width() - DIVIDER_SPACE;
        OffsetF buttonOffset;
        buttonOffset = OffsetF(buttonHorizontalOffset, buttonVerticalOffset) +
                       OffsetF(SEARCH_SPACING.ConvertToPx() + SEARCH_DIVIDER_WIDTH, 0.0);
        buttonGeometryNode->SetMarginFrameOffset(buttonOffset);
        buttonWrapper->Layout();
    }
}

} // namespace OHOS::Ace::NG
