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

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/window_scene/scene/system_window_scene.h"
#include "core/components_ng/pattern/window_scene/scene/window_node.h"
#include "core/components_ng/pattern/window_scene/scene/window_scene.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {
void WindowSceneModel::Create(uint64_t persistentId)
{
    auto sceneSession = Rosen::SceneSessionManager::GetInstance().GetSceneSession(persistentId);
    if (sceneSession == nullptr) {
        LOGE("scene session is nullptr");
        return;
    }

    if (sceneSession->GetSessionInfo().isSystem_) {
        auto stack = ViewStackProcessor::GetInstance();
        auto nodeId = stack->ClaimNodeId();
        auto node = FrameNode::GetOrCreateFrameNode(V2::WINDOW_SCENE_ETS_TAG, nodeId,
            [sceneSession]() { return AceType::MakeRefPtr<SystemWindowScene>(sceneSession); });
        stack->Push(node);
        return;
    }

    auto stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto windowNode = WindowNode::GetOrCreateWindowNode(V2::WINDOW_SCENE_ETS_TAG, nodeId,
        [sceneSession]() { return AceType::MakeRefPtr<WindowScene>(sceneSession); });
    if (windowNode->GetHitTestMode() != HitTestMode::HTMDEFAULT) {
        windowNode->SetHitTestMode(HitTestMode::HTMBLOCK);
    }
    stack->Push(windowNode);
    auto windowScene = windowNode->GetPattern<WindowScene>();
    windowScene->UpdateSession(sceneSession);
}
} // namespace OHOS::Ace::NG
