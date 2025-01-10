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

#include "core/components_ng/pattern/ui_extension/surface_proxy_node.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/render/adapter/rosen_render_context.h"

namespace OHOS::Ace::NG {
void SurfaceProxyNode::SetHostNode(const WeakPtr<FrameNode>& host)
{
    host_ = host;
}

bool SurfaceProxyNode::AddSurfaceNode(
    const std::shared_ptr<Rosen::RSSurfaceNode>& surfaceNode)
{
    TAG_LOGI(aceLogTag_, "AddSurfaceNode Start");
    CHECK_NULL_RETURN(surfaceNode, false);
    auto host = host_.Upgrade();
    CHECK_NULL_RETURN(host, false);
    if (surfaceProxyNode_ == nullptr) {
        CreateSurfaceProxyNode();
        CHECK_NULL_RETURN(surfaceProxyNode_, false);
    }

    auto context = AceType::DynamicCast<NG::RosenRenderContext>(surfaceProxyNode_->GetRenderContext());
    CHECK_NULL_RETURN(context, false);
    context->SetRSNode(surfaceNode);
    host->AddChild(surfaceProxyNode_, 0);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    surfaceNode->CreateNodeInRenderThread();
    OnAddSurfaceNode();
    TAG_LOGI(aceLogTag_, "AddSurfaceNode Success");
    return true;
}

void SurfaceProxyNode::CreateSurfaceProxyNode()
{
    auto host = host_.Upgrade();
    CHECK_NULL_VOID(host);
    surfaceProxyNode_ = FrameNode::CreateFrameNode(V2::UI_EXTENSION_SURFACE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    surfaceProxyNode_->GetLayoutProperty()->UpdateMeasureType(MeasureType::MATCH_PARENT);
    surfaceProxyNode_->SetHitTestMode(HitTestMode::HTMNONE);
    auto&& opts = host->GetLayoutProperty()->GetSafeAreaExpandOpts();
    if (opts && opts->Expansive()) {
        surfaceProxyNode_->GetLayoutProperty()->UpdateSafeAreaExpandOpts(*opts);
        surfaceProxyNode_->MarkModifyDone();
    }
}

void SurfaceProxyNode::OnAddSurfaceNode()
{
    TAG_LOGI(aceLogTag_, "OnAddSurfaceNode");
}

RefPtr<FrameNode> SurfaceProxyNode::GetSurfaceProxyNode()
{
    return surfaceProxyNode_;
}
} // namespace OHOS::Ace::NG
