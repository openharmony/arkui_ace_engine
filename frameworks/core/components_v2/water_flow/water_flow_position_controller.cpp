/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#include "core/components_v2/water_flow/water_flow_position_controller.h"

#include "core/components_v2/water_flow/render_water_flow.h"

namespace OHOS::Ace::V2 {
void WaterFlowPositionController::ScrollToIndex(
    int32_t index, bool /* smooth */, ScrollAlign /* align */, std::optional<float> /* extraOffset */)
{
    auto waterFlow = AceType::DynamicCast<V2::RenderWaterFlow>(scroll_.Upgrade());
    if (!waterFlow) {
        return;
    }
    waterFlow->ScrollToIndex(index);
}

Axis WaterFlowPositionController::GetScrollDirection() const
{
    auto waterFlow = AceType::DynamicCast<V2::RenderWaterFlow>(scroll_.Upgrade());
    if (!waterFlow) {
        return Axis::VERTICAL;
    }
    return waterFlow->GetAxis();
}

} // namespace OHOS::Ace::V2
