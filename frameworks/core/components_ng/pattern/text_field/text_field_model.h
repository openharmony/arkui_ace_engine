/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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
#include "base/geometry/ng/offset_t.h"
#include "base/memory/referenced.h"
#include "base/utils/macros.h"
#include "core/common/ime/text_input_action.h"
#include "core/common/ime/text_input_type.h"
#include "core/components/box/drag_drop_event.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/text_style.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components_ng/pattern/rich_editor/selection_info.h"
#include "core/components_ng/pattern/text/text_menu_extension.h"
#include "core/components_ng/pattern/text_field/text_content_type.h"
#include "core/components_ng/pattern/text_field/text_field_event_hub.h"
#include "core/components_ng/property/measure_property.h"

namespace OHOS::Ace {

struct Font {
    std::optional<FontWeight> fontWeight;
    std::optional<Dimension> fontSize;
    std::optional<FontStyle> fontStyle;
    std::vector<std::string> fontFamilies;
    std::optional<Color> fontColor;
    std::optional<std::vector<std::string>> fontFamiliesNG;
    std::optional<bool> enableVariableFontWeight;

    bool IsEqual(const Font& other) const
    {
        bool flag = fontWeight == other.fontWeight && fontSize == other.fontSize && fontStyle == other.fontStyle &&
                    fontColor == other.fontColor && enableVariableFontWeight == other.enableVariableFontWeight;
        if (!flag) {
            return false;
        }
        if (fontFamiliesNG.has_value() && other.fontFamiliesNG) {
            auto curFontFamilies = fontFamiliesNG.value();
            auto otherFontFamilies = other.fontFamiliesNG.value();
            if (curFontFamilies.size() != otherFontFamilies.size()) {
                return false;
            }
            for (size_t i = 0; i < curFontFamilies.size(); ++i) {
                if (curFontFamilies[i] != otherFontFamilies[i]) {
                    return false;
                }
            }
        }
        return flag;
    }

    std::string GetFontColor() const
    {
        return fontColor.has_value() ? fontColor.value().ColorToString() : "";
    }

    std::string GetFontFamily() const
    {
        if (!fontFamiliesNG.has_value() || fontFamiliesNG.value().empty()) {
            return "";
        }
        std::stringstream ss;
        auto fontFamily = fontFamiliesNG.value();
        ss << fontFamily[0];

        for (uint32_t index = 1; index < fontFamily.size(); ++index) {
            ss << "," << fontFamily[index];
        }
        return ss.str();
    }

    std::optional<FontWeight> GetFontWeight() const
    {
        return fontWeight;
    }

    std::optional<Dimension> GetFontSize() const
    {
        return fontSize;
    }

    std::optional<FontStyle> GetFontStyle() const
    {
        return fontStyle;
    }
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

struct UserUnderlineColor {
    std::optional<Color> typing = std::nullopt;
    std::optional<Color> normal = std::nullopt;
    std::optional<Color> error = std::nullopt;
    std::optional<Color> disable = std::nullopt;
};

enum class InputStyle {
    DEFAULT,
    INLINE,
};

enum class CleanNodeStyle {
    CONSTANT,
    INVISIBLE,
    INPUT,
};

enum class MenuPolicy { DEFAULT = 0, HIDE, SHOW };

enum class CancelButtonStyle {
    CONSTANT,
    INVISIBLE,
    INPUT,
};

struct SelectionOptions {
    MenuPolicy menuPolicy = MenuPolicy::DEFAULT;
};

enum class PreviewTextStyle {
    NORMAL,
    UNDERLINE,
};

class ACE_EXPORT TextFieldControllerBase : public AceType {
    DECLARE_ACE_TYPE(TextFieldControllerBase, AceType);

public:
    virtual void Focus(bool focus) {}

    virtual void ShowError(const std::string& errorText) {}
    virtual void Delete() {}
    virtual void Insert(const std::string& args) {}

    virtual void SetPasswordState(bool flag) {}

    virtual void CaretPosition(int32_t caretPosition) {}
    virtual int32_t GetCaretIndex()
    {
        return {};
    }
    virtual NG::OffsetF GetCaretPosition()
    {
        return {};
    }
    virtual void SetTextSelection(int32_t selectionStart, int32_t selectionEnd,
        const std::optional<SelectionOptions>& options = std::nullopt) {}
    virtual Rect GetTextContentRect()
    {
        return {};
    }
    virtual int32_t GetTextContentLinesNum()
    {
        return {};
    }
    virtual void StopEditing() {}

    virtual int32_t AddText(std::u16string text, int32_t offset) { return 0; }
    virtual void DeleteText(int32_t start, int32_t end) {}
    virtual SelectionInfo GetSelection() { return {}; }

    void SetGetCaretIndex(std::function<int32_t()>&& setGetCaretIndex)
    {
        getCaretIndex_ = std::move(setGetCaretIndex);
    }

    void SetGetCaretPosition(std::function<NG::OffsetF()>&& setGetCaretPosition)
    {
        getCaretPosition_ = std::move(setGetCaretPosition);
    }

    void SetCaretPosition(std::function<void(const int32_t)>&& setCaretPosition)
    {
        setCaretPosition_ = std::move(setCaretPosition);
    }

    void SetGetTextContentRect(std::function<Rect()>&& getTextContentRect)
    {
        getTextContentRect_ = std::move(getTextContentRect);
    }

    void SetGetTextContentLinesNum(std::function<int32_t()>&& getTextContentLinesNum)
    {
        getTextContentLinesNum_ = std::move(getTextContentLinesNum);
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
                    TAG_LOGW(AceLogTag::ACE_TEXT_FIELD, "Find escape \\%{private}s failed", nextChar.c_str());
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
    std::function<Rect(void)> getTextContentRect_;
    std::function<int32_t(void)> getCaretIndex_;
    std::function<NG::OffsetF(void)> getCaretPosition_;
    std::function<int32_t(void)> getTextContentLinesNum_;
    std::function<void(void)> stopEditing_;
};

class ACE_FORCE_EXPORT TextFieldModel {
public:
    static TextFieldModel* GetInstance();
    virtual ~TextFieldModel() = default;

    virtual RefPtr<TextFieldControllerBase> CreateTextInput(
        const std::optional<std::u16string>& placeholder, const std::optional<std::u16string>& value) = 0;
    virtual RefPtr<TextFieldControllerBase> CreateTextArea(
        const std::optional<std::u16string>& placeholder, const std::optional<std::u16string>& value) = 0;
    virtual void RequestKeyboardOnFocus(bool needToRequest) = 0;
    virtual void SetWidthAuto(bool isAuto) {}
    virtual void SetType(TextInputType value) = 0;
    virtual void SetContentType(const NG::TextContentType& value) = 0;
    virtual void SetPlaceholderColor(const Color& value) = 0;
    virtual void ResetPlaceholderColor() = 0;
    virtual void SetPlaceholderFont(const Font& value) = 0;
    virtual void SetEnterKeyType(TextInputAction value) = 0;
    virtual void SetTextAlign(TextAlign value) = 0;
    virtual void SetLineBreakStrategy(LineBreakStrategy lineBreakStrategy) = 0;
    virtual void SetCaretColor(const Color& value) = 0;
    virtual void ResetCaretColor() = 0;
    virtual void SetCaretPosition(const int32_t& value) = 0;
    virtual void SetSelectedBackgroundColor(const Color& value) = 0;
    virtual void SetCaretStyle(const CaretStyle& value) = 0;
    virtual void SetMaxLength(uint32_t value) = 0;
    virtual void SetMaxLines(uint32_t value) = 0;
    virtual void SetFontSize(const Dimension& value) = 0;
    virtual void SetFontWeight(FontWeight value) = 0;
    virtual void SetTextColor(const Color& value) = 0;
    virtual void ResetTextColor() = 0;
    virtual void SetWordBreak(Ace::WordBreak value) {};
    virtual void SetFontStyle(FontStyle value) = 0;
    virtual void SetFontFamily(const std::vector<std::string>& value) = 0;
    virtual void SetMinFontScale(const float value) = 0;
    virtual void SetMaxFontScale(const float value) = 0;

    virtual void SetInputFilter(const std::string& value,
        const std::function<void(const std::u16string&)>&& func) = 0;
    virtual void SetInputStyle(InputStyle value) = 0;
    virtual void SetShowPasswordIcon(bool value) = 0;
    virtual void SetOnEditChanged(std::function<void(bool)>&& func) = 0;
    virtual void SetOnSubmit(std::function<void(int32_t)>&& func) = 0;
    virtual void SetOnSubmit(std::function<void(int32_t, NG::TextFieldCommonEvent&)>&& func) = 0;
    virtual void SetOnChange(std::function<void(const ChangeValueInfo&)>&& func) = 0;
    virtual void SetOnTextSelectionChange(std::function<void(int32_t, int32_t)>&& func) = 0;
    virtual void SetOnSecurityStateChange(std::function<void(bool)>&& func) = 0;
    virtual void SetOnContentScroll(std::function<void(float, float)>&& func) = 0;
    virtual void SetOnCopy(std::function<void(const std::u16string&)>&& func) = 0;
    virtual void SetOnCut(std::function<void(const std::u16string&)>&& func) = 0;
    virtual void SetOnPaste(std::function<void(const std::u16string&)>&& func) = 0;
    virtual void SetOnPasteWithEvent(std::function<void(const std::u16string&, NG::TextCommonEvent&)>&& func) = 0;
    virtual void SetCopyOption(CopyOptions copyOption) = 0;
    virtual void ResetMaxLength() = 0;
    virtual void SetForegroundColor(const Color& value) = 0;
    virtual void SetBackgroundColor(const Color& color, bool tmp) = 0;
    virtual void ResetBackgroundColor() = 0;
    virtual void SetHeight(const Dimension& value) = 0;
    virtual void SetPadding(const NG::PaddingProperty& newPadding, Edge oldPadding, bool tmp) = 0;
    virtual void SetMargin() {};
    virtual void SetBackBorder() {};
    virtual void SetEllipsisMode(EllipsisMode modal) {};
    virtual void SetHoverEffect(HoverEffectType hoverEffect) = 0;
    virtual void SetShowPasswordText(bool value) = 0;
    virtual void SetOnClick(std::function<void(const ClickInfo&)>&& func) {};
    virtual void SetPasswordIcon(const PasswordIcon& passwordIcon) {};
    virtual void SetShowUnit(std::function<void()>&& unitAction) {};
    virtual void SetShowError(const std::u16string& errorText, bool visible) {};
    virtual void SetBarState(DisplayMode value) {};
    virtual void SetMaxViewLines(uint32_t value) {};
    virtual void SetNormalMaxViewLines(uint32_t value) {};

    virtual void SetShowUnderline(bool showUnderLine) {};
    virtual void SetNormalUnderlineColor(const Color& normalColor) {};
    virtual void SetUserUnderlineColor(UserUnderlineColor userColor) {};
    virtual void SetShowCounter(bool value) {};
    virtual void SetOnWillChangeEvent(std::function<bool(const ChangeValueInfo&)>&& func) = 0;
    virtual void SetOnChangeEvent(std::function<void(const std::u16string&)>&& func) = 0;
    virtual void SetFocusableAndFocusNode() {};
    virtual void SetSelectionMenuHidden(bool contextMenuHidden) = 0;
    virtual void SetCustomKeyboard(const std::function<void()>&& buildFunc, bool supportAvoidance = false) = 0;
    virtual void SetPasswordRules(const std::string& passwordRules) = 0;
    virtual void SetEnableAutoFill(bool enableAutoFill) = 0;
    virtual void SetCounterType(int32_t value) {};
    virtual void SetShowCounterBorder(bool value) {};
    virtual void SetCleanNodeStyle(CleanNodeStyle cleanNodeStyle) = 0;
    virtual void SetCancelIconSize(const CalcDimension& iconSize) = 0;
    virtual void SetCanacelIconSrc(
        const std::string& iconSrc, const std::string& bundleName, const std::string& moduleName) = 0;
    virtual void SetCancelIconColor(const Color& iconColor) = 0;
    virtual void SetCancelButtonSymbol(bool isShowSymbol) = 0;
    virtual void SetCancelSymbolIcon(const std::function<void(WeakPtr<NG::FrameNode>)>& iconSymbol) = 0;
    virtual void SetIsShowCancelButton(bool isShowCancelButton) = 0;

    virtual void SetSelectAllValue(bool isSetSelectAllValue) = 0;
    virtual void SetFontFeature(const std::list<std::pair<std::string, int32_t>>& value) = 0;
    virtual void SetLetterSpacing(const Dimension& value) {};
    virtual void SetLineHeight(const Dimension& value) {};
    virtual void SetHalfLeading(bool value) {};
    virtual void SetLineSpacing(const Dimension& value) {};
    virtual void SetAdaptMinFontSize(const Dimension& value) {};
    virtual void SetAdaptMaxFontSize(const Dimension& value) {};
    virtual void SetHeightAdaptivePolicy(TextHeightAdaptivePolicy value) {};
    virtual void SetTextDecoration(Ace::TextDecoration value) {};
    virtual void SetTextDecorationColor(const Color& value) {};
    virtual void SetTextDecorationStyle(Ace::TextDecorationStyle value) {};
    virtual void SetTextOverflow(Ace::TextOverflow value) {};
    virtual void SetTextIndent(const Dimension& value) {};
    virtual void SetOnWillInsertValueEvent(std::function<bool(const InsertValueInfo&)>&& func) = 0;
    virtual void SetOnDidInsertValueEvent(std::function<void(const InsertValueInfo&)>&& func) = 0;
    virtual void SetOnWillDeleteEvent(std::function<bool(const DeleteValueInfo&)>&& func) = 0;
    virtual void SetOnDidDeleteEvent(std::function<void(const DeleteValueInfo&)>&& func) = 0;
    virtual void SetSelectionMenuOptions(
        const NG::OnCreateMenuCallback&& onCreateMenuCallback, const NG::OnMenuItemClickCallback&& onMenuItemClick) {};
    virtual void SetEnablePreviewText(bool enablePreviewText) = 0;
    virtual void SetEnableHapticFeedback(bool state) = 0;
    virtual void SetStopBackPress(bool isStopBackPress) {};
    virtual void SetKeyboardAppearance(KeyboardAppearance value) = 0;

private:
    static std::unique_ptr<TextFieldModel> instance_;
    static std::mutex mutex_;
};

} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_TEXT_FIELD_MODEL_H
