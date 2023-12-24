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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_gauge_bridge.h"

#include "base/geometry/dimension.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_api.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "bridge/declarative_frontend/jsview/js_linear_gradient.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/pattern/gauge/gauge_paint_property.h"
#include "core/components_ng/pattern/gauge/gauge_theme.h"

namespace OHOS::Ace::NG {
namespace {
constexpr Color ERROR_COLOR = Color(0xFFE84026);
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
void ResetColor(void* nativeNode)
{
    if (!Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        GetArkUIInternalNodeAPI()->GetGaugeModifier().ResetGradientColors(nativeNode);
    } else {
        GetArkUIInternalNodeAPI()->GetGaugeModifier().ResetColors(nativeNode);
    }
}
}

void SortColorStopOffset(std::vector<NG::ColorStopArray>& colors)
{
    for (auto& colorStopArray : colors) {
        std::sort(colorStopArray.begin(), colorStopArray.end(),
            [](const std::pair<Color, Dimension>& left, const std::pair<Color, Dimension>& right) {
                return left.second.Value() < right.second.Value();
            });

        auto iter = std::unique(colorStopArray.begin(), colorStopArray.end(),
            [](const std::pair<Color, Dimension>& left, const std::pair<Color, Dimension>& right) {
                return left.second.Value() == right.second.Value();
            });
        colorStopArray.erase(iter, colorStopArray.end());
    }
}

void ConvertResourceColor(const EcmaVM* vm, const Local<JSValueRef>& item, std::vector<NG::ColorStopArray>& colors)
{
    Color color;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, item, color)) {
        color = ERROR_COLOR;
    }
    NG::ColorStopArray colorStopArray;
    colorStopArray.emplace_back(std::make_pair(color, Dimension(0.0)));
    colors.emplace_back(colorStopArray);
}

void ConvertGradientColor(
    const EcmaVM* vm, const Local<JSValueRef>& itemParam, std::vector<NG::ColorStopArray>& colors, NG::GaugeType& type)
{
    if (!itemParam->IsObject()) {
        type = NG::GaugeType::TYPE_CIRCULAR_MONOCHROME;
        return ConvertResourceColor(vm, itemParam, colors);
    }
    Framework::JSLinearGradient* jsLinearGradient =
        static_cast<Framework::JSLinearGradient*>(itemParam->ToObject(vm)->GetNativePointerField(0));
    if (!jsLinearGradient) {
        type = NG::GaugeType::TYPE_CIRCULAR_MONOCHROME;
        return ConvertResourceColor(vm, itemParam, colors);
    }

    type = NG::GaugeType::TYPE_CIRCULAR_SINGLE_SEGMENT_GRADIENT;
    if (jsLinearGradient->GetGradient().size() == 0) {
        NG::ColorStopArray colorStopArray;
        colorStopArray.emplace_back(std::make_pair(ERROR_COLOR, Dimension(0.0)));
        colors.emplace_back(colorStopArray);
    } else {
        colors.emplace_back(jsLinearGradient->GetGradient());
    }
}

void SetGradientColorsObject(const EcmaVM* vm, const Local<JSValueRef>& info, std::vector<NG::ColorStopArray>& colors,
    std::vector<float>& weights, NG::GaugeType& type, void* nativeNode)
{
    ArkUIGradientType gradient;
    ConvertGradientColor(vm, info, colors, type);
    auto colorStruct = std::make_unique<uint32_t[]>(colors[0].size());
    auto offsetStruct = std::make_unique<ArkUILengthType[]>(colors[0].size());
    std::vector<uint32_t> linearLengths { colors[0].size() };
    for (uint32_t i = 0; i < colors[0].size(); i++) {
        colorStruct[i] = colors[0][i].first.GetValue();
        offsetStruct[i].number = colors[0][i].second.Value();
        offsetStruct[i].unit = static_cast<int8_t>(colors[0][i].second.Unit());
    }
    gradient.color = colorStruct.get();
    gradient.offset = offsetStruct.get();
    gradient.gradientLength = &(*linearLengths.begin());
    gradient.weight = nullptr;
    gradient.type = static_cast<uint32_t>(type);
    gradient.length = 1;
    GetArkUIInternalNodeAPI()->GetGaugeModifier().SetGradientColors(nativeNode, &gradient, 0);
}

void SetGradientColorsArray(const EcmaVM* vm, const Local<JSValueRef>& info, std::vector<NG::ColorStopArray>& colors,
    std::vector<float>& weights, NG::GaugeType& type, void* nativeNode)
{
    ArkUIGradientType gradient;
    uint32_t totalLength = 0;
    std::vector<uint32_t> linearLengths(colors.size(), 0);
    for (uint32_t i = 0; i < colors.size(); i++) {
        linearLengths[i] = colors[i].size();
        totalLength += colors[i].size();
    }
    auto colorStruct = std::make_unique<uint32_t[]>(totalLength);
    auto offsetStruct = std::make_unique<ArkUILengthType[]>(totalLength);
    int32_t pos = 0;
    for (uint32_t i = 0; i < colors.size(); i++) {
        for (uint32_t j = 0; j < colors[i].size(); j++, pos++) {
            colorStruct[pos] = colors[i][j].first.GetValue();
            offsetStruct[pos].number = colors[i][j].second.Value();
            offsetStruct[pos].unit = static_cast<int8_t>(colors[i][j].second.Unit());
        }
    }
    gradient.color = colorStruct.get();
    gradient.offset = offsetStruct.get();
    gradient.gradientLength = &(*linearLengths.begin());
    gradient.weight = &(*weights.begin());
    gradient.type = static_cast<uint32_t>(type);
    gradient.length = colors.size();
    GetArkUIInternalNodeAPI()->GetGaugeModifier().SetGradientColors(nativeNode, &gradient, weights.size());
}

void SetGradientColors(const EcmaVM* vm, const Local<JSValueRef>& info, void* nativeNode)
{
    if (info->IsNull() || info->IsUndefined()) {
        GetArkUIInternalNodeAPI()->GetGaugeModifier().ResetGradientColors(nativeNode);
        return;
    }
    NG::GaugeType type = NG::GaugeType::TYPE_CIRCULAR_MULTI_SEGMENT_GRADIENT;
    std::vector<NG::ColorStopArray> colors;
    std::vector<float> weights;
    if (!info->IsArray(vm)) {
        SetGradientColorsObject(vm, info, colors, weights, type, nativeNode);
        return;
    }
    auto jsColorsArray = panda::CopyableGlobal<panda::ArrayRef>(vm, info);
    if (jsColorsArray->Length(vm) == 0) {
        GetArkUIInternalNodeAPI()->GetGaugeModifier().ResetGradientColors(nativeNode);
        return;
    }

    for (size_t i = 0; i < jsColorsArray->Length(vm); ++i) {
        if (static_cast<int32_t>(i) >= NG::COLORS_MAX_COUNT) {
            break;
        }
        auto jsValue = jsColorsArray->GetValueAt(vm, info, i);
        if (!jsValue->IsArray(vm)) {
            continue;
        }
        auto tempColors = panda::CopyableGlobal<panda::ArrayRef>(vm, jsValue);
        // Get weight
        float weight = tempColors->GetValueAt(vm, jsValue, 1)->ToNumber(vm)->Value();
        if (NonPositive(weight)) {
            continue;
        }
        weights.push_back(weight);
        // Get color
        auto jsColorValue = tempColors->GetValueAt(vm, jsValue, 0);
        ConvertGradientColor(vm, jsColorValue, colors, type);
    }
    type = NG::GaugeType::TYPE_CIRCULAR_MULTI_SEGMENT_GRADIENT;
    SortColorStopOffset(colors);
    SetGradientColorsArray(vm, info, colors, weights, type, nativeNode);
}

ArkUINativeModuleValue GaugeBridge::SetColors(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> jsArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();

    if (!Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        SetGradientColors(vm, jsArg, nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    if (!jsArg->IsArray(vm)) {
        ResetColor(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto jsColor = panda::CopyableGlobal<panda::ArrayRef>(vm, jsArg);
    int32_t length = jsColor->Length(vm);
    auto colors = std::make_unique<uint32_t[]>(length);
    auto weights = std::make_unique<float[]>(length);

    auto theme = ArkTSUtils::GetTheme<ProgressTheme>();
    for (int32_t i = 0; i < length; i++) {
        auto jsValue = jsColor->GetValueAt(vm, jsArg, i);
        if (!jsValue->IsArray(vm)) {
            ResetColor(nativeNode);
            return panda::JSValueRef::Undefined(vm);
        }
        auto handle = panda::CopyableGlobal<panda::ArrayRef>(vm, jsValue);
        float weight = handle->GetValueAt(vm, jsValue, 1)->ToNumber(vm)->Value();
        Color selectedColor;
        if (!ArkTSUtils::ParseJsColorAlpha(vm, handle->GetValueAt(vm, jsValue, 1), selectedColor)) {
            selectedColor = ERROR_COLOR;
        }
        colors[i] = selectedColor.GetValue();
        if (weight > 0) {
            weights[i] = weight;
        } else {
            weights[i] = 0.0f;
        }
    }
    GetArkUIInternalNodeAPI()->GetGaugeModifier().SetColors(nativeNode, colors.get(), weights.get(), length);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GaugeBridge::ResetColors(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    ResetColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GaugeBridge::SetGaugeVaule(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();

    if (!secondArg->IsNumber()) {
        GetArkUIInternalNodeAPI()->GetGaugeModifier().ResetGaugeVaule(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    float vaule = static_cast<float>(secondArg->ToNumber(vm)->Value());
    GetArkUIInternalNodeAPI()->GetGaugeModifier().SetGaugeVaule(nativeNode, vaule);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GaugeBridge::ResetGaugeVaule(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetGaugeModifier().ResetGaugeVaule(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GaugeBridge::SetGaugeStartAngle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();

    if (!secondArg->IsNumber()) {
        GetArkUIInternalNodeAPI()->GetGaugeModifier().ResetGaugeStartAngle(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    float vaule = static_cast<float>(secondArg->ToNumber(vm)->Value());
    GetArkUIInternalNodeAPI()->GetGaugeModifier().SetGaugeStartAngle(nativeNode, vaule);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GaugeBridge::ResetGaugeStartAngle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetGaugeModifier().ResetGaugeStartAngle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GaugeBridge::SetGaugeEndAngle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();

    if (!secondArg->IsNumber()) {
        GetArkUIInternalNodeAPI()->GetGaugeModifier().ResetGaugeEndAngle(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    float vaule = static_cast<float>(secondArg->ToNumber(vm)->Value());
    GetArkUIInternalNodeAPI()->GetGaugeModifier().SetGaugeEndAngle(nativeNode, vaule);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GaugeBridge::ResetGaugeEndAngle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetGaugeModifier().ResetGaugeEndAngle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GaugeBridge::SetGaugeStrokeWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    Local<JSValueRef> jsValue = runtimeCallInfo->GetCallArgRef(1);

    CalcDimension strokeWidth;
    if (!ArkTSUtils::ParseJsDimensionVpNG(vm, jsValue, strokeWidth) || strokeWidth.Unit() == DimensionUnit::PERCENT) {
        strokeWidth = CalcDimension(0);
    }
    GetArkUIInternalNodeAPI()->GetGaugeModifier().SetGaugeStrokeWidth(
        nativeNode, strokeWidth.Value(), static_cast<int>(strokeWidth.Unit()));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GaugeBridge::ResetGaugeStrokeWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetGaugeModifier().ResetGaugeStrokeWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GaugeBridge::SetGaugeTrackShadow(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    Local<JSValueRef> jsValue = runtimeCallInfo->GetCallArgRef(1);
    auto radiusArg = runtimeCallInfo->GetCallArgRef(2);
    auto offsetXArg = runtimeCallInfo->GetCallArgRef(3);
    auto offsetYArg = runtimeCallInfo->GetCallArgRef(4);

    if (jsValue->IsNull()) {
        GetArkUIInternalNodeAPI()->GetGaugeModifier().SetShadowOptions(nativeNode, DEFAULT_GAUGE_SHADOW_RADIUS,
            DEFAULT_GAUGE_SHADOW_OFFSETX, DEFAULT_GAUGE_SHADOW_OFFSETY, false);
        return panda::JSValueRef::Undefined(vm);
    }

    if (!jsValue->IsObject()) {
        GetArkUIInternalNodeAPI()->GetGaugeModifier().ResetShadowOptions(nativeNode);
        GetArkUIInternalNodeAPI()->GetGaugeModifier().SetIsShowIndicator(nativeNode, true);
        return panda::JSValueRef::Undefined(vm);
    }

    double radius = 0.0;
    if (!ArkTSUtils::ParseJsDouble(vm, radiusArg, radius)) {
        radius = DEFAULT_GAUGE_SHADOW_RADIUS;
    }

    if (NonPositive(radius)) {
        radius = DEFAULT_GAUGE_SHADOW_RADIUS;
    }

    double offsetX = 0.0;
    if (!ArkTSUtils::ParseJsDouble(vm, offsetXArg, offsetX)) {
        offsetX = DEFAULT_GAUGE_SHADOW_OFFSETX;
    }

    double offsetY = 0.0;
    if (!ArkTSUtils::ParseJsDouble(vm, offsetYArg, offsetY)) {
        offsetY = DEFAULT_GAUGE_SHADOW_OFFSETY;
    }

    GetArkUIInternalNodeAPI()->GetGaugeModifier().SetShadowOptions(nativeNode, radius, offsetX, offsetY, true);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GaugeBridge::ResetGaugeTrackShadow(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetGaugeModifier().ResetShadowOptions(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GaugeBridge::SetGaugeIndicator(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto iconArg = runtimeCallInfo->GetCallArgRef(1);
    auto spaceArg = runtimeCallInfo->GetCallArgRef(2);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetGaugeModifier().SetIsShowIndicator(nativeNode, true);
    std::string iconPath;
    if (ArkTSUtils::ParseJsMedia(vm, iconArg, iconPath)) {
        std::string bundleName;
        std::string moduleName;
        ArkTSUtils::GetJsMediaBundleInfo(vm, iconArg, bundleName, moduleName);
        GetArkUIInternalNodeAPI()->GetGaugeModifier().SetIndicatorIconPath(nativeNode,
            iconPath.c_str(), bundleName.c_str(), moduleName.c_str());
    } else {
        GetArkUIInternalNodeAPI()->GetGaugeModifier().ResetIndicatorIconPath(nativeNode);
    }
    CalcDimension space;
    if (!ArkTSUtils::ParseJsDimensionVpNG(vm, spaceArg, space, false)) {
        space = NG::INDICATOR_DISTANCE_TO_TOP;
    }
    if (space.IsNegative()) {
        space = NG::INDICATOR_DISTANCE_TO_TOP;
    }
    GetArkUIInternalNodeAPI()->GetGaugeModifier().SetIndicatorSpace(nativeNode,
        space.CalcValue().c_str(), space.Value(), static_cast<int32_t>(space.Unit()));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GaugeBridge::ResetGaugeIndicator(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto valueArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    if (valueArg->IsNull()) {
        GetArkUIInternalNodeAPI()->GetGaugeModifier().SetIsShowIndicator(nativeNode, false);
    } else if (valueArg->IsUndefined() || (!valueArg->IsObject())) {
        GetArkUIInternalNodeAPI()->GetGaugeModifier().ResetIndicatorIconPath(nativeNode);
        GetArkUIInternalNodeAPI()->GetGaugeModifier().ResetIndicatorSpace(nativeNode);
        GetArkUIInternalNodeAPI()->GetGaugeModifier().SetIsShowIndicator(nativeNode, true);
    }
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
