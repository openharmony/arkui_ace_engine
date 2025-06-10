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

#ifdef ENABLE_ROSEN_BACKEND
#include "feature/anco_manager/rs_ext_node_operation.h"

#include "core/components_ng/render/adapter/rosen_render_context.h"
#endif

namespace OHOS::Ace::NG {
std::unordered_map<std::string, WeakPtr<RenderContext>> XComponentInnerSurfaceController::surfaceRenderContextMap;

std::mutex XComponentInnerSurfaceController::mutex;

int32_t XComponentInnerSurfaceController::SetRenderFitBySurfaceId(
    const std::string& surfaceId, RenderFit renderFit, bool isRenderFitNewVersionEnabled)
{
    std::lock_guard<std::mutex> lock(mutex);
    auto it = surfaceRenderContextMap.find(surfaceId);
    if (it == surfaceRenderContextMap.end()) {
        return 1;
    }
    auto weakRenderContext = it->second;
    auto renderContext = weakRenderContext.Upgrade();
    CHECK_NULL_RETURN(renderContext, 1);
    TAG_LOGI(AceLogTag::ACE_XCOMPONENT, "SetRenderFitBySurfaceId, RenderFit: %{public}d, SurfaceId: %{public}s",
        static_cast<int32_t>(renderFit), surfaceId.c_str());
    renderContext->SetRenderFit(renderFit);
#ifdef ENABLE_ROSEN_BACKEND
    auto rosenRenderContext = AceType::DynamicCast<NG::RosenRenderContext>(renderContext);
    CHECK_NULL_RETURN(rosenRenderContext, 1);
    std::shared_ptr<Rosen::RSNode> rsNode = rosenRenderContext->GetRSNode();
    CHECK_NULL_RETURN(rsNode, 1);
    auto rsSurfaceNode = rsNode->ReinterpretCastTo<Rosen::RSSurfaceNode>();
    CHECK_NULL_RETURN(rsSurfaceNode, 1);
    rsSurfaceNode->SetFrameGravityNewVersionEnabled(isRenderFitNewVersionEnabled);
#endif
    return 0;
}

int32_t XComponentInnerSurfaceController::GetRenderFitBySurfaceId(
    const std::string& surfaceId, int32_t& renderFitNumber, bool& isRenderFitNewVersionEnabled)
{
    std::lock_guard<std::mutex> lock(mutex);
    auto it = surfaceRenderContextMap.find(surfaceId);
    if (it == surfaceRenderContextMap.end()) {
        return 1;
    }
    auto weakRenderContext = it->second;
    auto renderContext = weakRenderContext.Upgrade();
    CHECK_NULL_RETURN(renderContext, 1);
    RenderFit renderFit = renderContext->GetRenderFit().value_or(RenderFit::RESIZE_FILL);
    renderFitNumber = static_cast<int32_t>(renderFit);
    isRenderFitNewVersionEnabled = false;
#ifdef ENABLE_ROSEN_BACKEND
    auto rosenRenderContext = AceType::DynamicCast<NG::RosenRenderContext>(renderContext);
    CHECK_NULL_RETURN(rosenRenderContext, 1);
    std::shared_ptr<Rosen::RSNode> rsNode = rosenRenderContext->GetRSNode();
    CHECK_NULL_RETURN(rsNode, 1);
    auto rsSurfaceNode = rsNode->ReinterpretCastTo<Rosen::RSSurfaceNode>();
    CHECK_NULL_RETURN(rsSurfaceNode, 1);
    isRenderFitNewVersionEnabled = rsSurfaceNode->GetFrameGravityNewVersionEnabled();
#endif
    return 0;
}

void XComponentInnerSurfaceController::RegisterSurfaceRenderContext(
    const std::string& surfaceId, const WeakPtr<RenderContext>& renderContext)
{
    std::lock_guard<std::mutex> lock(mutex);
    if (!renderContext.Invalid()) {
        surfaceRenderContextMap[surfaceId] = renderContext;
    }
}

void XComponentInnerSurfaceController::UnregisterSurfaceRenderContext(const std::string& surfaceId)
{
    std::lock_guard<std::mutex> lock(mutex);
    surfaceRenderContextMap.erase(surfaceId);
}
} // namespace OHOS::Ace::NG
