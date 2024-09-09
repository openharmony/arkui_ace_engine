/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/loading_progress/loading_progress_model_ng.h"

#include "core/components_ng/pattern/loading_progress/loading_progress_pattern.h"

namespace OHOS::Ace::NG {
void LoadingProgressModelNG::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::LOADING_PROGRESS_ETS_TAG, nodeId);
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::LOADING_PROGRESS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<LoadingProgressPattern>(); });
    stack->Push(frameNode);
}
RefPtr<FrameNode> LoadingProgressModelNG::CreateFrameNode(int32_t nodeId)
{
    auto frameNode =
        FrameNode::CreateFrameNode(V2::LOADING_PROGRESS_ETS_TAG, nodeId, AceType::MakeRefPtr<LoadingProgressPattern>());
    return frameNode;
}
void LoadingProgressModelNG::SetColor(const Color& value)
{
    ACE_UPDATE_PAINT_PROPERTY(LoadingProgressPaintProperty, Color, value);
    ACE_UPDATE_RENDER_CONTEXT(ForegroundColor, value);
    ACE_RESET_RENDER_CONTEXT(RenderContext, ForegroundColorStrategy);
    ACE_UPDATE_RENDER_CONTEXT(ForegroundColorFlag, true);
}

void LoadingProgressModelNG::SetEnableLoading(bool enable)
{
    ACE_UPDATE_PAINT_PROPERTY(LoadingProgressPaintProperty, EnableLoading, enable);
}

uint32_t LoadingProgressModelNG::GetColor(FrameNode* frameNode)
{
    Color value;
    ACE_GET_NODE_PAINT_PROPERTY_WITH_DEFAULT_VALUE(LoadingProgressPaintProperty, Color, value, frameNode, value);
    return value.GetValue();
}

void LoadingProgressModelNG::SetColor(FrameNode* frameNode, const Color& value)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(LoadingProgressPaintProperty, Color, value, frameNode);
    ACE_UPDATE_NODE_RENDER_CONTEXT(ForegroundColor, value, frameNode);
    ACE_RESET_NODE_RENDER_CONTEXT(RenderContext, ForegroundColorStrategy, frameNode);
    ACE_UPDATE_NODE_RENDER_CONTEXT(ForegroundColorFlag, true, frameNode);
}

bool LoadingProgressModelNG::GetEnableLoading(FrameNode* frameNode)
{
    bool enable = true;
    ACE_GET_NODE_PAINT_PROPERTY_WITH_DEFAULT_VALUE(LoadingProgressPaintProperty,
        EnableLoading, enable, frameNode, enable);
    return enable;
}

void LoadingProgressModelNG::SetEnableLoading(FrameNode* frameNode, bool enable)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(LoadingProgressPaintProperty, EnableLoading, enable, frameNode);
}

void LoadingProgressModelNG::SetForegroundColor(FrameNode* frameNode, const Color& value)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(LoadingProgressPaintProperty, Color, value, frameNode);
    ACE_UPDATE_NODE_RENDER_CONTEXT(ForegroundColor, value, frameNode);
    ACE_RESET_NODE_RENDER_CONTEXT(RenderContext, ForegroundColorStrategy, frameNode);
    ACE_UPDATE_NODE_RENDER_CONTEXT(ForegroundColorFlag, true, frameNode);
}

void LoadingProgressModelNG::SetBuilderFunc(FrameNode* frameNode, NG::LoadingProgressMakeCallback&& makeFunc)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<LoadingProgressPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetBuilderFunc(std::move(makeFunc));
}
} // namespace OHOS::Ace::NG
