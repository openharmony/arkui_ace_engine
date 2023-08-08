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

#include "core/components_ng/pattern/custom/custom_node_base.h"

#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/ui_node.h"
#include "core/pipeline_ng/pipeline_context.h"

#include <queue>

namespace OHOS::Ace::NG {

CustomNodeBase::~CustomNodeBase()
{
    if (destroyFunc_) {
        destroyFunc_();
    }
}

void CustomNodeBase::Update()
{
    needRebuild_ = false;
    if (updateFunc_) {
        updateFunc_();
    }
}

void CustomNodeBase::MarkNeedUpdate()
{
    if (recycleRenderFunc_) {
        return;
    }
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    if (needRebuild_) {
        return;
    }
    needRebuild_ = true;
    context->AddDirtyCustomNode(AceType::DynamicCast<UINode>(Claim(this)));
}

void CustomNodeBase::FireRecycleSelf()
{
    std::queue<RefPtr<UINode>> q;
    q.push(AceType::DynamicCast<UINode>(Claim(this)));
    while (!q.empty()) {
        auto node = q.front();
        q.pop();
        auto frameNode = AceType::DynamicCast<FrameNode>(node);
        if (frameNode) {
            auto layoutProperty = frameNode->GetLayoutProperty();
            if (layoutProperty && layoutProperty->GetGeometryTransition()) {
                auto geometryTransitionId = layoutProperty->GetGeometryTransition()->GetId();
                layoutProperty->UpdateGeometryTransition("");
            }
        }
        const auto& children = node->GetChildren();
        for (const auto& child : children) {
            q.push(child);
        }
    }

    if (recycleCustomNodeFunc_) {
        recycleCustomNodeFunc_(AceType::Claim<CustomNodeBase>(this));
    }
}
} // namespace OHOS::Ace::NG
