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

#ifndef OHOS_ACE_FRAMEWORK_CJ_SCROLLBAR_FFI_H
#define OHOS_ACE_FRAMEWORK_CJ_SCROLLBAR_FFI_H

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_common_ffi.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_view_abstract_ffi.h"

extern "C" {
struct SearchCreateParam {
    const char* value;
    const char* placeholder;
    int64_t iconID;
    uint32_t iconType;
    const char* iconParams;
    int64_t controllerID;
};

using SearchTextMenuItemHandle = void*;

struct FFiSearchTextMenuItem {
    char* content;
    char* icon;
    char* id;
};

CJ_EXPORT void FfiOHOSAceFrameworkSearchCreateByIconID(SearchCreateParam value);
CJ_EXPORT void FfiOHOSAceFrameworkSearchSetSearchButton(const char* text);
CJ_EXPORT void FfiOHOSAceFrameworkSearchSetPlaceholderColor(uint32_t color);
CJ_EXPORT void FfiOHOSAceFrameworkSearchSetPlaceholderFont(
    double fontSize, int32_t sizeUnit, const char* fontWeight, int32_t fontStyle, const char* fontFamily);
CJ_EXPORT void FfiOHOSAceFrameworkSearchSetTextFont(
    double fontSize, int32_t sizeUnit, const char* fontWeight, int32_t fontStyle, const char* fontFamily);

struct SearchSetBorder {
    double width;
    int32_t widthUnit;
    uint32_t color;
    double radius;
    int32_t radiusUnit;
    int32_t style;
};
CJ_EXPORT void FfiOHOSAceFrameworkSearchSetBorder(SearchSetBorder value);
CJ_EXPORT void FfiOHOSAceFrameworkSearchSetBorderWidth(double width, int32_t widthUnit);
CJ_EXPORT void FfiOHOSAceFrameworkSearchSetBorderColor(uint32_t color);
CJ_EXPORT void FfiOHOSAceFrameworkSearchSetBorderStyle(int32_t style);
CJ_EXPORT void FfiOHOSAceFrameworkSearchSetBorderRadius(double radius, int32_t radiusUnit);
CJ_EXPORT void FfiOHOSAceFrameworkSearchSetHeight(double height, int32_t heightUnit);
CJ_EXPORT void FfiOHOSAceFrameworkSearchSetCopyOption(int32_t copyOption);
CJ_EXPORT void FfiOHOSAceFrameworkSearchOnSubmit(void (*callback)(const char* value));
CJ_EXPORT void FfiOHOSAceFrameworkSearchOnChange(void (*callback)(const char* value));
CJ_EXPORT void FfiOHOSAceFrameworkSearchOnCopy(void (*callback)(const char* value));
CJ_EXPORT void FfiOHOSAceFrameworkSearchOnCut(void (*callback)(const char* value));
CJ_EXPORT void FfiOHOSAceFrameworkSearchOnPaste(void (*callback)(const char* value));

CJ_EXPORT int64_t FfiOHOSAceFrameworkSearchController();
CJ_EXPORT void FfiOHOSAceFrameworkSearchCaretPosition(int64_t selfID, int32_t carePosition);
CJ_EXPORT void FfiOHOSAceFrameworkSearchCreateByIconRes(
    const char* value, const char* placeholder, const char* iconUrl, int64_t controllerId);
CJ_EXPORT void FfiOHOSAceFrameworkSearchSetMaxFontSize(double fontSize, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkSearchSetMinFontSize(double fontSize, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkSearchSetFontFeature(const char* fontFeature);
CJ_EXPORT void FfiOHOSAceFrameworkSearchSetLineHeight(double lineHeight, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkSearchSetLetterSpacing(double space, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkSearchSetDecoration(int32_t type, uint32_t color, int32_t style);
CJ_EXPORT void FfiOHOSAceFrameworkSearchSetEnterKeyType(int32_t type);
CJ_EXPORT void FfiOHOSAceFrameworkSearchSetSelectedBackgroundColor(uint32_t color);
CJ_EXPORT void FfiOHOSAceFrameworkSearchSetTextIndent(double value, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkSearchStopEditing(int64_t selfID);
CJ_EXPORT void FfiOHOSAceFrameworkSearchSetTextSelection(
    int64_t selfID, int32_t selectionStart, int32_t selectionEnd, int32_t option);
CJ_EXPORT void FfiOHOSAceFrameworkSearchSetCancelButton(
    int32_t style, double value, int32_t unit, uint32_t color, const char* src);
CJ_EXPORT void FfiOHOSAceFrameworkSearchSetSearchIcon(double value, int32_t unit, uint32_t color, const char* src);
CJ_EXPORT void FfiOHOSAceFrameworkSearchSetEnablePreviewText(bool enablePreviewText);
CJ_EXPORT void FfiOHOSAceFrameworkSearchSetType(int32_t type);
CJ_EXPORT void FfiOHOSAceFrameworkSearchSetMaxLength(uint32_t maxLength);
CJ_EXPORT void FfiOHOSAceFrameworkSearchSetSelectionMenuHidden(bool value);
CJ_EXPORT void FfiOHOSAceFrameworkSearchSetEnableKeyboardOnFocus(bool value);
CJ_EXPORT void FfiOHOSAceFrameworkSearchSetCaretStyle(double value, int32_t unit, uint32_t color);
CJ_EXPORT void FfiOHOSAceFrameworkSearchSetTextAlign(int32_t value);
CJ_EXPORT void FfiOHOSAceFrameworkSearchSetFontColor(uint32_t color);
CJ_EXPORT void FfiOHOSAceFrameworkSearchOnDidInsert(void (*callback)(double insertOffset, const char* insertValue));
CJ_EXPORT void FfiOHOSAceFrameworkSearchOnDidDelete(
    void (*callback)(double deleteOffset, int32_t direction, const char* deleteValue));
CJ_EXPORT void FfiOHOSAceFrameworkSearchOnWillInsert(bool (*callback)(double insertOffset, const char* insertValue));
CJ_EXPORT void FfiOHOSAceFrameworkSearchOnWillDelete(
    bool (*callback)(double deleteOffset, int32_t direction, const char* deleteValue));
CJ_EXPORT void FfiOHOSAceFrameworkSearchOnContentScroll(void (*callback)(float totalOffsetX, float totalOffsetY));
CJ_EXPORT void FfiOHOSAceFrameworkSearchOnTextSelectionChange(
    void (*callback)(int32_t selectionStart, int32_t selectionEnd));
CJ_EXPORT void FfiOHOSAceFrameworkSearchOnEditChange(void (*callback)(bool value));
CJ_EXPORT void FfiOHOSAceFrameworkSearchSetInputFilter(const char* value, void (*callback)(const char* value));
CJ_EXPORT void FfiOHOSAceFrameworkSearchSetCustomKeyboard(void (*callback)(), bool options);
CJ_EXPORT void FfiOHOSAceFrameworkSearchEditMenuOptions(void* (*callbackOnCreateMenu)(void* vecTextMenuItem),
    bool (*callbackOnMenuItemClick)(FFiSearchTextMenuItem textMenuItem, int32_t start, int32_t end));
CJ_EXPORT SearchTextMenuItemHandle FfiOHOSAceFrameworkSearchCreateTextMenuItem(int64_t size);
CJ_EXPORT void FfiOHOSAceFrameworkSearchTextMenuItemDelete(SearchTextMenuItemHandle vec);
CJ_EXPORT void FfiOHOSAceFrameworkSearchTextMenuItemSetElement(
    SearchTextMenuItemHandle vec, int64_t index, FFiSearchTextMenuItem textMenuItem);
CJ_EXPORT FFiSearchTextMenuItem FfiOHOSAceFrameworkSearchTextMenuItemGetElement(
    SearchTextMenuItemHandle vec, int64_t index);
CJ_EXPORT int64_t FfiOHOSAceFrameworkSearchTextMenuItemGetSize(SearchTextMenuItemHandle vec);
CJ_EXPORT CJRectResult FfiOHOSAceFrameworkSearchGetTextContentRect(int64_t id);
CJ_EXPORT int32_t FfiOHOSAceFrameworkSearchGetTextContentLineCount(int64_t id);
CJ_EXPORT CJCaretOffset FfiOHOSAceFrameworkSearchGetCaretOffset(int64_t id);
}

#endif // OHOS_ACE_FRAMEWORK_CJ_SCROLLBAR_FFI_H
