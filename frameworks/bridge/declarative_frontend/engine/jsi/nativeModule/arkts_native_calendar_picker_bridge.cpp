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

#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_calendar_picker_bridge.h"
#include "core/components/calendar/calendar_theme.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_common_bridge.h"
namespace OHOS::Ace::NG {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr Dimension DEFAULT_TEXTSTYLE_FONTSIZE = 16.0_fp;
constexpr int PARAM_ARR_LENGTH_1 = 1;
const std::string FORMAT_FONT = "%s|%s";

void ParseCalendarPickerPadding(
    const EcmaVM* vm, const Local<JSValueRef>& value, CalcDimension& dim, ArkUISizeType& result)
{
    if (ArkTSUtils::ParseJsDimensionVpNG(vm, value, dim)) {
        if (LessOrEqual(dim.Value(), 0.0)) {
            dim.SetValue(-1);
            dim.SetUnit(DimensionUnit::VP);
        }
        result.unit = static_cast<int8_t>(dim.Unit());
        if (dim.CalcValue() != "") {
            result.string = dim.CalcValue().c_str();
        } else {
            result.value = dim.Value();
        }
    } else {
        dim.SetValue(-1);
        dim.SetUnit(DimensionUnit::VP);
        result.unit = static_cast<int8_t>(dim.Unit());
        result.value = dim.Value();
    }
}

double GetMSByDate(const std::string& date)
{
    auto json = JsonUtil::ParseJsonString(date);
    if (!json || json->IsNull()) {
        return 0.0f;
    }

    std::tm dateTime {};
    auto year = json->GetValue("year");
    if (year && year->IsNumber()) {
        dateTime.tm_year = year->GetInt() - 1900; // local date start from 1900
    }
    auto month = json->GetValue("month");
    if (month && month->IsNumber()) {
        dateTime.tm_mon = month->GetInt() - 1;
    }
    auto day = json->GetValue("day");
    if (day && day->IsNumber()) {
        dateTime.tm_mday = day->GetInt();
    }
    auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    auto local = std::localtime(&now);
    CHECK_NULL_RETURN(local, 0.0f);
    dateTime.tm_hour = local->tm_hour;
    dateTime.tm_min = local->tm_min;
    dateTime.tm_sec = local->tm_sec;
    return Date::GetMilliSecondsByDateTime(dateTime);
}

ArkUINativeModuleValue CalendarPickerBridge::SetTextStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, panda::NativePointerRef::New(vm, nullptr));
    RefPtr<CalendarTheme> calendarTheme = pipeline->GetTheme<CalendarTheme>();
    CHECK_NULL_RETURN(calendarTheme, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> fontSizeArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> fontWeightArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Color textColor = calendarTheme->GetEntryFontColor();
    RefPtr<ResourceObject> textColorResObj;
    ArkUIPickerTextStyleStruct textStyleStruct;
    textStyleStruct.textColorSetByUser = false;
    if (!colorArg->IsUndefined()) {
        auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
        if (ArkTSUtils::ParseJsColorAlpha(vm, colorArg, textColor, textColorResObj, nodeInfo)) {
            textStyleStruct.textColorSetByUser = true;
        }
    }
    CalcDimension fontSizeData(DEFAULT_TEXTSTYLE_FONTSIZE);
    std::string fontSize = fontSizeData.ToString();
    RefPtr<ResourceObject> fontSizeResObj;
    if (ArkTSUtils::ParseJsDimensionFp(vm, fontSizeArg, fontSizeData, fontSizeResObj) &&
        !fontSizeData.IsNegative() && fontSizeData.Unit() != DimensionUnit::PERCENT) {
        fontSize = fontSizeData.ToString();
    }
    std::string fontWeight = "regular";
    if (fontWeightArg->IsString(vm) || fontWeightArg->IsNumber()) {
        fontWeight = fontWeightArg->ToString(vm)->ToString(vm);
    }

    std::string fontInfo = StringUtils::FormatString(FORMAT_FONT.c_str(), fontSize.c_str(), fontWeight.c_str());
    textStyleStruct.fontInfo = fontInfo.c_str();
    textStyleStruct.textColor = textColor.GetValue();
    textStyleStruct.fontSizeRawPtr = AceType::RawPtr(fontSizeResObj);
    textStyleStruct.textColorRawPtr = AceType::RawPtr(textColorResObj);
    GetArkUINodeModifiers()->getCalendarPickerModifier()->setTextStyleWithResObj(nativeNode, &textStyleStruct);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CalendarPickerBridge::ResetTextStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCalendarPickerModifier()->resetTextStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CalendarPickerBridge::SetEdgeAlign(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> alignTypeArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> dxArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> dyArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    int alignType = NUM_2;
    if (!alignTypeArg->IsNull() && !alignTypeArg->IsUndefined() && alignTypeArg->IsNumber()) {
        alignType = alignTypeArg->ToNumber(vm)->Value();
    }
    CalcDimension dx;
    CalcDimension dy;
    RefPtr<ResourceObject> dxResObj;
    RefPtr<ResourceObject> dyResObj;
    if (!dxArg->IsNull() && !dxArg->IsUndefined()) {
        ArkTSUtils::ParseJsDimensionVp(vm, dxArg, dx, dxResObj);
    }
    if (!dyArg->IsNull() && !dyArg->IsUndefined()) {
        ArkTSUtils::ParseJsDimensionVp(vm, dyArg, dy, dyResObj);
    }

    ArkUIPickerEdgeAlignStruct edgeAlignStruct;
    edgeAlignStruct.dxValue = dx.Value();
    edgeAlignStruct.dxUnit = static_cast<int>(dx.Unit());
    edgeAlignStruct.dyValue = dy.Value();
    edgeAlignStruct.dyUnit = static_cast<int>(dy.Unit());
    edgeAlignStruct.dxRawPtr = AceType::RawPtr(dxResObj);
    edgeAlignStruct.dyRawPtr = AceType::RawPtr(dyResObj);
    edgeAlignStruct.alignType = alignType;
    GetArkUINodeModifiers()->getCalendarPickerModifier()->setEdgeAlignWithResObj(nativeNode, &edgeAlignStruct);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CalendarPickerBridge::ResetEdgeAlign(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCalendarPickerModifier()->resetEdgeAlign(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CalendarPickerBridge::SetCalendarPickerPadding(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> topArg = runtimeCallInfo->GetCallArgRef(1);    // 1: index of parameter top
    Local<JSValueRef> rightArg = runtimeCallInfo->GetCallArgRef(2);  // 2: index of parameter right
    Local<JSValueRef> bottomArg = runtimeCallInfo->GetCallArgRef(3); // 3: index of parameter bottom
    Local<JSValueRef> leftArg = runtimeCallInfo->GetCallArgRef(4);   // 4: index of parameter left
    if (leftArg->IsUndefined() && rightArg->IsUndefined() && topArg->IsUndefined() && bottomArg->IsUndefined()) {
        GetArkUINodeModifiers()->getCalendarPickerModifier()->resetCalendarPickerPadding(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    struct ArkUISizeType top = { 0.0, static_cast<int8_t>(DimensionUnit::VP), nullptr };
    struct ArkUISizeType right = { 0.0, static_cast<int8_t>(DimensionUnit::VP), nullptr };
    struct ArkUISizeType bottom = { 0.0, static_cast<int8_t>(DimensionUnit::VP), nullptr };
    struct ArkUISizeType left = { 0.0, static_cast<int8_t>(DimensionUnit::VP), nullptr };

    CalcDimension topDim(0, DimensionUnit::VP);
    CalcDimension rightDim(0, DimensionUnit::VP);
    CalcDimension bottomDim(0, DimensionUnit::VP);
    CalcDimension leftDim(0, DimensionUnit::VP);
    ParseCalendarPickerPadding(vm, topArg, topDim, top);
    ParseCalendarPickerPadding(vm, rightArg, rightDim, right);
    ParseCalendarPickerPadding(vm, bottomArg, bottomDim, bottom);
    ParseCalendarPickerPadding(vm, leftArg, leftDim, left);
    GetArkUINodeModifiers()->getCalendarPickerModifier()->setCalendarPickerPadding(
        nativeNode, &top, &right, &bottom, &left);

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CalendarPickerBridge::ResetCalendarPickerPadding(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCalendarPickerModifier()->resetCalendarPickerPadding(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CalendarPickerBridge::SetCalendarPickerBorder(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    Local<JSValueRef> leftArg = runtimeCallInfo->GetCallArgRef(5);   // 5: index of parameter left color
    Local<JSValueRef> rightArg = runtimeCallInfo->GetCallArgRef(6);  // 6: index of parameter right color
    Local<JSValueRef> topArg = runtimeCallInfo->GetCallArgRef(7);    // 7: index of parameter top color
    Local<JSValueRef> bottomArg = runtimeCallInfo->GetCallArgRef(8); // 8: index of parameter bottom color

    CommonBridge::SetBorder(runtimeCallInfo);

    CalcDimension borderWidth;
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    if (!ArkTSUtils::ParseJsDimensionVpNG(vm, secondArg, borderWidth) || !borderWidth.IsValid()) {
        GetArkUINodeModifiers()->getCalendarPickerModifier()->resetCalendarPickerBorderWidth(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    if (leftArg->IsUndefined() && rightArg->IsUndefined() && topArg->IsUndefined() && bottomArg->IsUndefined()) {
        auto pipeline = PipelineBase::GetCurrentContext();
        CHECK_NULL_RETURN(pipeline, panda::NativePointerRef::New(vm, nullptr));
        RefPtr<CalendarTheme> calendarTheme = pipeline->GetTheme<CalendarTheme>();
        CHECK_NULL_RETURN(calendarTheme, panda::NativePointerRef::New(vm, nullptr));
        GetArkUINodeModifiers()->getCalendarPickerModifier()->setCalendarPickerBorder(
            nativeNode, calendarTheme->GetEntryBorderColor().GetValue());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CalendarPickerBridge::ResetCalendarPickerBorder(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCalendarPickerModifier()->resetCalendarPickerBorder(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CalendarPickerBridge::SetCalendarPickerHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> jsValue = runtimeCallInfo->GetCallArgRef(NUM_1);
    CalcDimension height;
    std::string calcStr;
    if (!ArkTSUtils::ParseJsDimensionVpNG(vm, jsValue, height)) {
        GetArkUINodeModifiers()->getCalendarPickerModifier()->resetCalendarPickerHeight(nativeNode);
        if (jsValue->IsObject(vm)) {
            auto obj = jsValue->ToObject(vm);
            auto layoutPolicy = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "id_"));
            if (layoutPolicy->IsString(vm)) {
                auto policy = ParseLayoutPolicy(layoutPolicy->ToString(vm)->ToString(vm));
                ViewAbstractModel::GetInstance()->UpdateLayoutPolicyProperty(policy, false);
                return panda::JSValueRef::Undefined(vm);
            }
        }
    } else {
        if (LessNotEqual(height.Value(), 0.0)) {
            if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
                GetArkUINodeModifiers()->getCalendarPickerModifier()->resetCalendarPickerHeight(nativeNode);
                ViewAbstractModel::GetInstance()->UpdateLayoutPolicyProperty(LayoutCalPolicy::NO_MATCH, false);
                return panda::JSValueRef::Undefined(vm);
            }
            height.SetValue(0.0);
        }
        if (height.Unit() == DimensionUnit::CALC) {
            GetArkUINodeModifiers()->getCalendarPickerModifier()->setCalendarPickerHeight(
                nativeNode, height.Value(), static_cast<int32_t>(height.Unit()));
        } else {
            GetArkUINodeModifiers()->getCalendarPickerModifier()->setCalendarPickerHeight(
                nativeNode, height.Value(), static_cast<int32_t>(height.Unit()));
        }
    }
    ViewAbstractModel::GetInstance()->UpdateLayoutPolicyProperty(LayoutCalPolicy::NO_MATCH, false);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CalendarPickerBridge::ResetCalendarPickerHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCalendarPickerModifier()->resetCalendarPickerHeight(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CalendarPickerBridge::SetCalendarPickerBorderColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Color color;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color)) {
        GetArkUINodeModifiers()->getCalendarPickerModifier()->resetCalendarPickerBorderColor(nativeNode);
    } else {
        GetArkUINodeModifiers()->getCalendarPickerModifier()->setCalendarPickerBorderColor(
            nativeNode, color.GetValue());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CalendarPickerBridge::ResetCalendarPickerBorderColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCalendarPickerModifier()->resetCalendarPickerBorderColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CalendarPickerBridge::SetCalendarPickerBorderRadius(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    CalcDimension borderRadius;
    if (!ArkTSUtils::ParseJsDimensionVpNG(vm, secondArg, borderRadius, true)) {
        GetArkUINodeModifiers()->getCalendarPickerModifier()->resetCalendarPickerBorderRadius(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    if (LessNotEqual(borderRadius.Value(), 0.0)) {
        GetArkUINodeModifiers()->getCalendarPickerModifier()->resetCalendarPickerBorderRadius(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    GetArkUINodeModifiers()->getCalendarPickerModifier()->setCalendarPickerBorderRadius(nativeNode,
        borderRadius.Value(), static_cast<int>(borderRadius.Unit()));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CalendarPickerBridge::ResetCalendarPickerBorderRadius(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCalendarPickerModifier()->resetCalendarPickerBorderRadius(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CalendarPickerBridge::SetCalendarPickerMarkToday(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> markTodayArg = runtimeCallInfo->GetCallArgRef(1); // markToday value
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (!markTodayArg->IsUndefined() && !markTodayArg.IsNull() && markTodayArg->IsBoolean()) {
        bool isMarkToday = markTodayArg->ToBoolean(vm)->Value();
        nodeModifiers->getCalendarPickerModifier()->setCalendarPickerMarkToday(nativeNode, isMarkToday);
    } else {
        nodeModifiers->getCalendarPickerModifier()->resetCalendarPickerMarkToday(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CalendarPickerBridge::ResetCalendarPickerMarkToday(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getCalendarPickerModifier()->resetCalendarPickerMarkToday(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue CalendarPickerBridge::SetCalendarPickerOnChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    uint32_t argsNumber = runtimeCallInfo->GetArgsNumber();
    if (argsNumber != NUM_2) {
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getCalendarPickerModifier()->resetCalendarPickerOnChange(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(const std::string&)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)](
                                                           const std::string& dateStr) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        panda::Local<panda::DateRef> dateObj = panda::DateRef::New(vm, GetMSByDate(dateStr));
        panda::Local<panda::JSValueRef> params[] = { dateObj };
        func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_1);
    };
    GetArkUINodeModifiers()->getCalendarPickerModifier()->setCalendarPickerOnChange(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue CalendarPickerBridge::ResetCalendarPickerOnChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCalendarPickerModifier()->resetCalendarPickerOnChange(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
