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
#include "base/utils/utf_helper.h"
#include "core/common/ime/text_input_type.h"
#include "core/components_ng/pattern/pattern.h"

namespace OHOS::Ace::NG {
class ContentController : public virtual AceType {
    DECLARE_ACE_TYPE(ContentController, AceType);

public:
    explicit ContentController(const WeakPtr<Pattern>& pattern) : pattern_(pattern) {}
    ~ContentController() override = default;
    bool InsertValue(int32_t index, const std::u16string& value);
    bool ReplaceSelectedValue(int32_t startIndex, int32_t endIndex, const std::u16string& value);
    std::u16string GetSelectedValue(int32_t startIndex, int32_t endIndex);
    std::u16string GetValueBeforeIndex(int32_t index);
    std::u16string GetValueAfterIndex(int32_t index);
    void erase(int32_t startIndex, int32_t length);
    int32_t Delete(int32_t startIndex, int32_t length, bool isBackward);
    int32_t GetDeleteLength(int32_t startIndex, int32_t length, bool isBackward);
    bool IsIndexBeforeOrInEmoji(int32_t index);
    bool FilterValue();
    void FilterValueType(std::u16string& value);
    std::string GetSelectedLimitValue(int32_t& index, int32_t& startIndex);
    void FilterTextInputStyle(bool& textChanged, std::u16string& result);

    std::string GetTextValue()
    {
        return UtfUtils::Str16DebugToStr8(content_);
    }

    const std::u16string& GetTextUtf16Value()
    {
        return content_;
    }

    bool IsEmpty()
    {
        return content_.empty();
    }

    void SetTextValue(std::u16string&& value)
    {
        content_ = value;
        FilterValue();
    }

    void SetTextValue(const std::u16string& value)
    {
        content_ = value;
        FilterValue();
    }

    void SetTextValueOnly(std::u16string&& value)
    {
        content_ = value;
    }

    void SetTextValueOnly(const std::u16string& value)
    {
        content_ = value;
    }

    void Reset()
    {
        content_ = u"";
    }

    std::u16string GetInsertValue()
    {
        return insertValue_;
    }

private:
    void FormatIndex(int32_t& startIndex, int32_t& endIndex);
    bool FilterWithEvent(const std::u16string& filter, std::u16string& result);
    std::u16string PreprocessString(int32_t startIndex, int32_t endIndex, const std::u16string& value);
    static std::u16string RemoveErrorTextFromValue(const std::u16string& value, const std::u16string& errorText);
    static std::u16string FilterWithRegex(const std::u16string& filter, std::u16string& result);
    static bool FilterWithEmail(std::u16string& result);
    static bool FilterWithAscii(std::u16string& result);
    static bool FilterWithDecimal(std::u16string& result);

    std::u16string insertValue_;
    std::u16string content_;
    WeakPtr<Pattern> pattern_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_PATTERN_CONTENT_CONTROLLER_H