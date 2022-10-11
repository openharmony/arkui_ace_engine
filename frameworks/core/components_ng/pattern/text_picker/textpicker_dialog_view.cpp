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
#include "core/components_ng/pattern/text_picker/textpicker_dialog_view.h"

#include "base/utils/utils.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/dialog/dialog_view.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
const uint32_t OPTION_COUNT_PHONE_LANDSCAPE = 3;
} // namespace

RefPtr<FrameNode> TextPickerDialogView::Show(const DialogProperties& dialogProperties, uint32_t selected,
    const Dimension& height, const std::vector<std::string>& getRangeVector,
    std::map<std::string, NG::DailogTextChangeEvent> dialogEvent)
{
    auto dialogNode = DialogView::CreateDialogNode(dialogProperties, nullptr);
    auto dialogNodeChild = AccessibilityManager::DynamicCast<FrameNode>(dialogNode->GetChildren().front());

    auto textNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textPickerNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXT_PICKER_ETS_TAG, textNodeId, []() { return AceType::MakeRefPtr<TextPickerPattern>(); });
    ViewStackProcessor::GetInstance()->Push(textPickerNode);
    auto textPickerPattern = textPickerNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_RETURN(textPickerPattern, nullptr);

    auto context = textPickerNode->GetContext();
    CHECK_NULL_RETURN(context, nullptr);
    auto themeManager = context->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, nullptr);
    auto pickerTheme = themeManager->GetTheme<PickerTheme>();
    CHECK_NULL_RETURN(pickerTheme, nullptr);

    uint32_t showCount = pickerTheme->GetShowOptionCount();
    if (SystemProperties::GetDeviceType() == DeviceType::PHONE &&
        SystemProperties::GetDeviceOrientation() == DeviceOrientation::LANDSCAPE) {
        showCount = OPTION_COUNT_PHONE_LANDSCAPE;
    }
    if (textPickerNode->GetChildren().empty()) {
        for (uint32_t index = 0; index < showCount; index++) {
            auto textNode = FrameNode::CreateFrameNode(
                V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
            CHECK_NULL_RETURN(textNode, nullptr);
            textNode->MountToParent(textPickerNode);
        }
    }
    SetRange(textPickerPattern, getRangeVector);
    SetSelected(textPickerPattern, selected);
    SetDefaultPickerItemHeight(height);
    auto changeEvent = dialogEvent["changeId"];
    SetDailogChange(textPickerNode, std::move(changeEvent));
    ViewStackProcessor::GetInstance()->Finish();
    auto childSize = dialogNode->GetChildren().size();
    textPickerNode->MountToParent(dialogNodeChild, static_cast<int32_t>(childSize) - 2); // place textPickerNode in front of the button
    dialogNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    return dialogNode;
}

void TextPickerDialogView::SetSelected(const RefPtr<TextPickerPattern>& textPickerPattern, uint32_t value)
{
    textPickerPattern->SetSelected(value);
}

void TextPickerDialogView::SetRange(
    const RefPtr<TextPickerPattern>& textPickerPattern, const std::vector<std::string>& value)
{
    textPickerPattern->SetRange(value);
}

void TextPickerDialogView::SetDailogChange(const RefPtr<FrameNode>& frameNode, DailogTextChangeEvent&& onChange)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<TextPickerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetDailogChange(std::move(onChange));
}

void TextPickerDialogView::SetDefaultPickerItemHeight(const Dimension& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, DefaultPickerItemHeight, value);
}

} // namespace OHOS::Ace::NG