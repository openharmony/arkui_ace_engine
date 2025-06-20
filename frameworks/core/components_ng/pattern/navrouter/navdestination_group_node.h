/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVROUTER_NAVDESTINATION_GROUP_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVROUTER_NAVDESTINATION_GROUP_NODE_H

#include <cstdint>
#include <list>

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/group_node.h"
#include "core/components_ng/pattern/navigation/navdestination_node_base.h"
#include "core/components_ng/pattern/navigation/navigation_declaration.h"
#include "core/components_ng/property/property.h"
#include "core/pipeline/base/element_register.h"

namespace OHOS::Ace::NG {

class CustomNodeBase;
class NavigationTransitionProxy;

using NavDestinationBackButtonEvent = std::function<bool(GestureEvent&)>;

class ACE_EXPORT NavDestinationGroupNode : public NavDestinationNodeBase {
    DECLARE_ACE_TYPE(NavDestinationGroupNode, NavDestinationNodeBase)
public:
    NavDestinationGroupNode(const std::string& tag, int32_t nodeId, const RefPtr<Pattern>& pattern)
        : NavDestinationNodeBase(tag, nodeId, pattern)
    {
        isNewToolbar_ = true;
    }
    ~NavDestinationGroupNode() override;
    void AddChildToGroup(const RefPtr<UINode>& child, int32_t slot = DEFAULT_NODE_SLOT) override;
    void DeleteChildFromGroup(int32_t slot = DEFAULT_NODE_SLOT) override;
    static RefPtr<NavDestinationGroupNode> GetOrCreateGroupNode(
        const std::string& tag, int32_t nodeId, const std::function<RefPtr<Pattern>(void)>& patternCreator);
    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override;

    void SetNavDestinationBackButtonEvent(const NavDestinationBackButtonEvent& backButtonEvent)
    {
        backButtonEvent_ = backButtonEvent;
    }

    NavDestinationBackButtonEvent GetNavDestinationBackButtonEvent() const
    {
        return backButtonEvent_;
    }

    void OnAttachToMainTree(bool recursive) override;

    void OnOffscreenProcess(bool recursive) override;

    void ProcessShallowBuilder();

    void SetIsOnAnimation(bool isOnAnimation)
    {
        isOnAnimation_ = isOnAnimation;
    }

    bool IsOnAnimation() const
    {
        return isOnAnimation_;
    }

    RefPtr<CustomNodeBase> GetNavDestinationCustomNode();
    
    void SetNavDestinationCustomNode(WeakPtr<CustomNodeBase> customNode)
    {
        customNode_ = customNode;
    }

    void SetNavDestinationMode(NavDestinationMode mode);

    NavDestinationMode GetNavDestinationMode() const;

    void SetIndex(int32_t index, bool updatePrimary = true);

    int32_t GetIndex() const
    {
        return index_;
    }

    void SetIsCacheNode(bool cache)
    {
        isCacheNode_ = cache;
    }

    bool IsCacheNode() const
    {
        return isCacheNode_;
    }

    void SetIsAnimated(const bool isAnimated)
    {
        isAnimated_ = isAnimated;
    }

    bool GetIsAnimated() const
    {
        return isAnimated_;
    }

    void SetCanReused(bool canReused);

    bool GetCanReused() const;

    void SetInCurrentStack(bool inStack)
    {
        inCurrentStack_ = inStack;
    }

    bool GetInCurrentStack() const
    {
        return inCurrentStack_;
    }

    void SetNavDestinationPathInfo(const std::string& moduleName, const std::string& pagePath)
    {
        navDestinationPathInfo_ = pagePath;
        navDestinationModuleName_ = moduleName;
    }

    const std::string& GetNavDestinationPathInfo() const
    {
        return navDestinationPathInfo_;
    }
    
    int32_t GetNavigationNodeId() const;

    void SetNeedRemoveInPush(bool need)
    {
        needRemoveInPush_ = need;
    }

    bool NeedRemoveInPush() const
    {
        return needRemoveInPush_;
    }

    void SetSystemTransitionType(NavigationSystemTransitionType type)
    {
        systemTransitionType_ = type;
        if (navDestinationTransitionDelegate_) {
            TAG_LOGI(AceLogTag::ACE_NAVIGATION,
                "reset customTransition delegate of navDestination cause by setting systemTransition");
            navDestinationTransitionDelegate_ = nullptr;
        }
    }

    NavigationSystemTransitionType GetSystemTransitionType() const
    {
        return systemTransitionType_;
    }

    std::shared_ptr<AnimationUtils::Animation> BackButtonAnimation(bool isTransitionIn);
    std::shared_ptr<AnimationUtils::Animation> TitleOpacityAnimation(bool isTransitionOut);

    void SystemTransitionPushStart(bool transitionIn) override;
    void SystemTransitionPushEnd(bool transitionIn) override;
    void SystemTransitionPushFinish(bool transitionIn, int32_t animationId) override;

    void SystemTransitionPopStart(bool transitionIn) override;
    void SystemTransitionPopEnd(bool transitionIn) override;
    bool SystemTransitionPopFinish(int32_t animationId = -1, bool isNeedCleanContent = true) override;

    void InitSoftTransitionPush(bool transitionIn);
    void StartSoftTransitionPush(bool transitionIn);
    void InitSoftTransitionPop(bool isTransitionIn);
    void StartSoftTransitionPop(bool transitionIn);
    bool CheckTransitionPop(const int32_t animationId);
    void InitDialogTransition(bool isZeroY);
    bool IsNodeInvisible(const RefPtr<FrameNode>& node) override;

    void SetRecoverable(bool recoverable)
    {
        recoverable_ = recoverable;
    }

    void SetFromNavrouterAndNoRouteInfo(bool fromNavrouterAndNoRouteInfo)
    {
        fromNavrouterAndNoRouteInfo_ = fromNavrouterAndNoRouteInfo;
    }

    bool CanRecovery() const
    {
        return recoverable_ && !fromNavrouterAndNoRouteInfo_;
    }

    void SetNeedAppearFromRecovery(bool needAppear)
    {
        needAppearFromRecovery_ = needAppear;
    }

    bool NeedAppearFromRecovery() const
    {
        return needAppearFromRecovery_;
    }

    void UpdateTextNodeListAsRenderGroup(bool isPopPage, const RefPtr<NavigationTransitionProxy>& proxy);
    void ReleaseTextNodeList();
    void CollectTextNodeAsRenderGroup(bool isPopPage);

    void CleanContent(bool cleanDirectly = false, bool allowTransition = false);
    bool IsNeedContentTransition();
    bool TransitionContentInValid();
    bool IsNeedTitleTransition();

    std::string ToDumpString();

    void SetNeedForceMeasure(bool need)
    {
        needForceMeasure_ = need;
    }
    bool NeedForceMeasure() const
    {
        return needForceMeasure_;
    }

    void SetNavDestinationTransitionDelegate(NavDestinationTransitionDelegate&& delegate)
    {
        navDestinationTransitionDelegate_ = std::move(delegate);
    }

    int32_t DoTransition(NavigationOperation operation, bool isEnter);
    bool HasStandardBefore() const;

    void UpdateUserSetOpacity(float opacity)
    {
        userSetOpacity_ = opacity;
    }

    RefPtr<UINode> GetNavigationNode() override;

    void SetIsShowInPrimaryPartition(bool show)
    {
        isShowInPrimaryPartition_ = show;
    }
    bool IsShowInPrimaryPartition() const
    {
        return isShowInPrimaryPartition_;
    }
    RefPtr<NavDestinationGroupNode> GetOrCreatePlaceHolder();
    void SetPrimaryNode(const WeakPtr<NavDestinationGroupNode>& node)
    {
        primaryNode_ = node;
    }
    RefPtr<NavDestinationGroupNode> GetPrimaryNode() const
    {
        return primaryNode_.Upgrade();
    }

private:
    int32_t DoCustomTransition(NavigationOperation operation, bool isEnter);
    int32_t DoSystemTransition(NavigationOperation operation, bool isEnter);
    int32_t DoSystemFadeTransition(bool isEnter);
    int32_t DoSystemSlideTransition(NavigationOperation operation, bool isEnter);
    int32_t DoSystemExplodeTransition(NavigationOperation operation, bool isEnter);
    int32_t DoSystemEnterExplodeTransition(NavigationOperation operation);
    int32_t DoSystemExitExplodeTransition(NavigationOperation operation);
    void DoMaskAnimation(const AnimationOption& option, Color begin, Color end);
    void StartCustomTransitionAnimation(NavDestinationTransition& transition,
        bool isEnter, bool& hasResetProperties, int32_t longestAnimationDuration);
    int32_t MakeUniqueAnimationId();
    void ResetCustomTransitionAnimationProperties();

    std::optional<AnimationOption> GetTransitionAnimationOption(NavigationOperation operation, bool isEnter) const;
    std::function<void()> BuildTransitionFinishCallback(
        bool isSystemTransition = true, std::function<void()>&& extraOption = nullptr);
    std::function<void()> BuildEmptyFinishCallback();

    WeakPtr<CustomNodeBase> customNode_; // nearest parent customNode
    NavDestinationBackButtonEvent backButtonEvent_;
    bool isOnAnimation_ = false;
    int32_t index_ = -1;
    NavDestinationMode mode_ = NavDestinationMode::STANDARD;
    bool isCacheNode_ = false;
    bool isAnimated_ = true;
    bool canReused_ = true;
    bool inCurrentStack_ = true;
    bool recoverable_ = true;
    bool fromNavrouterAndNoRouteInfo_ = false;
    bool needAppearFromRecovery_ = false;
    std::string navDestinationPathInfo_;
    std::string navDestinationModuleName_;
    bool needRemoveInPush_ = false;
    std::list<WeakPtr<UINode>> textNodeList_;
    NavigationSystemTransitionType systemTransitionType_ = NavigationSystemTransitionType::DEFAULT;
    bool needForceMeasure_ = false;
    float userSetOpacity_ = 1.0f;

    NavDestinationTransitionDelegate navDestinationTransitionDelegate_;

    bool isShowInPrimaryPartition_ = false;
    RefPtr<NavDestinationGroupNode> placeHolderNode_;
    WeakPtr<NavDestinationGroupNode> primaryNode_;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVROUTER_NAVDESTINATION_GROUP_NODE_H
