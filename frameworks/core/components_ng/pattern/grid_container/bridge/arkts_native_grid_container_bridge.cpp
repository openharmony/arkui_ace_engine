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

#include "core/components_ng/pattern/grid_container/bridge/arkts_native_grid_container_bridge.h"

#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "core/components_ng/base/view_stack_model.h"
#include "core/components_ng/pattern/grid_container/grid_container_model_ng.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t PARAM_INDEX_ZERO = 0;

Local<JSValueRef> GetObjectProperty(EcmaVM* vm, const Local<panda::ObjectRef>& object, const char* name)
{
    return object->Get(vm, panda::StringRef::NewFromUtf8(vm, name));
}

RefPtr<GridContainerInfo> ParseGridContainerInfo(ArkUIRuntimeCallInfo* runtimeCallInfo, EcmaVM* vm)
{
    GridContainerInfo::Builder gridContainerInfoBuilder;
    if (runtimeCallInfo->GetArgsNumber() <= PARAM_INDEX_ZERO) {
        return gridContainerInfoBuilder.Build();
    }

    auto options = runtimeCallInfo->GetCallArgRef(PARAM_INDEX_ZERO);
    if (!options->IsObject(vm)) {
        return gridContainerInfoBuilder.Build();
    }

    auto object = options->ToObject(vm);
    auto columns = GetObjectProperty(vm, object, "columns");
    if (columns->IsNumber()) {
        gridContainerInfoBuilder.SetColumns(columns->Int32Value(vm));
    }

    auto sizeType = GetObjectProperty(vm, object, "sizeType");
    if (sizeType->IsNumber()) {
        gridContainerInfoBuilder.SetSizeType(static_cast<GridSizeType>(sizeType->Int32Value(vm)));
    }

    CalcDimension dimension;
    auto gutter = GetObjectProperty(vm, object, "gutter");
    if (ArkTSUtils::ParseJsDimensionVp(vm, gutter, dimension)) {
        gridContainerInfoBuilder.SetGutterWidth(dimension);
    }

    auto margin = GetObjectProperty(vm, object, "margin");
    if (ArkTSUtils::ParseJsDimensionVp(vm, margin, dimension)) {
        gridContainerInfoBuilder.SetMarginLeft(dimension);
        gridContainerInfoBuilder.SetMarginRight(dimension);
    }
    return gridContainerInfoBuilder.Build();
}
} // namespace

void GridContainerBridge::RegisterGridContainerAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    const char* functionNames[] = { "create", "pop" };
    Local<JSValueRef> funcValues[] = {
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridContainerBridge::Create),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridContainerBridge::Pop),
    };
    auto gridContainer = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(functionNames), functionNames,
        funcValues);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "gridContainer"), gridContainer);
}

ArkUINativeModuleValue GridContainerBridge::Create(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));

    auto containerInfo = ParseGridContainerInfo(runtimeCallInfo, vm);
    GetArkUINodeModifiers()->getGridContainerModifier()->create(static_cast<void*>(&containerInfo));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridContainerBridge::Pop(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    if (ViewStackModel::GetInstance()->IsPrebuilding()) {
        ViewStackModel::GetInstance()->PushPrebuildCompCmd("[JSGridContainer][pop]", []() {
            GetArkUINodeModifiers()->getGridContainerModifier()->pop();
        });
        return panda::JSValueRef::Undefined(vm);
    }
    GetArkUINodeModifiers()->getGridContainerModifier()->pop();
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
