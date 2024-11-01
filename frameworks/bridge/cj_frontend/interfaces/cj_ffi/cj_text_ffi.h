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

#ifndef OHOS_ACE_FRAMEWORK_CJ_TEXT_FFI_H
#define OHOS_ACE_FRAMEWORK_CJ_TEXT_FFI_H

#include <cstdint>
#include <string>

#include "bridge/cj_frontend/cppview/view_abstract.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_common_ffi.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_view_abstract_ffi.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/text/text_controller.h"
#include "core/components_ng/pattern/text/text_model.h"

namespace OHOS::Ace::Framework {

class ACE_EXPORT NGNativeTextController : public OHOS::FFI::FFIData {
    DECL_TYPE(NGNativeTextController, OHOS::FFI::FFIData)

public:
    NGNativeTextController();

    void CloseSelectionMenu();
    void SetController(const RefPtr<TextControllerBase>& controller)
    {
        controller_ = controller;
    }

private:
    RefPtr<TextControllerBase> controller_;
};
} // namespace OHOS::Ace::Framework

#ifdef __cplusplus
extern "C" {
#endif

using VectorStringPtr = void*;
using VectorNativeShadowOptionsHandle = void*;
using VectorTextMenuItemHandle = void*;

struct NativeShadowOptions {
    double radius;
    uint32_t shadowType;
    uint32_t color;
    double offsetX;
    double offsetY;
    bool fill;
};

CJ_EXPORT void FfiOHOSAceFrameworkTextCreate(const char* content);
CJ_EXPORT void FfiOHOSAceFrameworkTextCreateWithController(const char* content, int64_t controllerId);
CJ_EXPORT void FfiOHOSAceFrameworkTextSetWidth(double width, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkTextSetHeight(double height, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkTextSetFontSize(double fontSize, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkTextSetFontWeight(const char* fontWeight);
CJ_EXPORT void FfiOHOSAceFrameworkTextSetFontColor(uint32_t textColor);
CJ_EXPORT void FfiOHOSAceFrameworkTextSetTextOverflow(int32_t overflow);
CJ_EXPORT void FfiOHOSAceFrameworkTextSetTextOverflowNew(int32_t overflow);
CJ_EXPORT void FfiOHOSAceFrameworkTextSetMaxLines(int32_t maxLines);
CJ_EXPORT void FfiOHOSAceFrameworkTextSetFontStyle(int32_t fontStyle);
CJ_EXPORT void FfiOHOSAceFrameworkTextSetTextAlign(int32_t textAlign);
CJ_EXPORT void FfiOHOSAceFrameworkTextSetLineHeight(double lineHeight, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkTextSetFontFamily(const char* fontFamily);
CJ_EXPORT void FfiOHOSAceFrameworkTextSetDecoration(int32_t typeValue, uint32_t colorValue);
CJ_EXPORT void FfiOHOSAceFrameworkTextSetDecorationNew(int32_t typeValue, uint32_t colorValue, int32_t styleValue);
CJ_EXPORT void FfiOHOSAceFrameworkTextSetMinFontSize(double fontSize, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkTextSetMaxFontSize(double fontSize, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkTextSetTextCase(int32_t textCase);
CJ_EXPORT void FfiOHOSAceFrameworkTextSetBaselineOffset(double baseLine, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkTextOnClick(void (*callback)(CJClickInfo clickInfo));
CJ_EXPORT void FfiTextSetResponseRegion(CJResponseRegion value);
CJ_EXPORT void FfiTextSetResponseRegionArray(VectorStringPtr vecContent);
CJ_EXPORT void FfiOHOSAceFrameworkTextSetFont(
    double fontSize, int32_t unit, const char* fontWeight, const char* fontFamily, int32_t fontStyle);
CJ_EXPORT VectorNativeShadowOptionsHandle FFICJCreateVectorNativeShadowOptions(int64_t size);
CJ_EXPORT void FFICJVectorNativeShadowOptionsDelete(VectorNativeShadowOptionsHandle vec);
CJ_EXPORT void FFICJVectorNativeShadowOptionsSetElement(
    VectorNativeShadowOptionsHandle vec, int64_t index, NativeShadowOptions shadowOptions);
CJ_EXPORT void FfiOHOSAceFrameworkTextShadow(VectorStringPtr vecContent);
CJ_EXPORT void FfiOHOSAceFrameworkTextSetDataDetectorConfig(VectorStringPtr vecContent,
    void (*callback)(const char* value), uint32_t entityColor, int32_t decorationType, uint32_t decorationColor,
    int32_t decorationStyle);
CJ_EXPORT void FfiOHOSAceFrameworkTextHalfLeading(bool value);
CJ_EXPORT void FfiOHOSAceFrameworkTextSetFontFeature(const char* fontFeature);
CJ_EXPORT void FfiOHOSAceFrameworkTextSetLineBreakStrategy(int32_t lineBreakStrategy);
CJ_EXPORT void FfiOHOSAceFrameworkTextSetLineSpacing(double lineSpacing, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkTextSetCopyOption(int32_t copyOption);
CJ_EXPORT void FfiOHOSAceFrameworkTextSetLetterSpacing(double letterSpacing, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkTextMaxFontScale(float maxFontScale);
CJ_EXPORT void FfiOHOSAceFrameworkTextMinFontScale(float minFontScale);
CJ_EXPORT void FfiOHOSAceFrameworkTextSetTextSelectable(int32_t textSelectable);
CJ_EXPORT void FfiOHOSAceFrameworkTextSetHeightAdaptivePolicy(int32_t heightAdaptivePolicy);
CJ_EXPORT void FfiOHOSAceFrameworkTextEditMenuOptions(
    CjOnCreateMenu cjOnCreateMenu, CjOnMenuItemClick cjOnMenuItemClick);
CJ_EXPORT VectorTextMenuItemHandle FFICJCreateVectorFfiTextMenuItem(int64_t size);
CJ_EXPORT void FFICJVectorFfiTextMenuItemDelete(VectorTextMenuItemHandle vec);
CJ_EXPORT void FFICJVectorFfiTextMenuItemSetElement(
    VectorTextMenuItemHandle vec, int64_t index, FfiTextMenuItem textMenuItem);
CJ_EXPORT FfiTextMenuItem FFICJVectorFfiTextMenuItemGetElement(VectorTextMenuItemHandle vec, int64_t index);
CJ_EXPORT int64_t FFICJVectorFfiTextMenuItemGetSize(VectorTextMenuItemHandle vec);
CJ_EXPORT void FfiOHOSAceFrameworkTextEnableDataDetector(bool value);
CJ_EXPORT void FfiOHOSAceFrameworkTextSetWordBreak(int32_t wordBreak);
CJ_EXPORT void FfiOHOSAceFrameworkTextSetSelection(int32_t start, int32_t end);
CJ_EXPORT void FfiOHOSAceFrameworkTextSetTextIndent(double textIndent, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkTextSetEllipsisMode(int32_t ellipsisMode);
CJ_EXPORT void FfiOHOSAceFrameworkTextOnCopy(void (*callback)(const char* value));
CJ_EXPORT void FfiOHOSAceFrameworkTextOnTextSelectionChange(void (*callback)(int32_t start, int32_t end));
CJ_EXPORT void FfiOHOSAceFrameworkTextBindSelectionMenu(int32_t spanType, void (*content)(), int32_t responseType,
    void (*onAppear)(int32_t start, int32_t end), void (*onDisappear)());
CJ_EXPORT void FfiOHOSAceFrameworkTextDraggable(bool value);
CJ_EXPORT void FfiOHOSAceFrameworkTextPrivacySensitive(bool value);
CJ_EXPORT int64_t FfiOHOSAceFrameworkTextControllerCtor();
CJ_EXPORT void FfiOHOSAceFrameworkTextControllerCloseSelectionMenu(int64_t selfID);
#ifdef __cplusplus
}
#endif
#endif // OHOS_ACE_FRAMEWORK_CJ_TEXT_FFI_H
