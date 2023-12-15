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
#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_api.h"

namespace OHOS::Ace::NG {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int NUM_4 = 4;
const std::string FORMAT_FONT = "%s|%s|%s";
const std::string DEFAULT_ERR_CODE = "-1";
const std::string DEFAULT_FAMILY = "HarmonyOS Sans";

ArkUINativeModuleValue MenuBridge::SetMenuFontColor(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    Color color;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color)) {
        GetArkUIInternalNodeAPI()->GetMenuModifier().ResetMenuFontColor(nativeNode);
    } else {
        GetArkUIInternalNodeAPI()->GetMenuModifier().SetMenuFontColor(nativeNode, color.GetValue());
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MenuBridge::ResetMenuFontColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetMenuModifier().ResetMenuFontColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MenuBridge::SetFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> sizeArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> weightArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> familyArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> styleArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    if (sizeArg->IsUndefined() && weightArg->IsUndefined() && familyArg->IsUndefined() && styleArg->IsUndefined()) {
        GetArkUIInternalNodeAPI()->GetMenuModifier().ResetFont(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    CalcDimension fontSize = Dimension(-1.0);
    ArkTSUtils::ParseJsDimensionFp(vm, sizeArg, fontSize, false);

    std::string weight = DEFAULT_ERR_CODE;
    if (weightArg->IsNumber()) {
        weight = std::to_string(weightArg->Int32Value(vm));
    } else {
        if (!ArkTSUtils::ParseJsString(vm, weightArg, weight) || weight.empty()) {
            weight = DEFAULT_ERR_CODE;
        }
    }

    int32_t style = 0;
    if (styleArg->IsNumber()) {
        style = styleArg->Int32Value(vm);
    }

    std::string family = DEFAULT_FAMILY;
    if (familyArg->IsString()) {
        family = familyArg->ToString(vm)->ToString();
    }

    std::string fontInfo = StringUtils::FormatString(FORMAT_FONT.c_str(),
        StringUtils::DoubleToString(fontSize.Value()).c_str(), weight.c_str(), family.c_str());

    GetArkUIInternalNodeAPI()->GetMenuModifier().SetFont(
        nativeNode, fontInfo.c_str(), style);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MenuBridge::ResetFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetMenuModifier().ResetFont(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MenuBridge::SetRadius(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    Local<JSValueRef> topLeftArgs = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> topRightArgs = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> bottomLeftArgs = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> bottomRightArgs = runtimeCallInfo->GetCallArgRef(NUM_4);
    if (topLeftArgs->IsUndefined() && topRightArgs->IsUndefined() && bottomLeftArgs->IsUndefined() &&
        bottomRightArgs->IsUndefined()) {
        GetArkUIInternalNodeAPI()->GetMenuModifier().ResetRadius(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    CalcDimension topLeft;
    CalcDimension topRight;
    CalcDimension bottomLeft;
    CalcDimension bottomRight;
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
  
    std::vector<double> radiusValues;
    std::vector<int32_t> radiusUnits;
    radiusUnits.push_back(static_cast<int>(topLeft.Unit()));
    radiusUnits.push_back(static_cast<int>(topRight.Unit()));
    radiusUnits.push_back(static_cast<int>(bottomLeft.Unit()));
    radiusUnits.push_back(static_cast<int>(bottomRight.Unit()));
    radiusValues.push_back(topLeft.Value());
    radiusValues.push_back(topRight.Value());
    radiusValues.push_back(bottomLeft.Value());
    radiusValues.push_back(bottomRight.Value());
    GetArkUIInternalNodeAPI()->GetMenuModifier().SetRadius(nativeNode, radiusValues.data(), radiusUnits.data());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MenuBridge::ResetRadius(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetMenuModifier().ResetRadius(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG