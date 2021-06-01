/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/js_frontend/js_ace_page.h"

#include "base/utils/system_properties.h"
#include "core/components/focus_collaboration/focus_collaboration_component.h"
#include "core/components/page/page_component.h"
#include "core/components/page_transition/page_transition_component.h"

namespace OHOS::Ace::Framework {

JsAcePage::~JsAcePage()
{
    auto pipelineContext = pipelineContext_.Upgrade();
    if (!pipelineContext) {
        return;
    }

    auto accessibilityManager = pipelineContext->GetAccessibilityManager();
    if (!accessibilityManager) {
        LOGE("accessibilityManager not exists");
        return;
    }

    auto taskExecutor = pipelineContext->GetTaskExecutor();
    if (!taskExecutor) {
        LOGE("taskExecutor not exists");
        return;
    }

    RefPtr<DOMDocument> domDoc;
    domDoc.Swap(domDoc_);
    taskExecutor->PostTask(
        [domDoc, accessibilityManager] { accessibilityManager->ClearPageAccessibilityNodes(domDoc->GetRootNodeId()); },
        TaskExecutor::TaskType::UI);
}

RefPtr<PageComponent> JsAcePage::BuildPage(const std::string& url)
{
    auto pageId = GetPageId();
    auto rootStack = domDoc_->GetRootStackComponent();
    auto rootComposedStack = domDoc_->GetRootComposedStack();
    auto focusCollaboration = AceType::MakeRefPtr<FocusCollaborationComponent>(true);
    if (!pageTransition_) {
        pageTransition_ = AceType::MakeRefPtr<PageTransitionComponent>();
    }
    if ((!rootStack || !rootComposedStack) && !component_) {
        LOGW("Page[%{public}d] can't be loaded. no root component.", pageId);
        pageTransition_->SetContent(nullptr);
    } else {
        if (component_) {
            focusCollaboration->InsertChild(0, component_);
        } else if (rootComposedStack) {
            focusCollaboration->InsertChild(0, rootComposedStack);
        }
        pageTransition_->SetContent(focusCollaboration);
        if ((SystemProperties::GetDeviceType() == DeviceType::TV) && (!pageTransition_->GetIsSetOption())) {
            pageTransition_->SetSeparation(true);
            SwapBackgroundDecoration(pageTransition_);
        }
    }
    std::unique_ptr<JsonValue> argsValue = JsonUtil::ParseJsonString(pageParams_);
    if (argsValue && argsValue->IsObject()) {
        const std::string& cardComposeId = argsValue->GetString(DOM_TRANSITION_CARD_COMPOSEID);
        if (!cardComposeId.empty()) {
            return AceType::MakeRefPtr<PageComponent>(pageId, cardComposeId, pageTransition_);
        }
    }
    return AceType::MakeRefPtr<PageComponent>(pageId, pageTransition_);
}

RefPtr<ComposedComponent> JsAcePage::BuildPagePatch(int32_t nodeId)
{
    RefPtr<Component> dirtyComponent = domDoc_->GetComponentById(nodeId);
    if (!dirtyComponent) {
        LOGE("Node[%{public}d] can't be reached.", nodeId);
        return nullptr;
    }

    auto composedComponent = AceType::DynamicCast<ComposedComponent>(dirtyComponent);
    ACE_DCHECK(composedComponent);
    return composedComponent;
}

void JsAcePage::SwapBackgroundDecoration(const RefPtr<PageTransitionComponent>& transition)
{
    if (!transition) {
        LOGW("swap background decoration failed. transition is null.");
        return;
    }

    auto rootNode = domDoc_->GetDOMNodeById(DOM_ROOT_NODE_ID_BASE + GetPageId());
    if (!rootNode) {
        LOGW("swap background decoration failed. root node is null.");
        return;
    }

    auto box = rootNode->GetBoxComponent();
    if (!box) {
        LOGW("swap background decoration failed. box is null.");
        return;
    }

    auto decoration = box->GetBackDecoration();
    if (!decoration) {
        LOGW("swap background decoration failed. decoration is null.");
        return;
    }

    auto backgroundBox = AceType::MakeRefPtr<BoxComponent>();
    backgroundBox->SetBackDecoration(decoration);
    backgroundBox->SetWidth(box->GetWidthDimension().Value(), box->GetWidthDimension().Unit());
    backgroundBox->SetHeight(box->GetHeightDimension().Value(), box->GetHeightDimension().Unit());
    backgroundBox->SetFlex(BoxFlex::FLEX_XY);
    transition->SetBackground(backgroundBox);
    box->SetBackDecoration(nullptr);
}

RefPtr<BaseCanvasBridge> JsAcePage::GetBridgeById(NodeId nodeId)
{
    auto iter = canvasBridges_.find(nodeId);
    if (iter == canvasBridges_.end()) {
        LOGE("the canvas is not in the map");
        return nullptr;
    }
    return iter->second;
}

RefPtr<BaseAnimationBridge> JsAcePage::GetAnimationBridge(NodeId nodeId)
{
    auto bridge = animationBridges_.find(nodeId);
    if (bridge == animationBridges_.end()) {
        LOGW("the animation bridge is not in the map, nodeId: %{public}d", nodeId);
        return nullptr;
    }
    return bridge->second;
}

void JsAcePage::RemoveAnimationBridge(NodeId nodeId)
{
    animationBridges_.erase(nodeId);
}

void JsAcePage::AddAnimationBridge(NodeId nodeId, const RefPtr<BaseAnimationBridge>& animationBridge)
{
    if (!animationBridge) {
        LOGE("AddAnimationBridge failed. Animation bridge is null.");
        return;
    }
    animationBridges_[nodeId] = animationBridge;
}

void JsAcePage::PushCanvasBridge(NodeId nodeId, const RefPtr<BaseCanvasBridge>& bridge)
{
    if (!bridge) {
        LOGE("PushCanvasBridge failed. Canvas bridge is null.");
        return;
    }
    canvasBridges_[nodeId] = bridge;
}

void JsAcePage::AddNodeEvent(int32_t nodeId, const std::string& actionType, const std::string& eventAction)
{
    nodeEvent_[nodeId][actionType] = eventAction;
}

std::string& JsAcePage::GetNodeEventAction(int32_t nodeId, const std::string& actionType)
{
    // in error case just use empty string.
    return nodeEvent_[nodeId][actionType];
}

std::shared_ptr<JsPageRadioGroups> JsAcePage::GetRadioGroups()
{
    return radioGroups_;
}

} // namespace OHOS::Ace::Framework
