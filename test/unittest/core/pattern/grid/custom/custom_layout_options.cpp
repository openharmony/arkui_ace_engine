/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "custom_layout_options.h"

#include <cmath>

namespace OHOS::Ace::NG {
GridLayoutOptions GetRegularDemoOptions(int32_t crossCount, float itemMainSize)
{
    GridLayoutOptions options;
    auto onGetStartIndexByOffset = [crossCount, itemMainSize](float offset) -> GridStartLineInfo {
        if (offset < 0.0f) {
            return {
                .startIndex = 0,
                .startLine = 0,
                .startOffset = 0 - offset,
                .totalOffset = offset
            };
        }
        int32_t line = offset / static_cast<int32_t>(itemMainSize);
        float startOffset = std::fmod(offset, itemMainSize);
        return {
            .startIndex = line * crossCount,
            .startLine = line,
            .startOffset = 0 - startOffset,
            .totalOffset = offset
        };
    };
    options.getStartIndexByOffset = std::move(onGetStartIndexByOffset);

    auto onGetStartIndexByIndex = [crossCount, itemMainSize](int32_t targetIndex) -> GridStartLineInfo {
        int32_t line = targetIndex / crossCount;
        return {
            .startIndex = line * crossCount,
            .startLine = line,
            .startOffset = 0.0f,
            .totalOffset = line * itemMainSize
        };
    };
    options.getStartIndexByIndex = std::move(onGetStartIndexByIndex);
    return options;
}

GridLayoutOptions Get3LinesIrregularDemoOptions(int32_t childrenCount, float itemMainSize)
{
    GridLayoutOptions options;
    int32_t crossCount = 3;

    for (int32_t i = 0; i < childrenCount; i++) {
        if (i % crossCount == 0) {
            options.irregularIndexes.emplace(i);
        }
    }

    auto onGetIrregularSizeByIndex = [](int32_t index) -> GridItemSize {
        return {
            .rows = 2, .columns = 2
        };
    };
    options.getSizeByIndex = std::move(onGetIrregularSizeByIndex);
    auto onGetStartIndexByOffset = [crossCount, itemMainSize](float offset) -> GridStartLineInfo {
        if (offset < 0.0f) {
            return {
                .startIndex = 0,
                .startLine = 0,
                .startOffset = 0 - offset,
                .totalOffset = offset
            };
        }
        int32_t line = offset / static_cast<int32_t>(itemMainSize * 2);
        float startOffset = std::fmod(offset, itemMainSize * 2);
        return {
            .startIndex = line * crossCount,
            .startLine = line * 2,
            .startOffset = 0 - startOffset,
            .totalOffset = offset
        };
    };
    options.getStartIndexByOffset = std::move(onGetStartIndexByOffset);

    auto onGetStartIndexByIndex = [crossCount, itemMainSize](int32_t targetIndex) -> GridStartLineInfo {
        int32_t line = targetIndex / crossCount;
        float offset = targetIndex % crossCount == 2 ? (-itemMainSize) : 0.f;
        return {
            .startIndex = line * crossCount,
            .startLine = line * 2,
            .startOffset = offset,
            .totalOffset = line * 2 * itemMainSize - offset
        };
    };
    options.getStartIndexByIndex = std::move(onGetStartIndexByIndex);
    return options;
}
} // namespace OHOS::Ace::NG