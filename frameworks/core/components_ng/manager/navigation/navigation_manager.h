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
#include "core/components/common/properties/color.h"

namespace OHOS::Ace::NG {
class NavigationStack;
struct NavigationInfo {
    int32_t nodeId = -1;
    std::string navigationId; // inspectorId
    WeakPtr<NavigationStack> pathStack;
    WeakPtr<FrameNode> navigationNode;
    int32_t uniqueId = -1;
    
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

using GetSystemColorCallback = std::function<bool(const std::string&, Color&)>;

const std::pair<bool, int32_t> DEFAULT_EXIST_FORCESPLIT_NAV_VALUE = {false, -1};

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

    void AddNavigationDumpCallback(const RefPtr<FrameNode>& navigationNode, const DumpCallback& callback);
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

    void SetGetSystemColorCallback(GetSystemColorCallback&& callback)
    {
        getSystemColorCallback_ = std::move(callback);
    }
    bool GetSystemColor(const std::string& name, Color& color)
    {
        if (getSystemColorCallback_) {
            return getSystemColorCallback_(name, color);
        }
        return false;
    }
    bool IsForceSplitSupported() const
    {
        return isForceSplitSupported_;
    }
    void SetForceSplitEnable(bool isForceSplit, const std::string& homePage, bool ignoreOrientation = false);
    bool IsForceSplitEnable() const
    {
        return isForceSplitEnable_;
    }
    const std::string& GetHomePageName() const
    {
        return homePageName_;
    }
    bool GetIgnoreOrientation() const;

    void AddForceSplitListener(int32_t nodeId, std::function<void()>&& listener);
    void RemoveForceSplitListener(int32_t nodeId);
    bool IsOuterMostNavigation(int32_t nodeId, int32_t depth);

    std::string GetTopNavDestinationInfo(int32_t pageId, bool onlyFullScreen, bool needParam);
    void RestoreNavDestinationInfo(const std::string& navDestinationInfo, bool isColdStart);

    //-------force split begin-------
    void IsTargetForceSplitNav(const RefPtr<FrameNode>& navigationNode);
    void SetForceSplitNavState(bool isTargetForceSplitNav, const RefPtr<FrameNode>& navigationNode);
    void RemoveForceSplitNavStateIfNeed(int32_t nodeId);
    void SetExistForceSplitNav(bool isTargetForceSplitNav, int32_t id)
    {
        existForceSplitNav_ = {isTargetForceSplitNav, id};
    }
    std::pair<bool, int32_t> GetExistForceSplitNav() const
    {
        return existForceSplitNav_;
    }
    bool TargetIdOrDepthExists() const
    {
        return forceSplitNavigationId_.has_value() || forceSplitNavigationDepth_.has_value();
    }
    void SetForceSplitNavigationId(std::optional<std::string> forceSplitNavigationId)
    {
        forceSplitNavigationId_ = forceSplitNavigationId;
    }
    void SetForceSplitNavigationDepth(std::optional<int32_t> forceSplitNavigationDepth)
    {
        forceSplitNavigationDepth_ = forceSplitNavigationDepth;
    }
    std::optional<std::string> GetTargetNavigationId() const
    {
        return forceSplitNavigationId_;
    }
    std::optional<int32_t> GetTargetNavigationDepth() const
    {
        return forceSplitNavigationDepth_;
    }
    //-------force split end-------
private:
    struct DumpMapKey {
        int32_t nodeId;
        int32_t depth;

        DumpMapKey(int32_t n, int32_t d) : nodeId(n), depth(d) {}
        bool operator== (const DumpMapKey& o) const
        {
            return nodeId == o.nodeId && depth == o.depth;
        }
        bool operator< (const DumpMapKey& o) const
        {
            if (depth != o.depth) {
                return depth < o.depth;
            }
            return nodeId < o.nodeId;
        }
    };

    RefPtr<FrameNode> GetNavigationByInspectorId(const std::string& id) const;
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

    GetSystemColorCallback getSystemColorCallback_;
    bool isForceSplitSupported_ = false;
    bool isForceSplitEnable_ = false;
    std::string homePageName_;
    std::unordered_map<int32_t, std::function<void()>> forceSplitListeners_;
    bool ignoreOrientation_ = false;

    //-------force split begin-------
    int32_t currNestedDepth_ = 0;
    std::pair<bool, int32_t> existForceSplitNav_ = DEFAULT_EXIST_FORCESPLIT_NAV_VALUE;
    std::optional<std::string> forceSplitNavigationId_;
    std::optional<int32_t> forceSplitNavigationDepth_;
    //-------force split end-------
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_PIPELINE_NG_NAVIGATION_MANAGER_H
