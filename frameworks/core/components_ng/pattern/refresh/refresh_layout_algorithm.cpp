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

#include "frameworks/core/components_ng/pattern/refresh/refresh_pattern.h"
#include "core/components_ng/property/measure_utils.h"

namespace OHOS::Ace::NG {
namespace {
constexpr Dimension TRIGGER_REFRESH_DISTANCE = 64.0_vp;
} // namespace

RefreshLayoutAlgorithm::RefreshLayoutAlgorithm() = default;

void RefreshLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto layoutProperty = AceType::DynamicCast<NG::RefreshLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto layoutConstraint = layoutProperty->CreateChildConstraint();
    int32_t index = 0;
    const auto& childlist = layoutWrapper->GetAllChildrenWithBuild();
    for (auto&& child : childlist) {
        if (!isHighVersion_) {
            child->Measure(layoutConstraint);
            ++index;
            continue;
        }
        if (HasCustomBuilderIndex() && index == customBuilderIndex_.value_or(0)) {
            auto builderLayoutConstraint = layoutConstraint;
            bool isCustomBuilderExist = layoutProperty->GetIsCustomBuilderExistValue(true);
            if (isCustomBuilderExist) {
                builderLayoutConstraint.UpdateIllegalSelfIdealSizeWithCheck(
                    CalculateBuilderSize(child, builderLayoutConstraint, builderBaseHeight_));
            } else {
                builderLayoutConstraint.minSize.SetHeight(builderBaseHeight_);
                builderLayoutConstraint.maxSize.SetHeight(builderBaseHeight_);
                builderLayoutConstraint.percentReference.SetHeight(builderBaseHeight_);
            }
            child->Measure(builderLayoutConstraint);
            ++index;
            continue;
        }
        child->Measure(layoutConstraint);
        ++index;
    }
    PerformMeasureSelfWithChildList(layoutWrapper, childlist);
}

OptionalSizeF RefreshLayoutAlgorithm::CalculateBuilderSize(
    RefPtr<LayoutWrapper> childLayoutWrapper, LayoutConstraintF& constraint, float customBaseHeight)
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
    std::optional<float> reSetHeight = customBaseHeight;
    if (calcLayoutConstraint->selfIdealSize.has_value() &&
        calcLayoutConstraint->selfIdealSize.value().Height().has_value()) {
        reSetHeight = ConvertToPx(
            calcLayoutConstraint->selfIdealSize.value().Height().value(), constraint.scaleProperty, customBaseHeight)
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
}

// Called to perform layout render node and child.
void RefreshLayoutAlgorithm::PerformLayout(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto layoutProperty = AceType::DynamicCast<NG::RefreshLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    // update child position.
    auto size = layoutWrapper->GetGeometryNode()->GetFrameSize();
    const auto& padding = layoutProperty->CreatePaddingAndBorder();
    MinusPaddingToSize(padding, size);
    auto left = padding.left.value_or(0);
    auto top = padding.top.value_or(0);
    auto paddingOffset = OffsetF(left, top);
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
        if (HasCustomBuilderIndex()) {
            if (isHighVersion_) {
                UpdateChildPosition(layoutWrapper, index, paddingOffsetChild);
            } else if (index == customBuilderIndex_.value_or(0)) {
                paddingOffsetChild += OffsetF(0.0f, customBuilderOffset_);
                auto geometryNode = child->GetGeometryNode();
                CHECK_NULL_VOID(geometryNode);
                customBuilderHeight = geometryNode->GetMarginFrameSize().Height();
            } else {
                auto refreshingProp = layoutProperty->GetIsRefreshing().value_or(false);
                if (refreshingProp) {
                    auto distance = static_cast<float>(TRIGGER_REFRESH_DISTANCE.ConvertToPx());
                    auto refreshingPosition = Positive(customBuilderHeight) ? distance + customBuilderHeight : 0.0f;
                    paddingOffsetChild += OffsetF(0.0f, refreshingPosition);
                } else {
                    paddingOffsetChild += OffsetF(0.0f, scrollOffset_);
                }
            }
        }
        auto translate =
            Alignment::GetAlignPosition(size, child->GetGeometryNode()->GetMarginFrameSize(), Alignment::TOP_CENTER) +
            paddingOffsetChild;
        child->GetGeometryNode()->SetMarginFrameOffset(translate);
        child->Layout();
        index++;
    }
}

void RefreshLayoutAlgorithm::UpdateChildPosition(
    LayoutWrapper* layoutWrapper, int32_t index, OffsetF& paddingOffsetChild)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto builderChild = layoutWrapper->GetOrCreateChildByIndex(customBuilderIndex_.value_or(0));
    CHECK_NULL_VOID(builderChild);
    auto geometryNode = builderChild->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto builderHeight = geometryNode->GetMarginFrameSize().Height();
    if (index == customBuilderIndex_.value_or(0)) {
        auto builderOffset = NearEqual(builderHeight, builderBaseHeight_) ? 0.0f : (builderBaseHeight_ - builderHeight);
        paddingOffsetChild += OffsetF(0.0f, builderOffset);
    } else {
        auto scrollOffset = NearEqual(builderHeight, builderBaseHeight_) ? builderHeight : builderBaseHeight_;
        paddingOffsetChild += OffsetF(0.0f, scrollOffset);
    }
}
} // namespace OHOS::Ace::NG
