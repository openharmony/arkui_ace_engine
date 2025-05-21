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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_GRID_GRID_FOCUS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_GRID_GRID_FOCUS_H

#include <unordered_set>

#include "base/utils/noncopyable.h"
#include "core/components_ng/event/focus_hub.h"
#include "core/components_ng/pattern/grid/grid_layout_info.h"

namespace OHOS::Ace::NG {
struct GridItemIndexInfo {
    int32_t mainIndex = -1;
    int32_t crossIndex = -1;
    int32_t mainSpan = -1;
    int32_t crossSpan = -1;
    int32_t mainStart = -1;
    int32_t mainEnd = -1;
    int32_t crossStart = -1;
    int32_t crossEnd = -1;
};

class GridPattern;

// helper class to handle focus-related tasks for Grid
class GridFocus {
public:
    GridFocus(GridPattern& grid, const GridLayoutInfo& info) : grid_(grid), info_(info) {}
    ~GridFocus() = default;

    int32_t GetFocusNodeIndex(const RefPtr<FocusHub>& focusNode);

    void ProcessFocusEvent(const KeyEvent& event, bool indexChanged);

    bool ScrollToLastFocusIndex(KeyCode keyCode);
    WeakPtr<FocusHub> GetChildFocusNodeByIndex(int32_t tarMainIndex, int32_t tarCrossIndex, int32_t tarIndex = -1);

    void HandleFocusEvent(const WeakPtr<FocusHub>& child);

    WeakPtr<FocusHub> GetNextFocusSimplified(FocusStep step, const RefPtr<FocusHub>& current); // focus algo rewritten
    WeakPtr<FocusHub> GetNextFocusNode(
        FocusStep step, const WeakPtr<FocusHub>& currentFocusNode, bool isMainSkip = false);
    bool GetCurrentFocusInfo(FocusStep step, const WeakPtr<FocusHub>& currentFocusNode);
    WeakPtr<FocusHub> HandleFocusSteps(
        FocusStep step, const WeakPtr<FocusHub>& currentFocusNode, std::pair<FocusStep, FocusStep> focusSteps);

    void ResetFocusIndex()
    {
        focusIndex_.reset();
    }

    void SetFocusIndex(int32_t index)
    {
        focusIndex_ = index;
    }

private:
    void ScrollToFocusNode(const WeakPtr<FocusHub>& focusNode);
    void FireFocus();
    std::pair<int32_t, int32_t> GetNextIndexByStep(
        int32_t curMainIndex, int32_t curCrossIndex, int32_t curMainSpan, int32_t curCrossSpan, FocusStep step);
    WeakPtr<FocusHub> SearchBigItemFocusableChildInCross(
        int32_t tarMainIndex, int32_t tarCrossIndex, FocusStep step = FocusStep::NONE, bool isMainSkip = false);
    bool CheckIsCrossDirectionFocus(FocusStep step);
    bool CheckStepDirection(FocusStep step, bool isNext);
    WeakPtr<FocusHub> SearchFocusableChildInCross(int32_t tarMainIndex, int32_t tarCrossIndex, int32_t maxCrossCount,
        int32_t curMainIndex = -1, int32_t curCrossIndex = -1);
    WeakPtr<FocusHub> SearchIrregularFocusableChild(int32_t tarMainIndex, int32_t tarCrossIndex);
    std::unordered_set<int32_t> GetFocusableChildCrossIndexesAt(int32_t tarMainIndex);
    std::pair<bool, bool> IsFirstOrLastFocusableChild(int32_t curMainIndex, int32_t curCrossIndex);
    std::pair<FocusStep, FocusStep> GetFocusSteps(int32_t curMainIndex, int32_t curCrossIndex, FocusStep step);
    FocusWrapMode GetFocusWrapMode();
    int32_t GetIndexByFocusHub(const WeakPtr<FocusHub>& focusNode);
    void ResetAllDirectionsStep();
    int32_t CalcIntersectAreaInTargetDirectionShadow(GridItemIndexInfo itemIndexInfo, bool isFindInMainAxis);
    double GetNearestDistanceFromChildToCurFocusItemInMainAxis(int32_t targetIndex, GridItemIndexInfo itemIndexInfo);
    double GetNearestDistanceFromChildToCurFocusItemInCrossAxis(int32_t targetIndex, GridItemIndexInfo itemIndexInfo);
    bool IsInViewport(int32_t index, bool needCheckCache) const;

    std::optional<int32_t> focusIndex_;
    GridItemIndexInfo curFocusIndexInfo_;

    GridPattern& grid_;
    const GridLayoutInfo& info_;

    bool isTab_ = false;
    bool isLeftStep_ = false;
    bool isRightStep_ = false;
    bool isUpStep_ = false;
    bool isDownStep_ = false;
    bool isLeftEndStep_ = false;
    bool isRightEndStep_ = false;
    bool needTriggerFocus_ = false;
    bool triggerFocus_ = false;

    ACE_DISALLOW_COPY_AND_MOVE(GridFocus);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_GRID_GRID_PATTERN_H
