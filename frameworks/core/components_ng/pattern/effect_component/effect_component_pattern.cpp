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

#include "core/components_ng/pattern/effect_component/effect_component_pattern.h"

#include "core/components_ng/render/adapter/rosen_render_context.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "render_service_client/core/ui/rs_surface_node.h"

namespace OHOS::Ace::NG {
namespace {
std::unordered_map<NG::EffectLayer, Rosen::TopLayerZOrder> effectLayerMap = {
    { NG::EffectLayer::CHARGE, Rosen::TopLayerZOrder::CHARGE_3D_MOTION },
    { NG::EffectLayer::TEXT, Rosen::TopLayerZOrder::CHARGE_ACTION_TEXT }
};
}

void EffectComponentPattern::AlwaysSnapshot(bool enable) const
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = AceType::DynamicCast<NG::RosenRenderContext>(host->GetRenderContext());
    CHECK_NULL_VOID(context);
    context->SetAlwaysSnapshot(enable);
}

bool EffectComponentPattern::OnDirtyLayoutWrapperSwap(
    const RefPtr<LayoutWrapper>& /*dirty*/, bool /*skipMeasure*/, bool /*skipLayout*/)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto pipiline = host->GetContext();
    CHECK_NULL_RETURN(pipiline, false);
    auto parent = host->GetParent();
    CHECK_NULL_RETURN(parent, false);
    if (parent_.Upgrade() == parent || effectLayer_ == EffectLayer::NONE) {
        return false;
    }
    parent_ = parent;
    pipiline->AddAfterLayoutTask([weak = AceType::WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto host = pattern->GetHost();
        CHECK_NULL_VOID(host);
        auto renderContext = host->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        auto rsNode = AceType::DynamicCast<NG::RosenRenderContext>(renderContext)->GetRSNode();
        CHECK_NULL_VOID(rsNode);
        auto surfaceNode = rsNode->ReinterpretCastTo<Rosen::RSSurfaceNode>();
        CHECK_NULL_VOID(surfaceNode);
        if (effectLayerMap.find(pattern->GetEffectLayer()) == effectLayerMap.end()) {
            return;
        }
        Rosen::TopLayerZOrder zOrder = effectLayerMap[pattern->GetEffectLayer()];
        surfaceNode->SetCompositeLayer(zOrder);
    });

    return false;
}
} // namespace OHOS::Ace::NG