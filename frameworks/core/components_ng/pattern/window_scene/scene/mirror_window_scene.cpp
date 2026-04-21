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

#include "core/components_ng/pattern/window_scene/scene/mirror_window_scene.h"

#include "ui/rs_surface_node.h"

#include "core/components_ng/render/adapter/rosen_render_context.h"

namespace OHOS::Ace::NG {

MirrorWindowScene::MirrorWindowScene(const sptr<Rosen::Session>& session)
{
    session_ = session;
}

void MirrorWindowScene::OnAttachToFrameNode()
{
    CHECK_NULL_VOID(session_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    ACE_SCOPED_TRACE("OnAttachToFrameNode Mirror [id:%d][self:%d][type:%d][name:%s]",
        session_->GetPersistentId(), host->GetId(), session_->GetWindowType(), session_->GetWindowName().c_str());
    TAG_LOGI(AceLogTag::ACE_WINDOW_SCENE,
        "OnAttachToFrameNode Mirror id: %{public}d, node id: %{public}d, type: %{public}d, name: %{public}s",
        session_->GetPersistentId(), host->GetId(), session_->GetWindowType(), session_->GetWindowName().c_str());
    auto name = session_->GetSessionInfo().bundleName_;
    auto pos = name.find_last_of('.');
    name = (pos == std::string::npos) ? name : name.substr(pos + 1); // skip '.'
    Rosen::RSSurfaceNodeConfig config;
    std::string surfaceName = "MirrorWindowScene_" + name + std::to_string(session_->GetPersistentId());
    config.SurfaceNodeName = surfaceName;
    auto rsUIContext = session_->GetRSUIContext(__func__);
    auto surfaceNode = Rosen::RSSurfaceNode::Create(
        config, Rosen::RSSurfaceNodeType::LEASH_WINDOW_NODE, true, false, rsUIContext);
    CHECK_NULL_VOID(surfaceNode);
    if (session_->GetSessionState() != Rosen::SessionState::STATE_BACKGROUND) {
        surfaceNode->SetClonedNodeInfo(session_->GetLeashWinSurfaceNode()->GetId());
    } else {
        AddSnapshot();
    }
    auto context = AceType::DynamicCast<RosenRenderContext>(host->GetRenderContext());
    CHECK_NULL_VOID(context);
    context->SetRSNode(surfaceNode);
    mirrorSurfaceNode_ = surfaceNode;
}

void MirrorWindowScene::AddSnapshot()
{
    CHECK_NULL_VOID(session_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto state = session_->GetSessionState();
    if (state == Rosen::SessionState::STATE_BACKGROUND && session_->GetScenePersistence() &&
        (session_->GetScenePersistence()->HasSnapshot() || session_->HasSnapshot())) {
        ACE_SCOPED_TRACE("AddSnapshot Mirror[id:%d][self:%d]", session_->GetPersistentId(), host->GetId());
        TAG_LOGI(AceLogTag::ACE_WINDOW_SCENE,
            "AddSnapshot Mirror id: %{public}d, node id: %{public}d, type: %{public}d, name: %{public}s",
            session_->GetPersistentId(), host->GetId(), session_->GetWindowType(), session_->GetWindowName().c_str());
        CreateSnapshotWindow();
        AddChild(host, snapshotWindow_, snapshotWindowName_);
    }
}

void MirrorWindowScene::OnDetachFromFrameNode(FrameNode* frameNode)
{
    CHECK_NULL_VOID(session_);
    CHECK_NULL_VOID(frameNode);
    ACE_SCOPED_TRACE("OnDetachFromFrameNode Mirror[id:%d][self:%d][type:%d][name:%s]",
        session_->GetPersistentId(), frameNode->GetId(),
        session_->GetWindowType(), session_->GetWindowName().c_str());
    TAG_LOGI(AceLogTag::ACE_WINDOW_SCENE,
        "OnDetachFromFrameNode Mirror id: %{public}d, node id: %{public}d, type: %{public}d, name: %{public}s",
        session_->GetPersistentId(), frameNode->GetId(),
        session_->GetWindowType(), session_->GetWindowName().c_str());
}

void MirrorWindowScene::OnAttachToMainTree()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetRenderContext();
    CHECK_NULL_VOID(context);
    context->SetIsNeedRebuildRSTree(true);
}

void MirrorWindowScene::OnDetachFromMainTree()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetRenderContext();
    CHECK_NULL_VOID(context);
    context->SetIsNeedRebuildRSTree(false);
}
} // namespace OHOS::Ace::NG