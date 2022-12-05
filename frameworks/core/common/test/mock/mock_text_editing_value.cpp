/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "core/common/ime/text_editing_value.h"

namespace OHOS::Ace {
void TextEditingValue::ParseFromJson(const JsonValue& json) {}

std::string TextEditingValue::ToJsonString() const
{
    return std::string();
}

bool TextEditingValue::operator==(const TextEditingValue& other) const
{
    return false;
}

bool TextEditingValue::operator!=(const TextEditingValue& other) const
{
    return false;
}

std::wstring TextEditingValue::GetWideText() const
{
    return std::wstring();
}

void TextEditingValue::MoveLeft() {}

void TextEditingValue::MoveRight() {}

void TextEditingValue::MoveToPosition(int32_t position) {}

void TextEditingValue::UpdateSelection(int32_t both) {}

void TextEditingValue::UpdateSelection(int32_t start, int32_t end) {}

#if defined(IOS_PLATFORM)
void TextEditingValue::UpdateCompose(int32_t start, int32_t end) {}
#endif

void TextEditingValue::SelectionAwareTextManipulation(const TextManipulation& manipulation) {}

std::string TextEditingValue::GetBeforeSelection() const
{
    return std::string();
}

std::string TextEditingValue::GetSelectedText() const
{
    return std::string();
}

std::string TextEditingValue::GetSelectedText(const TextSelection& textSelection) const
{
    return std::string();
}

std::string TextEditingValue::GetAfterSelection() const
{
    return std::string();
}

void TextEditingValue::Delete(int32_t start, int32_t end) {}

void TextEditingValue::Append(const std::string& newText) {}
} // namespace OHOS::Ace
