/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "frameworks/core/components_ng/pattern/refresh/refresh_layout_algorithm.h"

#include "frameworks/base/utils/utils.h"
#include "frameworks/core/common/container.h"
#include "frameworks/core/components_ng/base/frame_node.h"
#include "frameworks/core/components_ng/pattern/refresh/refresh_layout_property.h"
#include "frameworks/core/components_ng/pattern/refresh/refresh_pattern.h"
#include "frameworks/core/components_ng/property/measure_property.h"
#include "frameworks/core/components_ng/property/measure_utils.h"
#include "frameworks/core/components_ng/property/property.h"

namespace OHOS::Ace::NG {
namespace {
constexpr Dimension TRIGGER_REFRESH_DISTANCE = 64.0_vp;
} // namespace

RefreshLayoutAlgorithm::RefreshLayoutAlgorithm() = default;

void RefreshLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto layoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    int32_t index = 0;
    for (auto&& child : layoutWrapper->GetAllChildrenWithBuild()) {
        if (!Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
            child->Measure(layoutConstraint);
            ++index;
            continue;
        }
        if (HasCustomBuilderIndex() && index == customBuilderIndex_.value_or(0)) {
            auto builderLayoutConstraint = layoutConstraint;
            builderLayoutConstraint.UpdateIllegalSelfIdealSizeWithCheck(
                CalculateBuilderSize(child, builderLayoutConstraint));
            child->Measure(builderLayoutConstraint);
            ++index;
            continue;
        }
        child->Measure(layoutConstraint);
        ++index;
    }
    PerformMeasureSelf(layoutWrapper);
}

OptionalSizeF RefreshLayoutAlgorithm::CalculateBuilderSize(
    RefPtr<LayoutWrapper> childLayoutWrapper, LayoutConstraintF& constraint)
{
    OptionalSizeF defaultSize;
    CHECK_NULL_RETURN(childLayoutWrapper, defaultSize);
    auto layoutProperty = childLayoutWrapper->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, defaultSize);
    std::optional<CalcLength> width = std::nullopt;
    auto&& calcLayoutConstraint = layoutProperty->GetCalcLayoutConstraint();
    if (!calcLayoutConstraint) {
        return defaultSize;
    }
    std::optional<float> reSetHeight = scrollOffset_;
    if (calcLayoutConstraint->selfIdealSize.has_value() &&
        calcLayoutConstraint->selfIdealSize.value().Height().has_value()) {
        reSetHeight = ConvertToPx(
            calcLayoutConstraint->selfIdealSize.value().Height().value(), constraint.scaleProperty, scrollOffset_)
                          .value_or(-1.0f);
    }
    if (calcLayoutConstraint->selfIdealSize.has_value()) {
        width = calcLayoutConstraint->selfIdealSize->Width();
    }
    auto reSetWidth = ConvertToPx(width, constraint.scaleProperty, constraint.percentReference.Width());
    return { reSetWidth, reSetHeight };
}

void RefreshLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    PerformLayout(layoutWrapper);
    auto layoutProperty = AceType::DynamicCast<NG::RefreshLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);

    for (auto&& child : layoutWrapper->GetAllChildrenWithBuild()) {
        if (!child) {
            continue;
        }
        child->Layout();
    }
}
// Called to perform layout render node and child.
void RefreshLayoutAlgorithm::PerformLayout(LayoutWrapper* layoutWrapper)
{
    // update child position.
    auto size = layoutWrapper->GetGeometryNode()->GetFrameSize();
    const auto& padding = layoutWrapper->GetLayoutProperty()->CreatePaddingAndBorder();
    MinusPaddingToSize(padding, size);
    auto left = padding.left.value_or(0);
    auto top = padding.top.value_or(0);
    auto paddingOffset = OffsetF(left, top);
    auto align = Alignment::TOP_LEFT;
    if (layoutWrapper->GetLayoutProperty()->GetPositionProperty()) {
        align = layoutWrapper->GetLayoutProperty()->GetPositionProperty()->GetAlignment().value_or(align);
    }
    auto layoutProperty = AceType::DynamicCast<NG::RefreshLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);

    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto pattern = host->GetPattern<RefreshPattern>();
    CHECK_NULL_VOID(pattern);
    // Update child position.
    // if customBuilder exist, customBuilder is first child
    int32_t index = 0;
    float customBuilderHeight = 0.0f;
    for (const auto& child : layoutWrapper->GetAllChildrenWithBuild()) {
        if (!child) {
            index++;
            continue;
        }
        auto paddingOffsetChild = paddingOffset;
        auto alignChild = align;
        if (!HasCustomBuilderIndex()) {
            if (index == layoutWrapper->GetTotalChildCount() - 2) {
                paddingOffsetChild += layoutProperty->GetShowTimeOffsetValue();
                alignChild = Alignment::TOP_CENTER;
            } else if (index == layoutWrapper->GetTotalChildCount() - 1) {
                alignChild = Alignment::TOP_CENTER;
            }
        } else {
            if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
                auto builderChild = layoutWrapper->GetOrCreateChildByIndex(customBuilderIndex_.value_or(0));
                CHECK_NULL_VOID(builderChild);
                auto geometryNode = builderChild->GetGeometryNode();
                CHECK_NULL_VOID(geometryNode);
                auto builderHeight = geometryNode->GetMarginFrameSize().Height();
                alignChild = Alignment::TOP_CENTER;
                if (index == customBuilderIndex_.value_or(0)) {
                    auto builderOffset = 0.0f;
                    if (!NearEqual(builderHeight, scrollOffset_)) {
                        builderOffset = scrollOffset_ - builderHeight;
                    }
                    paddingOffsetChild += OffsetF(0.0f, builderOffset);
                } else {
                    auto scrollOffset = builderHeight;
                    if (!NearEqual(builderHeight, scrollOffset_)) {
                        scrollOffset = scrollOffset_;
                    }
                    paddingOffsetChild += OffsetF(0.0f, scrollOffset);
                }
                auto translate =
                    Alignment::GetAlignPosition(size, child->GetGeometryNode()->GetMarginFrameSize(), alignChild) +
                    paddingOffsetChild;
                child->GetGeometryNode()->SetMarginFrameOffset(translate);
                index++;
                continue;
            }
            if (index == customBuilderIndex_.value_or(0)) {
                alignChild = Alignment::TOP_CENTER;
                paddingOffsetChild += OffsetF(0.0f, customBuilderOffset_);
                auto geometryNode = child->GetGeometryNode();
                CHECK_NULL_VOID(geometryNode);
                customBuilderHeight = geometryNode->GetMarginFrameSize().Height();
            } else {
                auto paintProperty = pattern->GetPaintProperty<RefreshRenderProperty>();
                CHECK_NULL_VOID(paintProperty);
                auto refreshingProp = paintProperty->GetIsRefreshing().value_or(false);
                if (refreshingProp) {
                    auto distance = static_cast<float>(TRIGGER_REFRESH_DISTANCE.ConvertToPx());
                    auto refreshingPosition = Positive(customBuilderHeight) ? distance + customBuilderHeight : 0.0f;
                    paddingOffsetChild += OffsetF(0.0f, refreshingPosition);
                } else {
                    paddingOffsetChild += OffsetF(0.0f, scrollOffset_);
                }
            }
        }
        auto translate = Alignment::GetAlignPosition(size, child->GetGeometryNode()->GetMarginFrameSize(), alignChild) +
                         paddingOffsetChild;
        child->GetGeometryNode()->SetMarginFrameOffset(translate);
        index++;
    }
}

} // namespace OHOS::Ace::NG

