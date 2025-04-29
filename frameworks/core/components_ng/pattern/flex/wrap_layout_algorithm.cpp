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

#include "core/components_ng/pattern/flex/flex_layout_property.h"
#include "core/components_ng/property/measure_utils.h"

namespace OHOS::Ace::NG {

/**
 * Determine whether to start the layout from the upper left corner
 */

bool IsStartTopLeft(WrapDirection direction, TextDirection textDirection)
{
    switch (direction) {
        case WrapDirection::HORIZONTAL:
            return textDirection == TextDirection::LTR;
        case WrapDirection::HORIZONTAL_REVERSE:
            return textDirection == TextDirection::RTL;
        case WrapDirection::VERTICAL:
            return true;
        case WrapDirection::VERTICAL_REVERSE:
            return false;
        default:
            return true;
    }
}

bool IsColumnReverse(WrapDirection direction)
{
    switch (direction) {
        case WrapDirection::VERTICAL:
            return false;
        case WrapDirection::VERTICAL_REVERSE:
            return true;
        default:
            return false;
    }
}

void WrapLayoutAlgorithm::UpdatePercentSensitive(LayoutWrapper *layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper && layoutWrapper->GetHostTag() == V2::FLEX_ETS_TAG);
    auto layoutAlgorithmWrapper = layoutWrapper->GetLayoutAlgorithm();
    CHECK_NULL_VOID(layoutAlgorithmWrapper);
    layoutAlgorithmWrapper->SetPercentWidth(true);
    layoutAlgorithmWrapper->SetPercentHeight(true);
}

void WrapLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto children = layoutWrapper->GetAllChildrenWithBuild();
    if (children.empty()) {
        layoutWrapper->GetGeometryNode()->SetFrameSize(SizeF());
        return;
    }
    outOfLayoutChildren_.clear();
    auto flexProp = AceType::DynamicCast<FlexLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(flexProp);
    UpdatePercentSensitive(layoutWrapper);
    direction_ = flexProp->GetWrapDirection().value_or(WrapDirection::HORIZONTAL);
    // alignment for alignContent, alignment when cross axis has extra space
    alignment_ = flexProp->GetAlignment().value_or(WrapAlignment::START);
    // alignment for justifyContent, main axis alignment
    mainAlignment_ = flexProp->GetMainAlignment().value_or(WrapAlignment::START);
    // alignment for alignItems, crossAxisAlignment
    crossAlignment_ = flexProp->GetCrossAlignment().value_or(WrapAlignment::START);
    textDir_ = flexProp->GetLayoutDirection();
    if (textDir_ == TextDirection::AUTO) {
        textDir_ = AceApplicationInfo::GetInstance().IsRightToLeft() ? TextDirection::RTL : TextDirection::LTR;
    }
    isHorizontal_ = direction_ == WrapDirection::HORIZONTAL || direction_ == WrapDirection::HORIZONTAL_REVERSE;
    isReverse_ = !IsStartTopLeft(direction_, textDir_);
    isRightDirection_ = textDir_ == TextDirection::RTL;
    isColumnReverse_ = IsColumnReverse(direction_);
    PerformLayoutInitialize(flexProp);
    totalMainLength_ = 0.0f;
    totalCrossLength_ = 0.0f;
    auto realMaxSize = GetLeftSize(0.0f, mainLengthLimit_, crossLengthLimit_);
    auto childLayoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    padding_ = layoutWrapper->GetLayoutProperty()->CreatePaddingAndBorder();
    MinusPaddingToSize(padding_, realMaxSize);
    mainLengthLimit_ = GetMainAxisLengthOfSize(realMaxSize);
    crossLengthLimit_ = GetCrossAxisLengthOfSize(realMaxSize);
    childLayoutConstraint.UpdateMaxSizeWithCheck(realMaxSize);
    childLayoutConstraint.UpdateMinSizeWithCheck(SizeF(0.0f, 0.0f));
    if (isDialogStretch_) {
        HandleDialogStretch();
        return;
    }
    spacing_ = flexProp->GetSpaceValue({});
    contentSpace_ = flexProp->GetCrossSpaceValue({});
    auto spacing = static_cast<float>(spacing_.ConvertToPx());
    auto contentSpace = static_cast<float>(contentSpace_.ConvertToPx());
    float currentMainLength = 0.0f;
    float currentCrossLength = 0.0f;
    int32_t currentItemCount = 0;
    float baselineDistance = 0.0f;
    contentList_.clear();
    std::list<RefPtr<LayoutWrapper>> currentMainAxisItemsList;
    for (auto& item : children) {
        if (item->GetLayoutProperty()->GetVisibilityValue(VisibleType::VISIBLE) == VisibleType::GONE) {
            continue;
        }
        item->Measure(childLayoutConstraint);
        if (item->IsOutOfLayout()) {
            outOfLayoutChildren_.emplace_back(item);
            continue;
        }
        // can place current child at current row
        if (GreatOrEqual(mainLengthLimit_, currentMainLength + GetItemMainAxisLength(item->GetGeometryNode()))) {
            currentMainLength += GetItemMainAxisLength(item->GetGeometryNode());
            currentMainLength += spacing;
            currentCrossLength = std::max(currentCrossLength, GetItemCrossAxisLength(item->GetGeometryNode()));
            if (crossAlignment_ == WrapAlignment::BASELINE) {
                baselineDistance = std::max(baselineDistance, item->GetBaselineDistance());
            }
            currentMainAxisItemsList.emplace_back(item);
            currentItemCount += 1;
        } else {
            // after finish processing previous row, reverse align order if developer meant to
            currentMainLength -= spacing;
            // save info of current main axis items into struct
            auto contentInfo =
                ContentInfo(currentMainLength, currentCrossLength, currentItemCount, currentMainAxisItemsList);
            contentInfo.maxBaselineDistance = baselineDistance;
            // measure items again if cross axis alignment is stretch
            // and a item has main axis size differ than content height
            StretchItemsInContent(layoutWrapper, contentInfo);
            contentList_.emplace_back(contentInfo);
            currentMainAxisItemsList.clear();
            // place current item on a new main axis
            totalMainLength_ = std::max(currentMainLength, totalMainLength_);
            totalCrossLength_ += currentCrossLength + contentSpace;
            currentMainLength = GetItemMainAxisLength(item->GetGeometryNode()) + spacing;
            currentCrossLength = GetItemCrossAxisLength(item->GetGeometryNode());
            if (crossAlignment_ == WrapAlignment::BASELINE) {
                baselineDistance = item->GetBaselineDistance();
            }
            currentMainAxisItemsList.emplace_back(item);
            currentItemCount = 1;
        }
    }
    if (currentItemCount != 0) {
        // Add last content into list
        currentMainLength -= spacing;
        auto contentInfo =
            ContentInfo(currentMainLength, currentCrossLength, currentItemCount, currentMainAxisItemsList);
        contentInfo.maxBaselineDistance = baselineDistance;
        StretchItemsInContent(layoutWrapper, contentInfo);
        contentList_.emplace_back(contentInfo);
        totalMainLength_ = std::max(currentMainLength, totalMainLength_);
        totalCrossLength_ += currentCrossLength;
    }
    if (isHorizontal_) {
        frameSize_ = SizeF(mainLengthLimit_, hasIdealHeight_ ? crossLengthLimit_ : totalCrossLength_);
    } else {
        frameSize_ = SizeF(hasIdealWidth_ ? crossLengthLimit_ : totalCrossLength_, mainLengthLimit_);
    }
    auto& calcLayoutConstraint = layoutWrapper->GetLayoutProperty()->GetCalcLayoutConstraint();
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN) && calcLayoutConstraint) {
        OptionalSizeF finalSize(frameSize_.Width(), frameSize_.Height());
        finalSize = UpdateOptionSizeByCalcLayoutConstraint(finalSize, calcLayoutConstraint,
            layoutWrapper->GetLayoutProperty()->GetLayoutConstraint()->percentReference);
        frameSize_.SetHeight(finalSize.Height().value_or(frameSize_.Height()));
        frameSize_.SetWidth(finalSize.Width().value_or(frameSize_.Width()));
    }
    AddPaddingToSize(padding_, frameSize_);
    layoutWrapper->GetGeometryNode()->SetFrameSize(frameSize_);
    frameOffset_ = layoutWrapper->GetGeometryNode()->GetFrameOffset();
}

float WrapLayoutAlgorithm::GetMainAxisLengthOfSize(const SizeF& size) const
{
    if (!isHorizontal_) {
        return size.Height();
    }
    return size.Width();
}

float WrapLayoutAlgorithm::GetCrossAxisLengthOfSize(const SizeF& size) const
{
    if (!isHorizontal_) {
        return size.Width();
    }
    return size.Height();
}

void WrapLayoutAlgorithm::StretchItemsInContent(LayoutWrapper* layoutWrapper, const ContentInfo& content)
{
    if (crossAlignment_ != WrapAlignment::STRETCH) {
        return;
    }
    auto childLayoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    for (const auto& item : content.itemList) {
        auto itemCrossAxisLength = GetItemCrossAxisLength(item->GetGeometryNode());
        // if content cross axis size is larger than item cross axis size,
        // measure items again with content cross axis size as ideal size
        if (GreatNotEqual(content.crossLength, itemCrossAxisLength)) {
            if (isHorizontal_) {
                childLayoutConstraint.selfIdealSize.SetHeight(content.crossLength);
            } else {
                childLayoutConstraint.selfIdealSize.SetWidth(content.crossLength);
            }
            item->Measure(childLayoutConstraint);
        }
    }
}

void WrapLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    auto children = layoutWrapper->GetAllChildrenWithBuild();
    if (children.empty()) {
        return;
    }
    OffsetF startPosition;
    OffsetF spaceBetweenContentsOnCrossAxis;
    if (isHorizontal_) {
        LayoutWholeWrap(startPosition, spaceBetweenContentsOnCrossAxis, layoutWrapper);
        TraverseContent(startPosition, spaceBetweenContentsOnCrossAxis);
    } else {
        LayoutWholeColumnWrap(startPosition, spaceBetweenContentsOnCrossAxis, layoutWrapper);
        TraverseColumnContent(startPosition, spaceBetweenContentsOnCrossAxis);
    }

    for (const auto& child : children) {
        child->Layout();
    }
    contentList_.clear();
}

void WrapLayoutAlgorithm::HandleDialogStretch()
{
}

void WrapLayoutAlgorithm::PerformLayoutInitialize(const RefPtr<LayoutProperty>& layoutProp)
{
    CHECK_NULL_VOID(layoutProp);
    auto constraint = layoutProp->GetLayoutConstraint();
    // if flex width and height is not set, wrap is as large as children, no need to set alignment_.
    if (constraint->selfIdealSize.Height() || constraint->selfIdealSize.Width()) {
        auto widthValue = constraint->selfIdealSize.Width();
        auto heightValue = constraint->selfIdealSize.Height();
        hasIdealWidth_ = widthValue.has_value();
        hasIdealHeight_ = heightValue.has_value();
        if (isHorizontal_) {
            mainLengthLimit_ = hasIdealWidth_ ? widthValue.value() : constraint->maxSize.Width();
            crossLengthLimit_ = hasIdealHeight_ ? heightValue.value() : constraint->maxSize.Height();
        } else {
            mainLengthLimit_ = hasIdealHeight_ ? heightValue.value() : constraint->maxSize.Height();
            crossLengthLimit_ = hasIdealWidth_ ? widthValue.value() : constraint->maxSize.Width();
        }
        return;
    }
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        if (isHorizontal_) {
            mainLengthLimit_ = std::min(constraint->maxSize.Width(), constraint->percentReference.Width());
            crossLengthLimit_ = std::min(constraint->maxSize.Height(), constraint->percentReference.Height());
        } else {
            mainLengthLimit_ = std::min(constraint->maxSize.Height(), constraint->percentReference.Height());
            crossLengthLimit_ = std::min(constraint->maxSize.Width(), constraint->percentReference.Width());
        }
    } else {
        if (isHorizontal_) {
            mainLengthLimit_ = constraint->maxSize.Width();
            crossLengthLimit_ = constraint->maxSize.Height();
        } else {
            mainLengthLimit_ = constraint->maxSize.Height();
            crossLengthLimit_ = constraint->maxSize.Width();
        }
    }
}

SizeF WrapLayoutAlgorithm::GetLeftSize(float crossLength, float mainLeftLength, float crossLeftLength)
{
    if (isHorizontal_) {
        return SizeF(mainLeftLength, crossLeftLength - crossLength);
    }
    return SizeF(crossLeftLength - crossLength, mainLeftLength);
}

float WrapLayoutAlgorithm::GetItemMainAxisLength(const RefPtr<GeometryNode>& item) const
{
    return isHorizontal_ ? item->GetMarginFrameSize().Width() : item->GetMarginFrameSize().Height();
}

float WrapLayoutAlgorithm::GetItemCrossAxisLength(const RefPtr<GeometryNode>& item) const
{
    return !isHorizontal_ ? item->GetMarginFrameSize().Width() : item->GetMarginFrameSize().Height();
}

void WrapLayoutAlgorithm::AddPaddingToStartPosition(OffsetF& startPosition) const
{
    switch (direction_) {
        // horizontal or vertical will start from top left
        case WrapDirection::HORIZONTAL:
        case WrapDirection::VERTICAL:
            if (textDir_ == TextDirection::RTL) {
                startPosition.AddX(-padding_.right.value_or(0.0f));
            } else {
                startPosition.AddX(padding_.left.value_or(0.0f));
            }
            startPosition.AddY(padding_.top.value_or(0.0f));
            break;
        case WrapDirection::HORIZONTAL_REVERSE:
            if (textDir_ == TextDirection::RTL) {
                startPosition.AddX(padding_.left.value_or(0.0f));
            } else {
                startPosition.AddX(-padding_.right.value_or(0.0f));
            }
            startPosition.AddY(padding_.top.value_or(0.0f));
            break;
        case WrapDirection::VERTICAL_REVERSE:
            startPosition.AddX(padding_.left.value_or(0.0f));
            startPosition.AddY(-padding_.bottom.value_or(0.0f));
            break;
        default:
            LOGW("Unknown direction");
    }
}

void WrapLayoutAlgorithm::AddExtraSpaceToStartPosition(OffsetF& startPosition, float extraSpace, bool onMainAxis) const
{
    if (isReverse_) {
        extraSpace = -extraSpace;
    }
    if (onMainAxis) {
        if (isHorizontal_) {
            startPosition.AddX(extraSpace);
        } else {
            startPosition.AddY(extraSpace);
        }
        return;
    }
    if (isHorizontal_) {
        startPosition.AddY(extraSpace);
        return;
    }
    startPosition.AddX(extraSpace);
}

void WrapLayoutAlgorithm::LayoutWholeWrap(
    OffsetF& startPosition, OffsetF& spaceBetweenContentsOnCrossAxis, LayoutWrapper* layoutWrapper)
{
    auto contentNum = static_cast<int32_t>(contentList_.size());
    if (contentNum == 0) {
        return;
    }

    const auto& layoutProp = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProp);
    AddPaddingToStartPosition(startPosition);
    if (isReverse_) {
        AddExtraSpaceToStartPosition(startPosition, isHorizontal_ ? -frameSize_.Width() : -frameSize_.Height(), true);
    }
    // if cross axis size is not set, cross axis size is as large as children cross axis size sum
    // no need to set alignment_.
    if ((!isHorizontal_ && hasIdealWidth_ && crossLengthLimit_ <= totalCrossLength_) ||
        (!isHorizontal_ && !hasIdealWidth_)) {
        return;
    }
    if ((isHorizontal_ && hasIdealHeight_ && crossLengthLimit_ <= totalCrossLength_) ||
        (isHorizontal_ && !hasIdealHeight_)) {
        return;
    }

    auto crossAxisRemainSpace = crossLengthLimit_ - totalCrossLength_;

    if (isReverse_) {
        crossAxisRemainSpace = -crossAxisRemainSpace;
    }
    // switch align content enum, alignment when extra space exists in container extra spaces

    switch (alignment_) {
        case WrapAlignment::START:
            break;
        // for reverse cases, start position will not include "first" item's main axis size
        case WrapAlignment::END: {
            AddExtraSpaceToStartPosition(startPosition, crossAxisRemainSpace, false);
            break;
        }
        case WrapAlignment::CENTER: {
            // divided the space by two
            crossAxisRemainSpace /= 2.0f;
            AddExtraSpaceToStartPosition(startPosition, crossAxisRemainSpace, false);
            break;
        }
        case WrapAlignment::SPACE_BETWEEN: {
            // space between will not affect start position, update space between only
            float crossSpace =
                contentNum > 1 ? (crossLengthLimit_ - totalCrossLength_) / static_cast<float>(contentNum - 1) : 0.0f;
            spaceBetweenContentsOnCrossAxis = isHorizontal_ ? OffsetF(0.0f, crossSpace) : OffsetF(crossSpace, 0.0f);
            break;
        }
        case WrapAlignment::SPACE_EVENLY: {
            float crossSpace = contentNum != -1 ? crossAxisRemainSpace / static_cast<float>(contentNum + 1) : 0.0f;
            AddExtraSpaceToStartPosition(startPosition, crossSpace, false);
            spaceBetweenContentsOnCrossAxis =
                isHorizontal_ ? OffsetF(0.0f, std::abs(crossSpace)) : OffsetF(std::abs(crossSpace), 0.0f);
            break;
        }
        case WrapAlignment::SPACE_AROUND: {
            float crossSpace = crossAxisRemainSpace / static_cast<float>(contentNum);
            AddExtraSpaceToStartPosition(startPosition, crossSpace / 2.0f, false);
            spaceBetweenContentsOnCrossAxis =
                isHorizontal_ ? OffsetF(0.0f, std::abs(crossSpace)) : OffsetF(std::abs(crossSpace), 0.0);
            break;
        }
        default: {
            break;
        }
    }
}

SizeF WrapLayoutAlgorithm::GetMainAxisRemainSpace(float totalMainLength) const
{
    if (isHorizontal_) {
        return SizeF(mainLengthLimit_ - totalMainLength, 0.0f);
    }
    return SizeF(0.0f, mainLengthLimit_ - totalMainLength);
}

SizeF WrapLayoutAlgorithm::GetCrossAxisRemainSpace(float totalCrossLength) const
{
    if (isHorizontal_) {
        return SizeF(0.0f, crossLengthLimit_ - totalCrossLength);
    }
    return SizeF(crossLengthLimit_ - totalCrossLength, 0.0f);
}

float WrapLayoutAlgorithm::GetMainAxisOffset(const OffsetF& offset) const
{
    if (isHorizontal_) {
        return offset.GetX();
    }
    return offset.GetY();
}

float WrapLayoutAlgorithm::GetCrossAxisOffset(const OffsetF& offset) const
{
    if (isHorizontal_) {
        return offset.GetY();
    }
    return offset.GetX();
}

void WrapLayoutAlgorithm::TraverseContent(const OffsetF& startPosition, const OffsetF& spaceBetweenContentsOnCrossAxis)
{
    // determine the content start position by main axis
    OffsetF contentPosition(startPosition.GetX(), startPosition.GetY());
    auto contentSpace = static_cast<float>(contentSpace_.ConvertToPx());
    auto spaceBetween = isHorizontal_ ? spaceBetweenContentsOnCrossAxis.GetY() : spaceBetweenContentsOnCrossAxis.GetX();
    for (const auto& content : contentList_) {
        LayoutContent(content, contentPosition);
        if (isHorizontal_) {
            contentPosition.AddY(content.crossLength + contentSpace + spaceBetween);
        } else {
            contentPosition.AddX(content.crossLength + contentSpace + spaceBetween);
        }
    }
}

OffsetF WrapLayoutAlgorithm::GetItemMainOffset(float mainSpace) const
{
    // calculate the offset of each item in content
    if (isHorizontal_) {
        return OffsetF(mainSpace, 0.0);
    }
    return OffsetF(0.0, mainSpace);
}

float WrapLayoutAlgorithm::CalcItemCrossAxisOffset(
    const ContentInfo& content, const OffsetF& contentOffset, const RefPtr<GeometryNode>& node)
{
    switch (crossAlignment_) {
        case WrapAlignment::START:
        // stretch has been processed in measure, result is the same as start
        case WrapAlignment::STRETCH: {
            if (isHorizontal_) {
                return contentOffset.GetY();
            }
            return contentOffset.GetX();
        }
        case WrapAlignment::END: {
            auto itemFrameSize = node->GetMarginFrameSize();
            if (isHorizontal_) {
                return contentOffset.GetY() + content.crossLength - itemFrameSize.Height();
            }
            return contentOffset.GetX() + content.crossLength - itemFrameSize.Width();
        }
        case WrapAlignment::CENTER: {
            // divide the space by two
            auto itemFrameSize = node->GetMarginFrameSize();
            if (isHorizontal_) {
                return contentOffset.GetY() + (content.crossLength - itemFrameSize.Height()) / 2.0f;
            }
            return contentOffset.GetX() + (content.crossLength - itemFrameSize.Width()) / 2.0f;
        }
        case WrapAlignment::BASELINE: {
            break;
        }
        default: {
            if (isHorizontal_) {
                return contentOffset.GetY();
            }
            return contentOffset.GetX();

            break;
        }
    }
    if (isHorizontal_) {
        return contentOffset.GetY();
    }
    return contentOffset.GetX();
}

void WrapLayoutAlgorithm::CalcItemMainAxisStartAndSpaceBetween(
    OffsetF& startPosition, OffsetF& spaceBetweenItemsOnMainAxis, const ContentInfo& content)
{
    // switch align content enum, alignment when extra space exists in container extra spaces
    float spaceLeftOnMainAxis = mainLengthLimit_ - content.mainLength;
    switch (mainAlignment_) {
        case WrapAlignment::START:
            break;
        case WrapAlignment::END: {
            AddExtraSpaceToStartPosition(startPosition, spaceLeftOnMainAxis, true);
            break;
        }
        case WrapAlignment::CENTER: {
            AddExtraSpaceToStartPosition(startPosition, spaceLeftOnMainAxis / 2.0f, true);
            break;
        }
        case WrapAlignment::SPACE_BETWEEN: {
            float mainSpace = content.count > 1 ? spaceLeftOnMainAxis / static_cast<float>(content.count - 1) : 0.0f;
            spaceBetweenItemsOnMainAxis = isHorizontal_ ? OffsetF(mainSpace, 0.0f) : OffsetF(0.0f, mainSpace);
            break;
        }
        case WrapAlignment::SPACE_EVENLY: {
            float mainSpace = content.count != -1 ? spaceLeftOnMainAxis / static_cast<float>(content.count + 1) : 0.0f;
            AddExtraSpaceToStartPosition(startPosition, mainSpace, true);
            spaceBetweenItemsOnMainAxis = isHorizontal_ ? OffsetF(mainSpace, 0.0f) : OffsetF(0.0f, mainSpace);
            break;
        }
        case WrapAlignment::SPACE_AROUND: {
            float mainSpace = content.count != 0 ? spaceLeftOnMainAxis / static_cast<float>(content.count) : 0.0f;
            AddExtraSpaceToStartPosition(startPosition, mainSpace / 2.0f, true);
            spaceBetweenItemsOnMainAxis = isHorizontal_ ? OffsetF(mainSpace, 0.0f) : OffsetF(0.0f, mainSpace);
            break;
        }
        default: {
            break;
        }
    }
}

void WrapLayoutAlgorithm::LayoutContent(const ContentInfo& content, const OffsetF& position)
{
    int32_t itemNum = content.count;
    if (itemNum == 0) {
        return;
    }
    OffsetF contentStartPosition(position.GetX(), position.GetY());
    OffsetF spaceBetweenItemsOnMainAxis;
    CalcItemMainAxisStartAndSpaceBetween(contentStartPosition, spaceBetweenItemsOnMainAxis, content);

    FlexItemProperties flexItemProperties;
    GetFlexItemProperties(content, flexItemProperties);
    float remainSpace = mainLengthLimit_ - currentMainLength_;
    for (const auto& itemWrapper : content.itemList) {
        auto item = itemWrapper->GetGeometryNode();
        if (GreatNotEqual(remainSpace, 0.0f)) {
            CalcFlexGrowLayout(itemWrapper, flexItemProperties, remainSpace);
        }
        // calc start position and between space
        auto itemMainAxisOffset = isHorizontal_ ? contentStartPosition.GetX() : contentStartPosition.GetY();
        if (isReverse_) {
            itemMainAxisOffset -= GetItemMainAxisLength(item);
        }
        auto itemCrossAxisOffset = CalcItemCrossAxisOffset(content, contentStartPosition, item);
        OffsetF offset;
        float contentMainAxisSpan = 0.0f;
        if (isHorizontal_) {
            offset = OffsetF(itemMainAxisOffset, itemCrossAxisOffset);
            contentMainAxisSpan = item->GetMarginFrameSize().Width() + static_cast<float>(spacing_.ConvertToPx()) +
                                  spaceBetweenItemsOnMainAxis.GetX();
            contentStartPosition.AddX(isReverse_ ? -contentMainAxisSpan : contentMainAxisSpan);
        } else {
            offset = OffsetF(itemCrossAxisOffset, itemMainAxisOffset);
            contentMainAxisSpan = item->GetMarginFrameSize().Height() + static_cast<float>(spacing_.ConvertToPx()) +
                                  spaceBetweenItemsOnMainAxis.GetY();
            contentStartPosition.AddY(isReverse_ ? -contentMainAxisSpan : contentMainAxisSpan);
        }
        itemWrapper->GetGeometryNode()->SetMarginFrameOffset(offset);
    }
}

void WrapLayoutAlgorithm::GetFlexItemProperties(const ContentInfo& content, FlexItemProperties& flexItemProperties)
{
    auto spacing = static_cast<float>(spacing_.ConvertToPx());
    currentMainLength_ = 0.0f;
    for (const auto& itemWrapper : content.itemList) {
        if (!itemWrapper) {
            continue;
        }
        currentMainLength_ += GetItemMainAxisLength(itemWrapper->GetGeometryNode()) + spacing;
        auto layoutProperty = itemWrapper->GetLayoutProperty();
        if (!layoutProperty) {
            continue;
        }
        const auto& flexItemProperty = layoutProperty->GetFlexItemProperty();
        if (!flexItemProperty) {
            continue;
        }
        auto flexGrow = flexItemProperty->GetFlexGrow().value_or(0.0f);
        if (GreatNotEqual(flexGrow, 0.0f)) {
            flexItemProperties.totalGrow += flexGrow;
        }
    }
}

void WrapLayoutAlgorithm::CalcFlexGrowLayout(
    const RefPtr<LayoutWrapper>& itemWrapper, const FlexItemProperties& flexItemProperties, float remainSpace)
{
    CHECK_NULL_VOID(itemWrapper);
    auto layoutProperty = itemWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto& flexItemProperty = layoutProperty->GetFlexItemProperty();
    CHECK_NULL_VOID(flexItemProperty);
    auto layoutConstraint = layoutProperty->GetLayoutConstraint();
    if (!layoutConstraint.has_value()) {
        return;
    }

    auto layoutConstraintValue = layoutConstraint.value();
    float itemFlex = flexItemProperty->GetFlexGrow().value_or(0.0f);
    if (GreatNotEqual(itemFlex, 0.0f) && GreatNotEqual(remainSpace, 0.0f) &&
        GreatNotEqual(flexItemProperties.totalGrow, 0.0f)) {
        float flexSize = itemFlex * remainSpace / flexItemProperties.totalGrow;
        flexSize += GetItemMainAxisLength(itemWrapper->GetGeometryNode());
        OptionalSizeF& selfIdealSize = layoutConstraintValue.selfIdealSize;
        if (direction_ == WrapDirection::HORIZONTAL || direction_ == WrapDirection::HORIZONTAL_REVERSE) {
            selfIdealSize.SetWidth(flexSize);
        } else {
            selfIdealSize.SetHeight(flexSize);
        }
        itemWrapper->Measure(layoutConstraintValue);
    }
}

void WrapLayoutAlgorithm::AddPaddingToStartPositionForColumn(OffsetF& startPosition) const
{
    switch (direction_) {
        // vertical will start from top left
        case WrapDirection::VERTICAL:
            if (isRightDirection_) {
                startPosition.AddX(-padding_.right.value_or(0.0f));
            } else {
                startPosition.AddX(padding_.left.value_or(0.0f));
            }
            startPosition.AddY(padding_.top.value_or(0.0f));
            break;
        case WrapDirection::VERTICAL_REVERSE:
            if (isRightDirection_) {
                startPosition.AddX(-padding_.right.value_or(0.0f));
            } else {
                startPosition.AddX(padding_.left.value_or(0.0f));
            }
            startPosition.AddY(-padding_.bottom.value_or(0.0f));
            break;
        default:
            LOGW("Unknown direction");
    }
}

void WrapLayoutAlgorithm::UpdateStartPositionByAlign(
    OffsetF& startPosition, float crossAxisRemainSpace, OffsetF& spaceBetweenContentsOnCrossAxis, int32_t contentNum)
{
    // switch align content enum, alignment when extra space exists in container extra spaces
    switch (alignment_) {
        case WrapAlignment::START:
            break;
        // for reverse cases, start position will not include "first" item's main axis size
        case WrapAlignment::END: {
            startPosition.AddX(crossAxisRemainSpace);
            break;
        }
        case WrapAlignment::CENTER: {
            // divided the space by two
            crossAxisRemainSpace /= 2.0f;
            startPosition.AddX(crossAxisRemainSpace);
            break;
        }
        case WrapAlignment::SPACE_BETWEEN: {
            // space between will not affect start position, update space between only
            float crossSpace =
                contentNum > 1 ? (crossLengthLimit_ - totalCrossLength_) / static_cast<float>(contentNum - 1) : 0.0f;
            spaceBetweenContentsOnCrossAxis = OffsetF(crossSpace, 0.0f);
            break;
        }
        case WrapAlignment::SPACE_EVENLY: {
            float crossSpace = contentNum != -1 ? crossAxisRemainSpace / static_cast<float>(contentNum + 1) : 0.0f;
            startPosition.AddX(crossSpace);
            spaceBetweenContentsOnCrossAxis =
                isHorizontal_ ? OffsetF(0.0f, std::abs(crossSpace)) : OffsetF(std::abs(crossSpace), 0.0f);
            break;
        }
        case WrapAlignment::SPACE_AROUND: {
            float crossSpace = contentNum != 0 ? crossAxisRemainSpace / static_cast<float>(contentNum) : 0.0f;
            startPosition.AddX(crossSpace / 2.0f);
            spaceBetweenContentsOnCrossAxis = OffsetF(std::abs(crossSpace), 0.0);
            break;
        }
        default: {
            break;
        }
    }
}

void WrapLayoutAlgorithm::LayoutWholeColumnWrap(
    OffsetF& startPosition, OffsetF& spaceBetweenContentsOnCrossAxis, LayoutWrapper* layoutWrapper)
{
    auto contentNum = static_cast<int32_t>(contentList_.size());
    if (contentNum == 0) {
        return;
    }

    const auto& layoutProp = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProp);
    AddPaddingToStartPositionForColumn(startPosition);
    if (isRightDirection_) {
        startPosition.AddX(frameSize_.Width());
    }
    if (isColumnReverse_) {
        AddExtraSpaceToStartPosition(startPosition, -frameSize_.Height(), true);
    }
    // if cross axis size is not set, cross axis size is as large as children cross axis size sum
    // no need to set alignment_.
    if ((!isHorizontal_ && hasIdealWidth_ && crossLengthLimit_ <= totalCrossLength_) ||
        (!isHorizontal_ && !hasIdealWidth_)) {
        return;
    }
    auto crossAxisRemainSpace = crossLengthLimit_ - totalCrossLength_;
    if (isRightDirection_) {
        crossAxisRemainSpace = -crossAxisRemainSpace;
    }
    UpdateStartPositionByAlign(startPosition, crossAxisRemainSpace, spaceBetweenContentsOnCrossAxis, contentNum);
}

void WrapLayoutAlgorithm::LayoutColumnContent(const ContentInfo& content, const OffsetF& position)
{
    int32_t itemNum = content.count;
    if (itemNum == 0) {
        return;
    }
    OffsetF contentStartPosition(position.GetX(), position.GetY());
    OffsetF spaceBetweenItemsOnMainAxis;
    CalcItemMainAxisStartAndSpaceBetween(contentStartPosition, spaceBetweenItemsOnMainAxis, content);

    FlexItemProperties flexItemProperties;
    GetFlexItemProperties(content, flexItemProperties);
    float remainSpace = mainLengthLimit_ - currentMainLength_;
    for (const auto& itemWrapper : content.itemList) {
        auto item = itemWrapper->GetGeometryNode();
        if (GreatNotEqual(remainSpace, 0.0f)) {
            CalcFlexGrowLayout(itemWrapper, flexItemProperties, remainSpace);
        }
        // calc start position and between space
        auto itemMainAxisOffset = isHorizontal_ ? contentStartPosition.GetX() : contentStartPosition.GetY();
        auto itemCrossAxisOffset = CalcItemCrossAxisOffset(content, contentStartPosition, item);
        if (isRightDirection_) {
            itemCrossAxisOffset -= GetItemCrossAxisLength(item);
        }
        OffsetF offset;
        float contentMainAxisSpan = 0.0f;
        if (isColumnReverse_) {
            itemMainAxisOffset -= GetItemMainAxisLength(item);
        }
        offset = OffsetF(itemCrossAxisOffset, itemMainAxisOffset);
        contentMainAxisSpan = item->GetMarginFrameSize().Height() + static_cast<float>(spacing_.ConvertToPx()) +
                              spaceBetweenItemsOnMainAxis.GetY();
        contentStartPosition.AddY(isColumnReverse_ ? -contentMainAxisSpan : contentMainAxisSpan);
        itemWrapper->GetGeometryNode()->SetMarginFrameOffset(offset);
    }
}

void WrapLayoutAlgorithm::TraverseColumnContent(
    const OffsetF& startPosition, const OffsetF& spaceBetweenContentsOnCrossAxis)
{
    // determine the content start position by main axis
    OffsetF contentPosition(startPosition.GetX(), startPosition.GetY());
    auto contentSpace = static_cast<float>(contentSpace_.ConvertToPx());
    auto spaceBetween = spaceBetweenContentsOnCrossAxis.GetX();
    for (const auto& content : contentList_) {
        LayoutColumnContent(content, contentPosition);
        if (isRightDirection_) {
            float leftSpace = content.crossLength + contentSpace + spaceBetween;
            contentPosition.AddX(-leftSpace);
        } else {
            contentPosition.AddX(content.crossLength + contentSpace + spaceBetween);
        }
    }
}
} // namespace OHOS::Ace::NG
