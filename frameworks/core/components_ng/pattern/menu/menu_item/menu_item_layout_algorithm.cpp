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

#include "core/components_ng/pattern/menu/menu_item/menu_item_layout_algorithm.h"

#include "base/geometry/ng/size_t.h"
#include "base/utils/utils.h"
#include "core/components/select/select_theme.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::NG {
void MenuItemLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);
    horInterval_ = static_cast<float>(theme->GetMenuIconPadding().ConvertToPx()) -
                   static_cast<float>(theme->GetOutPadding().ConvertToPx());
    auto props = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(props);
    auto layoutConstraint = props->GetLayoutConstraint();
    CHECK_NULL_VOID(layoutConstraint);
    const auto& padding = props->CreatePaddingAndBorderWithDefault(horInterval_, 0.0f, 0.0f, 0.0f);
    float maxRowWidth = layoutConstraint->maxSize.Width() - padding.Width();
    // update ideal width if user defined
    const auto& calcConstraint = props->GetCalcLayoutConstraint();
    if (calcConstraint && calcConstraint->selfIdealSize.has_value() &&
        calcConstraint->selfIdealSize.value().Width().has_value()) {
        ScaleProperty scaleProperty;
        if (layoutWrapper->GetGeometryNode() && layoutWrapper->GetGeometryNode()->GetParentLayoutConstraint()) {
            scaleProperty = layoutWrapper->GetGeometryNode()->GetParentLayoutConstraint()->scaleProperty;
        } else {
            scaleProperty = layoutConstraint->scaleProperty;
        }
        layoutConstraint->selfIdealSize.SetWidth(
            ConvertToPx(calcConstraint->selfIdealSize.value().Width()->GetDimension(), scaleProperty,
                layoutConstraint->percentReference.Width()));
    }
    if (layoutConstraint->selfIdealSize.Width().has_value()) {
        maxRowWidth =
            std::max(layoutConstraint->minSize.Width(),
                std::min(layoutConstraint->maxSize.Width(), layoutConstraint->selfIdealSize.Width().value())) -
            padding.Width();
    }
    float minRowWidth = layoutConstraint->minSize.Width();

    auto childConstraint = props->CreateChildConstraint();
    // set item min height
    auto minItemHeight = static_cast<float>(theme->GetOptionMinHeight().ConvertToPx());
    childConstraint.minSize.SetHeight(minItemHeight);
    // measure right row
    childConstraint.maxSize.SetWidth(maxRowWidth);
    float rightRowWidth = 0.0f;
    float rightRowHeight = 0.0f;
    auto rightRow = layoutWrapper->GetOrCreateChildByIndex(1);
    if (rightRow) {
        rightRow->Measure(childConstraint);
        rightRowWidth = rightRow->GetGeometryNode()->GetMarginFrameSize().Width();
        rightRowHeight = rightRow->GetGeometryNode()->GetMarginFrameSize().Height();
    }
    // measure left row
    auto middleSpace = static_cast<float>(theme->GetIconContentPadding().ConvertToPx());
    maxRowWidth -= rightRowWidth + middleSpace;
    childConstraint.maxSize.SetWidth(maxRowWidth);
    auto leftRow = layoutWrapper->GetOrCreateChildByIndex(0);
    CHECK_NULL_VOID(leftRow);
    MeasureRow(leftRow, childConstraint);
    float leftRowWidth = leftRow->GetGeometryNode()->GetMarginFrameSize().Width();
    float leftRowHeight = leftRow->GetGeometryNode()->GetMarginFrameSize().Height();
    float contentWidth = leftRowWidth + rightRowWidth + padding.Width() + middleSpace;
    layoutWrapper->GetGeometryNode()->SetContentSize(
        SizeF(std::max(minRowWidth, contentWidth), std::max(leftRowHeight, rightRowHeight)));
    BoxLayoutAlgorithm::PerformMeasureSelf(layoutWrapper);

    if (layoutConstraint->selfIdealSize.Width().has_value()) {
        auto idealWidth = std::max(layoutConstraint->minSize.Width(),
            std::min(layoutConstraint->maxSize.Width(), layoutConstraint->selfIdealSize.Width().value()));
        auto idealSize = layoutWrapper->GetGeometryNode()->GetFrameSize();
        idealSize.SetWidth(idealWidth);
        layoutWrapper->GetGeometryNode()->SetFrameSize(idealSize);
    }
}

void MenuItemLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto itemSize = layoutWrapper->GetGeometryNode()->GetFrameSize();
    auto itemHeight = itemSize.Height();
    const auto& padding =
        layoutWrapper->GetLayoutProperty()->CreatePaddingAndBorderWithDefault(horInterval_, 0.0f, 0.0f, 0.0f);

    auto leftRow = layoutWrapper->GetOrCreateChildByIndex(0);
    CHECK_NULL_VOID(leftRow);
    auto leftRowSize = leftRow->GetGeometryNode()->GetFrameSize();
    float topSpace = (itemHeight - leftRowSize.Height()) / 2.0f;
    if (padding.top.has_value() && Positive(padding.top.value()) && padding.top.value() > topSpace) {
        topSpace = padding.top.value();
    }
    leftRow->GetLayoutProperty()->UpdatePropertyChangeFlag(PROPERTY_UPDATE_LAYOUT);
    leftRow->GetGeometryNode()->SetMarginFrameOffset(OffsetF(padding.left.value_or(horInterval_), topSpace));
    leftRow->Layout();

    auto rightRow = layoutWrapper->GetOrCreateChildByIndex(1);
    CHECK_NULL_VOID(rightRow);
    auto rightRowSize = rightRow->GetGeometryNode()->GetFrameSize();
    topSpace = (itemHeight - rightRowSize.Height()) / 2.0f;
    if (padding.top.has_value() && Positive(padding.top.value()) && padding.top.value() > topSpace) {
        topSpace = padding.top.value();
    }
    rightRow->GetGeometryNode()->SetMarginFrameOffset(
        OffsetF(layoutWrapper->GetGeometryNode()->GetFrameSize().Width() - padding.right.value_or(horInterval_) -
                    rightRow->GetGeometryNode()->GetFrameSize().Width(),
            topSpace));
    rightRow->Layout();
}

void MenuItemLayoutAlgorithm::MeasureRow(const RefPtr<LayoutWrapper>& row, const LayoutConstraintF& constraint)
{
    auto children = row->GetAllChildrenWithBuild();
    CHECK_NULL_VOID(!children.empty());
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);
    auto iconContentPadding = static_cast<float>(theme->GetIconContentPadding().ConvertToPx());

    float spaceWidth = constraint.maxSize.Width();
    float rowWidth = 0.0f;
    float roWHeight = 0.0f;
    for (const auto& child : children) {
        if (child != children.back()) {
            // not content node
            child->Measure(constraint);
        } else {
            // content node update constraint max width
            auto contentConstraint = constraint;
            contentConstraint.maxSize.SetWidth(spaceWidth);
            child->Measure(contentConstraint);
        }
        auto childSize = child->GetGeometryNode()->GetMarginFrameSize();
        spaceWidth -= childSize.Width() + iconContentPadding;
        rowWidth += childSize.Width() + iconContentPadding;
        roWHeight = std::max(roWHeight, childSize.Height());
    }
    rowWidth -= iconContentPadding;
    row->GetGeometryNode()->SetFrameSize(SizeF(rowWidth, roWHeight));
}
} // namespace OHOS::Ace::NG
