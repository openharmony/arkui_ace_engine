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

#include "base/utils/utf_helper.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"

namespace OHOS::Ace::NG {
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
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_RETURN(textFieldPattern, false);
    CHECK_NULL_RETURN(textFieldPattern->IsInPasswordMode(), false);
    auto responseArea = textFieldPattern->GetResponseArea();
    auto passwordArea = AceType::DynamicCast<PasswordResponseArea>(responseArea);
    CHECK_NULL_RETURN(passwordArea, false);
    return passwordArea->IsObscured();
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
        case TextInputType::PHONE:
            ret = AceTextCategory::INPUT_TYPE_PHONENUMBER;
            break;
        case TextInputType::DATETIME:
            ret = AceTextCategory::INPUT_TYPE_DATE;
            break;
        case TextInputType::EMAIL_ADDRESS:
            ret = AceTextCategory::INPUT_TYPE_EMAIL;
            break;
        case TextInputType::VISIBLE_PASSWORD:
        case TextInputType::NUMBER_PASSWORD:
            ret = AceTextCategory::INPUT_TYPE_PASSWORD;
            break;
        case TextInputType::USER_NAME:
            ret = AceTextCategory::INPUT_TYPE_USER_NAME;
            break;
        case TextInputType::NEW_PASSWORD:
            ret = AceTextCategory::INPUT_TYPE_NEW_PASSWORD;
            break;
        default:
            break;
    }
    return ret;
}

bool TextFieldAccessibilityProperty::IsMultiLine() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, false);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_RETURN(textFieldPattern, false);
    return textFieldPattern->IsTextArea();
}

bool TextFieldAccessibilityProperty::IsSelected() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, false);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_RETURN(textFieldPattern, false);
    return textFieldPattern->IsSelected();
}

int32_t TextFieldAccessibilityProperty::GetTextSelectionStart() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, -1);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_RETURN(textFieldPattern, -1);
    auto textSelectController = textFieldPattern->GetTextSelectController();
    CHECK_NULL_RETURN(textSelectController, -1);
    return textSelectController->GetStartIndex();
}

int32_t TextFieldAccessibilityProperty::GetTextSelectionEnd() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, -1);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_RETURN(textFieldPattern, -1);
    auto textSelectController = textFieldPattern->GetTextSelectController();
    CHECK_NULL_RETURN(textSelectController, -1);
    return textSelectController->GetEndIndex();
}

std::string TextFieldAccessibilityProperty::GetText() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, "");
    auto textFieldLayoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(textFieldLayoutProperty, "");
    std::string text = UtfUtils::Str16DebugToStr8(textFieldLayoutProperty->GetValueValue(u""));
    if (IsPassword() && !text.empty()) {
        return std::string(text.size(), '*');
    }

    return text;
}

bool TextFieldAccessibilityProperty::IsHint() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, false);
    auto textFieldLayoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(textFieldLayoutProperty, false);
    return !(!textFieldLayoutProperty->GetValueValue(u"").empty() ||
        textFieldLayoutProperty->GetPlaceholderValue(u"").empty());
}

std::string TextFieldAccessibilityProperty::GetHintText() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, "");
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_RETURN(textFieldPattern, "");
    return UtfUtils::Str16DebugToStr8(textFieldPattern->GetPlaceHolder());
}

bool TextFieldAccessibilityProperty::GetContentInvalid() const
{
    return !errorText_.empty();
}

bool TextFieldAccessibilityProperty::IsScrollable() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, false);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_RETURN(textFieldPattern, false);
    return textFieldPattern->IsScrollable();
}

void TextFieldAccessibilityProperty::SetSpecificSupportAction()
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_VOID(frameNode);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(textFieldPattern);
    if (textFieldPattern->AllowCopy()) {
        AddSupportAction(AceAction::ACTION_COPY);
        AddSupportAction(AceAction::ACTION_CUT);
    }

    AddSupportAction(AceAction::ACTION_PASTE);
    AddSupportAction(AceAction::ACTION_SET_SELECTION);
    AddSupportAction(AceAction::ACTION_CLEAR_SELECTION);
    AddSupportAction(AceAction::ACTION_SET_TEXT);
    AddSupportAction(AceAction::ACTION_NEXT_AT_MOVEMENT_GRANULARITY);
    AddSupportAction(AceAction::ACTION_PREVIOUS_AT_MOVEMENT_GRANULARITY);
}

bool TextFieldAccessibilityProperty::IsShowCount() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, false);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_RETURN(textFieldPattern, false);
    CHECK_NULL_RETURN(textFieldPattern->IsShowCount(), false);
    auto textCmpDecorator = textFieldPattern->GetCounterDecorator();
    CHECK_NULL_RETURN(textCmpDecorator, false);
    auto counterDecorator = DynamicCast<CounterDecorator>(textCmpDecorator);
    CHECK_NULL_RETURN(counterDecorator, false);
    return counterDecorator->HasContent();
}

bool TextFieldAccessibilityProperty::IsShowError() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, false);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_RETURN(textFieldPattern, false);
    return textFieldPattern->IsShowError();
}
} // namespace OHOS::Ace::NG
