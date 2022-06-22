/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components/remote_window/rosen_render_remote_window.h"

#include "render_service_client/core/ui/rs_surface_node.h"

namespace OHOS::Ace {
void RosenRenderRemoteWindow::Update(const RefPtr<Component>& component)
{
    RenderRemoteWindow::Update(component);
    
    RefPtr<RemoteWindowComponent> remoteWindowComponent = AceType::DynamicCast<RemoteWindowComponent>(component);
    if (!remoteWindowComponent) {
        return;
    }

    auto surfaceNode = remoteWindowComponent->GetRSSurfaceNode();
    // update RSNode if needed
    if (surfaceNode != nullptr && surfaceNode != GetRSNode()) {
        SetRSNode(surfaceNode);
        // create corresponding RSRenderNode in Render Thread
        surfaceNode->CreateNodeInRenderThread(true);
        // after updating RSNode, we need to explicitly sync geometry
        MarkNeedSyncGeometryProperties();
    }
}

void RosenRenderRemoteWindow::SyncGeometryProperties()
{
    auto rsNode = GetRSNode();
    if (!rsNode) {
        return;
    }
    Offset paintOffset = GetPaintOffset();
    // for surface nodes, only bounds is used
    rsNode->SetBounds(paintOffset.GetX(), paintOffset.GetY(), drawSize_.Width(), drawSize_.Height());
    rsNode->SetFrame(paintOffset.GetX(), paintOffset.GetY(), drawSize_.Width(), drawSize_.Height());
}
} // namespace OHOS::Ace
