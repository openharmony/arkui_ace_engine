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
#include "core/interfaces/native/node/api.h"
#include "core/components/calendar/calendar_theme.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"

namespace OHOS::Ace::NG {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int SIZE_OF_TWO = 2;
constexpr Dimension DEFAULT_TEXTSTYLE_FONTSIZE = 16.0_fp;

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
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    Color textColor = calendarTheme->GetEntryFontColor();
    if (!colorArg->IsUndefined()) {
        ArkTSUtils::ParseJsColorAlpha(vm, colorArg, textColor);
    }
    CalcDimension fontSizeData(DEFAULT_TEXTSTYLE_FONTSIZE);
    std::string fontSize = fontSizeData.ToString();
    if (ArkTSUtils::ParseJsDimensionFp(vm, fontSizeArg, fontSizeData) && !fontSizeData.IsNegative() &&
        fontSizeData.Unit() != DimensionUnit::PERCENT) {
        fontSize = fontSizeData.ToString();
    }
    std::string fontWeight = "regular";
    if (fontWeightArg->IsString() || fontWeightArg->IsNumber()) {
        fontWeight = fontWeightArg->ToString(vm)->ToString();
    }
    GetArkUIInternalNodeAPI()->GetCalendarPickerModifier().SetTextStyle(
        nativeNode, textColor.GetValue(), fontSize.c_str(), fontWeight.c_str());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CalendarPickerBridge::ResetTextStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetCalendarPickerModifier().ResetTextStyle(nativeNode);
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
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    if (!alignTypeArg->IsNull() && !alignTypeArg->IsUndefined() && alignTypeArg->IsNumber()) {
        int alignType = alignTypeArg->ToNumber(vm)->Value();
        CalcDimension dx;
        CalcDimension dy;
        if (!dxArg->IsNull() && !dxArg->IsUndefined()) {
            ArkTSUtils::ParseJsDimensionVp(vm, dxArg, dx);
        }
        if (!dyArg->IsNull() && !dyArg->IsUndefined()) {
            ArkTSUtils::ParseJsDimensionVp(vm, dyArg, dy);
        }

        double values[SIZE_OF_TWO];
        int units[SIZE_OF_TWO];

        values[NUM_0] = dx.Value();
        units[NUM_0] = static_cast<int>(dx.Unit());
        values[NUM_1] = dy.Value();
        units[NUM_1] = static_cast<int>(dy.Unit());

        GetArkUIInternalNodeAPI()->GetCalendarPickerModifier().SetEdgeAlign(
            nativeNode, values, units, SIZE_OF_TWO, alignType);
    } else {
        GetArkUIInternalNodeAPI()->GetCalendarPickerModifier().ResetEdgeAlign(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CalendarPickerBridge::ResetEdgeAlign(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetCalendarPickerModifier().ResetEdgeAlign(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
