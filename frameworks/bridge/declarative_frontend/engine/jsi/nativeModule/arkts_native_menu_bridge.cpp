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
const int SIZE_OF_FOUR = 4;
const int SIZE_OF_ONE = 1;
const std::string DEFAULT_ERR_CODE = "-1";

ArkUINativeModuleValue MenuBridge::SetMenuFontColor(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    Color color;
    if (secondArg->IsNull() || secondArg->IsUndefined() ||
        !ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color)) {
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

    CalcDimension fontSize = Dimension(-1.0);
    ArkTSUtils::ParseJsDimensionFp(vm, sizeArg, fontSize, false);

    std::string weight = DEFAULT_ERR_CODE;
    if (weightArg->IsNumber()) {
        weight = std::to_string(weightArg->Int32Value(vm));
    } else {
        ArkTSUtils::ParseJsString(vm, weightArg, weight);
    }

    std::string fontFamily;
    ArkTSUtils::GetStringFromJS(vm, familyArg, fontFamily);

    std::string style;
    if (styleArg->IsNumber()) {
        style = styleArg->ToString(vm)->ToString();
    } else {
        ArkTSUtils::ParseJsString(vm, styleArg, style);
    }

    std::string fontInfo = StringUtils::FormatString(FORMAT_FONT.c_str(),
        StringUtils::DoubleToString(fontSize.Value()).c_str(), weight.c_str(), style.c_str(), fontFamily.c_str());

    GetArkUIInternalNodeAPI()->GetMenuModifier().SetFont(
        nativeNode, fontInfo.c_str(), static_cast<int>(fontSize.Unit()));
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

    CalcDimension radius;
    if (topLeftArgs->IsNumber() || topLeftArgs->IsString() || ArkTSUtils::ParseJsDimensionVp(vm, topLeftArgs, radius)) {
        if (LessNotEqual(radius.Value(), 0.0)) {
            GetArkUIInternalNodeAPI()->GetMenuModifier().ResetRadius(nativeNode);
            return panda::JSValueRef::Undefined(vm);
        }
        uint32_t size = SIZE_OF_ONE;
        double values[size];
        int units[size];
        values[NUM_0] = radius.Value();
        units[NUM_0] = static_cast<int>(radius.Unit());
        GetArkUIInternalNodeAPI()->GetMenuModifier().SetRadius(nativeNode, values, units, SIZE_OF_ONE);
        return panda::JSValueRef::Undefined(vm);
    }

    CalcDimension topLeft;
    CalcDimension topRight;
    CalcDimension bottomLeft;
    CalcDimension bottomRight;
    ArkTSUtils::ParseJsDimensionVp(vm, topLeftArgs, topLeft);
    ArkTSUtils::ParseJsDimensionVp(vm, topRightArgs, topRight);
    ArkTSUtils::ParseJsDimensionVp(vm, bottomLeftArgs, bottomLeft);
    ArkTSUtils::ParseJsDimensionVp(vm, bottomRightArgs, bottomRight);

    uint32_t size = SIZE_OF_FOUR;
    double values[size];
    int units[size];

    values[NUM_0] = topLeft.Value();
    units[NUM_0] = static_cast<int>(topLeft.Unit());
    values[NUM_1] = topRight.Value();
    units[NUM_1] = static_cast<int>(topRight.Unit());
    values[NUM_2] = bottomLeft.Value();
    units[NUM_2] = static_cast<int>(bottomLeft.Unit());
    values[NUM_3] = bottomRight.Value();
    units[NUM_3] = static_cast<int>(bottomRight.Unit());

    GetArkUIInternalNodeAPI()->GetMenuModifier().SetRadius(nativeNode, values, units, SIZE_OF_FOUR);
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