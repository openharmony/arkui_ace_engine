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

#include "core/components_ng/pattern/linear_layout/linear_layout_property.h"

namespace OHOS::Ace::NG {
namespace {
float GetChildMainAxisSize(LayoutWrapper* layoutWrapper, bool isVertical)
{
    float size = 0.0f;
    if (!isVertical) {
        size = layoutWrapper->GetGeometryNode()->GetMarginFrameSize().Width();
    } else {
        size = layoutWrapper->GetGeometryNode()->GetMarginFrameSize().Height();
    }
    return size;
}

float GetChildCrossAxisSize(LayoutWrapper* layoutWrapper, bool isVertical)
{
    float size = 0.0f;
    if (!isVertical) {
        size = layoutWrapper->GetGeometryNode()->GetMarginFrameSize().Height();
    } else {
        size = layoutWrapper->GetGeometryNode()->GetMarginFrameSize().Width();
    }
    return size;
}

float GetMainAxisSize(const SizeF& size, bool isVertical)
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
        origin.UpdateSelfMarginSizeWithCheck({ value, std::nullopt });
    } else {
        origin.UpdateSelfMarginSizeWithCheck({ std::nullopt, value });
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
        if (magicItemProperty.GetLayoutWeight().value_or(-1) > 0) {
            linearMeasureProperty.totalFlexWeight += magicItemProperty.GetLayoutWeight().value();
            linearMeasureProperty.weightNodes.emplace_back(child);
        } else {
            linearMeasureProperty.relativeNodes.emplace_back(child);
        }
    }
}

float CalculateCrossOffset(float parent, float child, FlexAlign flexAlign)
{
    float offset = 0;
    switch (flexAlign) {
        case FlexAlign::FLEX_START:
            offset = 0;
            break;
        case FlexAlign::FLEX_END:
            offset = parent - child;
            break;
        case FlexAlign::CENTER:
            offset = (parent - child) / 2;
            break;
        default:
            break;
    }
    return offset;
}

} // namespace

void LinearLayoutUtils::Measure(LayoutWrapper* layoutWrapper, bool isVertical)
{
    const auto& layoutConstraint = layoutWrapper->GetLayoutProperty()->GetLayoutConstraint();
    const auto& minSize = layoutConstraint->minSize;
    const auto& maxSize = layoutConstraint->maxSize;
    const auto& parentIdeaSize = layoutConstraint->parentIdealSize;
    auto padding = layoutWrapper->GetLayoutProperty()->CreatePaddingAndBorder();
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
        linearMeasureProperty.allocatedSize += GetChildMainAxisSize(AceType::RawPtr(child), isVertical);
        auto crossSize = GetChildCrossAxisSize(AceType::RawPtr(child), isVertical);
        linearMeasureProperty.crossSize =
            linearMeasureProperty.crossSize > crossSize ? linearMeasureProperty.crossSize : crossSize;
    }
    if (!linearMeasureProperty.relativeNodes.empty()) {
        linearMeasureProperty.allocatedSize +=
            linearMeasureProperty.space * (static_cast<float>(linearMeasureProperty.relativeNodes.size()) - 1);
    }

    // measure weight node.
    if (!linearMeasureProperty.weightNodes.empty()) {
        float remainSize = GetMainAxisSize(idealSize, isVertical) - linearMeasureProperty.allocatedSize -
                           linearMeasureProperty.space * static_cast<float>(linearMeasureProperty.weightNodes.size());
        if (LessNotEqual(remainSize, 0.0)) {
            remainSize = GetMainAxisSize(idealSize, isVertical);
        }
        for (auto& child : linearMeasureProperty.weightNodes) {
            auto childMainSize = remainSize *
                                 child->GetLayoutProperty()->GetMagicItemProperty().GetLayoutWeight().value() /
                                 linearMeasureProperty.totalFlexWeight;
            SetIdealMainSize(childConstraint, childMainSize, isVertical);
            child->Measure(childConstraint);
            linearMeasureProperty.allocatedSize += GetChildMainAxisSize(AceType::RawPtr(child), isVertical);
            linearMeasureProperty.allocatedSize += linearMeasureProperty.space;
            auto crossSize = GetChildCrossAxisSize(AceType::RawPtr(child), isVertical);
            linearMeasureProperty.crossSize =
                linearMeasureProperty.crossSize > crossSize ? linearMeasureProperty.crossSize : crossSize;
        }
    }

    // measure self size.
    auto childTotalSize = CreateSize(linearMeasureProperty.allocatedSize, linearMeasureProperty.crossSize, isVertical);
    AddPaddingToSize(padding, childTotalSize);
    linearMeasureProperty.realSize.UpdateIllegalSizeWithCheck(ConstrainSize(childTotalSize, minSize, maxSize));
    layoutWrapper->GetGeometryNode()->SetFrameSize((linearMeasureProperty.realSize.ConvertToSizeT()));
}

OffsetF LinearLayoutUtils::AdjustChildOnDirection(
    const RefPtr<LayoutWrapper>& child, const OffsetF& offset, TextDirection direction, float parentWidth)
{
    auto frameSize = child->GetGeometryNode()->GetMarginFrameSize();
    float yOffset = offset.GetY();
    float xOffset = (direction == TextDirection::RTL) ? parentWidth - frameSize.Width() - offset.GetX() : offset.GetX();
    return { xOffset, yOffset };
}

void LinearLayoutUtils::Layout(LayoutWrapper* layoutWrapper, bool isVertical, FlexAlign crossAlign, FlexAlign mainAlign)
{
    const auto& layoutConstraint = layoutWrapper->GetLayoutProperty()->GetLayoutConstraint();
    auto linearLayoutProperty = AceType::DynamicCast<LinearLayoutProperty>(layoutWrapper->GetLayoutProperty());
    auto spaceDimension = linearLayoutProperty ? linearLayoutProperty->GetSpaceValue(Dimension(0)) : Dimension(0);
    auto space = ConvertToPx(spaceDimension, layoutConstraint->scaleProperty).value_or(0);
    // update child position.
    auto size = layoutWrapper->GetGeometryNode()->GetFrameSize();
    auto padding = layoutWrapper->GetLayoutProperty()->CreatePaddingAndBorder();
    MinusPaddingToSize(padding, size);
    auto left = padding.left.value_or(0);
    auto top = padding.top.value_or(0);
    auto paddingOffset = OffsetF(left, top);
    const auto& children = layoutWrapper->GetAllChildrenWithBuild();
    auto dir = linearLayoutProperty ? linearLayoutProperty->GetLayoutDirection() : TextDirection::AUTO;
    if (dir == TextDirection::AUTO) {
        dir = AceApplicationInfo::GetInstance().IsRightToLeft() ? TextDirection::RTL : TextDirection::LTR;
    }
    auto width = size.Width();
    if (isVertical) {
        float yPos = 0.0f;
        if (mainAlign == FlexAlign::FLEX_START) {
            for (const auto& child : children) {
                auto frameSize = child->GetGeometryNode()->GetMarginFrameSize();
                float xOffset = CalculateCrossOffset(size.Width(), frameSize.Width(), crossAlign);
                auto offset = AdjustChildOnDirection(child, OffsetF(xOffset, yPos), dir, width);
                child->GetGeometryNode()->SetMarginFrameOffset(paddingOffset + offset);
                yPos += frameSize.Height();
                yPos += space;
            }
            return;
        }
        LayoutConditions layoutConditions { layoutWrapper, isVertical, crossAlign, mainAlign, size, paddingOffset,
            space };
        LinearLayoutUtils::LayoutCondition(children, dir, layoutConditions);
        return;
    }
    float xPos = 0.0f;
    if (mainAlign == FlexAlign::FLEX_START) {
        for (const auto& child : children) {
            auto frameSize = child->GetGeometryNode()->GetMarginFrameSize();
            float yOffset = CalculateCrossOffset(size.Height(), frameSize.Height(), crossAlign);
            auto offset = AdjustChildOnDirection(child, OffsetF(xPos, yOffset), dir, width);
            child->GetGeometryNode()->SetMarginFrameOffset(paddingOffset + offset);
            xPos += frameSize.Width();
            xPos += space;
        }
        return;
    }
    LayoutConditions layoutConditions { layoutWrapper, isVertical, crossAlign, mainAlign, size, paddingOffset, space };
    LinearLayoutUtils::LayoutCondition(children, dir, layoutConditions);
}

void LinearLayoutUtils::LayoutCondition(
    const std::list<RefPtr<LayoutWrapper>>& children, TextDirection direction, LayoutConditions& layoutConditions)
{
    if (layoutConditions.isVertical) {
        float yPos = 0.0f;
        float frameHeightSum = 0.0f;
        float childNum = 0.0f;
        float blankSpace = 0.0f;
        for (const auto& child : children) {
            auto frameSize = child->GetGeometryNode()->GetMarginFrameSize();
            frameHeightSum += frameSize.Height();
            childNum++;
        }
        switch (layoutConditions.mainAlign) {
            case OHOS::Ace::FlexAlign::CENTER:
                blankSpace =
                    (layoutConditions.size.Height() - frameHeightSum - (childNum - 1) * layoutConditions.space) / 2;
                yPos += blankSpace;
                break;
            case OHOS::Ace::FlexAlign::FLEX_END:
                blankSpace = layoutConditions.size.Height() - frameHeightSum - (childNum - 1) * layoutConditions.space;
                yPos += blankSpace;
                break;
            case OHOS::Ace::FlexAlign::SPACE_BETWEEN:
                blankSpace = (layoutConditions.size.Height() - frameHeightSum) / (childNum - 1);
                break;
            case OHOS::Ace::FlexAlign::SPACE_AROUND:
                blankSpace = (layoutConditions.size.Height() - frameHeightSum) / childNum;
                yPos += blankSpace / 2;
                break;
            case OHOS::Ace::FlexAlign::SPACE_EVENLY:
                blankSpace = (layoutConditions.size.Height() - frameHeightSum) / (childNum + 1);
                yPos += blankSpace;
                break;
            default:
                break;
        }
        for (const auto& child : children) {
            auto frameSize = child->GetGeometryNode()->GetMarginFrameSize();
            float xOffset =
                CalculateCrossOffset(layoutConditions.size.Width(), frameSize.Width(), layoutConditions.crossAlign);
            auto offset =
                AdjustChildOnDirection(child, OffsetF(xOffset, yPos), direction, layoutConditions.size.Width());
            child->GetGeometryNode()->SetMarginFrameOffset(layoutConditions.paddingOffset + offset);
            yPos += frameSize.Height();
            if ((layoutConditions.mainAlign == FlexAlign::CENTER) ||
                (layoutConditions.mainAlign == FlexAlign::FLEX_END)) {
                yPos += layoutConditions.space;
            } else {
                yPos += blankSpace;
            }
        }
        return;
    }
    float xPos = 0.0f;
    float frameWidthSum = 0.0f;
    float childNum = 0.0f;
    float blankSpace = 0.0f;
    for (const auto& child : children) {
        auto frameSize = child->GetGeometryNode()->GetMarginFrameSize();
        frameWidthSum += frameSize.Width();
        childNum++;
    }
    switch (layoutConditions.mainAlign) {
        case OHOS::Ace::FlexAlign::CENTER:
            blankSpace = (layoutConditions.size.Width() - frameWidthSum - layoutConditions.space * (childNum - 1)) / 2;
            xPos += blankSpace;
            break;
        case OHOS::Ace::FlexAlign::FLEX_END:
            blankSpace = layoutConditions.size.Width() - frameWidthSum - layoutConditions.space * (childNum - 1);
            xPos += blankSpace;
            break;
        case OHOS::Ace::FlexAlign::SPACE_BETWEEN:
            blankSpace = (layoutConditions.size.Width() - frameWidthSum) / (childNum - 1);
            break;
        case OHOS::Ace::FlexAlign::SPACE_AROUND:
            blankSpace = (layoutConditions.size.Width() - frameWidthSum) / childNum;
            xPos += blankSpace / 2;
            break;
        case OHOS::Ace::FlexAlign::SPACE_EVENLY:
            blankSpace = (layoutConditions.size.Width() - frameWidthSum) / (childNum + 1);
            xPos += blankSpace;
            break;
        default:
            break;
    }
    for (const auto& child : children) {
        auto frameSize = child->GetGeometryNode()->GetMarginFrameSize();
        float yOffset =
            CalculateCrossOffset(layoutConditions.size.Height(), frameSize.Height(), layoutConditions.crossAlign);
        auto offset = AdjustChildOnDirection(child, OffsetF(xPos, yOffset), direction, layoutConditions.size.Width());
        child->GetGeometryNode()->SetMarginFrameOffset(layoutConditions.paddingOffset + offset);
        xPos += frameSize.Width();
        if ((layoutConditions.mainAlign == FlexAlign::CENTER) || (layoutConditions.mainAlign == FlexAlign::FLEX_END)) {
            xPos += layoutConditions.space;
        } else {
            xPos += blankSpace;
        }
    }
}
} // namespace OHOS::Ace::NG