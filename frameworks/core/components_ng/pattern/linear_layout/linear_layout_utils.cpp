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

#include "core/components/common/properties/alignment.h"
#include "core/components_ng/property/measure_utils.h"

namespace OHOS::Ace::NG {
namespace {
float GetMainSize(LayoutWrapper* layoutWrapper, bool isVertical)
{
    float size;
    if (!isVertical) {
        size = layoutWrapper->GetGeometryNode()->GetFrameSize().Width();
    } else {
        size = layoutWrapper->GetGeometryNode()->GetFrameSize().Height();
    }
    return size;
}

float GetCrossSize(LayoutWrapper* layoutWrapper, bool isVertical)
{
    float size;
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

void SetIdealMainSize(LayoutWrapper* layoutWrapper, float value, bool isVertical)
{
    if (!isVertical) {
        layoutWrapper->GetLayoutProperty()->UpdateCalcSelfIdealSize(CalcSize(CalcLength(value), CalcLength(-1)));
    } else {
        layoutWrapper->GetLayoutProperty()->UpdateCalcSelfIdealSize(CalcSize(CalcLength(-1), CalcLength(value)));
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
    for (const auto& child : layoutWrapper->GetChildren()) {
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

// Called to perform measure current render node.
void LinearLayoutUtils::Measure(LayoutWrapper* layoutWrapper, bool isVertical)
{
    const auto& layoutConstraint = layoutWrapper->GetLayoutProperty()->GetLayoutConstraint();
    const auto& minSize = layoutConstraint->minSize;
    const auto& maxSize = layoutConstraint->maxSize;
    const auto& parentIdeaSize = layoutConstraint->parentIdealSize;
    auto padding = layoutWrapper->GetLayoutProperty()->CreatePaddingPropertyF();
    auto measureType = layoutWrapper->GetLayoutProperty()->GetMeasureType();
    SizeF idealSize = { -1, -1 };
    LinearMeasureProperty linearMeasureProperty;
    do {
        // Use idea size first if it is valid.
        if (layoutConstraint->selfIdealSize.has_value()) {
            const auto& selfIdeaSize = layoutConstraint->selfIdealSize.value();
            idealSize.UpdateSizeWithCheck(selfIdeaSize);
            if (idealSize.IsNonNegative()) {
                break;
            }
        }

        if (measureType == MeasureType::MATCH_PARENT && parentIdeaSize.has_value()) {
            idealSize.UpdateIllegalSizeWithCheck(*parentIdeaSize);
            if (idealSize.IsNonNegative()) {
                break;
            }
        }
    } while (false);
    linearMeasureProperty.realSize = idealSize;
    idealSize.UpdateIllegalSizeWithCheck(maxSize);
    MinusPaddingToSize(padding, idealSize);

    // measure child.
    TravelChildrenFlexProps(layoutWrapper, linearMeasureProperty);
    for (auto& child : linearMeasureProperty.relativeNodes) {
        child->Measure(layoutWrapper->GetLayoutProperty()->GetContentLayoutConstraint());
        linearMeasureProperty.allocatedSize += GetMainSize(AceType::RawPtr(child), isVertical);
        auto crossSize = GetCrossSize(AceType::RawPtr(child), isVertical);
        linearMeasureProperty.crossSize =
            linearMeasureProperty.crossSize > crossSize ? linearMeasureProperty.crossSize : crossSize;
    }
    float remainSize = GetMainSize(idealSize, isVertical) - linearMeasureProperty.allocatedSize;
    remainSize = remainSize < 0 ? GetMainSize(idealSize, isVertical) : remainSize;
    // layout weight node.
    for (auto& child : linearMeasureProperty.weightNodes) {
        auto childMainSize = remainSize *
                             child->GetLayoutProperty()->GetMagicItemProperty()->GetLayoutWeight().value() /
                             linearMeasureProperty.totalFlexWeight;
        SetIdealMainSize(AceType::RawPtr(child), childMainSize, isVertical);
        child->Measure(layoutWrapper->GetLayoutProperty()->GetContentLayoutConstraint());
        linearMeasureProperty.allocatedSize += GetMainSize(AceType::RawPtr(child), isVertical);
        auto crossSize = GetCrossSize(AceType::RawPtr(child), isVertical);
        linearMeasureProperty.crossSize =
            linearMeasureProperty.crossSize > crossSize ? linearMeasureProperty.crossSize : crossSize;
    }
    linearMeasureProperty.realSize.UpdateIllegalSizeWithCheck(
        CreateSize(linearMeasureProperty.allocatedSize, linearMeasureProperty.crossSize, isVertical));

    linearMeasureProperty.realSize.UpdateIllegalSizeWithCheck(minSize);

    layoutWrapper->GetGeometryNode()->SetFrameSize((linearMeasureProperty.realSize));
}

// Called to perform layout render node and child.
void LinearLayoutUtils::Layout(LayoutWrapper* layoutWrapper, bool isVertical, FlexAlign flexAlign)
{
    // update child position.
    // TODO: add margin operation.
    auto size = layoutWrapper->GetGeometryNode()->GetFrameSize();
    auto padding = layoutWrapper->GetLayoutProperty()->CreatePaddingPropertyF();
    MinusPaddingToSize(padding, size);
    auto left = padding.left.value_or(0);
    auto top = padding.top.value_or(0);
    auto paddingOffset = OffsetF(left, top);
    if (isVertical) {
        float yPos = 0;
        for (const auto& child : layoutWrapper->GetChildren()) {
            auto frameSize = child->GetGeometryNode()->GetFrameSize();
            float xOffset = CalculateCrossOffset(size.Width(), frameSize.Width(), flexAlign);
            child->GetGeometryNode()->SetFrameOffset(paddingOffset + OffsetF(xOffset, yPos));
            yPos += frameSize.Height();
        }
        return;
    }
    float xPos = 0;
    for (const auto& child : layoutWrapper->GetChildren()) {
        auto frameSize = child->GetGeometryNode()->GetFrameSize();
        float yOffset = CalculateCrossOffset(size.Height(), frameSize.Height(), flexAlign);
        child->GetGeometryNode()->SetFrameOffset(paddingOffset + OffsetF(xPos, yOffset));
        xPos += frameSize.Width();
    }
}

} // namespace OHOS::Ace::NG
