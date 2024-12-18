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

#include "core/components_ng/pattern/remote_window/remote_window_model_ng.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/render/adapter/rosen_render_context.h"

namespace OHOS::Ace::NG {
void RemoteWindowModelNG::Create(const std::shared_ptr<OHOS::Rosen::RSNode>& rsNode)
{
    auto* stack = ViewStackProcessor::GetInstance();
    CHECK_NULL_VOID(stack);
    auto nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::REMOTE_WINDOW_ETS_TAG, nodeId);
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::REMOTE_WINDOW_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<RemoteWindowPattern>(); });
    CHECK_NULL_VOID(frameNode);
    stack->Push(frameNode);
#ifdef ENABLE_ROSEN_BACKEND
    auto context = AceType::DynamicCast<NG::RosenRenderContext>(frameNode->GetRenderContext());
    CHECK_NULL_VOID(context);
    context->SetRSNode(rsNode);
#endif
}
} // namespace OHOS::Ace::NG
