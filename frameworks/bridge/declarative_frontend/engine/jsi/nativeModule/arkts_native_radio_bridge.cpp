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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_radio_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "core/components/checkable/checkable_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/radio/radio_model_ng.h"

namespace OHOS::Ace::NG {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int NUM_4 = 4;
const char* RADIO_BUILDER_NODEPTR_OF_UINODE = "nodePtr_";
panda::Local<panda::JSValueRef> JsRadioChangeCallback(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    auto vm = runtimeCallInfo->GetVM();
    int32_t argc = static_cast<int32_t>(runtimeCallInfo->GetArgsNumber());
    if (argc != NUM_1) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    if (!firstArg->IsBoolean()) {
        return panda::JSValueRef::Undefined(vm);
    }
    bool value = firstArg->ToBoolean(vm)->Value();
    auto ref = runtimeCallInfo->GetThisRef();
    auto obj = ref->ToObject(vm);
    if (obj->GetNativePointerFieldCount(vm) < NUM_1) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = static_cast<FrameNode*>(obj->GetNativePointerField(vm, 0));
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    RadioModelNG::SetChangeValue(frameNode, value);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RadioBridge::SetRadioChecked(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    bool isCheck = secondArg->ToBoolean(vm)->Value();
    GetArkUINodeModifiers()->getRadioModifier()->setRadioChecked(nativeNode, isCheck);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RadioBridge::ResetRadioChecked(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getRadioModifier()->resetRadioChecked(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RadioBridge::SetRadioStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> checkedBackgroundColor = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> uncheckedBorderColor = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> indicatorColor = runtimeCallInfo->GetCallArgRef(NUM_3);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, panda::NativePointerRef::New(vm, nullptr));
    auto radioTheme = pipeline->GetTheme<RadioTheme>();
    CHECK_NULL_RETURN(radioTheme, panda::NativePointerRef::New(vm, nullptr));

    Color checkedBackgroundColorVal;
    if (checkedBackgroundColor->IsNull() || checkedBackgroundColor->IsUndefined() ||
        !ArkTSUtils::ParseJsColorAlpha(vm, checkedBackgroundColor, checkedBackgroundColorVal)) {
        checkedBackgroundColorVal = radioTheme->GetActiveColor();
    }
    Color uncheckedBorderColorVal;
    if (uncheckedBorderColor->IsNull() || uncheckedBorderColor->IsUndefined() ||
        !ArkTSUtils::ParseJsColorAlpha(vm, uncheckedBorderColor, uncheckedBorderColorVal)) {
        uncheckedBorderColorVal = radioTheme->GetInactiveColor();
    }
    Color indicatorColorVal;
    if (indicatorColor->IsNull() || indicatorColor->IsUndefined() ||
        !ArkTSUtils::ParseJsColorAlpha(vm, indicatorColor, indicatorColorVal)) {
        indicatorColorVal = radioTheme->GetPointColor();
    }

    GetArkUINodeModifiers()->getRadioModifier()->setRadioStyle(nativeNode,
        checkedBackgroundColorVal.GetValue(), uncheckedBorderColorVal.GetValue(), indicatorColorVal.GetValue());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RadioBridge::ResetRadioStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getRadioModifier()->resetRadioStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RadioBridge::SetRadioWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> widthArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    CalcDimension width;
    if (!ArkTSUtils::ParseJsDimensionVpNG(vm, widthArg, width)) {
        GetArkUINodeModifiers()->getRadioModifier()->resetRadioWidth(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    if (LessNotEqual(width.Value(), 0.0)) {
        width.SetValue(0.0);
    }
    std::string widthCalc = width.CalcValue();
    GetArkUINodeModifiers()->getRadioModifier()->setRadioWidth(
        nativeNode, width.Value(), static_cast<int32_t>(width.Unit()), widthCalc.c_str());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RadioBridge::ResetRadioWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0); //0 is node arguments
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getRadioModifier()->resetRadioWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RadioBridge::SetRadioHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> heightArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    CalcDimension height;
    if (!ArkTSUtils::ParseJsDimensionVpNG(vm, heightArg, height)) {
        GetArkUINodeModifiers()->getRadioModifier()->resetRadioHeight(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    if (LessNotEqual(height.Value(), 0.0)) {
        height.SetValue(0.0);
    }
    std::string heightCalc = height.CalcValue();
    GetArkUINodeModifiers()->getRadioModifier()->setRadioHeight(
        nativeNode, height.Value(), static_cast<int32_t>(height.Unit()), heightCalc.c_str());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RadioBridge::ResetRadioHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0); //0 is node arguments
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getRadioModifier()->resetRadioHeight(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RadioBridge::SetRadioSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);     //0 is node arguments
    Local<JSValueRef> widthArg = runtimeCallInfo->GetCallArgRef(1);  //1 is width value
    Local<JSValueRef> heightArg = runtimeCallInfo->GetCallArgRef(2); //2 is height value
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());

    CalcDimension width;
    CalcDimension height;
    if (!ArkTSUtils::ParseJsDimensionVpNG(vm, widthArg, width)) {
        GetArkUINodeModifiers()->getRadioModifier()->resetRadioWidth(nativeNode);
    } else {
        std::string widthCalc = width.CalcValue();
        if (LessNotEqual(width.Value(), 0.0)) {
            width.SetValue(0.0);
        }
        GetArkUINodeModifiers()->getRadioModifier()->setRadioWidth(
            nativeNode, width.Value(), static_cast<int>(width.Unit()), widthCalc.c_str());
    }
    if (!ArkTSUtils::ParseJsDimensionVpNG(vm, heightArg, height)) {
        GetArkUINodeModifiers()->getRadioModifier()->resetRadioHeight(nativeNode);
    } else {
        std::string heightCalc = height.CalcValue();
        if (LessNotEqual(height.Value(), 0.0)) {
            height.SetValue(0.0);
        }
        GetArkUINodeModifiers()->getRadioModifier()->setRadioHeight(
            nativeNode, height.Value(), static_cast<int>(height.Unit()), heightCalc.c_str());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RadioBridge::ResetRadioSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0); //0 is node arguments
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getRadioModifier()->resetRadioSize(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RadioBridge::SetRadioHoverEffect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);  //0 is node arguments
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(1); //1 is Jsvalue
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());

    if (valueArg->IsUndefined() || !valueArg->IsNumber()) {
        GetArkUINodeModifiers()->getRadioModifier()->resetRadioHoverEffect(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    int32_t intValue = valueArg->Int32Value(vm);
    GetArkUINodeModifiers()->getRadioModifier()->setRadioHoverEffect(nativeNode, intValue);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RadioBridge::ResetRadioHoverEffect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0); //0 is node arguments
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getRadioModifier()->resetRadioHoverEffect(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RadioBridge::SetRadioPadding(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);   //0 is node arguments
    Local<JSValueRef> topArg = runtimeCallInfo->GetCallArgRef(1);    //1 is top arguments
    Local<JSValueRef> rightArg = runtimeCallInfo->GetCallArgRef(2);  //2 is right arguments
    Local<JSValueRef> bottomArg = runtimeCallInfo->GetCallArgRef(3); //3 is bottom arguments
    Local<JSValueRef> leftArg = runtimeCallInfo->GetCallArgRef(4);   //4 is left arguments
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());

    struct ArkUISizeType top = { 0.0, static_cast<int8_t>(DimensionUnit::VP), "" };
    struct ArkUISizeType right = { 0.0, static_cast<int8_t>(DimensionUnit::VP), "" };
    struct ArkUISizeType bottom = { 0.0, static_cast<int8_t>(DimensionUnit::VP), "" };
    struct ArkUISizeType left = { 0.0, static_cast<int8_t>(DimensionUnit::VP), "" };

    CalcDimension topDimen(0, DimensionUnit::VP);
    CalcDimension rightDimen(0, DimensionUnit::VP);
    CalcDimension bottomDimen(0, DimensionUnit::VP);
    CalcDimension leftDimen(0, DimensionUnit::VP);
    ArkTSUtils::ParsePadding(vm, topArg, topDimen, top);
    ArkTSUtils::ParsePadding(vm, rightArg, rightDimen, right);
    ArkTSUtils::ParsePadding(vm, bottomArg, bottomDimen, bottom);
    ArkTSUtils::ParsePadding(vm, leftArg, leftDimen, left);
    GetArkUINodeModifiers()->getRadioModifier()->setRadioPadding(nativeNode, &top, &right, &bottom, &left);

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RadioBridge::ResetRadioPadding(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0); //0 is node arguments
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getRadioModifier()->resetRadioPadding(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RadioBridge::SetRadioResponseRegion(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);   //0 is node arguments
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(1);  //1 is JsValue
    Local<JSValueRef> lengthArg = runtimeCallInfo->GetCallArgRef(2); //2 is length arguments
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    uint32_t length = static_cast<uint32_t>(lengthArg->Int32Value(vm));
    ArkUI_Float32 regionArray[length];
    int32_t regionUnits[length];
    if (!ArkTSUtils::ParseResponseRegion(vm, valueArg, regionArray, regionUnits, length)) {
        GetArkUINodeModifiers()->getRadioModifier()->resetRadioResponseRegion(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    GetArkUINodeModifiers()->getRadioModifier()->setRadioResponseRegion(
        nativeNode, regionArray, regionUnits, length);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RadioBridge::ResetRadioResponseRegion(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0); //0 is node arguments
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getRadioModifier()->resetRadioResponseRegion(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RadioBridge::SetContentModifierBuilder(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto* frameNode = reinterpret_cast<FrameNode*>(firstArg->ToNativePointer(vm)->Value());
    if (!secondArg->IsObject(vm)) {
        RadioModelNG::SetBuilderFunc(frameNode, nullptr);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::CopyableGlobal<panda::ObjectRef> obj(vm, secondArg);
    RadioModelNG::SetBuilderFunc(frameNode,
        [vm, frameNode, obj = std::move(obj), containerId = Container::CurrentId()](
            RadioConfiguration config) -> RefPtr<FrameNode> {
            ContainerScope scope(containerId);
            auto context = ArkTSUtils::GetContext(vm);
            CHECK_EQUAL_RETURN(context->IsUndefined(), true, nullptr);
            const char* keysOfRadio[] = { "value", "checked", "enabled", "triggerChange"};
            Local<JSValueRef> valuesOfRadio[] = { panda::StringRef::NewFromUtf8(vm, config.value_.c_str()),
                panda::BooleanRef::New(vm, config.checked_), panda::BooleanRef::New(vm, config.enabled_),
                panda::FunctionRef::New(vm, JsRadioChangeCallback)};
            auto radio = panda::ObjectRef::NewWithNamedProperties(vm,
                ArraySize(keysOfRadio), keysOfRadio, valuesOfRadio);
            radio->SetNativePointerFieldCount(vm, 1);
            radio->SetNativePointerField(vm, 0, static_cast<void*>(frameNode));
            panda::Local<panda::JSValueRef> params[NUM_2] = { context, radio };
            LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            auto jsObject = obj.ToLocal();
            auto makeFunc = jsObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "makeContentModifierNode"));
            CHECK_EQUAL_RETURN(makeFunc->IsFunction(vm), false, nullptr);
            panda::Local<panda::FunctionRef> func = makeFunc;
            auto result = func->Call(vm, jsObject, params, NUM_2);
            JSNApi::ExecutePendingJob(vm);
            CHECK_EQUAL_RETURN(result.IsEmpty() || trycatch.HasCaught() || !result->IsObject(vm), true, nullptr);
            auto resultObj = result->ToObject(vm);
            panda::Local<panda::JSValueRef> nodeptr =
                resultObj->Get(vm, panda::StringRef::NewFromUtf8(vm, RADIO_BUILDER_NODEPTR_OF_UINODE));
            CHECK_EQUAL_RETURN(nodeptr.IsEmpty() || nodeptr->IsUndefined() || nodeptr->IsNull(), true, nullptr);
            auto* frameNode = reinterpret_cast<FrameNode*>(nodeptr->ToNativePointer(vm)->Value());
            CHECK_NULL_RETURN(frameNode, nullptr);
            return AceType::Claim(frameNode);
        });
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RadioBridge::SetRadioOptions(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    CHECK_EQUAL_RETURN(runtimeCallInfo->GetArgsNumber() != NUM_4, true, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> groupArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> indicatorTypeArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    std::string value;
    std::string group;
    auto indicatorType = RadioIndicatorType::TICK;

    if (!valueArg.IsNull() && valueArg->IsString(vm)) {
        value = valueArg->ToString(vm)->ToString(vm);
    }
    if (!groupArg.IsNull() && groupArg->IsString(vm)) {
        group = groupArg->ToString(vm)->ToString(vm);
    }
    if (!indicatorTypeArg.IsNull() && indicatorTypeArg->IsNumber()) {
        indicatorType = static_cast<RadioIndicatorType>(indicatorTypeArg->Int32Value(vm));
        if (indicatorType == RadioIndicatorType::CUSTOM) {
            indicatorType = RadioIndicatorType::TICK;
        }
    }
    if (!firstArg.IsNull() && !firstArg->IsUndefined()) {
        auto pointer = firstArg->ToNativePointer(vm);
        CHECK_EQUAL_RETURN(pointer.IsEmpty(), true, panda::JSValueRef::Undefined(vm));
        auto nativeNode = nodePtr(pointer->Value());
        CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
        GetArkUINodeModifiers()->getRadioModifier()->setRadioOptions(
            nativeNode, value.c_str(), group.c_str(), static_cast<int32_t>(indicatorType));
    }
    return panda::JSValueRef::Undefined(vm);
}
}
