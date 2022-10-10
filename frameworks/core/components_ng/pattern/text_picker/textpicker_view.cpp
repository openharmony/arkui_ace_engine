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

#include "core/components_ng/pattern/text_picker/textpicker_view.h"

#include "base/geometry/ng/size_t.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text_picker/textpicker_event_hub.h"
#include "core/components_ng/pattern/text_picker/textpicker_layout_property.h"
#include "core/components_ng/pattern/text_picker/textpicker_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
const uint32_t OPTION_COUNT_PHONE_LANDSCAPE = 3;
} // namespace

void TextPickerView::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto textPickerNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXT_PICKER_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TextPickerPattern>(); });
    auto textPickerPattern = textPickerNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_VOID(textPickerPattern);

    auto context = textPickerNode->GetContext();
    CHECK_NULL_VOID(context);
    auto pickerTheme = context->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(pickerTheme);

    uint32_t showCount = pickerTheme->GetShowOptionCount();
    if (SystemProperties::GetDeviceType() == DeviceType::PHONE &&
        SystemProperties::GetDeviceOrientation() == DeviceOrientation::LANDSCAPE) {
        showCount = OPTION_COUNT_PHONE_LANDSCAPE;
    }
    if (textPickerNode->GetChildren().empty()) {
        for (uint32_t index = 0; index < showCount; index++) {
            auto textNode = FrameNode::CreateFrameNode(
                V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
            CHECK_NULL_VOID(textNode);
            textNode->MountToParent(textPickerNode);
        }
    }
    stack->Push(textPickerNode);
}

void TextPickerView::SetSelected(uint32_t value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    textPickerPattern->SetSelected(value);
}

void TextPickerView::SetRange(const std::vector<std::string>& value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    textPickerPattern->SetRange(value);
}

void TextPickerView::SetDefaultPickerItemHeight(const Dimension& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, DefaultPickerItemHeight, value);
}

void TextPickerView::SetOnChange(TextChangeEvent&& onChange)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<TextPickerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChange(std::move(onChange));
}

} // namespace OHOS::Ace::NG