/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/manager/material/material_processor.h"

#include "core/components/common/properties/ui_material.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/render/render_context.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

void MaterialProcessor::Register(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_VOID(node);
    materialNodes_[node->GetId()] = WeakPtr<FrameNode>(node);
}

void MaterialProcessor::Unregister(int32_t nodeId)
{
    materialNodes_.erase(nodeId);
}

void MaterialProcessor::ApplyScopeGate(const RefPtr<PipelineContext>& pipeline)
{
    CHECK_NULL_VOID(pipeline);
    if (MaterialUtils::IsMaterialDisabled()) {
        return;
    }
    for (auto it = materialNodes_.begin(); it != materialNodes_.end();) {
        auto frameNode = it->second.Upgrade();
        if (!frameNode || frameNode->IsInDestroying() || frameNode->GetContext() != pipeline.GetRawPtr()) {
            it = materialNodes_.erase(it);
            continue;
        }
        const auto& rc = frameNode->GetRenderContext();
        if (!rc || !frameNode->IsVisibleAndActive()) {
            ++it;
            continue;
        }
        // Scope gate: system apps keep material effective everywhere; non-system
        // apps only inside a titleBar or a bottom Tabs TabBar subtree (both tracked
        // by inherited flags, O(1)). Unrestricted components (Slider / Toggle) and
        // overlay-exempt components (popup / dialog / menu / sheet / toast / select)
        // are always effective regardless of scope or system-app status.
        bool inScope = frameNode->IsInTitleBar() || frameNode->IsInBottomTabBar();
        bool effective = MaterialUtils::IsMaterialUnrestrictedComponent(frameNode->GetTag()) ||
                         MaterialUtils::IsSystemApp() || inScope ||
                         rc->IsMaterialScopeExempt() ||
                         frameNode->IsInCustomSelectMenu();
        if (!effective) {
            // Not in scope -> fully remove the material. Save it first so it can be
            // restored if the node re-enters a titleBar / bottom TabBar.
            if (!rc->IsMaterialSuppressed()) {
                auto material = rc->GetSystemMaterial();
                if (material) {
                    rc->SetSavedMaterialForSuppress(material);
                    // Mark suppressed BEFORE the clear so RenderContext::SetSystemMaterial
                    // keeps the node registered (intended = suppressed).
                    rc->SetMaterialSuppressed(true);
                    // Guard this limiter-owned clear so ViewAbstract::SetSystemMaterial
                    // does not block it as an "external call on a suppressed node".
                    rc->SetMaterialLimiterUpdating(true);
                    ViewAbstract::SetSystemMaterial(AceType::RawPtr(frameNode), nullptr);
                    LOGW("Material inactive: out of scope. Use component in navigation title bar or Tabbar.");
                    rc->SetMaterialLimiterUpdating(false);
                    frameNode->MarkDirtyNode();
                    auto pattern = frameNode->GetPattern();
                    if (pattern) {
                        pattern->OnMaterialDisable();
                    }
                }
            }
        } else if (rc->IsMaterialSuppressed()) {
            // Back in scope: restore the saved material.
            auto saved = rc->GetSavedMaterialForSuppress();
            rc->SetSavedMaterialForSuppress(nullptr);
            // Guard this limiter-owned restore so ViewAbstract::SetSystemMaterial
            // does not block it (the node is still flagged suppressed here).
            rc->SetMaterialLimiterUpdating(true);
            ViewAbstract::SetSystemMaterial(AceType::RawPtr(frameNode), saved.GetRawPtr());
            rc->SetMaterialSuppressed(false);
            rc->SetMaterialLimiterUpdating(false);
            frameNode->MarkDirtyNode();
        }
        ++it;
    }
}

} // namespace OHOS::Ace::NG
