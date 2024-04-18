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
#include "core/components/common/layout/constants.h"
#include "core/components/text_field/textfield_theme.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "core/components/search/search_theme.h"
#include "base/utils/string_utils.h"

namespace OHOS::Ace::NG {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int NUM_4 = 4;
const std::vector<TextAlign> TEXT_ALIGNS = { TextAlign::START, TextAlign::CENTER, TextAlign::END };
constexpr TextDecorationStyle DEFAULT_DECORATION_STYLE = TextDecorationStyle::SOLID;

ArkUINativeModuleValue SearchBridge::SetTextFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> threeArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> fourArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> fiveArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    const char* fontFamilies[1];
    struct ArkUIFontStruct value = {
        0.0, 0, static_cast<ArkUI_Int32>(FontWeight::NORMAL), INVALID_FONT_STYLE, fontFamilies, 0 };
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, panda::JSValueRef::Undefined(vm));
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipelineContext, panda::JSValueRef::Undefined(vm));
    auto themeManager = pipelineContext->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, panda::JSValueRef::Undefined(vm));
    auto theme = themeManager->GetTheme<SearchTheme>();
    CHECK_NULL_RETURN(theme, panda::JSValueRef::Undefined(vm));
    auto themeFontSize = theme->GetFontSize();
    CalcDimension size = themeFontSize;
    if (secondArg->IsNull() || secondArg->IsUndefined() ||
        !ArkTSUtils::ParseJsDimensionVpNG(vm, secondArg, size) || size.Unit() == DimensionUnit::PERCENT
        || LessNotEqual(size.Value(), 0.0)) {
        value.fontSizeNumber = themeFontSize.Value();
        value.fontSizeUnit = static_cast<int8_t>(themeFontSize.Unit());
    } else {
        ArkTSUtils::ParseJsDimensionFp(vm, secondArg, size);
        value.fontSizeNumber = size.Value();
        value.fontSizeUnit = static_cast<int8_t>(size.Unit());
    }

    if (threeArg->IsString() || threeArg->IsNumber()) {
        if (threeArg->IsString()) {
            auto weightStr = threeArg->ToString(vm)->ToString();
            value.fontWeight = static_cast<ArkUI_Int32>(OHOS::Ace::Framework::ConvertStrToFontWeight(weightStr));
        }

        if (threeArg->IsNumber()) {
            auto weightStr = std::to_string(threeArg->Int32Value(vm));
            value.fontWeight =
                static_cast<ArkUI_Int32>(OHOS::Ace::Framework::ConvertStrToFontWeight(weightStr, FontWeight::W400));
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

    GetArkUINodeModifiers()->getSearchModifier()->setSearchTextFont(nativeNode, &value);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetTextFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSearchModifier()->resetSearchTextFont(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetPlaceholderColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Color color;
    uint32_t result;
    if (ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color)) {
        result = color.GetValue();
        GetArkUINodeModifiers()->getSearchModifier()->setSearchPlaceholderColor(nativeNode, result);
    } else {
        GetArkUINodeModifiers()->getSearchModifier()->resetSearchPlaceholderColor(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SearchBridge::ResetPlaceholderColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSearchModifier()->resetSearchPlaceholderColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetSelectionMenuHidden(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsBoolean()) {
        uint32_t selectionMenuHidden = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
        GetArkUINodeModifiers()->getSearchModifier()->setSearchSelectionMenuHidden(nativeNode, selectionMenuHidden);
    } else {
        GetArkUINodeModifiers()->getSearchModifier()->resetSearchSelectionMenuHidden(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetSelectionMenuHidden(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSearchModifier()->resetSearchSelectionMenuHidden(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetCaretStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> caretWidthArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> caretColorArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

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
    GetArkUINodeModifiers()->getSearchModifier()->setSearchCaretStyle(
        nativeNode, caretWidth.Value(), static_cast<int8_t>(caretWidth.Unit()), caretColor);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetCaretStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSearchModifier()->resetSearchCaretStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetSearchTextAlign(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    if (secondArg->IsNumber()) {
        int32_t value = secondArg->Int32Value(vm);
        if (value >= 0 && value < static_cast<int32_t>(TEXT_ALIGNS.size())) {
            GetArkUINodeModifiers()->getSearchModifier()->setSearchTextAlign(nativeNode, value);
        }
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetSearchTextAlign(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSearchModifier()->resetSearchTextAlign(nativeNode);
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
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
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
    GetArkUINodeModifiers()->getSearchModifier()->setSearchCancelButton(nativeNode, style, &size, color, src);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetCancelButton(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSearchModifier()->resetSearchCancelButton(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetEnableKeyboardOnFocus(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    if (secondArg->IsBoolean()) {
        uint32_t value = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
        GetArkUINodeModifiers()->getSearchModifier()->setSearchEnableKeyboardOnFocus(nativeNode, value);
    } else {
        GetArkUINodeModifiers()->getSearchModifier()->resetSearchEnableKeyboardOnFocus(nativeNode);
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetEnableKeyboardOnFocus(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSearchModifier()->resetSearchEnableKeyboardOnFocus(nativeNode);
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
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    const char* fontFamilies[1];
    struct ArkUIFontStruct value = {
        0.0, 0, static_cast<ArkUI_Int32>(FontWeight::NORMAL), INVALID_FONT_STYLE, fontFamilies, 0 };
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
            value.fontWeight = static_cast<ArkUI_Int32>(OHOS::Ace::Framework::ConvertStrToFontWeight(weightStr));
        }

        if (threeArg->IsNumber()) {
            auto weightStr = std::to_string(threeArg->Int32Value(vm));
            value.fontWeight =
                static_cast<ArkUI_Int32>(OHOS::Ace::Framework::ConvertStrToFontWeight(weightStr, FontWeight::W400));
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
    GetArkUINodeModifiers()->getSearchModifier()->setSearchPlaceholderFont(nativeNode, &value);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetPlaceholderFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSearchModifier()->resetSearchPlaceholderFont(nativeNode);
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
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

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

    GetArkUINodeModifiers()->getSearchModifier()->setSearchSearchIcon(nativeNode, &value);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetSearchIcon(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSearchModifier()->resetSearchSearchIcon(nativeNode);
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
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

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
    GetArkUINodeModifiers()->getSearchModifier()->setSearchSearchButton(nativeNode, &value);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetSearchButton(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSearchModifier()->resetSearchSearchButton(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetFontColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
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
    GetArkUINodeModifiers()->getSearchModifier()->setSearchFontColor(nativeNode, color);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetFontColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSearchModifier()->resetSearchFontColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetCopyOption(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    
    auto copyOptions = CopyOptions::Local;
    uint32_t value = static_cast<uint32_t>(copyOptions);
    if (secondArg->IsNumber()) {
        value = secondArg->Uint32Value(vm);
    } else if (!secondArg->IsNumber() && !secondArg->IsUndefined()) {
        copyOptions = CopyOptions::None;
        value = static_cast<uint32_t>(copyOptions);
    }
    GetArkUINodeModifiers()->getSearchModifier()->setSearchCopyOption(nativeNode, value);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetCopyOption(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSearchModifier()->resetSearchCopyOption(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetSearchEnterKeyType(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    if (secondArg->IsNumber()) {
        int32_t value = secondArg->Int32Value(vm);
        GetArkUINodeModifiers()->getSearchModifier()->setSearchEnterKeyType(nativeNode, value);
    } else {
        GetArkUINodeModifiers()->getSearchModifier()->resetSearchEnterKeyType(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetSearchEnterKeyType(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSearchModifier()->resetSearchEnterKeyType(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetSearchHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(1);
    CalcDimension height;
    std::string calcStr;
    if (!ArkTSUtils::ParseJsDimensionVpNG(vm, valueArg, height)) {
        GetArkUINodeModifiers()->getCommonModifier()->resetHeight(nativeNode);
    } else {
        if (LessNotEqual(height.Value(), 0.0)) {
            height.SetValue(0.0);
        }
        if (height.Unit() == DimensionUnit::CALC) {
            GetArkUINodeModifiers()->getCommonModifier()->setHeight(
                nativeNode, height.Value(), static_cast<int>(height.Unit()), height.CalcValue().c_str());
        } else {
            GetArkUINodeModifiers()->getCommonModifier()->setHeight(
                nativeNode, height.Value(), static_cast<int>(height.Unit()), calcStr.c_str());
        }
        GetArkUINodeModifiers()->getSearchModifier()->setSearchHeight(
            nativeNode, height.Value(), static_cast<int>(height.Unit()));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetSearchHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSearchModifier()->resetSearchHeight(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetSearchInspectorId(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsString()) {
        std::string stringValue = secondArg->ToString(vm)->ToString();
        GetArkUINodeModifiers()->getSearchModifier()->setSearchInspectorId(nativeNode, stringValue.c_str());
    } else {
        GetArkUINodeModifiers()->getSearchModifier()->resetSearchInspectorId(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetSearchInspectorId(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSearchModifier()->resetSearchInspectorId(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetSearchMinFontSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CalcDimension value;
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, panda::NativePointerRef::New(vm, nullptr));
    auto theme = pipelineContext->GetTheme<SearchTheme>();
    CHECK_NULL_RETURN(theme, panda::NativePointerRef::New(vm, nullptr));
    if (!ArkTSUtils::ParseJsDimensionNG(vm, valueArg, value, DimensionUnit::FP, false)) {
        GetArkUINodeModifiers()->getSearchModifier()->resetSearchAdaptMinFontSize(nativeNode);
    } else {
        if (value.IsNegative()) {
            value = theme->GetTextStyle().GetAdaptMinFontSize();
        }
        GetArkUINodeModifiers()->getSearchModifier()->setSearchAdaptMinFontSize(
            nativeNode, value.Value(), static_cast<int32_t>(value.Unit()));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetDecoration(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, panda::JSValueRef::Undefined(vm));
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipelineContext, panda::JSValueRef::Undefined(vm));
    auto themeManager = pipelineContext->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, panda::JSValueRef::Undefined(vm));
    auto theme = themeManager->GetTheme<SearchTheme>();
    CHECK_NULL_RETURN(theme, panda::JSValueRef::Undefined(vm));
    Color color = theme->GetTextStyle().GetTextDecorationColor();
    int32_t searchDecoration = static_cast<int32_t>(theme->GetTextStyle().GetTextDecoration());
    if (secondArg->IsInt()) {
        searchDecoration = secondArg->Int32Value(vm);
    }
    ArkTSUtils::ParseJsColorAlpha(vm, thirdArg, color, Color::BLACK);
    int32_t textDecorationStyle = static_cast<int32_t>(DEFAULT_DECORATION_STYLE);
    GetArkUINodeModifiers()->getSearchModifier()->setSearchDecoration(
        nativeNode, searchDecoration, color.GetValue(), textDecorationStyle);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetDecoration(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSearchModifier()->resetSearchDecoration(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetLetterSpacing(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CalcDimension value;
    if (!ArkTSUtils::ParseJsDimensionNG(vm, valueArg, value, DimensionUnit::FP, false)) {
        GetArkUINodeModifiers()->getSearchModifier()->resetSearchLetterSpacing(nativeNode);
    } else {
        GetArkUINodeModifiers()->getSearchModifier()->setSearchLetterSpacing(
            nativeNode, value.Value(), static_cast<int>(value.Unit()));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetLetterSpacing(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSearchModifier()->resetSearchLetterSpacing(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetLineHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CalcDimension value;
    if (!ArkTSUtils::ParseJsDimensionNG(vm, valueArg, value, DimensionUnit::FP, true)) {
        GetArkUINodeModifiers()->getSearchModifier()->resetSearchLineHeight(nativeNode);
    } else {
        if (value.IsNegative()) {
            value.Reset();
        }
        GetArkUINodeModifiers()->getSearchModifier()->setSearchLineHeight(
            nativeNode, value.Value(), static_cast<int>(value.Unit()));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetSearchMinFontSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSearchModifier()->resetSearchAdaptMinFontSize(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetSearchMaxFontSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CalcDimension value;
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, panda::NativePointerRef::New(vm, nullptr));
    auto theme = pipelineContext->GetTheme<SearchTheme>();
    CHECK_NULL_RETURN(theme, panda::NativePointerRef::New(vm, nullptr));
    if (!ArkTSUtils::ParseJsDimensionNG(vm, valueArg, value, DimensionUnit::FP, false)) {
        GetArkUINodeModifiers()->getSearchModifier()->resetSearchAdaptMaxFontSize(nativeNode);
    } else {
        if (value.IsNegative()) {
            value = theme->GetTextStyle().GetAdaptMaxFontSize();
        }
        GetArkUINodeModifiers()->getSearchModifier()->setSearchAdaptMaxFontSize(
            nativeNode, value.Value(), static_cast<int32_t>(value.Unit()));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetLineHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSearchModifier()->resetSearchLineHeight(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetFontFeature(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsString()) {
        auto value = secondArg->ToString(vm)->ToString();
        GetArkUINodeModifiers()->getSearchModifier()->setSearchFontFeature(nativeNode, value.c_str());
    } else {
        GetArkUINodeModifiers()->getSearchModifier()->resetSearchFontFeature(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetFontFeature(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSearchModifier()->resetSearchFontFeature(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SearchBridge::ResetSearchMaxFontSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSearchModifier()->resetSearchAdaptMaxFontSize(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
