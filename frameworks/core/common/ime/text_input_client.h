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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_IME_TEXT_INPUT_CLIENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_IME_TEXT_INPUT_CLIENT_H

#include <cstdint>

#include "base/memory/ace_type.h"
#include "base/utils/string_utils.h"
#include "base/utils/utf_helper.h"
#include "core/common/ime/text_editing_value.h"
#include "core/common/ime/text_input_action.h"
#include "core/event/key_event.h"
#include "core/components_ng/render/paragraph.h"
#include "core/components_ng/pattern/text_field/text_field_model.h"

namespace OHOS::Ace {

constexpr uint32_t KEY_NULL = 0;
constexpr uint32_t KEY_ALT = 1 << 0;
constexpr uint32_t KEY_SHIFT = 1 << 1;
constexpr uint32_t KEY_CTRL = 1 << 2;
constexpr uint32_t KEY_META = 1 << 3;

constexpr int32_t INVALID_VALUE = -1;
const std::string PRIVATE_DATA_KEY = "previewTextStyle";

enum class CaretMoveIntent {
    Left,
    Right,
    Up,
    Down,
    LeftWord,
    RightWord,
    ParagraghBegin,
    ParagraghEnd,
    LineBegin,
    LineEnd,
    Home,
    End,
};

struct PreviewRange {
    int32_t start = INVALID_VALUE;
    int32_t end = INVALID_VALUE;
    bool operator==(const PreviewRange &range) const
    {
        return start == range.start && end == range.end;
    }
    void Set(int32_t startValue, int32_t endValue)
    {
        start = startValue;
        end = endValue;
    }
};

struct KeyComb final {
    KeyCode code;
    int32_t modKeyFlags;

    KeyComb(KeyCode code, int32_t modKeyFlags = KEY_NULL) : code(code), modKeyFlags(modKeyFlags) {};

    bool operator<(const KeyComb& other) const
    {
        return code == other.code ? modKeyFlags < other.modKeyFlags : code < other.code;
    }

    bool operator==(const KeyComb& other) const
    {
        return code == other.code && modKeyFlags == other.modKeyFlags;
    }
};

class TextInputClient : public virtual AceType {
    DECLARE_ACE_TYPE(TextInputClient, AceType);

public:
    // Requests that this client update its editing state to the given value.
    virtual void UpdateEditingValue(
        const std::shared_ptr<TextEditingValue>& value, bool needFireChangeEvent = true) = 0;

    // Requests that this client perform the given action.
    virtual void PerformAction(TextInputAction action, bool forceCloseKeyboard = false) = 0;

    virtual void InsertValue(const std::string& insertValue, bool isIME = false) {};
    virtual void InsertValue(const std::u16string& insertValue, bool isIME = false)
    {
        InsertValue(UtfUtils::Str16DebugToStr8(insertValue), isIME);
    };
    virtual void DeleteBackward(int32_t length) {};
    virtual void DeleteForward(int32_t length) {};
    virtual void SetInputMethodStatus(bool keyboardShown) {}
    virtual void NotifyKeyboardClosedByUser() {}
    virtual void NotifyKeyboardClosed() {}
    virtual void NotifyKeyboardHeight(uint32_t height);
    virtual std::u16string GetLeftTextOfCursor(int32_t number)
    {
        return StringUtils::DEFAULT_USTRING;
    }

    virtual std::u16string GetRightTextOfCursor(int32_t number)
    {
        return StringUtils::DEFAULT_USTRING;
    }
    virtual int32_t GetTextIndexAtCursor()
    {
        return -1;
    }

    virtual void HandleSetSelection(int32_t start, int32_t end, bool showHandle = true) {}
    virtual void HandleExtendAction(int32_t action) {}

#if defined(IOS_PLATFORM)
    virtual const TextEditingValue& GetInputEditingValue() const
    {
        static TextEditingValue value;
        return value;
    };
#endif
    virtual void UpdateInputFilterErrorText(const std::string& errorText) {};
    virtual void UpdateInputFilterErrorText(const std::u16string& errorText)
    {
        UpdateInputFilterErrorText(UtfUtils::Str16DebugToStr8(errorText));
    };
    virtual void ResetTouchAtLeftOffsetFlag() {}

    // Requests that this client Y point.
    virtual double GetEditingBoxY() const
    {
        return 0.0;
    };
    virtual double GetEditingBoxTopY() const
    {
        return 0.0;
    };
    virtual bool GetEditingBoxModel() const
    {
        return false;
    };

    virtual int32_t GetInstanceId() const
    {
        return instanceId_;
    }

    void SetInstanceId(int32_t instanceId)
    {
        instanceId_ = instanceId;
    }

    bool HandleKeyEvent(const KeyEvent& keyEvent);
    virtual void UpdateShiftFlag(const KeyEvent& keyEvent) {}

    virtual bool HandleOnEscape()
    {
        return false;
    }

    virtual bool HandleOnTab(bool backward)
    {
        return false;
    }

    virtual void CursorMove(CaretMoveIntent direction) {}

    virtual void HandleSelect(CaretMoveIntent direction) {}

    virtual void HandleSelectFontStyle(KeyCode code) {}

    virtual void HandleOnSelectAll() {}

    virtual void HandleOnEnter() {}

    virtual void HandleOnShowMenu() {}

    virtual void HandleOnCopy(bool isUsingExternalKeyboard = false) {}

    virtual void HandleOnCut() {}

    virtual void HandleOnPaste() {}

    virtual void HandleOnUndoAction() {}

    virtual void HandleOnRedoAction() {}

    virtual void HandleOnDelete(bool backward) {}

    virtual bool HandleOnDeleteComb(bool backward)
    {
        return false;
    }

    virtual int32_t SetPreviewText(const std::u16string& previewValue, const PreviewRange range)
    {
        return SetPreviewText(UtfUtils::Str16DebugToStr8(previewValue), range);
    }

    virtual int32_t SetPreviewText(const std::string& previewValue, const PreviewRange range)
    {
        return 0;
    }

    virtual void FinishTextPreview() {}
    virtual void ReceivePreviewTextStyle (const std::string& style) {}

    virtual int32_t CheckPreviewTextValidate(const std::string& previewValue, const PreviewRange range)
    {
        return 0;
    }

    virtual int32_t CheckPreviewTextValidate(const std::u16string& previewValue, const PreviewRange range)
    {
        return CheckPreviewTextValidate(UtfUtils::Str16DebugToStr8(previewValue), range);
    }

    static std::map<KeyComb, std::function<bool(TextInputClient*)>> functionKeys_;

    static std::map<KeyComb, std::function<void(TextInputClient*)>> keyboardShortCuts_;

    virtual bool SetCaretOffset(int32_t caretPosition)
    {
        return false;
    }

    virtual void SetSelection(int32_t start, int32_t end,
        const std::optional<SelectionOptions>& options = std::nullopt, bool isForward = false) {}

    virtual bool InsertOrDeleteSpace(int32_t index)
    {
        return false;
    }
    virtual void DeleteRange(int32_t start, int32_t end, bool isIME = true) {}
    virtual void HandleOnPageUp() {};
    virtual void HandleOnPageDown() {};
    virtual void ResetOriginCaretPosition() {};
    virtual bool RecordOriginCaretPosition() { return false; };
protected:
    int32_t instanceId_ = -1;
    bool shiftFlag_ = false;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_IME_TEXT_INPUT_CLIENT_H
