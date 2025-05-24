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

#include "core/components_ng/pattern/grid/grid_focus.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/grid/grid_item_pattern.h"

namespace OHOS::Ace::NG {
std::pair<bool, bool> GridFocus::IsFirstOrLastFocusableChild(int32_t curMainIndex, int32_t curCrossIndex)
{
    std::unordered_set<int32_t> crossIndexSet;
    size_t maxSize = 0;
    for (int32_t index = curMainIndex - curFocusIndexInfo_.mainSpan + 1; index <= curMainIndex; index++) {
        auto tempIndexSet = GetFocusableChildCrossIndexesAt(index);
        if (tempIndexSet.size() > maxSize) {
            maxSize = tempIndexSet.size();
            crossIndexSet = tempIndexSet;
        }
    }
    auto findLesser = std::find_if(crossIndexSet.begin(), crossIndexSet.end(),
        [curCrossIndex](int32_t crossIndex) { return curCrossIndex > crossIndex; });
    auto findGreater = std::find_if(crossIndexSet.begin(), crossIndexSet.end(),
        [curCrossIndex](int32_t crossIndex) { return curCrossIndex < crossIndex; });
    return { curCrossIndex == 0 || findLesser == crossIndexSet.end(),
        curCrossIndex == info_.crossCount_ - 1 || findGreater == crossIndexSet.end() };
}

std::pair<FocusStep, FocusStep> GridFocus::GetFocusSteps(int32_t curMainIndex, int32_t curCrossIndex, FocusStep step)
{
    auto firstStep = FocusStep::NONE;
    auto secondStep = FocusStep::NONE;
    auto isFirstOrLastFocusable = IsFirstOrLastFocusableChild(curMainIndex, curCrossIndex);
    auto isFirstFocusable = isFirstOrLastFocusable.first;
    auto isLastFocusable = isFirstOrLastFocusable.second;
    auto focusWrapMode = GetFocusWrapMode();
    if (info_.axis_ == Axis::VERTICAL) {
        if (isFirstFocusable && (step == FocusStep::SHIFT_TAB ||
            (focusWrapMode == FocusWrapMode::WRAP_WITH_ARROW && step == FocusStep::LEFT))) {
            firstStep = FocusStep::UP;
            secondStep = FocusStep::RIGHT_END;
        } else if (isLastFocusable && (step == FocusStep::TAB || (focusWrapMode == FocusWrapMode::WRAP_WITH_ARROW &&
            step == FocusStep::RIGHT))) {
            firstStep = FocusStep::DOWN;
            secondStep = FocusStep::LEFT_END;
        }
    } else if (info_.axis_ == Axis::HORIZONTAL) {
        if (isFirstFocusable && (step == FocusStep::SHIFT_TAB ||
            (focusWrapMode == FocusWrapMode::WRAP_WITH_ARROW && step == FocusStep::UP))) {
            firstStep = FocusStep::LEFT;
            secondStep = FocusStep::DOWN_END;
        } else if (isLastFocusable && (step == FocusStep::TAB || (focusWrapMode == FocusWrapMode::WRAP_WITH_ARROW &&
            step == FocusStep::DOWN))) {
            firstStep = FocusStep::RIGHT;
            secondStep = FocusStep::UP_END;
        }
    }
    TAG_LOGI(AceLogTag::ACE_GRID, "Get focus steps. First step is %{public}d. Second step is %{public}d", firstStep,
        secondStep);
    return { firstStep, secondStep };
}

FocusWrapMode GridFocus::GetFocusWrapMode()
{
    auto host = grid_.GetHost();
    CHECK_NULL_RETURN(host, FocusWrapMode::DEFAULT);
    auto gridLayoutProperty = host->GetLayoutProperty<GridLayoutProperty>();
    CHECK_NULL_RETURN(gridLayoutProperty, FocusWrapMode::DEFAULT);
    return gridLayoutProperty->GetFocusWrapMode().value_or(FocusWrapMode::DEFAULT);
}

WeakPtr<FocusHub> GridFocus::GetNextFocusSimplified(FocusStep step, const RefPtr<FocusHub>& current)
{
    CHECK_NULL_RETURN(current, nullptr);
    auto host = grid_.GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto* ctx = grid_.GetContext();
    CHECK_NULL_RETURN(ctx, nullptr);

    int32_t diff = 0;
    if (step == FocusStep::TAB) {
        diff = 1;
    } else if (step == FocusStep::SHIFT_TAB) {
        diff = -1;
    } else {
        // not yet implemented
        return nullptr;
    }

    int32_t idx = host->GetChildTrueIndex(current->GetFrameNode()) + diff;
    while (idx >= 0 && idx < info_.GetChildrenCount()) {
        if (idx < info_.startIndex_ || idx > info_.endIndex_) {
            grid_.ScrollToIndex(idx);
            ctx->FlushUITaskWithSingleDirtyNode(host);
        }
        auto next = host->GetChildByIndex(idx);
        CHECK_NULL_BREAK(next);
        auto nextFocus = next->GetHostNode()->GetFocusHub();
        if (nextFocus && nextFocus->IsFocusable()) {
            return nextFocus;
        }
        idx += diff;
    }
    return nullptr;
}

WeakPtr<FocusHub> GridFocus::GetNextFocusNode(
    FocusStep step, const WeakPtr<FocusHub>& currentFocusNode, bool isMainSkip)
{
    if (!GetCurrentFocusInfo(step, currentFocusNode)) {
        return nullptr;
    }
    auto focusSteps = GetFocusSteps(curFocusIndexInfo_.mainIndex, curFocusIndexInfo_.crossIndex, step);
    if (focusSteps.first != FocusStep::NONE && focusSteps.second != FocusStep::NONE) {
        return HandleFocusSteps(step, currentFocusNode, focusSteps);
    }
    ResetAllDirectionsStep();
    auto indexes = GetNextIndexByStep(curFocusIndexInfo_.mainIndex, curFocusIndexInfo_.crossIndex,
        curFocusIndexInfo_.mainSpan, curFocusIndexInfo_.crossSpan, step);
    auto nextMainIndex = indexes.first;
    auto nextCrossIndex = indexes.second;
    while (nextMainIndex >= 0 && nextCrossIndex >= 0) {
        if (info_.gridMatrix_.find(nextMainIndex) == info_.gridMatrix_.end()) {
            TAG_LOGW(AceLogTag::ACE_GRID, "Can not find next main index: %{public}d", nextMainIndex);
            return nullptr;
        }
        auto nextMaxCrossCount = info_.crossCount_;
        auto flag = (step == FocusStep::LEFT_END) || (step == FocusStep::RIGHT_END);
        auto weakChild = info_.hasBigItem_
                             ? (GetFocusWrapMode() == FocusWrapMode::WRAP_WITH_ARROW && CheckIsCrossDirectionFocus(step)
                                       ? SearchBigItemFocusableChildInCross(
                                           curFocusIndexInfo_.mainStart,
                                           nextCrossIndex,
                                           step,
                                           isMainSkip)
                                       : SearchIrregularFocusableChild(nextMainIndex, nextCrossIndex))
                             : SearchFocusableChildInCross(nextMainIndex, nextCrossIndex, nextMaxCrossCount,
                                 flag ? -1 : curFocusIndexInfo_.mainIndex,
                                 curFocusIndexInfo_.crossIndex);
        auto child = weakChild.Upgrade();
        if (child && child->IsFocusable()) {
            ScrollToFocusNode(weakChild);
            return weakChild;
        }
        auto indexes = GetNextIndexByStep(nextMainIndex, nextCrossIndex, 1, 1, step);
        nextMainIndex = indexes.first;
        nextCrossIndex = indexes.second;
    }
    return nullptr;
}

bool GridFocus::GetCurrentFocusInfo(FocusStep step, const WeakPtr<FocusHub>& currentFocusNode)
{
    auto curFocus = currentFocusNode.Upgrade();
    CHECK_NULL_RETURN(curFocus, false);
    auto curFrame = curFocus->GetFrameNode();
    CHECK_NULL_RETURN(curFrame, false);
    auto curPattern = curFrame->GetPattern();
    CHECK_NULL_RETURN(curPattern, false);
    auto curItemPattern = AceType::DynamicCast<GridItemPattern>(curPattern);
    CHECK_NULL_RETURN(curItemPattern, false);
    auto curItemProperty = curItemPattern->GetLayoutProperty<GridItemLayoutProperty>();
    CHECK_NULL_RETURN(curItemProperty, false);
    auto irregularInfo = curItemPattern->GetIrregularItemInfo();
    bool hasIrregularItemInfo = irregularInfo.has_value();

    auto curMainIndex = curItemProperty->GetMainIndex().value_or(-1);
    auto curCrossIndex = curItemProperty->GetCrossIndex().value_or(-1);
    auto curMainSpan =
        hasIrregularItemInfo ? irregularInfo.value().mainSpan : curItemProperty->GetMainSpan(info_.axis_);
    auto curCrossSpan =
        hasIrregularItemInfo ? irregularInfo.value().crossSpan : curItemProperty->GetCrossSpan(info_.axis_);
    auto curMainStart =
        hasIrregularItemInfo ? irregularInfo.value().mainStart : curItemProperty->GetMainStart(info_.axis_);
    auto curCrossStart =
        hasIrregularItemInfo ? irregularInfo.value().crossStart : curItemProperty->GetCrossStart(info_.axis_);
    auto curMainEnd = hasIrregularItemInfo ? irregularInfo.value().mainEnd : curItemProperty->GetMainEnd(info_.axis_);
    auto curCrossEnd =
        hasIrregularItemInfo ? irregularInfo.value().crossEnd : curItemProperty->GetCrossEnd(info_.axis_);

    curFocusIndexInfo_.mainIndex = curMainIndex;
    curFocusIndexInfo_.crossIndex = curCrossIndex;
    curFocusIndexInfo_.mainSpan = curMainSpan;
    curFocusIndexInfo_.crossSpan = curCrossSpan;
    curFocusIndexInfo_.mainStart = curMainStart;
    curFocusIndexInfo_.mainEnd = curMainEnd;
    curFocusIndexInfo_.crossStart = curCrossStart;
    curFocusIndexInfo_.crossEnd = curCrossEnd;

    if (curMainIndex < 0 || curCrossIndex < 0) {
        TAG_LOGW(AceLogTag::ACE_GRID, "can't find focused child.");
        return false;
    }
    if (info_.gridMatrix_.find(curMainIndex) == info_.gridMatrix_.end()) {
        TAG_LOGW(AceLogTag::ACE_GRID, "Can not find current main index: %{public}d", curMainIndex);
        return false;
    }
    TAG_LOGI(AceLogTag::ACE_GRID,
        "GetNextFocusNode: Current:(%{public}d,%{public}d)-[%{public}d,%{public}d]. Focus: %{public}d", curMainIndex,
        curCrossIndex, curMainSpan, curCrossSpan, step);

    return true;
}

WeakPtr<FocusHub> GridFocus::HandleFocusSteps(
    FocusStep step, const WeakPtr<FocusHub>& currentFocusNode, std::pair<FocusStep, FocusStep> focusSteps)
{
    isTab_ = (step == FocusStep::TAB || step == FocusStep::SHIFT_TAB);
    if (GetFocusWrapMode() == FocusWrapMode::WRAP_WITH_ARROW && curFocusIndexInfo_.mainSpan > 1 && !isTab_ &&
        (info_.axis_ == Axis::VERTICAL ? (focusSteps.first == FocusStep::DOWN)
                                       : (focusSteps.first == FocusStep::RIGHT))) {
        auto secondStepRes = GetNextFocusNode(focusSteps.second, currentFocusNode, true);
        if (!secondStepRes.Upgrade()) {
            return currentFocusNode;
        }
        return secondStepRes;
    } else {
        auto firstStepRes = GetNextFocusNode(focusSteps.first, currentFocusNode);
        if (!firstStepRes.Upgrade()) {
            isTab_ = false;
            return nullptr;
        }
        auto secondStepRes = GetNextFocusNode(focusSteps.second, firstStepRes);
        if (!secondStepRes.Upgrade()) {
            isTab_ = false;
            return firstStepRes;
        }
        isTab_ = false;
        return secondStepRes;
    }
}

bool GridFocus::CheckIsCrossDirectionFocus(FocusStep step)
{
    bool isVertical = (info_.axis_ == Axis::VERTICAL);

    bool isLeftOrRight = (step == FocusStep::LEFT) || (step == FocusStep::RIGHT) || (step == FocusStep::LEFT_END) ||
                         (step == FocusStep::RIGHT_END);

    bool isUpOrDown = (step == FocusStep::UP) || (step == FocusStep::DOWN) || (step == FocusStep::UP_END) ||
                      (step == FocusStep::DOWN_END);

    return !isTab_ && ((isVertical && isLeftOrRight) || (!isVertical && isUpOrDown));
}

int32_t GridFocus::GetIndexByFocusHub(const WeakPtr<FocusHub>& focusNode)
{
    auto focusHub = focusNode.Upgrade();
    CHECK_NULL_RETURN(focusHub, -1);
    auto node = focusHub->GetFrameNode();
    CHECK_NULL_RETURN(node, -1);
    auto property = AceType::DynamicCast<GridItemLayoutProperty>(node->GetLayoutProperty());
    CHECK_NULL_RETURN(property, -1);
    int32_t crossIndex = property->GetCrossIndex().value_or(-1);
    int32_t mainIndex = property->GetMainIndex().value_or(-1);
    return info_.FindInMatrixByMainIndexAndCrossIndex(mainIndex, crossIndex);
}

std::pair<int32_t, int32_t> GridFocus::GetNextIndexByStep(
    int32_t curMainIndex, int32_t curCrossIndex, int32_t curMainSpan, int32_t curCrossSpan, FocusStep step)
{
    auto curMainStart = info_.startMainLineIndex_;
    auto curMainEnd = info_.endMainLineIndex_;
    auto curChildStartIndex = info_.startIndex_;
    auto curChildEndIndex = info_.endIndex_;
    auto childrenCount = info_.GetChildrenCount();
    auto hasIrregularItems = info_.hasBigItem_;
    if (info_.gridMatrix_.find(curMainIndex) == info_.gridMatrix_.end()) {
        TAG_LOGW(AceLogTag::ACE_GRID, "Can not find current main index: %{public}d", curMainIndex);
        return { -1, -1 };
    }
    TAG_LOGI(AceLogTag::ACE_GRID,
        "Current: (%{public}d,%{public}d)-[%{public}d,%{public}d]. axis: %{public}d, step: %{public}d", curMainIndex,
        curCrossIndex, curMainSpan, curCrossSpan, info_.axis_, step);
    auto curMaxCrossCount = info_.crossCount_;
    auto nextMainIndex = curMainIndex;
    auto nextCrossIndex = curCrossIndex;
    if ((step == FocusStep::UP_END && info_.axis_ == Axis::HORIZONTAL) ||
        (step == FocusStep::LEFT_END && info_.axis_ == Axis::VERTICAL)) {
        nextMainIndex = curMainIndex;
        nextCrossIndex = 0;
        isLeftEndStep_ = hasIrregularItems ? true : false;
    } else if ((step == FocusStep::DOWN_END && info_.axis_ == Axis::HORIZONTAL) ||
               (step == FocusStep::RIGHT_END && info_.axis_ == Axis::VERTICAL)) {
        nextMainIndex = curMainIndex;
        nextCrossIndex = curMaxCrossCount - 1;
        isRightEndStep_ = hasIrregularItems ? true : false;
    } else if (((step == FocusStep::UP || step == FocusStep::SHIFT_TAB) && info_.axis_ == Axis::HORIZONTAL) ||
               ((step == FocusStep::LEFT || step == FocusStep::SHIFT_TAB) && info_.axis_ == Axis::VERTICAL)) {
        nextMainIndex = curMainIndex;
        nextCrossIndex = curCrossIndex - 1;
        isLeftStep_ = hasIrregularItems ? true : false;
    } else if ((step == FocusStep::UP && info_.axis_ == Axis::VERTICAL) ||
               (step == FocusStep::LEFT && info_.axis_ == Axis::HORIZONTAL)) {
        nextMainIndex = hasIrregularItems ? curMainIndex - curMainSpan : curMainIndex - 1;
        nextCrossIndex = curCrossIndex + static_cast<int32_t>((curCrossSpan - 1) / 2);
        isUpStep_ = hasIrregularItems ? true : false;
    } else if (((step == FocusStep::DOWN || step == FocusStep::TAB) && info_.axis_ == Axis::HORIZONTAL) ||
               ((step == FocusStep::RIGHT || step == FocusStep::TAB) && info_.axis_ == Axis::VERTICAL)) {
        nextMainIndex = curMainIndex;
        nextCrossIndex = curCrossIndex + curCrossSpan;
        isRightStep_ = hasIrregularItems ? true : false;
    } else if ((step == FocusStep::DOWN && info_.axis_ == Axis::VERTICAL) ||
               (step == FocusStep::RIGHT && info_.axis_ == Axis::HORIZONTAL)) {
        nextMainIndex = hasIrregularItems ? curMainIndex + 1 : curMainIndex + curMainSpan;
        nextCrossIndex = curCrossIndex + static_cast<int32_t>((curCrossSpan - 1) / 2);
        isDownStep_ = hasIrregularItems ? true : false;
    } else {
        TAG_LOGW(
            AceLogTag::ACE_GRID, "Next index return: Invalid step: %{public}d and axis: %{public}d", step, info_.axis_);
        return { -1, -1 };
    }
    if (curChildStartIndex == 0 && curMainIndex == 0 && nextMainIndex < curMainIndex) {
        nextMainIndex = curMainIndex;
    }
    if (curChildEndIndex == childrenCount - 1 && curMainIndex == curMainEnd && nextMainIndex > curMainIndex) {
        nextMainIndex = curMainIndex;
    }
    if (nextMainIndex == curMainIndex && nextCrossIndex == curCrossIndex) {
        TAG_LOGI(AceLogTag::ACE_GRID,
            "Next index return: Move stoped. Next index: (%{public}d,%{public}d) is same as current.", nextMainIndex,
            nextCrossIndex);
        ResetAllDirectionsStep();
        return { -1, -1 };
    }
    if (curChildStartIndex != 0 && curMainIndex == curMainStart && nextMainIndex < curMainIndex) {
        // Scroll item up.
        grid_.UpdateStartIndex(curChildStartIndex - 1);
        auto* pipeline = grid_.GetContext();
        if (pipeline) {
            pipeline->FlushUITasks();
        }
    } else if (curChildEndIndex != childrenCount - 1 && curMainIndex == curMainEnd && nextMainIndex > curMainIndex) {
        // Scroll item down.
        grid_.UpdateStartIndex(curChildEndIndex + 1);
        auto* pipeline = grid_.GetContext();
        if (pipeline) {
            pipeline->FlushUITasks();
        }
    }
    curMainStart = info_.startMainLineIndex_;
    curMainEnd = info_.endMainLineIndex_;
    if (nextMainIndex < curMainStart || nextMainIndex > curMainEnd) {
        ResetAllDirectionsStep();
        return { -1, -1 };
    }
    if (nextCrossIndex < 0) {
        ResetAllDirectionsStep();
        return { -1, -1 };
    }
    if (info_.gridMatrix_.find(nextMainIndex) == info_.gridMatrix_.end()) {
        ResetAllDirectionsStep();
        return { -1, -1 };
    }
    auto nextMaxCrossCount = info_.crossCount_;
    if (nextCrossIndex >= nextMaxCrossCount) {
        TAG_LOGI(AceLogTag::ACE_GRID,
            "Next index: { %{public}d,%{public}d }. Next cross index is greater than max cross count: %{public}d.",
            nextMainIndex, nextCrossIndex, nextMaxCrossCount - 1);
        if (nextMaxCrossCount - 1 != (curCrossIndex + curCrossSpan - 1)) {
            TAG_LOGI(AceLogTag::ACE_GRID,
                "Current cross index: %{public}d is not the tail item. Return to the tail: { %{public}d,%{public}d }",
                curCrossIndex, nextMainIndex, nextMaxCrossCount - 1);
            return { nextMainIndex, nextMaxCrossCount - 1 };
        }
        ResetAllDirectionsStep();
        TAG_LOGI(AceLogTag::ACE_GRID, "Current cross index: %{public}d is the tail item. No next item can be found!",
            curCrossIndex);
        return { -1, -1 };
    }
    TAG_LOGI(AceLogTag::ACE_GRID, "Next index return: { %{public}d,%{public}d }.", nextMainIndex, nextCrossIndex);
    return { nextMainIndex, nextCrossIndex };
}

WeakPtr<FocusHub> GridFocus::SearchBigItemFocusableChildInCross(
    int32_t curMainStart, int32_t tarCrossIndex, FocusStep step, bool isMainSkip)
{
    auto host = grid_.GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    if (isMainSkip) {
        ++curMainStart;
    }
    auto main = info_.gridMatrix_.find(curMainStart);
    while (main != info_.gridMatrix_.end()) {
        auto cross = main->second.find(tarCrossIndex);
        while (cross != main->second.end()) {
            auto next = host->GetChildByIndex(cross->second);
            CHECK_NULL_BREAK(next);
            auto nextNode = next->GetHostNode();
            CHECK_NULL_BREAK(nextNode);
            auto nextFocus = nextNode->GetFocusHub();
            if (nextFocus && nextFocus->IsFocusable()) {
                return nextFocus;
            }
            if (CheckStepDirection(step, false)) {
                tarCrossIndex--;
            } else if (CheckStepDirection(step, true)) {
                tarCrossIndex++;
            }
            if (main->second.find(tarCrossIndex) == main->second.end()) {
                tarCrossIndex = main->second.size() - tarCrossIndex;
                break;
            }
            cross = main->second.find(tarCrossIndex);
        }
        if (CheckStepDirection(step, false)) {
            curMainStart--;
        } else if (CheckStepDirection(step, true)) {
            curMainStart++;
        }
        if (info_.gridMatrix_.find(curMainStart) == info_.gridMatrix_.end()) {
            break;
        }
        main = info_.gridMatrix_.find(curMainStart);
    }
    return nullptr;
}

bool GridFocus::CheckStepDirection(FocusStep step, bool isNext)
{
    if (info_.axis_ == Axis::VERTICAL) {
        if (isNext) {
            return step == FocusStep::LEFT_END || step == FocusStep::RIGHT;
        } else {
            return step == FocusStep::RIGHT_END || step == FocusStep::LEFT;
        }
    } else {
        if (isNext) {
            return step == FocusStep::UP_END || step == FocusStep::DOWN;
        } else {
            return step == FocusStep::DOWN_END || step == FocusStep::UP;
        }
    }
}

WeakPtr<FocusHub> GridFocus::SearchFocusableChildInCross(
    int32_t tarMainIndex, int32_t tarCrossIndex, int32_t maxCrossCount, int32_t curMainIndex, int32_t curCrossIndex)
{
    bool isDirectionLeft = true;
    auto indexLeft = tarCrossIndex;
    auto indexRight = tarCrossIndex;
    if (curMainIndex == tarMainIndex) {
        // Search on the same main index. Do not need search on both left and right side.
        if (tarCrossIndex > curCrossIndex) {
            // Only search on the right side.
            indexLeft = -1;
        } else if (tarCrossIndex < curCrossIndex) {
            // Only search on the left side.
            indexRight = maxCrossCount;
        } else {
            TAG_LOGW(AceLogTag::ACE_GRID, "Invalid search index: (%{public}d,%{public}d). It's same as current.",
                tarMainIndex, tarCrossIndex);
            return nullptr;
        }
    }
    while (indexLeft >= 0 || indexRight < maxCrossCount) {
        int32_t curIndex = indexLeft;
        if (indexLeft < 0) {
            curIndex = indexRight++;
        } else if (indexRight >= maxCrossCount) {
            curIndex = indexLeft--;
        } else {
            curIndex = isDirectionLeft ? indexLeft-- : indexRight++;
            isDirectionLeft = !isDirectionLeft;
        }
        auto weakChild = GetChildFocusNodeByIndex(tarMainIndex, curIndex);
        auto child = weakChild.Upgrade();
        if (child && child->IsFocusable()) {
            TAG_LOGI(AceLogTag::ACE_GRID, "Found child. Index: %{public}d,%{public}d", tarMainIndex, curIndex);
            return weakChild;
        }
    }
    return nullptr;
}

WeakPtr<FocusHub> GridFocus::SearchIrregularFocusableChild(int32_t tarMainIndex, int32_t tarCrossIndex)
{
    double minDistance = std::numeric_limits<double>::max();
    int32_t minMainIndex = std::numeric_limits<int32_t>::max();
    int32_t minCrossIndex = std::numeric_limits<int32_t>::max();
    int32_t maxAreaInMainShadow = -1;
    int32_t maxAreaInCrossShadow = -1;
    WeakPtr<FocusHub> targetFocusHubWeak;

    auto gridFrame = grid_.GetHost();
    CHECK_NULL_RETURN(gridFrame, nullptr);
    auto gridFocus = gridFrame->GetFocusHub();
    CHECK_NULL_RETURN(gridFocus, nullptr);
    std::list<RefPtr<FocusHub>> childFocusList;
    gridFocus->FlushChildrenFocusHub(childFocusList);
    for (const auto& childFocus : childFocusList) {
        if (!childFocus->IsFocusable()) {
            continue;
        }
        auto childFrame = childFocus->GetFrameNode();
        if (!childFrame) {
            continue;
        }
        auto childPattern = childFrame->GetPattern<GridItemPattern>();
        if (!childPattern) {
            continue;
        }
        auto childItemProperty = childFrame->GetLayoutProperty<GridItemLayoutProperty>();
        if (!childItemProperty) {
            continue;
        }
        auto irregularInfo = childPattern->GetIrregularItemInfo();
        bool hasIrregularItemInfo = irregularInfo.has_value();

        auto childMainIndex = childItemProperty->GetMainIndex().value_or(-1);
        auto childCrossIndex = childItemProperty->GetCrossIndex().value_or(-1);
        auto childMainStart =
            hasIrregularItemInfo ? irregularInfo.value().mainStart : childItemProperty->GetMainStart(info_.axis_);
        auto childMainEnd =
            hasIrregularItemInfo ? irregularInfo.value().mainEnd : childItemProperty->GetMainEnd(info_.axis_);
        auto chidCrossStart =
            hasIrregularItemInfo ? irregularInfo.value().crossStart : childItemProperty->GetCrossStart(info_.axis_);
        auto chidCrossEnd =
            hasIrregularItemInfo ? irregularInfo.value().crossEnd : childItemProperty->GetCrossEnd(info_.axis_);
        auto childCrossSpan =
            hasIrregularItemInfo ? irregularInfo.value().crossSpan : childItemProperty->GetCrossSpan(info_.axis_);
        auto childMainSpan =
            hasIrregularItemInfo ? irregularInfo.value().mainSpan : childItemProperty->GetMainSpan(info_.axis_);

        GridItemIndexInfo childInfo;
        childInfo.mainIndex = childMainIndex;
        childInfo.crossIndex = childCrossIndex;
        childInfo.mainStart = childMainStart;
        childInfo.mainEnd = childMainEnd;
        childInfo.crossStart = chidCrossStart;
        childInfo.crossEnd = chidCrossEnd;

        if (childMainIndex < 0 || childCrossIndex < 0) {
            continue;
        }

        if ((isLeftStep_ && ((childCrossIndex == tarCrossIndex && childCrossSpan == 1) ||
                                (chidCrossEnd >= 0 && chidCrossEnd == tarCrossIndex))) ||
            (isRightStep_ && childCrossIndex == tarCrossIndex)) {
            double nearestDistance = GetNearestDistanceFromChildToCurFocusItemInMainAxis(tarCrossIndex, childInfo);
            int32_t intersectAreaSize = CalcIntersectAreaInTargetDirectionShadow(childInfo, true);
            if (LessNotEqual(nearestDistance, minDistance) ||
                (NearEqual(nearestDistance, minDistance) && intersectAreaSize > maxAreaInCrossShadow) ||
                (NearEqual(nearestDistance, minDistance) && intersectAreaSize == maxAreaInCrossShadow &&
                    childMainIndex < minMainIndex)) {
                minDistance = nearestDistance;
                maxAreaInCrossShadow = intersectAreaSize;
                minMainIndex = childMainIndex;
                targetFocusHubWeak = AceType::WeakClaim(AceType::RawPtr(childFocus));
            }
        } else if ((isUpStep_ && childMainIndex == tarMainIndex) ||
                   (isDownStep_ && ((childMainIndex == tarMainIndex && childMainSpan == 1) ||
                                       (childMainStart >= 0 && childMainStart == tarMainIndex)))) {
            double nearestDistance = GetNearestDistanceFromChildToCurFocusItemInCrossAxis(tarMainIndex, childInfo);
            int32_t intersectAreaSize = CalcIntersectAreaInTargetDirectionShadow(childInfo, false);
            if (LessNotEqual(nearestDistance, minDistance) ||
                (NearEqual(nearestDistance, minDistance) && intersectAreaSize > maxAreaInMainShadow) ||
                (NearEqual(nearestDistance, minDistance) && intersectAreaSize == maxAreaInMainShadow &&
                    childCrossIndex < minCrossIndex)) {
                minDistance = nearestDistance;
                minCrossIndex = childCrossIndex;
                maxAreaInMainShadow = intersectAreaSize;
                targetFocusHubWeak = AceType::WeakClaim(AceType::RawPtr(childFocus));
            }
        } else if ((isLeftEndStep_ || isRightEndStep_) &&
                   ((tarMainIndex == childMainIndex && tarCrossIndex == childCrossIndex) ||
                       (childMainStart >= 0 && childMainStart <= tarMainIndex && tarMainIndex <= childMainIndex &&
                           tarCrossIndex == childCrossIndex))) {
            targetFocusHubWeak = AceType::WeakClaim(AceType::RawPtr(childFocus));
        }
    }
    ResetAllDirectionsStep();
    return targetFocusHubWeak;
}

int32_t GridFocus::CalcIntersectAreaInTargetDirectionShadow(GridItemIndexInfo itemIndexInfo, bool isFindInMainAxis)
{
    int32_t curFocusLeftTopX = -1;
    int32_t curFocusLeftTopY = -1;
    int32_t curFocusRightBottonX = -1;
    int32_t curFocusRightBottonY = -1;

    if (isFindInMainAxis) {
        curFocusLeftTopX =
            curFocusIndexInfo_.mainStart == -1 ? curFocusIndexInfo_.mainIndex : curFocusIndexInfo_.mainStart;
        curFocusLeftTopY = 0;
        curFocusRightBottonX =
            curFocusIndexInfo_.mainEnd == -1 ? curFocusIndexInfo_.mainIndex : curFocusIndexInfo_.mainEnd;
        curFocusRightBottonY = info_.crossCount_;
    } else {
        curFocusLeftTopX = info_.startMainLineIndex_;
        curFocusLeftTopY =
            curFocusIndexInfo_.crossStart == -1 ? curFocusIndexInfo_.crossIndex : curFocusIndexInfo_.crossStart;
        curFocusRightBottonX = info_.endMainLineIndex_;
        curFocusRightBottonY =
            curFocusIndexInfo_.crossEnd == -1 ? curFocusIndexInfo_.crossIndex : curFocusIndexInfo_.crossEnd;
    }
    int32_t childLeftTopX = itemIndexInfo.mainStart == -1 ? itemIndexInfo.mainIndex : itemIndexInfo.mainStart;
    int32_t childLeftTopY = itemIndexInfo.crossStart == -1 ? itemIndexInfo.crossIndex : itemIndexInfo.crossStart;
    int32_t childRightBottonX = itemIndexInfo.mainEnd == -1 ? itemIndexInfo.mainIndex : itemIndexInfo.mainEnd;
    int32_t childRightBottonY = itemIndexInfo.crossEnd == -1 ? itemIndexInfo.crossIndex : itemIndexInfo.crossEnd;

    int32_t intersectAreaLeftTopX = std::max(curFocusLeftTopX, childLeftTopX);
    int32_t intersectAreaLeftTopY = std::max(curFocusLeftTopY, childLeftTopY);
    int32_t intersectAreaRightBottonX = std::min(curFocusRightBottonX, childRightBottonX);
    int32_t intersectAreaRightBottonY = std::min(curFocusRightBottonY, childRightBottonY);

    int32_t intersectWidth = intersectAreaRightBottonX - intersectAreaLeftTopX + 1;
    int32_t intersectHeight = intersectAreaRightBottonY - intersectAreaLeftTopY + 1;

    return (intersectWidth < 0 || intersectHeight < 0) ? -1 : intersectWidth * intersectHeight;
}

namespace {
double CalcCoordinatesDistance(double curFocusMain, double curFocusCross, double childMain, double childCross)
{
    return std::sqrt(std::pow((curFocusMain - childMain), 2) + std::pow((curFocusCross - childCross), 2));
}
} // namespace

double GridFocus::GetNearestDistanceFromChildToCurFocusItemInMainAxis(
    int32_t targetIndex, GridItemIndexInfo itemIndexInfo)
{
    double minDistance = std::numeric_limits<double>::max();
    auto mainAxisIndex =
        curFocusIndexInfo_.mainStart == -1 ? curFocusIndexInfo_.mainIndex : curFocusIndexInfo_.mainStart;
    auto mainAxisEndIndex =
        curFocusIndexInfo_.mainEnd == -1 ? curFocusIndexInfo_.mainIndex : curFocusIndexInfo_.mainEnd;
    for (int32_t i = mainAxisIndex; i <= mainAxisEndIndex; i++) {
        double childMainIndexDistance =
            CalcCoordinatesDistance(i, curFocusIndexInfo_.crossIndex, itemIndexInfo.mainIndex, targetIndex);
        double childMainStartDistance =
            itemIndexInfo.mainStart == -1
                ? std::numeric_limits<double>::max()
                : CalcCoordinatesDistance(i, curFocusIndexInfo_.crossIndex, itemIndexInfo.mainStart, targetIndex);
        double distance = std::min(childMainIndexDistance, childMainStartDistance);
        if (LessNotEqual(distance, minDistance)) {
            minDistance = distance;
        }
    }
    return minDistance;
}

double GridFocus::GetNearestDistanceFromChildToCurFocusItemInCrossAxis(
    int32_t targetIndex, GridItemIndexInfo itemIndexInfo)
{
    double minDistance = std::numeric_limits<double>::max();
    auto crossAxisIndex =
        curFocusIndexInfo_.crossStart == -1 ? curFocusIndexInfo_.crossIndex : curFocusIndexInfo_.crossStart;
    auto crossAxisEndIndex =
        curFocusIndexInfo_.crossEnd == -1 ? curFocusIndexInfo_.crossIndex : curFocusIndexInfo_.crossEnd;
    for (int32_t i = crossAxisIndex; i <= crossAxisEndIndex; i++) {
        double childCrossIndexDistance =
            CalcCoordinatesDistance(curFocusIndexInfo_.mainIndex, i, targetIndex, itemIndexInfo.crossIndex);
        double childCrossEndDistance =
            itemIndexInfo.crossEnd == -1
                ? std::numeric_limits<double>::max()
                : CalcCoordinatesDistance(curFocusIndexInfo_.mainIndex, i, targetIndex, itemIndexInfo.crossEnd);
        double distance = std::min(childCrossIndexDistance, childCrossEndDistance);
        if (LessNotEqual(distance, minDistance)) {
            minDistance = distance;
        }
    }
    return minDistance;
}

void GridFocus::ResetAllDirectionsStep()
{
    isLeftStep_ = false;
    isRightStep_ = false;
    isUpStep_ = false;
    isDownStep_ = false;
    isLeftEndStep_ = false;
    isRightEndStep_ = false;
}

WeakPtr<FocusHub> GridFocus::GetChildFocusNodeByIndex(int32_t tarMainIndex, int32_t tarCrossIndex, int32_t tarIndex)
{
    auto gridFrame = grid_.GetHost();
    CHECK_NULL_RETURN(gridFrame, nullptr);
    auto gridFocus = gridFrame->GetFocusHub();
    CHECK_NULL_RETURN(gridFocus, nullptr);
    std::list<RefPtr<FocusHub>> childFocusList;
    gridFocus->FlushChildrenFocusHub(childFocusList);
    for (const auto& childFocus : childFocusList) {
        auto childFrame = childFocus->GetFrameNode();
        if (!childFrame) {
            continue;
        }
        auto childPattern = childFrame->GetPattern();
        if (!childPattern) {
            continue;
        }
        auto childItemPattern = AceType::DynamicCast<GridItemPattern>(childPattern);
        if (!childItemPattern) {
            continue;
        }
        auto childItemProperty = childItemPattern->GetLayoutProperty<GridItemLayoutProperty>();
        if (!childItemProperty) {
            continue;
        }
        auto curMainIndex = childItemProperty->GetMainIndex().value_or(-1);
        auto curCrossIndex = childItemProperty->GetCrossIndex().value_or(-1);
        if (tarIndex < 0) {
            auto curMainSpan = childItemProperty->GetMainSpan(info_.axis_);
            auto curCrossSpan = childItemProperty->GetCrossSpan(info_.axis_);
            if (curMainIndex <= tarMainIndex && curMainIndex + curMainSpan > tarMainIndex &&
                curCrossIndex <= tarCrossIndex && curCrossIndex + curCrossSpan > tarCrossIndex) {
                return AceType::WeakClaim(AceType::RawPtr(childFocus));
            }
        } else {
            auto row = info_.gridMatrix_.find(curMainIndex);
            if (row == info_.gridMatrix_.end()) {
                TAG_LOGW(AceLogTag::ACE_GRID, "Can not find target main index: %{public}d", curMainIndex);
                continue;
            }
            auto cell = row->second.find(curCrossIndex);
            if (cell == row->second.end()) {
                TAG_LOGW(AceLogTag::ACE_GRID, "Can not find target cross index: %{public}d", curCrossIndex);
                continue;
            }
            if (cell->second == tarIndex) {
                return AceType::WeakClaim(AceType::RawPtr(childFocus));
            }
        }
    }
    return nullptr;
}

std::unordered_set<int32_t> GridFocus::GetFocusableChildCrossIndexesAt(int32_t tarMainIndex)
{
    std::unordered_set<int32_t> result;
    auto gridFrame = grid_.GetHost();
    CHECK_NULL_RETURN(gridFrame, result);
    auto gridFocus = gridFrame->GetFocusHub();
    CHECK_NULL_RETURN(gridFocus, result);
    std::list<RefPtr<FocusHub>> childFocusList;
    gridFocus->FlushChildrenFocusHub(childFocusList);
    for (const auto& childFocus : childFocusList) {
        if (!childFocus->IsFocusable()) {
            continue;
        }
        auto childFrame = childFocus->GetFrameNode();
        if (!childFrame) {
            continue;
        }
        auto childPattern = childFrame->GetPattern();
        if (!childPattern) {
            continue;
        }
        auto childItemPattern = AceType::DynamicCast<GridItemPattern>(childPattern);
        if (!childItemPattern) {
            continue;
        }
        auto childItemProperty = childItemPattern->GetLayoutProperty<GridItemLayoutProperty>();
        if (!childItemProperty) {
            continue;
        }
        auto irregularInfo = childItemPattern->GetIrregularItemInfo();
        bool hasIrregularItemInfo = irregularInfo.has_value();
        auto curMainIndex = childItemProperty->GetMainIndex().value_or(-1);
        auto curCrossIndex = childItemProperty->GetCrossIndex().value_or(-1);
        auto curMainStart =
            hasIrregularItemInfo ? irregularInfo.value().mainStart : childItemProperty->GetMainStart(info_.axis_);
        auto curMainEnd =
            hasIrregularItemInfo ? irregularInfo.value().mainEnd : childItemProperty->GetMainEnd(info_.axis_);
        if ((curMainIndex == tarMainIndex) ||
            (curMainStart >= 0 && curMainStart <= tarMainIndex && tarMainIndex <= curMainEnd)) {
            result.emplace(curCrossIndex);
        }
    }
    std::string output;
    for (const auto& index : result) {
        output += std::to_string(index);
    }
    return result;
}

int32_t GridFocus::GetFocusNodeIndex(const RefPtr<FocusHub>& focusNode)
{
    auto tarFrame = focusNode->GetFrameNode();
    CHECK_NULL_RETURN(tarFrame, -1);
    auto tarPattern = tarFrame->GetPattern();
    CHECK_NULL_RETURN(tarPattern, -1);
    auto tarItemPattern = AceType::DynamicCast<GridItemPattern>(tarPattern);
    CHECK_NULL_RETURN(tarItemPattern, -1);
    auto tarItemProperty = tarItemPattern->GetLayoutProperty<GridItemLayoutProperty>();
    CHECK_NULL_RETURN(tarItemProperty, -1);
    auto tarMainIndex = tarItemProperty->GetMainIndex().value_or(-1);
    auto tarCrossIndex = tarItemProperty->GetCrossIndex().value_or(-1);
    auto it = info_.gridMatrix_.find(tarMainIndex);
    if (it == info_.gridMatrix_.end()) {
        TAG_LOGW(AceLogTag::ACE_GRID, "Can not find target main index: %{public}d", tarMainIndex);
        if (tarMainIndex == 0) {
            return 0;
        }
        return info_.GetChildrenCount() - 1;
    }
    auto cell = it->second.find(tarCrossIndex);
    if (cell == it->second.end()) {
        TAG_LOGW(AceLogTag::ACE_GRID, "Can not find target cross index: %{public}d", tarCrossIndex);
        if (tarMainIndex == 0) {
            return 0;
        }
        return info_.GetChildrenCount() - 1;
    }
    return cell->second;
}

void GridFocus::ProcessFocusEvent(const KeyEvent& event, bool indexChanged)
{
    auto host = grid_.GetHost();
    CHECK_NULL_VOID(host);
    auto focusHub = host->GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    CHECK_NULL_VOID(focusHub->IsCurrentFocus());
    if (needTriggerFocus_) {
        if (triggerFocus_) {
            needTriggerFocus_ = false;
            triggerFocus_ = false;
            focusHub->GetNextFocusByStep(event);
        } else {
            if (!focusIndex_.has_value()) {
                needTriggerFocus_ = false;
                return;
            }
            triggerFocus_ = true;
            auto child = host->GetOrCreateChildByIndex(focusIndex_.value());
            CHECK_NULL_VOID(child);
            auto childNode = child->GetHostNode();
            auto childFocusHub = childNode->GetFocusHub();
            if (childFocusHub && !childFocusHub->IsCurrentFocus()) {
                childFocusHub->RequestFocusImmediately();
            }
            host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        }
        return;
    }
    if (indexChanged && focusIndex_.has_value()) {
        FireFocus();
    }
}

void GridFocus::FireFocus()
{
    auto host = grid_.GetHost();
    CHECK_NULL_VOID(host);
    auto* pipeline = grid_.GetContext();
    CHECK_NULL_VOID(pipeline);
    auto focusHub = host->GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    CHECK_NULL_VOID(focusHub->IsCurrentFocus());
    CHECK_NULL_VOID(focusIndex_.has_value());
    if (IsInViewport(focusIndex_.value(), true)) {
        auto child = host->GetChildByIndex(focusIndex_.value());
        CHECK_NULL_VOID(child);
        auto childNode = child->GetHostNode();
        CHECK_NULL_VOID(childNode);
        auto childFocusHub = childNode->GetFocusHub();
        CHECK_NULL_VOID(childFocusHub);
        if (!childFocusHub->IsCurrentFocus()) {
            focusHub->SetFocusDependence(FocusDependence::AUTO);
            childFocusHub->RequestFocusImmediately();
            TAG_LOGI(
                AceLogTag::ACE_GRID, "GridItem [%{public}d] scroll into viewport, Requests focus", focusIndex_.value());
        }
    } else {
        auto childFocusHub = focusHub->GetLastWeakFocusNode().Upgrade();
        CHECK_NULL_VOID(childFocusHub);
        if (childFocusHub->IsCurrentFocus()) {
            focusHub->LostChildFocusToSelf();
        }
    }
}

bool GridFocus::ScrollToLastFocusIndex(KeyCode keyCode)
{
    auto* pipeline = grid_.GetContext();
    CHECK_NULL_RETURN(pipeline, false);
    CHECK_NULL_RETURN(pipeline->GetIsFocusActive(), false);
    auto host = grid_.GetHost();
    CHECK_NULL_RETURN(host, false);
    auto focusHub = host->GetFocusHub();
    CHECK_NULL_RETURN(focusHub, false);
    CHECK_NULL_RETURN(focusHub->IsCurrentFocus(), false);
    CHECK_NULL_RETURN(focusIndex_.has_value(), false);
    auto focusIndex = focusIndex_.value();
    if (!IsInViewport(focusIndex, false)) {
        grid_.StopAnimate();
        needTriggerFocus_ = true;
        
        // If focused item is above viewport and the current keyCode type is UP, scroll forward one more line
        if (focusIndex < info_.startIndex_ && keyCode == KeyCode::KEY_DPAD_UP && focusIndex - info_.crossCount_ >= 0) {
            grid_.UpdateStartIndex(focusIndex - info_.crossCount_);
            // If focused item is below viewport and the current keyCode type is DOWN, scroll backward one more line
        } else if (focusIndex > info_.endIndex_ && keyCode == KeyCode::KEY_DPAD_DOWN &&
                   focusIndex + info_.crossCount_ < info_.GetChildrenCount()) {
            grid_.UpdateStartIndex(focusIndex + info_.crossCount_);
        } else {
            grid_.UpdateStartIndex(focusIndex);
        }
        return true;
    }
    return false;
}

void GridFocus::ScrollToFocusNode(const WeakPtr<FocusHub>& focusNode)
{
    grid_.StopAnimate();
    auto nextFocus = focusNode.Upgrade();
    CHECK_NULL_VOID(nextFocus);
    grid_.UpdateStartIndex(GetFocusNodeIndex(nextFocus));
}

bool GridFocus::IsInViewport(int32_t index, bool needCheckCache) const
{
    auto host = grid_.GetHost();
    CHECK_NULL_RETURN(host, true);
    auto gridLayoutProperty = host->GetLayoutProperty<GridLayoutProperty>();
    CHECK_NULL_RETURN(gridLayoutProperty, true);
    int32_t cacheCount = gridLayoutProperty->GetCachedCountValue(info_.defCachedCount_) * info_.crossCount_;
    bool showCachedItems = gridLayoutProperty->GetShowCachedItemsValue(false);
    if (needCheckCache && showCachedItems) {
        return index >= info_.startIndex_ - cacheCount && index <= info_.endIndex_ + cacheCount;
    }
    return index >= info_.startIndex_ && index <= info_.endIndex_;
}
} // namespace OHOS::Ace::NG