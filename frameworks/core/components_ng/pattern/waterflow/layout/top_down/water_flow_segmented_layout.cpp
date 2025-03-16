/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/waterflow/layout/top_down/water_flow_segmented_layout.h"

#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "base/utils/utils.h"
#include "core/components/scroll/scroll_controller_base.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/waterflow/layout/top_down/water_flow_layout_info.h"
#include "core/components_ng/pattern/waterflow/layout/water_flow_layout_utils.h"
#include "core/components_ng/pattern/waterflow/water_flow_layout_property.h"
#include "core/components_ng/pattern/waterflow/water_flow_pattern.h"
#include "core/components_ng/property/templates_parser.h"

namespace OHOS::Ace::NG {
bool WaterFlowSegmentLayoutBase::IsSectionValid(const RefPtr<WaterFlowLayoutInfoBase>& info, int32_t childrenCnt)
{
    if (info->segmentTails_.empty()) {
        TAG_LOGW(AceLogTag::ACE_WATERFLOW, "Section is empty.");
        return false;
    }
    if (childrenCnt - 1 != info->segmentTails_.back()) {
        TAG_LOGW(AceLogTag::ACE_WATERFLOW,
            "Children count = %{public}d and doesn't match the number provided in Sections, which is %{public}d.",
            childrenCnt, info->segmentTails_.back() + 1);
        return false;
    }
    return true;
}

void WaterFlowSegmentedLayout::Measure(LayoutWrapper* wrapper)
{
    InitEnv(wrapper);
    info_->childrenCount_ = wrapper_->GetTotalChildCount();
    sections_ = wrapper_->GetHostNode()->GetPattern<WaterFlowPattern>()->GetSections();
    if (sections_ && !IsSectionValid(info_, info_->childrenCount_)) {
        info_->isDataValid_ = false;
        return;
    }

    info_->axis_ = axis_ = props_->GetAxis();
    auto [idealSize, matchChildren] = WaterFlowLayoutUtils::PreMeasureSelf(wrapper_, axis_);

    GetExpandArea(props_, info_);

    Init(idealSize);

    mainSize_ = GetMainAxisSize(idealSize, axis_);

    if (info_->jumpIndex_ != EMPTY_JUMP_INDEX) {
        MeasureOnJump(info_->jumpIndex_);
        info_->jumpIndex_ = EMPTY_JUMP_INDEX;
    } else if (info_->targetIndex_) {
        MeasureToTarget(*info_->targetIndex_, std::nullopt);
        info_->targetIndex_.reset();
    } else {
        MeasureOnOffset();
    }

    if (matchChildren) {
        PostMeasureSelf(idealSize);
    }
    info_->lastMainSize_ = mainSize_;

    const int32_t cacheCnt = props_->GetCachedCountValue(info_->defCachedCount_);
    wrapper_->SetCacheCount(cacheCnt);
    if (props_->GetShowCachedItemsValue(false)) {
        SyncPreloadItems(wrapper_, info_, cacheCnt);
    } else {
        PreloadItems(wrapper_, info_, cacheCnt);
    }
}

void WaterFlowSegmentedLayout::Layout(LayoutWrapper* wrapper)
{
    if (!info_->isDataValid_) {
        return;
    }

    InitEnv(wrapper);

    auto padding = props_->CreatePaddingAndBorder();
    auto initialOffset = OffsetF(padding.left.value_or(0.0f), padding.top.value_or(0.0f));

    size_t segmentCnt = itemsCrossSize_.size();
    std::vector<std::vector<float>> crossPos(segmentCnt);
    auto crossSize = wrapper_->GetGeometryNode()->GetFrameSize().CrossSize(axis_);
    auto layoutDirection = props_->GetNonAutoLayoutDirection();
    auto isRtl = layoutDirection == TextDirection::RTL && axis_ == Axis::VERTICAL;
    // prepare crossPos
    for (size_t i = 0; i < segmentCnt; ++i) {
        float pos = ((axis_ == Axis::VERTICAL) ? info_->margins_[i].left : info_->margins_[i].top).value_or(0.0f);
        for (const auto& len : itemsCrossSize_[i]) {
            crossPos[i].push_back(!isRtl ? pos : crossSize - pos - len);
            pos += len + crossGaps_[i];
        }
    }

    const bool isReverse = props_->IsReverse();
    const int32_t cacheCount = props_->GetCachedCountValue(info_->defCachedCount_);
    if (!props_->HasCachedCount()) {
        info_->UpdateDefaultCachedCount();
    }
    const int32_t maxIdx = std::min(info_->endIndex_ + cacheCount, static_cast<int32_t>(info_->itemInfos_.size() - 1));
    for (int32_t i = std::max(0, info_->startIndex_ - cacheCount); i <= maxIdx; ++i) {
        LayoutItem(i, crossPos[info_->GetSegment(i)][info_->itemInfos_[i].crossIdx], initialOffset, isReverse);
    }
    wrapper_->SetActiveChildRange(info_->NodeIdx(info_->startIndex_), info_->NodeIdx(info_->endIndex_), cacheCount,
        cacheCount, props_->GetShowCachedItemsValue(false));

    UpdateOverlay(wrapper_);
    // for compatibility
    info_->firstIndex_ = info_->startIndex_;
}

namespace {
inline float GetMeasuredHeight(const RefPtr<LayoutWrapper>& item, Axis axis)
{
    return GetMainAxisSize(item->GetGeometryNode()->GetMarginFrameSize(), axis);
}
/**
 * @brief Prepares a jump to the current StartItem.
 *
 * @param info WaterFlowLayoutInfo
 * @param  postJumpOffset set to current StartItem's offset relative to the viewport.
 */
void PrepareJump(const RefPtr<WaterFlowLayoutInfo>& info, std::optional<float>& postJumpOffset)
{
    if (info->endIndex_ == -1 || info->jumpIndex_ != EMPTY_JUMP_INDEX) {
        // implies that LayoutInfo has already been reset, no need to jump
        return;
    }
    info->jumpIndex_ = std::min(info->startIndex_, info->childrenCount_ - 1);
    info->align_ = ScrollAlign::START;
    float itemOffset = (info->itemInfos_.size() <= static_cast<size_t>(info->startIndex_))
                           ? info->storedOffset_
                           : info->currentOffset_ + info->itemInfos_[info->startIndex_].mainOffset;

    postJumpOffset = itemOffset;
}
} // namespace

int32_t WaterFlowSegmentedLayout::CheckDirtyItem() const
{
    for (int32_t i = info_->startIndex_; i <= info_->endIndex_; ++i) {
        if (static_cast<int32_t>(info_->itemInfos_.size()) <= i) {
            break;
        }
        float userDefHeight = WaterFlowLayoutUtils::GetUserDefHeight(sections_, info_->GetSegment(i), i);
        if (NonNegative(userDefHeight)) {
            continue;
        }
        auto child =
            MeasureItem(i, { info_->itemInfos_[i].crossIdx, info_->itemInfos_[i].mainOffset }, userDefHeight, false);
        CHECK_NULL_BREAK(child);
        if (!NearEqual(GetMeasuredHeight(child, axis_), info_->itemInfos_[i].mainSize)) {
            return i;
        }
    }
    return -1;
}

void WaterFlowSegmentedLayout::Init(const SizeF& frameSize)
{
    if (sections_) {
        const auto& sections = sections_->GetSectionInfo();
        if (info_->margins_.empty()) {
            // empty margins_ implies a segment change
            auto constraint = props_->GetLayoutConstraint();
            PrepareJump(info_, postJumpOffset_);
            info_->InitMargins(sections, constraint->scaleProperty, constraint->percentReference.Width());
            info_->PrepareSegmentStartPos();
        }
        SegmentedInit(sections, info_->margins_, frameSize);
    } else {
        RegularInit(frameSize);
        if (info_->footerIndex_ >= 0) {
            InitFooter(frameSize.CrossSize(axis_));
        }
    }

    int32_t updateIdx = wrapper_->GetHostNode()->GetChildrenUpdated();
    if (updateIdx != -1) {
        if (updateIdx <= info_->endIndex_) {
            PrepareJump(info_, postJumpOffset_);
        }
        info_->ClearCacheAfterIndex(updateIdx - 1);
    }

    const bool childDirty = props_->GetPropertyChangeFlag() & PROPERTY_UPDATE_BY_CHILD_REQUEST;
    if (childDirty) {
        const int32_t res = CheckDirtyItem();
        if (res != -1) {
            PrepareJump(info_, postJumpOffset_);
            info_->ClearCacheAfterIndex(res - 1);
            return;
        }
    }

    if (wrapper_->ConstraintChanged()) {
        PrepareJump(info_, postJumpOffset_);
    }
}

void WaterFlowSegmentLayoutBase::SegmentedInit(const std::vector<WaterFlowSections::Section>& options,
    const std::vector<PaddingPropertyF>& margins, const SizeF& frameSize)
{
    auto scale = props_->GetLayoutConstraint()->scaleProperty;
    size_t n = options.size();
    crossGaps_.resize(n);
    mainGaps_.resize(n);
    itemsCrossSize_.resize(n);
    for (size_t i = 0; i < n; ++i) {
        auto rowGap = options[i].rowsGap.value_or(props_->GetRowsGap().value_or(0.0_vp));
        auto columnGap = options[i].columnsGap.value_or(props_->GetColumnsGap().value_or(0.0_vp));
        mainGaps_[i] = ConvertToPx(rowGap, scale, frameSize.Height()).value_or(0.0f);
        crossGaps_[i] = ConvertToPx(columnGap, scale, frameSize.Width()).value_or(0.0f);
        if (axis_ == Axis::HORIZONTAL) {
            std::swap(crossGaps_[i], mainGaps_[i]);
        }

        const auto& margin = margins[i];
        float crossSize = frameSize.CrossSize(axis_) - (axis_ == Axis::VERTICAL ? margin.Width() : margin.Height());
        int32_t crossCnt = options[i].crossCount.value_or(1);
        itemsCrossSize_[i].resize(crossCnt);
        if (crossCnt == 0) {
            continue;
        }
        float itemSize = (crossSize + crossGaps_[i]) / crossCnt - crossGaps_[i];
        for (int32_t cross = 0; cross < crossCnt; ++cross) {
            itemsCrossSize_[i][cross] = itemSize;
        }
    }
}

void WaterFlowSegmentedLayout::RegularInit(const SizeF& frameSize)
{
    auto rowsTemplate = props_->GetRowsTemplate().value_or("1fr");
    auto columnsTemplate = props_->GetColumnsTemplate().value_or("1fr");
    auto scale = props_->GetLayoutConstraint()->scaleProperty;
    auto rowsGap = ConvertToPx(props_->GetRowsGap().value_or(0.0_vp), scale, frameSize.Height()).value_or(0);
    auto columnsGap = ConvertToPx(props_->GetColumnsGap().value_or(0.0_vp), scale, frameSize.Width()).value_or(0);
    mainGaps_ = { axis_ == Axis::HORIZONTAL ? columnsGap : rowsGap };
    crossGaps_ = { axis_ == Axis::VERTICAL ? columnsGap : rowsGap };

    auto crossSize = frameSize.CrossSize(axis_);
    std::vector<double> crossLens;
    std::pair<std::vector<double>, double> cross;
    if (axis_ == Axis::VERTICAL) {
        cross = ParseTemplateArgs(
            WaterFlowLayoutUtils::PreParseArgs(columnsTemplate), crossSize, crossGaps_[0], info_->childrenCount_);
    } else {
        cross = ParseTemplateArgs(
            WaterFlowLayoutUtils::PreParseArgs(rowsTemplate), crossSize, crossGaps_[0], info_->childrenCount_);
    }
    crossLens = cross.first;
    if (crossLens.empty()) {
        crossLens.push_back(crossSize);
    }
    crossGaps_ = { cross.second };

    itemsCrossSize_ = { {} };

    if (crossLens.size() < info_->items_[0].size()) {
        auto it = info_->items_[0].find(crossLens.size());
        info_->items_[0].erase(it, info_->items_[0].end());
    }
    int32_t index = 0;
    for (const auto& len : crossLens) {
        itemsCrossSize_[0].push_back(len);
        info_->items_[0].try_emplace(index, std::map<int32_t, std::pair<float, float>>());
        ++index;
    }
    info_->margins_.resize(1);
    info_->segmentTails_ = { (info_->footerIndex_ >= 0) ? info_->childrenCount_ - 2 : info_->childrenCount_ - 1 };
}

void WaterFlowSegmentedLayout::InitFooter(float crossSize)
{
    mainGaps_.emplace_back(0.0f);
    itemsCrossSize_.emplace_back(std::vector<float> { crossSize });

    if (info_->items_.size() == 1) {
        info_->items_.emplace_back();
        info_->items_.back().try_emplace(0);
    }
    info_->margins_.emplace_back();
    info_->segmentTails_.emplace_back(info_->childrenCount_ - 1);

    if (info_->footerIndex_ != info_->childrenCount_ - 1) {
        info_->footerIndex_ = std::min(info_->footerIndex_, info_->childrenCount_ - 1);
        info_->ClearCacheAfterIndex(info_->footerIndex_ - 1);
        // re-insert at the end
        auto footer = wrapper_->GetOrCreateChildByIndex(info_->footerIndex_);
        auto waterFlow = wrapper_->GetHostNode();
        waterFlow->RemoveChildAtIndex(info_->footerIndex_);
        footer->GetHostNode()->MountToParent(waterFlow);
        footer->SetActive(false);
        info_->segmentCache_.erase(info_->footerIndex_);
        info_->footerIndex_ = info_->childrenCount_ - 1;
    }
}

void WaterFlowSegmentedLayout::MeasureOnOffset()
{
    const float prevOffset = wrapper_->GetHostNode()->GetPattern<WaterFlowPattern>()->GetPrevOffset();
    const bool forward = LessOrEqual(info_->currentOffset_, prevOffset) || info_->endIndex_ == -1;
    if (forward) {
        Fill(info_->endIndex_ + 1);
        MeasureLazyChild(info_->startIndex_, info_->endIndex_);
    }

    const int32_t oldStart = info_->startIndex_;
    info_->Sync(mainSize_, canOverScrollStart_, canOverScrollEnd_);

    if (!forward) {
        // measure appearing items when scrolling upwards
        const int32_t bound = std::min(oldStart, info_->endIndex_);
        bool heightChange = false;
        for (int32_t i = info_->startIndex_; i <= bound; ++i) {
            auto item = MeasureItem(i, { info_->itemInfos_[i].crossIdx, info_->itemInfos_[i].mainOffset },
                WaterFlowLayoutUtils::GetUserDefHeight(sections_, info_->GetSegment(i), i), false);
            CHECK_NULL_BREAK(item);
            if (!NearEqual(GetMeasuredHeight(item, axis_), info_->itemInfos_[i].mainSize)) {
                // refill from [i] if height doesn't match record
                info_->ClearCacheAfterIndex(i - 1);
                Fill(i);
                info_->Sync(mainSize_, canOverScrollStart_, canOverScrollEnd_);
                heightChange = true;
                break;
            }
        }
        if (!heightChange) {
            MeasureLazyChild(bound + 1, info_->endIndex_);
        }
    }
}

void WaterFlowSegmentedLayout::MeasureOnJump(int32_t jumpIdx)
{
    if (postJumpOffset_) { // preemptively reset layout range
        info_->startIndex_ = 0;
        info_->endIndex_ = -1;
    }
    if (info_->extraOffset_) {
        postJumpOffset_ = postJumpOffset_.value_or(0.0f) + *info_->extraOffset_;
    }
    if (jumpIdx >= info_->childrenCount_) {
        return;
    }
    if (jumpIdx == LAST_ITEM) {
        jumpIdx = info_->childrenCount_ - 1;
    }
    if (jumpIdx >= static_cast<int32_t>(info_->itemInfos_.size())) {
        // prepare items
        MeasureToTarget(jumpIdx, std::nullopt);
    }

    if (jumpIdx < 0 || jumpIdx >= static_cast<int32_t>(info_->itemInfos_.size())) {
        TAG_LOGW(AceLogTag::ACE_WATERFLOW, "jumpIdx %{public}d is out of range, itemInfos_.size() = %{public}zu",
            jumpIdx, info_->itemInfos_.size());
        return;
    }
    // solve offset
    const auto& item = info_->itemInfos_[jumpIdx];
    if (info_->align_ == ScrollAlign::AUTO) {
        info_->align_ = TransformAutoScroll(item);
    }
    info_->currentOffset_ = SolveJumpOffset(item) + postJumpOffset_.value_or(0.0f);

    Fill(jumpIdx);
    info_->Sync(mainSize_, false, false);

    // only if range [startIndex, jumpIdx) isn't measured (used user-defined size)
    if (!sections_) {
        return;
    }
    for (int32_t i = info_->startIndex_; i < jumpIdx; ++i) {
        auto seg = info_->GetSegment(i);
        MeasureItem(i, { info_->itemInfos_[i].crossIdx, info_->itemInfos_[i].mainOffset },
            WaterFlowLayoutUtils::GetUserDefHeight(sections_, seg, i), false);
    }
}

ScrollAlign WaterFlowSegmentedLayout::TransformAutoScroll(const WaterFlowLayoutInfo::ItemInfo& item) const
{
    const bool isAbove = Negative(info_->currentOffset_ + item.mainOffset);
    const bool isBelow = GreatNotEqual(info_->currentOffset_ + item.mainOffset + item.mainSize, mainSize_);
    if (isAbove && isBelow) {
        // possible when the item is larger than viewport
        return ScrollAlign::NONE;
    }
    if (isAbove) {
        return ScrollAlign::START;
    }
    if (isBelow) {
        return ScrollAlign::END;
    }
    return ScrollAlign::NONE;
}

float WaterFlowSegmentedLayout::SolveJumpOffset(const WaterFlowLayoutInfo::ItemInfo& item) const
{
    float offset = info_->currentOffset_;
    switch (info_->align_) {
        case ScrollAlign::START:
            offset = -item.mainOffset;
            break;

        case ScrollAlign::CENTER:
            offset = -(item.mainOffset + item.mainSize / 2.0f) + mainSize_ / 2.0f;
            break;

        case ScrollAlign::END:
            offset = -(item.mainOffset + item.mainSize) + mainSize_;
            break;
        default:
            break;
    }
    offset = std::min(0.0f, offset);
    return offset;
}

void WaterFlowSegmentedLayout::MeasureToTarget(int32_t targetIdx, std::optional<int64_t> cacheDeadline, bool force)
{
    targetIdx = std::min(targetIdx, info_->childrenCount_ - 1);
    for (int32_t i = static_cast<int32_t>(info_->itemInfos_.size()); i <= targetIdx; ++i) {
        int32_t seg = info_->GetSegment(i);
        auto position = WaterFlowLayoutUtils::GetItemPosition(info_, i, mainGaps_[seg]);
        float itemHeight = WaterFlowLayoutUtils::GetUserDefHeight(sections_, seg, i);
        if (force || Negative(itemHeight)) {
            auto item =
                MeasureItem(i, { position.crossIndex, position.startMainPos }, itemHeight, cacheDeadline.has_value());
            if (item) {
                itemHeight = GetMeasuredHeight(item, axis_);
            }
        }
        info_->RecordItem(i, position, itemHeight);
        if (cacheDeadline && GetSysTimestamp() > *cacheDeadline) {
            break;
        }
    }
}

void WaterFlowSegmentedLayout::Fill(int32_t startIdx)
{
    const float expandMainSize = mainSize_ + info_->expandHeight_;
    for (int32_t i = startIdx; i < info_->childrenCount_; ++i) {
        auto position = WaterFlowLayoutUtils::GetItemPosition(info_, i, mainGaps_[info_->GetSegment(i)]);
        if (GreatOrEqual(position.startMainPos + info_->currentOffset_, expandMainSize)) {
            break;
        }
        float itemHeight = WaterFlowLayoutUtils::GetUserDefHeight(sections_, info_->GetSegment(i), i);
        auto item = MeasureItem(i, { position.crossIndex, position.startMainPos }, itemHeight, false);
        if (!item) {
            continue;
        }
        if (info_->itemInfos_.size() == static_cast<size_t>(i)) {
            info_->RecordItem(i, position, GetMeasuredHeight(item, axis_));
        }
        if (info_->itemInfos_.size() < static_cast<size_t>(i)) {
            TAG_LOGW(AceLogTag::ACE_WATERFLOW, "Fill index %{public}d is out of range, itemInfos_.size() = %{public}zu",
                i, info_->itemInfos_.size());
            break;
        }
        if (!NearEqual(GetMeasuredHeight(item, axis_), info_->itemInfos_[i].mainSize)) {
            // refill from [i] if height doesn't match record
            info_->ClearCacheAfterIndex(i - 1);
            Fill(i);
            break;
        }
    }
}

RefPtr<LayoutWrapper> WaterFlowSegmentedLayout::MeasureItem(
    int32_t idx, std::pair<int32_t, float> position, float userDefMainSize, bool isCache) const
{
    auto item = wrapper_->GetOrCreateChildByIndex(idx, !isCache, isCache);
    CHECK_NULL_RETURN(item, nullptr);
    // override user-defined main size
    if (NonNegative(userDefMainSize)) {
        WaterFlowLayoutUtils::UpdateItemIdealSize(item, axis_, userDefMainSize);
    }
    auto seg = info_->GetSegment(idx);
    if (itemsCrossSize_[seg].size() > 1) {
        item->Measure(WaterFlowLayoutUtils::CreateChildConstraint(
            { itemsCrossSize_[seg][position.first], mainSize_, axis_, NonNegative(userDefMainSize) }, props_, item));
    } else {
        ViewPosReference ref {
            .viewPosStart = 0,
            .viewPosEnd = mainSize_ + info_->expandHeight_,
            .referencePos = position.second + info_->currentOffset_,
            .referenceEdge = ReferenceEdge::START,
            .axis = axis_,
        };
        item->Measure(WaterFlowLayoutUtils::CreateChildConstraint(
            { itemsCrossSize_[seg][position.first], mainSize_, axis_, NonNegative(userDefMainSize) }, ref, props_,
            item));
    }
    if (isCache) {
        item->Layout();
        item->SetActive(false);
    }
    return item;
}

void WaterFlowSegmentedLayout::PostMeasureSelf(SizeF size)
{
    mainSize_ = info_->maxHeight_;
    size.SetMainSize(mainSize_, axis_);
    AddPaddingToSize(props_->CreatePaddingAndBorder(), size);
    wrapper_->GetGeometryNode()->SetFrameSize(size);
}

void WaterFlowSegmentedLayout::LayoutItem(int32_t idx, float crossPos, const OffsetF& padding, bool isReverse)
{
    const bool isCache = IsCache(info_, idx);
    const auto& item = info_->itemInfos_[idx];
    auto mainOffset = item.mainOffset + info_->currentOffset_;
    if (isReverse) {
        mainOffset = mainSize_ - item.mainSize - mainOffset;
    }

    OffsetF offset = (axis_ == Axis::VERTICAL) ? OffsetF(crossPos, mainOffset) : OffsetF(mainOffset, crossPos);
    auto wrapper = wrapper_->GetChildByIndex(idx, isCache);
    CHECK_NULL_VOID(wrapper);
    wrapper->GetGeometryNode()->SetMarginFrameOffset(offset + padding);
    if (CheckNeedLayout(wrapper, isCache)) {
        wrapper->Layout();
    } else {
        wrapper->GetHostNode()->ForceSyncGeometryNode();
    }

    // recode restore info
    if (idx == info_->startIndex_) {
        info_->storedOffset_ = mainOffset;
    }
}

bool WaterFlowSegmentedLayout::PreloadItem(LayoutWrapper* host, int32_t itemIdx, int64_t deadline)
{
    InitEnv(host);
    if (itemIdx < static_cast<int32_t>(info_->itemInfos_.size())) {
        return host->GetOrCreateChildByIndex(itemIdx, false, true);
    }
    MeasureToTarget(itemIdx, deadline, true);
    return true;
}

void WaterFlowSegmentedLayout::SyncPreloadItem(LayoutWrapper* host, int32_t itemIdx)
{
    if (itemIdx >= static_cast<int32_t>(info_->itemInfos_.size())) {
        MeasureToTarget(itemIdx, std::nullopt, true);
    } else {
        int32_t seg = info_->GetSegment(itemIdx);
        MeasureItem(itemIdx, { info_->itemInfos_[itemIdx].crossIdx, info_->itemInfos_[itemIdx].mainOffset },
            WaterFlowLayoutUtils::GetUserDefHeight(sections_, seg, itemIdx), false);
    }
}

void WaterFlowSegmentedLayout::MeasureLazyChild(int32_t startIdx, int32_t endIdx) const
{
    for (int32_t idx = startIdx; idx <= endIdx; idx++) {
        auto item = wrapper_->GetChildByIndex(idx);
        auto itemLayoutProperty = item->GetLayoutProperty();
        if (itemLayoutProperty->GetNeedLazyLayout()) {
            int32_t seg = info_->GetSegment(idx);
            MeasureItem(idx, { info_->itemInfos_[idx].crossIdx, info_->itemInfos_[idx].mainOffset },
                WaterFlowLayoutUtils::GetUserDefHeight(sections_, seg, idx), false);
        }
    }
}
} // namespace OHOS::Ace::NG
