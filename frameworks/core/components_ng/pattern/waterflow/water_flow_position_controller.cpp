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

#include "core/components_ng/pattern/waterflow/water_flow_position_controller.h"

#include "core/components_ng/pattern/waterflow/water_flow_pattern.h"

namespace OHOS::Ace::NG {
void WaterFlowPositionController::JumpTo(int32_t index, bool /* smooth */, ScrollAlign /* align */,
    int32_t /* source */)
{
    auto pattern = scroll_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto waterFlowPattern = AceType::DynamicCast<WaterFlowPattern>(pattern);
    waterFlowPattern->UpdateStartIndex(index);
}

void WaterFlowPositionController::ScrollPage(bool reverse, bool /* smooth */)
{
    auto pattern = scroll_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto waterFlowPattern = AceType::DynamicCast<WaterFlowPattern>(pattern);
    if (waterFlowPattern && waterFlowPattern->GetAxis() != Axis::NONE) {
        waterFlowPattern->ScrollPage(reverse);
    }
}

bool WaterFlowPositionController::IsAtEnd() const
{
    auto waterFlowPattern = AceType::DynamicCast<WaterFlowPattern>(scroll_.Upgrade());
    CHECK_NULL_RETURN(waterFlowPattern, false);
    return waterFlowPattern->IsAtBottom();
}

Rect WaterFlowPositionController::GetItemRect(int32_t index) const
{
    auto waterFlowPattern = AceType::DynamicCast<WaterFlowPattern>(scroll_.Upgrade());
    CHECK_NULL_RETURN(waterFlowPattern, Rect());
    return waterFlowPattern->GetItemRect(index);
}
} // namespace OHOS::Ace::NG
