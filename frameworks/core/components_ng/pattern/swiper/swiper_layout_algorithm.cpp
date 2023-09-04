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

#include "core/components_ng/pattern/swiper/swiper_layout_algorithm.h"

#include <algorithm>
#include <cstdint>

#include "base/geometry/axis.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/log/ace_trace.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/pattern/swiper/swiper_layout_property.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/components_ng/pattern/swiper/swiper_utils.h"
#include "core/components_ng/pattern/swiper_indicator/dot_indicator/dot_indicator_paint_property.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/swiper_indicator_utils.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

namespace {
constexpr Dimension INDICATOR_PADDING = 8.0_vp;
constexpr uint32_t INDICATOR_HAS_CHILD = 2;
constexpr uint32_t SWIPER_HAS_CHILD = 3;
} // namespace

int32_t SwiperLayoutAlgorithm::GetLoopIndex(int32_t originalIndex) const
{
    auto loopIndex = originalIndex;
    while (loopIndex < 0) {
        loopIndex = loopIndex + totalItemCount_;
    }
    loopIndex %= totalItemCount_;
    return loopIndex;
}

void SwiperLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto swiperLayoutProperty = AceType::DynamicCast<SwiperLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(swiperLayoutProperty);

    // calculate idealSize and set FrameSize
    auto axis = swiperLayoutProperty->GetDirection().value_or(Axis::HORIZONTAL);

    // calculate main size.
    auto contentConstraint = swiperLayoutProperty->GetContentLayoutConstraint().value();
    bool hasMinSize = swiperLayoutProperty->GetMinSize().has_value() &&
                      !LessOrEqual(swiperLayoutProperty->GetMinSizeValue().Value(), 0);
    bool hasPrevMargin = swiperLayoutProperty->GetPrevMargin().has_value() &&
                         !LessOrEqual(swiperLayoutProperty->GetPrevMarginValue().ConvertToPx(), 0);
    bool hasNextMargin = swiperLayoutProperty->GetNextMargin().has_value() &&
                         !LessOrEqual(swiperLayoutProperty->GetNextMarginValue().ConvertToPx(), 0);

    if (SwiperUtils::IsStretch(swiperLayoutProperty)) {
        prevMargin_ = static_cast<float>(swiperLayoutProperty->GetPrevMarginValue(0.0_px).ConvertToPx());
        nextMargin_ = static_cast<float>(swiperLayoutProperty->GetNextMarginValue(0.0_px).ConvertToPx());
    }
    auto isSingleCase =
        !hasMinSize && (!hasPrevMargin && !hasNextMargin) &&
        ((swiperLayoutProperty->GetDisplayCount().has_value() && swiperLayoutProperty->GetDisplayCountValue() == 1) ||
            (!swiperLayoutProperty->GetDisplayCount().has_value() && SwiperUtils::IsStretch(swiperLayoutProperty)));

    OptionalSizeF contentIdealSize;
    if (isSingleCase) {
        contentIdealSize = CreateIdealSize(contentConstraint, axis, MeasureType::MATCH_CONTENT);
        if (mainSizeIsMeasured_) {
            if (layoutWrapper->IsContraintNoChanged()) {
                contentIdealSize.SetMainSize(contentMainSize_, axis);
            } else {
                mainSizeIsMeasured_ = false;
            }
        }
    } else {
        contentIdealSize = CreateIdealSize(contentConstraint, axis, MeasureType::MATCH_PARENT_MAIN_AXIS);
    }

    const auto& padding = swiperLayoutProperty->CreatePaddingAndBorder();
    paddingBeforeContent_ = axis == Axis::HORIZONTAL ? padding.left.value_or(0) : padding.top.value_or(0);
    paddingAfterContent_ = axis == Axis::HORIZONTAL ? padding.right.value_or(0) : padding.bottom.value_or(0);
    contentMainSize_ = 0.0f;
    if (!GetMainAxisSize(contentIdealSize, axis) && (!isSingleCase || !mainSizeIsMeasured_)) {
        if (totalItemCount_ == 0) {
            contentMainSize_ = 0.0f;
        } else {
            // use parent percentReference size first.
            auto parentPercentReference = contentConstraint.percentReference;
            contentMainSize_ =
                GetMainAxisSize(parentPercentReference, axis) - paddingBeforeContent_ - paddingAfterContent_;
            mainSizeIsDefined_ = false;
        }
    } else {
        contentMainSize_ = GetMainAxisSize(contentIdealSize.ConvertToSizeT(), axis);
        mainSizeIsDefined_ = true;
    }
    auto hostNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(hostNode);
    auto swiperPattern = hostNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(swiperPattern);
    auto getAutoFill = swiperPattern->IsAutoFill();

    // calculate child layout constraint.
    auto childLayoutConstraint =
        SwiperUtils::CreateChildConstraint(swiperLayoutProperty, contentIdealSize, getAutoFill);
    auto itemSpace = SwiperUtils::GetItemSpace(swiperLayoutProperty);
    spaceWidth_ = itemSpace > (contentMainSize_ + paddingBeforeContent_ + paddingAfterContent_) ? 0.0f : itemSpace;
    if (totalItemCount_ > 0) {
        currentOffset_ = currentDelta_;
        startMainPos_ = currentOffset_;
        if ((Positive(prevMargin_) && NonPositive(swiperLayoutProperty->GetPrevMarginValue(0.0_px).ConvertToPx())) ||
            (Positive(nextMargin_) && NonPositive(swiperLayoutProperty->GetNextMarginValue(0.0_px).ConvertToPx()))) {
            prevMargin_ = 0.0f;
            nextMargin_ = 0.0f;
            isNeedResetPrevMarginAndNextMargin_ = true;
        }
        if (prevMargin_ != 0.0f) {
            if (nextMargin_ != 0.0f) {
                endMainPos_ = currentOffset_ + contentMainSize_ - prevMargin_ - nextMargin_ - 2 * spaceWidth_;
            } else {
                endMainPos_ = currentOffset_ + contentMainSize_ - prevMargin_ - spaceWidth_;
            }
        } else {
            if (nextMargin_ != 0.0f) {
                endMainPos_ = currentOffset_ + contentMainSize_ - nextMargin_ - spaceWidth_;
            } else {
                endMainPos_ = currentOffset_ + contentMainSize_;
            }
        }

        MeasureSwiper(layoutWrapper, childLayoutConstraint, axis);
    } else {
        itemPosition_.clear();
        layoutWrapper->RemoveAllChildInRenderTree();
        LOGI("child size is empty");
    }

    auto crossSize = contentIdealSize.CrossSize(axis);
    if ((crossSize.has_value() && GreaterOrEqualToInfinity(crossSize.value())) || !crossSize.has_value()) {
        contentCrossSize_ = GetChildMaxSize(layoutWrapper, axis, false) == 0.0f
                                ? contentCrossSize_
                                : GetChildMaxSize(layoutWrapper, axis, false);
        contentIdealSize.SetCrossSize(contentCrossSize_, axis);
    }

    if (!mainSizeIsDefined_ && isSingleCase) {
        auto childMaxMainSize = GetChildMaxSize(layoutWrapper, axis, true);

        if (childMaxMainSize != contentMainSize_) {
            contentMainSize_ = childMaxMainSize;
            // CheckInactive
            SetInactive(layoutWrapper, 0.0f, contentMainSize_, currentTargetIndex_);
        }
    }

    contentIdealSize.SetMainSize(contentMainSize_, axis);
    AddPaddingToSize(padding, contentIdealSize);
    layoutWrapper->GetGeometryNode()->SetFrameSize(contentIdealSize.ConvertToSizeT());
    if (!itemPosition_.empty()) {
        mainSizeIsMeasured_ = true;
    }

    // set swiper cache info.
    layoutWrapper->SetCacheCount(swiperLayoutProperty->GetCachedCount().value_or(1), childLayoutConstraint);
    layoutWrapper->SetLongPredictTask();

    LOGD("new start index is %{public}d, new end index is %{public}d, offset is %{public}f, mainSize is %{public}f",
        GetStartIndex(), GetEndIndex(), currentOffset_, contentMainSize_);

    // Measure swiper indicator
    if (swiperLayoutProperty->GetShowIndicatorValue(true)) {
        auto hostNode = layoutWrapper->GetHostNode();
        CHECK_NULL_VOID(hostNode);
        auto swiperPattern = hostNode->GetPattern<SwiperPattern>();
        CHECK_NULL_VOID(swiperPattern);
        auto indicatorWrapper = GetNodeLayoutWrapperByTag(layoutWrapper, V2::SWIPER_INDICATOR_ETS_TAG);
        if (indicatorWrapper) {
            auto indicatorLayoutConstraint = swiperLayoutProperty->CreateChildConstraint();
            indicatorLayoutConstraint.parentIdealSize = contentIdealSize;
            indicatorWrapper->Measure(indicatorLayoutConstraint);
        }
    }

    if (swiperLayoutProperty->GetDisplayArrowValue(false)) {
        auto hostNode = layoutWrapper->GetHostNode();
        CHECK_NULL_VOID(hostNode);
        auto swiperPattern = hostNode->GetPattern<SwiperPattern>();
        CHECK_NULL_VOID(swiperPattern);

        if (swiperPattern->HasLeftButtonNode() && swiperPattern->HasRightButtonNode()) {
            auto leftArrowWrapper = GetNodeLayoutWrapperByTag(layoutWrapper, V2::SWIPER_LEFT_ARROW_ETS_TAG);
            auto rightArrowWrapper = GetNodeLayoutWrapperByTag(layoutWrapper, V2::SWIPER_RIGHT_ARROW_ETS_TAG);
            CHECK_NULL_VOID(leftArrowWrapper);
            CHECK_NULL_VOID(rightArrowWrapper);
            if (leftArrowWrapper->GetHostTag() == V2::SWIPER_LEFT_ARROW_ETS_TAG &&
                rightArrowWrapper->GetHostTag() == V2::SWIPER_RIGHT_ARROW_ETS_TAG) {
                MeasureArrow(leftArrowWrapper, swiperLayoutProperty);
                MeasureArrow(rightArrowWrapper, swiperLayoutProperty);
            }
        }
    }
}

float SwiperLayoutAlgorithm::GetChildMaxSize(LayoutWrapper* layoutWrapper, Axis axis, bool isMainAxis) const
{
    if (itemPosition_.empty()) {
        return 0.0f;
    }
    float maxSize = 0.0f;
    float size = 0.0f;
    float prevPos = itemPosition_.begin()->second.startPos;
    for (const auto& pos : itemPosition_) {
        auto wrapper = layoutWrapper->GetOrCreateChildByIndex(GetLoopIndex(pos.first), false);
        if (!wrapper) {
            continue;
        }
        auto geometryNode = wrapper->GetGeometryNode();
        if (!geometryNode) {
            continue;
        }
        size = isMainAxis ? geometryNode->GetMarginFrameSize().MainSize(axis)
                          : geometryNode->GetMarginFrameSize().CrossSize(axis);
        prevPos = pos.second.startPos;
        maxSize = std::max(size, maxSize);
    }
    return maxSize;
}

void SwiperLayoutAlgorithm::MeasureSwiper(
    LayoutWrapper* layoutWrapper, const LayoutConstraintF& layoutConstraint, Axis axis)
{
    int32_t startIndex = 0;
    int32_t endIndex = 0;
    float startPos = 0.0f;
    float endPos = 0.0f;
    int32_t startIndexInVisibleWindow = 0;
    if (!itemPosition_.empty()) {
        startPos = itemPosition_.begin()->second.startPos;
        endPos = itemPosition_.rbegin()->second.endPos;
        for (const auto& item : itemPosition_) {
            if (GreatNotEqual(
                Positive(prevMargin_) ? item.second.endPos + prevMargin_ + spaceWidth_ : item.second.endPos, 0.0f)) {
                startIndexInVisibleWindow = item.first;
                break;
            }
        }
        if (!isLoop_) {
            startIndex = std::min(GetLoopIndex(GetStartIndex()), totalItemCount_ - 1);
            endIndex = std::min(GetLoopIndex(GetEndIndex()), totalItemCount_ - 1);
            startIndexInVisibleWindow = std::min(GetLoopIndex(startIndexInVisibleWindow), totalItemCount_ - 1);
            if (targetIndex_.has_value()) {
                targetIndex_ = GetLoopIndex(targetIndex_.value());
            }
        } else {
            startIndex = GetStartIndex();
            endIndex = GetEndIndex();
        }
        itemPosition_.clear();
    }
    layoutWrapper->RemoveAllChildInRenderTree();
    if (jumpIndex_) {
        LOGD("Jump index: %{public}d, offset is %{public}f, startMainPos: %{public}f, endMainPos: %{public}f",
            jumpIndex_.value(), currentOffset_, startMainPos_, endMainPos_);
        startPos = (jumpIndex_.value() == 0) && Negative(startMainPos_) ? startMainPos_ : 0;
        LayoutForward(layoutWrapper, layoutConstraint, axis, jumpIndex_.value(), startPos);
        auto prevMarginMontage = Positive(prevMargin_) ? prevMargin_ + spaceWidth_ : 0.0f;
        if ((jumpIndex_.value() > 0 && GreatNotEqual(GetStartPosition(), startMainPos_ - prevMarginMontage)) ||
            (isLoop_ && Positive(prevMargin_))) {
            auto prevItemWidth = (Positive(prevMargin_) && NearZero(GetStartIndex()) ? spaceWidth_ : 0.0f);
            LayoutBackward(
                layoutWrapper, layoutConstraint, axis, jumpIndex_.value() - 1, GetStartPosition() - prevItemWidth);
        }
        currentIndex_ = jumpIndex_.value();
    } else if (targetIndex_.has_value()) {
        if (LessNotEqual(startIndexInVisibleWindow, targetIndex_.value())) {
            LayoutForward(layoutWrapper, layoutConstraint, axis, startIndexInVisibleWindow, startPos);
            if (GreatNotEqual(GetStartPosition(), startMainPos_)) {
                LayoutBackward(layoutWrapper, layoutConstraint, axis, GetStartIndex() - 1, GetStartPosition());
            }
        } else if (GreatNotEqual(startIndexInVisibleWindow, targetIndex_.value())) {
            int32_t stepsFromCurrentToTarget = endIndex - targetIndex_.value();
            endIndex -= (stepsFromCurrentToTarget > (totalItemCount_ - 1))
                ? (stepsFromCurrentToTarget - totalItemCount_ + 1) : 0;
            LayoutBackward(layoutWrapper, layoutConstraint, axis, endIndex, endPos);
            if (LessNotEqual(GetEndPosition(), endMainPos_)) {
                LayoutForward(layoutWrapper, layoutConstraint, axis, GetEndIndex() + 1, GetEndPosition());
            }
        } else {
            targetIsSameWithStartFlag_ = true;
            LayoutForward(layoutWrapper, layoutConstraint, axis, startIndexInVisibleWindow, startPos);
            if (Positive(prevMargin_)) {
                LayoutBackward(layoutWrapper, layoutConstraint, axis, GetStartIndex() - 1, GetStartPosition());
            }
        }
    } else {
        LOGD("StartIndex index: %{public}d, offset is %{public}f, startMainPos: %{public}f, endMainPos: %{public}f",
            startIndex, currentOffset_, startMainPos_, endMainPos_);
        bool overScrollTop = startIndex == 0 && GreatNotEqual(startPos, startMainPos_);
        if ((!overScrollFeature_ && NonNegative(currentOffset_)) || (overScrollFeature_ && overScrollTop)) {
            LayoutForward(layoutWrapper, layoutConstraint, axis, startIndex, startPos);
            if (GetStartIndex() > 0 && GreatNotEqual(GetStartPosition(), startMainPos_)) {
                LayoutBackward(layoutWrapper, layoutConstraint, axis, GetStartIndex() - 1, GetStartPosition());
            }
        } else {
            LayoutBackward(layoutWrapper, layoutConstraint, axis, endIndex, endPos);
            if (GetEndIndex() < (totalItemCount_ - 1) && LessNotEqual(GetEndPosition(), endMainPos_)) {
                LayoutForward(layoutWrapper, layoutConstraint, axis, GetEndIndex() + 1, GetEndPosition());
            }
        }
    }
}

bool SwiperLayoutAlgorithm::LayoutForwardItem(LayoutWrapper* layoutWrapper, const LayoutConstraintF& layoutConstraint,
    Axis axis, int32_t& currentIndex, float startPos, float& endPos)
{
    if ((currentIndex + 1 >= totalItemCount_ && !isLoop_) ||
        (static_cast<int32_t>(itemPosition_.size()) >= totalItemCount_)) {
        return false;
    }
    auto wrapper = layoutWrapper->GetOrCreateChildByIndex(GetLoopIndex(currentIndex + 1));
    CHECK_NULL_RETURN(wrapper, 0);
    if (wrapper->GetHostTag() == V2::SWIPER_INDICATOR_ETS_TAG ||
        wrapper->GetHostTag() == V2::SWIPER_LEFT_ARROW_ETS_TAG ||
        wrapper->GetHostTag() == V2::SWIPER_RIGHT_ARROW_ETS_TAG) {
        return false;
    }
    ++currentIndex;
    {
        ACE_SCOPED_TRACE("SwiperLayoutAlgorithm::LayoutForwardItem:%d", currentIndex);
        wrapper->Measure(layoutConstraint);
    }

    float mainLen = GetMainAxisSize(wrapper->GetGeometryNode()->GetMarginFrameSize(), axis);
    auto swiperLayoutProperty = AceType::DynamicCast<SwiperLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(swiperLayoutProperty, 0);

    if (SwiperUtils::IsStretch(swiperLayoutProperty)) {
        auto layoutProperty = wrapper->GetLayoutProperty();
        CHECK_NULL_RETURN(layoutProperty, 0);
        auto visibilityValue = layoutProperty->GetVisibilityValue(VisibleType::VISIBLE);
        if (visibilityValue == VisibleType::INVISIBLE || visibilityValue == VisibleType::GONE) {
            if (swiperLayoutProperty->GetDisplayCountValue(1) != 0) {
                mainLen = (contentMainSize_ - (swiperLayoutProperty->GetDisplayCountValue(1) - 1) * spaceWidth_) /
                          swiperLayoutProperty->GetDisplayCountValue(1);
            }
        }
    }
    endPos = startPos + mainLen;
    itemPosition_[currentIndex] = { startPos, endPos, wrapper->GetHostNode() };
    return true;
}

bool SwiperLayoutAlgorithm::LayoutBackwardItem(LayoutWrapper* layoutWrapper, const LayoutConstraintF& layoutConstraint,
    Axis axis, int32_t& currentIndex, float endPos, float& startPos)
{
    auto swiperLayoutProperty = AceType::DynamicCast<SwiperLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(swiperLayoutProperty, 0);
    int32_t displayCount = swiperLayoutProperty->GetDisplayCount().has_value() ?
        swiperLayoutProperty->GetDisplayCount().value() : 1;
    if ((currentIndex - 1 < 0 && !isLoop_) ||
        static_cast<int32_t>(itemPosition_.size()) >= totalItemCount_ + displayCount - 1) {
        return false;
    }
    auto wrapper = layoutWrapper->GetOrCreateChildByIndex(GetLoopIndex(currentIndex - 1));
    CHECK_NULL_RETURN(wrapper, 0);
    if (wrapper->GetHostTag() == V2::SWIPER_INDICATOR_ETS_TAG ||
        wrapper->GetHostTag() == V2::SWIPER_LEFT_ARROW_ETS_TAG ||
        wrapper->GetHostTag() == V2::SWIPER_RIGHT_ARROW_ETS_TAG) {
        return false;
    }
    --currentIndex;
    {
        ACE_SCOPED_TRACE("SwiperLayoutAlgorithm::MeasureSwiperItem:%d", currentIndex);
        wrapper->Measure(layoutConstraint);
    }
    float mainLen = GetMainAxisSize(wrapper->GetGeometryNode()->GetMarginFrameSize(), axis);

    if (SwiperUtils::IsStretch(swiperLayoutProperty)) {
        auto layoutProperty = wrapper->GetLayoutProperty();
        CHECK_NULL_RETURN(layoutProperty, 0);
        auto visibilityValue = layoutProperty->GetVisibilityValue(VisibleType::VISIBLE);
        if (visibilityValue == VisibleType::INVISIBLE || visibilityValue == VisibleType::GONE) {
            if (swiperLayoutProperty->GetDisplayCountValue(1) != 0) {
                mainLen = (contentMainSize_ - (swiperLayoutProperty->GetDisplayCountValue(1) - 1) * spaceWidth_) /
                          swiperLayoutProperty->GetDisplayCountValue(1);
            }
        }
    }
    startPos = endPos - mainLen;
    itemPosition_[currentIndex] = { startPos, endPos, wrapper->GetHostNode() };
    return true;
}

void SwiperLayoutAlgorithm::LayoutForward(LayoutWrapper* layoutWrapper, const LayoutConstraintF& layoutConstraint,
    Axis axis, int32_t startIndex, float startPos)
{
    float currentEndPos = startPos;
    float currentStartPos = 0.0f;
    float endMainPos = overScrollFeature_ ? std::max(startPos + contentMainSize_, endMainPos_) : endMainPos_;
    if (targetIndex_) {
        endMainPos = Infinity<float>();
    }
    auto swiperLayoutProperty = AceType::DynamicCast<SwiperLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(swiperLayoutProperty);

    auto currentIndex = startIndex - 1;
    do {
        currentStartPos = currentEndPos;
        auto result =
            LayoutForwardItem(layoutWrapper, layoutConstraint, axis, currentIndex, currentStartPos, currentEndPos);
        if (!result) {
            break;
        }
        bool hasMinSize = swiperLayoutProperty->GetMinSize().has_value() &&
                          !LessOrEqual(swiperLayoutProperty->GetMinSizeValue().Value(), 0);
        bool hasPrevMargin = swiperLayoutProperty->GetPrevMargin().has_value() &&
                        !LessOrEqual(swiperLayoutProperty->GetPrevMarginValue().ConvertToPx(), 0);
        bool hasNextMargin = swiperLayoutProperty->GetNextMargin().has_value() &&
                        !LessOrEqual(swiperLayoutProperty->GetNextMarginValue().ConvertToPx(), 0);
        auto isSingleCase =
            !hasMinSize && (!hasPrevMargin && !hasNextMargin) &&
            ((swiperLayoutProperty->GetDisplayCount().has_value() &&
                 swiperLayoutProperty->GetDisplayCountValue() == 1) ||
                (!swiperLayoutProperty->GetDisplayCount().has_value() && SwiperUtils::IsStretch(swiperLayoutProperty)));
        if (isSingleCase && !mainSizeIsDefined_) {
            endMainPos = startPos + itemPosition_.begin()->second.endPos - itemPosition_.begin()->second.startPos;
            endMainPos_ = endMainPos;
        }
        if ((currentIndex >= 0 && currentIndex < (totalItemCount_ - 1)) || isLoop_) {
            currentEndPos += spaceWidth_;
        }
        LOGD("LayoutForward: %{public}d current start pos: %{public}f, current end pos: %{public}f", currentIndex,
            currentStartPos, currentEndPos);
        // reach the valid target index
        if (targetIndex_ && GreatOrEqual(currentIndex, targetIndex_.value())) {
            if (!targetIsSameWithStartFlag_) {
                endMainPos = currentStartPos + contentMainSize_;
                currentTargetIndex_ = targetIndex_.value();
                targetIndex_.reset();
            } else {
                endMainPos = endMainPos_;
                currentTargetIndex_ = targetIndex_.value();
                targetIndex_.reset();
            }
        }
        if (static_cast<int32_t>(itemPosition_.size()) >= totalItemCount_) {
            break;
        }
    } while (LessNotEqual(currentEndPos, nextMargin_ != 0.0f ? endMainPos + nextMargin_ + spaceWidth_ : endMainPos));

    if (overScrollFeature_ && canOverScroll_) {
        LOGD("during over scroll, just return in LayoutForward");
        return;
    }

    // adjust offset.
    if (LessNotEqual(currentEndPos, endMainPos_) && !itemPosition_.empty()) {
        auto firstItemTop = itemPosition_.begin()->second.startPos;
        auto itemTotalSize = currentEndPos - firstItemTop;
        if (LessOrEqual(itemTotalSize, contentMainSize_) && (itemPosition_.begin()->first == 0)) {
            // all items size is less than swiper.
            currentOffset_ = firstItemTop;
            startMainPos_ = currentOffset_;
            if (!mainSizeIsDefined_) {
                // adapt child size.
                LOGD("LayoutForward: adapt child total size");
                contentMainSize_ = itemTotalSize;
            }
        } else {
            // adjust offset. If edgeEffect is SPRING, jump adjust to allow swiper scroll through boundary
            if (!canOverScroll_ || jumpIndex_.has_value()) {
                auto prevMarginMontage = Positive(prevMargin_) ? prevMargin_ + spaceWidth_ : 0.0f;
                auto nextMarginMontage = Positive(nextMargin_) ? nextMargin_ + spaceWidth_ : 0.0f;
                currentOffset_ = currentEndPos - contentMainSize_ + prevMarginMontage + nextMarginMontage;
                LOGD("LayoutForward: adjust offset to %{public}f", currentOffset_);
            }
            startMainPos_ = currentEndPos - contentMainSize_;
            endMainPos_ = currentEndPos;
        }
    }

    // Mark inactive in wrapper.
    for (auto pos = itemPosition_.begin(); pos != itemPosition_.end();) {
        if (GreatNotEqual(
                pos->second.endPos, prevMargin_ != 0.0f ? startMainPos_ - prevMargin_ - spaceWidth_ : startMainPos_)) {
            break;
        }
        layoutWrapper->RemoveChildInRenderTree(GetLoopIndex(pos->first));
        itemPosition_.erase(pos++);
    }
}

void SwiperLayoutAlgorithm::SetInactive(
    LayoutWrapper* layoutWrapper, float startMainPos, float endMainPos, std::optional<int32_t> targetIndex)
{
    auto swiperLayoutProperty = AceType::DynamicCast<SwiperLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(swiperLayoutProperty);
    std::list<int32_t> removeIndexes;
    for (auto pos = itemPosition_.rbegin(); pos != itemPosition_.rend(); ++pos) {
        if (targetIndex.has_value() && targetIndex.value() == pos->first) {
            continue;
        }
        if (LessOrEqual(
                pos->second.endPos, prevMargin_ != 0.0f ? startMainPos - prevMargin_ - spaceWidth_ : startMainPos) ||
            GreatOrEqual(
                pos->second.startPos, nextMargin_ != 0.0f ? endMainPos + nextMargin_ + spaceWidth_ : endMainPos)) {
            layoutWrapper->RemoveChildInRenderTree(GetLoopIndex(pos->first));
            removeIndexes.emplace_back(pos->first);
        }
    }
    for (const auto& index : removeIndexes) {
        itemPosition_.erase(index);
    }
}

void SwiperLayoutAlgorithm::LayoutBackward(
    LayoutWrapper* layoutWrapper, const LayoutConstraintF& layoutConstraint, Axis axis, int32_t endIndex, float endPos)
{
    float currentStartPos = endPos;
    float currentEndPos = 0.0f;
    float startMainPos = overScrollFeature_ ? std::min(endPos - contentMainSize_, startMainPos_) : startMainPos_;
    if (targetIndex_) {
        startMainPos = -Infinity<float>();
    }
    auto currentIndex = endIndex + 1;

    auto swiperLayoutProperty = AceType::DynamicCast<SwiperLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(swiperLayoutProperty);
    int32_t displayCount = swiperLayoutProperty->GetDisplayCount().has_value() ?
        swiperLayoutProperty->GetDisplayCount().value() : 1;
    do {
        currentEndPos = currentStartPos;
        auto result =
            LayoutBackwardItem(layoutWrapper, layoutConstraint, axis, currentIndex, currentEndPos, currentStartPos);
        if (!result) {
            break;
        }
        if (currentIndex > 0 || isLoop_) {
            currentStartPos = currentStartPos - spaceWidth_;
        }
        LOGD("LayoutBackward: %{public}d current start pos: %{public}f, current end pos: %{public}f", currentIndex,
            currentStartPos, currentEndPos);
        // reach the valid target index
        if (targetIndex_ && LessOrEqual(currentIndex, targetIndex_.value())) {
            startMainPos = currentStartPos;
            currentTargetIndex_ = targetIndex_.value();
            targetIndex_.reset();
        }
        if (static_cast<int32_t>(itemPosition_.size()) >= totalItemCount_ + displayCount - 1) {
            break;
        }
    } while (
        GreatNotEqual(currentStartPos, prevMargin_ != 0.0f ? startMainPos - prevMargin_ - spaceWidth_ : startMainPos));

    // adjust offset. If edgeEffect is SPRING, jump adjust to allow swiper scroll through boundary
    if (GreatNotEqual(currentStartPos, startMainPos_)) {
        if (!canOverScroll_ || jumpIndex_.has_value()) {
            currentOffset_ = currentStartPos;
            if (!mainSizeIsDefined_ && GetEndIndex() == totalItemCount_ - 1) {
                auto itemTotalSize = GetEndPosition() - currentStartPos;
                contentMainSize_ = std::min(contentMainSize_, itemTotalSize);
            }
        }
        endMainPos_ = currentStartPos + contentMainSize_;
        startMainPos_ = currentStartPos;
    }

    if (overScrollFeature_) {
        LOGD("during over scroll, just return in LayoutBackward");
        return;
    }

    // Mark inactive in wrapper.
    std::list<int32_t> removeIndexes;
    for (auto pos = itemPosition_.rbegin(); pos != itemPosition_.rend(); ++pos) {
        if (LessNotEqual(
                pos->second.startPos, nextMargin_ != 0.0f ? endMainPos_ + nextMargin_ + spaceWidth_ : endMainPos_)) {
            break;
        }
        layoutWrapper->RemoveChildInRenderTree(GetLoopIndex(pos->first));
        removeIndexes.emplace_back(pos->first);
    }
    for (const auto& index : removeIndexes) {
        itemPosition_.erase(index);
    }
}

void SwiperLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    auto swiperLayoutProperty = AceType::DynamicCast<SwiperLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(swiperLayoutProperty);
    auto axis = swiperLayoutProperty->GetDirection().value_or(Axis::HORIZONTAL);
    auto size = layoutWrapper->GetGeometryNode()->GetFrameSize();
    auto padding = layoutWrapper->GetLayoutProperty()->CreatePaddingAndBorder();
    MinusPaddingToSize(padding, size);
    auto paddingOffset = padding.Offset();

    // layout items.
    for (auto& pos : itemPosition_) {
        int32_t index = pos.first;
        auto offset = paddingOffset;
        auto wrapper = layoutWrapper->GetOrCreateChildByIndex(GetLoopIndex(index));
        if (!wrapper) {
            LOGI("wrapper is out of boundary");
            continue;
        }
        if (wrapper->GetHostTag() == V2::SWIPER_INDICATOR_ETS_TAG ||
            wrapper->GetHostTag() == V2::SWIPER_LEFT_ARROW_ETS_TAG ||
            wrapper->GetHostTag() == V2::SWIPER_RIGHT_ARROW_ETS_TAG) {
            continue;
        }
        float crossOffset = 0.0f;
        pos.second.startPos -= currentOffset_;
        pos.second.endPos -= currentOffset_;

        if (axis == Axis::VERTICAL) {
            offset += OffsetF(crossOffset, pos.second.startPos);
            if (prevMargin_ != 0.0f) {
                offset += OffsetF(0.0f, prevMargin_ + spaceWidth_);
            }
        } else {
            offset += OffsetF(pos.second.startPos, crossOffset);
            if (prevMargin_ != 0.0f) {
                offset += OffsetF(prevMargin_ + spaceWidth_, 0.0f);
            }
        }
        wrapper->GetGeometryNode()->SetMarginFrameOffset(offset);
        wrapper->Layout();
    }
    // Layout swiper indicator
    if (swiperLayoutProperty->GetShowIndicatorValue(true)) {
        auto hostNode = layoutWrapper->GetHostNode();
        CHECK_NULL_VOID(hostNode);
        auto swiperPattern = hostNode->GetPattern<SwiperPattern>();
        CHECK_NULL_VOID(swiperPattern);
        auto indicatorWrapper = GetNodeLayoutWrapperByTag(layoutWrapper, V2::SWIPER_INDICATOR_ETS_TAG);
        if (indicatorWrapper) {
            if (swiperLayoutProperty->GetIndicatorTypeValue(SwiperIndicatorType::DOT) == SwiperIndicatorType::DIGIT) {
                PlaceDigitChild(indicatorWrapper, swiperLayoutProperty);
            }
            indicatorWrapper->Layout();
        }
    }

    if (swiperLayoutProperty->GetDisplayArrowValue(false)) {
        auto hostNode = layoutWrapper->GetHostNode();
        CHECK_NULL_VOID(hostNode);
        auto swiperPattern = hostNode->GetPattern<SwiperPattern>();
        CHECK_NULL_VOID(swiperPattern);

        if (swiperPattern->HasLeftButtonNode() && swiperPattern->HasRightButtonNode()) {
            auto leftArrowWrapper = GetNodeLayoutWrapperByTag(layoutWrapper, V2::SWIPER_LEFT_ARROW_ETS_TAG);
            auto rightArrowWrapper = GetNodeLayoutWrapperByTag(layoutWrapper, V2::SWIPER_RIGHT_ARROW_ETS_TAG);
            if (leftArrowWrapper && (leftArrowWrapper->GetHostTag() == V2::SWIPER_LEFT_ARROW_ETS_TAG)) {
                ArrowLayout(layoutWrapper, leftArrowWrapper, padding);
            }
            if (rightArrowWrapper && (rightArrowWrapper->GetHostTag() == V2::SWIPER_RIGHT_ARROW_ETS_TAG)) {
                ArrowLayout(layoutWrapper, rightArrowWrapper, padding);
            }
        }
    }
}

void SwiperLayoutAlgorithm::PlaceDigitChild(
    const RefPtr<LayoutWrapper>& indicatorWrapper, const RefPtr<LayoutProperty>& layoutProperty)
{
    if (indicatorWrapper->GetTotalChildCount() != INDICATOR_HAS_CHILD) {
        return;
    }
    auto swiperLayoutProperty = AceType::DynamicCast<SwiperLayoutProperty>(layoutProperty);
    CHECK_NULL_VOID(swiperLayoutProperty);
    auto indicatorGeometryNode = indicatorWrapper->GetGeometryNode();
    CHECK_NULL_VOID(indicatorGeometryNode);
    auto indicatorWidth = INDICATOR_PADDING.ConvertToPx() * 2.0;
    auto indicatorHeight = 0.0f;
    for (auto&& child : indicatorWrapper->GetAllChildrenWithBuild()) {
        auto textGeometryNode = child->GetGeometryNode();
        CHECK_NULL_VOID(textGeometryNode);
        auto textFrameSize = textGeometryNode->GetFrameSize();
        indicatorWidth += textFrameSize.Width();
        if (indicatorHeight < textFrameSize.Height()) {
            indicatorHeight = textFrameSize.Height();
        }
    }

    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID_NOLOG(pipelineContext);
    auto swiperIndicatorTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_VOID_NOLOG(swiperIndicatorTheme);
    if (LessNotEqual(indicatorHeight, swiperIndicatorTheme->GetIndicatorDigitHeight().ConvertToPx())) {
        indicatorHeight = swiperIndicatorTheme->GetIndicatorDigitHeight().ConvertToPx();
    }

    auto frameNode = indicatorWrapper->GetHostNode();
    CHECK_NULL_VOID(frameNode);
    auto indicatorlayoutProperty = frameNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    CHECK_NULL_VOID(indicatorlayoutProperty);

    auto currentOffset = SwiperIndicatorUtils::CalcIndicatrFrameOffSet(swiperLayoutProperty,
                                                                       indicatorlayoutProperty,
                                                                       indicatorWidth, indicatorHeight);

    if (swiperLayoutProperty->GetDirectionValue(Axis::HORIZONTAL) == Axis::HORIZONTAL) {
        auto top = indicatorlayoutProperty->GetTop();
        auto bottom = indicatorlayoutProperty->GetBottom();
        if ((!top.has_value() || NearZero(top.value().Value())) &&
            (!bottom.has_value() || NearZero(bottom.value().Value()))) {
            auto dightPadding =
                std::abs(swiperIndicatorTheme->GetIndicatorDigitHeight().ConvertToPx() - indicatorHeight) / 2;
            auto dightVerPadding = swiperIndicatorTheme->GetIndicatorDigitVerticalPadding().ConvertToPx();
            currentOffset.SetY(currentOffset.GetY() - dightVerPadding + dightPadding);
        }
    }

    indicatorGeometryNode->SetMarginFrameOffset(currentOffset);
}

RefPtr<LayoutWrapper> SwiperLayoutAlgorithm::GetNodeLayoutWrapperByTag(
    LayoutWrapper* layoutWrapper, const std::string& tagName) const
{
    CHECK_NULL_RETURN(layoutWrapper, nullptr);
    auto hostNode = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(hostNode, nullptr);
    auto swiperPattern = hostNode->GetPattern<SwiperPattern>();
    CHECK_NULL_RETURN(swiperPattern, nullptr);
    RefPtr<LayoutWrapper> nodeWrapper = nullptr;
    int32_t totalChildCount = layoutWrapper->GetTotalChildCount();
    if (totalChildCount == 0) {
        return nullptr;
    }
    int32_t lastChildIndex = totalChildCount - 1;
    if (swiperPattern->HasIndicatorNode() && !swiperPattern->HasLeftButtonNode() &&
        !swiperPattern->HasRightButtonNode()) {
        nodeWrapper = layoutWrapper->GetOrCreateChildByIndex(lastChildIndex);
        return nodeWrapper;
    }
    int32_t endLoopChildIndex = lastChildIndex - SWIPER_HAS_CHILD;
    for (int32_t index = lastChildIndex; index > endLoopChildIndex && index >= 0; index--) {
        nodeWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
        if (nodeWrapper && (nodeWrapper->GetHostTag() == tagName)) {
            return nodeWrapper;
        }
    }

    return nullptr;
}

void SwiperLayoutAlgorithm::MeasureArrow(
    const RefPtr<LayoutWrapper>& arrowWrapper, const RefPtr<LayoutProperty>& layoutProperty) const
{
    CHECK_NULL_VOID(arrowWrapper);
    CHECK_NULL_VOID(layoutProperty);
    auto swiperLayoutProperty = AceType::DynamicCast<SwiperLayoutProperty>(layoutProperty);
    CHECK_NULL_VOID(swiperLayoutProperty);
    auto arrowGeometryNode = arrowWrapper->GetGeometryNode();
    CHECK_NULL_VOID(arrowGeometryNode);

    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID_NOLOG(pipelineContext);
    auto swiperIndicatorTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_VOID_NOLOG(swiperIndicatorTheme);

    arrowGeometryNode->SetFrameSize(
        SizeF { static_cast<float>(
                    swiperLayoutProperty->GetBackgroundSizeValue(swiperIndicatorTheme->GetBigArrowBackgroundSize())
                        .ConvertToPx()),
            static_cast<float>(
                swiperLayoutProperty->GetBackgroundSizeValue(swiperIndicatorTheme->GetBigArrowBackgroundSize())
                    .ConvertToPx()) });
    auto indicatorLayoutConstraint = swiperLayoutProperty->CreateChildConstraint();
    arrowWrapper->Measure(indicatorLayoutConstraint);
}

void SwiperLayoutAlgorithm::ArrowLayout(
    LayoutWrapper* layoutWrapper, const RefPtr<LayoutWrapper>& arrowWrapper, const PaddingPropertyF padding) const
{
    CHECK_NULL_VOID(layoutWrapper);
    CHECK_NULL_VOID(arrowWrapper);
    auto swiperLayoutProperty = AceType::DynamicCast<SwiperLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(swiperLayoutProperty);
    auto axis = swiperLayoutProperty->GetDirection().value_or(Axis::HORIZONTAL);
    auto indicatorType = swiperLayoutProperty->GetIndicatorTypeValue(SwiperIndicatorType::DOT);
    auto arrowGeometryNode = arrowWrapper->GetGeometryNode();
    CHECK_NULL_VOID(arrowGeometryNode);
    auto arrowFrameSize = arrowGeometryNode->GetFrameSize();
    auto layoutGeometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(layoutGeometryNode);
    auto swiperFrameSize = layoutGeometryNode->GetFrameSize();
    auto isShowIndicatorArrow =
        (!swiperLayoutProperty->GetIsSidebarMiddleValue(false) && swiperLayoutProperty->GetShowIndicatorValue(true));
    SizeF indicatorFrameSize;
    RectF indicatorFrameRect;
    auto normalArrowMargin = 0.0f;
    if (isShowIndicatorArrow) {
        auto indicatorWrapper = GetNodeLayoutWrapperByTag(layoutWrapper, V2::SWIPER_INDICATOR_ETS_TAG);
        CHECK_NULL_VOID(indicatorWrapper);
        auto indicatorGeometry = indicatorWrapper->GetGeometryNode();
        CHECK_NULL_VOID(indicatorGeometry);
        indicatorFrameSize = indicatorGeometry->GetFrameSize();
        indicatorFrameRect = indicatorGeometry->GetFrameRect();
        if (indicatorType == SwiperIndicatorType::DOT) {
            auto hostNode = layoutWrapper->GetHostNode();
            CHECK_NULL_VOID(hostNode);
            auto swiperPattern = hostNode->GetPattern<SwiperPattern>();
            CHECK_NULL_VOID(swiperPattern);
            auto itemCount = swiperPattern->TotalCount();
            auto indicatorNode = indicatorWrapper->GetHostNode();
            CHECK_NULL_VOID(indicatorNode);
            auto pipeline = PipelineBase::GetCurrentContext();
            CHECK_NULL_VOID(pipeline);
            auto theme = pipeline->GetTheme<SwiperIndicatorTheme>();
            CHECK_NULL_VOID(theme);
            auto indicatorPaintProperty = indicatorNode->GetPaintProperty<DotIndicatorPaintProperty>();
            CHECK_NULL_VOID(indicatorPaintProperty);
            auto itemWidth =
                static_cast<float>(indicatorPaintProperty->GetItemWidthValue(theme->GetSize()).ConvertToPx());
            auto selectedItemWidth =
                static_cast<float>(indicatorPaintProperty->GetSelectedItemWidthValue(theme->GetSize()).ConvertToPx());
            auto indicatorPadding = static_cast<float>(theme->GetIndicatorDotPadding().ConvertToPx());
            auto allPointDiameterSum = itemWidth * static_cast<float>(itemCount + 1);
            if (indicatorPaintProperty->GetIsCustomSizeValue(false)) {
                allPointDiameterSum = itemWidth * static_cast<float>(itemCount - 1) + selectedItemWidth;
            }
            auto allPointSpaceSum =
                static_cast<float>(theme->GetIndicatorDotItemSpace().ConvertToPx()) * (itemCount - 1);
            auto indicatorWidth = indicatorPadding + allPointDiameterSum + allPointSpaceSum + indicatorPadding;
            normalArrowMargin = ((axis == Axis::HORIZONTAL ? indicatorFrameSize.Width() : indicatorFrameSize.Height()) -
                                    indicatorWidth) * 0.5f;
        }
    }
    auto isLeftArrow = arrowWrapper->GetHostTag() == V2::SWIPER_LEFT_ARROW_ETS_TAG;
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto swiperIndicatorTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_VOID(swiperIndicatorTheme);
    OffsetF arrowOffset(0.0f, 0.0f);
    float startPoint = 0.0f;
    if (axis == Axis::HORIZONTAL && isShowIndicatorArrow) {
        auto indicatorPadding = indicatorType == SwiperIndicatorType::DIGIT
                                    ? swiperIndicatorTheme->GetIndicatorDigitPadding().ConvertToPx()
                                    : swiperIndicatorTheme->GetIndicatorDotPadding().ConvertToPx();
        startPoint = isLeftArrow ? (indicatorFrameRect.Left() - arrowFrameSize.Width() -
                                       swiperIndicatorTheme->GetArrowScale().ConvertToPx() + indicatorPadding +
                                       normalArrowMargin)
                                 : (indicatorFrameRect.Right() + swiperIndicatorTheme->GetArrowScale().ConvertToPx() -
                                       indicatorPadding - normalArrowMargin);
        arrowOffset.SetX(startPoint);
        if (isLeftArrow && !NonNegative(arrowOffset.GetX() - padding.left.value_or(0.0f))) {
            arrowOffset.SetX(padding.left.value_or(0.0f));
        }
        if (GreatOrEqual(
                arrowOffset.GetX() + arrowFrameSize.Width(), swiperFrameSize.Width() - padding.right.value_or(0.0f))) {
            arrowOffset.SetX(swiperFrameSize.Width() - arrowFrameSize.Width() - padding.right.value_or(0.0f));
        }
        arrowOffset.SetY(indicatorFrameRect.Top() + (indicatorFrameSize.Height() - arrowFrameSize.Height()) * 0.5f);
    } else if (axis == Axis::HORIZONTAL && !isShowIndicatorArrow) {
        startPoint = isLeftArrow
                         ? swiperIndicatorTheme->GetArrowHorizontalMargin().ConvertToPx() + padding.left.value_or(0.0f)
                         : (swiperFrameSize.Width() - padding.right.value_or(0.0f) - arrowFrameSize.Width() -
                               swiperIndicatorTheme->GetArrowHorizontalMargin().ConvertToPx());
        arrowOffset.SetX(startPoint);
        arrowOffset.SetY((swiperFrameSize.Height() - padding.top.value_or(0.0f) - padding.bottom.value_or(0.0f) -
                             arrowFrameSize.Height()) *
                             0.5f +
                         padding.top.value_or(0.0f));
    } else if (axis != Axis::HORIZONTAL && isShowIndicatorArrow) {
        auto indicatorPadding = indicatorType == SwiperIndicatorType::DIGIT
                                    ? swiperIndicatorTheme->GetIndicatorDigitPadding().ConvertToPx()
                                    : swiperIndicatorTheme->GetIndicatorDotPadding().ConvertToPx();
        startPoint =
            isLeftArrow
                ? (indicatorFrameRect.Top() - arrowFrameSize.Height() - padding.top.value_or(0.0f) -
                      swiperIndicatorTheme->GetArrowScale().ConvertToPx() + indicatorPadding + normalArrowMargin)
                : (indicatorFrameRect.Bottom() + padding.bottom.value_or(0.0f) +
                      swiperIndicatorTheme->GetArrowScale().ConvertToPx() - indicatorPadding - normalArrowMargin);
        arrowOffset.SetX(indicatorFrameRect.Left() + (indicatorFrameSize.Width() - arrowFrameSize.Width()) * 0.5f);
        arrowOffset.SetY(startPoint);
        if (isLeftArrow && !NonNegative(arrowOffset.GetY() - padding.top.value_or(0.0f))) {
            arrowOffset.SetY(padding.top.value_or(0.0f));
        }
        if (GreatOrEqual(arrowOffset.GetY() + arrowFrameSize.Height(),
                swiperFrameSize.Height() - padding.bottom.value_or(0.0f))) {
            arrowOffset.SetY(swiperFrameSize.Height() - arrowFrameSize.Height() - padding.bottom.value_or(0.0f));
        }
    } else {
        startPoint = isLeftArrow
                         ? swiperIndicatorTheme->GetArrowVerticalMargin().ConvertToPx() + padding.top.value_or(0.0f)
                         : (swiperFrameSize.Height() - arrowFrameSize.Width() - padding.bottom.value_or(0.0f) -
                               swiperIndicatorTheme->GetArrowVerticalMargin().ConvertToPx());
        arrowOffset.SetX(padding.left.value_or(0.0f) + (swiperFrameSize.Width() - padding.left.value_or(0.0f) -
                                                           padding.right.value_or(0.0f) - arrowFrameSize.Width()) *
                                                           0.5f);
        arrowOffset.SetY(startPoint);
    }
    arrowGeometryNode->SetMarginFrameOffset(arrowOffset);
    arrowWrapper->Layout();
}

} // namespace OHOS::Ace::NG
