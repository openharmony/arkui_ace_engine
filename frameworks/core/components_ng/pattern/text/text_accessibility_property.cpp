/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/text/text_accessibility_property.h"

#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/text/text_pattern.h"

namespace OHOS::Ace::NG {
std::string TextAccessibilityProperty::GetText() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, "");
    auto textPattern = frameNode->GetPattern<TextPattern>();
    CHECK_NULL_RETURN(textPattern, "");
    return textPattern->GetTextForDisplay();
}

bool TextAccessibilityProperty::IsSelected() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, false);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    CHECK_NULL_RETURN(textPattern, false);
    const auto& textSelector = textPattern->GetTextSelector();
    return textSelector.IsValid();
}

int32_t TextAccessibilityProperty::GetTextSelectionStart() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, -1);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    CHECK_NULL_RETURN(textPattern, -1);
    const auto& textSelector = textPattern->GetTextSelector();
    return textSelector.GetTextStart();
}

int32_t TextAccessibilityProperty::GetTextSelectionEnd() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, -1);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    CHECK_NULL_RETURN(textPattern, -1);
    const auto& textSelector = textPattern->GetTextSelector();
    return textSelector.GetTextEnd();
}

void TextAccessibilityProperty::SetSpecificSupportAction()
{
    AddSupportAction(AceAction::ACTION_COPY);
    AddSupportAction(AceAction::ACTION_NEXT_AT_MOVEMENT_GRANULARITY);
    AddSupportAction(AceAction::ACTION_PREVIOUS_AT_MOVEMENT_GRANULARITY);

    auto frameNode = host_.Upgrade();
    CHECK_NULL_VOID(frameNode);
    auto textLayoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    if (textLayoutProperty->GetCopyOptionValue(CopyOptions::None) != CopyOptions::None) {
        AddSupportAction(AceAction::ACTION_SELECT);
        AddSupportAction(AceAction::ACTION_SET_SELECTION);
        AddSupportAction(AceAction::ACTION_CLEAR_SELECTION);
    }
}
} // namespace OHOS::Ace::NG
