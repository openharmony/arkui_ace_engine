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

#include "core/components_ng/pattern/dynamiclayout/dynamic_layout_algorithm.h"
#include "core/components_ng/pattern/dynamiclayout/algorithm_param_base.h"
#include "core/components_ng/layout/layout_wrapper.h"

namespace OHOS::Ace::NG {
DynamicLayoutAlgorithm::DynamicLayoutAlgorithm(const RefPtr<CustomLayoutAlgorithmParam> &param) : customParams_(param)
{
}

void DynamicLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    if (customParams_) {
        customParams_->FireOnMeasureSize(layoutWrapper);
    }
}

void DynamicLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    if (customParams_) {
        customParams_->FireOnPlaceChildren(layoutWrapper);
    }
}
} // namespace OHOS::Ace::NG