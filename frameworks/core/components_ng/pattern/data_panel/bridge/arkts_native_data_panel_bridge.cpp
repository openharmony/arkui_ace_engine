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
#include "core/components_ng/pattern/data_panel/bridge/arkts_native_data_panel_bridge.h"
#include <codecvt>

#include "base/geometry/dimension.h"
#include "bridge/declarative_frontend/jsview/js_linear_gradient.h"
#include "core/common/resource/resource_parse_utils.h"
#include "core/components/common/properties/color.h"
#include "core/components/data_panel/data_panel_theme.h"
#include "core/components/divider/divider_theme.h"
#include "core/components_ng/pattern/gauge/gauge_paint_property.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/data_panel/data_panel_model_ng.h"
#include "native_engine/impl/ark/ark_native_engine.h"
#include "bridge/declarative_frontend/ark_theme/theme_apply/js_data_panel_theme.h"

namespace {
const char* DATA_PANEL_NODEPTR_OF_UINODE = "nodePtr_";
} // namespace
namespace OHOS::Ace::NG {
namespace {
constexpr int32_t NUM_0 = 0;
constexpr int32_t NUM_1 = 1;
constexpr int32_t NUM_2 = 2;
constexpr size_t MAX_COUNT = 9;
constexpr double DEFAULT_DATAPANEL_MAX = 100;
constexpr uint32_t TYPE_CYCLE = 0;

enum class JSCallbackInfoType { STRING, NUMBER, OBJECT, BOOLEAN, FUNCTION };

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

bool CheckJSCallbackInfo(const std::string& funcName, const Local<JSValueRef>& value,
    const std::vector<JSCallbackInfoType>& checkList, EcmaVM* vm)
{
    if (value.IsEmpty() || value->IsUndefined() || value->IsNull()) {
        return false;
    }

    JSCallbackInfoType argType;
    if (value->IsString(vm)) {
        argType = JSCallbackInfoType::STRING;
    } else if (value->IsNumber()) {
        argType = JSCallbackInfoType::NUMBER;
    } else if (value->IsObject(vm)) {
        argType = JSCallbackInfoType::OBJECT;
    } else if (value->IsBoolean()) {
        argType = JSCallbackInfoType::BOOLEAN;
    } else if (value->IsFunction(vm)) {
        argType = JSCallbackInfoType::FUNCTION;
    } else {
        return false;
    }

    for (const auto& type : checkList) {
        if (argType == type) {
            return true;
        }
    }
    return false;
}

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

bool ConvertResourceColor(const EcmaVM* vm, const Local<JSValueRef>& item, OHOS::Ace::NG::Gradient& gradient,
    size_t index, std::vector<RefPtr<ResourceObject>>& resObjs, const NodeInfo& nodeInfo)
{
    Color color;
    RefPtr<ResourceObject> resObj;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, item, color, resObj, nodeInfo)) {
        return false;
    }
    resObjs.push_back(resObj);
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

bool ConvertGradientColor(const EcmaVM* vm, const Local<JSValueRef>& itemParam, OHOS::Ace::NG::Gradient& gradient,
    size_t index, std::vector<RefPtr<ResourceObject>>& resObjs, const NodeInfo& nodeInfo)
{
    if (!itemParam->IsObject(vm)) {
        return ConvertResourceColor(vm, itemParam, gradient, index, resObjs, nodeInfo);
    }
    Framework::JSLinearGradient* jsLinearGradient =
        static_cast<Framework::JSLinearGradient*>(itemParam->ToObject(vm)->GetNativePointerField(vm, 0));
    if (!jsLinearGradient) {
        return ConvertResourceColor(vm, itemParam, gradient, index, resObjs, nodeInfo);
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

void SetTrackShadowObject(ArkUINodeHandle nativeNode, std::vector<OHOS::Ace::NG::Gradient>& shadowColors,
    const struct ArkUIDatePanelTrackShadow& trackShadow, const struct ArkUIShadowOptionsResource& shadowOptionsRes)
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
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_VOID(nodeModifiers);
    nodeModifiers->getDataPanelModifier()->setTrackShadowPtr(nativeNode, &gradient, &trackShadow, &shadowOptionsRes);
}
} // namespace

void DataPanelBridge::RegisterDataPanelAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    const char* functionNames[] = { "create", "setDataPanelValueColors", "resetDataPanelValueColors",
        "setDataPanelTrackShadow", "resetDataPanelTrackShadow", "setCloseEffect", "resetCloseEffect",
        "setDataPanelTrackBackgroundColor", "resetDataPanelTrackBackgroundColor",
        "setDataPanelStrokeWidth", "resetDataPanelStrokeWidth", "setContentModifierBuilder",
        "setDataPanelBorderRadius" };

    Local<JSValueRef> funcValues[] = {
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), DataPanelBridge::CreateDataPanel),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), DataPanelBridge::SetValueColors),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), DataPanelBridge::ResetValueColors),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), DataPanelBridge::SetTrackShadow),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), DataPanelBridge::ResetTrackShadow),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), DataPanelBridge::SetCloseEffect),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), DataPanelBridge::ResetCloseEffect),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), DataPanelBridge::SetDataPanelTrackBackgroundColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), DataPanelBridge::ResetDataPanelTrackBackgroundColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), DataPanelBridge::SetDataPanelStrokeWidth),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), DataPanelBridge::ResetDataPanelStrokeWidth),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), DataPanelBridge::SetContentModifierBuilder),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), DataPanelBridge::SetDataPanelBorderRadius),

    };

    auto dataPanel = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(functionNames), functionNames, funcValues);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "dataPanel"), dataPanel);
}

ArkUINativeModuleValue DataPanelBridge::CreateDataPanel(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    float datapanelMax = DEFAULT_DATAPANEL_MAX;
    datapanelMax = static_cast<float>(secondArg->ToNumber(vm)->Value());
    auto jsValue = panda::Local<panda::ArrayRef>(firstArg);
    if (!jsValue->IsArray(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    std::vector<double> dateValues;
    double dataSum = 0.0;
    size_t length = ArkTSUtils::GetArrayLength(vm, jsValue);
    size_t count = std::min(length, MAX_COUNT);
    auto nodeModifiers = GetArkUINodeModifiers();
    for (size_t i = 0; i < count; ++i) {
        Local<JSValueRef> item = panda::ArrayRef::GetValueAt(vm, jsValue, static_cast<uint32_t>(i));
        if (!item->IsNumber()) {
            continue;
        }
        double value = static_cast<double>(item->ToNumber(vm)->Value());
        if (LessOrEqual(value, 0.0)) {
            value = 0.0;
        }
        if (GreatOrEqual(dataSum+value, datapanelMax) && GreatNotEqual(datapanelMax, 0)) {
            dateValues.emplace_back(datapanelMax - dataSum);
            break;
        }
        dataSum += value;
        dateValues.emplace_back(value);
    }
    if (LessOrEqual(datapanelMax, 0.0)) {
        datapanelMax = dataSum;
    }
    size_t dataPanelType = 0;
    int32_t type = static_cast<int32_t>(ChartType::RAINBOW);
    if (thirdArg->IsNumber()) {
        type = static_cast<int32_t>(thirdArg->ToNumber(vm)->Value());
    }
    if (type == static_cast<int32_t>(ChartType::LINE)) {
        dataPanelType = 1;
    }
    nodeModifiers->getDataPanelModifier()->createModel(dateValues, datapanelMax, dataPanelType);
    Framework::JSDataPanelTheme::ApplyTheme();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DataPanelBridge::SetValueColors(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> colors = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    std::vector<OHOS::Ace::NG::Gradient> shadowColors;
    std::vector<RefPtr<ResourceObject>> colorVectorResObj;
    bool isJsView = IsJsView(firstArg, vm);
    if (!colors.IsEmpty() && colors->IsArray(vm)) {
        auto colorsArray = panda::CopyableGlobal<panda::ArrayRef>(vm, colors);
        if (!isJsView) {
            if (colorsArray.IsEmpty() || colorsArray->IsUndefined() || colorsArray->IsNull()) {
                return panda::JSValueRef::Undefined(vm);
            }
        }
        for (size_t i = 0; i < colorsArray->Length(vm); ++i) {
            auto item = colorsArray->GetValueAt(vm, colors, i);
            OHOS::Ace::NG::Gradient gradient;
            auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
            if (!ConvertGradientColor(vm, item, gradient, i, colorVectorResObj, nodeInfo)) {
                shadowColors.clear();
                ConvertThemeColor(shadowColors);
                break;
            }
            shadowColors.emplace_back(gradient);
        }
    } else {
        ConvertThemeColor(shadowColors);
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
            allOffset.emplace_back(ArkUILengthType {
                .number = static_cast<ArkUI_Float32>(shadowColors[i].GetColors()[j].GetDimension().Value()),
                .unit = static_cast<int8_t>(shadowColors[i].GetColors()[j].GetDimension().Unit()) });
        }
    }
    gradient.color = &(*allColor.begin());
    gradient.offset = &(*allOffset.begin());
    gradient.gradientLength = linearLength.get();
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));

    nodeModifiers->getDataPanelModifier()->setValueColorsPtr(
        nativeNode, &gradient, static_cast<void*>(&colorVectorResObj));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DataPanelBridge::ResetValueColors(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getDataPanelModifier()->resetValueColors(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

void ParseTrackShadowProperties(EcmaVM* vm, const Local<panda::ObjectRef>& obj, ArkUIDatePanelTrackShadow& trackShadow,
    ArkUIShadowOptionsResource& shadowOptionsRes, RefPtr<DataPanelTheme>& theme)
{
    auto jsRadius = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "radius"));
    auto jsOffsetX = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "offsetX"));
    auto jsOffsetY = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "offsetY"));

    RefPtr<ResourceObject> radiusResObj;
    if (!ArkTSUtils::ParseJsDouble(vm, jsRadius, trackShadow.radius, radiusResObj) || NonPositive(trackShadow.radius)) {
        trackShadow.radius = theme->GetTrackShadowRadius().ConvertToVp();
    }

    RefPtr<ResourceObject> offsetXResObj;
    if (!ArkTSUtils::ParseJsDouble(vm, jsOffsetX, trackShadow.offsetX, offsetXResObj)) {
        trackShadow.offsetX = theme->GetTrackShadowOffsetX().ConvertToVp();
    }

    RefPtr<ResourceObject> offsetYResObj;
    if (!ArkTSUtils::ParseJsDouble(vm, jsOffsetY, trackShadow.offsetY, offsetYResObj)) {
        trackShadow.offsetY = theme->GetTrackShadowOffsetY().ConvertToVp();
    }

    if (SystemProperties::ConfigChangePerform()) {
        shadowOptionsRes.radiusRawPtr = AceType::RawPtr(radiusResObj);
        if (radiusResObj != nullptr) {
            radiusResObj->IncRefCount();
        }
        shadowOptionsRes.offsetXRawPtr = AceType::RawPtr(offsetXResObj);
        if (offsetXResObj != nullptr) {
            offsetXResObj->IncRefCount();
        }
        shadowOptionsRes.offsetYRawPtr = AceType::RawPtr(offsetYResObj);
        if (offsetYResObj != nullptr) {
            offsetYResObj->IncRefCount();
        }
    }
}

ArkUINativeModuleValue DataPanelBridge::SetTrackShadow(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (secondArg->IsNull()) {
        nodeModifiers->getDataPanelModifier()->setNullTrackShadow(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    if (!secondArg->IsObject(vm)) {
        nodeModifiers->getDataPanelModifier()->resetTrackShadow(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto obj = secondArg->ToObject(vm);
    RefPtr<DataPanelTheme> theme = ArkTSUtils::GetTheme<DataPanelTheme>();
    ArkUIDatePanelTrackShadow trackShadow = { .radius = 0.0, .offsetX = 0.0, .offsetY = 0.0 };
    ArkUIShadowOptionsResource shadowOptionsRes;
    ParseTrackShadowProperties(vm, obj, trackShadow, shadowOptionsRes, theme);

    std::vector<OHOS::Ace::NG::Gradient> shadowColors;
    auto colors = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "colors"));
    std::vector<RefPtr<ResourceObject>> colorVectorResObj;
    ConvertThemeColor(shadowColors);
    if (!colors.IsEmpty() && colors->IsArray(vm)) {
        shadowColors.clear();
        bool isJsView = IsJsView(firstArg, vm);
        auto array = panda::Local<panda::ArrayRef>(colors);
        if (!isJsView) {
            if (array.IsEmpty() || array->IsUndefined() || array->IsNull()) {
                SetTrackShadowObject(nativeNode, shadowColors, trackShadow, shadowOptionsRes);
                return panda::JSValueRef::Undefined(vm);
            }
        }
        for (size_t i = 0; i < ArkTSUtils::GetArrayLength(vm, array); ++i) {
            auto item = array->GetValueAt(vm, colors, i);
            OHOS::Ace::NG::Gradient gradient;
            auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
            if (!ConvertGradientColor(vm, item, gradient, i, colorVectorResObj, nodeInfo)) {
                shadowColors.clear();
                ConvertThemeColor(shadowColors);
                break;
            }
            shadowColors.emplace_back(gradient);
        }
        if (!isJsView) {
            trackShadow.colorRawPtr = colorVectorResObj.empty() ? nullptr : static_cast<void*>(&colorVectorResObj);
        }
    }
    SetTrackShadowObject(nativeNode, shadowColors, trackShadow, shadowOptionsRes);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DataPanelBridge::ResetTrackShadow(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getDataPanelModifier()->resetTrackShadow(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue DataPanelBridge::SetCloseEffect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    if (!secondArg->IsBoolean()) {
        nodeModifiers->getDataPanelModifier()->resetCloseEffect(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    bool boolValue = secondArg->ToBoolean(vm)->Value();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getDataPanelModifier()->setCloseEffect(nativeNode, boolValue);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DataPanelBridge::ResetCloseEffect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(nativeNodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getDataPanelModifier()->resetCloseEffect(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DataPanelBridge::SetDataPanelTrackBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
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
        RefPtr<DataPanelTheme> theme = ArkTSUtils::GetTheme<DataPanelTheme>();
        color = theme->GetBackgroundColor();
    }

    auto colorRawPtr = AceType::RawPtr(colorResObj);
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getDataPanelModifier()->setDataPanelTrackBackgroundColorPtr(
        nativeNode, color.GetValue(), colorRawPtr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DataPanelBridge::ResetDataPanelTrackBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(nativeNodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getDataPanelModifier()->resetDataPanelTrackBackgroundColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DataPanelBridge::SetDataPanelStrokeWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> jsValue = runtimeCallInfo->GetCallArgRef(1);

    RefPtr<DataPanelTheme> theme = ArkTSUtils::GetTheme<DataPanelTheme>();
    CalcDimension strokeWidth;
    RefPtr<ResourceObject> strokeWidthResObj;

    if (!ArkTSUtils::ParseJsDimensionVpNG(vm, jsValue, strokeWidth, strokeWidthResObj)) {
        strokeWidth = theme->GetThickness();
    }

    if (jsValue->IsString(vm) && (jsValue->ToString(vm)->ToString(vm).empty() ||
        !StringUtils::StringToDimensionWithUnitNG(
        jsValue->ToString(vm)->ToString(vm), strokeWidth))) {
        strokeWidth = theme->GetThickness();
    }

    if (strokeWidth.IsNegative() || strokeWidth.Unit() == DimensionUnit::PERCENT) {
        strokeWidth = theme->GetThickness();
    }
    auto strokeWidthRawPtr = AceType::RawPtr(strokeWidthResObj);
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getDataPanelModifier()->setDataPanelStrokeWidthPtr(
        nativeNode, strokeWidth.Value(), static_cast<int32_t>(strokeWidth.Unit()), strokeWidthRawPtr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DataPanelBridge::ResetDataPanelStrokeWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getDataPanelModifier()->resetDataPanelStrokeWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DataPanelBridge::SetDataPanelBorderRadius(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));

    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        CalcDimension borderRadius;
        RefPtr<ResourceObject> resObj;
        auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
        if (ArkTSUtils::ParseJsDimensionVpNG(vm, secondArg, borderRadius, resObj)) {
            ViewAbstractModel::GetInstance()->SetBorderRadius(borderRadius);
        }
        return panda::JSValueRef::Undefined(vm);
    }

    std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::STRING, JSCallbackInfoType::NUMBER,
        JSCallbackInfoType::OBJECT };

    if (!CheckJSCallbackInfo("SetDataPanelBorderRadius", secondArg, checkList, vm)) {
        RefPtr<DataPanelTheme> theme = ArkTSUtils::GetTheme<DataPanelTheme>();
        CHECK_NULL_RETURN(theme, panda::JSValueRef::Undefined(vm));
        int32_t dataPanelType = 0;
        if (dataPanelType != TYPE_CYCLE) {
            ViewAbstractModel::GetInstance()->SetBorderRadius(theme->GetDefaultBorderRadius());
        } else {
            ViewAbstractModel::GetInstance()->SetBorderRadius(Dimension {});
        }
        return panda::JSValueRef::Undefined(vm);
    }
    CalcDimension borderRadius;
    RefPtr<ResourceObject> resObj;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (ArkTSUtils::ParseJsDimensionVpNG(vm, secondArg, borderRadius, resObj)) {
        ViewAbstractModel::GetInstance()->SetBorderRadius(borderRadius);
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DataPanelBridge::SetContentModifierBuilder(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    if (!secondArg->IsObject(vm)) {
        DataPanelModelNG::SetBuilderFunc(frameNode, nullptr);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::CopyableGlobal<panda::ObjectRef> globalObj(vm, secondArg);
    auto containerId = Container::CurrentId();
    bool isJsView = IsJsView(firstArg, vm);
    auto weakFrameNode = AceType::WeakClaim(frameNode);
    DataPanelModelNG::SetBuilderFunc(frameNode,
        [vm, weakFrameNode, globalObj = std::move(globalObj), containerId, isJsView](
            DataPanelConfiguration config) -> RefPtr<FrameNode> {
            panda::LocalScope pandaScope(vm);
            ContainerScope scope(containerId);
            CHECK_NULL_RETURN(Container::Current(), nullptr);
            CHECK_NULL_RETURN(Container::Current()->GetFrontend(), nullptr);
            auto frameNodeFromWeak = AceType::DynamicCast<FrameNode>(weakFrameNode.Upgrade());
            CHECK_NULL_RETURN(frameNodeFromWeak, nullptr);
            auto context = NapiValueToLocalValue(Container::Current()->GetFrontend()->GetContextValue());
            auto obj = panda::ObjectRef::New(vm);
            auto valueArray = panda::ArrayRef::New(vm, config.values_.size());
            for (uint32_t i = 0; i < config.values_.size(); ++i) {
                panda::ArrayRef::SetValueAt(vm, valueArray, i, panda::NumberRef::New(vm, config.values_[i]));
            }
            obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "values"), valueArray);
            obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "maxValue"), panda::NumberRef::New(vm, config.maxValue_));
            obj->SetNativePointerFieldCount(vm, 1);
            obj->SetNativePointerField(vm, 0, static_cast<void*>(AceType::RawPtr(frameNodeFromWeak)));
            panda::Local<panda::JSValueRef> params[NUM_2] = { context, obj };
            panda::TryCatch trycatch(vm);
            auto jsObject = globalObj.ToLocal();
            auto makeFunc = jsObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "makeContentModifierNode"));
            if (!makeFunc->IsFunction(vm)) { return nullptr; }
            panda::Local<panda::FunctionRef> func = makeFunc;
            auto result = func->Call(vm, jsObject, params, 2);
            if (isJsView) {
                ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
            } else {
                panda::JSNApi::ExecutePendingJob(vm);
            }
            if (result.IsEmpty() || trycatch.HasCaught() || !result->IsObject(vm)) { return nullptr; }
            auto resultObj = result->ToObject(vm);
            panda::Local<panda::JSValueRef> nodeptr = resultObj->Get(vm,
                panda::StringRef::NewFromUtf8(vm, DATA_PANEL_NODEPTR_OF_UINODE));
            if (nodeptr.IsEmpty() || nodeptr->IsUndefined() || nodeptr->IsNull()) { return nullptr; }
            auto* node = nodeptr->ToNativePointer(vm)->Value();
            auto* frameNode = reinterpret_cast<FrameNode*>(node);
            CHECK_NULL_RETURN(frameNode, nullptr);
            return AceType::Claim(frameNode);
        });
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
