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

    bool OnPrimaryPageDetected(const RefPtr<FrameNode>& primaryPage, LoadPlaceHolderPageCallback&& callback,
        const std::list<WeakPtr<FrameNode>>& pageStack);
    void RemoveSecondaryPagesOfPrimaryHomePage();
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

    void SetPrimaryPageTouched(bool primaryPageTouched)
    {
        primaryPageTouched_ = primaryPageTouched;
    }

    bool GetPrimaryPageTouched()
    {
        return primaryPageTouched_;
    }

    void SetNeedClearSecondaryPage(bool needClearSecondaryPage)
    {
        needClearSecondaryPage_ = needClearSecondaryPage;
    }
    bool ExchangePageFocus(bool &initFlag);
    bool UpdatePageFocus(RefPtr<FrameNode> &focusPage);

    std::vector<RefPtr<FrameNode>> GetTopPagesWithTransition() const override;
    bool IsSplitMode() const override;

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
    RefPtr<FrameNode> GetLastPrimaryPage();

    void FirePageHideOnPushPage(RouterPageType newPageType, const RefPtr<FrameNode>& lastPage,
        const RefPtr<FrameNode>& topPhPage, PageTransitionType hideTransitionType);
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

    bool GetPageNumberExcludePlaceHolderPage(int32_t& pageNumber);
    bool FirePageHideOnPopPageToIndex(int32_t popSize);
    bool FirePageShowOnPopPageToIndex(const RefPtr<ParallelStagePattern>& stagePattern,
        const RefPtr<FrameNode>& toPage, bool& addNewPhPage, PageTransitionType showTransitionType);
    bool PopPageToIndexInSplitMode(int32_t index, bool needShowNext, bool needTransition);

    bool CleanPageStackInSplitMode(const RefPtr<ParallelStagePattern>& stagePattern);

    RefPtr<FrameNode> RefreshAndGetLastPrimaryPage();
    void FirePageHideOnMovePageToFront(
        RouterPageType newTopPageType, const RefPtr<FrameNode>& preLastPage, PageTransitionType hideTransitionType);
    void FirePageShowOnMovePageToFront(
        const RefPtr<FrameNode>& preTopPage, const RefPtr<ParallelPagePattern>& preTopPattern,
        const RefPtr<FrameNode>& newTopPage, const RefPtr<ParallelPagePattern>& newTopPattern,
        PageTransitionType showTransitionType);
    RefPtr<FrameNode> GetPrePrimaryPage(const RefPtr<FrameNode>& preTopPage);
    bool MovePageToFrontInSplitMode(const RefPtr<FrameNode>& node, bool needHideLast, bool needTransition);

    bool RemovePlaceHolderPageIfExist(RefPtr<FrameNode>& phPage, bool needHidePlaceHolder = true);
    void MountAndShowPlaceHolderPageIfNeeded(
        const RefPtr<FrameNode>& phPage, PageTransitionType showTransitionType);
    bool IsEmptyInSplitMode();

    void FireParallelPageShow(const RefPtr<UINode>& node, PageTransitionType transitionType, bool needFocus = true);
    void FireParallelPageHide(const RefPtr<UINode>& node, PageTransitionType transitionType);

    std::list<WeakPtr<FrameNode>> secondaryPageStack_;
    bool isInStageOperation_ = false;
    bool primaryPageTouched_ = false;
    bool needClearSecondaryPage_ = false;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_STAGE_PRAALLEL_STAGE_MANAGER_H
