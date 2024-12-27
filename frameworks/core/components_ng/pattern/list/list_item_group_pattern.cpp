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

#include "base/log/dump_log.h"
#include "core/components_ng/pattern/list/list_item_group_paint_method.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

void ListItemGroupPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (listItemGroupStyle_ == V2::ListItemGroupStyle::CARD) {
        SetListItemGroupDefaultAttributes(host);
    }
}

void ListItemGroupPattern::OnColorConfigurationUpdate()
{
    if (listItemGroupStyle_ != V2::ListItemGroupStyle::CARD) {
        return;
    }
    auto itemGroupNode = GetHost();
    CHECK_NULL_VOID(itemGroupNode);
    auto renderContext = itemGroupNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto pipeline = itemGroupNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto listItemGroupTheme = pipeline->GetTheme<ListItemTheme>();
    CHECK_NULL_VOID(listItemGroupTheme);

    renderContext->UpdateBackgroundColor(listItemGroupTheme->GetItemGroupDefaultColor());
}

void ListItemGroupPattern::SetListItemGroupDefaultAttributes(const RefPtr<FrameNode>& itemGroupNode)
{
    auto renderContext = itemGroupNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto layoutProperty = itemGroupNode->GetLayoutProperty<ListItemGroupLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);

    auto pipeline = GetContext();
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

void ListItemGroupPattern::DumpAdvanceInfo()
{
    DumpLog::GetInstance().AddDesc("itemStartIndex:" + std::to_string(itemStartIndex_));
    DumpLog::GetInstance().AddDesc("itemTotalCount:" + std::to_string(itemTotalCount_));
    DumpLog::GetInstance().AddDesc("itemDisplayEndIndex:" + std::to_string(itemDisplayEndIndex_));
    DumpLog::GetInstance().AddDesc("itemDisplayStartIndex:" + std::to_string(itemDisplayStartIndex_));
    DumpLog::GetInstance().AddDesc("headerMainSize:" + std::to_string(headerMainSize_));
    DumpLog::GetInstance().AddDesc("footerMainSize:" + std::to_string(footerMainSize_));
    DumpLog::GetInstance().AddDesc("spaceWidth:" + std::to_string(spaceWidth_));
    DumpLog::GetInstance().AddDesc("lanes:" + std::to_string(lanes_));
    DumpLog::GetInstance().AddDesc("laneGutter:" + std::to_string(laneGutter_));
    DumpLog::GetInstance().AddDesc("startHeaderPos:" + std::to_string(startHeaderPos_));
    DumpLog::GetInstance().AddDesc("endFooterPos:" + std::to_string(endFooterPos_));
}

RefPtr<LayoutAlgorithm> ListItemGroupPattern::CreateLayoutAlgorithm()
{
    CalculateItemStartIndex();
    auto layoutAlgorithm = MakeRefPtr<ListItemGroupLayoutAlgorithm>(headerIndex_, footerIndex_, itemStartIndex_);
    layoutAlgorithm->SetItemsPosition(itemPosition_);
    layoutAlgorithm->SetCachedItemsPosition(cachedItemPosition_);
    layoutAlgorithm->SetCachedIndex(forwardCachedIndex_, backwardCachedIndex_);
    layoutAlgorithm->SetLayoutedItemInfo(layoutedItemInfo_);
    if (childrenSize_ && ListChildrenSizeExist()) {
        if (!posMap_) {
            posMap_ = MakeRefPtr<ListPositionMap>();
        }
        layoutAlgorithm->SetListChildrenMainSize(childrenSize_);
        layoutAlgorithm->SetListPositionMap(posMap_);
    }
    return layoutAlgorithm;
}

RefPtr<NodePaintMethod> ListItemGroupPattern::CreateNodePaintMethod()
{
    auto layoutProperty = GetLayoutProperty<ListItemGroupLayoutProperty>();
    V2::ItemDivider itemDivider;
    auto divider = layoutProperty->GetDivider().value_or(itemDivider);
    auto drawVertical = (axis_ == Axis::HORIZONTAL);
    ListItemGroupPaintInfo listItemGroupPaintInfo { layoutDirection_, mainSize_, drawVertical, lanes_,
        spaceWidth_, laneGutter_, itemTotalCount_ };
    return MakeRefPtr<ListItemGroupPaintMethod>(
        divider, listItemGroupPaintInfo, itemPosition_, cachedItemPosition_, pressedItem_);
}

void ListItemGroupPattern::SyncItemsToCachedItemPosition()
{
    itemPosition_.insert(cachedItemPosition_.begin(), cachedItemPosition_.end());
    cachedItemPosition_.swap(itemPosition_);
    itemPosition_.clear();
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
    itemTotalCount_ = layoutAlgorithm->GetTotalItemCount();
    auto cacheParam = layoutAlgorithm->GetCacheParam();
    if (cacheParam) {
        forwardCachedIndex_ = cacheParam.value().forwardCachedIndex;
        backwardCachedIndex_ = cacheParam.value().backwardCachedIndex;
        adjustRefPos_ = layoutAlgorithm->GetAdjustReferenceDelta();
        layoutAlgorithm->SetCacheParam(std::nullopt);
    }
    if (lanes_ != layoutAlgorithm->GetLanes()) {
        lanes_ = layoutAlgorithm->GetLanes();
        ClearCachedItemPosition();
    }
    itemPosition_ = layoutAlgorithm->GetItemPosition();
    cachedItemPosition_ = layoutAlgorithm->GetCachedItemPosition();
    spaceWidth_ = layoutAlgorithm->GetSpaceWidth();
    axis_ = layoutAlgorithm->GetAxis();
    layoutDirection_ = layoutAlgorithm->GetLayoutDirection();
    mainSize_ = layoutAlgorithm->GetMainSize();
    laneGutter_ = layoutAlgorithm->GetLaneGutter();
    itemDisplayEndIndex_ = layoutAlgorithm->GetEndIndex();
    itemDisplayStartIndex_ = layoutAlgorithm->GetStartIndex();
    headerMainSize_ = layoutAlgorithm->GetHeaderMainSize();
    footerMainSize_ = layoutAlgorithm->GetFooterMainSize();
    layoutedItemInfo_ = layoutAlgorithm->GetLayoutedItemInfo();
    startHeaderPos_ = layoutAlgorithm->GetStartHeaderPos();
    endFooterPos_ = layoutAlgorithm->GetEndFooterPos();
    adjustRefPos_ = layoutAlgorithm->GetAdjustReferenceDelta();
    adjustTotalSize_ = layoutAlgorithm->GetAdjustTotalSize();
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

float ListItemGroupPattern::GetPaddingAndMargin() const
{
    auto layoutProperty = GetLayoutProperty<ListItemGroupLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, 0.0f);
    const auto& padding = layoutProperty->CreatePaddingAndBorder();
    const auto& margin = layoutProperty->CreateMargin();
    auto offsetBeforeContent = axis_ == Axis::HORIZONTAL ? padding.left.value_or(0) : padding.top.value_or(0);
    auto offsetAfterContent = axis_ == Axis::HORIZONTAL ? padding.right.value_or(0) : padding.bottom.value_or(0);
    offsetBeforeContent += axis_ == Axis::HORIZONTAL ? margin.left.value_or(0) : margin.top.value_or(0);
    offsetAfterContent += axis_ == Axis::HORIZONTAL ? margin.right.value_or(0) : margin.bottom.value_or(0);
    return offsetBeforeContent + offsetAfterContent;
}

float ListItemGroupPattern::GetEstimateOffset(float height, const std::pair<float, float>& targetPos,
    float headerMainSize, float footerMainSize) const
{
    if (layoutedItemInfo_.has_value() && layoutedItemInfo_.value().startIndex > 0) {
        float averageHeight = 0.0f;
        float estimateHeight = GetEstimateHeight(averageHeight, headerMainSize, footerMainSize, spaceWidth_);
        if (layoutedItemInfo_.value().endIndex >= itemTotalCount_ - 1) {
            return height + estimateHeight - targetPos.second;
        } else {
            return height - targetPos.first + layoutedItemInfo_.value().startIndex * averageHeight - spaceWidth_;
        }
    }
    return height - targetPos.first;
}

float ListItemGroupPattern::GetEstimateHeight(float& averageHeight,
    float headerMainSize, float footerMainSize, float spaceWidth) const
{
    auto layoutProperty = GetLayoutProperty<ListItemGroupLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, 0.0f);
    auto visible = layoutProperty->GetVisibility().value_or(VisibleType::VISIBLE);
    if (visible == VisibleType::GONE) {
        return 0.0f;
    }
    float paddingAndMargin = GetPaddingAndMargin();
    if (layoutedItemInfo_.has_value()) {
        auto totalHeight = (layoutedItemInfo_.value().endPos - layoutedItemInfo_.value().startPos + spaceWidth_);
        auto itemCount = layoutedItemInfo_.value().endIndex - layoutedItemInfo_.value().startIndex + 1;
        averageHeight = totalHeight / itemCount;
    }
    if (layouted_) {
        if (itemTotalCount_ > 0) {
            return itemTotalCount_ * averageHeight + headerMainSize_ + footerMainSize_ + paddingAndMargin - spaceWidth_;
        } else {
            return headerMainSize_ + footerMainSize_ + paddingAndMargin;
        }
    }
    float totalHeight = 0.0f;
    auto host = GetHost();
    auto totalItem = host->GetTotalChildCount();
    if (header_.Upgrade()) {
        totalItem -= 1;
        totalHeight += headerMainSize;
    }
    if (footer_.Upgrade()) {
        totalItem -= 1;
        totalHeight += footerMainSize;
    }
    return totalHeight + averageHeight * totalItem + paddingAndMargin - spaceWidth;
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

RefPtr<FrameNode> ListItemGroupPattern::GetListFrameNode() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto parent = host->GetParent();
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(parent);
    while (parent && !frameNode) {
        parent = parent->GetParent();
        frameNode = AceType::DynamicCast<FrameNode>(parent);
    }
    return frameNode;
}

bool ListItemGroupPattern::ListChildrenSizeExist()
{
    RefPtr<FrameNode> listNode = GetListFrameNode();
    CHECK_NULL_RETURN(listNode, false);
    auto listPattern = listNode->GetPattern<ListPattern>();
    CHECK_NULL_RETURN(listPattern, false);
    return listPattern->ListChildrenSizeExist();
}

RefPtr<ListChildrenMainSize> ListItemGroupPattern::GetOrCreateListChildrenMainSize()
{
    if (childrenSize_) {
        return childrenSize_;
    }
    childrenSize_ = AceType::MakeRefPtr<ListChildrenMainSize>();
    auto callback = [weakPattern = WeakClaim(this)](std::tuple<int32_t, int32_t, int32_t> change, ListChangeFlag flag) {
        auto pattern = weakPattern.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto context = pattern->GetContext();
        CHECK_NULL_VOID(context);
        context->AddBuildFinishCallBack([weakPattern, change, flag]() {
            auto pattern = weakPattern.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->OnChildrenSizeChanged(change, flag);
        });
        context->RequestFrame();
    };
    childrenSize_->SetOnDataChange(callback);
    return childrenSize_;
}

void ListItemGroupPattern::SetListChildrenMainSize(
    float defaultSize, const std::vector<float>& mainSize)
{
    childrenSize_ = AceType::MakeRefPtr<ListChildrenMainSize>(mainSize, defaultSize);
    OnChildrenSizeChanged({ -1, -1, -1 }, LIST_UPDATE_CHILD_SIZE);
}

void ListItemGroupPattern::OnChildrenSizeChanged(std::tuple<int32_t, int32_t, int32_t> change, ListChangeFlag flag)
{
    if (!posMap_) {
        posMap_ = MakeRefPtr<ListPositionMap>();
    }
    posMap_->MarkDirty(flag);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_BY_CHILD_REQUEST);
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
    VisibleContentInfo startInfo = { startArea, startItemIndexInGroup };
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
    VisibleContentInfo endInfo = { endArea, endItemIndexInGroup };
    return endInfo;
}

void ListItemGroupPattern::ResetChildrenSize()
{
    if (childrenSize_) {
        childrenSize_ = nullptr;
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        host->MarkDirtyNode(PROPERTY_UPDATE_BY_CHILD_REQUEST);
        OnChildrenSizeChanged({ -1, -1, -1 }, LIST_UPDATE_CHILD_SIZE);
    }
}

void ListItemGroupPattern::ClearItemPosition()
{
    itemPosition_.clear();
}

void ListItemGroupPattern::ClearCachedItemPosition()
{
    cachedItemPosition_.clear();
    forwardCachedIndex_ = -1;
    backwardCachedIndex_ = INT_MAX;
}

void ListItemGroupPattern::CalculateItemStartIndex()
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
    headerIndex_ = headerIndex;
    footerIndex_ = footerIndex;
    itemStartIndex_ = itemStartIndex;
}

void ListItemGroupPattern::UpdateActiveChildRange(bool forward, int32_t cacheCount, bool show)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (forward) {
        host->SetActiveChildRange(-1, itemStartIndex_ - 1, 0, cacheCount, show);
    } else {
        int32_t index = itemTotalCount_ + itemStartIndex_;
        host->SetActiveChildRange(index, index, cacheCount, 0, show);
    }
    if (show && headerIndex_ >= 0) {
        host->GetOrCreateChildByIndex(headerIndex_);
    }
    if (show && footerIndex_ >= 0) {
        host->GetOrCreateChildByIndex(footerIndex_);
    }
    if (show) {
        host->RebuildRenderContextTree();
    }
}

void ListItemGroupPattern::UpdateActiveChildRange(bool show)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (!itemPosition_.empty()) {
        auto start = itemStartIndex_ + itemPosition_.begin()->first;
        auto end = itemStartIndex_ + itemPosition_.rbegin()->first;
        host->SetActiveChildRange(start, end);
    } else if (headerIndex_ >= 0 || footerIndex_ >= 0) {
        host->SetActiveChildRange(-1, itemStartIndex_ - 1);
    } else {
        host->RemoveAllChildInRenderTree();
    }
    if (headerIndex_ >= 0) {
        host->GetOrCreateChildByIndex(headerIndex_);
    }
    if (footerIndex_ >= 0) {
        host->GetOrCreateChildByIndex(footerIndex_);
    }
    if (show) {
        host->RebuildRenderContextTree();
    }
}

int32_t ListItemGroupPattern::UpdateCachedIndexForward(bool outOfView, bool show, int32_t cacheCount)
{
    int32_t endIndex = (outOfView || itemPosition_.empty()) ? -1 : itemPosition_.rbegin()->first;
    int32_t endLimit = std::min(endIndex + cacheCount * lanes_, itemTotalCount_ - 1);
    int32_t forwardCachedIndex = std::clamp(forwardCachedIndex_, endIndex, endLimit);
    auto iter = cachedItemPosition_.begin();
    while (iter != cachedItemPosition_.end()) {
        if (iter->first >= endIndex + 1 && iter->first <= endLimit) {
            iter++;
            continue;
        }
        iter = cachedItemPosition_.erase(iter);
    }
    if (cachedItemPosition_.find(forwardCachedIndex) == cachedItemPosition_.end() ||
        cachedItemPosition_.find(endIndex + 1) == cachedItemPosition_.end()) {
        forwardCachedIndex = endIndex;
        cachedItemPosition_.clear();
    }
    if (outOfView && forwardCachedIndex < forwardCachedIndex_) {
        UpdateActiveChildRange(true, forwardCachedIndex + 1, show);
    }
    return forwardCachedIndex;
}

int32_t ListItemGroupPattern::UpdateCachedIndexBackward(bool outOfView, bool show, int32_t cacheCount)
{
    int32_t startIndex = (outOfView || itemPosition_.empty()) ? itemTotalCount_ : itemPosition_.begin()->first;
    int32_t startLimit = std::max(startIndex - cacheCount * lanes_, 0);
    if (startLimit % lanes_ != 0) {
        startLimit += (lanes_ - startLimit % lanes_);
    }
    int32_t backwardCachedIndex = std::clamp(backwardCachedIndex_, startLimit, startIndex);
    auto iter = cachedItemPosition_.begin();
    while (iter != cachedItemPosition_.end()) {
        if (iter->first >= startLimit && iter->first <= startIndex - 1) {
            iter++;
            continue;
        }
        iter = cachedItemPosition_.erase(iter);
    }
    if (cachedItemPosition_.find(backwardCachedIndex) == cachedItemPosition_.end() ||
        cachedItemPosition_.find(startIndex - 1) == cachedItemPosition_.end()) {
        backwardCachedIndex = startIndex;
        cachedItemPosition_.clear();
    }
    if (outOfView && backwardCachedIndex > backwardCachedIndex_) {
        UpdateActiveChildRange(false, itemTotalCount_ - backwardCachedIndex, show);
    }
    return backwardCachedIndex;
}

std::pair<int32_t, int32_t> ListItemGroupPattern::UpdateCachedIndexOmni(int32_t forwardCache, int32_t backwardCache)
{
    int32_t forwardRes = -1;
    int32_t backwardRes = INT_MAX;
    int32_t startIndex = itemPosition_.begin()->first;
    int32_t startLimit = std::max(startIndex - backwardCache * lanes_, 0);
    if (startLimit % lanes_ != 0) {
        startLimit += (lanes_ - startLimit % lanes_);
    }
    int32_t backwardCachedIndex = std::clamp(backwardCachedIndex_, startLimit, startIndex);
    int32_t endIndex = itemPosition_.rbegin()->first;
    int32_t endLimit = std::min(endIndex + forwardCache * lanes_, itemTotalCount_ - 1);
    int32_t forwardCachedIndex = std::clamp(forwardCachedIndex_, endIndex, endLimit);
    auto iter = cachedItemPosition_.begin();
    while (iter != cachedItemPosition_.end()) {
        if ((iter->first >= startLimit && iter->first <= startIndex - 1) ||
            (iter->first >= endIndex + 1 && iter->first <= endLimit)) {
            iter++;
            continue;
        }
        iter = cachedItemPosition_.erase(iter);
    }
    if (cachedItemPosition_.find(backwardCachedIndex) == cachedItemPosition_.end() ||
        cachedItemPosition_.find(startIndex - 1) == cachedItemPosition_.end()) {
        backwardRes = startIndex;
    } else {
        backwardRes = backwardCachedIndex;
    }
    if (cachedItemPosition_.find(forwardCachedIndex) == cachedItemPosition_.end() ||
        cachedItemPosition_.find(endIndex + 1) == cachedItemPosition_.end()) {
        forwardRes = endIndex;
    } else {
        forwardRes = forwardCachedIndex;
    }
    return { forwardRes, backwardRes };
}

CachedIndexInfo ListItemGroupPattern::UpdateCachedIndex(
    bool outOfView, bool reCache, int32_t forwardCache, int32_t backwardCache)
{
    CachedIndexInfo res;
    auto host = GetHost();
    if (!host) {
        forwardCachedIndex_ = -1;
        backwardCachedIndex_ = INT_MAX;
        return res;
    }
    auto listNode = GetListFrameNode();
    bool show = listNode && listNode->GetLayoutProperty<ListLayoutProperty>() ?
        listNode->GetLayoutProperty<ListLayoutProperty>()->GetShowCachedItemsValue(false) : false;
    if (itemTotalCount_ == -1 || host->CheckNeedForceMeasureAndLayout()) {
        CalculateItemStartIndex();
        itemTotalCount_ = host->GetTotalChildCount() - itemStartIndex_;
    }
    if (outOfView) {
        ClearItemPosition();
    }
    if (reCache || reCache_) {
        ClearCachedItemPosition();
        UpdateActiveChildRange(show);
        reCache_ = false;
    }
    int32_t lanes = lanes_ > 1 ? lanes_ : 1;
    if (forwardCache > -1 && backwardCache > -1 && !itemPosition_.empty()) {
        auto cached = UpdateCachedIndexOmni(forwardCache, backwardCache);
        forwardCachedIndex_ = cached.first;
        backwardCachedIndex_ = cached.second;
        int32_t startIndex = itemPosition_.begin()->first;
        int32_t endIndex = itemPosition_.rbegin()->first;
        res.forwardCachedCount = (forwardCachedIndex_ - endIndex + lanes - 1) / lanes;
        res.forwardCacheMax = (itemTotalCount_ - 1 - endIndex + lanes - 1) / lanes;
        res.backwardCachedCount = (startIndex - backwardCachedIndex_ + lanes - 1) / lanes;
        res.backwardCacheMax = (startIndex + lanes - 1) / lanes;
    } else if (forwardCache > -1) {
        forwardCachedIndex_ = UpdateCachedIndexForward(outOfView, show, forwardCache);
        backwardCachedIndex_ = INT_MAX;
        int32_t endIndex = (outOfView || itemPosition_.empty()) ? -1 : itemPosition_.rbegin()->first;
        res.forwardCachedCount = (forwardCachedIndex_ - endIndex + lanes - 1) / lanes;
        res.forwardCacheMax = (itemTotalCount_ - 1 - endIndex + lanes - 1) / lanes;
    } else if (backwardCache > -1) {
        forwardCachedIndex_ = -1;
        backwardCachedIndex_ = UpdateCachedIndexBackward(outOfView, show, backwardCache);
        int32_t startIndex = (outOfView || itemPosition_.empty()) ? itemTotalCount_ : itemPosition_.begin()->first;
        res.backwardCachedCount = (startIndex - backwardCachedIndex_ + lanes - 1) / lanes;
        res.backwardCacheMax = (startIndex + lanes - 1) / lanes;
    }
    return res;
}

bool ListItemGroupPattern::NeedCacheForward(const LayoutWrapper* listWrapper) const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, true);
    auto listProperty = AceType::DynamicCast<ListLayoutProperty>(listWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(listProperty, true);
    auto listPadding = listProperty->CreatePaddingAndBorder().Offset();
    auto offset = host->GetGeometryNode()->GetMarginFrameOffset();
    if (GreatNotEqual(GetMainAxisOffset(offset, axis_) + headerMainSize_, GetMainAxisOffset(listPadding, axis_))) {
        return true;
    } else {
        return false;
    }
}

void ListItemGroupPattern::LayoutCache(const LayoutConstraintF& constraint, int64_t deadline,
    int32_t forwardCached, int32_t backwardCached, ListMainSizeValues listSizeValues)
{
    auto listNode = GetListFrameNode();
    CHECK_NULL_VOID(listNode);
    auto listPattern = listNode->GetPattern<ListPattern>();
    CHECK_NULL_VOID(listPattern);
    auto listLayoutProperty = listNode->GetLayoutProperty<ListLayoutProperty>();
    CHECK_NULL_VOID(listLayoutProperty);
    auto cacheCountForward = listLayoutProperty->GetCachedCountWithDefault() - forwardCached;
    auto cacheCountBackward = listLayoutProperty->GetCachedCountWithDefault() - backwardCached;
    if (cacheCountForward < 1 && cacheCountBackward < 1) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutAlgorithmWrapper = host->GetLayoutAlgorithm(true);
    CHECK_NULL_VOID(layoutAlgorithmWrapper);
    auto itemGroup = AceType::DynamicCast<ListItemGroupLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_VOID(itemGroup);
    ListItemGroupCacheParam param = {
        .forward = listSizeValues.forward,
        .backward = listSizeValues.backward,
        .show = listLayoutProperty->GetShowCachedItemsValue(false),
        .cacheCountForward = cacheCountForward,
        .cacheCountBackward = cacheCountBackward,
        .forwardCachedIndex = forwardCachedIndex_,
        .backwardCachedIndex = backwardCachedIndex_,
        .deadline = deadline,
    };
    itemGroup->SetContentOffset(listSizeValues.contentStartOffset, listSizeValues.contentEndOffset);
    itemGroup->SetCacheParam(param);
    itemGroup->SetListLayoutProperty(listLayoutProperty);
    itemGroup->SetListMainSize(listSizeValues.startPos, listSizeValues.endPos, listSizeValues.referencePos,
        listSizeValues.prevContentMainSize, listSizeValues.forward);
    host->GetLayoutProperty()->UpdatePropertyChangeFlag(PROPERTY_UPDATE_MEASURE);
    host->GetGeometryNode()->SetParentLayoutConstraint(constraint);
    FrameNode::ProcessOffscreenNode(host, true);
    if ((!NearZero(adjustRefPos_) || !NearZero(adjustTotalSize_)) && !(childrenSize_ && ListChildrenSizeExist())) {
        listPattern->UpdateChildPosInfo(indexInList_, adjustRefPos_, adjustTotalSize_);
        adjustRefPos_ = 0.0f;
        adjustTotalSize_ = 0.0f;
    }
}

void ListItemGroupPattern::SetListItemGroupStyle(V2::ListItemGroupStyle style)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (listItemGroupStyle_ == V2::ListItemGroupStyle::NONE && style == V2::ListItemGroupStyle::CARD) {
        listItemGroupStyle_ = style;
        SetListItemGroupDefaultAttributes(host);
    }
}

float ListItemGroupPattern::GetListPaddingOffset(const RefPtr<FrameNode>& listNode) const
{
    float offset = 0;
    CHECK_NULL_RETURN(listNode, offset);
    auto layoutProperty = listNode->GetLayoutProperty<ListLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, offset);
    auto padding = layoutProperty->CreatePaddingAndBorder();
    return GetMainAxisOffset(padding.Offset(), axis_);
}

bool ListItemGroupPattern::FirstItemFullVisible(const RefPtr<FrameNode>& listNode) const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, true);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, true);
    OffsetF selfOffset = geometryNode->GetPaddingOffset();
    float mainPos = GetMainAxisOffset(selfOffset, axis_) + headerMainSize_;
    float listPadding = GetListPaddingOffset(listNode);
    return GreatNotEqual(mainPos, listPadding);
}

bool ListItemGroupPattern::CheckDataChangeOutOfStart(int32_t index, int32_t count, int32_t startIndex)
{
    if (count == 0 || (count > 0 && index > startIndex) ||
        (count < 0 && index >= startIndex)) {
        return false;
    }

    RefPtr<FrameNode> listNode = GetListFrameNode();
    CHECK_NULL_RETURN(listNode, false);
    auto listPattern = listNode->GetPattern<ListPattern>();
    CHECK_NULL_RETURN(listPattern, false);
    if (!listPattern->GetMaintainVisibleContentPosition()) {
        return false;
    }

    if (startIndex == 0 && index == 0 && count > 0 && FirstItemFullVisible(listNode)) {
        return false;
    }
    listPattern->MarkNeedReEstimateOffset();
    return true;
}

void ListItemGroupPattern::NotifyDataChange(int32_t index, int32_t count)
{
    if (itemPosition_.empty()) {
        return;
    }
    index -= itemStartIndex_;
    int32_t startIndex = itemPosition_.begin()->first;
    if (!CheckDataChangeOutOfStart(index, count, startIndex)) {
        return;
    }

    count = std::max(count, index - startIndex);
    int32_t mod = 0;
    if (count < 0 && lanes_ > 1) {
        mod = -count % lanes_;
    }
    auto prevPosMap = std::move(itemPosition_);
    for (auto &pos : prevPosMap) {
        if (mod > 0) {
            mod--;
        } else {
            itemPosition_[pos.first + count] = pos.second;
        }
    }
    if (layoutedItemInfo_ && layoutedItemInfo_.value().startIndex >= index) {
        auto& info = layoutedItemInfo_.value();
        info.startIndex = std::max(info.startIndex + count, 0);
        info.endIndex = std::max(info.endIndex + count, 0);
        if (lanes_ > 1) {
            if (count < 0) {
                info.startIndex += -count % lanes_;
            } else {
                info.endIndex -= count % lanes_;
            }
        }
    }
}

void ListItemGroupPattern::DumpAdvanceInfo(std::unique_ptr<JsonValue>& json)
{
    json->Put("itemStartIndex", itemStartIndex_);
    json->Put("itemTotalCount", itemTotalCount_);
    json->Put("itemDisplayEndIndex", itemDisplayEndIndex_);
    json->Put("itemDisplayStartIndex", itemDisplayStartIndex_);
    json->Put("headerMainSize", headerMainSize_);
    json->Put("footerMainSize", footerMainSize_);
    json->Put("spaceWidth", spaceWidth_);
    json->Put("lanes", lanes_);
    json->Put("laneGutter", laneGutter_);
    json->Put("startHeaderPos", startHeaderPos_);
    json->Put("endFooterPos", endFooterPos_);
}
} // namespace OHOS::Ace::NG
