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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_MATERIAL_MATERIAL_PROCESSOR_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_MATERIAL_MATERIAL_PROCESSOR_H

#include <map>

#include "base/memory/ace_type.h"

namespace OHOS::Ace::NG {

class PipelineContext;
class FrameNode;

// Post-layout processor that enforces the scope gate for a component's
// SystemMaterial to take effect: system apps keep material effective everywhere;
// non-system apps only inside a Navigation titleBar or a bottom Tabs TabBar
// subtree (or on overlay-exempt components). Non-scope material is suppressed
// (removed) and restored on re-entry. Re-evaluated every frame after layout.
class ACE_FORCE_EXPORT MaterialProcessor : public virtual AceType {
    DECLARE_ACE_TYPE(MaterialProcessor, AceType);

public:
    MaterialProcessor() = default;
    ~MaterialProcessor() override = default;

    // Track a node that has an immersive SystemMaterial applied. Called when a
    // material is stored on the RenderContext so the processor only iterates
    // registered nodes instead of walking the frame tree.
    void Register(const RefPtr<FrameNode>& node);
    void Unregister(int32_t nodeId);

    // Scope gate (condition 1). For every registered material node, suppress
    // (remove) the material when the node is not in scope (not a system app,
    // not inside a titleBar / bottom TabBar subtree, not an overlay-exempt or
    // unrestricted component), and restore it when it is.
    void ApplyScopeGate(const RefPtr<PipelineContext>& pipeline);

private:
    // nodeId -> weak ref to the material node. Entries auto-expire when the node
    // is destroyed (Upgrade() fails) and are pruned during the post-layout pass.
    std::map<int32_t, WeakPtr<FrameNode>> materialNodes_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_MATERIAL_MATERIAL_PROCESSOR_H
