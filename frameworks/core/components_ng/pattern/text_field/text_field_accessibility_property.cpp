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

#include "core/components_ng/pattern/text_field/text_field_accessibility_property.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"

namespace OHOS::Ace::NG {
static const std::string DEFAULT_PASSWORD = "******";

int32_t TextFieldAccessibilityProperty::GetTextLengthLimit() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, Infinity<uint32_t>());
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_RETURN(textFieldPattern, Infinity<uint32_t>());
    return textFieldPattern->GetMaxLength();
}

bool TextFieldAccessibilityProperty::IsPassword() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, false);
    auto textFieldLayoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(textFieldLayoutProperty, false);
    return textFieldLayoutProperty->GetTextInputType() == TextInputType::VISIBLE_PASSWORD;
}

AceTextCategory TextFieldAccessibilityProperty::GetTextInputType() const
{
    AceTextCategory ret = AceTextCategory::INPUT_TYPE_DEFAULT;
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, ret);
    auto textFieldLayoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(textFieldLayoutProperty, ret);
    auto textInputType = textFieldLayoutProperty->GetTextInputTypeValue(TextInputType::BEGIN);

    switch (textInputType) {
        case TextInputType::TEXT:
            ret = AceTextCategory::INPUT_TYPE_TEXT;
            break;
        case TextInputType::NUMBER:
            ret = AceTextCategory::INPUT_TYPE_NUMBER;
            break;
        case TextInputType::DATETIME:
            ret = AceTextCategory::INPUT_TYPE_DATE;
            break;
        case TextInputType::EMAIL_ADDRESS:
            ret = AceTextCategory::INPUT_TYPE_EMAIL;
            break;
        case TextInputType::VISIBLE_PASSWORD:
            ret = AceTextCategory::INPUT_TYPE_PASSWORD;
            break;
        default:
            break;
    }
    return ret;
}

bool TextFieldAccessibilityProperty::IsEditable() const
{
    return true;
}

bool TextFieldAccessibilityProperty::IsMultiLine() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, false);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_RETURN(textFieldPattern, false);
    return textFieldPattern->IsTextArea();
}

int32_t TextFieldAccessibilityProperty::GetTextSelectionStart() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, -1);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_RETURN(textFieldPattern, -1);
    return textFieldPattern->GetTextSelector().GetStart();
}

int32_t TextFieldAccessibilityProperty::GetTextSelectionEnd() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, -1);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_RETURN(textFieldPattern, -1);
    return textFieldPattern->GetTextSelector().GetEnd();
}

std::string TextFieldAccessibilityProperty::GetText() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, "");
    auto textFieldLayoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(textFieldLayoutProperty, "");
    std::string text = textFieldLayoutProperty->GetValueValue("");
    if (IsPassword() && !text.empty()) {
        text = DEFAULT_PASSWORD;
    }
    return text;
}

bool TextFieldAccessibilityProperty::IsHint() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, false);
    auto textFieldLayoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(textFieldLayoutProperty, false);
    if (!textFieldLayoutProperty->GetValueValue("").empty() ||
        textFieldLayoutProperty->GetPlaceholderValue("").empty()) {
        return false;
    }
    return true;
}

std::string TextFieldAccessibilityProperty::GetHintText() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, "");
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_RETURN(textFieldPattern, "");
    return textFieldPattern->GetPlaceHolder();
}

std::string TextFieldAccessibilityProperty::GetErrorText() const
{
    return errorText_;
}

bool TextFieldAccessibilityProperty::GetContentInvalid() const
{
    return !errorText_.empty();
}

void TextFieldAccessibilityProperty::SetSpecificSupportAction()
{
    AddSupportAction(AceAction::ACTION_COPY);
    AddSupportAction(AceAction::ACTION_PASTE);
    AddSupportAction(AceAction::ACTION_CUT);
    AddSupportAction(AceAction::ACTION_SELECT);
    AddSupportAction(AceAction::ACTION_SET_SELECTION);
    AddSupportAction(AceAction::ACTION_CLEAR_SELECTION);
    AddSupportAction(AceAction::ACTION_SET_TEXT);
    AddSupportAction(AceAction::ACTION_NEXT_AT_MOVEMENT_GRANULARITY);
    AddSupportAction(AceAction::ACTION_PREVIOUS_AT_MOVEMENT_GRANULARITY);
}
} // namespace OHOS::Ace::NG
