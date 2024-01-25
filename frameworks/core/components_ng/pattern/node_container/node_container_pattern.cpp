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

#include "core/components_ng/pattern/node_container/node_container_pattern.h"

#include "base/utils/utils.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
void NodeContainerPattern::RemakeNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto newNode = FireMakeFunction();
    host->RemoveChildAtIndex(0);
    host->AddChild(newNode, 0);
    OnAddBaseNode();
    host->MarkNeedFrameFlushDirty(NG::PROPERTY_UPDATE_MEASURE);
}

bool NodeContainerPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (config.skipMeasure && config.skipLayout) {
        return false;
    }
    auto geometryNode = dirty->GetGeometryNode();
    auto size = geometryNode->GetFrameSize();
    FireOnResize(size);
    auto context = PipelineContext::GetCurrentContext();
    if (context && surfaceId_ != 0U && !exportTextureNode_.Invalid()) {
        context->AddAfterLayoutTask([weak = WeakClaim(this)]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            auto ret = pattern->HandleTextureExport(false);
            if (!ret) {
                TAG_LOGW(AceLogTag::ACE_NODE_CONTAINER, "DoTextureExport fail");
            }
        });
    }
    return false;
}

bool NodeContainerPattern::HandleTextureExport(bool isStop)
{
    auto exportTextureNode = GetExportTextureNode();
    CHECK_NULL_RETURN(exportTextureNode, false);
    auto exportTextureRenderContext = exportTextureNode->GetRenderContext();
    CHECK_NULL_RETURN(exportTextureRenderContext, false);
    auto host = GetHost();
    if (host) {
        auto renderContext = host->GetRenderContext();
        CHECK_NULL_RETURN(renderContext, false);
        renderContext->SetIsNeedRebuildRSTree(isStop);
    }
    if (isStop) {
        return exportTextureRenderContext->StopTextureExport();
    }
    return exportTextureRenderContext->DoTextureExport(surfaceId_);
}

void NodeContainerPattern::OnDetachFromFrameNode(FrameNode* /* frameNode */)
{
    HandleTextureExport(true);
}

RefPtr<FrameNode> NodeContainerPattern::GetExportTextureNode() const
{
    auto exportTextureNode = exportTextureNode_.Upgrade();
    CHECK_NULL_RETURN(exportTextureNode, nullptr);
    auto exportTextureFrameNode = DynamicCast<FrameNode>(exportTextureNode);
    while (exportTextureNode && !exportTextureFrameNode) {
        exportTextureNode = exportTextureNode->GetFirstChild();
        exportTextureFrameNode = DynamicCast<FrameNode>(exportTextureNode);
    }
    return exportTextureFrameNode;
}

void NodeContainerPattern::ResetExportTextureInfo()
{
    surfaceId_ = 0U;
    exportTextureNode_.Reset();
}

void NodeContainerPattern::SetExportTextureInfoIfNeeded()
{
    ResetExportTextureInfo();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto viewNode = host->GetChildAtIndex(0);
    CHECK_NULL_VOID(viewNode);
    if (!viewNode->IsNeedExportTexture()) {
        return;
    }
    auto parent = host->GetAncestorNodeOfFrame();
    if (parent) {
        auto nodeContainer = parent->GetNodeContainer();
        if (nodeContainer) {
            auto parentViewNode = nodeContainer->GetChildAtIndex(0);
            CHECK_NULL_VOID(parentViewNode);
            auto parnetExportTextureInfo = parentViewNode->GetExportTextureInfo();
            if (parnetExportTextureInfo &&
                parnetExportTextureInfo->GetCurrentRenderType() == NodeRenderType::RENDER_TYPE_TEXTURE) {
                return;
            }
        }
    }
    auto exportTextureInfo = viewNode->GetExportTextureInfo();
    exportTextureNode_ = viewNode;
    surfaceId_ = StringUtils::StringToLongUint(exportTextureInfo->GetSurfaceId());
}

void NodeContainerPattern::OnAddBaseNode()
{
    HandleTextureExport(true);
    SetExportTextureInfoIfNeeded();
}

void NodeContainerPattern::OnMountToParentDone()
{
    SetExportTextureInfoIfNeeded();
}
} // namespace OHOS::Ace::NG
