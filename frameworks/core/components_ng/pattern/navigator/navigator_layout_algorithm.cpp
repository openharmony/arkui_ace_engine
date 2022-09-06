/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "navigator_layout_algorithm.h"
#include "base/utils/utils.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/navigator/navigator_layout_property.h"
#include "core/components_ng/property/measure_utils.h"

namespace OHOS::Ace::NG {

void NavigatorLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto props = AceType::DynamicCast<NavigatorLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(props);

    // set size based on child
    auto size = CreateIdealSize(props->GetLayoutConstraint().value(), Axis::VERTICAL,
        props->GetMeasureType(MeasureType::MATCH_PARENT), true);

    layoutWrapper->GetGeometryNode()->SetFrameSize(size);

    for (auto&& child : layoutWrapper->GetAllChildrenWithBuild()) {
        child->Measure(props->GetLayoutConstraint());
    }
    LOGI("ZTE frame size: %{public}f x %{public}f", size.Height(), size.Width());
}

void NavigatorLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    auto parentOffset =
        layoutWrapper->GetGeometryNode()->GetParentGlobalOffset() + layoutWrapper->GetGeometryNode()->GetFrameOffset();
    auto children = layoutWrapper->GetAllChildrenWithBuild();
    for (auto&& child : children) {
        child->Layout(parentOffset);
    }
}

} // namespace OHOS::Ace::NG