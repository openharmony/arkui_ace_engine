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
#include "base/utils/multi_thread.h"
#include "core/components_ng/pattern/list/list_item_group_paint_method.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/components/list/list_theme.h"


namespace OHOS::Ace::NG {

void ListItemGroupPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    // call OnAttachToFrameNodeMultiThread by multi thread
    THREAD_SAFE_NODE_CHECK(host, OnAttachToFrameNode);
    CHECK_NULL_VOID(host);
    if (listItemGroupStyle_ == V2::ListItemGroupStyle::CARD) {
        SetListItemGroupDefaultAttributes(host);
    }
}

void ListItemGroupPattern::OnAttachToMainTree()
{
    auto host = GetHost();
    // call OnAttachToMainTreeMulti by multi thread
    THREAD_SAFE_NODE_CHECK(host, OnAttachToMainTree);
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
    auto layoutAlgorithm =
        MakeRefPtr<ListItemGroupLayoutAlgorithm>(headerIndex_, footerIndex_, itemStartIndex_, footerCount_);
    layoutAlgorithm->SetItemsPosition(itemPosition_);
    layoutAlgorithm->SetCachedItemsPosition(cachedItemPosition_);
    layoutAlgorithm->SetCachedIndex(forwardCachedIndex_, backwardCachedIndex_);
    layoutAlgorithm->SetLayoutedItemInfo(layoutedItemInfo_);
    layoutAlgorithm->SetPrevTotalItemCount(itemTotalCount_);
    layoutAlgorithm->SetPrevTotalMainSize(mainSize_);
    layoutAlgorithm->SetPrevMeasureBreak(prevMeasureBreak_);
    layoutAlgorithm->SetLanes(lanes_);
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
        spaceWidth_, laneGutter_, itemTotalCount_, listContentSize_ };
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
    footerIndex_ = layoutAlgorithm->GetFooterIndex();
    isStackFromEnd_ = layoutAlgorithm->GetStackFromEnd();
    auto cacheParam = layoutAlgorithm->GetCacheParam();
    if (cacheParam) {
        forwardCachedIndex_ = isStackFromEnd_ ? itemTotalCount_ - cacheParam.value().backwardCachedIndex - 1 :
                                                cacheParam.value().forwardCachedIndex;
        backwardCachedIndex_ = isStackFromEnd_ ? itemTotalCount_ - cacheParam.value().forwardCachedIndex - 1 :
                                                 cacheParam.value().backwardCachedIndex;
        layoutAlgorithm->SetCacheParam(std::nullopt);
    }
    MappingPropertiesFromLayoutAlgorithm(layoutAlgorithm);
    CheckListDirectionInCardStyle();
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto accessibilityProperty = host->GetAccessibilityProperty<ListItemGroupAccessibilityProperty>();
    if (accessibilityProperty != nullptr) {
        accessibilityProperty->SetCollectionItemCounts(layoutAlgorithm->GetTotalItemCount());
    }
    auto listLayoutProperty = host->GetLayoutProperty<ListItemGroupLayoutProperty>();
    return listLayoutProperty && listLayoutProperty->GetDivider().has_value();
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

bool ListItemGroupPattern::IsVisible() const
{
    auto layoutProperty = GetLayoutProperty<ListItemGroupLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    auto visible = layoutProperty->GetVisibility().value_or(VisibleType::VISIBLE);
    if (visible == VisibleType::GONE) {
        return false;
    }
    return true;
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
    auto pipeline = GetContext();
    if (pipeline && pipeline->GetPixelRoundMode() == PixelRoundMode::PIXEL_ROUND_AFTER_MEASURE) {
        childrenSize_->SetIsRoundingMode();
    }
    return childrenSize_;
}

void ListItemGroupPattern::SetListChildrenMainSize(
    float defaultSize, const std::vector<float>& mainSize)
{
    childrenSize_ = AceType::MakeRefPtr<ListChildrenMainSize>(mainSize, defaultSize);
    OnChildrenSizeChanged({ -1, -1, -1 }, LIST_UPDATE_CHILD_SIZE);
    auto pipeline = GetContext();
    if (pipeline && pipeline->GetPixelRoundMode() == PixelRoundMode::PIXEL_ROUND_AFTER_MEASURE) {
        childrenSize_->SetIsRoundingMode();
    }
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
    int32_t footerCount = 0;
    auto footer = footer_.Upgrade();
    if (footer) {
        int32_t count = footer->FrameCount();
        if (count > 0) {
            footerCount = count;
        }
    }
    AdjustMountTreeSequence(footerCount);
    
    int32_t headerIndex = -1;
    int32_t itemStartIndex = 0;
    auto header = header_.Upgrade();
    if (header) {
        auto count = header->FrameCount();
        if (count > 0) {
            headerIndex = itemStartIndex;
            itemStartIndex += count;
        }
    }

    headerIndex_ = headerIndex;
    itemStartIndex_ = itemStartIndex;
    footerCount_ = footerCount;
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
        host->SetActiveChildRange(-1, -1);
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
        itemTotalCount_ = host->GetTotalChildCount() - itemStartIndex_ - footerCount_;
    }
    if (outOfView) {
        cachedItemPosition_.merge(itemPosition_);
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
    if (isStackFromEnd_) {
        std::swap(res.forwardCachedCount, res.backwardCachedCount);
        std::swap(res.forwardCacheMax, res.backwardCacheMax);
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

bool ListItemGroupPattern::CheckDataChangeOutOfStart(int32_t index, int32_t count, int32_t startIndex, int32_t endIndex)
{
    if (count == 0) {
        return false;
    }
    if (((count > 0 && index > startIndex) || (count < 0 && index >= startIndex)) && !isStackFromEnd_) {
        return false;
    }
    if (((count > 0 && index < endIndex) || (count < 0 && index <= endIndex)) && isStackFromEnd_) {
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
    if (auto parentList = GetListFrameNode()) {
        if (auto listPattern = parentList->GetPattern<ListPattern>()) {
            listPattern->UpdateGroupFocusIndexForDataChange(GetIndexInList(), index, count);
        }
    }

    if (itemPosition_.empty()) {
        return;
    }
    index -= itemStartIndex_;
    int32_t startIndex = itemPosition_.begin()->first;
    int32_t endIndex = itemPosition_.rbegin()->first;
    if (!CheckDataChangeOutOfStart(index, count, startIndex, endIndex)) {
        return;
    }

    count = !isStackFromEnd_ ? std::max(count, index - startIndex) : - std::max(count, endIndex - index);
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

void ListItemGroupPattern::UpdateDefaultColor()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContextWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<ListTheme>();
    CHECK_NULL_VOID(theme);
    auto listItemLayoutProperty = host->GetLayoutProperty<ListItemGroupLayoutProperty>();
    CHECK_NULL_VOID(listItemLayoutProperty);
    if (!listItemLayoutProperty->HasDividerColorSetByUser() ||
        !listItemLayoutProperty->GetDividerColorSetByUserValue()) {
        V2::ItemDivider value;
        ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(ListItemGroupLayoutProperty, Divider, value, host, value);
        value.color = theme->GetDividerColor();
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListItemGroupLayoutProperty, Divider, value, host);
    }
}

void ListItemGroupPattern::OnColorModeChange(uint32_t colorMode)
{
    Pattern::OnColorModeChange(colorMode);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    CHECK_NULL_VOID(SystemProperties::ConfigChangePerform());
    UpdateDefaultColor();
    host->MarkDirtyNode(PROPERTY_UPDATE_NORMAL);
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

ScopeFocusAlgorithm ListItemGroupPattern::GetScopeFocusAlgorithm()
{
    auto property = GetLayoutProperty<ListItemGroupLayoutProperty>();
    if (!property) {
        return {};
    }
    auto listNode = GetListFrameNode();
    CHECK_NULL_RETURN(listNode, {});
    auto listProperty = listNode->GetLayoutProperty<ListLayoutProperty>();
    CHECK_NULL_RETURN(listProperty, {});
    return ScopeFocusAlgorithm(listProperty->GetListDirection().value_or(Axis::VERTICAL) == Axis::VERTICAL, true,
        ScopeType::OTHERS,
        [wp = WeakClaim(this)](
            FocusStep step, const WeakPtr<FocusHub>& currFocusNode, WeakPtr<FocusHub>& nextFocusNode) -> bool {
            auto listItemGroup = wp.Upgrade();
            if (listItemGroup) {
                nextFocusNode = listItemGroup->GetNextFocusNode(step, currFocusNode);
            }
            return nextFocusNode.Upgrade() != currFocusNode.Upgrade();
        });
}

WeakPtr<FocusHub> ListItemGroupPattern::GetChildFocusNodeByIndex(int32_t tarIndexInGroup)
{
    auto listItemGroupFrame = GetHost();
    CHECK_NULL_RETURN(listItemGroupFrame, nullptr);
    auto listItemGroupFocus = listItemGroupFrame->GetFocusHub();
    CHECK_NULL_RETURN(listItemGroupFocus, nullptr);
    WeakPtr<FocusHub> target;
    listItemGroupFocus->AnyChildFocusHub([&target, tarIndexInGroup](const RefPtr<FocusHub>& childFocus) {
        if (!childFocus->IsFocusable()) {
            return false;
        }
        auto childFrame = childFocus->GetFrameNode();
        if (!childFrame) {
            return false;
        }
        auto childPattern = childFrame->GetPattern();
        if (!childPattern) {
            return false;
        }
        auto childItemPattern = AceType::DynamicCast<ListItemPattern>(childPattern);
        if (!childItemPattern) {
            auto parentNode = childFrame->GetParentFrameNode();
            CHECK_NULL_RETURN(parentNode, false);
            auto parentPattern = AceType::DynamicCast<ListItemGroupPattern>(parentNode->GetPattern());
            CHECK_NULL_RETURN(parentPattern, false);
            if ((parentPattern->GetHeader() == childFrame && tarIndexInGroup == -1) ||
                (parentPattern->GetFooter() == childFrame && tarIndexInGroup == parentPattern->GetTotalItemCount())) {
                target = childFocus;
                return true;
            }

            return false;
        }

        auto curIndexInGroup = childItemPattern->GetIndexInListItemGroup();
        if (curIndexInGroup == tarIndexInGroup) {
            target = childFocus;
            return true;
        }
        return false;
    });
    return target;
}

void ListItemGroupPattern::AdjustMountTreeSequence(int32_t footerCount)
{
    // Adjust the mount tree sequence to header, listitem, footer
    if (footerIndex_ < itemStartIndex_) {
        auto footer = footer_.Upgrade();
        CHECK_NULL_VOID(footer);
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto totalChildCount = host->GetTotalChildCount();
        auto childNode = host->GetChildAtIndex(itemStartIndex_);
        CHECK_NULL_VOID(childNode);
        footer->MovePosition(-1);
        footerIndex_ = totalChildCount - footerCount;
        itemStartIndex_ -= footerCount;
    }
}

bool ListItemGroupPattern::GetCurrentFocusIndices(
    const RefPtr<FrameNode>& curFrame, const RefPtr<Pattern>& curPattern, int32_t& curIndexInGroup)
{
    // Only for GetNextFocusNode
    CHECK_NULL_RETURN(curFrame, false);
    CHECK_NULL_RETURN(curPattern, false);
    auto curItemPattern = AceType::DynamicCast<ListItemPattern>(curPattern);
    // In ListItemGroup, the current focus node could be the Header, Footer, or a ListItem of the ListItemGroup.
    // If the current focus node is the Header or Footer of the ListItemGroup,
    // it is necessary to retrieve the index of the current focus node within the ListItemGroup.
    if (!curItemPattern) {
        if (GetHeader() == curFrame) {
            curIndexInGroup = -1;
        } else if (GetFooter() == curFrame) {
            curIndexInGroup = GetTotalItemCount();
        } else {
            return false;
        }
    } else {
        // If the current focus node is a ListItem, it is necessary to retrieve the index of the current focus node
        // within the ListItemGroup.
        curIndexInGroup = curItemPattern->GetIndexInListItemGroup();
    }
    return true;
}

void ListItemGroupPattern::AdjustFocusStepForRtl(FocusStep& step, bool isVertical)
{
    // FocusStep LEFT/RIGH reverse flag
    bool reverseHorizontal = false;
    // FocusStep UP/DOWN reverse flag
    bool reverseVertical = false;

    if ((layoutDirection_ != TextDirection::RTL && isVertical && isStackFromEnd_) ||
        (layoutDirection_ == TextDirection::RTL && !isStackFromEnd_)) {
        reverseHorizontal = true;
    } else if (layoutDirection_ != TextDirection::RTL && !isVertical && isStackFromEnd_) {
        reverseVertical = true;
    } else if (layoutDirection_ == TextDirection::RTL && !isVertical && isStackFromEnd_) {
        reverseHorizontal = true;
        reverseVertical = true;
    }

    if (reverseHorizontal) {
        if (step == FocusStep::LEFT) {
            step = FocusStep::RIGHT;
        } else if (step == FocusStep::RIGHT) {
            step = FocusStep::LEFT;
        }
    }

    if (reverseVertical) {
        if (step == FocusStep::UP) {
            step = FocusStep::DOWN;
        } else if (step == FocusStep::DOWN) {
            step = FocusStep::UP;
        }
    }
}

const ListItemGroupInfo* ListItemGroupPattern::GetPosition(int32_t index) const
{
    // Only for GetCrossAxisNextIndex
    auto it = itemPosition_.find(index);
    if (it != itemPosition_.end()) {
        return &it->second;
    }
    auto cachedIt = cachedItemPosition_.find(index);
    return (cachedIt != cachedItemPosition_.end()) ? &cachedIt->second : nullptr;
}

bool ListItemGroupPattern::NextPositionBlocksMove(
    const ListItemGroupInfo* curPos, const ListItemGroupInfo* nextPos, bool isVertical) const
{
    // Only for GetCrossAxisNextIndex, determine if the next position blocks movement.

    if (!nextPos) {
        // No position information, allow movement (or handle externally).
        return false;
    }
    // Check if the current and next positions are in the same column.
    // If the endPos and startPos of two items are the same, it indicates they are in the same row or column, allowing
    // focus movement; otherwise, it is considered to have reached the first column (row) or the last column (row),
    // disallowing focus movement.
    return curPos && (!NearEqual(curPos->endPos, nextPos->endPos) && !NearEqual(curPos->startPos, nextPos->startPos));
}

void ListItemGroupPattern::HandleForwardStep(
    const RefPtr<FrameNode>& curFrame, int32_t curIndexInGroup, int32_t& moveStep, int32_t& nextIndex)
{
    // Only for DetermineMultiLaneStep
    CHECK_NULL_VOID(curFrame);
    moveStep = (GetHeader() == curFrame || GetFooter() == curFrame) ? 1 : lanes_;
    nextIndex = nextIndex + moveStep;
    if (curIndexInGroup < GetTotalItemCount() && curIndexInGroup >= 0) {
        // Neither Header nor Footer. If it is the last row and the DOWN key is pressed,
        // if there is a footer, move to the footer; if there is no footer, directly move
        // to the position where nextIndex >= itemTotalCount_, which is nullptr.
        auto row = (itemTotalCount_ - 1) / lanes_;
        auto curRow = curIndexInGroup / lanes_;
        if (isStackFromEnd_) {
            curRow = row - (itemTotalCount_ - 1 - curIndexInGroup) / lanes_;
        }
        if (curRow == row && IsHasFooter()) {
            nextIndex = itemTotalCount_;
        } else if (curRow == row - 1 && nextIndex >= itemTotalCount_) {
            // If it is the second-to-last row, pressing DOWN when nextIndex >= itemTotalCount_ moves to the last item.
            nextIndex = itemTotalCount_ - 1;
        }
    }
}

void ListItemGroupPattern::HandleBackwardStep(
    const RefPtr<FrameNode>& curFrame, int32_t curIndexInGroup, int32_t& moveStep, int32_t& nextIndex)
{
    // Only for DetermineMultiLaneStep
    CHECK_NULL_VOID(curFrame);
    // If the current focus is on the header, set moveStep = 1; if the current focus is on the footer,
    // set moveStep = -1;
    moveStep = (GetHeader() == curFrame || GetFooter() == curFrame) ? -1 : -lanes_;
    nextIndex = curIndexInGroup + moveStep;
    if (curIndexInGroup >= 0 && curIndexInGroup < GetTotalItemCount()) {
        auto curRow = curIndexInGroup / lanes_;
        if (isStackFromEnd_) {
            auto row = (itemTotalCount_ - 1) / lanes_;
            curRow = row - (itemTotalCount_ - 1 - curIndexInGroup) / lanes_;
        }
        // If the current focus is on the first row, pressing the UP key moves to the Header
        if (curRow == 0 && IsHasHeader()) {
            nextIndex = -1;
        } else if (curRow == 1 && nextIndex < 0) {
            // If it is the second row, pressing UP when nextIndex < 0 moves to the first item.
            nextIndex = 0;
        }
    }
}

bool ListItemGroupPattern::HandleCrossAxisRightOrDownStep(
    bool isVertical, int32_t curIndexInGroup, int32_t& moveStep, int32_t& nextIndex)
{
    // Only for DetermineMultiLaneStep
    moveStep = 1;
    nextIndex = curIndexInGroup + moveStep;
    auto col = curIndexInGroup % lanes_;
    // If the current focus is on the last column, pressing the RIGHT key will not move the focus further.
    if (isStackFromEnd_) {
        if ((itemTotalCount_ - 1 - curIndexInGroup) % lanes_ == 0) {
            nextIndex = curIndexInGroup;
        }
    } else if (col == lanes_ - 1 || curIndexInGroup == itemTotalCount_ - 1) {
        nextIndex = curIndexInGroup;
    }
    return true;
}

bool ListItemGroupPattern::HandleCrossAxisLeftOrUpStep(
    bool isVertical, int32_t curIndexInGroup, int32_t& moveStep, int32_t& nextIndex)
{
    // Only for DetermineMultiLaneStep
    moveStep = -1;
    nextIndex = curIndexInGroup + moveStep;
    auto col = curIndexInGroup % lanes_;
    // If the current focus is in the first column, pressing the LEFT key will not move the focus further.
    if (isStackFromEnd_) {
        if ((itemTotalCount_ - lanes_ - curIndexInGroup) % lanes_ == 0) {
            nextIndex = curIndexInGroup;
        }
    } else if (col <= 0) {
        nextIndex = curIndexInGroup;
    }
    return true;
}

bool ListItemGroupPattern::DetermineMultiLaneStep(FocusStep step, bool isVertical, const RefPtr<FrameNode>& curFrame,
    int32_t curIndexInGroup, int32_t& moveStep, int32_t& nextIndex)
{
    auto parentList = GetListFrameNode();
    CHECK_NULL_RETURN(parentList, false);
    auto listPattern = parentList->GetPattern<ListPattern>();
    CHECK_NULL_RETURN(listPattern, false);
    auto focusWrapMode = listPattern->GetFocusWrapMode();
    // Only for GetNextFocusNode
    CHECK_NULL_RETURN(curFrame, false);
    // ListItemGroup does not handle HOME/END, bubble it up to List for processing.
    if (step == FocusStep::UP_END || step == FocusStep::LEFT_END || step == FocusStep::DOWN_END ||
        step == FocusStep::RIGHT_END) {
        return false;
    } else if ((isVertical && (step == FocusStep::DOWN)) || (!isVertical && step == FocusStep::RIGHT)) {
        HandleForwardStep(curFrame, curIndexInGroup, moveStep, nextIndex);
    } else if ((isVertical && step == FocusStep::UP) || (!isVertical && step == FocusStep::LEFT)) {
        HandleBackwardStep(curFrame, curIndexInGroup, moveStep, nextIndex);
    } else if ((isVertical && (step == FocusStep::RIGHT)) || (!isVertical && step == FocusStep::DOWN)) {
        if (focusWrapMode == FocusWrapMode::WRAP_WITH_ARROW) {
            moveStep = 1;
            nextIndex = curIndexInGroup + 1;
        } else if (!HandleCrossAxisRightOrDownStep(isVertical, curIndexInGroup, moveStep, nextIndex)) {
            return false;
        }
    } else if ((isVertical && step == FocusStep::LEFT) || (!isVertical && step == FocusStep::UP)) {
        if (focusWrapMode == FocusWrapMode::WRAP_WITH_ARROW) {
            moveStep = -1;
            nextIndex = curIndexInGroup - 1;
        } else if (!HandleCrossAxisLeftOrUpStep(isVertical, curIndexInGroup, moveStep, nextIndex)) {
            return false;
        }
    } else if (step == FocusStep::TAB) {
        moveStep = 1;
        nextIndex = curIndexInGroup + 1;
    } else if (step == FocusStep::SHIFT_TAB) {
        moveStep = -1;
        nextIndex = curIndexInGroup - 1;
    }
    return true;
}

bool ListItemGroupPattern::DetermineSingleLaneStep(
    FocusStep step, bool isVertical, int32_t itemTotalCount_, int32_t& moveStep, int32_t& nextIndex)
{
    // Only for GetNextFocusNode
    // ListItemGroup does not handle HOME/END, bubble it up to List for processing.
    auto parentList = GetListFrameNode();
    CHECK_NULL_RETURN(parentList, false);
    auto listPattern = parentList->GetPattern<ListPattern>();
    CHECK_NULL_RETURN(listPattern, false);
    auto isDefault = listPattern->GetFocusWrapMode() == FocusWrapMode::DEFAULT;
    if (step == FocusStep::UP_END || step == FocusStep::LEFT_END || step == FocusStep::DOWN_END ||
        step == FocusStep::RIGHT_END) {
        return false;
    } else if (ListPattern::IsForwardStep(step, isVertical, isDefault)) {
        moveStep = 1;
        nextIndex += moveStep;
    } else if (ListPattern::IsBackwardStep(step, isVertical, isDefault)) {
        moveStep = -1;
        nextIndex += moveStep;
    } else if ((!isVertical && step == FocusStep::UP) || (!isVertical && step == FocusStep::DOWN)) {
        // If it is horizontal and there is only one row, pressing UP or DOWN keys returns nullptr,
        return false;
    }
    return true;
}

WeakPtr<FocusHub> ListItemGroupPattern::GetNextFocusNode(FocusStep step, const WeakPtr<FocusHub>& currentFocusNode)
{
    // Retrieve information about the current focus node.
    auto curFocus = currentFocusNode.Upgrade();
    CHECK_NULL_RETURN(curFocus, nullptr);
    auto curFrame = curFocus->GetFrameNode();
    CHECK_NULL_RETURN(curFrame, nullptr);
    auto parentList = GetListFrameNode();
    CHECK_NULL_RETURN(parentList, nullptr);
    auto listPattern = parentList->GetPattern<ListPattern>();
    CHECK_NULL_RETURN(listPattern, nullptr);
    auto curPattern = curFrame->GetPattern();
    CHECK_NULL_RETURN(curPattern, nullptr);

    int32_t curIndexInGroup = -1; // The index of the current item within the group.
    if (!GetCurrentFocusIndices(curFrame, curPattern, curIndexInGroup)) {
        return nullptr;
    }

    auto listProperty = parentList->GetLayoutProperty<ListLayoutProperty>();
    CHECK_NULL_RETURN(listProperty, nullptr);
    auto isVertical = listProperty->GetListDirection().value_or(Axis::VERTICAL) == Axis::VERTICAL;

    AdjustFocusStepForRtl(step, isVertical);

    auto moveStep = 0;
    auto nextIndex = curIndexInGroup;

    if (lanes_ <= 1) {
        if (!DetermineSingleLaneStep(step, isVertical, itemTotalCount_, moveStep, nextIndex)) {
            return nullptr;
        }
    } else {
        if (!DetermineMultiLaneStep(step, isVertical, curFrame, curIndexInGroup, moveStep, nextIndex)) {
            return nullptr;
        }
    }
    int32_t curGroupIndexInList = GetIndexInList();
    return FindNextValidFocus(moveStep, curIndexInGroup, curGroupIndexInList, nextIndex, currentFocusNode, step);
}

WeakPtr<FocusHub> ListItemGroupPattern::FindNextValidFocus(int32_t moveStep, int32_t curIndexInGroup,
    int32_t curGroupIndexInList, int32_t nextIndexInGroup, const WeakPtr<FocusHub>& currentFocusNode, FocusStep step)
{
    auto curFocus = currentFocusNode.Upgrade();
    CHECK_NULL_RETURN(curFocus, nullptr);
    auto parentList = GetListFrameNode();
    CHECK_NULL_RETURN(parentList, nullptr);
    auto listPattern = parentList->GetPattern<ListPattern>();
    CHECK_NULL_RETURN(listPattern, nullptr);
    auto listProperty = parentList->GetLayoutProperty<ListLayoutProperty>();
    CHECK_NULL_RETURN(listProperty, nullptr);
    auto isVertical = listProperty->GetListDirection().value_or(Axis::VERTICAL) == Axis::VERTICAL;

    ListItemGroupPara listItemGroupPara = { GetLanesInGroup(), GetEndIndexInGroup(), GetDisplayStartIndexInGroup(),
        GetDisplayEndIndexInGroup(), IsHasHeader(), IsHasFooter() };
    while (IsIndexInValidRange(nextIndexInGroup, itemTotalCount_)) {
        if (IsFocusMovementBlock(nextIndexInGroup, curIndexInGroup, itemTotalCount_)) {
            return currentFocusNode;
        }
        listPattern->LayoutItemInGroupForFocus(
            curGroupIndexInList, nextIndexInGroup, curIndexInGroup, listItemGroupPara, itemTotalCount_);
        auto nextFocusNode = GetChildFocusNodeByIndex(nextIndexInGroup);
        if (nextFocusNode.Upgrade()) {
            auto isDefault = listPattern->GetFocusWrapMode() == FocusWrapMode::DEFAULT;
            const ListItemGroupInfo* curPos = GetPosition(curIndexInGroup);
            const ListItemGroupInfo* nextPos = GetPosition(nextIndexInGroup);
            const bool isForward = (isVertical && step == FocusStep::RIGHT) || (!isVertical && step == FocusStep::DOWN);
            const bool isBackward = (isVertical && step == FocusStep::LEFT) || (!isVertical && step == FocusStep::UP);
            if ((isForward || isBackward) && NextPositionBlocksMove(curPos, nextPos, isVertical) && isDefault) {
                return nullptr;
            }
            return nextFocusNode;
        }
        nextIndexInGroup += moveStep;
    }
    return nullptr;
}

bool ListItemGroupPattern::IsIndexInValidRange(int32_t nextIndex, int32_t itemTotalCount_)
{
    const bool lowerBound = IsHasHeader() ? (nextIndex >= -1) : (nextIndex >= 0);
    const bool upperBound = IsHasFooter() ? (nextIndex <= itemTotalCount_) : (nextIndex < itemTotalCount_);
    return lowerBound && upperBound;
}

bool ListItemGroupPattern::IsFocusMovementBlock(int32_t nextIndex, int32_t curIndex, int32_t maxIndex) const
{
    return (nextIndex == curIndex) && (curIndex != -1) && (curIndex != maxIndex);
}

bool ListItemGroupPattern::FindHeadOrTailChild(
    const RefPtr<FocusHub>& childFocus, FocusStep step, WeakPtr<FocusHub>& target)
{
    CHECK_NULL_RETURN(childFocus, false);
    // Support moving focus to the first item of the List when pressing HOME
    // and to the last item of the List when pressing END.
    auto isHome = step == FocusStep::LEFT_END || step == FocusStep::UP_END;
    auto isEnd = step == FocusStep::RIGHT_END || step == FocusStep::DOWN_END;
    bool isFindTailOrHead = false;
    if (isHome) {
        isFindTailOrHead = childFocus->AnyChildFocusHub([&target](const RefPtr<FocusHub>& node) {
            auto headNode = node->GetHeadOrTailChild(true);
            if (headNode) {
                target = headNode;
                return true;
            }
            return false;
        });
    } else if (isEnd) {
        isFindTailOrHead = childFocus->AnyChildFocusHub(
            [&target](const RefPtr<FocusHub>& node) {
                auto tailNode = node->GetHeadOrTailChild(false);
                if (tailNode) {
                    target = tailNode;
                    return true;
                }
                return false;
            },
            true);
    }
    return isFindTailOrHead;
}
bool ListItemGroupPattern::IsInViewport(int32_t index) const
{
    if (itemDisplayStartIndex_ == itemDisplayEndIndex_ && itemDisplayStartIndex_ == 0) {
        auto host = GetHost();
        CHECK_NULL_RETURN(host, false);
        auto geometryNode = host->GetGeometryNode();
        CHECK_NULL_RETURN(geometryNode, false);
        auto rect = geometryNode->GetPaddingRect();
        auto footerOffset = rect.Height() + rect.GetY() - footerMainSize_;
        if (LessNotEqual(footerOffset, 0.0f)) {
            return false;
        }
    }
    return index >= itemDisplayStartIndex_ && index <= itemDisplayEndIndex_;
}

void ListItemGroupPattern::MappingPropertiesFromLayoutAlgorithm(
    const RefPtr<ListItemGroupLayoutAlgorithm>& layoutAlgorithm)
{
    CHECK_NULL_VOID(layoutAlgorithm);
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
    bool indexChanged = false;
    indexChanged = itemDisplayEndIndex_ != layoutAlgorithm->GetEndIndex() ||
                   itemDisplayStartIndex_ != layoutAlgorithm->GetStartIndex();
    itemDisplayEndIndex_ = layoutAlgorithm->GetEndIndex();
    itemDisplayStartIndex_ = layoutAlgorithm->GetStartIndex();
    headerMainSize_ = layoutAlgorithm->GetHeaderMainSize();
    footerMainSize_ = layoutAlgorithm->GetFooterMainSize();
    layoutedItemInfo_ = layoutAlgorithm->GetLayoutedItemInfo();
    startHeaderPos_ = layoutAlgorithm->GetStartHeaderPos();
    endFooterPos_ = layoutAlgorithm->GetEndFooterPos();
    adjustRefPos_ = layoutAlgorithm->GetAdjustReferenceDelta();
    adjustTotalSize_ = layoutAlgorithm->GetAdjustTotalSize();
    listContentSize_ = layoutAlgorithm->GetListContentSize();
    prevMeasureBreak_ = layoutAlgorithm->GroupMeasureInNextFrame();
    layouted_ = true;
    if (indexChanged) {
        auto parentList = GetListFrameNode();
        CHECK_NULL_VOID(parentList);
        auto listPattern = parentList->GetPattern<ListPattern>();
        CHECK_NULL_VOID(listPattern);
        if (!(itemDisplayStartIndex_ == itemDisplayEndIndex_ && itemDisplayStartIndex_ == 0)) {
            listPattern->FireFocusInListItemGroup(GetIndexInList());
        }
    }
}
} // namespace OHOS::Ace::NG
