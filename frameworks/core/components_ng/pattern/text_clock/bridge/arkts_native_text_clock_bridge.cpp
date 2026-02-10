/*
 * Copyright (c) 2023-2025 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/text_clock/bridge/arkts_native_text_clock_bridge.h"

#include "base/utils/string_utils.h"
#include "base/utils/utils.h"
#include "core/components/progress/progress_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_model.h"
#include "core/components_ng/pattern/text_clock/text_clock_model_ng.h"
#include "frameworks/base/geometry/calc_dimension.h"
#include "frameworks/base/geometry/dimension.h"
#include "frameworks/bridge/declarative_frontend/ark_theme/theme_apply/js_theme_utils.h"
#include "frameworks/bridge/declarative_frontend/engine/js_types.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_text_clock.h"
#include "bridge/declarative_frontend/ark_theme/theme_apply/js_text_clock_theme.h"

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
constexpr int32_t HOURS_WEST_LOWER_LIMIT = -14;
constexpr int32_t HOURS_WEST_UPPER_LIMIT = 12;
constexpr float HOURS_WEST[] = { 9.5f, 3.5f, -3.5f, -4.5f, -5.5f, -5.75f, -6.5f, -9.5f, -10.5f, -12.75f };
const std::string DEFAULT_STR = "-1";
const char* TEXTCLOCK_NODEPTR_OF_UINODE = "nodePtr_";
const std::string TEXTCLOCK_DATE_TIME_OPTIONS_HOUR = "hour";
const std::string TEXTCLOCK_DATE_TIME_OPTIONS_TWO_DIGIT_VAL = "2-digit";
const std::string TEXTCLOCK_DATE_TIME_OPTIONS_NUMERIC_VAL = "numeric";
const std::string DEFAULT_FORMAT_API_TEN = "hms";
const std::vector<OHOS::Ace::FontStyle> FONT_STYLES = { OHOS::Ace::FontStyle::NORMAL, OHOS::Ace::FontStyle::ITALIC };

bool IsJsView(const Local<JSValueRef>& jsVal, panda::ecmascript::EcmaVM* vm)
{
    return jsVal->IsBoolean() && jsVal->ToBoolean(vm)->Value();
}

bool GetNativeNode(ArkUINodeHandle& nativeNode, const Local<JSValueRef>& jsVal, panda::ecmascript::EcmaVM* vm)
{
    if (jsVal->IsNativePointer(vm)) {
        nativeNode = nodePtr(jsVal->ToNativePointer(vm)->Value());
        return true;
    }
    if (IsJsView(jsVal, vm)) {
        nativeNode = reinterpret_cast<ArkUINodeHandle>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
        return true;
    }
    return false;
}

bool HoursWestIsValid(int32_t hoursWest)
{
    return !(hoursWest < HOURS_WEST_LOWER_LIMIT || hoursWest > HOURS_WEST_UPPER_LIMIT);
}

float GetHoursWest(float hoursWest)
{
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_ELEVEN)) {
        for (float i : HOURS_WEST) {
            if (NearEqual(hoursWest, i)) {
                return hoursWest;
            }
        }
    }

    return int32_t(hoursWest);
}

void RemoveJSController(
    FrameNode* frameNode, const RefPtr<TextClockController>& controller, Framework::JSTextClockController* jsController)
{
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(controller);
    CHECK_NULL_VOID(jsController);
    auto pointer = TextClockModelNG::GetJSTextClockController(frameNode);
    auto preController = static_cast<Framework::JSTextClockController*>(Referenced::RawPtr(pointer));
    if (preController) {
        preController->removeController(controller);
    }
    TextClockModelNG::SetJSTextClockController(frameNode, Referenced::Claim(static_cast<Referenced*>(jsController)));
}
} // namespace

ArkUINativeModuleValue TextClockBridge::SetFormat(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> formatArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    std::string format;
    RefPtr<ResourceObject> formatResObj;
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (IsJsView(nodeArg, vm)) {
        if (!formatArg->IsString(vm) && !formatArg->IsObject(vm)) {
            if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_ELEVEN)) {
                nodeModifiers->getTextClockModifier()->setFormat(nativeNode, "");
            } else {
                nodeModifiers->getTextClockModifier()->setFormat(nativeNode, DEFAULT_FORMAT_API_TEN.c_str());
            }
            nodeModifiers->getTextClockModifier()->removeResObjByKey(
                reinterpret_cast<ArkUINodeHandle>(ViewStackProcessor::GetInstance()->GetMainFrameNode()),
                "textClockFormat");
            return panda::JSValueRef::Undefined(vm);
        }
        static const std::string TEXT_CLOCK_FORMAT_REGEX =
             R"(^([Yy]*[_|\W\s]*[M]*[_|\W\s]*[d]*[_|\W\s]*[D]*[_|\W\s]*[Hh]*[_|\W\s]*[m]*[_|\W\s]*[s]*[_|\W\s]*[S]*)$)";
        ArkTSUtils::ParseJsString(vm, formatArg, format, formatResObj);
        if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_ELEVEN)) {
            std::regex pattern(TEXT_CLOCK_FORMAT_REGEX);
            if (format.empty() || !StringUtils::IsAscii(format) || !std::regex_match(format, pattern)) {
                nodeModifiers->getTextClockModifier()->setFormat(nativeNode, DEFAULT_FORMAT_API_TEN.c_str());
                return panda::JSValueRef::Undefined(vm);
            }
        }
        auto formatRawPtr = AceType::RawPtr(formatResObj);
        nodeModifiers->getTextClockModifier()->setFormatRes(nativeNode, format.c_str(), formatRawPtr);
        return panda::JSValueRef::Undefined(vm);
    }
    ArkTSUtils::ParseJsString(vm, formatArg, format, formatResObj);
    if (0 == format.length() || DEFAULT_STR == format) {
        nodeModifiers->getTextClockModifier()->resetFormat(nativeNode);
    } else if (!StringUtils::IsAscii(format) && Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        nodeModifiers->getTextClockModifier()->resetFormat(nativeNode);
    } else {
        auto formatRawPtr = AceType::RawPtr(formatResObj);
        nodeModifiers->getTextClockModifier()->setFormatRes(nativeNode, format.c_str(), formatRawPtr);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextClockBridge::ResetFormat(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getTextClockModifier()->resetFormat(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextClockBridge::SetFontColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> fontColorArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    Color color;
    RefPtr<ResourceObject> fontColorResObj;
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    auto colorParsed = ArkTSUtils::ParseJsColorAlpha(vm, fontColorArg, color, fontColorResObj, nodeInfo);
    auto fontColorRawPtr = AceType::RawPtr(fontColorResObj);
    auto isJsView = IsJsView(nodeArg, vm);
    if (isJsView && SystemProperties::ConfigChangePerform()) {
        nodeModifiers->getTextClockModifier()->createWithTextColorResourceObj(nativeNode, fontColorRawPtr);
    }
    if (!colorParsed) {
        if (!isJsView) {
            nodeModifiers->getTextClockModifier()->resetFontColor(nativeNode);
            return panda::JSValueRef::Undefined(vm);
        }
        if (!Framework::JSTextClockTheme::ObtainTextColor(color)) {
            auto pipelineContext = PipelineContext::GetCurrentContext();
            CHECK_NULL_RETURN(pipelineContext, panda::JSValueRef::Undefined(vm));
            auto theme = pipelineContext->GetTheme<TextTheme>();
            color = theme->GetTextStyle().GetTextColor();
            if (SystemProperties::ConfigChangePerform()) {
                nodeModifiers->getTextClockModifier()->setFontColor(nativeNode, color.GetValue());
                nodeModifiers->getTextClockModifier()->setTextColorByUser(nativeNode, false);
                return panda::JSValueRef::Undefined(vm);
            }
        }
        nodeModifiers->getTextClockModifier()->setFontColor(nativeNode, color.GetValue());
    } else {
        if (isJsView) {
            nodeModifiers->getTextClockModifier()->setFontColor(nativeNode, color.GetValue());
        } else {
            nodeModifiers->getTextClockModifier()->setFontColorRes(nativeNode, color.GetValue(), fontColorRawPtr);
        }
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextClockBridge::ResetFontColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getTextClockModifier()->resetFontColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextClockBridge::SetFontSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> fontSizeArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    CalcDimension fontSize;
    RefPtr<ResourceObject> fontSizeResObj;
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (!ArkTSUtils::ParseJsDimensionNG(vm, fontSizeArg, fontSize, DimensionUnit::FP, fontSizeResObj, false) ||
        fontSize.Value() < 0 || fontSize.Unit() == DimensionUnit::PERCENT) {
        if (IsJsView(nodeArg, vm)) {
            auto pipelineContext = PipelineContext::GetCurrentContext();
            CHECK_NULL_RETURN(pipelineContext, panda::JSValueRef::Undefined(vm));
            auto theme = pipelineContext->GetTheme<TextTheme>();
            CHECK_NULL_RETURN(theme, panda::JSValueRef::Undefined(vm));
            nodeModifiers->getTextClockModifier()->setFontSize(nativeNode, theme->GetTextStyle().GetFontSize().Value(),
                static_cast<int>(theme->GetTextStyle().GetFontSize().Unit()));
            return panda::JSValueRef::Undefined(vm);
        }
        nodeModifiers->getTextClockModifier()->resetFontSize(nativeNode);
    } else {
        auto fontSizeRawPtr = AceType::RawPtr(fontSizeResObj);
        nodeModifiers->getTextClockModifier()->setFontSizeRes(
            nativeNode, fontSize.Value(), static_cast<int>(fontSize.Unit()), fontSizeRawPtr);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextClockBridge::ResetFontSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getTextClockModifier()->resetFontSize(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextClockBridge::SetFontStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> fontStyleArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (IsJsView(nodeArg, vm)) {
        if (fontStyleArg->IsNumber()) {
            int32_t fontStyle = fontStyleArg->Int32Value(vm);
            if (fontStyle < 0 || fontStyle >= 2) {
                return panda::JSValueRef::Undefined(vm);
            }
            nodeModifiers->getTextClockModifier()->setFontStyle(nativeNode, static_cast<uint32_t>(FONT_STYLES[fontStyle]));
        } else {
            nodeModifiers->getTextClockModifier()->setFontStyle(nativeNode, static_cast<uint32_t>(FONT_STYLES[0]));
        }
        return panda::JSValueRef::Undefined(vm);
    }
    if (fontStyleArg->IsNumber()) {
        uint32_t fontStyle = fontStyleArg->Uint32Value(vm);
        if (fontStyle < static_cast<uint32_t>(OHOS::Ace::FontStyle::NORMAL) ||
            fontStyle > static_cast<uint32_t>(OHOS::Ace::FontStyle::ITALIC)) {
            fontStyle = static_cast<uint32_t>(OHOS::Ace::FontStyle::NORMAL);
        }
        nodeModifiers->getTextClockModifier()->setFontStyle(nativeNode, fontStyle);
    } else {
        nodeModifiers->getTextClockModifier()->resetFontStyle(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextClockBridge::ResetFontStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getTextClockModifier()->resetFontStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextClockBridge::SetFontWeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> fontWeightArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    std::string fontWeight;
    RefPtr<ResourceObject> fontWeightResObj;
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if ((fontWeightArg->IsUndefined() || fontWeightArg->IsNull()) && IsJsView(nodeArg, vm)) {
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_RETURN(pipelineContext, panda::JSValueRef::Undefined(vm));
        auto theme = pipelineContext->GetTheme<TextTheme>();
        CHECK_NULL_RETURN(theme, panda::JSValueRef::Undefined(vm));
        nodeModifiers->getTextClockModifier()->setFontWeight(
            nativeNode, StringUtils::FontWeightToString(theme->GetTextStyle().GetFontWeight()).c_str());
        return panda::JSValueRef::Undefined(vm);
    }
    if (!fontWeightArg->IsNull()) {
        if (fontWeightArg->IsNumber()) {
            fontWeight = std::to_string(fontWeightArg->Int32Value(vm));
        } else {
            ArkTSUtils::ParseJsString(vm, fontWeightArg, fontWeight, fontWeightResObj);
        }
    }
    auto fontWeightRawPtr = AceType::RawPtr(fontWeightResObj);
    nodeModifiers->getTextClockModifier()->setFontWeightRes(nativeNode, fontWeight.c_str(), fontWeightRawPtr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextClockBridge::ResetFontWeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getTextClockModifier()->resetFontWeight(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextClockBridge::SetFontFamily(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> fontFamilyArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));

    std::string fontFamilyStr;
    RefPtr<ResourceObject> fontFamilyResObj;
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (!ArkTSUtils::ParseJsFontFamiliesToString(vm, fontFamilyArg, fontFamilyStr, fontFamilyResObj)) {
        if (!IsJsView(nodeArg, vm)) {
            nodeModifiers->getTextClockModifier()->resetFontFamily(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    auto fontFamilyRawPtr = AceType::RawPtr(fontFamilyResObj);
    nodeModifiers->getTextClockModifier()->setFontFamilyRes(nativeNode, fontFamilyStr.c_str(), fontFamilyRawPtr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextClockBridge::ResetFontFamily(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());

    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getTextClockModifier()->resetFontFamily(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextClockBridge::SetFontFeature(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (secondArg->IsString(vm)) {
        auto value = secondArg->ToString(vm)->ToString(vm);
        nodeModifiers->getTextClockModifier()->setFontFeature(nativeNode, value.c_str());
    } else if (!IsJsView(firstArg, vm)) {
        nodeModifiers->getTextClockModifier()->resetFontFeature(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextClockBridge::ResetFontFeature(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getTextClockModifier()->resetFontFeature(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextClockBridge::SetTextShadow(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> lengthArg = runtimeCallInfo->GetCallArgRef(NUM_7);
    if (!lengthArg->IsNumber()) {
        return panda::JSValueRef::Undefined(vm);
    }
    if (lengthArg->Uint32Value(vm) == 0 && IsJsView(firstArg, vm)) {
        GetArkUINodeModifiers()->getTextClockModifier()->removeResObjByKey(
            reinterpret_cast<ArkUINodeHandle>(ViewStackProcessor::GetInstance()->GetMainFrameNode()),
            "textClock.shadow");
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
        radiusArray.get(), length, ArkTSUtils::parseShadowRadiusWithResObj, radiusResObjArray);
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
    if (!radiusParseResult || !colorParseResult || !offsetXParseResult || !offsetYParseResult || !fillParseResult ||
        !typeParseResult) {
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
    GetArkUINodeModifiers()->getTextClockModifier()->setTextShadowRes(
        nativeNode, textShadowArray.get(), textShadowResArray.get(), length);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextClockBridge::ResetTextShadow(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getTextClockModifier()->resetTextShadow(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextClockBridge::SetContentModifierBuilder(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    if (!secondArg->IsObject(vm)) {
        TextClockModelNG::SetBuilderFunc(frameNode, nullptr);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::CopyableGlobal<panda::ObjectRef> obj(vm, secondArg);
    TextClockModelNG::SetBuilderFunc(frameNode,
        [vm, frameNode, obj = std::move(obj), containerId = Container::CurrentId()](
            TextClockConfiguration config) -> RefPtr<FrameNode> {
            panda::LocalScope pandaScope(vm);
            ContainerScope scope(containerId);
            auto context = ArkTSUtils::GetContext(vm);
            CHECK_EQUAL_RETURN(context->IsUndefined(), true, nullptr);
            const char* keysOfTextClock[] = { "timeZoneOffset", "started", "enabled", "timeValue" };
            Local<JSValueRef> valuesOfTextClock[] = { panda::NumberRef::New(vm, config.timeZoneOffset_),
                panda::BooleanRef::New(vm, config.started_), panda::BooleanRef::New(vm, config.enabled_),
                panda::NumberRef::New(vm, config.timeValue_) };
            auto textClock = panda::ObjectRef::NewWithNamedProperties(
                vm, ArraySize(keysOfTextClock), keysOfTextClock, valuesOfTextClock);
            obj->SetNativePointerFieldCount(vm, 1);
            obj->SetNativePointerField(vm, 0, static_cast<void*>(frameNode));
            panda::Local<panda::JSValueRef> params[NUM_2] = { context, textClock };
            panda::TryCatch trycatch(vm);
            auto jsObject = obj.ToLocal();
            auto makeFunc = jsObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "makeContentModifierNode"));
            CHECK_EQUAL_RETURN(makeFunc->IsFunction(vm), false, nullptr);
            panda::Local<panda::FunctionRef> func = makeFunc;
            auto result = func->Call(vm, jsObject, params, NUM_2);
            panda::JSNApi::ExecutePendingJob(vm);
            CHECK_EQUAL_RETURN(result.IsEmpty() || trycatch.HasCaught() || !result->IsObject(vm), true, nullptr);
            auto resultObj = result->ToObject(vm);
            panda::Local<panda::JSValueRef> nodeptr =
                resultObj->Get(vm, panda::StringRef::NewFromUtf8(vm, TEXTCLOCK_NODEPTR_OF_UINODE));
            CHECK_EQUAL_RETURN(nodeptr.IsEmpty() || nodeptr->IsUndefined() || nodeptr->IsNull(), true, nullptr);
            auto* frameNode = reinterpret_cast<FrameNode*>(nodeptr->ToNativePointer(vm)->Value());
            CHECK_NULL_RETURN(frameNode, nullptr);
            return AceType::Claim(frameNode);
        });
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue TextClockBridge::SetDateTimeOptions(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> hourArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    ZeroPrefixType hourType = ZeroPrefixType::AUTO;
    std::string hour = TEXTCLOCK_DATE_TIME_OPTIONS_HOUR;
    if (hourArg->IsString(vm)) {
        std::string hour = hourArg->ToString(vm)->ToString(vm);
        if (hour == TEXTCLOCK_DATE_TIME_OPTIONS_TWO_DIGIT_VAL) {
            hourType = ZeroPrefixType::SHOW;
        } else if (hour == TEXTCLOCK_DATE_TIME_OPTIONS_NUMERIC_VAL) {
            hourType = ZeroPrefixType::HIDE;
        }
    }
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getTextClockModifier()->setDateTimeOptions(nativeNode, static_cast<ArkUI_Int32>(hourType));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextClockBridge::ResetDateTimeOptions(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getTextClockModifier()->resetDateTimeOptions(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextClockBridge::SetTextClockTimeZoneOffset(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeVal = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> hourWestVal = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(nodeVal->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeVal->ToNativePointer(vm)->Value());
    auto themeColors = Framework::JSThemeUtils::GetThemeColors();
    float hourWest = NAN;
    if (hourWestVal->IsNumber() && HoursWestIsValid(hourWestVal->Int32Value(vm))) {
        hourWest = GetHoursWest(hourWestVal->ToNumber(vm)->Value());
    }
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (themeColors.has_value()) {
        nodeModifiers->getTextClockModifier()->setFontColor(nativeNode, themeColors->FontSecondary().GetValue());
    }
    nodeModifiers->getTextClockModifier()->setTextClockTimeZoneOffset(nativeNode, hourWest);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextClockBridge::SetTextClockController(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeVal = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> controllerVal = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(nodeVal->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeVal->ToNativePointer(vm)->Value());
    auto themeColors = Framework::JSThemeUtils::GetThemeColors();
    if (themeColors.has_value()) {
        auto nodeModifiers = GetArkUINodeModifiers();
        CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
        nodeModifiers->getTextClockModifier()->setFontColor(nativeNode, themeColors->FontSecondary().GetValue());
    }

    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    auto controller = TextClockModelNG::InitTextController(frameNode);
    if (!controllerVal->IsUndefined() && !controllerVal->IsNull() && controllerVal->IsObject(vm)) {
        Local<ObjectRef> obj = controllerVal->ToObject(vm);
        auto* jsController =
            static_cast<Framework::JSTextClockController*>(obj->GetNativePointerField(vm, 0));
        if (jsController) {
            jsController->SetInstanceId(Container::CurrentId());
            if (controller) {
                RemoveJSController(frameNode, controller, jsController);
                jsController->AddController(controller);
            }
        }
    } else if (controller) {
        auto pointer = TextClockModelNG::GetJSTextClockController(frameNode);
        auto preController = static_cast<Framework::JSTextClockController*>(Referenced::RawPtr(pointer));
        if (preController) {
            preController->removeController(controller);
        }
        TextClockModelNG::SetJSTextClockController(frameNode, nullptr);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextClockBridge::SetTextClockOnDateChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        if (!IsJsView(firstArg, vm)) {
            GetArkUINodeModifiers()->getTextClockModifier()->resetTextClockOnDateChange(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    if (!IsJsView(firstArg, vm)) {
        CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    }
    std::function<void(const std::string&)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)](
                                                           const std::string& value) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));

        panda::Local<panda::JSValueRef> params[1] = { panda::StringRef::NewFromUtf8(vm, value.c_str()) };
        func->Call(vm, func.ToLocal(), params, 1);
    };
    GetArkUINodeModifiers()->getTextClockModifier()->setTextClockOnDateChange(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextClockBridge::ResetTextClockOnDateChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextClockModifier()->resetTextClockOnDateChange(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

void TextClockBridge::RegisterTextClockAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    const char* functionNames[] = {
        "create",
        "setFormat",
        "resetFormat",
        "setFontColor",
        "resetFontColor",
        "setFontSize",
        "resetFontSize",
        "setFontStyle",
        "resetFontStyle",
        "setFontWeight",
        "resetFontWeight",
        "setFontFamily",
        "resetFontFamily",
        "setTextShadow",
        "resetTextShadow",
        "setFontFeature",
        "resetFontFeature",
        "setContentModifierBuilder",
        "setDateTimeOptions",
        "resetDateTimeOptions",
        "setTextClockTimeZoneOffset",
        "setTextClockController",
        "setTextClockOnDateChange",
        "resetTextClockOnDateChange",
    };
    Local<JSValueRef> funcValues[] = {
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextClockBridge::CreateTextClock),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextClockBridge::SetFormat),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextClockBridge::ResetFormat),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextClockBridge::SetFontColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextClockBridge::ResetFontColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextClockBridge::SetFontSize),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextClockBridge::ResetFontSize),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextClockBridge::SetFontStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextClockBridge::ResetFontStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextClockBridge::SetFontWeight),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextClockBridge::ResetFontWeight),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextClockBridge::SetFontFamily),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextClockBridge::ResetFontFamily),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextClockBridge::SetTextShadow),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextClockBridge::ResetTextShadow),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextClockBridge::SetFontFeature),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextClockBridge::ResetFontFeature),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextClockBridge::SetContentModifierBuilder),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextClockBridge::SetDateTimeOptions),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextClockBridge::ResetDateTimeOptions),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextClockBridge::SetTextClockTimeZoneOffset),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextClockBridge::SetTextClockController),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextClockBridge::SetTextClockOnDateChange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextClockBridge::ResetTextClockOnDateChange),
    };

    auto textClock = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(functionNames), functionNames, funcValues);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "textclock"), textClock);
}

ArkUINativeModuleValue TextClockBridge::CreateTextClock(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));

    auto controller = AceType::Claim(reinterpret_cast<OHOS::Ace::TextClockController*>(
        GetArkUINodeModifiers()->getTextClockModifier()->createTextClockController()));
    auto* frameNode = reinterpret_cast<FrameNode*>(ViewStackProcessor::GetInstance()->GetMainFrameNode());

    if (runtimeCallInfo->GetArgsNumber() < 1 || !runtimeCallInfo->GetCallArgRef(0)->IsObject(vm)) {
        GetArkUINodeModifiers()->getTextClockModifier()->initFontDefault(reinterpret_cast<ArkUINodeHandle>(frameNode));
        if (auto themeColors = Framework::JSThemeUtils::GetThemeColors(); themeColors.has_value()) {
            GetArkUINodeModifiers()->getTextClockModifier()->setFontColor(
                reinterpret_cast<ArkUINodeHandle>(frameNode), themeColors->FontSecondary().GetValue());
        }
        return panda::JSValueRef::Undefined(vm);
    }
    if (auto themeColors = Framework::JSThemeUtils::GetThemeColors(); themeColors.has_value()) {
        GetArkUINodeModifiers()->getTextClockModifier()->setFontColor(
            reinterpret_cast<ArkUINodeHandle>(frameNode), themeColors->FontSecondary().GetValue());
    }

    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto paramsObj = firstArg->ToObject(vm);
    auto timeZoneOffsetKey = panda::StringRef::NewFromUtf8(vm, "timeZoneOffset");
    Local<JSValueRef> timeZoneOffsetVal = paramsObj->Get(vm, timeZoneOffsetKey);
    if (timeZoneOffsetVal->IsNumber() && HoursWestIsValid(timeZoneOffsetVal->ToNumber(vm)->Value()) && frameNode) {
        float hoursWest = GetHoursWest(static_cast<float>(timeZoneOffsetVal->ToNumber(vm)->Value()));
        GetArkUINodeModifiers()->getTextClockModifier()->setTextClockTimeZoneOffset(
            reinterpret_cast<ArkUINodeHandle>(frameNode), hoursWest);
    } else {
        GetArkUINodeModifiers()->getTextClockModifier()->setTextClockTimeZoneOffset(
            reinterpret_cast<ArkUINodeHandle>(frameNode), NAN);
    }

    auto controllerKey = panda::StringRef::NewFromUtf8(vm, "controller");
    Local<JSValueRef> controllerVal = paramsObj->Get(vm, controllerKey);
    if (!controllerVal->IsUndefined() && !controllerVal->IsNull() && controllerVal->IsObject(vm)) {
        Local<ObjectRef> obj = controllerVal->ToObject(vm);
        auto* jsController = static_cast<Framework::JSTextClockController*>(obj->GetNativePointerField(vm, 0));
        if (jsController) {
            jsController->SetInstanceId(Container::CurrentId());
            if (controller) {
                jsController->AddController(controller);
            }
        }
    }
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
