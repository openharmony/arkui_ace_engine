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

#include "test/unittest/core/pattern/lazydynamiclayout/mock_lazy_grid_layout_algorithm.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/dynamiclayout/lazy_dynamic_layout_model_ng.h"
#include "core/components_ng/property/measure_utils.h"

namespace OHOS::Ace::NG {
void MockLazyGridLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    LazyGridLayoutAlgorithm::Measure(layoutWrapper);
    auto frameNode = layoutWrapper->GetHostNode();
    if (forwardLayout_) {
        LazyDynamicLayoutModelNG::SetAdjustedOffset(AceType::RawPtr(frameNode), -layoutInfo_->adjustOffset_.start);
    } else {
        LazyDynamicLayoutModelNG::SetAdjustedOffset(AceType::RawPtr(frameNode), layoutInfo_->adjustOffset_.end);
    }
}

void MockLazyGridLayoutAlgorithm::LayoutCachedItems(LayoutWrapper* layoutWrapper, float crossSize,
    const OffsetF& paddingOffset)
{
}
} // namespace OHOS::Ace::NG