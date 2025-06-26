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

#include "core/components_ng/pattern/slider/slider_pattern.h"

#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
void SliderPattern::UpdateValueMultiThread(float value)
{
    TAG_LOGD(AceLogTag::ACE_SELECT_COMPONENT, "slider update value %{public}d %{public}f", panMoveFlag_, value_);
    if (!panMoveFlag_) {
        auto sliderPaintProperty = GetPaintProperty<SliderPaintProperty>();
        CHECK_NULL_VOID(sliderPaintProperty);
        sliderPaintProperty->UpdateValue(value);
    }

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto updateTask = [this]() {
        CalcSliderValue();
        FireBuilder();
    };
    host->PostAfterAttachMainTreeTask(std::move(updateTask));
}

void SliderPattern::OnAttachToFrameNodeMultiThread()
{
    InitHapticController();
}

void SliderPattern::OnAttachToMainTreeMultiThread()
{
    RegisterVisibleAreaChange();
}

void SliderPattern::OnDetachFromFrameNodeMultiThread()
{
}

void SliderPattern::OnDetachFromMainTreeMultiThread()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto frameNode = host.GetRawPtr();
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->RemoveVisibleAreaChangeNode(frameNode->GetId());
    pipeline->RemoveWindowStateChangedCallback(frameNode->GetId());
    pipeline->RemoveWindowSizeChangeCallback(frameNode->GetId());
    hasVisibleChangeRegistered_ = false;

    auto accessibilityManager = pipeline->GetAccessibilityManager();
    CHECK_NULL_VOID(accessibilityManager);
    accessibilityManager->DeregisterAccessibilitySAObserverCallback(frameNode->GetAccessibilityId());
    TAG_LOGD(AceLogTag::ACE_SELECT_COMPONENT, "Slider OnDetachFromMainTree OK");
}
} // namespace OHOS::Ace::NG