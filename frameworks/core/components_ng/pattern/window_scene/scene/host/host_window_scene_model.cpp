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

#include "core/components_ng/pattern/window_scene/scene/host/host_window_scene_model.h"

#include "session_manager/include/scene_session_manager.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/window_scene/scene/host/host_window_node.h"
#include "core/components_ng/pattern/window_scene/scene/host/host_window_scene.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {
void HostWindowSceneModel::Create(uint64_t persistentId)
{
    auto session = Rosen::SceneSessionManager::GetInstance().GetSceneSession(persistentId);
    if (session == nullptr) {
        LOGE("scene session is nullptr");
        return;
    }

    auto stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = HostWindowNode::GetOrCreateHostWindowNode(V2::HOST_WINDOW_SCENE_ETS_TAG, nodeId,
        [&session]() { return AceType::MakeRefPtr<HostWindowScene>(session); });
    stack->Push(frameNode);

    auto pattern = frameNode->GetPattern<HostWindowScene>();
    pattern->UpdateSession(session);
}
} // namespace OHOS::Ace::NG
