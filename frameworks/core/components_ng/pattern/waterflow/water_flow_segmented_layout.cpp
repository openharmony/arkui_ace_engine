/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/waterflow/water_flow_segmented_layout.h"

#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "base/utils/utils.h"
#include "core/components/scroll/scroll_controller_base.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/waterflow/water_flow_layout_info.h"
#include "core/components_ng/pattern/waterflow/water_flow_layout_property.h"
#include "core/components_ng/pattern/waterflow/water_flow_layout_utils.h"
#include "core/components_ng/pattern/waterflow/water_flow_pattern.h"
#include "core/components_ng/pattern/waterflow/water_flow_sections.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/components_ng/property/templates_parser.h"

namespace OHOS::Ace::NG {
namespace {
bool IsDataValid(const WaterFlowLayoutInfo& info)
{
    if (info.segmentTails_.empty()) {
        return false;
    }
    if (info.childrenCount_ - 1 != info.segmentTails_.back()) {
        TAG_LOGW(AceLogTag::ACE_WATERFLOW,
            "Children count = %{public}d and doesn't match the number provided in Sections, which is %{public}d.",
            info.childrenCount_, info.segmentTails_.back() + 1);
        return false;
    }
    return true;
}
} // namespace

void WaterFlowSegmentedLayout::Measure(LayoutWrapper* wrapper)
{
    wrapper_ = wrapper;
    auto props = DynamicCast<WaterFlowLayoutProperty>(wrapper->GetLayoutProperty());
    info_.axis_ = axis_ = props->GetAxis();
    auto [idealSize, matchChildren] = PreMeasureSelf();

    Init(idealSize);
    if (!IsDataValid(info_)) {
        return;
    }

    mainSize_ = GetMainAxisSize(idealSize, axis_);

    if (info_.jumpIndex_ != EMPTY_JUMP_INDEX) {
        MeasureOnJump(info_.jumpIndex_);
        info_.jumpIndex_ = EMPTY_JUMP_INDEX;
    } else if (info_.targetIndex_) {
        MeasureToTarget(*info_.targetIndex_);
        info_.targetIndex_.reset();
    } else {
        MeasureOnOffset();
    }

    if (matchChildren) {
        PostMeasureSelf(idealSize);
    }
    info_.lastMainSize_ = mainSize_;

    wrapper_->SetCacheCount(props->GetCachedCountValue(1));
}

void WaterFlowSegmentedLayout::Layout(LayoutWrapper* wrapper)
{
    if (!IsDataValid(info_)) {
        return;
    }

    wrapper_ = wrapper;

    auto padding = wrapper_->GetLayoutProperty()->CreatePaddingAndBorder();
    auto initialOffset = OffsetF(padding.left.value_or(0.0f), padding.top.value_or(0.0f));
    auto props = DynamicCast<WaterFlowLayoutProperty>(wrapper_->GetLayoutProperty());

    size_t segmentCnt = itemsCrossSize_.size();
    std::vector<std::vector<float>> crossPos(segmentCnt);
    auto crossSize = wrapper_->GetGeometryNode()->GetFrameSize().CrossSize(axis_);
    auto layoutDirection = wrapper_->GetLayoutProperty()->GetNonAutoLayoutDirection();
    auto isRtl = layoutDirection == TextDirection::RTL && axis_ == Axis::VERTICAL;
    // prepare crossPos
    for (size_t i = 0; i < segmentCnt; ++i) {
        float pos = ((axis_ == Axis::VERTICAL) ? info_.margins_[i].left : info_.margins_[i].top).value_or(0.0f);
        for (const auto& len : itemsCrossSize_[i]) {
            crossPos[i].push_back(!isRtl ? pos : crossSize - pos - len);
            pos += len + crossGaps_[i];
        }
    }

    bool isReverse = props->IsReverse();
    for (int32_t i = info_.startIndex_; i <= info_.endIndex_; ++i) {
        LayoutItem(i, crossPos[info_.GetSegment(i)][info_.itemInfos_[i].crossIdx], initialOffset, isReverse);
    }
    wrapper_->SetActiveChildRange(info_.startIndex_, info_.endIndex_);

    // for compatibility
    info_.firstIndex_ = info_.startIndex_;
}

namespace {
/**
 * @brief Prepares a jump to the current StartItem.
 *
 * @param info WaterFlowLayoutInfo
 * @return current StartItem's offset relative to the viewport.
 */
float PrepareJump(WaterFlowLayoutInfo& info)
{
    if (info.endIndex_ == -1) {
        // implies that LayoutInfo has already been reset, no need to jump
        return 0.0f;
    }
    info.jumpIndex_ = info.startIndex_;
    info.align_ = ScrollAlign::START;
    float itemOffset = (info.itemInfos_.size() <= static_cast<size_t>(info.startIndex_))
                           ? info.storedOffset_
                           : info.currentOffset_ + info.itemInfos_[info.startIndex_].mainOffset;

    info.startIndex_ = 0;
    info.endIndex_ = -1;
    info.currentOffset_ = 0.0f;

    return itemOffset;
}
} // namespace

void WaterFlowSegmentedLayout::Init(const SizeF& frameSize)
{
    info_.childrenCount_ = wrapper_->GetTotalChildCount();
    sections_ = wrapper_->GetHostNode()->GetPattern<WaterFlowPattern>()->GetSections();
    if (sections_) {
        const auto& sections = sections_->GetSectionInfo();
        if (info_.margins_.empty()) {
            // empty margins_ implies a segment change
            auto constraint = wrapper_->GetLayoutProperty()->GetLayoutConstraint();
            postJumpOffset_ = PrepareJump(info_);
            info_.InitMargins(sections, constraint->scaleProperty, constraint->percentReference.Width());
        }
        SegmentInit(sections, frameSize);
        if (info_.segmentTails_.empty()) {
            info_.InitSegments(sections, 0);
        }
    } else {
        RegularInit(frameSize);
        if (info_.footerIndex_ >= 0) {
            InitFooter(frameSize.CrossSize(axis_));
        }
    }

    int32_t updateIdx = wrapper_->GetHostNode()->GetChildrenUpdated();
    if (updateIdx != -1) {
        if (updateIdx <= info_.endIndex_) {
            postJumpOffset_ = PrepareJump(info_);
        }
        info_.ClearCacheAfterIndex(updateIdx - 1);
        wrapper_->GetHostNode()->ChildrenUpdatedFrom(-1);
    }
    if (!wrapper_->IsContraintNoChanged()) {
        postJumpOffset_ = PrepareJump(info_);
    }
}

void WaterFlowSegmentedLayout::SegmentInit(
    const std::vector<WaterFlowSections::Section>& options, const SizeF& frameSize)
{
    auto props = DynamicCast<WaterFlowLayoutProperty>(wrapper_->GetLayoutProperty());
    auto scale = props->GetLayoutConstraint()->scaleProperty;
    size_t n = options.size();
    crossGaps_.resize(n);
    mainGaps_.resize(n);
    itemsCrossSize_.resize(n);
    for (size_t i = 0; i < n; ++i) {
        auto rowGap = options[i].rowsGap.value_or(props->GetRowsGap().value_or(0.0_vp));
        auto columnGap = options[i].columnsGap.value_or(props->GetColumnsGap().value_or(0.0_vp));
        mainGaps_[i] = ConvertToPx(rowGap, scale, frameSize.Height()).value_or(0.0f);
        crossGaps_[i] = ConvertToPx(columnGap, scale, frameSize.Width()).value_or(0.0f);
        if (axis_ == Axis::HORIZONTAL) {
            std::swap(crossGaps_[i], mainGaps_[i]);
        }

        const auto& margin = info_.margins_[i];
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
    auto props = DynamicCast<WaterFlowLayoutProperty>(wrapper_->GetLayoutProperty());
    auto rowsTemplate = props->GetRowsTemplate().value_or("1fr");
    auto columnsTemplate = props->GetColumnsTemplate().value_or("1fr");
    auto scale = props->GetLayoutConstraint()->scaleProperty;
    auto rowsGap = ConvertToPx(props->GetRowsGap().value_or(0.0_vp), scale, frameSize.Height()).value_or(0);
    auto columnsGap = ConvertToPx(props->GetColumnsGap().value_or(0.0_vp), scale, frameSize.Width()).value_or(0);
    mainGaps_ = { axis_ == Axis::HORIZONTAL ? columnsGap : rowsGap };
    crossGaps_ = { axis_ == Axis::VERTICAL ? columnsGap : rowsGap };

    auto crossSize = frameSize.CrossSize(axis_);
    std::vector<double> crossLens;
    std::pair<std::vector<double>, bool> cross;
    if (axis_ == Axis::VERTICAL) {
        cross = ParseTemplateArgs(
            WaterFlowLayoutUtils::PreParseArgs(columnsTemplate), crossSize, crossGaps_[0], info_.childrenCount_);
    } else {
        cross = ParseTemplateArgs(
            WaterFlowLayoutUtils::PreParseArgs(rowsTemplate), crossSize, crossGaps_[0], info_.childrenCount_);
    }
    crossLens = cross.first;
    if (crossLens.empty()) {
        crossLens.push_back(crossSize);
    }
    if (cross.second) {
        crossGaps_ = { 0 };
    }

    itemsCrossSize_ = { {} };

    if (crossLens.size() < info_.items_[0].size()) {
        auto it = info_.items_[0].find(crossLens.size());
        info_.items_[0].erase(it, info_.items_[0].end());
    }
    int32_t index = 0;
    for (const auto& len : crossLens) {
        itemsCrossSize_[0].push_back(len);
        info_.items_[0].try_emplace(index, std::map<int32_t, std::pair<float, float>>());
        ++index;
    }
    info_.margins_.resize(1);
    info_.segmentTails_ = { (info_.footerIndex_ >= 0) ? info_.childrenCount_ - 2 : info_.childrenCount_ - 1 };
}

void WaterFlowSegmentedLayout::InitFooter(float crossSize)
{
    mainGaps_.emplace_back(0.0f);
    itemsCrossSize_.emplace_back(std::vector<float> { crossSize });

    if (info_.items_.size() == 1) {
        info_.items_.emplace_back();
        info_.items_.back().try_emplace(0);
    }
    info_.margins_.emplace_back();
    info_.segmentTails_.emplace_back(info_.childrenCount_ - 1);

    if (info_.footerIndex_ != info_.childrenCount_ - 1) {
        info_.footerIndex_ = std::min(info_.footerIndex_, info_.childrenCount_ - 1);
        info_.ClearCacheAfterIndex(info_.footerIndex_ - 1);
        // re-insert at the end
        auto footer = wrapper_->GetOrCreateChildByIndex(info_.footerIndex_);
        auto waterFlow = wrapper_->GetHostNode();
        waterFlow->RemoveChildAtIndex(info_.footerIndex_);
        footer->GetHostNode()->MountToParent(waterFlow);
        footer->SetActive(false);
        info_.segmentCache_.erase(info_.footerIndex_);
        info_.footerIndex_ = info_.childrenCount_ - 1;
    }
}

namespace {
float GetUserDefHeight(const RefPtr<WaterFlowSections>& sections, int32_t seg, int32_t idx)
{
    CHECK_NULL_RETURN(sections, -1.0f);
    const auto& section = sections->GetSectionInfo()[seg];
    if (section.onGetItemMainSizeByIndex) {
        Dimension len(section.onGetItemMainSizeByIndex(idx), DimensionUnit::VP);
        if (len.IsNegative()) {
            return 0.0f;
        }
        return len.ConvertToPx();
    }
    return -1.0f;
}
} // namespace

void WaterFlowSegmentedLayout::MeasureOnOffset()
{
    bool forward = LessOrEqual(info_.currentOffset_ - info_.prevOffset_, 0.0f) || info_.endIndex_ == -1;
    if (forward) {
        Fill(info_.endIndex_ + 1);
    }

    int32_t oldStart = info_.startIndex_;
    info_.Sync(mainSize_, overScroll_);

    if (!forward) {
        // measure appearing items when scrolling upwards
        auto props = DynamicCast<WaterFlowLayoutProperty>(wrapper_->GetLayoutProperty());
        for (int32_t i = info_.startIndex_; i < oldStart; ++i) {
            MeasureItem(props, i, info_.itemInfos_[i].crossIdx, GetUserDefHeight(sections_, info_.GetSegment(i), i));
        }
    }
}

void WaterFlowSegmentedLayout::MeasureOnJump(int32_t jumpIdx)
{
    if (jumpIdx >= info_.childrenCount_) {
        return;
    }
    if (jumpIdx == LAST_ITEM) {
        jumpIdx = info_.childrenCount_ - 1;
    }
    if (static_cast<size_t>(jumpIdx) >= info_.itemInfos_.size()) {
        // prepare items
        MeasureToTarget(jumpIdx);
    }
    // solve offset
    const auto& item = info_.itemInfos_[jumpIdx];
    if (info_.align_ == ScrollAlign::AUTO) {
        info_.align_ = TransformAutoScroll(item);
    }
    info_.currentOffset_ = SolveJumpOffset(item) + postJumpOffset_;

    Fill(jumpIdx);
    info_.Sync(mainSize_, false);

    // only if range [startIndex, jumpIdx) isn't measured (used user-defined size)
    if (!sections_) {
        return;
    }
    auto props = DynamicCast<WaterFlowLayoutProperty>(wrapper_->GetLayoutProperty());
    for (int32_t i = info_.startIndex_; i < jumpIdx; ++i) {
        auto seg = info_.GetSegment(i);
        if (sections_->GetSectionInfo()[seg].onGetItemMainSizeByIndex) {
            MeasureItem(props, i, info_.itemInfos_[i].crossIdx, GetUserDefHeight(sections_, seg, i));
        }
    }
}

ScrollAlign WaterFlowSegmentedLayout::TransformAutoScroll(const WaterFlowLayoutInfo::ItemInfo& item) const
{
    bool isAbove = LessNotEqual(info_.currentOffset_ + item.mainOffset, 0.0f);
    bool isBelow = GreatNotEqual(info_.currentOffset_ + item.mainOffset + item.mainSize, mainSize_);
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
    float offset = info_.currentOffset_;
    switch (info_.align_) {
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

void WaterFlowSegmentedLayout::MeasureToTarget(int32_t targetIdx)
{
    auto props = DynamicCast<WaterFlowLayoutProperty>(wrapper_->GetLayoutProperty());
    targetIdx = std::min(targetIdx, info_.childrenCount_ - 1);
    for (int32_t i = info_.itemInfos_.size(); i <= targetIdx; ++i) {
        int32_t seg = info_.GetSegment(i);
        auto position = WaterFlowLayoutUtils::GetItemPosition(info_, i, mainGaps_[seg]);
        float itemHeight = GetUserDefHeight(sections_, seg, i);
        if (itemHeight < 0.0f) {
            auto item = MeasureItem(props, i, position.crossIndex, -1.0f);
            if (item) {
                itemHeight = GetMainAxisSize(item->GetGeometryNode()->GetMarginFrameSize(), axis_);
            }
        }
        info_.RecordItem(i, position, itemHeight);
    }
}

void WaterFlowSegmentedLayout::Fill(int32_t startIdx)
{
    auto props = DynamicCast<WaterFlowLayoutProperty>(wrapper_->GetLayoutProperty());
    for (int32_t i = startIdx; i < info_.childrenCount_; ++i) {
        auto position = WaterFlowLayoutUtils::GetItemPosition(info_, i, mainGaps_[info_.GetSegment(i)]);
        if (GreatOrEqual(position.startMainPos + info_.currentOffset_, mainSize_)) {
            break;
        }
        float itemHeight = GetUserDefHeight(sections_, info_.GetSegment(i), i);
        auto item = MeasureItem(props, i, position.crossIndex, itemHeight);
        if (!item) {
            continue;
        }
        if (info_.itemInfos_.size() <= static_cast<size_t>(i)) {
            info_.RecordItem(i, position, GetMainAxisSize(item->GetGeometryNode()->GetMarginFrameSize(), axis_));
        }
    }
}

RefPtr<LayoutWrapper> WaterFlowSegmentedLayout::MeasureItem(
    const RefPtr<WaterFlowLayoutProperty>& props, int32_t idx, int32_t crossIdx, float userDefMainSize) const
{
    auto item = wrapper_->GetOrCreateChildByIndex(idx);
    CHECK_NULL_RETURN(item, nullptr);
    // override user-defined main size
    if (userDefMainSize >= 0.0f) {
        auto props = item->GetLayoutProperty();
        // get previously user defined ideal width
        std::optional<CalcLength> crossSize;
        const auto& layoutConstraint = props->GetCalcLayoutConstraint();
        if (layoutConstraint && layoutConstraint->selfIdealSize) {
            crossSize = axis_ == Axis::VERTICAL ? layoutConstraint->selfIdealSize->Width()
                                                : layoutConstraint->selfIdealSize->Height();
        }
        props->UpdateUserDefinedIdealSize(axis_ == Axis::VERTICAL ? CalcSize(crossSize, CalcLength(userDefMainSize))
                                                                  : CalcSize(CalcLength(userDefMainSize), crossSize));
    }
    item->Measure(WaterFlowLayoutUtils::CreateChildConstraint(
        { itemsCrossSize_[info_.GetSegment(idx)][crossIdx], mainSize_, axis_ }, props, item));
    return item;
}

std::pair<SizeF, bool> WaterFlowSegmentedLayout::PreMeasureSelf()
{
    auto props = wrapper_->GetLayoutProperty();
    auto size = CreateIdealSize(props->GetLayoutConstraint().value(), axis_, props->GetMeasureType(), true);
    auto matchChildren = GreaterOrEqualToInfinity(GetMainAxisSize(size, axis_));
    if (!matchChildren) {
        wrapper_->GetGeometryNode()->SetFrameSize(size);
    }
    MinusPaddingToSize(props->CreatePaddingAndBorder(), size);
    wrapper_->GetGeometryNode()->SetContentSize(size);
    return { size, matchChildren };
}

void WaterFlowSegmentedLayout::PostMeasureSelf(SizeF size)
{
    mainSize_ = info_.maxHeight_;
    size.SetMainSize(mainSize_, axis_);
    auto props = wrapper_->GetLayoutProperty();
    AddPaddingToSize(props->CreatePaddingAndBorder(), size);
    wrapper_->GetGeometryNode()->SetFrameSize(size);
}

void WaterFlowSegmentedLayout::LayoutItem(int32_t idx, float crossPos, const OffsetF& padding, bool isReverse)
{
    const auto& item = info_.itemInfos_[idx];
    auto mainOffset = item.mainOffset + info_.currentOffset_;
    if (isReverse) {
        mainOffset = mainSize_ - item.mainSize - mainOffset;
    }

    OffsetF offset = (axis_ == Axis::VERTICAL) ? OffsetF(crossPos, mainOffset) : OffsetF(mainOffset, crossPos);
    auto wrapper = wrapper_->GetOrCreateChildByIndex(idx);
    CHECK_NULL_VOID(wrapper);
    wrapper->GetGeometryNode()->SetMarginFrameOffset(offset + padding);
    if (wrapper->CheckNeedForceMeasureAndLayout()) {
        wrapper->Layout();
    } else {
        wrapper->GetHostNode()->ForceSyncGeometryNode();
    }

    // recode restore info
    if (idx == info_.startIndex_) {
        info_.storedOffset_ = mainOffset;
    }
}
} // namespace OHOS::Ace::NG
