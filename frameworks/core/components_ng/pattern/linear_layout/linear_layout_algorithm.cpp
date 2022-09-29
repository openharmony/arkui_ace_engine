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

#include "core/components_ng/pattern/linear_layout/linear_layout_algorithm.h"

#include "core/components/common/layout/constants.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_property.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_utils.h"

namespace OHOS::Ace::NG {

void LinearLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto linearLayoutProperty = DynamicCast<LinearLayoutProperty>(layoutWrapper->GetLayoutProperty());
    LinearLayoutUtils::Measure(layoutWrapper, linearLayoutProperty ? linearLayoutProperty->IsVertical() : false);
}

void LinearLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    auto linearLayoutProperty = DynamicCast<LinearLayoutProperty>(layoutWrapper->GetLayoutProperty());
    if (linearLayoutProperty) {
        LinearLayoutUtils::Layout(layoutWrapper, linearLayoutProperty->IsVertical(),
            linearLayoutProperty->GetCrossAxisAlignValue(FlexAlign::CENTER),
            linearLayoutProperty->GetMainAxisAlignValue(FlexAlign::FLEX_START));
    } else {
        LOGW("fail to cast to LinearLayoutProperty");
    }

    auto children = layoutWrapper->GetAllChildrenWithBuild();
    for (auto&& child : children) {
        child->Layout();
    }
}

} // namespace OHOS::Ace::NG
