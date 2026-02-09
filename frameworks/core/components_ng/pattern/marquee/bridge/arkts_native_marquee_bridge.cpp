/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/marquee/bridge/arkts_native_marquee_bridge.h"

#include "base/geometry/dimension.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "core/components/common/properties/text_style.h"
#include "core/components_ng/pattern/marquee/marquee_model_ng.h"

static const std::string DEFAULT_FONT_WEIGHT = "400";
static const std::vector<OHOS::Ace::MarqueeUpdateStrategy> MARQUEE_UPDATE_STRATEGYS = {
    OHOS::Ace::MarqueeUpdateStrategy::DEFAULT, OHOS::Ace::MarqueeUpdateStrategy::PRESERVE_POSITION
};

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t NUM_SIX = 6;
constexpr int32_t NUM_SEVEN = 7;
constexpr int32_t DEFAULT_MARQUEE_LOOP = -1;

bool IsJsView(const Local<JSValueRef>& jsVal, panda::ecmascript::EcmaVM* vm)
{
    return !jsVal->IsNativePointer(vm);
}

void SetMarqueeScrollAmount(const EcmaVM* vm, const Local<JSValueRef>& jsVal, ArkUINodeHandle nativeNode)
{
    if (jsVal->IsNumber()) {
        bool isNumber = false;
        auto step = jsVal->GetValueDouble(isNumber);
        if (GreatNotEqual(step, 0.0)) {
            double stepOpt = Dimension(step, DimensionUnit::VP).ConvertToPx();
            GetArkUINodeModifiers()->getMarqueeModifier()->setMarqueeScrollAmount(nativeNode, stepOpt);
            return;
        }
    }
    GetArkUINodeModifiers()->getMarqueeModifier()->resetMarqueeScrollAmount(nativeNode);
}

void SetMarqueeLoop(const EcmaVM* vm, const Local<JSValueRef>& jsVal, ArkUINodeHandle nativeNode)
{
    if (jsVal->IsNumber()) {
        int32_t loopOpt = 0;
        bool isNumber = false;
        auto loopDouble = jsVal->GetValueDouble(isNumber);
        int32_t loop = DEFAULT_MARQUEE_LOOP;
        if (GreatNotEqual(loopDouble, 0.0)) {
            loop = static_cast<int32_t>(loopDouble);
            if (loop == std::numeric_limits<int32_t>::max() || loop < 0) {
                loop = DEFAULT_MARQUEE_LOOP;
            }
        }
        loopOpt = loop;
        GetArkUINodeModifiers()->getMarqueeModifier()->setMarqueeLoop(nativeNode, loopOpt);
        return;
    }
    GetArkUINodeModifiers()->getMarqueeModifier()->resetMarqueeLoop(nativeNode);
}

void SetMarqueeDelay(const EcmaVM* vm, const Local<JSValueRef>& jsVal, ArkUINodeHandle nativeNode)
{
    if (jsVal->IsNumber()) {
        auto delay = jsVal->Int32Value(vm);
        if (delay > 0) {
            GetArkUINodeModifiers()->getMarqueeModifier()->setMarqueeDelay(nativeNode, delay);
            return;
        }
    }
    GetArkUINodeModifiers()->getMarqueeModifier()->resetMarqueeDelay(nativeNode);
}

bool GetNativeNode(ArkUINodeHandle& nativeNode, const Local<JSValueRef>& firstArg, panda::ecmascript::EcmaVM* vm)
{
    if (firstArg->IsNativePointer(vm)) {
        nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
        return true;
    }
    if (firstArg->IsBoolean() && firstArg->ToBoolean(vm)->Value()) {
        nativeNode = nullptr;
        return true;
    }

    return false;
}

void ParseStartValue(panda::ecmascript::EcmaVM* vm, Local<panda::ObjectRef> paramObj, std::optional<bool>& start)
{
    auto startVal = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "start"));
    if (startVal->IsBoolean()) {
        start = std::optional<bool>(startVal->ToBoolean(vm)->Value());
    } else {
        start = std::optional<bool>(false);
    }
}

void ParseStepValue(panda::ecmascript::EcmaVM* vm, Local<panda::ObjectRef> paramObj, std::optional<double>& step,
    bool isJsView)
{
    auto stepVal = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "step"));
    if (stepVal->IsNumber()) {
        if (GreatNotEqual(stepVal->ToNumber(vm)->Value(), 0.0)) {
            step = std::optional<double>(Dimension(stepVal->ToNumber(vm)->Value(), DimensionUnit::VP).ConvertToPx());
        }
    }
}

void ParseLoopValue(panda::ecmascript::EcmaVM* vm, Local<panda::ObjectRef> paramObj, std::optional<int32_t>& loop,
    bool isJsView)
{
    auto loopVal = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "loop"));
    if (loopVal->IsNumber()) {
        bool isNumber = false;
        auto loopDouble = loopVal->GetValueDouble(isNumber);
        int32_t loopInt = DEFAULT_MARQUEE_LOOP;
        if (GreatNotEqual(loopDouble, 0.0)) {
            loopInt = static_cast<int32_t>(loopDouble);
            if (loopInt == std::numeric_limits<int32_t>::max() || loopInt < 0) {
                loopInt = DEFAULT_MARQUEE_LOOP;
            }
        }
        loop = std::optional<int32_t>(loopInt);
    }
}

void ParseFromStartValue(panda::ecmascript::EcmaVM* vm, Local<panda::ObjectRef> paramObj,
    std::optional<bool>& fromStart)
{
    auto fromStartVal = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "fromStart"));
    if (fromStartVal->IsBoolean()) {
        fromStart = std::optional<bool>(fromStartVal->ToBoolean(vm)->Value());
    } else {
        fromStart = std::optional<bool>(true);
    }
}

void ParseSrcValue(panda::ecmascript::EcmaVM* vm, Local<panda::ObjectRef> paramObj, std::optional<std::string>& src,
    bool isJsView)
{
    auto srcVal = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "src"));
    if (srcVal->IsString(vm)) {
        src = std::optional<std::string>(srcVal->ToString(vm)->ToString(vm));
    } else if (!isJsView) {
        src = std::optional<std::string>("");
    }
}

void ParseSpacingValue(panda::ecmascript::EcmaVM* vm, Local<panda::ObjectRef> paramObj,
    std::optional<CalcDimension>& spacing, RefPtr<ResourceObject> spacingResObj)
{
    auto spacingVal = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "spacing"));
    CalcDimension marqueeSpacing;
    bool spacingParseResult = spacingVal->IsNull() || spacingVal->IsUndefined() ? false :
        ArkTSUtils::ParseJsLengthMetrics(vm, spacingVal, marqueeSpacing, spacingResObj);
    if (spacingParseResult) {
        spacing = std::optional<CalcDimension>(marqueeSpacing);
    }
}

void ParseDelayValue(panda::ecmascript::EcmaVM* vm, Local<panda::ObjectRef> paramObj, std::optional<int32_t>& delay)
{
    auto delayVal = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "delay"));
    bool isNumber = false;
    if (delayVal->IsNumber()) {
        int32_t delayInt = static_cast<int32_t>(delayVal->GetValueDouble(isNumber));
        if (GreatNotEqual(delayInt, 0)) {
            delay = std::optional<int32_t>(delayInt);
        }
    }
}
} // namespace

void MarqueeBridge::RegisterMarqueeAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    const char* functionNames[] = { "create", "setAllowScale", "resetAllowScale", "setFontColor",
        "resetFontColor", "setFontSize", "resetFontSize", "setFontWeight", "resetFontWeight",
        "setFontFamily", "resetFontFamily", "setMarqueeUpdateStrategy", "resetMarqueeUpdateStrategy",
        "setMarqueeOnStart", "resetMarqueeOnStart", "setMarqueeOnBounce", "resetMarqueeOnBounce",
        "setMarqueeOnFinish", "resetMarqueeOnFinish", "setInitialize" };

    Local<JSValueRef> funcValues[] = {
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MarqueeBridge::CreateMarquee),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MarqueeBridge::SetAllowScale),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MarqueeBridge::ResetAllowScale),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MarqueeBridge::SetFontColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MarqueeBridge::ResetFontColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MarqueeBridge::SetFontSize),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MarqueeBridge::ResetFontSize),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MarqueeBridge::SetFontWeight),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MarqueeBridge::ResetFontWeight),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MarqueeBridge::SetFontFamily),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MarqueeBridge::ResetFontFamily),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MarqueeBridge::SetMarqueeUpdateStrategy),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MarqueeBridge::ResetMarqueeUpdateStrategy),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MarqueeBridge::SetMarqueeOnStart),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MarqueeBridge::ResetMarqueeOnStart),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MarqueeBridge::SetMarqueeOnBounce),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MarqueeBridge::ResetMarqueeOnBounce),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MarqueeBridge::SetMarqueeOnFinish),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MarqueeBridge::ResetMarqueeOnFinish),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MarqueeBridge::SetInitialize),

    };

    auto marquee = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(functionNames), functionNames, funcValues);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "marquee"), marquee);
}

void ParseMarqueeAttributes(ArkUINodeHandle& nativeNode, panda::ecmascript::EcmaVM* vm,
    Local<panda::ObjectRef> paramObj, bool isJsView)
{
    std::optional<bool> start;
    std::optional<double> step;
    std::optional<int32_t> loop;
    std::optional<bool> fromStart = std::optional<bool>(true);
    std::optional<std::string> src;
    std::optional<CalcDimension> spacing;
    std::optional<int32_t> delay;
    RefPtr<ResourceObject> spacingResObj;

    if (!paramObj->IsUndefined()) {
        ParseStartValue(vm, paramObj, start);
        ParseStepValue(vm, paramObj, step, isJsView);
        ParseLoopValue(vm, paramObj, loop, isJsView);
        ParseFromStartValue(vm, paramObj, fromStart);
        ParseSrcValue(vm, paramObj, src, isJsView);
        ParseSpacingValue(vm, paramObj, spacing, spacingResObj);
        ParseDelayValue(vm, paramObj, delay);
    }
    if (isJsView) {
        static MarqueeModelNG model;
        model.Create();
    }
    start.has_value() ? GetArkUINodeModifiers()->getMarqueeModifier()->setMarqueePlayerStatus(nativeNode, start.value())
                      : GetArkUINodeModifiers()->getMarqueeModifier()->resetMarqueePlayerStatus(nativeNode);
    step.has_value() ? GetArkUINodeModifiers()->getMarqueeModifier()->setMarqueeScrollAmount(nativeNode, step.value())
                     : GetArkUINodeModifiers()->getMarqueeModifier()->resetMarqueeScrollAmount(nativeNode);
    loop.has_value() ? GetArkUINodeModifiers()->getMarqueeModifier()->setMarqueeLoop(nativeNode, loop.value())
                     : GetArkUINodeModifiers()->getMarqueeModifier()->resetMarqueeLoop(nativeNode);
    int32_t marqueeDirection = fromStart.value() ?
        static_cast<int32_t>(MarqueeDirection::LEFT) : static_cast<int32_t>(MarqueeDirection::RIGHT);
    fromStart.has_value() ?
        GetArkUINodeModifiers()->getMarqueeModifier()->setMarqueeDirection(nativeNode, marqueeDirection) :
        GetArkUINodeModifiers()->getMarqueeModifier()->resetMarqueeDirection(nativeNode);
    src.has_value() ? GetArkUINodeModifiers()->getMarqueeModifier()->setMarqueeSrcValue(nativeNode, src.value().c_str())
                    : GetArkUINodeModifiers()->getMarqueeModifier()->resetMarqueeSrcValue(nativeNode);
    spacing.has_value() ? GetArkUINodeModifiers()->getMarqueeModifier()->setMarqueeSpacing(nativeNode,
        spacing.value().Value(), static_cast<int>(spacing.value().Unit()), AceType::RawPtr(spacingResObj))
                       : GetArkUINodeModifiers()->getMarqueeModifier()->resetMarqueeSpacing(nativeNode);
    delay.has_value() ? GetArkUINodeModifiers()->getMarqueeModifier()->setMarqueeDelay(nativeNode, delay.value())
                      : GetArkUINodeModifiers()->getMarqueeModifier()->resetMarqueeDelay(nativeNode);
}

ArkUINativeModuleValue MarqueeBridge::CreateMarquee(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    bool isJSView = IsJsView(firstArg, vm);
    auto paramObj = firstArg->ToObject(vm);
    ArkUINodeHandle nativeNode = nullptr;
    if (firstArg->IsObject(vm)) {
        paramObj = firstArg->ToObject(vm);
    } else {
        CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
        if (!isJSView) {
            if (secondArg->IsObject(vm)) {
                paramObj = secondArg->ToObject(vm);
            }
        }
    }
    ParseMarqueeAttributes(nativeNode, vm, paramObj, isJSView);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MarqueeBridge::SetAllowScale(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool allowScale = secondArg->ToBoolean(vm)->Value();
    GetArkUINodeModifiers()->getMarqueeModifier()->setMarqueeAllowScale(nativeNode, allowScale);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MarqueeBridge::ResetAllowScale(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getMarqueeModifier()->resetMarqueeAllowScale(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MarqueeBridge::SetFontWeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> weightArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    std::string weight = DEFAULT_FONT_WEIGHT;
    if (!weightArg->IsNull()) {
        if (weightArg->IsNumber()) {
            weight = std::to_string(weightArg->Int32Value(vm));
        } else if (weightArg->IsString(vm)) {
            weight = weightArg->ToString(vm)->ToString(vm);
        }
    }
    GetArkUINodeModifiers()->getMarqueeModifier()->setMarqueeFontWeight(nativeNode, weight.c_str());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MarqueeBridge::ResetFontWeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getMarqueeModifier()->resetMarqueeFontWeight(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MarqueeBridge::SetFontFamily(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (!secondArg->IsString(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    std::string families = secondArg->ToString(vm)->ToString(vm);
    GetArkUINodeModifiers()->getMarqueeModifier()->setMarqueeFontFamily(nativeNode, families.c_str());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MarqueeBridge::ResetFontFamily(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getMarqueeModifier()->resetMarqueeFontFamily(nativeNode, IsJsView(firstArg, vm));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MarqueeBridge::SetFontSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    CalcDimension fontSize;
    RefPtr<ResourceObject> fontSizeResObj;
    if (!ArkTSUtils::ParseJsDimensionFp(vm, secondArg, fontSize, fontSizeResObj) || fontSize.IsNegative() ||
        fontSize.Unit() == DimensionUnit::PERCENT) {
        bool isJsView = IsJsView(firstArg, vm);
        GetArkUINodeModifiers()->getMarqueeModifier()->resetMarqueeFontSize(nativeNode, isJsView);
    } else {
        GetArkUINodeModifiers()->getMarqueeModifier()->setMarqueeFontSize(
            nativeNode, fontSize.Value(), static_cast<int>(fontSize.Unit()), AceType::RawPtr(fontSizeResObj));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MarqueeBridge::ResetFontSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = IsJsView(firstArg, vm);
    GetArkUINodeModifiers()->getMarqueeModifier()->resetMarqueeFontSize(nativeNode, isJsView);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MarqueeBridge::SetFontColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    Color color;
    RefPtr<ResourceObject> colorResObj;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color, colorResObj, nodeInfo)) {
        GetArkUINodeModifiers()->getMarqueeModifier()->resetMarqueeFontColor(nativeNode);
    } else {
        GetArkUINodeModifiers()->getMarqueeModifier()->setMarqueeFontColor(
            nativeNode, color.GetValue(), AceType::RawPtr(colorResObj));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MarqueeBridge::ResetFontColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getMarqueeModifier()->resetMarqueeFontColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MarqueeBridge::SetMarqueeUpdateStrategy(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto value = secondArg->ToString(vm)->ToString(vm);
    static const LinearMapNode<MarqueeUpdateStrategy> marqueeUpdateStrategyTable[] = {
        { "default", MarqueeUpdateStrategy::DEFAULT },
        { "preserve_position", MarqueeUpdateStrategy::PRESERVE_POSITION },
    };
    auto marqueeUpdateStrategyIter =
        BinarySearchFindIndex(marqueeUpdateStrategyTable, ArraySize(marqueeUpdateStrategyTable), value.c_str());
    if (marqueeUpdateStrategyIter != -1) {
        GetArkUINodeModifiers()->getMarqueeModifier()->setMarqueeUpdateStrategy(nativeNode, marqueeUpdateStrategyIter);
    } else {
        GetArkUINodeModifiers()->getMarqueeModifier()->resetMarqueeUpdateStrategy(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MarqueeBridge::ResetMarqueeUpdateStrategy(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getMarqueeModifier()->resetMarqueeUpdateStrategy(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MarqueeBridge::SetMarqueeOnStart(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getMarqueeModifier()->resetMarqueeOnStart(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    bool isJsView = IsJsView(firstArg, vm);
    auto frameNode =
        isJsView ? ViewStackProcessor::GetInstance()->GetMainFrameNode() : reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(void)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func), isJsView]() {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        auto result = func->Call(vm, func.ToLocal(), nullptr, 0);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        }
    };
    GetArkUINodeModifiers()->getMarqueeModifier()->setMarqueeOnStart(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MarqueeBridge::ResetMarqueeOnStart(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getMarqueeModifier()->resetMarqueeOnStart(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MarqueeBridge::SetMarqueeOnBounce(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getMarqueeModifier()->resetMarqueeOnBounce(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    bool isJsView = IsJsView(firstArg, vm);
    auto frameNode =
        isJsView ? ViewStackProcessor::GetInstance()->GetMainFrameNode() : reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(void)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func), isJsView]() {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        auto result = func->Call(vm, func.ToLocal(), nullptr, 0);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        }
    };
    GetArkUINodeModifiers()->getMarqueeModifier()->setMarqueeOnBounce(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MarqueeBridge::ResetMarqueeOnBounce(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getMarqueeModifier()->resetMarqueeOnBounce(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MarqueeBridge::SetMarqueeOnFinish(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getMarqueeModifier()->resetMarqueeOnFinish(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    bool isJsView = IsJsView(firstArg, vm);
    auto frameNode =
        isJsView ? ViewStackProcessor::GetInstance()->GetMainFrameNode() : reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(void)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func), isJsView]() {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        auto result = func->Call(vm, func.ToLocal(), nullptr, 0);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        }
    };
    GetArkUINodeModifiers()->getMarqueeModifier()->setMarqueeOnFinish(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MarqueeBridge::ResetMarqueeOnFinish(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getMarqueeModifier()->resetMarqueeOnFinish(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MarqueeBridge::SetInitialize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeVal = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> startVal = runtimeCallInfo->GetCallArgRef(1);
    Local<JSValueRef> stepVal = runtimeCallInfo->GetCallArgRef(2);
    Local<JSValueRef> loopVal = runtimeCallInfo->GetCallArgRef(3);
    Local<JSValueRef> fromStartVal = runtimeCallInfo->GetCallArgRef(4);
    Local<JSValueRef> srcVal = runtimeCallInfo->GetCallArgRef(5);
    Local<JSValueRef> spacing = runtimeCallInfo->GetCallArgRef(NUM_SIX);
    Local<JSValueRef> delayVal = runtimeCallInfo->GetCallArgRef(NUM_SEVEN);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, nodeVal, vm), true, panda::JSValueRef::Undefined(vm));
    bool fromStart = fromStartVal->IsBoolean() ? fromStartVal->ToBoolean(vm)->Value() : true;
    SetMarqueeScrollAmount(vm, stepVal, nativeNode);
    SetMarqueeLoop(vm, loopVal, nativeNode);
    GetArkUINodeModifiers()->getMarqueeModifier()->setMarqueePlayerStatus(
        nativeNode, startVal->IsBoolean() ? startVal->ToBoolean(vm)->Value() : false);
    GetArkUINodeModifiers()->getMarqueeModifier()->setMarqueeDirection(nativeNode,
        fromStart ? static_cast<int32_t>(MarqueeDirection::LEFT) : static_cast<int32_t>(MarqueeDirection::RIGHT));
    if (srcVal->IsString(vm)) {
        GetArkUINodeModifiers()->getMarqueeModifier()->setMarqueeSrcValue(
            nativeNode, srcVal->ToString(vm)->ToString(vm).c_str());
    } else {
        GetArkUINodeModifiers()->getMarqueeModifier()->resetMarqueeSrcValue(nativeNode);
    }

    CalcDimension marqueeSpacing;
    RefPtr<ResourceObject> spacingResObj;
    bool spacingParseResult = (spacing->IsNull() || spacing->IsUndefined()) ? false:
        ArkTSUtils::ParseJsLengthMetrics(vm, spacing, marqueeSpacing, spacingResObj);
    if (spacingParseResult) {
        GetArkUINodeModifiers()->getMarqueeModifier()->setMarqueeSpacing(nativeNode,
            marqueeSpacing.Value(), static_cast<int>(marqueeSpacing.Unit()), AceType::RawPtr(spacingResObj));
    } else {
        GetArkUINodeModifiers()->getMarqueeModifier()->resetMarqueeSpacing(nativeNode);
    }

    SetMarqueeDelay(vm, delayVal, nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG