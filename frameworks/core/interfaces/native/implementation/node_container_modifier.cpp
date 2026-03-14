/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#include <functional>
#include <utility>

#include "arkoala_api_generated.h"
#include "ui/base/utils/utils.h"

#include "core/common/container_scope.h"
#include "core/components_ng/pattern/node_container/node_container_event_hub.h"
#include "core/components_ng/pattern/node_container/node_container_node.h"
#include "core/components_ng/pattern/node_container/node_container_model_ng.h"
#include "core/components_ng/pattern/node_container/node_container_pattern.h"
#include "core/interfaces/native/implementation/frame_node_peer_impl.h"
#include "core/interfaces/native/implementation/touch_event_peer.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace NodeContainerModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    auto frameNode = NodeContainerModelNG::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // NodeContainerModifier
namespace NodeContainerInterfaceModifier {
void SetNodeContainerOptionsImpl(Ark_NativePointer node,
                                 Ark_NodeController controller)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(controller);
    //auto convValue = Converter::OptConvert<type>(controller); // for enums
    //NodeContainerModelNG::SetNodeContainerOptions(frameNode, convValue);
}

void AddNodeContainerRootNodeImpl(Ark_NativePointer self, Ark_NativePointer childNode)
{
    auto nodeContainer = reinterpret_cast<FrameNode*>(self);
    auto* childPeer = reinterpret_cast<Ark_FrameNode>(childNode);
    auto pattern = nodeContainer->GetPattern<NodeContainerPattern>();
    CHECK_NULL_VOID(pattern);
    if (!childPeer) {
        pattern->AddBaseNode(nullptr);
        return;
    }
    auto child = FrameNodePeer::GetFrameNodeByPeer(childPeer);
    pattern->AddBaseNode(child);
}

void SetAboutToAppearImpl(Ark_NativePointer self, const Callback_Void* value)
{
    auto nodeContainer = reinterpret_cast<FrameNode*>(self);
    CHECK_NULL_VOID(nodeContainer);
    auto eventHub = nodeContainer->GetEventHub<NodeContainerEventHub>();
    CHECK_NULL_VOID(eventHub);
    auto* context = nodeContainer->GetContext();
    CHECK_NULL_VOID(context);
    auto aboutToAppearFunc = [callback = CallbackHelper(*value), instanceId = context->GetInstanceId()]() -> void {
        ContainerScope scope(instanceId);
        callback.InvokeSync();
    };
    eventHub->SetControllerAboutToAppear(std::move(aboutToAppearFunc));
}

void SetAboutToDisappearImpl(Ark_NativePointer self, const Callback_Void* value)
{
    auto nodeContainer = reinterpret_cast<FrameNode*>(self);
    CHECK_NULL_VOID(nodeContainer);
    auto eventHub = nodeContainer->GetEventHub<NodeContainerEventHub>();
    CHECK_NULL_VOID(eventHub);
    auto* context = nodeContainer->GetContext();
    CHECK_NULL_VOID(context);
    auto aboutToDisappearFunc = [callback = CallbackHelper(*value), instanceId = context->GetInstanceId()]() -> void {
        ContainerScope scope(instanceId);
        callback.InvokeSync();
    };
    eventHub->SetControllerAboutToDisappear(std::move(aboutToDisappearFunc));
}

void SetOnAttachImpl(Ark_NativePointer self, const Callback_Void* value)
{
    auto nodeContainer = reinterpret_cast<FrameNode*>(self);
    CHECK_NULL_VOID(nodeContainer);
    auto eventHub = nodeContainer->GetEventHub<NodeContainerEventHub>();
    CHECK_NULL_VOID(eventHub);
    auto* context = nodeContainer->GetContext();
    auto onAttachFunc = [callback = CallbackHelper(*value), instanceId = context->GetInstanceId()]() -> void {
        ContainerScope scope(instanceId);
        callback.InvokeSync();
    };
    eventHub->SetControllerOnAttach(std::move(onAttachFunc));
}

void SetOnDetachImpl(Ark_NativePointer self, const Callback_Void* value)
{
    auto nodeContainer = reinterpret_cast<FrameNode*>(self);
    CHECK_NULL_VOID(nodeContainer);
    auto eventHub = nodeContainer->GetEventHub<NodeContainerEventHub>();
    CHECK_NULL_VOID(eventHub);
    auto* context = nodeContainer->GetContext();
    auto onDetachFunc = [callback = CallbackHelper(*value), instanceId = context->GetInstanceId()]() -> void {
        ContainerScope scope(instanceId);
        callback.InvokeSync();
    };
    eventHub->SetControllerOnDetach(std::move(onDetachFunc));
}

void SetOnTouchEventImpl(Ark_NativePointer self, const Opt_Callback_TouchEventProxy_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(self);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto onEvent = [arkCallback = CallbackHelper(*optValue)](TouchEventInfo& info) {
        Ark_TouchEventProxy proxy = {
            .target = Converter::ArkValue<Ark_EventTarget>(info.GetTarget()),
            .timeStamp = Converter::ArkValue<Ark_Int64>(
                static_cast<int64_t>(info.GetTimeStamp().time_since_epoch().count())),
            .pressure = Converter::ArkValue<Ark_Float64>(info.GetForce()),
            .tiltX = Converter::ArkValue<Ark_Float64>(static_cast<double>(info.GetTiltX().value_or(0))),
            .tiltY = Converter::ArkValue<Ark_Float64>(static_cast<double>(info.GetTiltY().value_or(0))),
            .sourceTool = Converter::ArkValue<Ark_SourceTool>(info.GetSourceTool()),
            .deviceId = Converter::ArkValue<Opt_Int32>(info.GetDeviceId()),
            .targetDisplayId = Converter::ArkValue<Opt_Int32>(info.GetTargetDisplayId()),
            .type = Converter::ArkValue<Ark_TouchType>(info.GetChangedTouches().front().GetTouchType()),
            .touches = Converter::ArkValue<Array_TouchObject>(info.GetTouches(), Converter::FC),
            .changedTouches = Converter::ArkValue<Array_TouchObject>(info.GetChangedTouches(), Converter::FC),
            .ptr = &info
        };
        arkCallback.InvokeSync(proxy);
    };
    ViewAbstract::SetOnTouch(frameNode, std::move(onEvent));
}
} // NodeContainerInterfaceModifier
const GENERATED_ArkUINodeContainerModifier* GetNodeContainerModifier()
{
    static const GENERATED_ArkUINodeContainerModifier ArkUINodeContainerModifierImpl {
        NodeContainerModifier::ConstructImpl,
        NodeContainerInterfaceModifier::SetNodeContainerOptionsImpl,
    };
    return &ArkUINodeContainerModifierImpl;
}

}
