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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_NAVDESTINATION_NODE_BASE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_NAVDESTINATION_NODE_BASE_H

#include <cstdint>
#include <optional>

#include "core/animation/page_transition_common.h"
#include "core/common/display_info.h"
#include "core/common/page_viewport_config.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/group_node.h"
#include "core/components_ng/pattern/navigation/navigation_declaration.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/property/property.h"
#include "interfaces/inner_api/ace/viewport_config.h"

namespace OHOS::Ace::NG {
class NavDestinationNodeBase : public GroupNode {
    DECLARE_ACE_TYPE(NavDestinationNodeBase, GroupNode)
public:
    NavDestinationNodeBase(const std::string& tag, int32_t nodeId, const RefPtr<Pattern>& pattern)
        : GroupNode(tag, nodeId, pattern) {}
    ~NavDestinationNodeBase() override = default;

    bool IsAtomicNode() const override
    {
        return false;
    }

    void SetMenu(const RefPtr<UINode>& menu)
    {
        menu_ = menu;
    }

    const RefPtr<UINode>& GetMenu() const
    {
        return menu_;
    }

    void SetToolbarContainer(const RefPtr<UINode>& menu)
    {
        toolbarMenu_ = menu;
    }

    const RefPtr<UINode>& GetToolbarContainer() const
    {
        return toolbarMenu_;
    }

    void SetMenuNode(const RefPtr<UINode>& menuNode)
    {
        moreMenuNode_ = menuNode;
    }

    void SetToolbarMenuNode(const RefPtr<UINode>& menuNode)
    {
        toolbarMoreMenuNode_ = menuNode;
    }

    void SetLandscapeMenuNode(const RefPtr<UINode>& moreLandscapeMenuNode)
    {
        moreLandscapeMenuNode_ = moreLandscapeMenuNode;
    }

    void SetLandscapeMenu(const RefPtr<UINode>& menu)
    {
        landscapeMenu_ = menu;
    }

    const RefPtr<UINode>& GetLandscapeMenu() const
    {
        return landscapeMenu_;
    }

    void SetContentNode(const RefPtr<UINode>& contentNode)
    {
        contentNode_ = contentNode;
    }

    const RefPtr<UINode>& GetContentNode() const
    {
        return contentNode_;
    }

    void SetTitleBarNode(const RefPtr<UINode>& title)
    {
        titleBarNode_ = title;
    }

    const RefPtr<UINode>& GetTitleBarNode() const
    {
        return titleBarNode_;
    }

    void SetToolBarNode(const RefPtr<UINode>& toolBarNode)
    {
        toolBarNode_ = toolBarNode;
    }

    const RefPtr<UINode>& GetToolBarNode() const
    {
        return toolBarNode_;
    }

    void SetPreToolBarNode(const RefPtr<UINode>& preToolBarNode)
    {
        preToolBarNode_ = preToolBarNode;
    }

    const RefPtr<UINode>& GetPreToolBarNode() const
    {
        return preToolBarNode_;
    }

    void SetToolBarDividerNode(const RefPtr<UINode>& toolBarDividerNode)
    {
        toolBarDividerNode_ = toolBarDividerNode;
    }

    const RefPtr<UINode>& GetToolBarDividerNode() const
    {
        return toolBarDividerNode_;
    }

    void SetIsUseToolbarConfiguration(bool isNewToolbar)
    {
        isNewToolbar_ = isNewToolbar;
    }
    
    bool IsToolBarVisible() const;

    bool IsUseToolbarConfiguration() const
    {
        return isNewToolbar_;
    }

    std::string GetBarItemsString(bool isMenu) const;
    virtual bool IsNodeInvisible(const RefPtr<FrameNode>& node) { return false; }

    // custom node checking
    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(PrevTitleIsCustom, bool);
    void OnPrevTitleIsCustomUpdate(bool value) {}
    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(PrevMenuIsCustom, bool);
    void OnPrevMenuIsCustomUpdate(bool value) {}
    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(PrevToolBarIsCustom, bool);
    void OnPrevToolBarIsCustomUpdate(bool value) {}

    // node operation related
    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(MenuNodeOperation, ChildNodeOperation);
    void OnMenuNodeOperationUpdate(ChildNodeOperation value) {}
    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(ToolBarNodeOperation, ChildNodeOperation);
    void OnToolBarNodeOperationUpdate(ChildNodeOperation value) {}

    void SetTransitionType(PageTransitionType type)
    {
        transitionType_ = type;
    }

    PageTransitionType GetTransitionType() const
    {
        return transitionType_;
    }

    float GetLanguageDirection()
    {
        return AceApplicationInfo::GetInstance().IsRightToLeft() ? -1.0f : 1.0f;
    }

    void UpdateAnimationId(int32_t animationId)
    {
        animationId_ = animationId;
    }

    int32_t GetAnimationId() const
    {
        return animationId_;
    }

    virtual RefPtr<UINode> GetNavigationNode()
    {
        return nullptr;
    }

    bool CustomizeExpandSafeArea();
    void Measure(const std::optional<LayoutConstraintF>& parentConstraint) override;
    void Layout() override;

    void SetOrientation(const std::optional<Orientation>& ori)
    {
        orientation_ = ori;
    }
    const std::optional<Orientation>& GetOrientation() const
    {
        return orientation_;
    }
    void SetPreOrientation(const std::optional<Orientation>& ori)
    {
        preOrientation_ = ori;
    }
    const std::optional<Orientation>& GetPreOrientation() const
    {
        return preOrientation_;
    }
    void SetPageViewportConfig(const RefPtr<PageViewportConfig>& config);
    const RefPtr<PageViewportConfig>& GetPageViewportConfig() const
    {
        return viewportConfig_;
    }
    void SetPageRotateAngle(const std::optional<int32_t>& angle)
    {
        rotateAngle_ = angle;
    }
    const std::optional<int32_t>& GetPageRotateAngle() const
    {
        return rotateAngle_;
    }
    void SetIsRotated(bool rotate)
    {
        isRotated_ = rotate;
    }
    bool IsRotated() const
    {
        return isRotated_;
    }

    LayoutConstraintF AdjustLayoutConstarintIfNeeded(const LayoutConstraintF& originConstraint);

    void AdjustRenderContextIfNeeded();
    void RestoreRenderContext();

    void SetOnStartTransitionAnimationCallback(std::function<void()>&& callback)
    {
        onStartTransitionAnimationCb_ = std::move(callback);
    }
    void OnStartOneTransitionAnimation()
    {
        if (onStartTransitionAnimationCb_) {
            onStartTransitionAnimationCb_();
        }
    }
    void SetOnFinishTransitionAnimationCallback(std::function<void()>&& callback)
    {
        onFinishTransitionAnimationCb_ = std::move(callback);
    }
    void OnFinishOneTransitionAnimation()
    {
        if (onFinishTransitionAnimationCb_) {
            onFinishTransitionAnimationCb_();
        }
    }

    void SetStatusBarConfig(const std::optional<std::pair<bool, bool>>& status)
    {
        statusBarConfig_ = status;
    }
    const std::optional<std::pair<bool, bool>>& GetStatusBarConfig()
    {
        return statusBarConfig_;
    }
    void SetPreStatusBarConfig(const std::optional<std::pair<bool, bool>>& status)
    {
        preStatusBarConfig_ = status;
    }
    const std::optional<std::pair<bool, bool>>& GetPreStatusBarConfig()
    {
        return preStatusBarConfig_;
    }

    void SetNavigationIndicatorConfig(const std::optional<bool>& navigationIndicator)
    {
        navigationIndicatorConfig_ = navigationIndicator;
    }
    const std::optional<bool>& GetNavigationIndicatorConfig()
    {
        return navigationIndicatorConfig_;
    }
    void SetPreNavigationIndicatorConfig(const std::optional<bool>& navigationIndicator)
    {
        preNavigationIndicatorConfig_ = navigationIndicator;
    }
    const std::optional<bool>& GetPreNavigationIndicatorConfig()
    {
        return preNavigationIndicatorConfig_;
    }
    void SetIsSizeMatchNavigation(bool match)
    {
        isSizeMatchNavigation_ = match;
    }
    bool IsSizeMatchNavigation() const
    {
        return isSizeMatchNavigation_;
    }

protected:
    RectF CalcFullClipRectForTransition(const SizeF& frameSize);
    RectF CalcHalfClipRectForTransition(const SizeF& frameSize);
    // push
    OffsetF CalcTranslateForTransitionPushStart(const SizeF& frameSize, bool transitionIn);
    OffsetF CalcTranslateForTransitionPushEnd(const SizeF& frameSize, bool transitionIn);
    // pop
    OffsetF CalcTranslateForTransitionPopStart(const SizeF& frameSize, bool transitionIn);
    OffsetF CalcTranslateForTransitionPopEnd(const SizeF& frameSize, bool transitionIn);
    // Dialog
    TranslateOptions CalcContentTranslateForDialog(const SizeF& frameSize);
    // slide
    OffsetF CalcTranslateForSlideTransition(const SizeF& frameSize, bool isRight, bool isEnter, bool isEnd);

    OffsetF GetParentGlobalOffsetWithSafeArea(bool checkBoundary = false, bool checkPosition = false) const override;

    RefPtr<UINode> contentNode_;
    RefPtr<UINode> menu_;
    RefPtr<UINode> toolbarMenu_;
    RefPtr<UINode> landscapeMenu_;
    RefPtr<UINode> moreMenuNode_;
    RefPtr<UINode> toolbarMoreMenuNode_;
    RefPtr<UINode> moreLandscapeMenuNode_;
    RefPtr<UINode> titleBarNode_;
    RefPtr<UINode> toolBarNode_;
    RefPtr<UINode> preToolBarNode_;
    RefPtr<UINode> toolBarDividerNode_;
    bool isNewToolbar_ = false;
    int32_t animationId_ = -1;
    PageTransitionType transitionType_ = PageTransitionType::NONE;
    std::optional<Orientation> orientation_;
    std::optional<Orientation> preOrientation_;
    RefPtr<PageViewportConfig> viewportConfig_;
    SafeAreaInsets safeAreaInsets_;
    bool isRotated_ = false;
    std::optional<int32_t> rotateAngle_;
    bool isCustomExpandRunning_ = false;
    std::function<void()> onStartTransitionAnimationCb_;
    std::function<void()> onFinishTransitionAnimationCb_;
    // pair.first -> enable, pair.second -> animated
    std::optional<std::pair<bool, bool>> statusBarConfig_;
    std::optional<std::pair<bool, bool>> preStatusBarConfig_;
    std::optional<bool> navigationIndicatorConfig_;
    std::optional<bool> preNavigationIndicatorConfig_;
    bool isSizeMatchNavigation_ = true;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_NAVDESTINATION_NODE_BASE_H