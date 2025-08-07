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

#include "core/components_ng/render/render_context.h"

#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
void RenderContext::RequestNextFrameMultiThread() const
{
    if (requestFrame_) {
        requestFrame_();
        auto node = GetHost();
        CHECK_NULL_VOID(node);
        auto eventHub = node->GetEventHub<NG::EventHub>();
        if (node->GetInspectorId().has_value() || (eventHub && eventHub->HasNDKDrawCompletedCallback())) {
            node->PostAfterAttachMainTreeTask([weak = WeakPtr<FrameNode>(node)]() {
                auto pipeline = AceType::DynamicCast<PipelineContext>(PipelineBase::GetCurrentContext());
                CHECK_NULL_VOID(pipeline);
                pipeline->SetNeedRenderNode(weak);
            });
        }
        if (node->IsObservedByDrawChildren()) {
            node->PostAfterAttachMainTreeTask([weak = WeakPtr<FrameNode>(node)]() {
                auto pipeline = AceType::DynamicCast<PipelineContext>(PipelineBase::GetCurrentContext());
                CHECK_NULL_VOID(pipeline);

                auto node = weak.Upgrade();
                CHECK_NULL_VOID(node);
                auto frameNode = AceType::DynamicCast<FrameNode>(node->GetObserverParentForDrawChildren());
                pipeline->SetNeedRenderForDrawChildrenNode(WeakPtr<FrameNode>(frameNode));
            });
        }
    }
}
} // namespace OHOS::Ace::NG