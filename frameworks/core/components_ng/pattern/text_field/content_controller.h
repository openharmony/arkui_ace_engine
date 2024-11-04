/*
 * Copyright (c) 2023-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_PATTERN_CONTENT_CONTROLLER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_PATTERN_CONTENT_CONTROLLER_H

#include <string>
#include <utility>

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/string_utils.h"
#include "core/common/ime/text_input_type.h"
#include "core/components_ng/pattern/pattern.h"

namespace OHOS::Ace::NG {
class ContentController : public virtual AceType {
    DECLARE_ACE_TYPE(ContentController, AceType);

public:
    explicit ContentController(const WeakPtr<Pattern>& pattern) : pattern_(pattern) {}
    ~ContentController() override = default;
    bool InsertValue(int32_t index, const std::string& value);
    bool ReplaceSelectedValue(int32_t startIndex, int32_t endIndex, const std::string& value);
    std::string GetSelectedValue(int32_t startIndex, int32_t endIndex);
    std::string GetValueBeforeIndex(int32_t index);
    std::string GetValueAfterIndex(int32_t index);
    void erase(int32_t startIndex, int32_t length);
    int32_t Delete(int32_t startIndex, int32_t length, bool isBackward);
    int32_t GetDeleteLength(int32_t startIndex, int32_t length, bool isBackward);
    bool IsIndexBeforeOrInEmoji(int32_t index);
    bool FilterValue();
    void FilterValueType(std::string& value);
    std::string GetSelectedLimitValue(int32_t& index, int32_t& startIndex);
    void FilterTextInputStyle(bool& textChanged, std::string& result);

    std::wstring GetWideText()
    {
        return StringUtils::ToWstring(content_);
    }

    std::string GetTextValue()
    {
        return content_;
    }

    bool IsEmpty()
    {
        return content_.empty();
    }

    void SetTextValue(std::string&& value)
    {
        content_ = value;
        FilterValue();
    }

    void SetTextValue(const std::string& value)
    {
        content_ = value;
        FilterValue();
    }

    void SetTextValueOnly(std::string&& value)
    {
        content_ = value;
    }

    void Reset()
    {
        content_ = "";
    }

    std::string GetInsertValue()
    {
        return insertValue_;
    }

private:
    void FormatIndex(int32_t& startIndex, int32_t& endIndex);
    bool FilterWithEvent(const std::string& filter, std::string& result);
    std::string PreprocessString(int32_t startIndex, int32_t endIndex, const std::string& value);
    static std::string RemoveErrorTextFromValue(const std::string& value, const std::string& errorText);
    static std::string FilterWithRegex(const std::string& filter, std::string& result);
    static bool FilterWithEmail(std::string& result);
    static bool FilterWithAscii(std::string& result);
    static bool FilterWithDecimal(std::string& result);

    std::string insertValue_;
    std::string content_;
    WeakPtr<Pattern> pattern_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_PATTERN_CONTENT_CONTROLLER_H