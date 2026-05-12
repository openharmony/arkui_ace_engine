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
#include "frameworks/core/accessibility/utils/accessibility_manager_utils.h"
#include "base/log/log_wrapper.h"
#include "frameworks/core/accessibility/accessibility_manager.h"

namespace OHOS::Ace::NG {

void NextFocusRelationController::RebuildTargetPrimaryForTarget(
    const std::string& targetInspectorId,
    TargetMap& targetMap,
    std::map<int64_t, NextFocusSourceEntry>& sourceMap,
    std::map<std::string, std::set<int64_t>>& targetSourcesMap)
{
    auto targetIt = targetSourcesMap.find(targetInspectorId);
    if (targetIt == targetSourcesMap.end() || targetIt->second.empty()) {
        targetMap.erase(targetInspectorId);
        return;
    }
    for (auto sourceAccessibilityId : targetIt->second) {
        auto sourceIt = sourceMap.find(sourceAccessibilityId);
        if (sourceIt == sourceMap.end()) {
            continue;
        }
        if (sourceIt->second.targetInspectorId != targetInspectorId) {
            continue;
        }
        targetMap[targetInspectorId] = { sourceAccessibilityId, sourceIt->second.descendantMode };
        return;
    }
    targetMap.erase(targetInspectorId);
}

void NextFocusRelationController::RemoveSourceRelationByAccessibilityId(
    int64_t sourceAccessibilityId,
    TargetMap& targetMap,
    std::map<int64_t, NextFocusSourceEntry>& sourceMap,
    std::map<std::string, std::set<int64_t>>& targetSourcesMap)
{
    auto sourceIt = sourceMap.find(sourceAccessibilityId);
    if (sourceIt == sourceMap.end()) {
        return;
    }
    auto oldTargetInspectorId = sourceIt->second.targetInspectorId;
    sourceMap.erase(sourceIt);
    auto targetIt = targetSourcesMap.find(oldTargetInspectorId);
    if (targetIt != targetSourcesMap.end()) {
        targetIt->second.erase(sourceAccessibilityId);
        if (targetIt->second.empty()) {
            targetSourcesMap.erase(targetIt);
        }
    }
    RebuildTargetPrimaryForTarget(oldTargetInspectorId, targetMap, sourceMap, targetSourcesMap);
}

void NextFocusRelationController::HandleExistingContext(
    std::map<int32_t, TargetMap>::iterator& targetMapIt,
    std::map<int32_t, std::map<int64_t, NextFocusSourceEntry>>::iterator& sourceMapIt,
    std::map<int32_t, std::map<std::string, std::set<int64_t>>>::iterator& targetSourcesIt,
    const std::string& nextFocusInspectorKey, int64_t sourceAccessibilityId, bool descendantMode)
{
    auto& targetMap = targetMapIt->second;
    auto& sourceMap = sourceMapIt->second;
    auto& targetSourcesMap = targetSourcesIt->second;

    RemoveSourceRelationByAccessibilityId(sourceAccessibilityId, targetMap, sourceMap, targetSourcesMap);
    if (nextFocusInspectorKey.empty()) {
        return;
    }
    sourceMap[sourceAccessibilityId] = { nextFocusInspectorKey, descendantMode };
    targetSourcesMap[nextFocusInspectorKey].insert(sourceAccessibilityId);
    targetMap[nextFocusInspectorKey] = { sourceAccessibilityId, descendantMode }; // latest source wins
}

void NextFocusRelationController::UpdateNextFocusIdMap(
    int32_t containerId, const std::string& nextFocusInspectorKey, int64_t sourceAccessibilityId, bool descendantMode)
{
    auto targetFindIt = nextFocusMapWithSubWindow_.find(containerId);
    auto sourceFindIt = nextFocusSourceMapWithSubWindow_.find(containerId);
    auto targetSourcesFindIt = nextFocusTargetSourcesWithSubWindow_.find(containerId);
    if (targetFindIt == nextFocusMapWithSubWindow_.end() &&
        sourceFindIt == nextFocusSourceMapWithSubWindow_.end() &&
        targetSourcesFindIt == nextFocusTargetSourcesWithSubWindow_.end() &&
        nextFocusInspectorKey.empty()) {
        return;
    }

    auto targetIt = nextFocusMapWithSubWindow_.try_emplace(containerId).first;
    auto sourceIt = nextFocusSourceMapWithSubWindow_.try_emplace(containerId).first;
    auto targetSourcesIt = nextFocusTargetSourcesWithSubWindow_.try_emplace(containerId).first;
    HandleExistingContext(
        targetIt, sourceIt, targetSourcesIt, nextFocusInspectorKey, sourceAccessibilityId, descendantMode);

    if (targetIt->second.empty() && sourceIt->second.empty() && targetSourcesIt->second.empty()) {
        nextFocusMapWithSubWindow_.erase(targetIt);
        nextFocusSourceMapWithSubWindow_.erase(containerId);
        nextFocusTargetSourcesWithSubWindow_.erase(containerId);
    }
}

bool NextFocusRelationController::GetNextFocusDescendantMode(int32_t containerId, const std::string& inspectorId) const
{
    if (inspectorId.empty()) {
        return false;
    }
    auto containerIt = nextFocusMapWithSubWindow_.find(containerId);
    if (containerIt == nextFocusMapWithSubWindow_.end()) {
        return false;
    }
    auto it = containerIt->second.find(inspectorId);
    if (it != containerIt->second.end()) {
        return it->second.descendantMode;
    }
    return false;
}

const NextFocusRelationController::TargetMap& NextFocusRelationController::GetTargetMap(int32_t containerId) const
{
    auto containerIt = nextFocusMapWithSubWindow_.find(containerId);
    if (containerIt == nextFocusMapWithSubWindow_.end()) {
        return emptyTargetMap_;
    }
    return containerIt->second;
}

void AccessibilityEventBlockerInAction::AddBlockedEvent(int64_t actionId, AccessibilityEventType event)
{
    CHECK_EQUAL_VOID(actionId, -1);
    if (currentActionId_ == -1) {
        currentActionId_ = actionId;
    }
    if (currentActionId_ != actionId) {
        TAG_LOGI(AceLogTag::ACE_ACCESSIBILITY,
            "AddBlockedEvent fail by currentActionId_ %{public}" PRId64
            " actionId: %{public}" PRId64, currentActionId_, actionId);
        return;
    }
    blockedEvents_.insert(static_cast<uint32_t>(event));
}

void AccessibilityEventBlockerInAction::SetBlockedEvents(int64_t actionId,
    const std::vector<AccessibilityEventType>& events)
{
    CHECK_EQUAL_VOID(actionId, -1);
    if (currentActionId_ == -1) {
        currentActionId_ = actionId;
    }
    if (currentActionId_ != actionId) {
        TAG_LOGI(AceLogTag::ACE_ACCESSIBILITY,
            "SetBlockedEvents fail by currentActionId_ %{public}" PRId64
            " actionId: %{public}" PRId64, currentActionId_, actionId);
        return;
    }
    blockedEvents_.clear();
    blockedEvents_.reserve(events.size());
    
    for (const auto& event : events) {
        blockedEvents_.insert(static_cast<uint32_t>(event));
    }
}


bool AccessibilityEventBlockerInAction::ShouldBlock(int64_t actionId, AccessibilityEventType eventType) const
{
    CHECK_EQUAL_RETURN(actionId, -1, false);
    CHECK_NE_RETURN(actionId, currentActionId_, false);
    CHECK_NE_RETURN(blockedEvents_.find(static_cast<uint32_t>(eventType)), blockedEvents_.end(), true);
    return false;
}

void AccessibilityEventBlockerInAction::Reset()
{
    currentActionId_ = -1;
    blockedEvents_.clear();
}
} // namespace OHOS::Ace::NG
