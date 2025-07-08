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

#include "core/components_ng/pattern/xcomponent/xcomponent_inner_surface_controller.h"

#include "core/components_ng/pattern/xcomponent/xcomponent_pattern.h"
#ifdef ENABLE_ROSEN_BACKEND
#include "feature/anco_manager/rs_ext_node_operation.h"

#include "core/components_ng/render/adapter/rosen_render_context.h"
#endif

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t XCOMPONENT_CONTROLLER_NO_ERROR = 0;
constexpr int32_t XCOMPONENT_CONTROLLER_INVALID_PARAMETER = 1;
} // namespace
std::unordered_map<std::string, WeakPtr<FrameNode>> XComponentInnerSurfaceController::nodeMap;

std::mutex XComponentInnerSurfaceController::mutex;

int32_t XComponentInnerSurfaceController::SetRenderFitBySurfaceId(
    const std::string& surfaceId, RenderFit renderFit, bool isRenderFitNewVersionEnabled)
{
    std::lock_guard<std::mutex> lock(mutex);
    auto it = nodeMap.find(surfaceId);
    if (it == nodeMap.end()) {
        return XCOMPONENT_CONTROLLER_INVALID_PARAMETER;
    }
    auto weakNode = it->second;
    auto node = weakNode.Upgrade();
    CHECK_NULL_RETURN(node, XCOMPONENT_CONTROLLER_INVALID_PARAMETER);
    auto xcPattern = AceType::DynamicCast<XComponentPattern>(node->GetPattern());
    CHECK_NULL_RETURN(xcPattern, XCOMPONENT_CONTROLLER_INVALID_PARAMETER);
    auto renderContext = xcPattern->GetRenderContextForSurface();
    CHECK_NULL_RETURN(renderContext, XCOMPONENT_CONTROLLER_INVALID_PARAMETER);
    renderContext->SetRenderFit(renderFit);
#ifdef ENABLE_ROSEN_BACKEND
    auto rosenRenderContext = AceType::DynamicCast<NG::RosenRenderContext>(renderContext);
    CHECK_NULL_RETURN(rosenRenderContext, XCOMPONENT_CONTROLLER_INVALID_PARAMETER);
    std::shared_ptr<Rosen::RSNode> rsNode = rosenRenderContext->GetRSNode();
    CHECK_NULL_RETURN(rsNode, XCOMPONENT_CONTROLLER_INVALID_PARAMETER);
    auto rsSurfaceNode = rsNode->ReinterpretCastTo<Rosen::RSSurfaceNode>();
    CHECK_NULL_RETURN(rsSurfaceNode, XCOMPONENT_CONTROLLER_INVALID_PARAMETER);
    TAG_LOGI(AceLogTag::ACE_XCOMPONENT, "SetRenderFitBySurfaceId, RenderFit: %{public}d, SurfaceId: %{public}s, "
        "isNewVersion: %{public}d", static_cast<int32_t>(renderFit), surfaceId.c_str(), isRenderFitNewVersionEnabled);
    rsSurfaceNode->SetFrameGravityNewVersionEnabled(isRenderFitNewVersionEnabled);
#endif
    node->MarkNeedRenderOnly();
    return XCOMPONENT_CONTROLLER_NO_ERROR;
}

int32_t XComponentInnerSurfaceController::GetRenderFitBySurfaceId(
    const std::string& surfaceId, int32_t& renderFitNumber, bool& isRenderFitNewVersionEnabled)
{
    std::lock_guard<std::mutex> lock(mutex);
    auto it = nodeMap.find(surfaceId);
    if (it == nodeMap.end()) {
        return XCOMPONENT_CONTROLLER_INVALID_PARAMETER;
    }
    auto weakNode = it->second;
    auto node = weakNode.Upgrade();
    CHECK_NULL_RETURN(node, XCOMPONENT_CONTROLLER_INVALID_PARAMETER);
    auto xcPattern = AceType::DynamicCast<XComponentPattern>(node->GetPattern());
    CHECK_NULL_RETURN(xcPattern, XCOMPONENT_CONTROLLER_INVALID_PARAMETER);
    auto renderContext = xcPattern->GetRenderContextForSurface();
    CHECK_NULL_RETURN(renderContext, XCOMPONENT_CONTROLLER_INVALID_PARAMETER);
    RenderFit renderFit = renderContext->GetRenderFit().value_or(RenderFit::RESIZE_FILL);
    renderFitNumber = static_cast<int32_t>(renderFit);
    isRenderFitNewVersionEnabled = false;
#ifdef ENABLE_ROSEN_BACKEND
    auto rosenRenderContext = AceType::DynamicCast<NG::RosenRenderContext>(renderContext);
    CHECK_NULL_RETURN(rosenRenderContext, XCOMPONENT_CONTROLLER_INVALID_PARAMETER);
    std::shared_ptr<Rosen::RSNode> rsNode = rosenRenderContext->GetRSNode();
    CHECK_NULL_RETURN(rsNode, XCOMPONENT_CONTROLLER_INVALID_PARAMETER);
    auto rsSurfaceNode = rsNode->ReinterpretCastTo<Rosen::RSSurfaceNode>();
    CHECK_NULL_RETURN(rsSurfaceNode, XCOMPONENT_CONTROLLER_INVALID_PARAMETER);
    isRenderFitNewVersionEnabled = rsSurfaceNode->GetFrameGravityNewVersionEnabled();
#endif
    return XCOMPONENT_CONTROLLER_NO_ERROR;
}

void XComponentInnerSurfaceController::RegisterNode(
    const std::string& surfaceId, const WeakPtr<FrameNode>& node)
{
    std::lock_guard<std::mutex> lock(mutex);
    if (!node.Invalid()) {
        nodeMap[surfaceId] = node;
    }
}

void XComponentInnerSurfaceController::UnregisterNode(const std::string& surfaceId)
{
    std::lock_guard<std::mutex> lock(mutex);
    nodeMap.erase(surfaceId);
}
} // namespace OHOS::Ace::NG
