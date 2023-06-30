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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_TEXT_FIELD_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_TEXT_FIELD_MODEL_H

#include <functional>
#include <mutex>
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
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components_ng/pattern/text/text_menu_extension.h"
#include "core/components_ng/property/measure_property.h"

namespace OHOS::Ace {

struct Font {
    std::optional<FontWeight> fontWeight;
    std::optional<Dimension> fontSize;
    std::optional<FontStyle> fontStyle;
    std::vector<std::string> fontFamilies;
};

struct CaretStyle {
    std::optional<Dimension> caretWidth;
};

struct PasswordIcon {
    std::string showResult;
    std::string hideResult;
    std::string showBundleName;
    std::string hideBundleName;
    std::string showModuleName;
    std::string hideModuleName;
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
    virtual void SetTextSelection(int32_t selectionStart, int32_t selectionEnd) {}
    virtual void StopEditing() {}

    void SetCaretPosition(std::function<void(const int32_t)>&& setCaretPosition)
    {
        setCaretPosition_ = std::move(setCaretPosition);
    }

    void SetStopEditing(std::function<void(void)>&& stopEditing)
    {
        stopEditing_ = std::move(stopEditing);
    }

    static bool EscapeString(const std::string& value, std::string& result)
    {
        const std::unordered_map<std::string, std::string> escapeMap = { { "a", "\a" }, { "b", "\b" }, { "f", "\f" },
            { "n", "\n" }, { "r", "\r" }, { "t", "\t" }, { "v", "\v" }, { "'", "\'" }, { "\"", "\"" }, { "\\", "\\" },
            { "?", "\?" }, { "0", "\0" } };
        size_t i = 0;
        for (; i < value.size();) {
            std::string ch = value.substr(i, 1);
            if (ch == "\\") {
                if (i + 1 >= value.size()) {
                    return false;
                }
                i++;
                // cannot escape this combo
                auto nextChar = value.substr(i, 1);
                auto mapTuple = escapeMap.find(nextChar);
                if (mapTuple == escapeMap.end()) {
                    LOGE("Find escape \\%{public}s failed", nextChar.c_str());
                    return false;
                }
                ch = mapTuple->second;
            }
            result += ch;
            i++;
        }
        return true;
    }

protected:
    std::function<void(const int32_t)> setCaretPosition_;
    std::function<void(void)> stopEditing_;
};

class ACE_EXPORT TextFieldModel {
public:
    static TextFieldModel* GetInstance();
    virtual ~TextFieldModel() = default;

    virtual RefPtr<TextFieldControllerBase> CreateTextInput(
        const std::optional<std::string>& placeholder, const std::optional<std::string>& value) = 0;

    virtual RefPtr<TextFieldControllerBase> CreateTextArea(
        const std::optional<std::string>& placeholder, const std::optional<std::string>& value) = 0;

    virtual void RequestKeyboardOnFocus(bool needToRequest) = 0;
    virtual void SetWidthAuto(bool isAuto) {}
    virtual void SetType(TextInputType value) = 0;
    virtual void SetPlaceholderColor(const Color& value) = 0;
    virtual void SetPlaceholderFont(const Font& value) = 0;
    virtual void SetEnterKeyType(TextInputAction value) = 0;
    virtual void SetTextAlign(TextAlign value) = 0;
    virtual void SetCaretColor(const Color& value) = 0;
    virtual void SetCaretPosition(const int32_t& value) = 0;
    virtual void SetSelectedBackgroundColor(const Color& value) = 0;
    virtual void SetCaretStyle(const CaretStyle& value) = 0;
    virtual void SetMaxLength(uint32_t value) = 0;
    virtual void SetMaxLines(uint32_t value) = 0;
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
    virtual void SetOnTextSelectionChange(std::function<void(int32_t, int32_t)>&& func) = 0;
    virtual void SetOnScroll(std::function<void(float, float)>&& func) = 0;
    virtual void SetOnCopy(std::function<void(const std::string&)>&& func) = 0;
    virtual void SetOnCut(std::function<void(const std::string&)>&& func) = 0;
    virtual void SetOnPaste(std::function<void(const std::string&)>&& func) = 0;
    virtual void SetCopyOption(CopyOptions copyOption) = 0;
    virtual void ResetMaxLength() = 0;
    virtual void SetForegroundColor(const Color& value) = 0;
    virtual void SetBackgroundColor(const Color& color, bool tmp) = 0;
    virtual void SetHeight(const Dimension& value) = 0;
    virtual void SetPadding(NG::PaddingProperty& newPadding, Edge oldPadding, bool tmp) = 0;
    virtual void SetBackBorder() {};
    virtual void SetHoverEffect(HoverEffectType hoverEffect) = 0;
    virtual void SetOnClick(std::function<void(const ClickInfo&)>&& func) {};

    virtual void SetMenuOptionItems(std::vector<NG::MenuOptionsParam>&& menuOptionsItems) = 0;
    virtual void SetPasswordIcon(const PasswordIcon& passwordIcon) {};
    virtual void SetShowUnit(std::function<void()>&& unitAction) {};
    virtual void SetShowError(const std::string& errorText, bool visible) {};
    virtual void SetBarState(DisplayMode value) {};
    virtual void SetMaxViewLines(uint32_t value) {};

    virtual void SetShowUnderline(bool showUnderLine) {};
    virtual void SetShowCounter(bool value) {};
    virtual void SetOnChangeEvent(std::function<void(const std::string&)>&& func) = 0;
    virtual void SetFocusableAndFocusNode() {};
    virtual void SetSelectionMenuHidden(bool contextMenuHidden) = 0;

private:
    static std::unique_ptr<TextFieldModel> instance_;
    static std::mutex mutex_;
};

} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_TEXT_FIELD_MODEL_H
