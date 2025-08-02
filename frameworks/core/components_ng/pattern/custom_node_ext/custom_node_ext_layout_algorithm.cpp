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

#include "core/components_ng/pattern/custom_node_ext/custom_node_ext_layout_algorithm.h"

#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {

void CustomNodeExtLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    if (measureCallback_) {
        auto layoutProperty = layoutWrapper->GetLayoutProperty();
        CHECK_NULL_VOID(layoutProperty);
        if (layoutProperty->GetLayoutConstraint().has_value()) {
            measureCallback_(layoutProperty->GetLayoutConstraint().value());
        }
    } else {
        BoxLayoutAlgorithm::Measure(layoutWrapper);
    }
}

void CustomNodeExtLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    if (layoutCallback_) {
        auto rect = layoutWrapper->GetGeometryNode()->GetFrameRect();
        layoutCallback_(rect);
    } else {
        BoxLayoutAlgorithm::Layout(layoutWrapper);
    }
}
} // OHOS::Ace::NG