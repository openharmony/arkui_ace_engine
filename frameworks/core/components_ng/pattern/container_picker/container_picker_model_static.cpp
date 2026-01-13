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

#include "core/components_ng/pattern/container_picker/container_picker_model_static.h"

#include "core/common/resource/resource_parse_utils.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/container_picker/container_picker_event_hub.h"
#include "core/components_ng/pattern/container_picker/container_picker_pattern.h"

namespace OHOS::Ace::NG {

RefPtr<FrameNode> ContainerPickerModelStatic::CreateFrameNode(int32_t nodeId)
{
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::CONTAINER_PICKER_ETS_TAG, nodeId);
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CONTAINER_PICKER_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<ContainerPickerPattern>(); });
    return frameNode;
}

void ContainerPickerModelStatic::SetIndicatorStyle(
    FrameNode* frameNode, const std::optional<PickerIndicatorStyle>& style)
{
    CHECK_NULL_VOID(frameNode);
    if (!style.has_value()) {
        ACE_RESET_NODE_LAYOUT_PROPERTY(ContainerPickerLayoutProperty, IndicatorType, frameNode);
        ACE_RESET_NODE_LAYOUT_PROPERTY(ContainerPickerLayoutProperty, IndicatorDividerWidth, frameNode);
        ACE_RESET_NODE_LAYOUT_PROPERTY(ContainerPickerLayoutProperty, IndicatorDividerColor, frameNode);
        ACE_RESET_NODE_LAYOUT_PROPERTY(ContainerPickerLayoutProperty, IndicatorStartMargin, frameNode);
        ACE_RESET_NODE_LAYOUT_PROPERTY(ContainerPickerLayoutProperty, IndicatorEndMargin, frameNode);
        ACE_RESET_NODE_LAYOUT_PROPERTY(ContainerPickerLayoutProperty, IndicatorBackgroundColor, frameNode);
        ACE_RESET_NODE_LAYOUT_PROPERTY(ContainerPickerLayoutProperty, IndicatorBorderRadius, frameNode);
    } else {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ContainerPickerLayoutProperty, IndicatorType, style->type, frameNode);
        if (style->type == static_cast<int32_t>(PickerIndicatorType::DIVIDER)) {
            if (style->strokeWidth.has_value()) {
                ACE_UPDATE_NODE_LAYOUT_PROPERTY(
                    ContainerPickerLayoutProperty, IndicatorDividerWidth, style->strokeWidth.value(), frameNode);
            }
            if (style->dividerColor.has_value()) {
                ACE_UPDATE_NODE_LAYOUT_PROPERTY(
                    ContainerPickerLayoutProperty, IndicatorDividerColor, style->dividerColor.value(), frameNode);
            }
            if (style->startMargin.has_value()) {
                ACE_UPDATE_NODE_LAYOUT_PROPERTY(
                    ContainerPickerLayoutProperty, IndicatorStartMargin, style->startMargin.value(), frameNode);
            }
            if (style->endMargin.has_value()) {
                ACE_UPDATE_NODE_LAYOUT_PROPERTY(
                    ContainerPickerLayoutProperty, IndicatorEndMargin, style->endMargin.value(), frameNode);
            }
        } else if (style->type == static_cast<int32_t>(PickerIndicatorType::BACKGROUND)) {
            if (style->backgroundColor.has_value()) {
                ACE_UPDATE_NODE_LAYOUT_PROPERTY(
                    ContainerPickerLayoutProperty, IndicatorBackgroundColor, style->backgroundColor.value(), frameNode);
            }
            if (style->borderRadius.has_value()) {
                ACE_UPDATE_NODE_LAYOUT_PROPERTY(
                    ContainerPickerLayoutProperty, IndicatorBorderRadius, style->borderRadius.value(), frameNode);
            }
        } else {
            TAG_LOGE(AceLogTag::ACE_CONTAINER_PICKER, "invalid type of PickerIndicatorStyle.");
            return;
        }
    }

    auto pickerPattern = frameNode->GetPattern<ContainerPickerPattern>();
    CHECK_NULL_VOID(pickerPattern);
    pickerPattern->SetIndicatorStyleVal(style.value_or(PickerIndicatorStyle()));
}

void ContainerPickerModelStatic::SetSelectedIndex(FrameNode* frameNode, int32_t index)
{
    CHECK_NULL_VOID(frameNode);
    auto pickerPattern = frameNode->GetPattern<ContainerPickerPattern>();
    CHECK_NULL_VOID(pickerPattern);
    auto layoutProperty = frameNode->GetLayoutProperty<ContainerPickerLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (layoutProperty->HasSelectedIndex()) {
        pickerPattern->SetTargetIndex(index);
    } else {
        pickerPattern->SetSelectedIndex(index);
    }
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ContainerPickerLayoutProperty, SelectedIndex, index, frameNode);
}

void ContainerPickerModelStatic::SetCanLoop(FrameNode* frameNode, bool isLoop)
{
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ContainerPickerLayoutProperty, CanLoop, isLoop, frameNode);
}

void ContainerPickerModelStatic::SetEnableHapticFeedback(FrameNode* frameNode, bool isEnableHapticFeedback)
{
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(
        ContainerPickerLayoutProperty, EnableHapticFeedback, isEnableHapticFeedback, frameNode);
}

void ContainerPickerModelStatic::SetOnChange(FrameNode* frameNode, ContainerPickerChangeEvent&& onChange)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ContainerPickerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChange(std::move(onChange));
}

void ContainerPickerModelStatic::SetOnScrollStop(FrameNode* frameNode, ContainerPickerChangeEvent&& onScrollStop)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ContainerPickerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScrollStop(std::move(onScrollStop));
}

void ContainerPickerModelStatic::SetChangeEvent(FrameNode* frameNode, ContainerPickerChangeEvent&& onChange)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ContainerPickerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetChangeEvent(std::move(onChange));
}
} // namespace OHOS::Ace::NG
