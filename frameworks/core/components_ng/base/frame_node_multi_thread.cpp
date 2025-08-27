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

#include "core/components_ng/base/frame_node.h"

#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
void FrameNode::MarkModifyDoneMultiThread()
{
    PostAfterAttachMainTreeTask([weak = WeakClaim(this)]() {
        auto host = weak.Upgrade();
        CHECK_NULL_VOID(host);
        host->MarkModifyDone();
    });
}

void FrameNode::MarkDirtyNodeMultiThread(PropertyChangeFlag extraFlag)
{
    PostAfterAttachMainTreeTask([weak = WeakClaim(this), extraFlag]() {
        auto host = weak.Upgrade();
        CHECK_NULL_VOID(host);
        host->MarkDirtyNode(extraFlag);
    });
}

void FrameNode::RebuildRenderContextTreeMultiThread()
{
    PostAfterAttachMainTreeTask([weak = WeakClaim(this)]() {
        auto host = weak.Upgrade();
        CHECK_NULL_VOID(host);
        host->RebuildRenderContextTree();
    });
}

void FrameNode::MarkNeedRenderMultiThread(bool isRenderBoundary)
{
    auto context = GetContext();
    CHECK_NULL_VOID(context);
    // If it has dirtyLayoutBox, need to mark dirty after layout done.
    paintProperty_->UpdatePropertyChangeFlag(PROPERTY_UPDATE_RENDER);
    if (isRenderDirtyMarked_ || isLayoutDirtyMarked_) {
        return;
    }
    isRenderDirtyMarked_ = true;
    if (isRenderBoundary) {
        PostAfterAttachMainTreeTask([weak = WeakClaim(this)]() {
            auto frameNode = weak.Upgrade();
            CHECK_NULL_VOID(frameNode);
            auto context = frameNode->GetContext();
            CHECK_NULL_VOID(context);
            context->AddDirtyRenderNode(weak.Upgrade());
        });
        return;
    }
    auto parent = GetAncestorNodeOfFrame(false);
    if (parent) {
        parent->MarkDirtyNode(PROPERTY_UPDATE_RENDER_BY_CHILD_REQUEST);
    }
}
} // namespace OHOS::Ace::NG