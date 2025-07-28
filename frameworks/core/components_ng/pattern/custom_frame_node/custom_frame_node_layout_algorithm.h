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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CUSTOM_FRAME_NODE_FRAME_CUSTOM_NODE_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CUSTOM_FRAME_NODE_FRAME_CUSTOM_NODE_LAYOUT_ALGORITHM_H

#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/stack/stack_layout_algorithm.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT CustomFrameNodeLayoutAlgorithm : public StackLayoutAlgorithm {
    DECLARE_ACE_TYPE(CustomFrameNodeLayoutAlgorithm, StackLayoutAlgorithm);

public:
    CustomFrameNodeLayoutAlgorithm() = default;
    ~CustomFrameNodeLayoutAlgorithm() override = default;

    void Measure(LayoutWrapper* layoutWrapper) override
    {
        auto layoutProp = layoutWrapper->GetLayoutProperty();
        CHECK_NULL_VOID(layoutProp);
        auto layoutConstraint = layoutProp->CreateChildConstraint();
        for (auto&& child : layoutWrapper->GetAllChildrenWithBuild()) {
            if (child->GetHostTag() == "RenderNode") {
                child->Measure(std::nullopt);
            } else {
                child->Measure(layoutConstraint);
            }
        }
        PerformMeasureSelf(layoutWrapper);
    }

private:
    ACE_DISALLOW_COPY_AND_MOVE(CustomFrameNodeLayoutAlgorithm);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CUSTOM_FRAME_NODE_FRAME_CUSTOM_NODE_LAYOUT_ALGORITHM_H
