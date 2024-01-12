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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_select_bridge.h"

#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "core/interfaces/native/node/api.h"

namespace OHOS::Ace::NG {
const int32_t SIZE_OF_TWO = 2;
const std::string FORMAT_FONT = "%s|%s|%s";
const std::string DEFAULT_STR = "-1";

ArkUINativeModuleValue SelectBridge::SelectBridge::SetSpace(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, panda::NativePointerRef::New(vm, nullptr));
    auto selectTheme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_RETURN(selectTheme, panda::NativePointerRef::New(vm, nullptr));

    CalcDimension space;
    if (!ArkTSUtils::ParseJsDimensionVp(vm, secondArg, space)) {
        space = selectTheme->GetContentSpinnerPadding();
    }
    if (LessNotEqual(space.Value(), 0.0) || space.Unit() == DimensionUnit::PERCENT) {
        space = selectTheme->GetContentSpinnerPadding();
    }

    GetArkUIInternalNodeAPI()->GetSelectModifier().SetSpace(
        nativeNode, space.Value(), static_cast<int32_t>(space.Unit()));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::SetValue(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    std::string value;
    ArkTSUtils::ParseJsString(vm, secondArg, value);
    GetArkUIInternalNodeAPI()->GetSelectModifier().SetValue(nativeNode, value.c_str());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::SetSelected(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    int32_t value = 0;
    ArkTSUtils::ParseJsInteger(vm, secondArg, value);
    GetArkUIInternalNodeAPI()->GetSelectModifier().SetSelected(nativeNode, value);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::SetFontColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();

    Color fontColor;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, colorArg, fontColor)) {
        return ResetFontColor(runtimeCallInfo);
    }
    GetArkUIInternalNodeAPI()->GetSelectModifier().SetSelectFontColor(nativeNode, fontColor.GetValue());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::SetSelectedOptionBgColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();

    Color selectedOptionBgColor;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, colorArg, selectedOptionBgColor)) {
        return ResetSelectedOptionBgColor(runtimeCallInfo);
    }

    GetArkUIInternalNodeAPI()->GetSelectModifier().SetSelectedOptionBgColor(
        nativeNode, selectedOptionBgColor.GetValue());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::SetOptionBgColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();

    Color optionBgColor;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, colorArg, optionBgColor)) {
        return ResetOptionBgColor(runtimeCallInfo);
    }
    GetArkUIInternalNodeAPI()->GetSelectModifier().SetOptionBgColor(nativeNode, optionBgColor.GetValue());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::SetOptionFontColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();

    Color optionFontColor;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, colorArg, optionFontColor)) {
        return ResetOptionFontColor(runtimeCallInfo);
    }
    GetArkUIInternalNodeAPI()->GetSelectModifier().SetOptionFontColor(nativeNode, optionFontColor.GetValue());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::SetSelectedOptionFontColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    Color optionFontColor;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, colorArg, optionFontColor)) {
        return ResetSelectedOptionFontColor(runtimeCallInfo);
    }
    GetArkUIInternalNodeAPI()->GetSelectModifier().SetSelectedOptionFontColor(nativeNode, optionFontColor.GetValue());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::SelectBridge::SetArrowPosition(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    int32_t arrowPosition = secondArg->Int32Value(vm);
    GetArkUIInternalNodeAPI()->GetSelectModifier().SetArrowPosition(nativeNode, arrowPosition);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::SetMenuAlign(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> alignTypeArg = runtimeCallInfo->GetCallArgRef(1); // 1: index of alignType
    Local<JSValueRef> offsetDx = runtimeCallInfo->GetCallArgRef(2);     // 2: index of offset Dx
    Local<JSValueRef> offsetDy = runtimeCallInfo->GetCallArgRef(3);     // 3: index of offset Dy
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();

    int32_t alignType = 0;
    if (alignTypeArg->IsNumber()) {
        alignType = alignTypeArg->Int32Value(vm);
    }

    CalcDimension menuAlignOffsetDx = Dimension(0.0);
    CalcDimension menuAlignOffsetDy = Dimension(0.0);
    if (offsetDx->IsNull() || !ArkTSUtils::ParseJsDimensionVp(vm, offsetDx, menuAlignOffsetDx)) {
        menuAlignOffsetDx = Dimension(0.0);
    }

    if (offsetDy->IsNull() || !ArkTSUtils::ParseJsDimensionVp(vm, offsetDy, menuAlignOffsetDy)) {
        menuAlignOffsetDy = Dimension(0.0);
    }

    uint32_t size = SIZE_OF_TWO;
    float values[size];
    int32_t units[size];
    values[0] = menuAlignOffsetDx.Value();
    units[0] = static_cast<int32_t>(menuAlignOffsetDx.Unit());
    values[1] = menuAlignOffsetDy.Value();
    units[1] = static_cast<int32_t>(menuAlignOffsetDy.Unit());
    GetArkUIInternalNodeAPI()->GetSelectModifier().SetMenuAlign(nativeNode, alignType, values, units, SIZE_OF_TWO);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::SetFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> fontSizeArg = runtimeCallInfo->GetCallArgRef(1);   // 1： index of font size value
    Local<JSValueRef> fontWeightArg = runtimeCallInfo->GetCallArgRef(2); // 2: index of font weight value
    Local<JSValueRef> fontFamilyArg = runtimeCallInfo->GetCallArgRef(3); // 3: index of font family value
    Local<JSValueRef> styleArg = runtimeCallInfo->GetCallArgRef(4);      // 4: index of font style value
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();

    std::string fontSizeStr = DEFAULT_STR;
    CalcDimension fontSize;
    if (!fontSizeArg->IsNull() && !fontSizeArg->IsUndefined() &&
        ArkTSUtils::ParseJsDimensionFp(vm, fontSizeArg, fontSize)) {
        fontSizeStr = fontSize.ToString();
    }

    std::string fontWeight = DEFAULT_STR;
    if (!fontWeightArg->IsNull() && !fontWeightArg->IsUndefined()) {
        if (fontWeightArg->IsNumber()) {
            fontWeight = std::to_string(fontWeightArg->Int32Value(vm));
        } else {
            if (!ArkTSUtils::ParseJsString(vm, fontWeightArg, fontWeight) || fontWeight.empty()) {
                fontWeight = DEFAULT_STR;
            }
        }
    }
    std::string fontFamily;
    if (!ArkTSUtils::ParseJsFontFamiliesToString(vm, fontFamilyArg, fontFamily) || fontFamily.empty()) {
        fontFamily = DEFAULT_STR;
    }
    int32_t styleVal = 0;
    if (!styleArg->IsNull() && !styleArg->IsUndefined() && styleArg->IsNumber()) {
        styleVal = styleArg->Int32Value(vm);
    }

    std::string fontInfo =
        StringUtils::FormatString(FORMAT_FONT.c_str(), fontSizeStr.c_str(), fontWeight.c_str(), fontFamily.c_str());

    GetArkUIInternalNodeAPI()->GetSelectModifier().SetFont(nativeNode, fontInfo.c_str(), styleVal);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::SetOptionFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> fontSizeArg = runtimeCallInfo->GetCallArgRef(1);   // 1： index of font size value
    Local<JSValueRef> fontWeightArg = runtimeCallInfo->GetCallArgRef(2); // 2: index of font weight value
    Local<JSValueRef> fontFamilyArg = runtimeCallInfo->GetCallArgRef(3); // 3: index of font family value
    Local<JSValueRef> styleArg = runtimeCallInfo->GetCallArgRef(4);      // 4: index of font style value
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, panda::NativePointerRef::New(vm, nullptr));
    auto selectTheme = pipeline->GetTheme<SelectTheme>();

    CalcDimension fontSize;
    if (fontSizeArg->IsNull() || fontSizeArg->IsUndefined() ||
        !ArkTSUtils::ParseJsDimensionFp(vm, fontSizeArg, fontSize)) {
        fontSize = selectTheme->GetMenuFontSize();
    }

    std::string fontWeight = DEFAULT_STR;
    if (!fontWeightArg->IsNull() && !fontWeightArg->IsUndefined()) {
        if (fontWeightArg->IsNumber()) {
            fontWeight = std::to_string(fontWeightArg->Int32Value(vm));
        } else {
            if (!ArkTSUtils::ParseJsString(vm, fontWeightArg, fontWeight) || fontWeight.empty()) {
                fontWeight = DEFAULT_STR;
            }
        }
    }
    std::string fontFamily;
    if (!ArkTSUtils::ParseJsFontFamiliesToString(vm, fontFamilyArg, fontFamily) || fontFamily.empty()) {
        fontFamily = DEFAULT_STR;
    }
    int32_t styleVal = 0;
    if (!styleArg->IsNull() && !styleArg->IsUndefined() && styleArg->IsNumber()) {
        styleVal = styleArg->Int32Value(vm);
    }
    std::string fontSizeStr = fontSize.ToString();
    std::string fontInfo =
        StringUtils::FormatString(FORMAT_FONT.c_str(), fontSizeStr.c_str(), fontWeight.c_str(), fontFamily.c_str());

    GetArkUIInternalNodeAPI()->GetSelectModifier().SetOptionFont(nativeNode, fontInfo.c_str(), styleVal);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::SetSelectedOptionFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> fontSizeArg = runtimeCallInfo->GetCallArgRef(1);   // 1： index of font size value
    Local<JSValueRef> fontWeightArg = runtimeCallInfo->GetCallArgRef(2); // 2: index of font weight value
    Local<JSValueRef> fontFamilyArg = runtimeCallInfo->GetCallArgRef(3); // 3: index of font family value
    Local<JSValueRef> styleArg = runtimeCallInfo->GetCallArgRef(4);      // 4: index of font style value
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();

    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, panda::NativePointerRef::New(vm, nullptr));
    auto selectTheme = pipeline->GetTheme<SelectTheme>();

    CalcDimension fontSize;
    if (fontSizeArg->IsNull() || fontSizeArg->IsUndefined() ||
        !ArkTSUtils::ParseJsDimensionFp(vm, fontSizeArg, fontSize)) {
        fontSize = selectTheme->GetFontSize();
    }

    std::string fontWeight = DEFAULT_STR;
    if (!fontWeightArg->IsNull() && !fontWeightArg->IsUndefined()) {
        if (fontWeightArg->IsNumber()) {
            fontWeight = std::to_string(fontWeightArg->Int32Value(vm));
        } else {
            if (!ArkTSUtils::ParseJsString(vm, fontWeightArg, fontWeight) || fontWeight.empty()) {
                fontWeight = DEFAULT_STR;
            }
        }
    }
    std::string fontFamily;
    if (!ArkTSUtils::ParseJsFontFamiliesToString(vm, fontFamilyArg, fontFamily) || fontFamily.empty()) {
        fontFamily = DEFAULT_STR;
    }
    int32_t styleVal = 0;
    if (!styleArg->IsNull() && !styleArg->IsUndefined() && styleArg->IsNumber()) {
        styleVal = styleArg->Int32Value(vm);
    }
    std::string fontSizeStr = fontSize.ToString();
    std::string fontInfo =
        StringUtils::FormatString(FORMAT_FONT.c_str(), fontSizeStr.c_str(), fontWeight.c_str(), fontFamily.c_str());

    GetArkUIInternalNodeAPI()->GetSelectModifier().SetSelectedOptionFont(nativeNode, fontInfo.c_str(), styleVal);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::ResetSpace(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSelectModifier().ResetSpace(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::ResetValue(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSelectModifier().ResetValue(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::ResetSelected(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSelectModifier().ResetSelected(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::ResetFontColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSelectModifier().ResetSelectFontColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::ResetSelectedOptionBgColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSelectModifier().ResetSelectedOptionBgColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::ResetOptionBgColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSelectModifier().ResetOptionBgColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::ResetOptionFontColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSelectModifier().ResetOptionFontColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::ResetSelectedOptionFontColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSelectModifier().ResetSelectedOptionFontColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::ResetFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSelectModifier().ResetFont(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::ResetOptionFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSelectModifier().ResetOptionFont(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::ResetSelectedOptionFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSelectModifier().ResetSelectedOptionFont(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::ResetMenuAlign(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSelectModifier().ResetMenuAlign(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::ResetArrowPosition(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSelectModifier().ResetArrowPosition(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::SetOptionWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> optionWidthArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    CalcDimension value;
    std::string width;
    if (optionWidthArg->IsString()) {
        std::string modeFlag = optionWidthArg->ToString(vm)->ToString();
        if (modeFlag.compare("fit_content") == 0) {
            GetArkUIInternalNodeAPI()->GetSelectModifier().SetOptionWidthFitTrigger(nativeNode, false);
            return panda::JSValueRef::Undefined(vm);
        } else if (modeFlag.compare("fit_trigger") == 0) {
            GetArkUIInternalNodeAPI()->GetSelectModifier().SetOptionWidthFitTrigger(nativeNode, true);
            return panda::JSValueRef::Undefined(vm);
        } else if (ArkTSUtils::IsPercentStr(modeFlag)) {
            return panda::JSValueRef::Undefined(vm);
        } else {
            ArkTSUtils::ParseJsDimensionVpNG(vm, optionWidthArg, value);
            if (value.IsNegative()) {
                value.Reset();
            }
            width = value.ToString();
        }
    } else {
        ArkTSUtils::ParseJsDimensionVpNG(vm, optionWidthArg, value);
        if (value.IsNegative()) {
            value.Reset();
        }
        width = value.ToString();
    }

    GetArkUIInternalNodeAPI()->GetSelectModifier().SetOptionWidth(nativeNode, width.c_str());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::ResetOptionWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSelectModifier().ResetOptionWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::SetOptionHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> optionHeightArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    CalcDimension value;
    std::string height;
    if (optionHeightArg->IsString()) {
        std::string modeFlag = optionHeightArg->ToString(vm)->ToString();
        if (ArkTSUtils::IsPercentStr(modeFlag)) {
            return panda::JSValueRef::Undefined(vm);
        }
    }

    ArkTSUtils::ParseJsDimensionVpNG(vm, optionHeightArg, value);
    if (value.IsNegative()) {
        return panda::JSValueRef::Undefined(vm);
    } else if (NEAR_ZERO(value.Value())) {
        return panda::JSValueRef::Undefined(vm);
    } else {
        height = value.ToString();
    }

    GetArkUIInternalNodeAPI()->GetSelectModifier().SetOptionHeight(nativeNode, height.c_str());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::ResetOptionHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSelectModifier().ResetOptionHeight(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::SetWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> widthArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    CalcDimension width;
    if (!ArkTSUtils::ParseJsDimensionVp(vm, widthArg, width, false)) {
        return panda::JSValueRef::Undefined(vm);
    }
    if (LessNotEqual(width.Value(), 0.0)) {
        width.SetValue(0.0);
    }
    std::string widthCalc = width.CalcValue();
    GetArkUIInternalNodeAPI()->GetSelectModifier().SetSelectWidth(
        nativeNode, width.Value(), static_cast<int32_t>(width.Unit()), widthCalc.c_str());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::ResetWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSelectModifier().ResetSelectWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::SetHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> heightArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    CalcDimension height;
    if (!ArkTSUtils::ParseJsDimensionVp(vm, heightArg, height, false)) {
        return panda::JSValueRef::Undefined(vm);
    }
    if (LessNotEqual(height.Value(), 0.0)) {
        height.SetValue(0.0);
    }
    std::string heightCalc = height.CalcValue();
    GetArkUIInternalNodeAPI()->GetSelectModifier().SetSelectHeight(
        nativeNode, height.Value(), static_cast<int32_t>(height.Unit()), heightCalc.c_str());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::ResetHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSelectModifier().ResetSelectHeight(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::SetSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> widthArg = runtimeCallInfo->GetCallArgRef(1);  // 1: index of width value
    Local<JSValueRef> heightArg = runtimeCallInfo->GetCallArgRef(2); // 2: index of heigth value
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    CalcDimension width;
    CalcDimension height;
    if (widthArg->IsUndefined() || !ArkTSUtils::ParseJsDimensionVp(vm, widthArg, width, false)) {
        return panda::JSValueRef::Undefined(vm);
    }
    if (LessNotEqual(width.Value(), 0.0)) {
        width.SetValue(0.0);
    }

    if (heightArg->IsUndefined() || !ArkTSUtils::ParseJsDimensionVp(vm, heightArg, height, false)) {
        return panda::JSValueRef::Undefined(vm);
    }
    if (LessNotEqual(height.Value(), 0.0)) {
        height.SetValue(0.0);
    }

    std::string widthCalc = width.CalcValue();
    std::string heightCalc = height.CalcValue();
    GetArkUIInternalNodeAPI()->GetSelectModifier().SetSelectWidth(
        nativeNode, width.Value(), static_cast<int32_t>(width.Unit()), widthCalc.c_str());
    GetArkUIInternalNodeAPI()->GetSelectModifier().SetSelectHeight(
        nativeNode, height.Value(), static_cast<int32_t>(height.Unit()), heightCalc.c_str());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::ResetSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSelectModifier().ResetSelectSize(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG