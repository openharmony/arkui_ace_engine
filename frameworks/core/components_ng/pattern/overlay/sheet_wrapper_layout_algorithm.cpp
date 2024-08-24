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

#include "core/components_ng/layout/box_layout_algorithm.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/overlay/sheet_wrapper_layout_algorithm.h"

namespace OHOS::Ace::NG {
void SheetWrapperLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    BoxLayoutAlgorithm::PerformMeasureSelf(layoutWrapper);
    auto child = layoutWrapper->GetChildByIndex(0);
    CHECK_NULL_VOID(child);
    auto sheetLayoutProperty = child->GetLayoutProperty();
    CHECK_NULL_VOID(sheetLayoutProperty);
    sheetLayoutProperty->UpdatePropertyChangeFlag(PROPERTY_UPDATE_MEASURE);
    auto layoutProp = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProp);
    auto childConstraint = layoutProp->CreateChildConstraint();
    child->Measure(childConstraint);
}

} // namespace OHOS::Ace::NG
