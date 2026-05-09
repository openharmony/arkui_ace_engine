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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_STAGE_PARALLEL_STAGE_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_STAGE_PARALLEL_STAGE_MANAGER_H

#include "frameworks/base/utils/noncopyable.h"
#include "frameworks/core/components_ng/pattern/stage/stage_manager.h"
#include "frameworks/core/components_ng/pattern/stage/force_split/parallel_stage_pattern.h"

namespace OHOS::Ace::NG {
class ParallelStageManager : public StageManager {
    DECLARE_ACE_TYPE(ParallelStageManager, StageManager);
public:
    ParallelStageManager(const RefPtr<FrameNode>& stageNode);
    ~ParallelStageManager() = default;

    bool PushPage(const RefPtr<FrameNode>& node, bool needHideLast = true, bool needTransition = true,
        const std::function<bool()>&& pushIntentPageCallback = nullptr) override;
    bool PopPage(const RefPtr<FrameNode>& node, bool needShowNext = true, bool needTransition = true) override;
    bool PopPageToIndex(int32_t index, bool needShowNext = true, bool needTransition = true) override;
    bool CleanPageStack() override;
    bool MovePageToFront(const RefPtr<FrameNode>& node, bool needHideLast = true, bool needTransition = true) override;

    bool OnHomePageDetected(const RefPtr<FrameNode>& homePage, const std::list<WeakPtr<FrameNode>>& pageStack);
    void RemoveSecondaryPagesOfPrimaryPage();
    int32_t UpdateSecondaryPageNeedRemoved(bool needClearSecondaryPage);

    RefPtr<FrameNode> GetLastPage() const override;

    RefPtr<FrameNode> GetPrevPageWithTransition() const override;

    RefPtr<FrameNode> GetLastPageWithTransition() const override;

    RefPtr<FrameNode> GetFocusPage() const override;

    bool IsInStageOperation() const
    {
        return isInStageOperation_;
    }

    void SyncPageSafeArea(bool KeyboardSafeArea) override;

    bool CheckPageFocus() override;
    
    void MarkDirtyPageAndOverlay(const RefPtr<FrameNode>& needMarkDirtyPage, PropertyChangeFlag changeFlag);

    void SetHomePageTouched(bool homePageTouched)
    {
        homePageTouched_ = homePageTouched;
    }

    bool GetHomePageTouched()
    {
        return homePageTouched_;
    }

    void SetNeedClearSecondaryPage(bool needClearSecondaryPage)
    {
        needClearSecondaryPage_ = needClearSecondaryPage;
        if (!needClearSecondaryPage) {
            touchedPrimaryColumnPage_.Reset();
        }
    }
    bool ExchangePageFocus(bool &initFlag);
    bool UpdatePageFocus(RefPtr<FrameNode> &focusPage);

    std::vector<RefPtr<FrameNode>> GetTopPagesWithTransition() const override;
    bool IsSplitMode() const override;

    void UpdateIsTopFullScreenPage(bool isTopFullScreenPage)
    {
        if (isTopFullScreenPage_ == isTopFullScreenPage) {
            isTopFullScreenPageChanged_ = false;
        } else {
            isTopFullScreenPage_ = isTopFullScreenPage;
            isTopFullScreenPageChanged_ = true;
        }
    }

    bool IsTopFullScreenPageChanged() const
    {
        return isTopFullScreenPageChanged_;
    }

    bool IsTopFullScreenPage() const override
    {
        return isTopFullScreenPage_;
    }

    RefPtr<FrameNode> GetRelatedOrPlaceHolderPage();

    bool IsDisplaySplitMode() const override;

    RefPtr<FrameNode> GetTopPrimaryColumnPage() const;
    RefPtr<FrameNode> GetTopSecondaryColumnPage() const;

    struct RouterVisiblePages {
        RefPtr<FrameNode> primary = nullptr;
        RefPtr<FrameNode> detail = nullptr;
    };
    struct RouterAnimatedPageInfo {
        WeakPtr<FrameNode> page;
        PageTransitionType transitionType = PageTransitionType::NONE;
    };
    void SetTouchedPrimaryColumnPage(const RefPtr<FrameNode>& page)
    {
        touchedPrimaryColumnPage_ = page;
    }

    RefPtr<FrameNode> GetTouchedPrimaryColumnPage() const
    {
        return touchedPrimaryColumnPage_.Upgrade();
    }
    void SetTouchedSecondaryColumnPage(const RefPtr<FrameNode>& page)
    {
        touchedSecondaryColumnPage_ = page;
    }
    RefPtr<FrameNode> TakeTouchedSecondaryColumnPage()
    {
        auto page = touchedSecondaryColumnPage_.Upgrade();
        touchedSecondaryColumnPage_.Reset();
        return page;
    }
    void OnStageNodeStructureChanged() override;

private:
    class StageOptScope {
    public:
        explicit StageOptScope(ParallelStageManager* manager) : manager_(manager)
        {
            manager_->isInStageOperation_ = true;
        }
        ~StageOptScope()
        {
            manager_->isInStageOperation_ = false;
        }
    private:
        ParallelStageManager* manager_ = nullptr;
    };

    void OnModeChange();
    void OnWindowStateChange(bool show);
    RefPtr<FrameNode> GetHomePage() const;

    void FirePageHideOnPushPage(RouterPageType newPageType, const RefPtr<FrameNode>& lastPage,
        const RefPtr<FrameNode>& topRelatedOrPhPage, const RefPtr<FrameNode>& preHomePage,
        PageTransitionType hideTransitionType, bool newPageIsFullScreenPage);
    void FirePageShowOnPushPage(const RefPtr<FrameNode>& newTopPage,
        const RefPtr<ParallelPagePattern>& newTopPattern, PageTransitionType showTransitionType);
    bool PushPageInSplitMode(
        const RefPtr<FrameNode>& node, bool isNewLifecycle, bool needHideLast, bool needTransition);

    bool FirePageHideOnPopPage(const RefPtr<FrameNode>& topPhPage,
        const RefPtr<FrameNode>& preTopPage, const RefPtr<FrameNode>& newTopPage,
        const RefPtr<ParallelPagePattern>& newTopPattern, PageTransitionType hideTransitionType);
    bool FirePageShowOnPopPage(const RefPtr<FrameNode>& topPhPage,
        const RefPtr<FrameNode>& preTopPage, const RefPtr<ParallelPagePattern>& preTopPattern,
        const RefPtr<FrameNode>& newTopPage, const RefPtr<ParallelPagePattern>& newTopPattern,
        PageTransitionType showTransitionType);
    bool PopPageInSplitMode(bool needShowNext, bool needTransition);

    bool GetPageNumberExcludeRelatedOrPlaceHolderPage(int32_t& pageNumber);
    bool FirePageHideOnPopPageToIndex(int32_t popSize);
    bool FirePageShowOnPopPageToIndex(const RefPtr<ParallelStagePattern>& stagePattern,
        const RefPtr<FrameNode>& toPage, bool& addRelatedOrPhPage, PageTransitionType showTransitionType);
    bool PopPageToIndexInSplitMode(int32_t index, bool needShowNext, bool needTransition);

    bool CleanPageStackInSplitMode(const RefPtr<ParallelStagePattern>& stagePattern);

    void FirePageHideOnMovePageToFront(
        RouterPageType newTopPageType, const RefPtr<FrameNode>& preLastPage, PageTransitionType hideTransitionType);
    void FirePageShowOnMovePageToFront(
        const RefPtr<FrameNode>& preTopPage, const RefPtr<ParallelPagePattern>& preTopPattern,
        const RefPtr<FrameNode>& newTopPage, const RefPtr<ParallelPagePattern>& newTopPattern,
        PageTransitionType showTransitionType);
    bool MovePageToFrontInSplitMode(const RefPtr<FrameNode>& node, bool needHideLast, bool needTransition);

    bool RemoveRelatedOrPlaceHolderPageIfExist(RefPtr<FrameNode>& page, bool needHidePage = true);
    void MountAndShowRelatedOrPlaceHolderPageIfNeeded(
        const RefPtr<FrameNode>& page, PageTransitionType showTransitionType);
    bool IsEmptyInSplitMode();

    void FireParallelPageShow(const RefPtr<UINode>& node, PageTransitionType transitionType, bool needFocus = true);
    void FireParallelPageHide(const RefPtr<UINode>& node, PageTransitionType transitionType);
    void ReportPageTransitionEnd(const RefPtr<FrameNode>& page);

    void RebuildRouterColumnNodesIfNeeded() const;
    void InvalidateRouterColumnNodes() const;
    bool IsVirtualStackBasedSplit() const;
    void OnModeChangeInVirtualStackBasedSplit(const RefPtr<FrameNode>& lastPage);
    void OnWindowStateChangeInVirtualStackBasedSplit(bool show);
    bool PushPageInVirtualStackBasedSplit(
        const RefPtr<FrameNode>& node, bool isNewLifecycle, bool needHideLast, bool needTransition);
    bool PopPageInVirtualStackBasedSplit(bool needShowNext, bool needTransition);
    bool PopPageToIndexInVirtualStackBasedSplit(int32_t index, bool needShowNext, bool needTransition);
    bool CleanPageStackInVirtualStackBasedSplit(const RefPtr<ParallelStagePattern>& stagePattern);
    bool MovePageToFrontInVirtualStackBasedSplit(const RefPtr<FrameNode>& node, bool needHideLast, bool needTransition);

    void FireLifecycleOnPopByVisibleDiff(
        const RouterVisiblePages& preVisiblePages, const RouterVisiblePages& newVisiblePages,
        bool needShowNext, PageTransitionType hideTransitionType, PageTransitionType showTransitionType);
    void EnsureSplitSecondaryPageIfNeeded();
    bool HasRouterPushPageToPrimaryState() const;
    bool ShouldCurrentPushPageToPrimary(const RefPtr<FrameNode>& newPageNode) const;
    RefPtr<FrameNode> GetLastPageInStack() const;
    std::vector<RefPtr<FrameNode>> CollectRouterStackPages() const;
    std::vector<RefPtr<FrameNode>> CollectRouterStackPages(
        const std::vector<RefPtr<FrameNode>>& excludedPages) const;
    void UpdateRouterSplitPlaceholder();
    void FireRouterHideByVisibleDiff(const RouterVisiblePages& preVisiblePages,
        const RouterVisiblePages& newVisiblePages, PageTransitionType transitionType = PageTransitionType::NONE);
    void FireRouterShowByVisibleDiff(const RouterVisiblePages& preVisiblePages,
        const RouterVisiblePages& newVisiblePages, PageTransitionType transitionType = PageTransitionType::NONE);
    RouterVisiblePages GetRouterVisiblePagesForCurrentStackTree() const;
    RouterVisiblePages GetRouterVisiblePagesForCurrentSplitTree() const;
    RouterVisiblePages GetRouterVisiblePages();
    RouterVisiblePages ResolveRouterVisiblePagesFromStackPages(
        const std::vector<RefPtr<FrameNode>>& stackPages, const RefPtr<FrameNode>& secondaryFallbackPage) const;
    RouterVisiblePages GetRouterVisiblePagesExcluding(const std::vector<RefPtr<FrameNode>>& excludedPages);
    // Transition-end should follow the final actually visible result.
    // Prefer the right visible page, otherwise fall back to the left visible page.
    RefPtr<FrameNode> GetRouterTransitionEndPageForCurrentVisible();
    bool CheckIfMovePageToPrimaryIsAllowed(
        const RouterVisiblePages& preVisiblePages, const RouterVisiblePages& newVisiblePages) const;
    bool CheckIfMovePageToSecondaryIsAllowed(
        const RouterVisiblePages& preVisiblePages, const RouterVisiblePages& newVisiblePages) const;
    bool StartRouterSplitAnimation(
        const RouterVisiblePages& preVisiblePages, const RouterVisiblePages& newVisiblePages);
    bool StartSplitPushAnimation(const RouterVisiblePages& preVisiblePages, const RouterVisiblePages& newVisiblePages);
    bool StartSplitPopAnimation(const RouterVisiblePages& preVisiblePages, const RouterVisiblePages& newVisiblePages);
    void OnRouterPagesSplitPushStart(
        const RefPtr<FrameNode>& exitPage, const RefPtr<FrameNode>& movePage, const RefPtr<FrameNode>& enterPage);
    void OnRouterPagesSplitPushEnd(
        const RefPtr<FrameNode>& exitPage, const RefPtr<FrameNode>& movePage, const RefPtr<FrameNode>& enterPage);
    void OnRouterPagesSplitPopStart(
        const RefPtr<FrameNode>& enterPage, const RefPtr<FrameNode>& exitPage, const RefPtr<FrameNode>& movePage);
    void OnRouterPagesSplitPopEnd(
        const RefPtr<FrameNode>& enterPage, const RefPtr<FrameNode>& exitPage, const RefPtr<FrameNode>& movePage);
    void SetRouterDividerVisible(bool visible);
    void OnRouterPagesSplitFinish(
        const std::vector<RouterAnimatedPageInfo>& animatedPages, int32_t animationId);
    void ClearCurrentRouterAnimationState();
    void AddRouterAnimatedPage(
        const RefPtr<FrameNode>& page, PageTransitionType transitionType, int32_t animationId);
    void ResetRouterAnimatedPages();
    int32_t GetPrimaryNodeCount() const;
    ForceSplitPageColumnType GetPageColumnType(const RefPtr<FrameNode>& page) const;
    void SetPageColumnType(const RefPtr<FrameNode>& page, ForceSplitPageColumnType columnType);
    void ClearRouterPageState(const RefPtr<FrameNode>& page);
    bool IsSecondaryPushToPrimaryScene(const RefPtr<FrameNode>& prePrimaryTopPage,
        const RefPtr<FrameNode>& fromPage, const RefPtr<FrameNode>& toPage) const;
    bool ShouldMovePageToPrimaryForTransition(
        const RefPtr<FrameNode>& fromPage, const RefPtr<FrameNode>& toPage, bool onlyWhenSplit = true) const;
    bool FinalizeRouterStackChange(
        const RouterVisiblePages& beforeVisible, const RouterVisiblePages& afterVisible, bool needTransition);
    void NormalizeRouterColumnsAfterStackChange();
    void NormalizeRouterColumnsAfterStackChange(const RouterVisiblePages& afterVisible);
    void UpdateRouterColumnsOnPush(const RefPtr<FrameNode>& currentTopPage, const RefPtr<FrameNode>& newPageNode);
    void OnAbortAnimation() override;

    std::list<WeakPtr<FrameNode>> secondaryPageStack_;
    bool isInStageOperation_ = false;
    bool homePageTouched_ = false;
    bool needClearSecondaryPage_ = false;
    bool isTopFullScreenPage_ = false;
    bool isTopFullScreenPageChanged_ = false;
    mutable std::vector<WeakPtr<FrameNode>> primaryNodes_;
    mutable std::vector<WeakPtr<FrameNode>> secondaryNodes_;
    mutable bool routerColumnNodesDirty_ = true;
    WeakPtr<FrameNode> touchedPrimaryColumnPage_;
    WeakPtr<FrameNode> touchedSecondaryColumnPage_;
    std::vector<RouterAnimatedPageInfo> routerAnimatedPages_;
    WeakPtr<FrameNode> routerFocusOnFinishPage_;
    WeakPtr<FrameNode> routerTransitionEndPage_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_STAGE_PRAALLEL_STAGE_MANAGER_H
