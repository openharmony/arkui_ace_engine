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

#include "core/components_ng/pattern/option/option_layout_algorithm.h"

#include <optional>
#include <string>

#include "base/utils/utils.h"
#include "core/components/select/select_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/option/option_paint_property.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::NG {
void OptionLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
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
    auto idealSize = CreateIdealSize(
        layoutConstraint.value(), Axis::HORIZONTAL, props->GetMeasureType(MeasureType::MATCH_CONTENT), true);
    float maxChildWidth = layoutConstraint->maxSize.Width() - horInterval_ * 2.0f;

    // measure child
    auto childConstraint = props->CreateChildConstraint();
    childConstraint.maxSize.SetWidth(maxChildWidth);
    // set self size based on childNode size;
    auto minOptionHeight = static_cast<float>(theme->GetOptionMinHeight().ConvertToPx());
    auto child = layoutWrapper->GetOrCreateChildByIndex(0);
    CHECK_NULL_VOID(child);
    MeasureRow(child, childConstraint);

    auto childSize = child->GetGeometryNode()->GetMarginFrameSize();
    childSize.AddWidth(horInterval_ * 2.0f);
    idealSize.UpdateSizeWithCheck(childSize);

    auto idealWidth = GetIdealWidth(layoutWrapper);
    if (idealWidth.has_value()) {
        idealSize.SetWidth(idealWidth.value());
    }
    idealSize.SetHeight(std::max(minOptionHeight, idealSize.Height()));
    LOGD("option frame size set to %{public}s", idealSize.ToString().c_str());
    layoutWrapper->GetGeometryNode()->SetFrameSize(idealSize);
}

void OptionLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto optionSize = layoutWrapper->GetGeometryNode()->GetFrameSize();
    auto optionHeight = optionSize.Height();

    auto child = layoutWrapper->GetOrCreateChildByIndex(0);
    child->GetLayoutProperty()->UpdatePropertyChangeFlag(PROPERTY_UPDATE_LAYOUT);
    child->GetGeometryNode()->SetMarginFrameOffset(
        OffsetF(horInterval_, (optionHeight - child->GetGeometryNode()->GetFrameSize().Height()) / 2.0f));
    child->Layout();
}

std::optional<float> OptionLayoutAlgorithm::GetIdealWidth(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_RETURN(layoutWrapper, std::nullopt);
    // layout property not update in layoutWrapper when measure
    auto optionProps = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_RETURN(optionProps, std::nullopt);
    CHECK_NULL_RETURN(optionProps->GetCalcLayoutConstraint(), std::nullopt);
    if (optionProps->GetCalcLayoutConstraint()->minSize->Width()->IsValid()) {
        auto idealWidth = optionProps->GetCalcLayoutConstraint()->minSize->Width()->GetDimension().ConvertToPx();
        return idealWidth;
    }
    return std::nullopt;
}

void OptionLayoutAlgorithm::MeasureRow(const RefPtr<LayoutWrapper>& row, const LayoutConstraintF& constraint)
{
    auto children = row->GetAllChildrenWithBuild();
    CHECK_NULL_VOID_NOLOG(!children.empty());

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
        spaceWidth -= childSize.Width();
        rowWidth += childSize.Width();
        roWHeight = std::max(roWHeight, childSize.Height());
    }
    row->GetGeometryNode()->SetFrameSize(SizeF(rowWidth, roWHeight));
}
} // namespace OHOS::Ace::NG
