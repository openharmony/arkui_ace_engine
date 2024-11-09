/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_PIPELINE_NG_NAVIGATION_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_PIPELINE_NG_NAVIGATION_MANAGER_H

#include <cstdint>
#include <functional>
#include <map>

#include "base/json/json_util.h"
#include "base/memory/ace_type.h"
#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {
class NavigationStack;
struct NavigationInfo {
    std::string navigationId;
    WeakPtr<NavigationStack> pathStack;

    NavigationInfo() = default;
    NavigationInfo(const std::string& id, const WeakPtr<NavigationStack>& navigationStack)
        : navigationId(std::move(id)), pathStack(navigationStack)
    {}
};

struct NavdestinationRecoveryInfo {
    std::string name;
    std::string param;
    // mode of navdestination, 0 for standard page and 1 for dialog page
    int32_t mode;

    NavdestinationRecoveryInfo(const std::string& name, const std::string& param, int32_t mode)
        : name(std::move(name)), param(std::move(param)), mode(mode) {}
};

class NavigationManager : public virtual AceType {
    DECLARE_ACE_TYPE(NavigationManager, AceType);
public:
    using DumpLogDepth = int;
    using DumpCallback = std::function<void(DumpLogDepth)>;
    NavigationManager();
    ~NavigationManager() = default;

    void AddNavigationDumpCallback(int32_t nodeId, int32_t depth, const DumpCallback& callback);
    void RemoveNavigationDumpCallback(int32_t nodeId, int32_t depth);

    void OnDumpInfo();

    void AddNavigationUpdateCallback(std::function<void()> callback)
    {
        updateCallbacks_.emplace_back(callback);
    }

    void FireNavigationUpdateCallback();
    std::shared_ptr<NavigationInfo> GetNavigationInfo(const RefPtr<AceType>& node);

    bool IsInteractive() const
    {
        return isInteractive_;
    }

    void SetInteractive(int32_t frameNodeId)
    {
        isInteractive_ = true;
        interactiveAnimationId_ = frameNodeId;
    }

    void FinishInteractiveAnimation()
    {
        isInteractive_ = false;
    }

    void SetCurNodeAnimationCached(bool curNodeAnimationCached)
    {
        curNodeAnimationCached_ = curNodeAnimationCached;
    }
    void SetCurrentNodeNeverSet(bool currentNodeNeverSet)
    {
        currentNodeNeverSet_ = currentNodeNeverSet;
    }

    void SetPreNodeHasAnimation(bool preNodeHasAnimation)
    {
        preNodeHasAnimation_ = preNodeHasAnimation;
    }

    void SetNavNodeInTransition(const RefPtr<FrameNode>& curNode, const RefPtr<FrameNode>& preNode)
    {
        curNavNode_ = curNode;
        preNavNode_ = preNode;
    }

    void SetIsNavigationOnAnimation(bool isInAnimation)
    {
        isInAnimation_ = isInAnimation;
    }

    bool IsNavigationInAnimation() const
    {
        return isInAnimation_;
    }

    bool HasCacheNavigationNodeEnable()
    {
        return hasCacheNavigationNodeEnable_;
    }

    void UpdateRenderGroup(const RefPtr<FrameNode>& curNode, bool isSet);
    void UpdatePreNavNodeRenderGroupProperty();
    void ResetCurNavNodeRenderGroupProperty();
    void UpdateCurNavNodeRenderGroupProperty();
    void CacheNavigationNodeAnimation();
    bool CheckChildrenAnimationAndTagState(const RefPtr<FrameNode>& node);
    RefPtr<FrameNode> GetNavDestContentFrameNode(const RefPtr<FrameNode>& node);
    bool AddInteractiveAnimation(const std::function<void()>& addCallback);

    bool AddRecoverableNavigation(std::string id, RefPtr<AceType> navigationNode);
    std::unique_ptr<JsonValue> GetNavigationJsonInfo();
    void StorageNavigationRecoveryInfo(std::unique_ptr<JsonValue> allNavigationInfo);
    const std::vector<NavdestinationRecoveryInfo> GetNavigationRecoveryInfo(std::string navigationId);

private:
    struct DumpMapKey {
        int32_t nodeId;
        int32_t depth;

        DumpMapKey(int32_t n, int32_t d) : nodeId(n), depth(d) {}
        bool operator< (const DumpMapKey& o) const
        {
            if (depth != o.depth) {
                return depth < o.depth;
            }
            return nodeId < o.nodeId;
        }
    };
    std::unordered_map<std::string, WeakPtr<AceType>> recoverableNavigationMap_;
    std::unordered_map<std::string, std::vector<NavdestinationRecoveryInfo>> navigationRecoveryInfo_;
    std::map<DumpMapKey, DumpCallback> dumpMap_;
    std::vector<std::function<void()>> updateCallbacks_;
    bool isInteractive_ = false;

    RefPtr<FrameNode> curNavNode_;
    RefPtr<FrameNode> preNavNode_;
    bool currentNodeNeverSet_ = true;
    bool curNodeAnimationCached_ = false;
    bool preNodeHasAnimation_ = false;
    bool isInAnimation_ = false;
    bool hasCacheNavigationNodeEnable_ = false;
    int32_t interactiveAnimationId_ = -1;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_PIPELINE_NG_NAVIGATION_MANAGER_H
