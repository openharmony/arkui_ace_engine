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

#include "core/components_ng/pattern/container_picker/container_picker_model.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/container_picker/container_picker_event_hub.h"
#include "core/components_ng/pattern/container_picker/container_picker_pattern.h"

namespace OHOS::Ace::NG {

void ContainerPickerModel::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::CONTAINER_PICKER_ETS_TAG, nodeId);
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::CONTAINER_PICKER_ETS_TAG, nodeId, []() {
            return AceType::MakeRefPtr<ContainerPickerPattern>();
        });
    stack->Push(frameNode);
}

void ContainerPickerModel::SetCanLoop(bool isLoop)
{
    ACE_UPDATE_LAYOUT_PROPERTY(ContainerPickerLayoutProperty, CanLoop, isLoop);
}

void ContainerPickerModel::SetEnableHapticFeedback(bool isEnableHapticFeedback)
{
    ACE_UPDATE_LAYOUT_PROPERTY(ContainerPickerLayoutProperty, EnableHapticFeedback, isEnableHapticFeedback);
}

void ContainerPickerModel::SetOnChange(ContainerPickerChangeEvent&& onChange)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ContainerPickerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChange(std::move(onChange));
}

void ContainerPickerModel::SetOnScrollStop(ContainerPickerChangeEvent&& onScrollStop)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ContainerPickerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScrollStop(std::move(onScrollStop));
}

void ContainerPickerModel::SetIndicatorStyle(const PickerIndicatorStyle& style)
{
    ACE_UPDATE_LAYOUT_PROPERTY(ContainerPickerLayoutProperty, IndicatorType, style.type);
    if (style.type == static_cast<int32_t>(IndicatorType::DIVIDER)) {
        if (style.dividerWidth.has_value()) {
            ACE_UPDATE_LAYOUT_PROPERTY(ContainerPickerLayoutProperty, IndicatorDividerWidth,
                style.dividerWidth.value());
        }
        if (style.dividerColor.has_value()) {
            ACE_UPDATE_LAYOUT_PROPERTY(ContainerPickerLayoutProperty, IndicatorDividerColor,
                style.dividerColor.value());
        }
        if (style.startMargin.has_value()) {
            ACE_UPDATE_LAYOUT_PROPERTY(ContainerPickerLayoutProperty, IndicatorStartMargin,
                style.startMargin.value());
        }
        if (style.endMargin.has_value()) {
            ACE_UPDATE_LAYOUT_PROPERTY(ContainerPickerLayoutProperty, IndicatorEndMargin,
                style.endMargin.value());
        }
    } else if (style.type == static_cast<int32_t>(IndicatorType::BACKGROUND)) {
        if (style.backgroundColor.has_value()) {
            ACE_UPDATE_LAYOUT_PROPERTY(ContainerPickerLayoutProperty, IndicatorBackgroundColor,
                style.backgroundColor.value());
        }
        if (style.borderRadius.has_value()) {
            ACE_UPDATE_LAYOUT_PROPERTY(ContainerPickerLayoutProperty, IndicatorBorderRadius,
                style.borderRadius.value());
        }
    } else {
        TAG_LOGE(AceLogTag::ACE_CONTAINER_PICKER, "invalid type of PickerIndicatorStyle.");
    }
}
} // namespace OHOS::Ace::NG
