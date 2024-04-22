/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_frame_node_bridge.h"

#include "jsnapi_expo.h"

#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "bridge/declarative_frontend/engine/jsi/jsi_types.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_render_node_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_utils_bridge.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/custom_frame_node/custom_frame_node.h"
#include "core/components_ng/pattern/custom_frame_node/custom_frame_node_pattern.h"
#include "core/interfaces/arkoala/arkoala_api.h"

namespace OHOS::Ace::NG {
ArkUINodeHandle FrameNodeBridge::GetFrameNode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, nullptr);
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), nullptr);
    auto* nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    return nativeNode;
}
int FrameNodeBridge::GetInstanceId(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, -1);
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(2); // index of instanceId
    CHECK_NULL_RETURN(!thirdArg.IsNull(), -1);
    return thirdArg->ToNumber(vm)->Value();
}

Local<panda::ObjectRef> FrameNodeBridge::CreateEventTargetObject(EcmaVM* vm, const BaseEventInfo& info)
{
    const auto& localOffset = info.GetTarget().area.GetOffset();
    const auto& origin = info.GetTarget().origin;
    const char* keysOfOffset[] = { "x", "y" };
    Local<JSValueRef> valuesOfOffset[] = { panda::NumberRef::New(vm, localOffset.GetX().ConvertToVp()),
        panda::NumberRef::New(vm, localOffset.GetY().ConvertToVp()) };
    auto offset = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keysOfOffset), keysOfOffset, valuesOfOffset);

    const char* keysOfGlobalOffset[] = { "x", "y" };
    Local<JSValueRef> valuesOfGlobalOffset[] = { panda::NumberRef::New(
                                                     vm, (origin.GetX() + localOffset.GetX()).ConvertToVp()),
        panda::NumberRef::New(vm, (origin.GetY() + localOffset.GetY()).ConvertToVp()) };
    auto globalOffset = panda::ObjectRef::NewWithNamedProperties(
        vm, ArraySize(keysOfGlobalOffset), keysOfGlobalOffset, valuesOfGlobalOffset);
    const char* keysOfArea[] = { "position", "globalPosition", "width", "height" };
    Local<JSValueRef> valuesOfArea[] = { offset, globalOffset,
        panda::NumberRef::New(vm, info.GetTarget().area.GetWidth().ConvertToVp()),
        panda::NumberRef::New(vm, info.GetTarget().area.GetHeight().ConvertToVp()) };
    auto area = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keysOfArea), keysOfArea, valuesOfArea);
    auto target = panda::ObjectRef::New(vm);
    target->Set(vm, panda::StringRef::NewFromUtf8(vm, "area"), area);
    return target;
}

Local<panda::ObjectRef> FrameNodeBridge::CreateTouchInfo(
    EcmaVM* vm, const TouchLocationInfo& touchInfo, TouchEventInfo& info)
{
    double density = PipelineBase::GetCurrentDensity();
    const Offset& globalOffset = touchInfo.GetGlobalLocation();
    const Offset& localOffset = touchInfo.GetLocalLocation();
    const Offset& screenOffset = touchInfo.GetScreenLocation();
    const char* keys[] = { "type", "id", "displayX", "displayY", "windowX", "windowY", "screenX", "screenY", "x", "y" };
    Local<JSValueRef> values[] = { panda::NumberRef::New(vm, static_cast<int32_t>(touchInfo.GetTouchType())),
        panda::NumberRef::New(vm, touchInfo.GetFingerId()), panda::NumberRef::New(vm, screenOffset.GetX() / density),
        panda::NumberRef::New(vm, screenOffset.GetY() / density),
        panda::NumberRef::New(vm, globalOffset.GetX() / density),
        panda::NumberRef::New(vm, globalOffset.GetY() / density),
        panda::NumberRef::New(vm, globalOffset.GetX() / density),
        panda::NumberRef::New(vm, globalOffset.GetY() / density),
        panda::NumberRef::New(vm, localOffset.GetX() / density),
        panda::NumberRef::New(vm, localOffset.GetY() / density) };
    auto touchInfoObj = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
    touchInfoObj->SetNativePointerFieldCount(vm, 1);
    touchInfoObj->SetNativePointerField(vm, 0, static_cast<void*>(&info));
    return touchInfoObj;
}

ArkUINativeModuleValue FrameNodeBridge::IsModifiable(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::BooleanRef::New(vm, false));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto result = GetArkUINodeModifiers()->getFrameNodeModifier()->isModifiable(nativeNode);
    return panda::BooleanRef::New(vm, result);
}

ArkUINativeModuleValue FrameNodeBridge::MakeFrameNodeInfo(EcmaVM* vm, ArkUINodeHandle frameNode)
{
    const char* keys[] = { "nodeId", "nodePtr" };
    auto nodeId = GetArkUINodeModifiers()->getFrameNodeModifier()->getIdByNodePtr(frameNode);
    Local<JSValueRef> values[] = { panda::NumberRef::New(vm, nodeId), panda::NativePointerRef::New(vm, frameNode) };
    auto obj = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
    return obj;
}

void AddAttachFuncCallback(EcmaVM* vm, const RefPtr<FrameNode>& node)
{
    auto global = JSNApi::GetGlobalObject(vm);
    auto funcName = panda::StringRef::NewFromUtf8(vm, "__AttachToMainTree__");
    auto obj = global->Get(vm, funcName);
    panda::Local<panda::FunctionRef> attachFunc = obj;
    if (obj->IsFunction()) {
        node->SetOnAttachFunc([vm, func = panda::CopyableGlobal(vm, attachFunc)](int32_t nodeId) {
            panda::Local<panda::JSValueRef> params[] = { panda::NumberRef::New(vm, nodeId) };
            func->Call(vm, func.ToLocal(), params, ArraySize(params));
        });
    }
    funcName = panda::StringRef::NewFromUtf8(vm, "__DetachToMainTree__");
    obj = global->Get(vm, funcName);
    panda::Local<panda::FunctionRef> detachFunc = obj;
    if (detachFunc->IsFunction()) {
        node->SetOnDetachFunc([vm, func = panda::CopyableGlobal(vm, detachFunc)](int32_t nodeId) {
            panda::Local<panda::JSValueRef> params[] = { panda::NumberRef::New(vm, nodeId) };
            func->Call(vm, func.ToLocal(), params, ArraySize(params));
        });
    }
}

ArkUINativeModuleValue FrameNodeBridge::CreateFrameNode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto node = NG::CustomFrameNode::GetOrCreateCustomFrameNode(nodeId);
    node->SetExclusiveEventForChild(true);
    AddAttachFuncCallback(vm, node);
    FrameNodeBridge::SetDrawFunc(node, runtimeCallInfo);
    const char* keys[] = { "nodeId", "nativeStrongRef" };
    Local<JSValueRef> values[] = { panda::NumberRef::New(vm, nodeId), NativeUtilsBridge::CreateStrongRef(vm, node) };
    auto reslut = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
    return reslut;
}

ArkUINativeModuleValue FrameNodeBridge::CreateTypedFrameNode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(1);
    std::string type = firstArg->IsString() ? firstArg->ToString(vm)->ToString() : "";
    static const std::unordered_map<std::string, ArkUINodeType> typeMap = { { "Text", ARKUI_TEXT },
        { "Column", ARKUI_COLUMN }, { "Row", ARKUI_ROW }, { "Stack", ARKUI_STACK } };
    ArkUINodeType nodeType = ARKUI_CUSTOM;
    RefPtr<FrameNode> node;
    auto iter = typeMap.find(type);
    if (iter != typeMap.end()) {
        nodeType = iter->second;
        if (nodeType != ARKUI_CUSTOM) {
            auto nodePtr = GetArkUIFullNodeAPI()->getBasicAPI()->createNode(nodeType, nodeId, 0);
            // let 'node' take the reference, so decrease ref of C node
            node = AceType::Claim(reinterpret_cast<FrameNode*>(nodePtr));
            node->DecRefCount();
            if (node) {
                node->SetExclusiveEventForChild(true);
                AddAttachFuncCallback(vm, node);
            }
        }
    }

    const char* keys[] = { "nodeId", "nativeStrongRef" };
    Local<JSValueRef> values[] = { panda::NumberRef::New(vm, nodeId), NativeUtilsBridge::CreateStrongRef(vm, node) };
    auto reslut = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
    return reslut;
}

ArkUINativeModuleValue FrameNodeBridge::Invalidate(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getFrameNodeModifier()->invalidate(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

void FrameNodeBridge::SetDrawFunc(const RefPtr<FrameNode>& frameNode, ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    CHECK_NULL_VOID(frameNode);
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_VOID(firstArg->IsObject());
    auto obj = Local<panda::ObjectRef>(firstArg);
    auto funcName = panda::StringRef::NewFromUtf8(vm, "onDraw");
    auto funcObj = obj->Get(vm, funcName);
    CHECK_NULL_VOID(funcObj->IsFunction());
    auto drawCallback = [vm, object = JsWeak(panda::CopyableGlobal(vm, obj))](NG::DrawingContext& context) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        auto funcName = panda::StringRef::NewFromUtf8(vm, "onDraw");
        RenderNodeBridge::FireDrawCallback(vm, object, context, funcName);
    };
    auto pattern = frameNode->GetPattern<NG::CustomFrameNodePattern>();
    pattern->SetDrawCallback(std::move(drawCallback));
}

ArkUINativeModuleValue FrameNodeBridge::AppendChild(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::BooleanRef::New(vm, true));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto childNativeNode = nodePtr(secondArg->ToNativePointer(vm)->Value());
    auto result = GetArkUINodeModifiers()->getFrameNodeModifier()->appendChild(nativeNode, childNativeNode);
    return panda::BooleanRef::New(vm, result);
}
ArkUINativeModuleValue FrameNodeBridge::InsertChildAfter(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::BooleanRef::New(vm, true));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto child = nodePtr(secondArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(2); // 2 : index to get the insert node
    if (thirdArg.IsNull()) {
        GetArkUINodeModifiers()->getFrameNodeModifier()->insertChildAfter(nativeNode, child, nullptr);
        return panda::JSValueRef::Undefined(vm);
    }
    auto sibling = nodePtr(thirdArg->ToNativePointer(vm)->Value());
    auto result = GetArkUINodeModifiers()->getFrameNodeModifier()->insertChildAfter(nativeNode, child, sibling);
    return panda::BooleanRef::New(vm, result);
}
ArkUINativeModuleValue FrameNodeBridge::RemoveChild(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto childNativeNode = nodePtr(secondArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getFrameNodeModifier()->removeChild(nativeNode, childNativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue FrameNodeBridge::ClearChildren(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getFrameNodeModifier()->clearChildren(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue FrameNodeBridge::GetChildrenCount(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::NumberRef::New(vm, 0));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto number = GetArkUINodeModifiers()->getFrameNodeModifier()->getChildrenCount(nativeNode);
    return panda::NumberRef::New(vm, number);
}
ArkUINativeModuleValue FrameNodeBridge::GetChild(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    int index = secondArg->ToNumber(vm)->Value();
    auto nodePtr = GetArkUINodeModifiers()->getFrameNodeModifier()->getChild(nativeNode, index);
    CHECK_NULL_RETURN(nodePtr, panda::JSValueRef::Undefined(vm));
    return FrameNodeBridge::MakeFrameNodeInfo(vm, nodePtr);
}
ArkUINativeModuleValue FrameNodeBridge::GetFirst(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodePtr = GetArkUINodeModifiers()->getFrameNodeModifier()->getFirst(nativeNode);
    CHECK_NULL_RETURN(nodePtr, panda::JSValueRef::Undefined(vm));
    return FrameNodeBridge::MakeFrameNodeInfo(vm, nodePtr);
}
ArkUINativeModuleValue FrameNodeBridge::GetNextSibling(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodePtr = GetArkUINodeModifiers()->getFrameNodeModifier()->getNextSibling(nativeNode);
    CHECK_NULL_RETURN(nodePtr, panda::JSValueRef::Undefined(vm));
    return FrameNodeBridge::MakeFrameNodeInfo(vm, nodePtr);
}
ArkUINativeModuleValue FrameNodeBridge::GetPreviousSibling(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodePtr = GetArkUINodeModifiers()->getFrameNodeModifier()->getPreviousSibling(nativeNode);
    CHECK_NULL_RETURN(nodePtr, panda::JSValueRef::Undefined(vm));
    return FrameNodeBridge::MakeFrameNodeInfo(vm, nodePtr);
}
ArkUINativeModuleValue FrameNodeBridge::GetParent(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodePtr = GetArkUINodeModifiers()->getFrameNodeModifier()->getParent(nativeNode);
    CHECK_NULL_RETURN(nodePtr, panda::JSValueRef::Undefined(vm));
    return FrameNodeBridge::MakeFrameNodeInfo(vm, nodePtr);
}
ArkUINativeModuleValue FrameNodeBridge::GetIdByNodePtr(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::NumberRef::New(vm, -1));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeId = GetArkUINodeModifiers()->getFrameNodeModifier()->getIdByNodePtr(nativeNode);
    return panda::NumberRef::New(vm, nodeId);
}
ArkUINativeModuleValue FrameNodeBridge::GetPositionToParent(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<Framework::ArrayRef> valueArray = Framework::ArrayRef::New(vm, 2);
    auto position = GetArkUINodeModifiers()->getFrameNodeModifier()->getPositionToParent(nativeNode);
    CHECK_NULL_RETURN(position, panda::JSValueRef::Undefined(vm));
    Framework::ArrayRef::SetValueAt(vm, valueArray, 0, panda::NumberRef::New(vm, position[0]));
    Framework::ArrayRef::SetValueAt(vm, valueArray, 1, panda::NumberRef::New(vm, position[1]));
    return valueArray;
}
ArkUINativeModuleValue FrameNodeBridge::GetPositionToWindow(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<Framework::ArrayRef> valueArray = Framework::ArrayRef::New(vm, 2);
    auto position = GetArkUINodeModifiers()->getFrameNodeModifier()->getPositionToWindow(nativeNode);
    CHECK_NULL_RETURN(position, panda::JSValueRef::Undefined(vm));
    Framework::ArrayRef::SetValueAt(vm, valueArray, 0, panda::NumberRef::New(vm, position[0]));
    Framework::ArrayRef::SetValueAt(vm, valueArray, 1, panda::NumberRef::New(vm, position[1]));
    return valueArray;
}
ArkUINativeModuleValue FrameNodeBridge::GetMeasuredSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<Framework::ArrayRef> valueArray = Framework::ArrayRef::New(vm, 2);
    auto size = GetArkUINodeModifiers()->getFrameNodeModifier()->getMeasuredSize(nativeNode);
    CHECK_NULL_RETURN(size, panda::JSValueRef::Undefined(vm));
    Framework::ArrayRef::SetValueAt(vm, valueArray, 0, panda::NumberRef::New(vm, size[0]));
    Framework::ArrayRef::SetValueAt(vm, valueArray, 1, panda::NumberRef::New(vm, size[1]));
    return valueArray;
}
ArkUINativeModuleValue FrameNodeBridge::GetLayoutPosition(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<Framework::ArrayRef> valueArray = Framework::ArrayRef::New(vm, 2);
    auto position = GetArkUINodeModifiers()->getFrameNodeModifier()->getLayoutPosition(nativeNode);
    CHECK_NULL_RETURN(position, panda::JSValueRef::Undefined(vm));
    Framework::ArrayRef::SetValueAt(vm, valueArray, 0, panda::NumberRef::New(vm, position[0]));
    Framework::ArrayRef::SetValueAt(vm, valueArray, 1, panda::NumberRef::New(vm, position[1]));
    return valueArray;
}
ArkUINativeModuleValue FrameNodeBridge::GetConfigBorderWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<Framework::ArrayRef> valueArray = Framework::ArrayRef::New(vm, 8);
    ArkUI_Float32 borderWidthValue[4];
    ArkUI_Int32 borderWidthUnit[4];
    GetArkUINodeModifiers()->getCommonModifier()->getBorderWidthDimension(
        nativeNode, borderWidthValue, borderWidthUnit);
    for (int i = 0; i < 4; i++) {
        Framework::ArrayRef::SetValueAt(vm, valueArray, i * 2, panda::NumberRef::New(vm, borderWidthValue[i]));
        Framework::ArrayRef::SetValueAt(vm, valueArray, i * 2 + 1, panda::NumberRef::New(vm, borderWidthUnit[i]));
    }
    return valueArray;
}
ArkUINativeModuleValue FrameNodeBridge::GetConfigPadding(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<Framework::ArrayRef> valueArray = Framework::ArrayRef::New(vm, 8);
    ArkUI_Float32 paddingValue[4];
    ArkUI_Int32 paddingUnit[4];
    GetArkUINodeModifiers()->getCommonModifier()->getPaddingDimension(nativeNode, paddingValue, paddingUnit);
    for (int i = 0; i < 4; i++) {
        Framework::ArrayRef::SetValueAt(vm, valueArray, i * 2, panda::NumberRef::New(vm, paddingValue[i]));
        Framework::ArrayRef::SetValueAt(vm, valueArray, i * 2 + 1, panda::NumberRef::New(vm, paddingUnit[i]));
    }
    return valueArray;
}
ArkUINativeModuleValue FrameNodeBridge::GetConfigMargin(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<Framework::ArrayRef> valueArray = Framework::ArrayRef::New(vm, 8);
    ArkUI_Float32 marginValue[4];
    ArkUI_Int32 marginUnit[4];
    GetArkUINodeModifiers()->getCommonModifier()->getMarginDimension(nativeNode, marginValue, marginUnit);
    for (int i = 0; i < 4; i++) {
        Framework::ArrayRef::SetValueAt(vm, valueArray, i * 2, panda::NumberRef::New(vm, marginValue[i]));
        Framework::ArrayRef::SetValueAt(vm, valueArray, i * 2 + 1, panda::NumberRef::New(vm, marginUnit[i]));
    }
    return valueArray;
}
ArkUINativeModuleValue FrameNodeBridge::GetConfigSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<Framework::ArrayRef> valueArray = Framework::ArrayRef::New(vm, 4);
    ArkUI_Float32 sizeValue[2];
    ArkUI_Int32 sizeUnit[2];
    GetArkUINodeModifiers()->getCommonModifier()->getConfigSize(nativeNode, sizeValue, sizeUnit);
    for (int i = 0; i < 2; i++) {
        Framework::ArrayRef::SetValueAt(vm, valueArray, i * 2, panda::NumberRef::New(vm, sizeValue[i]));
        Framework::ArrayRef::SetValueAt(vm, valueArray, i * 2 + 1, panda::NumberRef::New(vm, sizeUnit[i]));
    }
    return valueArray;
}
ArkUINativeModuleValue FrameNodeBridge::GetId(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::StringRef::NewFromUtf8(vm, ""));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::StringRef::NewFromUtf8(vm, ""));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto inspectorId = GetArkUINodeModifiers()->getFrameNodeModifier()->getInspectorId(nativeNode);
    return panda::StringRef::NewFromUtf8(vm, inspectorId);
}
ArkUINativeModuleValue FrameNodeBridge::GetNodeType(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::StringRef::NewFromUtf8(vm, ""));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::StringRef::NewFromUtf8(vm, ""));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeType = GetArkUINodeModifiers()->getFrameNodeModifier()->getNodeType(nativeNode);
    return panda::StringRef::NewFromUtf8(vm, nodeType);
}
ArkUINativeModuleValue FrameNodeBridge::GetOpacity(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NumberRef::New(vm, 0));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::NumberRef::New(vm, 0));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto opacity = GetArkUINodeModifiers()->getCommonModifier()->getOpacity(nativeNode);
    return panda::NumberRef::New(vm, opacity);
}
ArkUINativeModuleValue FrameNodeBridge::IsVisible(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::BooleanRef::New(vm, false));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::BooleanRef::New(vm, false));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto visible = GetArkUINodeModifiers()->getFrameNodeModifier()->isVisible(nativeNode);
    return panda::BooleanRef::New(vm, visible);
}
ArkUINativeModuleValue FrameNodeBridge::IsClipToFrame(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::BooleanRef::New(vm, false));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::BooleanRef::New(vm, false));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto clip = GetArkUINodeModifiers()->getCommonModifier()->getClip(nativeNode);
    return panda::BooleanRef::New(vm, clip != 0);
}
ArkUINativeModuleValue FrameNodeBridge::IsAttached(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::BooleanRef::New(vm, false));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::BooleanRef::New(vm, false));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto isAttached = GetArkUINodeModifiers()->getFrameNodeModifier()->isVisible(nativeNode);
    return panda::BooleanRef::New(vm, isAttached);
}
ArkUINativeModuleValue FrameNodeBridge::GetInspectorInfo(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::StringRef::NewFromUtf8(vm, "{}"));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::StringRef::NewFromUtf8(vm, "{}"));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto inspectorInfo = GetArkUINodeModifiers()->getFrameNodeModifier()->getInspectorInfo(nativeNode);
    return panda::StringRef::NewFromUtf8(vm, inspectorInfo);
}
Local<panda::ObjectRef> FrameNodeBridge::CreateGestureEventInfo(EcmaVM* vm, GestureEvent& info)
{
    const Offset& globalOffset = info.GetGlobalLocation();
    const Offset& localOffset = info.GetLocalLocation();
    const Offset& screenOffset = info.GetScreenLocation();
    double density = PipelineBase::GetCurrentDensity();

    const char* keys[] = { "displayX", "displayY", "windowX", "windowY", "screenX", "screenY", "x", "y", "timestamp",
        "source", "pressure" };
    Local<JSValueRef> values[] = { panda::NumberRef::New(vm, screenOffset.GetX() / density),
        panda::NumberRef::New(vm, screenOffset.GetY() / density),
        panda::NumberRef::New(vm, globalOffset.GetX() / density),
        panda::NumberRef::New(vm, globalOffset.GetY() / density),
        panda::NumberRef::New(vm, globalOffset.GetX() / density),
        panda::NumberRef::New(vm, globalOffset.GetY() / density),
        panda::NumberRef::New(vm, localOffset.GetX() / density),
        panda::NumberRef::New(vm, localOffset.GetY() / density),
        panda::NumberRef::New(vm, static_cast<double>(info.GetTimeStamp().time_since_epoch().count())),
        panda::NumberRef::New(vm, static_cast<int32_t>(info.GetSourceDevice())),
        panda::NumberRef::New(vm, info.GetForce()) };
    auto obj = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
    if (info.GetTiltX().has_value()) {
        obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "tiltX"),
            panda::NumberRef::New(vm, static_cast<int32_t>(info.GetTiltX().value())));
    }
    if (info.GetTiltY().has_value()) {
        obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "tiltY"),
            panda::NumberRef::New(vm, static_cast<int32_t>(info.GetTiltY().value())));
    }
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "sourceTool"),
        panda::NumberRef::New(vm, static_cast<int32_t>(static_cast<int32_t>(info.GetSourceTool()))));
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "target"), CreateEventTargetObject(vm, info));
    return obj;
}

ArkUINativeModuleValue FrameNodeBridge::SetOnClick(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto* nativeNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> secondeArg = runtimeCallInfo->GetCallArgRef(1);
    if (secondeArg->IsUndefined()) {
        NG::ViewAbstract::ClearJSFrameNodeOnClick(frameNode);
        return panda::JSValueRef::Undefined(vm);
    }
    CHECK_NULL_RETURN(secondeArg->IsFunction(), panda::JSValueRef::Undefined(vm));
    auto obj = secondeArg->ToObject(vm);
    auto containerId = GetInstanceId(runtimeCallInfo);
    CHECK_NULL_RETURN(containerId != -1, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = obj;
    auto onClick = [vm, func = JsWeak(panda::CopyableGlobal(vm, func)), node = AceType::WeakClaim(frameNode),
                       containerId](GestureEvent& info) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        ContainerScope scope(containerId);
        auto function = func.Lock();
        CHECK_NULL_VOID(!function.IsEmpty());
        CHECK_NULL_VOID(function->IsFunction());
        PipelineContext::SetCallBackNode(node);
        auto obj = CreateGestureEventInfo(vm, info);
        panda::Local<panda::JSValueRef> params[1] = { obj };
        function->Call(vm, function.ToLocal(), params, 1);
    };
    NG::ViewAbstract::SetJSFrameNodeOnClick(frameNode, std::move(onClick));
    return panda::JSValueRef::Undefined(vm);
}

Local<panda::ObjectRef> FrameNodeBridge::CreateTouchEventInfo(EcmaVM* vm, TouchEventInfo& info)
{
    const char* keys[] = { "source", "timestamp", "target", "pressure" };
    Local<JSValueRef> values[] = { panda::NumberRef::New(vm, static_cast<int32_t>(info.GetSourceDevice())),
        panda::NumberRef::New(vm, static_cast<double>(info.GetTimeStamp().time_since_epoch().count())),
        CreateEventTargetObject(vm, info), panda::NumberRef::New(vm, info.GetForce()) };
    auto eventObj = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
    eventObj->SetNativePointerFieldCount(vm, 1);
    if (info.GetTiltX().has_value()) {
        eventObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "tiltX"),
            panda::NumberRef::New(vm, static_cast<int32_t>(info.GetTiltX().value())));
    }
    if (info.GetTiltY().has_value()) {
        eventObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "tiltY"),
            panda::NumberRef::New(vm, static_cast<int32_t>(info.GetTiltY().value())));
    }
    eventObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "sourceTool"),
        panda::NumberRef::New(vm, static_cast<int32_t>(static_cast<int32_t>(info.GetSourceTool()))));

    auto touchArr = panda::ArrayRef::New(vm);
    const std::list<TouchLocationInfo>& touchList = info.GetTouches();
    uint32_t idx = 0;
    for (const TouchLocationInfo& location : touchList) {
        panda::ArrayRef::SetValueAt(vm, touchArr, idx++, CreateTouchInfo(vm, location, info));
    }
    eventObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "touches"), touchArr);

    auto changeTouchArr = panda::ArrayRef::New(vm);
    idx = 0; // reset index counter
    const std::list<TouchLocationInfo>& changeTouch = info.GetChangedTouches();
    for (const TouchLocationInfo& change : changeTouch) {
        panda::ArrayRef::SetValueAt(vm, changeTouchArr, idx++, CreateTouchInfo(vm, change, info));
    }
    if (changeTouch.size() > 0) {
        eventObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "type"),
            panda::NumberRef::New(vm, static_cast<int32_t>(changeTouch.front().GetTouchType())));
    }
    eventObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "changedTouches"), changeTouchArr);
    eventObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "stopPropagation"),
        panda::FunctionRef::New(vm, Framework::JsStopPropagation));
    eventObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "getHistoricalPoints"),
        panda::FunctionRef::New(vm, Framework::JsGetHistoricalPoints));
    eventObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "preventDefault"),
        panda::FunctionRef::New(vm, Framework::JsPreventDefault));
    eventObj->SetNativePointerField(vm, 0, static_cast<void*>(&info));
    return eventObj;
}

ArkUINativeModuleValue FrameNodeBridge::SetOnTouch(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto* nativeNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> secondeArg = runtimeCallInfo->GetCallArgRef(1);
    if (secondeArg->IsUndefined()) {
        NG::ViewAbstract::ClearJSFrameNodeOnTouch(frameNode);
        return panda::JSValueRef::Undefined(vm);
    }
    CHECK_NULL_RETURN(secondeArg->IsFunction(), panda::JSValueRef::Undefined(vm));
    auto obj = secondeArg->ToObject(vm);
    auto containerId = Container::CurrentId();
    panda::Local<panda::FunctionRef> func = obj;
    auto onTouch = [vm, func = JsWeak(panda::CopyableGlobal(vm, func)), node = AceType::WeakClaim(frameNode),
                       containerId](TouchEventInfo& info) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        ContainerScope scope(containerId);
        auto function = func.Lock();
        CHECK_NULL_VOID(!function.IsEmpty());
        CHECK_NULL_VOID(function->IsFunction());
        PipelineContext::SetCallBackNode(node);
        auto eventObj = CreateTouchEventInfo(vm, info);
        panda::Local<panda::JSValueRef> params[1] = { eventObj };
        function->Call(vm, function.ToLocal(), params, 1);
    };
    NG::ViewAbstract::SetJSFrameNodeOnTouch(frameNode, std::move(onTouch));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue FrameNodeBridge::SetOnAppear(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto* nativeNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> secondeArg = runtimeCallInfo->GetCallArgRef(1);
    if (secondeArg->IsUndefined()) {
        NG::ViewAbstract::ClearJSFrameNodeOnAppear(frameNode);
        return panda::JSValueRef::Undefined(vm);
    }
    CHECK_NULL_RETURN(secondeArg->IsFunction(), panda::JSValueRef::Undefined(vm));
    auto obj = secondeArg->ToObject(vm);
    auto containerId = GetInstanceId(runtimeCallInfo);
    CHECK_NULL_RETURN(containerId != -1, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = obj;
    auto onAppear = [vm, func = JsWeak(panda::CopyableGlobal(vm, func)), node = AceType::WeakClaim(frameNode),
                        containerId]() {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        ContainerScope scope(containerId);
        auto function = func.Lock();
        CHECK_NULL_VOID(!function.IsEmpty());
        CHECK_NULL_VOID(function->IsFunction());
        PipelineContext::SetCallBackNode(node);
        function->Call(vm, function.ToLocal(), nullptr, 0);
    };
    NG::ViewAbstract::SetJSFrameNodeOnAppear(frameNode, std::move(onAppear));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue FrameNodeBridge::SetOnDisappear(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto* nativeNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> secondeArg = runtimeCallInfo->GetCallArgRef(1);
    if (secondeArg->IsUndefined()) {
        NG::ViewAbstract::ClearJSFrameNodeOnDisappear(frameNode);
        return panda::JSValueRef::Undefined(vm);
    }
    CHECK_NULL_RETURN(secondeArg->IsFunction(), panda::JSValueRef::Undefined(vm));
    auto obj = secondeArg->ToObject(vm);
    auto containerId = GetInstanceId(runtimeCallInfo);
    CHECK_NULL_RETURN(containerId != -1, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = obj;
    auto onDisappear = [vm, func = JsWeak(panda::CopyableGlobal(vm, func)), node = AceType::WeakClaim(frameNode),
                           containerId]() {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        ContainerScope scope(containerId);
        auto function = func.Lock();
        CHECK_NULL_VOID(!function.IsEmpty());
        CHECK_NULL_VOID(function->IsFunction());
        PipelineContext::SetCallBackNode(node);
        function->Call(vm, function.ToLocal(), nullptr, 0);
    };
    NG::ViewAbstract::SetJSFrameNodeOnDisappear(frameNode, std::move(onDisappear));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue FrameNodeBridge::SetOnKeyEvent(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto* nativeNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> secondeArg = runtimeCallInfo->GetCallArgRef(1);
    if (secondeArg->IsUndefined()) {
        NG::ViewAbstract::ClearJSFrameNodeOnKeyCallback(frameNode);
        return panda::JSValueRef::Undefined(vm);
    }
    CHECK_NULL_RETURN(secondeArg->IsFunction(), panda::JSValueRef::Undefined(vm));
    auto obj = secondeArg->ToObject(vm);
    auto containerId = GetInstanceId(runtimeCallInfo);
    CHECK_NULL_RETURN(containerId != -1, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = obj;
    auto onKeyEvent = [vm, func = JsWeak(panda::CopyableGlobal(vm, func)), node = AceType::WeakClaim(frameNode),
                          containerId](KeyEventInfo& info) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        ContainerScope scope(containerId);
        auto function = func.Lock();
        CHECK_NULL_VOID(!function.IsEmpty());
        CHECK_NULL_VOID(function->IsFunction());
        PipelineContext::SetCallBackNode(node);
        const char* keys[] = { "type", "keyCode", "keyText", "keySource", "deviceId", "metaKey", "timestamp",
            "stopPropagation", "intentionCode" };
        Local<JSValueRef> values[] = { panda::NumberRef::New(vm, static_cast<int32_t>(info.GetKeyType())),
            panda::NumberRef::New(vm, static_cast<int32_t>(info.GetKeyCode())),
            panda::StringRef::NewFromUtf8(vm, info.GetKeyText()),
            panda::NumberRef::New(vm, static_cast<int32_t>(info.GetKeySource())),
            panda::NumberRef::New(vm, info.GetDeviceId()), panda::NumberRef::New(vm, info.GetMetaKey()),
            panda::NumberRef::New(vm, static_cast<double>(info.GetTimeStamp().time_since_epoch().count())),
            panda::FunctionRef::New(vm, Framework::JsStopPropagation),
            panda::NumberRef::New(vm, static_cast<int32_t>(info.GetKeyIntention())) };
        auto obj = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
        obj->SetNativePointerFieldCount(vm, 1);
        obj->SetNativePointerField(vm, 0, static_cast<void*>(&info));
        panda::Local<panda::JSValueRef> params[] = { obj };
        function->Call(vm, function.ToLocal(), params, 1);
    };

    NG::ViewAbstract::SetJSFrameNodeOnKeyCallback(frameNode, std::move(onKeyEvent));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue FrameNodeBridge::SetOnFocus(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto* nativeNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> secondeArg = runtimeCallInfo->GetCallArgRef(1);
    if (secondeArg->IsUndefined()) {
        NG::ViewAbstract::ClearJSFrameNodeOnFocusCallback(frameNode);
        return panda::JSValueRef::Undefined(vm);
    }
    CHECK_NULL_RETURN(secondeArg->IsFunction(), panda::JSValueRef::Undefined(vm));
    auto obj = secondeArg->ToObject(vm);
    auto containerId = GetInstanceId(runtimeCallInfo);
    CHECK_NULL_RETURN(containerId != -1, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = obj;
    auto onFocus = [vm, func = JsWeak(panda::CopyableGlobal(vm, func)), node = AceType::WeakClaim(frameNode),
                       containerId]() {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        ContainerScope scope(containerId);
        auto function = func.Lock();
        CHECK_NULL_VOID(!function.IsEmpty());
        CHECK_NULL_VOID(function->IsFunction());
        PipelineContext::SetCallBackNode(node);
        function->Call(vm, function.ToLocal(), nullptr, 0);
    };
    NG::ViewAbstract::SetJSFrameNodeOnFocusCallback(frameNode, std::move(onFocus));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue FrameNodeBridge::SetOnBlur(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto* nativeNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> secondeArg = runtimeCallInfo->GetCallArgRef(1);
    if (secondeArg->IsUndefined()) {
        NG::ViewAbstract::ClearJSFrameNodeOnBlurCallback(frameNode);
        return panda::JSValueRef::Undefined(vm);
    }
    CHECK_NULL_RETURN(secondeArg->IsFunction(), panda::JSValueRef::Undefined(vm));
    auto obj = secondeArg->ToObject(vm);
    auto containerId = GetInstanceId(runtimeCallInfo);
    CHECK_NULL_RETURN(containerId != -1, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = obj;
    auto onBlur = [vm, func = JsWeak(panda::CopyableGlobal(vm, func)), node = AceType::WeakClaim(frameNode),
                      containerId]() {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        ContainerScope scope(containerId);
        auto function = func.Lock();
        CHECK_NULL_VOID(!function.IsEmpty());
        CHECK_NULL_VOID(function->IsFunction());
        PipelineContext::SetCallBackNode(node);
        function->Call(vm, function.ToLocal(), nullptr, 0);
    };
    NG::ViewAbstract::SetJSFrameNodeOnBlurCallback(frameNode, std::move(onBlur));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue FrameNodeBridge::SetOnHover(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto* nativeNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> secondeArg = runtimeCallInfo->GetCallArgRef(1);
    if (secondeArg->IsUndefined()) {
        NG::ViewAbstract::ClearJSFrameNodeOnHover(frameNode);
        return panda::JSValueRef::Undefined(vm);
    }
    CHECK_NULL_RETURN(secondeArg->IsFunction(), panda::JSValueRef::Undefined(vm));
    auto obj = secondeArg->ToObject(vm);
    auto containerId = GetInstanceId(runtimeCallInfo);
    CHECK_NULL_RETURN(containerId != -1, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = obj;
    auto onHover = [vm, func = JsWeak(panda::CopyableGlobal(vm, func)), node = AceType::WeakClaim(frameNode),
                       containerId](bool isHover, HoverInfo& hoverInfo) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        ContainerScope scope(containerId);
        auto function = func.Lock();
        CHECK_NULL_VOID(!function.IsEmpty());
        CHECK_NULL_VOID(function->IsFunction());
        PipelineContext::SetCallBackNode(node);
        auto isHoverParam = panda::BooleanRef::New(vm, isHover);
        const char* keys[] = {
            "stopPropagation",
            "timestamp",
            "source",
            "target",
        };
        Local<JSValueRef> values[] = { panda::FunctionRef::New(vm, Framework::JsStopPropagation),
            panda::NumberRef::New(vm, static_cast<double>(hoverInfo.GetTimeStamp().time_since_epoch().count())),
            panda::NumberRef::New(vm, static_cast<int32_t>(hoverInfo.GetSourceDevice())),
            CreateEventTargetObject(vm, hoverInfo) };
        auto obj = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
        obj->SetNativePointerFieldCount(vm, 1);
        obj->SetNativePointerField(vm, 0, static_cast<void*>(&hoverInfo));
        panda::Local<panda::JSValueRef> params[] = { isHoverParam, obj };
        function->Call(vm, function.ToLocal(), params, ArraySize(params));
    };
    NG::ViewAbstract::SetJSFrameNodeOnHover(frameNode, std::move(onHover));
    return panda::JSValueRef::Undefined(vm);
}

Local<panda::ObjectRef> FrameNodeBridge::CreateMouseInfo(EcmaVM* vm, MouseInfo& info)
{
    const Offset& globalOffset = info.GetGlobalLocation();
    const Offset& localOffset = info.GetLocalLocation();
    const Offset& screenOffset = info.GetScreenLocation();
    double density = PipelineBase::GetCurrentDensity();
    const char* keys[] = { "button", "action", "displayX", "displayY", "windowX", "windowY", "screenX", "screenY", "x",
        "y", "timestamp", "stopPropagation", "source", "pressure" };
    Local<JSValueRef> values[] = { panda::NumberRef::New(vm, static_cast<int32_t>(info.GetButton())),
        panda::NumberRef::New(vm, static_cast<int32_t>(info.GetAction())),
        panda::NumberRef::New(vm, screenOffset.GetX() / density),
        panda::NumberRef::New(vm, screenOffset.GetY() / density),
        panda::NumberRef::New(vm, globalOffset.GetX() / density),
        panda::NumberRef::New(vm, globalOffset.GetY() / density),
        panda::NumberRef::New(vm, globalOffset.GetX() / density),
        panda::NumberRef::New(vm, globalOffset.GetY() / density),
        panda::NumberRef::New(vm, localOffset.GetX() / density),
        panda::NumberRef::New(vm, localOffset.GetY() / density),
        panda::NumberRef::New(vm, static_cast<double>(info.GetTimeStamp().time_since_epoch().count())),
        panda::FunctionRef::New(vm, Framework::JsStopPropagation),
        panda::NumberRef::New(vm, static_cast<int32_t>(info.GetSourceDevice())),
        panda::NumberRef::New(vm, info.GetForce()) };
    auto obj = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
    obj->SetNativePointerFieldCount(vm, 1);
    if (info.GetTiltX().has_value()) {
        obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "tiltX"),
            panda::NumberRef::New(vm, static_cast<int32_t>(info.GetTiltX().value())));
    }
    if (info.GetTiltY().has_value()) {
        obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "tiltY"),
            panda::NumberRef::New(vm, static_cast<int32_t>(info.GetTiltY().value())));
    }
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "sourceTool"),
        panda::NumberRef::New(vm, static_cast<int32_t>(static_cast<int32_t>(info.GetSourceTool()))));
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "target"), CreateEventTargetObject(vm, info));
    obj->SetNativePointerField(vm, 0, static_cast<void*>(&info));
    return obj;
}

ArkUINativeModuleValue FrameNodeBridge::SetOnMouse(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto* nativeNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> secondeArg = runtimeCallInfo->GetCallArgRef(1);
    if (secondeArg->IsUndefined()) {
        NG::ViewAbstract::ClearJSFrameNodeOnMouse(frameNode);
        return panda::JSValueRef::Undefined(vm);
    }
    CHECK_NULL_RETURN(secondeArg->IsFunction(), panda::JSValueRef::Undefined(vm));
    auto obj = secondeArg->ToObject(vm);
    auto containerId = GetInstanceId(runtimeCallInfo);
    CHECK_NULL_RETURN(containerId != -1, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = obj;
    auto onMouse = [vm, func = JsWeak(panda::CopyableGlobal(vm, func)), node = AceType::WeakClaim(frameNode),
                       containerId](MouseInfo& info) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        ContainerScope scope(containerId);
        auto function = func.Lock();
        CHECK_NULL_VOID(!function.IsEmpty());
        CHECK_NULL_VOID(function->IsFunction());
        PipelineContext::SetCallBackNode(node);
        auto obj = CreateMouseInfo(vm, info);
        panda::Local<panda::JSValueRef> params[1] = { obj };
        function->Call(vm, function.ToLocal(), params, 1);
    };
    NG::ViewAbstract::SetJSFrameNodeOnMouse(frameNode, std::move(onMouse));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue FrameNodeBridge::SetOnSizeChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto* nativeNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> secondeArg = runtimeCallInfo->GetCallArgRef(1);
    if (secondeArg->IsUndefined()) {
        NG::ViewAbstract::ClearJSFrameNodeOnSizeChange(frameNode);
        return panda::JSValueRef::Undefined(vm);
    }
    CHECK_NULL_RETURN(secondeArg->IsFunction(), panda::JSValueRef::Undefined(vm));
    auto obj = secondeArg->ToObject(vm);
    auto containerId = GetInstanceId(runtimeCallInfo);
    CHECK_NULL_RETURN(containerId != -1, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = obj;
    auto onSizeChange = [vm, func = JsWeak(panda::CopyableGlobal(vm, func)), node = AceType::WeakClaim(frameNode),
                            containerId](const NG::RectF& oldRect, const NG::RectF& rect) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        ContainerScope scope(containerId);
        auto function = func.Lock();
        CHECK_NULL_VOID(!function.IsEmpty());
        CHECK_NULL_VOID(function->IsFunction());
        PipelineContext::SetCallBackNode(node);
        double density = PipelineBase::GetCurrentDensity();
        const char* keys[] = { "width", "height" };
        Local<JSValueRef> oldValues[] = { panda::NumberRef::New(vm, oldRect.Width() / density),
            panda::NumberRef::New(vm, oldRect.Height() / density) };
        auto oldSize = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, oldValues);
        Local<JSValueRef> newValues[] = { panda::NumberRef::New(vm, rect.Width() / density),
            panda::NumberRef::New(vm, rect.Height() / density) };
        auto newSize = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, newValues);
        panda::Local<panda::JSValueRef> params[2] = { oldSize, newSize };
        function->Call(vm, function.ToLocal(), params, 2);
    };
    NG::ViewAbstract::SetJSFrameNodeOnSizeChange(frameNode, std::move(onSizeChange));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue FrameNodeBridge::PropertyUpdate(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getFrameNodeModifier()->propertyUpdate(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue FrameNodeBridge::RegisterFrameCallback(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsFunction(), panda::JSValueRef::Undefined(vm));
    auto obj = firstArg->ToObject(vm);
    auto containerId = Container::CurrentId();
    panda::Local<panda::FunctionRef> func = obj;
    auto getVsyncFunc = [vm, func = JsWeak(panda::CopyableGlobal(vm, func)), containerId]() {
        panda::LocalScope pandaScope(vm);
        ContainerScope scope(containerId);
        auto function = func.Lock();
        CHECK_NULL_VOID(!function.IsEmpty());
        CHECK_NULL_VOID(function->IsFunction());
        auto container = Container::Current();
        CHECK_NULL_VOID(container);
        auto frontend = container->GetFrontend();
        CHECK_NULL_VOID(frontend);
        function->Call(vm, function.ToLocal(), nullptr, 0);
    };
    auto pipelineContext = PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_RETURN(pipelineContext, panda::JSValueRef::Undefined(vm));
    pipelineContext->SetOnceVsyncListener(std::move(getVsyncFunc));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue FrameNodeBridge::MarkDirty(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> secondeArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(secondeArg->IsNumber(), panda::JSValueRef::Undefined(vm));
    ArkUIDirtyFlag dirtyFlag = static_cast<ArkUIDirtyFlag>(secondeArg->ToNumber(vm)->Value());
    GetArkUIFullNodeAPI()->getBasicAPI()->markDirty(nativeNode, dirtyFlag);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG