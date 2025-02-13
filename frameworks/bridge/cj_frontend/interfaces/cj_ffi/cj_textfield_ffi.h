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

#ifndef OHOS_ACE_FRAMEWORK_CJ_TEXTINPUT_FFI_H
#define OHOS_ACE_FRAMEWORK_CJ_TEXTINPUT_FFI_H

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_view_abstract_ffi.h"
#include "core/components/common/properties/text_style_parser.h"
#include "core/components_ng/pattern/text_field/text_field_model.h"

extern "C" {
struct CJSubmitEvent {
    char* text;
    bool keepEditable;
};

CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetHeight(double value, uint32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetSize(
    double width, uint32_t widthUnit, double height, uint32_t heightUnit);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetBorder(CJBorder params);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetBorderWidth(double value, uint32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetBorderWidthWithCJEdge(CJEdge params);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetBorderColor(uint32_t color);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetBorderStyle(int32_t style);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetBorderRadius(double value, uint32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetAllBorderRadius(CJBorderRadius value);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetBackgroundColor(uint32_t color);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetPadding(double value, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetPaddings(CJEdge params);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetMargin(double value, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetMargins(CJEdge params);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetType(int32_t value);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetPlaceholderColor(uint32_t value);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetPlaceholderFont(
    double size, int32_t unit, const char* weight, const char* family, int32_t style);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetFont(
    double size, int32_t unit, const char* weight, const char* family, int32_t style);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetEnterKeyType(int32_t value);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetCaretColor(uint32_t value);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetMaxLength(uint32_t value);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetTextAlign(int32_t value);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetFontSize(double value, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetFontColor(uint32_t value);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetFontWeight(const char* value);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetFontStyle(int32_t value);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetFontFamily(const char* value);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetInputFilter(const char* value, void (*callback)(const char* value));
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldOnSubmit(void (*callback)(int32_t value));
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldOnChange(void (*callback)(const char* value));
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldOnCopy(void (*callback)(const char* value));
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldOnCut(void (*callback)(const char* value));
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldOnPaste(void (*callback)(const char* value));
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldOnEditChanged(void (*callback)(bool value));
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetFontFeature(const char* value);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetLineHeight(double value, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetLineSpacing(double value, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetLetterSpacing(double value, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetDecoration(int32_t value, uint32_t color, int32_t style);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetLineBreakStrategy(int32_t value);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetWordBreak(int32_t value);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetHeightAdaptivePolicy(int32_t value);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetMaxFontSize(double value, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetMinFontSize(double value, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetSelectedBackgroundColor(uint32_t value);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetCaretStyle(double value, int32_t unit, uint32_t color);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetTextIndent(double value, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetTextOverflow(int32_t value);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetEnablePreviewText(bool value);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetStyle(int32_t value);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetBarState(int32_t value);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetSelectionMenuHidden(bool value);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetShowCounter(bool value, int32_t threshold, bool showBorder);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetMaxLines(int32_t value);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetEnableKeyboardOnFocus(bool value);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetContentType(int32_t value);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetEnableAutoFill(bool value);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetTextAreaType(int32_t value);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetCopyOption(int32_t value);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetCustomKeyboard(void (*callback)(), bool options);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldOnContentScroll(void (*callback)(float totalOffsetX, float totalOffsetY));
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldOnTextSelectionChange(
    void (*callback)(int32_t selectionStart, int32_t selectionEnd));
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldOnDidDelete(
    void (*callback)(double deleteOffset, int32_t direction, const char* deleteValue));
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldOnWillDelete(
    bool (*callback)(double deleteOffset, int32_t direction, const char* deleteValue));
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldOnDidInsert(void (*callback)(double insertOffset, const char* insertValue));
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldOnWillInsert(bool (*callback)(double insertOffset, const char* insertValue));
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldOnSecurityStateChange(void (*callback)(bool value));
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldShowUnit(void (*callback)());
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetPasswordRules(const char* rules);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetShowError(const char* errorText);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetShowPasswordIcon(bool isShow);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldShowPasswordText(bool show);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetPasswordIcon(const char* onIconSrc, const char* offIconSrc);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetCaretPosition(int32_t position);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetSelectAllValue(bool value);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetShowUnderline(bool show);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldNormalUnderlineColor(uint32_t color);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldUserUnderlineColor(
    uint32_t typing, uint32_t normal, uint32_t error, uint32_t disable);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldCancelButton(
    int32_t style, double size, int32_t unit, uint32_t color, const char* src);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldOnChangePreviewText(
    void (*callback)(const char* value, int32_t offset, const char* text));
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldonSubmitWithEvent(bool (*callback)(int32_t value, CJSubmitEvent));
}

#endif // OHOS_ACE_FRAMEWORK_CJ_TEXTINPUT_FFI_H
