/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_IRREGULAR_CHILD_LOADER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_IRREGULAR_CHILD_LOADER_H

#include "base/utils/noncopyable.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/grid/grid_layout_info.h"
#include "core/components_ng/pattern/grid/grid_layout_options.h"

namespace OHOS::Ace::NG {
class GridIrregularFiller {
    ACE_DISALLOW_COPY_AND_MOVE(GridIrregularFiller);

public:
    GridIrregularFiller(GridLayoutInfo* info, LayoutWrapper* wrapper);
    ~GridIrregularFiller() = default;

    struct FillParameters {
        std::vector<float> crossLens;
        float targetLen = 0.0f;
        float crossGap = 0.0f;
        float mainGap = 0.0f;
    };

    float Fill(const FillParameters& params);

private:
    void FillOne();
    void UpdateLength(int32_t prevRow, float mainGap);
    void MeasureNewItem(const FillParameters& params, int32_t col);

    void InitPos();

    bool FindNextItem(int32_t target);
    bool AdvancePos();

    inline bool IsFull(float targetLen);
    inline bool ItemCanFit(const decltype(GridLayoutInfo::gridMatrix_)::iterator& it, int32_t itemWidth);

    GridItemSize GetItemSize(int32_t idx);

    float length_ = 0.0f;

    int32_t posY_ = 0;
    int32_t posX_ = -1;

    GridLayoutInfo* info_;
    LayoutWrapper* wrapper_;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_IRREGULAR_CHILD_LOADER_H
