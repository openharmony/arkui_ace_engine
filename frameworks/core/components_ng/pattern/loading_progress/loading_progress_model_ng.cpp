/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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

#include "core/common/resource/resource_parse_utils.h"
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
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    RefPtr<ProgressTheme> theme = pipeline->GetTheme<ProgressTheme>(frameNode->GetThemeScopeId());
    CHECK_NULL_VOID(theme);
    if (frameNode->GetThemeScopeId()) {
        ACE_UPDATE_PAINT_PROPERTY(LoadingProgressPaintProperty, Color, theme->GetLoadingColor());
    }
    auto pros = frameNode->GetPaintProperty<LoadingProgressPaintProperty>();
    if (pros) {
        pros->ResetColorSetByUser();
    }
}
RefPtr<FrameNode> LoadingProgressModelNG::CreateFrameNode(int32_t nodeId)
{
    auto frameNode =
        FrameNode::CreateFrameNode(V2::LOADING_PROGRESS_ETS_TAG, nodeId, AceType::MakeRefPtr<LoadingProgressPattern>());
    return frameNode;
}
void LoadingProgressModelNG::SetColor(const Color& value)
{
    auto frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<LoadingProgressPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetColorLock(true);
    ACE_UPDATE_PAINT_PROPERTY(LoadingProgressPaintProperty, Color, value);
    ACE_UPDATE_PAINT_PROPERTY(LoadingProgressPaintProperty, ColorSetByUser, true);
    ACE_UPDATE_RENDER_CONTEXT(ForegroundColor, value);
    ACE_RESET_RENDER_CONTEXT(RenderContext, ForegroundColorStrategy);
    ACE_UPDATE_RENDER_CONTEXT(ForegroundColorFlag, true);
}

void LoadingProgressModelNG::SetColorByUser(bool isSetByUser)
{
    ACE_UPDATE_PAINT_PROPERTY(LoadingProgressPaintProperty, ColorSetByUser, isSetByUser);
}

void LoadingProgressModelNG::SetEnableLoading(bool enable)
{
    ACE_UPDATE_PAINT_PROPERTY(LoadingProgressPaintProperty, EnableLoading, enable);
}

void LoadingProgressModelNG::ResetColor()
{
    auto frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<LoadingProgressPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetColorLock(false);
    ACE_RESET_PAINT_PROPERTY_WITH_FLAG(LoadingProgressPaintProperty, Color, PROPERTY_UPDATE_RENDER);
    ACE_UPDATE_PAINT_PROPERTY(LoadingProgressPaintProperty, ColorSetByUser, true);
    ACE_RESET_RENDER_CONTEXT(RenderContext, ForegroundColor);
    ACE_RESET_RENDER_CONTEXT(RenderContext, ForegroundColorStrategy);
    ACE_RESET_RENDER_CONTEXT(RenderContext, ForegroundColorFlag);
}

void LoadingProgressModelNG::SetForegroundColorParseFailed(bool isParseFailed)
{
    auto frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<LoadingProgressPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetForegroundColorParseFailed(isParseFailed);
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
    ACE_UPDATE_NODE_PAINT_PROPERTY(LoadingProgressPaintProperty, ColorSetByUser, true, frameNode);
    ACE_RESET_NODE_RENDER_CONTEXT(RenderContext, ForegroundColorStrategy, frameNode);
    ACE_UPDATE_NODE_RENDER_CONTEXT(ForegroundColorFlag, true, frameNode);
}

void LoadingProgressModelNG::SetColorByUser(FrameNode* frameNode, bool isSetByUser)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(LoadingProgressPaintProperty, ColorSetByUser, isSetByUser, frameNode);
}

bool LoadingProgressModelNG::GetEnableLoading(FrameNode* frameNode)
{
    bool enable = true;
    ACE_GET_NODE_PAINT_PROPERTY_WITH_DEFAULT_VALUE(
        LoadingProgressPaintProperty, EnableLoading, enable, frameNode, enable);
    return enable;
}

void LoadingProgressModelNG::SetEnableLoading(FrameNode* frameNode, bool enable)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(LoadingProgressPaintProperty, EnableLoading, enable, frameNode);
}

void LoadingProgressModelNG::SetForegroundColor(FrameNode* frameNode, const Color& value)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(LoadingProgressPaintProperty, Color, value, frameNode);
    ACE_UPDATE_NODE_PAINT_PROPERTY(LoadingProgressPaintProperty, ColorSetByUser, true, frameNode);
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

void LoadingProgressModelNG::ResetColor(FrameNode* frameNode)
{
    ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(LoadingProgressPaintProperty, Color, PROPERTY_UPDATE_RENDER, frameNode);
    ACE_UPDATE_NODE_PAINT_PROPERTY(LoadingProgressPaintProperty, ColorSetByUser, true, frameNode);
    ACE_RESET_NODE_RENDER_CONTEXT(RenderContext, ForegroundColor, frameNode);
    ACE_RESET_NODE_RENDER_CONTEXT(RenderContext, ForegroundColorStrategy, frameNode);
    ACE_RESET_NODE_RENDER_CONTEXT(RenderContext, ForegroundColorFlag, frameNode);
}

void LoadingProgressModelNG::ResetForegroundColor(FrameNode* frameNode)
{
    ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(LoadingProgressPaintProperty, Color, PROPERTY_UPDATE_RENDER, frameNode);
    ACE_UPDATE_NODE_PAINT_PROPERTY(LoadingProgressPaintProperty, ColorSetByUser, true, frameNode);
    ACE_RESET_NODE_RENDER_CONTEXT(RenderContext, ForegroundColor, frameNode);
    ACE_RESET_NODE_RENDER_CONTEXT(RenderContext, ForegroundColorStrategy, frameNode);
    ACE_RESET_NODE_RENDER_CONTEXT(RenderContext, ForegroundColorFlag, frameNode);
}

void LoadingProgressModelNG::SetForegroundColorParseFailed(FrameNode* frameNode, bool isParseFailed)
{
    auto pattern = frameNode->GetPattern<LoadingProgressPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetForegroundColorParseFailed(isParseFailed);
}

void LoadingProgressModelNG::SetColorParseFailed(FrameNode* frameNode, bool isParseFailed)
{
    auto pattern = frameNode->GetPattern<LoadingProgressPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetColorLock(isParseFailed);
}

void LoadingProgressModelNG::CreateWithResourceObj(
    LoadingProgressResourceType LoadingProgressResourceType, const RefPtr<ResourceObject>& resObj)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    CreateWithResourceObj(frameNode, LoadingProgressResourceType, resObj);
}

void HandleColorResource(const RefPtr<LoadingProgressPattern>& pattern, const RefPtr<ResourceObject>& resObj)
{
    std::string key = "loadingProgress.Color";
    pattern->RemoveResObj(key);
    CHECK_NULL_VOID(resObj);
    auto&& updateFunc = [weak = AceType::WeakClaim(AceType::RawPtr(pattern)), key](
                            const RefPtr<ResourceObject>& resObj, bool isFirstLoad = false) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        Color result;
        if (!ResourceParseUtils::ParseResColor(resObj, result)) {
            if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
                auto pipeline = PipelineBase::GetCurrentContext();
                CHECK_NULL_VOID(pipeline);
                auto progressTheme = pipeline->GetTheme<ProgressTheme>();
                CHECK_NULL_VOID(progressTheme);
                result = progressTheme->GetLoadingColor();
            }
        }
        pattern->UpdateColor(result, isFirstLoad);
    };
    pattern->AddResObj(key, resObj, std::move(updateFunc));
}

void HandleForegroundColorResource(const RefPtr<LoadingProgressPattern>& pattern, const RefPtr<ResourceObject>& resObj)
{
    std::string key = "loadingProgress.ForegroundColor";
    pattern->RemoveResObj(key);
    CHECK_NULL_VOID(resObj);
    auto&& updateFunc = [weak = AceType::WeakClaim(AceType::RawPtr(pattern)), key](
                            const RefPtr<ResourceObject>& resObj, bool isFirstLoad = false) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        Color result;
        if (!ResourceParseUtils::ParseResColor(resObj, result)) {
            if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
                auto pipeline = PipelineBase::GetCurrentContext();
                CHECK_NULL_VOID(pipeline);
                auto progressTheme = pipeline->GetTheme<ProgressTheme>();
                CHECK_NULL_VOID(progressTheme);
                result = progressTheme->GetLoadingColor();
            }
        }
        pattern->UpdateColor(result, isFirstLoad);
    };
    pattern->AddResObj(key, resObj, std::move(updateFunc));
}

void LoadingProgressModelNG::CreateWithResourceObj(
    FrameNode* frameNode, LoadingProgressResourceType resourceType, const RefPtr<ResourceObject>& resObj)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<LoadingProgressPattern>();
    CHECK_NULL_VOID(pattern);
    switch (resourceType) {
        case LoadingProgressResourceType::COLOR:
            HandleColorResource(pattern, resObj);
            break;
        case LoadingProgressResourceType::FOREGROUNDCOLOR:
            HandleForegroundColorResource(pattern, resObj);
            break;
        default:
            break;
    }
}
} // namespace OHOS::Ace::NG
