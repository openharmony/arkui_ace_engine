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
#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {
void NodeContainerPattern::RemakeNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto newNode = FireMakeFunction();
    host->RemoveChildAtIndex(0);
    host->AddChild(newNode, 0);
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
    auto exportTextureNode = exportTextureNode_.Upgrade();
    if (exportTextureNode) {
        auto exportTextureFrameNode = DynamicCast<FrameNode>(exportTextureNode);
        while (exportTextureNode && !exportTextureFrameNode) {
            exportTextureNode = exportTextureNode->GetFirstChild();
            exportTextureFrameNode = DynamicCast<FrameNode>(exportTextureNode);
        }
        CHECK_NULL_RETURN(exportTextureFrameNode, false);
        auto renderContext = exportTextureFrameNode->GetRenderContext();
        CHECK_NULL_RETURN(renderContext, false);
        auto ret = renderContext->DoTextureExport(surfaceId_);
        if (!ret) {
            TAG_LOGW(AceLogTag::ACE_NODE_CONTAINER, "DoTextureExport fail");
        }
        exportTextureNode_.Reset();
    }
    return false;
}

void NodeContainerPattern::OnMountToParentDone()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto viewNode = host->GetChildAtIndex(0);
    CHECK_NULL_VOID(viewNode);
    if (!viewNode->IsNeedExportTexture()) {
        return;
    }
    auto exportTextureInfo = viewNode->GetExportTextureInfo();
    auto parent = host->GetAncestorNodeOfFrame();
    CHECK_NULL_VOID(parent);
    auto nodeContainer = parent->GetNodeContainer();
    if (nodeContainer) {
        auto parentViewNode = nodeContainer->GetChildAtIndex(0);
        if (parentViewNode) {
            auto parnetExportTextureInfo = parentViewNode->GetExportTextureInfo();
            if (parnetExportTextureInfo &&
                parnetExportTextureInfo->GetCurrentRenderType() == NodeRenderType::RENDER_TYPE_TEXTURE) {
                // TODO: fire viewNode's on oldType=Export, newType=Default
            }
        }
    } else {
        exportTextureNode_ = viewNode;
        surfaceId_ = StringUtils::StringToLongUint(exportTextureInfo->GetSurfaceId());
    }
}
} // namespace OHOS::Ace::NG
