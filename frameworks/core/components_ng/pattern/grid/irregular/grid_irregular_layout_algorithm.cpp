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

#include "core/components_ng/pattern/grid/irregular/grid_irregular_layout_algorithm.h"

namespace OHOS::Ace::NG {
void GridIrregularLayout::Measure(LayoutWrapper* layoutWrapper) {
    // obtain self size
    int selfMainLength;
    int contentLength = 0;
    int32_t index = 0;
    while (contentLength < selfMainLength && index < layoutWrapper->GetTotalChildCount()) {
        LoadChild(layoutWrapper, index++);
    }
}

void GridIrregularLayout::LoadChild(LayoutWrapper* wrapper, int32_t index)
{
    auto child = 
}

void GridIrregularLayout::Layout(LayoutWrapper* layoutWrapper) {}
} // namespace OHOS::Ace::NG