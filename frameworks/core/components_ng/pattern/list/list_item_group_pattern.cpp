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

#include "core/components_ng/pattern/list/list_item_group_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/components_ng/pattern/list/list_item_group_layout_algorithm.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/pattern/list/list_item_group_paint_method.h"
#include "core/components/list/list_item_theme.h"

namespace OHOS::Ace::NG {

void ListItemGroupPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (listItemGroupStyle_ == V2::ListItemGroupStyle::CARD) {
        SetListItemGroupDefaultAttributes(host);
    }
}

void ListItemGroupPattern::SetListItemGroupDefaultAttributes(const RefPtr<FrameNode>& itemGroupNode)
{
    auto renderContext = itemGroupNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto layoutProperty = itemGroupNode->GetLayoutProperty<ListItemGroupLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);

    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto listItemGroupTheme = pipeline->GetTheme<ListItemTheme>();
    CHECK_NULL_VOID(listItemGroupTheme);

    renderContext->UpdateBackgroundColor(listItemGroupTheme->GetItemGroupDefaultColor());

    MarginProperty itemGroupMargin;
    itemGroupMargin.left = CalcLength(listItemGroupTheme->GetItemGroupDefaultLeftMargin());
    itemGroupMargin.right = CalcLength(listItemGroupTheme->GetItemGroupDefaultRightMargin());
    layoutProperty->UpdateMargin(itemGroupMargin);

    PaddingProperty itemGroupPadding;
    itemGroupPadding.left = CalcLength(listItemGroupTheme->GetItemGroupDefaultPadding().Left());
    itemGroupPadding.right = CalcLength(listItemGroupTheme->GetItemGroupDefaultPadding().Right());
    itemGroupPadding.top = CalcLength(listItemGroupTheme->GetItemGroupDefaultPadding().Top());
    itemGroupPadding.bottom = CalcLength(listItemGroupTheme->GetItemGroupDefaultPadding().Bottom());
    layoutProperty->UpdatePadding(itemGroupPadding);

    renderContext->UpdateBorderRadius(listItemGroupTheme->GetItemGroupDefaultBorderRadius());
}

RefPtr<LayoutAlgorithm> ListItemGroupPattern::CreateLayoutAlgorithm()
{
    int32_t headerIndex = -1;
    int32_t footerIndex = -1;
    int32_t itemStartIndex = 0;
    auto header = header_.Upgrade();
    if (header) {
        auto count = header->FrameCount();
        if (count > 0) {
            headerIndex = itemStartIndex;
            itemStartIndex += count;
        }
    }
    auto footer = footer_.Upgrade();
    if (footer) {
        int32_t count = footer->FrameCount();
        if (count > 0) {
            footerIndex = itemStartIndex;
            itemStartIndex += count;
        }
    }
    itemStartIndex_ = itemStartIndex;
    auto layoutAlgorithm = MakeRefPtr<ListItemGroupLayoutAlgorithm>(headerIndex, footerIndex, itemStartIndex_);
    layoutAlgorithm->SetItemsPosition(itemPosition_);
    layoutAlgorithm->SetLayoutedItemInfo(layoutedItemInfo_);
    return layoutAlgorithm;
}

RefPtr<NodePaintMethod> ListItemGroupPattern::CreateNodePaintMethod()
{
    auto layoutProperty = GetLayoutProperty<ListItemGroupLayoutProperty>();
    V2::ItemDivider itemDivider;
    auto divider = layoutProperty->GetDivider().value_or(itemDivider);
    auto drawVertical = (axis_ == Axis::HORIZONTAL);
    ListItemGroupPaintInfo listItemGroupPaintInfo { drawVertical, lanes_, spaceWidth_, laneGutter_, itemTotalCount_ };
    return MakeRefPtr<ListItemGroupPaintMethod>(divider, listItemGroupPaintInfo, itemPosition_, pressedItem_);
}

bool ListItemGroupPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (config.skipMeasure && config.skipLayout) {
        return false;
    }
    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto layoutAlgorithm = DynamicCast<ListItemGroupLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithm, false);
    itemPosition_ = layoutAlgorithm->GetItemPosition();
    spaceWidth_ = layoutAlgorithm->GetSpaceWidth();
    lanes_ = layoutAlgorithm->GetLanes();
    axis_ = layoutAlgorithm->GetAxis();
    laneGutter_ = layoutAlgorithm->GetLaneGutter();
    itemDisplayEndIndex_ = layoutAlgorithm->GetEndIndex();
    itemDisplayStartIndex_ = layoutAlgorithm->GetStartIndex();
    itemTotalCount_ = layoutAlgorithm->GetTotalItemCount();
    headerMainSize_ = layoutAlgorithm->GetHeaderMainSize();
    footerMainSize_ = layoutAlgorithm->GetFooterMainSize();
    layoutedItemInfo_ = layoutAlgorithm->GetLayoutedItemInfo();
    startHeaderPos_ = layoutAlgorithm->GetStartHeaderPos();
    endFooterPos_ = layoutAlgorithm->GetEndFooterPos();
    layouted_ = true;
    CheckListDirectionInCardStyle();
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto accessibilityProperty = host->GetAccessibilityProperty<ListItemGroupAccessibilityProperty>();
    if (accessibilityProperty != nullptr) {
        accessibilityProperty->SetCollectionItemCounts(layoutAlgorithm->GetTotalItemCount());
    }
    auto listLayoutProperty = host->GetLayoutProperty<ListItemGroupLayoutProperty>();
    return listLayoutProperty && listLayoutProperty->GetDivider().has_value() && !itemPosition_.empty();
}

float ListItemGroupPattern::GetEstimateOffset(float height, const std::pair<float, float>& targetPos) const
{
    if (layoutedItemInfo_.has_value() && layoutedItemInfo_.value().startIndex > 0) {
        float averageHeight = 0.0f;
        float estimateHeight = GetEstimateHeight(averageHeight);
        return height + estimateHeight - targetPos.second;
    }
    return height - targetPos.first;
}

float ListItemGroupPattern::GetEstimateHeight(float& averageHeight) const
{
    if (layoutedItemInfo_.has_value()) {
        auto totalHeight = (layoutedItemInfo_.value().endPos - layoutedItemInfo_.value().startPos + spaceWidth_);
        auto itemCount = layoutedItemInfo_.value().endIndex - layoutedItemInfo_.value().startIndex + 1;
        averageHeight = totalHeight / itemCount;
    }
    if (layouted_) {
        if (itemTotalCount_ > 0) {
            return itemTotalCount_ * averageHeight + headerMainSize_ + footerMainSize_ - spaceWidth_;
        } else {
            return headerMainSize_ + footerMainSize_;
        }
    }
    auto host = GetHost();
    auto totalItem = host->GetTotalChildCount();
    return averageHeight * totalItem;
}

void ListItemGroupPattern::CheckListDirectionInCardStyle()
{
    if (axis_ == Axis::HORIZONTAL && listItemGroupStyle_ == V2::ListItemGroupStyle::CARD) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        RefPtr<FrameNode> listNode = AceType::DynamicCast<FrameNode>(host->GetParent());
        CHECK_NULL_VOID(listNode);
        auto listPattern = listNode->GetPattern<ListPattern>();
        CHECK_NULL_VOID(listPattern);
        listPattern->SetNeedToUpdateListDirectionInCardStyle(true);
    }
}

VisibleContentInfo ListItemGroupPattern::GetStartListItemIndex()
{
    bool isHeader = false;
    auto startHeaderMainSize = GetHeaderMainSize();
    auto startFooterMainSize = GetFooterMainSize();
    if (GetDisplayStartIndexInGroup() == 0) {
        auto startHeaderPos = startHeaderPos_;
        isHeader = (startHeaderPos + startHeaderMainSize) > 0 ? true : false;
    }
    auto startPositionSize = GetItemPosition().size();
    auto startItemIndexInGroup = GetDisplayStartIndexInGroup();
    auto startArea = ListItemGroupArea::IN_LIST_ITEM_AREA;
    if (startPositionSize == 0 && startFooterMainSize > 0) {
        startArea = ListItemGroupArea::IN_FOOTER_AREA;
        startItemIndexInGroup = -1;
    }
    if (GetDisplayStartIndexInGroup() == 0 && isHeader && startHeaderMainSize > 0) {
        startArea = ListItemGroupArea::IN_HEADER_AREA;
        startItemIndexInGroup = -1;
    }
    if (startHeaderMainSize == 0 && startFooterMainSize == 0 && GetTotalItemCount() == 0) {
        startArea = ListItemGroupArea::NONE_AREA;
    }
    VisibleContentInfo startInfo = {startArea, startItemIndexInGroup};
    return startInfo;
}

VisibleContentInfo ListItemGroupPattern::GetEndListItemIndex()
{
    bool isFooter = endFooterPos_ < 0 ? true : false;
    auto endHeaderMainSize = GetHeaderMainSize();
    auto endFooterMainSize = GetFooterMainSize();
    auto endPositionSize = GetItemPosition().size();
    auto endItemIndexInGroup = GetDisplayEndIndexInGroup();
    auto endArea = ListItemGroupArea::IN_LIST_ITEM_AREA;
    if (endPositionSize == 0 && endHeaderMainSize > 0) {
        endArea = ListItemGroupArea::IN_HEADER_AREA;
        endItemIndexInGroup = -1;
    }
    if (isFooter && endFooterMainSize > 0) {
        endArea = ListItemGroupArea::IN_FOOTER_AREA;
        endItemIndexInGroup = -1;
    }
    if (endHeaderMainSize == 0 && endFooterMainSize == 0 && GetTotalItemCount() == 0) {
        endArea = ListItemGroupArea::NONE_AREA;
    }
    VisibleContentInfo endInfo = {endArea, endItemIndexInGroup};
    return endInfo;
}
} // namespace OHOS::Ace::NG
