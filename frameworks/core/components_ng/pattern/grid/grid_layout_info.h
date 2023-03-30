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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_LAYOUT_INFO_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_LAYOUT_INFO_H

#include <map>

#include "base/geometry/axis.h"

namespace OHOS::Ace::NG {

// Try not to add more variables in [GridLayoutInfo] because the more state variables, the more problematic and the
// harder it is to maintain
struct GridLayoutInfo {
    float GetTotalHeightOfItemsInView(float mainGap)
    {
        float lengthOfItemsInViewport = 0.0;
        for (auto i = startMainLineIndex_; i <= endMainLineIndex_; i++) {
            lengthOfItemsInViewport += (lineHeightMap_[i] + mainGap);
        }
        return lengthOfItemsInViewport - mainGap;
    }

    void UpdateStartIndexByStartLine()
    {
        auto startLine = gridMatrix_.find(startMainLineIndex_);
        if (startLine == gridMatrix_.end()) {
            return;
        }
        if (startLine->second.empty()) {
            return;
        }
        startIndex_ = startLine->second.begin()->second;
    }

    void UpdateEndLine(float mainSize, float mainGap)
    {
        if (mainSize >= lastMainSize_) {
            return;
        }
        for (auto i = startMainLineIndex_; i < endMainLineIndex_; ++i) {
            mainSize -= (lineHeightMap_[i] + mainGap);
            if (LessOrEqual(mainSize + mainGap, 0)) {
                endMainLineIndex_ = i;
                break;
            }
        }
    }
    float GetAverageLineHeight()
    {
        float totalHeight = 0;
        int32_t totalRow = 0;
        for (const auto& record : lineHeightMap_) {
            if (record.second > 0) {
                totalRow++;
                totalHeight += record.second;
            }
        }
        return totalRow > 0 ? totalHeight / totalRow : 0;
    }

    void ResetPositionFlags()
    {
        reachEnd_ = false;
        reachStart_ = false;
        offsetEnd_ = false;
    }

    Axis axis_ = Axis::VERTICAL;

    float currentOffset_ = 0.0f;
    float prevOffset_ = 0.0f;
    float lastMainSize_ = 0.0f;

    // index of first and last GridItem in viewport
    int32_t startIndex_ = 0;
    int32_t endIndex_ = -1;

    // index of first row and last row in viewport (assuming it's a vertical Grid)
    int32_t startMainLineIndex_ = 0;
    int32_t endMainLineIndex_ = 0;

    int32_t jumpIndex_ = -1;
    int32_t crossCount_ = 0;
    int32_t childrenCount_ = 0;

    bool reachEnd_ = false;
    bool reachStart_ = false;

    bool offsetEnd_ = false;

    // Map structure: [mainIndex, [crossIndex, index]],
    // when vertical, mainIndex is rowIndex and crossIndex is columnIndex.
    std::map<int32_t, std::map<int32_t, int32_t>> gridMatrix_;
    // in vertical grid, this map is like: [rowIndex: rowHeight]
    std::map<int32_t, float> lineHeightMap_;

    // Grid has GridItem whose columnEnd - columnStart > 0
    bool hasBigItem_;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_LAYOUT_ALGORITHM_H