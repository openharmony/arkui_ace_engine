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

#include "core/components_v2/water_flow/water_flow_scroll_controller.h"

#include "core/components_v2/water_flow/render_water_flow.h"

namespace OHOS::Ace::V2 {
void WaterFlowScrollController::MarkScrollRender()
{
    auto waterFlow = AceType::DynamicCast<RenderWaterFlow>(scroll_.Upgrade());
    if (waterFlow) {
        waterFlow->MarkNeedLayout();
    }
}

bool WaterFlowScrollController::CheckScroll()
{
    auto waterFlow = AceType::DynamicCast<RenderWaterFlow>(scroll_.Upgrade());
    return waterFlow != nullptr;
}

bool WaterFlowScrollController::UpdateScrollPosition(const double offset, int32_t source)
{
    if (!callback_) {
        return true;
    }
    auto waterFlow = AceType::DynamicCast<RenderWaterFlow>(scroll_.Upgrade());
    if (!waterFlow || NearZero(waterFlow->GetEstimatedHeight())) {
        return true;
    }
    double height = waterFlow->GetLayoutSize().Height();
    double estimateHeight = waterFlow->GetEstimatedHeight();
    if (NearZero(estimateHeight)) {
        return false;
    }
    double activeHeight = height * height / estimateHeight;
    if (!NearEqual(activeHeight, height)) {
        if (NearZero(height)) {
            return false;
        }
        double value = offset * estimateHeight / height;
        return callback_(value, source);
    }
    return true;
}

void WaterFlowScrollController::ProcessScrollMotion(double position)
{
    if (!NearEqual(currentPos_, position)) {
        UpdateScrollPosition(0.0, SCROLL_FROM_ANIMATION);
    } else {
        if (!UpdateScrollPosition(currentPos_ - position, SCROLL_FROM_BAR)) {
            dragEndAnimator_->Stop();
        }
    }
    currentPos_ = position;
}
} // namespace OHOS::Ace::V2