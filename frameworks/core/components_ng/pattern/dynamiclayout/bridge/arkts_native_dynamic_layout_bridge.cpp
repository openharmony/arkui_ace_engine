/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "base/geometry/dimension.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_utils_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "core/components_ng/pattern/dynamiclayout/algorithm_param_base.h"
#include "core/components_ng/layout/utils.h"
#include "core/components_ng/pattern/dynamiclayout/bridge/arkts_native_dynamic_layout_bridge.h"
#include "core/components/common/layout/constants.h"

namespace OHOS::Ace::NG {
namespace {
constexpr inline int32_t COLUMN_LAYOUT = 2;
constexpr inline int32_t ROW_LAYOUT = 3;
constexpr inline int32_t STACK_LAYOUT = 4;
constexpr inline int32_t CUSTOM_LAYOUT = 1;
constexpr inline int32_t GRID_LAYOUT = 5;
constexpr inline int32_t PARAMS_NUM_TWO = 2;

using ParsingParamFunc = std::function<void(EcmaVM*, const Local<panda::ObjectRef>&, RefPtr<AlgorithmParamBase>&)>;

void ParseLinearCrossAxisAlignment(EcmaVM* vm, const Local<JSValueRef>& alignItemVal, FlexAlign &result)
{
    if (alignItemVal->IsNumber()) {
        auto value = alignItemVal->Int32Value(vm);
        if ((value == static_cast<int32_t>(FlexAlign::FLEX_START)) ||
            (value == static_cast<int32_t>(FlexAlign::FLEX_END)) ||
            (value == static_cast<int32_t>(FlexAlign::CENTER)) ||
            (value == static_cast<int32_t>(FlexAlign::STRETCH))) {
            result = static_cast<FlexAlign>(value);
        }
    }
}

void ParseLinearMainAxisAlignment(EcmaVM* vm, const Local<JSValueRef>& justifyVal, FlexAlign &result)
{
    if (justifyVal->IsNumber()) {
        auto value = justifyVal->Int32Value(vm);
        if ((value == static_cast<int32_t>(FlexAlign::FLEX_START)) ||
            (value == static_cast<int32_t>(FlexAlign::FLEX_END)) ||
            (value == static_cast<int32_t>(FlexAlign::CENTER)) ||
            (value == static_cast<int32_t>(FlexAlign::SPACE_BETWEEN)) ||
            (value == static_cast<int32_t>(FlexAlign::SPACE_AROUND)) ||
            (value == static_cast<int32_t>(FlexAlign::SPACE_EVENLY))) {
            result = static_cast<FlexAlign>(value);
        }
    }
}

void ParseSpace(EcmaVM* vm, const Local<JSValueRef>& spaceVal, CalcDimension &result)
{
    if (spaceVal->IsObject(vm) && (!ArkTSUtils::ParseJsLengthMetrics(vm, spaceVal, result) || result.IsNegative())) {
        result = CalcDimension(0);
    }
}

void ParseAlignContent(EcmaVM* vm, const Local<JSValueRef>& alignVal, Alignment &result)
{
    if (alignVal->IsString(vm)) {
        auto value = alignVal->ToString(vm)->ToString(vm);
        Alignment alignContent = NG::ConvertStringToAlignment(value);
        result = alignContent;
    }
}

void ParseLinearAlgorithmOption(
    EcmaVM*vm, const Local<panda::ObjectRef>& jsObj, RefPtr<LinearLayoutAlgorithmParam>& params)
{
    auto justifyVal = jsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "justifyContent"));
    auto alignItemVal = jsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "alignItems"));
    auto spaceVal = jsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "space"));
    auto reverseVal = jsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "isReverse"));
    FlexAlign crossAxisAlign = FlexAlign::CENTER;
    FlexAlign justifyContent = FlexAlign::FLEX_START;
    CalcDimension space;
    bool isReverse = false;
    ParseLinearCrossAxisAlignment(vm, alignItemVal, crossAxisAlign);
    ParseLinearMainAxisAlignment(vm, justifyVal, justifyContent);
    ParseSpace(vm, spaceVal, space);
    params->SetSpace(space);
    params->SetMainAxisAlign(justifyContent);
    params->SetCrossAxisAlign(crossAxisAlign);
    if (reverseVal->IsBoolean()) {
        isReverse = reverseVal->ToBoolean(vm)->Value();
    }
    params->SetIsReverse(isReverse);
}

void ParseColumnAlgorithmOption(
    EcmaVM*vm, const Local<panda::ObjectRef>& jsObj, RefPtr<AlgorithmParamBase>& params)
{
    auto linearParams = AceType::MakeRefPtr<LinearLayoutAlgorithmParam>(true);
    ParseLinearAlgorithmOption(vm, jsObj, linearParams);
    params = linearParams;
}

void ParseRowAlgorithmOption(
    EcmaVM*vm, const Local<panda::ObjectRef>& jsObj, RefPtr<AlgorithmParamBase>& params)
{
    auto linearParams = AceType::MakeRefPtr<LinearLayoutAlgorithmParam>(false);
    ParseLinearAlgorithmOption(vm, jsObj, linearParams);
    params = linearParams;
}

void ParseStackAlgorithmOption(EcmaVM*vm, const Local<panda::ObjectRef>& jsObj, RefPtr<AlgorithmParamBase>& params)
{
    auto alignVal = jsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "alignContent"));
    Alignment alignContent = Alignment::CENTER;
    ParseAlignContent(vm, alignVal, alignContent);
    auto stackParams = AceType::MakeRefPtr<StackLayoutAlgorithmParam>();
    stackParams->SetAlignContent(alignContent);
    params = stackParams;
}

PresetFillType ParseFillTypeFromObject(EcmaVM* vm, const Local<panda::ObjectRef>& columnsTemplateObj)
{
    auto fillTypeParam = columnsTemplateObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "fillType"));
    // Return default if fillType is undefined or null
    if (fillTypeParam->IsUndefined() || fillTypeParam->IsNull()) {
        return PresetFillType::BREAKPOINT_DEFAULT;
    }

    // Return default if fillType is not a number
    if (!fillTypeParam->IsNumber()) {
        return PresetFillType::BREAKPOINT_DEFAULT;
    }

    int32_t fillTypeValue = fillTypeParam->Int32Value(vm);
    // Validate range: BREAKPOINT_DEFAULT(0) to BREAKPOINT_SM2MD3LG5(2)
    if (fillTypeValue >= static_cast<int32_t>(PresetFillType::BREAKPOINT_DEFAULT) &&
        fillTypeValue <= static_cast<int32_t>(PresetFillType::BREAKPOINT_SM2MD3LG5)) {
        return static_cast<PresetFillType>(fillTypeValue);
    }

    return PresetFillType::BREAKPOINT_DEFAULT;
}

void ParseGridLayoutOption(EcmaVM*vm, const Local<panda::ObjectRef>& jsObj, RefPtr<AlgorithmParamBase>& params)
{
    auto gridParams = AceType::MakeRefPtr<GridLayoutAlgorithmParam>();

    // Parse columnsTemplate (string | object with fillType)
    auto columnsTemplateVal = jsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "columnsTemplate"));
    if (columnsTemplateVal->IsString(vm)) {
        auto columnsTemplate = columnsTemplateVal->ToString(vm)->ToString(vm);
        gridParams->SetColumnsTemplate(columnsTemplate);
    } else if (columnsTemplateVal->IsObject(vm)) {
        auto columnsTemplateObj = columnsTemplateVal->ToObject(vm);
        auto fillType = ParseFillTypeFromObject(vm, columnsTemplateObj);
        gridParams->SetItemFillPolicy(fillType);
    }

    // Parse rowsGap (CalcDimension)
    auto rowsGapVal = jsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "rowsGap"));
    CalcDimension rowsGap;
    ArkTSUtils::ParseJsLengthMetrics(vm, rowsGapVal, rowsGap);
    gridParams->SetRowsGap(rowsGap);

    // Parse columnsGap (CalcDimension)
    auto columnsGapVal = jsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "columnsGap"));
    CalcDimension columnsGap;
    ArkTSUtils::ParseJsLengthMetrics(vm, columnsGapVal, columnsGap);
    gridParams->SetColumnsGap(columnsGap);

    params = gridParams;
}

struct ExtensionLayoutConstraint {
    int32_t maxWidth { 0 };
    int32_t minWidth { 0 };
    int32_t maxHeight { 0 };
    int32_t minHeight { 0 };
    int32_t parentIdealWidth { 0 };
    int32_t parentIdealHeight { 0 };
};

ExtensionLayoutConstraint CreateExtensionLayoutConstraint(const LayoutConstraintF& layoutConstraintF)
{
    auto maxWidth = floor(layoutConstraintF.maxSize.Width());
    auto maxHeight = floor(layoutConstraintF.maxSize.Height());
    auto minWidth = floor(layoutConstraintF.minSize.Width());
    auto minHeight = floor(layoutConstraintF.minSize.Height());
    if (layoutConstraintF.selfIdealSize.Width().has_value()) {
        maxWidth = floor(layoutConstraintF.selfIdealSize.Width().value());
        minWidth = maxWidth;
    }
    if (layoutConstraintF.selfIdealSize.Height().has_value()) {
        maxHeight = floor(layoutConstraintF.selfIdealSize.Height().value());
        minHeight = maxHeight;
    }
    auto parentIdealWidth = floor(layoutConstraintF.percentReference.Width());
    auto parentIdealHeight = floor(layoutConstraintF.percentReference.Height());
    return { maxWidth, minWidth, maxHeight, minHeight, parentIdealWidth, parentIdealHeight };
}

Local<panda::ObjectRef> GenConstraintObj(EcmaVM* vm, const LayoutConstraintF& parentConstraint)
{
    auto extensionConstraint = CreateExtensionLayoutConstraint(parentConstraint);
    const char* keysOfSize[] = { "height", "width" };
    Local<JSValueRef> valuesOfMaxSize[] = {
        panda::NumberRef::New(vm, extensionConstraint.maxHeight),
        panda::NumberRef::New(vm, extensionConstraint.maxWidth) };
    Local<JSValueRef> valuesOfMinSize[] = {
        panda::NumberRef::New(vm, extensionConstraint.minHeight),
        panda::NumberRef::New(vm, extensionConstraint.minWidth) };
    Local<JSValueRef> valuesOfPercentReference[] = {
        panda::NumberRef::New(vm, extensionConstraint.parentIdealHeight),
        panda::NumberRef::New(vm, extensionConstraint.parentIdealWidth)
    };
    auto maxSizeObj = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keysOfSize), keysOfSize, valuesOfMaxSize);
    auto minSizeObj = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keysOfSize), keysOfSize, valuesOfMinSize);
    auto percentReferenceObj =
        panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keysOfSize), keysOfSize, valuesOfPercentReference);

    Local<JSValueRef> values[] = { maxSizeObj, minSizeObj, percentReferenceObj };
    const char* keys[] = { "maxSize", "minSize", "percentReference" };
    auto constraintObj = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
    return constraintObj;
}

Local<panda::ObjectRef> GetFrameNode(int32_t nodeId, panda::ecmascript::EcmaVM* vm)
{
    auto globalObj = panda::JSNApi::GetGlobalObject(vm);
    auto globalFunc = globalObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "__getFrameNodeByNodeId__"));
    if (!globalFunc->IsFunction(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> getFrameNodeFunc = globalFunc->ToObject(vm);
    auto func = panda::CopyableGlobal(vm, getFrameNodeFunc);
    panda::Local<panda::JSValueRef> params[PARAMS_NUM_TWO] = {
        panda::NumberRef::New(vm, Container::CurrentId()),
        panda::NumberRef::New(vm, nodeId)
    };
    return func->Call(vm, func.ToLocal(), params, PARAMS_NUM_TWO);
}

std::function<void(LayoutWrapper*)> PrepareMeasureSizeFunc(EcmaVM* vm, const Local<panda::ObjectRef>& jsObj)
{
    return [vm = vm, object = NG::JsWeak(panda::CopyableGlobal(vm, jsObj))]
        (LayoutWrapper* layoutWrapper) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        auto obj = object.Lock();
        CHECK_NULL_VOID(!obj.IsEmpty());
        CHECK_NULL_VOID(obj->IsObject(vm));
        auto funcObj = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "onMeasure"));
        CHECK_NULL_VOID(funcObj->IsFunction(vm));
        panda::Local<panda::FunctionRef> func = funcObj;
        auto host = layoutWrapper->GetHostNode();
        CHECK_NULL_VOID(host);
        auto nodeId = host->GetId();
        auto returnPtr = GetFrameNode(nodeId, vm);
        if (returnPtr->IsUndefined()) {
            return;
        }
        const auto& layoutProperty = layoutWrapper->GetLayoutProperty();
        CHECK_NULL_VOID(layoutProperty);
        auto layoutConstraint = layoutProperty->GetLayoutConstraint().value_or(LayoutConstraintF());
        auto constraint = GenConstraintObj(vm, layoutConstraint);
        panda::Local<panda::JSValueRef> measureParams[PARAMS_NUM_TWO] = { returnPtr, constraint };
        func->Call(vm, obj.ToLocal(), measureParams, PARAMS_NUM_TWO);
    };
}

std::function<void(LayoutWrapper*)> PreparePlaceChildrenFunc(EcmaVM* vm, const Local<panda::ObjectRef>& jsObj)
{
    return [vm = vm, object = NG::JsWeak(panda::CopyableGlobal(vm, jsObj))]
        (LayoutWrapper* layoutWrapper) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        auto obj = object.Lock();
        CHECK_NULL_VOID(!obj.IsEmpty());
        CHECK_NULL_VOID(obj->IsObject(vm));
        auto funcObj = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "onLayout"));
        CHECK_NULL_VOID(funcObj->IsFunction(vm));
        panda::Local<panda::FunctionRef> func = funcObj;
        auto host = layoutWrapper->GetHostNode();
        CHECK_NULL_VOID(host);
        auto nodeId = host->GetId();
        auto returnPtr = GetFrameNode(nodeId, vm);
        if (returnPtr->IsUndefined()) {
            return;
        }
        auto rect = layoutWrapper->GetGeometryNode()->GetFrameRect();
        const char* keysOfSize[] = { "x", "y" };
        Local<JSValueRef> valuesOfPosition[] = {
            panda::NumberRef::New(vm, rect.GetX()),
            panda::NumberRef::New(vm, rect.GetY())
        };
        auto positionObj =
            panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keysOfSize), keysOfSize, valuesOfPosition);
        panda::Local<panda::JSValueRef> params[PARAMS_NUM_TWO] = { returnPtr, positionObj };
        func->Call(vm, obj.ToLocal(), params, PARAMS_NUM_TWO);
    };
}

void ParseCustomLayoutAlgorithmOption(
    EcmaVM* vm, const Local<panda::ObjectRef>& jsObj, RefPtr<AlgorithmParamBase>& params)
{
    auto jsMeasureSizeFunc = jsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "onMeasure"));
    auto jsOnLayoutFunc = jsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "onLayout"));
    if (!jsMeasureSizeFunc->IsFunction(vm) && !jsOnLayoutFunc->IsFunction(vm)) {
        return;
    }
    auto customParams = AceType::MakeRefPtr<CustomLayoutAlgorithmParam>();
    if (jsMeasureSizeFunc->IsFunction(vm)) {
        auto onMeasureSizeFunc = PrepareMeasureSizeFunc(vm, jsObj);
        customParams->SetOnMeasureSize(std::move(onMeasureSizeFunc));
    }
    if (jsOnLayoutFunc->IsFunction(vm)) {
        auto onPlaceChildrenFunc = PreparePlaceChildrenFunc(vm, jsObj);
        customParams->SetOnPlaceChildren(std::move(onPlaceChildrenFunc));
    }
    params = customParams;
}

std::unordered_map<int32_t, ParsingParamFunc> parsingParamFuncMap = {
    { COLUMN_LAYOUT, &ParseColumnAlgorithmOption },
    { ROW_LAYOUT, &ParseRowAlgorithmOption },
    { STACK_LAYOUT, &ParseStackAlgorithmOption },
    { CUSTOM_LAYOUT, &ParseCustomLayoutAlgorithmOption},
    { GRID_LAYOUT, &ParseGridLayoutOption},
};

bool ParseLayoutAlgorithmOption(
    EcmaVM* vm, const Local<panda::ObjectRef>& jsObj, RefPtr<AlgorithmParamBase>& params)
{
    auto layoutTypeVal = jsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "layoutType"));
    if (!layoutTypeVal->IsNumber()) {
        return false;
    }
    auto layoutType = layoutTypeVal->Int32Value(vm);
    if (parsingParamFuncMap.find(layoutType) != parsingParamFuncMap.end()) {
        parsingParamFuncMap[layoutType](vm, jsObj, params);
        return true;
    }
    return false;
}
}

void DynamicLayoutBridge::RegisterDynamicLayoutAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    const char* functionNames[] = { "create" };
    Local<JSValueRef> funcValues[] = {
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), DynamicLayoutBridge::CreateDynamicLayout),
    };
    auto dynamicLayout =
        panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(functionNames), functionNames, funcValues);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "dynamiclayout"), dynamicLayout);
}

ArkUINativeModuleValue DynamicLayoutBridge::CreateDynamicLayout(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (!firstArg->IsObject(vm)) {
        nodeModifiers->getDynamicLayoutModifier()->createDynamicLayout(
            nullptr, NG::DynamicLayoutType::DEFAULT_LAYOUT);
        return panda::JSValueRef::Undefined(vm);
    }
    auto algorithmObj = firstArg->ToObject(vm);
    RefPtr<AlgorithmParamBase> params;
    if (ParseLayoutAlgorithmOption(vm, algorithmObj, params) && params) {
        nodeModifiers->getDynamicLayoutModifier()->createDynamicLayout(
            reinterpret_cast<void*>(AceType::RawPtr(params)), static_cast<int32_t>(params->GetDynamicLayoutType()));
    } else {
        nodeModifiers->getDynamicLayoutModifier()->createDynamicLayout(
            reinterpret_cast<void*>(AceType::RawPtr(params)), NG::DynamicLayoutType::DEFAULT_LAYOUT);
    }
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG