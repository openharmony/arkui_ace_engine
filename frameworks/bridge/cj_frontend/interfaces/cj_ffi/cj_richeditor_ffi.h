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
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_richeditor_controller_ffi.h"

extern "C" {
struct NativeRichEditorInsertValue {
    int32_t insertOffset;
    const char* insertValue;
};

struct CJTextRange {
    int32_t start;
    int32_t end;
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
CJ_EXPORT void FfiOHOSAceFrameworkRichEditorCustomKeyboard(void(*builder)());
CJ_EXPORT void FfiOHOSAceFrameworkRichEditorBindSelectionMenu(
    int32_t spantype, void(*content)(), int32_t, void(*onAppear)(), void(*onDisappear)());
CJ_EXPORT void FfiOHOSAceFrameworkRichEditorCopyOptions(int32_t copyOptions);
CJ_EXPORT void FfiOHOSAceFrameworkRichEditorOnReady(void(*callback)());
CJ_EXPORT void FfiOHOSAceFrameworkRichEditorOnDeleteComplete(void(*callback)());
CJ_EXPORT void FfiOHOSAceFrameworkRichEditorAboutToIMEInput(bool(*callback)(NativeRichEditorInsertValue));
CJ_EXPORT void FfiOHOSAceFrameworkRichEditorOnIMEInputComplete(void(*callback)(NativeRichEditorTextSpanResult));
CJ_EXPORT void FfiOHOSAceFrameworkRichEditorOnSelect(void(*callback)(NativeRichEditorSelection));
CJ_EXPORT void FfiOHOSAceFrameworkRichEditorAboutToDelete(bool(*callback)(NativeRichEditorDeleteValue));
CJ_EXPORT void FfiOHOSAceFrameworkRichEditorOnPaste(void(*callback)(int64_t));
CJ_EXPORT void FfiOHOSAceFrameworkRichEditorPreventDefault(int64_t controller);
CJ_EXPORT void FfiOHOSAceFrameworkRichEditorOnDidChange(
    void(*callback)(CJTextRange rangeBefore, CJTextRange rangeAfter));
}

#endif // OHOS_ACE_FRAMEWORK_CJ_RICHEDITOR_FFI_H
