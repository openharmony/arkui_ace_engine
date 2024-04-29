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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_COMMON_VIEW_COMMON_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_COMMON_VIEW_COMMON_LAYOUT_ALGORITHM_H

#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/pattern/custom/custom_measure_layout_node.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT CommonViewLayoutAlgorithm : public BoxLayoutAlgorithm {
    DECLARE_ACE_TYPE(CommonViewLayoutAlgorithm, BoxLayoutAlgorithm);
public:
    CommonViewLayoutAlgorithm() {}

    void Measure(LayoutWrapper* layoutWrapper) override
    {
        auto child = layoutWrapper->GetChildByIndex(0);
        BoxLayoutAlgorithm::Measure(layoutWrapper);
        CHECK_NULL_VOID(child);
        auto layoutNode = AceType::DynamicCast<CustomMeasureLayoutNode>(child->GetHostNode());
        CHECK_NULL_VOID(layoutNode);
        auto frameSize = child->GetGeometryNode()->GetFrameSize();
        layoutWrapper->GetGeometryNode()->SetFrameSize(frameSize);
    }
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_COMMON_VIEW_COMMON_LAYOUT_ALGORITHM_H
