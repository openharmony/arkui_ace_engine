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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_data_panel_bridge.h"

#include "base/geometry/dimension.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_api.h"
#include "bridge/declarative_frontend/jsview/js_linear_gradient.h"
#include "bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "core/components/common/properties/color.h"
#include "core/components/data_panel/data_panel_theme.h"
#include "core/components/divider/divider_theme.h"
#include "core/components_ng/pattern/gauge/gauge_paint_property.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;

void ConvertThemeColor(std::vector<OHOS::Ace::NG::Gradient>& colors)
{
    RefPtr<DataPanelTheme> theme = ArkTSUtils::GetTheme<DataPanelTheme>();
    auto themeColors = theme->GetColorsArray();
    for (const auto& item : themeColors) {
        OHOS::Ace::NG::Gradient gradient;
        OHOS::Ace::NG::GradientColor gradientColorStart;
        gradientColorStart.SetLinearColor(LinearColor(item.first));
        gradientColorStart.SetDimension(Dimension(0.0));
        gradient.AddColor(gradientColorStart);
        OHOS::Ace::NG::GradientColor gradientColorEnd;
        gradientColorEnd.SetLinearColor(LinearColor(item.second));
        gradientColorEnd.SetDimension(Dimension(1.0));
        gradient.AddColor(gradientColorEnd);
        colors.emplace_back(gradient);
    }
}

bool ConvertResourceColor(const EcmaVM* vm, const Local<JSValueRef>& item, OHOS::Ace::NG::Gradient& gradient)
{
    Color color;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, item, color)) {
        return false;
    }
    OHOS::Ace::NG::GradientColor gradientColorStart;
    gradientColorStart.SetLinearColor(LinearColor(color));
    gradientColorStart.SetDimension(Dimension(0.0));
    gradient.AddColor(gradientColorStart);
    OHOS::Ace::NG::GradientColor gradientColorEnd;
    gradientColorEnd.SetLinearColor(LinearColor(color));
    gradientColorEnd.SetDimension(Dimension(1.0));
    gradient.AddColor(gradientColorEnd);
    return true;
}

bool ConvertGradientColor(const EcmaVM* vm, const Local<JSValueRef>& itemParam, OHOS::Ace::NG::Gradient& gradient)
{
    if (!itemParam->IsObject()) {
        return ConvertResourceColor(vm, itemParam, gradient);
    }
    Framework::JSLinearGradient* jsLinearGradient =
        static_cast<Framework::JSLinearGradient*>(itemParam->ToObject(vm)->GetNativePointerField(0));
    if (!jsLinearGradient) {
        return ConvertResourceColor(vm, itemParam, gradient);
    }

    size_t colorLength = jsLinearGradient->GetGradient().size();
    if (colorLength == 0) {
        return false;
    }
    for (size_t colorIndex = 0; colorIndex < colorLength; ++colorIndex) {
        OHOS::Ace::NG::GradientColor gradientColor;
        gradientColor.SetLinearColor(LinearColor(jsLinearGradient->GetGradient().at(colorIndex).first));
        gradientColor.SetDimension(jsLinearGradient->GetGradient().at(colorIndex).second);
        gradient.AddColor(gradientColor);
    }
    return true;
}

void SetTrackShadownObject(
    void* nativeNode, std::vector<OHOS::Ace::NG::Gradient>& shadowColors, double radius, double offsetX, double offsetY)
{
    ArkUIGradientType gradient;
    gradient.length = shadowColors.size();
    auto linearLength = std::make_unique<uint32_t[]>(shadowColors.size());
    std::vector<uint32_t> allColor;
    std::vector<ArkUILengthType> allOffset;
    for (uint32_t i = 0; i < shadowColors.size(); i++) {
        linearLength[i] = shadowColors[i].GetColors().size();
        for (uint32_t j = 0; j < linearLength[i]; j++) {
            allColor.emplace_back(shadowColors[i].GetColors()[j].GetLinearColor().GetValue());
            allOffset.emplace_back(ArkUILengthType { .number = shadowColors[i].GetColors()[j].GetDimension().Value(),
                .unit = static_cast<int8_t>(shadowColors[i].GetColors()[j].GetDimension().Unit()) });
        }
    }
    gradient.color = &(*allColor.begin());
    gradient.offset = &(*allOffset.begin());
    gradient.gradientLength = linearLength.get();
    GetArkUIInternalNodeAPI()->GetDataPanelModifier().SetTrackShadow(nativeNode, &gradient, radius, offsetX, offsetY);
}
} // namespace

ArkUINativeModuleValue DataPanelBridge::SetValueColors(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> colors = runtimeCallInfo->GetCallArgRef(NUM_1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();

    std::vector<OHOS::Ace::NG::Gradient> shadowColors;
    if (!colors.IsEmpty() && colors->IsArray(vm)) {
        auto colorsArray = panda::CopyableGlobal<panda::ArrayRef>(vm, colors);
        for (size_t i = 0; i < colorsArray->Length(vm); ++i) {
            auto item = colorsArray->GetValueAt(vm, colors, i);
            OHOS::Ace::NG::Gradient gradient;
            if (!ConvertGradientColor(vm, item, gradient)) {
                shadowColors.clear();
                ConvertThemeColor(shadowColors);
                break;
            }
            shadowColors.emplace_back(gradient);
        }
    }
    ArkUIGradientType gradient;
    gradient.length = shadowColors.size();
    auto linearLength = std::make_unique<uint32_t[]>(shadowColors.size());
    std::vector<uint32_t> allColor;
    std::vector<ArkUILengthType> allOffset;
    for (uint32_t i = 0; i < shadowColors.size(); i++) {
        linearLength[i] = shadowColors[i].GetColors().size();
        for (uint32_t j = 0; j < linearLength[i]; j++) {
            allColor.emplace_back(shadowColors[i].GetColors()[j].GetLinearColor().GetValue());
            allOffset.emplace_back(ArkUILengthType { .number = shadowColors[i].GetColors()[j].GetDimension().Value(),
                .unit = static_cast<int8_t>(shadowColors[i].GetColors()[j].GetDimension().Unit()) });
        }
    }
    gradient.color = &(*allColor.begin());
    gradient.offset = &(*allOffset.begin());
    gradient.gradientLength = linearLength.get();
    GetArkUIInternalNodeAPI()->GetDataPanelModifier().SetValueColors(nativeNode, &gradient);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DataPanelBridge::ResetValueColors(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetDataPanelModifier().ResetValueColors(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DataPanelBridge::SetTrackShadow(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    if (secondArg->IsNull()) {
        GetArkUIInternalNodeAPI()->GetDataPanelModifier().SetNullTrackShadow(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    if (!secondArg->IsObject()) {
        GetArkUIInternalNodeAPI()->GetDataPanelModifier().ResetTrackShadow(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto obj = secondArg->ToObject(vm);
    auto jsRadius = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "radius"));
    auto jsOffsetX = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "offsetX"));
    auto jsOffsetY = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "offsetY"));
    RefPtr<DataPanelTheme> theme = ArkTSUtils::GetTheme<DataPanelTheme>();
    double radius = 0.0;
    if (!ArkTSUtils::ParseJsDouble(vm, jsRadius, radius)) {
        radius = theme->GetTrackShadowRadius().ConvertToVp();
    }

    if (NonPositive(radius)) {
        radius = theme->GetTrackShadowRadius().ConvertToVp();
    }

    double offsetX = 0.0;
    if (!ArkTSUtils::ParseJsDouble(vm, jsOffsetX, offsetX)) {
        offsetX = theme->GetTrackShadowOffsetX().ConvertToVp();
    }

    double offsetY = 0.0;
    if (!ArkTSUtils::ParseJsDouble(vm, jsOffsetY, offsetY)) {
        offsetY = theme->GetTrackShadowOffsetY().ConvertToVp();
    }

    auto colors = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "colors"));
    std::vector<OHOS::Ace::NG::Gradient> shadowColors;
    if (!colors.IsEmpty() && colors->IsArray(vm)) {
        auto colorsArray = panda::CopyableGlobal<panda::ArrayRef>(vm, colors);
        for (size_t i = 0; i < colorsArray->Length(vm); ++i) {
            auto item = colorsArray->GetValueAt(vm, colors, i);
            OHOS::Ace::NG::Gradient gradient;
            if (!ConvertGradientColor(vm, item, gradient)) {
                shadowColors.clear();
                ConvertThemeColor(shadowColors);
                break;
            }
            shadowColors.emplace_back(gradient);
        }
    }
    SetTrackShadownObject(nativeNode, shadowColors, radius, offsetX, offsetY);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DataPanelBridge::ResetTrackShadow(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetDataPanelModifier().ResetTrackShadow(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue DataPanelBridge::SetCloseEffect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    bool boolValue = secondArg->ToBoolean(vm)->Value();
    GetArkUIInternalNodeAPI()->GetDataPanelModifier().SetCloseEffect(nativeNode, boolValue);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DataPanelBridge::ResetCloseEffect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = nativeNodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetDataPanelModifier().ResetCloseEffect(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DataPanelBridge::SetDataPanelTrackBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();

    Color color;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color)) {
        RefPtr<DataPanelTheme> theme = ArkTSUtils::GetTheme<DataPanelTheme>();
        color = theme->GetBackgroundColor();
    }
    GetArkUIInternalNodeAPI()->GetDataPanelModifier().SetDataPanelTrackBackgroundColor(nativeNode, color.GetValue());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DataPanelBridge::ResetDataPanelTrackBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = nativeNodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetDataPanelModifier().ResetDataPanelTrackBackgroundColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DataPanelBridge::SetDataPanelStrokeWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    Local<JSValueRef> jsValue = runtimeCallInfo->GetCallArgRef(1);

    RefPtr<DataPanelTheme> theme = ArkTSUtils::GetTheme<DataPanelTheme>();

    CalcDimension strokeWidth;

    if (!ArkTSUtils::ParseJsDimensionVp(vm, jsValue, strokeWidth)) {
        strokeWidth = theme->GetThickness();
    }

    if (jsValue->IsString() && jsValue->ToString(vm)->ToString().empty()) {
        strokeWidth = theme->GetThickness();
    }

    if (strokeWidth.IsNegative() || strokeWidth.Unit() == DimensionUnit::PERCENT) {
        strokeWidth = theme->GetThickness();
    }

    GetArkUIInternalNodeAPI()->GetDataPanelModifier().SetDataPanelStrokeWidth(
        nativeNode, strokeWidth.Value(), static_cast<int>(strokeWidth.Unit()));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DataPanelBridge::ResetDataPanelStrokeWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetDataPanelModifier().ResetDataPanelStrokeWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
