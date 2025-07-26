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

#include "core/pipeline/base/rs_node_adapter.h"

#include "core/pipeline/pipeline_base.h"
#include "core/pipeline/pipeline_context.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "render_service_client/core/ui/rs_node.h"
#include "render_service_client/core/ui/rs_root_node.h"
#include "render_service_client/core/ui/rs_surface_node.h"
#include "render_service_client/core/ui/rs_ui_context.h"
#include "render_service_client/core/ui/rs_ui_director.h"

namespace OHOS::Ace {

std::shared_ptr<Rosen::RSNode> RsNodeAdapter::CreateCanvasNode()
{
    auto rsUIContext = GetRSUIContext();
    if (rsUIContext) {
        auto canvasNode = Rosen::RSCanvasNode::Create(false, false, rsUIContext);
        if (canvasNode) {
            canvasNode->SetSkipCheckInMultiInstance(true);
        }
        return canvasNode;
    }
    return Rosen::RSCanvasNode::Create();
}

std::shared_ptr<Rosen::RSNode> RsNodeAdapter::CreateRootNode()
{
    auto rsUIContext = GetRSUIContext();
    if (rsUIContext) {
        auto rootNode = Rosen::RSRootNode::Create(false, false, rsUIContext);
        if (rootNode) {
            rootNode->SetSkipCheckInMultiInstance(true);
        }
        return rootNode;
    }
    return Rosen::RSRootNode::Create();
}

std::shared_ptr<Rosen::RSNode> RsNodeAdapter::CreateSurfaceNode(
    const Rosen::RSSurfaceNodeConfig& surfaceNodeConfig)
{
    auto rsUIContext = GetRSUIContext();
    if (rsUIContext) {
        auto surfaceNode = Rosen::RSSurfaceNode::Create(surfaceNodeConfig, false, rsUIContext);
        if (surfaceNode) {
            surfaceNode->SetSkipCheckInMultiInstance(true);
        }
        return surfaceNode;
    }
    return Rosen::RSSurfaceNode::Create(surfaceNodeConfig, false);
}

std::shared_ptr<Rosen::RSUIContext> RsNodeAdapter::GetRSUIContext()
{
    std::shared_ptr<Rosen::RSUIDirector> rsUIDirector;
    auto currentContainer = Container::CurrentSafelyWithCheck();
    CHECK_NULL_RETURN(currentContainer, nullptr);
    auto context = AceType::DynamicCast<PipelineContext>(currentContainer->GetPipelineContext());
    if (context) {
        rsUIDirector = context->GetRSUIDirector();
    } else {
        // Add JS Card use NG::PipelineContext
        auto contextNG = AceType::DynamicCast<NG::PipelineContext>(currentContainer->GetPipelineContext());
        if (contextNG) {
            rsUIDirector = contextNG->GetRSUIDirector();
        }
    }
    if (rsUIDirector) {
        return rsUIDirector->GetRSUIContext();
    }
    return nullptr;
}
}