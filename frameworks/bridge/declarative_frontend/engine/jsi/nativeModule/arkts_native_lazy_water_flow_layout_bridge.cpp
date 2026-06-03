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

#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_lazy_water_flow_layout_bridge.h"

#include <memory>
#include <string>

#include "base/log/log_wrapper.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/lazy_layout/header_footer_utils.h"
#include "core/components_ng/pattern/lazy_waterflow_layout/lazy_water_flow_layout_model.h"

namespace OHOS::Ace::NG {

class FrameNode;
void SetLazyWaterFlowCallbackNode(FrameNode* frameNode);

namespace {
constexpr int32_t NODE_ARG_INDEX = 0;
constexpr int32_t VALUE_ARG_INDEX = 1;
constexpr int32_t BREAKPOINT_DEFAULT = 0;
constexpr int32_t BREAKPOINT_SM2MD3LG5 = 2;
constexpr int32_t STICKY_STYLE_NONE = 0;
constexpr int32_t STICKY_STYLE_BOTH = 3;
constexpr int32_t VISIBLE_INDEX_PARAM_COUNT = 2;
const std::string DEFAULT_COLUMNS_TEMPLATE = "1fr";
constexpr Dimension DEFAULT_COLUMNS_GAP = 0.0_fp;
constexpr Dimension DEFAULT_ROWS_GAP = 0.0_fp;
using VisibleIndexesChangeFunc = std::function<void(int32_t, int32_t)>;

ArkUINativeModuleValue Undefined(EcmaVM* vm)
{
    CHECK_NULL_RETURN(vm, panda::Local<panda::JSValueRef>());
    return panda::JSValueRef::Undefined(vm);
}

EcmaVM* GetEcmaVm(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    CHECK_NULL_RETURN(runtimeCallInfo, nullptr);
    return runtimeCallInfo->GetVM();
}

bool IsStackNodeArg(EcmaVM* vm, const Local<JSValueRef>& value)
{
    return vm && !value.IsEmpty() && value->IsBoolean() && value->ToBoolean(vm)->Value();
}

ArkUINodeHandle ParseNativeNode(EcmaVM* vm, const Local<JSValueRef>& value)
{
    CHECK_NULL_RETURN(vm, nullptr);
    if (value.IsEmpty() || !value->IsNativePointer(vm)) {
        return nullptr;
    }
    auto nativePointer = value->ToNativePointer(vm);
    if (nativePointer.IsEmpty()) {
        return nullptr;
    }
    return nodePtr(nativePointer->Value());
}

const ArkUILazyWaterFlowLayoutModifier* GetLazyWaterFlowLayoutModifier()
{
    auto* nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, nullptr);
    CHECK_NULL_RETURN(nodeModifiers->getLazyWaterFlowLayoutModifier, nullptr);
    return nodeModifiers->getLazyWaterFlowLayoutModifier();
}

Local<JSValueRef> GetProperty(EcmaVM* vm, const Local<JSValueRef>& object, const char* key)
{
    CHECK_NULL_RETURN(vm, panda::Local<panda::JSValueRef>());
    CHECK_NULL_RETURN(key, panda::JSValueRef::Undefined(vm));
    if (object.IsEmpty() || !object->IsObject(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto objectRef = object->ToObject(vm);
    if (objectRef.IsEmpty()) {
        return panda::JSValueRef::Undefined(vm);
    }
    return objectRef->Get(vm, panda::StringRef::NewFromUtf8(vm, key));
}

void CallJsFunction(EcmaVM* vm, const panda::CopyableGlobal<panda::FunctionRef>& func)
{
    CHECK_NULL_VOID(vm);
    panda::LocalScope pandaScope(vm);
    panda::TryCatch trycatch(vm);
    func->Call(vm, func.ToLocal(), nullptr, 0);
}

RefPtr<UINode> BuildHeaderFooterNodeFromFunction(EcmaVM* vm, const Local<JSValueRef>& value)
{
    CHECK_NULL_RETURN(vm, nullptr);
    if (value.IsEmpty() || !value->IsFunction(vm)) {
        return nullptr;
    }
    panda::Local<panda::FunctionRef> func = value->ToObject(vm);
    if (func.IsEmpty()) {
        return nullptr;
    }
    auto* stack = ViewStackProcessor::GetInstance();
    CHECK_NULL_RETURN(stack, nullptr);
    auto isBuilderNode = stack->IsBuilderNode();
    auto isExportTexture = stack->IsExportTexture();
    // Builder modifiers run outside the component creation stack. Use an isolated stack so edge builders
    // cannot leak nodes into the current component tree.
    ScopedViewStackProcessor builderViewStackProcessor;
    stack = ViewStackProcessor::GetInstance();
    CHECK_NULL_RETURN(stack, nullptr);
    stack->SetIsBuilderNode(isBuilderNode);
    stack->SetIsExportTexture(isExportTexture);
    panda::CopyableGlobal<panda::FunctionRef> globalFunc(vm, func);
    CallJsFunction(vm, globalFunc);
    auto builtNode = stack->Finish();
    if (!builtNode) {
        TAG_LOGW(AceLogTag::ACE_WATERFLOW, "LazyWaterFlowLayout header/footer builder produced no node");
    }
    return builtNode;
}

bool TryParseComponentContentNode(EcmaVM* vm, const Local<JSValueRef>& value, ArkUINodeHandle& contentNode)
{
    contentNode = nullptr;
    CHECK_NULL_RETURN(vm, false);
    if (value.IsEmpty() || value->IsUndefined() || value->IsNull() || !value->IsObject(vm)) {
        return false;
    }
    auto builderNode = GetProperty(vm, value, "builderNode_");
    if (builderNode.IsEmpty() || builderNode->IsUndefined() || builderNode->IsNull() || !builderNode->IsObject(vm)) {
        return false;
    }
    auto nodePtrValue = GetProperty(vm, builderNode, "nodePtr_");
    if (nodePtrValue.IsEmpty() || nodePtrValue->IsUndefined() || nodePtrValue->IsNull() ||
        !nodePtrValue->IsNativePointer(vm)) {
        return false;
    }
    auto nativePointer = nodePtrValue->ToNativePointer(vm);
    if (nativePointer.IsEmpty()) {
        return false;
    }
    // ComponentContent owns a BuilderNode internally; the native side only needs the built root node.
    contentNode = nodePtr(nativePointer->Value());
    return contentNode != nullptr;
}

void CallVisibleIndexesChange(EcmaVM* vm, const panda::CopyableGlobal<panda::FunctionRef>& func,
    int32_t start, int32_t end)
{
    CHECK_NULL_VOID(vm);
    panda::LocalScope pandaScope(vm);
    panda::TryCatch trycatch(vm);
    panda::Local<panda::NumberRef> startParam = panda::NumberRef::New(vm, start);
    panda::Local<panda::NumberRef> endParam = panda::NumberRef::New(vm, end);
    panda::Local<panda::JSValueRef> params[VISIBLE_INDEX_PARAM_COUNT] = { startParam, endParam };
    func->Call(vm, func.ToLocal(), params, VISIBLE_INDEX_PARAM_COUNT);
}

CalcDimension ParseLengthMetricsOrDefault(EcmaVM* vm, const Local<JSValueRef>& value, const Dimension& defaultValue)
{
    CalcDimension size;
    if (value.IsEmpty() || value->IsUndefined() || !ArkTSUtils::ParseJsLengthMetrics(vm, value, size) ||
        LessNotEqual(size.Value(), 0.0)) {
        return CalcDimension(defaultValue.Value(), defaultValue.Unit());
    }
    return size;
}

bool TryParseItemFillPolicy(EcmaVM* vm, const Local<JSValueRef>& value, PresetFillType& policy)
{
    if (value.IsEmpty() || value->IsUndefined() || value->IsNull()) {
        return false;
    }
    if (value->IsObject(vm)) {
        auto fillTypeArg = GetProperty(vm, value, "fillType");
        auto policyValue = BREAKPOINT_DEFAULT;
        if (!fillTypeArg.IsEmpty() && !fillTypeArg->IsUndefined() && !fillTypeArg->IsNull() &&
            ArkTSUtils::ParseJsInt32(vm, fillTypeArg, policyValue) &&
            policyValue >= BREAKPOINT_DEFAULT && policyValue <= BREAKPOINT_SM2MD3LG5) {
            policy = static_cast<PresetFillType>(policyValue);
            return true;
        }
        return false;
    }
    auto policyValue = BREAKPOINT_DEFAULT;
    if (ArkTSUtils::ParseJsInt32(vm, value, policyValue) &&
        policyValue >= BREAKPOINT_DEFAULT && policyValue <= BREAKPOINT_SM2MD3LG5) {
        policy = static_cast<PresetFillType>(policyValue);
        return true;
    }
    return false;
}

enum class ColumnsTemplateArgType {
    POLICY,
    STRING,
    RESET,
    INVALID_OBJECT,
};

struct ColumnsTemplateArg {
    ColumnsTemplateArgType type = ColumnsTemplateArgType::RESET;
    PresetFillType policy = static_cast<PresetFillType>(BREAKPOINT_DEFAULT);
    std::string value;
};

ColumnsTemplateArg ParseColumnsTemplateArg(EcmaVM* vm, const Local<JSValueRef>& value)
{
    ColumnsTemplateArg result;
    if (!value.IsEmpty() && value->IsObject(vm) && TryParseItemFillPolicy(vm, value, result.policy)) {
        result.type = ColumnsTemplateArgType::POLICY;
        return result;
    }
    if (!value.IsEmpty() && value->IsObject(vm)) {
        result.type = ColumnsTemplateArgType::INVALID_OBJECT;
        return result;
    }
    if (value.IsEmpty() || value->IsUndefined() || value->IsNull() || !value->IsString(vm)) {
        result.type = ColumnsTemplateArgType::RESET;
        return result;
    }
    result.type = ColumnsTemplateArgType::STRING;
    result.value = value->ToString(vm)->ToString(vm);
    return result;
}

void ApplyColumnsTemplateToStack(const ColumnsTemplateArg& arg)
{
    switch (arg.type) {
        case ColumnsTemplateArgType::POLICY:
            LazyVWaterFlowLayoutModel::SetColumnsTemplate("");
            LazyVWaterFlowLayoutModel::SetItemFillPolicy(arg.policy);
            return;
        case ColumnsTemplateArgType::INVALID_OBJECT:
            TAG_LOGW(AceLogTag::ACE_WATERFLOW,
                "LazyWaterFlowLayout columnsTemplate ignores non-ItemFillPolicy object");
            [[fallthrough]];
        case ColumnsTemplateArgType::RESET:
            LazyVWaterFlowLayoutModel::ResetItemFillPolicy();
            LazyVWaterFlowLayoutModel::SetColumnsTemplate(DEFAULT_COLUMNS_TEMPLATE);
            return;
        case ColumnsTemplateArgType::STRING:
            LazyVWaterFlowLayoutModel::ResetItemFillPolicy();
            LazyVWaterFlowLayoutModel::SetColumnsTemplate(arg.value);
            return;
    }
}

void ApplyColumnsTemplateToModifier(
    ArkUINodeHandle nativeNode, const ArkUILazyWaterFlowLayoutModifier* modifier, const ColumnsTemplateArg& arg)
{
    switch (arg.type) {
        case ColumnsTemplateArgType::POLICY:
            modifier->resetColumnsTemplate(nativeNode);
            modifier->setItemFillPolicy(nativeNode, static_cast<int32_t>(arg.policy));
            return;
        case ColumnsTemplateArgType::INVALID_OBJECT:
            TAG_LOGW(AceLogTag::ACE_WATERFLOW,
                "LazyWaterFlowLayout columnsTemplate ignores non-ItemFillPolicy object");
            [[fallthrough]];
        case ColumnsTemplateArgType::RESET:
            modifier->resetItemFillPolicy(nativeNode);
            modifier->resetColumnsTemplate(nativeNode);
            return;
        case ColumnsTemplateArgType::STRING:
            modifier->resetItemFillPolicy(nativeNode);
            modifier->setColumnsTemplate(nativeNode, arg.value.c_str());
            return;
    }
}
} // namespace

void RegisterLazyWaterFlowLayoutBridgeAttributes(panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm)
{
    LazyWaterFlowLayoutBridge::RegisterLazyWaterFlowLayoutAttributes(object, vm);
}

void RegisterLazyVWaterFlowLayoutBridgeAttributes(panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm)
{
    LazyVWaterFlowLayoutBridge::RegisterLazyVWaterFlowLayoutAttributes(object, vm);
}

void LazyWaterFlowLayoutBridge::RegisterLazyWaterFlowLayoutAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    CHECK_NULL_VOID(vm);
    if (object.IsEmpty()) {
        return;
    }
    auto lazyWaterFlowLayout = panda::ObjectRef::New(vm);
    lazyWaterFlowLayout->Set(vm, panda::StringRef::NewFromUtf8(vm, "setColumnsGap"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), LazyWaterFlowLayoutBridge::SetColumnsGap));
    lazyWaterFlowLayout->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetColumnsGap"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), LazyWaterFlowLayoutBridge::ResetColumnsGap));
    lazyWaterFlowLayout->Set(vm, panda::StringRef::NewFromUtf8(vm, "setRowsGap"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), LazyWaterFlowLayoutBridge::SetRowsGap));
    lazyWaterFlowLayout->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetRowsGap"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), LazyWaterFlowLayoutBridge::ResetRowsGap));
    lazyWaterFlowLayout->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSticky"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), LazyWaterFlowLayoutBridge::SetSticky));
    lazyWaterFlowLayout->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSticky"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), LazyWaterFlowLayoutBridge::ResetSticky));
    lazyWaterFlowLayout->Set(vm, panda::StringRef::NewFromUtf8(vm, "setHeader"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), LazyWaterFlowLayoutBridge::SetHeader));
    lazyWaterFlowLayout->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetHeader"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), LazyWaterFlowLayoutBridge::ResetHeader));
    lazyWaterFlowLayout->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFooter"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), LazyWaterFlowLayoutBridge::SetFooter));
    lazyWaterFlowLayout->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFooter"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), LazyWaterFlowLayoutBridge::ResetFooter));
    lazyWaterFlowLayout->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnVisibleIndexesChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm),
            LazyWaterFlowLayoutBridge::SetOnVisibleIndexesChange));
    lazyWaterFlowLayout->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnVisibleIndexesChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm),
            LazyWaterFlowLayoutBridge::ResetOnVisibleIndexesChange));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "lazyWaterFlowLayout"), lazyWaterFlowLayout);
}

ArkUINativeModuleValue LazyWaterFlowLayoutBridge::SetColumnsGap(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    auto* vm = GetEcmaVm(runtimeCallInfo);
    CHECK_NULL_RETURN(vm, panda::Local<panda::JSValueRef>());
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> argSize = runtimeCallInfo->GetCallArgRef(1);
    if (IsStackNodeArg(vm, node)) {
        LazyWaterFlowLayoutModel::SetColumnGap(ParseLengthMetricsOrDefault(vm, argSize, DEFAULT_COLUMNS_GAP));
        return Undefined(vm);
    }
    auto nativeNode = ParseNativeNode(vm, node);
    CHECK_NULL_RETURN(nativeNode, Undefined(vm));
    auto* modifier = GetLazyWaterFlowLayoutModifier();
    CHECK_NULL_RETURN(modifier, Undefined(vm));

    CalcDimension size;
    std::string calcStr;
    struct ArkUIResourceLength columnGap = { 0.0, 0, nullptr };
    if (argSize.IsEmpty() || argSize->IsUndefined() || !ArkTSUtils::ParseJsLengthMetrics(vm, argSize, size)) {
        modifier->resetColumnsGap(nativeNode);
    } else {
        if (size.Unit() == DimensionUnit::CALC) {
            columnGap.unit = static_cast<int32_t>(DimensionUnit::CALC);
            calcStr = size.CalcValue();
            columnGap.string = calcStr.c_str();
        } else {
            columnGap.value = size.Value();
            columnGap.unit = static_cast<int32_t>(size.Unit());
            columnGap.string = nullptr;
        }
        modifier->setColumnsGap(nativeNode, &columnGap);
    }
    return Undefined(vm);
}

ArkUINativeModuleValue LazyWaterFlowLayoutBridge::ResetColumnsGap(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    auto* vm = GetEcmaVm(runtimeCallInfo);
    CHECK_NULL_RETURN(vm, panda::Local<panda::JSValueRef>());
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(0);
    if (IsStackNodeArg(vm, node)) {
        LazyWaterFlowLayoutModel::SetColumnGap(DEFAULT_COLUMNS_GAP);
        return Undefined(vm);
    }
    auto nativeNode = ParseNativeNode(vm, node);
    CHECK_NULL_RETURN(nativeNode, Undefined(vm));
    auto* modifier = GetLazyWaterFlowLayoutModifier();
    CHECK_NULL_RETURN(modifier, Undefined(vm));
    modifier->resetColumnsGap(nativeNode);
    return Undefined(vm);
}

ArkUINativeModuleValue LazyWaterFlowLayoutBridge::SetRowsGap(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    auto* vm = GetEcmaVm(runtimeCallInfo);
    CHECK_NULL_RETURN(vm, panda::Local<panda::JSValueRef>());
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> argSize = runtimeCallInfo->GetCallArgRef(1);
    if (IsStackNodeArg(vm, node)) {
        LazyWaterFlowLayoutModel::SetRowGap(ParseLengthMetricsOrDefault(vm, argSize, DEFAULT_ROWS_GAP));
        return Undefined(vm);
    }
    auto nativeNode = ParseNativeNode(vm, node);
    CHECK_NULL_RETURN(nativeNode, Undefined(vm));
    auto* modifier = GetLazyWaterFlowLayoutModifier();
    CHECK_NULL_RETURN(modifier, Undefined(vm));

    CalcDimension size;
    std::string calcStr;
    struct ArkUIResourceLength rowsGap = { 0.0, 0, nullptr };
    if (argSize.IsEmpty() || argSize->IsUndefined() || !ArkTSUtils::ParseJsLengthMetrics(vm, argSize, size)) {
        modifier->resetRowsGap(nativeNode);
    } else {
        if (size.Unit() == DimensionUnit::CALC) {
            rowsGap.unit = static_cast<int32_t>(DimensionUnit::CALC);
            calcStr = size.CalcValue();
            rowsGap.string = calcStr.c_str();
        } else {
            rowsGap.value = size.Value();
            rowsGap.unit = static_cast<int32_t>(size.Unit());
            rowsGap.string = nullptr;
        }
        modifier->setRowsGap(nativeNode, &rowsGap);
    }
    return Undefined(vm);
}

ArkUINativeModuleValue LazyWaterFlowLayoutBridge::ResetRowsGap(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    auto* vm = GetEcmaVm(runtimeCallInfo);
    CHECK_NULL_RETURN(vm, panda::Local<panda::JSValueRef>());
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(0);
    if (IsStackNodeArg(vm, node)) {
        LazyWaterFlowLayoutModel::SetRowGap(DEFAULT_ROWS_GAP);
        return Undefined(vm);
    }
    auto nativeNode = ParseNativeNode(vm, node);
    CHECK_NULL_RETURN(nativeNode, Undefined(vm));
    auto* modifier = GetLazyWaterFlowLayoutModifier();
    CHECK_NULL_RETURN(modifier, Undefined(vm));
    modifier->resetRowsGap(nativeNode);
    return Undefined(vm);
}

ArkUINativeModuleValue LazyWaterFlowLayoutBridge::SetSticky(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    auto* vm = GetEcmaVm(runtimeCallInfo);
    CHECK_NULL_RETURN(vm, panda::Local<panda::JSValueRef>());
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> argSticky = runtimeCallInfo->GetCallArgRef(1);
    if (IsStackNodeArg(vm, node)) {
        auto stickyStyle = STICKY_STYLE_NONE;
        if (!argSticky.IsEmpty() && !argSticky->IsUndefined() && !argSticky->IsNull() && argSticky->IsNumber()) {
            stickyStyle = argSticky->Int32Value(vm);
        }
        if (stickyStyle < STICKY_STYLE_NONE || stickyStyle > STICKY_STYLE_BOTH) {
            stickyStyle = STICKY_STYLE_NONE;
        }
        LazyWaterFlowLayoutModel::SetSticky(static_cast<StickyStyle>(stickyStyle));
        return Undefined(vm);
    }
    auto nativeNode = ParseNativeNode(vm, node);
    CHECK_NULL_RETURN(nativeNode, Undefined(vm));
    auto* modifier = GetLazyWaterFlowLayoutModifier();
    CHECK_NULL_RETURN(modifier, Undefined(vm));
    if (argSticky.IsEmpty() || argSticky->IsUndefined() || argSticky->IsNull() || !argSticky->IsNumber()) {
        modifier->resetSticky(nativeNode);
    } else {
        modifier->setSticky(nativeNode, argSticky->Int32Value(vm));
    }
    return Undefined(vm);
}

ArkUINativeModuleValue LazyWaterFlowLayoutBridge::ResetSticky(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    auto* vm = GetEcmaVm(runtimeCallInfo);
    CHECK_NULL_RETURN(vm, panda::Local<panda::JSValueRef>());
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(0);
    if (IsStackNodeArg(vm, node)) {
        LazyWaterFlowLayoutModel::SetSticky(static_cast<StickyStyle>(STICKY_STYLE_NONE));
        return Undefined(vm);
    }
    auto nativeNode = ParseNativeNode(vm, node);
    CHECK_NULL_RETURN(nativeNode, Undefined(vm));
    auto* modifier = GetLazyWaterFlowLayoutModifier();
    CHECK_NULL_RETURN(modifier, Undefined(vm));
    modifier->resetSticky(nativeNode);
    return Undefined(vm);
}

ArkUINativeModuleValue LazyWaterFlowLayoutBridge::SetHeader(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    auto* vm = GetEcmaVm(runtimeCallInfo);
    CHECK_NULL_RETURN(vm, panda::Local<panda::JSValueRef>());
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NODE_ARG_INDEX);
    Local<JSValueRef> headerArg = runtimeCallInfo->GetCallArgRef(VALUE_ARG_INDEX);
    if (IsStackNodeArg(vm, nodeArg)) {
        if (!headerArg.IsEmpty() && headerArg->IsFunction(vm)) {
            panda::Local<panda::FunctionRef> func = headerArg->ToObject(vm);
            if (func.IsEmpty()) {
                return Undefined(vm);
            }
            std::function<void()> headerAction = [vm, func = panda::CopyableGlobal(vm, func)]() {
                CallJsFunction(vm, func);
            };
            LazyWaterFlowLayoutModel::SetHeader(std::move(headerAction));
        } else {
            LazyWaterFlowLayoutModel::RemoveHeader();
        }
        return Undefined(vm);
    }
    auto nativeNode = ParseNativeNode(vm, nodeArg);
    CHECK_NULL_RETURN(nativeNode, Undefined(vm));
    if (!headerArg.IsEmpty() && headerArg->IsFunction(vm)) {
        auto headerNode = BuildHeaderFooterNodeFromFunction(vm, headerArg);
        auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
        CHECK_NULL_RETURN(frameNode, Undefined(vm));
        LazyWaterFlowLayoutModel::SetHeader(frameNode, headerNode);
        return Undefined(vm);
    }
    auto* modifier = GetLazyWaterFlowLayoutModifier();
    CHECK_NULL_RETURN(modifier, Undefined(vm));
    ArkUINodeHandle headerNode = nullptr;
    if (TryParseComponentContentNode(vm, headerArg, headerNode)) {
        modifier->setHeader(nativeNode, headerNode);
    } else {
        modifier->resetHeader(nativeNode);
    }
    return Undefined(vm);
}

ArkUINativeModuleValue LazyWaterFlowLayoutBridge::ResetHeader(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    auto* vm = GetEcmaVm(runtimeCallInfo);
    CHECK_NULL_RETURN(vm, panda::Local<panda::JSValueRef>());
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NODE_ARG_INDEX);
    if (IsStackNodeArg(vm, nodeArg)) {
        LazyWaterFlowLayoutModel::RemoveHeader();
        return Undefined(vm);
    }
    auto nativeNode = ParseNativeNode(vm, nodeArg);
    CHECK_NULL_RETURN(nativeNode, Undefined(vm));
    auto* modifier = GetLazyWaterFlowLayoutModifier();
    CHECK_NULL_RETURN(modifier, Undefined(vm));
    modifier->resetHeader(nativeNode);
    return Undefined(vm);
}

ArkUINativeModuleValue LazyWaterFlowLayoutBridge::SetFooter(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    auto* vm = GetEcmaVm(runtimeCallInfo);
    CHECK_NULL_RETURN(vm, panda::Local<panda::JSValueRef>());
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NODE_ARG_INDEX);
    Local<JSValueRef> footerArg = runtimeCallInfo->GetCallArgRef(VALUE_ARG_INDEX);
    if (IsStackNodeArg(vm, nodeArg)) {
        if (!footerArg.IsEmpty() && footerArg->IsFunction(vm)) {
            panda::Local<panda::FunctionRef> func = footerArg->ToObject(vm);
            if (func.IsEmpty()) {
                return Undefined(vm);
            }
            std::function<void()> footerAction = [vm, func = panda::CopyableGlobal(vm, func)]() {
                CallJsFunction(vm, func);
            };
            LazyWaterFlowLayoutModel::SetFooter(std::move(footerAction));
        } else {
            LazyWaterFlowLayoutModel::RemoveFooter();
        }
        return Undefined(vm);
    }
    auto nativeNode = ParseNativeNode(vm, nodeArg);
    CHECK_NULL_RETURN(nativeNode, Undefined(vm));
    if (!footerArg.IsEmpty() && footerArg->IsFunction(vm)) {
        auto footerNode = BuildHeaderFooterNodeFromFunction(vm, footerArg);
        auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
        CHECK_NULL_RETURN(frameNode, Undefined(vm));
        LazyWaterFlowLayoutModel::SetFooter(frameNode, footerNode);
        return Undefined(vm);
    }
    auto* modifier = GetLazyWaterFlowLayoutModifier();
    CHECK_NULL_RETURN(modifier, Undefined(vm));
    ArkUINodeHandle footerNode = nullptr;
    if (TryParseComponentContentNode(vm, footerArg, footerNode)) {
        modifier->setFooter(nativeNode, footerNode);
    } else {
        modifier->resetFooter(nativeNode);
    }
    return Undefined(vm);
}

ArkUINativeModuleValue LazyWaterFlowLayoutBridge::ResetFooter(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    auto* vm = GetEcmaVm(runtimeCallInfo);
    CHECK_NULL_RETURN(vm, panda::Local<panda::JSValueRef>());
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NODE_ARG_INDEX);
    if (IsStackNodeArg(vm, nodeArg)) {
        LazyWaterFlowLayoutModel::RemoveFooter();
        return Undefined(vm);
    }
    auto nativeNode = ParseNativeNode(vm, nodeArg);
    CHECK_NULL_RETURN(nativeNode, Undefined(vm));
    auto* modifier = GetLazyWaterFlowLayoutModifier();
    CHECK_NULL_RETURN(modifier, Undefined(vm));
    modifier->resetFooter(nativeNode);
    return Undefined(vm);
}

ArkUINativeModuleValue LazyWaterFlowLayoutBridge::SetOnVisibleIndexesChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    auto* vm = GetEcmaVm(runtimeCallInfo);
    CHECK_NULL_RETURN(vm, panda::Local<panda::JSValueRef>());
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    if (IsStackNodeArg(vm, firstArg)) {
        if (!callbackArg.IsEmpty() && callbackArg->IsFunction(vm)) {
            panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
            if (func.IsEmpty()) {
                return Undefined(vm);
            }
            VisibleIndexesChangeFunc callback = [vm, func = panda::CopyableGlobal(vm, func)](
                                                    const int32_t start, const int32_t end) {
                CallVisibleIndexesChange(vm, func, start, end);
            };
            LazyWaterFlowLayoutModel::SetOnVisibleIndexesChange(std::move(callback));
        } else {
            LazyWaterFlowLayoutModel::SetOnVisibleIndexesChange(nullptr);
        }
        return Undefined(vm);
    }
    auto nativeNode = ParseNativeNode(vm, firstArg);
    CHECK_NULL_RETURN(nativeNode, Undefined(vm));
    auto* modifier = GetLazyWaterFlowLayoutModifier();
    CHECK_NULL_RETURN(modifier, Undefined(vm));
    if (callbackArg.IsEmpty() || callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        modifier->resetOnVisibleIndexesChange(nativeNode);
        return Undefined(vm);
    }

    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    if (func.IsEmpty()) {
        return Undefined(vm);
    }
    // Keep the callback node in PipelineContext so JS exceptions and lifecycle tracing point to the owner node.
    // Transfer a heap-owned callback object across the C ABI so the modifier can take ownership immediately without
    // relying on a stack address that expires when this bridge call returns.
    // The pattern owns this callback after the C ABI transfer; resetOnVisibleIndexesChange replaces it before a new one
    // is installed, and the captured node is only used as the callback owner while that pattern callback is alive.
    auto callback = std::make_unique<std::function<void(int32_t, int32_t)>>(
        [vm, frameNode, func = panda::CopyableGlobal(vm, func)](const int32_t start, const int32_t end) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        SetLazyWaterFlowCallbackNode(frameNode);

        panda::Local<panda::NumberRef> startParam = panda::NumberRef::New(vm, start);
        panda::Local<panda::NumberRef> endParam = panda::NumberRef::New(vm, end);
        panda::Local<panda::JSValueRef> params[VISIBLE_INDEX_PARAM_COUNT] = { startParam, endParam };
        func->Call(vm, func.ToLocal(), params, VISIBLE_INDEX_PARAM_COUNT);
    });
    modifier->setOnVisibleIndexesChange(nativeNode, callback.release());
    return Undefined(vm);
}

ArkUINativeModuleValue LazyWaterFlowLayoutBridge::ResetOnVisibleIndexesChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    auto* vm = GetEcmaVm(runtimeCallInfo);
    CHECK_NULL_RETURN(vm, panda::Local<panda::JSValueRef>());
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (IsStackNodeArg(vm, firstArg)) {
        LazyWaterFlowLayoutModel::SetOnVisibleIndexesChange(nullptr);
        return Undefined(vm);
    }
    auto nativeNode = ParseNativeNode(vm, firstArg);
    CHECK_NULL_RETURN(nativeNode, Undefined(vm));
    auto* modifier = GetLazyWaterFlowLayoutModifier();
    CHECK_NULL_RETURN(modifier, Undefined(vm));
    modifier->resetOnVisibleIndexesChange(nativeNode);
    return Undefined(vm);
}

void LazyVWaterFlowLayoutBridge::RegisterLazyVWaterFlowLayoutAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    CHECK_NULL_VOID(vm);
    if (object.IsEmpty()) {
        return;
    }
    auto lazyVWaterFlowLayout = panda::ObjectRef::New(vm);
    lazyVWaterFlowLayout->Set(vm, panda::StringRef::NewFromUtf8(vm, "create"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), LazyVWaterFlowLayoutBridge::Create));
    lazyVWaterFlowLayout->Set(vm, panda::StringRef::NewFromUtf8(vm, "setColumnsGap"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), LazyWaterFlowLayoutBridge::SetColumnsGap));
    lazyVWaterFlowLayout->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetColumnsGap"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), LazyWaterFlowLayoutBridge::ResetColumnsGap));
    lazyVWaterFlowLayout->Set(vm, panda::StringRef::NewFromUtf8(vm, "setRowsGap"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), LazyWaterFlowLayoutBridge::SetRowsGap));
    lazyVWaterFlowLayout->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetRowsGap"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), LazyWaterFlowLayoutBridge::ResetRowsGap));
    lazyVWaterFlowLayout->Set(vm, panda::StringRef::NewFromUtf8(vm, "setColumnsTemplate"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), LazyVWaterFlowLayoutBridge::SetColumnsTemplate));
    lazyVWaterFlowLayout->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetColumnsTemplate"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), LazyVWaterFlowLayoutBridge::ResetColumnsTemplate));
    lazyVWaterFlowLayout->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSticky"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), LazyWaterFlowLayoutBridge::SetSticky));
    lazyVWaterFlowLayout->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSticky"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), LazyWaterFlowLayoutBridge::ResetSticky));
    lazyVWaterFlowLayout->Set(vm, panda::StringRef::NewFromUtf8(vm, "setHeader"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), LazyWaterFlowLayoutBridge::SetHeader));
    lazyVWaterFlowLayout->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetHeader"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), LazyWaterFlowLayoutBridge::ResetHeader));
    lazyVWaterFlowLayout->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFooter"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), LazyWaterFlowLayoutBridge::SetFooter));
    lazyVWaterFlowLayout->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFooter"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), LazyWaterFlowLayoutBridge::ResetFooter));
    lazyVWaterFlowLayout->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnVisibleIndexesChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm),
            LazyWaterFlowLayoutBridge::SetOnVisibleIndexesChange));
    lazyVWaterFlowLayout->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnVisibleIndexesChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm),
            LazyWaterFlowLayoutBridge::ResetOnVisibleIndexesChange));
    lazyVWaterFlowLayout->Set(vm, panda::StringRef::NewFromUtf8(vm, "setItemFillPolicy"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), LazyVWaterFlowLayoutBridge::SetItemFillPolicy));
    lazyVWaterFlowLayout->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetItemFillPolicy"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), LazyVWaterFlowLayoutBridge::ResetItemFillPolicy));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "lazyVWaterFlowLayout"), lazyVWaterFlowLayout);
}

ArkUINativeModuleValue LazyVWaterFlowLayoutBridge::Create(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    auto* vm = GetEcmaVm(runtimeCallInfo);
    CHECK_NULL_RETURN(vm, panda::Local<panda::JSValueRef>());
    LazyVWaterFlowLayoutModel::Create();
    return Undefined(vm);
}

ArkUINativeModuleValue LazyVWaterFlowLayoutBridge::SetColumnsTemplate(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    auto* vm = GetEcmaVm(runtimeCallInfo);
    CHECK_NULL_RETURN(vm, panda::Local<panda::JSValueRef>());
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(0);
    auto columnsTemplateArg = ParseColumnsTemplateArg(vm, runtimeCallInfo->GetCallArgRef(1));
    // columnsTemplate and itemFillPolicy are a union: setting one clears the other before layout reads it.
    if (IsStackNodeArg(vm, node)) {
        ApplyColumnsTemplateToStack(columnsTemplateArg);
        return Undefined(vm);
    }
    auto nativeNode = ParseNativeNode(vm, node);
    CHECK_NULL_RETURN(nativeNode, Undefined(vm));
    auto* modifier = GetLazyWaterFlowLayoutModifier();
    CHECK_NULL_RETURN(modifier, Undefined(vm));
    ApplyColumnsTemplateToModifier(nativeNode, modifier, columnsTemplateArg);
    return Undefined(vm);
}

ArkUINativeModuleValue LazyVWaterFlowLayoutBridge::ResetColumnsTemplate(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    auto* vm = GetEcmaVm(runtimeCallInfo);
    CHECK_NULL_RETURN(vm, panda::Local<panda::JSValueRef>());
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(0);
    if (IsStackNodeArg(vm, node)) {
        LazyVWaterFlowLayoutModel::ResetItemFillPolicy();
        LazyVWaterFlowLayoutModel::SetColumnsTemplate(DEFAULT_COLUMNS_TEMPLATE);
        return Undefined(vm);
    }
    auto nativeNode = ParseNativeNode(vm, node);
    CHECK_NULL_RETURN(nativeNode, Undefined(vm));
    auto* modifier = GetLazyWaterFlowLayoutModifier();
    CHECK_NULL_RETURN(modifier, Undefined(vm));
    modifier->resetItemFillPolicy(nativeNode);
    modifier->resetColumnsTemplate(nativeNode);
    return Undefined(vm);
}

ArkUINativeModuleValue LazyVWaterFlowLayoutBridge::SetItemFillPolicy(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    auto* vm = GetEcmaVm(runtimeCallInfo);
    CHECK_NULL_RETURN(vm, panda::Local<panda::JSValueRef>());
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> argItemFillPolicy = runtimeCallInfo->GetCallArgRef(1);
    PresetFillType policy = static_cast<PresetFillType>(BREAKPOINT_DEFAULT);
    const bool hasPolicy = TryParseItemFillPolicy(vm, argItemFillPolicy, policy);
    // Keep the union invariant explicit on the direct ItemFillPolicy path as well.
    if (IsStackNodeArg(vm, node)) {
        if (!hasPolicy) {
            TAG_LOGW(AceLogTag::ACE_WATERFLOW, "LazyWaterFlowLayout rejects invalid ItemFillPolicy");
            LazyVWaterFlowLayoutModel::ResetItemFillPolicy();
            LazyVWaterFlowLayoutModel::SetColumnsTemplate(DEFAULT_COLUMNS_TEMPLATE);
            return Undefined(vm);
        }
        LazyVWaterFlowLayoutModel::SetColumnsTemplate("");
        LazyVWaterFlowLayoutModel::SetItemFillPolicy(policy);
        return Undefined(vm);
    }
    auto nativeNode = ParseNativeNode(vm, node);
    CHECK_NULL_RETURN(nativeNode, Undefined(vm));
    auto* modifier = GetLazyWaterFlowLayoutModifier();
    CHECK_NULL_RETURN(modifier, Undefined(vm));
    if (!hasPolicy) {
        TAG_LOGW(AceLogTag::ACE_WATERFLOW, "LazyWaterFlowLayout rejects invalid ItemFillPolicy");
        modifier->resetItemFillPolicy(nativeNode);
        modifier->resetColumnsTemplate(nativeNode);
        return Undefined(vm);
    }
    modifier->setItemFillPolicy(nativeNode, static_cast<int32_t>(policy));
    return Undefined(vm);
}

ArkUINativeModuleValue LazyVWaterFlowLayoutBridge::ResetItemFillPolicy(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    auto* vm = GetEcmaVm(runtimeCallInfo);
    CHECK_NULL_RETURN(vm, panda::Local<panda::JSValueRef>());
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(0);
    if (IsStackNodeArg(vm, node)) {
        LazyVWaterFlowLayoutModel::ResetItemFillPolicy();
        return Undefined(vm);
    }
    auto nativeNode = ParseNativeNode(vm, node);
    CHECK_NULL_RETURN(nativeNode, Undefined(vm));
    auto* modifier = GetLazyWaterFlowLayoutModifier();
    CHECK_NULL_RETURN(modifier, Undefined(vm));
    modifier->resetItemFillPolicy(nativeNode);
    return Undefined(vm);
}
} // namespace OHOS::Ace::NG
