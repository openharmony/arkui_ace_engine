/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/grid_row/bridge/arkts_native_grid_row_bridge.h"

#include "base/log/ace_scoring_log.h"
#include "bridge/declarative_frontend/engine/js_execution_scope_defines.h"
#include "bridge/declarative_frontend/engine/jsi/jsi_types.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "core/components/common/layout/constants.h"
#include "core/common/resource/resource_parse_utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/grid_row/grid_row_model_ng.h"
#include "core/components_v2/grid_layout/grid_container_utils.h"
#include "core/interfaces/native/node/node_api.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t MAX_NUMBER_BREAKPOINT = 6;
constexpr int XS = 0;
constexpr int SM = 1;
constexpr int MD = 2;
constexpr int LG = 3;
constexpr int XL = 4;
constexpr int XXL = 5;
constexpr int32_t MAX_NUMBER_GUTTER = 12;
constexpr int X_XS = 0;
constexpr int X_SM = 1;
constexpr int X_MD = 2;
constexpr int X_LG = 3;
constexpr int X_XL = 4;
constexpr int X_XXL = 5;
constexpr int Y_XS = 6;
constexpr int Y_SM = 7;
constexpr int Y_MD = 8;
constexpr int Y_LG = 9;
constexpr int Y_XL = 10;
constexpr int Y_XXL = 11;

Local<JSValueRef> GetObjectProperty(EcmaVM* vm, const Local<panda::ObjectRef>& object, const char* name)
{
    return object->Get(vm, panda::StringRef::NewFromUtf8(vm, name));
}

bool GetNativeNode(ArkUINodeHandle& nativeNode, const Local<JSValueRef>& firstArg, EcmaVM* vm)
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

bool IsJsView(const Local<JSValueRef>& firstArg, EcmaVM* vm)
{
    return firstArg->IsBoolean() && firstArg->ToBoolean(vm)->Value();
}

FrameNode* GetFrameNode(ArkUINodeHandle nativeNode)
{
    return nativeNode ? reinterpret_cast<FrameNode*>(nativeNode)
                      : ViewStackProcessor::GetInstance()->GetMainFrameNode();
}

void ParseColumns(ArkUIRuntimeCallInfo* runtimeCallInfo, EcmaVM* vm, int32_t* containerSizeArray)
{
    Local<JSValueRef> xs = runtimeCallInfo->GetCallArgRef(XS + 1);
    Local<JSValueRef> sm = runtimeCallInfo->GetCallArgRef(SM + 1);
    Local<JSValueRef> md = runtimeCallInfo->GetCallArgRef(MD + 1);
    Local<JSValueRef> lg = runtimeCallInfo->GetCallArgRef(LG + 1);
    Local<JSValueRef> xl = runtimeCallInfo->GetCallArgRef(XL + 1);
    Local<JSValueRef> xxl = runtimeCallInfo->GetCallArgRef(XXL + 1);
    containerSizeArray[XS] = xs->IsNumber() && xs->Int32Value(vm) >= 0 ? xs->Int32Value(vm) : -1;
    containerSizeArray[SM] = sm->IsNumber() && sm->Int32Value(vm) >= 0 ? sm->Int32Value(vm) : -1;
    containerSizeArray[MD] = md->IsNumber() && md->Int32Value(vm) >= 0 ? md->Int32Value(vm) : -1;
    containerSizeArray[LG] = lg->IsNumber() && lg->Int32Value(vm) >= 0 ? lg->Int32Value(vm) : -1;
    containerSizeArray[XL] = xl->IsNumber() && xl->Int32Value(vm) >= 0 ? xl->Int32Value(vm) : -1;
    containerSizeArray[XXL] = xxl->IsNumber() && xxl->Int32Value(vm) >= 0 ? xxl->Int32Value(vm) : -1;
}

int32_t GetIntValue(EcmaVM* vm, const Local<JSValueRef>& value, int32_t defaultValue)
{
    return value->IsNumber() ? value->Int32Value(vm) : defaultValue;
}

void ParseGutterObjectSub(
    EcmaVM* vm, const Local<panda::ObjectRef>& gutterParam, const RefPtr<V2::Gutter>& gutter, bool isHorizontal)
{
    std::optional<CalcDimension> gutterOptions[MAX_NUMBER_BREAKPOINT];
    RefPtr<ResourceObject> gutterOptionsResObj[MAX_NUMBER_BREAKPOINT];

    auto xs = GetObjectProperty(vm, gutterParam, "xs");
    CalcDimension xsDimension;
    RefPtr<ResourceObject> xsDimensionResObj;
    if (ArkTSUtils::ParseJsDimensionVp(vm, xs, xsDimension, xsDimensionResObj)) {
        gutterOptions[XS] = xsDimension;
    }

    auto sm = GetObjectProperty(vm, gutterParam, "sm");
    CalcDimension smDimension;
    RefPtr<ResourceObject> smDimensionResObj;
    if (ArkTSUtils::ParseJsDimensionVp(vm, sm, smDimension, smDimensionResObj)) {
        gutterOptions[SM] = smDimension;
    }

    auto md = GetObjectProperty(vm, gutterParam, "md");
    CalcDimension mdDimension;
    RefPtr<ResourceObject> mdDimensionResObj;
    if (ArkTSUtils::ParseJsDimensionVp(vm, md, mdDimension, mdDimensionResObj)) {
        gutterOptions[MD] = mdDimension;
    }

    auto lg = GetObjectProperty(vm, gutterParam, "lg");
    CalcDimension lgDimension;
    RefPtr<ResourceObject> lgDimensionResObj;
    if (ArkTSUtils::ParseJsDimensionVp(vm, lg, lgDimension, lgDimensionResObj)) {
        gutterOptions[LG] = lgDimension;
    }

    auto xl = GetObjectProperty(vm, gutterParam, "xl");
    CalcDimension xlDimension;
    RefPtr<ResourceObject> xlDimensionResObj;
    if (ArkTSUtils::ParseJsDimensionVp(vm, xl, xlDimension, xlDimensionResObj)) {
        gutterOptions[XL] = xlDimension;
    }

    auto xxl = GetObjectProperty(vm, gutterParam, "xxl");
    CalcDimension xxlDimension;
    RefPtr<ResourceObject> xxlDimensionResObj;
    if (ArkTSUtils::ParseJsDimensionVp(vm, xxl, xxlDimension, xxlDimensionResObj)) {
        gutterOptions[XXL] = xxlDimension;
    }

    if (SystemProperties::ConfigChangePerform()) {
        gutterOptionsResObj[XS] = xsDimensionResObj;
        gutterOptionsResObj[SM] = smDimensionResObj;
        gutterOptionsResObj[MD] = mdDimensionResObj;
        gutterOptionsResObj[LG] = lgDimensionResObj;
        gutterOptionsResObj[XL] = xlDimensionResObj;
        gutterOptionsResObj[XXL] = xxlDimensionResObj;
    }
    V2::GridContainerUtils::InheritGridRowGutterOption(gutter, gutterOptions, gutterOptionsResObj, isHorizontal);
}

void SetXGutterResObj(const RefPtr<ResourceObject>& xDimension, RefPtr<V2::Gutter>& gutter)
{
    auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, RefPtr<V2::Gutter>& gutter) {
        CalcDimension result;
        ResourceParseUtils::ParseResDimensionVpNG(resObj, result);
        gutter->xXs = result;
        gutter->xSm = result;
        gutter->xMd = result;
        gutter->xLg = result;
        gutter->xXl = result;
        gutter->xXXl = result;
    };
    gutter->AddResource("gridrow.gutter.x", xDimension, std::move(updateFunc));
}

void SetYGutterResObj(const RefPtr<ResourceObject>& yDimension, RefPtr<V2::Gutter>& gutter)
{
    auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, RefPtr<V2::Gutter>& gutter) {
        CalcDimension result;
        ResourceParseUtils::ParseResDimensionVpNG(resObj, result);
        gutter->yXs = result;
        gutter->ySm = result;
        gutter->yMd = result;
        gutter->yLg = result;
        gutter->yXl = result;
        gutter->yXXl = result;
    };
    gutter->AddResource("gridrow.gutter.y", yDimension, std::move(updateFunc));
}

void ParseGutterObject(
    EcmaVM* vm, const Local<JSValueRef>& gutterObject, RefPtr<V2::Gutter>& gutter, bool isHorizontal)
{
    CalcDimension dimension;
    RefPtr<ResourceObject> dimensionResObj;
    if (ArkTSUtils::ParseJsDimensionVp(vm, gutterObject, dimension, dimensionResObj)) {
        if (SystemProperties::ConfigChangePerform() && dimensionResObj) {
            isHorizontal ? SetXGutterResObj(dimensionResObj, gutter) : SetYGutterResObj(dimensionResObj, gutter);
        }
        isHorizontal ? gutter->SetXGutter(dimension) : gutter->SetYGutter(dimension);
        return;
    }
    if (!gutterObject->IsObject(vm)) {
        return;
    }
    auto gutterParam = gutterObject->ToObject(vm);
    ParseGutterObjectSub(vm, gutterParam, gutter, isHorizontal);
}

RefPtr<V2::Gutter> ParseGutter(EcmaVM* vm, const Local<JSValueRef>& jsValue)
{
    CalcDimension result;
    if (ArkTSUtils::ParseJsDimensionVp(vm, jsValue, result)) {
        return AceType::MakeRefPtr<V2::Gutter>(result);
    }
    if (!jsValue->IsObject(vm)) {
        return AceType::MakeRefPtr<V2::Gutter>();
    }
    auto paramGutter = jsValue->ToObject(vm);
    auto xObject = GetObjectProperty(vm, paramGutter, "x");
    auto yObject = GetObjectProperty(vm, paramGutter, "y");
    auto gutter = AceType::MakeRefPtr<V2::Gutter>();
    ParseGutterObject(vm, xObject, gutter, true);
    ParseGutterObject(vm, yObject, gutter, false);
    return gutter;
}

RefPtr<V2::GridContainerSize> ParseColumns(EcmaVM* vm, const Local<JSValueRef>& jsValue)
{
    if (jsValue->IsNumber()) {
        auto columnNumber = jsValue->Int32Value(vm);
        return columnNumber > 0 ? AceType::MakeRefPtr<V2::GridContainerSize>(columnNumber)
                                : AceType::MakeRefPtr<V2::GridContainerSize>(NG::DEFAULT_COLUMN_NUMBER);
    }
    if (jsValue->IsObject(vm)) {
        auto gridContainerSize = AceType::MakeRefPtr<V2::GridContainerSize>(NG::DEFAULT_COLUMN_NUMBER);
        auto gridParam = jsValue->ToObject(vm);
        std::optional<int32_t> containerSizeArray[MAX_NUMBER_BREAKPOINT];
        auto xs = GetObjectProperty(vm, gridParam, "xs");
        if (xs->IsNumber() && xs->Int32Value(vm) > 0) {
            containerSizeArray[XS] = xs->Int32Value(vm);
        }
        auto sm = GetObjectProperty(vm, gridParam, "sm");
        if (sm->IsNumber() && sm->Int32Value(vm) > 0) {
            containerSizeArray[SM] = sm->Int32Value(vm);
        }
        auto md = GetObjectProperty(vm, gridParam, "md");
        if (md->IsNumber() && md->Int32Value(vm) > 0) {
            containerSizeArray[MD] = md->Int32Value(vm);
        }
        auto lg = GetObjectProperty(vm, gridParam, "lg");
        if (lg->IsNumber() && lg->Int32Value(vm) > 0) {
            containerSizeArray[LG] = lg->Int32Value(vm);
        }
        auto xl = GetObjectProperty(vm, gridParam, "xl");
        if (xl->IsNumber() && xl->Int32Value(vm) > 0) {
            containerSizeArray[XL] = xl->Int32Value(vm);
        }
        auto xxl = GetObjectProperty(vm, gridParam, "xxl");
        if (xxl->IsNumber() && xxl->Int32Value(vm) > 0) {
            containerSizeArray[XXL] = xxl->Int32Value(vm);
        }
        V2::GridContainerUtils::InheritGridRowOption(gridContainerSize, containerSizeArray);
        return gridContainerSize;
    }
    return AceType::MakeRefPtr<V2::GridContainerSize>(NG::DEFAULT_COLUMN_NUMBER);
}

RefPtr<V2::GridContainerSize> ParseColumnsNG(EcmaVM* vm, const Local<JSValueRef>& jsValue)
{
    if (jsValue->IsNumber()) {
        auto columnNumber = jsValue->Int32Value(vm);
        return columnNumber > 0 ? AceType::MakeRefPtr<V2::GridContainerSize>(columnNumber)
                                : AceType::MakeRefPtr<V2::GridContainerSize>();
    }
    if (jsValue->IsObject(vm)) {
        auto gridContainerSize = AceType::MakeRefPtr<V2::GridContainerSize>();
        auto gridParam = jsValue->ToObject(vm);
        int32_t containerSizeArray[MAX_NUMBER_BREAKPOINT] = { -1, -1, -1, -1, -1, -1 };
        auto xs = GetObjectProperty(vm, gridParam, "xs");
        if (xs->IsNumber() && xs->Int32Value(vm) > 0) {
            containerSizeArray[XS] = xs->Int32Value(vm);
        }
        auto sm = GetObjectProperty(vm, gridParam, "sm");
        if (sm->IsNumber() && sm->Int32Value(vm) > 0) {
            containerSizeArray[SM] = sm->Int32Value(vm);
        }
        auto md = GetObjectProperty(vm, gridParam, "md");
        if (md->IsNumber() && md->Int32Value(vm) > 0) {
            containerSizeArray[MD] = md->Int32Value(vm);
        }
        auto lg = GetObjectProperty(vm, gridParam, "lg");
        if (lg->IsNumber() && lg->Int32Value(vm) > 0) {
            containerSizeArray[LG] = lg->Int32Value(vm);
        }
        auto xl = GetObjectProperty(vm, gridParam, "xl");
        if (xl->IsNumber() && xl->Int32Value(vm) > 0) {
            containerSizeArray[XL] = xl->Int32Value(vm);
        }
        auto xxl = GetObjectProperty(vm, gridParam, "xxl");
        if (xxl->IsNumber() && xxl->Int32Value(vm) > 0) {
            containerSizeArray[XXL] = xxl->Int32Value(vm);
        }
        V2::GridContainerUtils::InheritGridRowColumns(gridContainerSize, containerSizeArray,
            MAX_NUMBER_BREAKPOINT);
        return gridContainerSize;
    }
    return AceType::MakeRefPtr<V2::GridContainerSize>();
}

RefPtr<V2::BreakPoints> ParseBreakpoints(EcmaVM* vm, const Local<JSValueRef>& jsValue)
{
    auto breakpoint = AceType::MakeRefPtr<V2::BreakPoints>();
    if (!jsValue->IsObject(vm)) {
        return breakpoint;
    }
    auto breakpoints = jsValue->ToObject(vm);
    auto value = GetObjectProperty(vm, breakpoints, "value");
    auto reference = GetObjectProperty(vm, breakpoints, "reference");
    if (reference->IsNumber()) {
        breakpoint->reference = static_cast<V2::BreakPointsReference>(reference->Int32Value(vm));
    }
    if (!value->IsArray(vm)) {
        return breakpoint;
    }
    auto array = panda::Local<panda::ArrayRef>(value);
    breakpoint->breakpoints.clear();
    if (array->Length(vm) > MAX_NUMBER_BREAKPOINT - 1) {
        return breakpoint;
    }
    double width = -1.0;
    for (uint32_t i = 0; i < array->Length(vm); i++) {
        auto threshold = panda::ArrayRef::GetValueAt(vm, array, i);
        if (!threshold->IsString(vm) && !threshold->IsNumber()) {
            continue;
        }
        CalcDimension valueDimension;
        ArkTSUtils::ParseJsDimensionVp(vm, threshold, valueDimension);
        breakpoint->userDefine = true;
        if (GreatNotEqual(width, valueDimension.Value())) {
            return breakpoint;
        }
        width = valueDimension.Value();
        breakpoint->breakpoints.push_back(threshold->ToString(vm)->ToString(vm));
    }
    return breakpoint;
}

V2::GridRowDirection ParseDirection(EcmaVM* vm, const Local<JSValueRef>& jsValue)
{
    auto direction = V2::GridRowDirection::Row;
    if (jsValue->IsNumber()) {
        direction = static_cast<V2::GridRowDirection>(jsValue->Int32Value(vm));
    }
    return direction;
}
} // namespace

void GridRowBridge::RegisterGridRowAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    const char* functionNames[] = { "create", "setHeight", "setAlignItems", "resetAlignItems", "setDirection",
        "resetDirection", "setBreakpoints", "resetBreakpoints", "setColumns", "resetColumns", "setGutter", "resetGutter",
        "setOnBreakpointChange", "resetOnBreakpointChange" };
    Local<JSValueRef> funcValues[] = {
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridRowBridge::Create),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridRowBridge::SetHeight),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridRowBridge::SetAlignItems),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridRowBridge::ResetAlignItems),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridRowBridge::SetDirection),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridRowBridge::ResetDirection),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridRowBridge::SetBreakpoints),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridRowBridge::ResetBreakpoints),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridRowBridge::SetColumns),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridRowBridge::ResetColumns),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridRowBridge::SetGutter),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridRowBridge::ResetGutter),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridRowBridge::SetOnBreakpointChange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridRowBridge::ResetOnBreakpointChange),
    };
    auto gridRow = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(functionNames), functionNames, funcValues);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "gridRow"), gridRow);
}

ArkUINativeModuleValue GridRowBridge::SetHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    if (!GetNativeNode(nativeNode, firstArg, vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    auto gridRowModifier = nodeModifiers->getGridRowModifier();
    CHECK_NULL_RETURN(gridRowModifier, panda::JSValueRef::Undefined(vm));
    CHECK_NULL_RETURN(gridRowModifier->setHeight, panda::JSValueRef::Undefined(vm));
    gridRowModifier->setHeight(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridRowBridge::Create(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (firstArg->IsObject(vm)) {
        auto gridRow = firstArg->ToObject(vm);
        auto columns = GetObjectProperty(vm, gridRow, "columns");
        auto gutter = GetObjectProperty(vm, gridRow, "gutter");
        auto breakpoints = GetObjectProperty(vm, gridRow, "breakpoints");
        auto direction = GetObjectProperty(vm, gridRow, "direction");

        RefPtr<V2::GridContainerSize> parsedColumns;
        if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWENTY)) {
            parsedColumns = ParseColumns(vm, columns);
        } else {
            parsedColumns = ParseColumnsNG(vm, columns);
        }
        auto parsedGutter = ParseGutter(vm, gutter);
        auto parsedBreakpoints = ParseBreakpoints(vm, breakpoints);
        auto parsedDirection = ParseDirection(vm, direction);
        nodeModifiers->getGridRowModifier()->create(static_cast<void*>(&parsedColumns),
            static_cast<void*>(&parsedGutter), static_cast<void*>(&parsedBreakpoints),
            static_cast<int32_t>(parsedDirection));
    } else {
        nodeModifiers->getGridRowModifier()->create(nullptr, nullptr, nullptr,
            static_cast<int32_t>(V2::GridRowDirection::Row));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridRowBridge::SetAlignItems(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    if (!GetNativeNode(nativeNode, firstArg, vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    if (secondArg->IsNumber()) {
        int32_t alignItem = secondArg->Int32Value(vm);
        if (alignItem == static_cast<int32_t>(OHOS::Ace::FlexAlign::FLEX_START) ||
            alignItem == static_cast<int32_t>(OHOS::Ace::FlexAlign::FLEX_END) ||
            alignItem == static_cast<int32_t>(OHOS::Ace::FlexAlign::CENTER) ||
            alignItem == static_cast<int32_t>(OHOS::Ace::FlexAlign::STRETCH)) {
            GetArkUINodeModifiers()->getGridRowModifier()->setAlignItems(nativeNode, alignItem);
        } else if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
            GetArkUINodeModifiers()->getGridRowModifier()->setAlignItems(nativeNode,
                static_cast<int32_t>(OHOS::Ace::FlexAlign::FLEX_START));
        }
    } else {
        GetArkUINodeModifiers()->getGridRowModifier()->resetAlignItems(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridRowBridge::ResetAlignItems(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    if (GetNativeNode(nativeNode, firstArg, vm)) {
        GetArkUINodeModifiers()->getGridRowModifier()->resetAlignItems(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridRowBridge::SetDirection(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    if (!GetNativeNode(nativeNode, firstArg, vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    if (secondArg->IsNumber()) {
        GetArkUINodeModifiers()->getGridRowModifier()->setDirection(nativeNode, secondArg->Int32Value(vm));
    } else {
        GetArkUINodeModifiers()->getGridRowModifier()->resetDirection(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridRowBridge::ResetDirection(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    if (GetNativeNode(nativeNode, firstArg, vm)) {
        GetArkUINodeModifiers()->getGridRowModifier()->resetDirection(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridRowBridge::SetBreakpoints(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    Local<JSValueRef> threeArg = runtimeCallInfo->GetCallArgRef(2);
    ArkUINodeHandle nativeNode = nullptr;
    if (!GetNativeNode(nativeNode, firstArg, vm)) {
        return panda::JSValueRef::Undefined(vm);
    }

    int32_t reference = threeArg->IsNumber() ? threeArg->Int32Value(vm) : 0;
    std::vector<ArkUI_Float32> pointValues;
    std::vector<const char*> pointStr;
    int32_t size = 0;
    if (!secondArg->IsArray(vm)) {
        GetArkUINodeModifiers()->getGridRowModifier()->setBreakpoints(
            nativeNode, reference, pointValues.data(), pointStr.data(), size);
        return panda::JSValueRef::Undefined(vm);
    }
    auto arrayVal = panda::Local<panda::ArrayRef>(secondArg);
    auto length = ArkTSUtils::GetArrayLength(vm, arrayVal);
    if (length <= 0 || length > (MAX_NUMBER_BREAKPOINT - 1)) {
        GetArkUINodeModifiers()->getGridRowModifier()->setBreakpoints(
            nativeNode, reference, pointValues.data(), pointStr.data(), size);
        return panda::JSValueRef::Undefined(vm);
    }
    std::vector<std::string> calcStrings;
    for (uint32_t index = 0; index < length; index++) {
        CalcDimension calvalue;
        auto item = panda::ArrayRef::GetValueAt(vm, arrayVal, index);
        calcStrings.emplace_back(item->ToString(vm)->ToString(vm));
        if (!ArkTSUtils::ParseJsDimensionVp(vm, item, calvalue, false)) {
            calvalue = CalcDimension(0, DimensionUnit::VP);
        }
        pointValues.push_back(calvalue.Value());
        size++;
    }
    for (auto& calStr : calcStrings) {
        pointStr.push_back(calStr.c_str());
    }
    GetArkUINodeModifiers()->getGridRowModifier()->setBreakpoints(nativeNode, reference, pointValues.data(),
        pointStr.data(), size);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridRowBridge::ResetBreakpoints(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    if (GetNativeNode(nativeNode, firstArg, vm)) {
        GetArkUINodeModifiers()->getGridRowModifier()->resetBreakpoints(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridRowBridge::SetColumns(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    if (!GetNativeNode(nativeNode, firstArg, vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    int32_t containerSizeArray[MAX_NUMBER_BREAKPOINT];
    ParseColumns(runtimeCallInfo, vm, containerSizeArray);
    GetArkUINodeModifiers()->getGridRowModifier()->setColumns(nativeNode, containerSizeArray, MAX_NUMBER_BREAKPOINT);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridRowBridge::ResetColumns(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    if (GetNativeNode(nativeNode, firstArg, vm)) {
        GetArkUINodeModifiers()->getGridRowModifier()->resetColumns(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridRowBridge::SetGutter(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    if (!GetNativeNode(nativeNode, firstArg, vm)) {
        return panda::JSValueRef::Undefined(vm);
    }

    Local<JSValueRef> xXs = runtimeCallInfo->GetCallArgRef(X_XS + 1);
    Local<JSValueRef> xSm = runtimeCallInfo->GetCallArgRef(X_SM + 1);
    Local<JSValueRef> xMd = runtimeCallInfo->GetCallArgRef(X_MD + 1);
    Local<JSValueRef> xLg = runtimeCallInfo->GetCallArgRef(X_LG + 1);
    Local<JSValueRef> xXl = runtimeCallInfo->GetCallArgRef(X_XL + 1);
    Local<JSValueRef> xXxl = runtimeCallInfo->GetCallArgRef(X_XXL + 1);
    Local<JSValueRef> yXs = runtimeCallInfo->GetCallArgRef(Y_XS + 1);
    Local<JSValueRef> ySm = runtimeCallInfo->GetCallArgRef(Y_SM + 1);
    Local<JSValueRef> yMd = runtimeCallInfo->GetCallArgRef(Y_MD + 1);
    Local<JSValueRef> yLg = runtimeCallInfo->GetCallArgRef(Y_LG + 1);
    Local<JSValueRef> yXl = runtimeCallInfo->GetCallArgRef(Y_XL + 1);
    Local<JSValueRef> yXxl = runtimeCallInfo->GetCallArgRef(Y_XXL + 1);
    int32_t containerSizeArray[MAX_NUMBER_GUTTER];
    containerSizeArray[X_XS] = GetIntValue(vm, xXs, 0);
    containerSizeArray[X_SM] = GetIntValue(vm, xSm, containerSizeArray[X_XS]);
    containerSizeArray[X_MD] = GetIntValue(vm, xMd, containerSizeArray[X_SM]);
    containerSizeArray[X_LG] = GetIntValue(vm, xLg, containerSizeArray[X_MD]);
    containerSizeArray[X_XL] = GetIntValue(vm, xXl, containerSizeArray[X_LG]);
    containerSizeArray[X_XXL] = GetIntValue(vm, xXxl, containerSizeArray[X_XL]);
    containerSizeArray[Y_XS] = GetIntValue(vm, yXs, 0);
    containerSizeArray[Y_SM] = GetIntValue(vm, ySm, containerSizeArray[Y_XS]);
    containerSizeArray[Y_MD] = GetIntValue(vm, yMd, containerSizeArray[Y_SM]);
    containerSizeArray[Y_LG] = GetIntValue(vm, yLg, containerSizeArray[Y_MD]);
    containerSizeArray[Y_XL] = GetIntValue(vm, yXl, containerSizeArray[Y_LG]);
    containerSizeArray[Y_XXL] = GetIntValue(vm, yXxl, containerSizeArray[Y_XL]);
    GetArkUINodeModifiers()->getGridRowModifier()->setGutter(nativeNode, containerSizeArray, MAX_NUMBER_GUTTER);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridRowBridge::ResetGutter(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    if (GetNativeNode(nativeNode, firstArg, vm)) {
        GetArkUINodeModifiers()->getGridRowModifier()->resetGutter(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridRowBridge::SetOnBreakpointChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    if (!GetNativeNode(nativeNode, firstArg, vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    bool isJsView = IsJsView(firstArg, vm);
    auto frameNode = GetFrameNode(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        if (!isJsView) {
            GetArkUINodeModifiers()->getGridRowModifier()->resetOnBreakpointChange(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(const std::string&)> callback = [vm, frameNode, isJsView,
        execCtx = Framework::JsiExecutionContext(vm),
        func = panda::CopyableGlobal(vm, func)](const std::string& changeStr) {
        auto invokeCallback = [&]() {
            panda::TryCatch trycatch(vm);
            PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
            panda::Local<panda::JSValueRef> params[1] = { panda::StringRef::NewFromUtf8(vm, changeStr.c_str()) };
            auto result = func->Call(vm, func.ToLocal(), params, 1);
            if (isJsView) {
                ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
            }
        };
        if (isJsView) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("GridRow.onBreakpointChange");
            invokeCallback();
            return;
        }
        panda::LocalScope pandaScope(vm);
        invokeCallback();
    };
    GetArkUINodeModifiers()->getGridRowModifier()->setOnBreakpointChange(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridRowBridge::ResetOnBreakpointChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    if (GetNativeNode(nativeNode, firstArg, vm)) {
        GetArkUINodeModifiers()->getGridRowModifier()->resetOnBreakpointChange(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
