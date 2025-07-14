/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/window_scene/scene/window_scene_model.h"

#include "session_manager/include/scene_session_manager.h"

#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/window_scene/scene/input_scene.h"
#include "core/components_ng/pattern/window_scene/scene/panel_scene.h"
#include "core/components_ng/pattern/window_scene/scene/transform_scene.h"
#include "core/components_ng/pattern/window_scene/scene/window_node.h"
#include "core/components_ng/pattern/window_scene/scene/window_scene.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {
void UpdateAlignmentProperty()
{ // This function is needed for overlapping returning void type of macros
    ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, Alignment, Alignment::TOP_LEFT);
}

std::function<RefPtr<Pattern>(void)> PatternCreator(const sptr<Rosen::SceneSession>& sceneSession)
{
    std::function<RefPtr<Pattern>(void)> patternCreator;
    switch (sceneSession->GetSessionInfo().sceneType_) {
        case Rosen::SceneType::SYSTEM_WINDOW_SCENE:
            patternCreator = [sceneSession]() { return AceType::MakeRefPtr<SystemWindowScene>(sceneSession); };
            break;
        case Rosen::SceneType::PANEL_SCENE:
            patternCreator = [sceneSession]() { return AceType::MakeRefPtr<PanelScene>(sceneSession); };
            break;
        case Rosen::SceneType::INPUT_SCENE:
            patternCreator = [sceneSession]() { return AceType::MakeRefPtr<InputScene>(sceneSession); };
            break;
        default:
            break;
    }
    return patternCreator;
}

void CheckParentNodeDfx(RefPtr<FrameNode>& node, sptr<Rosen::SceneSession>& sceneSession, int persistentId)
{
    if (node == nullptr) {
        TAG_LOGW(AceLogTag::ACE_WINDOW_SCENE, "node is nullptr, sessionId:%{public}d", persistentId);
        return;
    }
    if (sceneSession == nullptr) {
        TAG_LOGW(AceLogTag::ACE_WINDOW_SCENE, "session is nullptr, nodeId:%{public}d, sessionId:%{public}d",
            node->GetId(), persistentId);
        return;
    }
    auto parent = node->GetParentFrameNode();
    if (parent) {
        TAG_LOGW(AceLogTag::ACE_WINDOW_SCENE, "parentId:%{public}d, nodeId:%{public}d, sessionId:%{public}d",
            parent->GetId(), node->GetId(), sceneSession->GetPersistentId());
    }
}

RefPtr<FrameNode> CreateNodeHelper(int32_t persistentId, int32_t inNodeId)
{
    if (inNodeId < 0) {
        auto stack = ViewStackProcessor::GetInstance();
        stack->Pop(); // Remove the current window scene node
    }
    if (persistentId == -1) { // -1: transform window scene type
        auto stack = ViewStackProcessor::GetInstance();
        auto nodeId = inNodeId >= 0 ? inNodeId : stack->ClaimNodeId();
        ACE_SCOPED_TRACE("Create[%s][self:%d][TransformScene]", V2::WINDOW_SCENE_ETS_TAG, nodeId);
        auto node = FrameNode::GetOrCreateFrameNode(V2::WINDOW_SCENE_ETS_TAG, nodeId,
            []() { return AceType::MakeRefPtr<TransformScene>(); });
        stack->Push(node);
        UpdateAlignmentProperty();
        return node;
    }

    auto sceneSession = Rosen::SceneSessionManager::GetInstance().GetSceneSession(persistentId);
    if (sceneSession == nullptr) {
        TAG_LOGE(AceLogTag::ACE_WINDOW_SCENE,
            "session is nullptr, persistentId: %{public}d", persistentId);
        return nullptr;
    }

    if (sceneSession->GetSessionInfo().sceneType_ != Rosen::SceneType::WINDOW_SCENE) {
        auto stack = ViewStackProcessor::GetInstance();
        auto nodeId =  inNodeId >= 0 ? inNodeId : stack->ClaimNodeId();
        ACE_SCOPED_TRACE("Create[%s][self:%d][%s]",
            V2::WINDOW_SCENE_ETS_TAG, nodeId, sceneSession->GetSessionInfo().bundleName_.c_str());
        auto node = FrameNode::GetOrCreateFrameNode(V2::WINDOW_SCENE_ETS_TAG, nodeId, PatternCreator(sceneSession));
        stack->Push(node);
        UpdateAlignmentProperty();
        CheckParentNodeDfx(node, sceneSession, persistentId);
        return node;
    }

    auto stack = ViewStackProcessor::GetInstance();
    auto nodeId = inNodeId >= 0 ? inNodeId : stack->ClaimNodeId();
    ACE_SCOPED_TRACE("Create[%s][self:%d][%s]",
        V2::WINDOW_SCENE_ETS_TAG, nodeId, sceneSession->GetSessionInfo().bundleName_.c_str());
    auto windowNode = WindowNode::GetOrCreateWindowNode(V2::WINDOW_SCENE_ETS_TAG, nodeId, persistentId,
        [sceneSession]() { return AceType::MakeRefPtr<WindowScene>(sceneSession); });
    if (windowNode == nullptr) {
        TAG_LOGE(AceLogTag::ACE_WINDOW_SCENE, "windowNode is nullptr, persistentId: %{public}d", persistentId);
        return windowNode;
    }
    stack->Push(windowNode);
    UpdateAlignmentProperty();

    if (windowNode->GetHitTestMode() == HitTestMode::HTMDEFAULT) {
        windowNode->SetHitTestMode(HitTestMode::HTMBLOCK);
    }
    auto node = AceType::DynamicCast<FrameNode>(windowNode);
    CheckParentNodeDfx(node, sceneSession, persistentId);
    return windowNode;
}

RefPtr<FrameNode> WindowSceneModel::Create(int32_t persistentId)
{
    return CreateNodeHelper(persistentId, -1);
}

void WindowSceneModel::SetAttractionEffect(const AttractionEffect& effect)
{
    ViewAbstract::SetAttractionEffect(effect);
}

RefPtr<FrameNode> WindowSceneModel::CreateNode(int32_t nodeId)
{
    return CreateNodeHelper(-1, nodeId);
}
} // namespace OHOS::Ace::NG
