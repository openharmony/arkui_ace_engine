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
#include "core/components/common/layout/constants.h"

namespace OHOS::Ace::NG {
class NavigationStack;
struct NavigationInfo {
    int32_t nodeId;
    std::string navigationId; // inspectorId
    WeakPtr<NavigationStack> pathStack;
    WeakPtr<FrameNode> navigationNode;
    int32_t uniqueId;
    
    NavigationInfo() = default;
    NavigationInfo(const std::string& id, const WeakPtr<NavigationStack>& navigationStack)
        : navigationId(std::move(id)), pathStack(navigationStack)
    {}
    NavigationInfo(int32_t nodeId, const std::string& navigationId, WeakPtr<FrameNode> navigationNode)
        : nodeId(nodeId), navigationId(std::move(navigationId)), navigationNode(navigationNode)
    {}
    NavigationInfo(const std::string& id, const WeakPtr<NavigationStack>& navigationStack, int32_t navigationUniqueId)
        : navigationId(std::move(id)), pathStack(navigationStack), uniqueId(std::move(navigationUniqueId))
    {}
};

struct NavigationIntentInfo {
    std::string navigationInspectorId;
    std::string navDestinationName;
    std::string param;
    bool isColdStart;

    std::string ToString()
    {
        return "-------- Navigation info below --------\n"
               "navigationId:   " + navigationInspectorId + "\n"
               "navDestName:    " + navDestinationName + "\n"
               "isColdStart:    " + (isColdStart? "yes" : "no") + "\n"
               "---------------------------------------\n";
    }
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
    NavigationManager()
    {
#ifdef PREVIEW
        hasCacheNavigationNodeEnable_ = false;
#else
        hasCacheNavigationNodeEnable_ = SystemProperties::GetCacheNavigationNodeEnable();
#endif
    }
    ~NavigationManager() = default;

    void SetPipelineContext(const WeakPtr<PipelineContext>& pipeline)
    {
        pipeline_ = pipeline;
    }

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

    void SetNodeAddAnimation(bool isNodeAddAnimation)
    {
        isNodeAddAnimation_ = isNodeAddAnimation;
    }

    void SetCurNodeAnimationCached(bool curNodeAnimationCached)
    {
        curNodeAnimationCached_ = curNodeAnimationCached;
    }

    void SetCurrentNodeNeverSet(bool currentNodeNeverSet)
    {
        currentNodeNeverSet_ = currentNodeNeverSet;
    }

    void SetPreNodeNeverSet(bool preNodeNeverSet)
    {
        preNodeNeverSet_ = preNodeNeverSet;
    }

    void SetPreNodeAnimationCached(bool preNodeAnimationCached)
    {
        preNodeAnimationCached_ = preNodeAnimationCached;
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

    void UpdateAnimationCachedRenderGroup(const RefPtr<FrameNode>& curNode, bool isSet);
    void UpdatePreNavNodeRenderGroupProperty();
    void ResetCurNavNodeRenderGroupProperty();
    void UpdateCurNavNodeRenderGroupProperty();
    void CacheNavigationNodeAnimation();
    bool CheckNodeNeedCache(const RefPtr<FrameNode>& node);
    RefPtr<FrameNode> GetNavDestContentFrameNode(const RefPtr<FrameNode>& node);
    bool AddInteractiveAnimation(const std::function<void()>& addCallback);

    bool AddRecoverableNavigation(std::string id, RefPtr<AceType> navigationNode);
    std::unique_ptr<JsonValue> GetNavigationJsonInfo();
    void StorageNavigationRecoveryInfo(std::unique_ptr<JsonValue> allNavigationInfo);
    const std::vector<NavdestinationRecoveryInfo> GetNavigationRecoveryInfo(std::string navigationId);

    void AddNavigation(int32_t parentNodeId, const RefPtr<FrameNode>& navigationNode);

    void RemoveNavigation(int32_t navigationNodeId);

    std::vector<int32_t> FindNavigationInTargetParent(int32_t targetId);

    void FireNavigationLifecycle(const RefPtr<UINode>& node, int32_t lifecycle, int32_t reason);

    void FireOverlayLifecycle(const RefPtr<UINode>& node, int32_t lifecycle, int32_t reason);

    void FireLowerLayerLifecycle(const RefPtr<UINode>& node, int lifecycle, int32_t reason);

    void FireSubWindowLifecycle(const RefPtr<UINode>& node, int32_t lifecycle, int32_t reason);

    // for non-animation
    void AddBeforeOrientationChangeTask(const std::function<void()>&& task);
    void ClearBeforeOrientationChangeTask();
    void OnOrientationChanged();
    // for intent framework
    bool FireNavigationIntentActively(int32_t pageId, bool needTransition);
    void SetNavigationIntentInfo(const std::string& intentInfoSerialized, bool isColdStart);

    std::optional<NavigationIntentInfo> GetNavigationIntentInfo() const
    {
        return navigationIntentInfo_;
    }

    void ResetNavigationIntentInfo()
    {
        navigationIntentInfo_.reset();
    }
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

    bool IsOverlayValid(const RefPtr<UINode>& frameNode);
    bool IsCustomDialogValid(const RefPtr<UINode>& node);
    NavigationIntentInfo ParseNavigationIntentInfo(const std::string& intentInfoSerialized);

    std::unordered_map<std::string, WeakPtr<AceType>> recoverableNavigationMap_;
    std::unordered_map<std::string, std::vector<NavdestinationRecoveryInfo>> navigationRecoveryInfo_;
    // record all the navigation in current UI-Context. The key is the page/model id where the navigation is located.
    std::unordered_map<int32_t, std::vector<NavigationInfo>> navigationMap_;
    std::map<DumpMapKey, DumpCallback> dumpMap_;
    std::vector<std::function<void()>> updateCallbacks_;
    bool isInteractive_ = false;

    WeakPtr<FrameNode> curNavNode_;
    WeakPtr<FrameNode> preNavNode_;
    bool currentNodeNeverSet_ = true;
    bool curNodeAnimationCached_ = false;
    bool preNodeNeverSet_ = true;
    bool preNodeAnimationCached_ = false;
    bool isInAnimation_ = false;
    bool isNodeAddAnimation_ = false;
    bool hasCacheNavigationNodeEnable_ = true;
    int32_t interactiveAnimationId_ = -1;

    WeakPtr<PipelineContext> pipeline_;
    std::vector<std::function<void()>> beforeOrientationChangeTasks_;
    std::optional<NavigationIntentInfo> navigationIntentInfo_ = std::nullopt;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_PIPELINE_NG_NAVIGATION_MANAGER_H
