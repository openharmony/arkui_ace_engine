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

#include "core/components_ng/manager/gesture_debug/gesture_debug_boundary_manager.h"

#include <array>

#include "base/utils/system_properties.h"
#include "core/components/theme/theme_manager.h"
#include "core/components_ng/base/observer_handler.h"
#include "core/components_ng/render/render_context.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {

struct GestureDebugConfig {
    GestureListenerType type;
    const char* colorResName;
    bool needsDelayReset;
};

constexpr std::array<GestureDebugConfig, GESTURE_DEBUG_TYPE_COUNT> GESTURE_DEBUG_CONFIGS = { {
    { GestureListenerType::TAP, "sys.color.ohos_id_color_palette7", true },
    { GestureListenerType::LONG_PRESS, "sys.color.ohos_id_color_palette4", false },
    { GestureListenerType::PAN, "sys.color.ohos_id_color_palette2", false },
    { GestureListenerType::PINCH, "sys.color.ohos_id_color_palette6", false },
    { GestureListenerType::SWIPE, "sys.color.ohos_id_color_palette9", true },
    { GestureListenerType::ROTATION, "sys.color.ohos_id_color_palette11", false },
} };

size_t GestureTypeIndex(GestureListenerType type)
{
    for (size_t index = 0; index < GESTURE_DEBUG_CONFIGS.size(); ++index) {
        if (GESTURE_DEBUG_CONFIGS[index].type == type) {
            return index;
        }
    }
    return 0;
}

const GestureDebugConfig* GetGestureDebugConfig(GestureListenerType type)
{
    for (const auto& config : GESTURE_DEBUG_CONFIGS) {
        if (config.type == type) {
            return &config;
        }
    }
    return nullptr;
}

bool NeedsDelayReset(GestureListenerType type)
{
    auto config = GetGestureDebugConfig(type);
    return config ? config->needsDelayReset : false;
}

} // namespace

void GestureDebugBoundaryManager::HandleGestureAccept(GestureListenerType type, const RefPtr<FrameNode>& node)
{
    CHECK_EQUAL_VOID(SystemProperties::GetGestureDebugBoundaryEnabled(), false);
    CHECK_NULL_VOID(node);

    auto nodeId = node->GetId();
    auto& state = nodeStates_[nodeId];
    state.node = WeakPtr<FrameNode>(node);

    // Cancel prior delay task for same gesture type if exists
    CancelDelayReset(type, state);

    // Set active bit
    state.activeGestures.set(GestureTypeIndex(type));

    // For Tap/Swipe, schedule delayed reset
    if (NeedsDelayReset(type)) {
        ScheduleDelayReset(type, nodeId, WeakPtr<FrameNode>(node));
    }

    // Build and deliver render snapshot
    auto info = BuildRenderInfo(node, state);
    NotifyNodeRefresh(node, info);
}

void GestureDebugBoundaryManager::HandleGestureEnd(GestureListenerType type, const RefPtr<FrameNode>& node)
{
    CHECK_EQUAL_VOID(SystemProperties::GetGestureDebugBoundaryEnabled(), false);
    CHECK_NULL_VOID(node);

    auto nodeId = node->GetId();
    auto iter = nodeStates_.find(nodeId);
    if (iter == nodeStates_.end()) {
        return;
    }

    auto& state = iter->second;
    CancelDelayReset(type, state);
    state.activeGestures.reset(GestureTypeIndex(type));

    if (state.activeGestures.none() && state.delayedResetTasks.empty()) {
        nodeStates_.erase(iter);
        NotifyNodeRefresh(node, GestureDebugBoundaryInfo {});
    } else if (state.activeGestures.any()) {
        auto info = BuildRenderInfo(node, state);
        NotifyNodeRefresh(node, info);
    }
    // else: no active gestures but delay tasks still pending; border will be cleared by the delay callbacks
}

void GestureDebugBoundaryManager::ClearNode(int32_t nodeId)
{
    auto iter = nodeStates_.find(nodeId);
    if (iter == nodeStates_.end()) {
        return;
    }

    auto node = iter->second.node.Upgrade();
    // Cancel all pending delay tasks
    for (auto& [type, task] : iter->second.delayedResetTasks) {
        task.Cancel();
    }
    if (node) {
        NotifyNodeRefresh(node, GestureDebugBoundaryInfo {});
    }
    nodeStates_.erase(iter);
}

void GestureDebugBoundaryManager::ScheduleDelayReset(
    GestureListenerType type, int32_t nodeId, const WeakPtr<FrameNode>& weakNode)
{
    auto iter = nodeStates_.find(nodeId);
    if (iter == nodeStates_.end()) {
        return;
    }

    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);

    auto weakManager = WeakClaim(this);
    auto&& callback = [weakManager, type, nodeId, weakNode]() {
        auto manager = weakManager.Upgrade();
        CHECK_NULL_VOID(manager);
        auto node = weakNode.Upgrade();
        if (!node) {
            manager->ClearNode(nodeId);
            return;
        }
        auto state = manager->GetNodeState(nodeId);
        if (!state) {
            return;
        }
        state->delayedResetTasks.erase(type);
        state->activeGestures.reset(GestureTypeIndex(type));

        if (state->activeGestures.none() && state->delayedResetTasks.empty()) {
            manager->EraseNodeState(nodeId);
            manager->NotifyNodeRefresh(node, GestureDebugBoundaryInfo {});
        } else {
            auto info = manager->BuildRenderInfo(node, *state);
            manager->NotifyNodeRefresh(node, info);
        }
    };

    auto& delayTask = iter->second.delayedResetTasks[type];
    delayTask.Reset(callback);
    auto taskExecutor = SingleTaskExecutor::Make(pipeline->GetTaskExecutor(), TaskExecutor::TaskType::UI);
    taskExecutor.PostDelayedTask(delayTask, DELAY_RESET_MS, "ArkUIGestureDebugBoundaryDelayReset");
}

void GestureDebugBoundaryManager::CancelDelayReset(GestureListenerType type, GestureDebugBoundaryState& state)
{
    auto iter = state.delayedResetTasks.find(type);
    if (iter != state.delayedResetTasks.end()) {
        iter->second.Cancel();
        state.delayedResetTasks.erase(iter);
    }
}

GestureDebugBoundaryState* GestureDebugBoundaryManager::GetNodeState(int32_t nodeId)
{
    auto iter = nodeStates_.find(nodeId);
    return iter != nodeStates_.end() ? &iter->second : nullptr;
}

void GestureDebugBoundaryManager::EraseNodeState(int32_t nodeId)
{
    nodeStates_.erase(nodeId);
}

std::optional<GestureDebugBoundaryInfo> GestureDebugBoundaryManager::BuildRenderInfo(
    const RefPtr<FrameNode>& node, const GestureDebugBoundaryState& state)
{
    CHECK_EQUAL_RETURN(state.activeGestures.none(), true, GestureDebugBoundaryInfo {});
    CHECK_NULL_RETURN(node, std::nullopt);

    // Check minimum size threshold
    auto geometryNode = node->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, std::nullopt);
    auto frameSize = geometryNode->GetMarginFrameSize();
    auto pipeline = node->GetContext();
    CHECK_NULL_RETURN(pipeline, std::nullopt);
    auto density = static_cast<float>(pipeline->GetDensity());
    float thresholdPx = MIN_SIZE_THRESHOLD_VP * density;
    if ((frameSize.Width() < thresholdPx) || (frameSize.Height() < thresholdPx)) {
        return GestureDebugBoundaryInfo {};
    }

    GestureDebugBoundaryInfo info;
    info.strokeWidthPx = DEFAULT_STROKE_WIDTH_PX;
    info.gestureMask = static_cast<uint8_t>(state.activeGestures.to_ulong());

    for (const auto& config : GESTURE_DEBUG_CONFIGS) {
        const auto index = GestureTypeIndex(config.type);
        if (state.activeGestures.test(index)) {
            info.colors.emplace_back(ResolveGestureColor(node, config.type));
        }
    }

    return info;
}

Color GestureDebugBoundaryManager::ResolveGestureColor(const RefPtr<FrameNode>& node, GestureListenerType type) const
{
    auto config = GetGestureDebugConfig(type);
    if (!config || !config->colorResName) {
        return Color::RED;
    }

    auto pipeline = node->GetContext();
    CHECK_NULL_RETURN(pipeline, Color::RED);
    auto themeManager = pipeline->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, Color::RED);
    auto themeConstants = themeManager->GetThemeConstants();
    CHECK_NULL_RETURN(themeConstants, Color::RED);
    return themeConstants->GetColorByName(config->colorResName);
}

void GestureDebugBoundaryManager::NotifyNodeRefresh(
    const RefPtr<FrameNode>& node, const std::optional<GestureDebugBoundaryInfo>& info)
{
    CHECK_NULL_VOID(node);
    auto renderContext = node->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->PaintGestureDebugBoundary(info);
    renderContext->RequestNextFrame();
}

} // namespace OHOS::Ace::NG
