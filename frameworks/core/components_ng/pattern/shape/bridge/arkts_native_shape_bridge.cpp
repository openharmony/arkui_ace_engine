
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

#include "core/components_ng/pattern/shape/bridge/arkts_native_shape_bridge.h"

#include "base/image/pixel_map.h"
#include "base/memory/referenced.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/shape/shape_model_ng.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t NUM_0 = 0;
constexpr int32_t NUM_1 = 1;
constexpr int32_t NUM_2 = 2;
constexpr int32_t NUM_3 = 3;
} // namespace

void ShapeBridge::RegisterShapeAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    const char* functionNames[] = {
        "create",
        "setShapeViewPort",
        "resetShapeViewPort",
        "setShapeMesh",
        "resetShapeMesh",
        "setShapeInitialize",
        "resetShapeInitialize",
    };
    Local<JSValueRef> funcValues[] = {
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ShapeBridge::CreateShape),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ShapeBridge::SetViewPort),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ShapeBridge::ResetViewPort),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ShapeBridge::SetMesh),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ShapeBridge::ResetMesh),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ShapeBridge::SetShapeInitialize),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ShapeBridge::ResetShapeInitialize),
    };
    auto shape = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(functionNames), functionNames, funcValues);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "shape"), shape);
}

ArkUINativeModuleValue ShapeBridge::CreateShape(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    RefPtr<PixelMap> pixMap = nullptr;
#if !defined(PREVIEW) && defined(PIXEL_MAP_SUPPORTED)
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    if (valueArg->IsObject(vm)) {
        pixMap = ArkTSUtils::CreatePixelMapFromNapiValue(vm, valueArg);
    }
#endif

    GetArkUINodeModifiers()->getShapeModifier()->createShape();
    ViewAbstractModel::GetInstance()->SetFocusable(true);
    auto* frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ShapeModelNG::InitBox(frameNode, pixMap);
    return panda::NativePointerRef::New(vm, frameNode);
}

ArkUINativeModuleValue ShapeBridge::SetViewPort(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> optionsArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(optionsArg->IsObject(vm), panda::JSValueRef::Undefined(vm));
    auto options = optionsArg->ToObject(vm);
    auto xArg = options->Get(vm, panda::StringRef::NewFromUtf8(vm, "x"));
    auto yArg = options->Get(vm, panda::StringRef::NewFromUtf8(vm, "y"));
    auto widthArg = options->Get(vm, panda::StringRef::NewFromUtf8(vm, "width"));
    auto heightArg = options->Get(vm, panda::StringRef::NewFromUtf8(vm, "height"));

    CalcDimension dimLeft;
    RefPtr<ResourceObject> dimLeftResObj;
    ArkTSUtils::ParseJsDimensionVp(vm, xArg, dimLeft, dimLeftResObj);
    CalcDimension dimTop;
    RefPtr<ResourceObject> dimTopResObj;
    ArkTSUtils::ParseJsDimensionVp(vm, yArg, dimTop, dimTopResObj);
    CalcDimension dimWidth;
    RefPtr<ResourceObject> dimWidthResObj;
    ArkTSUtils::ParseJsDimensionVp(vm, widthArg, dimWidth, dimWidthResObj);
    CalcDimension dimHeight;
    RefPtr<ResourceObject> dimHeightResObj;
    ArkTSUtils::ParseJsDimensionVp(vm, heightArg, dimHeight, dimHeightResObj);

    std::vector<ArkUI_Float32> dimValues = {
        static_cast<ArkUI_Float32>(dimLeft.Value()),
        static_cast<ArkUI_Float32>(dimTop.Value()),
        static_cast<ArkUI_Float32>(dimWidth.Value()),
        static_cast<ArkUI_Float32>(dimHeight.Value()),
    };
    std::vector<int32_t> dimUnits = {
        static_cast<int32_t>(dimLeft.Unit()),
        static_cast<int32_t>(dimTop.Unit()),
        static_cast<int32_t>(dimWidth.Unit()),
        static_cast<int32_t>(dimHeight.Unit()),
    };
    std::vector<RefPtr<ResourceObject>> resObjArray = { dimLeftResObj, dimTopResObj, dimWidthResObj, dimHeightResObj };
    GetArkUINodeModifiers()->getShapeModifier()->setShapeViewPort(
        nativeNode, dimValues.data(), dimUnits.data(), resObjArray.data());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ShapeBridge::ResetViewPort(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getShapeModifier()->resetShapeViewPort(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ShapeBridge::SetMesh(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> valueArrayArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> columnArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> rowArg = runtimeCallInfo->GetCallArgRef(NUM_3);

    std::vector<ArkUI_Float32> mesh;
    if (valueArrayArg->IsArray(vm)) {
        auto array = Local<panda::ArrayRef>(valueArrayArg);
        auto length = ArkTSUtils::GetArrayLength(vm, array);
        for (size_t i = 0; i < length; i++) {
            Local<JSValueRef> meshItem = panda::ArrayRef::GetValueAt(vm, array, i);
            double vert = 0.0;
            if (ArkTSUtils::ParseJsDouble(vm, meshItem, vert)) {
                mesh.push_back(static_cast<ArkUI_Float32>(vert));
            }
        }
    }

    int32_t column = 0;
    int32_t row = 0;
    if (!ArkTSUtils::ParseJsInteger(vm, columnArg, column) || !ArkTSUtils::ParseJsInteger(vm, rowArg, row)) {
        GetArkUINodeModifiers()->getShapeModifier()->resetShapeMesh(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    GetArkUINodeModifiers()->getShapeModifier()->setShapeMesh(nativeNode, mesh.data(), mesh.size(), column, row);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ShapeBridge::ResetMesh(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getShapeModifier()->resetShapeMesh(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ShapeBridge::SetShapeInitialize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    RefPtr<PixelMap> pixMap = nullptr;
#if !defined(PREVIEW) && defined(PIXEL_MAP_SUPPORTED)
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    if (valueArg->IsObject(vm)) {
        pixMap = ArkTSUtils::CreatePixelMapFromNapiValue(vm, valueArg);
    }
#endif
    ShapeModelNG::InitBox(reinterpret_cast<FrameNode*>(nativeNode), pixMap);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ShapeBridge::ResetShapeInitialize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    ShapeModelNG::InitBox(reinterpret_cast<FrameNode*>(nativeNode), nullptr);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG