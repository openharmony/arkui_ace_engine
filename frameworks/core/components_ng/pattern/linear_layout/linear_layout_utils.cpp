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

#include "core/components_ng/pattern/linear_layout/linear_layout_utils.h"

#include <cstdint>
#include <optional>

#include "base/geometry/dimension.h"
#include "base/geometry/ng/size_t.h"
#include "base/utils/utils.h"
#include "core/components/common/properties/alignment.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_property.h"
#include "core/components_ng/property/measure_utils.h"

namespace OHOS::Ace::NG {
namespace {
float GetMainSize(LayoutWrapper* layoutWrapper, bool isVertical)
{
    float size = 0.0f;
    if (!isVertical) {
        size = layoutWrapper->GetGeometryNode()->GetFrameSize().Width();
    } else {
        size = layoutWrapper->GetGeometryNode()->GetFrameSize().Height();
    }
    return size;
}

float GetCrossSize(LayoutWrapper* layoutWrapper, bool isVertical)
{
    float size = 0.0f;
    if (!isVertical) {
        size = layoutWrapper->GetGeometryNode()->GetFrameSize().Height();
    } else {
        size = layoutWrapper->GetGeometryNode()->GetFrameSize().Width();
    }
    return size;
}

float GetMainSize(const SizeF& size, bool isVertical)
{
    if (!isVertical) {
        return size.Width();
    }
    return size.Height();
}

void SetIdealMainSize(LayoutConstraintF& origin, float value, bool isVertical)
{
    origin.selfIdealSize.Reset();
    if (!isVertical) {
        origin.UpdateSelfIdealSizeWithCheck({ value, std::nullopt });
    } else {
        origin.UpdateSelfIdealSizeWithCheck({ std::nullopt, value });
    }
}

SizeF CreateSize(float mainSize, float crossSize, bool isVertical)
{
    if (!isVertical) {
        return { mainSize, crossSize };
    }
    return { crossSize, mainSize };
}

void TravelChildrenFlexProps(LayoutWrapper* layoutWrapper, LinearMeasureProperty& linearMeasureProperty)
{
    for (const auto& child : layoutWrapper->GetAllChildrenWithBuild()) {
        const auto& magicItemProperty = child->GetLayoutProperty()->GetMagicItemProperty();
        if (magicItemProperty && (magicItemProperty->GetLayoutWeight().value_or(-1) > 0)) {
            linearMeasureProperty.totalFlexWeight += magicItemProperty->GetLayoutWeight().value();
            linearMeasureProperty.weightNodes.emplace_back(child);
        } else {
            linearMeasureProperty.relativeNodes.emplace_back(child);
        }
    }
}

float CalculateCrossOffset(float parent, float child, FlexAlign flexAlign)
{
    float offfset = 0;
    switch (flexAlign) {
        case FlexAlign::FLEX_START:
            offfset = 0;
            break;
        case FlexAlign::FLEX_END:
            offfset = parent - child;
            break;
        case FlexAlign::CENTER:
            offfset = (parent - child) / 2;
            break;
        default:
            break;
    }
    return offfset;
}

} // namespace

void LinearLayoutUtils::Measure(LayoutWrapper* layoutWrapper, bool isVertical)
{
    const auto& layoutConstraint = layoutWrapper->GetLayoutProperty()->GetLayoutConstraint();
    const auto& minSize = layoutConstraint->minSize;
    const auto& maxSize = layoutConstraint->maxSize;
    const auto& parentIdeaSize = layoutConstraint->parentIdealSize;
    auto padding = layoutWrapper->GetLayoutProperty()->CreatePaddingPropertyF();
    auto measureType = layoutWrapper->GetLayoutProperty()->GetMeasureType();
    OptionalSizeF realSize;
    LinearMeasureProperty linearMeasureProperty;
    do {
        // Use idea size first if it is valid.
        realSize.UpdateSizeWithCheck(layoutConstraint->selfIdealSize);
        if (realSize.IsValid()) {
            break;
        }

        if (measureType == MeasureType::MATCH_PARENT) {
            realSize.UpdateIllegalSizeWithCheck(parentIdeaSize);
        }
    } while (false);
    linearMeasureProperty.realSize = realSize;

    // Get Max Size for children.
    realSize.UpdateIllegalSizeWithCheck(maxSize);
    auto idealSize = realSize.ConvertToSizeT();
    MinusPaddingToSize(padding, idealSize);

    auto linearLayoutProperty = AceType::DynamicCast<LinearLayoutProperty>(layoutWrapper->GetLayoutProperty());
    auto spaceDimension = linearLayoutProperty ? linearLayoutProperty->GetSpaceValue(Dimension(0)) : Dimension(0);
    linearMeasureProperty.space = ConvertToPx(spaceDimension, layoutConstraint->scaleProperty).value_or(0);

    // measure child.
    TravelChildrenFlexProps(layoutWrapper, linearMeasureProperty);
    auto childConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();

    // measure normal node.
    for (auto& child : linearMeasureProperty.relativeNodes) {
        child->Measure(childConstraint);
        linearMeasureProperty.allocatedSize += GetMainSize(AceType::RawPtr(child), isVertical);
        auto crossSize = GetCrossSize(AceType::RawPtr(child), isVertical);
        linearMeasureProperty.crossSize =
            linearMeasureProperty.crossSize > crossSize ? linearMeasureProperty.crossSize : crossSize;
    }
    if (!linearMeasureProperty.relativeNodes.empty()) {
        linearMeasureProperty.allocatedSize +=
            linearMeasureProperty.space * static_cast<float>(linearMeasureProperty.relativeNodes.size() - 1);
    }

    // measure weight node.
    if (!linearMeasureProperty.weightNodes.empty()) {
        float remainSize = GetMainSize(idealSize, isVertical) - linearMeasureProperty.allocatedSize -
                           linearMeasureProperty.space * static_cast<float>(linearMeasureProperty.weightNodes.size());
        if (LessNotEqual(remainSize, 0.0)) {
            LOGW("the remain size is less than zero, use mainSize to measure weight node");
            remainSize = GetMainSize(idealSize, isVertical);
        }
        for (auto& child : linearMeasureProperty.weightNodes) {
            auto childMainSize = remainSize *
                                 child->GetLayoutProperty()->GetMagicItemProperty()->GetLayoutWeight().value() /
                                 linearMeasureProperty.totalFlexWeight;
            SetIdealMainSize(childConstraint, childMainSize, isVertical);
            child->Measure(childConstraint);
            linearMeasureProperty.allocatedSize += GetMainSize(AceType::RawPtr(child), isVertical);
            linearMeasureProperty.allocatedSize += linearMeasureProperty.space;
            auto crossSize = GetCrossSize(AceType::RawPtr(child), isVertical);
            linearMeasureProperty.crossSize =
                linearMeasureProperty.crossSize > crossSize ? linearMeasureProperty.crossSize : crossSize;
        }
    }

    // measure self size.
    auto childTotalSize = CreateSize(linearMeasureProperty.allocatedSize, linearMeasureProperty.crossSize, isVertical);
    linearMeasureProperty.realSize.UpdateIllegalSizeWithCheck(ConstrainSize(childTotalSize, minSize, maxSize));

    layoutWrapper->GetGeometryNode()->SetFrameSize((linearMeasureProperty.realSize.ConvertToSizeT()));
}

void LinearLayoutUtils::Layout(LayoutWrapper* layoutWrapper, bool isVertical, FlexAlign flexAlign)
{
    const auto& layoutConstraint = layoutWrapper->GetLayoutProperty()->GetLayoutConstraint();
    auto linearLayoutProperty = AceType::DynamicCast<LinearLayoutProperty>(layoutWrapper->GetLayoutProperty());
    auto spaceDimension = linearLayoutProperty ? linearLayoutProperty->GetSpaceValue(Dimension(0)) : Dimension(0);
    auto space = ConvertToPx(spaceDimension, layoutConstraint->scaleProperty).value_or(0);
    // update child position.
    auto size = layoutWrapper->GetGeometryNode()->GetFrameSize();
    auto padding = layoutWrapper->GetLayoutProperty()->CreatePaddingPropertyF();
    MinusPaddingToSize(padding, size);
    auto left = padding.left.value_or(0);
    auto top = padding.top.value_or(0);
    auto paddingOffset = OffsetF(left, top);
    if (isVertical) {
        float yPos = 0;
        for (const auto& child : layoutWrapper->GetAllChildrenWithBuild()) {
            auto frameSize = child->GetGeometryNode()->GetFrameSize();
            float xOffset = CalculateCrossOffset(size.Width(), frameSize.Width(), flexAlign);
            child->GetGeometryNode()->SetFrameOffset(paddingOffset + OffsetF(xOffset, yPos));
            LOGD("Set %{public}s Child Position: %{public}s", child->GetHostTag().c_str(),
                child->GetGeometryNode()->GetFrameOffset().ToString().c_str());
            yPos += frameSize.Height();
            yPos += space;
        }
        return;
    }
    float xPos = 0;
    for (const auto& child : layoutWrapper->GetAllChildrenWithBuild()) {
        auto frameSize = child->GetGeometryNode()->GetFrameSize();
        float yOffset = CalculateCrossOffset(size.Height(), frameSize.Height(), flexAlign);
        child->GetGeometryNode()->SetFrameOffset(paddingOffset + OffsetF(xPos, yOffset));
        LOGD("Set %{public}s Child Position: %{public}s", child->GetHostTag().c_str(),
            child->GetGeometryNode()->GetFrameOffset().ToString().c_str());
        xPos += frameSize.Width();
        xPos += space;
    }
}
} // namespace OHOS::Ace::NG
