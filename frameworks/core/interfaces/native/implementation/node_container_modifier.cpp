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
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/node_container/node_container_event_hub.h"
#include "core/components_ng/pattern/node_container/node_container_node.h"
#include "core/components_ng/pattern/node_container/node_container_pattern.h"
#include "core/interfaces/native/implementation/frame_node_peer_impl.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace NodeContainerModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id, Ark_Int32 flags)
{
    auto frameNode = NodeContainerNode::GetOrCreateNodeContainerNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // namespace NodeContainerModifier
namespace NodeContainerInterfaceModifier {
void SetNodeContainerOptionsImpl(Ark_NativePointer node, const Ark_NodeController* controller)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(controller);
    // auto convValue = Converter::OptConvert<type_name>(*controller);
    // NodeContainerModelNG::SetSetNodeContainerOptions(frameNode, convValue);
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
    auto child = childPeer->node;
    pattern->AddBaseNode(child);
}

void SetAboutToAppearImpl(Ark_NativePointer self, const Callback_Void* value)
{
    auto nodeContainer = reinterpret_cast<FrameNode*>(self);
    CHECK_NULL_VOID(nodeContainer);
    auto eventHub = nodeContainer->GetEventHub<NodeContainerEventHub>();
    CHECK_NULL_VOID(eventHub);
    auto* context = nodeContainer->GetContext();
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
    auto aboutToDisappearFunc = [callback = CallbackHelper(*value), instanceId = context->GetInstanceId()]() -> void {
        ContainerScope scope(instanceId);
        callback.InvokeSync();
    };
    eventHub->SetControllerAboutToDisappear(std::move(aboutToDisappearFunc));
}

void SetAboutToResizeImpl(Ark_NativePointer self, const NodeContainer_AboutToResizeCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(self);
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<NodeContainerPattern>();
    CHECK_NULL_VOID(pattern);
    CHECK_NULL_VOID(value);
    auto aboutToResizeFunc = [arkCallback = CallbackHelper(*value)](const SizeF& size) -> void {
        auto arkSize = Converter::ArkValue<Ark_Size>(size);
        arkCallback.Invoke(arkSize);
    };
    pattern->SetOnResize(aboutToResizeFunc);
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

void SetOnTouchEventImpl(Ark_NativePointer self, const Opt_Callback_TouchEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(self);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    if (value->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        ViewAbstract::DisableOnTouch(frameNode);
        return;
    }
    auto onEvent = [callback = CallbackHelper(value->value)](TouchEventInfo& info) {
        const auto event = Converter::ArkTouchEventSync(info);
        callback.Invoke(event.ArkValue());
    };
    ViewAbstract::SetOnTouch(frameNode, std::move(onEvent));
}
} // namespace NodeContainerInterfaceModifier
const GENERATED_ArkUINodeContainerModifier* GetNodeContainerModifier()
{
    static const GENERATED_ArkUINodeContainerModifier ArkUINodeContainerModifierImpl {
        NodeContainerModifier::ConstructImpl,
        NodeContainerInterfaceModifier::SetNodeContainerOptionsImpl,
        NodeContainerInterfaceModifier::AddNodeContainerRootNodeImpl,
        NodeContainerInterfaceModifier::SetAboutToAppearImpl,
        NodeContainerInterfaceModifier::SetAboutToDisappearImpl,
        NodeContainerInterfaceModifier::SetAboutToResizeImpl,
        NodeContainerInterfaceModifier::SetOnAttachImpl,
        NodeContainerInterfaceModifier::SetOnDetachImpl,
        NodeContainerInterfaceModifier::SetOnTouchEventImpl,
    };
    return &ArkUINodeContainerModifierImpl;
}

} // namespace OHOS::Ace::NG::GeneratedModifier
