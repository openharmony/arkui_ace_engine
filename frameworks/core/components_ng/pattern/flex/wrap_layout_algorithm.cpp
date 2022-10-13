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

#include "core/components_ng/pattern/flex/wrap_layout_algorithm.h"

#include <algorithm>

#include "base/geometry/axis.h"
#include "base/geometry/ng/size_t.h"
#include "base/log/ace_trace.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/alignment.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/geometry_node.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/flex/flex_layout_property.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/measure_utils.h"

namespace OHOS::Ace::NG {

void WrapLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto children = layoutWrapper->GetAllChildrenWithBuild();
    if (children.empty()) {
        layoutWrapper->GetGeometryNode()->SetFrameSize(SizeF());
        return;
    }
    auto flexProp = AceType::DynamicCast<FlexLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(flexProp);
    direction_ = flexProp->GetWrapDirection().value_or(WrapDirection::HORIZONTAL);
    alignment_ = flexProp->GetAlignment().value_or(WrapAlignment::START);
    mainAlignment_ = flexProp->GetMainAlignment().value_or(WrapAlignment::START);
    crossAlignment_ = flexProp->GetCrossAlignment().value_or(WrapAlignment::START);
    PerformLayoutInitialize(flexProp);

    totalMainLength_ = 0.0f;
    totalCrossLength_ = 0.0f;
    auto childLayoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.UpdateMaxSizeWithCheck(GetLeftSize(0.0f, mainLengthLimit_, crossLengthLimit_));
    childLayoutConstraint.UpdateMinSizeWithCheck(SizeF(0.0f, 0.0f));
    if (isDialogStretch_) {
        HandleDialogStretch();
        return;
    }
    auto spacing = spacing_.ConvertToPx();
    auto contentSpace = contentSpace_.ConvertToPx();
    float currentMainLength = 0.0f;
    float currentCrossLength = 0.0f;
    int32_t count = 0;
    float baselineDistance = 0.0f;
    std::list<RefPtr<LayoutWrapper>> itemsList;
    for (auto& item : children) {
        item->Measure(childLayoutConstraint);
        if (mainLengthLimit_ >= currentMainLength + GetMainItemLength(item->GetGeometryNode())) {
            currentMainLength += GetMainItemLength(item->GetGeometryNode());
            currentMainLength += spacing;
            currentCrossLength = std::max(currentCrossLength, GetCrossItemLength(item->GetGeometryNode()));
            if (crossAlignment_ == WrapAlignment::BASELINE) {
                baselineDistance = std::max(baselineDistance, item->GetBaselineDistance());
            }
            itemsList.emplace_back(item);
            count += 1;
        } else {
            currentMainLength -= spacing;
            if ((direction_ == WrapDirection::HORIZONTAL && !isLeftToRight_) ||
                (direction_ == WrapDirection::HORIZONTAL_REVERSE && isLeftToRight_) ||
                direction_ == WrapDirection::VERTICAL_REVERSE) {
                itemsList.reverse();
            }
            auto contentInfo = ContentInfo(currentMainLength, currentCrossLength, count, itemsList);
            contentInfo.maxBaselineDistance = baselineDistance;
            contentList_.emplace_back(contentInfo);
            itemsList.clear();
            totalMainLength_ = std::max(currentMainLength, totalMainLength_);
            totalCrossLength_ += currentCrossLength + contentSpace;
            currentMainLength = GetMainItemLength(item->GetGeometryNode()) + spacing;
            currentCrossLength = GetCrossItemLength(item->GetGeometryNode());
            if (crossAlignment_ == WrapAlignment::BASELINE) {
                baselineDistance = item->GetBaselineDistance();
            }
            itemsList.emplace_back(item);
            count = 1;
        }
    }
    if (count != 0) {
        // Add last content into list
        currentMainLength -= spacing;
        if ((direction_ == WrapDirection::HORIZONTAL && !isLeftToRight_) ||
            (direction_ == WrapDirection::HORIZONTAL_REVERSE && isLeftToRight_) ||
            (direction_ == WrapDirection::VERTICAL_REVERSE)) {
            itemsList.reverse();
        }
        auto contentInfo = ContentInfo(currentMainLength, currentCrossLength, count, itemsList);
        contentInfo.maxBaselineDistance = baselineDistance;
        contentList_.emplace_back(contentInfo);
        if ((direction_ == WrapDirection::VERTICAL || direction_ == WrapDirection::VERTICAL_REVERSE) &&
            !isLeftToRight_) {
            contentList_.reverse();
        }
        totalMainLength_ = std::max(currentMainLength, totalMainLength_);
        // n contents has n - 1 space
        totalCrossLength_ += currentCrossLength;
    }
    layoutWrapper->GetGeometryNode()->SetFrameSize(SizeF(mainLengthLimit_, totalCrossLength_));
}

void WrapLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    auto children = layoutWrapper->GetAllChildrenWithBuild();
    if (children.empty()) {
        LOGE("WrapLayoutAlgorithm::Layout, children is empty");
        return;
    }
    LayoutWholeWrap(layoutWrapper);
    for (const auto& child : children) {
        child->Layout();
    }
    contentList_.clear();
}

void WrapLayoutAlgorithm::HandleDialogStretch()
{
    // TODO: Not completed.
}

void WrapLayoutAlgorithm::PerformLayoutInitialize(const RefPtr<LayoutProperty>& layoutProp)
{
    auto constraint = layoutProp->GetLayoutConstraint();
    if (direction_ == WrapDirection::HORIZONTAL || direction_ == WrapDirection::HORIZONTAL_REVERSE) {
        mainLengthLimit_ = constraint->maxSize.Width();
        crossLengthLimit_ = constraint->maxSize.Height();
    } else {
        mainLengthLimit_ = constraint->maxSize.Height();
        crossLengthLimit_ = constraint->maxSize.Width();
    }
}

SizeF WrapLayoutAlgorithm::GetLeftSize(float crossLength, float mainLeftLength, float crossLeftLength)
{
    if (direction_ == WrapDirection::HORIZONTAL || direction_ == WrapDirection::HORIZONTAL_REVERSE) {
        return SizeF(mainLeftLength, crossLeftLength - crossLength);
    }
    return SizeF(crossLeftLength - crossLength, mainLeftLength);
}

float WrapLayoutAlgorithm::GetMainItemLength(const RefPtr<GeometryNode>& item) const
{
    return direction_ == WrapDirection::HORIZONTAL || direction_ == WrapDirection::HORIZONTAL_REVERSE
               ? item->GetFrameSize().Width()
               : item->GetFrameSize().Height();
}

float WrapLayoutAlgorithm::GetCrossItemLength(const RefPtr<GeometryNode>& item) const
{
    return direction_ == WrapDirection::VERTICAL || direction_ == WrapDirection::VERTICAL_REVERSE
               ? item->GetFrameSize().Width()
               : item->GetFrameSize().Height();
}

void WrapLayoutAlgorithm::LayoutWholeWrap(LayoutWrapper* layoutWrapper)
{
    int32_t contentNum = static_cast<int32_t>(contentList_.size());
    if (contentNum == 0) {
        LOGW("no content in wrap");
        return;
    }
    OffsetF startPosition;
    OffsetF betweenPosition;
    bool isHorizontal = direction_ == WrapDirection::HORIZONTAL || direction_ == WrapDirection::HORIZONTAL_REVERSE;

    switch (alignment_) {
        case WrapAlignment::START: {
            startPosition = OffsetF();
            betweenPosition = OffsetF();
            break;
        }
        case WrapAlignment::END: {
            startPosition = GetContentOffset(totalCrossLength_);
            betweenPosition = OffsetF();
            break;
        }
        case WrapAlignment::CENTER: {
            // divided the space by two
            startPosition = GetContentOffset(totalCrossLength_) / 2.0;
            betweenPosition = OffsetF();
            break;
        }
        case WrapAlignment::SPACE_BETWEEN: {
            startPosition = OffsetF(0.0, 0.0);
            float crossSpace =
                contentNum > 1 ? (crossLengthLimit_ - totalCrossLength_) / static_cast<double>(contentNum - 1) : 0.0;
            betweenPosition = isHorizontal ? OffsetF(0.0f, crossSpace) : OffsetF(crossSpace, 0.0f);
            break;
        }
        case WrapAlignment::SPACE_EVENLY: {
            float leftSpace = crossLengthLimit_ - totalCrossLength_;
            float crossSpace = leftSpace / static_cast<float>(contentNum + 1);
            startPosition = isHorizontal ? OffsetF(0.0f, crossSpace) : OffsetF(crossSpace, 0.0f);
            betweenPosition = isHorizontal ? OffsetF(0.0f, crossSpace) : OffsetF(crossSpace, 0.0f);
            break;
        }
        case WrapAlignment::SPACE_AROUND: {
            float leftSpace = crossLengthLimit_ - totalCrossLength_;
            float crossSpace = leftSpace / static_cast<float>(contentNum);
            startPosition = isHorizontal ? OffsetF(0.0f, crossSpace / 2.0) : OffsetF(crossSpace / 2, 0.0);
            betweenPosition = isHorizontal ? OffsetF(0.0f, crossSpace) : OffsetF(crossSpace, 0.0);
            break;
        }
        default: {
            LOGE("Wrap::alignment setting error.");
            startPosition = OffsetF();
            betweenPosition = OffsetF();
            break;
        }
    }

    auto layoutProp = layoutWrapper->GetLayoutProperty();
    // In content type, wrap is as large as children, no need to set alignment_.
    if ((!isHorizontal && layoutProp->GetCalcLayoutConstraint()->selfIdealSize->Width()->IsValid()) ||
        (isHorizontal && layoutProp->GetCalcLayoutConstraint()->selfIdealSize->Height()->IsValid())) {
        startPosition = OffsetF();
        betweenPosition = OffsetF();
    }
    TraverseContent(startPosition, betweenPosition);
}

OffsetF WrapLayoutAlgorithm::GetContentOffset(float totalCrossLength) const
{
    if (direction_ == WrapDirection::HORIZONTAL || direction_ == WrapDirection::HORIZONTAL_REVERSE) {
        return OffsetF(0.0f, crossLengthLimit_ - totalCrossLength);
    } else {
        return OffsetF(crossLengthLimit_ - totalCrossLength, 0.0f);
    }
}

void WrapLayoutAlgorithm::TraverseContent(const OffsetF& startPosition, const OffsetF& betweenPosition) const
{
    // determine the content start position by main axis
    OffsetF accumulateOffset = startPosition;
    int32_t startItemIndex = 0;
    float currentMainSpaceLength = 0.0f;
    for (const auto& content : contentList_) {
        // dfs positioned item in each content
        currentMainSpaceLength = mainLengthLimit_ - content.mainLength;
        int32_t itemNum = content.count;
        if (itemNum == 0) {
            return;
        }

        switch (mainAlignment_) {
            case WrapAlignment::START: {
                if ((direction_ == WrapDirection::HORIZONTAL && !isLeftToRight_) ||
                    (direction_ == WrapDirection::HORIZONTAL_REVERSE && isLeftToRight_) ||
                    (direction_ == WrapDirection::VERTICAL_REVERSE)) {
                    PositionedItem(0.0, content, accumulateOffset + GetItemMainOffset(currentMainSpaceLength),
                        content.crossLength);
                } else {
                    PositionedItem(0.0, content, accumulateOffset, content.crossLength);
                }
                break;
            }
            case WrapAlignment::END: {
                if ((direction_ == WrapDirection::HORIZONTAL && !isLeftToRight_) ||
                    (direction_ == WrapDirection::HORIZONTAL_REVERSE && isLeftToRight_) ||
                    direction_ == WrapDirection::VERTICAL_REVERSE) {
                    PositionedItem(0.0, content, accumulateOffset, content.crossLength);
                } else {
                    PositionedItem(0.0, content, accumulateOffset + GetItemMainOffset(currentMainSpaceLength),
                        content.crossLength);
                }
                break;
            }
            case WrapAlignment::CENTER: {
                // divided the space by two
                PositionedItem(0.0, content, accumulateOffset + GetItemMainOffset(currentMainSpaceLength / 2),
                    content.crossLength);
                break;
            }
            case WrapAlignment::SPACE_BETWEEN: {
                double betweenSpace = (itemNum - 1 == 0) ? 0.0 : currentMainSpaceLength / (itemNum - 1);
                PositionedItem(betweenSpace, content, accumulateOffset, content.crossLength);
                break;
            }
            case WrapAlignment::SPACE_AROUND: {
                double itemMainSpace = currentMainSpaceLength / itemNum;
                PositionedItem(itemMainSpace, content, accumulateOffset + GetItemMainOffset(itemMainSpace / 2),
                    content.crossLength);
                break;
            }
            case WrapAlignment::SPACE_EVENLY: {
                double itemMainSpace = currentMainSpaceLength / (itemNum + 1);
                PositionedItem(
                    itemMainSpace, content, accumulateOffset + GetItemMainOffset(itemMainSpace), content.crossLength);
                break;
            }
            default: {
                LOGE("Wrap::mainAlignment setting error. Now using START");
                PositionedItem(0.0, content, accumulateOffset, content.crossLength);
                break;
            }
        }
        auto contentSpace = contentSpace_.ConvertToPx();
        startItemIndex += itemNum;
        accumulateOffset += betweenPosition;
        accumulateOffset += (direction_ == WrapDirection::HORIZONTAL || direction_ == WrapDirection::HORIZONTAL_REVERSE)
                                ? OffsetF(0.0, content.crossLength + contentSpace)
                                : OffsetF(content.crossLength + contentSpace, 0.0);
    }
}

OffsetF WrapLayoutAlgorithm::GetItemMainOffset(float mainSpace) const
{
    // calculate the offset of each item in content
    if (direction_ == WrapDirection::HORIZONTAL || direction_ == WrapDirection::HORIZONTAL_REVERSE) {
        return OffsetF(mainSpace, 0.0);
    }
    return OffsetF(0.0, mainSpace);
}

void WrapLayoutAlgorithm::PositionedItem(
    float betweenSpace, const ContentInfo& content, const OffsetF& position, float totalCrossSpace) const
{
    OffsetF itemPositionOffset;
    // iterate every item in content
    for (const auto& itemWrapper : content.itemList) {
        auto item = itemWrapper->GetGeometryNode();
        switch (crossAlignment_) {
            case WrapAlignment::START: {
                if ((direction_ == WrapDirection::VERTICAL && !isLeftToRight_) ||
                    (direction_ == WrapDirection::VERTICAL_REVERSE && !isLeftToRight_)) {
                    HandleEndAlignment(totalCrossSpace, item, position, betweenSpace, itemPositionOffset);
                } else {
                    HandleStartAlignment(item, position, betweenSpace, itemPositionOffset);
                }
                break;
            }
            case WrapAlignment::STRETCH: {
                // TODO: stretch not complete. Use start
                if ((direction_ == WrapDirection::VERTICAL && !isLeftToRight_) ||
                    (direction_ == WrapDirection::VERTICAL_REVERSE && !isLeftToRight_)) {
                    HandleEndAlignment(totalCrossSpace, item, position, betweenSpace, itemPositionOffset);
                } else {
                    HandleStartAlignment(item, position, betweenSpace, itemPositionOffset);
                }
                break;
            }
            case WrapAlignment::END: {
                if ((direction_ == WrapDirection::VERTICAL && !isLeftToRight_) ||
                    (direction_ == WrapDirection::VERTICAL_REVERSE && !isLeftToRight_)) {
                    HandleStartAlignment(item, position, betweenSpace, itemPositionOffset);
                } else {
                    HandleEndAlignment(totalCrossSpace, item, position, betweenSpace, itemPositionOffset);
                }
                break;
            }
            case WrapAlignment::CENTER: {
                // divide the space by two
                HandleCenterAlignment(totalCrossSpace, item, position, betweenSpace, itemPositionOffset);
                break;
            }
            case WrapAlignment::BASELINE: {
                if (direction_ == WrapDirection::VERTICAL || direction_ == WrapDirection::VERTICAL_REVERSE) {
                    if (isLeftToRight_) {
                        HandleStartAlignment(item, position, betweenSpace, itemPositionOffset);
                    } else {
                        HandleEndAlignment(totalCrossSpace, item, position, betweenSpace, itemPositionOffset);
                    }
                } else {
                    HandleBaselineAlignment(
                        content.maxBaselineDistance, item, position, betweenSpace, itemPositionOffset);
                }
                break;
            }
            default: {
                if ((direction_ == WrapDirection::VERTICAL && !isLeftToRight_) ||
                    (direction_ == WrapDirection::VERTICAL_REVERSE && !isLeftToRight_)) {
                    HandleEndAlignment(totalCrossSpace, item, position, betweenSpace, itemPositionOffset);
                } else {
                    HandleStartAlignment(item, position, betweenSpace, itemPositionOffset);
                }
                break;
            }
        }
    }
}

void WrapLayoutAlgorithm::HandleStartAlignment(
    const RefPtr<GeometryNode>& item, const OffsetF& position, float betweenSpace, OffsetF& itemPositionOffset) const
{
    PlaceItemAndLog(item, position + itemPositionOffset, "START");
    // Decide content offset position
    auto spacing = spacing_.ConvertToPx();
    bool isHorizontal = direction_ == WrapDirection::HORIZONTAL || direction_ == WrapDirection::HORIZONTAL_REVERSE;
    itemPositionOffset +=
        OffsetF(isHorizontal ? item->GetFrameSize().Width() + betweenSpace + spacing : 0.0,
            isHorizontal ? 0.0 : item->GetFrameSize().Height() + betweenSpace + spacing);
}

void WrapLayoutAlgorithm::HandleEndAlignment(float totalCrossSpace, const RefPtr<GeometryNode>& item,
    const OffsetF& position, float betweenSpace, OffsetF& itemPositionOffset) const
{
    // itemPositionOffset will change in this function
    OffsetF crossOffset;
    auto spacing = spacing_.ConvertToPx();
    if (direction_ == WrapDirection::HORIZONTAL || direction_ == WrapDirection::HORIZONTAL_REVERSE) {
        crossOffset = OffsetF(0.0, totalCrossSpace - item->GetFrameSize().Height());
        PlaceItemAndLog(item, position + itemPositionOffset + crossOffset, "END");
        itemPositionOffset += OffsetF(item->GetFrameSize().Width() + betweenSpace + spacing, 0.0);
    } else {
        crossOffset = OffsetF(totalCrossSpace - item->GetFrameSize().Width(), 0.0);
        PlaceItemAndLog(item, position + itemPositionOffset + crossOffset, "END");
        itemPositionOffset += OffsetF(0.0, item->GetFrameSize().Height() + betweenSpace + spacing);
    }
}

void WrapLayoutAlgorithm::HandleCenterAlignment(float totalCrossSpace, const RefPtr<GeometryNode>& item,
    const OffsetF& position, float betweenSpace, OffsetF& itemPositionOffset) const
{
    // itemPositionOffset will change in this function
    OffsetF crossOffset;
    auto spacing = spacing_.ConvertToPx();
    if (direction_ == WrapDirection::HORIZONTAL || direction_ == WrapDirection::HORIZONTAL_REVERSE) {
        crossOffset = OffsetF(0.0, (totalCrossSpace - item->GetFrameSize().Height()) / 2.0);
        PlaceItemAndLog(item, position + itemPositionOffset + crossOffset, "CENTER");
        itemPositionOffset += OffsetF(item->GetFrameSize().Width() + betweenSpace + spacing, 0.0);
    } else {
        crossOffset = OffsetF((totalCrossSpace - item->GetFrameSize().Width()) / 2, 0.0);
        PlaceItemAndLog(item, position + itemPositionOffset + crossOffset, "CENTER");
        itemPositionOffset += OffsetF(0.0, item->GetFrameSize().Height() + betweenSpace + spacing);
    }
}

void WrapLayoutAlgorithm::HandleBaselineAlignment(float totalCrossSpace, const RefPtr<GeometryNode>& item,
    const OffsetF& position, float betweenSpace, OffsetF& itemPositionOffset) const
{
    OffsetF crossOffset;
    auto spacing = spacing_.ConvertToPx();
    crossOffset = OffsetF(0.0, totalCrossSpace - item->GetBaselineDistance());
    PlaceItemAndLog(item, position + itemPositionOffset + crossOffset, "Baseline");
    itemPositionOffset += OffsetF(item->GetFrameSize().Width() + betweenSpace + spacing, 0.0);
}

void WrapLayoutAlgorithm::PlaceItemAndLog(
    const RefPtr<GeometryNode>& node, const OffsetF& position, const std::string& align) const
{
    if (!node) {
        return;
    }
    node->SetMarginFrameOffset(position);
    LOGD("align is %{public}s, position is %{public}s", align.c_str(), position.ToString().c_str());
}

} // namespace OHOS::Ace::NG
