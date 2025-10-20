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

#include "core/components_ng/pattern/view_context/view_context_model_static.h"

#include "core/components_ng/base/frame_node.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
thread_local std::stack<std::pair<FrameNode*, bool>> g_animationCallStack; // true means has AnimationOption
} // namespace {}

void ViewContextModelStatic::OpenAnimation(FrameNode* node, const std::optional<AnimationOption>& option)
{
    CHECK_NULL_VOID(node);
    g_animationCallStack.emplace(node, option.has_value());
    if (!option.has_value()) {
        return;
    }
    node->MarkDirtyNode();
    NG::ViewStackProcessor::GetInstance()->SetImplicitAnimationOption(*option);
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->OpenFrontendAnimation(*option, option->GetCurve(), option->GetOnFinishEvent());
    bool isDirtyLayoutNodesEmpty = pipelineContext->IsDirtyLayoutNodesEmpty();
    bool isDirtyPropertyNodesEmpty = pipelineContext->IsDirtyPropertyNodesEmpty();
    if (option->GetIteration() == ANIMATION_REPEAT_INFINITE && !pipelineContext->IsLayouting()
        && (!isDirtyLayoutNodesEmpty || !isDirtyPropertyNodesEmpty)) {
        TAG_LOGW(AceLogTag::ACE_ANIMATION, "openAnimation: option:%{public}s,"
            "dirtyLayoutNodes is empty:%{public}d, dirtyPropertyNodes is empty:%{public}d",
            option->ToString().c_str(), isDirtyLayoutNodesEmpty, isDirtyPropertyNodesEmpty);
    }
}

void ViewContextModelStatic::CloseAnimation(FrameNode* node)
{
    CHECK_NULL_VOID(node);
    if (g_animationCallStack.empty()) {
        TAG_LOGE(AceLogTag::ACE_ANIMATION, "animation is not opened before");
        return;
    }
    auto top = g_animationCallStack.top();
    if (top.first != node) {
        TAG_LOGE(AceLogTag::ACE_ANIMATION, "animationStack node is not same");
        return;
    }
    g_animationCallStack.pop();
    if (top.second == false) {
        return; // open is undefined
    }
    NG::ViewStackProcessor::GetInstance()->SetImplicitAnimationOption(AnimationOption());
    node->MarkDirtyNode();
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->CloseFrontendAnimation(true); // force close animation because we have judged nodes.
}
} // namespace OHOS::Ace::NG
