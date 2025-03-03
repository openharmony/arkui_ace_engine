/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef OHOS_ACE_FRAMEWORK_CJ_RICHEDITOR_FFI_H
#define OHOS_ACE_FRAMEWORK_CJ_RICHEDITOR_FFI_H

#include <cstdint>
#include <vector>

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_common_ffi.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_richeditor_controller_ffi.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_textfield_ffi.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_search_ffi.h"

extern "C" {
struct NativeRichEditorInsertValue {
    int32_t insertOffset;
    const char* insertValue;
};

struct NativeRichEditorInsertValue12 {
    int32_t insertOffset;
    ExternalString insertValue;
    ExternalString previewText;
};

struct CJTextRange {
    int32_t start;
    int32_t end;
};

struct NativePlaceholderStyle {
    bool hasFont;
    bool hasFontColor;
    NativeFont font;
    uint32_t fontColor;
};

struct NativeKeyboardOptions {
    bool supportAvoidance;
};

struct NativeTextRange {
    int32_t start;
    int32_t end;
};

struct NativeDecorationStyleInterface {
    int32_t type;
    uint32_t color;
    int32_t style;
    bool hasColor;
    bool hasStyle;
};

struct NativeTextDataDetectorConfig {
    VectorStringPtr types;
    void (*onDetectResultUpdate)(const char* value);
    uint32_t color;
    NativeDecorationStyleInterface decoration;
    bool hasOnDetectResultUpdate;
    bool hasColor;
    bool hasDecoration;
};

struct NativeRichEditorChangeValue {
    NativeTextRange rangeBefore;
    NativeRichEditorTextSpanResult12* replacedSpans;
    int64_t replacedSpansSize;
    NativeRichEditorImageSpanResult12* replacedImageSpans;
    int64_t replacedImageSpansSize;
    NativeRichEditorTextSpanResult12* replacedSymbolSpans;
    int64_t replacedSymbolSpansSize;
};

class ACE_EXPORT NativePasteEvent : public OHOS::FFI::FFIData {
    DECL_TYPE(NativeTextCommonEvent, OHOS::FFI::FFIData)
public:
    explicit NativePasteEvent(OHOS::Ace::NG::TextCommonEvent* event) {
        event_ = event;
    }

    OHOS::Ace::NG::TextCommonEvent* GetEvent()
    {
        return event_;
    }

    void PreventDefault()
    {
        event_->SetPreventDefault(true);
    }

private:
    OHOS::Ace::NG::TextCommonEvent* event_;
};

CJ_EXPORT void FfiOHOSAceFrameworkRichEditorCreateWithController(int64_t controller);
CJ_EXPORT void FfiOHOSAceFrameworkRichEditorCreateWithStyledStringController(int64_t controller);
CJ_EXPORT void FfiOHOSAceFrameworkRichEditorCustomKeyboard(void(*builder)());
CJ_EXPORT void FfiOHOSAceFrameworkRichEditorBindSelectionMenu(
    int32_t spantype, void(*content)(), int32_t, void(*onAppear)(), void(*onDisappear)());
CJ_EXPORT void FfiOHOSAceFrameworkRichEditorCopyOptions(int32_t copyOptions);
CJ_EXPORT void FfiOHOSAceFrameworkRichEditorOnReady(void(*callback)());
CJ_EXPORT void FfiOHOSAceFrameworkRichEditorOnDeleteComplete(void(*callback)());
CJ_EXPORT void FfiOHOSAceFrameworkRichEditorAboutToIMEInput(bool(*callback)(NativeRichEditorInsertValue));
CJ_EXPORT void FfiOHOSAceFrameworkRichEditorAboutToIMEInput12(bool(*callback)(NativeRichEditorInsertValue12));
CJ_EXPORT void FfiOHOSAceFrameworkRichEditorOnIMEInputComplete(void(*callback)(NativeRichEditorTextSpanResult));
CJ_EXPORT void FfiOHOSAceFrameworkRichEditorOnIMEInputComplete12(void(*callback)(NativeRichEditorTextSpanResult12));
CJ_EXPORT void FfiOHOSAceFrameworkRichEditorOnSelect(void(*callback)(NativeRichEditorSelection));
CJ_EXPORT void FfiOHOSAceFrameworkRichEditorAboutToDelete(bool(*callback)(NativeRichEditorDeleteValue));
CJ_EXPORT void FfiOHOSAceFrameworkRichEditorAboutToDelete12(bool(*callback)(NativeRichEditorDeleteValue12));
CJ_EXPORT void FfiOHOSAceFrameworkRichEditorOnPaste(void(*callback)(int64_t));
CJ_EXPORT void FfiOHOSAceFrameworkRichEditorPreventDefault(int64_t controller);
CJ_EXPORT void FfiOHOSAceFrameworkRichEditorOnDidChange(
    void(*callback)(CJTextRange rangeBefore, CJTextRange rangeAfter));
CJ_EXPORT void FfiOHOSAceFrameworkRichEditorEnableDataDetector(bool enable);
CJ_EXPORT void FfiOHOSAceFrameworkRichEditorDataDetectorConfig(NativeTextDataDetectorConfig config);
CJ_EXPORT void FfiOHOSAceFrameworkRichEditorEditMenuOptions(
    CjOnCreateMenu cjOnCreateMenu, CjOnMenuItemClick cjOnMenuItemClick);
CJ_EXPORT void FfiOHOSAceFrameworkRichEditorEnablePreviewText(bool enable);
CJ_EXPORT void FfiOHOSAceFrameworkRichEditorPlaceholder(const char* value, NativePlaceholderStyle style);
CJ_EXPORT void FfiOHOSAceFrameworkRichEditorCaretColor(uint32_t color);
CJ_EXPORT void FfiOHOSAceFrameworkRichEditorSelectedBackgroundColor(uint32_t color);
CJ_EXPORT void FfiOHOSAceFrameworkRichEditorEnterKeyType(uint32_t value);
CJ_EXPORT void FfiOHOSAceFrameworkRichEditorEnableKeyboardOnFocus(bool enable);
CJ_EXPORT void FfiOHOSAceFrameworkRichEditorCustomKeyboardWithOptions(void(*builder)(), NativeKeyboardOptions options);
CJ_EXPORT void FfiOHOSAceFrameworkRichEditorOnDidIMEInput(void(*callback)(NativeTextRange));
CJ_EXPORT void FfiOHOSAceFrameworkRichEditorOnSelectionChange(void(*callback)(NativeRichEditorRange));
CJ_EXPORT void FfiOHOSAceFrameworkRichEditorOnEditingChange(void(*callback)(bool));
CJ_EXPORT void FfiOHOSAceFrameworkRichEditorOnSubmit(bool(*callback)(int32_t, CJSubmitEvent));
CJ_EXPORT void FfiOHOSAceFrameworkRichEditorOnCut(void(*callback)(int64_t));
CJ_EXPORT void FfiOHOSAceFrameworkRichEditorOnCopy(void(*callback)(int64_t));
CJ_EXPORT void FfiOHOSAceFrameworkRichEditorOnWillChange(bool(*callback)(NativeRichEditorChangeValue));
CJ_EXPORT void FfiOHOSAceFrameworkRichEditorSetEnableHapticFeedBack(bool enable);
}

#endif // OHOS_ACE_FRAMEWORK_CJ_RICHEDITOR_FFI_H
