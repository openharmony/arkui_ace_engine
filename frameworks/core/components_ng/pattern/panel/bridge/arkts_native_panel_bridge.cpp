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

#include "base/log/ace_scoring_log.h"
#include "core/components/panel/sliding_events.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/panel/bridge/arkts_native_panel_bridge.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"

namespace OHOS::Ace::NG {
struct BorderRadius {
    CalcDimension radiusTopLeft;
    CalcDimension radiusTopRight;
    CalcDimension radiusBottomLeft;
    CalcDimension radiusBottomRight;
};
namespace {
const std::vector<PanelMode> PANEL_MODES = { PanelMode::MINI, PanelMode::HALF, PanelMode::FULL, PanelMode::AUTO };
const std::vector<PanelType> PANEL_TYPES = { PanelType::MINI_BAR, PanelType::FOLDABLE_BAR, PanelType::TEMP_DISPLAY,
    PanelType::CUSTOM };
const static PanelMode DEFAULT_PANELMODE = PanelMode::HALF;
const static PanelType DEFAULT_PANELTYPE = PanelType::FOLDABLE_BAR;
const std::string DEFAULT_BACKGROUND_MASK = "#08182431";
constexpr int NUM_0 = 0;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int NUM_4 = 4;

void ParseModeObject(ArkUIRuntimeCallInfo* runtimeCallInfo, const Local<JSValueRef>& changeEventVal)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_VOID(vm);
    CHECK_NULL_VOID(changeEventVal->IsFunction(vm));
    ArkUINodeHandle nativeNode = nodePtr(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    CHECK_NULL_VOID(nativeNode);
    FrameNode* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_VOID(frameNode);
    Local<panda::FunctionRef> jsfunc = changeEventVal->ToObject(vm);
    auto onMode = [func = panda::CopyableGlobal(vm, jsfunc), node = AceType::WeakClaim(frameNode)](
                      const BaseEventInfo* baseEventInfo) {
        auto vm = func.GetEcmaVM();
        CHECK_EQUAL_VOID(ArkTSUtils::CheckJavaScriptScope(vm), false);
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        ACE_SCORING_EVENT("SlidingPanel.ModeChangeEvent");
        PipelineContext::SetCallBackNode(node);
        auto eventInfo = TypeInfoHelper::DynamicCast<SlidingPanelSizeChangeEvent>(baseEventInfo);
        if (!eventInfo) {
            return;
        }
        auto newJSVal = panda::NumberRef::New(vm, static_cast<int32_t>(eventInfo->GetMode()));
        panda::Local<panda::JSValueRef> params[] = { newJSVal };
        auto result = func->Call(vm, func.ToLocal(), params, 1);
        ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
    };
    GetArkUINodeModifiers()->getPanelModifier()->setModeChangeEvent(reinterpret_cast<void*>(&onMode));
}

ArkUINativeModuleValue SetJSPanelMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> modeArg = runtimeCallInfo->GetCallArgRef(1);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_EQUAL_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), false, panda::JSValueRef::Undefined(vm));
    if (runtimeCallInfo->GetArgsNumber() < NUM_2 || runtimeCallInfo->GetArgsNumber() > NUM_3) {
        return panda::JSValueRef::Undefined(vm);
    }
    int32_t mode = static_cast<int32_t>(DEFAULT_PANELMODE);
    if (runtimeCallInfo->GetArgsNumber() > 0 && modeArg->IsNumber()) {
        const auto modeNumber = modeArg->ToNumber(vm)->Int32Value(vm);
        if (modeNumber >= 0 && modeNumber < static_cast<int32_t>(PANEL_MODES.size())) {
            mode = modeNumber;
        }
    }

    if (runtimeCallInfo->GetArgsNumber() > NUM_2) {
        if (!callbackArg.IsEmpty() && callbackArg->IsFunction(vm)) {
            ParseModeObject(runtimeCallInfo, callbackArg);
        }
    }
    GetArkUINodeModifiers()->getPanelModifier()->setPanelMode(
        nativeNode, static_cast<int32_t>(PANEL_MODES[mode]));
    return panda::JSValueRef::Undefined(vm);
}

void ParsePanelRadius(const EcmaVM* vm, const Local<JSValueRef>& args, BorderRadius& borderRadius)
{
    if (!args->IsObject(vm) && !args->IsNumber() && !args->IsString(vm)) {
        return;
    }

    CalcDimension radius;
    if (ArkTSUtils::ParseJsDimensionVp(vm, args, radius, true)) {
        borderRadius.radiusTopLeft = radius;
        borderRadius.radiusTopRight = radius;
        borderRadius.radiusBottomLeft = radius;
        borderRadius.radiusBottomRight = radius;
        return;
    }
    if (args->IsObject(vm)) {
        panda::Local<panda::ObjectRef> object = args->ToObject(vm);
        auto valueTopLeft = ArkTSUtils::GetProperty(vm, object, "topLeft");
        if (!valueTopLeft->IsUndefined()) {
            ArkTSUtils::ParseJsDimensionVp(vm, valueTopLeft, borderRadius.radiusTopLeft);
        }
        auto valueTopRight = ArkTSUtils::GetProperty(vm, object, "topRight");
        if (!valueTopRight->IsUndefined()) {
            ArkTSUtils::ParseJsDimensionVp(vm, valueTopRight, borderRadius.radiusTopRight);
        }
        auto valueBottomLeft = ArkTSUtils::GetProperty(vm, object, "bottomLeft");
        if (!valueBottomLeft->IsUndefined()) {
            ArkTSUtils::ParseJsDimensionVp(vm, valueBottomLeft, borderRadius.radiusBottomLeft);
        }
        auto valueBottomRight = ArkTSUtils::GetProperty(vm, object, "bottomRight");
        if (!valueBottomRight->IsUndefined()) {
            ArkTSUtils::ParseJsDimensionVp(vm, valueBottomRight, borderRadius.radiusBottomRight);
        }
        return;
    }
}
} // namespace
void PanelBridge::RegisterPanelAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    const char* functionNames[] = {
        "create", "pop", "setPanelMode", "resetPanelMode", "setPanelFullHeight", "resetPanelFullHeight",
        "setPanelHalfHeight", "resetPanelHalfHeight", "setPanelMiniHeight", "resetPanelMiniHeight",
        "setPanelBackgroundMask", "resetPanelBackgroundMask", "setPanelType", "resetPanelType",
        "setPanelCustomHeight", "resetPanelCustomHeight", "setShowCloseIcon", "resetShowCloseIcon",
        "setDragBar", "resetDragBar", "setShow", "resetShow", "setOnSizeChange", "setOnHeightChange",
        "setJsBackgroundColor", "setJsPanelBorder", "setJsPanelBorderWidth", "setJsPanelBorderColor",
        "setJsPanelBorderStyle", "setJsPanelBorderRadius"
    };

    Local<JSValueRef> funcValues[] = {
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PanelBridge::CreatePanel),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PanelBridge::PopPanel),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PanelBridge::SetPanelMode),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PanelBridge::ResetPanelMode),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PanelBridge::SetPanelFullHeight),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PanelBridge::ResetPanelFullHeight),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PanelBridge::SetPanelHalfHeight),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PanelBridge::ResetPanelHalfHeight),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PanelBridge::SetPanelMiniHeight),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PanelBridge::ResetPanelMiniHeight),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PanelBridge::SetPanelBackgroundMask),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PanelBridge::ResetPanelBackgroundMask),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PanelBridge::SetPanelType),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PanelBridge::ResetPanelType),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PanelBridge::SetPanelCustomHeight),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PanelBridge::ResetPanelCustomHeight),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PanelBridge::SetShowCloseIcon),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PanelBridge::ResetShowCloseIcon),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PanelBridge::SetDragBar),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PanelBridge::ResetDragBar),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PanelBridge::SetShow),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PanelBridge::ResetShow),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PanelBridge::SetOnSizeChange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PanelBridge::SetOnHeightChange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PanelBridge::SetJsBackgroundColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PanelBridge::SetJsPanelBorder),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PanelBridge::SetJsPanelBorderWidth),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PanelBridge::SetJsPanelBorderColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PanelBridge::SetJsPanelBorderStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PanelBridge::SetJsPanelBorderRadius)
    };

    auto panel = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(functionNames), functionNames, funcValues);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "panel"), panel);
}

ArkUINativeModuleValue PanelBridge::CreatePanel(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    bool isShow = true;
    if (runtimeCallInfo->GetArgsNumber() > 0 && firstArg->IsBoolean()) {
        isShow = firstArg->ToBoolean(vm)->Value();
    }
    GetArkUINodeModifiers()->getPanelModifier()->createPanel(isShow);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PanelBridge::PopPanel(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    GetArkUINodeModifiers()->getPanelModifier()->pop();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PanelBridge::SetPanelBackgroundMask(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_EQUAL_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), false, panda::JSValueRef::Undefined(vm));

    Color color;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color)) {
        GetArkUINodeModifiers()->getPanelModifier()->resetPanelBackgroundMask(nativeNode);
    } else {
        GetArkUINodeModifiers()->getPanelModifier()->setPanelBackgroundMask(nativeNode, color.GetValue());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PanelBridge::ResetPanelBackgroundMask(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getPanelModifier()->resetPanelBackgroundMask(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PanelBridge::SetPanelMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> modeArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        SetJSPanelMode(runtimeCallInfo);
        return panda::JSValueRef::Undefined(vm);
    }
    if (modeArg->IsNumber()) {
        int32_t mode = modeArg->Int32Value(vm);
        GetArkUINodeModifiers()->getPanelModifier()->setPanelMode(nativeNode, mode);
    } else {
        GetArkUINodeModifiers()->getPanelModifier()->resetPanelMode(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PanelBridge::ResetPanelMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getPanelModifier()->resetPanelMode(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PanelBridge::SetPanelType(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> typeArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_EQUAL_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), false, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        auto type = static_cast<int32_t>(DEFAULT_PANELTYPE);
        if (typeArg->IsNumber()) {
            const auto typeNumber = typeArg->ToNumber(vm)->Int32Value(vm);
            if (typeNumber >= 0 && typeNumber < static_cast<int32_t>(PANEL_TYPES.size())) {
                type = typeNumber;
            }
        }
        GetArkUINodeModifiers()->getPanelModifier()->setPanelType(nativeNode, type);
        return panda::JSValueRef::Undefined(vm);
    }
    if (typeArg->IsNumber()) {
        int32_t type = typeArg->Int32Value(vm);
        GetArkUINodeModifiers()->getPanelModifier()->setPanelType(nativeNode, type);
    } else {
        GetArkUINodeModifiers()->getPanelModifier()->resetPanelType(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PanelBridge::ResetPanelType(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getPanelModifier()->resetPanelType(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PanelBridge::ResetPanelFullHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getPanelModifier()->resetPanelFullHeight(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PanelBridge::SetPanelFullHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_EQUAL_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), false, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> jsValue = runtimeCallInfo->GetCallArgRef(1);
    CalcDimension height;

    if (jsValue->IsUndefined() || !ArkTSUtils::ParseJsDimensionVpNG(vm, jsValue, height, true)) {
        if (ArkTSUtils::IsJsView(firstArg, vm)) {
            return panda::JSValueRef::Undefined(vm);
        }
        GetArkUINodeModifiers()->getPanelModifier()->resetPanelFullHeight(nativeNode);
    } else {
        if (LessNotEqual(height.Value(), 0.0)) {
            height.SetValue(0.0);
        }
        GetArkUINodeModifiers()->getPanelModifier()->setPanelFullHeight(
            nativeNode, height.Value(), static_cast<int>(height.Unit()));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PanelBridge::ResetPanelHalfHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getPanelModifier()->resetPanelHalfHeight(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PanelBridge::SetPanelHalfHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_EQUAL_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), false, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> jsValue = runtimeCallInfo->GetCallArgRef(1);
    CalcDimension height;

    if (jsValue->IsUndefined() || !ArkTSUtils::ParseJsDimensionVpNG(vm, jsValue, height, true)) {
        if (ArkTSUtils::IsJsView(firstArg, vm)) {
            return panda::JSValueRef::Undefined(vm);
        }
        GetArkUINodeModifiers()->getPanelModifier()->resetPanelHalfHeight(nativeNode);
    } else {
        if (LessNotEqual(height.Value(), 0.0)) {
            height.SetValue(0.0);
        }
        GetArkUINodeModifiers()->getPanelModifier()->setPanelHalfHeight(
            nativeNode, height.Value(), static_cast<int>(height.Unit()));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PanelBridge::ResetPanelMiniHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getPanelModifier()->resetPanelMiniHeight(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PanelBridge::SetPanelMiniHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_EQUAL_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), false, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> jsValue = runtimeCallInfo->GetCallArgRef(1);
    CalcDimension height;

    if (jsValue->IsUndefined() || !ArkTSUtils::ParseJsDimensionVpNG(vm, jsValue, height, true)) {
        if (ArkTSUtils::IsJsView(firstArg, vm)) {
            return panda::JSValueRef::Undefined(vm);
        }
        GetArkUINodeModifiers()->getPanelModifier()->resetPanelMiniHeight(nativeNode);
    } else {
        if (LessNotEqual(height.Value(), 0.0)) {
            height.SetValue(0.0);
        }
        GetArkUINodeModifiers()->getPanelModifier()->setPanelMiniHeight(
            nativeNode, height.Value(), static_cast<int>(height.Unit()));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PanelBridge::SetPanelCustomHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_EQUAL_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), false, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> jsValue = runtimeCallInfo->GetCallArgRef(1);
    CalcDimension customHeight;

    if (jsValue->IsUndefined()) {
        GetArkUINodeModifiers()->getPanelModifier()->resetPanelCustomHeight(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    if (jsValue->IsString(vm) && jsValue->ToString(vm)->ToString(vm).find("wrapContent") != std::string::npos) {
        if (ArkTSUtils::IsJsView(firstArg, vm)) {
            customHeight = CalcDimension(jsValue->ToString(vm)->ToString(vm));
        } else {
            GetArkUINodeModifiers()->getPanelModifier()->setPanelCustomHeightByString(
                nativeNode, jsValue->ToString(vm)->ToString(vm).c_str());
            return panda::JSValueRef::Undefined(vm);
        }
    } else if (!ArkTSUtils::ParseJsDimensionVp(vm, jsValue, customHeight)) {
        customHeight = Dimension(0.0);
    }
    GetArkUINodeModifiers()->getPanelModifier()->setPanelCustomHeight(
        nativeNode, customHeight.Value(), static_cast<int>(customHeight.Unit()));

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PanelBridge::ResetPanelCustomHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getPanelModifier()->resetPanelCustomHeight(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PanelBridge::SetShowCloseIcon(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> showCloseArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (showCloseArg->IsNull()) {
        GetArkUINodeModifiers()->getPanelModifier()->resetShowCloseIcon(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    bool boolValue = false;
    if (showCloseArg->IsBoolean()) {
        boolValue = showCloseArg->ToBoolean(vm)->Value();
    }
    GetArkUINodeModifiers()->getPanelModifier()->setShowCloseIcon(nativeNode, boolValue);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PanelBridge::ResetShowCloseIcon(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getPanelModifier()->resetShowCloseIcon(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PanelBridge::SetDragBar(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> dragBarArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_EQUAL_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), false, panda::JSValueRef::Undefined(vm));
    if (dragBarArg->IsNull()) {
        GetArkUINodeModifiers()->getPanelModifier()->resetDragBar(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    bool boolValue = true;
    if (dragBarArg->IsBoolean()) {
        boolValue = dragBarArg->ToBoolean(vm)->Value();
    }
    GetArkUINodeModifiers()->getPanelModifier()->setDragBar(nativeNode, boolValue);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PanelBridge::ResetDragBar(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getPanelModifier()->resetDragBar(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PanelBridge::SetShow(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> showArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN) &&
        (showArg->IsUndefined() || showArg->IsNull())) {
        GetArkUINodeModifiers()->getPanelModifier()->setShow(nativeNode, true);
        return panda::JSValueRef::Undefined(vm);
    } else {
        bool boolValue = true;
        if (showArg->IsBoolean()) {
            boolValue = showArg->ToBoolean(vm)->Value();
        }
        GetArkUINodeModifiers()->getPanelModifier()->setShow(nativeNode, boolValue);
        return panda::JSValueRef::Undefined(vm);
    }
}

ArkUINativeModuleValue PanelBridge::ResetShow(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getPanelModifier()->resetShow(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PanelBridge::SetOnSizeChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    if (!callbackArg->IsFunction(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_EQUAL_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), false, panda::JSValueRef::Undefined(vm));
    FrameNode* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    Local<panda::FunctionRef> jsfunc = callbackArg->ToObject(vm);
    std::function<void(const BaseEventInfo*)> onSizeChange =
        [func = panda::CopyableGlobal(vm, jsfunc), node = AceType::WeakClaim(frameNode)](
            const BaseEventInfo* info) {
        auto vm = func.GetEcmaVM();
        CHECK_EQUAL_VOID(ArkTSUtils::CheckJavaScriptScope(vm), false);
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        ACE_SCORING_EVENT("SlidingPanel.OnSizeChange");
        PipelineContext::SetCallBackNode(node);
        auto eventInfo = TypeInfoHelper::DynamicCast<SlidingPanelSizeChangeEvent>(info);
        if (!eventInfo) {
            return;
        }
        panda::Local<panda::JSValueRef> params[] = {
            panda::NumberRef::New(vm, eventInfo->GetWidth()),
            panda::NumberRef::New(vm, eventInfo->GetHeight()),
            panda::NumberRef::New(vm, static_cast<int32_t>(eventInfo->GetMode()))
        };
        auto result = func->Call(vm, func.ToLocal(), params, 3);
        ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
    };
    GetArkUINodeModifiers()->getPanelModifier()->setOnSizeChange(
        reinterpret_cast<void*>(&onSizeChange));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PanelBridge::SetOnHeightChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    if (callbackArg->IsUndefined() || !callbackArg->IsFunction(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_EQUAL_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), false, panda::JSValueRef::Undefined(vm));
    FrameNode* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    Local<panda::FunctionRef> jsfunc = callbackArg->ToObject(vm);
    std::function<void(const float)> onHeightChange =
        [func = panda::CopyableGlobal(vm, jsfunc), node = AceType::WeakClaim(frameNode)](
            const float height) {
        auto vm = func.GetEcmaVM();
        CHECK_EQUAL_VOID(ArkTSUtils::CheckJavaScriptScope(vm), false);
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        ACE_SCORING_EVENT("OnHeightChange");
        PipelineContext::SetCallBackNode(node);
        panda::Local<panda::JSValueRef> params[] = { panda::NumberRef::New(vm, height) };
        auto result = func->Call(vm, func.ToLocal(), params, 1);
        ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
    };
    GetArkUINodeModifiers()->getPanelModifier()->setOnHeightChange(reinterpret_cast<void*>(&onHeightChange));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PanelBridge::SetJsBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_EQUAL_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), false, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        nativeNode = nodePtr(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
        CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));

        Color color = Color::TRANSPARENT;
        if (!ArkTSUtils::ParseJsColorAlpha(vm, colorArg, color)) {
            return panda::JSValueRef::Undefined(vm);
        }
        auto headRoomOptional = color.GetHeadRoomColor();
        if (headRoomOptional.has_value()) {
            ArkUIColorHeadRoom colorRom;
            auto colorWithHeadRoom = headRoomOptional.value();
            colorRom.red = static_cast<ArkUI_Float32>(colorWithHeadRoom.red);
            colorRom.green = static_cast<ArkUI_Float32>(colorWithHeadRoom.green);
            colorRom.blue = static_cast<ArkUI_Float32>(colorWithHeadRoom.blue);
            colorRom.alpha = static_cast<ArkUI_Float32>(colorWithHeadRoom.alpha);
            colorRom.headRoom = static_cast<ArkUI_Float32>(colorWithHeadRoom.headRoom);
            colorRom.colorSpace = static_cast<ArkUI_Int32>(color.GetColorSpace());
            GetArkUINodeModifiers()->getPanelModifier()->setBackgroundColorForHDR(nativeNode, colorRom);
            return panda::JSValueRef::Undefined(vm);
        } else {
            GetArkUINodeModifiers()->getPanelModifier()->setPanelBackgroundColorWithColorSpace(
                color.GetValue(), color.GetColorSpace());
        }
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PanelBridge::SetJsPanelBorder(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> borderArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_EQUAL_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), false, panda::JSValueRef::Undefined(vm));
    if (!borderArg->IsObject(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    
    panda::Local<panda::ObjectRef> borderObj = borderArg->ToObject(vm);
    auto widthVal = ArkTSUtils::GetProperty(vm, borderObj, "width");
    CalcDimension width = CalcDimension(0.0, DimensionUnit::VP);
    if (!ArkTSUtils::ParseJsDimensionVpNG(vm, widthVal, width, true)) {
        width = CalcDimension(0.0, DimensionUnit::VP);
    }
    GetArkUINodeModifiers()->getPanelModifier()->setPanelBorderWidth(width.Value(), static_cast<int>(width.Unit()));
    
    auto radiusVal = ArkTSUtils::GetProperty(vm, borderObj, "radius");
    BorderRadius borderRadius;
    ParsePanelRadius(vm, radiusVal, borderRadius);
    ViewAbstractModel::GetInstance()->SetBorderRadius(borderRadius.radiusTopLeft, borderRadius.radiusTopRight,
        borderRadius.radiusBottomLeft, borderRadius.radiusBottomRight);
    
    auto styleVal = ArkTSUtils::GetProperty(vm, borderObj, "style");
    auto borderStyle = BorderStyle::SOLID;
    if (!styleVal->IsUndefined() && styleVal->IsNumber()) {
        auto styleValue = styleVal->ToNumber(vm)->Uint32Value(vm);
        if (styleValue > NUM_0 && styleValue < NUM_4) {
            borderStyle = static_cast<BorderStyle>(styleValue);
        }
    }
    GetArkUINodeModifiers()->getPanelModifier()->setPanelBorderStyle(static_cast<int32_t>(borderStyle));
    
    auto colorVal = ArkTSUtils::GetProperty(vm, borderObj, "color");
    Color borderColor;
    ArkTSUtils::ParseJsColor(vm, colorVal, borderColor);
    GetArkUINodeModifiers()->getPanelModifier()->setPanelBorderColor(borderColor.GetValue());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PanelBridge::SetJsPanelBorderWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> widthArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_EQUAL_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), false, panda::JSValueRef::Undefined(vm));
    CalcDimension borderWidth;
    if (!ArkTSUtils::ParseJsDimensionVpNG(vm, widthArg, borderWidth, true)) {
        return panda::JSValueRef::Undefined(vm);
    }
    GetArkUINodeModifiers()->getPanelModifier()->setPanelBorderWidth(
        borderWidth.Value(), static_cast<int>(borderWidth.Unit()));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PanelBridge::SetJsPanelBorderColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_EQUAL_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), false, panda::JSValueRef::Undefined(vm));
    Color borderColor;
    if (!ArkTSUtils::ParseJsColor(vm, colorArg, borderColor)) {
        return panda::JSValueRef::Undefined(vm);
    }
    GetArkUINodeModifiers()->getPanelModifier()->setPanelBorderColor(borderColor.GetValue());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PanelBridge::SetJsPanelBorderStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> styleArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_EQUAL_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), false, panda::JSValueRef::Undefined(vm));
    auto borderStyle = BorderStyle::SOLID;
    if (styleArg->IsNumber()) {
        auto styleValue = styleArg->ToNumber(vm)->Uint32Value(vm);
        if (styleValue > NUM_0 && styleValue < NUM_4) {
            borderStyle = static_cast<BorderStyle>(styleValue);
        }
    }
    GetArkUINodeModifiers()->getPanelModifier()->setPanelBorderStyle(static_cast<int32_t>(borderStyle));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PanelBridge::SetJsPanelBorderRadius(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> radiusArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_EQUAL_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), false, panda::JSValueRef::Undefined(vm));
    ArkTSUtils::SetRenderStrategy(runtimeCallInfo, NUM_2);
    BorderRadius borderRadius;
    ParsePanelRadius(vm, radiusArg, borderRadius);
    ViewAbstractModel::GetInstance()->SetBorderRadius(borderRadius.radiusTopLeft, borderRadius.radiusTopRight,
        borderRadius.radiusBottomLeft, borderRadius.radiusBottomRight);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG