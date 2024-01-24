/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_search_bridge.h"

#include "base/geometry/dimension.h"
#include "base/utils/utils.h"
#include "core/interfaces/native/node/api.h"
#include "core/components/common/layout/constants.h"
#include "core/components/text_field/textfield_theme.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "core/components/search/search_theme.h"

namespace OHOS::Ace::NG {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int NUM_4 = 4;
const std::vector<TextAlign> TEXT_ALIGNS = { TextAlign::START, TextAlign::CENTER, TextAlign::END };

ArkUINativeModuleValue SearchBridge::SetTextFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> threeArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> fourArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> fiveArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();

    const char* fontFamilies[1];
    struct ArkUIFontStruct value = {0.0, 0, 0, INVALID_FONT_STYLE, fontFamilies, 0};
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, panda::JSValueRef::Undefined(vm));
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipelineContext, panda::JSValueRef::Undefined(vm));
    auto themeManager = pipelineContext->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, panda::JSValueRef::Undefined(vm));
    auto theme = themeManager->GetTheme<SearchTheme>();
    CHECK_NULL_RETURN(theme, panda::JSValueRef::Undefined(vm));
    auto themeFontSize = theme->GetFontSize();
    CalcDimension size;
    if (secondArg->IsNull() || secondArg->IsUndefined() ||
        !ArkTSUtils::ParseJsDimensionFp(vm, secondArg, size) || size.Unit() == DimensionUnit::PERCENT) {
        value.fontSizeNumber = themeFontSize.Value();
        value.fontSizeUnit = static_cast<int8_t>(themeFontSize.Unit());
    } else {
        value.fontSizeNumber = size.Value();
        value.fontSizeUnit = static_cast<int8_t>(size.Unit());
    }

    if (threeArg->IsString() || threeArg->IsNumber()) {
        if (threeArg->IsString()) {
            auto weightStr = threeArg->ToString(vm)->ToString();
            value.fontWeight = std::stoi(weightStr);
        }

        if (threeArg->IsNumber()) {
            value.fontWeight = threeArg->Int32Value(vm);
        }
    }

    if (fourArg->IsString()) {
        auto familyStr = fourArg->ToString(vm)->ToString();
        value.fontFamilies[0] = familyStr.c_str();
        value.familyLength = 1;
    }

    if (!fiveArg->IsNull() && fiveArg->IsNumber()) {
        value.fontStyle = fiveArg->Int32Value(vm);
    }

    GetArkUIInternalNodeAPI()->GetSearchModifier().SetSearchTextFont(nativeNode, &value);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetTextFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSearchModifier().ResetSearchTextFont(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetPlaceholderColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    Color color;
    uint32_t result;
    if (ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color)) {
        result = color.GetValue();
        GetArkUIInternalNodeAPI()->GetSearchModifier().SetSearchPlaceholderColor(nativeNode, result);
    } else {
        GetArkUIInternalNodeAPI()->GetSearchModifier().ResetSearchPlaceholderColor(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SearchBridge::ResetPlaceholderColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSearchModifier().ResetSearchPlaceholderColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetSelectionMenuHidden(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    if (secondArg->IsBoolean()) {
        uint32_t selectionMenuHidden = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
        GetArkUIInternalNodeAPI()->GetSearchModifier().SetSearchSelectionMenuHidden(nativeNode, selectionMenuHidden);
    } else {
        GetArkUIInternalNodeAPI()->GetSearchModifier().ResetSearchSelectionMenuHidden(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetSelectionMenuHidden(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSearchModifier().ResetSearchSelectionMenuHidden(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetCaretStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> caretWidthArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> caretColorArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();

    auto textFieldTheme = ArkTSUtils::GetTheme<TextFieldTheme>();
    CHECK_NULL_RETURN(textFieldTheme, panda::JSValueRef::Undefined(vm));
    CalcDimension caretWidth = textFieldTheme->GetCursorWidth();
    if (!ArkTSUtils::ParseJsDimensionVpNG(vm, caretWidthArg, caretWidth, false) ||
            LessNotEqual(caretWidth.Value(), 0.0)) {
        caretWidth = textFieldTheme->GetCursorWidth();
    }
    Color color;
    uint32_t caretColor;
    if (ArkTSUtils::ParseJsColorAlpha(vm, caretColorArg, color)) {
        caretColor = color.GetValue();
    } else {
        caretColor = textFieldTheme->GetCursorColor().GetValue();
    }
    GetArkUIInternalNodeAPI()->GetSearchModifier().SetSearchCaretStyle(
        nativeNode, caretWidth.Value(), static_cast<int8_t>(caretWidth.Unit()), caretColor);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetCaretStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSearchModifier().ResetSearchCaretStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetSearchTextAlign(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();

    if (secondArg->IsNumber()) {
        int32_t value = secondArg->Int32Value(vm);
        if (value >= 0 && value < static_cast<int32_t>(TEXT_ALIGNS.size())) {
            GetArkUIInternalNodeAPI()->GetSearchModifier().SetSearchTextAlign(nativeNode, value);
        }
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetSearchTextAlign(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSearchModifier().ResetSearchTextAlign(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

static CancelButtonStyle ConvertStrToCancelButtonStyle(const std::string& value)
{
    if (value == "CONSTANT") {
        return CancelButtonStyle::CONSTANT;
    } else if (value == "INVISIBLE") {
        return CancelButtonStyle::INVISIBLE;
    } else {
        return CancelButtonStyle::INPUT;
    }
}

ArkUINativeModuleValue SearchBridge::SetCancelButton(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> forthArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> fifthArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, panda::JSValueRef::Undefined(vm));
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipelineContext, panda::JSValueRef::Undefined(vm));
    auto themeManager = pipelineContext->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, panda::JSValueRef::Undefined(vm));
    auto theme = themeManager->GetTheme<SearchTheme>();
    CHECK_NULL_RETURN(theme, panda::JSValueRef::Undefined(vm));
    int32_t style = static_cast<int32_t>(theme->GetCancelButtonStyle());
    if (secondArg->IsString()) {
        CancelButtonStyle cancelButtonStyle = ConvertStrToCancelButtonStyle(secondArg->ToString(vm)->ToString());
        style = static_cast<int32_t>(cancelButtonStyle);
    }
    struct ArkUISizeType size = {0.0, 0};
    CalcDimension iconSize;
    if (!thirdArg->IsUndefined() && !thirdArg->IsNull() &&
        ArkTSUtils::ParseJsDimensionVpNG(vm, thirdArg, iconSize, false)) {
        if (LessNotEqual(iconSize.Value(), 0.0) || iconSize.Unit() == DimensionUnit::PERCENT) {
            iconSize = theme->GetIconHeight();
        }
    } else {
        iconSize = theme->GetIconHeight();
    }
    size.value = iconSize.Value();
    size.unit = static_cast<int8_t>(iconSize.Unit());
    Color value;
    uint32_t color;
    if (!forthArg->IsUndefined() && !forthArg->IsNull() &&
        ArkTSUtils::ParseJsColorAlpha(vm, forthArg, value)) {
        color = value.GetValue();
    } else {
        color = theme->GetSearchIconColor().GetValue();
    }
    std::string srcStr;
    if (fifthArg->IsUndefined() || fifthArg->IsNull() ||
        !ArkTSUtils::ParseJsMedia(vm, fifthArg, srcStr)) {
        srcStr = "";
    }
    const char* src = srcStr.c_str();
    GetArkUIInternalNodeAPI()->GetSearchModifier().SetSearchCancelButton(nativeNode, style, &size, color, src);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetCancelButton(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSearchModifier().ResetSearchCancelButton(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetEnableKeyboardOnFocus(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();

    if (secondArg->IsBoolean()) {
        uint32_t value = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
        GetArkUIInternalNodeAPI()->GetSearchModifier().SetSearchEnableKeyboardOnFocus(nativeNode, value);
    } else {
        GetArkUIInternalNodeAPI()->GetSearchModifier().ResetSearchEnableKeyboardOnFocus(nativeNode);
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetEnableKeyboardOnFocus(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSearchModifier().ResetSearchEnableKeyboardOnFocus(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetPlaceholderFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> threeArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> fourArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> fiveArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();

    const char* fontFamilies[1];
    struct ArkUIFontStruct value = {0.0, 0, 0, INVALID_FONT_STYLE, fontFamilies, 0};
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, panda::JSValueRef::Undefined(vm));
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipelineContext, panda::JSValueRef::Undefined(vm));
    auto themeManager = pipelineContext->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, panda::JSValueRef::Undefined(vm));
    auto theme = themeManager->GetTheme<SearchTheme>();
    CHECK_NULL_RETURN(theme, panda::JSValueRef::Undefined(vm));
    auto themeFontSize = theme->GetFontSize();
    CalcDimension size;
    if (secondArg->IsNull() || secondArg->IsUndefined() ||
        !ArkTSUtils::ParseJsDimensionFp(vm, secondArg, size) || size.Unit() == DimensionUnit::PERCENT) {
        value.fontSizeNumber = themeFontSize.Value();
        value.fontSizeUnit = static_cast<int8_t>(themeFontSize.Unit());
    } else {
        value.fontSizeNumber = size.Value();
        value.fontSizeUnit = static_cast<int8_t>(size.Unit());
    }

    if (threeArg->IsString() || threeArg->IsNumber()) {
        if (threeArg->IsString()) {
            auto weightStr = threeArg->ToString(vm)->ToString();
            value.fontWeight = std::stoi(weightStr);
        }

        if (threeArg->IsNumber()) {
            value.fontWeight = threeArg->Int32Value(vm);
        }
    }

    if (fourArg->IsString()) {
        auto familyStr = fourArg->ToString(vm)->ToString();
        value.fontFamilies[0] = familyStr.c_str();
        value.familyLength = 1;
    }

    if (!fiveArg->IsNull() && fiveArg->IsNumber()) {
        value.fontStyle = fiveArg->Int32Value(vm);
    }
    GetArkUIInternalNodeAPI()->GetSearchModifier().SetSearchPlaceholderFont(nativeNode, &value);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetPlaceholderFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSearchModifier().ResetSearchPlaceholderFont(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetSearchIcon(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> threeArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> fourArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();

    struct ArkUIIconOptionsStruct value = {0.0, 0, INVALID_COLOR_VALUE, nullptr};

    CalcDimension size;
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, panda::JSValueRef::Undefined(vm));
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipelineContext, panda::JSValueRef::Undefined(vm));
    auto themeManager = pipelineContext->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, panda::JSValueRef::Undefined(vm));
    auto theme = themeManager->GetTheme<SearchTheme>();
    CHECK_NULL_RETURN(theme, panda::JSValueRef::Undefined(vm));
    if (!secondArg->IsUndefined() && !secondArg->IsNull() &&
        ArkTSUtils::ParseJsDimensionVpNG(vm, secondArg, size, false)) {
        if (LessNotEqual(size.Value(), 0.0) || size.Unit() == DimensionUnit::PERCENT) {
            size = theme->GetIconHeight();
        }
    } else {
        size = theme->GetIconHeight();
    }
    value.value = size.Value();
    value.unit = static_cast<int8_t>(size.Unit());

    Color color;
    if (ArkTSUtils::ParseJsColorAlpha(vm, threeArg, color)) {
        value.color = static_cast<int32_t>(color.GetValue());
    } else {
        value.color = INVALID_COLOR_VALUE;
    }

    std::string srcStr;
    if (fourArg->IsUndefined() || fourArg->IsNull() || !ArkTSUtils::ParseJsMedia(vm, fourArg, srcStr)) {
        srcStr = "";
    }
    value.src = srcStr.c_str();

    GetArkUIInternalNodeAPI()->GetSearchModifier().SetSearchSearchIcon(nativeNode, &value);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetSearchIcon(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSearchModifier().ResetSearchSearchIcon(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetSearchButton(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> threeArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> fourArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();

    struct ArkUISearchButtonOptionsStruct value = {"", 0.0, 0, INVALID_COLOR_VALUE};
    
    std::string valueString = "";
    if (secondArg->IsString()) {
        valueString = secondArg->ToString(vm)->ToString();
        value.value = valueString.c_str();
    }

    auto container = Container::Current();
    CHECK_NULL_RETURN(container, panda::JSValueRef::Undefined(vm));
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipelineContext, panda::JSValueRef::Undefined(vm));
    auto themeManager = pipelineContext->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, panda::JSValueRef::Undefined(vm));
    auto theme = themeManager->GetTheme<SearchTheme>();
    CHECK_NULL_RETURN(theme, panda::JSValueRef::Undefined(vm));
    CalcDimension size = theme->GetFontSize();
    if (ArkTSUtils::ParseJsDimensionVpNG(vm, threeArg, size) && size.Unit() != DimensionUnit::PERCENT &&
        GreatOrEqual(size.Value(), 0.0)) {
        ArkTSUtils::ParseJsDimensionFp(vm, threeArg, size);
    } else {
        size = theme->GetFontSize();
    }
    value.sizeValue = size.Value();
    value.sizeUnit = static_cast<int8_t>(size.Unit());

    Color fontColor;
    if (ArkTSUtils::ParseJsColorAlpha(vm, fourArg, fontColor)) {
        value.fontColor = static_cast<int32_t>(fontColor.GetValue());
    } else {
        value.fontColor = static_cast<int32_t>(theme->GetSearchButtonTextColor().GetValue());
    }
    GetArkUIInternalNodeAPI()->GetSearchModifier().SetSearchSearchButton(nativeNode, &value);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetSearchButton(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSearchModifier().ResetSearchSearchButton(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetFontColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, panda::JSValueRef::Undefined(vm));
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipelineContext, panda::JSValueRef::Undefined(vm));
    auto themeManager = pipelineContext->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, panda::JSValueRef::Undefined(vm));
    auto theme = themeManager->GetTheme<SearchTheme>();
    CHECK_NULL_RETURN(theme, panda::JSValueRef::Undefined(vm));
    Color value;
    uint32_t color = theme->GetTextColor().GetValue();
    if (ArkTSUtils::ParseJsColorAlpha(vm, secondArg, value)) {
        color = value.GetValue();
    }
    GetArkUIInternalNodeAPI()->GetSearchModifier().SetSearchFontColor(nativeNode, color);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetFontColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSearchModifier().ResetSearchFontColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetCopyOption(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    
    auto copyOptions = CopyOptions::Local;
    uint32_t value = static_cast<uint32_t>(copyOptions);
    if (secondArg->IsNumber()) {
        value = secondArg->Uint32Value(vm);
    } else if (!secondArg->IsNumber() && !secondArg->IsUndefined()) {
        copyOptions = CopyOptions::None;
        value = static_cast<uint32_t>(copyOptions);
    }
    GetArkUIInternalNodeAPI()->GetSearchModifier().SetSearchCopyOption(nativeNode, value);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetCopyOption(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSearchModifier().ResetSearchCopyOption(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetSearchHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(1);
    CalcDimension height;
    std::string calcStr;
    if (!ArkTSUtils::ParseJsDimensionVpNG(vm, valueArg, height)) {
        GetArkUIInternalNodeAPI()->GetCommonModifier().ResetHeight(nativeNode);
    } else {
        if (LessNotEqual(height.Value(), 0.0)) {
            height.SetValue(0.0);
        }
        if (height.Unit() == DimensionUnit::CALC) {
            GetArkUIInternalNodeAPI()->GetCommonModifier().SetHeight(
                nativeNode, height.Value(), static_cast<int>(height.Unit()), height.CalcValue().c_str());
        } else {
            GetArkUIInternalNodeAPI()->GetCommonModifier().SetHeight(
                nativeNode, height.Value(), static_cast<int>(height.Unit()), calcStr.c_str());
        }
        GetArkUIInternalNodeAPI()->GetSearchModifier().SetSearchHeight(
            nativeNode, height.Value(), static_cast<int>(height.Unit()));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetSearchHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSearchModifier().ResetSearchHeight(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
