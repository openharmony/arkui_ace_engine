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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_GESTURE_DEBUG_BOUNDARY_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_GESTURE_DEBUG_BOUNDARY_MANAGER_H

#include <bitset>
#include <cstddef>
#include <optional>
#include <unordered_map>
#include <vector>

#include "base/memory/ace_type.h"
#include "base/thread/cancelable_callback.h"
#include "core/components/common/properties/color.h"

namespace OHOS::Ace::NG {

class FrameNode;
enum class GestureListenerType;
inline constexpr size_t GESTURE_DEBUG_TYPE_COUNT = 6;

// Render snapshot delivered to DebugBoundaryPainter
struct GestureDebugBoundaryInfo {
    uint8_t gestureMask = 0;
    float strokeWidthPx = 8.0f;
    std::vector<Color> colors;
};

// Per-node internal state
struct GestureDebugBoundaryState {
    WeakPtr<FrameNode> node;
    std::bitset<GESTURE_DEBUG_TYPE_COUNT> activeGestures;
    std::unordered_map<GestureListenerType, CancelableCallback<void()>> delayedResetTasks;
};

class GestureDebugBoundaryManager : public AceType {
    DECLARE_ACE_TYPE(GestureDebugBoundaryManager, AceType);

public:
    GestureDebugBoundaryManager() = default;
    ~GestureDebugBoundaryManager() override = default;

    void HandleGestureAccept(GestureListenerType type, const RefPtr<FrameNode>& node);
    void HandleGestureEnd(GestureListenerType type, const RefPtr<FrameNode>& node);
    void ClearNode(int32_t nodeId);

private:
    static constexpr uint32_t DELAY_RESET_MS = 300;
    static constexpr float MIN_SIZE_THRESHOLD_VP = 32.0f;
    static constexpr float DEFAULT_STROKE_WIDTH_PX = 8.0f;

    void ScheduleDelayReset(GestureListenerType type, int32_t nodeId, const WeakPtr<FrameNode>& weakNode);
    void CancelDelayReset(GestureListenerType type, GestureDebugBoundaryState& state);
    GestureDebugBoundaryState* GetNodeState(int32_t nodeId);
    void EraseNodeState(int32_t nodeId);
    std::optional<GestureDebugBoundaryInfo> BuildRenderInfo(
        const RefPtr<FrameNode>& node, const GestureDebugBoundaryState& state);
    Color ResolveGestureColor(const RefPtr<FrameNode>& node, GestureListenerType type) const;
    void NotifyNodeRefresh(const RefPtr<FrameNode>& node, const std::optional<GestureDebugBoundaryInfo>& info);

    std::unordered_map<int32_t, GestureDebugBoundaryState> nodeStates_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_GESTURE_DEBUG_BOUNDARY_MANAGER_H
