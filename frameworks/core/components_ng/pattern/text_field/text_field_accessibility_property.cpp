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

bool TextFieldAccessibilityProperty::IsPassword() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, false);
    auto textFieldLayoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(textFieldLayoutProperty, false);
    return textFieldLayoutProperty->GetTextInputType() == TextInputType::VISIBLE_PASSWORD;
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
} // namespace OHOS::Ace::NG
