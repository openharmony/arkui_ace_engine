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

#include "core/components_ng/pattern/shape/bridge/arkts_native_path_bridge.h"

#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/shape/path_model_ng.h"
#include "core/components_ng/pattern/shape/shape_abstract_model.h"
#include "core/components_ng/pattern/shape/bridge/arkts_native_common_shape_bridge.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;

void ParsePathCommands(EcmaVM* vm, Local<JSValueRef> firstArg, Local<ObjectRef>& paramObj,
    ArkUINodeHandle nativeNode)
{
    auto commandsVal = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "commands"));
    if (!commandsVal->IsString(vm) && !commandsVal->IsObject(vm)) {
        if (ArkTSUtils::IsJsView(vm, firstArg)) {
            GetArkUINodeModifiers()->getPathModifier()->setPathCommands(nativeNode, "undefined", nullptr);
        } else {
            GetArkUINodeModifiers()->getPathModifier()->resetPathCommands(nativeNode);
        }
        return;
    }

    std::string commands;
    RefPtr<ResourceObject> commandsResObj;
    if (commandsVal->IsString(vm)) {
        commands = commandsVal->ToString(vm)->ToString(vm);
    } else if (commandsVal->IsObject(vm)) {
        ArkTSUtils::ParseJsStringFromResource(vm, commandsVal, commands, commandsResObj);
    }
    GetArkUINodeModifiers()->getPathModifier()->setPathCommands(
        nativeNode, commands.c_str(), AceType::RawPtr(commandsResObj));
}
} // namespace

void PathBridge::RegisterPathAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    const char* functionNames[] = { "create", "setPathCommands", "resetPathCommands", "setInitialize" };

    Local<JSValueRef> funcValues[] = {
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PathBridge::CreatePath),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PathBridge::SetPathCommands),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PathBridge::ResetPathCommands),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PathBridge::SetInitialize),
    };

    auto path = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(functionNames), functionNames, funcValues);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "path"), path);
}

ArkUINativeModuleValue PathBridge::CreatePath(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    GetArkUINodeModifiers()->getPathModifier()->createPath();

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
        ParsePathCommands(vm, firstArg, paramObj, nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PathBridge::SetPathCommands(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    if (!secondArg->IsString(vm) && !secondArg->IsObject(vm)) {
        if (ArkTSUtils::IsJsView(vm, firstArg)) {
            GetArkUINodeModifiers()->getPathModifier()->setPathCommands(nativeNode, "undefined", nullptr);
        } else {
            GetArkUINodeModifiers()->getPathModifier()->resetPathCommands(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }

    std::string commands;
    RefPtr<ResourceObject> resObj;
    if (secondArg->IsString(vm)) {
        commands = secondArg->ToString(vm)->ToString(vm);
    } else if (secondArg->IsObject(vm)) {
        ArkTSUtils::ParseJsStringFromResource(vm, secondArg, commands, resObj);
    }
    GetArkUINodeModifiers()->getPathModifier()->setPathCommands(nativeNode, commands.c_str(), AceType::RawPtr(resObj));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PathBridge::ResetPathCommands(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getPathModifier()->resetPathCommands(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PathBridge::SetInitialize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeVal = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> widthVal = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> heightVal = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> commandsVal = runtimeCallInfo->GetCallArgRef(NUM_3);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeVal, vm), true, panda::JSValueRef::Undefined(vm));

    // width
    CalcDimension widthDim;
    RefPtr<ResourceObject> widthResObj;
    if (ArkTSUtils::ParseJsDimensionVp(vm, widthVal, widthDim, widthResObj)) {
        GetArkUINodeModifiers()->getCommonShapeModifier()->setShapeWidth(nativeNode,
            widthDim.Value(), static_cast<int>(widthDim.Unit()), AceType::RawPtr(widthResObj));
    } else {
        GetArkUINodeModifiers()->getCommonShapeModifier()->resetShapeWidth(nativeNode);
    }

    // height
    CalcDimension heightDim;
    RefPtr<ResourceObject> heightResObj;
    if (ArkTSUtils::ParseJsDimensionVp(vm, heightVal, heightDim, heightResObj)) {
        GetArkUINodeModifiers()->getCommonShapeModifier()->setShapeHeight(nativeNode,
            heightDim.Value(), static_cast<int>(heightDim.Unit()), AceType::RawPtr(heightResObj));
    } else {
        GetArkUINodeModifiers()->getCommonShapeModifier()->resetShapeHeight(nativeNode);
    }

    // commands
    if (commandsVal->IsString(vm)) {
        auto commands = commandsVal->ToString(vm)->ToString(vm);
        GetArkUINodeModifiers()->getPathModifier()->setPathCommands(nativeNode, commands.c_str(), nullptr);
    } else if (commandsVal->IsObject(vm)) {
        std::string commands;
        RefPtr<ResourceObject> resObj;
        ArkTSUtils::ParseJsStringFromResource(vm, commandsVal, commands, resObj);
        GetArkUINodeModifiers()->getPathModifier()->setPathCommands(nativeNode, commands.c_str(),
            AceType::RawPtr(resObj));
    } else {
        GetArkUINodeModifiers()->getPathModifier()->resetPathCommands(nativeNode);
    }

    return panda::JSValueRef::Undefined(vm);
}

} // namespace OHOS::Ace::NG

