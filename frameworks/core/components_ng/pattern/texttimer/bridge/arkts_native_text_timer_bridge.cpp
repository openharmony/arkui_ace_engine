/*
 * Copyright (c) 2023-2026 Huawei Device Co., Ltd.
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
#include "frameworks/core/components_ng/pattern/texttimer/bridge/arkts_native_text_timer_bridge.h"
#include "base/utils/string_utils.h"
#include "base/utils/utils.h"
#include "frameworks/base/geometry/calc_dimension.h"
#include "frameworks/base/geometry/dimension.h"
#include "frameworks/core/components_v2/inspector/utils.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/jsi_value_conversions.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "core/components/declaration/texttimer/texttimer_declaration.h"
#include "core/components/text/text_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/texttimer/text_timer_model_ng.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_texttimer_controller.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t NUM_0 = 0;
constexpr int32_t NUM_1 = 1;
constexpr int32_t NUM_2 = 2;
constexpr int32_t NUM_3 = 3;
constexpr int32_t NUM_4 = 4;
constexpr int32_t NUM_5 = 5;
constexpr int32_t NUM_6 = 6;
constexpr int32_t NUM_7 = 7;
constexpr bool DEFAULT_COUNT_DOWN = false;
constexpr double MAX_COUNT_DOWN = 86400000.0;
const std::string DEFAULT_STR = "-1";
const char* TEXTTIMER_NODEPTR_OF_UINODE = "nodePtr_";
const std::string DEFAULT_FORMAT = "HH:mm:ss.SS";
} // namespace

bool IsEmptyJsString(const Local<JSValueRef>& arg, panda::ecmascript::EcmaVM* vm)
{
    return arg->IsString(vm) && arg->ToString(vm)->ToString(vm).empty();
}

void SetJSFontColor(const Local<JSValueRef>& paramArg, const Local<JSValueRef>& nodeArg,
    panda::ecmascript::EcmaVM* vm, ArkUINodeHandle nativeNode)
{
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_VOID(nodeModifiers);
    Color textColor;
    RefPtr<ResourceObject> resObj;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (SystemProperties::ConfigChangePerform()) {
        bool state = ArkTSUtils::ParseJsColorAlpha(vm, paramArg, textColor, resObj, nodeInfo);
        if (state) {
            nodeModifiers->getTextTimerModifier()->setFontColorRes(
                nativeNode, textColor.GetValue(), AceType::RawPtr(resObj));
            nodeModifiers->getTextTimerModifier()->setTextColorByUser(nativeNode, true);
        } else {
            auto theme = ArkTSUtils::GetTheme<TextTheme>();
            CHECK_NULL_VOID(theme);
            textColor = theme->GetTextStyle().GetTextColor();
            nodeModifiers->getTextTimerModifier()->setFontColorRes(nativeNode, textColor.GetValue(), nullptr);
            nodeModifiers->getTextTimerModifier()->setTextColorByUser(nativeNode, false);
        }
    } else {
        bool setTextColorByUser = true;
        if (!ArkTSUtils::ParseJsColorAlpha(vm, paramArg, textColor, resObj, nodeInfo)) {
            auto theme = ArkTSUtils::GetTheme<TextTheme>();
            CHECK_NULL_VOID(theme);
            textColor = theme->GetTextStyle().GetTextColor();
            setTextColorByUser = false;
        }
        nodeModifiers->getTextTimerModifier()->setFontColorRes(nativeNode, textColor.GetValue(), nullptr);
        nodeModifiers->getTextTimerModifier()->setTextColorByUser(nativeNode, setTextColorByUser);
    }
}

ArkUINativeModuleValue TextTimerBridge::SetFontColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> paramArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(nodeArg, vm)) {
        SetJSFontColor(paramArg, nodeArg, vm, nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    Color color;
    RefPtr<ResourceObject> colorResObj;
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!ArkTSUtils::ParseJsColorAlpha(vm, paramArg, color, colorResObj, nodeInfo)) {
        nodeModifiers->getTextTimerModifier()->resetFontColor(nativeNode);
    } else {
        auto colorRawPtr = AceType::RawPtr(colorResObj);
        nodeModifiers->getTextTimerModifier()->setFontColorRes(nativeNode, color.GetValue(), colorRawPtr);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextTimerBridge::ResetFontColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getTextTimerModifier()->resetFontColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextTimerBridge::SetFontSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> fontSizeArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    CalcDimension fontSize;
    RefPtr<ResourceObject> fontSizeResObj;
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    bool isEmptyFontSize = IsEmptyJsString(fontSizeArg, vm);
    if ((isEmptyFontSize || !ArkTSUtils::ParseJsDimensionFp(vm, fontSizeArg, fontSize, fontSizeResObj)) ||
        fontSize.Value() < 0 ||
        fontSize.Unit() == DimensionUnit::PERCENT) {
        if (ArkTSUtils::IsJsView(nodeArg, vm)) {
            if (isEmptyFontSize) {
                fontSize = CalcDimension(0.0, DimensionUnit::FP);
                fontSizeResObj = nullptr;
            } else {
                auto theme = ArkTSUtils::GetTheme<TextTheme>();
                CHECK_NULL_RETURN(theme, panda::JSValueRef::Undefined(vm));
                fontSize = theme->GetTextStyle().GetFontSize();
            }
            auto fontSizeRawPtr = AceType::RawPtr(fontSizeResObj);
            nodeModifiers->getTextTimerModifier()->setFontSizeRes(
                nativeNode, fontSize.Value(), static_cast<int32_t>(fontSize.Unit()), fontSizeRawPtr);
            nodeModifiers->getTextTimerModifier()->setFontSizeByUser(nativeNode, false);
        } else {
            nodeModifiers->getTextTimerModifier()->resetFontSize(nativeNode);
        }
    } else {
        auto fontSizeRawPtr = AceType::RawPtr(fontSizeResObj);
        nodeModifiers->getTextTimerModifier()->setFontSizeRes(
            nativeNode, fontSize.Value(), static_cast<int32_t>(fontSize.Unit()), fontSizeRawPtr);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextTimerBridge::ResetFontSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getTextTimerModifier()->resetFontSize(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextTimerBridge::SetFontStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> paramArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(nodeArg, vm);
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (!paramArg->IsNumber()) {
        nodeModifiers->getTextTimerModifier()->resetFontStyle(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    uint32_t fontStyle = paramArg->Uint32Value(vm);
    if (fontStyle < static_cast<uint32_t>(OHOS::Ace::FontStyle::NORMAL) ||
        fontStyle > static_cast<uint32_t>(OHOS::Ace::FontStyle::ITALIC)) {
        if (isJsView) {
            return panda::JSValueRef::Undefined(vm);
        }
        nodeModifiers->getTextTimerModifier()->resetFontStyle(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    nodeModifiers->getTextTimerModifier()->setFontStyle(nativeNode, fontStyle);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextTimerBridge::ResetFontStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getTextTimerModifier()->resetFontStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextTimerBridge::SetFontWeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> fontWeightArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    std::string fontWeight;
    RefPtr<ResourceObject> fontWeightResObj;
    if (!fontWeightArg->IsNull()) {
        if (fontWeightArg->IsNumber()) {
            fontWeight = std::to_string(fontWeightArg->Int32Value(vm));
        } else if (fontWeightArg->IsString(vm)) {
            fontWeight = fontWeightArg->ToString(vm)->ToString(vm);
        } else if (fontWeightArg->IsObject(vm)) {
            ArkTSUtils::ParseJsString(vm, fontWeightArg, fontWeight, fontWeightResObj);
        } else if (fontWeightArg->IsUndefined() && ArkTSUtils::IsJsView(nodeArg, vm)) {
            auto textTheme = ArkTSUtils::GetTheme<TextTheme>();
            CHECK_NULL_RETURN(textTheme, panda::JSValueRef::Undefined(vm));
            fontWeight = V2::ConvertWrapFontWeightToStirng(textTheme->GetTextStyle().GetFontWeight());
        }
    } else if (ArkTSUtils::IsJsView(nodeArg, vm)) {
        auto textTheme = ArkTSUtils::GetTheme<TextTheme>();
        CHECK_NULL_RETURN(textTheme, panda::JSValueRef::Undefined(vm));
        fontWeight = V2::ConvertWrapFontWeightToStirng(textTheme->GetTextStyle().GetFontWeight());
    }
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    auto fontWeightRawPtr = AceType::RawPtr(fontWeightResObj);
    nodeModifiers->getTextTimerModifier()->setFontWeightRes(nativeNode, fontWeight.c_str(), fontWeightRawPtr);
    if (fontWeightArg->IsNull() || fontWeightArg->IsUndefined()) {
        nodeModifiers->getTextTimerModifier()->setFontWeightByUser(nativeNode, false);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextTimerBridge::ResetFontWeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getTextTimerModifier()->resetFontWeight(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextTimerBridge::SetFontFamily(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> fontFamilyArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));

    std::string fontFamilyStr;
    RefPtr<ResourceObject> fontFamilyResObj;
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (!ArkTSUtils::ParseJsFontFamiliesToString(vm, fontFamilyArg, fontFamilyStr, fontFamilyResObj)) {
        if (ArkTSUtils::IsJsView(nodeArg, vm)) {
            return panda::JSValueRef::Undefined(vm);
        }
        nodeModifiers->getTextTimerModifier()->resetFontFamily(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto fontFamilyRawPtr = AceType::RawPtr(fontFamilyResObj);
    nodeModifiers->getTextTimerModifier()->setFontFamilyRes(nativeNode, fontFamilyStr.c_str(), fontFamilyRawPtr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextTimerBridge::ResetFontFamily(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));

    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getTextTimerModifier()->resetFontFamily(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextTimerBridge::SetFormat(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (!secondArg->IsString(vm)) {
        if (isJsView) {
            if (!secondArg->IsUndefined()) {
                nodeModifiers->getTextTimerModifier()->setFormat(nativeNode, DEFAULT_FORMAT.c_str());
            }
            return panda::JSValueRef::Undefined(vm);
        }
        nodeModifiers->getTextTimerModifier()->resetFormat(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    std::string format = secondArg->ToString(vm)->ToString(vm);
    if (isJsView) {
        std::smatch result;
        std::regex pattern("(([YyMdD]+))");
        if (std::regex_search(format, result, pattern)) {
            if (!result.empty()) {
                format = DEFAULT_FORMAT;
            }
        }

        std::string target = "HmsS:.";
        for (auto ch : format) {
            if (target.find(ch) == std::string::npos) {
                format = DEFAULT_FORMAT;
            }
        }

        auto pos = format.find("hh");
        if (pos != std::string::npos) {
            format.replace(pos, sizeof("hh") - 1, "HH");
        }
    }
    nodeModifiers->getTextTimerModifier()->setFormat(nativeNode, format.c_str());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextTimerBridge::ResetFormat(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getTextTimerModifier()->resetFormat(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextTimerBridge::SetTextShadow(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> lengthArg = runtimeCallInfo->GetCallArgRef(NUM_7);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    if (!lengthArg->IsNumber() || lengthArg->Uint32Value(vm) == 0) {
        return panda::JSValueRef::Undefined(vm);
    }
    uint32_t length = lengthArg->Uint32Value(vm);
    auto radiusArray = std::make_unique<double[]>(length);
    auto typeArray = std::make_unique<uint32_t[]>(length);
    auto colorArray = std::make_unique<uint32_t[]>(length);
    auto offsetXArray = std::make_unique<double[]>(length);
    auto offsetYArray = std::make_unique<double[]>(length);
    auto fillArray = std::make_unique<uint32_t[]>(length);
    std::vector<RefPtr<ResourceObject>> radiusResObjArray;
    std::vector<RefPtr<ResourceObject>> colorResObjArray;
    std::vector<RefPtr<ResourceObject>> offsetXResObjArray;
    std::vector<RefPtr<ResourceObject>> offsetYResObjArray;
    bool radiusParseResult = ArkTSUtils::ParseArrayWithResObj<double>(vm, runtimeCallInfo->GetCallArgRef(NUM_1),
        radiusArray.get(), length, ArkTSUtils::parseTextShadowRadiusWithResObj, radiusResObjArray);
    bool typeParseResult = ArkTSUtils::ParseArray<uint32_t>(
        vm, runtimeCallInfo->GetCallArgRef(NUM_2), typeArray.get(), length, ArkTSUtils::parseShadowType);
    bool colorParseResult = ArkTSUtils::ParseArrayWithResObj<uint32_t>(vm, runtimeCallInfo->GetCallArgRef(NUM_3),
        colorArray.get(), length, ArkTSUtils::parseShadowColorWithResObj, colorResObjArray);
    bool offsetXParseResult = ArkTSUtils::ParseArrayWithResObj<double>(vm, runtimeCallInfo->GetCallArgRef(NUM_4),
        offsetXArray.get(), length, ArkTSUtils::parseShadowOffsetWithResObj, offsetXResObjArray);
    bool offsetYParseResult = ArkTSUtils::ParseArrayWithResObj<double>(vm, runtimeCallInfo->GetCallArgRef(NUM_5),
        offsetYArray.get(), length, ArkTSUtils::parseShadowOffsetWithResObj, offsetYResObjArray);
    bool fillParseResult = ArkTSUtils::ParseArray<uint32_t>(
        vm, runtimeCallInfo->GetCallArgRef(NUM_6), fillArray.get(), length, ArkTSUtils::parseShadowFill);
    if (!radiusParseResult || !colorParseResult || !offsetXParseResult ||
        !offsetYParseResult || !fillParseResult || !typeParseResult) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto textShadowArray = std::make_unique<ArkUITextShadowStruct[]>(length);
    auto textShadowResArray = std::make_unique<ArkUITextShadowResStruct[]>(length);
    CHECK_NULL_RETURN(textShadowArray && textShadowResArray, panda::JSValueRef::Undefined(vm));
    for (uint32_t i = 0; i < length; i++) {
        textShadowArray[i] = { radiusArray[i], typeArray[i], colorArray[i], offsetXArray[i], offsetYArray[i],
            fillArray[i] };
        textShadowResArray[i] = { AceType::RawPtr(radiusResObjArray[i]), AceType::RawPtr(colorResObjArray[i]),
            AceType::RawPtr(offsetXResObjArray[i]), AceType::RawPtr(offsetYResObjArray[i]) };
    }
    GetArkUINodeModifiers()->getTextTimerModifier()->setTextShadowRes(
        nativeNode, textShadowArray.get(), textShadowResArray.get(), length);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextTimerBridge::ResetTextShadow(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getTextTimerModifier()->resetTextShadow(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextTimerBridge::SetContentModifierBuilder(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto* frameNode = reinterpret_cast<FrameNode*>(firstArg->ToNativePointer(vm)->Value());
    if (!secondArg->IsObject(vm)) {
        TextTimerModelNG::SetBuilderFunc(frameNode, nullptr);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::CopyableGlobal<panda::ObjectRef> obj(vm, secondArg);
    TextTimerModelNG::SetBuilderFunc(frameNode,
        [vm, frameNode, obj = std::move(obj), containerId = Container::CurrentId()](
            TextTimerConfiguration config) -> RefPtr<FrameNode> {
            LocalScope pandaScope(vm);
            ContainerScope scope(containerId);
            auto context = ArkTSUtils::GetContext(vm);
            CHECK_EQUAL_RETURN(context->IsUndefined(), true, nullptr);
            const char* keysOfTextTimer[] = { "count", "isCountDown", "started", "enabled", "elapsedTime",
                "startTime" };
            Local<JSValueRef> valuesOfTextTimer[] = { panda::NumberRef::New(vm, config.count_),
                panda::BooleanRef::New(vm, config.isCountDown_), panda::BooleanRef::New(vm, config.started_),
                panda::BooleanRef::New(vm, config.enabled_),
                panda::NumberRef::New(vm, static_cast<int64_t>(config.elapsedTime_)),
                panda::NumberRef::New(vm, config.startTime_) };
            auto textTimer = panda::ObjectRef::NewWithNamedProperties(vm,
                ArraySize(keysOfTextTimer), keysOfTextTimer, valuesOfTextTimer);
            textTimer->SetNativePointerFieldCount(vm, 1);
            textTimer->SetNativePointerField(vm, 0, static_cast<void*>(frameNode));
            panda::Local<panda::JSValueRef> params[2] = { context, textTimer };
            panda::TryCatch trycatch(vm);
            auto jsObject = obj.ToLocal();
            auto makeFunc = jsObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "makeContentModifierNode"));
            CHECK_EQUAL_RETURN(makeFunc->IsFunction(vm), false, nullptr);
            panda::Local<panda::FunctionRef> func = makeFunc;
            auto result = func->Call(vm, jsObject, params, 2);
            JSNApi::ExecutePendingJob(vm);
            CHECK_EQUAL_RETURN(result.IsEmpty() || trycatch.HasCaught() || !result->IsObject(vm), true, nullptr);
            auto resultObj = result->ToObject(vm);
            panda::Local<panda::JSValueRef> nodeptr =
                resultObj->Get(vm, panda::StringRef::NewFromUtf8(vm, TEXTTIMER_NODEPTR_OF_UINODE));
            CHECK_EQUAL_RETURN(nodeptr.IsEmpty() || nodeptr->IsUndefined() || nodeptr->IsNull(), true, nullptr);
            auto* frameNode = reinterpret_cast<FrameNode*>(nodeptr->ToNativePointer(vm)->Value());
            CHECK_NULL_RETURN(frameNode, nullptr);
            return AceType::Claim(frameNode);
        });
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextTimerBridge::SetTextTimerOptions(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeVal = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> isCountDownVal = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> countVal = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> controllerVal = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> startTimeVal = runtimeCallInfo->GetCallArgRef(NUM_4);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeVal, vm), true, panda::JSValueRef::Undefined(vm));
    bool isCountDown = isCountDownVal->IsBoolean() ? isCountDownVal->ToBoolean(vm)->Value() : DEFAULT_COUNT_DOWN;
    double count = TIME_DEFAULT_COUNT;
    if (isCountDown && countVal->IsNumber()) {
        auto tempCount = countVal->ToNumber(vm)->Value();
        if (tempCount > 0 && tempCount < MAX_COUNT_DOWN) {
            count = tempCount;
        }
    }
    int32_t startTime = startTimeVal->IsNumber() ? startTimeVal->Int32Value(vm) : 0;
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getTextTimerModifier()->setTextTimerOptions(nativeNode, isCountDown, count, startTime);
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    if (controllerVal->IsObject(vm)) {
        auto* jsController = Framework::JsiRef<Framework::JsiObject>(Framework::JsiObject(controllerVal->ToObject(vm)))
                                 ->Unwrap<Framework::JSTextTimerController>();
        CHECK_NULL_RETURN(jsController, panda::JSValueRef::Undefined(vm));
        auto pointer = TextTimerModelNG::GetJSTextTimerController(frameNode);
        auto preController = static_cast<Framework::JSTextTimerController*>(Referenced::RawPtr(pointer));
        if (preController) {
            preController->SetController(nullptr);
        }
        TextTimerModelNG::SetJSTextTimerController(
            frameNode, Referenced::Claim(static_cast<Referenced*>(jsController)));
        auto controller = TextTimerModelNG::InitTextController(frameNode);
        jsController->SetInstanceId(Container::CurrentId());
        jsController->SetController(controller);
    } else {
        auto pointer = TextTimerModelNG::GetJSTextTimerController(frameNode);
        auto preController = static_cast<Framework::JSTextTimerController*>(Referenced::RawPtr(pointer));
        if (preController) {
            preController->SetController(nullptr);
        }
        TextTimerModelNG::SetJSTextTimerController(frameNode, nullptr);
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextTimerBridge::SetTextTimerOnTimer(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getTextTimerModifier()->resetTextTimerOnTimer(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    if (frameNode == nullptr) {
        if (isJsView) {
            frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
        } else {
            return panda::JSValueRef::Undefined(vm);
        }
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);

    std::function<void(int64_t, int64_t)> callback = [vm, frameNode, isJsView, func = panda::CopyableGlobal(vm, func)](
                                                         const int64_t first, const int64_t last) {
        auto vm = func.GetEcmaVM();
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));

        panda::Local<panda::NumberRef> firstParam = panda::NumberRef::New(vm, first);
        panda::Local<panda::NumberRef> lastParam = panda::NumberRef::New(vm, last);
        // 2: Array length
        panda::Local<panda::JSValueRef> params[2] = { firstParam, lastParam };
        auto result = func->Call(vm, func.ToLocal(), params, 2); // 2: Array length
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        }
    };
    GetArkUINodeModifiers()->getTextTimerModifier()->setTextTimerOnTimer(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextTimerBridge::ResetTextTimerOnTimer(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextTimerModifier()->resetTextTimerOnTimer(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

void SetFontDefault(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    if (runtimeCallInfo->GetCallArgRef(NUM_0).IsEmpty() && runtimeCallInfo->GetCallArgRef(NUM_1).IsEmpty() &&
        runtimeCallInfo->GetCallArgRef(NUM_2).IsEmpty() && runtimeCallInfo->GetCallArgRef(NUM_3).IsEmpty()) {
        RefPtr<TextTheme> textTheme = ArkTSUtils::GetTheme<TextTheme>();
        auto nodeModifiers = GetArkUINodeModifiers();
        CHECK_NULL_VOID(nodeModifiers);
        nodeModifiers->getTextTimerModifier()->setFontDefault(nullptr);
    }
}

ArkUINativeModuleValue TextTimerBridge::CreateTextTimer(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));

    Local<JSValueRef> isCountDownVal = runtimeCallInfo->GetCallArgRef(NUM_0);
    SetFontDefault(runtimeCallInfo);
    GetArkUINodeModifiers()->getTextTimerModifier()->createTextTimerModel();
    if (!isCountDownVal.IsEmpty() && isCountDownVal->IsBoolean()) {
        bool isCountDown = isCountDownVal->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getTextTimerModifier()->setIsCountDown(nullptr, isCountDown);
        if (isCountDown) {
            Local<JSValueRef> countVal = runtimeCallInfo->GetCallArgRef(NUM_1);
            if (!countVal.IsEmpty() && countVal->IsNumber()) {
                auto inputCount = countVal->ToNumber(vm)->Value();
                if (inputCount > 0 && inputCount < MAX_COUNT_DOWN) {
                    GetArkUINodeModifiers()->getTextTimerModifier()->setInputCount(nullptr, inputCount);
                } else {
                    GetArkUINodeModifiers()->getTextTimerModifier()->setInputCount(nullptr, TIME_DEFAULT_COUNT);
                }
            }
            if (countVal.IsEmpty() || countVal->IsUndefined() || countVal->IsNull()) {
                GetArkUINodeModifiers()->getTextTimerModifier()->setInputCount(nullptr, TIME_DEFAULT_COUNT);
            }
        }
    }
    int32_t startTime = 0;
    Local<JSValueRef> startTimeVal = runtimeCallInfo->GetCallArgRef(NUM_3);
    if (!startTimeVal.IsEmpty() && startTimeVal->IsNumber()) {
        startTime = startTimeVal->Int32Value(vm);
    }
    GetArkUINodeModifiers()->getTextTimerModifier()->setStartTime(nullptr, startTime);

    auto* frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();

    auto controllerVal = runtimeCallInfo->GetCallArgRef(NUM_2);
    if (!controllerVal.IsEmpty() && controllerVal->IsObject(vm)) {
        auto* jsController =
            Framework::JsiRef<Framework::JsiObject>(Framework::JsiObject(controllerVal->ToObject(vm)))
                .Unwrap<Framework::JSTextTimerController>();
        if (jsController && frameNode) {
            auto controller = TextTimerModelNG::InitTextController(frameNode);
            jsController->SetInstanceId(Container::CurrentId());
            jsController->SetController(controller);
        }
    }
    
    return panda::JSValueRef::Undefined(vm);
}

void TextTimerBridge::RegisterAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    const char* functionNames[] = {
        "create", "setFontColor", "resetFontColor", "setFontSize", "resetFontSize",
        "setFontWeight", "resetFontWeight", "setFontStyle", "resetFontStyle", "setFontFamily", "resetFontFamily",
        "setFormat", "resetFormat", "setTextShadow", "resetTextShadow", "setTextTimerOnTimer", "resetTextTimerOnTimer",
        "setTextTimerOptions", "setContentModifierBuilder"
    };

    Local<JSValueRef> funcValues[] = {
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextTimerBridge::CreateTextTimer),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextTimerBridge::SetFontColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextTimerBridge::ResetFontColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextTimerBridge::SetFontSize),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextTimerBridge::ResetFontSize),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextTimerBridge::SetFontWeight),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextTimerBridge::ResetFontWeight),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextTimerBridge::SetFontStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextTimerBridge::ResetFontStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextTimerBridge::SetFontFamily),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextTimerBridge::ResetFontFamily),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextTimerBridge::SetFormat),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextTimerBridge::ResetFormat),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextTimerBridge::SetTextShadow),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextTimerBridge::ResetTextShadow),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextTimerBridge::SetTextTimerOnTimer),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextTimerBridge::ResetTextTimerOnTimer),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextTimerBridge::SetTextTimerOptions),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextTimerBridge::SetContentModifierBuilder)
    };

    auto textTimer = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(functionNames), functionNames, funcValues);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "texttimer"), textTimer);
}
} // namespace OHOS::Ace::NG
