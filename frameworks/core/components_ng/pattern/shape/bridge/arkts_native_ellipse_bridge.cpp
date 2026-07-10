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
#include "core/components_ng/pattern/shape/bridge/arkts_native_ellipse_bridge.h"
#include "core/components_ng/pattern/shape/ellipse_model_ng.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "core/components_ng/pattern/shape/shape_abstract_model.h"
#include "core/components_ng/pattern/shape/bridge/arkts_native_common_shape_bridge.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int NUM_0 = 0;
}

void EllipseBridge::RegisterEllipseAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    const char* functionNames[] = { "create" };

    Local<JSValueRef> funcValues[] = {
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), EllipseBridge::CreateEllipse),
    };

    auto ellipse = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(functionNames), functionNames, funcValues);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "ellipse"), ellipse);
}

ArkUINativeModuleValue EllipseBridge::CreateEllipse(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    GetArkUINodeModifiers()->getEllipseModifier()->createEllipse();

    CalcDimension width;
    CalcDimension height;
    if (runtimeCallInfo->GetArgsNumber() > 0 && firstArg->IsObject(vm)) {
        auto nativeNode = reinterpret_cast<ArkUINodeHandle>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
        CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
        auto paramObj = firstArg->ToObject(vm);
        auto widthVal = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "width"));
        RefPtr<ResourceObject> widthResObj;
        CommonShapeBridge::ParseJsValue(vm, widthVal, width, widthResObj, true);
        auto heightVal = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "height"));
        RefPtr<ResourceObject> heightResObj;
        CommonShapeBridge::ParseJsValue(vm, heightVal, height, heightResObj, false);

        if (LessNotEqual(width.Value(), 0.0)) {
            width.SetValue(0.0);
        }
        if (LessNotEqual(height.Value(), 0.0)) {
            height.SetValue(0.0);
        }
        GetArkUINodeModifiers()->getCommonShapeModifier()->setShapeWidth(
            nativeNode, width.Value(), static_cast<int32_t>(width.Unit()), AceType::RawPtr(widthResObj));
        GetArkUINodeModifiers()->getCommonShapeModifier()->setShapeHeight(
            nativeNode, height.Value(), static_cast<int32_t>(height.Unit()), AceType::RawPtr(heightResObj));
    }
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
