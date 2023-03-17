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

namespace OHOS::Ace::NG {
int32_t TextFieldAccessibilityProperty::GetTextLengthLimit() const
{
    return 0;
}

bool TextFieldAccessibilityProperty::IsPassword() const
{
    return false;
}

AceTextCategory TextFieldAccessibilityProperty::GetTextInputType() const
{
    return AceTextCategory::INPUT_TYPE_TEXT;
}

bool TextFieldAccessibilityProperty::IsEditable() const
{
    return true;
}

bool TextFieldAccessibilityProperty::IsMultiLine() const
{
    return false;
}

int32_t TextFieldAccessibilityProperty::GetTextSelectionStart() const
{
    return 0;
}

int32_t TextFieldAccessibilityProperty::GetTextSelectionEnd() const
{
    return 0;
}

std::string TextFieldAccessibilityProperty::GetText() const
{
    return "";
}

bool TextFieldAccessibilityProperty::IsHint() const
{
    return true;
}

std::string TextFieldAccessibilityProperty::GetHintText() const
{
    return "";
}

std::string TextFieldAccessibilityProperty::GetErrorText() const
{
    return "";
}

bool TextFieldAccessibilityProperty::GetContentInvalid() const
{
    return false;
}

void TextFieldAccessibilityProperty::SetSpecificSupportAction() {}
} // namespace OHOS::Ace::NG
