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

#include "core/components_ng/pattern/stage/stage_layout_algorithm.h"

#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
void StageLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    // apply safe area to page nodes
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto layoutConstraint = layoutProperty->CreateChildConstraint();
    auto pipeline = PipelineContext::GetCurrentContext();
    childInsets_ = pipeline->GetSafeArea();
    LayoutWrapper::ApplySafeArea(childInsets_, layoutConstraint);
    for (auto&& child : layoutWrapper->GetAllChildrenWithBuild()) {
        child->Measure(layoutConstraint);
    }
    PerformMeasureSelf(layoutWrapper);
}

void StageLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    PerformLayout(layoutWrapper);
    for (auto&& child : layoutWrapper->GetAllChildrenWithBuild()) {
        child->GetGeometryNode()->SetFrameOffset(OffsetF(childInsets_.left_.Length(), childInsets_.top_.Length()));
        child->Layout();
    }
}
} // namespace OHOS::Ace::NG
