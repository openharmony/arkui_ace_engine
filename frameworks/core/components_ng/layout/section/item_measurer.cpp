/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "item_measurer.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/waterflow/layout/water_flow_layout_utils.h"

namespace OHOS::Ace::NG {
float FlowItemMeasurer::Measure(FrameNode* item, int32_t index, float crossLen) const
{
    auto itemRefPtr = AceType::Claim(item);
    CHECK_NULL_RETURN(item && itemRefPtr, 0.0f);
    float userHeight = getUserDefHeight_ ? getUserDefHeight_(index) : -1.0f;
    if (NonNegative(userHeight)) {
        return userHeight;
    }
    item->Measure(
        WaterFlowLayoutUtils::CreateChildConstraint({ crossLen, containerMainLen_, axis_ }, props_, itemRefPtr));
    return item->GetGeometryNode()->GetMarginFrameSize().MainSize(axis_);
}
} // namespace OHOS::Ace::NG
