/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "ui/view/components/custom_node.h"

#include "interfaces/inner_api/ace_kit/src/view/frame_node_impl.h"
#include "interfaces/inner_api/ace_kit/src/view/ui_context_impl.h"
#include "ui/base/referenced.h"

#include "core/components_ng/pattern/custom_node_ext/custom_node_ext_model_ng.h"

namespace OHOS::Ace::Kit {

CustomNode::CustomNode(const RefPtr<FrameNode> aceNode)
{
    node_ = aceNode;
}

CustomNode::~CustomNode() = default;

RefPtr<CustomNode> CustomNode::Create(const std::string& tag)
{
    auto aceNode = NG::CustomNodeExtModelNG::CreateFrameNode(tag);
    return Referenced::MakeRefPtr<CustomNode>(AceType::MakeRefPtr<FrameNodeImpl>(aceNode));
}

RefPtr<CustomNode> CustomNode::GetOrCreateFrameNode(const std::string& tag)
{
    auto aceNode = NG::CustomNodeExtModelNG::GetOrCreateFrameNode(tag);
    return Referenced::MakeRefPtr<CustomNode>(AceType::MakeRefPtr<FrameNodeImpl>(aceNode));
}

void CustomNode::SetOnWindowFocusedCallback(const NodeHandle node, void (*onWindowFocused)(NodeHandle node))
{
    auto* frameNode = reinterpret_cast<AceNode*>(node);
    CHECK_NULL_VOID(frameNode);
    
    auto onWindowFocusedCallback = [node, onWindowFocused]() {
        onWindowFocused(node);
    };
    NG::CustomNodeExtModelNG::SetOnWindowFocusedCallback(frameNode, std::move(onWindowFocusedCallback));
}

void CustomNode::SetOnWindowUnfocusedCallback(const NodeHandle node, void (*onWindowUnfocused)(NodeHandle node))
{
    auto* frameNode = reinterpret_cast<AceNode*>(node);
    CHECK_NULL_VOID(frameNode);
    
    auto onWindowUnfocusedCallback = [node, onWindowUnfocused]() {
        onWindowUnfocused(node);
    };
    NG::CustomNodeExtModelNG::SetOnWindowUnfocusedCallback(frameNode, std::move(onWindowUnfocusedCallback));
}

void CustomNode::SetOnWindowActivatedCallback(const NodeHandle node, void (*onWindowActivated)(NodeHandle node))
{
    auto* frameNode = reinterpret_cast<AceNode*>(node);
    CHECK_NULL_VOID(frameNode);
    
    auto onWindowActivatedCallback = [node, onWindowActivated]() {
        onWindowActivated(node);
    };
    NG::CustomNodeExtModelNG::SetOnWindowActivatedCallback(frameNode, std::move(onWindowActivatedCallback));
}

void CustomNode::SetOnWindowDeactivatedCallback(const NodeHandle node, void (*onWindowDeactivated)(NodeHandle node))
{
    auto* frameNode = reinterpret_cast<AceNode*>(node);
    CHECK_NULL_VOID(frameNode);
    
    auto onWindowDeactivatedCallback = [node, onWindowDeactivated]() {
        onWindowDeactivated(node);
    };
    NG::CustomNodeExtModelNG::SetOnWindowDeactivatedCallback(frameNode, std::move(onWindowDeactivatedCallback));
}

void CustomNode::SetOnAttachToMainTreeCallback(const NodeHandle node, void (*onAttachToMainTree)(NodeHandle node))
{
    auto* frameNode = reinterpret_cast<AceNode*>(node);
    CHECK_NULL_VOID(frameNode);
    
    auto onAttachToMainTreeCallback = [node, onAttachToMainTree]() {
        onAttachToMainTree(node);
    };
    NG::CustomNodeExtModelNG::SetOnAttachToMainTreeCallback(frameNode, std::move(onAttachToMainTreeCallback));
}

void CustomNode::SetOnDetachFromMainTreeCallback(const NodeHandle node, void (*onDetachFromMainTree)(NodeHandle node))
{
    auto* frameNode = reinterpret_cast<AceNode*>(node);
    CHECK_NULL_VOID(frameNode);
    
    auto onDetachFromMainTreeCallback = [node, onDetachFromMainTree]() {
        onDetachFromMainTree(node);
    };
    NG::CustomNodeExtModelNG::SetOnDetachFromMainTreeCallback(frameNode, std::move(onDetachFromMainTreeCallback));
}

void CustomNode::SetOnAvoidInfoChangeCallback(const NodeHandle node, void (*onAvoidInfoChange)(NodeHandle node))
{
    auto* frameNode = reinterpret_cast<AceNode*>(node);
    CHECK_NULL_VOID(frameNode);
    
    auto onAvoidInfoChangeCallback = [node, onAvoidInfoChange]() {
        onAvoidInfoChange(node);
    };
    NG::CustomNodeExtModelNG::SetOnAvoidInfoChangeCallback(frameNode, std::move(onAvoidInfoChangeCallback));
}

void CustomNode::SetIsNeedRegisterAvoidInfoChangeListener(const NodeHandle node, bool isRegister)
{
    auto* frameNode = reinterpret_cast<AceNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::CustomNodeExtModelNG::SetIsNeedRegisterAvoidInfoChangeListener(frameNode, isRegister);
}

void CustomNode::SetOnWindowSizeChangedCallback(const NodeHandle node,
    void (*onWindowSizeChanged)(NodeHandle node, int32_t width, int32_t height, Ace::WindowSizeChangeReason type))
{
    auto* frameNode = reinterpret_cast<AceNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto uiContext = UIContextImpl::Current();
    CHECK_NULL_VOID(uiContext);
    uiContext->AddWindowSizeChangeCallback(frameNode->GetId());
    auto onWindowSizeChangedCallback =
        [node, onWindowSizeChanged](int32_t width, int32_t height, WindowSizeChangeReason type) {
            onWindowSizeChanged(node, width, height, type);
        };
    NG::CustomNodeExtModelNG::SetOnWindowSizeChangedCallback(frameNode, std::move(onWindowSizeChangedCallback));
}
} // namespace OHOS::Ace::Kit
