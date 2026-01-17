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

#include "core/components_ng/pattern/calendar_picker/bridge/arkts_native_calendar_picker_bridge.h"

#include "calendar_picker_utils.h"

#include "base/log/ace_scoring_log.h"
#include "bridge/declarative_frontend/engine/jsi/js_ui_index.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_common_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "core/common/resource/resource_parse_utils.h"
#include "core/components/calendar/calendar_theme.h"
#include "core/components_ng/pattern/calendar_picker/calendar_picker_model_ng.h"
#include "core/components_ng/pattern/calendar_picker/calendar_type_define.h"
#include "core/components_ng/pattern/picker/picker_data.h"
namespace OHOS::Ace::NG {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int NUM_4 = 4;
constexpr Dimension DEFAULT_TEXTSTYLE_FONTSIZE = 16.0_fp;
constexpr int PARAM_ARR_LENGTH_1 = 1;
const std::string FORMAT_FONT = "%s|%s";
namespace {
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

bool IsJsView(const Local<JSValueRef>& firstArg, panda::ecmascript::EcmaVM* vm)
{
    return firstArg->IsBoolean() && firstArg->ToBoolean(vm)->Value();
}

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


} // namespace
ArkUINativeModuleValue ParseTextStyle(
    EcmaVM* vm, const panda::Local<panda::ObjectRef>& paramObj, NG::PickerTextStyle& textStyle)
{
    auto fontColor = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "color"));
    auto fontStyle = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "font"));

    Color color;
    if (ArkTSUtils::ParseJsColor(vm, fontColor, color, textStyle.textColorResObj)) {
        textStyle.textColor = color;
        textStyle.textColorSetByUser = true;
    }

    if (!fontStyle->IsObject(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::ObjectRef> fontObj = fontStyle->ToObject(vm);
    auto fontSize = fontObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "size"));
    auto fontWeight = fontObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "weight"));
    if (fontSize->IsNull() || fontSize->IsUndefined()) {
        textStyle.fontSize = Dimension(-1);
    } else {
        CalcDimension size;
        if (!ArkTSUtils::ParseJsDimensionFpNG(vm, fontSize, size, textStyle.fontSizeResObj) ||
            size.Unit() == DimensionUnit::PERCENT) {
            textStyle.fontSize = Dimension(-1);
        } else {
            textStyle.fontSize = size;
        }
    }

    if (!fontWeight->IsNull() && !fontWeight->IsUndefined()) {
        std::string weight;
        if (fontWeight->IsNumber()) {
            weight = std::to_string(fontWeight->ToNumber(vm)->Int32Value(vm));
        } else {
            ArkTSUtils::ParseJsString(vm, fontWeight, weight);
        }
        textStyle.fontWeight = Framework::ConvertStrToFontWeight(weight);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SetJSTextStyle(EcmaVM* vm, const panda::Local<panda::JSValueRef>& jsValue)
{
    ArkUINodeHandle nativeNode =
        reinterpret_cast<ArkUINodeHandle>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, panda::NativePointerRef::New(vm, nullptr));
    RefPtr<CalendarTheme> calendarTheme = pipeline->GetTheme<CalendarTheme>();
    CHECK_NULL_RETURN(calendarTheme, panda::NativePointerRef::New(vm, nullptr));

    NG::PickerTextStyle textStyle;
    textStyle.fontSize = calendarTheme->GetEntryFontSize();
    textStyle.textColor = calendarTheme->GetEntryFontColor();
    textStyle.fontWeight = FontWeight::NORMAL;

    if (jsValue->IsObject(vm)) {
        panda::Local<panda::ObjectRef> paramObj = jsValue->ToObject(vm);
        ParseTextStyle(vm, paramObj, textStyle);
    }
    GetArkUINodeModifiers()->getCalendarPickerModifier()->setJSTextStyle(nativeNode, &textStyle);
    return panda::JSValueRef::Undefined(vm);
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
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (IsJsView(firstArg, vm)) {
        SetJSTextStyle(vm, runtimeCallInfo->GetCallArgRef(NUM_1));
        return panda::JSValueRef::Undefined(vm);
    }
    Color textColor = calendarTheme->GetEntryFontColor();
    RefPtr<ResourceObject> textColorResObj;
    ArkUIPickerTextStyleStruct textStyleStruct;
    textStyleStruct.textColorSetByUser = false;
    if (!colorArg->IsUndefined()) {
        auto frameNode = nativeNode
                             ? nativeNode
                             : reinterpret_cast<ArkUINodeHandle>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
        auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(frameNode);
        if (ArkTSUtils::ParseJsColorAlpha(vm, colorArg, textColor, textColorResObj, nodeInfo)) {
            textStyleStruct.textColorSetByUser = true;
        }
    }

    CalcDimension fontSizeData(DEFAULT_TEXTSTYLE_FONTSIZE);
    std::string fontSize = fontSizeData.ToString();
    RefPtr<ResourceObject> fontSizeResObj;
    if (ArkTSUtils::ParseJsDimensionFp(vm, fontSizeArg, fontSizeData, fontSizeResObj) && !fontSizeData.IsNegative() &&
        fontSizeData.Unit() != DimensionUnit::PERCENT) {
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
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (IsJsView(firstArg, vm)) {
        nativeNode = nodePtr(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    }
    GetArkUINodeModifiers()->getCalendarPickerModifier()->resetTextStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SetJsEdgeAlign(EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    ArkUINodeHandle nativeNode = nodePtr(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    NG::CalendarEdgeAlign alignType = NG::CalendarEdgeAlign::EDGE_ALIGN_END;
    DimensionOffset offset;

    Local<JSValueRef> alignTypeValue = runtimeCallInfo->GetCallArgRef(NUM_1);
    if (alignTypeValue->IsNumber()) {
        alignType = static_cast<NG::CalendarEdgeAlign>(alignTypeValue->ToNumber(vm)->Int32Value(vm));
    }

    Local<JSValueRef> offsetValue = runtimeCallInfo->GetCallArgRef(NUM_2);
    if (!offsetValue->IsObject(vm)) {
        GetArkUINodeModifiers()->getCalendarPickerModifier()->setJsEdgeAlign(
            nativeNode, &offset, static_cast<int32_t>(alignType));
        return panda::JSValueRef::Undefined(vm);
    }

    panda::Local<panda::ObjectRef> offsetObj = offsetValue->ToObject(vm);
    Local<JSValueRef> dxValue = offsetObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "dx"));
    Local<JSValueRef> dyValue = offsetObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "dy"));

    CalcDimension dx;
    CalcDimension dy;

    if (SystemProperties::ConfigChangePerform()) {
        RefPtr<ResourceObject> dxResObj;
        RefPtr<ResourceObject> dyResObj;
        ArkTSUtils::ParseJsDimensionVpNG(vm, dxValue, dx, dxResObj);
        ArkTSUtils::ParseJsDimensionVpNG(vm, dyValue, dy, dyResObj);
        offset = DimensionOffset(dx, dy);

        if (dxResObj || dyResObj) {
            std::vector<RefPtr<ResourceObject>> resArray = { dxResObj, dyResObj };
            GetArkUINodeModifiers()->getCalendarPickerModifier()->parseJSEdgeAlignResObjArray(nativeNode, &resArray);
        } else {
            GetArkUINodeModifiers()->getCalendarPickerModifier()->jsCalendarPickerRemoveResObj(
                nativeNode, "CalendarPicker.EdgeAlign");
        }
    } else {
        ArkTSUtils::ParseJsDimensionVpNG(vm, dxValue, dx);
        ArkTSUtils::ParseJsDimensionVpNG(vm, dyValue, dy);
        offset = DimensionOffset(dx, dy);
    }

    GetArkUINodeModifiers()->getCalendarPickerModifier()->setJsEdgeAlign(
        nativeNode, &offset, static_cast<int32_t>(alignType));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CalendarPickerBridge::SetEdgeAlign(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (IsJsView(firstArg, vm)) {
        SetJsEdgeAlign(vm, runtimeCallInfo);
        return panda::JSValueRef::Undefined(vm);
    }

    Local<JSValueRef> alignTypeArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> dxArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> dyArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    int alignType = NUM_2;
    if (!alignTypeArg->IsNull() && !alignTypeArg->IsUndefined() && alignTypeArg->IsNumber()) {
        alignType = alignTypeArg->ToNumber(vm)->Int32Value(vm);
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
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (IsJsView(firstArg, vm)) {
        nativeNode = nodePtr(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    }
    GetArkUINodeModifiers()->getCalendarPickerModifier()->resetEdgeAlign(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

NG::PaddingProperty SetPaddings(const std::optional<CalcDimension>& top, const std::optional<CalcDimension>& bottom,
    const std::optional<CalcDimension>& left, const std::optional<CalcDimension>& right)
{
    NG::PaddingProperty paddings;
    if (top.has_value()) {
        if (top.value().Unit() == DimensionUnit::CALC) {
            paddings.top =
                NG::CalcLength(top.value().IsNonNegative() ? top.value().CalcValue() : CalcDimension().CalcValue());
        } else {
            paddings.top = NG::CalcLength(top.value().IsNonNegative() ? top.value() : CalcDimension());
        }
    }
    if (bottom.has_value()) {
        if (bottom.value().Unit() == DimensionUnit::CALC) {
            paddings.bottom = NG::CalcLength(
                bottom.value().IsNonNegative() ? bottom.value().CalcValue() : CalcDimension().CalcValue());
        } else {
            paddings.bottom = NG::CalcLength(bottom.value().IsNonNegative() ? bottom.value() : CalcDimension());
        }
    }
    if (left.has_value()) {
        if (left.value().Unit() == DimensionUnit::CALC) {
            paddings.left =
                NG::CalcLength(left.value().IsNonNegative() ? left.value().CalcValue() : CalcDimension().CalcValue());
        } else {
            paddings.left = NG::CalcLength(left.value().IsNonNegative() ? left.value() : CalcDimension());
        }
    }
    if (right.has_value()) {
        if (right.value().Unit() == DimensionUnit::CALC) {
            paddings.right =
                NG::CalcLength(right.value().IsNonNegative() ? right.value().CalcValue() : CalcDimension().CalcValue());
        } else {
            paddings.right = NG::CalcLength(right.value().IsNonNegative() ? right.value() : CalcDimension());
        }
    }

    return paddings;
}

ArkUINativeModuleValue SetCalendarPickerJSPadding(EcmaVM* vm, const panda::Local<panda::JSValueRef>& jsValue)
{
    auto nativeNode = nodePtr(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    NG::PaddingProperty padding;
    if (jsValue->IsObject(vm)) {
        CommonCalcDimension commonCalcDimension;
        panda::Local<panda::ObjectRef> paddingObj = jsValue->ToObject(vm);
        ArkTSUtils::ParseCommonMarginOrPaddingCorner(vm, paddingObj, commonCalcDimension);
        if (commonCalcDimension.left.has_value() || commonCalcDimension.right.has_value() ||
            commonCalcDimension.top.has_value() || commonCalcDimension.bottom.has_value()) {
            padding = SetPaddings(commonCalcDimension.top, commonCalcDimension.bottom, commonCalcDimension.left,
                commonCalcDimension.right);
            GetArkUINodeModifiers()->getCalendarPickerModifier()->setJSPaddingProperty(nativeNode, &padding);
            return panda::JSValueRef::Undefined(vm);
        }
    }

    CalcDimension length(-1);
    if (ArkTSUtils::ParseJsDimensionVpNG(vm, jsValue, length) && length.IsNonNegative()) {
        padding.SetEdges(NG::CalcLength(length));
        GetArkUINodeModifiers()->getCalendarPickerModifier()->setJSPaddingProperty(nativeNode, &padding);
    } else {
        GetArkUINodeModifiers()->getCalendarPickerModifier()->resetCalendarPickerPadding(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CalendarPickerBridge::SetCalendarPickerPadding(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (IsJsView(firstArg, vm)) {
        SetCalendarPickerJSPadding(vm, runtimeCallInfo->GetCallArgRef(NUM_1));
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> topArg = runtimeCallInfo->GetCallArgRef(NUM_1);    // 1: index of parameter top
    Local<JSValueRef> rightArg = runtimeCallInfo->GetCallArgRef(NUM_2);  // 2: index of parameter right
    Local<JSValueRef> bottomArg = runtimeCallInfo->GetCallArgRef(NUM_3); // 3: index of parameter bottom
    Local<JSValueRef> leftArg = runtimeCallInfo->GetCallArgRef(NUM_4);   // 4: index of parameter left
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
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (IsJsView(firstArg, vm)) {
        nativeNode = nodePtr(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    }
    GetArkUINodeModifiers()->getCalendarPickerModifier()->resetCalendarPickerPadding(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

void ParseBorderColor(ArkUINodeHandle handle, EcmaVM* vm, const Local<JSValueRef>& args)
{
    GetArkUINodeModifiers()->getCalendarPickerModifier()->jSResetResObj(handle, "borderColor");
    Color borderColor;
    RefPtr<ResourceObject> borderColorResObj;
    if (ArkTSUtils::ParseJsColor(vm, args, borderColor, borderColorResObj)) {
        if (SystemProperties::ConfigChangePerform() && borderColorResObj) {
            GetArkUINodeModifiers()->getCalendarPickerModifier()->setJSBorderColorResObj(
                handle, reinterpret_cast<void*>(AceType::RawPtr(borderColorResObj)));
        }
        GetArkUINodeModifiers()->getCalendarPickerModifier()->setJSBorderColor(handle, borderColor.GetValue());
    } else if (args->IsObject(vm)) {
        CommonColor commonColor;
        panda::Local<panda::ObjectRef> object = args->ToObject(vm);
        if (ArkTSUtils::ParseCommonEdgeColors(vm, object, commonColor)) {
            NG::BorderColorProperty borderColorProperty = ArkTSUtils::GetBorderColor(commonColor);
            GetArkUINodeModifiers()->getCalendarPickerModifier()->setJSBorderColorProperty(
                handle, reinterpret_cast<void*>(&borderColorProperty));
            return;
        }
        NG::BorderColorProperty borderColorProperty = ArkTSUtils::GetBorderColor(commonColor);
        GetArkUINodeModifiers()->getCalendarPickerModifier()->setJSBorderColorProperty(
            handle, reinterpret_cast<void*>(&borderColorProperty));
    } else {
        GetArkUINodeModifiers()->getCalendarPickerModifier()->setJSBorderColor(handle, Color::BLACK.GetValue());
    }
}

void BuildBorderWidthOption(const CommonCalcDimension& commonCalcDimension, ArkUIBorderWidthOption* borderWidthOption)
{
    if (commonCalcDimension.left.has_value()) {
        borderWidthOption[NUM_0].value = commonCalcDimension.left.value().Value();
        borderWidthOption[NUM_0].unit = static_cast<int32_t>(commonCalcDimension.left.value().Unit());
        borderWidthOption[NUM_0].hasValue = true;
    } else {
        borderWidthOption[NUM_0].hasValue = false;
    }

    if (commonCalcDimension.right.has_value()) {
        borderWidthOption[NUM_1].value = commonCalcDimension.right.value().Value();
        borderWidthOption[NUM_1].unit = static_cast<int32_t>(commonCalcDimension.right.value().Unit());
        borderWidthOption[NUM_1].hasValue = true;
    } else {
        borderWidthOption[NUM_1].hasValue = false;
    }

    if (commonCalcDimension.top.has_value()) {
        borderWidthOption[NUM_2].value = commonCalcDimension.top.value().Value();
        borderWidthOption[NUM_2].unit = static_cast<int32_t>(commonCalcDimension.top.value().Unit());
        borderWidthOption[NUM_2].hasValue = true;
    } else {
        borderWidthOption[NUM_2].hasValue = false;
    }

    if (commonCalcDimension.bottom.has_value()) {
        borderWidthOption[NUM_3].value = commonCalcDimension.bottom.value().Value();
        borderWidthOption[NUM_3].unit = static_cast<int32_t>(commonCalcDimension.bottom.value().Unit());
        borderWidthOption[NUM_3].hasValue = true;
    } else {
        borderWidthOption[NUM_3].hasValue = false;
    }
}

void ParseBorderWidth(ArkUINodeHandle node, EcmaVM* vm, const panda::Local<panda::JSValueRef>& args)
{
    CalcDimension borderWidth;
    RefPtr<ResourceObject> borderWidthResObj;
    if (ArkTSUtils::ParseJsDimensionVp(vm, args, borderWidth, borderWidthResObj)) {
        if (borderWidth.IsNegative()) {
            borderWidth.Reset();
        }
        if (borderWidth.Unit() == DimensionUnit::PERCENT) {
            borderWidth.Reset();
        }
        if (SystemProperties::ConfigChangePerform() && borderWidthResObj) {
            GetArkUINodeModifiers()->getCalendarPickerModifier()->setJSBorderWidthResObj(
                node, reinterpret_cast<void*>(AceType::RawPtr(borderWidthResObj)));
        } else {
            GetArkUINodeModifiers()->getCalendarPickerModifier()->setJSBorderWidth(
                node, borderWidth.Value(), static_cast<int32_t>(borderWidth.Unit()));
        }
    } else if (args->IsObject(vm)) {
        if (ArkTSUtils::IsBorderWidthObjUndefined(vm, args)) {
            CalcDimension value = {};
            GetArkUINodeModifiers()->getCalendarPickerModifier()->setJSBorderWidth(
                node, borderWidth.Value(), static_cast<int32_t>(borderWidth.Unit()));
            return;
        }
        CommonCalcDimension commonCalcDimension;
        panda::Local<panda::ObjectRef> obj = args->ToObject(vm);
        if (ArkTSUtils::ParseCommonEdgeWidths(vm, obj, commonCalcDimension, true)) {
            ArkUIBorderWidthOption borderWidthOption[NUM_4];
            BuildBorderWidthOption(commonCalcDimension, borderWidthOption);
            GetArkUINodeModifiers()->getCalendarPickerModifier()->setJSBorderWidthIsLocalized(
                node, borderWidthOption, NUM_4, true);
            return;
        }
        if (SystemProperties::ConfigChangePerform()) {
            NG::BorderWidthProperty borderWidth;
            ArkTSUtils::ParseEdgeWidthsResObj(vm, obj, borderWidth, true);
            GetArkUINodeModifiers()->getCalendarPickerModifier()->setJSBorderWidthProperty(node, &borderWidth);
        } else {
            ArkUIBorderWidthOption borderWidthOption[NUM_4];
            BuildBorderWidthOption(commonCalcDimension, borderWidthOption);
            GetArkUINodeModifiers()->getCalendarPickerModifier()->setJSBorderWidthArray(node, borderWidthOption, NUM_4);
        }
    } else {
        return;
    }
}

NG::BorderRadiusProperty GetLocalizedBorderRadius(const BorderRadiusOption& borderRadius)
{
    NG::BorderRadiusProperty borderRadiusProperty;
    borderRadiusProperty.radiusTopStart = borderRadius.topLeft;
    borderRadiusProperty.radiusTopEnd = borderRadius.topRight;
    borderRadiusProperty.radiusBottomStart = borderRadius.bottomLeft;
    borderRadiusProperty.radiusBottomEnd = borderRadius.bottomRight;
    borderRadiusProperty.multiValued = true;
    return borderRadiusProperty;
}

void BuildArkUIBorderRadiusOption(const BorderRadiusOption& borderRadius,
    ArkUIBorderRadiusOption* arkUIBorderRadiusOption)
{
    arkUIBorderRadiusOption[NUM_0].value = borderRadius.topLeft.Value();
    arkUIBorderRadiusOption[NUM_0].unit = static_cast<ArkUI_Int32>(borderRadius.topLeft.Unit());
    arkUIBorderRadiusOption[NUM_0].hasValue = true;
    arkUIBorderRadiusOption[NUM_1].value = borderRadius.topRight.Value();
    arkUIBorderRadiusOption[NUM_1].unit = static_cast<ArkUI_Int32>(borderRadius.topRight.Unit());
    arkUIBorderRadiusOption[NUM_1].hasValue = true;
    arkUIBorderRadiusOption[NUM_2].value = borderRadius.bottomLeft.Value();
    arkUIBorderRadiusOption[NUM_2].unit = static_cast<ArkUI_Int32>(borderRadius.bottomLeft.Unit());
    arkUIBorderRadiusOption[NUM_2].hasValue = true;
    arkUIBorderRadiusOption[NUM_3].value = borderRadius.bottomRight.Value();
    arkUIBorderRadiusOption[NUM_3].unit = static_cast<ArkUI_Int32>(borderRadius.bottomRight.Unit());
    arkUIBorderRadiusOption[NUM_3].hasValue = true;
}

void ParseBorderRadius(ArkUINodeHandle nativeNode, EcmaVM* vm, const panda::Local<panda::JSValueRef>& args)
{
    CalcDimension borderRadius;
    RefPtr<ResourceObject> borderRadiusResObj;
    if (ArkTSUtils::ParseJsDimensionVp(vm, args, borderRadius, borderRadiusResObj)) {
        if (SystemProperties::ConfigChangePerform() && borderRadiusResObj) {
            GetArkUINodeModifiers()->getCalendarPickerModifier()->setJSBorderRadiusResObj(
                nativeNode, reinterpret_cast<void*>(AceType::RawPtr(borderRadiusResObj)));
        } else {
            GetArkUINodeModifiers()->getCalendarPickerModifier()->setJSBorderRadius(
                nativeNode, borderRadius.Value(), static_cast<int32_t>(borderRadius.Unit()));
        }
    } else if (args->IsObject(vm)) {
        panda::Local<panda::ObjectRef> object = args->ToObject(vm);
        BorderRadiusOption borderRadiusOption;
        if (ArkTSUtils::ParseAllBorderRadiuses(vm, object, borderRadiusOption)) {
            NG::BorderRadiusProperty borderRadiusProperty = GetLocalizedBorderRadius(borderRadiusOption);
            GetArkUINodeModifiers()->getCalendarPickerModifier()->setJSBorderRadiusProperty(
                nativeNode, &borderRadiusProperty);
            return;
        }
        if (SystemProperties::ConfigChangePerform()) {
            auto borderRadiusProperty = ArkTSUtils::BorderRadiusProperty(vm, object, borderRadiusOption);
            GetArkUINodeModifiers()->getCalendarPickerModifier()->setJSBorderRadiusProperty(
                nativeNode, &borderRadiusProperty);
        } else {
            ArkUIBorderRadiusOption arkUIBorderRadiusOption[NUM_4];
            BuildArkUIBorderRadiusOption(borderRadiusOption, arkUIBorderRadiusOption);
            GetArkUINodeModifiers()->getCalendarPickerModifier()->setJSBorderRadiusArray(
                nativeNode, arkUIBorderRadiusOption, NUM_4);
        }
    }
}

void ParseBorderStyle(ArkUINodeHandle nativeNode, EcmaVM* vm, const panda::Local<panda::JSValueRef>& args)
{
    if (args->IsObject(vm)) {
        BorderStyleOption borderStyle = ArkTSUtils::ParseBorderStyle(vm, args->ToObject(vm));
        ArkUI_Int32 styles[NUM_4] = {
            static_cast<ArkUI_Int32>(
                borderStyle.styleLeft.has_value() ? borderStyle.styleLeft.value() : BorderStyle::SOLID),
            static_cast<ArkUI_Int32>(
                borderStyle.styleRight.has_value() ? borderStyle.styleRight.value() : BorderStyle::SOLID),
            static_cast<ArkUI_Int32>(
                borderStyle.styleTop.has_value() ? borderStyle.styleTop.value() : BorderStyle::SOLID),
            static_cast<ArkUI_Int32>(
                borderStyle.styleBottom.has_value() ? borderStyle.styleBottom.value() : BorderStyle::SOLID)
        };
        GetArkUINodeModifiers()->getCalendarPickerModifier()->setJSBorderStyleArray(nativeNode, styles, NUM_4);
        return;
    }
    if (args->IsNumber()) {
        auto borderStyle = ArkTSUtils::ConvertBorderStyle(args->ToNumber(vm)->Int32Value(vm));
        GetArkUINodeModifiers()->getCalendarPickerModifier()->setJsBorderStyle(
            nativeNode, static_cast<ArkUI_Int32>(borderStyle));
        return;
    }
    GetArkUINodeModifiers()->getCalendarPickerModifier()->setJsBorderStyle(
        nativeNode, static_cast<ArkUI_Int32>(BorderStyle::SOLID));
}

bool HandleParseHeightError(ArkUINodeHandle nativeNode, EcmaVM* vm, const panda::Local<panda::JSValueRef>& jsValue)
{
    GetArkUINodeModifiers()->getCalendarPickerModifier()->clearJSWidthOrHeight(nativeNode, false);
    if (jsValue->IsObject(vm)) {
        panda::Local<panda::ObjectRef> object = jsValue->ToObject(vm);
        auto layoutPolicy = object->Get(vm, panda::StringRef::NewFromUtf8(vm, "id_"));
        if (layoutPolicy->IsString(vm)) {
            auto policy = ArkTSUtils::ParseLayoutPolicy(layoutPolicy->ToString(vm)->ToString(vm));
            GetArkUINodeModifiers()->getCalendarPickerModifier()->updateOnlyLayoutPolicyProperty(
                nativeNode, static_cast<int32_t>(policy), false);
            return true;
        }
    }
    GetArkUINodeModifiers()->getCalendarPickerModifier()->updateOnlyLayoutPolicyProperty(
        nativeNode, static_cast<int32_t>(LayoutCalPolicy::NO_MATCH), false);
    return false;
}

bool SetJsHeight(ArkUINodeHandle nativeNode, EcmaVM* vm, const panda::Local<panda::JSValueRef>& jsValue)
{
    GetArkUINodeModifiers()->getCalendarPickerModifier()->jSResetResObj(nativeNode, "height");
    CalcDimension value;
    RefPtr<ResourceObject> valueResObj;
    if (jsValue->IsUndefined()) {
        GetArkUINodeModifiers()->getCalendarPickerModifier()->updateOnlyLayoutPolicyProperty(
            nativeNode, static_cast<int32_t>(LayoutCalPolicy::NO_MATCH), false);
        GetArkUINodeModifiers()->getCalendarPickerModifier()->clearJSWidthOrHeight(nativeNode, false);
        return true;
    }
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
        if (!ArkTSUtils::ParseJsDimensionVpNG(vm, jsValue, value, valueResObj)) {
            // JsHeight return false, check if set LayoutPolicy before return.
            return HandleParseHeightError(nativeNode, vm, jsValue);
        }
    } else if (!ArkTSUtils::ParseJsDimensionVp(vm, jsValue, value, valueResObj)) {
        return false;
    }

    GetArkUINodeModifiers()->getCalendarPickerModifier()->updateOnlyLayoutPolicyProperty(
        nativeNode, static_cast<int32_t>(LayoutCalPolicy::NO_MATCH), false);
    if (!SystemProperties::ConfigChangePerform() ? LessNotEqual(value.Value(), 0.0)
                                                 : (LessNotEqual(value.Value(), 0.0) && !valueResObj)) {
        if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
            GetArkUINodeModifiers()->getCalendarPickerModifier()->clearJSWidthOrHeight(nativeNode, false);
            return true;
        } else {
            value.SetValue(0.0);
        }
    }

    if (SystemProperties::ConfigChangePerform() && valueResObj) {
        GetArkUINodeModifiers()->getCalendarPickerModifier()->setJSHeightResObj(
            nativeNode, reinterpret_cast<void*>(AceType::RawPtr(valueResObj)));
    } else {
        GetArkUINodeModifiers()->getCalendarPickerModifier()->setJSHeight(
            nativeNode, value.Value(), static_cast<int32_t>(value.Unit()), value.CalcValue().c_str());
    }
    return true;
}

void ParseCalendarPickerBorderColor(ArkUINodeHandle nativeNode, EcmaVM* vm, const panda::Local<panda::JSValueRef>& args)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    RefPtr<CalendarTheme> theme = pipelineContext->GetTheme<CalendarTheme>();
    CHECK_NULL_VOID(theme);
    if (!args->IsObject(vm) && !args->IsNumber() && !args->IsString(vm)) {
        GetArkUINodeModifiers()->getCalendarPickerModifier()->setJSBorderColor(
            nativeNode, theme->GetEntryBorderColor().GetValue());
    } else {
        ParseBorderColor(nativeNode, vm, args);
    }
}

ArkUINativeModuleValue SetCalendarPickerJSBorder(EcmaVM* vm, const panda::Local<panda::JSValueRef>& jsValue)
{
    ArkUINodeHandle nativeNode = nodePtr(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    if (!jsValue->IsObject(vm)) {
        GetArkUINodeModifiers()->getCalendarPickerModifier()->resetCalendarPickerBorder(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    panda::Local<panda::ObjectRef> object = jsValue->ToObject(vm);
    auto valueWidth = object->Get(vm, panda::StringRef::NewFromUtf8(vm, "width"));
    CalcDimension value;
    if (ArkTSUtils::ParseJsDimensionVpNG(vm, valueWidth, value) || valueWidth->IsObject(vm)) {
        ParseBorderWidth(nativeNode, vm, valueWidth);
    } else {
        GetArkUINodeModifiers()->getCalendarPickerModifier()->resetCalendarPickerBorderWidth(nativeNode);
    }

    // use default value when undefined.
    ParseCalendarPickerBorderColor(nativeNode, vm, object->Get(vm, panda::StringRef::NewFromUtf8(vm, "color")));

    auto valueRadius = object->Get(vm, panda::StringRef::NewFromUtf8(vm, "radius"));
    if (!valueRadius->IsUndefined()) {
        ParseBorderRadius(nativeNode, vm, valueRadius);
    }
    // use default value when undefined.
    ParseBorderStyle(nativeNode, vm, object->Get(vm, panda::StringRef::NewFromUtf8(vm, "style")));

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CalendarPickerBridge::SetCalendarPickerBorder(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (IsJsView(firstArg, vm)) {
        SetCalendarPickerJSBorder(vm, secondArg);
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> leftArg = runtimeCallInfo->GetCallArgRef(5);   // 5: index of parameter left color
    Local<JSValueRef> rightArg = runtimeCallInfo->GetCallArgRef(6);  // 6: index of parameter right color
    Local<JSValueRef> topArg = runtimeCallInfo->GetCallArgRef(7);    // 7: index of parameter top color
    Local<JSValueRef> bottomArg = runtimeCallInfo->GetCallArgRef(8); // 8: index of parameter bottom color

    CommonBridge::SetBorder(runtimeCallInfo);

    CalcDimension borderWidth;
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
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (IsJsView(firstArg, vm)) {
        nativeNode = nodePtr(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    }
    GetArkUINodeModifiers()->getCalendarPickerModifier()->resetCalendarPickerBorder(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SetCalendarPickerJSHeight(EcmaVM* vm, const panda::Local<panda::JSValueRef>& jsValue)
{
    ArkUINodeHandle nativeNode = nodePtr(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    CalcDimension value;
    if (ArkTSUtils::ParseJsDimensionVpNG(vm, jsValue, value) && value.IsValid()) {
        SetJsHeight(nativeNode, vm, jsValue);
        return panda::JSValueRef::Undefined(vm);
    }

    LayoutCalPolicy policy = LayoutCalPolicy::NO_MATCH;
    if (jsValue->IsObject(vm)) {
        auto object = jsValue->ToObject(vm);
        CHECK_NE_RETURN(!object.IsEmpty(), true, panda::JSValueRef::Undefined(vm));
        auto layoutPolicy = object->Get(vm, panda::StringRef::NewFromUtf8(vm, "id_"));
        if (layoutPolicy->IsNull() || layoutPolicy->IsUndefined()) {
            return panda::JSValueRef::Undefined(vm);
        }
        if (layoutPolicy->IsString(vm)) {
            policy = ArkTSUtils::ParseLayoutPolicy(layoutPolicy->ToString(vm)->ToString(vm));
        }
    }
    GetArkUINodeModifiers()->getCalendarPickerModifier()->updateOnlyLayoutPolicyProperty(
        nativeNode, static_cast<int32_t>(policy), false);
    GetArkUINodeModifiers()->getCalendarPickerModifier()->clearJSHeight(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CalendarPickerBridge::SetCalendarPickerHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> jsValue = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (IsJsView(firstArg, vm)) {
        SetCalendarPickerJSHeight(vm, jsValue);
        return panda::JSValueRef::Undefined(vm);
    }
    CalcDimension height;
    std::string calcStr;
    if (!ArkTSUtils::ParseJsDimensionVpNG(vm, jsValue, height)) {
        GetArkUINodeModifiers()->getCalendarPickerModifier()->resetCalendarPickerHeight(nativeNode);
        if (jsValue->IsObject(vm)) {
            auto obj = jsValue->ToObject(vm);
            auto layoutPolicy = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "id_"));
            if (layoutPolicy->IsString(vm)) {
                auto policy = ArkTSUtils::ParseLayoutPolicy(layoutPolicy->ToString(vm)->ToString(vm));
                GetArkUINodeModifiers()->getCalendarPickerModifier()->updateOnlyLayoutPolicyProperty(
                    nativeNode, static_cast<int32_t>(policy), false);
                return panda::JSValueRef::Undefined(vm);
            }
        }
    } else {
        if (LessNotEqual(height.Value(), 0.0)) {
            if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
                GetArkUINodeModifiers()->getCalendarPickerModifier()->resetCalendarPickerHeight(nativeNode);
                GetArkUINodeModifiers()->getCalendarPickerModifier()->updateOnlyLayoutPolicyProperty(
                    nativeNode, static_cast<int32_t>(LayoutCalPolicy::NO_MATCH), false);
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
    GetArkUINodeModifiers()->getCalendarPickerModifier()->updateOnlyLayoutPolicyProperty(
        nativeNode, static_cast<int32_t>(LayoutCalPolicy::NO_MATCH), false);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CalendarPickerBridge::ResetCalendarPickerHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (IsJsView(firstArg, vm)) {
        nativeNode = nodePtr(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    }
    GetArkUINodeModifiers()->getCalendarPickerModifier()->resetCalendarPickerHeight(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SetCalendarPickerJSBorderColor(EcmaVM* vm, const panda::Local<panda::JSValueRef>& jsValue)
{
    Color borderColor;
    auto nativeNode = nodePtr(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    if (ArkTSUtils::ParseJsColor(vm, jsValue, borderColor) || jsValue->IsObject(vm)) {
        ParseBorderColor(nativeNode, vm, jsValue);
    } else {
        GetArkUINodeModifiers()->getCalendarPickerModifier()->resetCalendarPickerBorderColor(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CalendarPickerBridge::SetCalendarPickerBorderColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (IsJsView(firstArg, vm)) {
        SetCalendarPickerJSBorderColor(vm, secondArg);
        return panda::JSValueRef::Undefined(vm);
    }
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
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (IsJsView(firstArg, vm)) {
        nativeNode = nodePtr(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    }
    GetArkUINodeModifiers()->getCalendarPickerModifier()->resetCalendarPickerBorderColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

void SetRenderStrategy(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    auto nativeNode = nodePtr(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    uint32_t argsNumber = runtimeCallInfo->GetArgsNumber();
    if (argsNumber != NUM_3) {
        return;
    }
    auto value = runtimeCallInfo->GetCallArgRef(NUM_2);
    if (!value->IsNumber()) {
        GetArkUINodeModifiers()->getCommonModifier()->setRenderStrategy(
            nativeNode, static_cast<int32_t>(RenderStrategy::FAST));
        return;
    }
    GetArkUINodeModifiers()->getCommonModifier()->setRenderStrategy(nativeNode, value->ToNumber(vm)->Int32Value(vm));
}

bool ArkUIRuntimeCallBackInfo(EcmaVM* vm, const std::string& callerName, const panda::Local<panda::JSValueRef>& tmpInfo,
    std::vector<ArkUIRuntimeCallBackInfoType>& infoTypes)
{
    bool typeVerified = false;
    std::string unrecognizedType;
    for (const auto& infoType : infoTypes) {
        switch (infoType) {
            case ArkUIRuntimeCallBackInfoType::STRING:
                if (tmpInfo->IsString(vm)) {
                    typeVerified = true;
                } else {
                    unrecognizedType += "string|";
                }
                break;
            case ArkUIRuntimeCallBackInfoType::NUMBER:
                if (tmpInfo->IsNumber()) {
                    typeVerified = true;
                } else {
                    unrecognizedType += "number|";
                }
                break;
            case ArkUIRuntimeCallBackInfoType::OBJECT:
                if (tmpInfo->IsObject(vm)) {
                    typeVerified = true;
                } else {
                    unrecognizedType += "object|";
                }
                break;
            case ArkUIRuntimeCallBackInfoType::FUNCTION:
                if (tmpInfo->IsFunction(vm)) {
                    typeVerified = true;
                } else {
                    unrecognizedType += "Function|";
                }
                break;
            default:
                break;
        }
    }
    if (!typeVerified) {
        LOGD("%{public}s: info[0] is not a [%{public}s]", callerName.c_str(),
            unrecognizedType.substr(0, unrecognizedType.size() - 1).c_str());
    }
    return typeVerified || infoTypes.size() == 0;
}

void JsBorderRadius(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_VOID(vm);
    auto nativeNode = nodePtr(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    GetArkUINodeModifiers()->getCalendarPickerModifier()->jSResetResObj(nativeNode, "borderRadius");
    SetRenderStrategy(runtimeCallInfo);
    static std::vector<ArkUIRuntimeCallBackInfoType> checkCallbackList { ArkUIRuntimeCallBackInfoType::STRING,
        ArkUIRuntimeCallBackInfoType::NUMBER, ArkUIRuntimeCallBackInfoType::OBJECT };
    auto radiusVal = runtimeCallInfo->GetCallArgRef(NUM_1);
    if (!ArkUIRuntimeCallBackInfo(vm, "JsBorderRadius", radiusVal, checkCallbackList)) {
        Dimension defalut {};
        GetArkUINodeModifiers()->getCalendarPickerModifier()->setJSBorderRadius(
            nativeNode, defalut.Value(), static_cast<int32_t>(defalut.Unit()));
        return;
    }
    ParseBorderRadius(nativeNode, vm, radiusVal);
}

ArkUINativeModuleValue SetCalendarPickerJSBorderRadius(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    CalcDimension value;
    if (ArkTSUtils::ParseJsDimensionVpNG(vm, secondArg, value) || secondArg->IsObject(vm)) {
        JsBorderRadius(runtimeCallInfo);
    } else {
        SetRenderStrategy(runtimeCallInfo);
        GetArkUINodeModifiers()->getCalendarPickerModifier()->resetCalendarPickerBorderRadius(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CalendarPickerBridge::SetCalendarPickerBorderRadius(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (IsJsView(firstArg, vm)) {
        SetCalendarPickerJSBorderRadius(runtimeCallInfo);
        return panda::JSValueRef::Undefined(vm);
    }
    CalcDimension borderRadius;
    if (!ArkTSUtils::ParseJsDimensionVpNG(vm, secondArg, borderRadius, true)) {
        GetArkUINodeModifiers()->getCalendarPickerModifier()->resetCalendarPickerBorderRadius(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    if (LessNotEqual(borderRadius.Value(), 0.0)) {
        GetArkUINodeModifiers()->getCalendarPickerModifier()->resetCalendarPickerBorderRadius(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    GetArkUINodeModifiers()->getCalendarPickerModifier()->setCalendarPickerBorderRadius(
        nativeNode, borderRadius.Value(), static_cast<int>(borderRadius.Unit()));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CalendarPickerBridge::ResetCalendarPickerBorderRadius(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (IsJsView(firstArg, vm)) {
        nativeNode = nodePtr(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    }
    GetArkUINodeModifiers()->getCalendarPickerModifier()->resetCalendarPickerBorderRadius(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CalendarPickerBridge::SetCalendarPickerMarkToday(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> markTodayArg = runtimeCallInfo->GetCallArgRef(NUM_1); // markToday value
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (IsJsView(nodeArg, vm)) {
        nativeNode = nodePtr(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    }
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
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (IsJsView(nodeArg, vm)) {
        nativeNode = nodePtr(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    }
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
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, nativeNodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (IsJsView(nativeNodeArg, vm)) {
        nativeNode = nodePtr(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    }
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
        auto result = func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_1);
        ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
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
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, nativeNodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (IsJsView(nativeNodeArg, vm)) {
        nativeNode = nodePtr(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    }
    GetArkUINodeModifiers()->getCalendarPickerModifier()->resetCalendarPickerOnChange(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

void ParseHintRadius(EcmaVM* vm, const panda::Local<panda::ObjectRef>& obj, NG::CalendarSettingData& settingData,
    CalcDimension& dayRadius)
{
    RefPtr<CalendarTheme> calendarTheme = GetTheme<CalendarTheme>();
    CHECK_NULL_VOID(calendarTheme);

    panda::Local<panda::JSValueRef> hintRadiusVal = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "hintRadius"));

    if (SystemProperties::ConfigChangePerform()) {
        RefPtr<ResourceObject> hintRadiusResObj;
        if (!ArkTSUtils::ParseJsDimensionVpNG(vm, hintRadiusVal, dayRadius, hintRadiusResObj)) {
            dayRadius = calendarTheme->GetCalendarDayRadius();
        }

        if (hintRadiusResObj) {
            settingData.dayRadiusResObj = hintRadiusResObj;
        }
    } else {
        if (!ArkTSUtils::ParseJsDimensionVpNG(vm, hintRadiusVal, dayRadius)) {
            dayRadius = calendarTheme->GetCalendarDayRadius();
        }
    }
}

void ParseSelectedDateObject(
    const ArkUIRuntimeCallInfo* runtimeCallInfo, const panda::Local<panda::ObjectRef>& selectedObject)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_VOID(vm);
    panda::Local<panda::JSValueRef> changeEventVal =
        selectedObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "changeEvent"));
    if (changeEventVal->IsUndefined() || changeEventVal->IsNull() || !changeEventVal->IsFunction(vm)) {
        return;
    }
    panda::Local<panda::FunctionRef> func = changeEventVal->ToObject(vm);
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());

    std::function<void(std::string&)> changeEvent = [vm, func = panda::CopyableGlobal(vm, func), node = targetNode](
                                                        const std::string& dateStr) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        ACE_SCORING_EVENT("DatePicker.SelectedDateTimeChangeEvent");
        PipelineContext::SetCallBackNode(node);
        panda::Local<panda::DateRef> dateObj = panda::DateRef::New(vm, GetMSByDate(dateStr));
        panda::Local<panda::JSValueRef> params[] = { dateObj };
        auto result = func->Call(vm, func.ToLocal(), params, 1);
        ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
    };

    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_VOID(GetNativeNode(nativeNode, firstArg, vm), true);
    GetArkUINodeModifiers()->getCalendarPickerModifier()->setCalendarPickerOnChange(
        nativeNode, reinterpret_cast<void*>(&changeEvent));
}

void ParseSelectedDate(ArkUIRuntimeCallInfo* runtimeCallInfo, EcmaVM* vm, const panda::Local<panda::ObjectRef>& obj,
    NG::CalendarSettingData& settingData)
{
    panda::Local<panda::JSValueRef> selected = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "selected"));
    auto parseSelectedDate = CalendarPickerUtils::ParseDate(vm, selected);
    if (selected->IsObject(vm) && parseSelectedDate.GetYear() != 0) {
        panda::Local<panda::ObjectRef> selectedDateObj = selected->ToObject(vm);
        panda::Local<panda::JSValueRef> changeEventVal =
            selectedDateObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "changeEvent"));

        if (!changeEventVal->IsUndefined() && changeEventVal->IsFunction(vm)) {
            ParseSelectedDateObject(runtimeCallInfo, selectedDateObj);
            panda::Local<panda::JSValueRef> valueVal =
                selectedDateObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "value"));
            settingData.selectedDate = CalendarPickerUtils::ParseDate(vm, valueVal);
        } else {
            settingData.selectedDate = parseSelectedDate;
        }
    }
}

ArkUINativeModuleValue CalendarPickerBridge::CreateCalendarPicker(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    NG::CalendarSettingData settingData;
    RefPtr<CalendarTheme> calendarTheme = GetTheme<CalendarTheme>();
    CHECK_NULL_RETURN(calendarTheme, panda::NativePointerRef::New(vm, nullptr));
    CalcDimension dayRadius;

    uint32_t argsNumber = runtimeCallInfo->GetArgsNumber();
    if (argsNumber != NUM_1) {
        return panda::JSValueRef::Undefined(vm);
    }

    panda::Local<panda::JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    if (firstArg->IsObject(vm)) {
        panda::Local<panda::ObjectRef> obj = firstArg->ToObject(vm);

        ParseHintRadius(vm, obj, settingData, dayRadius);
        ParseSelectedDate(runtimeCallInfo, vm, obj, settingData);

        auto disabledDateRangeValue = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "disabledDateRange"));
        CalendarPickerUtils::ParseDisabledDateRange(vm, disabledDateRangeValue, settingData);
        PickerDate::SortAndMergeDisabledDateRange(settingData.disabledDateRange);

        panda::Local<panda::JSValueRef> startDate = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "start"));
        panda::Local<panda::JSValueRef> endDate = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "end"));
        auto parseStartDate = CalendarPickerUtils::ParseDate(vm, startDate, false);
        auto parseEndDate = CalendarPickerUtils::ParseDate(vm, endDate, false);
        if (parseEndDate.GetYear() > 0 && parseStartDate.ToDays() > parseEndDate.ToDays()) {
            parseStartDate = PickerDate();
            parseEndDate = PickerDate();
        }
        settingData.startDate = parseStartDate;
        settingData.endDate = parseEndDate;
    } else {
        dayRadius = calendarTheme->GetCalendarDayRadius();
    }

    settingData.dayRadius = dayRadius;
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getCalendarPickerModifier()->jsCreate(&settingData);
    return panda::JSValueRef::Undefined(vm);
}

void CalendarPickerBridge::RegisterCalendarPickerAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
#ifndef ARKUI_WEARABLE
    const char* functionNames[] = { "create", "setTextStyle", "resetTextStyle", "setEdgeAlign", "resetEdgeAlign",
        "setCalendarPickerPadding", "resetCalendarPickerPadding", "setCalendarPickerBorder",
        "resetCalendarPickerBorder", "setCalendarPickerHeight", "resetCalendarPickerHeight",
        "setCalendarPickerBorderColor", "resetCalendarPickerBorderColor", "setCalendarPickerBorderRadius",
        "resetCalendarPickerBorderRadius", "setCalendarPickerMarkToday", "resetCalendarPickerMarkToday",
        "setCalendarPickerOnChange", "resetCalendarPickerOnChange" };

    Local<JSValueRef> funcValues[] = {
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CalendarPickerBridge::CreateCalendarPicker),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CalendarPickerBridge::SetTextStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CalendarPickerBridge::ResetTextStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CalendarPickerBridge::SetEdgeAlign),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CalendarPickerBridge::ResetEdgeAlign),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CalendarPickerBridge::SetCalendarPickerPadding),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CalendarPickerBridge::ResetCalendarPickerPadding),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CalendarPickerBridge::SetCalendarPickerBorder),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CalendarPickerBridge::ResetCalendarPickerBorder),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CalendarPickerBridge::SetCalendarPickerHeight),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CalendarPickerBridge::ResetCalendarPickerHeight),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CalendarPickerBridge::SetCalendarPickerBorderColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CalendarPickerBridge::ResetCalendarPickerBorderColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CalendarPickerBridge::SetCalendarPickerBorderRadius),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CalendarPickerBridge::ResetCalendarPickerBorderRadius),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CalendarPickerBridge::SetCalendarPickerMarkToday),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CalendarPickerBridge::ResetCalendarPickerMarkToday),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CalendarPickerBridge::SetCalendarPickerOnChange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CalendarPickerBridge::ResetCalendarPickerOnChange),
    };

    auto calendarPicker =
        panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(functionNames), functionNames, funcValues);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "calendarPicker"), calendarPicker);

#endif
}
} // namespace OHOS::Ace::NG
