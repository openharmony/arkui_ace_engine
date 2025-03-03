
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

#include "render_service_client/core/ui/rs_surface_node.h"

namespace OHOS {
namespace Rosen {
RSSurfaceNode::SharedPtr RSSurfaceNode::Create(const RSSurfaceNodeConfig& surfaceNodeConfig, bool isWindow)
{
    return nullptr;
}

RSSurfaceNode::SharedPtr RSSurfaceNode::Create(
    const RSSurfaceNodeConfig& surfaceNodeConfig, RSSurfaceNodeType type, bool isWindow, bool unobscured)
{
    return nullptr;
}

void RSSurfaceNode::CreateNodeInRenderThread() {}

RSSurfaceNode::RSSurfaceNode(const RSSurfaceNodeConfig& config, bool isRenderServiceNode)
    : RSNode(isRenderServiceNode), name_(config.SurfaceNodeName)
{}

RSSurfaceNode::RSSurfaceNode(const RSSurfaceNodeConfig& config, bool isRenderServiceNode, NodeId id)
    : RSNode(isRenderServiceNode, id), name_(config.SurfaceNodeName)
{}

RSSurfaceNode::~RSSurfaceNode() {}
} // namespace Rosen
} // namespace OHOS
