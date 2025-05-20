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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_menu_bridge.h"
#include "core/interfaces/arkoala/arkoala_api.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"

namespace OHOS::Ace::NG {
const std::string FORMAT_FONT = "%s|%s|%s";
const std::string DEFAULT_ERR_CODE = "-1";
constexpr int ARG_INDEX_0 = 0;
constexpr int ARG_INDEX_1 = 1;
constexpr int ARG_INDEX_2 = 2;
constexpr int ARG_INDEX_3 = 3;
constexpr int ARG_INDEX_4 = 4;
constexpr int ARG_INDEX_5 = 5;

ArkUIMenuDividerOptions BuildMenuDividerOptions(EcmaVM* vm, Local<JSValueRef> strokeWidthArg,
    Local<JSValueRef> colorArg, Local<JSValueRef> startMarginArg, Local<JSValueRef> endMarginArg)
{
    ArkUIDimensionType strokeWidthOption;
    ArkUIDimensionType startMarginOption;
    ArkUIDimensionType endMarginOption;

    CalcDimension strokeWidth;
    if (!ArkTSUtils::ParseJsLengthMetrics(vm, strokeWidthArg, strokeWidth)) {
        strokeWidth = Dimension(0.0);
    }
    strokeWidthOption.value = strokeWidth.Value();
    strokeWidthOption.units = static_cast<int32_t>(strokeWidth.Unit());

    Color color;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, colorArg, color)) {
        color = Color::TRANSPARENT;
    }

    CalcDimension startMargin;
    if (!ArkTSUtils::ParseJsLengthMetrics(vm, startMarginArg, startMargin)) {
        startMargin = Dimension(0.0);
    }
    startMarginOption.value = startMargin.Value();
    startMarginOption.units = static_cast<int32_t>(startMargin.Unit());

    CalcDimension endMargin;
    if (!ArkTSUtils::ParseJsLengthMetrics(vm, endMarginArg, endMargin)) {
        endMargin = Dimension(0.0);
    }
    endMarginOption.value = endMargin.Value();
    endMarginOption.units = static_cast<int32_t>(endMargin.Unit());

    ArkUIMenuDividerOptions dividerOptions;
    dividerOptions.strokeWidth = strokeWidthOption;
    dividerOptions.color = color.GetValue();
    dividerOptions.startMargin = startMarginOption;
    dividerOptions.endMargin = endMarginOption;
    return dividerOptions;
}

ArkUINativeModuleValue SetMenuDivider(ArkUIRuntimeCallInfo* runtimeCallInfo, bool isGroupDivider)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(ARG_INDEX_0);
    Local<JSValueRef> strokeWidthArg = runtimeCallInfo->GetCallArgRef(ARG_INDEX_1);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(ARG_INDEX_2);
    Local<JSValueRef> startMarginArg = runtimeCallInfo->GetCallArgRef(ARG_INDEX_3);
    Local<JSValueRef> endMarginArg = runtimeCallInfo->GetCallArgRef(ARG_INDEX_4);
    Local<JSValueRef> modeArg = runtimeCallInfo->GetCallArgRef(ARG_INDEX_5);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (strokeWidthArg->IsUndefined() && colorArg->IsUndefined() && startMarginArg->IsUndefined()
        && endMarginArg->IsUndefined() && modeArg->IsUndefined()) {
        if (isGroupDivider) {
            GetArkUINodeModifiers()->getMenuModifier()->resetMenuItemGroupDivider(nativeNode);
        } else {
            GetArkUINodeModifiers()->getMenuModifier()->resetMenuItemDivider(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    auto dividerOptions = BuildMenuDividerOptions(vm, strokeWidthArg, colorArg, startMarginArg, endMarginArg);
    int32_t mode = 0;
    if (modeArg->IsNumber()) {
        mode = modeArg->Int32Value(vm);
    }
    dividerOptions.mode = mode;
    if (isGroupDivider) {
        GetArkUINodeModifiers()->getMenuModifier()->setMenuItemGroupDivider(nativeNode, &dividerOptions);
    } else {
        GetArkUINodeModifiers()->getMenuModifier()->setMenuItemDivider(nativeNode, &dividerOptions);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ResetMenuDivider(ArkUIRuntimeCallInfo* runtimeCallInfo, bool isGroupDivider)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (isGroupDivider) {
        GetArkUINodeModifiers()->getMenuModifier()->resetMenuItemGroupDivider(nativeNode);
    } else {
        GetArkUINodeModifiers()->getMenuModifier()->resetMenuItemDivider(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MenuBridge::SetMenuFontColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Color color;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color)) {
        GetArkUINodeModifiers()->getMenuModifier()->resetMenuFontColor(nativeNode);
    } else {
        GetArkUINodeModifiers()->getMenuModifier()->setMenuFontColor(nativeNode, color.GetValue());
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MenuBridge::ResetMenuFontColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getMenuModifier()->resetMenuFontColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MenuBridge::SetFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> sizeArg = runtimeCallInfo->GetCallArgRef(1);   // 1: index of font size value
    Local<JSValueRef> weightArg = runtimeCallInfo->GetCallArgRef(2); // 2: index of font weight value
    Local<JSValueRef> familyArg = runtimeCallInfo->GetCallArgRef(3); // 3: index of font family value
    Local<JSValueRef> styleArg = runtimeCallInfo->GetCallArgRef(4);  // 4: index of font style value
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (sizeArg->IsUndefined() && weightArg->IsUndefined() && familyArg->IsUndefined() && styleArg->IsUndefined()) {
        GetArkUINodeModifiers()->getMenuModifier()->resetFont(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    CalcDimension fontSize;
    if (!ArkTSUtils::ParseJsDimensionFp(vm, sizeArg, fontSize, false)) {
        fontSize = Dimension(0.0);
    }
    std::string weight = DEFAULT_ERR_CODE;
    if (weightArg->IsNumber()) {
        weight = std::to_string(weightArg->Int32Value(vm));
    } else {
        if (!ArkTSUtils::ParseJsString(vm, weightArg, weight) || weight.empty()) {
            weight = DEFAULT_ERR_CODE;
        }
    }

    int32_t style = -1;
    if (styleArg->IsNumber()) {
        style = styleArg->Int32Value(vm);
    }

    std::string family;
    if (!ArkTSUtils::ParseJsFontFamiliesToString(vm, familyArg, family) || family.empty()) {
        family = DEFAULT_ERR_CODE;
    }
    std::string fontSizeStr = fontSize.ToString();
    std::string fontInfo =
        StringUtils::FormatString(FORMAT_FONT.c_str(), fontSizeStr.c_str(), weight.c_str(), family.c_str());

    GetArkUINodeModifiers()->getMenuModifier()->setFont(nativeNode, fontInfo.c_str(), style);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MenuBridge::ResetFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getMenuModifier()->resetFont(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

bool MenuBridge::ParseRadius(EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUINodeHandle nativeNode,
    std::vector<ArkUI_Float32>& radiusValues, std::vector<int32_t>& radiusUnits)
{
    Local<JSValueRef> topLeftArgs = runtimeCallInfo->GetCallArgRef(1);     // 1: index of top left value
    Local<JSValueRef> topRightArgs = runtimeCallInfo->GetCallArgRef(2);    // 2: index of top right value
    Local<JSValueRef> bottomLeftArgs = runtimeCallInfo->GetCallArgRef(3);  // 3: index of bottom left value
    Local<JSValueRef> bottomRightArgs = runtimeCallInfo->GetCallArgRef(4); // 4: index of bottom right value
    Local<JSValueRef> isObjectArgs = runtimeCallInfo->GetCallArgRef(5);    // 5: check is object radius
    if (topLeftArgs->IsUndefined() && topRightArgs->IsUndefined() && bottomLeftArgs->IsUndefined() &&
        bottomRightArgs->IsUndefined()) {
        GetArkUINodeModifiers()->getMenuModifier()->resetRadius(nativeNode);
        return false;
    }

    CalcDimension topLeft;
    CalcDimension topRight;
    CalcDimension bottomLeft;
    CalcDimension bottomRight;
    if (isObjectArgs->IsBoolean() && !isObjectArgs->ToBoolean(vm)->Value()) {
        if (!ArkTSUtils::ParseJsDimensionVpNG(vm, topLeftArgs, topLeft, true)) {
            GetArkUINodeModifiers()->getMenuModifier()->resetRadius(nativeNode);
            return false;
        }
        if (LessNotEqual(topLeft.Value(), 0.0)) {
            GetArkUINodeModifiers()->getMenuModifier()->resetRadius(nativeNode);
            return false;
        }
        topRight = topLeft;
        bottomLeft = topLeft;
        bottomRight = topLeft;
    } else {
        if (!ArkTSUtils::ParseJsDimensionVpNG(vm, topLeftArgs, topLeft, true)) {
            topLeft = CalcDimension(0.0, DimensionUnit::VP);
        }

        if (!ArkTSUtils::ParseJsDimensionVpNG(vm, topRightArgs, topRight, true)) {
            topRight = CalcDimension(0.0, DimensionUnit::VP);
        }

        if (!ArkTSUtils::ParseJsDimensionVpNG(vm, bottomLeftArgs, bottomLeft, true)) {
            bottomLeft = CalcDimension(0.0, DimensionUnit::VP);
        }

        if (!ArkTSUtils::ParseJsDimensionVpNG(vm, bottomRightArgs, bottomRight, true)) {
            bottomRight = CalcDimension(0.0, DimensionUnit::VP);
        }
    }
    radiusUnits.push_back(static_cast<int32_t>(topLeft.Unit()));
    radiusUnits.push_back(static_cast<int32_t>(topRight.Unit()));
    radiusUnits.push_back(static_cast<int32_t>(bottomLeft.Unit()));
    radiusUnits.push_back(static_cast<int32_t>(bottomRight.Unit()));
    radiusValues.push_back(topLeft.Value());
    radiusValues.push_back(topRight.Value());
    radiusValues.push_back(bottomLeft.Value());
    radiusValues.push_back(bottomRight.Value());
    return true;
}

ArkUINativeModuleValue MenuBridge::SetRadius(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    std::vector<ArkUI_Float32> radiusValues;
    std::vector<int32_t> radiusUnits;
    if (!ParseRadius(vm, runtimeCallInfo, nativeNode, radiusValues, radiusUnits)) {
        return panda::JSValueRef::Undefined(vm);
    }
    GetArkUINodeModifiers()->getMenuModifier()->setRadius(nativeNode, radiusValues.data(), radiusUnits.data());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MenuBridge::ResetRadius(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getMenuModifier()->resetRadius(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MenuBridge::SetWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> widthArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    CalcDimension width;
    if (!ArkTSUtils::ParseJsDimensionVp(vm, widthArg, width, false)) {
        GetArkUINodeModifiers()->getMenuModifier()->resetMenuWidth(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    GetArkUINodeModifiers()->getMenuModifier()->setMenuWidth(
        nativeNode, width.Value(), static_cast<int32_t>(width.Unit()));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MenuBridge::ResetWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getMenuModifier()->resetMenuWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MenuBridge::SetMenuItemDivider(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    return SetMenuDivider(runtimeCallInfo, false);
}

ArkUINativeModuleValue MenuBridge::ResetMenuItemDivider(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    return ResetMenuDivider(runtimeCallInfo, false);
}

ArkUINativeModuleValue MenuBridge::SetMenuItemGroupDivider(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    return SetMenuDivider(runtimeCallInfo, true);
}

ArkUINativeModuleValue MenuBridge::ResetMenuItemGroupDivider(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    return ResetMenuDivider(runtimeCallInfo, true);
}

ArkUINativeModuleValue MenuBridge::SetSubMenuExpandingMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsUndefined() || secondArg->IsNull()) {
        GetArkUINodeModifiers()->getMenuModifier()->resetSubMenuExpandingMode(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    if (secondArg->IsNumber()) {
        GetArkUINodeModifiers()->getMenuModifier()->setSubMenuExpandingMode(nativeNode,
            secondArg->ToNumber(vm)->Value());
    } else {
        GetArkUINodeModifiers()->getMenuModifier()->resetSubMenuExpandingMode(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MenuBridge::ResetSubMenuExpandingMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getMenuModifier()->resetSubMenuExpandingMode(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MenuBridge::SetSubMenuExpandSymbol(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    std::function<void(WeakPtr<NG::FrameNode>)> symbolApply;
    if (secondArg->IsObject(vm)) {
        Framework::JsiCallbackInfo info = Framework::JsiCallbackInfo(runtimeCallInfo);
        Framework::JSViewAbstract::SetSymbolOptionApply(runtimeCallInfo, symbolApply, info[1]);
        GetArkUINodeModifiers()->getMenuModifier()->setSubMenuExpandSymbol(
            nativeNode, reinterpret_cast<void*>(&symbolApply));
    } else {
        GetArkUINodeModifiers()->getMenuModifier()->resetSubMenuExpandSymbol(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MenuBridge::ResetSubMenuExpandSymbol(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getMenuModifier()->resetSubMenuExpandSymbol(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MenuBridge::SetFontSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    uint32_t argsNumber = runtimeCallInfo->GetArgsNumber();
    if (argsNumber != ARG_INDEX_2) {
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(ARG_INDEX_0);
    Local<JSValueRef> fontSizeArg = runtimeCallInfo->GetCallArgRef(ARG_INDEX_1);
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    CalcDimension fontSize;
    if (!ArkTSUtils::ParseJsDimensionFp(vm, fontSizeArg, fontSize) || fontSize.IsNegative()) {
        GetArkUINodeModifiers()->getMenuModifier()->resetMenuFontSize(nativeNode);
    } else {
        GetArkUINodeModifiers()->getMenuModifier()->setMenuFontSize(
            nativeNode, fontSize.Value(), static_cast<int>(fontSize.Unit()));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MenuBridge::ResetFontSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(ARG_INDEX_0);
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getMenuModifier()->resetMenuFontSize(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

} // namespace OHOS::Ace::NG
