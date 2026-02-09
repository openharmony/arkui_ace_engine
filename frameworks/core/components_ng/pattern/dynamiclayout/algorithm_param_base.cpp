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

#include "core/components_ng/pattern/dynamiclayout/algorithm_param_base.h"

namespace OHOS::Ace::NG {
DynamicLayoutType AlgorithmParamBase::GetDynamicLayoutType() const
{
    return layoutType_;
}

void AlgorithmParamBase::SetDynamicLayoutType(DynamicLayoutType layoutType)
{
    layoutType_ = layoutType;
}

LinearLayoutAlgorithmParam::LinearLayoutAlgorithmParam(bool isVertical)
{
    if (isVertical) {
        SetDynamicLayoutType(DynamicLayoutType::COLUMN_LAYOUT);
    } else {
        SetDynamicLayoutType(DynamicLayoutType::ROW_LAYOUT);
    }
}

bool CustomLayoutAlgorithmParam::FireOnMeasureSize(LayoutWrapper* layoutWrapper) const
{
    if (onMeasureSizeFunc_) {
        onMeasureSizeFunc_(layoutWrapper);
        return true;
    }
    return false;
}

bool CustomLayoutAlgorithmParam::FireOnPlaceChildren(LayoutWrapper* layoutWrapper) const
{
    if (onPlaceChildrenFunc_) {
        onPlaceChildrenFunc_(layoutWrapper);
        return true;
    }
    return false;
}
} // namespace OHOS::Ace::NG