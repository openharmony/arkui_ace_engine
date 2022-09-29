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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_TEXT_FIELD_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_TEXT_FIELD_MODEL_H

#include <functional>
#include <optional>
#include <utility>
#include <vector>

#include "base/geometry/dimension.h"
#include "base/memory/referenced.h"
#include "base/utils/macros.h"
#include "core/common/ime/text_input_action.h"
#include "core/common/ime/text_input_type.h"
#include "core/components/box/drag_drop_event.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/text_style.h"
#include "core/components_ng/property/measure_property.h"

namespace OHOS::Ace {

struct Font {
    std::optional<FontWeight> fontWeight;
    std::optional<Dimension> fontSize;
    std::optional<FontStyle> fontStyle;
    std::vector<std::string> fontFamilies;
};

enum class InputStyle {
    DEFAULT,
    INLINE,
};

class ACE_EXPORT TextFieldControllerBase : public AceType {
    DECLARE_ACE_TYPE(TextFieldControllerBase, AceType);

public:
    virtual void Focus(bool focus) {}

    virtual void ShowError(const std::string& errorText) {}
    virtual void Delete() {}
    virtual void Insert(const std::string& args) {}

    virtual void CaretPosition(int32_t caretPosition) {}

    void SetCaretPosition(std::function<void(const int32_t)>&& setCaretPosition)
    {
        setCaretPosition_ = std::move(setCaretPosition);
    }

protected:
    std::function<void(const int32_t)> setCaretPosition_;
};

class ACE_EXPORT TextFieldModel {
public:
    static TextFieldModel* GetInstance();
    virtual ~TextFieldModel() = default;

    virtual RefPtr<TextFieldControllerBase> CreateTextInput(
        const std::optional<std::string>& placeholder, const std::optional<std::string>& value) = 0;

    virtual RefPtr<TextFieldControllerBase> CreateTextArea(
        const std::optional<std::string>& placeholder, const std::optional<std::string>& value) = 0;

    virtual void SetType(TextInputType value) = 0;
    virtual void SetPlaceholderColor(const Color& value) = 0;
    virtual void SetPlaceholderFont(const Font& value) = 0;
    virtual void SetEnterKeyType(TextInputAction value) = 0;
    virtual void SetTextAlign(TextAlign value) = 0;
    virtual void SetCaretColor(const Color& value) = 0;
    virtual void SetMaxLength(uint32_t value) = 0;
    virtual void SetFontSize(const Dimension& value) = 0;
    virtual void SetFontWeight(FontWeight value) = 0;
    virtual void SetTextColor(const Color& value) = 0;
    virtual void SetFontStyle(FontStyle value) = 0;
    virtual void SetFontFamily(const std::vector<std::string>& value) = 0;
    virtual void SetInputFilter(const std::string& value, const std::function<void(const std::string&)>& onError) = 0;
    virtual void SetInputStyle(InputStyle value) = 0;
    virtual void SetShowPasswordIcon(bool value) = 0;
    virtual void SetOnEditChanged(std::function<void(bool)>&& func) = 0;
    virtual void SetOnSubmit(std::function<void(int32_t)>&& func) = 0;
    virtual void SetOnChange(std::function<void(const std::string&)>&& func) = 0;
    virtual void SetOnCopy(std::function<void(const std::string&)>&& func) = 0;
    virtual void SetOnCut(std::function<void(const std::string&)>&& func) = 0;
    virtual void SetOnPaste(std::function<void(const std::string&)>&& func) = 0;
    virtual void SetCopyOption(CopyOptions copyOption) = 0;

private:
    static std::unique_ptr<TextFieldModel> instance_;
};

} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_TEXT_FIELD_MODEL_H
