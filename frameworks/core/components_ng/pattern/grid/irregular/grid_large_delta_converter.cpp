/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/grid/irregular/grid_large_delta_converter.h"

#include "core/components_ng/pattern/grid/irregular/grid_irregular_filler.h"

namespace OHOS::Ace::NG {

namespace {
// Local function to add line height
void AddLineHeight(float& height, int32_t curLine, int32_t startLine, const std::map<int32_t, float>& lineHeights)
{
    auto iter = lineHeights.find(curLine);
    if (iter != lineHeights.end()) {
        height += iter->second;
    } else {
        // estimation
        height += height / std::abs(curLine - startLine);
    }
}
} // namespace

int32_t GridLargeDeltaConverter::SkipLinesForward()
{
    int32_t line = info_.startMainLineIndex_;
    float height = 0.0f;
    GridIrregularFiller filler(&info_, wrapper_);
    int32_t lastIdx = info_.endIndex_;
    while (LessNotEqual(height, -info_.currentOffset_)) {
        AddLineHeight(height, line, info_.startMainLineIndex_, info_.lineHeightMap_);
        lastIdx = filler.FillMatrixByLine(line, line + 1);
        if (lastIdx == info_.childrenCount_ - 1) {
            break;
        }
        ++line;
    }
    return lastIdx;
}

int32_t GridLargeDeltaConverter::SkipLinesBackward() const
{
    const auto& info = info_;
    float height = info.GetHeightInRange(info.startMainLineIndex_, info.endMainLineIndex_ + 1, 0.0f);

    float target = info.currentOffset_ + height;
    int32_t line = info.startMainLineIndex_;
    while (LessNotEqual(height, target) && line > 0) {
        AddLineHeight(height, --line, info.endMainLineIndex_, info.lineHeightMap_);
    }
    return std::max(0, info.FindEndIdx(line).itemIdx);
}

int32_t GridLargeDeltaConverter::Convert(float delta)
{
    if (Negative(delta)) {
        return SkipLinesForward();
    }
    return SkipLinesBackward();
}
} // namespace OHOS::Ace::NG
