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

#include "core/components_ng/pattern/arc_list/arc_list_layout_algorithm.h"

#include <algorithm>
#include <unordered_set>
#include <utility>

#include "base/geometry/axis.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/log/ace_trace.h"
#include "base/memory/ace_type.h"
#include "base/utils/time_util.h"
#include "base/utils/utils.h"
#include "core/components/common/layout/layout_param.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/arc_list/arc_list_item_pattern.h"
#include "core/components_ng/pattern/arc_list/arc_list_pattern.h"
#include "core/components_ng/pattern/list/list_layout_property.h"
#include "core/components_ng/pattern/scrollable/scrollable_utils.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/components_ng/property/property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/components_v2/list/list_properties.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
static constexpr float ARC_LIST_MAIN_POS_OFFSET = 200.f;
static constexpr Dimension ARC_LIST_ITEM_SNAP_SIZE = 145.0_vp;
static constexpr float FLOAT_TWO = 2.0f;
static constexpr float HEADER_DIST = 40.f;
static constexpr float TRANSPARENCY_DIST = 40.f;
static constexpr double SCALE_FACTOR_A = 108;
static constexpr double SCALE_FACTOR_B = -0.012414818053443355;
static constexpr double SCALE_FACTOR_C = -0.0015925017083441295;
static constexpr double SCALE_FACTOR_D = 3.0809306290456454E-06;
static constexpr double SCALE_FACTOR_E = 100.0;
} // namespace

float ArcListLayoutAlgorithm::GetNearScale(float pos)
{
    float offset = fabs(pos);
    float ratio = static_cast<float>((SCALE_FACTOR_A +
                                    SCALE_FACTOR_B * offset +
                                    SCALE_FACTOR_C * pow(offset, 2) + // 2:平方
                                    SCALE_FACTOR_D * pow(offset, 3)) / SCALE_FACTOR_E); // 3:3次方
    return ratio;
}

void ArcListLayoutAlgorithm::MeasureList(LayoutWrapper* layoutWrapper)
{
    int32_t startIndex = 0;
    int32_t endIndex = 0;
    int32_t midIndex = 0;
    float midItemMidPos = contentMainSize_ / FLOAT_TWO;
    float startPos = headerMainSize_;
    float endPos = 0.0f;
    float itemTotalSize = 0.0f;

    if (jumpIndex_) {
        if (!CheckJumpValid(layoutWrapper)) {
            jumpIndex_.reset();
        } else {
            if (jumpIndex_) {
                ClearAllItemPosition(layoutWrapper);
            }
        }
    }
    if (targetIndex_) {
        if (targetIndex_.value() == LAST_ITEM) {
            targetIndex_ = totalItemCount_ - 1;
        } else if ((targetIndex_.value() < 0) || (targetIndex_.value() >= totalItemCount_)) {
            targetIndex_.reset();
        }
        targetIndexStaged_ = targetIndex_;
    }
    if (!itemPosition_.empty()) {
        startPos = itemPosition_.begin()->second.startPos;
        endPos = itemPosition_.rbegin()->second.endPos;
        itemTotalSize = GetEndPosition() - GetStartPosition();
        startIndex = std::min(GetStartIndex(), totalItemCount_ - 1);
        endIndex = std::min(GetEndIndex(), totalItemCount_ - 1);
        if (GetStartIndex() > totalItemCount_ - 1 && !jumpIndex_.has_value()) {
            jumpIndex_ = totalItemCount_ - 1;
        }
        UpdateSnapCenterContentOffset(layoutWrapper);
        midIndex = GetMidIndex(layoutWrapper, true);
        midItemMidPos = (itemPosition_[midIndex].startPos + itemPosition_[midIndex].endPos) / FLOAT_TWO -
                        prevContentMainSize_ / FLOAT_TWO + contentMainSize_ / FLOAT_TWO;
        midIndex = std::min(midIndex, totalItemCount_ - 1);
        OffScreenLayoutDirection(layoutWrapper);

        itemPosition_.clear();
    }
    if (jumpIndex_) {
        HandleJumpCenter(layoutWrapper);
        needEstimateOffset_ = true;
    } else if (targetIndex_.has_value()) {
        if (LessOrEqual(startIndex, targetIndex_.value())) {
            LayoutForward(layoutWrapper, startIndex, startPos);
            if (GetStartIndex() > 0 && GreatNotEqual(GetStartPosition(), startMainPos_)) {
                LayoutBackward(layoutWrapper, GetStartIndex() - 1, GetStartPosition());
            }
        } else if (GreatNotEqual(startIndex, targetIndex_.value())) {
            LayoutBackward(layoutWrapper, endIndex, endPos);
            if (GetEndIndex() < (totalItemCount_ - 1) && LessNotEqual(GetEndPosition(), endMainPos_)) {
                LayoutForward(layoutWrapper, GetEndIndex() + 1, GetEndPosition());
            }
        }
    } else {
        bool overScrollTop = startIndex == 0 && GreatNotEqual(startPos, contentStartOffset_);
        float midItemHeight = 0.0f;
        midItemHeight =
            childrenSize_ ? GetChildHeight(layoutWrapper, midIndex) : MeasureAndGetChildHeight(layoutWrapper, midIndex);
        startIndex = midIndex;
        endIndex = midIndex;
        if (NearZero(currentOffset_) || (!overScrollFeature_ && NonNegative(currentOffset_)) ||
            (overScrollFeature_ && overScrollTop) ||
            LessOrEqual(itemTotalSize, contentMainSize_ - contentStartOffset_ - contentEndOffset_)) {
            startPos = midItemMidPos - midItemHeight / FLOAT_TWO;
            if (childrenSize_) {
                posMap_->OptimizeBeforeMeasure(startIndex, startPos, currentOffset_, contentMainSize_);
            }
            LayoutForward(layoutWrapper, startIndex, startPos);
            if (GetStartIndex() > 0 && GreatNotEqual(GetStartPosition(), startMainPos_)) {
                LayoutBackward(layoutWrapper, GetStartIndex() - 1, GetStartPosition());
            }
        } else {
            endPos = midItemMidPos + midItemHeight / FLOAT_TWO;
            if (childrenSize_) {
                posMap_->OptimizeBeforeMeasure(endIndex, endPos, currentOffset_, contentMainSize_);
            }
            LayoutBackward(layoutWrapper, endIndex, endPos);
            if (GetEndIndex() < (totalItemCount_ - 1) && LessNotEqual(GetEndPosition(), endMainPos_)) {
                LayoutForward(layoutWrapper, GetEndIndex() + 1, GetEndPosition());
            }
        }
    }
}

int32_t ArcListLayoutAlgorithm::LayoutALineForward(
    LayoutWrapper* layoutWrapper, int32_t& currentIndex, float startPos, float& endPos)
{
    if (currentIndex + 1 >= totalItemCount_) {
        return 0;
    }

    auto wrapper = GetListItem(layoutWrapper, currentIndex + 1);
    CHECK_NULL_RETURN(wrapper, 0);
    int32_t id = wrapper->GetHostNode()->GetId();
    ++currentIndex;
    ACE_SCOPED_TRACE("ArcListLayoutAlgorithm::MeasureListItem:%d, %f", currentIndex, startPos);

    wrapper->Measure(childLayoutConstraint_);

    float mainLen = childrenSize_ ? childrenSize_->GetChildSize(currentIndex)
                                  : GetMainAxisSize(wrapper->GetGeometryNode()->GetMarginFrameSize(), axis_);

    endPos = startPos + mainLen;
    itemPosition_[currentIndex] = { id, startPos, endPos };

    OnItemPositionAddOrUpdate(layoutWrapper, currentIndex);
    return 1;
}

int32_t ArcListLayoutAlgorithm::LayoutALineBackward(
    LayoutWrapper* layoutWrapper, int32_t& currentIndex, float endPos, float& startPos)
{
    if (currentIndex - 1 < 0) {
        return 0;
    }

    auto wrapper = GetListItem(layoutWrapper, currentIndex - 1);
    CHECK_NULL_RETURN(wrapper, 0);
    int32_t id = wrapper->GetHostNode()->GetId();
    --currentIndex;
    ACE_SCOPED_TRACE("ArcListLayoutAlgorithm::MeasureListItem:%d, %f", currentIndex, endPos);

    wrapper->Measure(childLayoutConstraint_);

    float mainLen = childrenSize_ ? childrenSize_->GetChildSize(currentIndex)
                                  : GetMainAxisSize(wrapper->GetGeometryNode()->GetMarginFrameSize(), axis_);

    startPos = endPos - mainLen;
    itemPosition_[currentIndex] = { id, startPos, endPos };

    OnItemPositionAddOrUpdate(layoutWrapper, currentIndex);
    return 1;
}

float ArcListLayoutAlgorithm::CalculateLaneCrossOffset(float crossSize, float childCrossSize, bool isGroup)
{
    float delta = 0.0;
    if (isGroup == false) {
        delta = crossSize - childCrossSize;
    }
    if (LessOrEqual(delta, 0)) {
        return 0.0f;
    }
    return delta / FLOAT_TWO;
}

void ArcListLayoutAlgorithm::FixPredictSnapOffset(const RefPtr<ListLayoutProperty>& listLayoutProperty)
{
    if (!predictSnapOffset_.has_value()) {
        return;
    }
    auto predictEndPos = totalOffset_ - predictSnapOffset_.value();
    int32_t endIndex = FindPredictSnapEndIndexInItemPositions(predictEndPos, ScrollSnapAlign::CENTER);
    if (endIndex != -1) {
        predictEndPos = CalculatePredictSnapEndPositionByIndex(endIndex, predictEndPos);
        predictSnapOffset_ = totalOffset_ - predictEndPos + currentOffset_;
        predictSnapEndPos_.reset();
    } else {
        if (IsUniformHeightProbably()) {
            FixPredictSnapOffsetAlignCenter();
        } else {
            predictSnapEndPos_ = predictEndPos;
        }
    }

    return;
}

void ArcListLayoutAlgorithm::FixPredictSnapOffsetAlignCenter()
{
    if (itemPosition_.empty()) {
        return;
    }

    auto predictEndPos = totalOffset_ - predictSnapOffset_.value();
    auto itemHeight = itemPosition_.begin()->second.endPos - itemPosition_.begin()->second.startPos + spaceWidth_;
    float snapSize = LessOrEqual(itemHeight, GetItemSnapSize() + spaceWidth_)
                         ? itemHeight
                         : GetItemSnapSize() + spaceWidth_;
    if (LessNotEqual(predictEndPos, snapSize / FLOAT_TWO - contentMainSize_ / FLOAT_TWO - spaceWidth_ / FLOAT_TWO)) {
        if (isSpringEffect_) {
            return;
        }
        predictEndPos = snapSize / FLOAT_TWO - contentMainSize_ / FLOAT_TWO - spaceWidth_ / FLOAT_TWO;
    } else if (GreatNotEqual(
        predictEndPos + contentMainSize_ / FLOAT_TWO, itemHeight * totalItemCount_ - snapSize / FLOAT_TWO)) {
        if (isSpringEffect_) {
            return;
        }
        predictEndPos = itemHeight * totalItemCount_ - snapSize / FLOAT_TWO - contentMainSize_ / FLOAT_TWO -
                        spaceWidth_ / FLOAT_TWO;
    } else {
        int32_t index;
        for (index = 0; index <= GetMaxListItemIndex(); index++) {
            if (std::abs(predictEndPos + contentMainSize_ / FLOAT_TWO - index * itemHeight - itemHeight / FLOAT_TWO) <
                itemHeight / FLOAT_TWO) {
                break;
            }
        }
        float snapLow =
            index * itemHeight + snapSize / FLOAT_TWO - contentMainSize_ / FLOAT_TWO - spaceWidth_ / FLOAT_TWO;
        float snapHigh =
            (index + 1) * itemHeight - snapSize / FLOAT_TWO - contentMainSize_ / FLOAT_TWO - spaceWidth_ / FLOAT_TWO;
        predictEndPos = LessNotEqual(predictEndPos, snapLow) ? snapLow : predictEndPos;
        predictEndPos = LessNotEqual(snapHigh, predictEndPos) ? snapHigh : predictEndPos;
        if (LessNotEqual(predictEndPos, snapSize / FLOAT_TWO - contentMainSize_ / FLOAT_TWO)) {
            predictEndPos = snapSize / FLOAT_TWO - contentMainSize_ / FLOAT_TWO - spaceWidth_ / FLOAT_TWO;
        } else if (GreatNotEqual(predictEndPos + contentMainSize_ / FLOAT_TWO,
            itemHeight * totalItemCount_ - snapSize / FLOAT_TWO)) {
            predictEndPos = itemHeight * totalItemCount_ - snapSize / FLOAT_TWO - contentMainSize_ / FLOAT_TWO -
                            spaceWidth_ / FLOAT_TWO;
        }
    }

    predictSnapOffset_ = totalOffset_ - predictEndPos;
    predictSnapEndPos_ = predictEndPos;
}

float ArcListLayoutAlgorithm::InitItemOffset(LayoutWrapper* layoutWrapper)
{
    float midOffsetScale = 0.0f;
    int32_t midIndex = GetMidIndex(layoutWrapper, true);
    auto centerPos = contentMainSize_ / FLOAT_TWO;
    for (auto& pos : itemPosition_) {
        auto wrapper = GetListItem(layoutWrapper, pos.first);
        if (wrapper == nullptr) {
            continue;
        }

        auto autoScale = true;
        auto listItemLayoutProperty = AceType::DynamicCast<ArcListItemLayoutProperty>(wrapper->GetLayoutProperty());
        if (listItemLayoutProperty != nullptr) {
            autoScale = listItemLayoutProperty->GetAutoScale().value_or(true);
        }

        pos.second.scale = 1.0f;
        pos.second.offsetY = 0.0f;
        if (!autoScale) {
            continue;
        }

        auto distance = (pos.second.startPos + pos.second.endPos) / FLOAT_TWO - centerPos;
        pos.second.scale = GetNearScale(distance);
        pos.second.offsetY = (pos.second.endPos - pos.second.startPos) * (pos.second.scale - 1);
        if (midIndex != pos.first) {
            continue;
        }

        auto centerToStart = centerPos - pos.second.startPos;
        if (GreatNotEqual(centerToStart, 0)) {
            midOffsetScale = centerToStart / (pos.second.endPos - pos.second.startPos);
            midOffsetScale = GreatOrEqual(midOffsetScale, 1) ? 1 : midOffsetScale;
        }
    }
    return midOffsetScale;
}

void ArcListLayoutAlgorithm::GenerateItemOffset(LayoutWrapper* layoutWrapper)
{
    float midOffsetScale = InitItemOffset(layoutWrapper);

    int32_t midIndex = GetMidIndex(layoutWrapper, true);

    auto iter = itemPosition_.find(midIndex);
    if (iter != itemPosition_.end()) {
        auto offset = iter->second.offsetY * (1 - midOffsetScale);
        for (++iter; iter != itemPosition_.end(); ++iter) {
            offset += iter->second.offsetY;
            iter->second.offsetY = offset - iter->second.offsetY / FLOAT_TWO;
        }
    }

    auto riter = itemPosition_.rbegin();
    while (riter != itemPosition_.rend() && riter->first != midIndex) {
        ++riter;
    }
    if (riter != itemPosition_.rend()) {
        auto offset = riter->second.offsetY * midOffsetScale;
        riter->second.offsetY *= 1 / FLOAT_TWO - midOffsetScale;
        for (++riter; riter != itemPosition_.rend(); ++riter) {
            offset += riter->second.offsetY;
            riter->second.offsetY = -(offset - riter->second.offsetY / FLOAT_TWO);
        }
    }
}

float ArcListLayoutAlgorithm::CalculatePredictSnapEndPositionByIndex(uint32_t index, float prevPredictEndPos)
{
    float predictSnapEndPos = prevPredictEndPos;
    float predictPos = prevPredictEndPos + contentMainSize_ / FLOAT_TWO - totalOffset_;
    float itemHeight = itemPosition_[index].endPos - itemPosition_[index].startPos;
    float snapSize = LessOrEqual(itemHeight, GetItemSnapSize()) ? itemHeight : GetItemSnapSize();
    float snapLow = itemPosition_[index].startPos + snapSize / FLOAT_TWO;
    float snapHigh = itemPosition_[index].endPos - snapSize / FLOAT_TWO;
    predictPos = LessNotEqual(predictPos, snapLow) ? snapLow : predictPos;
    predictPos = LessNotEqual(snapHigh, predictPos) ? snapHigh : predictPos;
    predictSnapEndPos = totalOffset_ + predictPos - contentMainSize_ / FLOAT_TWO;
    return predictSnapEndPos;
}

void ArcListLayoutAlgorithm::OnItemPositionAddOrUpdate(LayoutWrapper* layoutWrapper, uint32_t index)
{
    if (!predictSnapEndPos_.has_value()) {
        return;
    }

    float startPos = 0.0f;
    float endPos = 0.0f;
    startPos = totalOffset_ + itemPosition_[index].startPos - spaceWidth_ / FLOAT_TWO;
    endPos = totalOffset_ + itemPosition_[index].endPos + spaceWidth_ / FLOAT_TWO;

    float predictSnapEndPos = predictSnapEndPos_.value();
    float stopOnScreen = contentMainSize_ / FLOAT_TWO;
    if (GreatOrEqual(predictSnapEndPos + stopOnScreen, startPos) &&
        LessNotEqual(predictSnapEndPos + stopOnScreen, endPos)) {
        predictSnapEndPos = CalculatePredictSnapEndPositionByIndex(index, predictSnapEndPos);
    } else {
        return;
    }

    if (!NearEqual(predictSnapEndPos, predictSnapEndPos_.value())) {
        predictSnapEndPos_ = predictSnapEndPos;
    }
}

float ArcListLayoutAlgorithm::GetItemSnapSize()
{
    return ARC_LIST_ITEM_SNAP_SIZE.ConvertToPx();
}

void ArcListLayoutAlgorithm::MeasureHeader(LayoutWrapper* layoutWrapper)
{
    if (headerIndex_ < 0) {
        return;
    }

    const auto& layoutProperty = layoutWrapper->GetLayoutProperty();
    auto headerLayoutConstraint = layoutProperty->CreateChildConstraint();
    headerLayoutConstraint.maxSize.SetMainSize(Infinity<float>(), axis_);

    auto headerWrapper = layoutWrapper->GetOrCreateChildByIndex(headerIndex_);
    CHECK_NULL_VOID(headerWrapper);
    headerWrapper->Measure(headerLayoutConstraint);
    headerMainSize_ = GetMainAxisSize(headerWrapper->GetGeometryNode()->GetMarginFrameSize(), axis_);
}

void ArcListLayoutAlgorithm::LayoutHeader(LayoutWrapper* layoutWrapper, const OffsetF& paddingOffset, float crossSize)
{
    if (headerIndex_ < 0) {
        return;
    }

    auto wrapper = layoutWrapper->GetOrCreateChildByIndex(headerIndex_);
    CHECK_NULL_VOID(wrapper);
    UpdateZIndex(wrapper);

    auto chainOffset = chainOffsetFunc_ ? chainOffsetFunc_(headerIndex_) : 0.0f;
    float transparency = 0.0f;
    if (itemPosition_.count(0) != 0) {
        auto info = itemPosition_[0];
        float itemDeltaHeight = (info.endPos - info.startPos) * (info.scale - 1);
        float itemDispStartPos = info.startPos + info.offsetY - itemDeltaHeight / FLOAT_TWO;
        startHeaderPos_ = itemDispStartPos - headerMainSize_;
        if (LessNotEqual(headerOffset_, 0.0f)) {
            headerOffset_ = GreatNotEqual(startHeaderPos_, HEADER_DIST) ? startHeaderPos_ - HEADER_DIST : 0.0f;
        }
        startHeaderPos_ -= headerOffset_;
        if (GreatNotEqual(startHeaderPos_, -TRANSPARENCY_DIST)) {
            transparency = (startHeaderPos_ + TRANSPARENCY_DIST) / (HEADER_DIST + TRANSPARENCY_DIST);
            transparency = GreatNotEqual(transparency, 1) ? 1 : transparency;
        }
    } else {
        startHeaderPos_ = -chainOffset - headerMainSize_;
        if (LessNotEqual(headerOffset_, 0.0f)) {
            headerOffset_ = 0.0f;
        }
    }

    auto offset = paddingOffset;
    float childCrossSize = GetCrossAxisSize(wrapper->GetGeometryNode()->GetMarginFrameSize(), axis_);
    float crossOffset = (crossSize - childCrossSize) / FLOAT_TWO;
    crossOffset = GreatOrEqual(crossOffset, 0.0f) ? crossOffset : 0.0f;

    offset = offset + OffsetF(crossOffset, startHeaderPos_ + chainOffset);

    wrapper->GetGeometryNode()->SetMarginFrameOffset(offset);

    if (expandSafeArea_ || wrapper->CheckNeedForceMeasureAndLayout()) {
        wrapper->Layout();
    } else {
        SyncGeometry(wrapper);
    }
    auto frameNode = AceType::DynamicCast<FrameNode>(wrapper);
    if (frameNode) {
        frameNode->MarkAndCheckNewOpIncNode();
        auto renderContext = frameNode->GetRenderContext();
        if (renderContext) {
            renderContext->UpdateOpacity(transparency);
        }
    }
}

void ArcListLayoutAlgorithm::UpdateZIndex(const RefPtr<LayoutWrapper>& layoutWrapper)
{
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateZIndex(1);
}

void ArcListLayoutAlgorithm::UpdateSnapCenterContentOffset(LayoutWrapper* layoutWrapper)
{
    if (itemPosition_.empty()) {
        return;
    }

    float itemHeight = 0.0f;
    if (GetStartIndex() == 0) {
        itemHeight = itemPosition_.begin()->second.endPos - itemPosition_.begin()->second.startPos;
        auto snapSize = LessOrEqual(itemHeight, GetItemSnapSize()) ? itemHeight : GetItemSnapSize();
        contentStartOffset_ = std::max((contentMainSize_ - snapSize) / FLOAT_TWO, 0.0f);
    }
    if (GetEndIndex() == totalItemCount_ - 1) {
        itemHeight = itemPosition_.rbegin()->second.endPos - itemPosition_.rbegin()->second.startPos;
        auto snapSize = LessOrEqual(itemHeight, GetItemSnapSize()) ? itemHeight : GetItemSnapSize();
        contentEndOffset_ = std::max((contentMainSize_ - snapSize) / FLOAT_TWO, 0.0f);
    }

    if (childrenSize_ && totalItemCount_ - 1 > 0) {
        auto startItemHeight = posMap_->GetPositionInfo(0).mainSize;
        auto endItemHeight = posMap_->GetPositionInfo(totalItemCount_ - 1).mainSize;
        contentStartOffset_ = std::max((contentMainSize_ - startItemHeight) / FLOAT_TWO, 0.0f);
        contentEndOffset_ = std::max((contentMainSize_ - endItemHeight) / FLOAT_TWO, 0.0f);
    }
}

float ArcListLayoutAlgorithm::GetLayoutFixOffset()
{
    return ARC_LIST_MAIN_POS_OFFSET;
}

void ArcListLayoutAlgorithm::FixItemLayoutOffset(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);

    GenerateItemOffset(layoutWrapper);

    for (auto& pos : itemPosition_) {
        auto wrapper = GetListItem(layoutWrapper, pos.first);
        if (!wrapper) {
            continue;
        }

        auto frameNode = wrapper->GetHostNode();
        if (!frameNode) {
            continue;
        }

        auto renderContext = frameNode->GetRenderContext();
        if (!renderContext) {
            continue;
        }

        // Adjust item location.
        // This must be adjust item location first and then scale it, otherwise it will not work properly.
        renderContext->UpdateTranslateInXY({ 0, pos.second.offsetY });

        // Scale item.
        renderContext->UpdateTransformScale({ pos.second.scale, pos.second.scale });
    }
}

} // namespace OHOS::Ace::NG
