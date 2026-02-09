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

#include "native_engine/impl/ark/ark_native_engine.h"

#include "base/geometry/dimension.h"
#include "bridge/declarative_frontend/ark_theme/theme_apply/js_data_panel_theme.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "bridge/declarative_frontend/jsview/js_linear_gradient.h"
#include "core/common/resource/resource_parse_utils.h"
#include "core/components/common/properties/color.h"
#include "core/components/data_panel/data_panel_theme.h"
#include "core/components/divider/divider_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/data_panel/data_panel_model_ng.h"
#include "core/components_ng/pattern/gauge/gauge_paint_property.h"
#include "frameworks/core/components_ng/base/view_abstract_model.h"

namespace {
const char* DATA_PANEL_NODEPTR_OF_UINODE = "nodePtr_";
} // namespace
namespace OHOS::Ace::NG {
uint32_t DataPanelBridge::dataPanelType_ = 0;
namespace {
constexpr int32_t NUM_0 = 0;
constexpr int32_t NUM_1 = 1;
constexpr int32_t NUM_2 = 2;
constexpr size_t MAX_COUNT = 9;
constexpr int32_t DEFAULT_TYPE = 4;
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

bool CheckJSCallbackInfo(EcmaVM* vm, const std::string& callerName, const Local<JSValueRef>& tmpInfo,
    std::vector<JSCallbackInfoType>& infoTypes)
{
    bool typeVerified = false;
    std::string unrecognizedType;
    for (const auto& infoType : infoTypes) {
        switch (infoType) {
            case JSCallbackInfoType::STRING:
                if (tmpInfo->IsString(vm)) {
                    typeVerified = true;
                } else {
                    unrecognizedType += "string|";
                }
                break;
            case JSCallbackInfoType::NUMBER:
                if (tmpInfo->IsNumber()) {
                    typeVerified = true;
                } else {
                    unrecognizedType += "number|";
                }
                break;
            case JSCallbackInfoType::OBJECT:
                if (tmpInfo->IsObject(vm)) {
                    typeVerified = true;
                } else {
                    unrecognizedType += "object|";
                }
                break;
            case JSCallbackInfoType::FUNCTION:
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

NG::BorderRadiusProperty GetLocalizedBorderRadius(const std::optional<Dimension>& radiusTopStart,
    const std::optional<Dimension>& radiusTopEnd, const std::optional<Dimension>& radiusBottomStart,
    const std::optional<Dimension>& radiusBottomEnd)
{
    NG::BorderRadiusProperty borderRadius;
    borderRadius.radiusTopStart = radiusTopStart;
    borderRadius.radiusTopEnd = radiusTopEnd;
    borderRadius.radiusBottomStart = radiusBottomStart;
    borderRadius.radiusBottomEnd = radiusBottomEnd;
    borderRadius.multiValued = true;
    return borderRadius;
}

void ParseBorderRadius(EcmaVM* vm, const Local<JSValueRef>& args)
{
    CalcDimension borderRadius;
    RefPtr<ResourceObject> borderRadiusResObj;
    if (ArkTSUtils::ParseJsDimensionVpNG(vm, args, borderRadius, borderRadiusResObj)) {
        if (SystemProperties::ConfigChangePerform() && borderRadiusResObj) {
            ViewAbstractModel::GetInstance()->SetBorderRadius(borderRadiusResObj);
        } else {
            ViewAbstractModel::GetInstance()->SetBorderRadius(borderRadius);
        }
    } else if (args->IsObject(vm)) {
        auto paramObject = args->ToObject(vm);
        BorderRadiusOption borderRadiusOption;
        if (ArkTSUtils::ParseAllBorderRadiuses(vm, paramObject, borderRadiusOption)) {
            ViewAbstractModel::GetInstance()->SetBorderRadius(
                GetLocalizedBorderRadius(borderRadiusOption.topLeft, borderRadiusOption.topRight,
                    borderRadiusOption.bottomLeft, borderRadiusOption.bottomRight));
            return;
        }
        CalcDimension topLeft = borderRadiusOption.topLeft;
        CalcDimension topRight = borderRadiusOption.topRight;
        CalcDimension bottomLeft = borderRadiusOption.bottomLeft;
        CalcDimension bottomRight = borderRadiusOption.bottomRight;
        if (SystemProperties::ConfigChangePerform()) {
            NG::BorderRadiusProperty borderRadius;
            RefPtr<ResourceObject> topLeftResObj;
            RefPtr<ResourceObject> topRightResObj;
            RefPtr<ResourceObject> bottomLeftResObj;
            RefPtr<ResourceObject> bottomRightResObj;
            ArkTSUtils::GetBorderRadiusResObj(vm, "topLeft", paramObject, topLeft, topLeftResObj);
            ArkTSUtils::GetBorderRadiusResObj(vm, "topRight", paramObject, topRight, topRightResObj);
            ArkTSUtils::GetBorderRadiusResObj(vm, "bottomLeft", paramObject, bottomLeft, bottomLeftResObj);
            ArkTSUtils::GetBorderRadiusResObj(vm, "bottomRight", paramObject, bottomRight, bottomRightResObj);
            borderRadius.radiusTopLeft = topLeft;
            borderRadius.radiusTopRight = topRight;
            borderRadius.radiusBottomLeft = bottomLeft;
            borderRadius.radiusBottomRight = bottomRight;
            borderRadius.multiValued = true;
            ArkTSUtils::ParseAllBorderRadiusesResObj(
                borderRadius, topLeftResObj, topRightResObj, bottomLeftResObj, bottomRightResObj);
            ViewAbstractModel::GetInstance()->SetBorderRadius(borderRadius);
        } else {
            ViewAbstractModel::GetInstance()->SetBorderRadius(topLeft, topRight, bottomLeft, bottomRight);
        }
    }
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

void ParseGradientColor(NG::Gradient& gradient, RefPtr<ResourceObject>& colorResObj, Color& color, int32_t& indx)
{
    ArkTSUtils::CompleteResourceObjectFromColor(colorResObj, color, true);
    auto&& updateFunc = [indx](const RefPtr<ResourceObject>& colorResObj, NG::Gradient& gradient) {
        std::vector<NG::GradientColor> colorVector = gradient.GetColors();
        int32_t colorLength = static_cast<int32_t>(colorVector.size());
        gradient.ClearColors();
        for (int32_t index = 0; index < colorLength; index++) {
            NG::GradientColor gradColor = colorVector[index];
            if (index == indx) {
                Color color;
                ResourceParseUtils::ParseResColor(colorResObj, color);
                gradColor.SetLinearColor(LinearColor(color));
            }
            gradient.AddColor(gradColor);
        }
    };
    std::string key = "LinearGradient.gradient.color" + std::to_string(indx);
    gradient.AddResource(key, colorResObj, std::move(updateFunc));
}

void ParseGradientOffset(NG::Gradient& gradient, RefPtr<ResourceObject>& offsetResObj, int32_t& indx)
{
    CHECK_NULL_VOID(offsetResObj);
    auto&& updateFunc = [indx](const RefPtr<ResourceObject>& offsetResObj, NG::Gradient& gradient) {
        std::vector<NG::GradientColor> colorVector = gradient.GetColors();
        int32_t colorLength = static_cast<int32_t>(colorVector.size());
        gradient.ClearColors();
        for (int32_t index = 0; index < colorLength; index++) {
            NG::GradientColor gradColor = colorVector[index];
            if (index == indx) {
                CalcDimension offset;
                ResourceParseUtils::ParseResDimensionVp(offsetResObj, offset);
                gradColor.SetDimension(offset);
            }
            gradient.AddColor(gradColor);
        }
    };
    std::string key = "LinearGradient.gradient.offset" + std::to_string(indx);
    gradient.AddResource(key, offsetResObj, std::move(updateFunc));
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
    int32_t indexStart = 0;
    ParseGradientColor(gradient, resObj, color, indexStart);
    OHOS::Ace::NG::GradientColor gradientColorEnd;
    gradientColorEnd.SetLinearColor(LinearColor(color));
    gradientColorEnd.SetDimension(Dimension(1.0));
    gradient.AddColor(gradientColorEnd);
    int32_t indexEnd = 1;
    ParseGradientColor(gradient, resObj, color, indexEnd);
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
    auto jsGradient = jsLinearGradient->GetGradient();
    auto jsGradientResObj = jsLinearGradient->GetGradientResObj();

    for (size_t i = 0; i < colorLength; i++) {
        NG::GradientColor gradientColor;
        Color color = jsGradient.at(i).first;
        CalcDimension offset = jsGradient.at(i).second;
        if (SystemProperties::ConfigChangePerform()) {
            int32_t indx = static_cast<int32_t>(i);
            if (jsGradientResObj.at(i).first) {
                ResourceParseUtils::ParseResColor(jsGradientResObj.at(i).first, color);
            }
            ParseGradientColor(gradient, jsGradientResObj.at(i).first, color, indx);
            if (jsGradientResObj.at(i).second) {
                ResourceParseUtils::ParseResDimensionVp(jsGradientResObj.at(i).second, offset);
                ParseGradientOffset(gradient, jsGradientResObj.at(i).second, indx);
            }
        }
        if (Negative(offset.ConvertToVp())) {
            offset = Dimension(0.0, DimensionUnit::VP);
        }

        if (GreatNotEqual(offset.ConvertToVp(), 1.0)) {
            offset = Dimension(1.0, DimensionUnit::VP);
        }
        gradientColor.SetLinearColor(LinearColor(color));
        gradientColor.SetDimension(offset);
        gradient.AddColor(gradientColor);
    }
    return true;
}

void SetRenderStrategy(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_VOID(vm);
    if (runtimeCallInfo->GetArgsNumber() < NUM_2) {
        return;
    }
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    if (!secondArg->IsNumber()) {
        ViewAbstractModel::GetInstance()->SetRenderStrategy(RenderStrategy::FAST);
        return;
    }
    ViewAbstractModel::GetInstance()->SetRenderStrategy(static_cast<RenderStrategy>(secondArg->ToNumber(vm)->Value()));
    return;
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
    if (!firstArg->IsObject(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto paramObject = firstArg->ToObject(vm);
    auto maxArg = paramObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "max"));
    double max = maxArg->IsNumber() ? maxArg->ToNumber(vm)->Value() : 100.0;
    auto valuesArg = paramObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "values"));
    if (!valuesArg->IsArray(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto jsArray = panda::Local<panda::ArrayRef>(valuesArg);
    size_t length = ArkTSUtils::GetArrayLength(vm, jsArray);
    std::vector<double> dataValues;
    double dataSum = 0.0;
    size_t count = std::min(length, MAX_COUNT);
    for (size_t i = 0; i < count; ++i) {
        auto item = jsArray->GetValueAt(vm, jsArray, i);
        if (!item->IsNumber()) {
            continue;
        }
        double value = item->ToNumber(vm)->Value();
        if (LessOrEqual(value, 0.0)) {
            value = 0.0;
        }
        // if the sum of values exceeds the maximum value, only fill in to the maximum value
        if (GreatOrEqual(dataSum + value, max) && GreatNotEqual(max, 0)) {
            dataValues.emplace_back(max - dataSum);
            break;
        }
        dataSum += value;
        dataValues.emplace_back(value);
    }
    if (LessOrEqual(max, 0.0)) {
        max = dataSum;
    }
    size_t dataPanelType = 0;
    auto jsType = paramObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "type"));
    int32_t type = jsType->IsNumber() ? jsType->ToNumber(vm)->Value() : DEFAULT_TYPE ;
    if (type == static_cast<int32_t>(ChartType::LINE)) {
        dataPanelType = 1;
    }
    dataPanelType_ = dataPanelType;
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getDataPanelModifier()->createModel(dataValues, max, dataPanelType);
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

    std::vector<OHOS::Ace::NG::Gradient> valueColors;
    std::vector<RefPtr<ResourceObject>> colorVectorResObj;
    bool isSetByUser = true;
    bool isJsView = IsJsView(firstArg, vm);
    if (!colors.IsEmpty() && colors->IsArray(vm)) {
        auto colorsArray = panda::Local<panda::ArrayRef>(colors);
        if (!isJsView) {
            if (colorsArray.IsEmpty() || colorsArray->IsUndefined() || colorsArray->IsNull()) {
                return panda::JSValueRef::Undefined(vm);
            }
        }
        for (size_t i = 0; i < ArkTSUtils::GetArrayLength(vm, colorsArray); ++i) {
            auto item = colorsArray->GetValueAt(vm, colors, i);
            OHOS::Ace::NG::Gradient gradient;
            auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
            if (!ConvertGradientColor(vm, item, gradient, i, colorVectorResObj, nodeInfo)) {
                isSetByUser = false;
                valueColors.clear();
                ConvertThemeColor(valueColors);
                break;
            }
            valueColors.emplace_back(gradient);
        }
    } else {
        ConvertThemeColor(valueColors);
        isSetByUser = false;
    }
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getDataPanelModifier()->setValueColorsNew(
        nativeNode, static_cast<void*>(&valueColors), valueColors.size(), isSetByUser);
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
                trackShadow.colorRawPtr = static_cast<void*>(&shadowColors);
                nodeModifiers->getDataPanelModifier()->setTrackShadowNew(
                    nativeNode, shadowColors.size(), &trackShadow, &shadowOptionsRes);
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
    }

    trackShadow.colorRawPtr = static_cast<void*>(&shadowColors);
    nodeModifiers->getDataPanelModifier()->setTrackShadowNew(
        nativeNode, shadowColors.size(), &trackShadow, &shadowOptionsRes);
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
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    bool isSetByUser = true;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color, colorResObj, nodeInfo)) {
        RefPtr<DataPanelTheme> theme = ArkTSUtils::GetTheme<DataPanelTheme>();
        color = theme->GetBackgroundColor();
        isSetByUser = false;
    }

    auto colorRawPtr = AceType::RawPtr(colorResObj);
    nodeModifiers->getDataPanelModifier()->setDataPanelTrackBackgroundColorNew(
        nativeNode, color.GetValue(), colorRawPtr, isSetByUser);
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

    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    bool isSetByUser = true;
    if (!ArkTSUtils::ParseJsDimensionVpNG(vm, jsValue, strokeWidth, strokeWidthResObj)) {
        strokeWidth = theme->GetThickness();
        isSetByUser = false;
    }

    if (jsValue->IsString(vm) && (jsValue->ToString(vm)->ToString(vm).empty() ||
        !StringUtils::StringToDimensionWithUnitNG(jsValue->ToString(vm)->ToString(vm), strokeWidth))) {
        strokeWidth = theme->GetThickness();
        isSetByUser = false;
    }

    if (strokeWidth.IsNegative() || strokeWidth.Unit() == DimensionUnit::PERCENT) {
        strokeWidth = theme->GetThickness();
        isSetByUser = false;
    }
    auto strokeWidthRawPtr = AceType::RawPtr(strokeWidthResObj);
    nodeModifiers->getDataPanelModifier()->setDataPanelStrokeWidthNew(
        nativeNode, strokeWidth.Value(), static_cast<int32_t>(strokeWidth.Unit()), strokeWidthRawPtr, isSetByUser);
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
    ArkUINodeHandle nativeNode = nullptr;
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        CalcDimension borderRadius;
        RefPtr<ResourceObject> resObj;
        auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
        if (ArkTSUtils::ParseJsDimensionVpNG(vm, firstArg, borderRadius, resObj)) {
            ViewAbstractModel::GetInstance()->SetBorderRadius(borderRadius);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    SetRenderStrategy(runtimeCallInfo);
    std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::STRING, JSCallbackInfoType::NUMBER,
        JSCallbackInfoType::OBJECT };
    if (!CheckJSCallbackInfo(vm, "JsBorderRadius", firstArg, checkList)) {
        if (dataPanelType_ != TYPE_CYCLE) {
            RefPtr<DataPanelTheme> theme = GetTheme<DataPanelTheme>();
            CHECK_NULL_RETURN(theme, panda::JSValueRef::Undefined(vm));
            ViewAbstractModel::GetInstance()->SetBorderRadius(theme->GetDefaultBorderRadius());
        } else {
            ViewAbstractModel::GetInstance()->SetBorderRadius(Dimension {});
        }
        return panda::JSValueRef::Undefined(vm);
    }
    ParseBorderRadius(vm, firstArg);
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
