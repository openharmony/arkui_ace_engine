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

#include "core/components_ng/pattern/radio/radio_model_static.h"

#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/radio/radio_pattern.h"

namespace OHOS::Ace::NG {
void RadioModelStatic::SetChecked(FrameNode* frameNode, const std::optional<bool> isChecked)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<NG::RadioEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetCurrentUIState(UI_STATE_SELECTED, isChecked.value_or(false));
    if (isChecked) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(RadioPaintProperty, RadioCheck, isChecked.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(RadioPaintProperty, RadioCheck, frameNode);
    }
}

void RadioModelStatic::SetCheckedBackgroundColor(FrameNode* frameNode, const std::optional<Color>& color)
{
    if (color) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(RadioPaintProperty, RadioCheckedBackgroundColor, color.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(RadioPaintProperty, RadioCheckedBackgroundColor, frameNode);
    }
}

void RadioModelStatic::SetUncheckedBorderColor(FrameNode* frameNode, const std::optional<Color>& color)
{
    if (color) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(RadioPaintProperty, RadioUncheckedBorderColor, color.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(RadioPaintProperty, RadioUncheckedBorderColor, frameNode);
    }
}

void RadioModelStatic::SetIndicatorColor(FrameNode* frameNode, const std::optional<Color>& color)
{
    if (color) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(RadioPaintProperty, RadioIndicatorColor, color.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(RadioPaintProperty, RadioIndicatorColor, frameNode);
    }
}

void RadioModelStatic::SetBuilder(FrameNode* frameNode, std::function<void()>&& builder)
{
    CHECK_NULL_VOID(frameNode);
    auto radioPattern = frameNode->GetPattern<RadioPattern>();
    CHECK_NULL_VOID(radioPattern);
    radioPattern->SetBuilder(std::move(builder));
}

void RadioModelStatic::SetOnChangeEvent(FrameNode* frameNode, ChangeEvent&& onChangeEvent)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<RadioEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChangeEvent(std::move(onChangeEvent));
}

void RadioModelStatic::SetRadioIndicatorType(FrameNode* frameNode, const std::optional<int32_t>& indicator)
{
    CHECK_NULL_VOID(frameNode);
    if (indicator.has_value()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(RadioPaintProperty, RadioIndicator, indicator.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(RadioPaintProperty, RadioIndicator, frameNode);
    }
}
} // namespace OHOS::Ace::NG
