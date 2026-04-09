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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SMART_GESTURE_SMART_GESTURE_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SMART_GESTURE_SMART_GESTURE_MANAGER_H

#include <functional>
#include <memory>
#include <mutex>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include "base/memory/ace_type.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/manager/smart_gesture/smart_gesture_types.h"
#include "core/event/key_event.h"

namespace OHOS::Ace::NG {
class PipelineContext;

class ACE_FORCE_EXPORT SmartGestureManager : public virtual AceType {
    DECLARE_ACE_TYPE(SmartGestureManager, AceType);

public:
    using SmartGestureMonitor = std::function<SmartGestureHandlingResolution(const SmartGestureProposal&)>;

    explicit SmartGestureManager(const WeakPtr<PipelineContext>& context);
    ~SmartGestureManager() override = default;

    void RefreshProductGestureEnabled();

    bool HandleTrigger(SmartGestureTrigger trigger);

    bool HandleTrigger(SmartGestureTrigger trigger, const KeyEvent& event);

    bool IsProductGestureEnabled() const
    {
        return productGestureEnabled_;
    }

    void SetSmartTapAndSlideGesturesEnabled(bool enabled)
    {
        smartTapAndSlideGesturesEnabled_ = enabled;
    }

    bool IsSmartTapAndSlideGesturesEnabled() const
    {
        return smartTapAndSlideGesturesEnabled_;
    }

    void SetMonitor(SmartGestureMonitor&& callback);

    void RequestSelected(const std::string& inspectorId);
    void ClearSelected();
    void UpdateSelectedNodePaintIfNeeded(const RefPtr<FrameNode>& node);
    std::vector<RefPtr<FrameNode>> BuildVisiblePrimaryActionNodes();

    void SyncPrimaryActionNode(const RefPtr<FrameNode>& node);
    void AddPrimaryActionNode(const RefPtr<FrameNode>& node);
    void RemovePrimaryActionNode(int32_t nodeId);

private:
    RefPtr<PipelineContext> GetPipelineContext() const;
    SmartGestureMonitor GetMonitorHandle() const;
    void UpdateSelectedNode(const RefPtr<FrameNode>& node);
    void PaintSelectedNode(const RefPtr<FrameNode>& node);
    void ClearSelectedNodePaint(const RefPtr<FrameNode>& node);
    void SyncSelectedNodePaint(const RefPtr<FrameNode>& node);
    void RefreshSelectedNodeState();
    std::vector<RefPtr<FrameNode>> BuildCenterHitPath() const;
    std::vector<RefPtr<FrameNode>> BuildSelectedAncestorPath(const RefPtr<FrameNode>& selectedNode) const;
    std::optional<SmartGestureProposal> BuildSlideForwardProposal(
        const std::vector<RefPtr<FrameNode>>& visiblePrimaryNodes, const RefPtr<FrameNode>& selectedNode,
        const std::vector<RefPtr<FrameNode>>& centerHitPath) const;
    void RevealSelectedNodeIfNeeded(const RefPtr<FrameNode>& node);
    bool IsSelectedNodeValid(const RefPtr<FrameNode>& node) const;
    std::optional<SmartGestureProposal> ResolveProposal(const SmartGestureProposal& defaultProposal) const;
    bool ValidateProposal(const SmartGestureProposal& proposal) const;
    bool ValidateTargetNode(const RefPtr<FrameNode>& node) const;
    bool ValidateClickProposal(const SmartGestureProposal& proposal) const;
    bool ValidateSelectProposal(const SmartGestureProposal& proposal) const;
    bool ValidateScrollProposal(const SmartGestureProposal& proposal) const;
    bool ExecuteProposal(const SmartGestureProposal& proposal, const KeyEvent& event);
    bool ExecuteClickProposal(const RefPtr<FrameNode>& node, const KeyEvent& event);
    bool ExecuteScrollProposal(const SmartGestureProposal& proposal);
    void ExecuteBackPressProposal();
    bool IsPrimaryActionNodeActive(const RefPtr<FrameNode>& node) const;
    bool IsPrimaryActionNodeVisible(const RefPtr<FrameNode>& node) const;
    bool IsPrimaryActionNodeSelectable(const RefPtr<FrameNode>& node) const;

    bool productGestureEnabled_ = false;
    bool smartTapAndSlideGesturesEnabled_ = false;
    SmartGestureMonitor monitorCallback_;
    WeakPtr<PipelineContext> context_;
    WeakPtr<FrameNode> selectedNode_;
    WeakPtr<FrameNode> selectedPaintedNode_;
    std::unordered_map<int32_t, WeakPtr<FrameNode>> primaryActionRegistry_;
    std::unordered_map<int32_t, uint64_t> primaryActionRegistryOrder_;
    uint64_t nextPrimaryActionOrder_ = 0;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SMART_GESTURE_SMART_GESTURE_MANAGER_H
