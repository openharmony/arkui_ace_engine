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

#pragma once

#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/grid/grid_layout_info.h"
#include "core/components_ng/pattern/scrollable/large_delta_converter.h"

namespace OHOS::Ace::NG {

class GridLargeDeltaConverter : public LargeDeltaConverter {
public:
    GridLargeDeltaConverter(GridLayoutInfo& info, LayoutWrapper* wrapper) : info_(info), wrapper_(wrapper) {}

    // Override the Convert method from LargeDeltaConverter
    int32_t Convert(float delta) override;

private:
    /**
     * @brief Skip forward by currentOffset_ and fill the matrix along the way.
     *
     * @return item index to jump to after skipping.
     */
    int32_t SkipLinesForward();

    /**
     * @brief Skip backward by currentOffset_. Can assume that the matrix is already filled up to startIdx_
     *
     * @return item index to jump to after skipping.
     */
    int32_t SkipLinesBackward() const;

    GridLayoutInfo& info_;
    LayoutWrapper* wrapper_;
};

} // namespace OHOS::Ace::NG