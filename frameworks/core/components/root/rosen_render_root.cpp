/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "core/components/root/rosen_render_root.h"

#include "render_service_client/core/ui/rs_root_node.h"

#include "core/pipeline/base/rosen_render_context.h"

#include "core/pipeline/base/rs_node_adapter.h"

namespace OHOS::Ace {

void RosenRenderRoot::Paint(RenderContext& context, const Offset& offset)
{
    auto rsNode = static_cast<RosenRenderContext*>(&context)->GetRSNode();
    if (!rsNode) {
        LOGE("Paint canvas is null");
        return;
    }
    if (isContextMenu_) {
        bgColor_ = Color::TRANSPARENT;
    }
    rsNode->SetBackgroundColor(bgColor_.GetValue());
    RenderNode::Paint(context, offset);
}

void RosenRenderRoot::SyncGeometryProperties()
{
    auto rsNode = GetRSNode();
    if (!rsNode) {
        return;
    }
    Offset paintOffset = GetPaintOffset();
    Size paintSize = GetLayoutSize();

    rsNode->SetBounds(paintOffset.GetX(), paintOffset.GetY(), paintSize.Width(), paintSize.Height());
    rsNode->SetFrame(paintOffset.GetX(), paintOffset.GetY(), paintSize.Width(), paintSize.Height());

    rsNode->SetPivot(0.0f, 0.0f);
    rsNode->SetScale(scale_);
}

void RosenRenderRoot::FinishRender(const std::unique_ptr<DrawDelegate>& delegate, const Rect& dirty)
{
    if (delegate) {
        if (!GetRSNode()) {
            SyncRSNodeBoundary(true, true);
        }
        auto rsNode = GetRSNode();
        delegate->DrawRSFrame(rsNode, dirty);
    }
}

std::shared_ptr<RSNode> RosenRenderRoot::CreateRSNode() const
{
    if (!SystemProperties::GetMultiInstanceEnabled()) {
        return OHOS::Rosen::RSRootNode::Create();
    }
    return RsNodeAdapter::CreateRootNode();
}

} // namespace OHOS::Ace
